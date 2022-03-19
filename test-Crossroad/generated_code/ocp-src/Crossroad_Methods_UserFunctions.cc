/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_UserFunctions.cc                             |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"
#include <cmath>

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
#define ALIAS_VelBound_max_DD(__t1) VelBound_max.DD( __t1)
#define ALIAS_VelBound_max_D(__t1) VelBound_max.D( __t1)
#define ALIAS_VelBound_min_DD(__t1) VelBound_min.DD( __t1)
#define ALIAS_VelBound_min_D(__t1) VelBound_min.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {
  using std::acos;
  using std::acosh;
  using std::asin;
  using std::asinh;
  using std::atan;
  using std::atan2;
  using std::atanh;
  using std::cbrt;
  using std::ceil;
  using std::abs;
  using std::cos;
  using std::cosh;
  using std::exp;
  using std::exp2;
  using std::expm1;
  using std::floor;
  using std::log;
  using std::log10;
  using std::log1p;
  using std::log2;
  using std::logb;
  using std::pow;
  using std::hypot;
  using std::floor;
  using std::round;
  using std::sin;
  using std::sinh;
  using std::sqrt;
  using std::tan;
  using std::tanh;
  using std::trunc;
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  Crossroad::kappa( real_type xo__s ) const {
    real_type result__ = (xo__s < ModelPars[iM_L] / 2 ? 2 * ((ModelPars[iM_L] / 2 - xo__s) * ModelPars[iM_kappa0] + xo__s * ModelPars[iM_kappa1]) / ModelPars[iM_L] : 2 * ((ModelPars[iM_L] - xo__s) * ModelPars[iM_kappa1] + (xo__s - ModelPars[iM_L] / 2) * ModelPars[iM_kappa2]) / ModelPars[iM_L]);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Crossroad::kappa_D( real_type xo__s ) const {
    real_type result__ = (xo__s < ModelPars[iM_L] / 2 ? 2 * (ModelPars[iM_kappa1] - ModelPars[iM_kappa0]) / ModelPars[iM_L] : 2 * (ModelPars[iM_kappa2] - ModelPars[iM_kappa1]) / ModelPars[iM_L]);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Crossroad::kappa_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Crossroad::VelBound( real_type xo___V ) const {
    real_type t1   = VelBound_min(-xo___V);
    real_type t4   = VelBound_min(xo___V - ModelPars[iM_v_max]);
    real_type result__ = t1 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_VelBound( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  Crossroad::VelBound_D( real_type xo___V ) const {
    real_type t1   = ALIAS_VelBound_min_D(-xo___V);
    real_type t4   = ALIAS_VelBound_min_D(xo___V - ModelPars[iM_v_max]);
    real_type result__ = -t1 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_VelBound_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  Crossroad::VelBound_DD( real_type xo___V ) const {
    real_type t1   = ALIAS_VelBound_min_DD(-xo___V);
    real_type t4   = ALIAS_VelBound_min_DD(xo___V - ModelPars[iM_v_max]);
    real_type result__ = t1 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_VelBound_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

}

// EOF: Crossroad_Methods_UserFunctions.cc
