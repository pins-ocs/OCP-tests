/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Pars.hh                                                |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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


#ifndef ZERMELOPARS_DOT_HH
#define ZERMELOPARS_DOT_HH

#define numBc                    7
#define numModelPars             1
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 5
#define numLvars                 5
#define numUvars                 1
#define numOMEGAvars             7
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 1
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_y           1
#define iX_vx          2
#define iX_vy          3
#define iX_T           4

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_S           0

#endif

// EOF: Zermelo_Pars.hh
