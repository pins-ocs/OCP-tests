/*-----------------------------------------------------------------------*\
 |  file: HyperSensitive_Pars.hh                                         |
 |                                                                       |
 |  version: 1.0   date 12/11/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef HYPERSENSITIVEPARS_HH
#define HYPERSENSITIVEPARS_HH

#define numBc                    2
#define numModelPars             2
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 1
#define numLvars                 1
#define numUvars                 1
#define numOMEGAvars             2
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_y           0

// Lvars
#define iL_lambda1__xo 0

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_y_f         0
#define iM_y_i         1

#endif

// EOF: HyperSensitive_Pars.hh
