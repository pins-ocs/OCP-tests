--[[
/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Data.lua                                           |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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
eps_l    = 0.01
tol_c0   = 0.1
tol_c    = tol_c0
rw       = 0.3
eps_c0   = 0.1
eps_c    = eps_c0
tol_l    = 0.01
w__t0    = 1
w__t     = w__t0
L        = 300
mesh_np  = 2.000000000*L
h__b     = 1
v__0     = 10
omega__0 = 1/rw*v__0
TT__max  = 800
E__pow   = 60*TT__max

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
  -- DumpFile = "TyreDynamic_dump",

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
      max_accumulated_iter = 1500,
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
      max_accumulated_iter = 1500,
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
    initial_v = SET,
    initial_b = SET,
    final_v   = SET,
    lambda__i = SET,
    p__i      = SET,
    omega__i  = SET,
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
    Iw         = 0.4351,
    b__lb      = -1,
    b__ub      = 1,
    l__x       = 0.1,
    m          = 115,
    p__lb      = -1,
    p__ub      = 1,
    rw         = rw,
    tau__b     = 0.1,
    tau__p     = 0.1,
    v__adm     = 1,
    v__lb      = 0,
    v__ub      = 10000,
    w__U       = 0.0001,
    w__t       = w__t,
    b__o__lb   = -1,
    b__o__ub   = 1,
    lambda__lb = -1,
    lambda__ub = 1,
    omega__lb  = 0,
    omega__ub  = 10000,
    p__o__lb   = -1,
    p__o__ub   = 1,

    -- Guess Parameters
    p__ss      = 0.175698,
    lambda__ss = 0.000554,
    omega__ss  = 33.351785,

    -- Boundary Conditions
    b__ss = 0.1,
    v__ss = 10,

    -- Post Processing Parameters
    g           = 9.81,
    h__b        = h__b,
    lambda__max = 1,

    -- User Function Parameters
    BT__max  = 300,
    Bx0      = 10,
    Cx0      = 1.6,
    E__pow   = E__pow,
    TB__max  = 500,
    TT__max  = TT__max,
    kD       = 0.2,
    kDo      = 0.001,
    mu__x0   = 1,
    rho_a    = 1.1839,
    BTv__max = 50,

    -- Continuation Parameters
    eps_c0 = eps_c0,
    eps_c1 = 0.01,
    tol_c0 = tol_c0,
    tol_c1 = 0.01,
    w__t0  = w__t0,
    w__t1  = 1,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  -- PositivePartRegularizedWithErf
    posParth = 0.01,
  -- NegativePartRegularizedWithErf
    negParth = 0.01,
  -- ClipSuperior
    clipSuph = 0.01,
  -- ClipIntervalWithErf
    clipIntdelta = 0,
    clipIntdelta2 = 0,
    clipInth = 0.01,
  -- SignRegularizedWithErf
    sign_regh = 0.01,
  -- AbsoluteValueRegularizedWithErf
    abs_regh = 0.01,
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, QUARTIC, BIPOWER
  -- Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    b__oControl = {
      type      = ,
      epsilon   = eps_c,
      tolerance = tol_c,
    },
    p__oControl = {
      type      = ,
      epsilon   = eps_c,
      tolerance = tol_c,
    },
  },

  Constraints = {
  --  _  _____
  -- | ||_   _|
  -- | |__| |
  -- |____|_|
  -- Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DLessThan
    OnlyBrakingRearsubType   = "PENALTY_PIECEWISE",
    OnlyBrakingRearepsilon   = 0.001,
    OnlyBrakingReartolerance = h__b,
    OnlyBrakingRearactive    = true

    -- PenaltyBarrier1DLessThan
    OnlyTractionRearsubType   = "PENALTY_PIECEWISE",
    OnlyTractionRearepsilon   = 0.001,
    OnlyTractionReartolerance = h__b,
    OnlyTractionRearactive    = true

    -- PenaltyBarrier1DLessThan
    LongSlipRear_minsubType   = "PENALTY_PIECEWISE",
    LongSlipRear_minepsilon   = eps_l,
    LongSlipRear_mintolerance = tol_l,
    LongSlipRear_minactive    = true

    -- PenaltyBarrier1DLessThan
    LongSlipRear_maxsubType   = "PENALTY_PIECEWISE",
    LongSlipRear_maxepsilon   = eps_l,
    LongSlipRear_maxtolerance = tol_l,
    LongSlipRear_maxactive    = true

    -- PenaltyBarrier1DLessThan
    v_minsubType   = "BARRIER_LOG",
    v_minepsilon   = eps_l,
    v_mintolerance = tol_l,
    v_minactive    = true

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
        n      = 0.4*mesh_np,
        length = 0.1*L,
      },
      
      {
        n      = 0.8*mesh_np,
        length = 0.8*L,
      },
      
      {
        n      = 0.4*mesh_np,
        length = 0.1*L,
      },
    },
  },


}

-- EOF
