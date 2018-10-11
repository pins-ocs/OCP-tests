/*-----------------------------------------------------------------------*\
 |  file: Catalyst_Pars.hh                                               |
 |                                                                       |
 |  version: 1.0   date 17/8/2018                                        |
 |                                                                       |
 |  Copyright (C) 2018                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#ifndef CATALYSTPARS_HH
#define CATALYSTPARS_HH

#define numBc                    2
#define numModelPars             2
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             2
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 0

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
#define iM_x1_i        0
#define iM_x2_i        1


#endif

// EOF: Catalyst_Pars.hh