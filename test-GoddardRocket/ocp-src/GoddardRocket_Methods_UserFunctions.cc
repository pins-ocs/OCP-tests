/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods1.cc                                      |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  GoddardRocket::DD( real_type h__XO, real_type v__XO ) const {
    real_type t2   = v__XO * v__XO;
    real_type t10  = exp(ModelPars[7] * (1 - h__XO / ModelPars[6]));
    return t10 * t2 * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_1( real_type h__XO, real_type v__XO ) const {
    real_type t2   = v__XO * v__XO;
    real_type t4   = ModelPars[7];
    real_type t5   = ModelPars[6];
    real_type t8   = 1.0 / t5;
    real_type t10  = exp(t8 * (t5 - h__XO) * t4);
    return -t8 * t10 * t4 * t2 * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_1_1( real_type h__XO, real_type v__XO ) const {
    real_type t2   = v__XO * v__XO;
    real_type t4   = ModelPars[7];
    real_type t5   = t4 * t4;
    real_type t6   = ModelPars[6];
    real_type t7   = t6 * t6;
    real_type t14  = exp(1.0 / t6 * (t6 - h__XO) * t4);
    return t14 / t7 * t5 * t2 * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_1_2( real_type h__XO, real_type v__XO ) const {
    real_type t3   = ModelPars[7];
    real_type t4   = ModelPars[6];
    real_type t7   = 1.0 / t4;
    real_type t9   = exp(t7 * (t4 - h__XO) * t3);
    return -2 * t7 * t9 * t3 * ModelPars[0] * v__XO;
  }

  real_type
  GoddardRocket::DD_D_2( real_type h__XO, real_type v__XO ) const {
    real_type t4   = ModelPars[6];
    real_type t9   = exp(1.0 / t4 * (t4 - h__XO) * ModelPars[7]);
    return 2 * t9 * v__XO * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_2_2( real_type h__XO, real_type v__XO ) const {
    real_type t3   = ModelPars[6];
    real_type t8   = exp(1.0 / t3 * (t3 - h__XO) * ModelPars[7]);
    return 2 * t8 * ModelPars[0];
  }

  real_type
  GoddardRocket::gg( real_type h__XO ) const {
    real_type t3   = ModelPars[6] * ModelPars[6];
    real_type t5   = h__XO * h__XO;
    return 1.0 / t5 * t3 * ModelPars[5];
  }

  real_type
  GoddardRocket::gg_D( real_type h__XO ) const {
    real_type t3   = ModelPars[6] * ModelPars[6];
    real_type t5   = h__XO * h__XO;
    return -2 / t5 / h__XO * t3 * ModelPars[5];
  }

  real_type
  GoddardRocket::gg_DD( real_type h__XO ) const {
    real_type t3   = ModelPars[6] * ModelPars[6];
    real_type t5   = h__XO * h__XO;
    real_type t6   = t5 * t5;
    return 6 / t6 * t3 * ModelPars[5];
  }

  real_type
  GoddardRocket::explog( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = log(a__XO);
    real_type t4   = log(b__XO);
    return exp(t2 * (1 - s__XO) + t4 * s__XO);
  }

  real_type
  GoddardRocket::explog_D_1( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t5   = pow(a__XO, 1 - s__XO);
    real_type t7   = pow(b__XO, s__XO);
    return -t7 * t5 * (t1 - t2);
  }

  real_type
  GoddardRocket::explog_D_1_1( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t4   = pow(t1 - t2, 2);
    real_type t6   = pow(a__XO, 1 - s__XO);
    real_type t8   = pow(b__XO, s__XO);
    return t8 * t6 * t4;
  }

  real_type
  GoddardRocket::explog_D_1_2( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = pow(b__XO, s__XO);
    real_type t2   = -1 + s__XO;
    real_type t3   = log(a__XO);
    real_type t6   = log(b__XO);
    real_type t10  = pow(a__XO, -s__XO);
    return t10 * (t3 * t2 - t6 * t2 - 1) * t1;
  }

  real_type
  GoddardRocket::explog_D_1_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(b__XO, t1);
    real_type t4   = pow(a__XO, -t1);
    real_type t6   = log(a__XO);
    real_type t8   = log(b__XO);
    return -(s__XO * t6 - t8 * s__XO - 1) * t4 * t2;
  }

  real_type
  GoddardRocket::explog_D_2( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, s__XO);
    return -t4 * t2 * (-1 + s__XO);
  }

  real_type
  GoddardRocket::explog_D_2_2( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t3   = pow(a__XO, -s__XO - 1);
    real_type t5   = pow(b__XO, s__XO);
    return t5 * s__XO * t3 * (-1 + s__XO);
  }

  real_type
  GoddardRocket::explog_D_2_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, t1);
    return -s__XO * t4 * t2 * t1;
  }

  real_type
  GoddardRocket::explog_D_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(b__XO, t1);
    real_type t5   = pow(a__XO, -t1);
    return t5 * t2 * s__XO;
  }

  real_type
  GoddardRocket::explog_D_3_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(b__XO, -2 + s__XO);
    real_type t4   = -1 + s__XO;
    real_type t6   = pow(a__XO, -t4);
    return t6 * t4 * t2 * s__XO;
  }

}

// EOF: GoddardRocket_Methods1.cc
