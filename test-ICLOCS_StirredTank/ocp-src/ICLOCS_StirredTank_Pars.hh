/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Pars.hh                                     |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#ifndef ICLOCS_STIRREDTANKPARS_DOT_HH
#define ICLOCS_STIRREDTANKPARS_DOT_HH

#define numBc                    0
#define numModelPars             16
#define numConstraint1D          3
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             0
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1          0
#define iX_x2          1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_En          0
#define iM_T_guess     1
#define iM_Tc          2
#define iM_Tf          3
#define iM_a           4
#define iM_k           5
#define iM_theta       6
#define iM_u_f         7
#define iM_w           8
#define iM_wT          9
#define iM_x1_f        10
#define iM_x1_i        11
#define iM_x2_f        12
#define iM_x2_i        13
#define iM_w_exp_max   14
#define iM_w_exp_min   15

#endif

// EOF: ICLOCS_StirredTank_Pars.hh
