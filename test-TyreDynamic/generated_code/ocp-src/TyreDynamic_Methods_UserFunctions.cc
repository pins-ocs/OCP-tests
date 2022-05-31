/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_UserFunctions.cc                           |
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


#include "TyreDynamic.hh"
#include "TyreDynamic_Pars.hh"
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
#define ALIAS_abs_reg_DD(__t1) abs_reg.DD( __t1)
#define ALIAS_abs_reg_D(__t1) abs_reg.D( __t1)
#define ALIAS_sign_reg_DD(__t1) sign_reg.DD( __t1)
#define ALIAS_sign_reg_D(__t1) sign_reg.D( __t1)
#define ALIAS_clipInt_D_3(__t1, __t2, __t3) clipInt.D_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2(__t1, __t2, __t3) clipInt.D_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1(__t1, __t2, __t3) clipInt.D_1( __t1, __t2, __t3)
#define ALIAS_clipInt_D_3_3(__t1, __t2, __t3) clipInt.D_3_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_3(__t1, __t2, __t3) clipInt.D_2_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_2(__t1, __t2, __t3) clipInt.D_2_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_3(__t1, __t2, __t3) clipInt.D_1_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_2(__t1, __t2, __t3) clipInt.D_1_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_1(__t1, __t2, __t3) clipInt.D_1_1( __t1, __t2, __t3)
#define ALIAS_clipSup_D_2(__t1, __t2) clipSup.D_2( __t1, __t2)
#define ALIAS_clipSup_D_1(__t1, __t2) clipSup.D_1( __t1, __t2)
#define ALIAS_clipSup_D_2_2(__t1, __t2) clipSup.D_2_2( __t1, __t2)
#define ALIAS_clipSup_D_1_2(__t1, __t2) clipSup.D_1_2( __t1, __t2)
#define ALIAS_clipSup_D_1_1(__t1, __t2) clipSup.D_1_1( __t1, __t2)
#define ALIAS_negPart_DD(__t1) negPart.DD( __t1)
#define ALIAS_negPart_D(__t1) negPart.D( __t1)
#define ALIAS_posPart_DD(__t1) posPart.DD( __t1)
#define ALIAS_posPart_D(__t1) posPart.D( __t1)
#define ALIAS_v_min_DD(__t1) v_min.DD( __t1)
#define ALIAS_v_min_D(__t1) v_min.D( __t1)
#define ALIAS_LongSlipRear_max_DD(__t1) LongSlipRear_max.DD( __t1)
#define ALIAS_LongSlipRear_max_D(__t1) LongSlipRear_max.D( __t1)
#define ALIAS_LongSlipRear_min_DD(__t1) LongSlipRear_min.DD( __t1)
#define ALIAS_LongSlipRear_min_D(__t1) LongSlipRear_min.D( __t1)
#define ALIAS_OnlyTractionRear_DD(__t1) OnlyTractionRear.DD( __t1)
#define ALIAS_OnlyTractionRear_D(__t1) OnlyTractionRear.D( __t1)
#define ALIAS_OnlyBrakingRear_DD(__t1) OnlyBrakingRear.DD( __t1)
#define ALIAS_OnlyBrakingRear_D(__t1) OnlyBrakingRear.D( __t1)
#define ALIAS_p__oControl_D_3(__t1, __t2, __t3) p__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2(__t1, __t2, __t3) p__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1(__t1, __t2, __t3) p__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_3_3(__t1, __t2, __t3) p__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_3(__t1, __t2, __t3) p__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_2(__t1, __t2, __t3) p__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_3(__t1, __t2, __t3) p__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_2(__t1, __t2, __t3) p__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_1(__t1, __t2, __t3) p__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3(__t1, __t2, __t3) b__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2(__t1, __t2, __t3) b__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1(__t1, __t2, __t3) b__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3_3(__t1, __t2, __t3) b__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_3(__t1, __t2, __t3) b__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_2(__t1, __t2, __t3) b__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_3(__t1, __t2, __t3) b__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_2(__t1, __t2, __t3) b__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_1(__t1, __t2, __t3) b__oControl.D_1_1( __t1, __t2, __t3)


namespace TyreDynamicDefine {
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
  TyreDynamic::LongSlipRear( real_type xo___V ) const {
    real_type t2   = LongSlipRear_min(-1 - xo___V);
    real_type t4   = LongSlipRear_min(xo___V - 1);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_LongSlipRear( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::LongSlipRear_D( real_type xo___V ) const {
    real_type t2   = ALIAS_LongSlipRear_min_D(-1 - xo___V);
    real_type t4   = ALIAS_LongSlipRear_min_D(xo___V - 1);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_LongSlipRear_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::LongSlipRear_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_LongSlipRear_min_DD(-1 - xo___V);
    real_type t4   = ALIAS_LongSlipRear_min_DD(xo___V - 1);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_LongSlipRear_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::kappa__w( real_type xo__v, real_type xo__omega ) const {
    real_type result__ = 1.0 / xo__v * ModelPars[iM_rw] * xo__omega - 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa__w( v={}, omega={} ) return {}\n",
        xo__v, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::kappa__w_D_1( real_type xo__v, real_type xo__omega ) const {
    real_type t1   = xo__v * xo__v;
    real_type result__ = -xo__omega * ModelPars[iM_rw] / t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa__w_D_1( v={}, omega={} ) return {}\n",
        xo__v, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::kappa__w_D_1_1( real_type xo__v, real_type xo__omega ) const {
    real_type t1   = xo__v * xo__v;
    real_type result__ = 2 * xo__omega * ModelPars[iM_rw] / t1 / xo__v;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa__w_D_1_1( v={}, omega={} ) return {}\n",
        xo__v, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::kappa__w_D_1_2( real_type xo__v, real_type xo__omega ) const {
    real_type t1   = xo__v * xo__v;
    real_type result__ = -ModelPars[iM_rw] / t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa__w_D_1_2( v={}, omega={} ) return {}\n",
        xo__v, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::kappa__w_D_2( real_type xo__v, real_type xo__omega ) const {
    real_type result__ = 1.0 / xo__v * ModelPars[iM_rw];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa__w_D_2( v={}, omega={} ) return {}\n",
        xo__v, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::kappa__w_D_2_2( real_type xo__v, real_type xo__omega ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_kappa__w_D_2_2( v={}, omega={} ) return {}\n",
        xo__v, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::F__x( real_type xo__lambda ) const {
    real_type t6   = atan(xo__lambda * ModelPars[iM_Bx0]);
    real_type t9   = sin(ModelPars[iM_Cx0] * t6);
    real_type result__ = ModelPars[iM_mu__x0] * t9 * ModelPars[iM_g] * ModelPars[iM_m];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_F__x( lambda={} ) return {}\n",
        xo__lambda, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::F__x_D( real_type xo__lambda ) const {
    real_type t4   = ModelPars[iM_Bx0];
    real_type t6   = xo__lambda * xo__lambda;
    real_type t7   = t4 * t4;
    real_type t11  = ModelPars[iM_Cx0];
    real_type t14  = atan(t4 * xo__lambda);
    real_type t16  = cos(t11 * t14);
    real_type result__ = ModelPars[iM_mu__x0] * t16 * t11 / (t6 * t7 + 1) * t4 * ModelPars[iM_m] * ModelPars[iM_g];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_F__x_D( lambda={} ) return {}\n",
        xo__lambda, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::F__x_DD( real_type xo__lambda ) const {
    real_type t3   = ModelPars[iM_g] * ModelPars[iM_m];
    real_type t4   = ModelPars[iM_Bx0];
    real_type t5   = t4 * t4;
    real_type t7   = xo__lambda * xo__lambda;
    real_type t10  = pow(t5 * t7 + 1, 2);
    real_type t11  = 1.0 / t10;
    real_type t14  = ModelPars[iM_Cx0];
    real_type t16  = atan(t4 * xo__lambda);
    real_type t17  = t14 * t16;
    real_type t18  = cos(t17);
    real_type t20  = ModelPars[iM_mu__x0];
    real_type t26  = t14 * t14;
    real_type t28  = sin(t17);
    real_type result__ = -2 * xo__lambda * t20 * t18 * t14 * t11 * t5 * t4 * t3 - t20 * t28 * t26 * t11 * t5 * t3;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_F__x_DD( lambda={} ) return {}\n",
        xo__lambda, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::p__pos( real_type xo__p ) const {
    real_type result__ = posPart(xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p__pos( p={} ) return {}\n",
        xo__p, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::p__pos_D( real_type xo__p ) const {
    real_type result__ = ALIAS_posPart_D(xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p__pos_D( p={} ) return {}\n",
        xo__p, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::p__pos_DD( real_type xo__p ) const {
    real_type result__ = ALIAS_posPart_DD(xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p__pos_DD( p={} ) return {}\n",
        xo__p, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::p__neg( real_type xo__p ) const {
    real_type result__ = negPart(xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p__neg( p={} ) return {}\n",
        xo__p, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::p__neg_D( real_type xo__p ) const {
    real_type result__ = ALIAS_negPart_D(xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p__neg_D( p={} ) return {}\n",
        xo__p, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::p__neg_DD( real_type xo__p ) const {
    real_type result__ = ALIAS_negPart_DD(xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_p__neg_DD( p={} ) return {}\n",
        xo__p, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::b__pos( real_type xo__b ) const {
    real_type result__ = posPart(xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_b__pos( b={} ) return {}\n",
        xo__b, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::b__pos_D( real_type xo__b ) const {
    real_type result__ = ALIAS_posPart_D(xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_b__pos_D( b={} ) return {}\n",
        xo__b, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::b__pos_DD( real_type xo__b ) const {
    real_type result__ = ALIAS_posPart_DD(xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_b__pos_DD( b={} ) return {}\n",
        xo__b, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::b__neg( real_type xo__b ) const {
    real_type result__ = negPart(xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_b__neg( b={} ) return {}\n",
        xo__b, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::b__neg_D( real_type xo__b ) const {
    real_type result__ = ALIAS_negPart_D(xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_b__neg_D( b={} ) return {}\n",
        xo__b, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::b__neg_DD( real_type xo__b ) const {
    real_type result__ = ALIAS_negPart_DD(xo__b);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_b__neg_DD( b={} ) return {}\n",
        xo__b, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT__env( real_type xo__omega ) const {
    real_type t1   = abs_reg(xo__omega);
    real_type result__ = clipSup(ModelPars[iM_E__pow] / t1, ModelPars[iM_TT__max]);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT__env( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT__env_D( real_type xo__omega ) const {
    real_type t1   = abs_reg(xo__omega);
    real_type t3   = ModelPars[iM_E__pow];
    real_type t6   = ALIAS_clipSup_D_1(t3 / t1, ModelPars[iM_TT__max]);
    real_type t7   = t1 * t1;
    real_type t10  = ALIAS_abs_reg_D(xo__omega);
    real_type result__ = -t10 * t3 / t7 * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT__env_D( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT__env_DD( real_type xo__omega ) const {
    real_type t1   = abs_reg(xo__omega);
    real_type t3   = ModelPars[iM_E__pow];
    real_type t4   = t3 / t1;
    real_type t5   = ModelPars[iM_TT__max];
    real_type t6   = ALIAS_clipSup_D_1_1(t4, t5);
    real_type t7   = t1 * t1;
    real_type t8   = t7 * t7;
    real_type t11  = t3 * t3;
    real_type t12  = ALIAS_abs_reg_D(xo__omega);
    real_type t13  = t12 * t12;
    real_type t16  = ALIAS_clipSup_D_1(t4, t5);
    real_type t25  = ALIAS_abs_reg_DD(xo__omega);
    real_type result__ = t13 * t11 / t8 * t6 + 2 * t13 * t3 / t7 / t1 * t16 - t25 * t3 / t7 * t16;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT__env_DD( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::BT__env( real_type xo__omega ) const {
    real_type t4   = ModelPars[iM_BT__max];
    real_type t6   = clipSup(t4 / ModelPars[iM_BTv__max] * xo__omega, t4);
    real_type result__ = -t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BT__env( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::BT__env_D( real_type xo__omega ) const {
    real_type t2   = 1.0 / ModelPars[iM_BTv__max];
    real_type t4   = ModelPars[iM_BT__max];
    real_type t6   = ALIAS_clipSup_D_1(t4 * t2 * xo__omega, t4);
    real_type result__ = -t4 * t2 * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BT__env_D( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::BT__env_DD( real_type xo__omega ) const {
    real_type t1   = ModelPars[iM_BTv__max];
    real_type t4   = ModelPars[iM_BT__max];
    real_type t6   = ALIAS_clipSup_D_1_1(t4 / t1 * xo__omega, t4);
    real_type t7   = t1 * t1;
    real_type t10  = t4 * t4;
    real_type result__ = -t10 / t7 * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BT__env_DD( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT( real_type xo__p__pos, real_type xo__omega ) const {
    real_type t1   = TT__env(xo__omega);
    real_type t2   = BT__env(xo__omega);
    real_type result__ = xo__p__pos * (t1 - t2) + t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT( p__pos={}, omega={} ) return {}\n",
        xo__p__pos, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT_D_1( real_type xo__p__pos, real_type xo__omega ) const {
    real_type t1   = TT__env(xo__omega);
    real_type t2   = BT__env(xo__omega);
    real_type result__ = t1 - t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT_D_1( p__pos={}, omega={} ) return {}\n",
        xo__p__pos, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT_D_1_1( real_type xo__p__pos, real_type xo__omega ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT_D_1_1( p__pos={}, omega={} ) return {}\n",
        xo__p__pos, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT_D_1_2( real_type xo__p__pos, real_type xo__omega ) const {
    real_type t1   = TT__env_D(xo__omega);
    real_type t2   = BT__env_D(xo__omega);
    real_type result__ = t1 - t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT_D_1_2( p__pos={}, omega={} ) return {}\n",
        xo__p__pos, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT_D_2( real_type xo__p__pos, real_type xo__omega ) const {
    real_type t1   = TT__env_D(xo__omega);
    real_type t2   = BT__env_D(xo__omega);
    real_type result__ = xo__p__pos * (t1 - t2) + t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT_D_2( p__pos={}, omega={} ) return {}\n",
        xo__p__pos, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TT_D_2_2( real_type xo__p__pos, real_type xo__omega ) const {
    real_type t1   = TT__env_DD(xo__omega);
    real_type t2   = BT__env_DD(xo__omega);
    real_type result__ = xo__p__pos * (t1 - t2) + t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TT_D_2_2( p__pos={}, omega={} ) return {}\n",
        xo__p__pos, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TB( real_type xo__b__neg, real_type xo__omega ) const {
    real_type t1   = sign_reg(xo__omega);
    real_type result__ = xo__b__neg * ModelPars[iM_TB__max] * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TB( b__neg={}, omega={} ) return {}\n",
        xo__b__neg, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TB_D_1( real_type xo__b__neg, real_type xo__omega ) const {
    real_type t1   = sign_reg(xo__omega);
    real_type result__ = ModelPars[iM_TB__max] * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TB_D_1( b__neg={}, omega={} ) return {}\n",
        xo__b__neg, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TB_D_1_1( real_type xo__b__neg, real_type xo__omega ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TB_D_1_1( b__neg={}, omega={} ) return {}\n",
        xo__b__neg, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TB_D_1_2( real_type xo__b__neg, real_type xo__omega ) const {
    real_type t1   = ALIAS_sign_reg_D(xo__omega);
    real_type result__ = ModelPars[iM_TB__max] * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TB_D_1_2( b__neg={}, omega={} ) return {}\n",
        xo__b__neg, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TB_D_2( real_type xo__b__neg, real_type xo__omega ) const {
    real_type t1   = ALIAS_sign_reg_D(xo__omega);
    real_type result__ = xo__b__neg * ModelPars[iM_TB__max] * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TB_D_2( b__neg={}, omega={} ) return {}\n",
        xo__b__neg, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::TB_D_2_2( real_type xo__b__neg, real_type xo__omega ) const {
    real_type t1   = ALIAS_sign_reg_DD(xo__omega);
    real_type result__ = xo__b__neg * ModelPars[iM_TB__max] * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_TB_D_2_2( b__neg={}, omega={} ) return {}\n",
        xo__b__neg, xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::Fa( real_type xo__v ) const {
    real_type t1   = xo__v * xo__v;
    real_type result__ = ModelPars[iM_rho_a] * ModelPars[iM_kD] * t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Fa( v={} ) return {}\n",
        xo__v, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::Fa_D( real_type xo__v ) const {
    real_type result__ = xo__v * ModelPars[iM_kD] * ModelPars[iM_rho_a];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Fa_D( v={} ) return {}\n",
        xo__v, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::Fa_DD( real_type xo__v ) const {
    real_type result__ = ModelPars[iM_kD] * ModelPars[iM_rho_a];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Fa_DD( v={} ) return {}\n",
        xo__v, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::Ma( real_type xo__omega ) const {
    real_type t1   = xo__omega * xo__omega;
    real_type t2   = sign_reg(xo__omega);
    real_type result__ = -ModelPars[iM_kDo] * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ma( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::Ma_D( real_type xo__omega ) const {
    real_type t1   = sign_reg(xo__omega);
    real_type t3   = ModelPars[iM_kDo];
    real_type t6   = xo__omega * xo__omega;
    real_type t7   = ALIAS_sign_reg_D(xo__omega);
    real_type result__ = -2 * t3 * t1 * xo__omega - t3 * t7 * t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ma_D( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

  real_type
  TyreDynamic::Ma_DD( real_type xo__omega ) const {
    real_type t1   = sign_reg(xo__omega);
    real_type t2   = ModelPars[iM_kDo];
    real_type t5   = ALIAS_sign_reg_D(xo__omega);
    real_type t9   = xo__omega * xo__omega;
    real_type t10  = ALIAS_sign_reg_DD(xo__omega);
    real_type result__ = -t2 * t10 * t9 - 4 * t2 * t5 * xo__omega - 2 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ma_DD( omega={} ) return {}\n",
        xo__omega, result__
      );
    }
    return result__;
  }

}

// EOF: TyreDynamic_Methods_UserFunctions.cc
