/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Pars.hh                                    |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#ifndef ECONOMICGROWTHMODELPARS_DOT_HH
#define ECONOMICGROWTHMODELPARS_DOT_HH

#define numBc                    3
#define numModelPars             10
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             3
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           7
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_T           2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_Qc          0
#define iM_l1_i        1
#define iM_l2_i        2
#define iM_t0          3
#define iM_u_epsi0     4
#define iM_u_epsi1     5
#define iM_u_tol0      6
#define iM_u_tol1      7
#define iM_x1_i        8
#define iM_x2_i        9

#endif

// EOF: EconomicGrowthModel_Pars.hh
