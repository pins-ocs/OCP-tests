/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Pars.hh                                             |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#ifndef HANGGLIDERPARS_DOT_HH
#define HANGGLIDERPARS_DOT_HH

#define numBc                    7
#define numModelPars             25
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
#define numUvars                 1
#define numOMEGAvars             7
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_x           0
#define iX_y           1
#define iX_vx          2
#define iX_vy          3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_cL          0

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_S           0
#define iM_Tguess      1
#define iM_W           2
#define iM_W0          3
#define iM_W1          4
#define iM_c0          5
#define iM_c1          6
#define iM_cL_max      7
#define iM_cL_min      8
#define iM_g           9
#define iM_m           10
#define iM_rc          11
#define iM_rho         12
#define iM_tol_max     13
#define iM_tol_min     14
#define iM_uc          15
#define iM_vx_f        16
#define iM_vx_i        17
#define iM_vy_f        18
#define iM_vy_i        19
#define iM_x_i         20
#define iM_y_f         21
#define iM_y_i         22
#define iM_epsi_max    23
#define iM_epsi_min    24

#endif

// EOF: HangGlider_Pars.hh
