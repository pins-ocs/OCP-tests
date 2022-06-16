/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Pars.hh                                 |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#ifndef ICLOCS2_BATCHFERMENTORPARS_DOT_HH
#define ICLOCS2_BATCHFERMENTORPARS_DOT_HH

#define numBc                    4
#define numModelPars             33
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 4
#define numLvars                 4
#define numUvars                 5
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_x           0
#define iX_p           1
#define iX_s           2
#define iX_v           3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_c_x         0
#define iU_c_p         1
#define iU_c_s         2
#define iU_c_v         3
#define iU_w           4

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_K_degr      0
#define iM_S_f         1
#define iM_Tf          2
#define iM_W           3
#define iM_W0          4
#define iM_W1          5
#define iM_WP          6
#define iM_WP0         7
#define iM_WP1         8
#define iM_Yes         9
#define iM_Yxs         10
#define iM_epsilon     11
#define iM_kappa_m     12
#define iM_kappa_p     13
#define iM_kappa_x     14
#define iM_mu_max      15
#define iM_mu_s        16
#define iM_p_f         17
#define iM_p_i         18
#define iM_p_max       19
#define iM_rho_max     20
#define iM_s_f         21
#define iM_s_i         22
#define iM_s_max       23
#define iM_v_f         24
#define iM_v_i         25
#define iM_v_max       26
#define iM_x_f         27
#define iM_x_i         28
#define iM_x_max       29
#define iM_epsilon0    30
#define iM_epsilon1    31
#define iM_kappa_in    32

#endif

// EOF: ICLOCS2_BatchFermentor_Pars.hh
