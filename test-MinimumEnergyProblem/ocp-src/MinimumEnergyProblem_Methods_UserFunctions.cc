/*-----------------------------------------------------------------------*\
 |  file: MinimumEnergyProblem_Methods_UserFunctions.cc                  |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
    real_type t1   = pow(xo__v1, xo__s);
    real_type t3   = pow(xo__v0, 1 - xo__s);
    real_type t5   = log(xo__v0);
    real_type t6   = log(xo__v1);
    real_type result__ = -(t5 - t6) * t3 * t1;
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
    real_type t1   = pow(xo__v1, xo__s);
    real_type t3   = pow(xo__v0, 1 - xo__s);
    real_type t5   = log(xo__v0);
    real_type t6   = log(xo__v1);
    real_type t8   = pow(t5 - t6, 2);
    real_type result__ = t8 * t3 * t1;
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
    real_type t1   = pow(xo__v1, xo__s);
    real_type t2   = -1 + xo__s;
    real_type t3   = log(xo__v0);
    real_type t6   = log(xo__v1);
    real_type t10  = pow(xo__v0, -xo__s);
    real_type result__ = t10 * (t3 * t2 - t6 * t2 - 1) * t1;
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
    real_type t1   = -1 + xo__s;
    real_type t2   = pow(xo__v1, t1);
    real_type t4   = pow(xo__v0, -t1);
    real_type t6   = log(xo__v0);
    real_type t8   = log(xo__v1);
    real_type result__ = -(t6 * xo__s - t8 * xo__s - 1) * t4 * t2;
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
    real_type t1   = pow(xo__v0, -xo__s);
    real_type t4   = pow(xo__v1, xo__s);
    real_type result__ = t4 * (1 - xo__s) * t1;
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
    real_type t2   = pow(xo__v0, -xo__s - 1);
    real_type t5   = pow(xo__v1, xo__s);
    real_type result__ = t5 * (-1 + xo__s) * xo__s * t2;
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
    real_type t1   = pow(xo__v0, -xo__s);
    real_type t2   = 1 - xo__s;
    real_type t5   = pow(xo__v1, -t2);
    real_type result__ = xo__s * t5 * t2 * t1;
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
    real_type t1   = 1 - xo__s;
    real_type t2   = pow(xo__v0, t1);
    real_type t4   = pow(xo__v1, -t1);
    real_type result__ = xo__s * t4 * t2;
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
    real_type t1   = 1 - xo__s;
    real_type t2   = pow(xo__v0, t1);
    real_type t4   = pow(xo__v1, -2 + xo__s);
    real_type result__ = -xo__s * t1 * t4 * t2;
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
