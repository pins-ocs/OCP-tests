/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Pars.hh                                            |
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


#ifndef GTOCX_2BURNPARS_DOT_HH
#define GTOCX_2BURNPARS_DOT_HH

#define numBc                    6
#define numModelPars             7
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 6
#define numLvars                 6
#define numUvars                 0
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           21
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_p           0
#define iX_f           1
#define iX_g           2
#define iX_h           3
#define iX_k           4
#define iX_L           5

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4
#define iL_lambda6__xo 5

// Uvars

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_muS         0
#define iM_time_f      1
#define iM_time_i      2
#define iM_w_guess     3
#define iM_epsi_norm   4
#define iM_retrograde  5
#define iM_w_nonlin    6

#endif

// EOF: gtocX_2burn_Pars.hh
