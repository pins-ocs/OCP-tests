--[[
/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Data.lua                                  |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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

content = {

  -- activate run time debug
  data.Debug = false,

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
  JacobianCheck            = false,
  JacobianCheckFull        = false,
  JacobianCheck_epsilon    = 1e-4,
  FiniteDifferenceJacobian = false,

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "EconomicGrowthModel2_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  ControlSolver = {
    -- ==============================================================
    -- "Hyness", "NewtonDumped", "LM", "YS", "QN"
    -- "LM" = Levenberg-Marquardt, "YS" = Yixun Shi, "QN" = Quasi Newton
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
  },

  -- setup solver
  Solver = {
    -- Linear algebra factorization selection:
    -- "LU", "QR", "QRP", "SUPERLU"
    factorization = "LU",

    -- Last Block selection:
    -- "LU", "LUPQ", "QR", "QRP", "SVD", "LSS", "LSY", "PINV"
    last_factorization = "LU",

    -- choose solves: Hyness, NewtonDumped
    solver = "Hyness",

    -- solver parameters
    max_iter             = 300,
    max_step_iter        = 40,
    max_accumulated_iter = 800,
    tolerance            = 9.999999999999999e-10,

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
    initial_x1 = SET,
    initial_x2 = SET,
    initial_y1 = SET,
    initial_y2 = SET,
    FinalX     = SET,
    FinalY1    = SET,
    FinalY2    = SET,
  },

  -- Guess
  Guess = {
    -- possible value: zero, default, none, warm
    initialize = "zero",
    -- possible value: default, none, warm, spline, table
    guess_type = "default"
  },

  Parameters = {

    -- Model Parameters

    -- Guess Parameters
    T_guess = 1,

    -- Boundary Conditions
    Yc   = 10,
    x1_i = 1,
    x2_i = 2,
    y1_i = 1,
    y2_i = 2,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    epsi_max = 0.01,
    epsi_min = 1e-09,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC
  -- Barrier subtype: LOGARITHMIC, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    uControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = 0.01,
      tolerance = 0.01,
    },
  },

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DGreaterThan
    TpositivesubType   = "PENALTY_REGULAR",
    Tpositiveepsilon   = 0.001,
    Tpositivetolerance = 0.001,
    Tpositiveactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: M E S H
  Mesh = 
  {
    s0       = 0,
    segments = {
      
      {
        length = 1,
        n      = 5000,
      },
    },
  },


}

-- EOF
