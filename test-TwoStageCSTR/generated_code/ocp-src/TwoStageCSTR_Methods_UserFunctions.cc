/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods_UserFunctions.cc                          |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"
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
#pragma warning( disable : 4189 )
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
  TwoStageCSTR::R1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t6   = exp(25 * xo__x2 / (xo__x2 + 2));
    real_type result__ = t6 * (xo__x1 + 0.5e0);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R1_D_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = exp(25 * xo__x2 / (xo__x2 + 2));
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R1_D_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R1_D_1_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R1_D_1_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R1_D_1_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = xo__x2 + 2;
    real_type t2   = 1.0 / t1;
    real_type t3   = t1 * t1;
    real_type t10  = exp(25 * t2 * xo__x2);
    real_type result__ = t10 * (25 * t2 - 25 / t3 * xo__x2);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R1_D_1_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R1_D_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t2   = xo__x2 + 2;
    real_type t3   = 1.0 / t2;
    real_type t4   = t2 * t2;
    real_type t12  = exp(25 * t3 * xo__x2);
    real_type result__ = t12 * (25 * t3 - 25 / t4 * xo__x2) * (xo__x1 + 0.5e0);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R1_D_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R1_D_2_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = xo__x1 + 0.5e0;
    real_type t2   = xo__x2 + 2;
    real_type t3   = t2 * t2;
    real_type t4   = 1.0 / t3;
    real_type t11  = 1.0 / t2;
    real_type t14  = exp(25 * t11 * xo__x2);
    real_type t19  = pow(-25 * t4 * xo__x2 + 25 * t11, 2);
    real_type result__ = t14 * (-50 * t4 + 50 / t3 / t2 * xo__x2) * t1 + t14 * t19 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R1_D_2_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R2( real_type xo__x3, real_type xo__x4 ) const {
    real_type t6   = exp(25 * xo__x4 / (xo__x4 + 2));
    real_type result__ = t6 * (xo__x3 + 0.25e0);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R2( x3={}, x4={} ) return {}\n",
        xo__x3, xo__x4, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R2_D_1( real_type xo__x3, real_type xo__x4 ) const {
    real_type result__ = exp(25 * xo__x4 / (xo__x4 + 2));
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R2_D_1( x3={}, x4={} ) return {}\n",
        xo__x3, xo__x4, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R2_D_1_1( real_type xo__x3, real_type xo__x4 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R2_D_1_1( x3={}, x4={} ) return {}\n",
        xo__x3, xo__x4, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R2_D_1_2( real_type xo__x3, real_type xo__x4 ) const {
    real_type t1   = xo__x4 + 2;
    real_type t2   = 1.0 / t1;
    real_type t3   = t1 * t1;
    real_type t10  = exp(25 * t2 * xo__x4);
    real_type result__ = t10 * (25 * t2 - 25 / t3 * xo__x4);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R2_D_1_2( x3={}, x4={} ) return {}\n",
        xo__x3, xo__x4, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R2_D_2( real_type xo__x3, real_type xo__x4 ) const {
    real_type t2   = xo__x4 + 2;
    real_type t3   = 1.0 / t2;
    real_type t4   = t2 * t2;
    real_type t12  = exp(25 * t3 * xo__x4);
    real_type result__ = t12 * (25 * t3 - 25 / t4 * xo__x4) * (xo__x3 + 0.25e0);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R2_D_2( x3={}, x4={} ) return {}\n",
        xo__x3, xo__x4, result__
      );
    }
    return result__;
  }

  real_type
  TwoStageCSTR::R2_D_2_2( real_type xo__x3, real_type xo__x4 ) const {
    real_type t1   = xo__x3 + 0.25e0;
    real_type t2   = xo__x4 + 2;
    real_type t3   = t2 * t2;
    real_type t4   = 1.0 / t3;
    real_type t11  = 1.0 / t2;
    real_type t14  = exp(25 * t11 * xo__x4);
    real_type t19  = pow(-25 * t4 * xo__x4 + 25 * t11, 2);
    real_type result__ = t14 * (-50 * t4 + 50 / t3 / t2 * xo__x4) * t1 + t14 * t19 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_R2_D_2_2( x3={}, x4={} ) return {}\n",
        xo__x3, xo__x4, result__
      );
    }
    return result__;
  }

}

// EOF: TwoStageCSTR_Methods_UserFunctions.cc
