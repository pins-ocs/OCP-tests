--[[
/*-----------------------------------------------------------------------*\
 |  file: Underwater_Data.lua                                            |
 |                                                                       |
 |  version: 1.0   date 12/11/2020                                       |
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
epsi_penalty = 0.1
epsi_max     = epsi_penalty
tol_penalty  = 0.01

content = {

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
  -- DumpFile = "Underwater_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

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
    initial_x     = SET,
    initial_z     = SET,
    initial_vx    = SET,
    initial_vz    = SET,
    initial_theta = SET,
    final_x       = SET,
    final_z       = SET,
    final_vx      = SET,
    final_vz      = SET,
    final_theta   = SET,
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
    inertia = 0.12,
    m1      = 13.2,
    m3      = 25.6,

    -- Guess Parameters
    Tguess = 10,

    -- Boundary Conditions
    theta_f = 0,
    theta_i = 0,
    vx_f    = 0,
    vx_i    = 0,
    vz_f    = 0,
    vz_i    = 0,
    x_f     = 2,
    x_i     = 0,
    z_f     = 1,
    z_i     = 1,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    epsi_max = epsi_max,
    epsi_min = 1e-07,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty type controls: 'QUADRATIC', 'QUADRATIC2', 'PARABOLA', 'CUBIC'
  -- Barrier type controls: 'LOGARITHMIC', 'COS_LOGARITHMIC', 'TAN2', 'HYPERBOLIC'

  Controls = {
    u1Control = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = epsi_penalty,
      tolerance = tol_penalty,
    },
    u2Control = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = epsi_penalty,
      tolerance = tol_penalty,
    },
    u3Control = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = epsi_penalty,
      tolerance = tol_penalty,
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
        length = 1,
        n      = 1000,
      },
    },
  },


}

-- EOF
