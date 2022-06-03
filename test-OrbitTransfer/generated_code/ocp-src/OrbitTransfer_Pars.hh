/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Pars.hh                                          |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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


#ifndef ORBITTRANSFERPARS_DOT_HH
#define ORBITTRANSFERPARS_DOT_HH

#define numBc                    7
#define numModelPars             7
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 5
#define numLvars                 5
#define numUvars                 1
#define numOMEGAvars             7
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           4
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_m           0
#define iX_alpha       1
#define iX_r           2
#define iX_u           3
#define iX_v           4

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4

// Uvars
#define iU_theta       0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_T           0
#define iM_m0          1
#define iM_mdot        2
#define iM_mu          3
#define iM_r0          4
#define iM_tf          5
#define iM_v0          6

#endif

// EOF: OrbitTransfer_Pars.hh
