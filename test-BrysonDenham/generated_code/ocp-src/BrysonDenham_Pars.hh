/*-----------------------------------------------------------------------*\
 |  file: BrysonDenham_Pars.hh                                           |
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


#ifndef BRYSONDENHAMPARS_DOT_HH
#define BRYSONDENHAMPARS_DOT_HH

#define numBc                    4
#define numModelPars             0
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_v           1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps

#endif

// EOF: BrysonDenham_Pars.hh
