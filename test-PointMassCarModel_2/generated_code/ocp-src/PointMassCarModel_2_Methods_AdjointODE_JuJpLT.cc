/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "PointMassCarModel_2.hh"
#include "PointMassCarModel_2_Pars.hh"

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
#pragma warning( disable : 4189 )
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


namespace PointMassCarModel_2Define {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_2::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_2::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t11  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type result__ = t11 * t6 + t6 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_2::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t3   = X__[iX_n];
    real_type t5   = zeta__dot(t1, X__[iX_alpha], t3, Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t7   = X__[iX_fx];
    real_type t8   = t7 * t7;
    real_type t10  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t14  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t15  = 1.0 / t14;
    real_type t18  = X__[iX_Omega] * X__[iX_Omega];
    real_type t19  = t1 * t1;
    real_type t22  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t27  = AdherenceEllipse(t15 / t10 * t8 + t15 / t22 * t19 * t18 - 1);
    real_type t31  = RoadLeftBorder(t3 - Q__[iQ_leftWidth]);
    real_type t35  = RoadRightBorder(-t3 - Q__[iQ_rightWidth]);
    real_type t44  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t7 * t1 - 1);
    real_type t46  = LimitMinSpeed(-t1);
    real_type result__ = t27 * t6 + t31 * t6 + t35 * t6 + t44 * t6 + t46 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JPxpu_numEqns() const { return 7; }

  void
  PointMassCarModel_2::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JUxpu_numEqns() const { return 7; }

  void
  PointMassCarModel_2::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t8   = U__[iU_v__fx];
    real_type t9   = v__fxControl(t8, -1, 1);
    real_type t10  = t9 * t7;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t13  = U__[iU_v__Omega];
    real_type t14  = v__OmegaControl(t13, -1, 1);
    real_type t15  = t14 * t7;
    result__[ 0   ] = -t10 * t11 - t11 * t15;
    real_type t17  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t10 * t17 - t15 * t17;
    real_type t20  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t10 * t20 - t15 * t20;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    real_type t23  = 1.0 / t5;
    real_type t24  = ALIAS_v__fxControl_D_1(t8, -1, 1);
    result__[ 5   ] = t24 * t23;
    real_type t25  = ALIAS_v__OmegaControl_D_1(t13, -1, 1);
    result__[ 6   ] = t25 * t23;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::LTxpu_numEqns() const { return 7; }

  void
  PointMassCarModel_2::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t8   = X__[iX_fx];
    real_type t9   = t8 * t8;
    real_type t11  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t16  = 1.0 / t15;
    real_type t18  = X__[iX_Omega];
    real_type t19  = t18 * t18;
    real_type t20  = t1 * t1;
    real_type t23  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = 1.0 / t23;
    real_type t27  = t16 * t24 * t20 * t19 + t16 * t12 * t9 - 1;
    real_type t28  = AdherenceEllipse(t27);
    real_type t29  = t28 * t7;
    real_type t30  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t33  = t3 - Q__[iQ_leftWidth];
    real_type t34  = RoadLeftBorder(t33);
    real_type t35  = t34 * t7;
    real_type t37  = 1.0 / t5;
    real_type t38  = ALIAS_RoadLeftBorder_D(t33);
    real_type t41  = -t3 - Q__[iQ_rightWidth];
    real_type t42  = RoadRightBorder(t41);
    real_type t43  = t42 * t7;
    real_type t45  = ALIAS_RoadRightBorder_D(t41);
    real_type t48  = ModelPars[iM_m];
    real_type t50  = 1.0 / ModelPars[iM_Pmax];
    real_type t53  = t50 * t48 * t8 * t1 - 1;
    real_type t54  = PowerLimit(t53);
    real_type t55  = t54 * t7;
    real_type t57  = LimitMinSpeed(-t1);
    real_type t58  = t57 * t7;
    result__[ 0   ] = -t30 * t29 - t30 * t35 - t30 * t43 - t30 * t55 - t30 * t58 + t38 * t37 - t45 * t37;
    real_type t60  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t60 * t29 - t60 * t35 - t60 * t43 - t60 * t55 - t60 * t58;
    real_type t66  = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t68  = ALIAS_AdherenceEllipse_D(t27);
    real_type t69  = t68 * t37;
    real_type t78  = ALIAS_PowerLimit_D(t53);
    real_type t79  = t78 * t37;
    real_type t84  = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 2   ] = 2 * t16 * t24 * t1 * t19 * t69 + t50 * t48 * t8 * t79 - t66 * t29 - t66 * t35 - t84 * t37 - t66 * t43 - t66 * t55 - t66 * t58;
    result__[ 3   ] = 2 * t16 * t24 * t20 * t18 * t69;
    result__[ 4   ] = t50 * t48 * t1 * t79 + 2 * t16 * t12 * t8 * t69;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::LTargs_numEqns() const { return 5; }

  void
  PointMassCarModel_2::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_fx];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t12  = X__[iX_Omega] * X__[iX_Omega];
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    result__[ 0   ] = t9 / t4 * t2 + t9 / t17 * t14 * t12 - 1;
    real_type t21  = X__[iX_n];
    result__[ 1   ] = t21 - Q__[iQ_leftWidth];
    result__[ 2   ] = -t21 - Q__[iQ_rightWidth];
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13 - 1;
    result__[ 4   ] = -t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2JPD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2JPD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2JPD2xpu_nnz()     const { return 0; }

  void
  PointMassCarModel_2::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2LTD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2LTD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2LTD2xpu_nnz()     const { return 25; }

  void
  PointMassCarModel_2::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 4   ;
    iIndex[15] = 3   ; jIndex[15] = 0   ;
    iIndex[16] = 3   ; jIndex[16] = 1   ;
    iIndex[17] = 3   ; jIndex[17] = 2   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 4   ; jIndex[20] = 0   ;
    iIndex[21] = 4   ; jIndex[21] = 1   ;
    iIndex[22] = 4   ; jIndex[22] = 2   ;
    iIndex[23] = 4   ; jIndex[23] = 3   ;
    iIndex[24] = 4   ; jIndex[24] = 4   ;
  }


  void
  PointMassCarModel_2::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t8   = 1.0 / t6 / t5;
    real_type t9   = X__[iX_fx];
    real_type t10  = t9 * t9;
    real_type t12  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = 1.0 / t12;
    real_type t16  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t17  = 1.0 / t16;
    real_type t19  = X__[iX_Omega];
    real_type t20  = t19 * t19;
    real_type t21  = t1 * t1;
    real_type t24  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t25  = 1.0 / t24;
    real_type t28  = t17 * t25 * t21 * t20 + t17 * t13 * t10 - 1;
    real_type t29  = AdherenceEllipse(t28);
    real_type t30  = t29 * t8;
    real_type t31  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t32  = t31 * t31;
    real_type t35  = 1.0 / t6;
    real_type t36  = t29 * t35;
    real_type t37  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t40  = t3 - Q__[iQ_leftWidth];
    real_type t41  = RoadLeftBorder(t40);
    real_type t42  = t41 * t8;
    real_type t45  = ALIAS_RoadLeftBorder_D(t40);
    real_type t46  = t45 * t35;
    real_type t49  = t41 * t35;
    real_type t51  = 1.0 / t5;
    real_type t52  = ALIAS_RoadLeftBorder_DD(t40);
    real_type t55  = -t3 - Q__[iQ_rightWidth];
    real_type t56  = RoadRightBorder(t55);
    real_type t57  = t56 * t8;
    real_type t60  = ALIAS_RoadRightBorder_D(t55);
    real_type t61  = t60 * t35;
    real_type t64  = t56 * t35;
    real_type t66  = ALIAS_RoadRightBorder_DD(t55);
    real_type t69  = ModelPars[iM_m];
    real_type t70  = ModelPars[iM_Pmax];
    real_type t72  = 1.0 / t70 * t69;
    real_type t74  = t72 * t9 * t1 - 1;
    real_type t75  = PowerLimit(t74);
    real_type t76  = t75 * t8;
    real_type t79  = t75 * t35;
    real_type t81  = LimitMinSpeed(-t1);
    real_type t82  = t81 * t8;
    real_type t85  = t81 * t35;
    result__[ 0   ] = 2 * t32 * t30 - 2 * t31 * t46 + 2 * t31 * t61 + 2 * t32 * t42 + 2 * t32 * t57 + 2 * t32 * t76 + 2 * t32 * t82 - t37 * t36 - t37 * t49 - t37 * t64 - t37 * t79 - t37 * t85 + t52 * t51 + t66 * t51;
    real_type t87  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t88  = t87 * t31;
    real_type t91  = zeta__dot_D_2_3(t1, t2, t3, t4);
    result__[ 1   ] = 2 * t88 * t30 - t91 * t36 + 2 * t88 * t42 - t87 * t46 - t91 * t49 + 2 * t88 * t57 + t87 * t61 - t91 * t64 + 2 * t88 * t76 - t91 * t79 + 2 * t88 * t82 - t91 * t85;
    real_type t107 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t108 = t107 * t31;
    real_type t111 = ALIAS_AdherenceEllipse_D(t28);
    real_type t112 = t111 * t35;
    real_type t113 = t20 * t112;
    real_type t114 = t25 * t1;
    real_type t115 = t31 * t17;
    real_type t119 = zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t131 = ALIAS_PowerLimit_D(t74);
    real_type t132 = t131 * t35;
    real_type t133 = t9 * t132;
    real_type t134 = t31 * t72;
    real_type t139 = ALIAS_LimitMinSpeed_D(-t1);
    real_type t140 = t139 * t35;
    result__[ 2   ] = -2 * t115 * t114 * t113 - t107 * t46 + t107 * t61 + 2 * t108 * t30 + 2 * t108 * t42 + 2 * t108 * t57 + 2 * t108 * t76 + 2 * t108 * t82 - t119 * t36 - t119 * t49 - t119 * t64 - t119 * t79 - t119 * t85 - t134 * t133 + t31 * t140;
    real_type t143 = t19 * t112;
    real_type t144 = t25 * t21;
    result__[ 3   ] = -2 * t115 * t144 * t143;
    real_type t148 = t9 * t112;
    real_type t149 = t17 * t13;
    real_type t153 = t1 * t132;
    result__[ 4   ] = -2 * t31 * t149 * t148 - t134 * t153;
    result__[ 5   ] = result__[1];
    real_type t155 = t87 * t87;
    real_type t158 = zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = 2 * t155 * t30 + 2 * t155 * t42 + 2 * t155 * t57 + 2 * t155 * t76 + 2 * t155 * t82 - t158 * t36 - t158 * t49 - t158 * t64 - t158 * t79 - t158 * t85;
    real_type t172 = t107 * t87;
    real_type t175 = t87 * t17;
    real_type t179 = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t189 = t87 * t72;
    result__[ 7   ] = -2 * t175 * t114 * t113 - t189 * t133 + t87 * t140 + 2 * t172 * t30 + 2 * t172 * t42 + 2 * t172 * t57 + 2 * t172 * t76 + 2 * t172 * t82 - t179 * t36 - t179 * t49 - t179 * t64 - t179 * t79 - t179 * t85;
    result__[ 8   ] = -2 * t175 * t144 * t143;
    result__[ 9   ] = -2 * t87 * t149 * t148 - t189 * t153;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t203 = t107 * t107;
    real_type t206 = t107 * t17;
    real_type t210 = zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t212 = ALIAS_AdherenceEllipse_DD(t28);
    real_type t213 = t212 * t51;
    real_type t214 = t20 * t20;
    real_type t216 = t24 * t24;
    real_type t217 = 1.0 / t216;
    real_type t219 = t16 * t16;
    real_type t220 = 1.0 / t219;
    real_type t224 = t111 * t51;
    real_type t237 = t107 * t72;
    real_type t241 = ALIAS_PowerLimit_DD(t74);
    real_type t242 = t241 * t51;
    real_type t243 = t69 * t69;
    real_type t245 = t70 * t70;
    real_type t246 = 1.0 / t245;
    real_type t254 = ALIAS_LimitMinSpeed_DD(-t1);
    result__[ 12  ] = 2 * t203 * t30 - 4 * t206 * t114 * t113 - t210 * t36 + 4 * t220 * t217 * t21 * t214 * t213 + 2 * t17 * t25 * t20 * t224 + 2 * t203 * t42 - t210 * t49 + 2 * t203 * t57 - t210 * t64 + 2 * t203 * t76 - 2 * t237 * t133 - t210 * t79 + t246 * t243 * t10 * t242 + 2 * t203 * t82 + 2 * t107 * t140 - t210 * t85 + t254 * t51;
    result__[ 13  ] = 4 * t220 * t217 * t21 * t1 * t20 * t19 * t213 + 4 * t17 * t114 * t19 * t224 - 2 * t206 * t144 * t143;
    real_type t274 = t13 * t9 * t213;
    result__[ 14  ] = t9 * t246 * t243 * t1 * t242 + 4 * t114 * t20 * t220 * t274 - 2 * t107 * t149 * t148 + t72 * t131 * t51 - t237 * t153;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t287 = t21 * t21;
    result__[ 18  ] = 4 * t220 * t217 * t287 * t20 * t213 + 2 * t17 * t144 * t224;
    result__[ 19  ] = 4 * t144 * t19 * t220 * t274;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t298 = t12 * t12;
    result__[ 24  ] = 4 * t220 / t298 * t10 * t213 + 2 * t149 * t224 + t246 * t243 * t21 * t242;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 25, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2JUD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2JUD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2JUD2xpu_nnz()     const { return 23; }

  void
  PointMassCarModel_2::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 5   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 5   ; jIndex[15] = 0   ;
    iIndex[16] = 5   ; jIndex[16] = 1   ;
    iIndex[17] = 5   ; jIndex[17] = 2   ;
    iIndex[18] = 5   ; jIndex[18] = 5   ;
    iIndex[19] = 6   ; jIndex[19] = 0   ;
    iIndex[20] = 6   ; jIndex[20] = 1   ;
    iIndex[21] = 6   ; jIndex[21] = 2   ;
    iIndex[22] = 6   ; jIndex[22] = 6   ;
  }


  void
  PointMassCarModel_2::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t8   = 1.0 / t6 / t5;
    real_type t9   = U__[iU_v__fx];
    real_type t10  = v__fxControl(t9, -1, 1);
    real_type t11  = t8 * t10;
    real_type t12  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t13  = t12 * t12;
    real_type t16  = 1.0 / t6;
    real_type t17  = t10 * t16;
    real_type t18  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t20  = U__[iU_v__Omega];
    real_type t21  = v__OmegaControl(t20, -1, 1);
    real_type t22  = t21 * t8;
    real_type t25  = t21 * t16;
    result__[ 0   ] = 2 * t13 * t11 + 2 * t13 * t22 - t18 * t17 - t18 * t25;
    real_type t27  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t28  = t27 * t12;
    real_type t31  = zeta__dot_D_2_3(t1, t2, t3, t4);
    result__[ 1   ] = 2 * t28 * t11 - t31 * t17 + 2 * t28 * t22 - t31 * t25;
    real_type t36  = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t37  = t36 * t12;
    real_type t40  = zeta__dot_D_1_3(t1, t2, t3, t4);
    result__[ 2   ] = 2 * t11 * t37 - t17 * t40 + 2 * t22 * t37 - t25 * t40;
    real_type t45  = ALIAS_v__fxControl_D_1(t9, -1, 1);
    real_type t46  = t45 * t16;
    result__[ 3   ] = -t12 * t46;
    real_type t48  = ALIAS_v__OmegaControl_D_1(t20, -1, 1);
    real_type t49  = t48 * t16;
    result__[ 4   ] = -t12 * t49;
    result__[ 5   ] = result__[1];
    real_type t51  = t27 * t27;
    real_type t54  = zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = 2 * t11 * t51 - t17 * t54 + 2 * t22 * t51 - t25 * t54;
    real_type t59  = t36 * t27;
    real_type t62  = zeta__dot_D_1_2(t1, t2, t3, t4);
    result__[ 7   ] = 2 * t11 * t59 - t17 * t62 + 2 * t22 * t59 - t25 * t62;
    result__[ 8   ] = -t27 * t46;
    result__[ 9   ] = -t27 * t49;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t69  = t36 * t36;
    real_type t72  = zeta__dot_D_1_1(t1, t2, t3, t4);
    result__[ 12  ] = 2 * t11 * t69 - t17 * t72 + 2 * t22 * t69 - t25 * t72;
    result__[ 13  ] = -t36 * t46;
    result__[ 14  ] = -t36 * t49;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t79  = 1.0 / t5;
    real_type t80  = ALIAS_v__fxControl_D_1_1(t9, -1, 1);
    result__[ 18  ] = t80 * t79;
    result__[ 19  ] = result__[4];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[14];
    real_type t81  = ALIAS_v__OmegaControl_D_1_1(t20, -1, 1);
    result__[ 22  ] = t81 * t79;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 23, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTargsDxpu_numRows() const { return 5; }
  integer PointMassCarModel_2::DLTargsDxpu_numCols() const { return 7; }
  integer PointMassCarModel_2::DLTargsDxpu_nnz()     const { return 8; }

  void
  PointMassCarModel_2::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 2   ;
  }


  void
  PointMassCarModel_2::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_Omega];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_V];
    real_type t6   = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t9   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t10  = 1.0 / t9;
    real_type t11  = t10 / t6;
    result__[ 0   ] = 2 * t11 * t3 * t2;
    real_type t13  = t3 * t3;
    result__[ 1   ] = 2 * t11 * t13 * t1;
    real_type t16  = X__[iX_fx];
    real_type t18  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    result__[ 2   ] = 2 * t10 / t18 * t16;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    real_type t22  = ModelPars[iM_m];
    real_type t25  = 1.0 / ModelPars[iM_Pmax];
    result__[ 5   ] = t25 * t22 * t16;
    result__[ 6   ] = t25 * t22 * t3;
    result__[ 7   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 8, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2LTargsD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2LTargsD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2LTargsD2xpu_nnz()     const { return 7; }

  void
  PointMassCarModel_2::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 4   ;
  }


  void
  PointMassCarModel_2::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_Omega];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t5   = 1.0 / t4;
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t10  = OMEGA__[0];
    real_type t11  = t10 * t9;
    result__[ 0   ] = 2 * t11 * t5 * t2;
    real_type t13  = X__[iX_V];
    result__[ 1   ] = 4 * t10 * t9 * t5 * t13 * t1;
    result__[ 2   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * OMEGA__[3];
    result__[ 3   ] = result__[1];
    real_type t23  = t13 * t13;
    result__[ 4   ] = 2 * t11 * t5 * t23;
    result__[ 5   ] = result__[2];
    real_type t27  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    result__[ 6   ] = 2 * t10 * t9 / t27;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 7, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
