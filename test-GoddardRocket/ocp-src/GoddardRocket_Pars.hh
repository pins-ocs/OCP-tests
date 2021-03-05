/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Pars.hh                                          |
 |                                                                       |
 |  version: 1.0   date 5/3/2021                                         |
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


#ifndef GODDARDROCKETPARS_DOT_HH
#define GODDARDROCKETPARS_DOT_HH

#define numBc                    4
#define numModelPars             17
#define numConstraint1D          3
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

// Xvars
#define iX_h           0
#define iX_v           1
#define iX_m           2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_T           0

// Qvars
#define iQ_zeta        0

// Pvars
#define iP_TimeSize    0

// ModelPars Maps
#define iM_Dc          0
#define iM_Tmax        1
#define iM_c           2
#define iM_epsi_T      3
#define iM_epsi_TS     4
#define iM_g0          5
#define iM_h_i         6
#define iM_hc          7
#define iM_m_f         8
#define iM_m_i         9
#define iM_tol_T       10
#define iM_tol_TS      11
#define iM_v_i         12
#define iM_epsi_TSmin  13
#define iM_epsi_Tmin   14
#define iM_tol_TSmin   15
#define iM_tol_Tmin    16

#endif

// EOF: GoddardRocket_Pars.hh
