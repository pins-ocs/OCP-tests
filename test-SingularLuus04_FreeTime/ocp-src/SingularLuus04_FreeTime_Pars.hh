/*-----------------------------------------------------------------------*\
 |  file: SingularLuus04_FreeTime_Pars.hh                                |
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


#ifndef SINGULARLUUS04_FREETIMEPARS_HH
#define SINGULARLUUS04_FREETIMEPARS_HH

#define numBc                    6
#define numModelPars             12
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 4
#define numLvars                 4
#define numUvars                 1
#define numOMEGAvars             6
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           1
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_x           0
#define iX_y           1
#define iX_z           2
#define iX_T           3

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3

// Uvars
#define iU_u           0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_T_guess     0
#define iM_theta       1
#define iM_theta0      2
#define iM_theta1      3
#define iM_u_epsi      4
#define iM_x_f         5
#define iM_x_i         6
#define iM_y_f         7
#define iM_y_i         8
#define iM_z_f         9
#define iM_z_i         10
#define iM_min_u_epsi  11

#endif

// EOF: SingularLuus04_FreeTime_Pars.hh
