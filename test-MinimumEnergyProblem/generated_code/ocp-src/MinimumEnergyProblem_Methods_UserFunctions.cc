/*-----------------------------------------------------------------------*\
 |  file: MinimumEnergyProblem_Methods_UserFunctions.cc                  |
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


#include "MinimumEnergyProblem.hh"
#include "MinimumEnergyProblem_Pars.hh"
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
#define ALIAS_x1Limitation_DD(__t1) x1Limitation.DD( __t1)
#define ALIAS_x1Limitation_D(__t1) x1Limitation.D( __t1)


namespace MinimumEnergyProblemDefine {
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
  MinimumEnergyProblem::interpLog( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t2   = pow(xo__v0, 1 - xo__s);
    real_type t3   = pow(xo__v1, xo__s);
    real_type result__ = t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t2   = pow(xo__v0, 1 - xo__s);
    real_type t3   = log(xo__v0);
    real_type t5   = pow(xo__v1, xo__s);
    real_type t8   = log(xo__v1);
    real_type result__ = -t5 * t3 * t2 + t8 * t5 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_1( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1_1( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t2   = pow(xo__v0, 1 - xo__s);
    real_type t3   = log(xo__v0);
    real_type t4   = t3 * t3;
    real_type t6   = pow(xo__v1, xo__s);
    real_type t9   = log(xo__v1);
    real_type t14  = t9 * t9;
    real_type result__ = -2 * t9 * t6 * t3 * t2 + t14 * t6 * t2 + t6 * t4 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_1_1( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1_2( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t1   = 1 - xo__s;
    real_type t2   = pow(xo__v0, t1);
    real_type t3   = t1 * t2;
    real_type t4   = 1.0 / xo__v0;
    real_type t5   = log(xo__v0);
    real_type t7   = pow(xo__v1, xo__s);
    real_type t13  = log(xo__v1);
    real_type result__ = t13 * t7 * t4 * t3 - t7 * t5 * t4 * t3 - t7 * t4 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_1_2( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1_3( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t2   = pow(xo__v0, 1 - xo__s);
    real_type t3   = log(xo__v0);
    real_type t5   = pow(xo__v1, xo__s);
    real_type t7   = 1.0 / xo__v1;
    real_type t10  = t5 * t2;
    real_type t12  = log(xo__v1);
    real_type result__ = -t7 * xo__s * t5 * t3 * t2 + t12 * t7 * xo__s * t10 + t7 * t10;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_1_3( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_2( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t1   = 1 - xo__s;
    real_type t2   = pow(xo__v0, t1);
    real_type t5   = pow(xo__v1, xo__s);
    real_type result__ = t5 / xo__v0 * t1 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_2( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_2_2( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t1   = 1 - xo__s;
    real_type t2   = pow(xo__v0, t1);
    real_type t3   = t1 * t1;
    real_type t5   = xo__v0 * xo__v0;
    real_type t7   = pow(xo__v1, xo__s);
    real_type t8   = t7 / t5;
    real_type result__ = -t8 * t1 * t2 + t8 * t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_2_2( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_2_3( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t1   = 1 - xo__s;
    real_type t2   = pow(xo__v0, t1);
    real_type t6   = pow(xo__v1, xo__s);
    real_type result__ = 1.0 / xo__v1 * xo__s * t6 / xo__v0 * t1 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_2_3( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_3( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t2   = pow(xo__v0, 1 - xo__s);
    real_type t3   = pow(xo__v1, xo__s);
    real_type result__ = xo__s / xo__v1 * t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_3( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_3_3( real_type xo__s, real_type xo__v0, real_type xo__v1 ) const {
    real_type t2   = pow(xo__v0, 1 - xo__s);
    real_type t3   = pow(xo__v1, xo__s);
    real_type t4   = t3 * t2;
    real_type t5   = xo__s * xo__s;
    real_type t6   = xo__v1 * xo__v1;
    real_type t7   = 1.0 / t6;
    real_type result__ = t7 * t5 * t4 - t7 * xo__s * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_interpLog_D_3_3( s={}, v0={}, v1={} ) return {}\n",
        xo__s, xo__v0, xo__v1, result__
      );
    }
    return result__;
  }

}

// EOF: MinimumEnergyProblem_Methods_UserFunctions.cc
