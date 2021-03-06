/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#ifndef BRACHIOSTOCRONAPARS_HH
#define BRACHIOSTOCRONAPARS_HH

#define numBc                    5
#define numModelPars             6
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
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
#define iX_theta       3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_vtheta      0

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_Tf          0
#define iM_Vf          1
#define iM_g           2
#define iM_mass        3
#define iM_xf          4
#define iM_yf          5

#endif

// EOF: Brachiostocrona_Pars.hh
