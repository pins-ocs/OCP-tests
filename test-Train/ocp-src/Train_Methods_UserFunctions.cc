/*-----------------------------------------------------------------------*\
 |  file: Train_Methods_UserFunctions.cc                                 |
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


#include "Train.hh"
#include "Train_Pars.hh"

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
#define ALIAS_ubControl_D_3(__t1, __t2, __t3) ubControl.D_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2(__t1, __t2, __t3) ubControl.D_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1(__t1, __t2, __t3) ubControl.D_1( __t1, __t2, __t3)
#define ALIAS_ubControl_D_3_3(__t1, __t2, __t3) ubControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_3(__t1, __t2, __t3) ubControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_2(__t1, __t2, __t3) ubControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_3(__t1, __t2, __t3) ubControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_2(__t1, __t2, __t3) ubControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_1(__t1, __t2, __t3) ubControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3(__t1, __t2, __t3) uaControl.D_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2(__t1, __t2, __t3) uaControl.D_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1(__t1, __t2, __t3) uaControl.D_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3_3(__t1, __t2, __t3) uaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_3(__t1, __t2, __t3) uaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_2(__t1, __t2, __t3) uaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_3(__t1, __t2, __t3) uaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_2(__t1, __t2, __t3) uaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_1(__t1, __t2, __t3) uaControl.D_1_1( __t1, __t2, __t3)


namespace TrainDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  Train::acc( real_type xo__x, real_type xo__v ) const {
    real_type t1   = h(xo__x);
    real_type t3   = xo__v * xo__v;
    real_type result__ = -t3 * ModelPars[iM_gm] - ModelPars[iM_beta] * xo__v + t1 - ModelPars[iM_alpha];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acc( x={}, v={} ) return {}\n",
        xo__x, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  Train::acc_D_1( real_type xo__x, real_type xo__v ) const {
    real_type result__ = h_D(xo__x);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acc_D_1( x={}, v={} ) return {}\n",
        xo__x, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  Train::acc_D_1_1( real_type xo__x, real_type xo__v ) const {
    real_type result__ = h_DD(xo__x);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acc_D_1_1( x={}, v={} ) return {}\n",
        xo__x, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  Train::acc_D_1_2( real_type xo__x, real_type xo__v ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acc_D_1_2( x={}, v={} ) return {}\n",
        xo__x, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  Train::acc_D_2( real_type xo__x, real_type xo__v ) const {
    real_type result__ = -2 * xo__v * ModelPars[iM_gm] - ModelPars[iM_beta];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acc_D_2( x={}, v={} ) return {}\n",
        xo__x, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  Train::acc_D_2_2( real_type xo__x, real_type xo__v ) const {
    real_type result__ = -2 * ModelPars[iM_gm];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acc_D_2_2( x={}, v={} ) return {}\n",
        xo__x, xo__v, result__
      );
    }
    return result__;
  }

}

// EOF: Train_Methods_UserFunctions.cc
