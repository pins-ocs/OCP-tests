/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Pars.hh                                              |
 |                                                                       |
 |  version: 1.0   date 4/12/2021                                        |
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


#ifndef CROSSROADPARS_DOT_HH
#define CROSSROADPARS_DOT_HH

#define numBc                    6
#define numModelPars             17
#define numConstraint1D          3
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
#define numUvars                 1
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_s           0
#define iX_v           1
#define iX_a           2
#define iX_Ts          3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_jerk        0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_L           0
#define iM_Vmean       1
#define iM_a_f         2
#define iM_a_i         3
#define iM_kappa0      4
#define iM_kappa1      5
#define iM_kappa2      6
#define iM_s_f         7
#define iM_s_i         8
#define iM_v_f         9
#define iM_v_i         10
#define iM_wJ          11
#define iM_wT          12
#define iM_alat_max    13
#define iM_along_max   14
#define iM_jerk_max    15
#define iM_jerk_min    16

#endif

// EOF: Crossroad_Pars.hh
