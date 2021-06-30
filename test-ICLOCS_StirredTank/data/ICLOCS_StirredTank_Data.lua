--[[
/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Data.lua                                    |
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
w_exp_min = 0
epsi_ctrl = 0.001
tol_T     = 1
epsi_T    = 0.001
x_epsi    = 0.1
x_tol     = 0.01
tol_ctrl  = 0.001
w         = exp(w_exp_min)

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
  -- DumpFile = "ICLOCS_StirredTank_dump",

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
    ns_continuation_end   = 1,
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
    En    = 5,
    Tc    = 0.38158,
    Tf    = 0.3947,
    a     = 0.117,
    k     = 300,
    theta = 20,
    wT    = 0.001,

    -- Guess Parameters
    T_guess = 90,
    u_f     = 0.76,

    -- Boundary Conditions
    w    = w,
    x1_f = 0.26,
    x1_i = 0.98,
    x2_f = 0.65,
    x2_i = 0.39,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    w_exp_max = 15,
    w_exp_min = w_exp_min,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC, BIPOWER
  -- Barrier subtype: LOGARITHMIC, LOGARITHMIC2, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    uControl = {
      type      = ,
      epsilon   = epsi_ctrl,
      tolerance = tol_ctrl,
    },
  },

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: WALL_ERF_POWER1, WALL_ERF_POWER2, WALL_ERF_POWER3, WALL_TANH_POWER1, WALL_TANH_POWER2, WALL_TANH_POWER3, WALL_PIECEWISE_POWER1, WALL_PIECEWISE_POWER2, WALL_PIECEWISE_POWER3, PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_1X, BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DInterval
    tfboundsubType   = "BARRIER_LOG",
    tfboundepsilon   = epsi_T,
    tfboundtolerance = tol_T,
    tfboundmin       = 10,
    tfboundmax       = 200,
    tfboundactive    = true

    -- PenaltyBarrier1DInterval
    x1boundsubType   = "BARRIER_LOG",
    x1boundepsilon   = x_epsi,
    x1boundtolerance = x_tol,
    x1boundmin       = 0,
    x1boundmax       = 1,
    x1boundactive    = true

    -- PenaltyBarrier1DInterval
    x2boundsubType   = "BARRIER_LOG",
    x2boundepsilon   = x_epsi,
    x2boundtolerance = x_tol,
    x2boundmin       = 0,
    x2boundmax       = 1,
    x2boundactive    = true

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
        length = 1,
      },
    },
  },


}

-- EOF