/*-----------------------------------------------------------------------*\
 |  file: BangBangF_Pars.hh                                              |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#ifndef BANGBANGFPARS_DOT_HH
#define BANGBANGFPARS_DOT_HH

#define numBc                    3
#define numModelPars             4
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             3
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
#define iU_F           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_v__max      0
#define iM_v_f         1
#define iM_v_i         2
#define iM_x_i         3

#endif

// EOF: BangBangF_Pars.hh
