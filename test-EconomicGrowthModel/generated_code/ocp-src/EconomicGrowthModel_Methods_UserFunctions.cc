/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Methods_UserFunctions.cc                   |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "EconomicGrowthModel.hh"
#include "EconomicGrowthModel_Pars.hh"
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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModelDefine {
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
  EconomicGrowthModel::Q( real_type xo__x, real_type xo__y ) const {
    real_type result__ = xo__x * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Q( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::Q_D_1( real_type xo__x, real_type xo__y ) const {
    real_type result__ = xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Q_D_1( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::Q_D_1_1( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Q_D_1_1( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::Q_D_1_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Q_D_1_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::Q_D_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = xo__x;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Q_D_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::Q_D_2_2( real_type xo__x, real_type xo__y ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Q_D_2_2( x={}, y={} ) return {}\n",
        xo__x, xo__y, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x1L( real_type xo__t ) const {
    real_type t4   = exp(ModelPars[iM_x2_i] * xo__t);
    real_type result__ = t4 * ModelPars[iM_x1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x1L( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x1L_D( real_type xo__t ) const {
    real_type t2   = ModelPars[iM_x2_i];
    real_type t5   = exp(xo__t * t2);
    real_type result__ = t5 * t2 * ModelPars[iM_x1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x1L_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x1L_DD( real_type xo__t ) const {
    real_type t2   = ModelPars[iM_x2_i];
    real_type t3   = t2 * t2;
    real_type t6   = exp(xo__t * t2);
    real_type result__ = t6 * t3 * ModelPars[iM_x1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x1L_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x2L( real_type xo__t ) const {
    real_type result__ = ModelPars[iM_x2_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x2L( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x2L_D( real_type xo__t ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x2L_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x2L_DD( real_type xo__t ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x2L_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l1L( real_type xo__t ) const {
    real_type t4   = exp(-ModelPars[iM_x2_i] * xo__t);
    real_type result__ = t4 * ModelPars[iM_l1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l1L( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l1L_D( real_type xo__t ) const {
    real_type t2   = ModelPars[iM_x2_i];
    real_type t5   = exp(-xo__t * t2);
    real_type result__ = -t5 * t2 * ModelPars[iM_l1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l1L_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l1L_DD( real_type xo__t ) const {
    real_type t2   = ModelPars[iM_x2_i];
    real_type t3   = t2 * t2;
    real_type t6   = exp(-xo__t * t2);
    real_type result__ = t6 * t3 * ModelPars[iM_l1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l1L_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l2L( real_type xo__t ) const {
    real_type result__ = -xo__t * ModelPars[iM_l1_i] * ModelPars[iM_x1_i] + ModelPars[iM_l2_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l2L( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l2L_D( real_type xo__t ) const {
    real_type result__ = -ModelPars[iM_l1_i] * ModelPars[iM_x1_i];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l2L_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l2L_DD( real_type xo__t ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l2L_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x1R( real_type xo__t ) const {
    real_type t1   = ModelPars[iM_x2_i];
    real_type result__ = 1.0 / (1 + (ModelPars[iM_t0] - xo__t) * t1 / 2) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x1R( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x1R_D( real_type xo__t ) const {
    real_type t1   = ModelPars[iM_x2_i];
    real_type t2   = t1 * t1;
    real_type t8   = pow(1 + (ModelPars[iM_t0] - xo__t) * t1 / 2, 2);
    real_type result__ = 1.0 / t8 * t2 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x1R_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x1R_DD( real_type xo__t ) const {
    real_type t1   = ModelPars[iM_x2_i];
    real_type t2   = t1 * t1;
    real_type t8   = 1 + (ModelPars[iM_t0] - xo__t) * t1 / 2;
    real_type t9   = t8 * t8;
    real_type result__ = 1.0 / t9 / t8 * t2 * t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x1R_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x2R( real_type xo__t ) const {
    real_type result__ = x1R(xo__t);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x2R( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x2R_D( real_type xo__t ) const {
    real_type result__ = x1R_D(xo__t);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x2R_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::x2R_DD( real_type xo__t ) const {
    real_type result__ = x1R_DD(xo__t);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_x2R_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l1R( real_type xo__t ) const {
    real_type t1   = ModelPars[iM_t0];
    real_type t2   = l1L(t1);
    real_type t8   = pow((xo__t - t1) * ModelPars[iM_x2_i] / 2 - 1, 2);
    real_type result__ = t8 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l1R( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l1R_D( real_type xo__t ) const {
    real_type t1   = ModelPars[iM_t0];
    real_type t2   = l1L(t1);
    real_type t3   = ModelPars[iM_x2_i];
    real_type result__ = t3 * ((xo__t - t1) * t3 / 2 - 1) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l1R_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l1R_DD( real_type xo__t ) const {
    real_type t2   = l1L(ModelPars[iM_t0]);
    real_type t4   = ModelPars[iM_x2_i] * ModelPars[iM_x2_i];
    real_type result__ = t4 * t2 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l1R_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l2R( real_type xo__t ) const {
    real_type result__ = l1R(xo__t);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l2R( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l2R_D( real_type xo__t ) const {
    real_type result__ = l1R_D(xo__t);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l2R_D( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

  real_type
  EconomicGrowthModel::l2R_DD( real_type xo__t ) const {
    real_type result__ = l1R_DD(xo__t);
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_l2R_DD( t={} ) return {}\n",
        xo__t, result__
      );
    }
    return result__;
  }

}

// EOF: EconomicGrowthModel_Methods_UserFunctions.cc
