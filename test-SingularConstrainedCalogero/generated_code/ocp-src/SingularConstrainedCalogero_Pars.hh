/*-----------------------------------------------------------------------*\
 |  file: SingularConstrainedCalogero_Pars.hh                            |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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


#ifndef SINGULARCONSTRAINEDCALOGEROPARS_DOT_HH
#define SINGULARCONSTRAINEDCALOGEROPARS_DOT_HH

#define numBC                    2
#define numModelPars             6
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 1
#define numLvars                 1
#define numUvars                 1
#define numOMEGAvars             2
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 1
#define numContinuationSteps     1

// Xvars
#define iX_x           0

// Lvars
#define iL_lambda1__xo 0

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_tol_max     0
#define iM_tol_min     1
#define iM_x_f         2
#define iM_x_i         3
#define iM_epsi_max    4
#define iM_epsi_min    5

#endif

// EOF: SingularConstrainedCalogero_Pars.hh
