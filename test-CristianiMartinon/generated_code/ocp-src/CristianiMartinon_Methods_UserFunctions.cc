/*-----------------------------------------------------------------------*\
 |  file: CristianiMartinon_Methods_UserFunctions.cc                     |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "CristianiMartinon.hh"
#include "CristianiMartinon_Pars.hh"
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
#define ALIAS_pos_DD(__t1) pos.DD( __t1)
#define ALIAS_pos_D(__t1) pos.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace CristianiMartinonDefine {
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
  CristianiMartinon::cfun( real_type xo__x, real_type xo__y ) const {
    real_type t2   = pos(xo__y - 1);
    real_type t3   = t2 * t2;
    real_type result__ = 1 + t3;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_cfun( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::cfun_D_1( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_cfun_D_1( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::cfun_D_1_1( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_cfun_D_1_1( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::cfun_D_1_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_cfun_D_1_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::cfun_D_2( real_type xo__x, real_type xo__y ) const {
    real_type t1   = xo__y - 1;
    real_type t2   = pos(t1);
    real_type t3   = ALIAS_pos_D(t1);
    real_type result__ = 2 * t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_cfun_D_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::cfun_D_2_2( real_type xo__x, real_type xo__y ) const {
    real_type t1   = xo__y - 1;
    real_type t2   = ALIAS_pos_D(t1);
    real_type t3   = t2 * t2;
    real_type t4   = pos(t1);
    real_type t5   = ALIAS_pos_DD(t1);
    real_type result__ = 2 * t5 * t4 + 2 * t3;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_cfun_D_2_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::yguess( real_type xo__zeta ) const {
    real_type result__ = 4 * ModelPars[iM_ymax_guess] * xo__zeta * (1 - xo__zeta);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yguess( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::yguess_D( real_type xo__zeta ) const {
    real_type t1   = ModelPars[iM_ymax_guess];
    real_type result__ = 4 * (1 - xo__zeta) * t1 - 4 * xo__zeta * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yguess_D( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::yguess_DD( real_type xo__zeta ) const {
    real_type result__ = -8 * ModelPars[iM_ymax_guess];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_yguess_DD( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::xguess( real_type xo__zeta ) const {
    real_type t1   = ModelPars[iM_x_i];
    real_type result__ = t1 + (ModelPars[iM_x_f] - t1) * xo__zeta;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xguess( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::xguess_D( real_type xo__zeta ) const {
    real_type result__ = ModelPars[iM_x_f] - ModelPars[iM_x_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xguess_D( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  CristianiMartinon::xguess_DD( real_type xo__zeta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_xguess_DD( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

}

// EOF: CristianiMartinon_Methods_UserFunctions.cc
