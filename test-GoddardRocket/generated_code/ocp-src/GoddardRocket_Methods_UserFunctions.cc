/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_UserFunctions.cc                         |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  GoddardRocket::DD( real_type xo__h, real_type xo__v ) const {
    real_type t2   = xo__v * xo__v;
    real_type t10  = exp(ModelPars[iM_hc] * (1 - xo__h / ModelPars[iM_h_i]));
    real_type result__ = t10 * t2 * ModelPars[iM_Dc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_1( real_type xo__h, real_type xo__v ) const {
    real_type t2   = xo__v * xo__v;
    real_type t4   = ModelPars[iM_hc];
    real_type t6   = 1.0 / ModelPars[iM_h_i];
    real_type t11  = exp((-t6 * xo__h + 1) * t4);
    real_type result__ = -t11 * t6 * t4 * t2 * ModelPars[iM_Dc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_1( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_1_1( real_type xo__h, real_type xo__v ) const {
    real_type t2   = xo__v * xo__v;
    real_type t4   = ModelPars[iM_hc];
    real_type t5   = t4 * t4;
    real_type t6   = ModelPars[iM_h_i];
    real_type t7   = t6 * t6;
    real_type t14  = exp((1 - 1.0 / t6 * xo__h) * t4);
    real_type result__ = t14 / t7 * t5 * t2 * ModelPars[iM_Dc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_1_1( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_1_2( real_type xo__h, real_type xo__v ) const {
    real_type t3   = ModelPars[iM_hc];
    real_type t5   = 1.0 / ModelPars[iM_h_i];
    real_type t10  = exp((-t5 * xo__h + 1) * t3);
    real_type result__ = -2 * t10 * t5 * t3 * ModelPars[iM_Dc] * xo__v;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_1_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_2( real_type xo__h, real_type xo__v ) const {
    real_type t9   = exp(ModelPars[iM_hc] * (1 - xo__h / ModelPars[iM_h_i]));
    real_type result__ = 2 * t9 * xo__v * ModelPars[iM_Dc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::DD_D_2_2( real_type xo__h, real_type xo__v ) const {
    real_type t8   = exp(ModelPars[iM_hc] * (1 - xo__h / ModelPars[iM_h_i]));
    real_type result__ = 2 * t8 * ModelPars[iM_Dc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DD_D_2_2( h={}, v={} ) return {}\n",
        xo__h, xo__v, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::gg( real_type xo__h ) const {
    real_type t3   = ModelPars[iM_h_i] * ModelPars[iM_h_i];
    real_type t5   = xo__h * xo__h;
    real_type result__ = 1.0 / t5 * t3 * ModelPars[iM_g0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_gg( h={} ) return {}\n",
        xo__h, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::gg_D( real_type xo__h ) const {
    real_type t3   = ModelPars[iM_h_i] * ModelPars[iM_h_i];
    real_type t5   = xo__h * xo__h;
    real_type result__ = -2 / t5 / xo__h * t3 * ModelPars[iM_g0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_gg_D( h={} ) return {}\n",
        xo__h, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::gg_DD( real_type xo__h ) const {
    real_type t3   = ModelPars[iM_h_i] * ModelPars[iM_h_i];
    real_type t5   = xo__h * xo__h;
    real_type t6   = t5 * t5;
    real_type result__ = 6 / t6 * t3 * ModelPars[iM_g0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_gg_DD( h={} ) return {}\n",
        xo__h, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t2   = log(xo__a);
    real_type t4   = log(xo__b);
    real_type result__ = exp(t2 * (1 - xo__s) + t4 * xo__s);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = log(xo__a);
    real_type t2   = log(xo__b);
    real_type t8   = exp(t1 * (1 - xo__s) + t2 * xo__s);
    real_type result__ = t8 * (-t1 + t2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1_1( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = log(xo__a);
    real_type t2   = log(xo__b);
    real_type t4   = pow(t1 - t2, 2);
    real_type t9   = exp(t1 * (1 - xo__s) + t2 * xo__s);
    real_type result__ = t9 * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1_1( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1_2( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = 1 - xo__s;
    real_type t2   = log(xo__a);
    real_type t4   = log(xo__b);
    real_type t7   = exp(t2 * t1 + t4 * xo__s);
    real_type result__ = 1.0 / xo__a * (-t2 * t1 + t4 * t1 - 1) * t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1_2( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_1_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t2   = log(xo__a);
    real_type t4   = log(xo__b);
    real_type t5   = t4 * xo__s;
    real_type t7   = exp(t2 * (1 - xo__s) + t5);
    real_type result__ = -1.0 / xo__b * (t2 * xo__s - t5 - 1) * t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_1_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_2( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = 1 - xo__s;
    real_type t4   = log(xo__a);
    real_type t6   = log(xo__b);
    real_type t9   = exp(t4 * t1 + t6 * xo__s);
    real_type result__ = t9 / xo__a * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_2( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_2_2( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = -1 + xo__s;
    real_type t3   = log(xo__a);
    real_type t5   = log(xo__b);
    real_type t8   = exp(-t3 * t1 + t5 * xo__s);
    real_type t10  = xo__a * xo__a;
    real_type result__ = 1.0 / t10 * xo__s * t8 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_2_2( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_2_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = 1 - xo__s;
    real_type t6   = log(xo__a);
    real_type t8   = log(xo__b);
    real_type t11  = exp(t6 * t1 + t8 * xo__s);
    real_type result__ = t11 / xo__b * xo__s / xo__a * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_2_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t4   = log(xo__a);
    real_type t6   = log(xo__b);
    real_type t9   = exp(t4 * (1 - xo__s) + t6 * xo__s);
    real_type result__ = t9 / xo__b * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

  real_type
  GoddardRocket::explog_D_3_3( real_type xo__s, real_type xo__a, real_type xo__b ) const {
    real_type t1   = -1 + xo__s;
    real_type t3   = log(xo__a);
    real_type t5   = log(xo__b);
    real_type t8   = exp(-t3 * t1 + t5 * xo__s);
    real_type t10  = xo__b * xo__b;
    real_type result__ = 1.0 / t10 * xo__s * t8 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_explog_D_3_3( s={}, a={}, b={} ) return {}\n",
        xo__s, xo__a, xo__b, result__
      );
    }
    return result__;
  }

}

// EOF: GoddardRocket_Methods_UserFunctions.cc
