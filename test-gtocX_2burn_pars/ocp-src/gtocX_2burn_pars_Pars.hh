/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Pars.hh                                       |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#ifndef GTOCX_2BURN_PARSPARS_DOT_HH
#define GTOCX_2BURN_PARSPARS_DOT_HH

#define numBc                    6
#define numModelPars             7
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 3
#define numLvars                 3
#define numUvars                 0
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 3
#define numPostProcess           20
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_f           0
#define iX_g           1
#define iX_L           2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_p           0
#define iP_h           1
#define iP_k           2

// ModelPars Maps
#define iM_muS         0
#define iM_time_f      1
#define iM_time_i      2
#define iM_w_guess     3
#define iM_epsi_norm   4
#define iM_retrograde  5
#define iM_w_nonlin    6

#endif

// EOF: gtocX_2burn_pars_Pars.hh
