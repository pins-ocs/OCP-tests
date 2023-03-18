/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods_UserFunctions.cc                                 |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "Brake.hh"
#include "Brake_Pars.hh"
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


namespace BrakeDefine {
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
  Brake::guess_x( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_Tguess] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_x( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_x_D( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_Tguess];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_x_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_x_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_x_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_v( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_v_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_v( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_v_D( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_v_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_v_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_v_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_lambda1( real_type xo__s ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_lambda1( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_lambda1_D( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_lambda1_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_lambda1_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_lambda1_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_lambda2( real_type xo__s ) const {
    real_type result__ = 1 - xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_lambda2( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_lambda2_D( real_type xo__s ) const {
    real_type result__ = -1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_lambda2_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_lambda2_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_lambda2_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_u( real_type xo__s ) const {
    real_type result__ = -1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_u( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_u_D( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_u_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  Brake::guess_u_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_guess_u_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

}

// EOF: Brake_Methods_UserFunctions.cc
