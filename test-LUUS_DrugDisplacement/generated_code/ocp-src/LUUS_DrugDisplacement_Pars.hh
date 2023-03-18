/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Pars.hh                                  |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#ifndef LUUS_DRUGDISPLACEMENTPARS_DOT_HH
#define LUUS_DRUGDISPLACEMENTPARS_DOT_HH

#define numBc                    4
#define numModelPars             4
#define numConstraintLT          0
#define numConstraint1D          0
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 2
#define numLvars                 2
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 1
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     1

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
#define iP_T           0

// ModelPars Maps
#define iM_pen_u_epsi0 0
#define iM_pen_u_epsi1 1
#define iM_pen_u_tol0  2
#define iM_pen_u_tol1  3

#endif

// EOF: LUUS_DrugDisplacement_Pars.hh
