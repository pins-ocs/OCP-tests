/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_UserFunctions.cc                 |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"
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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace LUUS_DrugDisplacementDefine {
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
  LUUS_DrugDisplacement::g2( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 1 + 0.2e0 * xo__x1 + 0.2e0 * xo__x2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g2_D_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 0.2e0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g2_D_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g2_D_1_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g2_D_1_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g2_D_1_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g2_D_1_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g2_D_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 0.2e0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g2_D_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g2_D_2_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g2_D_2_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g3( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type result__ = t2 + 232 + 0.464e2 * xo__x2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g3( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g3_D_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = g2_D_1(xo__x1, xo__x2);
    real_type result__ = 2 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g3_D_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g3_D_1_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_1(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g2(xo__x1, xo__x2);
    real_type t4   = g2_D_1_1(xo__x1, xo__x2);
    real_type result__ = 2 * t4 * t3 + 2 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g3_D_1_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g3_D_1_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_2(xo__x1, xo__x2);
    real_type t2   = g2_D_1(xo__x1, xo__x2);
    real_type t4   = g2(xo__x1, xo__x2);
    real_type t5   = g2_D_1_2(xo__x1, xo__x2);
    real_type result__ = 2 * t2 * t1 + 2 * t5 * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g3_D_1_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g3_D_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = g2_D_2(xo__x1, xo__x2);
    real_type result__ = 2 * t2 * t1 + 0.464e2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g3_D_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g3_D_2_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_2(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g2(xo__x1, xo__x2);
    real_type t4   = g2_D_2_2(xo__x1, xo__x2);
    real_type result__ = 2 * t4 * t3 + 2 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g3_D_2_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g4( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type result__ = t2 + 232 + 0.464e2 * xo__x1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g4( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g4_D_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = g2_D_1(xo__x1, xo__x2);
    real_type result__ = 2 * t2 * t1 + 0.464e2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g4_D_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g4_D_1_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_1(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g2(xo__x1, xo__x2);
    real_type t4   = g2_D_1_1(xo__x1, xo__x2);
    real_type result__ = 2 * t3 * t4 + 2 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g4_D_1_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g4_D_1_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_2(xo__x1, xo__x2);
    real_type t2   = g2_D_1(xo__x1, xo__x2);
    real_type t4   = g2(xo__x1, xo__x2);
    real_type t5   = g2_D_1_2(xo__x1, xo__x2);
    real_type result__ = 2 * t2 * t1 + 2 * t5 * t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g4_D_1_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g4_D_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = g2_D_2(xo__x1, xo__x2);
    real_type result__ = 2 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g4_D_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g4_D_2_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_2(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g2(xo__x1, xo__x2);
    real_type t4   = g2_D_2_2(xo__x1, xo__x2);
    real_type result__ = 2 * t3 * t4 + 2 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g4_D_2_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g3(xo__x1, xo__x2);
    real_type t4   = g4(xo__x1, xo__x2);
    real_type result__ = 1.0 / (t3 * t4 - 0.215296e4 * xo__x1 * xo__x2) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g1_D_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = g3(xo__x1, xo__x2);
    real_type t3   = g4(xo__x1, xo__x2);
    real_type t7   = t3 * t2 - 0.215296e4 * xo__x1 * xo__x2;
    real_type t10  = g2_D_1(xo__x1, xo__x2);
    real_type t13  = t1 * t1;
    real_type t14  = t7 * t7;
    real_type t17  = g3_D_1(xo__x1, xo__x2);
    real_type t19  = g4_D_1(xo__x1, xo__x2);
    real_type result__ = 2 * t10 / t7 * t1 - (t3 * t17 + t19 * t2 - 0.215296e4 * xo__x2) / t14 * t13;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g1_D_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g1_D_1_1( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_1(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g3(xo__x1, xo__x2);
    real_type t4   = g4(xo__x1, xo__x2);
    real_type t8   = t3 * t4 - 0.215296e4 * xo__x1 * xo__x2;
    real_type t9   = 1.0 / t8;
    real_type t12  = g2(xo__x1, xo__x2);
    real_type t13  = t8 * t8;
    real_type t14  = 1.0 / t13;
    real_type t16  = g3_D_1(xo__x1, xo__x2);
    real_type t18  = g4_D_1(xo__x1, xo__x2);
    real_type t21  = t4 * t16 + t18 * t3 - 0.215296e4 * xo__x2;
    real_type t26  = g2_D_1_1(xo__x1, xo__x2);
    real_type t29  = t12 * t12;
    real_type t33  = t21 * t21;
    real_type t37  = g3_D_1_1(xo__x1, xo__x2);
    real_type t41  = g4_D_1_1(xo__x1, xo__x2);
    real_type result__ = 2 * t9 * t2 - 4 * t21 * t1 * t14 * t12 + 2 * t26 * t9 * t12 + 2 * t33 / t13 / t8 * t29 - (2 * t18 * t16 + t41 * t3 + t4 * t37) * t14 * t29;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g1_D_1_1( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g1_D_1_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_2(xo__x1, xo__x2);
    real_type t2   = g3(xo__x1, xo__x2);
    real_type t3   = g4(xo__x1, xo__x2);
    real_type t7   = t3 * t2 - 0.215296e4 * xo__x1 * xo__x2;
    real_type t8   = 1.0 / t7;
    real_type t10  = g2_D_1(xo__x1, xo__x2);
    real_type t13  = g2(xo__x1, xo__x2);
    real_type t14  = t7 * t7;
    real_type t15  = 1.0 / t14;
    real_type t16  = t15 * t13;
    real_type t17  = g3_D_2(xo__x1, xo__x2);
    real_type t19  = g4_D_2(xo__x1, xo__x2);
    real_type t22  = t3 * t17 + t19 * t2 - 0.215296e4 * xo__x1;
    real_type t27  = g2_D_1_2(xo__x1, xo__x2);
    real_type t30  = g3_D_1(xo__x1, xo__x2);
    real_type t32  = g4_D_1(xo__x1, xo__x2);
    real_type t35  = t3 * t30 + t32 * t2 - 0.215296e4 * xo__x2;
    real_type t39  = t13 * t13;
    real_type t47  = g3_D_1_2(xo__x1, xo__x2);
    real_type t51  = g4_D_1_2(xo__x1, xo__x2);
    real_type result__ = 2 * t10 * t8 * t1 - 2 * t22 * t10 * t16 + 2 * t27 * t8 * t13 - 2 * t1 * t35 * t16 + 2 * t22 * t35 / t14 / t7 * t39 - (t3 * t47 + t19 * t30 + t32 * t17 + t51 * t2 - 0.215296e4) * t15 * t39;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g1_D_1_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g1_D_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2(xo__x1, xo__x2);
    real_type t2   = g3(xo__x1, xo__x2);
    real_type t3   = g4(xo__x1, xo__x2);
    real_type t7   = t3 * t2 - 0.215296e4 * xo__x1 * xo__x2;
    real_type t10  = g2_D_2(xo__x1, xo__x2);
    real_type t13  = t1 * t1;
    real_type t14  = t7 * t7;
    real_type t17  = g3_D_2(xo__x1, xo__x2);
    real_type t19  = g4_D_2(xo__x1, xo__x2);
    real_type result__ = 2 * t10 / t7 * t1 - (t3 * t17 + t19 * t2 - 0.215296e4 * xo__x1) / t14 * t13;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g1_D_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

  real_type
  LUUS_DrugDisplacement::g1_D_2_2( real_type xo__x1, real_type xo__x2 ) const {
    real_type t1   = g2_D_2(xo__x1, xo__x2);
    real_type t2   = t1 * t1;
    real_type t3   = g3(xo__x1, xo__x2);
    real_type t4   = g4(xo__x1, xo__x2);
    real_type t8   = t3 * t4 - 0.215296e4 * xo__x1 * xo__x2;
    real_type t9   = 1.0 / t8;
    real_type t12  = g2(xo__x1, xo__x2);
    real_type t13  = t8 * t8;
    real_type t14  = 1.0 / t13;
    real_type t16  = g3_D_2(xo__x1, xo__x2);
    real_type t18  = g4_D_2(xo__x1, xo__x2);
    real_type t21  = t4 * t16 + t18 * t3 - 0.215296e4 * xo__x1;
    real_type t26  = g2_D_2_2(xo__x1, xo__x2);
    real_type t29  = t12 * t12;
    real_type t33  = t21 * t21;
    real_type t37  = g3_D_2_2(xo__x1, xo__x2);
    real_type t41  = g4_D_2_2(xo__x1, xo__x2);
    real_type result__ = 2 * t9 * t2 - 4 * t21 * t1 * t14 * t12 + 2 * t26 * t9 * t12 + 2 * t33 / t13 / t8 * t29 - (2 * t18 * t16 + t41 * t3 + t4 * t37) * t14 * t29;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_g1_D_2_2( x1={}, x2={} ) return {}\n",
        xo__x1, xo__x2, result__
      );
    }
    return result__;
  }

}

// EOF: LUUS_DrugDisplacement_Methods_UserFunctions.cc
