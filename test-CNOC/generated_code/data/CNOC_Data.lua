--[[
/*-----------------------------------------------------------------------*\
 |  file: CNOC_Data.lua                                                  |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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
jn_max                   = 65
v_nom                    = 0.173
path_following_tolerance = 1.0e-05
mesh_segments            = 100
deltaFeed                = v_nom
js_min                   = -50
js_max                   = 30
pf_error                 = path_following_tolerance

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
  -- DumpFile = "CNOC_dump",

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
    Iterative = false,
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
    ns_continuation_end   = 0,
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
    initial_n  = SET,
    initial_vs = SET,
    initial_vn = SET,
    initial_as = SET,
    initial_an = SET,
    final_n    = SET,
    final_vs   = SET,
    final_vn   = SET,
    final_as   = SET,
    final_an   = SET,
    initial_s  = SET,
    final_s    = SET,
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
    an_max                   = 1.2,
    as_max                   = 2.1,
    ax_max                   = 2.1,
    ay_max                   = 2.1,
    jn_max                   = jn_max,
    js_max                   = js_max,
    js_min                   = js_min,
    deltaFeed                = deltaFeed,
    path_following_tolerance = path_following_tolerance,

    -- Guess Parameters

    -- Boundary Conditions
    an_f = 0,
    an_i = 0,
    as_f = 0,
    as_i = 0,
    n_f  = 0,
    n_i  = 0,
    vn_f = 0,
    vn_i = 0,
    vs_f = 0,
    vs_i = 0,

    -- Post Processing Parameters
    pf_error = pf_error,

    -- User Function Parameters

    -- Continuation Parameters

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
  -- Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    jsControl = {
      type      = ,
      epsilon   = 0.01,
      tolerance = 0.01,
    },
    jnControl = {
      type      = ,
      epsilon   = 0.01,
      tolerance = 0.01,
    },
  },

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DGreaterThan
    timePositivesubType   = "BARRIER_LOG",
    timePositiveepsilon   = 0.01,
    timePositivetolerance = 0.01,
    timePositiveactive    = true

    -- PenaltyBarrier1DGreaterThan
    vLimitsubType   = "PENALTY_PIECEWISE",
    vLimitepsilon   = 0.01,
    vLimittolerance = 0.01,
    vLimitactive    = true

    -- PenaltyBarrier1DInterval
    PathFollowingTolerancesubType   = "PENALTY_REGULAR",
    PathFollowingToleranceepsilon   = 0.01,
    PathFollowingTolerancetolerance = 0.1,
    PathFollowingTolerancemin       = -1,
    PathFollowingTolerancemax       = 1,
    PathFollowingToleranceactive    = true

    -- PenaltyBarrier1DInterval
    as_limitsubType   = "PENALTY_REGULAR",
    as_limitepsilon   = 0.01,
    as_limittolerance = 0.01,
    as_limitmin       = -1,
    as_limitmax       = 1,
    as_limitactive    = true

    -- PenaltyBarrier1DInterval
    an_limitsubType   = "PENALTY_REGULAR",
    an_limitepsilon   = 0.01,
    an_limittolerance = 0.01,
    an_limitmin       = -1,
    an_limitmax       = 1,
    an_limitactive    = true

    -- PenaltyBarrier1DInterval
    ax_limitsubType   = "PENALTY_REGULAR",
    ax_limitepsilon   = 0.01,
    ax_limittolerance = 0.01,
    ax_limitmin       = -1,
    ax_limitmax       = 1,
    ax_limitactive    = true

    -- PenaltyBarrier1DInterval
    ay_limitsubType   = "PENALTY_REGULAR",
    ay_limitepsilon   = 0.01,
    ay_limittolerance = 0.01,
    ay_limitmin       = -1,
    ay_limitmax       = 1,
    ay_limitactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: T O O L P A T H 2 D
  ToolPath2D = 
  {
    segments = {
      
      {
        x0           = -0.01,
        y0           = 0,
        x1           = 0.02,
        y1           = 0.002,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.002,
        x1           = 0.05,
        y1           = 0,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.05,
        y0           = 0,
        x1           = 0.05,
        y1           = 0.01,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
        angle0       = 0,
        angle1       = 3.1415,
      },
      
      {
        x0           = 0.05,
        y0           = 0.01,
        x1           = 0.02,
        y1           = 0.012,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.012,
        x1           = -0.01,
        y1           = 0.01,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.01,
        x1           = -0.01,
        y1           = 0.02,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.02,
        x1           = 0.02,
        y1           = 0.022,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.022,
        x1           = 0.05,
        y1           = 0.02,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.05,
        y0           = 0.02,
        x1           = 0.05,
        y1           = 0.03,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
        angle0       = 0,
        angle1       = 3.1415,
      },
      
      {
        x0           = 0.05,
        y0           = 0.03,
        x1           = 0.02,
        y1           = 0.032,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.032,
        x1           = -0.01,
        y1           = 0.03,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.03,
        x1           = -0.01,
        y1           = 0.04,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.04,
        x1           = 0.02,
        y1           = 0.042,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.042,
        x1           = 0.05,
        y1           = 0.04,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.05,
        y0           = 0.04,
        x1           = 0.05,
        y1           = 0.05,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
        angle0       = 0,
        angle1       = 3.1415,
      },
      
      {
        x0           = 0.05,
        y0           = 0.05,
        x1           = 0.02,
        y1           = 0.052,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.052,
        x1           = -0.01,
        y1           = 0.05,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.05,
        x1           = -0.01,
        y1           = 0.06,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.06,
        x1           = 0.02,
        y1           = 0.062,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.062,
        x1           = 0.05,
        y1           = 0.06,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
    },
  },


}

-- EOF