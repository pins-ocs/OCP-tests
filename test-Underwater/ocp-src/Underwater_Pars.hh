/*-----------------------------------------------------------------------*\
 |  file: Underwater_Pars.hh                                             |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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


#ifndef UNDERWATERPARS_DOT_HH
#define UNDERWATERPARS_DOT_HH

#define numBc                    10
#define numModelPars             16
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           3
#define numXvars                 6
#define numLvars                 6
#define numUvars                 3
#define numOMEGAvars             10
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
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
#define iM_Tguess      0
#define iM_inertia     1
#define iM_m1          2
#define iM_m3          3
#define iM_theta_f     4
#define iM_theta_i     5
#define iM_vx_f        6
#define iM_vx_i        7
#define iM_vz_f        8
#define iM_vz_i        9
#define iM_x_f         10
#define iM_x_i         11
#define iM_z_f         12
#define iM_z_i         13
#define iM_epsi_max    14
#define iM_epsi_min    15

#endif

// EOF: Underwater_Pars.hh
