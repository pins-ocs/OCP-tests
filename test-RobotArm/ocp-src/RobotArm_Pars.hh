/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Pars.hh                                               |
 |                                                                       |
 |  version: 1.0   date 13/9/2020                                        |
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


#ifndef ROBOTARMPARS_HH
#define ROBOTARMPARS_HH

#define numBc                    12
#define numModelPars             7
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           3
#define numXvars                 6
#define numLvars                 6
#define numUvars                 3
#define numOMEGAvars             12
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_rho          0
#define iX_theta        1
#define iX_phi          2
#define iX_rho1         3
#define iX_theta1       4
#define iX_phi1         5

// Lvars
#define iL_lambda1__xo  0
#define iL_lambda2__xo  1
#define iL_lambda3__xo  2
#define iL_lambda4__xo  3
#define iL_lambda5__xo  4
#define iL_lambda6__xo  5

// Uvars
#define iU_u_rho        0
#define iU_u_theta      1
#define iU_u_phi        2

// Qvars
#define iQ_zeta         0

// Pvars
#define iP_T            0

// ModelPars Maps
#define iM_L            0
#define iM_Tguess       1
#define iM_W            2
#define iM_u_epsilon0   3
#define iM_u_epsilon1   4
#define iM_u_tolerance0 5
#define iM_u_tolerance1 6

#endif

// EOF: RobotArm_Pars.hh
