/*-----------------------------------------------------------------------*\
 |  file: MinimumEnergyProblem_Pars.hh                                   |
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


#ifndef MINIMUMENERGYPROBLEMPARS_DOT_HH
#define MINIMUMENERGYPROBLEMPARS_DOT_HH

#define numBc                    4
#define numModelPars             8
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1          0
#define iX_x2          1

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_maxEpsi     0
#define iM_maxTol      1
#define iM_minEpsi     2
#define iM_minTol      3
#define iM_x1_f        4
#define iM_x1_i        5
#define iM_x2_f        6
#define iM_x2_i        7

#endif

// EOF: MinimumEnergyProblem_Pars.hh
