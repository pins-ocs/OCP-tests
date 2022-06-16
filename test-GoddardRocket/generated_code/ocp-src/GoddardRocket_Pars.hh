/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Pars.hh                                          |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#ifndef GODDARDROCKETPARS_DOT_HH
#define GODDARDROCKETPARS_DOT_HH

#define numBc                    4
#define numModelPars             29
#define numConstraintLT          3
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           7
#define numIntegratedPostProcess 0
#define numContinuationSteps     2

// Xvars
#define iX_h              0
#define iX_v              1
#define iX_m              2

// Lvars
#define iL_lambda1__xo    0
#define iL_lambda2__xo    1
#define iL_lambda3__xo    2

// Uvars
#define iU_u              0

// Qvars
#define iQ_zeta           0

// Pvars
#define iP_TimeSize       0

// ModelPars Maps
#define iM_D0             0
#define iM_Hscale         1
#define iM_Tmax           2
#define iM_Ve             3
#define iM_g              4
#define iM_h_i            5
#define iM_m_f            6
#define iM_m_i            7
#define iM_mu             8
#define iM_mu0            9
#define iM_mu1            10
#define iM_v_i            11
#define iM_TimeSize_guess 12
#define iM_epsi_TS_max    13
#define iM_epsi_TS_min    14
#define iM_epsi_mass_max  15
#define iM_epsi_mass_min  16
#define iM_epsi_u_max     17
#define iM_epsi_u_min     18
#define iM_epsi_v_max     19
#define iM_epsi_v_min     20
#define iM_tol_TS_max     21
#define iM_tol_TS_min     22
#define iM_tol_mass_max   23
#define iM_tol_mass_min   24
#define iM_tol_u_max      25
#define iM_tol_u_min      26
#define iM_tol_v_max      27
#define iM_tol_v_min      28

#endif

// EOF: GoddardRocket_Pars.hh
