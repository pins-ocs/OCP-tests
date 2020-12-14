--[[
/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Data.lua                                              |
 |                                                                       |
 |  version: 1.0   date 14/12/2020                                       |
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
u_tolerance0 = 0.01
u_epsilon0   = 0.01
u_tolerance  = u_tolerance0
u_epsilon    = u_epsilon0

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
  -- DumpFile = "RobotArm_dump",

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  ControlSolver = {
    -- "LU", "LUPQ", "QR", "QRP", "SVD", "LSS", "LSY", "PINV"
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
    initial_rho    = SET,
    initial_theta  = SET,
    initial_phi    = SET,
    initial_rho1   = SET,
    initial_theta1 = SET,
    initial_phi1   = SET,
    final_rho      = SET,
    final_theta    = SET,
    final_phi      = SET,
    final_rho1     = SET,
    final_theta1   = SET,
    final_phi1     = SET,
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
    L = 5,

    -- Guess Parameters
    Tguess = 1,

    -- Boundary Conditions
    W = 0,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters
    u_epsilon0   = u_epsilon0,
    u_epsilon1   = 1e-05,
    u_tolerance0 = u_tolerance0,
    u_tolerance1 = 1e-05,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  Controls = {
    u_rhoControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = u_epsilon,
      tolerance = u_tolerance,
    },
    u_thetaControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = u_epsilon,
      tolerance = u_tolerance,
    },
    u_phiControl = {
      type      = 'COS_LOGARITHMIC',
      epsilon   = u_epsilon,
      tolerance = u_tolerance,
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
        n      = 400,
      },
    },
  },


}

-- EOF
