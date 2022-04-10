/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_UserFunctions.cc                  |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"
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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {
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
  EconomicGrowthModel2::Q( real_type xo__x, real_type xo__y ) const {
    real_type result__ = xo__x * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Q( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::Q_D_1( real_type xo__x, real_type xo__y ) const {
    real_type result__ = xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Q_D_1( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::Q_D_1_1( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Q_D_1_1( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::Q_D_1_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Q_D_1_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::Q_D_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = xo__x;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Q_D_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::Q_D_2_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Q_D_2_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = log(xo__a);
    real_type t4   = log(xo__b);
    real_type result__ = exp((1 - xo__s) * t1 + xo__s * t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_1( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t2   = 1 - xo__s;
    real_type t4   = log(xo__a);
    real_type t6   = log(xo__b);
    real_type t9   = exp(t2 * t4 + xo__s * t6);
    real_type result__ = t9 * t2 / xo__a;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_1_1( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = xo__a * xo__a;
    real_type t2   = 1.0 / t1;
    real_type t3   = 1 - xo__s;
    real_type t5   = log(xo__a);
    real_type t7   = log(xo__b);
    real_type t10  = exp(t3 * t5 + xo__s * t7);
    real_type t12  = t3 * t3;
    real_type result__ = t10 * t12 * t2 - t10 * t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1_1( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_1_2( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t2   = 1 - xo__s;
    real_type t6   = log(xo__a);
    real_type t8   = log(xo__b);
    real_type t11  = exp(t2 * t6 + xo__s * t8);
    real_type result__ = t11 * xo__s / xo__b * t2 / xo__a;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1_2( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_1_3( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = 1.0 / xo__a;
    real_type t2   = log(xo__a);
    real_type t3   = 1 - xo__s;
    real_type t5   = log(xo__b);
    real_type t8   = exp(t3 * t2 + xo__s * t5);
    real_type result__ = -t8 * t1 + t8 * (-t2 + t5) * t3 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1_3( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_2( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t3   = log(xo__a);
    real_type t6   = log(xo__b);
    real_type t9   = exp((1 - xo__s) * t3 + xo__s * t6);
    real_type result__ = t9 * xo__s / xo__b;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_2( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_2_2( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = xo__b * xo__b;
    real_type t2   = 1.0 / t1;
    real_type t4   = log(xo__a);
    real_type t7   = log(xo__b);
    real_type t10  = exp((1 - xo__s) * t4 + xo__s * t7);
    real_type t12  = xo__s * xo__s;
    real_type result__ = t10 * t12 * t2 - t10 * xo__s * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_2_2( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_2_3( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = 1.0 / xo__b;
    real_type t2   = log(xo__a);
    real_type t5   = log(xo__b);
    real_type t8   = exp((1 - xo__s) * t2 + xo__s * t5);
    real_type result__ = t8 * t1 + t8 * (-t2 + t5) * xo__s * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_2_3( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_3( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = log(xo__a);
    real_type t2   = log(xo__b);
    real_type t8   = exp((1 - xo__s) * t1 + xo__s * t2);
    real_type result__ = t8 * (-t1 + t2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_3( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel2::explog_D_3_3( real_type xo__a, real_type xo__b, real_type xo__s ) const {
    real_type t1   = log(xo__a);
    real_type t2   = log(xo__b);
    real_type t4   = pow(-t1 + t2, 2);
    real_type t9   = exp((1 - xo__s) * t1 + xo__s * t2);
    real_type result__ = t9 * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_3_3( a={}, b={}, s={} ) return {}\n",
        xo__a, xo__b, xo__s, result__
      );
    }
    return result__;
  }

}

// EOF: EconomicGrowthModel2_Methods_UserFunctions.cc
