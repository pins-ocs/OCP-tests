/*-----------------------------------------------------------------------*\
 |  file: LUUS_Singular04_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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


#ifndef LUUS_SINGULAR04PARS_DOT_HH
#define LUUS_SINGULAR04PARS_DOT_HH

#define numBc                    3
#define numModelPars             10
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             3
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 1
#define numContinuationSteps     1

// Xvars
#define iX_x1           0
#define iX_x2           1
#define iX_x3           2

// Lvars
#define iL_lambda1__xo  0
#define iL_lambda2__xo  1
#define iL_lambda3__xo  2

// Uvars
#define iU_u            0

// Qvars
#define iQ_zeta         0

// Pvars

// ModelPars Maps
#define iM_epsi_x       0
#define iM_epsi_x0      1
#define iM_epsi_x1      2
#define iM_x1_i         3
#define iM_x2_i         4
#define iM_x3_i         5
#define iM_u_epsilon0   6
#define iM_u_epsilon1   7
#define iM_u_tolerance0 8
#define iM_u_tolerance1 9

#endif

// EOF: LUUS_Singular04_Pars.hh
