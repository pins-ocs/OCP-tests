/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Methods_UserFunctions.cc                              |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "Pugliese.hh"
#include "Pugliese_Pars.hh"
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


namespace PuglieseDefine {
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
  Pugliese::T_lim( real_type xo__T ) const {
    real_type result__ = ModelPars[iM_e__C] * xo__T / (ModelPars[iM_s__C] + xo__T);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_T_lim( T={} ) return {}\n",
        xo__T, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::T_lim_D( real_type xo__T ) const {
    real_type t1   = ModelPars[iM_e__C];
    real_type t3   = ModelPars[iM_s__C] + xo__T;
    real_type t7   = t3 * t3;
    real_type result__ = 1.0 / t3 * t1 - 1.0 / t7 * xo__T * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_T_lim_D( T={} ) return {}\n",
        xo__T, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::T_lim_DD( real_type xo__T ) const {
    real_type t1   = ModelPars[iM_e__C];
    real_type t3   = ModelPars[iM_s__C] + xo__T;
    real_type t4   = t3 * t3;
    real_type result__ = -2 / t4 * t1 + 2 / t4 / t3 * xo__T * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_T_lim_DD( T={} ) return {}\n",
        xo__T, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::D_lim( real_type xo__DD ) const {
    real_type result__ = ModelPars[iM_e__D] * xo__DD / (ModelPars[iM_s__D] + xo__DD);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_D_lim( DD={} ) return {}\n",
        xo__DD, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::D_lim_D( real_type xo__DD ) const {
    real_type t1   = ModelPars[iM_e__D];
    real_type t3   = ModelPars[iM_s__D] + xo__DD;
    real_type t7   = t3 * t3;
    real_type result__ = 1.0 / t3 * t1 - 1.0 / t7 * xo__DD * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_D_lim_D( DD={} ) return {}\n",
        xo__DD, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::D_lim_DD( real_type xo__DD ) const {
    real_type t1   = ModelPars[iM_e__D];
    real_type t3   = ModelPars[iM_s__D] + xo__DD;
    real_type t4   = t3 * t3;
    real_type result__ = -2 / t4 * t1 + 2 / t4 / t3 * xo__DD * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_D_lim_DD( DD={} ) return {}\n",
        xo__DD, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_lim( real_type xo__IL ) const {
    real_type result__ = ModelPars[iM_e__IL] * xo__IL / (ModelPars[iM_s__IL] + xo__IL);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_lim( IL={} ) return {}\n",
        xo__IL, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_lim_D( real_type xo__IL ) const {
    real_type t1   = ModelPars[iM_e__IL];
    real_type t3   = ModelPars[iM_s__IL] + xo__IL;
    real_type t7   = t3 * t3;
    real_type result__ = 1.0 / t3 * t1 - 1.0 / t7 * xo__IL * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_lim_D( IL={} ) return {}\n",
        xo__IL, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_lim_DD( real_type xo__IL ) const {
    real_type t1   = ModelPars[iM_e__IL];
    real_type t3   = ModelPars[iM_s__IL] + xo__IL;
    real_type t4   = t3 * t3;
    real_type result__ = -2 / t4 * t1 + 2 / t4 / t3 * xo__IL * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_lim_DD( IL={} ) return {}\n",
        xo__IL, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL( real_type xo__T, real_type xo__C ) const {
    real_type result__ = ModelPars[iM_i0] + ModelPars[iM_e] * xo__C * xo__T / (ModelPars[iM_s] + xo__T);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL( T={}, C={} ) return {}\n",
        xo__T, xo__C, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_D_1( real_type xo__T, real_type xo__C ) const {
    real_type t2   = ModelPars[iM_e] * xo__C;
    real_type t4   = ModelPars[iM_s] + xo__T;
    real_type t7   = t4 * t4;
    real_type result__ = 1.0 / t4 * t2 - 1.0 / t7 * xo__T * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_D_1( T={}, C={} ) return {}\n",
        xo__T, xo__C, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_D_1_1( real_type xo__T, real_type xo__C ) const {
    real_type t2   = ModelPars[iM_e] * xo__C;
    real_type t4   = ModelPars[iM_s] + xo__T;
    real_type t5   = t4 * t4;
    real_type result__ = -2 / t5 * t2 + 2 / t5 / t4 * xo__T * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_D_1_1( T={}, C={} ) return {}\n",
        xo__T, xo__C, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_D_1_2( real_type xo__T, real_type xo__C ) const {
    real_type t1   = ModelPars[iM_e];
    real_type t3   = ModelPars[iM_s] + xo__T;
    real_type t7   = t3 * t3;
    real_type result__ = 1.0 / t3 * t1 - 1.0 / t7 * xo__T * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_D_1_2( T={}, C={} ) return {}\n",
        xo__T, xo__C, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_D_2( real_type xo__T, real_type xo__C ) const {
    real_type result__ = ModelPars[iM_e] * xo__T / (ModelPars[iM_s] + xo__T);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_D_2( T={}, C={} ) return {}\n",
        xo__T, xo__C, result__
      );
    }
    return result__;
  }

  real_type
  Pugliese::IL_D_2_2( real_type xo__T, real_type xo__C ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_IL_D_2_2( T={}, C={} ) return {}\n",
        xo__T, xo__C, result__
      );
    }
    return result__;
  }

}

// EOF: Pugliese_Methods_UserFunctions.cc
