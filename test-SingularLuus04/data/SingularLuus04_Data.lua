--[[
/*-----------------------------------------------------------------------*\
 |  file: SingularLuus04_Data.lua                                        |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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

-- Auxiliary values
u_tol     = 0.01
u_epsi    = 0.01
Tf        = 6
epsilon_X = 1e-07

content = {

  -- Level of message
  InfoLevel = 4,

  -- maximum number of threads used for linear algebra and various solvers
  N_threads   = 4,
  U_threaded  = true,
  F_threaded  = true,
  JF_threaded = true,
  LU_threaded = true,

  -- Enable doctor
  Doctor = false,

  -- Enable check jacobian
  JacobianCheck            = false,
  JacobianCheckFull        = false,
  JacobianCheck_epsilon    = 1e-4,
  FiniteDifferenceJacobian = false,

  -- Redirect output to GenericContainer["stream_output"]
  RedirectStreamToString = false,

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "SingularLuus04_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  -- Redirect output to GenericContainer["stream_output"]
  RedirectStreamToString = false,

  ControlSolver = {
    -- "LU", "LUPQ", "QR", "QRP", "SVD", "LSS", "LSY", "MINIMIZATION"
    factorization = "LU",
    MaxIter       = 50,
    Tolerance     = 1e-9,
    Iterative     = false,
    InfoLevel     = -1 -- suppress all messages
  },

  -- setup solver
  Solver = {
    -- Linear algebra factorization selection:
    -- "LU", "QR", "QRP", "SUPERLU"
    factorization = "LU",

    -- Last Block selection:
    -- "LU", "LUPQ", "QR", "QRP", "SVD", "LSS", "LSY"
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
    initial_y = SET,
    initial_z = SET,
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
    epsilon_X = epsilon_X,

    -- Guess Parameters

    -- Boundary Conditions
    x_i = 1,
    y_i = 0,
    z_i = 0,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    u_epsi     = u_epsi,
    min_u_epsi = 1e-07,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty type controls: 'QUADRATIC', 'QUADRATIC2', 'PARABOLA', 'CUBIC'
  -- Barrier type controls: 'LOGARITHMIC', 'COS_LOGARITHMIC', 'TAN2', HYPERBOLIC'

  Controls = {
    uControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = u_epsi,
      tolerance = u_tol,
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
        n      = 2000,
        length = Tf,
      },
    },
  },


}

-- EOF
