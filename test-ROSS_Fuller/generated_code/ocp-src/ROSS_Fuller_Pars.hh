/*-----------------------------------------------------------------------*\
 |  file: ROSS_Fuller_Pars.hh                                            |
 |                                                                       |
 |  version: 1.0   date 12/3/2023                                        |
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


#ifndef ROSS_FULLERPARS_DOT_HH
#define ROSS_FULLERPARS_DOT_HH

#define numBc                    4
#define numModelPars             5
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x               0
#define iX_v               1

// Lvars
#define iL_lambda1__xo     0
#define iL_lambda2__xo     1

// Uvars
#define iU_u               0

// Qvars
#define iQ_zeta            0

// Pvars

// ModelPars Maps
#define iM_u_max           0
#define iM_u_epsilon_max   1
#define iM_u_epsilon_min   2
#define iM_u_tolerance_max 3
#define iM_u_tolerance_min 4

#endif

// EOF: ROSS_Fuller_Pars.hh
