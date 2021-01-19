#-----------------------------------------------------------------------#
#  file: RobotArm_Data.rb                                               #
#                                                                       #
#  version: 1.0   date 19/1/2021                                        #
#                                                                       #
#  Copyright (C) 2021                                                   #
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

# User Header

# Auxiliary values
u_epsilon0   = 0.01
u_epsilon    = u_epsilon0
u_tolerance0 = 0.01
u_tolerance  = u_tolerance0

mechatronix do |data|

  # activate run time debug
  data.Debug = false

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
  #data.DumpFile = "RobotArm_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # ==============================================================
    # 'Hyness', 'NewtonDumped', 'LM', 'YS', 'QN'
    # 'LM' = Levenberg–Marquardt, 'YS' = Yixun Shi, 'QN' = Quasi Newton
    :solver => 'NewtonDumped',
    # 'LU', 'LUPQ', 'QR', 'QRP', 'SVD', 'LSS', 'LSY', 'PINV' for Hyness and NewtonDumped
    :factorization => 'LU',
    # 'BFGS', 'DFP', 'SR1' for Quasi Newton
    :update => 'BFGS',
    # 'EXACT', 'ARMIJO'
    :linesearch => 'EXACT',
    # ==============================================================
    :MaxIter   => 50,
    :Tolerance => 1e-9,
    :Iterative => false,
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
    #:last_factorization => 'PINV',
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
    :ns_continuation_end   => 1,
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
    :initial_rho    => SET,
    :initial_theta  => SET,
    :initial_phi    => SET,
    :initial_rho1   => SET,
    :initial_theta1 => SET,
    :initial_phi1   => SET,
    :final_rho      => SET,
    :final_theta    => SET,
    :final_phi      => SET,
    :final_rho1     => SET,
    :final_theta1   => SET,
    :final_phi1     => SET,
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
    :L => 5,

    # Guess Parameters
    :Tguess => 1,

    # Boundary Conditions
    :W => 0,

    # Post Processing Parameters

    # User Function Parameters

    # Continuation Parameters
    :u_epsilon0   => u_epsilon0,
    :u_epsilon1   => 1e-05,
    :u_tolerance0 => u_tolerance0,
    :u_tolerance1 => 1e-05,

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty subtype: QUADRATIC, QUADRATIC2, PARABOLA, CUBIC
  # Barrier subtype: LOGARITHMIC, COS_LOGARITHMIC, TAN2, HYPERBOLIC
  data.Controls = {}
  data.Controls[:u_rhoControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => u_epsilon,
    :tolerance => u_tolerance
  }

  data.Controls[:u_thetaControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => u_epsilon,
    :tolerance => u_tolerance
  }

  data.Controls[:u_phiControl] = {
    :type      => 'COS_LOGARITHMIC',
    :epsilon   => u_epsilon,
    :tolerance => u_tolerance
  }


  data.Constraints = {}
  # Constraint1D: none defined
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
