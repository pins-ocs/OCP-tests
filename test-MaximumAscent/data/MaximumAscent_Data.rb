#-----------------------------------------------------------------------#
#  file: MaximumAscent_Data.rb                                          #
#                                                                       #
#  version: 1.0   date 3/6/2021                                         #
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
T      = 0.68
days   = 1
mu     = 398600441800000
days1  = 30
g0     = 9.80665
Isp    = 1500
mdot   = T/g0/Isp
tf     = 86400*days
r0     = 6678140
v0     = (mu/r0)**(1/2.0)
u0     = 0
u0_bar = u0/v0

mechatronix do |data|

  # activate run time debug
  data.Debug = true

  # Enable doctor
  data.Doctor = false

  # Level of message
  data.InfoLevel = 4

  # maximum number of threads used for linear algebra and various solvers
  data.N_threads   = [1,$MAX_THREAD_NUM-1].max
  data.U_threaded  = true
  data.F_threaded  = true
  data.JF_threaded = true
  data.LU_threaded = true

  # Enable check jacobian
  data.JacobianCheck            = false
  data.JacobianCheckFull        = false
  data.JacobianCheck_epsilon    = 1e-4
  data.FiniteDifferenceJacobian = false

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "MaximumAscent_dump"

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver for controls
  data.ControlSolver = {
    # 'LM' = Levenberg-Marquard'
    # 'YS' = Yixun Shi
    # 'QN' = Quasi Newton
    # ==============================================================
    # 'Hyness', 'NewtonDumped', 'LM', 'YS', 'QN'
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
    # ==============================================================
    # 'LM', 'YS', 'QN'
    :InitSolver    => 'QN',
    :InitMaxIter   => 10,
    :InitTolerance => 1e-4
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
    :last_factorization => 'LUPQ', # automatically use PINV if singular
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
    :initial_r      => SET,
    :initial_u      => SET,
    :initial_v      => SET,
    :initial_theta  => SET,
    :final_u        => SET,
    :final_velocity => SET,
  }

  # Guess
  data.Guess = {
    # possible value: zero, default, none, warm
    :initialize => 'zero',
    # possible value: default, none, warm, spline, table
    :guess_type => 'default',
    # initilize or not lagrange multiplier with redundant linear system
    :initialize_multipliers => false,
    # 'use_guess', 'minimize', 'none'
    :initialize_controls    => 'use_guess'
  }

  data.Parameters = {

    # Model Parameters
    :days => days,
    :m0   => 5000,
    :mdot => mdot,

    # Guess Parameters

    # Boundary Conditions
    :r0_bar => 1,
    :theta0 => 0,
    :u0_bar => u0_bar,
    :uf_bar => 0,
    :v0_bar => 1,

    # Post Processing Parameters
    :r0 => r0,
    :v0 => v0,

    # User Function Parameters
    :T => T,

    # Continuation Parameters
    :days0 => 1,
    :days1 => days1,

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls: No penalties or barriers constraint defined
  data.Controls = {}

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
        :n      => 1000*days1,
        :length => 1,
      },
    ],
  };


end

# EOF
