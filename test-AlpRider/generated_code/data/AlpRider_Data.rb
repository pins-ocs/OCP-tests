#-----------------------------------------------------------------------#
#  file: AlpRider_Data.rb                                               #
#                                                                       #
#  version: 1.0   date 17/4/2022                                        #
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
tol0  = 0.1
tol   = tol0
W0    = 0
epsi0 = 0.1
epsi  = epsi0
W     = W0

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
  #data.DumpFile = "AlpRider_dump"

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
      :merit                => "MERIT_D2",
      :max_iter             => 50,
      :max_step_iter        => 10,
      :max_accumulated_iter => 150,
      :tolerance            => 1e-10, # tolerance for stopping criteria
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

    :LevenbergMarquardt => {
      :max_iter  => 50,
      :tolerance => 1e-9
    },

    :YixunShi => {
      :max_iter  => 50,
      :tolerance => 1e-9
    },

    :QuasiNewton => {
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
      # "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2", "MERIT_LOG_F2_and_LOG_D2"
      :merit                => "MERIT_LOG_F2_and_D2",
      :max_iter             => 300,
      :max_step_iter        => 20,
      :max_accumulated_iter => 10000,

      :continuation => {
        :initial_step   => 0.2   , # -- initial step for continuation
        :min_step       => 1e-06 , # -- minimum accepted step for continuation
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
      :max_step_iter        => 20,
      :max_accumulated_iter => 10000,
      :tolerance            => 1e-09,
      :continuation => {
        :initial_step   => 0.2   , # -- initial step for continuation
        :min_step       => 1e-06 , # -- minimum accepted step for continuation
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
    :initial_y1 => SET,
    :initial_y2 => SET,
    :initial_y3 => SET,
    :initial_y4 => SET,
    :final_y1   => SET,
    :final_y2   => SET,
    :final_y3   => SET,
    :final_y4   => SET,
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
    :W => W,

    # Guess Parameters

    # Boundary Conditions
    :y1_f => 2,
    :y1_i => 2,
    :y2_f => 3,
    :y2_i => 1,
    :y3_f => 1,
    :y3_i => 2,
    :y4_f => -2,
    :y4_i => 1,

    # Post Processing Parameters

    # User Function Parameters

    # Continuation Parameters
    :W0    => W0,
    :W1    => 100,
    :epsi0 => epsi0,
    :epsi1 => 0.001,
    :tol0  => tol0,
    :tol1  => 0.001,

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
  #  _  _____
  # | ||_   _|
  # | |__| |
  # |____|_|
  # Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DLessThan
  data.Constraints[:Ybound] = {
    :subType   => "BARRIER_LOG",
    :epsilon   => epsi,
    :tolerance => tol,
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
  # User defined classes: M E S H
  data.Mesh =
  {
    :s0       => 0,
    :segments => [
      {
        :length => 20,
        :n      => 4000,
      },
    ],
  };


end

# EOF