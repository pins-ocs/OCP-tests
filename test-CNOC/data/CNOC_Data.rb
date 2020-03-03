#-----------------------------------------------------------------------#
#  file: CNOC_Data.rb                                                   #
#                                                                       #
#  version: 1.0   date 28/3/2020                                        #
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
js_min                   = -50
js_max                   = 30
jn_max                   = 65
path_following_tolerance = 1.0e-05
pf_error                 = path_following_tolerance
mesh_segments            = 100
v_nom                    = 0.173
deltaFeed                = v_nom

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
  #data.DumpFile = "CNOC_dump"

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
    :initial_n  => SET,
    :initial_vs => SET,
    :initial_vn => SET,
    :initial_as => SET,
    :initial_an => SET,
    :final_n    => SET,
    :final_vs   => SET,
    :final_vn   => SET,
    :final_as   => SET,
    :final_an   => SET,
    :initial_s  => SET,
    :final_s    => SET,
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
    :an_max                   => 1.2,
    :as_max                   => 2.1,
    :ax_max                   => 2.1,
    :ay_max                   => 2.1,
    :jn_max                   => jn_max,
    :js_max                   => js_max,
    :js_min                   => js_min,
    :deltaFeed                => deltaFeed,
    :path_following_tolerance => path_following_tolerance,

    # Guess Parameters

    # Boundary Conditions
    :an_f => 0,
    :an_i => 0,
    :as_f => 0,
    :as_i => 0,
    :n_f  => 0,
    :n_i  => 0,
    :vn_f => 0,
    :vn_i => 0,
    :vs_f => 0,
    :vs_i => 0,

    # Post Processing Parameters
    :pf_error => pf_error,

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
  data.Controls[:jsControl] = {
    :type      => 'LOGARITHMIC',
    :epsilon   => 0.01,
    :tolerance => 0.01
  }

  data.Controls[:jnControl] = {
    :type      => 'LOGARITHMIC',
    :epsilon   => 0.01,
    :tolerance => 0.01
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: 'PENALTY_REGULAR', 'PENALTY_SMOOTH', 'PENALTY_PIECEWISE'
  # Barrier subtype: 'BARRIER_LOG', 'BARRIER_LOG_EXP', 'BARRIER_LOG0'
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:timePositive] = {
    :subType   => 'BARRIER_LOG',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :active    => true
  }
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:vLimit] = {
    :subType   => 'PENALTY_PIECEWISE',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:PathFollowingTolerance] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.1,
    :min       => -1,
    :max       => 1,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:as_limit] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :min       => -1,
    :max       => 1,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:an_limit] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :min       => -1,
    :max       => 1,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:ax_limit] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :min       => -1,
    :max       => 1,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:ay_limit] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.01,
    :tolerance => 0.01,
    :min       => -1,
    :max       => 1,
    :active    => true
  }
  # Constraint2D: none defined

  # User defined classes initialization
  # User defined classes: T O O L P A T H 2 D
  data.ToolPath2D =
  {
    :segments => [
      {
        :x0           => -0.01,
        :y0           => 0,
        :x1           => 0.02,
        :y1           => 0.002,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.002,
        :x1           => 0.05,
        :y1           => 0,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.05,
        :y0           => 0,
        :x1           => 0.05,
        :y1           => 0.01,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
        :angle0       => 0,
        :angle1       => 3.1415,
      },
      {
        :x0           => 0.05,
        :y0           => 0.01,
        :x1           => 0.02,
        :y1           => 0.012,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.012,
        :x1           => -0.01,
        :y1           => 0.01,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.01,
        :x1           => -0.01,
        :y1           => 0.02,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.02,
        :x1           => 0.02,
        :y1           => 0.022,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.022,
        :x1           => 0.05,
        :y1           => 0.02,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.05,
        :y0           => 0.02,
        :x1           => 0.05,
        :y1           => 0.03,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
        :angle0       => 0,
        :angle1       => 3.1415,
      },
      {
        :x0           => 0.05,
        :y0           => 0.03,
        :x1           => 0.02,
        :y1           => 0.032,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.032,
        :x1           => -0.01,
        :y1           => 0.03,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.03,
        :x1           => -0.01,
        :y1           => 0.04,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.04,
        :x1           => 0.02,
        :y1           => 0.042,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.042,
        :x1           => 0.05,
        :y1           => 0.04,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.05,
        :y0           => 0.04,
        :x1           => 0.05,
        :y1           => 0.05,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
        :angle0       => 0,
        :angle1       => 3.1415,
      },
      {
        :x0           => 0.05,
        :y0           => 0.05,
        :x1           => 0.02,
        :y1           => 0.052,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.052,
        :x1           => -0.01,
        :y1           => 0.05,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.05,
        :x1           => -0.01,
        :y1           => 0.06,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.06,
        :x1           => 0.02,
        :y1           => 0.062,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.062,
        :x1           => 0.05,
        :y1           => 0.06,
        :feedRate     => v_nom,
        :spindleRate  => 3000,
        :crossSection => 1,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
    ],
  };


end

# EOF
