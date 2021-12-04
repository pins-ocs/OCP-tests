/*-----------------------------------------------------------------------*\
 |  file: HangingChain_Pars.hh                                           |
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


#ifndef HANGINGCHAINPARS_DOT_HH
#define HANGINGCHAINPARS_DOT_HH

#define numBc                    3
#define numModelPars             6
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             3
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x           0
#define iX_z           1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_L           0
#define iM_L0          1
#define iM_L1          2
#define iM_a           3
#define iM_b           4
#define iM_u0          5

#endif

// EOF: HangingChain_Pars.hh
