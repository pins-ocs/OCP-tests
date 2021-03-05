/*-----------------------------------------------------------------------*\
 |  file: BangBangFclip_Pars.hh                                          |
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


#ifndef BANGBANGFCLIPPARS_DOT_HH
#define BANGBANGFCLIPPARS_DOT_HH

#define numBc                    5
#define numModelPars             7
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x           0
#define iX_v           1
#define iX_F           2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_vF          0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_h0          0
#define iM_h1          1
#define iM_maxClip     2
#define iM_minClip     3
#define iM_vFmax       4
#define iM_epsilon0    5
#define iM_epsilon1    6

#endif

// EOF: BangBangFclip_Pars.hh
