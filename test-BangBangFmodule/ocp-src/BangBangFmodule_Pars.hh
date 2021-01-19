/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 20/1/2021                                        |
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


#ifndef BANGBANGFMODULEPARS_DOT_HH
#define BANGBANGFMODULEPARS_DOT_HH

#define numBc                    4
#define numModelPars             2
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 2
#define numLvars                 2
#define numUvars                 2
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_v           1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_Fp          0
#define iU_Fm          1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_FmMax       0
#define iM_FpMax       1

#endif

// EOF: BangBangFmodule_Pars.hh
