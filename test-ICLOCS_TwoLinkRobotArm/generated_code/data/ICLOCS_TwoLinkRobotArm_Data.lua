--[[
/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Data.lua                                |
 |                                                                       |
 |  version: 1.0   date 14/12/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/

--]]

-- User Header

-- Auxiliary values
u_epsilon0   = 0.01
u_epsilon    = u_epsilon0
u_tolerance0 = 0.01
u_tolerance  = u_tolerance0

content = {

  -- activate run time debug
  data.Debug = true,

  -- Enable doctor
  Doctor = false,

  -- Level of message
  InfoLevel = 4,

  --[[
   _   _                        _
  | |_| |__  _ __ ___  __ _  __| |___
  | __| '_ \| '__/ _ \/ _` |/ _` / __|
  | |_| | | | | |  __/ (_| | (_| \__ \
   \__|_| |_|_|  \___|\__,_|\__,_|___/
  --]]

  -- maximum number of threads used for linear algebra and various solvers
  N_threads   = [1,$MAX_THREAD_NUM-1].max,
  U_threaded  = true,
  F_threaded  = true,
  JF_threaded = true,
  LU_threaded = true,

  -- Enable check jacobian and controls
  ControlsCheck         = true,
  ControlsCheck_epsilon = 1e-8,
  JacobianCheck         = false,
  JacobianCheckFull     = false,
  JacobianCheck_epsilon = 1e-4,

  -- Jacobian discretization: 'ANALYTIC', 'ANALYTIC2', 'FINITE_DIFFERENCE'
  JacobianDiscretization = 'ANALYTIC,

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "ICLOCS_TwoLinkRobotArm_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  --[[
    ____            _             _   ____        _
   / ___|___  _ __ | |_ _ __ ___ | | / ___|  ___ | |_   _____ _ __
  | |   / _ \| '_ \| __| '__/ _ \| | \___ \ / _ \| \ \ / / _ \ '__|
  | |__| (_) | | | | |_| | | (_) | |  ___) | (_) | |\ V /  __/ |
   \____\___/|_| |_|\__|_|  \___/|_| |____/ \___/|_| \_/ \___|_|

  --]]

  -- setup solver for controls
  ControlSolver = {
    -- 'LM' = Levenberg-Marquard'
    -- 'YS' = Yixun Shi
    -- 'QN' = Quasi Newton
    -- 'Hyness', 'NewtonDumped', 'LM', 'YS', 'QN'
    solver = 'NewtonDumped',
    -- 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV' for Hyness and NewtonDumped
    factorization = 'LU',
    Iterative = true,
    InfoLevel = -1, -- suppress all messages
    -- 'LM', 'YS', 'QN'
    initialize_control_solver = 'QN',

    -- solver parameters
    NewtonDumped = {
      -- "MERIT_D2", "MERIT_F2"
      -- "MERIT_LOG_D2", "MERIT_LOG_F2"
      -- "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2"
      merit                = "MERIT_D2",
      max_iter             = 50,
      max_step_iter        = 10,
      max_accumulated_iter = 150,
      tolerance            = 1e-9,  -- tolerance for stopping criteria
      c1                   = 0.01,  -- Constant for Armijo step acceptance criteria
      lambda_min           = 1e-10, -- minimum lambda for linesearch
      dump_min             = 0.4,   -- (0,0.5)  dumping factor for linesearch
      dump_max             = 0.8,   -- (0.5,0.99)
      -- Potenza `n` della funzione di interpolazione per minimizzazione
      -- f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      merit_power          = 4, -- (2..100)
      -- check that search direction and new estimated search direction have an angle less than check_angle
      -- if check_angle == 0 no check is done
      check_angle            = 120,
      check_ratio_norm_two_f = 1.4,  -- check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      check_ratio_norm_two_d = 1.4,  -- check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      check_ratio_norm_one_f = 1.4,  -- check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      check_ratio_norm_one_d = 1.4,  -- check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
    },

    Hyness = { max_iter = 50, tolerance = 1e-9 },

    -- 'LM' = Levenberg-Marquard'
    LM = { max_iter = 50, tolerance = 1e-9 },

    -- 'YS' = Yixun Shi
    YS = { max_iter = 50, tolerance = 1e-9 },

    -- 'QN' = Quasi Newton
    QN = {
      max_iter  = 50,
      tolerance = 1e-9,
      -- 'BFGS', 'DFP', 'SR1' for Quasi Newton
      update = 'BFGS',
      -- 'EXACT', 'ARMIJO'
      linesearch = 'EXACT',
    },
  }

  --[[
   ____        _
  / ___|  ___ | |_   _____ _ __
  \___ \ / _ \| \ \ / / _ \ '__|
   ___) | (_) | |\ V /  __/ |
  |____/ \___/|_| \_/ \___|_|

  --]]

  -- setup solver
  Solver = {
    -- Linear algebra factorization selection:
    -- 'LU', 'QR', 'QRP', 'SUPERLU'
    factorization = 'LU',

    -- Last Block selection:
    -- 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
    last_factorization = 'LUPQ', -- automatically use PINV if singular

    -- choose solves: Hyness, NewtonDumped
    solver = "NewtonDumped",

    -- solver parameters
    NewtonDumped = {
      -- "MERIT_D2", "MERIT_F2"
      -- "MERIT_LOG_D2", "MERIT_LOG_F2"
      -- "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2"
      merit                = "MERIT_F2_and_D2",
      max_iter             = 300,
      max_step_iter        = 40,
      max_accumulated_iter = 800,
      continuation = {
        initial_step   = 0.2   , -- initial step for continuation
        min_step       = 0.001 , -- minimum accepted step for continuation
        reduce_factor  = 0.5   , -- if continuation step fails, reduce step by this factor
        augment_factor = 1.5   , -- if step successful in less than few_iteration augment step by this factor
        few_iterations = 8       -- if step successful in less than few_iteration augment step by this factor
      },

      -- tolerance for stopping criteria
      tolerance = 1e-09,

      -- Constant for Armijo step acceptance criteria
      c1 = 0.01,

      -- minimum lambda for linesearch
      lambda_min = 1e-10,

      -- dumping factor for linesearch
      dump_min = 0.4, -- (0,0.5)
      dump_max = 0.9, -- (0.5,0.99)

      -- Potenza `n` della funzione di interpolazione per minimizzazione
      -- f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      merit_power = 3, -- (2..100)

      -- check that search direction and new estimated search direction have an angle less than check_angle
      -- if check_angle == 0 no check is done
      check_angle = 120,

      -- check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      check_ratio_norm_two_f = 1.4,
      -- check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      check_ratio_norm_two_d = 1.4,
      -- check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      check_ratio_norm_one_f = 1.4,
      -- check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
      check_ratio_norm_one_d = 1.4,
    },

    Hyness = {
      max_iter             = 300,
      max_step_iter        = 40,
      max_accumulated_iter = 800,
      tolerance            = 1e-09,
      continuation = {
        initial_step   = 0.2   , -- initial step for continuation
        min_step       = 0.001 , -- minimum accepted step for continuation
        reduce_factor  = 0.5   , -- if continuation step fails, reduce step by this factor
        augment_factor = 1.5   , -- if step successful in less than few_iteration augment step by this factor
        few_iterations = 8       -- if step successful in less than few_iteration augment step by this factor
      }
    },

    -- continuation parameters
    ns_continuation_begin = 0,
    ns_continuation_end   = 2,
  },

  --[[
                                        _
   _ __   __ _ _ __ __ _ _ __ ___   ___| |_ ___ _ __ ___
  | '_ \ / _` | '__/ _` | '_ ` _ \ / _ \ __/ _ \ '__/ __|
  | |_) | (_| | | | (_| | | | | | |  __/ ||  __/ |  \__ \
  | .__/ \__,_|_|  \__,_|_| |_| |_|\___|\__\___|_|  |___/
  |_|
  --]]

  -- Boundary Conditions (SET/FREE)
  BoundaryConditions = {
    initial_omega__alpha = SET,
    initial_omega__beta  = SET,
    initial_theta        = SET,
    initial_alpha        = SET,
    final_omega__alpha   = SET,
    final_omega__beta    = SET,
    final_theta          = SET,
    final_alpha          = SET,
  },

  -- Guess
  Guess = {
    -- possible value: zero, default, none, warm
    initialize = "zero",
    -- possible value: default, none, warm, spline, table
    guess_type = "default",
    -- initilize or not lagrange multiplier with redundant linear system
    initialize_multipliers = true,
    -- "use_guess", "minimize", "none"
    initialize_controls    = "use_guess"
  },

  Parameters = {

    -- Model Parameters
    rho = 0.01,

    -- Guess Parameters

    -- Boundary Conditions
    T_guess        = 3,
    W              = 0,
    alpha_f        = 0.522,
    alpha_i        = 0,
    theta_f        = 0.5,
    theta_i        = 0,
    omega__alpha_f = 0,
    omega__alpha_i = 0,
    omega__beta_f  = 0,
    omega__beta_i  = 0,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    u_epsilon0   = u_epsilon0,
    u_epsilon1   = 1e-05,
    u_tolerance0 = u_tolerance0,
    u_tolerance1 = 1e-05,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
  -- Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    u1Control = {
      type      = ,
      epsilon   = u_epsilon,
      tolerance = u_tolerance,
    },
    u2Control = {
      type      = ,
      epsilon   = u_epsilon,
      tolerance = u_tolerance,
    },
  },

  Constraints = {
  -- Constraint1D: none defined
  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: M E S H
  Mesh = 
  {
    s0       = 0,
    segments = {
      
      {
        n      = 800,
        length = 1,
      },
    },
  },


}

-- EOF