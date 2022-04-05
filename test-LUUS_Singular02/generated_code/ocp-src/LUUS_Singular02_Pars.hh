/*-----------------------------------------------------------------------*\
 |  file: LUUS_Singular02_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#ifndef LUUS_SINGULAR02PARS_DOT_HH
#define LUUS_SINGULAR02PARS_DOT_HH

#define numBc                    2
#define numModelPars             7
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             2
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 1
#define numContinuationSteps     1

// Xvars
#define iX_x1           0
#define iX_x2           1

// Lvars
#define iL_lambda1__xo  0
#define iL_lambda2__xo  1

// Uvars
#define iU_u            0

// Qvars
#define iQ_zeta         0

// Pvars

// ModelPars Maps
#define iM_epsi_x1      0
#define iM_x1_i         1
#define iM_x2_i         2
#define iM_u_epsilon0   3
#define iM_u_epsilon1   4
#define iM_u_tolerance0 5
#define iM_u_tolerance1 6

#endif

// EOF: LUUS_Singular02_Pars.hh
