/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Pars.hh                                   |
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


#ifndef ECONOMICGROWTHMODEL2PARS_DOT_HH
#define ECONOMICGROWTHMODEL2PARS_DOT_HH

#define numBc                    7
#define numModelPars             8
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 5
#define numLvars                 5
#define numUvars                 1
#define numOMEGAvars             7
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_y1          2
#define iX_y2          3
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
#define iM_T_guess     0
#define iM_Yc          1
#define iM_x1_i        2
#define iM_x2_i        3
#define iM_y1_i        4
#define iM_y2_i        5
#define iM_epsi_max    6
#define iM_epsi_min    7

#endif

// EOF: EconomicGrowthModel2_Pars.hh
