#-----------------------------------------------------------------------#
#  file: ICLOCS_ContinuousMP_Data.rb                                    #
#                                                                       #
#  version: 1.0   date 13/12/2021                                       #
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
xy_bound  = 2
xy_tol0   = 0.1
tol_ctrl  = 0.01
xy_tol    = xy_tol0
xy_eps0   = 0.1
xy_eps    = xy_eps0
epsi_ctrl = 0.01

mechatronix do |data|

  # activate run time debug
  data.Debug = true

  # Enable doctor
  data.Doctor = false

  # Level of message
  data.InfoLevel = 4

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
  data.ControlsCheck_epsilon = 1e-8
  data.JacobianCheck         = true
  data.JacobianCheckFull     = false
  data.JacobianCheck_epsilon = 1e-4

  # jacobian discretization: 'ANALYTIC', 'ANALYTIC2', 'FINITE_DIFFERENCE'
  data.JacobianDiscretization = 'ANALYTIC'

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "ICLOCS_ContinuousMP_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  #   ____            _             _   ____        _
  #  / ___|___  _ __ | |_ _ __ ___ | | / ___|  ___ | |_   _____ _ __
  # | |   / _ \| '_ \| __| '__/ _ \| | \___ \ / _ \| \ \ / / _ \ '__|
  # | |__| (_) | | | | |_| | | (_) | |  ___) | (_) | |\ V /  __/ |
  #  \____\___/|_| |_|\__|_|  \___/|_| |____/ \___/|_| \_/ \___|_|

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
    # ==============================================================
    :Iterative => false,
    :InfoLevel => -1,     # suppress all messages
    # ==============================================================
    # 'LM', 'YS', 'QN'
    :initialize_control_solver => 'QN',

    # solver parameters
    :NewtonDumped => {
      # "MERIT_D2", "MERIT_F2"
      # "MERIT_LOG_D2", "MERIT_LOG_F2"
      # "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2"
      :merit                => "MERIT_D2",
      :max_iter             => 50,
      :max_step_iter        => 10,
      :max_accumulated_iter => 150,
      :tolerance            => 1e-12, # tolerance for stopping criteria
      :c1                   => 0.01,  # Constant for Armijo step acceptance criteria
      :lambda_min           => 1e-10, # minimum lambda for linesearch
      :dump_min             => 0.4,   # (0,0.5)  dumping factor for linesearch
      :dump_max             => 0.9,   # (0.5,0.99)
      # Potenza `n` della funzione di interpolazione per minimizzazione
      # f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      :merit_power          => 4, # (2..100)
      # check that search direction and new estimated search direction have an angle less than check_angle
      # if check_angle == 0 no check is done
      :check_angle            => 120,
      :check_ratio_norm_two_f => 1.4,  # check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      :check_ratio_norm_two_d => 1.4,  # check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      :check_ratio_norm_one_f => 1.4,  # check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      :check_ratio_norm_one_d => 1.4,  # check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
    },

    :Hyness => {
      :max_iter  => 50,
      :tolerance => 1e-9
    },

    # 'LM' = Levenberg-Marquard'
    :LM => {
      :max_iter  => 50,
      :tolerance => 1e-9
    },

    # 'YS' = Yixun Shi
    :YS => {
      :max_iter  => 50,
      :tolerance => 1e-9
    },

    # 'QN' = Quasi Newton
    :QN => {
      :max_iter  => 50,
      :tolerance => 1e-9,
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
      # "MERIT_D2", "MERIT_F2"
      # "MERIT_LOG_D2", "MERIT_LOG_F2"
      # "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2"
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
      :dump_max => 0.9, # (0.5,0.99)

      # Potenza `n` della funzione di interpolazione per minimizzazione
      # f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      :merit_power => 2, # (2..100)

      # check that search direction and new estimated search direction have an angle less than check_angle
      # if check_angle == 0 no check is done
      :check_angle  => 120,

      # check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      :check_ratio_norm_two_f => 1.4,
      # check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      :check_ratio_norm_two_d => 1.4,
      # check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      :check_ratio_norm_one_f => 1.4,
      # check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
      :check_ratio_norm_one_d => 1.4,
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
    :ns_continuation_end   => 1,
  }

  #                                       _
  #  _ __   __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  # | '_ \ / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  # | |_) | (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  # | .__/ \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  # |_|

  # Boundary Conditions
  data.BoundaryConditions = {
    :initial_xx1    => SET,
    :initial_yy1    => SET,
    :X1_continuity  => SET,
    :X2_continuity  => SET,
    :X3_continuity  => SET,
    :X4_continuity  => SET,
    :X5_continuity  => SET,
    :X6_continuity  => SET,
    :X7_continuity  => SET,
    :X8_continuity  => SET,
    :X9_continuity  => SET,
    :X10_continuity => SET,
    :X11_continuity => SET,
    :X12_continuity => SET,
    :X13_continuity => SET,
    :X14_continuity => SET,
    :X15_continuity => SET,
    :X16_continuity => SET,
    :X17_continuity => SET,
    :X18_continuity => SET,
    :X19_continuity => SET,
    :Y1_continuity  => SET,
    :Y2_continuity  => SET,
    :Y3_continuity  => SET,
    :Y4_continuity  => SET,
    :Y5_continuity  => SET,
    :Y6_continuity  => SET,
    :Y7_continuity  => SET,
    :Y8_continuity  => SET,
    :Y9_continuity  => SET,
    :Y10_continuity => SET,
    :Y11_continuity => SET,
    :Y12_continuity => SET,
    :Y13_continuity => SET,
    :Y14_continuity => SET,
    :Y15_continuity => SET,
    :Y16_continuity => SET,
    :Y17_continuity => SET,
    :Y18_continuity => SET,
    :Y19_continuity => SET,
    :X1_initial     => SET,
    :X2_initial     => SET,
    :X3_initial     => SET,
    :X4_initial     => SET,
    :X5_initial     => SET,
    :X6_initial     => SET,
    :X7_initial     => SET,
    :X8_initial     => SET,
    :X9_initial     => SET,
    :X10_initial    => SET,
    :X11_initial    => SET,
    :X12_initial    => SET,
    :X13_initial    => SET,
    :X14_initial    => SET,
    :X15_initial    => SET,
    :X16_initial    => SET,
    :X17_initial    => SET,
    :X18_initial    => SET,
    :X19_initial    => SET,
    :X20_initial    => SET,
    :Y1_initial     => SET,
    :Y2_initial     => SET,
    :Y3_initial     => SET,
    :Y4_initial     => SET,
    :Y5_initial     => SET,
    :Y6_initial     => SET,
    :Y7_initial     => SET,
    :Y8_initial     => SET,
    :Y9_initial     => SET,
    :Y10_initial    => SET,
    :Y11_initial    => SET,
    :Y12_initial    => SET,
    :Y13_initial    => SET,
    :Y14_initial    => SET,
    :Y15_initial    => SET,
    :Y16_initial    => SET,
    :Y17_initial    => SET,
    :Y18_initial    => SET,
    :Y19_initial    => SET,
    :Y20_initial    => SET,
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

    # Guess Parameters

    # Boundary Conditions

    # Post Processing Parameters

    # User Function Parameters

    # Continuation Parameters
    :xy_eps0 => xy_eps0,
    :xy_eps1 => 0.001,
    :xy_tol0 => xy_tol0,
    :xy_tol1 => 0.001,

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
  # Controls: No penalties or barriers constraint defined
  data.Controls = {}


  #                      _             _       _
  #   ___ ___  _ __  ___| |_ _ __ __ _(_)_ __ | |_ ___
  #  / __/ _ \| '_ \/ __| __| '__/ _` | | '_ \| __/ __|
  # | (_| (_) | | | \__ \ |_| | | (_| | | | | | |_\__ \
  #  \___\___/|_| |_|___/\__|_|  \__,_|_|_| |_|\__|___/
  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DInterval
  data.Constraints[:u1Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u2Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u3Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u4Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u5Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u6Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u7Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u8Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u9Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u10Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u11Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u12Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u13Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u14Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u15Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u16Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u17Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u18Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u19Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:u20Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl,
    :min       => -10,
    :max       => 10,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx1Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy1Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx2Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy2Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx3Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy3Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx4Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy4Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx5Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy5Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx6Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy6Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx7Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy7Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx8Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy8Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx9Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy9Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx10Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy10Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx11Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy11Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx12Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy12Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx13Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy13Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx14Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy14Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx15Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy15Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx16Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy16Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx17Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy17Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx18Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy18Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx19Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy19Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:xx20Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # PenaltyBarrier1DInterval
  data.Constraints[:yy20Limitation] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => xy_eps,
    :tolerance => xy_tol,
    :min       => -xy_bound,
    :max       => xy_bound,
    :active    => true
  }
  # Constraint2D: none defined


  #                             _
  #  _   _ ___  ___ _ __    ___| | __ _ ___ ___
  # | | | / __|/ _ \ '__|  / __| |/ _` / __/ __|
  # | |_| \__ \  __/ |    | (__| | (_| \__ \__ \
  #  \__,_|___/\___|_|     \___|_|\__,_|___/___/
  # User defined classes initialization
  # User defined classes: M E S H
  data.Mesh =
  {
    :s0       => 0,
    :segments => [
      {
        :n      => 50,
        :length => 1,
      },
    ],
  };


end

# EOF