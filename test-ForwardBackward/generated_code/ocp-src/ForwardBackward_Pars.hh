/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Pars.hh                                        |
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


#ifndef FORWARDBACKWARDPARS_DOT_HH
#define FORWARDBACKWARDPARS_DOT_HH

#define numBc                    2
#define numModelPars             22
#define numConstraintLT          5
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 1
#define numLvars                 1
#define numUvars                 1
#define numOMEGAvars             2
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           13
#define numIntegratedPostProcess 1
#define numContinuationSteps     3

// Xvars
#define iX_v           0

// Lvars
#define iL_lambda1__xo 0

// Uvars
#define iU_a           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_E_epsi0     0
#define iM_E_epsi1     1
#define iM_E_max       2
#define iM_E_tol0      3
#define iM_E_tol1      4
#define iM_WA          5
#define iM_a_max       6
#define iM_a_min       7
#define iM_c0          8
#define iM_c0_0        9
#define iM_c0_1        10
#define iM_c1          11
#define iM_c1_0        12
#define iM_c1_1        13
#define iM_epsilon     14
#define iM_v0          15
#define iM_v1          16
#define iM_v_max       17
#define iM_v_min       18
#define iM_wT          19
#define iM_epsilon0    20
#define iM_epsilon1    21

#endif

// EOF: ForwardBackward_Pars.hh
