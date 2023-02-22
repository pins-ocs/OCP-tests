/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Pars.hh                                           |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#ifndef STIRRED_TANKPARS_DOT_HH
#define STIRRED_TANKPARS_DOT_HH

#define numBc                    8
#define numModelPars             4
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           4
#define numXvars                 8
#define numLvars                 8
#define numUvars                 4
#define numOMEGAvars             8
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           4
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_x3          2
#define iX_x4          3
#define iX_x5          4
#define iX_x6          5
#define iX_x7          6
#define iX_x8          7

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4
#define iL_lambda6__xo 5
#define iL_lambda7__xo 6
#define iL_lambda8__xo 7

// Uvars
#define iU_u1          0
#define iU_u2          1
#define iU_u3          2
#define iU_u4          3

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_tol_max     0
#define iM_tol_min     1
#define iM_epsi_max    2
#define iM_epsi_min    3

#endif

// EOF: stirred_tank_Pars.hh
