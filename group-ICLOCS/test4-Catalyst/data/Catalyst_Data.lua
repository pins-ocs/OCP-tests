--[[
/*-----------------------------------------------------------------------*\
 |  file: Catalyst_Data.lua                                              |
 |                                                                       |
 |  version: 1.0   date 17/8/2018                                        |
 |                                                                       |
 |  Copyright (C) 2018                                                   |
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
epsi_ctrl = 1e-05
tol_ctrl  = 1e-05


content = {

  -- LU factorization selection:
  -- CYCLIC_REDUCTION_LU, CYCLIC_REDUCTION_QR, CYCLIC_REDUCTION_QRP
  LU_method = CYCLIC_REDUCTION_LU,

  -- Last Block selection:
  -- LASTBLOCK_LU, LASTBLOCK_LUPQ, LASTBLOCK_QR, LASTBLOCK_QRP
  -- LASTBLOCK_SVD, LASTBLOCK_LSS, LASTBLOCK_LSY
  Last_block = LASTBLOCK_LSS,

  -- Solver selection:
  -- CS_use_LU, CS_use_LUPQ, CS_use_QR, CS_use_SVD
  -- CS_use_LSS, CS_use_LSY, CS_use_MINIMIZATION
  ControlSolutionMethod    = CS_use_LSS,
  ControlSolutionRcond     = 1e-14, -- reciprocal condition number thresold for QR, SVD, LSS, LSY
  ControlSolutionMaxIter   = 50,
  ControlSolutionTolerance = 1e-9,

  -- Enable doctor
  Doctor = false,

  -- Enable check jacobian
  JacobianCheck            = false,
  JacobianCheck_epsilon    = 1e-4,
  FiniteDifferenceJacobian = false,

  -- Redirect output to GenericContainer["stream_output"]
  RedirectStreamToString = false,

  -- Dump Function and Jacobian if uncommented
  -- DumpFile = "Catalyst_dump",

  -- Level of message
  InfoLevel = 4,

  -- spline output (all values as function of "s")
  -- OutputSplines = [0],

  -- Redirect output to GenericContainer["stream_output"]
  RedirectStreamToString = false,

  -- setup solver
  Solver = {
    max_iter             = 300,
    max_step_iter        = 40,
    max_accumulated_iter = 800,
    tolerance            = 1e-09,
    -- continuation parameters
    initial_step   = 0.2,   -- initial step for continuation
    min_step       = 0.001, -- minimum accepted step for continuation
    reduce_factor  = 0.5,   -- if continuation steo fails, reduce step by this factor
    augment_factor = 1.5,   -- if step successfull in less than few_iteration augment step by this factor
    few_iterations = 8,
  },

  -- Boundary Conditions (SET/FREE)
  BoundaryConditions = {
    initial_x1 = SET,
    initial_x2 = SET,
  },

  Parameters = {

    -- Model Parameters

    -- Guess Parameters

    -- Boundary Conditions
    x1_i = 1,
    x2_i = 0,

    -- Post Processing Parameters

    -- User Function Parameters

    -- Continuation Parameters

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty type controls: U_QUADRATIC, U_QUADRATIC2, U_PARABOLA, U_CUBIC
  -- Barrier type controls: U_LOGARITHMIC, U_COS_LOGARITHMIC, U_HYPERBOLIC

  Controls = {
    uControl = {
      type      = U_COS_LOGARITHMIC,
      epsilon   = epsi_ctrl,
      tolerance = tol_ctrl,
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
