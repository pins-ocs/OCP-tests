/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Pars.hh                                           |
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


#ifndef TWOSTAGECSTRPARS_DOT_HH
#define TWOSTAGECSTRPARS_DOT_HH

#define numBc                    4
#define numModelPars             6
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 4
#define numLvars                 4
#define numUvars                 2
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_x3          2
#define iX_x4          3

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
#define iM_tau         1
#define iM_x1_i        2
#define iM_x2_i        3
#define iM_x3_i        4
#define iM_x4_i        5

#endif

// EOF: TwoStageCSTR_Pars.hh
