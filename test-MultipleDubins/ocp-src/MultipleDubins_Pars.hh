/*-----------------------------------------------------------------------*\
 |  file: MultipleDubins_Pars.hh                                         |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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


#ifndef MULTIPLEDUBINSPARS_DOT_HH
#define MULTIPLEDUBINSPARS_DOT_HH

#define numBc                    12
#define numModelPars             8
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 9
#define numLvars                 9
#define numUvars                 0
#define numOMEGAvars             12
#define numQvars                 1
#define numPvars                 6
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x1          0
#define iX_y1          1
#define iX_theta1      2
#define iX_x2          3
#define iX_y2          4
#define iX_theta2      5
#define iX_x3          6
#define iX_y3          7
#define iX_theta3      8

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4
#define iL_lambda6__xo 5
#define iL_lambda7__xo 6
#define iL_lambda8__xo 7
#define iL_lambda9__xo 8

// Uvars

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_L1          0
#define iP_L2          1
#define iP_L3          2
#define iP_kappa1      3
#define iP_kappa2      4
#define iP_kappa3      5

// ModelPars Maps
#define iM_theta_f     0
#define iM_theta_i     1
#define iM_x_f         2
#define iM_x_i         3
#define iM_y_f         4
#define iM_y_i         5
#define iM_epsilon_K   6
#define iM_epsilon_L   7

#endif

// EOF: MultipleDubins_Pars.hh
