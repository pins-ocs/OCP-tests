/*-----------------------------------------------------------------------*\
 |  file: Underwater_Pars.hh                                             |
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


#ifndef UNDERWATERPARS_DOT_HH
#define UNDERWATERPARS_DOT_HH

#define numBc                    12
#define numModelPars             18
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           3
#define numXvars                 6
#define numLvars                 6
#define numUvars                 3
#define numOMEGAvars             12
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           3
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_x           0
#define iX_z           1
#define iX_theta       2
#define iX_vx          3
#define iX_vz          4
#define iX_Omega       5

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2
#define iL_lambda4__xo 3
#define iL_lambda5__xo 4
#define iL_lambda6__xo 5

// Uvars
#define iU_u1          0
#define iU_u2          1
#define iU_u3          2

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_Omega_f     0
#define iM_Omega_i     1
#define iM_Tguess      2
#define iM_inertia     3
#define iM_m1          4
#define iM_m3          5
#define iM_theta_f     6
#define iM_theta_i     7
#define iM_vx_f        8
#define iM_vx_i        9
#define iM_vz_f        10
#define iM_vz_i        11
#define iM_x_f         12
#define iM_x_i         13
#define iM_z_f         14
#define iM_z_i         15
#define iM_epsi_max    16
#define iM_epsi_min    17

#endif

// EOF: Underwater_Pars.hh
