--[[
/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Data.lua                                 |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
u_epsilon     = 0.1
WTF0          = 1.0
one_km        = 1000.0
re            = 6378*one_km
V_f           = 2*one_km
V_i           = 2*one_km
h_i           = 40*one_km
S             = 7500*one_km
u_tolerance   = 0.1
WTF           = WTF0
CTRL0         = 1.0
CTRL          = CTRL0
ODE0          = 0.0
ODE           = ODE0
to_rad        = 0.01745329252
theta_f       = 2*to_rad
G_i           = -15*to_rad
sigma_dot_max = 10*to_rad
G_f           = -15*to_rad
phi_f         = 0.5*to_rad

content = {

  -- activate run time debug
  Debug = true,

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
  N_threads   = 4,
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
  JacobianDiscretization = "ANALYTIC",

  -- jacobian discretization BC part: 'ANALYTIC', 'FINITE_DIFFERENCE'
  JacobianDiscretizationBC = "ANALYTIC",

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "HypersonicProblem3DOF_dump",

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
    -- 'Hyness', 'NewtonDumped', 'LevenbergMarquardt', 'YixunShi', 'QuasiNewton'
    solver = 'NewtonDumped',
    -- 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV' for Hyness and NewtonDumped
    factorization = 'LU',
    Iterative = true,
    InfoLevel = -1, -- suppress all messages
    -- 'LevenbergMarquardt', 'YixunShi', 'QuasiNewton'
    initialize_control_solver = 'QuasiNewton',

    -- solver parameters
    NewtonDumped = {
      -- "MERIT_D2", "MERIT_F2", "MERIT_LOG_D2", "MERIT_LOG_F2"
      -- "MERIT_F2_and_D2", "MERIT_LOG_F2_and_D2", "MERIT_LOG_F2_and_LOG_D2"
      merit                = "MERIT_LOG_F2_and_LOG_D2",
      max_iter             = 50,
      max_step_iter        = 10,
      max_accumulated_iter = 150,
      tolerance            = 1.0e-10, -- tolerance for stopping criteria
      c1                   = 0.01, -- Constant for Armijo step acceptance criteria
      lambda_min           = 1.0e-10, -- minimum lambda for linesearch
      dump_min             = 0.25, -- (0,0.5)  dumping factor for linesearch
      dump_max             = 0.9, -- (0.5,0.99)
      -- Potenza `n` della funzione di interpolazione per minimizzazione
      -- f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      merit_power          = 6, -- (2..100)
      -- check that search direction and new estimated search direction have an angle less than check_angle
      -- if check_angle == 0 no check is done
      check_angle            = 120,
      check_ratio_norm_two_f = 2,  -- check that ratio of ||f(x_{k+1})||_2/||f(x_{k})||_2 <= NUMBER
      check_ratio_norm_two_d = 2,  -- check that ratio of ||d(x_{k+1})||_2/||d(x_{k})||_2 <= NUMBER
      check_ratio_norm_one_f = 2,  -- check that ratio of ||f(x_{k+1})||_1/||f(x_{k})||_1 <= NUMBER
      check_ratio_norm_one_d = 2,  -- check that ratio of ||d(x_{k+1})||_1/||d(x_{k})||_1 <= NUMBER
    },

    Hyness = { max_iter = 50, tolerance = 1.0e-10 },

    LevenbergMarquardt = { max_iter = 50, tolerance = 1.0e-10, low_tolerance = 1e-6 },
    YixunShi           = { max_iter = 50, tolerance = 1.0e-10, low_tolerance = 1e-6 },
    QuasiNewton = {
      max_iter      = 50,
      tolerance     = 1.0e-10,
      low_tolerance = 1e-6,
      update        = 'BFGS',  -- 'BFGS', 'DFP', 'SR1' for Quasi Newton
      linesearch    = 'EXACT', -- 'EXACT', 'ARMIJO'
    },
  },

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
      dump_max = 0.95, -- (0.5,0.99)

      -- Potenza `n` della funzione di interpolazione per minimizzazione
      -- f(x) = f0 * exp( (f0'/f0) * x ) + C * x^n
      merit_power = 2, -- (2..100)

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
    ns_continuation_end   = 3,
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
    initial_h     = SET,
    initial_theta = SET,
    initial_phi   = SET,
    initial_V     = SET,
    initial_G     = SET,
    initial_psi   = SET,
    initial_sigma = SET,
    final_h       = SET,
    final_theta   = SET,
    final_phi     = SET,
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
    Aref          = 0.29186,
    CD0           = 0.1971,
    CD1           = -0.1427,
    CD2           = 3.7677,
    CL0           = -0.0448,
    CL1           = 2.5457,
    CTRL          = CTRL,
    ODE           = ODE,
    S             = S,
    WTF           = WTF,
    m             = 340.19,
    mu            = 398600000000000.0,
    re            = re,
    rho0          = 1.2,
    Tf_guess      = 100.0,
    sigma_dot_max = sigma_dot_max,

    -- Guess Parameters

    -- Boundary Conditions
    G_i     = G_i,
    V_i     = V_i,
    h_f     = 0.0,
    h_i     = h_i,
    phi_f   = phi_f,
    phi_i   = 0.0,
    psi_i   = 0.0,
    sigma_i = 0.0,
    theta_f = theta_f,
    theta_i = 0.0,

    -- Post Processing Parameters
    to_deg = 57.29577951,

    -- User Function Parameters
    G_f   = G_f,
    V_f   = V_f,
    psi_f = 0.0,

    -- Continuation Parameters
    CTRL0 = CTRL0,
    CTRL1 = 0.0,
    ODE0  = ODE0,
    ODE1  = 1.0,
    WTF0  = WTF0,
    WTF1  = 0.0,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, PARABOLA, CUBIC, QUARTIC, BIPOWER
  -- Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    u2Control = {
      type      = "COS_LOGARITHMIC",
      epsilon   = u_epsilon,
      tolerance = u_tolerance,
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
    G_bound_minsubType   = "BARRIER_LOG",
    G_bound_minepsilon   = 0.1,
    G_bound_mintolerance = 0.1,
    G_bound_minactive    = true

    -- PenaltyBarrier1DLessThan
    G_bound_maxsubType   = "BARRIER_LOG",
    G_bound_maxepsilon   = 0.1,
    G_bound_maxtolerance = 0.1,
    G_bound_maxactive    = true

  -- Constraint1D: none defined
  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: M E S H
  Mesh = 
  {
    s0       = 0.0,
    segments = {
      
      {
        n      = 400.0,
        length = 1.0,
      },
    },
  },


}

-- EOF