/*-----------------------------------------------------------------------*\
 |  file: BangBangFredundant_Pars.hh                                     |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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


#ifndef BANGBANGFREDUNDANTPARS_DOT_HH
#define BANGBANGFREDUNDANTPARS_DOT_HH

#define numBc                    3
#define numModelPars             2
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 6
#define numLvars                 6
#define numUvars                 2
#define numOMEGAvars             3
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           4
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_v           1
#define iX_F1          2
#define iX_F2          3
#define iX_vF1         4
#define iX_vF2         5

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4
#define iL_lambda6__xo 5

// Uvars
#define iU_aF1         0
#define iU_aF2         1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_maxAF       0
#define iM_w_F         1

#endif

// EOF: BangBangFredundant_Pars.hh
