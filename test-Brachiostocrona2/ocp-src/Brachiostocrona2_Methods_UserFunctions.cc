/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods_UserFunctions.cc                      |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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


namespace Brachiostocrona2Define {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  Brachiostocrona2::theta_sol( real_type xo__v, real_type xo__l1, real_type xo__l2, real_type xo__l3 ) const {
    real_type t8   = arctan2(xo__l2 * xo__v - xo__l3 * ModelPars[iM_g], xo__v * xo__l1);
    real_type result__ = ModelPars[iM_kappa] * 0.3141592654e1 + t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_theta_sol( v={}, l1={}, l2={}, l3={} ) return {}\n",
        xo__v, xo__l1, xo__l2, xo__l3, result__
      );
    }
    return result__;
  }

  real_type
  Brachiostocrona2::theta_sol_D_1( real_type xo__v, real_type xo__l1, real_type xo__l2, real_type xo__l3 ) const {
    real_type t4   = xo__l2 * xo__v - xo__l3 * ModelPars[iM_g];
    real_type t5   = xo__v * xo__l1;
    real_type t6   = arctan2_D_1(t4, t5);
    real_type t8   = arctan2_D_2(t4, t5);
    real_type result__ = xo__l2 * t6 + xo__l1 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_theta_sol_D_1( v={}, l1={}, l2={}, l3={} ) return {}\n",
        xo__v, xo__l1, xo__l2, xo__l3, result__
      );
    }
    return result__;
  }

  real_type
  Brachiostocrona2::theta_sol_D_2( real_type xo__v, real_type xo__l1, real_type xo__l2, real_type xo__l3 ) const {
    real_type t6   = arctan2_D_2(xo__l2 * xo__v - xo__l3 * ModelPars[iM_g], xo__v * xo__l1);
    real_type result__ = xo__v * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_theta_sol_D_2( v={}, l1={}, l2={}, l3={} ) return {}\n",
        xo__v, xo__l1, xo__l2, xo__l3, result__
      );
    }
    return result__;
  }

  real_type
  Brachiostocrona2::theta_sol_D_3( real_type xo__v, real_type xo__l1, real_type xo__l2, real_type xo__l3 ) const {
    real_type t6   = arctan2_D_1(xo__l2 * xo__v - xo__l3 * ModelPars[iM_g], xo__v * xo__l1);
    real_type result__ = xo__v * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_theta_sol_D_3( v={}, l1={}, l2={}, l3={} ) return {}\n",
        xo__v, xo__l1, xo__l2, xo__l3, result__
      );
    }
    return result__;
  }

  real_type
  Brachiostocrona2::theta_sol_D_4( real_type xo__v, real_type xo__l1, real_type xo__l2, real_type xo__l3 ) const {
    real_type t2   = ModelPars[iM_g];
    real_type t6   = arctan2_D_1(-t2 * xo__l3 + xo__l2 * xo__v, xo__v * xo__l1);
    real_type result__ = -t2 * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_theta_sol_D_4( v={}, l1={}, l2={}, l3={} ) return {}\n",
        xo__v, xo__l1, xo__l2, xo__l3, result__
      );
    }
    return result__;
  }

}

// EOF: Brachiostocrona2_Methods_UserFunctions.cc
