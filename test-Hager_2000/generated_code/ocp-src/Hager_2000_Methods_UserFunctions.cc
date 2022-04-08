/*-----------------------------------------------------------------------*\
 |  file: Hager_2000_Methods_UserFunctions.cc                            |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "Hager_2000.hh"
#include "Hager_2000_Pars.hh"
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


namespace Hager_2000Define {
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
  Hager_2000::x_exact( real_type xo__t ) const {
    real_type t2   = exp(3 * xo__t);
    real_type t4   = exp(3);
    real_type t7   = exp(3.0 / 2.0 * xo__t);
    real_type result__ = 1.0 / (2 + t4) / t7 * (2 * t2 + t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_exact( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  Hager_2000::x_exact_D( real_type xo__t ) const {
    real_type t2   = exp(3 * xo__t);
    real_type t4   = exp(3.0 / 2.0 * xo__t);
    real_type t5   = 1.0 / t4;
    real_type t7   = exp(3);
    real_type t9   = 1.0 / (2 + t7);
    real_type result__ = 6 * t9 * t5 * t2 - 3.0 / 2.0 * t9 * t5 * (2 * t2 + t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_exact_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  Hager_2000::x_exact_DD( real_type xo__t ) const {
    real_type t2   = exp(3 * xo__t);
    real_type t4   = exp(3);
    real_type t7   = exp(3.0 / 2.0 * xo__t);
    real_type result__ = 9.0 / 4.0 / (2 + t4) / t7 * (2 * t2 + t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_exact_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  Hager_2000::u_exact( real_type xo__t ) const {
    real_type t2   = exp(3 * xo__t);
    real_type t3   = exp(3);
    real_type t6   = exp(3.0 / 2.0 * xo__t);
    real_type result__ = 2 / (2 + t3) / t6 * (t2 - t3);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_u_exact( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  Hager_2000::u_exact_D( real_type xo__t ) const {
    real_type t2   = exp(3 * xo__t);
    real_type t4   = exp(3.0 / 2.0 * xo__t);
    real_type t5   = 1.0 / t4;
    real_type t7   = exp(3);
    real_type t9   = 1.0 / (2 + t7);
    real_type result__ = 6 * t9 * t5 * t2 - 3 * t9 * t5 * (t2 - t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_u_exact_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  Hager_2000::u_exact_DD( real_type xo__t ) const {
    real_type t2   = exp(3 * xo__t);
    real_type t3   = exp(3);
    real_type t6   = exp(3.0 / 2.0 * xo__t);
    real_type result__ = 9.0 / 2.0 / (2 + t3) / t6 * (t2 - t3);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_u_exact_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

}

// EOF: Hager_2000_Methods_UserFunctions.cc
