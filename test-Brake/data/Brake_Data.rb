#-----------------------------------------------------------------------#
#  file: Brake_Data.rb                                                  #
#                                                                       #
#  version: 1.0   date 13/9/2020                                        #
#                                                                       #
#  Copyright (C) 2020                                                   #
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

# Auxiliary values

mechatronix do |data|

  # Level of message
  data.InfoLevel = 4

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads   = 4
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

  # Redirect output to GenericContainer["stream_output"]
  data.RedirectStreamToString = false

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "Brake_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'MINIMIZATION'
    :factorization => 'LU',
    # ==============================================================
    :Rcond     => 1e-14,  # reciprocal condition number threshold for QR, SVD, LSS, LSY
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
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY'
    # ==============================================
    :last_factorization => 'LU',
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
    :initial_x => SET,
    :initial_v => SET,
    :final_v   => SET,
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

    # Guess Parameters

    # Boundary Conditions
    :v_f => 0,
    :v_i => 1,
    :x_i => 0,

    # Post Processing Parameters

    # User Function Parameters

    # Continuation Parameters

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty type controls: "QUADRATIC", "QUADRATIC2", "PARABOLA", "CUBIC"
  # Barrier type controls: "LOGARITHMIC", "COS_LOGARITHMIC", "TAN2", "HYPERBOLIC"

  data.Controls = {}
  data.Controls[:aControl] = {
    :type      => 'LOGARITHMIC',
    :epsilon   => 0.01,
    :tolerance => 0.01
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: 'PENALTY_REGULAR', 'PENALTY_SMOOTH', 'PENALTY_PIECEWISE'
  # Barrier subtype: 'BARRIER_LOG', 'BARRIER_LOG_EXP', 'BARRIER_LOG0'
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:Tpositive] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
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
        :n      => 400,
      },
    ],
  };


end

# EOF
