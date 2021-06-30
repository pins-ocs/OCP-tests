--[[
/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Data.lua                                             |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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
jerk_min = -10
L        = 100
v_max    = 30
jerk_max = 10
wJ       = 1/jerk_max**2
s_f      = L

content = {

  -- activate run time debug
  data.Debug = true,

  -- Enable doctor
  Doctor = false,

  -- Level of message
  InfoLevel = 4,

  -- maximum number of threads used for linear algebra and various solvers
  N_threads   = [1,$MAX_THREAD_NUM-1].max,
  U_threaded  = true,
  F_threaded  = true,
  JF_threaded = true,
  LU_threaded = true,

  -- Enable check jacobian
  JacobianCheck         = false,
  JacobianCheckFull     = false,
  JacobianCheck_epsilon = 1e-4,

  -- Jacobian discretization: 'ANALYTIC', 'ANALYTIC2', 'FINITE_DIFFERENCE'
  JacobianDiscretization = 'ANALYTIC,

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "Crossroad_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  ControlSolver = {
    -- "LM" = Levenberg-Marquardt
    -- "YS" = Yixun Shi
    -- "QN" = Quasi Newton
    -- ==============================================================
    -- "Hyness", "NewtonDumped", "LM", "YS", "QN"
    solver = "QN",
    -- "LU", "LUPQ", "QR", "QRP", "SVD", "LSS", "LSY", "PINV" for Hyness and NewtonDumped
    factorization = "LU",
    -- "BFGS", "DFP", "SR1" for Quasi Newton
    update = "BFGS",
    -- 'EXACT', 'ARMIJO'
    linesearch = "EXACT",
    -- ==============================================================
    MaxIter   = 50,
    Tolerance = 1e-9,
    Iterative = true,
    InfoLevel = -1 -- suppress all messages
    -- ==============================================================
    -- "LM", "YS", "QN"
    InitSolver    = "QN",
    InitMaxIter   = 10,
    InitTolerance = 1e-4
  },

  -- setup solver
  Solver = {
    -- Linear algebra factorization selection:
    -- "LU", "QR", "QRP", "SUPERLU"
    factorization = "LU",

    -- Last Block selection:
    -- "LU", "LUPQ", "QR", "QRP", "SVD", "LSS", "LSY", "PINV"
    last_factorization = "LUPQ",

    -- choose solves: Hyness, NewtonDumped
    solver = "Hyness",

    -- solver parameters
    max_iter             = 300,
    max_step_iter        = 40,
    max_accumulated_iter = 800,
    tolerance            = 1e-09,

    -- continuation parameters
    ns_continuation_begin = 0,
    ns_continuation_end   = 0,
    continuation = {
      initial_step   = 0.2,   -- initial step for continuation
      min_step       = 0.001, -- minimum accepted step for continuation
      reduce_factor  = 0.5,   -- if continuation step fails, reduce step by this factor
      augment_factor = 1.5,   -- if step successful in less than few_iteration augment step by this factor
      few_iterations = 8
    }
  },

  -- Boundary Conditions (SET/FREE)
  BoundaryConditions = {
    initial_s = SET,
    initial_v = SET,
    initial_a = SET,
    final_s   = SET,
    final_v   = SET,
    final_a   = SET,
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
    L         = L,
    wJ        = wJ,
    wT        = 10,
    alat_max  = 4,
    along_max = 4,
    jerk_max  = jerk_max,
    jerk_min  = jerk_min,

    -- Guess Parameters
    Vmean = 2,

    -- Boundary Conditions
    a_f = 0,
    a_i = 0,
    s_f = s_f,
    s_i = 0,
    v_f = 1,
    v_i = 0,

    -- Post Processing Parameters

    -- User Function Parameters
    kappa0 = 0,
    kappa1 = 1/10.00,
    kappa2 = 1/10.00,

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
    jerkControl = {
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
    TpositivesubType   = "PENALTY_REGULAR",
    Tpositiveepsilon   = 0.01,
    Tpositivetolerance = 0.01,
    Tpositiveactive    = true

    -- PenaltyBarrier1DGreaterThan
    AccBoundsubType   = "PENALTY_REGULAR",
    AccBoundepsilon   = 0.01,
    AccBoundtolerance = 0.01,
    AccBoundactive    = true

    -- PenaltyBarrier1DInterval
    VelBoundsubType   = "PENALTY_REGULAR",
    VelBoundepsilon   = 0.01,
    VelBoundtolerance = 0.01,
    VelBoundmin       = 0,
    VelBoundmax       = v_max,
    VelBoundactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: M E S H
  Mesh = 
  {
    s0       = 0,
    segments = {
      
      {
        n      = 100,
        length = 0.5,
      },
      
      {
        n      = 100,
        length = 0.5,
      },
    },
  },


}

-- EOF
