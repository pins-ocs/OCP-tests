--[[
/*-----------------------------------------------------------------------*\
 |  file: CNOC_Data.lua                                                  |
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
v_nom                    = 0.173
deltaFeed                = v_nom
js_min                   = -50
js_max                   = 30
mesh_segments            = 100
path_following_tolerance = 1.0e-05
pf_error                 = path_following_tolerance
jn_max                   = 65

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
  -- DumpFile = "CNOC_dump",

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
    initial_n  = SET,
    initial_vs = SET,
    initial_vn = SET,
    initial_as = SET,
    initial_an = SET,
    final_n    = SET,
    final_vs   = SET,
    final_vn   = SET,
    final_as   = SET,
    final_an   = SET,
    initial_s  = SET,
    final_s    = SET,
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
    an_max                   = 1.2,
    as_max                   = 2.1,
    ax_max                   = 2.1,
    ay_max                   = 2.1,
    jn_max                   = jn_max,
    js_max                   = js_max,
    js_min                   = js_min,
    deltaFeed                = deltaFeed,
    path_following_tolerance = path_following_tolerance,

    -- Guess Parameters

    -- Boundary Conditions
    an_f = 0,
    an_i = 0,
    as_f = 0,
    as_i = 0,
    n_f  = 0,
    n_i  = 0,
    vn_f = 0,
    vn_i = 0,
    vs_f = 0,
    vs_i = 0,

    -- Post Processing Parameters
    pf_error = pf_error,

    -- User Function Parameters

    -- Continuation Parameters

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty type controls: 'QUADRATIC', 'QUADRATIC2', 'PARABOLA', 'CUBIC'
  -- Barrier type controls: 'LOGARITHMIC', 'COS_LOGARITHMIC', 'TAN2', HYPERBOLIC'

  Controls = {
    jsControl = {
      type      = 'LOGARITHMIC',
      epsilon   = 0.01,
      tolerance = 0.01,
    },
    jnControl = {
      type      = 'LOGARITHMIC',
      epsilon   = 0.01,
      tolerance = 0.01,
    },
  },

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: "PENALTY_REGULAR", "PENALTY_SMOOTH", "PENALTY_PIECEWISE"
  -- Barrier subtype: "BARRIER_LOG", "BARRIER_LOG_EXP", "BARRIER_LOG0"
    -- PenaltyBarrier1DGreaterThan
    timePositivesubType   = "BARRIER_LOG",
    timePositiveepsilon   = 0.01,
    timePositivetolerance = 0.01,
    timePositiveactive    = true

    -- PenaltyBarrier1DGreaterThan
    vLimitsubType   = "PENALTY_PIECEWISE",
    vLimitepsilon   = 0.01,
    vLimittolerance = 0.01,
    vLimitactive    = true

    -- PenaltyBarrier1DInterval
    PathFollowingTolerancesubType   = "PENALTY_REGULAR",
    PathFollowingToleranceepsilon   = 0.01,
    PathFollowingTolerancetolerance = 0.1,
    PathFollowingTolerancemin       = -1,
    PathFollowingTolerancemax       = 1,
    PathFollowingToleranceactive    = true

    -- PenaltyBarrier1DInterval
    as_limitsubType   = "PENALTY_REGULAR",
    as_limitepsilon   = 0.01,
    as_limittolerance = 0.01,
    as_limitmin       = -1,
    as_limitmax       = 1,
    as_limitactive    = true

    -- PenaltyBarrier1DInterval
    an_limitsubType   = "PENALTY_REGULAR",
    an_limitepsilon   = 0.01,
    an_limittolerance = 0.01,
    an_limitmin       = -1,
    an_limitmax       = 1,
    an_limitactive    = true

    -- PenaltyBarrier1DInterval
    ax_limitsubType   = "PENALTY_REGULAR",
    ax_limitepsilon   = 0.01,
    ax_limittolerance = 0.01,
    ax_limitmin       = -1,
    ax_limitmax       = 1,
    ax_limitactive    = true

    -- PenaltyBarrier1DInterval
    ay_limitsubType   = "PENALTY_REGULAR",
    ay_limitepsilon   = 0.01,
    ay_limittolerance = 0.01,
    ay_limitmin       = -1,
    ay_limitmax       = 1,
    ay_limitactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: T O O L P A T H 2 D
  ToolPath2D = 
  {
    segments = {
      
      {
        x0           = -0.01,
        y0           = 0,
        x1           = 0.02,
        y1           = 0.002,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.002,
        x1           = 0.05,
        y1           = 0,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.05,
        y0           = 0,
        x1           = 0.05,
        y1           = 0.01,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
        angle0       = 0,
        angle1       = 3.1415,
      },
      
      {
        x0           = 0.05,
        y0           = 0.01,
        x1           = 0.02,
        y1           = 0.012,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.012,
        x1           = -0.01,
        y1           = 0.01,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.01,
        x1           = -0.01,
        y1           = 0.02,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.02,
        x1           = 0.02,
        y1           = 0.022,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.022,
        x1           = 0.05,
        y1           = 0.02,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.05,
        y0           = 0.02,
        x1           = 0.05,
        y1           = 0.03,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
        angle0       = 0,
        angle1       = 3.1415,
      },
      
      {
        x0           = 0.05,
        y0           = 0.03,
        x1           = 0.02,
        y1           = 0.032,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.032,
        x1           = -0.01,
        y1           = 0.03,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.03,
        x1           = -0.01,
        y1           = 0.04,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.04,
        x1           = 0.02,
        y1           = 0.042,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.042,
        x1           = 0.05,
        y1           = 0.04,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.05,
        y0           = 0.04,
        x1           = 0.05,
        y1           = 0.05,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
        angle0       = 0,
        angle1       = 3.1415,
      },
      
      {
        x0           = 0.05,
        y0           = 0.05,
        x1           = 0.02,
        y1           = 0.052,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.052,
        x1           = -0.01,
        y1           = 0.05,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.05,
        x1           = -0.01,
        y1           = 0.06,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = -0.01,
        y0           = 0.06,
        x1           = 0.02,
        y1           = 0.062,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
      
      {
        x0           = 0.02,
        y0           = 0.062,
        x1           = 0.05,
        y1           = 0.06,
        feedRate     = v_nom,
        spindleRate  = 3000,
        crossSection = 1,
        tolerance    = path_following_tolerance,
        n            = mesh_segments,
      },
    },
  },


}

-- EOF
