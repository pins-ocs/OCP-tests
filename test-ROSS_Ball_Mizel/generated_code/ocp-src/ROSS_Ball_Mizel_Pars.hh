/*-----------------------------------------------------------------------*\
 |  file: ROSS_Ball_Mizel_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef ROSS_BALL_MIZELPARS_DOT_HH
#define ROSS_BALL_MIZELPARS_DOT_HH

#define numBc                    2
#define numModelPars             2
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 1
#define numLvars                 1
#define numUvars                 1
#define numOMEGAvars             2
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x           0

// Lvars
#define iL_lambda1__xo 0

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_epsilon     0
#define iM_kappa       1

#endif

// EOF: ROSS_Ball_Mizel_Pars.hh
