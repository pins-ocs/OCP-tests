/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking_Pars.hh                                 |
 |                                                                       |
 |  version: 1.0   date 5/12/2021                                        |
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


#ifndef ICLOCS_PARALLELPARKINGPARS_DOT_HH
#define ICLOCS_PARALLELPARKINGPARS_DOT_HH

#define numBc                    8
#define numModelPars             14
#define numConstraint1D          9
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 6
#define numLvars                 6
#define numUvars                 2
#define numOMEGAvars             8
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           0
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_x           0
#define iX_y           1
#define iX_v           2
#define iX_a           3
#define iX_theta       4
#define iX_phi         5

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

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_T           0

// ModelPars Maps
#define iM_T_guess     0
#define iM_a_f         1
#define iM_a_i         2
#define iM_b           3
#define iM_len_SL      4
#define iM_len_a       5
#define iM_len_f       6
#define iM_len_r       7
#define iM_phi_i       8
#define iM_theta_i     9
#define iM_v_f         10
#define iM_v_i         11
#define iM_x_i         12
#define iM_y_i         13

#endif

// EOF: ICLOCS_ParallelParking_Pars.hh
