/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods1.cc                                       |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wunused-macros"
#elif defined(__llvm__) || defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wunused-macros"
#elif defined(_MSC_VER)
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#endif

// map user defined functions and objects with macros
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoStageCSTRDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  TwoStageCSTR::R1( real_type x1__XO, real_type x2__XO ) const {
    real_type t6   = exp(25 * x2__XO / (x2__XO + 2));
    return t6 * (x1__XO + 0.5e0);
  }

  real_type
  TwoStageCSTR::R1_D_1( real_type x1__XO, real_type x2__XO ) const {
    return exp(25 * x2__XO / (x2__XO + 2));
  }

  real_type
  TwoStageCSTR::R1_D_1_1( real_type x1__XO, real_type x2__XO ) const {
    return 0;
  }

  real_type
  TwoStageCSTR::R1_D_1_2( real_type x1__XO, real_type x2__XO ) const {
    real_type t1   = x2__XO + 2;
    real_type t2   = t1 * t1;
    real_type t7   = exp(25 / t1 * x2__XO);
    return 50 * t7 / t2;
  }

  real_type
  TwoStageCSTR::R1_D_2( real_type x1__XO, real_type x2__XO ) const {
    real_type t2   = x2__XO + 2;
    real_type t3   = t2 * t2;
    real_type t9   = exp(25 / t2 * x2__XO);
    return 50 * t9 / t3 * (x1__XO + 0.5e0);
  }

  real_type
  TwoStageCSTR::R1_D_2_2( real_type x1__XO, real_type x2__XO ) const {
    real_type t2   = x2__XO + 2;
    real_type t6   = exp(25 / t2 * x2__XO);
    real_type t9   = t2 * t2;
    real_type t10  = t9 * t9;
    return -100 / t10 * (x2__XO - 23) * t6 * (x1__XO + 0.5e0);
  }

  real_type
  TwoStageCSTR::R2( real_type x3__XO, real_type x4__XO ) const {
    real_type t6   = exp(25 * x4__XO / (x4__XO + 2));
    return t6 * (x3__XO + 0.25e0);
  }

  real_type
  TwoStageCSTR::R2_D_1( real_type x3__XO, real_type x4__XO ) const {
    return exp(25 * x4__XO / (x4__XO + 2));
  }

  real_type
  TwoStageCSTR::R2_D_1_1( real_type x3__XO, real_type x4__XO ) const {
    return 0;
  }

  real_type
  TwoStageCSTR::R2_D_1_2( real_type x3__XO, real_type x4__XO ) const {
    real_type t1   = x4__XO + 2;
    real_type t2   = t1 * t1;
    real_type t7   = exp(25 / t1 * x4__XO);
    return 50 * t7 / t2;
  }

  real_type
  TwoStageCSTR::R2_D_2( real_type x3__XO, real_type x4__XO ) const {
    real_type t2   = x4__XO + 2;
    real_type t3   = t2 * t2;
    real_type t9   = exp(25 / t2 * x4__XO);
    return 50 * t9 / t3 * (x3__XO + 0.25e0);
  }

  real_type
  TwoStageCSTR::R2_D_2_2( real_type x3__XO, real_type x4__XO ) const {
    real_type t2   = x4__XO + 2;
    real_type t6   = exp(25 / t2 * x4__XO);
    real_type t9   = t2 * t2;
    real_type t10  = t9 * t9;
    return -100 / t10 * (x4__XO - 23) * t6 * (x3__XO + 0.25e0);
  }

}

// EOF: TwoStageCSTR_Methods1.cc
