/*-----------------------------------------------------------------------*\
 |  file: GerdtsKunkel_Pars.hh                                           |
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


#ifndef GERDTSKUNKELPARS_DOT_HH
#define GERDTSKUNKELPARS_DOT_HH

#define numBc                    5
#define numModelPars             9
#define numConstraintLT          1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1            0
#define iX_x2            1
#define iX_x3            2

// Lvars
#define iL_lambda1__xo   0
#define iL_lambda2__xo   1
#define iL_lambda3__xo   2

// Uvars
#define iU_u             0

// Qvars
#define iQ_zeta          0

// Pvars

// ModelPars Maps
#define iM_x1_f          0
#define iM_x1_i          1
#define iM_x2_f          2
#define iM_x2_i          3
#define iM_x3_i          4
#define iM_epsilon_max   5
#define iM_epsilon_min   6
#define iM_tolerance_max 7
#define iM_tolerance_min 8

#endif

// EOF: GerdtsKunkel_Pars.hh
