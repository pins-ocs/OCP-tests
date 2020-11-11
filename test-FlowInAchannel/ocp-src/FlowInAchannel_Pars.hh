/*-----------------------------------------------------------------------*\
 |  file: FlowInAchannel_Pars.hh                                         |
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


#ifndef FLOWINACHANNELPARS_HH
#define FLOWINACHANNELPARS_HH

#define numBc                    4
#define numModelPars             1
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 4
#define numLvars                 4
#define numUvars                 0
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_u           0
#define iX_u1          1
#define iX_u2          2
#define iX_u3          3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_R           0

#endif

// EOF: FlowInAchannel_Pars.hh
