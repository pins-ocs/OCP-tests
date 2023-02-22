/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Pars.hh                                     |
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


#ifndef ICLOCS_STIRREDTANKPARS_DOT_HH
#define ICLOCS_STIRREDTANKPARS_DOT_HH

#define numBc                    4
#define numModelPars             20
#define numConstraintLT          5
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           7
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

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
#define iP_TimeSize    0

// ModelPars Maps
#define iM_En          0
#define iM_T_guess     1
#define iM_T_min       2
#define iM_Tc          3
#define iM_Tf          4
#define iM_a           5
#define iM_k           6
#define iM_theta       7
#define iM_u_f         8
#define iM_w_time      9
#define iM_x1_f        10
#define iM_x1_i        11
#define iM_x2_f        12
#define iM_x2_i        13
#define iM_epsi_ctrl0  14
#define iM_epsi_ctrl1  15
#define iM_tol_ctrl0   16
#define iM_tol_ctrl1   17
#define iM_w_time_max  18
#define iM_w_time_min  19

#endif

// EOF: ICLOCS_StirredTank_Pars.hh
