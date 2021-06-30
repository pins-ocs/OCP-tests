/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Pars.hh                                           |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#ifndef BANGBANGFTAUPARS_DOT_HH
#define BANGBANGFTAUPARS_DOT_HH

#define numBc                    5
#define numModelPars             6
#define numConstraint1D          4
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 4
#define numLvars                 4
#define numUvars                 2
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_v           1
#define iX_sT          2
#define iX_sB          3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_vsT         0
#define iU_vsB         1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_epsiTB      0
#define iM_maxClip     1
#define iM_maxT        2
#define iM_minClip     3
#define iM_tauB        4
#define iM_tauT        5

#endif

// EOF: BangBangFtau_Pars.hh
