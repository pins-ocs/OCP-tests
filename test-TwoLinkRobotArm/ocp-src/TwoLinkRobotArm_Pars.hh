/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 5/3/2021                                         |
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


#ifndef TWOLINKROBOTARMPARS_DOT_HH
#define TWOLINKROBOTARMPARS_DOT_HH

#define numBc                    8
#define numModelPars             6
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 4
#define numLvars                 4
#define numUvars                 2
#define numOMEGAvars             8
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_x1           0
#define iX_x2           1
#define iX_x3           2
#define iX_x4           3

// Lvars
#define iL_lambda1__xo  0
#define iL_lambda2__xo  1
#define iL_lambda3__xo  2
#define iL_lambda4__xo  3

// Uvars
#define iU_u1           0
#define iU_u2           1

// Qvars
#define iQ_zeta         0

// Pvars
#define iP_T            0

// ModelPars Maps
#define iM_Tguess       0
#define iM_W            1
#define iM_u_epsilon0   2
#define iM_u_epsilon1   3
#define iM_u_tolerance0 4
#define iM_u_tolerance1 5

#endif

// EOF: TwoLinkRobotArm_Pars.hh
