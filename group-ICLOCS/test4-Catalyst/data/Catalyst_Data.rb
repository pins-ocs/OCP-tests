#-----------------------------------------------------------------------#
#  file: Catalyst_Data.rb                                               #
#                                                                       #
#  version: 1.0   date 17/8/2018                                        #
#                                                                       #
#  Copyright (C) 2018                                                   #
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
epsi_ctrl = 1e-05
tol_ctrl  = 1e-05


mechatronix do |data|

  # LU factorization selection:
  # CYCLIC_REDUCTION_LU, CYCLIC_REDUCTION_QR, CYCLIC_REDUCTION_QRP
  data.LU_method = CYCLIC_REDUCTION_LU

  # Last Block selection:
  # LASTBLOCK_LU, LASTBLOCK_LUPQ, LASTBLOCK_QR, LASTBLOCK_QRP
  # LASTBLOCK_SVD, LASTBLOCK_LSS, LASTBLOCK_LSY
  data.Last_block = LASTBLOCK_LSS

  # Solver selection:
  # CS_use_LU, CS_use_LUPQ, CS_use_QR, CS_use_SVD,
  # CS_use_LSS, CS_use_LSY, CS_use_MINIMIZATION
  data.ControlSolutionMethod    = CS_use_LSS
  data.ControlSolutionRcond     = 1e-14  # reciprocal condition number thresold for QR, SVD, LSS, LSY
  data.ControlSolutionMaxIter   = 50
  data.ControlSolutionTolerance = 1e-9

  # Enable doctor
  data.Doctor = false

  # Enable check jacobian
  data.JacobianCheck            = true
  data.JacobianCheck_epsilon    = 1e-4
  data.FiniteDifferenceJacobian = false

  # Redirect output to GenericContainer["stream_output"]
  data.RedirectStreamToString = false

  # Dump Function and Jacobian if uncommented
  #data.DumpFile = "Catalyst_dump"

  # Level of message
  data.InfoLevel = 4

  # spline output (all values as function of "s")
  data.OutputSplines = [:s]

  # setup solver
  data.Solver = {
    :max_iter             => 300,
    :max_step_iter        => 40,
    :max_accumulated_iter => 800,
    :tolerance            => 1e-09,
    # continuation parameters
    :initial_step   => 0.2,   # initial step for continuation
    :min_step       => 0.001, # minimum accepted step for continuation
    :reduce_factor  => 0.5,   # if continuation steo fails, reduce step by this factor
    :augment_factor => 1.5,   # if step successfull in less than few_iteration augment step by this factor
    :few_iterations => 8      #
  }

  # Boundary Conditions
  data.BoundaryConditions = {
    :initial_x1 => SET,
    :initial_x2 => SET,
  }

  data.Parameters = {

    # Model Parameters

    # Guess Parameters

    # Boundary Conditions
    :x1_i => 1,
    :x2_i => 0,

    # Post Processing Parameters

    # User Function Parameters

    # Continuation Parameters

    # Constraints Parameters
  }

  # functions mapped on objects
  data.MappedObjects = {}

  # Controls
  # Penalty type controls: U_QUADRATIC, U_QUADRATIC2, U_PARABOLA, U_CUBIC
  # Barrier type controls: U_LOGARITHMIC, U_COS_LOGARITHMIC, U_HYPERBOLIC

  data.Controls = {}
  data.Controls[:uControl] = {
    :type      => U_COS_LOGARITHMIC,
    :epsilon   => epsi_ctrl,
    :tolerance => tol_ctrl
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
