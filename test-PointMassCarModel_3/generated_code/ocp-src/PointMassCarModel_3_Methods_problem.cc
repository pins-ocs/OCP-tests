/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_problem.cc                         |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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


#include "PointMassCarModel_3.hh"
#include "PointMassCarModel_3_Pars.hh"

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


namespace PointMassCarModel_3Define {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_3::continuation_step_0( real_type s ) {
    real_type t1   = ModelPars[iM_wT0];
    ModelPars[iM_wT] = t1 + (ModelPars[iM_wT1] - t1) * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_3::continuation_step_1( real_type s ) {
    real_type t1   = ModelPars[iM_p_epsi0];
    real_type t5   = t1 + (ModelPars[iM_p_epsi1] - t1) * s;
    AdherenceEllipse.update_epsilon(t5);
    RoadRightBorder.update_epsilon(t5);
    RoadLeftBorder.update_epsilon(t5);
    PowerLimit.update_epsilon(t5);
    real_type t6   = ModelPars[iM_up_epsi0];
    real_type t10  = t6 + (ModelPars[iM_up_epsi1] - t6) * s;
    v__fxControl.update_epsilon(t10);
    v__OmegaControl.update_epsilon(t10);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  PointMassCarModel_3::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[iX_Omega];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = AdherenceEllipse(t11 / t6 * t4 + t11 / t19 * t16 * t14 - 1);
    real_type t26  = X__[iX_n];
    real_type t27  = X__[iX_s];
    real_type t28  = ALIAS_leftWidth(t27);
    real_type t30  = RoadLeftBorder(t26 - t28);
    real_type t32  = ALIAS_rightWidth(t27);
    real_type t34  = RoadRightBorder(-t26 - t32);
    real_type t43  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15 - 1);
    real_type t48  = X__[iX_alpha];
    real_type t49  = ALIAS_Kappa(t27);
    real_type t50  = zeta__dot(t15, t48, t26, t49);
    real_type t55  = sin(t48);
    real_type result__ = t24 * t2 + t30 * t2 + t34 * t2 + t43 * t2 + t2 * ModelPars[iM_wT] + t2 * t50 * L__[iL_lambda1__xo] + t2 * t55 * t15 * L__[iL_lambda2__xo] + (-t49 * t50 + t13) * t2 * L__[iL_lambda3__xo] + (-t16 * ModelPars[iM_kD] + t3) * t2 * L__[iL_lambda4__xo] + t2 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo] * U__[iU_v__Omega] + t2 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo] * U__[iU_v__fx];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  PointMassCarModel_3::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JP_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_3::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t4   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t7   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type result__ = t4 * t2 + t7 * t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_3::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t14  = X__[iX_Omega] * X__[iX_Omega];
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = AdherenceEllipse(t11 / t6 * t4 + t11 / t19 * t16 * t14 - 1);
    real_type t26  = X__[iX_n];
    real_type t27  = X__[iX_s];
    real_type t28  = ALIAS_leftWidth(t27);
    real_type t30  = RoadLeftBorder(t26 - t28);
    real_type t32  = ALIAS_rightWidth(t27);
    real_type t34  = RoadRightBorder(-t26 - t32);
    real_type t43  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15 - 1);
    real_type result__ = t24 * t2 + t30 * t2 + t34 * t2 + t43 * t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "LT_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  PointMassCarModel_3::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type result__ = t3 * ModelPars[iM_wT];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  PointMassCarModel_3::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::DmayerDxxp_numEqns() const { return 14; }

  void
  PointMassCarModel_3::DmayerDxxp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 14, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer PointMassCarModel_3::DlagrangeDxup_numEqns() const { return 9; }

  void
  PointMassCarModel_3::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 2 * ModelPars[iM_wT] * X__[iX_sqrt_inv_Vseg];
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 9, i_segment );
  }

  /*\
   |   ___ ____   ___  ____ _____
   |  |_ _|  _ \ / _ \|  _ \_   _|
   |   | || |_) | | | | |_) || |
   |   | ||  __/| |_| |  __/ | |
   |  |___|_|    \___/|_|    |_|
  \*/
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::IPOPT_hess_numRows() const { return 9; }
  integer PointMassCarModel_3::IPOPT_hess_numCols() const { return 9; }
  integer PointMassCarModel_3::IPOPT_hess_nnz()     const { return 33; }

  void
  PointMassCarModel_3::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 3   ; jIndex[15] = 0   ;
    iIndex[16] = 3   ; jIndex[16] = 1   ;
    iIndex[17] = 3   ; jIndex[17] = 2   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 6   ;
    iIndex[20] = 4   ; jIndex[20] = 6   ;
    iIndex[21] = 5   ; jIndex[21] = 6   ;
    iIndex[22] = 6   ; jIndex[22] = 0   ;
    iIndex[23] = 6   ; jIndex[23] = 1   ;
    iIndex[24] = 6   ; jIndex[24] = 2   ;
    iIndex[25] = 6   ; jIndex[25] = 3   ;
    iIndex[26] = 6   ; jIndex[26] = 4   ;
    iIndex[27] = 6   ; jIndex[27] = 5   ;
    iIndex[28] = 6   ; jIndex[28] = 6   ;
    iIndex[29] = 6   ; jIndex[29] = 7   ;
    iIndex[30] = 6   ; jIndex[30] = 8   ;
    iIndex[31] = 7   ; jIndex[31] = 6   ;
    iIndex[32] = 8   ; jIndex[32] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::IPOPT_hess_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            sigma__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = X__[iX_s];
    real_type t6   = ALIAS_Kappa(t5);
    real_type t7   = zeta__dot_D_4_4(t2, t3, t4, t6);
    real_type t9   = ALIAS_Kappa_D(t5);
    real_type t10  = t9 * t9;
    real_type t11  = X__[iX_sqrt_inv_Vseg];
    real_type t12  = t11 * t11;
    real_type t15  = zeta__dot_D_4(t2, t3, t4, t6);
    real_type t16  = t15 * t1;
    real_type t17  = ALIAS_Kappa_DD(t5);
    real_type t20  = L__[iL_lambda3__xo];
    real_type t21  = t12 * t20;
    real_type t28  = zeta__dot(t2, t3, t4, t6);
    result__[ 0   ] = t12 * t10 * t7 * t1 + t12 * t17 * t16 + (-t6 * t10 * t7 - t6 * t17 * t15 - 2 * t10 * t15 - t17 * t28) * t21;
    real_type t32  = zeta__dot_D_3_4(t2, t3, t4, t6);
    real_type t34  = t12 * t9;
    real_type t38  = zeta__dot_D_3(t2, t3, t4, t6);
    result__[ 1   ] = t34 * t32 * t1 + (-t6 * t9 * t32 - t9 * t38) * t21;
    real_type t42  = zeta__dot_D_2_4(t2, t3, t4, t6);
    real_type t47  = zeta__dot_D_2(t2, t3, t4, t6);
    result__[ 2   ] = t34 * t42 * t1 + (-t6 * t9 * t42 - t9 * t47) * t21;
    real_type t51  = zeta__dot_D_1_4(t2, t3, t4, t6);
    real_type t56  = zeta__dot_D_1(t2, t3, t4, t6);
    result__[ 3   ] = t34 * t51 * t1 + (-t6 * t9 * t51 - t9 * t56) * t21;
    real_type t62  = t11 * t20;
    result__[ 4   ] = 2 * t11 * t9 * t16 + 2 * (-t6 * t9 * t15 - t9 * t28) * t62;
    result__[ 5   ] = result__[1];
    real_type t69  = zeta__dot_D_3_3(t2, t3, t4, t6);
    result__[ 6   ] = t12 * t69 * t1 - t6 * t69 * t21;
    real_type t74  = zeta__dot_D_2_3(t2, t3, t4, t6);
    result__[ 7   ] = t12 * t74 * t1 - t6 * t74 * t21;
    real_type t79  = zeta__dot_D_1_3(t2, t3, t4, t6);
    result__[ 8   ] = t12 * t79 * t1 - t6 * t79 * t21;
    result__[ 9   ] = 2 * t11 * t38 * t1 - 2 * t6 * t38 * t62;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t89  = zeta__dot_D_2_2(t2, t3, t4, t6);
    real_type t92  = L__[iL_lambda2__xo];
    real_type t93  = t2 * t92;
    real_type t94  = sin(t3);
    result__[ 12  ] = t12 * t89 * t1 - t12 * t94 * t93 - t6 * t89 * t21;
    real_type t99  = zeta__dot_D_1_2(t2, t3, t4, t6);
    real_type t102 = cos(t3);
    result__[ 13  ] = t12 * t99 * t1 + t12 * t102 * t92 - t6 * t99 * t21;
    result__[ 14  ] = 2 * t11 * t47 * t1 + 2 * t11 * t102 * t93 - 2 * t6 * t47 * t62;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t114 = zeta__dot_D_1_1(t2, t3, t4, t6);
    real_type t119 = L__[iL_lambda4__xo];
    real_type t121 = ModelPars[iM_kD];
    result__[ 18  ] = t12 * t114 * t1 - t6 * t114 * t21 - 2 * t121 * t12 * t119;
    real_type t133 = t11 * t119;
    result__[ 19  ] = 2 * t11 * t56 * t1 + 2 * t11 * t94 * t92 - 4 * t2 * t121 * t133 - 2 * t6 * t56 * t62;
    result__[ 20  ] = 2 * t62;
    result__[ 21  ] = 2 * t133;
    result__[ 22  ] = result__[4];
    result__[ 23  ] = result__[9];
    result__[ 24  ] = result__[14];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[21];
    real_type t145 = t2 * t2;
    real_type t150 = L__[iL_lambda5__xo];
    real_type t153 = ModelPars[iM_v__Omega__max];
    real_type t155 = L__[iL_lambda6__xo];
    real_type t158 = ModelPars[iM_v__fx__max];
    result__[ 28  ] = 2 * sigma__ * ModelPars[iM_wT] + 2 * t28 * t1 + 2 * t94 * t93 + 2 * (-t6 * t28 + X__[iX_Omega]) * t20 + 2 * (-t145 * t121 + X__[iX_fx]) * t119 + 2 * t153 * U__[iU_v__Omega] * t150 + 2 * t158 * U__[iU_v__fx] * t155;
    result__[ 29  ] = 2 * t11 * t158 * t155;
    result__[ 30  ] = 2 * t11 * t153 * t150;
    result__[ 31  ] = result__[29];
    result__[ 32  ] = result__[30];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 33, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  PointMassCarModel_3::q_numEqns() const
  { return 4; }

  void
  PointMassCarModel_3::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
    result__[ 1   ] = ALIAS_L();
    result__[ 2   ] = ALIAS_ssSegmentMin();
    result__[ 3   ] = ALIAS_ssSegmentMax();
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer PointMassCarModel_3::segmentLink_numEqns() const { return 0; }

  void
  PointMassCarModel_3::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::DsegmentLinkDxp_numRows() const { return 0; }
  integer PointMassCarModel_3::DsegmentLinkDxp_numCols() const { return 0; }
  integer PointMassCarModel_3::DsegmentLinkDxp_nnz() const { return 0; }

  void
  PointMassCarModel_3::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer PointMassCarModel_3::jump_numEqns() const { return 14; }

  void
  PointMassCarModel_3::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_s] - QL__[iQ_zeta];
    result__[ 1   ] = XR__[iX_n] - XL__[iX_n];
    result__[ 2   ] = XR__[iX_alpha] - XL__[iX_alpha];
    result__[ 3   ] = XR__[iX_V] - XL__[iX_V];
    result__[ 4   ] = XR__[iX_Omega] - XL__[iX_Omega];
    result__[ 5   ] = XR__[iX_fx] - XL__[iX_fx];
    result__[ 6   ] = LL__[iL_lambda7__xo];
    result__[ 7   ] = XR__[iX_s] - QR__[iQ_zeta];
    result__[ 8   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 9   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 10  ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 11  ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    result__[ 12  ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo];
    result__[ 13  ] = LR__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 14, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DjumpDxlxlp_numRows() const { return 14; }
  integer PointMassCarModel_3::DjumpDxlxlp_numCols() const { return 28; }
  integer PointMassCarModel_3::DjumpDxlxlp_nnz()     const { return 24; }

  void
  PointMassCarModel_3::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 15  ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 16  ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 17  ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 18  ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 5   ;
    iIndex[10] = 5   ; jIndex[10] = 19  ;
    iIndex[11] = 6   ; jIndex[11] = 13  ;
    iIndex[12] = 7   ; jIndex[12] = 14  ;
    iIndex[13] = 8   ; jIndex[13] = 8   ;
    iIndex[14] = 8   ; jIndex[14] = 22  ;
    iIndex[15] = 9   ; jIndex[15] = 9   ;
    iIndex[16] = 9   ; jIndex[16] = 23  ;
    iIndex[17] = 10  ; jIndex[17] = 10  ;
    iIndex[18] = 10  ; jIndex[18] = 24  ;
    iIndex[19] = 11  ; jIndex[19] = 11  ;
    iIndex[20] = 11  ; jIndex[20] = 25  ;
    iIndex[21] = 12  ; jIndex[21] = 12  ;
    iIndex[22] = 12  ; jIndex[22] = 26  ;
    iIndex[23] = 13  ; jIndex[23] = 27  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    result__[ 5   ] = -1;
    result__[ 6   ] = 1;
    result__[ 7   ] = -1;
    result__[ 8   ] = 1;
    result__[ 9   ] = -1;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    result__[ 12  ] = 1;
    result__[ 13  ] = -1;
    result__[ 14  ] = 1;
    result__[ 15  ] = -1;
    result__[ 16  ] = 1;
    result__[ 17  ] = -1;
    result__[ 18  ] = 1;
    result__[ 19  ] = -1;
    result__[ 20  ] = 1;
    result__[ 21  ] = -1;
    result__[ 22  ] = 1;
    result__[ 23  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 24, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer PointMassCarModel_3::post_numEqns() const { return 24; }

  void
  PointMassCarModel_3::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = v__fxControl(U__[iU_v__fx], -1, 1);
    result__[ 1   ] = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t5   = ModelPars[iM_mu__x__max];
    real_type t6   = t5 * t5;
    real_type t9   = ModelPars[iM_g];
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[iX_Omega];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t18  = ModelPars[iM_mu__y__max];
    real_type t19  = t18 * t18;
    result__[ 2   ] = AdherenceEllipse(t11 / t6 * t4 + t11 / t19 * t16 * t14 - 1);
    real_type t24  = X__[iX_n];
    real_type t25  = X__[iX_s];
    real_type t26  = ALIAS_leftWidth(t25);
    result__[ 3   ] = RoadLeftBorder(t24 - t26);
    real_type t28  = ALIAS_rightWidth(t25);
    result__[ 4   ] = RoadRightBorder(-t24 - t28);
    result__[ 5   ] = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15 - 1);
    result__[ 6   ] = ALIAS_Kappa(t25);
    result__[ 7   ] = t26;
    result__[ 8   ] = t28;
    result__[ 9   ] = ALIAS_xLane(t25);
    result__[ 10  ] = ALIAS_yLane(t25);
    result__[ 11  ] = ALIAS_theta(t25);
    result__[ 12  ] = ALIAS_xV(t25, t24);
    result__[ 13  ] = ALIAS_yV(t25, t24);
    result__[ 14  ] = ALIAS_xL(t25);
    result__[ 15  ] = ALIAS_yL(t25);
    result__[ 16  ] = ALIAS_xR(t25);
    result__[ 17  ] = ALIAS_yR(t25);
    result__[ 18  ] = t15 * t13;
    real_type t39  = 1.0 / t9;
    result__[ 19  ] = t39 / t5 * t3;
    result__[ 20  ] = t39 / t18 * result__[18];
    real_type t43  = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    result__[ 21  ] = 1.0 / t43;
    result__[ 22  ] = result__[21] * Q__[iQ_L];
    result__[ 23  ] = zeta__dot(t15, X__[iX_alpha], t24, result__[6]);
    Mechatronix::check_in_segment( result__, "post_eval", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::integrated_post_numEqns() const { return 1; }

  void
  PointMassCarModel_3::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: PointMassCarModel_3_Methods_problem.cc
