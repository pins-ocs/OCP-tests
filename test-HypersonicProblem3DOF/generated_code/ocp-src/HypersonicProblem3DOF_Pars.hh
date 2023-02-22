/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Pars.hh                                  |
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


#ifndef HYPERSONICPROBLEM3DOFPARS_DOT_HH
#define HYPERSONICPROBLEM3DOFPARS_DOT_HH

#define numBc                    10
#define numModelPars             36
#define numConstraintLT          2
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 7
#define numLvars                 7
#define numUvars                 9
#define numOMEGAvars             10
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           14
#define numIntegratedPostProcess 0
#define numContinuationSteps     3

// Xvars
#define iX_h             0
#define iX_theta         1
#define iX_phi           2
#define iX_V             3
#define iX_G             4
#define iX_psi           5
#define iX_sigma         6

// Lvars
#define iL_lambda1__xo   0
#define iL_lambda2__xo   1
#define iL_lambda3__xo   2
#define iL_lambda4__xo   3
#define iL_lambda5__xo   4
#define iL_lambda6__xo   5
#define iL_lambda7__xo   6

// Uvars
#define iU_alpha         0
#define iU_u2            1
#define iU_c_h           2
#define iU_c_theta       3
#define iU_c_phi         4
#define iU_c_V           5
#define iU_c_G           6
#define iU_c_psi         7
#define iU_c_sigma       8

// Qvars
#define iQ_zeta          0

// Pvars
#define iP_Tf            0

// ModelPars Maps
#define iM_Aref          0
#define iM_CD0           1
#define iM_CD1           2
#define iM_CD2           3
#define iM_CL0           4
#define iM_CL1           5
#define iM_CTRL          6
#define iM_CTRL0         7
#define iM_CTRL1         8
#define iM_G_f           9
#define iM_G_i           10
#define iM_ODE           11
#define iM_ODE0          12
#define iM_ODE1          13
#define iM_S             14
#define iM_V_f           15
#define iM_V_i           16
#define iM_WTF           17
#define iM_WTF0          18
#define iM_WTF1          19
#define iM_h_f           20
#define iM_h_i           21
#define iM_m             22
#define iM_mu            23
#define iM_phi_f         24
#define iM_phi_i         25
#define iM_psi_f         26
#define iM_psi_i         27
#define iM_re            28
#define iM_rho0          29
#define iM_sigma_i       30
#define iM_theta_f       31
#define iM_theta_i       32
#define iM_to_deg        33
#define iM_Tf_guess      34
#define iM_sigma_dot_max 35

#endif

// EOF: HypersonicProblem3DOF_Pars.hh
