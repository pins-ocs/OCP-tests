#-----------------------------------------------------------------------#
#  file: GoddardRocket_Data.rb                                          #
#                                                                       #
#  version: 1.0   date 26/2/2021                                        #
#                                                                       #
#  Copyright (C) 2021                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#


include Mechatronix

# User Header

# Auxiliary values
tol_v     = 0.01
epsi_T    = 0.01
tol_TS    = 0.01
m_i       = 1
epsi_TS   = 0.01
h_i       = 1
epsi_mass = 0.01
mc        = 0.6
tol_T     = 0.01
epsi_v    = 0.01
vc        = 620
m_f       = mc*m_i
g0        = 1
Dc        = 0.5*vc*m_i/g0
c         = 0.5*(g0*h_i)**(1/2.0)
Tmax      = 3.5*g0*m_i
tol_mass  = 0.01

mechatronix do |data|

  # activate run time debug
  data.Debug = false

  # Enable doctor
  data.Doctor = false

  # Level of message
  data.InfoLevel = 4

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads   = [1,$MAX_THREAD_NUM-1].max
  data.U_threaded  = true
  data.F_threaded  = true
  data.JF_threaded = true
  data.LU_threaded = true

  # Enable check jacobian
  data.JacobianCheck            = false
  data.JacobianCheckFull        = false
  data.JacobianCheck_epsilon    = 1e-4
  data.FiniteDifferenceJacobian = false

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "GoddardRocket_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'Hyness', 'NewtonDumped', 'LM', 'YS', 'QN'
    # 'LM' = Levenberg-Marquardt, 'YS' = Yixun Shi, 'QN' = Quasi Newton
    :solver => 'NewtonDumped',
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV' for Hyness and NewtonDumped
    :factorization => 'LU',
    # 'BFGS', 'DFP', 'SR1' for Quasi Newton
    :update => 'BFGS',
    # 'EXACT', 'ARMIJO'
    :linesearch => 'EXACT',
    # ==============================================================
    :MaxIter   => 50,
    :Tolerance => 1e-9,
    :Iterative => false,
    :InfoLevel => -1,     # suppress all messages
  }

  # setup solver
  data.Solver = {
    # Linear algebra factorization selection:
    # 'LU', 'QR', 'QRP', 'SUPERLU'
    # =================
    :factorization => 'LU',
    # =================

    # Last Block selection:
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
    # ==============================================
    :last_factorization => 'LU',
    #:last_factorization => 'PINV',
    # ==============================================

    # choose solves: Hyness, NewtonDumped
    # ===================================
    :solver => "Hyness",
    # ===================================

    # solver parameters
    :max_iter             => 300,
    :max_step_iter        => 40,
    :max_accumulated_iter => 800,
    :tolerance            => 9.999999999999999e-10,

    # continuation parameters
    :ns_continuation_begin => 0,
    :ns_continuation_end   => 1,
    :continuation => {
      :initial_step   => 0.2,   # initial step for continuation
      :min_step       => 0.001, # minimum accepted step for continuation
      :reduce_factor  => 0.5,   # p fails, reduce step by this factor
      :augment_factor => 1.5,   # if step successful in less than few_iteration augment step by this factor
      :few_iterations => 8,     #
    }
  }

  # Boundary Conditions
  data.BoundaryConditions = {
    :initial_h => SET,
    :initial_v => SET,
    :initial_m => SET,
    :final_m   => SET,
  }

  # Guess
  data.Guess = {
    # possible value: zero, default, none, warm
    :initialize => 'zero',
    # possible value: default, none, warm, spline, table
    :guess_type => 'default',
  }

  data.Parameters = {

    # Model Parameters
    :Tmax => Tmax,
    :c    => c,

    # Guess Parameters

    # Boundary Conditions
    :h_i => h_i,
    :m_f => m_f,
    :m_i => m_i,
    :v_i => 0,

    # Post Processing Parameters

    # User Function Parameters
    :Dc => Dc,
    :g0 => g0,
    :hc => 500,

    # Continuation Parameters
    :epsi_T     => epsi_T,
    :epsi_TS    => epsi_TS,
    :tol_T      => tol_T,
    :tol_TS     => tol_TS,
    :epsi_TSmin => 1e-10,
    :epsi_Tmin  => 1e-07,
    :tol_TSmin  => 0.001,
    :tol_Tmin   => 0.0001,

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC
  # Barrier subtype: LOGARITHMIC, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  data.Controls = {}
  data.Controls[:TControl] = {
    :type      => 'QUADRATIC',
    :epsilon   => epsi_T,
    :tolerance => tol_T
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:massPositive] = {
    :subType   => 'BARRIER_LOG',
    :epsilon   => epsi_mass,
    :tolerance => tol_mass,
    :active    => true
  }
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:vPositive] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => epsi_v,
    :tolerance => tol_v,
    :active    => true
  }
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:TSPositive] = {
    :subType   => 'BARRIER_LOG',
    :epsilon   => epsi_TS,
    :tolerance => tol_TS,
    :active    => true
  }
  # Constraint2D: none defined

  # User defined classes initialization
  # User defined classes: M E S H
  data.Mesh =
  {
    :s0       => 0,
    :segments => [
      {
        :length => 1,
        :n      => 1000,
      },
    ],
  };


end

# EOF
