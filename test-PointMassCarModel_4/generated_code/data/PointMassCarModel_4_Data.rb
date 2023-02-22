#-----------------------------------------------------------------------#
#  file: PointMassCarModel_4_Data.rb                                    #
#                                                                       #
#  version: 1.0   date 22/2/2023                                        #
#                                                                       #
#  Copyright (C) 2023                                                   #
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
wT0       = 0.01
road_tol0 = 0.01
p_epsi0   = 0.1
wT        = wT0
up_tol0   = 0.01
up_epsi0  = 0.1
p_tol0    = 0.1
m         = 700.0
kD        = 0.2500000000/m

mechatronix do |data|

  data.Debug             = false  # activate run time debug
  data.Doctor            = false  # Enable doctor
  data.InfoLevel         = 4      # Level of message
  data.Max_penalty_value = 1000

  #  _   _                        _
  # | |_| |__  _ __ ___  __ _  __| |___
  # | __| '_ \| '__/ _ \/ _` |/ _` / __|
  # | |_| | | | | |  __/ (_| | (_| \__ \
  #  \__|_| |_|_|  \___|\__,_|\__,_|___/

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads             = [1,$MAX_THREAD_NUM-1].max
  data.U_threaded            = true
  data.JU_threaded           = true
  data.F_threaded            = true
  data.JF_threaded           = true
  data.LU_threaded           = true
  data.LU_factorize_threaded = true
  data.LU_solve_threaded     = true


  # Enable check jacobian and controls
  data.MuCheck_epsilon       = 1e-6
  data.MuCheck               = false
  data.ControlsCheck         = true
  data.ControlsCheck_epsilon = 1e-6
  data.JacobianCheck         = true
  data.JacobianCheckFull     = false
  data.JacobianCheck_epsilon = 1e-4

  # jacobian discretization: 'ANALYTIC', 'FINITE_DIFFERENCE'
  data.JacobianDiscretization = 'ANALYTIC'

  # jacobian discretization BC part: 'ANALYTIC', 'FINITE_DIFFERENCE'
  data.JacobianDiscretizationBC = 'ANALYTIC'

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "PointMassCarModel_4_dump"

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
    :ns_continuation_end   => 2,
  }

  #                                       _
  #  _ __   __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  # | '_ \ / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  # | |_) | (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  # | .__/ \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  # |_|

  # Boundary Conditions
  data.BoundaryConditions = {
    :initial_V    => SET,
    :initial_s    => SET,
    :final_s      => SET,
    :cyclic_n     => SET,
    :cyclic_alpha => SET,
    :cyclic_V     => SET,
    :cyclic_fx    => SET,
    :cyclic_Omega => SET,
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
    :kD            => kD,
    :wT            => wT,
    :v__Omega__max => 5.0,
    :v__fx__max    => 30.0,

    # Guess Parameters
    :Vguess => 10.0,

    # Boundary Conditions
    :V0 => 0.0,

    # Post Processing Parameters
    :Pmax       => 200000.0,
    :g          => 9.806,
    :m          => m,
    :mu__x__max => 1.0,
    :mu__y__max => 1.5,

    # User Function Parameters

    # Continuation Parameters
    :p_epsi0  => p_epsi0,
    :p_epsi1  => 0.001,
    :wT0      => wT0,
    :wT1      => 1.0,
    :up_epsi0 => up_epsi0,
    :up_epsi1 => 0.01,

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
  data.Controls[:v__fxControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => up_epsi0,
    :tolerance => up_tol0
  }

  data.Controls[:v__OmegaControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => up_epsi0,
    :tolerance => up_tol0
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
  data.Constraints[:AdherenceEllipse] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => p_epsi0,
    :tolerance => p_tol0,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:RoadLeftBorder] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => p_epsi0,
    :tolerance => road_tol0,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:RoadRightBorder] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => p_epsi0,
    :tolerance => road_tol0,
    :active    => true
  }
  # PenaltyBarrier1DLessThan
  data.Constraints[:PowerLimit] = {
    :subType   => "PENALTY_REGULAR",
    :epsilon   => p_epsi0,
    :tolerance => p_tol0,
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
  # User defined classes: R O A D
  data.Road =
  {
    :theta0   => 0.0,
    :s0       => 0.0,
    :x0       => 0.0,
    :y0       => 0.0,
    :is_SAE   => false,
    :segments => [
      {
        :curvature  => 0.0,
        :leftWidth  => 15/2.0,
        :length     => 190.0,
        :gridSize   => 1.0,
        :rightWidth => 60.0,
      },
      {
        :curvature  => 0.003225806452,
        :leftWidth  => 60.0,
        :length     => 973.8937227,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => 0.0,
        :leftWidth  => 30.0,
        :length     => 180.0,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => 0.006666666667,
        :leftWidth  => 20.0,
        :length     => 235.619449,
        :gridSize   => 1.0,
        :rightWidth => 15.0,
      },
      {
        :curvature  => 0.0,
        :leftWidth  => 30.0,
        :length     => 240.0,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => -1/150.0,
        :leftWidth  => 30.0,
        :length     => 235.619449,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => 0.0,
        :leftWidth  => 30.0,
        :length     => 200.0,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => 0.025,
        :leftWidth  => 30.0,
        :length     => 125.6637062,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => 0.0,
        :leftWidth  => 30.0,
        :length     => 480.0,
        :gridSize   => 1.0,
        :rightWidth => 30.0,
      },
      {
        :curvature  => 0.0,
        :leftWidth  => 30.0,
        :length     => 10.0,
        :gridSize   => 0.1,
        :rightWidth => 30.0,
      },
    ],
  };


end

# EOF
