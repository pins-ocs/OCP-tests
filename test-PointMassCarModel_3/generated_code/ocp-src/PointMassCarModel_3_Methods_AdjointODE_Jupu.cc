/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
#pragma warning( disable : 4189 )
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_3::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_3::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t4   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t7   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type result__ = t4 * t2 + t7 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_3::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
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
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::JPxpu_numEqns() const { return 9; }

  void
  PointMassCarModel_3::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::JUxpu_numEqns() const { return 9; }

  void
  PointMassCarModel_3::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = U__[iU_v__fx];
    real_type t3   = v__fxControl(t2, -1, 1);
    real_type t5   = U__[iU_v__Omega];
    real_type t6   = v__OmegaControl(t5, -1, 1);
    result__[ 6   ] = 2 * t3 * t1 + 2 * t6 * t1;
    real_type t9   = t1 * t1;
    real_type t10  = ALIAS_v__fxControl_D_1(t2, -1, 1);
    result__[ 7   ] = t10 * t9;
    real_type t11  = ALIAS_v__OmegaControl_D_1(t5, -1, 1);
    result__[ 8   ] = t11 * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::LTxpu_numEqns() const { return 9; }

  void
  PointMassCarModel_3::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_D(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t11  = ALIAS_rightWidth(t4);
    real_type t12  = -t3 - t11;
    real_type t13  = ALIAS_RoadRightBorder_D(t12);
    real_type t14  = t13 * t2;
    real_type t15  = ALIAS_rightWidth_D(t4);
    result__[ 0   ] = -t15 * t14 - t9 * t8;
    result__[ 1   ] = t8 - t14;
    result__[ 2   ] = 0;
    real_type t17  = X__[iX_fx];
    real_type t18  = t17 * t17;
    real_type t20  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t21  = 1.0 / t20;
    real_type t24  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t25  = 1.0 / t24;
    real_type t27  = X__[iX_Omega];
    real_type t28  = t27 * t27;
    real_type t29  = X__[iX_V];
    real_type t30  = t29 * t29;
    real_type t33  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t34  = 1.0 / t33;
    real_type t37  = t25 * t34 * t30 * t28 + t25 * t21 * t18 - 1;
    real_type t38  = ALIAS_AdherenceEllipse_D(t37);
    real_type t39  = t38 * t2;
    real_type t46  = ModelPars[iM_m];
    real_type t48  = 1.0 / ModelPars[iM_Pmax];
    real_type t51  = t48 * t46 * t17 * t29 - 1;
    real_type t52  = ALIAS_PowerLimit_D(t51);
    real_type t53  = t52 * t2;
    result__[ 3   ] = 2 * t25 * t34 * t29 * t28 * t39 + t48 * t46 * t17 * t53;
    result__[ 4   ] = 2 * t25 * t34 * t30 * t27 * t39;
    result__[ 5   ] = 2 * t25 * t21 * t17 * t39 + t48 * t46 * t29 * t53;
    real_type t68  = AdherenceEllipse(t37);
    real_type t70  = RoadLeftBorder(t6);
    real_type t72  = RoadRightBorder(t12);
    real_type t74  = PowerLimit(t51);
    result__[ 6   ] = 2 * t1 * t68 + 2 * t1 * t70 + 2 * t1 * t72 + 2 * t1 * t74;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::LTargs_numEqns() const { return 4; }

  void
  PointMassCarModel_3::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
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
    real_type t22  = X__[iX_s];
    real_type t23  = ALIAS_leftWidth(t22);
    result__[ 1   ] = t21 - t23;
    real_type t24  = ALIAS_rightWidth(t22);
    result__[ 2   ] = -t21 - t24;
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13 - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2JPD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2JPD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2JPD2xpu_nnz()     const { return 0; }

  void
  PointMassCarModel_3::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_3::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2LTD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2LTD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2LTD2xpu_nnz()     const { return 24; }

  void
  PointMassCarModel_3::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 6   ;
    iIndex[10] = 4   ; jIndex[10] = 3   ;
    iIndex[11] = 4   ; jIndex[11] = 4   ;
    iIndex[12] = 4   ; jIndex[12] = 5   ;
    iIndex[13] = 4   ; jIndex[13] = 6   ;
    iIndex[14] = 5   ; jIndex[14] = 3   ;
    iIndex[15] = 5   ; jIndex[15] = 4   ;
    iIndex[16] = 5   ; jIndex[16] = 5   ;
    iIndex[17] = 5   ; jIndex[17] = 6   ;
    iIndex[18] = 6   ; jIndex[18] = 0   ;
    iIndex[19] = 6   ; jIndex[19] = 1   ;
    iIndex[20] = 6   ; jIndex[20] = 3   ;
    iIndex[21] = 6   ; jIndex[21] = 4   ;
    iIndex[22] = 6   ; jIndex[22] = 5   ;
    iIndex[23] = 6   ; jIndex[23] = 6   ;
  }


  void
  PointMassCarModel_3::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_RoadLeftBorder_D(t6);
    real_type t14  = ALIAS_leftWidth_DD(t4);
    real_type t16  = ALIAS_rightWidth(t4);
    real_type t17  = -t3 - t16;
    real_type t18  = ALIAS_RoadRightBorder_DD(t17);
    real_type t19  = t18 * t2;
    real_type t20  = ALIAS_rightWidth_D(t4);
    real_type t21  = t20 * t20;
    real_type t23  = ALIAS_RoadRightBorder_D(t17);
    real_type t25  = ALIAS_rightWidth_DD(t4);
    result__[ 0   ] = -t14 * t12 * t2 - t25 * t23 * t2 + t10 * t8 + t21 * t19;
    result__[ 1   ] = t20 * t19 - t9 * t8;
    real_type t29  = t12 * t1;
    real_type t31  = t23 * t1;
    result__[ 2   ] = -2 * t20 * t31 - 2 * t9 * t29;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = t8 + t19;
    result__[ 5   ] = 2 * t29 - 2 * t31;
    real_type t35  = X__[iX_fx];
    real_type t36  = t35 * t35;
    real_type t38  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t39  = 1.0 / t38;
    real_type t42  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t43  = 1.0 / t42;
    real_type t45  = X__[iX_Omega];
    real_type t46  = t45 * t45;
    real_type t47  = X__[iX_V];
    real_type t48  = t47 * t47;
    real_type t51  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t52  = 1.0 / t51;
    real_type t55  = t43 * t52 * t48 * t46 + t43 * t39 * t36 - 1;
    real_type t56  = ALIAS_AdherenceEllipse_DD(t55);
    real_type t57  = t56 * t2;
    real_type t58  = t46 * t46;
    real_type t60  = t51 * t51;
    real_type t61  = 1.0 / t60;
    real_type t63  = t42 * t42;
    real_type t64  = 1.0 / t63;
    real_type t68  = ALIAS_AdherenceEllipse_D(t55);
    real_type t69  = t68 * t2;
    real_type t75  = ModelPars[iM_m];
    real_type t76  = ModelPars[iM_Pmax];
    real_type t77  = 1.0 / t76;
    real_type t78  = t77 * t75;
    real_type t80  = t78 * t35 * t47 - 1;
    real_type t81  = ALIAS_PowerLimit_DD(t80);
    real_type t82  = t81 * t2;
    real_type t83  = t75 * t75;
    real_type t85  = t76 * t76;
    real_type t86  = 1.0 / t85;
    result__[ 6   ] = 4 * t64 * t61 * t48 * t58 * t57 + t86 * t83 * t36 * t82 + 2 * t43 * t52 * t46 * t69;
    real_type t96  = t52 * t47;
    real_type t97  = t43 * t96;
    result__[ 7   ] = 4 * t64 * t61 * t48 * t47 * t46 * t45 * t57 + 4 * t97 * t45 * t69;
    real_type t100 = t39 * t35;
    real_type t101 = t100 * t57;
    real_type t110 = ALIAS_PowerLimit_D(t80);
    result__[ 8   ] = t35 * t86 * t83 * t47 * t82 + 4 * t96 * t46 * t64 * t101 + t78 * t110 * t2;
    real_type t113 = t68 * t1;
    real_type t117 = t110 * t1;
    result__[ 9   ] = 2 * t77 * t75 * t35 * t117 + 4 * t97 * t46 * t113;
    result__[ 10  ] = result__[7];
    real_type t123 = t48 * t48;
    real_type t128 = t52 * t48;
    real_type t129 = t43 * t128;
    result__[ 11  ] = 4 * t64 * t61 * t123 * t46 * t57 + 2 * t129 * t69;
    result__[ 12  ] = 4 * t128 * t45 * t64 * t101;
    result__[ 13  ] = 4 * t129 * t45 * t113;
    result__[ 14  ] = result__[8];
    result__[ 15  ] = result__[12];
    real_type t137 = t38 * t38;
    result__[ 16  ] = 4 * t64 / t137 * t36 * t57 + 2 * t43 * t39 * t69 + t86 * t83 * t48 * t82;
    result__[ 17  ] = 2 * t77 * t75 * t47 * t117 + 4 * t43 * t100 * t113;
    result__[ 18  ] = result__[2];
    result__[ 19  ] = result__[5];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[13];
    result__[ 22  ] = result__[17];
    real_type t156 = AdherenceEllipse(t55);
    real_type t157 = RoadLeftBorder(t6);
    real_type t158 = RoadRightBorder(t17);
    real_type t159 = PowerLimit(t80);
    result__[ 23  ] = 2 * t156 + 2 * t157 + 2 * t158 + 2 * t159;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2JUD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2JUD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2JUD2xpu_nnz()     const { return 7; }

  void
  PointMassCarModel_3::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 6   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 6   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 6   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 7   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 7   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 8   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 8   ; jIndex[6 ] = 8   ;
  }


  void
  PointMassCarModel_3::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_v__fx];
    real_type t2   = v__fxControl(t1, -1, 1);
    real_type t3   = U__[iU_v__Omega];
    real_type t4   = v__OmegaControl(t3, -1, 1);
    result__[ 0   ] = 2 * t2 + 2 * t4;
    real_type t6   = X__[iX_sqrt_inv_Vseg];
    real_type t7   = ALIAS_v__fxControl_D_1(t1, -1, 1);
    result__[ 1   ] = 2 * t7 * t6;
    real_type t9   = ALIAS_v__OmegaControl_D_1(t3, -1, 1);
    result__[ 2   ] = 2 * t9 * t6;
    result__[ 3   ] = result__[1];
    real_type t11  = t6 * t6;
    real_type t12  = ALIAS_v__fxControl_D_1_1(t1, -1, 1);
    result__[ 4   ] = t12 * t11;
    result__[ 5   ] = result__[2];
    real_type t13  = ALIAS_v__OmegaControl_D_1_1(t3, -1, 1);
    result__[ 6   ] = t13 * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DLTargsDxpu_numRows() const { return 4; }
  integer PointMassCarModel_3::DLTargsDxpu_numCols() const { return 9; }
  integer PointMassCarModel_3::DLTargsDxpu_nnz()     const { return 9; }

  void
  PointMassCarModel_3::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 5   ;
  }


  void
  PointMassCarModel_3::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
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
    real_type t22  = X__[iX_s];
    real_type t23  = ALIAS_leftWidth_D(t22);
    result__[ 3   ] = -t23;
    result__[ 4   ] = 1;
    real_type t24  = ALIAS_rightWidth_D(t22);
    result__[ 5   ] = -t24;
    result__[ 6   ] = -1;
    real_type t25  = ModelPars[iM_m];
    real_type t28  = 1.0 / ModelPars[iM_Pmax];
    result__[ 7   ] = t28 * t25 * t16;
    result__[ 8   ] = t28 * t25 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 9, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2LTargsD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2LTargsD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2LTargsD2xpu_nnz()     const { return 8; }

  void
  PointMassCarModel_3::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 5   ;
  }


  void
  PointMassCarModel_3::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_s];
    real_type t2   = ALIAS_leftWidth_DD(t1);
    real_type t5   = ALIAS_rightWidth_DD(t1);
    result__[ 0   ] = -OMEGA__[1] * t2 - OMEGA__[2] * t5;
    real_type t8   = X__[iX_Omega];
    real_type t9   = t8 * t8;
    real_type t11  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t16  = 1.0 / t15;
    real_type t17  = OMEGA__[0];
    real_type t18  = t17 * t16;
    result__[ 1   ] = 2 * t18 * t12 * t9;
    real_type t20  = X__[iX_V];
    result__[ 2   ] = 4 * t17 * t16 * t12 * t20 * t8;
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * OMEGA__[3];
    result__[ 4   ] = result__[2];
    real_type t30  = t20 * t20;
    result__[ 5   ] = 2 * t18 * t12 * t30;
    result__[ 6   ] = result__[3];
    real_type t34  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    result__[ 7   ] = 2 * t17 * t16 / t34;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 8, i_segment );
  }

}

// EOF: PointMassCarModel_3_Methods_AdjointODE.cc