#-----------------------------------------------------------------------#
#  file: Farmer_Data.rb                                                 #
#                                                                       #
#  version: 1.0   date 12/11/2020                                       #
#                                                                       #
#  Copyright (C) 2020                                                   #
#                                                                       #
#      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             #
#      Dipartimento di Ingegneria Industriale                           #
#      Universita` degli Studi di Trento                                #
#      Via Sommarive 9, I-38123, Trento, Italy                          #
#      email: enrico.bertolazzi@unitn.it                                #
#             francesco.biral@unitn.it                                  #
#             paolo.bosetti@unitn.it                                    #
#-----------------------------------------------------------------------#


include Mechatronix

# Auxiliary values

mechatronix do |data|

  # Level of message
  data.InfoLevel = 4

  # Activate dynamic debugging
  data.Debug = false

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads   = [1,$MAX_THREAD_NUM-1].max
  data.U_threaded  = true
  data.F_threaded  = true
  data.JF_threaded = true
  data.LU_threaded = true

  # Enable doctor
  data.Doctor = false

  # Enable check jacobian
  data.JacobianCheck            = false
  data.JacobianCheckFull        = false
  data.JacobianCheck_epsilon    = 1e-4
  data.FiniteDifferenceJacobian = false

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "Farmer_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'MINIMIZATION'
    :factorization => 'LU',
    # ==============================================================
    :Rcond     => 1e-14,  # reciprocal condition number threshold for QR, SVD, LSS, LSY
    :MaxIter   => 50,
    :Tolerance => 1e-9,
    :Iterative => true,
    :InfoLevel => -1,     # suppress all messages
  }

  # setup solver
  data.Solver = {
    # Linear algebra factorization selection:
    # 'LU', 'QR', 'QRP', 'SUPERLU'
    # =================
    :factorization => 'LU',
    # =================

    # Last Block selection:
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY'
    # ==============================================
    :last_factorization => 'LU',
    # ==============================================

    # choose solves: Hyness, NewtonDumped
    # ===================================
    :solver => "Hyness",
    # ===================================

    # solver parameters
    :max_iter             => 120,
    :max_step_iter        => 40,
    :max_accumulated_iter => 800,
    :tolerance            => 9.999999999999999e-10,

    # continuation parameters
    :ns_continuation_begin => 0,
    :ns_continuation_end   => 0,
    :continuation => {
      :initial_step   => 0.2,   # initial step for continuation
      :min_step       => 0.001, # minimum accepted step for continuation
      :reduce_factor  => 0.5,   # p fails, reduce step by this factor
      :augment_factor => 1.5,   # if step successful in less than few_iteration augment step by this factor
      :few_iterations => 8,     #
    }
  }

  # Boundary Conditions
  data.BoundaryConditions = {
    :initial_x1  => SET,
    :initial_x2  => SET,
    :initial_x3  => SET,
    :initial_res => SET,
    :initial_x4  => SET,
  }

  # Guess
  data.Guess = {
    # possible value: zero, default, none, warm
    :initialize => 'zero',
    # possible value: default, none, warm, spline, table
    :guess_type => 'default',
  }

  data.Parameters = {

    # Model Parameters
    :P1     => 0.1,
    :P2     => 0.1,
    :t1     => 0,
    :t2     => 60,
    :tau__1 => 3,
    :tau__2 => 25,
    :tau__3 => 10,
    :tau__4 => 60,
    :tau__5 => 120,
    :w1     => 1.3,
    :w2     => 0.1,
    :w3     => 1.2,
    :w4     => 0.9,
    :wJ1    => 1,
    :wJ2    => 1,
    :wJ3    => 1,
    :wJ4    => 1,
    :wP     => 1,

    # Guess Parameters

    # Boundary Conditions
    :res0 => 0.001,
    :x10  => 0.001,
    :x20  => 0.001,
    :x30  => 0.001,
    :x40  => 0.001,

    # Post Processing Parameters

    # User Function Parameters

    # Continuation Parameters

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty type controls: 'QUADRATIC', 'QUADRATIC2', 'PARABOLA', 'CUBIC'
  # Barrier type controls: 'LOGARITHMIC', 'COS_LOGARITHMIC', 'TAN2', 'HYPERBOLIC'

  data.Controls = {}
  data.Controls[:x1__oControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => 0.001,
    :tolerance => 0.001
  }

  data.Controls[:x2__oControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => 0.001,
    :tolerance => 0.001
  }

  data.Controls[:x3__oControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => 0.001,
    :tolerance => 0.001
  }

  data.Controls[:x4__oControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => 0.001,
    :tolerance => 0.001
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: 'PENALTY_REGULAR', 'PENALTY_SMOOTH', 'PENALTY_PIECEWISE'
  # Barrier subtype: 'BARRIER_LOG', 'BARRIER_LOG_EXP', 'BARRIER_LOG0'

  # PenaltyBarrier1DGreaterThan
  data.Constraints[:LimitX2X4] = {
    :subType   => 'PENALTY_REGULAR',
    :epsilon   => 0.001,
    :tolerance => 0.001,
    :active    => true
  }
  # Constraint2D: none defined

  # User defined classes initialization
  # User defined classes: M E S H
  data.Mesh =
  {
    :s0       => 0,
    :segments => [
      {
        :length => 2,
        :n      => 400,
      },
    ],
  };


end

# EOF
