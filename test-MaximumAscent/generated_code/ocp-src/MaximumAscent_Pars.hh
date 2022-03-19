/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Pars.hh                                          |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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


#ifndef MAXIMUMASCENTPARS_DOT_HH
#define MAXIMUMASCENTPARS_DOT_HH

#define numBc                    6
#define numModelPars             13
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 4
#define numLvars                 4
#define numUvars                 1
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           4
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_r           0
#define iX_u           1
#define iX_v           2
#define iX_theta       3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_alpha       0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_T           0
#define iM_days        1
#define iM_days0       2
#define iM_days1       3
#define iM_m0          4
#define iM_mdot        5
#define iM_r0          6
#define iM_r0_bar      7
#define iM_theta0      8
#define iM_u0_bar      9
#define iM_uf_bar      10
#define iM_v0          11
#define iM_v0_bar      12

#endif

// EOF: MaximumAscent_Pars.hh
