#-----------------------------------------------------------------------#
#  file: CNOC_Data.rb                                                   #
#                                                                       #
#  version: 1.0   date 10/11/2022                                       #
#                                                                       #
#  Copyright (C) 2022                                                   #
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
tol_PATH                 = 0.01
epsi_ACC                 = 0.01
tol_ACC                  = 0.01
path_following_tolerance = 1.0e-05
tol_CTRL                 = 0.01
tol_COV                  = 0.01
epsi_COV                 = 0.01
epsi_PATH                = 0.01
epsi_VMAX                = 0.01
tol_VMAX                 = 0.01
jn_max                   = 65.0
epsi_CTRL                = 0.01
js_min                   = -50
js_max                   = 30.0
mesh_segments            = 100.0
v_nom                    = 0.173
deltaFeed                = v_nom
pf_error                 = path_following_tolerance

mechatronix do |data|

  data.Debug     = false  # activate run time debug
  data.Doctor    = false  # Enable doctor
  data.InfoLevel = 4      # Level of message
  data.Use_control_penalties_in_adjoint_equations = false
  data.Max_penalty_value = 1000

  #  _   _                        _
  # | |_| |__  _ __ ___  __ _  __| |___
  # | __| '_ \| '__/ _ \/ _` |/ _` / __|
  # | |_| | | | | |  __/ (_| | (_| \__ \
  #  \__|_| |_|_|  \___|\__,_|\__,_|___/

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads   = [1,$MAX_THREAD_NUM-1].max
  data.U_threaded  = true
  data.F_threaded  = true
  data.JF_threaded = true
  data.LU_threaded = true

  # Enable check jacobian and controls
  data.ControlsCheck         = true
  data.ControlsCheck_epsilon = 1e-6
  data.JacobianCheck         = true
  data.JacobianCheckFull     = false
  data.JacobianCheck_epsilon = 1e-4

  # jacobian discretization: 'ANALYTIC', 'ANALYTIC2', 'FINITE_DIFFERENCE'
  data.JacobianDiscretization = 'ANALYTIC'

  # jacobian discretization BC part: 'ANALYTIC', 'FINITE_DIFFERENCE'
  data.JacobianDiscretizationBC = 'ANALYTIC'

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "CNOC_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  #   ____            _             _   ____        _
  #  / ___|___  _ __ | |_ _ __ ___ | | / ___|  ___ | |_   _____ _ __
  # | |   / _ \| '_ \| __| '__/ _ \| | \___ \ / _ \| \ \ / / _ \ '__|
  # | |__| (_) | | | | |_| | | (_) | |  ___) | (_) | |\ V /  __/ |
  #  \____\___/|_| |_|\__|_|  \___/|_| |____/ \___/|_| \_/ \___|_|

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'Hyness', 'NewtonDumped', 'LevenbergMarquardt', 'YixunShi', 'QuasiNewton'
    :solver => 'NewtonDumped',
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV' for Hyness and NewtonDumped
    :factorization => 'LU',
    # ==============================================================
    :Iterative => false,
    :InfoLevel => -1, # suppress all messages
    # ==============================================================
    # 'LevenbergMarquardt', 'YixunShi', 'QuasiNewton'
    :initialize_control_solver => 'QuasiNewton',

    # solver parameters
    :NewtonDumped => {
      # "MERIT_D2", "MERIT_F2"
      # "MERIT_LOG_D2", "MERIT_LOG_F2"
      # "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2", "MERIT_LOG_F2_and_LOG_D2"
      :merit                => "MERIT_F2_and_D2",
      :max_iter             => 50,
      :max_step_iter        => 10,
      :max_accumulated_iter => 150,
      :tolerance            => 1.0e-10, # tolerance for stopping criteria
      :c1                   => 0.01, # Constant for Armijo step acceptance criteria
      :lambda_min           => 1.0e-10, # minimum lambda for linesearch
      :dump_min             => 0.25, # (0,0.5)  dumping factor for linesearch
      :dump_max             => 0.9, # (0.5,0.99)
      # Potenza `n` della funzione di interpolazione per minimizzazione
      # f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      :merit_power          => 6, # (2..100)
      # check that search direction and new estimated search direction have an angle less than check_angle
      # if check_angle == 0 no check is done
      :check_angle            => 120,
      :check_ratio_norm_two_f => 2,  # check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      :check_ratio_norm_two_d => 2,  # check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      :check_ratio_norm_one_f => 2,  # check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      :check_ratio_norm_one_d => 2,  # check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
    },

    :Hyness => {
      :max_iter  => 50,
      :tolerance => 1.0e-10
    },

    :LevenbergMarquardt => {
      :max_iter  => 50,
      :tolerance => 1.0e-10
    },

    :YixunShi => {
      :max_iter  => 50,
      :tolerance => 1.0e-10
    },

    :QuasiNewton => {
      :max_iter  => 50,
      :tolerance => 1.0e-10,
      # 'BFGS', 'DFP', 'SR1' for Quasi Newton
      :update => 'BFGS',
      # 'EXACT', 'ARMIJO'
      :linesearch => 'EXACT',
    },
  }

  #  ____        _
  # / ___|  ___ | |_   _____ _ __
  # \___ \ / _ \| \ \ / / _ \ '__|
  #  ___) | (_) | |\ V /  __/ |
  # |____/ \___/|_| \_/ \___|_|

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
    :solver => "NewtonDumped",
    # ===================================

    # solver parameters
    :NewtonDumped => {
      # "MERIT_D2", "MERIT_F2", "MERIT_LOG_D2", "MERIT_LOG_F2"
      # "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2", "MERIT_LOG_F2_and_LOG_D2"
      :merit                => "MERIT_F2_and_D2",
      :max_iter             => 300,
      :max_step_iter        => 40,
      :max_accumulated_iter => 800,

      :continuation => {
        :initial_step   => 0.2   , # -- initial step for continuation
        :min_step       => 0.001 , # -- minimum accepted step for continuation
        :reduce_factor  => 0.5   , # -- if continuation step fails, reduce step by this factor
        :augment_factor => 1.5   , # -- if step successful in less than few_iteration augment step by this factor
        :few_iterations => 8       # -- if step successful in less than few_iteration augment step by this factor
      },

      # tolerance for stopping criteria
      :tolerance => 1e-09,

      # Constant for Armijo step acceptance criteria
      :c1 => 0.01,

      # minimum lambda for linesearch
      :lambda_min => 1e-10,

      # dumping factor for linesearch
      :dump_min => 0.4, # (0,0.5)
      :dump_max => 0.95, # (0.5,0.99)

      # Potenza `n` della funzione di interpolazione per minimizzazione
      # f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      :merit_power => 2, # (2..100)

      # check that search direction and new estimated search direction have an angle less than check_angle
      # if check_angle == 0 no check is done
      :check_angle  => 120,

      # check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      :check_ratio_norm_two_f => 2,
      # check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      :check_ratio_norm_two_d => 2,
      # check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      :check_ratio_norm_one_f => 2,
      # check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
      :check_ratio_norm_one_d => 2,
    },

    :Hyness => {
      :max_iter             => 300,
      :max_step_iter        => 40,
      :max_accumulated_iter => 800,
      :tolerance            => 1e-09,
      :continuation => {
        :initial_step   => 0.2   , # -- initial step for continuation
        :min_step       => 0.001 , # -- minimum accepted step for continuation
        :reduce_factor  => 0.5   , # -- if continuation step fails, reduce step by this factor
        :augment_factor => 1.5   , # -- if step successful in less than few_iteration augment step by this factor
        :few_iterations => 8       # -- if step successful in less than few_iteration augment step by this factor
      }
    },

    # continuation parameters
    :ns_continuation_begin => 0,
    :ns_continuation_end   => 0,
  }

  #                                       _
  #  _ __   __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  # | '_ \ / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  # | |_) | (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  # | .__/ \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  # |_|

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
    # initilize or not lagrange multiplier with redundant linear system
    :initialize_multipliers => false,
    # 'use_guess', 'minimize', 'none'
    :initialize_controls    => 'use_guess'
  }

  data.Parameters = {

    # Model Parameters
    :jn_max    => jn_max,
    :js_max    => js_max,
    :js_min    => js_min,
    :deltaFeed => deltaFeed,

    # Guess Parameters

    # Boundary Conditions
    :an_f => 0.0,
    :an_i => 0.0,
    :as_f => 0.0,
    :as_i => 0.0,
    :n_f  => 0.0,
    :n_i  => 0.0,
    :vn_f => 0.0,
    :vn_i => 0.0,
    :vs_f => 0.0,
    :vs_i => 0.0,

    # Post Processing Parameters
    :an_max                   => 1.2,
    :as_max                   => 2.1,
    :ax_max                   => 2.1,
    :ay_max                   => 2.1,
    :pf_error                 => pf_error,
    :path_following_tolerance => path_following_tolerance,

    # User Function Parameters

    # Continuation Parameters

    # Constraints Parameters
  }

  #                              _
  #  _ __ ___   __ _ _ __  _ __ (_)_ __   __ _
  # | '_ ` _ \ / _` | '_ \| '_ \| | '_ \ / _` |
  # | | | | | | (_| | |_) | |_) | | | | | (_| |
  # |_| |_| |_|\__,_| .__/| .__/|_|_| |_|\__, |
  #                 |_|   |_|            |___/
  # functions mapped on objects
  data.MappedObjects = {}


  #                  _             _
  #   ___ ___  _ __ | |_ _ __ ___ | |___
  #  / __/ _ \| '_ \| __| '__/ _ \| / __|
  # | (_| (_) | | | | |_| | | (_) | \__ \
  #  \___\___/|_| |_|\__|_|  \___/|_|___/
  # Controls
  # Penalty subtype: QUADRATIC, PARABOLA, CUBIC, QUARTIC, BIPOWER
  # Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  data.Controls = {}
  data.Controls[:jsControl] = {
    :type      => 'LOGARITHMIC',
    :epsilon   => epsi_CTRL,
    :tolerance => tol_CTRL
  }

  data.Controls[:jnControl] = {
    :type      => 'LOGARITHMIC',
    :epsilon   => epsi_CTRL,
    :tolerance => tol_CTRL
  }



  #                      _             _       _
  #   ___ ___  _ __  ___| |_ _ __ __ _(_)_ __ | |_ ___
  #  / __/ _ \| '_ \/ __| __| '__/ _` | | '_ \| __/ __|
  # | (_| (_) | | | \__ \ |_| | | (_| | | | | | |_\__ \
  #  \___\___/|_| |_|___/\__|_|  \__,_|_|_| |_|\__|___/
  data.Constraints = {}
  #  _  _____
  # | ||_   _|
  # | |__| |
  # |____|_|
  # Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DLessThan
  data.Constraints[:timePositive] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_COV,
    :tolerance => tol_COV,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:vLimit] = {
    :subType   => "PENALTY_PIECEWISE",
    :epsilon   => epsi_VMAX,
    :tolerance => tol_VMAX,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:PathFollowingTolerance_min] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_PATH,
    :tolerance => tol_PATH,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:PathFollowingTolerance_max] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_PATH,
    :tolerance => tol_PATH,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:as_limit_min] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:as_limit_max] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:an_limit_min] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:an_limit_max] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:ax_limit_min] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:ax_limit_max] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:ay_limit_min] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:ay_limit_max] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => epsi_ACC,
    :tolerance => tol_ACC,
    :active    => true
  }
  # Constraint1D: none defined
  # Constraint2D: none defined


  #                             _
  #  _   _ ___  ___ _ __    ___| | __ _ ___ ___
  # | | | / __|/ _ \ '__|  / __| |/ _` / __/ __|
  # | |_| \__ \  __/ |    | (__| | (_| \__ \__ \
  #  \__,_|___/\___|_|     \___|_|\__,_|___/___/
  # User defined classes initialization
  # User defined classes: T O O L P A T H 2 D
  data.ToolPath2D =
  {
    :segments => [
      {
        :x0           => -0.01,
        :y0           => 0.0,
        :x1           => 0.02,
        :y1           => 0.002,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.002,
        :x1           => 0.05,
        :y1           => 0.0,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.05,
        :y0           => 0.0,
        :x1           => 0.05,
        :y1           => 0.01,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
        :angle0       => 0.0,
        :angle1       => 3.1415,
      },
      {
        :x0           => 0.05,
        :y0           => 0.01,
        :x1           => 0.02,
        :y1           => 0.012,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.012,
        :x1           => -0.01,
        :y1           => 0.01,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.01,
        :x1           => -0.01,
        :y1           => 0.02,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.02,
        :x1           => 0.02,
        :y1           => 0.022,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.022,
        :x1           => 0.05,
        :y1           => 0.02,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.05,
        :y0           => 0.02,
        :x1           => 0.05,
        :y1           => 0.03,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
        :angle0       => 0.0,
        :angle1       => 3.1415,
      },
      {
        :x0           => 0.05,
        :y0           => 0.03,
        :x1           => 0.02,
        :y1           => 0.032,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.032,
        :x1           => -0.01,
        :y1           => 0.03,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.03,
        :x1           => -0.01,
        :y1           => 0.04,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.04,
        :x1           => 0.02,
        :y1           => 0.042,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.042,
        :x1           => 0.05,
        :y1           => 0.04,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.05,
        :y0           => 0.04,
        :x1           => 0.05,
        :y1           => 0.05,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
        :angle0       => 0.0,
        :angle1       => 3.1415,
      },
      {
        :x0           => 0.05,
        :y0           => 0.05,
        :x1           => 0.02,
        :y1           => 0.052,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.052,
        :x1           => -0.01,
        :y1           => 0.05,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.05,
        :x1           => -0.01,
        :y1           => 0.06,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => -0.01,
        :y0           => 0.06,
        :x1           => 0.02,
        :y1           => 0.062,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
      {
        :x0           => 0.02,
        :y0           => 0.062,
        :x1           => 0.05,
        :y1           => 0.06,
        :feedRate     => v_nom,
        :spindleRate  => 3000.0,
        :crossSection => 1.0,
        :tolerance    => path_following_tolerance,
        :n            => mesh_segments,
      },
    ],
  };


end

# EOF
