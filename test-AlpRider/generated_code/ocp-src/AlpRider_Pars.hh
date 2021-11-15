/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Pars.hh                                               |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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


#ifndef ALPRIDERPARS_DOT_HH
#define ALPRIDERPARS_DOT_HH

#define numBC                    8
#define numModelPars             15
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 4
#define numLvars                 4
#define numUvars                 2
#define numOMEGAvars             8
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_y1          0
#define iX_y2          1
#define iX_y3          2
#define iX_y4          3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_u1          0
#define iU_u2          1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_W           0
#define iM_W0          1
#define iM_W1          2
#define iM_epsi0       3
#define iM_epsi1       4
#define iM_tol0        5
#define iM_tol1        6
#define iM_y1_f        7
#define iM_y1_i        8
#define iM_y2_f        9
#define iM_y2_i        10
#define iM_y3_f        11
#define iM_y3_i        12
#define iM_y4_f        13
#define iM_y4_i        14

#endif

// EOF: AlpRider_Pars.hh
