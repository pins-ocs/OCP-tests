/*-----------------------------------------------------------------------*\
 |  file: Farmer_Pars.hh                                                 |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef FARMERPARS_DOT_HH
#define FARMERPARS_DOT_HH

#define numBc                    5
#define numModelPars             23
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           4
#define numXvars                 5
#define numLvars                 5
#define numUvars                 4
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           7
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_x3          2
#define iX_res         3
#define iX_x4          4

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4

// Uvars
#define iU_x1__o       0
#define iU_x2__o       1
#define iU_x3__o       2
#define iU_x4__o       3

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_P1          0
#define iM_P2          1
#define iM_res0        2
#define iM_t1          3
#define iM_t2          4
#define iM_tau__1      5
#define iM_tau__2      6
#define iM_tau__3      7
#define iM_tau__4      8
#define iM_tau__5      9
#define iM_w1          10
#define iM_w2          11
#define iM_w3          12
#define iM_w4          13
#define iM_wJ1         14
#define iM_wJ2         15
#define iM_wJ3         16
#define iM_wJ4         17
#define iM_wP          18
#define iM_x10         19
#define iM_x20         20
#define iM_x30         21
#define iM_x40         22

#endif

// EOF: Farmer_Pars.hh
