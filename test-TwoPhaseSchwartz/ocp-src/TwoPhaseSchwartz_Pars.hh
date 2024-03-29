/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Pars.hh                                       |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#ifndef TWOPHASESCHWARTZPARS_HH
#define TWOPHASESCHWARTZPARS_HH

#define numBc                    4
#define numModelPars             8
#define numConstraint1D          2
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
#define numUvars                 2
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x1          0
#define iX_x2          1
#define iX_x3          2
#define iX_x4          3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_u1          0
#define iU_u2          1

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_T2          0
#define iM_epsi0       1
#define iM_epsi1       2
#define iM_epsilon     3
#define iM_tol0        4
#define iM_tol1        5
#define iM_epsilon0    6
#define iM_epsilon1    7

#endif

// EOF: TwoPhaseSchwartz_Pars.hh
