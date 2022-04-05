--[[
/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ContinuousMP_Data.lua                                   |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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
tol_ctrl  = 0.01
xy_eps0   = 0.1
xy_eps    = xy_eps0
epsi_ctrl = 0.01
xy_tol0   = 0.1
xy_tol    = xy_tol0

content = {

  -- activate run time debug
  data.Debug = true,

  -- Enable doctor
  Doctor = false,

  -- Level of message
  InfoLevel = 4,

  Use_control_penalties_in_adjoint_equations = false,

  Max_penalty_value = 1000,

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
  ControlsCheck_epsilon = 1e-6,
  JacobianCheck         = false,
  JacobianCheckFull     = false,
  JacobianCheck_epsilon = 1e-4,

  -- Jacobian discretization: 'ANALYTIC', 'ANALYTIC2', 'FINITE_DIFFERENCE'
  JacobianDiscretization = 'ANALYTIC,

  -- jacobian discretization BC part: 'ANALYTIC', 'FINITE_DIFFERENCE'
  JacobianDiscretizationBC = 'ANALYTIC',

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
      -- "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2", "MERIT_LOG_F2_and_LOG_D2"
      merit                = "MERIT_LOG_F2_and_D2",
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
      -- "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2", "MERIT_LOG_F2_and_LOG_D2"
      merit                = "MERIT_LOG_F2_and_D2",
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
      check_ratio_norm_two_f = 2,
      -- check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      check_ratio_norm_two_d = 2,
      -- check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      check_ratio_norm_one_f = 2,
      -- check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
      check_ratio_norm_one_d = 2,
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
    xy_bound = 2,

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
  --  _  _____
  -- | ||_   _|
  -- | |__| |
  -- |____|_|
  -- Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DLessThan
    u1Limitation_minsubType   = "BARRIER_LOG",
    u1Limitation_minepsilon   = epsi_ctrl,
    u1Limitation_mintolerance = tol_ctrl,
    u1Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u1Limitation_maxsubType   = "BARRIER_LOG",
    u1Limitation_maxepsilon   = epsi_ctrl,
    u1Limitation_maxtolerance = tol_ctrl,
    u1Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u2Limitation_minsubType   = "BARRIER_LOG",
    u2Limitation_minepsilon   = epsi_ctrl,
    u2Limitation_mintolerance = tol_ctrl,
    u2Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u2Limitation_maxsubType   = "BARRIER_LOG",
    u2Limitation_maxepsilon   = epsi_ctrl,
    u2Limitation_maxtolerance = tol_ctrl,
    u2Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u3Limitation_minsubType   = "BARRIER_LOG",
    u3Limitation_minepsilon   = epsi_ctrl,
    u3Limitation_mintolerance = tol_ctrl,
    u3Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u3Limitation_maxsubType   = "BARRIER_LOG",
    u3Limitation_maxepsilon   = epsi_ctrl,
    u3Limitation_maxtolerance = tol_ctrl,
    u3Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u4Limitation_minsubType   = "BARRIER_LOG",
    u4Limitation_minepsilon   = epsi_ctrl,
    u4Limitation_mintolerance = tol_ctrl,
    u4Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u4Limitation_maxsubType   = "BARRIER_LOG",
    u4Limitation_maxepsilon   = epsi_ctrl,
    u4Limitation_maxtolerance = tol_ctrl,
    u4Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u5Limitation_minsubType   = "BARRIER_LOG",
    u5Limitation_minepsilon   = epsi_ctrl,
    u5Limitation_mintolerance = tol_ctrl,
    u5Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u5Limitation_maxsubType   = "BARRIER_LOG",
    u5Limitation_maxepsilon   = epsi_ctrl,
    u5Limitation_maxtolerance = tol_ctrl,
    u5Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u6Limitation_minsubType   = "BARRIER_LOG",
    u6Limitation_minepsilon   = epsi_ctrl,
    u6Limitation_mintolerance = tol_ctrl,
    u6Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u6Limitation_maxsubType   = "BARRIER_LOG",
    u6Limitation_maxepsilon   = epsi_ctrl,
    u6Limitation_maxtolerance = tol_ctrl,
    u6Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u7Limitation_minsubType   = "BARRIER_LOG",
    u7Limitation_minepsilon   = epsi_ctrl,
    u7Limitation_mintolerance = tol_ctrl,
    u7Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u7Limitation_maxsubType   = "BARRIER_LOG",
    u7Limitation_maxepsilon   = epsi_ctrl,
    u7Limitation_maxtolerance = tol_ctrl,
    u7Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u8Limitation_minsubType   = "BARRIER_LOG",
    u8Limitation_minepsilon   = epsi_ctrl,
    u8Limitation_mintolerance = tol_ctrl,
    u8Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u8Limitation_maxsubType   = "BARRIER_LOG",
    u8Limitation_maxepsilon   = epsi_ctrl,
    u8Limitation_maxtolerance = tol_ctrl,
    u8Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u9Limitation_minsubType   = "BARRIER_LOG",
    u9Limitation_minepsilon   = epsi_ctrl,
    u9Limitation_mintolerance = tol_ctrl,
    u9Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u9Limitation_maxsubType   = "BARRIER_LOG",
    u9Limitation_maxepsilon   = epsi_ctrl,
    u9Limitation_maxtolerance = tol_ctrl,
    u9Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u10Limitation_minsubType   = "BARRIER_LOG",
    u10Limitation_minepsilon   = epsi_ctrl,
    u10Limitation_mintolerance = tol_ctrl,
    u10Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u10Limitation_maxsubType   = "BARRIER_LOG",
    u10Limitation_maxepsilon   = epsi_ctrl,
    u10Limitation_maxtolerance = tol_ctrl,
    u10Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u11Limitation_minsubType   = "BARRIER_LOG",
    u11Limitation_minepsilon   = epsi_ctrl,
    u11Limitation_mintolerance = tol_ctrl,
    u11Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u11Limitation_maxsubType   = "BARRIER_LOG",
    u11Limitation_maxepsilon   = epsi_ctrl,
    u11Limitation_maxtolerance = tol_ctrl,
    u11Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u12Limitation_minsubType   = "BARRIER_LOG",
    u12Limitation_minepsilon   = epsi_ctrl,
    u12Limitation_mintolerance = tol_ctrl,
    u12Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u12Limitation_maxsubType   = "BARRIER_LOG",
    u12Limitation_maxepsilon   = epsi_ctrl,
    u12Limitation_maxtolerance = tol_ctrl,
    u12Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u13Limitation_minsubType   = "BARRIER_LOG",
    u13Limitation_minepsilon   = epsi_ctrl,
    u13Limitation_mintolerance = tol_ctrl,
    u13Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u13Limitation_maxsubType   = "BARRIER_LOG",
    u13Limitation_maxepsilon   = epsi_ctrl,
    u13Limitation_maxtolerance = tol_ctrl,
    u13Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u14Limitation_minsubType   = "BARRIER_LOG",
    u14Limitation_minepsilon   = epsi_ctrl,
    u14Limitation_mintolerance = tol_ctrl,
    u14Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u14Limitation_maxsubType   = "BARRIER_LOG",
    u14Limitation_maxepsilon   = epsi_ctrl,
    u14Limitation_maxtolerance = tol_ctrl,
    u14Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u15Limitation_minsubType   = "BARRIER_LOG",
    u15Limitation_minepsilon   = epsi_ctrl,
    u15Limitation_mintolerance = tol_ctrl,
    u15Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u15Limitation_maxsubType   = "BARRIER_LOG",
    u15Limitation_maxepsilon   = epsi_ctrl,
    u15Limitation_maxtolerance = tol_ctrl,
    u15Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u16Limitation_minsubType   = "BARRIER_LOG",
    u16Limitation_minepsilon   = epsi_ctrl,
    u16Limitation_mintolerance = tol_ctrl,
    u16Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u16Limitation_maxsubType   = "BARRIER_LOG",
    u16Limitation_maxepsilon   = epsi_ctrl,
    u16Limitation_maxtolerance = tol_ctrl,
    u16Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u17Limitation_minsubType   = "BARRIER_LOG",
    u17Limitation_minepsilon   = epsi_ctrl,
    u17Limitation_mintolerance = tol_ctrl,
    u17Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u17Limitation_maxsubType   = "BARRIER_LOG",
    u17Limitation_maxepsilon   = epsi_ctrl,
    u17Limitation_maxtolerance = tol_ctrl,
    u17Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u18Limitation_minsubType   = "BARRIER_LOG",
    u18Limitation_minepsilon   = epsi_ctrl,
    u18Limitation_mintolerance = tol_ctrl,
    u18Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u18Limitation_maxsubType   = "BARRIER_LOG",
    u18Limitation_maxepsilon   = epsi_ctrl,
    u18Limitation_maxtolerance = tol_ctrl,
    u18Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u19Limitation_minsubType   = "BARRIER_LOG",
    u19Limitation_minepsilon   = epsi_ctrl,
    u19Limitation_mintolerance = tol_ctrl,
    u19Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u19Limitation_maxsubType   = "BARRIER_LOG",
    u19Limitation_maxepsilon   = epsi_ctrl,
    u19Limitation_maxtolerance = tol_ctrl,
    u19Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    u20Limitation_minsubType   = "BARRIER_LOG",
    u20Limitation_minepsilon   = epsi_ctrl,
    u20Limitation_mintolerance = tol_ctrl,
    u20Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    u20Limitation_maxsubType   = "BARRIER_LOG",
    u20Limitation_maxepsilon   = epsi_ctrl,
    u20Limitation_maxtolerance = tol_ctrl,
    u20Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx1Limitation_minsubType   = "BARRIER_LOG",
    xx1Limitation_minepsilon   = xy_eps,
    xx1Limitation_mintolerance = xy_tol,
    xx1Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx1Limitation_maxsubType   = "BARRIER_LOG",
    xx1Limitation_maxepsilon   = xy_eps,
    xx1Limitation_maxtolerance = xy_tol,
    xx1Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy1Limitation_minsubType   = "BARRIER_LOG",
    yy1Limitation_minepsilon   = xy_eps,
    yy1Limitation_mintolerance = xy_tol,
    yy1Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy1Limitation_maxsubType   = "BARRIER_LOG",
    yy1Limitation_maxepsilon   = xy_eps,
    yy1Limitation_maxtolerance = xy_tol,
    yy1Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx2Limitation_minsubType   = "BARRIER_LOG",
    xx2Limitation_minepsilon   = xy_eps,
    xx2Limitation_mintolerance = xy_tol,
    xx2Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx2Limitation_maxsubType   = "BARRIER_LOG",
    xx2Limitation_maxepsilon   = xy_eps,
    xx2Limitation_maxtolerance = xy_tol,
    xx2Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy2Limitation_minsubType   = "BARRIER_LOG",
    yy2Limitation_minepsilon   = xy_eps,
    yy2Limitation_mintolerance = xy_tol,
    yy2Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy2Limitation_maxsubType   = "BARRIER_LOG",
    yy2Limitation_maxepsilon   = xy_eps,
    yy2Limitation_maxtolerance = xy_tol,
    yy2Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx3Limitation_minsubType   = "BARRIER_LOG",
    xx3Limitation_minepsilon   = xy_eps,
    xx3Limitation_mintolerance = xy_tol,
    xx3Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx3Limitation_maxsubType   = "BARRIER_LOG",
    xx3Limitation_maxepsilon   = xy_eps,
    xx3Limitation_maxtolerance = xy_tol,
    xx3Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy3Limitation_minsubType   = "BARRIER_LOG",
    yy3Limitation_minepsilon   = xy_eps,
    yy3Limitation_mintolerance = xy_tol,
    yy3Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy3Limitation_maxsubType   = "BARRIER_LOG",
    yy3Limitation_maxepsilon   = xy_eps,
    yy3Limitation_maxtolerance = xy_tol,
    yy3Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx4Limitation_minsubType   = "BARRIER_LOG",
    xx4Limitation_minepsilon   = xy_eps,
    xx4Limitation_mintolerance = xy_tol,
    xx4Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx4Limitation_maxsubType   = "BARRIER_LOG",
    xx4Limitation_maxepsilon   = xy_eps,
    xx4Limitation_maxtolerance = xy_tol,
    xx4Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy4Limitation_minsubType   = "BARRIER_LOG",
    yy4Limitation_minepsilon   = xy_eps,
    yy4Limitation_mintolerance = xy_tol,
    yy4Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy4Limitation_maxsubType   = "BARRIER_LOG",
    yy4Limitation_maxepsilon   = xy_eps,
    yy4Limitation_maxtolerance = xy_tol,
    yy4Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx5Limitation_minsubType   = "BARRIER_LOG",
    xx5Limitation_minepsilon   = xy_eps,
    xx5Limitation_mintolerance = xy_tol,
    xx5Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx5Limitation_maxsubType   = "BARRIER_LOG",
    xx5Limitation_maxepsilon   = xy_eps,
    xx5Limitation_maxtolerance = xy_tol,
    xx5Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy5Limitation_minsubType   = "BARRIER_LOG",
    yy5Limitation_minepsilon   = xy_eps,
    yy5Limitation_mintolerance = xy_tol,
    yy5Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy5Limitation_maxsubType   = "BARRIER_LOG",
    yy5Limitation_maxepsilon   = xy_eps,
    yy5Limitation_maxtolerance = xy_tol,
    yy5Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx6Limitation_minsubType   = "BARRIER_LOG",
    xx6Limitation_minepsilon   = xy_eps,
    xx6Limitation_mintolerance = xy_tol,
    xx6Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx6Limitation_maxsubType   = "BARRIER_LOG",
    xx6Limitation_maxepsilon   = xy_eps,
    xx6Limitation_maxtolerance = xy_tol,
    xx6Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy6Limitation_minsubType   = "BARRIER_LOG",
    yy6Limitation_minepsilon   = xy_eps,
    yy6Limitation_mintolerance = xy_tol,
    yy6Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy6Limitation_maxsubType   = "BARRIER_LOG",
    yy6Limitation_maxepsilon   = xy_eps,
    yy6Limitation_maxtolerance = xy_tol,
    yy6Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx7Limitation_minsubType   = "BARRIER_LOG",
    xx7Limitation_minepsilon   = xy_eps,
    xx7Limitation_mintolerance = xy_tol,
    xx7Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx7Limitation_maxsubType   = "BARRIER_LOG",
    xx7Limitation_maxepsilon   = xy_eps,
    xx7Limitation_maxtolerance = xy_tol,
    xx7Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy7Limitation_minsubType   = "BARRIER_LOG",
    yy7Limitation_minepsilon   = xy_eps,
    yy7Limitation_mintolerance = xy_tol,
    yy7Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy7Limitation_maxsubType   = "BARRIER_LOG",
    yy7Limitation_maxepsilon   = xy_eps,
    yy7Limitation_maxtolerance = xy_tol,
    yy7Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx8Limitation_minsubType   = "BARRIER_LOG",
    xx8Limitation_minepsilon   = xy_eps,
    xx8Limitation_mintolerance = xy_tol,
    xx8Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx8Limitation_maxsubType   = "BARRIER_LOG",
    xx8Limitation_maxepsilon   = xy_eps,
    xx8Limitation_maxtolerance = xy_tol,
    xx8Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy8Limitation_minsubType   = "BARRIER_LOG",
    yy8Limitation_minepsilon   = xy_eps,
    yy8Limitation_mintolerance = xy_tol,
    yy8Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy8Limitation_maxsubType   = "BARRIER_LOG",
    yy8Limitation_maxepsilon   = xy_eps,
    yy8Limitation_maxtolerance = xy_tol,
    yy8Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx9Limitation_minsubType   = "BARRIER_LOG",
    xx9Limitation_minepsilon   = xy_eps,
    xx9Limitation_mintolerance = xy_tol,
    xx9Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx9Limitation_maxsubType   = "BARRIER_LOG",
    xx9Limitation_maxepsilon   = xy_eps,
    xx9Limitation_maxtolerance = xy_tol,
    xx9Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy9Limitation_minsubType   = "BARRIER_LOG",
    yy9Limitation_minepsilon   = xy_eps,
    yy9Limitation_mintolerance = xy_tol,
    yy9Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy9Limitation_maxsubType   = "BARRIER_LOG",
    yy9Limitation_maxepsilon   = xy_eps,
    yy9Limitation_maxtolerance = xy_tol,
    yy9Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx10Limitation_minsubType   = "BARRIER_LOG",
    xx10Limitation_minepsilon   = xy_eps,
    xx10Limitation_mintolerance = xy_tol,
    xx10Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx10Limitation_maxsubType   = "BARRIER_LOG",
    xx10Limitation_maxepsilon   = xy_eps,
    xx10Limitation_maxtolerance = xy_tol,
    xx10Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy10Limitation_minsubType   = "BARRIER_LOG",
    yy10Limitation_minepsilon   = xy_eps,
    yy10Limitation_mintolerance = xy_tol,
    yy10Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy10Limitation_maxsubType   = "BARRIER_LOG",
    yy10Limitation_maxepsilon   = xy_eps,
    yy10Limitation_maxtolerance = xy_tol,
    yy10Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx11Limitation_minsubType   = "BARRIER_LOG",
    xx11Limitation_minepsilon   = xy_eps,
    xx11Limitation_mintolerance = xy_tol,
    xx11Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx11Limitation_maxsubType   = "BARRIER_LOG",
    xx11Limitation_maxepsilon   = xy_eps,
    xx11Limitation_maxtolerance = xy_tol,
    xx11Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy11Limitation_minsubType   = "BARRIER_LOG",
    yy11Limitation_minepsilon   = xy_eps,
    yy11Limitation_mintolerance = xy_tol,
    yy11Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy11Limitation_maxsubType   = "BARRIER_LOG",
    yy11Limitation_maxepsilon   = xy_eps,
    yy11Limitation_maxtolerance = xy_tol,
    yy11Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx12Limitation_minsubType   = "BARRIER_LOG",
    xx12Limitation_minepsilon   = xy_eps,
    xx12Limitation_mintolerance = xy_tol,
    xx12Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx12Limitation_maxsubType   = "BARRIER_LOG",
    xx12Limitation_maxepsilon   = xy_eps,
    xx12Limitation_maxtolerance = xy_tol,
    xx12Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy12Limitation_minsubType   = "BARRIER_LOG",
    yy12Limitation_minepsilon   = xy_eps,
    yy12Limitation_mintolerance = xy_tol,
    yy12Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy12Limitation_maxsubType   = "BARRIER_LOG",
    yy12Limitation_maxepsilon   = xy_eps,
    yy12Limitation_maxtolerance = xy_tol,
    yy12Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx13Limitation_minsubType   = "BARRIER_LOG",
    xx13Limitation_minepsilon   = xy_eps,
    xx13Limitation_mintolerance = xy_tol,
    xx13Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx13Limitation_maxsubType   = "BARRIER_LOG",
    xx13Limitation_maxepsilon   = xy_eps,
    xx13Limitation_maxtolerance = xy_tol,
    xx13Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy13Limitation_minsubType   = "BARRIER_LOG",
    yy13Limitation_minepsilon   = xy_eps,
    yy13Limitation_mintolerance = xy_tol,
    yy13Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy13Limitation_maxsubType   = "BARRIER_LOG",
    yy13Limitation_maxepsilon   = xy_eps,
    yy13Limitation_maxtolerance = xy_tol,
    yy13Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx14Limitation_minsubType   = "BARRIER_LOG",
    xx14Limitation_minepsilon   = xy_eps,
    xx14Limitation_mintolerance = xy_tol,
    xx14Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx14Limitation_maxsubType   = "BARRIER_LOG",
    xx14Limitation_maxepsilon   = xy_eps,
    xx14Limitation_maxtolerance = xy_tol,
    xx14Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy14Limitation_minsubType   = "BARRIER_LOG",
    yy14Limitation_minepsilon   = xy_eps,
    yy14Limitation_mintolerance = xy_tol,
    yy14Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy14Limitation_maxsubType   = "BARRIER_LOG",
    yy14Limitation_maxepsilon   = xy_eps,
    yy14Limitation_maxtolerance = xy_tol,
    yy14Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx15Limitation_minsubType   = "BARRIER_LOG",
    xx15Limitation_minepsilon   = xy_eps,
    xx15Limitation_mintolerance = xy_tol,
    xx15Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx15Limitation_maxsubType   = "BARRIER_LOG",
    xx15Limitation_maxepsilon   = xy_eps,
    xx15Limitation_maxtolerance = xy_tol,
    xx15Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy15Limitation_minsubType   = "BARRIER_LOG",
    yy15Limitation_minepsilon   = xy_eps,
    yy15Limitation_mintolerance = xy_tol,
    yy15Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy15Limitation_maxsubType   = "BARRIER_LOG",
    yy15Limitation_maxepsilon   = xy_eps,
    yy15Limitation_maxtolerance = xy_tol,
    yy15Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx16Limitation_minsubType   = "BARRIER_LOG",
    xx16Limitation_minepsilon   = xy_eps,
    xx16Limitation_mintolerance = xy_tol,
    xx16Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx16Limitation_maxsubType   = "BARRIER_LOG",
    xx16Limitation_maxepsilon   = xy_eps,
    xx16Limitation_maxtolerance = xy_tol,
    xx16Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy16Limitation_minsubType   = "BARRIER_LOG",
    yy16Limitation_minepsilon   = xy_eps,
    yy16Limitation_mintolerance = xy_tol,
    yy16Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy16Limitation_maxsubType   = "BARRIER_LOG",
    yy16Limitation_maxepsilon   = xy_eps,
    yy16Limitation_maxtolerance = xy_tol,
    yy16Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx17Limitation_minsubType   = "BARRIER_LOG",
    xx17Limitation_minepsilon   = xy_eps,
    xx17Limitation_mintolerance = xy_tol,
    xx17Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx17Limitation_maxsubType   = "BARRIER_LOG",
    xx17Limitation_maxepsilon   = xy_eps,
    xx17Limitation_maxtolerance = xy_tol,
    xx17Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy17Limitation_minsubType   = "BARRIER_LOG",
    yy17Limitation_minepsilon   = xy_eps,
    yy17Limitation_mintolerance = xy_tol,
    yy17Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy17Limitation_maxsubType   = "BARRIER_LOG",
    yy17Limitation_maxepsilon   = xy_eps,
    yy17Limitation_maxtolerance = xy_tol,
    yy17Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx18Limitation_minsubType   = "BARRIER_LOG",
    xx18Limitation_minepsilon   = xy_eps,
    xx18Limitation_mintolerance = xy_tol,
    xx18Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx18Limitation_maxsubType   = "BARRIER_LOG",
    xx18Limitation_maxepsilon   = xy_eps,
    xx18Limitation_maxtolerance = xy_tol,
    xx18Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy18Limitation_minsubType   = "BARRIER_LOG",
    yy18Limitation_minepsilon   = xy_eps,
    yy18Limitation_mintolerance = xy_tol,
    yy18Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy18Limitation_maxsubType   = "BARRIER_LOG",
    yy18Limitation_maxepsilon   = xy_eps,
    yy18Limitation_maxtolerance = xy_tol,
    yy18Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx19Limitation_minsubType   = "BARRIER_LOG",
    xx19Limitation_minepsilon   = xy_eps,
    xx19Limitation_mintolerance = xy_tol,
    xx19Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx19Limitation_maxsubType   = "BARRIER_LOG",
    xx19Limitation_maxepsilon   = xy_eps,
    xx19Limitation_maxtolerance = xy_tol,
    xx19Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy19Limitation_minsubType   = "BARRIER_LOG",
    yy19Limitation_minepsilon   = xy_eps,
    yy19Limitation_mintolerance = xy_tol,
    yy19Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy19Limitation_maxsubType   = "BARRIER_LOG",
    yy19Limitation_maxepsilon   = xy_eps,
    yy19Limitation_maxtolerance = xy_tol,
    yy19Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    xx20Limitation_minsubType   = "BARRIER_LOG",
    xx20Limitation_minepsilon   = xy_eps,
    xx20Limitation_mintolerance = xy_tol,
    xx20Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    xx20Limitation_maxsubType   = "BARRIER_LOG",
    xx20Limitation_maxepsilon   = xy_eps,
    xx20Limitation_maxtolerance = xy_tol,
    xx20Limitation_maxactive    = true

    -- PenaltyBarrier1DLessThan
    yy20Limitation_minsubType   = "BARRIER_LOG",
    yy20Limitation_minepsilon   = xy_eps,
    yy20Limitation_mintolerance = xy_tol,
    yy20Limitation_minactive    = true

    -- PenaltyBarrier1DLessThan
    yy20Limitation_maxsubType   = "BARRIER_LOG",
    yy20Limitation_maxepsilon   = xy_eps,
    yy20Limitation_maxtolerance = xy_tol,
    yy20Limitation_maxactive    = true

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
        n      = 50,
        length = 1,
      },
    },
  },


}

-- EOF
