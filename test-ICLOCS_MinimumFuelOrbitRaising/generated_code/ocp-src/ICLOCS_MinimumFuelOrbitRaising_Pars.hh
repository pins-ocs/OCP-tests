/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Pars.hh                         |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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


#ifndef ICLOCS_MINIMUMFUELORBITRAISINGPARS_DOT_HH
#define ICLOCS_MINIMUMFUELORBITRAISINGPARS_DOT_HH

#define numBc                    5
#define numModelPars             3
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           0
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             5
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_r           0
#define iX_vr          1
#define iX_vt          2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_theta       0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_T           0
#define iM_md          1
#define iM_theta_max   2

#endif

// EOF: ICLOCS_MinimumFuelOrbitRaising_Pars.hh
