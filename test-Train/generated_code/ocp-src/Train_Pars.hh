/*-----------------------------------------------------------------------*\
 |  file: Train_Pars.hh                                                  |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef TRAINPARS_DOT_HH
#define TRAINPARS_DOT_HH

#define numBc                    4
#define numModelPars             13
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 2
#define numLvars                 2
#define numUvars                 2
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x           0
#define iX_v           1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_ua          0
#define iU_ub          1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_alpha       0
#define iM_beta        1
#define iM_gm          2
#define iM_tol_max     3
#define iM_tol_min     4
#define iM_uaMax       5
#define iM_ubMax       6
#define iM_v_f         7
#define iM_v_i         8
#define iM_x_f         9
#define iM_x_i         10
#define iM_epsi_max    11
#define iM_epsi_min    12

#endif

// EOF: Train_Pars.hh
