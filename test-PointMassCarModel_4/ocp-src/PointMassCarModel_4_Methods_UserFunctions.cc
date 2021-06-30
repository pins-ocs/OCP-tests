/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_UserFunctions.cc                   |
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


#include "PointMassCarModel_4.hh"
#include "PointMassCarModel_4_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Road2D;


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
#define ALIAS_yR_R(__t1) segmentRight.iso_right_y( __t1)
#define ALIAS_yR_L(__t1) segmentLeft.iso_right_y( __t1)
#define ALIAS_yR(__t1) segment.iso_right_y( __t1)
#define ALIAS_xR_R(__t1) segmentRight.iso_right_x( __t1)
#define ALIAS_xR_L(__t1) segmentLeft.iso_right_x( __t1)
#define ALIAS_xR(__t1) segment.iso_right_x( __t1)
#define ALIAS_yL_R(__t1) segmentRight.iso_left_y( __t1)
#define ALIAS_yL_L(__t1) segmentLeft.iso_left_y( __t1)
#define ALIAS_yL(__t1) segment.iso_left_y( __t1)
#define ALIAS_xL_R(__t1) segmentRight.iso_left_x( __t1)
#define ALIAS_xL_L(__t1) segmentLeft.iso_left_x( __t1)
#define ALIAS_xL(__t1) segment.iso_left_x( __t1)
#define ALIAS_theta_R_DD(__t1) segmentRight.iso_angle_DD( __t1)
#define ALIAS_theta_R_D(__t1) segmentRight.iso_angle_D( __t1)
#define ALIAS_theta_R(__t1) segmentRight.iso_angle( __t1)
#define ALIAS_theta_L_DD(__t1) segmentLeft.iso_angle_DD( __t1)
#define ALIAS_theta_L_D(__t1) segmentLeft.iso_angle_D( __t1)
#define ALIAS_theta_L(__t1) segmentLeft.iso_angle( __t1)
#define ALIAS_theta_DD(__t1) segment.iso_angle_DD( __t1)
#define ALIAS_theta_D(__t1) segment.iso_angle_D( __t1)
#define ALIAS_theta(__t1) segment.iso_angle( __t1)
#define ALIAS_yLane_R_DD(__t1) segmentRight.iso_y_DD( __t1)
#define ALIAS_yLane_R_D(__t1) segmentRight.iso_y_D( __t1)
#define ALIAS_yLane_R(__t1) segmentRight.iso_y( __t1)
#define ALIAS_yLane_L_DD(__t1) segmentLeft.iso_y_DD( __t1)
#define ALIAS_yLane_L_D(__t1) segmentLeft.iso_y_D( __t1)
#define ALIAS_yLane_L(__t1) segmentLeft.iso_y( __t1)
#define ALIAS_yLane_DD(__t1) segment.iso_y_DD( __t1)
#define ALIAS_yLane_D(__t1) segment.iso_y_D( __t1)
#define ALIAS_yLane(__t1) segment.iso_y( __t1)
#define ALIAS_xLane_R_DD(__t1) segmentRight.iso_x_DD( __t1)
#define ALIAS_xLane_R_D(__t1) segmentRight.iso_x_D( __t1)
#define ALIAS_xLane_R(__t1) segmentRight.iso_x( __t1)
#define ALIAS_xLane_L_DD(__t1) segmentLeft.iso_x_DD( __t1)
#define ALIAS_xLane_L_D(__t1) segmentLeft.iso_x_D( __t1)
#define ALIAS_xLane_L(__t1) segmentLeft.iso_x( __t1)
#define ALIAS_xLane_DD(__t1) segment.iso_x_DD( __t1)
#define ALIAS_xLane_D(__t1) segment.iso_x_D( __t1)
#define ALIAS_xLane(__t1) segment.iso_x( __t1)
#define ALIAS_rightWidth_R_DD(__t1) segmentRight.right_width_DD( __t1)
#define ALIAS_rightWidth_R_D(__t1) segmentRight.right_width_D( __t1)
#define ALIAS_rightWidth_R(__t1) segmentRight.right_width( __t1)
#define ALIAS_rightWidth_L_DD(__t1) segmentLeft.right_width_DD( __t1)
#define ALIAS_rightWidth_L_D(__t1) segmentLeft.right_width_D( __t1)
#define ALIAS_rightWidth_L(__t1) segmentLeft.right_width( __t1)
#define ALIAS_rightWidth_DD(__t1) segment.right_width_DD( __t1)
#define ALIAS_rightWidth_D(__t1) segment.right_width_D( __t1)
#define ALIAS_rightWidth(__t1) segment.right_width( __t1)
#define ALIAS_leftWidth_R_DD(__t1) segmentRight.left_width_DD( __t1)
#define ALIAS_leftWidth_R_D(__t1) segmentRight.left_width_D( __t1)
#define ALIAS_leftWidth_R(__t1) segmentRight.left_width( __t1)
#define ALIAS_leftWidth_L_DD(__t1) segmentLeft.left_width_DD( __t1)
#define ALIAS_leftWidth_L_D(__t1) segmentLeft.left_width_D( __t1)
#define ALIAS_leftWidth_L(__t1) segmentLeft.left_width( __t1)
#define ALIAS_leftWidth_DD(__t1) segment.left_width_DD( __t1)
#define ALIAS_leftWidth_D(__t1) segment.left_width_D( __t1)
#define ALIAS_leftWidth(__t1) segment.left_width( __t1)
#define ALIAS_yV_R(__t1, __t2) segmentRight.iso_y( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.iso_y( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.iso_y( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.iso_x( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.iso_x( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.iso_x( __t1, __t2)
#define ALIAS_Kappa_R_DD(__t1) segmentRight.iso_curvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.iso_curvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.iso_curvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.iso_curvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.iso_curvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.iso_curvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.iso_curvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.iso_curvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.iso_curvature( __t1)
#define ALIAS_ssSegmentMax_R(___dummy___) segmentRight.ss_segment_max()
#define ALIAS_ssSegmentMax_L(___dummy___) segmentLeft.ss_segment_max()
#define ALIAS_ssSegmentMax(___dummy___) segment.ss_segment_max()
#define ALIAS_ssSegmentMin_R(___dummy___) segmentRight.ss_segment_min()
#define ALIAS_ssSegmentMin_L(___dummy___) segmentLeft.ss_segment_min()
#define ALIAS_ssSegmentMin(___dummy___) segment.ss_segment_min()
#define ALIAS_L_R(___dummy___) segmentRight.length()
#define ALIAS_L_L(___dummy___) segmentLeft.length()
#define ALIAS_L(___dummy___) segment.length()
#define ALIAS_PowerLimit_DD(__t1) PowerLimit.DD( __t1)
#define ALIAS_PowerLimit_D(__t1) PowerLimit.D( __t1)
#define ALIAS_RoadRightBorder_DD(__t1) RoadRightBorder.DD( __t1)
#define ALIAS_RoadRightBorder_D(__t1) RoadRightBorder.D( __t1)
#define ALIAS_RoadLeftBorder_DD(__t1) RoadLeftBorder.DD( __t1)
#define ALIAS_RoadLeftBorder_D(__t1) RoadLeftBorder.D( __t1)
#define ALIAS_AdherenceEllipse_DD(__t1) AdherenceEllipse.DD( __t1)
#define ALIAS_AdherenceEllipse_D(__t1) AdherenceEllipse.D( __t1)
#define ALIAS_v__OmegaControl_D_3(__t1, __t2, __t3) v__OmegaControl.D_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_2(__t1, __t2, __t3) v__OmegaControl.D_2( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1(__t1, __t2, __t3) v__OmegaControl.D_1( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_3_3(__t1, __t2, __t3) v__OmegaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_2_3(__t1, __t2, __t3) v__OmegaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_2_2(__t1, __t2, __t3) v__OmegaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1_3(__t1, __t2, __t3) v__OmegaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1_2(__t1, __t2, __t3) v__OmegaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1_1(__t1, __t2, __t3) v__OmegaControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_3(__t1, __t2, __t3) v__fxControl.D_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_2(__t1, __t2, __t3) v__fxControl.D_2( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1(__t1, __t2, __t3) v__fxControl.D_1( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_3_3(__t1, __t2, __t3) v__fxControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_2_3(__t1, __t2, __t3) v__fxControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_2_2(__t1, __t2, __t3) v__fxControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1_3(__t1, __t2, __t3) v__fxControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1_2(__t1, __t2, __t3) v__fxControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1_1(__t1, __t2, __t3) v__fxControl.D_1_1( __t1, __t2, __t3)


namespace PointMassCarModel_4Define {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  PointMassCarModel_4::zeta__dot( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type result__ = 1.0 / (-xo__n * xo__Kappa + 1) * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_1( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type result__ = 1.0 / (-xo__n * xo__Kappa + 1) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_1( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_1_1( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_1_1( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_1_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = sin(xo__alpha);
    real_type result__ = 1.0 / (xo__n * xo__Kappa - 1) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_1_2( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_1_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t5   = pow(xo__n * xo__Kappa - 1, 2);
    real_type result__ = 1.0 / t5 * xo__Kappa * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_1_3( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_1_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t5   = pow(xo__n * xo__Kappa - 1, 2);
    real_type result__ = 1.0 / t5 * xo__n * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_1_4( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = sin(xo__alpha);
    real_type result__ = 1.0 / (xo__n * xo__Kappa - 1) * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_2( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_2_2( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type result__ = 1.0 / (xo__n * xo__Kappa - 1) * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_2_2( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_2_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = sin(xo__alpha);
    real_type t5   = pow(xo__n * xo__Kappa - 1, 2);
    real_type result__ = -xo__Kappa / t5 * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_2_3( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_2_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = sin(xo__alpha);
    real_type t5   = pow(xo__n * xo__Kappa - 1, 2);
    real_type result__ = -xo__n / t5 * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_2_4( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t5   = pow(xo__n * xo__Kappa - 1, 2);
    real_type result__ = xo__Kappa / t5 * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_3( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_3_3( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t3   = xo__Kappa * xo__Kappa;
    real_type t5   = xo__n * xo__Kappa - 1;
    real_type t6   = t5 * t5;
    real_type result__ = -2 / t6 / t5 * t3 * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_3_3( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_3_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t3   = xo__n * xo__Kappa;
    real_type t5   = t3 - 1;
    real_type t6   = t5 * t5;
    real_type result__ = -1.0 / t6 / t5 * (t3 + 1) * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_3_4( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t5   = pow(xo__n * xo__Kappa - 1, 2);
    real_type result__ = xo__n / t5 * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_4( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

  real_type
  PointMassCarModel_4::zeta__dot_D_4_4( real_type xo__V, real_type xo__alpha, real_type xo__n, real_type xo__Kappa ) const {
    real_type t1   = cos(xo__alpha);
    real_type t3   = xo__n * xo__n;
    real_type t5   = xo__n * xo__Kappa - 1;
    real_type t6   = t5 * t5;
    real_type result__ = -2 / t6 / t5 * t3 * t1 * xo__V;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_zeta__dot_D_4_4( V={}, alpha={}, n={}, Kappa={} ) return {}\n",
        xo__V, xo__alpha, xo__n, xo__Kappa, result__
      );
    }
    return result__;
  }

}

// EOF: PointMassCarModel_4_Methods_UserFunctions.cc
