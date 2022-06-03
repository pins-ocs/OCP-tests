/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Pars.hh                                        |
 |                                                                       |
 |  version: 1.0   date 14/6/2022                                        |
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


#ifndef BRACHIOSTOCRONAPARS_DOT_HH
#define BRACHIOSTOCRONAPARS_DOT_HH

#define numBc                    5
#define numModelPars             14
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
#define numUvars                 2
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

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
#define iU_sz          1

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_Tf          0
#define iM_Vf          1
#define iM_g           2
#define iM_mass        3
#define iM_mu          4
#define iM_mu0         5
#define iM_mu1         6
#define iM_w_ARG       7
#define iM_w_ARG0      8
#define iM_w_ARG1      9
#define iM_xf          10
#define iM_y0_low      11
#define iM_yf          12
#define iM_slope_low   13

#endif

// EOF: Brachiostocrona_Pars.hh
