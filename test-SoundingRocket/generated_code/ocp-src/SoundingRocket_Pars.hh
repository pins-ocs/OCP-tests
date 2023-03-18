/*-----------------------------------------------------------------------*\
 |  file: SoundingRocket_Pars.hh                                         |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#ifndef SOUNDINGROCKETPARS_DOT_HH
#define SOUNDINGROCKETPARS_DOT_HH

#define numBc                    4
#define numModelPars             12
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

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

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_Tf          0

// ModelPars Maps
#define iM_B           0
#define iM_W           1
#define iM_W0          2
#define iM_W1          3
#define iM_epsi0       4
#define iM_epsi1       5
#define iM_g           6
#define iM_kappa       7
#define iM_tol0        8
#define iM_tol1        9
#define iM_x3_f        10
#define iM_Tf_guess    11

#endif

// EOF: SoundingRocket_Pars.hh
