/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_UserFunctions.cc                         |
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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


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
        Utils::is_finite(result__),
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
        Utils::is_finite(result__),
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
        Utils::is_finite(result__),
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
        Utils::is_finite(result__),
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
        Utils::is_finite(result__),
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
        Utils::is_finite(result__),
        "UserFunctions_DD_D_2_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::T( real_type xo__u ) const {
    real_type result__ = ModelPars[iM_Tmax] * xo__u;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_T( u={} ) return {}\n",
        xo__u, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::T_D( real_type xo__u ) const {
    real_type result__ = ModelPars[iM_Tmax];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_T_D( u={} ) return {}\n",
        xo__u, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::T_DD( real_type xo__u ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_T_DD( u={} ) return {}\n",
        xo__u, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t2   = log(xo__a);
    real_type t4   = log(xo__b);
    real_type result__ = exp(t2 * (1 - xo__s) + t4 * xo__s);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = log(xo__a);
    real_type t2   = log(xo__b);
    real_type t8   = exp(t1 * (1 - xo__s) + t2 * xo__s);
    real_type result__ = t8 * (-t1 + t2);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_1( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1_1( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = log(xo__a);
    real_type t2   = log(xo__b);
    real_type t4   = pow(-t1 + t2, 2);
    real_type t9   = exp(t1 * (1 - xo__s) + t2 * xo__s);
    real_type result__ = t9 * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_1_1( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1_2( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t2   = 1 - xo__s;
    real_type t3   = log(xo__a);
    real_type t5   = log(xo__b);
    real_type t8   = exp(t3 * t2 + t5 * xo__s);
    real_type t9   = t8 / xo__a;
    real_type result__ = -t9 + t9 * t2 * (-t3 + t5);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_1_2( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t3   = log(xo__a);
    real_type t5   = log(xo__b);
    real_type t8   = exp(t3 * (1 - xo__s) + t5 * xo__s);
    real_type t9   = t8 / xo__b;
    real_type result__ = t9 + t9 * xo__s * (-t3 + t5);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_1_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_2( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = 1 - xo__s;
    real_type t4   = log(xo__a);
    real_type t6   = log(xo__b);
    real_type t9   = exp(t4 * t1 + t6 * xo__s);
    real_type result__ = t9 / xo__a * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_2( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_2_2( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = 1 - xo__s;
    real_type t2   = xo__a * xo__a;
    real_type t3   = 1.0 / t2;
    real_type t5   = log(xo__a);
    real_type t7   = log(xo__b);
    real_type t10  = exp(t1 * t5 + t7 * xo__s);
    real_type t12  = t1 * t1;
    real_type result__ = -t1 * t10 * t3 + t10 * t12 * t3;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_2_2( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_2_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = 1 - xo__s;
    real_type t6   = log(xo__a);
    real_type t8   = log(xo__b);
    real_type t11  = exp(t6 * t1 + t8 * xo__s);
    real_type result__ = t11 / xo__b * xo__s / xo__a * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_2_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t4   = log(xo__a);
    real_type t6   = log(xo__b);
    real_type t9   = exp(t4 * (1 - xo__s) + t6 * xo__s);
    real_type result__ = t9 / xo__b * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_3_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = xo__b * xo__b;
    real_type t2   = 1.0 / t1;
    real_type t5   = log(xo__a);
    real_type t7   = log(xo__b);
    real_type t10  = exp(t5 * (1 - xo__s) + t7 * xo__s);
    real_type t12  = xo__s * xo__s;
    real_type result__ = t10 * t2 * t12 - t10 * t2 * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_explog_D_3_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

}

// EOF: GoddardRocket_Methods_UserFunctions.cc
