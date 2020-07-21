/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Pars.hh                                       |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef BRACHIOSTOCRONA2PARS_HH
#define BRACHIOSTOCRONA2PARS_HH

#define numBc                    5
#define numModelPars             7
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_y           1
#define iX_v           2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_theta       0

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_Tf          0
#define iM_Vf          1
#define iM_g           2
#define iM_kappa       3
#define iM_mass        4
#define iM_xf          5
#define iM_yf          6

#endif

// EOF: Brachiostocrona2_Pars.hh
