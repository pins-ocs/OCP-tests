/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Pars.hh                                    |
 |                                                                       |
 |  version: 1.0   date 21/1/2021                                        |
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


#ifndef POINTMASSCARMODEL_3PARS_DOT_HH
#define POINTMASSCARMODEL_3PARS_DOT_HH

#define numBc                    8
#define numModelPars             16
#define numConstraint1D          6
#define numConstraint2D          0
#define numConstraintU           2
#define numXvars                 7
#define numLvars                 7
#define numUvars                 2
#define numOMEGAvars             8
#define numQvars                 4
#define numPvars                 0
#define numPostProcess           25
#define numIntegratedPostProcess 1
#define numContinuationSteps     2

// Xvars
#define iX_s             0
#define iX_n             1
#define iX_alpha         2
#define iX_V             3
#define iX_Omega         4
#define iX_fx            5
#define iX_T             6

// Lvars
#define iL_lambda1__xo   0
#define iL_lambda2__xo   1
#define iL_lambda3__xo   2
#define iL_lambda4__xo   3
#define iL_lambda5__xo   4
#define iL_lambda6__xo   5
#define iL_lambda7__xo   6

// Uvars
#define iU_v__fx         0
#define iU_v__Omega      1

// Qvars
#define iQ_zeta          0
#define iQ_L             1
#define iQ_ssSegmentMin  2
#define iQ_ssSegmentMax  3

// Pvars

// ModelPars Maps
#define iM_Pmax          0
#define iM_V0            1
#define iM_g             2
#define iM_kD            3
#define iM_m             4
#define iM_p_epsi0       5
#define iM_p_epsi1       6
#define iM_wT            7
#define iM_wT0           8
#define iM_wT1           9
#define iM_mu__x__max    10
#define iM_mu__y__max    11
#define iM_up_epsi0      12
#define iM_up_epsi1      13
#define iM_v__Omega__max 14
#define iM_v__fx__max    15

#endif

// EOF: PointMassCarModel_3_Pars.hh
