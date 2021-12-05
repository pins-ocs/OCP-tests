/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Pars.hh                                 |
 |                                                                       |
 |  version: 1.0   date 6/12/2021                                        |
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


#ifndef ICLOCS2_BATCHFERMENTORPARS_DOT_HH
#define ICLOCS2_BATCHFERMENTORPARS_DOT_HH

#define numBc                    4
#define numModelPars             31
#define numConstraint1D          4
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     3

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
#define iU_u           0

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
#define iM_WX          6
#define iM_WX0         7
#define iM_WX1         8
#define iM_Yes         9
#define iM_Yxs         10
#define iM_kappa_m     11
#define iM_kappa_p     12
#define iM_kappa_x     13
#define iM_mu_max      14
#define iM_mu_s        15
#define iM_p_f         16
#define iM_p_i         17
#define iM_rho_max     18
#define iM_s_f         19
#define iM_s_i         20
#define iM_v_f         21
#define iM_v_i         22
#define iM_x_f         23
#define iM_x_i         24
#define iM_kappa_in    25
#define iM_state_epsi0 26
#define iM_state_epsi1 27
#define iM_state_tol   28
#define iM_state_tol0  29
#define iM_state_tol1  30

#endif

// EOF: ICLOCS2_BatchFermentor_Pars.hh
