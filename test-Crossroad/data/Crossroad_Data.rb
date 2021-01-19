#-----------------------------------------------------------------------#
#  file: Crossroad_Data.rb                                              #
#                                                                       #
#  version: 1.0   date 19/1/2021                                        #
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
jerk_min = -10
jerk_max = 10
wJ       = 1/jerk_max**2
v_max    = 30
L        = 100
s_f      = L

mechatronix do |data|

  # activate run time debug
  data.Debug = false

  # Level of message
  data.InfoLevel = 4

  # Activate dynamic debugging
  data.Debug = false

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads   = [1,$MAX_THREAD_NUM-1].max
  data.U_threaded  = true
  data.F_threaded  = true
  data.JF_threaded = true
  data.LU_threaded = true

  # Enable doctor
  data.Doctor = false

  # Enable check jacobian
  data.JacobianCheck            = false
  data.JacobianCheckFull        = false
  data.JacobianCheck_epsilon    = 1e-4
  data.FiniteDifferenceJacobian = false

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "Crossroad_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'Hyness', 'NewtonDumped', 'LM', 'YS', 'QN'
    # 'LM' = Levenberg–Marquardt, 'YS' = Yixun Shi, 'QN' = Quasi Newton
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
    :Iterative => true,
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
    :ns_continuation_end   => 0,
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
    :initial_s => SET,
    :initial_v => SET,
    :initial_a => SET,
    :final_s   => SET,
    :final_v   => SET,
    :final_a   => SET,
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
    :L         => L,
    :wJ        => wJ,
    :wT        => 10,
    :alat_max  => 4,
    :along_max => 4,
    :jerk_max  => jerk_max,
    :jerk_min  => jerk_min,

    # Guess Parameters
    :Vmean => 2,

    # Boundary Conditions
    :a_f => 0,
    :a_i => 0,
    :s_f => s_f,
    :s_i => 0,
    :v_f => 1,
    :v_i => 0,

    # Post Processing Parameters

    # User Function Parameters
    :kappa0 => 0,
    :kappa1 => 1/10.00,
    :kappa2 => 1/10.00,

    # Continuation Parameters

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC
  # Barrier subtype: LOGARITHMIC, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  data.Controls = {}
  data.Controls[:jerkControl] = {
    :type      => 'LOGARITHMIC',
    :epsilon   => 0.01,
    :tolerance => 0.01
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:Tpositive] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :active    => true
  }
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:AccBound] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:VelBound] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :min       => 0,
    :max       => v_max,
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
        :n      => 100,
        :length => 0.5,
      },
      {
        :n      => 100,
        :length => 0.5,
      },
    ],
  };


end

# EOF
