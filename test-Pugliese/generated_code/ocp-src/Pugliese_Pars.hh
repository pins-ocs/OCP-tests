/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Pars.hh                                               |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#ifndef PUGLIESEPARS_DOT_HH
#define PUGLIESEPARS_DOT_HH

#define numBc                    5
#define numModelPars             28
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 5
#define numLvars                 5
#define numUvars                 0
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_T           0
#define iX_C           1
#define iX_R           2
#define iX_DD          3
#define iX_I__p        4

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4

// Uvars

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_C0          0
#define iM_D0          1
#define iM_Ip0         2
#define iM_K           3
#define iM_R0          4
#define iM_T0          5
#define iM_a           6
#define iM_a__IL       7
#define iM_a__R        8
#define iM_b           9
#define iM_e           10
#define iM_e__C        11
#define iM_e__D        12
#define iM_e__IL       13
#define iM_i0          14
#define iM_lambda      15
#define iM_mu__C       16
#define iM_mu__D       17
#define iM_mu__R       18
#define iM_r           19
#define iM_rho__D      20
#define iM_s           21
#define iM_s__C        22
#define iM_s__D        23
#define iM_s__IL       24
#define iM_w2          25
#define iM_kappa__AC   26
#define iM_kappa__R    27

#endif

// EOF: Pugliese_Pars.hh
