--[[
/*-----------------------------------------------------------------------*\
 |  file: Train_Data.lua                                                 |
 |                                                                       |
 |  version: 1.0   date 20/1/2021                                        |
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
ubMax    = 2
tol_max  = 0.01
uaMax    = 10
epsi_max = 0.01

content = {

  -- activate run time debug
  data.Debug = false,

  -- Level of message
  InfoLevel = 4,

  -- maximum number of threads used for linear algebra and various solvers
  N_threads   = [1,$MAX_THREAD_NUM-1].max,
  U_threaded  = true,
  F_threaded  = true,
  JF_threaded = true,
  LU_threaded = true,

  -- Enable doctor
  Doctor = false,

  -- Activate dynamic debugging
  Debug = false,

  -- Enable check jacobian
  JacobianCheck            = false,
  JacobianCheckFull        = false,
  JacobianCheck_epsilon    = 1e-4,
  FiniteDifferenceJacobian = false,

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "Train_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  ControlSolver = {
    -- ==============================================================
    -- "Hyness", "NewtonDumped", "LM", "YS", "QN"
    -- "LM" = Levenberg–Marquardt, "YS" = Yixun Shi, "QN" = Quasi Newton
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
    initial_x = SET,
    initial_v = SET,
    final_x   = SET,
    final_v   = SET,
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
    uaMax = uaMax,
    ubMax = ubMax,

    -- Guess Parameters

    -- Boundary Conditions
    v_f = 0,
    v_i = 0,
    x_f = 6,
    x_i = 0,

    -- Post Processing Parameters

    -- User Function Parameters
    alpha = 0.3,
    beta  = 0.14,
    gm    = 0.16,

    -- Continuation Parameters
    tol_max  = tol_max,
    tol_min  = 0.001,
    epsi_max = epsi_max,
    epsi_min = 0.0001,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC
  -- Barrier subtype: LOGARITHMIC, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    uaControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = epsi_max,
      tolerance = tol_max,
    },
    ubControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = epsi_max,
      tolerance = tol_max,
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
        n      = 25,
        length = 0.25,
      },
      
      {
        n      = 3000,
        length = 0.75,
      },
      
      {
        n      = 100,
        length = 3.8,
      },
    },
  },


}

-- EOF
