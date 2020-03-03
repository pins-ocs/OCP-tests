/*-----------------------------------------------------------------------*\
 |  file: SingularLuus04_Pars.hh                                         |
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


#ifndef SINGULARLUUS04PARS_HH
#define SINGULARLUUS04PARS_HH

#define numBc                    3
#define numModelPars             6
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             3
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           0
#define numIntegratedPostProcess 1
#define numContinuationSteps     1

// Xvars
#define iX_x           0
#define iX_y           1
#define iX_z           2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_u_epsi      0
#define iM_x_i         1
#define iM_y_i         2
#define iM_z_i         3
#define iM_epsilon_X   4
#define iM_min_u_epsi  5

#endif

// EOF: SingularLuus04_Pars.hh
