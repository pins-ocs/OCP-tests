/*-----------------------------------------------------------------------*\
 |  file: CNOC_Pars.hh                                                   |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


#ifndef CNOCPARS_DOT_HH
#define CNOCPARS_DOT_HH

#define numBc                    12
#define numModelPars             20
#define numConstraintLT          12
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 7
#define numLvars                 7
#define numUvars                 2
#define numOMEGAvars             12
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           31
#define numIntegratedPostProcess 1
#define numContinuationSteps     0

// Xvars
#define iX_s                        0
#define iX_n                        1
#define iX_vs                       2
#define iX_vn                       3
#define iX_as                       4
#define iX_an                       5
#define iX_coV                      6

// Lvars
#define iL_lambda1__xo              0
#define iL_lambda2__xo              1
#define iL_lambda3__xo              2
#define iL_lambda4__xo              3
#define iL_lambda5__xo              4
#define iL_lambda6__xo              5
#define iL_lambda7__xo              6

// Uvars
#define iU_js                       0
#define iU_jn                       1

// Qvars
#define iQ_zeta                     0

// Pvars

// ModelPars Maps
#define iM_an_f                     0
#define iM_an_i                     1
#define iM_an_max                   2
#define iM_as_f                     3
#define iM_as_i                     4
#define iM_as_max                   5
#define iM_ax_max                   6
#define iM_ay_max                   7
#define iM_jn_max                   8
#define iM_js_max                   9
#define iM_js_min                   10
#define iM_n_f                      11
#define iM_n_i                      12
#define iM_vn_f                     13
#define iM_vn_i                     14
#define iM_vs_f                     15
#define iM_vs_i                     16
#define iM_deltaFeed                17
#define iM_pf_error                 18
#define iM_path_following_tolerance 19

#endif

// EOF: CNOC_Pars.hh
