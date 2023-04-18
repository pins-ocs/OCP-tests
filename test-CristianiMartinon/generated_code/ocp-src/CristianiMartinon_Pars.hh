/*-----------------------------------------------------------------------*\
 |  file: CristianiMartinon_Pars.hh                                      |
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


#ifndef CRISTIANIMARTINONPARS_DOT_HH
#define CRISTIANIMARTINONPARS_DOT_HH

#define numBc                    4
#define numModelPars             7
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           6
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x           0
#define iX_y           1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_Tguess      0
#define iM_WY          1
#define iM_x_f         2
#define iM_x_i         3
#define iM_y_f         4
#define iM_y_i         5
#define iM_ymax_guess  6

#endif

// EOF: CristianiMartinon_Pars.hh
