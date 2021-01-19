--[[
/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Data.lua                                         |
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
tol_TS    = 0.01
epsi_TS   = 0.01
epsi_mass = 0.01
m_i       = 1
tol_mass  = 0.01
h_i       = 1
tol_T     = 0.01
epsi_v    = 0.01
mc        = 0.6
m_f       = mc*m_i
vc        = 620
epsi_T    = 0.01
tol_v     = 0.01
g0        = 1
Dc        = 0.5*vc*m_i/g0
Tmax      = 3.5*g0*m_i
c         = 0.5*(g0*h_i)**(1/2.0)

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
  -- DumpFile = "GoddardRocket_dump",

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
    initial_h = SET,
    initial_v = SET,
    initial_m = SET,
    final_m   = SET,
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
    Tmax = Tmax,
    c    = c,

    -- Guess Parameters

    -- Boundary Conditions
    h_i = h_i,
    m_f = m_f,
    m_i = m_i,
    v_i = 0,

    -- Post Processing Parameters

    -- User Function Parameters
    Dc = Dc,
    g0 = g0,
    hc = 500,

    -- Continuation Parameters
    epsi_T     = epsi_T,
    epsi_TS    = epsi_TS,
    tol_T      = tol_T,
    tol_TS     = tol_TS,
    epsi_TSmin = 1e-10,
    epsi_Tmin  = 1e-07,
    tol_TSmin  = 0.001,
    tol_Tmin   = 0.0001,

    -- Constraints Parameters
  },

  -- functions mapped objects
  MappedObjects = {
  },

  -- Controls
  -- Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC
  -- Barrier subtype: LOGARITHMIC, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  Controls = {
    TControl = {
      type      = 'QUADRATIC',
      epsilon   = epsi_T,
      tolerance = tol_T,
    },
  },

  Constraints = {
  -- Constraint1D
  -- Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  -- Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
    -- PenaltyBarrier1DGreaterThan
    massPositivesubType   = "BARRIER_LOG",
    massPositiveepsilon   = epsi_mass,
    massPositivetolerance = tol_mass,
    massPositiveactive    = true

    -- PenaltyBarrier1DGreaterThan
    vPositivesubType   = "PENALTY_REGULAR",
    vPositiveepsilon   = epsi_v,
    vPositivetolerance = tol_v,
    vPositiveactive    = true

    -- PenaltyBarrier1DGreaterThan
    TSPositivesubType   = "BARRIER_LOG",
    TSPositiveepsilon   = epsi_TS,
    TSPositivetolerance = tol_TS,
    TSPositiveactive    = true

  -- Constraint2D: none defined
  },

  -- User defined classes initialization
  -- User defined classes: M E S H
  Mesh = 
  {
    s0       = 0,
    segments = {
      
      {
        n      = 1000,
        length = 1,
      },
    },
  },


}

-- EOF
