/*-----------------------------------------------------------------------*\
 |  file: BikeSteering_Pars.hh                                           |
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


#ifndef BIKESTEERINGPARS_HH
#define BIKESTEERINGPARS_HH

#define numBc                    4
#define numModelPars             9
#define numConstraint1D          1
#define numConstraint2D          0
#define numConstraintU           1
#define numXvars                 3
#define numLvars                 3
#define numUvars                 1
#define numOMEGAvars             4
#define numQvars                 1
#define numPvars                 0
#define numPostProcess           2
#define numIntegratedPostProcess 0
#define numContinuationSteps     0

// Xvars
#define iX_omega       0
#define iX_phi         1
#define iX_TimeSize    2

// Lvars
#define iL_lambda1__xo 0
#define iL_lambda2__xo 1
#define iL_lambda3__xo 2

// Uvars
#define iU_Fy          0

// Qvars
#define iQ_zeta        0

// Pvars

// ModelPars Maps
#define iM_Fmax        0
#define iM_Ix          1
#define iM_g           2
#define iM_h           3
#define iM_m           4
#define iM_omega_f     5
#define iM_omega_i     6
#define iM_phi_f       7
#define iM_phi_i       8

#endif

// EOF: BikeSteering_Pars.hh
