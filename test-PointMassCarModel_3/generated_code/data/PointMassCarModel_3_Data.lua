--[[
/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Data.lua                                   |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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
road_tol0 = 0.01
p_tol0    = 0.1
p_epsi0   = 0.1
up_tol0   = 0.01
m         = 700
up_epsi0  = 0.1
kD        = 0.2500000000/m
wT0       = 0.01
wT        = wT0

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
  -- DumpFile = "PointMassCarModel_3_dump",

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
    Iterative = false,
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
    ns_continuation_end   = 2,
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
    initial_V    = SET,
    initial_s    = SET,
    final_s      = SET,
    cyclic_n     = SET,
    cyclic_alpha = SET,
    cyclic_V     = SET,
    cyclic_fx    = SET,
    cyclic_Omega = SET,
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
    Pmax          = 200000,
    g             = 9.806,
    kD            = kD,
    m             = m,
    wT            = wT,
    mu__x__max    = 1,
    mu__y__max    = 1.5,
    v__Omega__max = 5,
    v__fx__max    = 30,

    -- Guess Parameters
    Vguess = 10,

    -- Boundary Conditions
    V0 = 0,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    p_epsi0  = p_epsi0,
    p_epsi1  = 0.001,
    wT0      = wT0,
    wT1      = 1,
    up_epsi0 = up_epsi0,
    up_epsi1 = 0.01,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
  -- Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    v__fxControl = {
      type      = ,
      epsilon   = up_epsi0,
      tolerance = up_tol0,
    },
    v__OmegaControl = {
      type      = ,
      epsilon   = up_epsi0,
      tolerance = up_tol0,
    },
  },

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DGreaterThan
    AdherenceEllipsesubType   = "PENALTY_REGULAR",
    AdherenceEllipseepsilon   = p_epsi0,
    AdherenceEllipsetolerance = p_tol0,
    AdherenceEllipseactive    = true

    -- PenaltyBarrier1DGreaterThan
    RoadLeftBordersubType   = "PENALTY_REGULAR",
    RoadLeftBorderepsilon   = p_epsi0,
    RoadLeftBordertolerance = road_tol0,
    RoadLeftBorderactive    = true

    -- PenaltyBarrier1DGreaterThan
    RoadRightBordersubType   = "PENALTY_REGULAR",
    RoadRightBorderepsilon   = p_epsi0,
    RoadRightBordertolerance = road_tol0,
    RoadRightBorderactive    = true

    -- PenaltyBarrier1DGreaterThan
    PowerLimitsubType   = "PENALTY_REGULAR",
    PowerLimitepsilon   = p_epsi0,
    PowerLimittolerance = p_tol0,
    PowerLimitactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: R O A D
  Road = 
  {
    theta0   = 0,
    s0       = 0,
    x0       = 0,
    y0       = 0,
    is_SAE   = false,
    segments = {
      
      {
        length     = 190,
        gridSize   = 1,
        curvature  = 0,
        rightWidth = 60,
        leftWidth  = 15/2.0,
      },
      
      {
        length     = 973.8937227,
        gridSize   = 1,
        curvature  = 0.003225806452,
        rightWidth = 30,
        leftWidth  = 60,
      },
      
      {
        length     = 180,
        gridSize   = 1,
        curvature  = 0,
        rightWidth = 30,
        leftWidth  = 30,
      },
      
      {
        length     = 235.619449,
        gridSize   = 1,
        curvature  = 0.006666666667,
        rightWidth = 15,
        leftWidth  = 20,
      },
      
      {
        length     = 240,
        gridSize   = 1,
        curvature  = 0,
        rightWidth = 30,
        leftWidth  = 30,
      },
      
      {
        length     = 235.619449,
        gridSize   = 1,
        curvature  = -1/150.0,
        rightWidth = 30,
        leftWidth  = 30,
      },
      
      {
        length     = 200,
        gridSize   = 1,
        curvature  = 0,
        rightWidth = 30,
        leftWidth  = 30,
      },
      
      {
        length     = 125.6637062,
        gridSize   = 1,
        curvature  = 0.025,
        rightWidth = 30,
        leftWidth  = 30,
      },
      
      {
        length     = 480,
        gridSize   = 1,
        curvature  = 0,
        rightWidth = 30,
        leftWidth  = 30,
      },
      
      {
        length     = 10,
        gridSize   = 0.1,
        curvature  = 0,
        rightWidth = 30,
        leftWidth  = 30,
      },
    },
  },


}

-- EOF
