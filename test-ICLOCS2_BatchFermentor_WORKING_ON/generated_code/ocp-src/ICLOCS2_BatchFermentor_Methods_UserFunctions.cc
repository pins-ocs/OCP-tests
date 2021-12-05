/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_UserFunctions.cc                |
 |                                                                       |
 |  version: 1.0   date 6/12/2021                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

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
#define ALIAS_v_Limit_DD(__t1) v_Limit.DD( __t1)
#define ALIAS_v_Limit_D(__t1) v_Limit.D( __t1)
#define ALIAS_s_Limit_DD(__t1) s_Limit.DD( __t1)
#define ALIAS_s_Limit_D(__t1) s_Limit.D( __t1)
#define ALIAS_p_Limit_DD(__t1) p_Limit.DD( __t1)
#define ALIAS_p_Limit_D(__t1) p_Limit.D( __t1)
#define ALIAS_x_Limit_DD(__t1) x_Limit.DD( __t1)
#define ALIAS_x_Limit_D(__t1) x_Limit.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS2_BatchFermentorDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  ICLOCS2_BatchFermentor::mu( real_type xo__s, real_type xo__x ) const {
    real_type result__ = ModelPars[iM_mu_max] * xo__s / (xo__x * ModelPars[iM_kappa_x] + xo__s);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mu( s={}, x={} ) return {}\n",
        xo__s, xo__x, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::mu_D_1( real_type xo__s, real_type xo__x ) const {
    real_type t1   = ModelPars[iM_mu_max];
    real_type t4   = xo__x * ModelPars[iM_kappa_x] + xo__s;
    real_type t8   = t4 * t4;
    real_type result__ = 1.0 / t4 * t1 - 1.0 / t8 * xo__s * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mu_D_1( s={}, x={} ) return {}\n",
        xo__s, xo__x, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::mu_D_1_1( real_type xo__s, real_type xo__x ) const {
    real_type t1   = ModelPars[iM_mu_max];
    real_type t4   = xo__x * ModelPars[iM_kappa_x] + xo__s;
    real_type t5   = t4 * t4;
    real_type result__ = -2 / t5 * t1 + 2 / t5 / t4 * xo__s * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mu_D_1_1( s={}, x={} ) return {}\n",
        xo__s, xo__x, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::mu_D_1_2( real_type xo__s, real_type xo__x ) const {
    real_type t1   = ModelPars[iM_mu_max];
    real_type t2   = ModelPars[iM_kappa_x];
    real_type t4   = t2 * xo__x + xo__s;
    real_type t5   = t4 * t4;
    real_type result__ = -t2 / t5 * t1 + 2 * t2 / t5 / t4 * xo__s * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mu_D_1_2( s={}, x={} ) return {}\n",
        xo__s, xo__x, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::mu_D_2( real_type xo__s, real_type xo__x ) const {
    real_type t3   = ModelPars[iM_kappa_x];
    real_type t6   = pow(t3 * xo__x + xo__s, 2);
    real_type result__ = -t3 / t6 * ModelPars[iM_mu_max] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mu_D_2( s={}, x={} ) return {}\n",
        xo__s, xo__x, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::mu_D_2_2( real_type xo__s, real_type xo__x ) const {
    real_type t3   = ModelPars[iM_kappa_x];
    real_type t5   = t3 * xo__x + xo__s;
    real_type t6   = t5 * t5;
    real_type t9   = t3 * t3;
    real_type result__ = 2 * t9 / t6 / t5 * ModelPars[iM_mu_max] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_mu_D_2_2( s={}, x={} ) return {}\n",
        xo__s, xo__x, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::rho( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_rho_max] * xo__s / (ModelPars[iM_kappa_p] + xo__s * (1 + xo__s / ModelPars[iM_kappa_in]));
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_rho( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::rho_D( real_type xo__s ) const {
    real_type t1   = ModelPars[iM_rho_max];
    real_type t5   = xo__s / ModelPars[iM_kappa_in];
    real_type t8   = ModelPars[iM_kappa_p] + (1 + t5) * xo__s;
    real_type t12  = t8 * t8;
    real_type result__ = 1.0 / t8 * t1 - (1 + 2 * t5) / t12 * xo__s * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_rho_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS2_BatchFermentor::rho_DD( real_type xo__s ) const {
    real_type t1   = ModelPars[iM_rho_max];
    real_type t4   = 1.0 / ModelPars[iM_kappa_in];
    real_type t5   = t4 * xo__s;
    real_type t8   = ModelPars[iM_kappa_p] + (1 + t5) * xo__s;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t13  = 1 + 2 * t5;
    real_type t15  = xo__s * t1;
    real_type t18  = t13 * t13;
    real_type result__ = -2 * t13 * t10 * t1 + 2 * t18 / t9 / t8 * t15 - 2 * t4 * t10 * t15;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_rho_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_UserFunctions.cc
