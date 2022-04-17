/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_UserFunctions.cc                              |
 |                                                                       |
 |  version: 1.0   date 17/4/2022                                        |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"
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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {
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
  AlpRider::p_base( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t2   = pow(xo__t - xo__a, 2);
    real_type result__ = exp(-t2 * xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_1( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t1   = xo__t - xo__a;
    real_type t3   = t1 * t1;
    real_type t5   = exp(-t3 * xo__b);
    real_type result__ = -2 * t5 * t1 * xo__b;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_1( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_1_1( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t2   = pow(xo__t - xo__a, 2);
    real_type t4   = exp(-t2 * xo__b);
    real_type t7   = xo__b * xo__b;
    real_type result__ = 4 * t4 * t2 * t7 - 2 * t4 * xo__b;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_1_1( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_1_2( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t2   = pow(xo__t - xo__a, 2);
    real_type t4   = exp(-t2 * xo__b);
    real_type t7   = xo__b * xo__b;
    real_type result__ = -4 * t4 * t2 * t7 + 2 * t4 * xo__b;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_1_2( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_1_3( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t1   = xo__t - xo__a;
    real_type t2   = t1 * t1;
    real_type t4   = exp(-t2 * xo__b);
    real_type result__ = 2 * t4 * t2 * t1 * xo__b - 2 * t4 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_1_3( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_2( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t1   = xo__t - xo__a;
    real_type t3   = t1 * t1;
    real_type t5   = exp(-t3 * xo__b);
    real_type result__ = 2 * t5 * t1 * xo__b;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_2( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_2_2( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t2   = pow(xo__t - xo__a, 2);
    real_type t4   = exp(-t2 * xo__b);
    real_type t7   = xo__b * xo__b;
    real_type result__ = 4 * t4 * t2 * t7 - 2 * t4 * xo__b;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_2_2( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_2_3( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t1   = xo__t - xo__a;
    real_type t2   = t1 * t1;
    real_type t4   = exp(-t2 * xo__b);
    real_type result__ = -2 * t4 * t2 * t1 * xo__b + 2 * t4 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_2_3( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_3( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t2   = pow(xo__t - xo__a, 2);
    real_type t4   = exp(-t2 * xo__b);
    real_type result__ = -t4 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_3( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::p_base_D_3_3( real_type xo__t, real_type xo__a, real_type xo__b ) const {
    real_type t2   = pow(xo__t - xo__a, 2);
    real_type t3   = t2 * t2;
    real_type t5   = exp(-t2 * xo__b);
    real_type result__ = t5 * t3;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p_base_D_3_3( t={}, a={}, b={} ) return {}\n",
        xo__t, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::q_lower( real_type xo__t ) const {
    real_type t1   = p_base(xo__t, 3, 12);
    real_type t3   = p_base(xo__t, 6, 10);
    real_type t5   = p_base(xo__t, 10, 6);
    real_type t7   = p_base(xo__t, 15, 4);
    real_type result__ = 3 * t1 + 3 * t3 + 3 * t5 + 8 * t7 + 0.1e-1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_q_lower( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::q_lower_D( real_type xo__t ) const {
    real_type t1   = p_base_D_1(xo__t, 3, 12);
    real_type t3   = p_base_D_1(xo__t, 6, 10);
    real_type t5   = p_base_D_1(xo__t, 10, 6);
    real_type t7   = p_base_D_1(xo__t, 15, 4);
    real_type result__ = 3 * t1 + 3 * t3 + 3 * t5 + 8 * t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_q_lower_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  AlpRider::q_lower_DD( real_type xo__t ) const {
    real_type t1   = p_base_D_1_1(xo__t, 3, 12);
    real_type t3   = p_base_D_1_1(xo__t, 6, 10);
    real_type t5   = p_base_D_1_1(xo__t, 10, 6);
    real_type t7   = p_base_D_1_1(xo__t, 15, 4);
    real_type result__ = 3 * t1 + 3 * t3 + 3 * t5 + 8 * t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_q_lower_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

}

// EOF: AlpRider_Methods_UserFunctions.cc
