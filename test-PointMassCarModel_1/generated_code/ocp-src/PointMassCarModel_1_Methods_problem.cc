/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_problem.cc                         |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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


#include "PointMassCarModel_1.hh"
#include "PointMassCarModel_1_Pars.hh"

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
#define ALIAS_yV_R(__t1, __t2) segmentRight.iso_y( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.iso_y( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.iso_y( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.iso_x( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.iso_x( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.iso_x( __t1, __t2)
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
#define ALIAS_Kappa_R_DD(__t1) segmentRight.iso_curvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.iso_curvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.iso_curvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.iso_curvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.iso_curvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.iso_curvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.iso_curvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.iso_curvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.iso_curvature( __t1)
#define ALIAS_LimitMinSpeed_DD(__t1) LimitMinSpeed.DD( __t1)
#define ALIAS_LimitMinSpeed_D(__t1) LimitMinSpeed.D( __t1)
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


namespace PointMassCarModel_1Define {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_1::continuation_step_0( real_type s ) {
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
  PointMassCarModel_1::continuation_step_1( real_type s ) {
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
  PointMassCarModel_1::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot(t1, t2, t3, t4);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t16  = X__[iX_Omega];
    real_type t17  = t16 * t16;
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t26  = AdherenceEllipse(1 - t14 / t9 * t7 - t14 / t21 * t18 * t17);
    real_type t30  = RoadLeftBorder(Q__[iQ_leftWidth] - t3);
    real_type t34  = RoadRightBorder(Q__[iQ_rightWidth] + t3);
    real_type t43  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t6 * t1);
    real_type t45  = LimitMinSpeed(t1);
    real_type t51  = sin(t2);
    real_type result__ = t26 * t5 + t30 * t5 + t34 * t5 + t43 * t5 + t45 * t5 + t5 * ModelPars[iM_wT] + t5 * t51 * t1 * L__[iL_lambda1__xo] + (t5 * t16 - t4) * L__[iL_lambda2__xo] + (-t18 * ModelPars[iM_kD] + t6) * t5 * L__[iL_lambda3__xo] + t5 * ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo] * U__[iU_v__Omega] + t5 * ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo] * U__[iU_v__fx];
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
  PointMassCarModel_1::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t3   = X__[iX_n];
    real_type t5   = inv_zeta__dot(t1, X__[iX_alpha], t3, Q__[iQ_Kappa]);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t17  = X__[iX_Omega] * X__[iX_Omega];
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t26  = AdherenceEllipse(1 - t14 / t9 * t7 - t14 / t21 * t18 * t17);
    real_type t30  = RoadLeftBorder(Q__[iQ_leftWidth] - t3);
    real_type t34  = RoadRightBorder(Q__[iQ_rightWidth] + t3);
    real_type t43  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t6 * t1);
    real_type t45  = LimitMinSpeed(t1);
    real_type result__ = t26 * t5 + t30 * t5 + t34 * t5 + t43 * t5 + t45 * t5;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_1::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t10  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type result__ = t10 * t5 + t7 * t5;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  PointMassCarModel_1::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t6   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type result__ = t6 * ModelPars[iM_wT];
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
  PointMassCarModel_1::mayer_target(
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

  integer
  PointMassCarModel_1::DmayerDxxp_numEqns() const
  { return 10; }

  void
  PointMassCarModel_1::DmayerDxxp_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 10, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer
  PointMassCarModel_1::DlagrangeDxup_numEqns() const
  { return 7; }

  void
  PointMassCarModel_1::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_wT];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = inv_zeta__dot_D_3(t2, t3, t4, t5);
    result__[ 0   ] = t6 * t1;
    real_type t7   = inv_zeta__dot_D_2(t2, t3, t4, t5);
    result__[ 1   ] = t7 * t1;
    real_type t8   = inv_zeta__dot_D_1(t2, t3, t4, t5);
    result__[ 2   ] = t8 * t1;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 7, i_segment );
  }

  integer
  PointMassCarModel_1::DJDx_numEqns() const
  { return 5; }

  void
  PointMassCarModel_1::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = 1.0 / t9;
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t16  = X__[iX_Omega];
    real_type t17  = t16 * t16;
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = 1.0 / t21;
    real_type t25  = -t14 * t22 * t18 * t17 - t14 * t10 * t7 + 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = Q__[iQ_leftWidth] - t3;
    real_type t30  = RoadLeftBorder(t29);
    real_type t32  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t33  = ALIAS_RoadLeftBorder_D(t29);
    real_type t36  = Q__[iQ_rightWidth] + t3;
    real_type t37  = RoadRightBorder(t36);
    real_type t39  = ALIAS_RoadRightBorder_D(t36);
    real_type t42  = ModelPars[iM_m];
    real_type t44  = 1.0 / ModelPars[iM_Pmax];
    real_type t47  = -t44 * t42 * t6 * t1 + 1;
    real_type t48  = PowerLimit(t47);
    real_type t50  = LimitMinSpeed(t1);
    real_type t53  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t56  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 0   ] = t26 * t5 + t30 * t5 - t33 * t32 + t39 * t32 + t37 * t5 + t48 * t5 + t50 * t5 + t5 * t53 + t56 * t5;
    real_type t58  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t26 * t58 + t30 * t58 + t37 * t58 + t48 * t58 + t50 * t58 + t53 * t58 + t56 * t58;
    real_type t66  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t68  = ALIAS_AdherenceEllipse_D(t25);
    real_type t69  = t68 * t32;
    real_type t78  = ALIAS_PowerLimit_D(t47);
    real_type t79  = t78 * t32;
    real_type t84  = ALIAS_LimitMinSpeed_D(t1);
    result__[ 2   ] = -2 * t14 * t22 * t1 * t17 * t69 - t44 * t42 * t6 * t79 + t26 * t66 + t30 * t66 + t84 * t32 + t37 * t66 + t48 * t66 + t50 * t66 + t53 * t66 + t56 * t66;
    result__[ 3   ] = -2 * t14 * t22 * t18 * t16 * t69;
    result__[ 4   ] = -t44 * t42 * t1 * t79 - 2 * t14 * t10 * t6 * t69;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DJDp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_1::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DJDu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t7 * t5;
    real_type t9   = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t9 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDu_eval", 2, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  PointMassCarModel_1::q_numEqns() const
  { return 11; }

  void
  PointMassCarModel_1::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
    result__[ 1   ] = ALIAS_Kappa(s);
    result__[ 2   ] = ALIAS_leftWidth(s);
    result__[ 3   ] = ALIAS_rightWidth(s);
    result__[ 4   ] = ALIAS_xLane(s);
    result__[ 5   ] = ALIAS_yLane(s);
    result__[ 6   ] = ALIAS_theta(s);
    result__[ 7   ] = ALIAS_xL(s);
    result__[ 8   ] = ALIAS_yL(s);
    result__[ 9   ] = ALIAS_xR(s);
    result__[ 10  ] = ALIAS_yR(s);
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  PointMassCarModel_1::segmentLink_numEqns() const
  { return 0; }

  void
  PointMassCarModel_1::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_1::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_1::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DsegmentLinkDxp_sparse(
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

  integer
  PointMassCarModel_1::jump_numEqns() const
  { return 10; }

  void
  PointMassCarModel_1::jump_eval(
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
    result__[ 0   ] = XR__[iX_n] - XL__[iX_n];
    result__[ 1   ] = XR__[iX_alpha] - XL__[iX_alpha];
    result__[ 2   ] = XR__[iX_V] - XL__[iX_V];
    result__[ 3   ] = XR__[iX_Omega] - XL__[iX_Omega];
    result__[ 4   ] = XR__[iX_fx] - XL__[iX_fx];
    result__[ 5   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 6   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 7   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 8   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 9   ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DjumpDxlxlp_numRows() const
  { return 10; }

  integer
  PointMassCarModel_1::DjumpDxlxlp_numCols() const
  { return 20; }

  integer
  PointMassCarModel_1::DjumpDxlxlp_nnz() const
  { return 20; }

  void
  PointMassCarModel_1::DjumpDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 10  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 11  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 12  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 13  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 14  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 15  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 16  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 17  ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 18  ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 19  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DjumpDxlxlp_sparse(
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
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    result__[ 18  ] = -1;
    result__[ 19  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 20, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  PointMassCarModel_1::post_numEqns() const
  { return 14; }

  void
  PointMassCarModel_1::post_eval(
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
    result__[ 2   ] = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t25  = X__[iX_n];
    result__[ 3   ] = RoadLeftBorder(Q__[iQ_leftWidth] - t25);
    result__[ 4   ] = RoadRightBorder(Q__[iQ_rightWidth] + t25);
    result__[ 5   ] = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15);
    result__[ 6   ] = LimitMinSpeed(t15);
    real_type t36  = Q__[iQ_zeta];
    result__[ 7   ] = ALIAS_xV(t36, t25);
    result__[ 8   ] = ALIAS_yV(t36, t25);
    result__[ 9   ] = t15 * t13;
    real_type t39  = 1.0 / t9;
    result__[ 10  ] = t39 / t5 * t3;
    result__[ 11  ] = t39 / t18 * result__[9];
    result__[ 12  ] = inv_zeta__dot(t15, X__[iX_alpha], t25, Q__[iQ_Kappa]);
    result__[ 13  ] = 1.0 / result__[12];
    Mechatronix::check_in_segment( result__, "post_eval", 14, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::integrated_post_numEqns() const
  { return 1; }

  void
  PointMassCarModel_1::integrated_post_eval(
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
    result__[ 0   ] = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: PointMassCarModel_1_Methods_problem.cc
