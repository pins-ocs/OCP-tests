/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_UserFunctions.cc                            |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  HangGlider::r( real_type xo__x ) const {
    real_type result__ = pow(xo__x / ModelPars[iM_rc] - 0.25e1, 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_r( x={} ) return {}\n",
        xo__x, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::r_D( real_type xo__x ) const {
    real_type t2   = ModelPars[iM_rc];
    real_type t5   = t2 * t2;
    real_type result__ = 1.0 / t5 * (2.0 * xo__x - 5.0 * t2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_r_D( x={} ) return {}\n",
        xo__x, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::r_DD( real_type xo__x ) const {
    real_type t2   = ModelPars[iM_rc] * ModelPars[iM_rc];
    real_type result__ = 2.0 / t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_r_DD( x={} ) return {}\n",
        xo__x, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::u( real_type xo__x ) const {
    real_type t2   = r(xo__x);
    real_type t5   = exp(-t2);
    real_type result__ = t5 * (1 - t2) * ModelPars[iM_uc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_u( x={} ) return {}\n",
        xo__x, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::u_D( real_type xo__x ) const {
    real_type t2   = r_D(xo__x);
    real_type t4   = r(xo__x);
    real_type t5   = exp(-t4);
    real_type result__ = (t4 - 2) * t5 * t2 * ModelPars[iM_uc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_u_D( x={} ) return {}\n",
        xo__x, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::u_DD( real_type xo__x ) const {
    real_type t2   = r(xo__x);
    real_type t3   = exp(-t2);
    real_type t6   = r_DD(xo__x);
    real_type t8   = r_D(xo__x);
    real_type t9   = t8 * t8;
    real_type result__ = -(t6 * (-t2 + 2) + (t2 - 3) * t9) * t3 * ModelPars[iM_uc];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_u_DD( x={} ) return {}\n",
        xo__x, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::w( real_type xo__x, real_type xo__y1 ) const {
    real_type t1   = u(xo__x);
    real_type result__ = xo__y1 - t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_w( x={}, y1={} ) return {}\n",
        xo__x, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::w_D_1( real_type xo__x, real_type xo__y1 ) const {
    real_type t1   = u_D(xo__x);
    real_type result__ = -t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_w_D_1( x={}, y1={} ) return {}\n",
        xo__x, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::w_D_1_1( real_type xo__x, real_type xo__y1 ) const {
    real_type t1   = u_DD(xo__x);
    real_type result__ = -t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_w_D_1_1( x={}, y1={} ) return {}\n",
        xo__x, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::w_D_1_2( real_type xo__x, real_type xo__y1 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_w_D_1_2( x={}, y1={} ) return {}\n",
        xo__x, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::w_D_2( real_type xo__x, real_type xo__y1 ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_w_D_2( x={}, y1={} ) return {}\n",
        xo__x, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::w_D_2_2( real_type xo__x, real_type xo__y1 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_w_D_2_2( x={}, y1={} ) return {}\n",
        xo__x, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = xo__x1 * xo__x1;
    real_type t2   = w(xo__x, xo__y1);
    real_type t3   = t2 * t2;
    real_type result__ = t1 + t3;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = w(xo__x, xo__y1);
    real_type t2   = w_D_1(xo__x, xo__y1);
    real_type result__ = 2 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_1_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = w_D_1(xo__x, xo__y1);
    real_type t2   = t1 * t1;
    real_type t3   = w(xo__x, xo__y1);
    real_type t4   = w_D_1_1(xo__x, xo__y1);
    real_type result__ = 2 * t4 * t3 + 2 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_1_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_1_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_1_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_1_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = w_D_2(xo__x, xo__y1);
    real_type t2   = w_D_1(xo__x, xo__y1);
    real_type t4   = w(xo__x, xo__y1);
    real_type t5   = w_D_1_2(xo__x, xo__y1);
    real_type result__ = 2 * t2 * t1 + 2 * t5 * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_1_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type result__ = 2 * xo__x1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_2_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type result__ = 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_2_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_2_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_2_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = w(xo__x, xo__y1);
    real_type t2   = w_D_2(xo__x, xo__y1);
    real_type result__ = 2 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v2_D_3_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = w_D_2(xo__x, xo__y1);
    real_type t2   = t1 * t1;
    real_type t3   = w(xo__x, xo__y1);
    real_type t4   = w_D_2_2(xo__x, xo__y1);
    real_type result__ = 2 * t4 * t3 + 2 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v2_D_3_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2(xo__x, xo__x1, xo__y1);
    real_type result__ = sqrt(t1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2(xo__x, xo__x1, xo__y1);
    real_type t2   = sqrt(t1);
    real_type t4   = v2_D_1(xo__x, xo__x1, xo__y1);
    real_type result__ = t4 / t2 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_1_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2_D_1_1(xo__x, xo__x1, xo__y1);
    real_type t2   = v2(xo__x, xo__x1, xo__y1);
    real_type t5   = v2_D_1(xo__x, xo__x1, xo__y1);
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t2);
    real_type result__ = 1.0 / t8 / t2 * (2 * t2 * t1 - t6) / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_1_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_1_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2_D_1_2(xo__x, xo__x1, xo__y1);
    real_type t2   = v2(xo__x, xo__x1, xo__y1);
    real_type t5   = v2_D_1(xo__x, xo__x1, xo__y1);
    real_type t6   = v2_D_2(xo__x, xo__x1, xo__y1);
    real_type t9   = sqrt(t2);
    real_type result__ = 1.0 / t9 / t2 * (2 * t2 * t1 - t6 * t5) / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_1_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_1_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2_D_1_3(xo__x, xo__x1, xo__y1);
    real_type t2   = v2(xo__x, xo__x1, xo__y1);
    real_type t5   = v2_D_1(xo__x, xo__x1, xo__y1);
    real_type t6   = v2_D_3(xo__x, xo__x1, xo__y1);
    real_type t9   = sqrt(t2);
    real_type result__ = 1.0 / t9 / t2 * (2 * t2 * t1 - t6 * t5) / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_1_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2(xo__x, xo__x1, xo__y1);
    real_type t2   = sqrt(t1);
    real_type t4   = v2_D_2(xo__x, xo__x1, xo__y1);
    real_type result__ = t4 / t2 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_2_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2_D_2_2(xo__x, xo__x1, xo__y1);
    real_type t2   = v2(xo__x, xo__x1, xo__y1);
    real_type t5   = v2_D_2(xo__x, xo__x1, xo__y1);
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t2);
    real_type result__ = 1.0 / t8 / t2 * (2 * t2 * t1 - t6) / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_2_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_2_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2_D_2_3(xo__x, xo__x1, xo__y1);
    real_type t2   = v2(xo__x, xo__x1, xo__y1);
    real_type t5   = v2_D_2(xo__x, xo__x1, xo__y1);
    real_type t6   = v2_D_3(xo__x, xo__x1, xo__y1);
    real_type t9   = sqrt(t2);
    real_type result__ = 1.0 / t9 / t2 * (2 * t2 * t1 - t6 * t5) / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_2_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2(xo__x, xo__x1, xo__y1);
    real_type t2   = sqrt(t1);
    real_type t4   = v2_D_3(xo__x, xo__x1, xo__y1);
    real_type result__ = t4 / t2 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::v_D_3_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t1   = v2_D_3_3(xo__x, xo__x1, xo__y1);
    real_type t2   = v2(xo__x, xo__x1, xo__y1);
    real_type t5   = v2_D_3(xo__x, xo__x1, xo__y1);
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t2);
    real_type result__ = 1.0 / t8 / t2 * (2 * t2 * t1 - t6) / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_v_D_3_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_1_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1_1(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_1_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_1_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1_2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_1_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_1_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_1_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_2_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_2_2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_2_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_2_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_2_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_2_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Dfun_D_3_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_3_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dfun_D_3_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_1_1( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1_1(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_1_1( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_1_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1_2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_1_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_1_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_1_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_1_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_2_2( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_2_2(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_2_2( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_2_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_2_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_2_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

  real_type
  HangGlider::Lfun_D_3_3( real_type xo__x, real_type xo__x1, real_type xo__y1 ) const {
    real_type t4   = v2_D_3_3(xo__x, xo__x1, xo__y1);
    real_type result__ = 0.5e0 * t4 * ModelPars[iM_S] * ModelPars[iM_rho];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Lfun_D_3_3( x={}, x1={}, y1={} ) return {}\n",
        xo__x, xo__x1, xo__y1, result__
      );
    }
    return result__;
  }

}

// EOF: HangGlider_Methods_UserFunctions.cc
