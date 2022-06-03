/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_UserFunctions.cc                         |
 |                                                                       |
 |  version: 1.0   date 14/6/2022                                        |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"
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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)


namespace GoddardRocketDefine {
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
  GoddardRocket::DD( real_type xo__h, real_type xo__v ) const {
    real_type t2   = xo__v * xo__v;
    real_type t7   = exp(-xo__h / ModelPars[iM_Hscale]);
    real_type result__ = t7 * t2 * ModelPars[iM_D0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_1( real_type xo__h, real_type xo__v ) const {
    real_type t2   = xo__v * xo__v;
    real_type t5   = 1.0 / ModelPars[iM_Hscale];
    real_type t7   = exp(-t5 * xo__h);
    real_type result__ = -t7 * t5 * t2 * ModelPars[iM_D0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_1( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_1_1( real_type xo__h, real_type xo__v ) const {
    real_type t2   = xo__v * xo__v;
    real_type t4   = ModelPars[iM_Hscale];
    real_type t5   = t4 * t4;
    real_type t9   = exp(-1.0 / t4 * xo__h);
    real_type result__ = t9 / t5 * t2 * ModelPars[iM_D0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_1_1( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_1_2( real_type xo__h, real_type xo__v ) const {
    real_type t4   = 1.0 / ModelPars[iM_Hscale];
    real_type t6   = exp(-t4 * xo__h);
    real_type result__ = -2 * t6 * t4 * ModelPars[iM_D0] * xo__v;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_1_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_2( real_type xo__h, real_type xo__v ) const {
    real_type t6   = exp(-xo__h / ModelPars[iM_Hscale]);
    real_type result__ = 2 * t6 * xo__v * ModelPars[iM_D0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_2_2( real_type xo__h, real_type xo__v ) const {
    real_type t5   = exp(-xo__h / ModelPars[iM_Hscale]);
    real_type result__ = 2 * t5 * ModelPars[iM_D0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_2_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

}

// EOF: GoddardRocket_Methods_UserFunctions.cc
