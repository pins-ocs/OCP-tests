#-----------------------------------------------------------------------#
#  file: GoddardRocket_Data.rb                                          #
#                                                                       #
#  version: 1.0   date 3/6/2021                                         #
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
epsi_v    = 0.01
tol_TS    = 0.01
m_i       = 1
tol_T     = 0.01
h_i       = 1
epsi_T    = 0.01
g0        = 1
Tmax      = 3.5*g0*m_i
epsi_TS   = 0.01
tol_v     = 0.01
tol_mass  = 0.01
mc        = 0.6
m_f       = mc*m_i
epsi_mass = 0.01
vc        = 620
Dc        = 0.5*vc*m_i/g0
c         = 0.5*(g0*h_i)**(1/2.0)

mechatronix do |data|

  # activate run time debug
  data.Debug = true

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
    # 'LM' = Levenberg-Marquard'
    # 'YS' = Yixun Shi
    # 'QN' = Quasi Newton
    # ==============================================================
    # 'Hyness', 'NewtonDumped', 'LM', 'YS', 'QN'
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
    # ==============================================================
    # 'LM', 'YS', 'QN'
    :InitSolver    => 'QN',
    :InitMaxIter   => 10,
    :InitTolerance => 1e-4
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
    :last_factorization => 'LUPQ', # automatically use PINV if singular
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
    # initilize or not lagrange multiplier with redundant linear system
    :initialize_multipliers => false,
    # 'use_guess', 'minimize', 'none'
    :initialize_controls    => 'use_guess'
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
  # Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
  # Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  data.Controls = {}
  data.Controls[:TControl] = {
    :type      => 'QUADRATIC',
    :epsilon   => epsi_T,
    :tolerance => tol_T
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:massPositive] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_mass,
    :tolerance => tol_mass,
    :active    => true
  }
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:vPositive] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_v,
    :tolerance => tol_v,
    :active    => true
  }
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:TSPositive] = {
    :subType   => "BARRIER_LOG",
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
