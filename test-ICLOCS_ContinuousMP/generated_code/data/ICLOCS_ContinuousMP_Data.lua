--[[
/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Data.lua                                   |
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
xy_bound  = 2
xy_tol0   = 0.1
tol_ctrl  = 0.01
xy_tol    = xy_tol0
xy_eps0   = 0.1
xy_eps    = xy_eps0
epsi_ctrl = 0.01

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
  -- DumpFile = "ICLOCS_ContinuousMP_dump",

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
    ns_continuation_end   = 1,
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
    initial_xx1    = SET,
    initial_yy1    = SET,
    X1_continuity  = SET,
    X2_continuity  = SET,
    X3_continuity  = SET,
    X4_continuity  = SET,
    X5_continuity  = SET,
    X6_continuity  = SET,
    X7_continuity  = SET,
    X8_continuity  = SET,
    X9_continuity  = SET,
    X10_continuity = SET,
    X11_continuity = SET,
    X12_continuity = SET,
    X13_continuity = SET,
    X14_continuity = SET,
    X15_continuity = SET,
    X16_continuity = SET,
    X17_continuity = SET,
    X18_continuity = SET,
    X19_continuity = SET,
    Y1_continuity  = SET,
    Y2_continuity  = SET,
    Y3_continuity  = SET,
    Y4_continuity  = SET,
    Y5_continuity  = SET,
    Y6_continuity  = SET,
    Y7_continuity  = SET,
    Y8_continuity  = SET,
    Y9_continuity  = SET,
    Y10_continuity = SET,
    Y11_continuity = SET,
    Y12_continuity = SET,
    Y13_continuity = SET,
    Y14_continuity = SET,
    Y15_continuity = SET,
    Y16_continuity = SET,
    Y17_continuity = SET,
    Y18_continuity = SET,
    Y19_continuity = SET,
    X1_initial     = SET,
    X2_initial     = SET,
    X3_initial     = SET,
    X4_initial     = SET,
    X5_initial     = SET,
    X6_initial     = SET,
    X7_initial     = SET,
    X8_initial     = SET,
    X9_initial     = SET,
    X10_initial    = SET,
    X11_initial    = SET,
    X12_initial    = SET,
    X13_initial    = SET,
    X14_initial    = SET,
    X15_initial    = SET,
    X16_initial    = SET,
    X17_initial    = SET,
    X18_initial    = SET,
    X19_initial    = SET,
    X20_initial    = SET,
    Y1_initial     = SET,
    Y2_initial     = SET,
    Y3_initial     = SET,
    Y4_initial     = SET,
    Y5_initial     = SET,
    Y6_initial     = SET,
    Y7_initial     = SET,
    Y8_initial     = SET,
    Y9_initial     = SET,
    Y10_initial    = SET,
    Y11_initial    = SET,
    Y12_initial    = SET,
    Y13_initial    = SET,
    Y14_initial    = SET,
    Y15_initial    = SET,
    Y16_initial    = SET,
    Y17_initial    = SET,
    Y18_initial    = SET,
    Y19_initial    = SET,
    Y20_initial    = SET,
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

    -- Guess Parameters

    -- Boundary Conditions

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    xy_eps0 = xy_eps0,
    xy_eps1 = 0.001,
    xy_tol0 = xy_tol0,
    xy_tol1 = 0.001,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls: No penalties or barriers constraint defined

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DInterval
    u1LimitationsubType   = "BARRIER_LOG",
    u1Limitationepsilon   = epsi_ctrl,
    u1Limitationtolerance = tol_ctrl,
    u1Limitationmin       = -10,
    u1Limitationmax       = 10,
    u1Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u2LimitationsubType   = "BARRIER_LOG",
    u2Limitationepsilon   = epsi_ctrl,
    u2Limitationtolerance = tol_ctrl,
    u2Limitationmin       = -10,
    u2Limitationmax       = 10,
    u2Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u3LimitationsubType   = "BARRIER_LOG",
    u3Limitationepsilon   = epsi_ctrl,
    u3Limitationtolerance = tol_ctrl,
    u3Limitationmin       = -10,
    u3Limitationmax       = 10,
    u3Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u4LimitationsubType   = "BARRIER_LOG",
    u4Limitationepsilon   = epsi_ctrl,
    u4Limitationtolerance = tol_ctrl,
    u4Limitationmin       = -10,
    u4Limitationmax       = 10,
    u4Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u5LimitationsubType   = "BARRIER_LOG",
    u5Limitationepsilon   = epsi_ctrl,
    u5Limitationtolerance = tol_ctrl,
    u5Limitationmin       = -10,
    u5Limitationmax       = 10,
    u5Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u6LimitationsubType   = "BARRIER_LOG",
    u6Limitationepsilon   = epsi_ctrl,
    u6Limitationtolerance = tol_ctrl,
    u6Limitationmin       = -10,
    u6Limitationmax       = 10,
    u6Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u7LimitationsubType   = "BARRIER_LOG",
    u7Limitationepsilon   = epsi_ctrl,
    u7Limitationtolerance = tol_ctrl,
    u7Limitationmin       = -10,
    u7Limitationmax       = 10,
    u7Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u8LimitationsubType   = "BARRIER_LOG",
    u8Limitationepsilon   = epsi_ctrl,
    u8Limitationtolerance = tol_ctrl,
    u8Limitationmin       = -10,
    u8Limitationmax       = 10,
    u8Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u9LimitationsubType   = "BARRIER_LOG",
    u9Limitationepsilon   = epsi_ctrl,
    u9Limitationtolerance = tol_ctrl,
    u9Limitationmin       = -10,
    u9Limitationmax       = 10,
    u9Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u10LimitationsubType   = "BARRIER_LOG",
    u10Limitationepsilon   = epsi_ctrl,
    u10Limitationtolerance = tol_ctrl,
    u10Limitationmin       = -10,
    u10Limitationmax       = 10,
    u10Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u11LimitationsubType   = "BARRIER_LOG",
    u11Limitationepsilon   = epsi_ctrl,
    u11Limitationtolerance = tol_ctrl,
    u11Limitationmin       = -10,
    u11Limitationmax       = 10,
    u11Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u12LimitationsubType   = "BARRIER_LOG",
    u12Limitationepsilon   = epsi_ctrl,
    u12Limitationtolerance = tol_ctrl,
    u12Limitationmin       = -10,
    u12Limitationmax       = 10,
    u12Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u13LimitationsubType   = "BARRIER_LOG",
    u13Limitationepsilon   = epsi_ctrl,
    u13Limitationtolerance = tol_ctrl,
    u13Limitationmin       = -10,
    u13Limitationmax       = 10,
    u13Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u14LimitationsubType   = "BARRIER_LOG",
    u14Limitationepsilon   = epsi_ctrl,
    u14Limitationtolerance = tol_ctrl,
    u14Limitationmin       = -10,
    u14Limitationmax       = 10,
    u14Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u15LimitationsubType   = "BARRIER_LOG",
    u15Limitationepsilon   = epsi_ctrl,
    u15Limitationtolerance = tol_ctrl,
    u15Limitationmin       = -10,
    u15Limitationmax       = 10,
    u15Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u16LimitationsubType   = "BARRIER_LOG",
    u16Limitationepsilon   = epsi_ctrl,
    u16Limitationtolerance = tol_ctrl,
    u16Limitationmin       = -10,
    u16Limitationmax       = 10,
    u16Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u17LimitationsubType   = "BARRIER_LOG",
    u17Limitationepsilon   = epsi_ctrl,
    u17Limitationtolerance = tol_ctrl,
    u17Limitationmin       = -10,
    u17Limitationmax       = 10,
    u17Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u18LimitationsubType   = "BARRIER_LOG",
    u18Limitationepsilon   = epsi_ctrl,
    u18Limitationtolerance = tol_ctrl,
    u18Limitationmin       = -10,
    u18Limitationmax       = 10,
    u18Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u19LimitationsubType   = "BARRIER_LOG",
    u19Limitationepsilon   = epsi_ctrl,
    u19Limitationtolerance = tol_ctrl,
    u19Limitationmin       = -10,
    u19Limitationmax       = 10,
    u19Limitationactive    = true

    -- PenaltyBarrier1DInterval
    u20LimitationsubType   = "BARRIER_LOG",
    u20Limitationepsilon   = epsi_ctrl,
    u20Limitationtolerance = tol_ctrl,
    u20Limitationmin       = -10,
    u20Limitationmax       = 10,
    u20Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx1LimitationsubType   = "BARRIER_LOG",
    xx1Limitationepsilon   = xy_eps,
    xx1Limitationtolerance = xy_tol,
    xx1Limitationmin       = -xy_bound,
    xx1Limitationmax       = xy_bound,
    xx1Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy1LimitationsubType   = "BARRIER_LOG",
    yy1Limitationepsilon   = xy_eps,
    yy1Limitationtolerance = xy_tol,
    yy1Limitationmin       = -xy_bound,
    yy1Limitationmax       = xy_bound,
    yy1Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx2LimitationsubType   = "BARRIER_LOG",
    xx2Limitationepsilon   = xy_eps,
    xx2Limitationtolerance = xy_tol,
    xx2Limitationmin       = -xy_bound,
    xx2Limitationmax       = xy_bound,
    xx2Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy2LimitationsubType   = "BARRIER_LOG",
    yy2Limitationepsilon   = xy_eps,
    yy2Limitationtolerance = xy_tol,
    yy2Limitationmin       = -xy_bound,
    yy2Limitationmax       = xy_bound,
    yy2Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx3LimitationsubType   = "BARRIER_LOG",
    xx3Limitationepsilon   = xy_eps,
    xx3Limitationtolerance = xy_tol,
    xx3Limitationmin       = -xy_bound,
    xx3Limitationmax       = xy_bound,
    xx3Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy3LimitationsubType   = "BARRIER_LOG",
    yy3Limitationepsilon   = xy_eps,
    yy3Limitationtolerance = xy_tol,
    yy3Limitationmin       = -xy_bound,
    yy3Limitationmax       = xy_bound,
    yy3Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx4LimitationsubType   = "BARRIER_LOG",
    xx4Limitationepsilon   = xy_eps,
    xx4Limitationtolerance = xy_tol,
    xx4Limitationmin       = -xy_bound,
    xx4Limitationmax       = xy_bound,
    xx4Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy4LimitationsubType   = "BARRIER_LOG",
    yy4Limitationepsilon   = xy_eps,
    yy4Limitationtolerance = xy_tol,
    yy4Limitationmin       = -xy_bound,
    yy4Limitationmax       = xy_bound,
    yy4Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx5LimitationsubType   = "BARRIER_LOG",
    xx5Limitationepsilon   = xy_eps,
    xx5Limitationtolerance = xy_tol,
    xx5Limitationmin       = -xy_bound,
    xx5Limitationmax       = xy_bound,
    xx5Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy5LimitationsubType   = "BARRIER_LOG",
    yy5Limitationepsilon   = xy_eps,
    yy5Limitationtolerance = xy_tol,
    yy5Limitationmin       = -xy_bound,
    yy5Limitationmax       = xy_bound,
    yy5Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx6LimitationsubType   = "BARRIER_LOG",
    xx6Limitationepsilon   = xy_eps,
    xx6Limitationtolerance = xy_tol,
    xx6Limitationmin       = -xy_bound,
    xx6Limitationmax       = xy_bound,
    xx6Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy6LimitationsubType   = "BARRIER_LOG",
    yy6Limitationepsilon   = xy_eps,
    yy6Limitationtolerance = xy_tol,
    yy6Limitationmin       = -xy_bound,
    yy6Limitationmax       = xy_bound,
    yy6Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx7LimitationsubType   = "BARRIER_LOG",
    xx7Limitationepsilon   = xy_eps,
    xx7Limitationtolerance = xy_tol,
    xx7Limitationmin       = -xy_bound,
    xx7Limitationmax       = xy_bound,
    xx7Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy7LimitationsubType   = "BARRIER_LOG",
    yy7Limitationepsilon   = xy_eps,
    yy7Limitationtolerance = xy_tol,
    yy7Limitationmin       = -xy_bound,
    yy7Limitationmax       = xy_bound,
    yy7Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx8LimitationsubType   = "BARRIER_LOG",
    xx8Limitationepsilon   = xy_eps,
    xx8Limitationtolerance = xy_tol,
    xx8Limitationmin       = -xy_bound,
    xx8Limitationmax       = xy_bound,
    xx8Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy8LimitationsubType   = "BARRIER_LOG",
    yy8Limitationepsilon   = xy_eps,
    yy8Limitationtolerance = xy_tol,
    yy8Limitationmin       = -xy_bound,
    yy8Limitationmax       = xy_bound,
    yy8Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx9LimitationsubType   = "BARRIER_LOG",
    xx9Limitationepsilon   = xy_eps,
    xx9Limitationtolerance = xy_tol,
    xx9Limitationmin       = -xy_bound,
    xx9Limitationmax       = xy_bound,
    xx9Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy9LimitationsubType   = "BARRIER_LOG",
    yy9Limitationepsilon   = xy_eps,
    yy9Limitationtolerance = xy_tol,
    yy9Limitationmin       = -xy_bound,
    yy9Limitationmax       = xy_bound,
    yy9Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx10LimitationsubType   = "BARRIER_LOG",
    xx10Limitationepsilon   = xy_eps,
    xx10Limitationtolerance = xy_tol,
    xx10Limitationmin       = -xy_bound,
    xx10Limitationmax       = xy_bound,
    xx10Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy10LimitationsubType   = "BARRIER_LOG",
    yy10Limitationepsilon   = xy_eps,
    yy10Limitationtolerance = xy_tol,
    yy10Limitationmin       = -xy_bound,
    yy10Limitationmax       = xy_bound,
    yy10Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx11LimitationsubType   = "BARRIER_LOG",
    xx11Limitationepsilon   = xy_eps,
    xx11Limitationtolerance = xy_tol,
    xx11Limitationmin       = -xy_bound,
    xx11Limitationmax       = xy_bound,
    xx11Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy11LimitationsubType   = "BARRIER_LOG",
    yy11Limitationepsilon   = xy_eps,
    yy11Limitationtolerance = xy_tol,
    yy11Limitationmin       = -xy_bound,
    yy11Limitationmax       = xy_bound,
    yy11Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx12LimitationsubType   = "BARRIER_LOG",
    xx12Limitationepsilon   = xy_eps,
    xx12Limitationtolerance = xy_tol,
    xx12Limitationmin       = -xy_bound,
    xx12Limitationmax       = xy_bound,
    xx12Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy12LimitationsubType   = "BARRIER_LOG",
    yy12Limitationepsilon   = xy_eps,
    yy12Limitationtolerance = xy_tol,
    yy12Limitationmin       = -xy_bound,
    yy12Limitationmax       = xy_bound,
    yy12Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx13LimitationsubType   = "BARRIER_LOG",
    xx13Limitationepsilon   = xy_eps,
    xx13Limitationtolerance = xy_tol,
    xx13Limitationmin       = -xy_bound,
    xx13Limitationmax       = xy_bound,
    xx13Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy13LimitationsubType   = "BARRIER_LOG",
    yy13Limitationepsilon   = xy_eps,
    yy13Limitationtolerance = xy_tol,
    yy13Limitationmin       = -xy_bound,
    yy13Limitationmax       = xy_bound,
    yy13Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx14LimitationsubType   = "BARRIER_LOG",
    xx14Limitationepsilon   = xy_eps,
    xx14Limitationtolerance = xy_tol,
    xx14Limitationmin       = -xy_bound,
    xx14Limitationmax       = xy_bound,
    xx14Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy14LimitationsubType   = "BARRIER_LOG",
    yy14Limitationepsilon   = xy_eps,
    yy14Limitationtolerance = xy_tol,
    yy14Limitationmin       = -xy_bound,
    yy14Limitationmax       = xy_bound,
    yy14Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx15LimitationsubType   = "BARRIER_LOG",
    xx15Limitationepsilon   = xy_eps,
    xx15Limitationtolerance = xy_tol,
    xx15Limitationmin       = -xy_bound,
    xx15Limitationmax       = xy_bound,
    xx15Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy15LimitationsubType   = "BARRIER_LOG",
    yy15Limitationepsilon   = xy_eps,
    yy15Limitationtolerance = xy_tol,
    yy15Limitationmin       = -xy_bound,
    yy15Limitationmax       = xy_bound,
    yy15Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx16LimitationsubType   = "BARRIER_LOG",
    xx16Limitationepsilon   = xy_eps,
    xx16Limitationtolerance = xy_tol,
    xx16Limitationmin       = -xy_bound,
    xx16Limitationmax       = xy_bound,
    xx16Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy16LimitationsubType   = "BARRIER_LOG",
    yy16Limitationepsilon   = xy_eps,
    yy16Limitationtolerance = xy_tol,
    yy16Limitationmin       = -xy_bound,
    yy16Limitationmax       = xy_bound,
    yy16Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx17LimitationsubType   = "BARRIER_LOG",
    xx17Limitationepsilon   = xy_eps,
    xx17Limitationtolerance = xy_tol,
    xx17Limitationmin       = -xy_bound,
    xx17Limitationmax       = xy_bound,
    xx17Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy17LimitationsubType   = "BARRIER_LOG",
    yy17Limitationepsilon   = xy_eps,
    yy17Limitationtolerance = xy_tol,
    yy17Limitationmin       = -xy_bound,
    yy17Limitationmax       = xy_bound,
    yy17Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx18LimitationsubType   = "BARRIER_LOG",
    xx18Limitationepsilon   = xy_eps,
    xx18Limitationtolerance = xy_tol,
    xx18Limitationmin       = -xy_bound,
    xx18Limitationmax       = xy_bound,
    xx18Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy18LimitationsubType   = "BARRIER_LOG",
    yy18Limitationepsilon   = xy_eps,
    yy18Limitationtolerance = xy_tol,
    yy18Limitationmin       = -xy_bound,
    yy18Limitationmax       = xy_bound,
    yy18Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx19LimitationsubType   = "BARRIER_LOG",
    xx19Limitationepsilon   = xy_eps,
    xx19Limitationtolerance = xy_tol,
    xx19Limitationmin       = -xy_bound,
    xx19Limitationmax       = xy_bound,
    xx19Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy19LimitationsubType   = "BARRIER_LOG",
    yy19Limitationepsilon   = xy_eps,
    yy19Limitationtolerance = xy_tol,
    yy19Limitationmin       = -xy_bound,
    yy19Limitationmax       = xy_bound,
    yy19Limitationactive    = true

    -- PenaltyBarrier1DInterval
    xx20LimitationsubType   = "BARRIER_LOG",
    xx20Limitationepsilon   = xy_eps,
    xx20Limitationtolerance = xy_tol,
    xx20Limitationmin       = -xy_bound,
    xx20Limitationmax       = xy_bound,
    xx20Limitationactive    = true

    -- PenaltyBarrier1DInterval
    yy20LimitationsubType   = "BARRIER_LOG",
    yy20Limitationepsilon   = xy_eps,
    yy20Limitationtolerance = xy_tol,
    yy20Limitationmin       = -xy_bound,
    yy20Limitationmax       = xy_bound,
    yy20Limitationactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: M E S H
  Mesh = 
  {
    s0       = 0,
    segments = {
      
      {
        n      = 50,
        length = 1,
      },
    },
  },


}

-- EOF
