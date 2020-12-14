#-----------------------------------------------------------------------#
#  file: HangGlider_Data.rb                                             #
#                                                                       #
#  version: 1.0   date 14/12/2020                                       #
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
W0       = 1000
cL_max   = 1.4
tol_max  = 0.01
cL_min   = 0
W        = W0
epsi_max = 0.01

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
  #data.DumpFile = "HangGlider_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
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
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV'
    # ==============================================
    :last_factorization => 'LU',
    ###:last_factorization => 'PINV',
    # ==============================================

    # choose solves: Hyness, NewtonDumped
    # ===================================
    :solver => "Hyness",
    # ===================================

    # solver parameters
    :max_iter             => 300,
    :max_step_iter        => 40,
    :max_accumulated_iter => 800,
    :tolerance            => 9.999999999999999e-10,

    # continuation parameters
    :ns_continuation_begin => 0,
    :ns_continuation_end   => 2,
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
    :initial_x  => SET,
    :initial_y  => SET,
    :initial_vx => SET,
    :initial_vy => SET,
    :final_y    => SET,
    :final_vx   => SET,
    :final_vy   => SET,
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
    :W      => W,
    :c0     => 0.034,
    :c1     => 0.069662,
    :cL_max => cL_max,
    :cL_min => cL_min,
    :g      => 9.80665,
    :m      => 100,

    # Guess Parameters
    :Tguess => 105,

    # Boundary Conditions
    :vx_f => 13.2275675,
    :vx_i => 13.2275675,
    :vy_f => -1.28750052,
    :vy_i => -1.28750052,
    :x_i  => 0,
    :y_f  => 900,
    :y_i  => 1000,

    # Post Processing Parameters

    # User Function Parameters
    :S   => 14,
    :rc  => 100,
    :rho => 1.13,
    :uc  => 2.5,

    # Continuation Parameters
    :W0       => W0,
    :W1       => 0,
    :tol_max  => tol_max,
    :tol_min  => 0.0001,
    :epsi_max => epsi_max,
    :epsi_min => 0.0001,

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  data.Controls = {}
  data.Controls[:cLControl] = {
    :type      => 'QUADRATIC2',
    :epsilon   => epsi_max,
    :tolerance => tol_max
  }


  data.Constraints = {}
  # Constraint1D
  # Penalty subtype: PENALTY_REGULAR, PENALTY_SMOOTH, PENALTY_PIECEWISE
  # Barrier subtype: BARRIER_LOG, BARRIER_LOG_EXP, BARRIER_LOG0
  # PenaltyBarrier1DGreaterThan
  data.Constraints[:Tbound] = {
    :subType   => 'BARRIER_LOG',
    :epsilon   => 0.1,
    :tolerance => 0.5,
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
        :length => 1,
        :n      => 400,
      },
    ],
  };


end

# EOF
