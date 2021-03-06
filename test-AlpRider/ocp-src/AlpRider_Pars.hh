/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Pars.hh                                               |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#ifndef ALPRIDERPARS_HH
#define ALPRIDERPARS_HH

#define numBc                    8
#define numModelPars             14
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
#define numContinuationSteps     2

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
#define iM_W1          1
#define iM_epsi0       2
#define iM_epsi1       3
#define iM_tol0        4
#define iM_tol1        5
#define iM_y1_f        6
#define iM_y1_i        7
#define iM_y2_f        8
#define iM_y2_i        9
#define iM_y3_f        10
#define iM_y3_i        11
#define iM_y4_f        12
#define iM_y4_i        13

#endif

// EOF: AlpRider_Pars.hh
