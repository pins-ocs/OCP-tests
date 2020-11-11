/*-----------------------------------------------------------------------*\
 |  file: WorstCaseScenario_Pars.hh                                      |
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


#ifndef WORSTCASESCENARIOPARS_HH
#define WORSTCASESCENARIOPARS_HH

#define numBc                    1
#define numModelPars             1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 1
#define numLvars                 1
#define numUvars                 1
#define numOMEGAvars             1
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

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
#define iM_x_i         0

#endif

// EOF: WorstCaseScenario_Pars.hh
