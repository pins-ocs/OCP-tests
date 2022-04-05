/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::JPx_numEqns() const { return 7; }

  void
  PointMassCarModel_4::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
      Mechatronix::check_in_segment( result__, "JPx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::LTx_numEqns() const { return 7; }

  void
  PointMassCarModel_4::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_D(t6);
    real_type t8   = t2 * t7;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t11  = ALIAS_rightWidth(t4);
    real_type t12  = -t3 - t11;
    real_type t13  = ALIAS_RoadRightBorder_D(t12);
    real_type t14  = t13 * t2;
    real_type t15  = ALIAS_rightWidth_D(t4);
    result__[ 0   ] = -t14 * t15 - t8 * t9;
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
    real_type t37  = t25 * t28 * t30 * t34 + t18 * t21 * t25 - 1;
    real_type t38  = ALIAS_AdherenceEllipse_D(t37);
    real_type t39  = t38 * t2;
    real_type t46  = ModelPars[iM_m];
    real_type t48  = 1.0 / ModelPars[iM_Pmax];
    real_type t51  = t17 * t29 * t46 * t48 - 1;
    real_type t52  = ALIAS_PowerLimit_D(t51);
    real_type t53  = t52 * t2;
    result__[ 3   ] = 2 * t25 * t28 * t29 * t34 * t39 + t17 * t46 * t48 * t53;
    result__[ 4   ] = 2 * t25 * t34 * t30 * t27 * t39;
    result__[ 5   ] = 2 * t17 * t21 * t25 * t39 + t29 * t46 * t48 * t53;
    real_type t68  = AdherenceEllipse(t37);
    real_type t70  = RoadLeftBorder(t6);
    real_type t72  = RoadRightBorder(t12);
    real_type t74  = PowerLimit(t51);
    result__[ 6   ] = t2 * t68 + t2 * t70 + t2 * t72 + t2 * t74;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::JUx_numEqns() const { return 7; }

  void
  PointMassCarModel_4::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t7   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 6   ] = t4 * t2 + t2 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::JPp_numEqns() const { return 0; }

  void
  PointMassCarModel_4::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::LTp_numEqns() const { return 0; }

  void
  PointMassCarModel_4::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::JUp_numEqns() const { return 0; }

  void
  PointMassCarModel_4::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::JPu_numEqns() const { return 2; }

  void
  PointMassCarModel_4::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::LTu_numEqns() const { return 2; }

  void
  PointMassCarModel_4::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::JUu_numEqns() const { return 2; }

  void
  PointMassCarModel_4::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::LTargs_numEqns() const { return 4; }

  void
  PointMassCarModel_4::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  integer PointMassCarModel_4::DJPxDxp_numRows() const { return 7; }
  integer PointMassCarModel_4::DJPxDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DJPxDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DLTxDxp_numRows() const { return 7; }
  integer PointMassCarModel_4::DLTxDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DLTxDxp_nnz()     const { return 24; }

  void
  PointMassCarModel_4::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_4::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_RoadLeftBorder_D(t6);
    real_type t13  = t12 * t2;
    real_type t14  = ALIAS_leftWidth_DD(t4);
    real_type t16  = ALIAS_rightWidth(t4);
    real_type t17  = -t3 - t16;
    real_type t18  = ALIAS_RoadRightBorder_DD(t17);
    real_type t19  = t18 * t2;
    real_type t20  = ALIAS_rightWidth_D(t4);
    real_type t21  = t20 * t20;
    real_type t23  = ALIAS_RoadRightBorder_D(t17);
    real_type t24  = t23 * t2;
    real_type t25  = ALIAS_rightWidth_DD(t4);
    result__[ 0   ] = t10 * t8 - t14 * t13 + t21 * t19 - t25 * t24;
    result__[ 1   ] = t20 * t19 - t9 * t8;
    result__[ 2   ] = -t9 * t13 - t20 * t24;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = t8 + t19;
    result__[ 5   ] = t13 - t24;
    real_type t31  = X__[iX_fx];
    real_type t32  = t31 * t31;
    real_type t34  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t35  = 1.0 / t34;
    real_type t38  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t39  = 1.0 / t38;
    real_type t41  = X__[iX_Omega];
    real_type t42  = t41 * t41;
    real_type t43  = X__[iX_V];
    real_type t44  = t43 * t43;
    real_type t47  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t48  = 1.0 / t47;
    real_type t51  = t39 * t48 * t44 * t42 + t39 * t35 * t32 - 1;
    real_type t52  = ALIAS_AdherenceEllipse_DD(t51);
    real_type t53  = t52 * t2;
    real_type t54  = t42 * t42;
    real_type t56  = t47 * t47;
    real_type t57  = 1.0 / t56;
    real_type t59  = t38 * t38;
    real_type t60  = 1.0 / t59;
    real_type t64  = ALIAS_AdherenceEllipse_D(t51);
    real_type t65  = t64 * t2;
    real_type t71  = ModelPars[iM_m];
    real_type t72  = ModelPars[iM_Pmax];
    real_type t73  = 1.0 / t72;
    real_type t74  = t73 * t71;
    real_type t76  = t74 * t31 * t43 - 1;
    real_type t77  = ALIAS_PowerLimit_DD(t76);
    real_type t78  = t77 * t2;
    real_type t79  = t71 * t71;
    real_type t81  = t72 * t72;
    real_type t82  = 1.0 / t81;
    result__[ 6   ] = 4 * t60 * t57 * t44 * t54 * t53 + t82 * t79 * t32 * t78 + 2 * t39 * t48 * t42 * t65;
    real_type t91  = t41 * t65;
    real_type t92  = t48 * t43;
    real_type t93  = t39 * t92;
    result__[ 7   ] = 4 * t60 * t57 * t44 * t43 * t42 * t41 * t53 + 4 * t93 * t91;
    real_type t96  = t35 * t31;
    real_type t97  = t96 * t53;
    real_type t106 = ALIAS_PowerLimit_D(t76);
    real_type t107 = t106 * t2;
    result__[ 8   ] = t31 * t82 * t79 * t43 * t78 + 4 * t92 * t42 * t60 * t97 + t74 * t107;
    result__[ 9   ] = t73 * t71 * t31 * t107 + 2 * t93 * t42 * t65;
    result__[ 10  ] = result__[7];
    real_type t116 = t44 * t44;
    real_type t121 = t48 * t44;
    real_type t122 = t39 * t121;
    result__[ 11  ] = 4 * t60 * t57 * t116 * t42 * t53 + 2 * t122 * t65;
    result__[ 12  ] = 4 * t121 * t41 * t60 * t97;
    result__[ 13  ] = 2 * t122 * t91;
    result__[ 14  ] = result__[8];
    result__[ 15  ] = result__[12];
    real_type t129 = t34 * t34;
    result__[ 16  ] = 4 * t60 / t129 * t32 * t53 + 2 * t39 * t35 * t65 + t82 * t79 * t44 * t78;
    result__[ 17  ] = t73 * t71 * t43 * t107 + 2 * t39 * t96 * t65;
    result__[ 18  ] = result__[2];
    result__[ 19  ] = result__[5];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[13];
    result__[ 22  ] = result__[17];
    real_type t147 = AdherenceEllipse(t51);
    real_type t149 = RoadLeftBorder(t6);
    real_type t151 = RoadRightBorder(t17);
    real_type t153 = PowerLimit(t76);
    result__[ 23  ] = t147 * t2 + t149 * t2 + t151 * t2 + t153 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DJUxDxp_numRows() const { return 7; }
  integer PointMassCarModel_4::DJUxDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DJUxDxp_nnz()     const { return 1; }

  void
  PointMassCarModel_4::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 6   ; jIndex[0 ] = 6   ;
  }


  void
  PointMassCarModel_4::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t7   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 0   ] = t4 * t2 + t7 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DJPuDxp_numRows() const { return 2; }
  integer PointMassCarModel_4::DJPuDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DJPuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DLTuDxp_numRows() const { return 2; }
  integer PointMassCarModel_4::DLTuDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DLTuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DJUuDxp_numRows() const { return 2; }
  integer PointMassCarModel_4::DJUuDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DJUuDxp_nnz()     const { return 2; }

  void
  PointMassCarModel_4::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }


  void
  PointMassCarModel_4::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DJPpDp_numRows() const { return 0; }
  integer PointMassCarModel_4::DJPpDp_numCols() const { return 0; }
  integer PointMassCarModel_4::DJPpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DLTpDp_numRows() const { return 0; }
  integer PointMassCarModel_4::DLTpDp_numCols() const { return 0; }
  integer PointMassCarModel_4::DLTpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DJUpDp_numRows() const { return 0; }
  integer PointMassCarModel_4::DJUpDp_numCols() const { return 0; }
  integer PointMassCarModel_4::DJUpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DLTargsDxup_numRows() const { return 4; }
  integer PointMassCarModel_4::DLTargsDxup_numCols() const { return 9; }
  integer PointMassCarModel_4::DLTargsDxup_nnz()     const { return 9; }

  void
  PointMassCarModel_4::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_4::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 9, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::D2LTargsD2xup_numRows() const { return 9; }
  integer PointMassCarModel_4::D2LTargsD2xup_numCols() const { return 9; }
  integer PointMassCarModel_4::D2LTargsD2xup_nnz()     const { return 8; }

  void
  PointMassCarModel_4::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_4::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
      Mechatronix::check_in_segment( result__, "D2LTargsD2xup_sparse", 8, i_segment );
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::Hx_numEqns() const { return 7; }

  void
  PointMassCarModel_4::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = t3 * L__[iL_lambda1__xo];
    real_type t5   = X__[iX_V];
    real_type t6   = X__[iX_alpha];
    real_type t7   = X__[iX_n];
    real_type t8   = X__[iX_s];
    real_type t9   = ALIAS_Kappa(t8);
    real_type t10  = zeta__dot_D_4(t5, t6, t7, t9);
    real_type t11  = ALIAS_Kappa_D(t8);
    real_type t14  = L__[iL_lambda3__xo];
    real_type t15  = zeta__dot(t5, t6, t7, t9);
    result__[ 0   ] = t11 * t10 * t4 - t3 * (t11 * t10 * t9 + t15 * t11) * t14;
    real_type t22  = zeta__dot_D_3(t5, t6, t7, t9);
    real_type t24  = t9 * t14;
    result__[ 1   ] = -t3 * t22 * t24 + t22 * t4;
    real_type t27  = zeta__dot_D_2(t5, t6, t7, t9);
    real_type t30  = t3 * L__[iL_lambda2__xo];
    real_type t31  = cos(t6);
    result__[ 2   ] = -t3 * t27 * t24 + t31 * t5 * t30 + t27 * t4;
    real_type t36  = zeta__dot_D_1(t5, t6, t7, t9);
    real_type t38  = sin(t6);
    real_type t42  = L__[iL_lambda4__xo];
    real_type t43  = ModelPars[iM_kD];
    result__[ 3   ] = -2 * t3 * t5 * t43 * t42 - t3 * t36 * t24 + t38 * t30 + t36 * t4;
    result__[ 4   ] = t3 * t14;
    result__[ 5   ] = t3 * t42;
    real_type t58  = t5 * t5;
    result__[ 6   ] = t3 * ModelPars[iM_wT] + t15 * t4 + t38 * t5 * t30 - t3 * (t15 * t9 - X__[iX_Omega]) * t14 + t3 * (-t58 * t43 + X__[iX_fx]) * t42 + U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo] + U__[iU_v__fx] * ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::Hp_numEqns() const { return 0; }

  void
  PointMassCarModel_4::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DHxDxp_numRows() const { return 7; }
  integer PointMassCarModel_4::DHxDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DHxDxp_nnz()     const { return 29; }

  void
  PointMassCarModel_4::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  PointMassCarModel_4::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = t3 * L__[iL_lambda1__xo];
    real_type t5   = X__[iX_V];
    real_type t6   = X__[iX_alpha];
    real_type t7   = X__[iX_n];
    real_type t8   = X__[iX_s];
    real_type t9   = ALIAS_Kappa(t8);
    real_type t10  = zeta__dot_D_4_4(t5, t6, t7, t9);
    real_type t11  = ALIAS_Kappa_D(t8);
    real_type t12  = t11 * t11;
    real_type t15  = zeta__dot_D_4(t5, t6, t7, t9);
    real_type t16  = ALIAS_Kappa_DD(t8);
    real_type t19  = L__[iL_lambda3__xo];
    real_type t20  = zeta__dot(t5, t6, t7, t9);
    real_type t26  = t15 * t9;
    result__[ 0   ] = t12 * t10 * t4 + t16 * t15 * t4 - t3 * (t10 * t12 * t9 + 2 * t12 * t15 + t16 * t20 + t16 * t26) * t19;
    real_type t31  = zeta__dot_D_3_4(t5, t6, t7, t9);
    real_type t32  = t11 * t31;
    real_type t33  = t32 * t4;
    real_type t34  = zeta__dot_D_3(t5, t6, t7, t9);
    result__[ 1   ] = t33 - t3 * (t11 * t31 * t9 + t11 * t34) * t19;
    real_type t41  = zeta__dot_D_2_4(t5, t6, t7, t9);
    real_type t42  = t11 * t41;
    real_type t43  = t42 * t4;
    real_type t44  = zeta__dot_D_2(t5, t6, t7, t9);
    result__[ 2   ] = t43 - t3 * (t11 * t41 * t9 + t11 * t44) * t19;
    real_type t51  = zeta__dot_D_1_4(t5, t6, t7, t9);
    real_type t52  = t11 * t51;
    real_type t53  = t52 * t4;
    real_type t54  = zeta__dot_D_1(t5, t6, t7, t9);
    result__[ 3   ] = t53 - t3 * (t11 * t51 * t9 + t11 * t54) * t19;
    result__[ 4   ] = t11 * t15 * t4 - t3 * (t11 * t20 + t11 * t26) * t19;
    real_type t68  = t11 * t19;
    real_type t69  = t3 * t34;
    real_type t71  = t9 * t19;
    result__[ 5   ] = -t3 * t32 * t71 - t68 * t69 + t33;
    real_type t74  = zeta__dot_D_3_3(t5, t6, t7, t9);
    result__[ 6   ] = -t3 * t71 * t74 + t4 * t74;
    real_type t78  = zeta__dot_D_2_3(t5, t6, t7, t9);
    result__[ 7   ] = -t3 * t71 * t78 + t4 * t78;
    real_type t82  = zeta__dot_D_1_3(t5, t6, t7, t9);
    result__[ 8   ] = -t3 * t71 * t82 + t4 * t82;
    result__[ 9   ] = t34 * t4 - t69 * t71;
    real_type t88  = t3 * t44;
    result__[ 10  ] = -t3 * t42 * t71 - t68 * t88 + t43;
    result__[ 11  ] = result__[7];
    real_type t92  = zeta__dot_D_2_2(t5, t6, t7, t9);
    real_type t95  = t3 * L__[iL_lambda2__xo];
    real_type t96  = sin(t6);
    real_type t98  = t96 * t5 * t95;
    result__[ 12  ] = -t3 * t71 * t92 + t4 * t92 - t98;
    real_type t101 = zeta__dot_D_1_2(t5, t6, t7, t9);
    real_type t103 = cos(t6);
    result__[ 13  ] = -t101 * t3 * t71 + t101 * t4 + t103 * t95;
    result__[ 14  ] = t103 * t5 * t95 + t4 * t44 - t71 * t88;
    real_type t111 = t3 * t54;
    result__[ 15  ] = -t3 * t52 * t71 - t111 * t68 + t53;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t115 = zeta__dot_D_1_1(t5, t6, t7, t9);
    real_type t119 = L__[iL_lambda4__xo];
    real_type t120 = ModelPars[iM_kD];
    real_type t121 = t120 * t119;
    result__[ 18  ] = -t115 * t3 * t71 + t115 * t4 - 2 * t121 * t3;
    result__[ 19  ] = -2 * t121 * t3 * t5 - t111 * t71 + t4 * t54 + t95 * t96;
    result__[ 20  ] = t3 * t19;
    result__[ 21  ] = t3 * t119;
    result__[ 22  ] = result__[4];
    result__[ 23  ] = result__[9];
    result__[ 24  ] = result__[14];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[21];
    real_type t138 = t5 * t5;
    result__[ 28  ] = t3 * ModelPars[iM_wT] + t20 * t4 + t98 - t3 * (t20 * t9 - X__[iX_Omega]) * t19 + t3 * (-t138 * t120 + X__[iX_fx]) * t119 + U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo] + U__[iU_v__fx] * ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 29, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DHpDp_numRows() const { return 0; }
  integer PointMassCarModel_4::DHpDp_numCols() const { return 0; }
  integer PointMassCarModel_4::DHpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::Hu_numEqns() const { return 2; }

  void
  PointMassCarModel_4::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    result__[ 0   ] = ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    result__[ 1   ] = ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DHuDxp_numRows() const { return 2; }
  integer PointMassCarModel_4::DHuDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DHuDxp_nnz()     const { return 2; }

  void
  PointMassCarModel_4::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }


  void
  PointMassCarModel_4::DHuDxp_sparse(
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
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    result__[ 0   ] = ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    result__[ 1   ] = ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 2, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::eta_numEqns() const { return 7; }

  void
  PointMassCarModel_4::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    result__[ 6   ] = L__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DetaDxp_numRows() const { return 7; }
  integer PointMassCarModel_4::DetaDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DetaDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::nu_numEqns() const { return 7; }

  void
  PointMassCarModel_4::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DnuDxp_numRows() const { return 7; }
  integer PointMassCarModel_4::DnuDxp_numCols() const { return 7; }
  integer PointMassCarModel_4::DnuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_4::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_4::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_4_Methods_AdjointODE.cc
