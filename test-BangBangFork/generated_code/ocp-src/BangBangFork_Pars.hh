/*-----------------------------------------------------------------------*\
 |  file: BangBangFork_Pars.hh                                           |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#ifndef BANGBANGFORKPARS_DOT_HH
#define BANGBANGFORKPARS_DOT_HH

#define numBc                    6
#define numModelPars             16
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 2
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     3

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_x3          2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_u           0
#define iU_u2          1

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_T_guess     0
#define iM_WC          1
#define iM_WC0         2
#define iM_WC1         3
#define iM_WU2         4
#define iM_kappa       5
#define iM_u_epsi0     6
#define iM_u_epsi1     7
#define iM_u_tol0      8
#define iM_u_tol1      9
#define iM_x1_f        10
#define iM_x1_i        11
#define iM_x2_f        12
#define iM_x2_i        13
#define iM_x3_f        14
#define iM_x3_i        15

#endif

// EOF: BangBangFork_Pars.hh
