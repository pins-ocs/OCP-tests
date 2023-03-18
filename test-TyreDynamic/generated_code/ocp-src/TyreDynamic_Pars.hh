/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Pars.hh                                            |
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


#ifndef TYREDYNAMICPARS_DOT_HH
#define TYREDYNAMICPARS_DOT_HH

#define numBc                    6
#define numModelPars             48
#define numConstraintLT          5
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 5
#define numLvars                 5
#define numUvars                 2
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           20
#define numIntegratedPostProcess 2
#define numContinuationSteps     2

// Xvars
#define iX_v           0
#define iX_omega       1
#define iX_lambda      2
#define iX_p           3
#define iX_b           4

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4

// Uvars
#define iU_p__o        0
#define iU_b__o        1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_BT__max     0
#define iM_Bx0         1
#define iM_Cx0         2
#define iM_E__pow      3
#define iM_Iw          4
#define iM_TB__max     5
#define iM_TT__max     6
#define iM_b__lb       7
#define iM_b__ss       8
#define iM_b__ub       9
#define iM_eps_c0      10
#define iM_eps_c1      11
#define iM_g           12
#define iM_h__b        13
#define iM_kD          14
#define iM_kDo         15
#define iM_l__x        16
#define iM_m           17
#define iM_mu__x0      18
#define iM_p__lb       19
#define iM_p__ss       20
#define iM_p__ub       21
#define iM_rho_a       22
#define iM_rw          23
#define iM_tau__b      24
#define iM_tau__p      25
#define iM_tol_c0      26
#define iM_tol_c1      27
#define iM_v__adm      28
#define iM_v__lb       29
#define iM_v__ss       30
#define iM_v__ub       31
#define iM_w__U        32
#define iM_w__t        33
#define iM_w__t0       34
#define iM_w__t1       35
#define iM_BTv__max    36
#define iM_b__o__lb    37
#define iM_b__o__ub    38
#define iM_lambda__lb  39
#define iM_lambda__max 40
#define iM_lambda__ss  41
#define iM_lambda__ub  42
#define iM_omega__lb   43
#define iM_omega__ss   44
#define iM_omega__ub   45
#define iM_p__o__lb    46
#define iM_p__o__ub    47

#endif

// EOF: TyreDynamic_Pars.hh
