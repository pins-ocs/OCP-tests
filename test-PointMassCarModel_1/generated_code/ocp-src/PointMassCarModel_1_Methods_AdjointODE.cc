/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JPx_numEqns() const { return 5; }

  void
  PointMassCarModel_1::JPx_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::LTx_numEqns() const { return 5; }

  void
  PointMassCarModel_1::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
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
    real_type t25  = t14 * t17 * t18 * t22 + t10 * t14 * t7 - 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = t3 - Q__[iQ_leftWidth];
    real_type t30  = RoadLeftBorder(t29);
    real_type t32  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t33  = ALIAS_RoadLeftBorder_D(t29);
    real_type t36  = -t3 - Q__[iQ_rightWidth];
    real_type t37  = RoadRightBorder(t36);
    real_type t39  = ALIAS_RoadRightBorder_D(t36);
    real_type t42  = ModelPars[iM_m];
    real_type t44  = 1.0 / ModelPars[iM_Pmax];
    real_type t47  = t1 * t42 * t44 * t6 - 1;
    real_type t48  = PowerLimit(t47);
    real_type t50  = LimitMinSpeed(-t1);
    result__[ 0   ] = t26 * t5 + t30 * t5 + t32 * t33 - t32 * t39 + t37 * t5 + t48 * t5 + t5 * t50;
    real_type t52  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t26 * t52 + t30 * t52 + t37 * t52 + t48 * t52 + t50 * t52;
    real_type t58  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t60  = ALIAS_AdherenceEllipse_D(t25);
    real_type t61  = t60 * t32;
    real_type t70  = ALIAS_PowerLimit_D(t47);
    real_type t71  = t70 * t32;
    real_type t76  = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 2   ] = 2 * t1 * t14 * t17 * t22 * t61 + t42 * t44 * t6 * t71 + t26 * t58 + t30 * t58 - t32 * t76 + t37 * t58 + t48 * t58 + t50 * t58;
    result__[ 3   ] = 2 * t14 * t22 * t18 * t16 * t61;
    result__[ 4   ] = t1 * t42 * t44 * t71 + 2 * t10 * t14 * t6 * t61;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JUx_numEqns() const { return 5; }

  void
  PointMassCarModel_1::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t7   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t10  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 0   ] = t10 * t5 + t7 * t5;
    real_type t12  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t10 * t12 + t7 * t12;
    real_type t15  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t10 * t15 + t7 * t15;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JPp_numEqns() const { return 0; }

  void
  PointMassCarModel_1::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::LTp_numEqns() const { return 0; }

  void
  PointMassCarModel_1::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JUp_numEqns() const { return 0; }

  void
  PointMassCarModel_1::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JPu_numEqns() const { return 2; }

  void
  PointMassCarModel_1::JPu_eval(
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

  integer PointMassCarModel_1::LTu_numEqns() const { return 2; }

  void
  PointMassCarModel_1::LTu_eval(
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

  integer PointMassCarModel_1::JUu_numEqns() const { return 2; }

  void
  PointMassCarModel_1::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t7 * t5;
    real_type t9   = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t9 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::LTargs_numEqns() const { return 5; }

  void
  PointMassCarModel_1::LTargs_eval(
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
    result__[ 1   ] = t21 - Q__[iQ_leftWidth];
    result__[ 2   ] = -t21 - Q__[iQ_rightWidth];
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13 - 1;
    result__[ 4   ] = -t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJPxDxp_numRows() const { return 5; }
  integer PointMassCarModel_1::DJPxDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DJPxDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DLTxDxp_numRows() const { return 5; }
  integer PointMassCarModel_1::DLTxDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DLTxDxp_nnz()     const { return 25; }

  void
  PointMassCarModel_1::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3_3(t1, t2, t3, t4);
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
    real_type t25  = t14 * t22 * t18 * t17 + t14 * t10 * t7 - 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = t3 - Q__[iQ_leftWidth];
    real_type t30  = RoadLeftBorder(t29);
    real_type t32  = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t33  = ALIAS_RoadLeftBorder_D(t29);
    real_type t36  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t37  = ALIAS_RoadLeftBorder_DD(t29);
    real_type t40  = -t3 - Q__[iQ_rightWidth];
    real_type t41  = RoadRightBorder(t40);
    real_type t43  = ALIAS_RoadRightBorder_D(t40);
    real_type t46  = ALIAS_RoadRightBorder_DD(t40);
    real_type t49  = ModelPars[iM_m];
    real_type t50  = ModelPars[iM_Pmax];
    real_type t51  = 1.0 / t50;
    real_type t52  = t51 * t49;
    real_type t54  = t52 * t6 * t1 - 1;
    real_type t55  = PowerLimit(t54);
    real_type t57  = LimitMinSpeed(-t1);
    result__[ 0   ] = t26 * t5 + t30 * t5 + 2 * t33 * t32 - 2 * t43 * t32 + t37 * t36 + t46 * t36 + t41 * t5 + t55 * t5 + t57 * t5;
    real_type t59  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t62  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t26 * t59 + t30 * t59 + t33 * t62 + t41 * t59 - t43 * t62 + t55 * t59 + t57 * t59;
    real_type t68  = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t70  = ALIAS_AdherenceEllipse_D(t25);
    real_type t71  = t70 * t32;
    real_type t73  = t22 * t1;
    real_type t74  = t14 * t73;
    real_type t78  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t83  = ALIAS_PowerLimit_D(t54);
    real_type t84  = t83 * t32;
    real_type t86  = t51 * t49 * t6;
    real_type t89  = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 2   ] = 2 * t74 * t17 * t71 + t26 * t68 + t30 * t68 - t89 * t32 + t33 * t78 + t41 * t68 - t43 * t78 + t55 * t68 + t57 * t68 + t86 * t84;
    real_type t92  = t22 * t18;
    real_type t93  = t14 * t92;
    result__[ 3   ] = 2 * t93 * t16 * t71;
    real_type t95  = t10 * t6;
    real_type t96  = t14 * t95;
    real_type t100 = t51 * t49 * t1;
    result__[ 4   ] = t100 * t84 + 2 * t96 * t71;
    result__[ 5   ] = result__[1];
    real_type t102 = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = t26 * t102 + t30 * t102 + t41 * t102 + t55 * t102 + t57 * t102;
    real_type t108 = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t110 = t70 * t62;
    real_type t117 = t83 * t62;
    result__[ 7   ] = 2 * t74 * t17 * t110 + t26 * t108 + t30 * t108 + t41 * t108 + t55 * t108 + t57 * t108 + t86 * t117 - t89 * t62;
    result__[ 8   ] = 2 * t93 * t16 * t110;
    result__[ 9   ] = t100 * t117 + 2 * t96 * t110;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t126 = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t128 = t70 * t78;
    real_type t132 = ALIAS_AdherenceEllipse_DD(t25);
    real_type t133 = t132 * t36;
    real_type t134 = t17 * t17;
    real_type t136 = t21 * t21;
    real_type t137 = 1.0 / t136;
    real_type t139 = t13 * t13;
    real_type t140 = 1.0 / t139;
    real_type t144 = t70 * t36;
    real_type t152 = t83 * t78;
    real_type t155 = ALIAS_PowerLimit_DD(t54);
    real_type t156 = t155 * t36;
    real_type t157 = t49 * t49;
    real_type t159 = t50 * t50;
    real_type t160 = 1.0 / t159;
    real_type t166 = ALIAS_LimitMinSpeed_DD(-t1);
    result__[ 12  ] = 4 * t140 * t137 * t18 * t134 * t133 + 2 * t14 * t22 * t17 * t144 + t160 * t157 * t7 * t156 + 4 * t74 * t17 * t128 + t26 * t126 + t30 * t126 + t41 * t126 + t55 * t126 + t57 * t126 + 2 * t86 * t152 + t166 * t36 - 2 * t89 * t78;
    result__[ 13  ] = 4 * t140 * t137 * t18 * t1 * t17 * t16 * t133 + 2 * t93 * t16 * t128 + 4 * t74 * t16 * t144;
    real_type t183 = t95 * t133;
    result__[ 14  ] = t6 * t160 * t157 * t1 * t156 + 4 * t73 * t17 * t140 * t183 + t52 * t83 * t36 + t100 * t152 + 2 * t96 * t128;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t196 = t18 * t18;
    result__[ 18  ] = 4 * t140 * t137 * t196 * t17 * t133 + 2 * t93 * t144;
    result__[ 19  ] = 4 * t92 * t16 * t140 * t183;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t206 = t9 * t9;
    result__[ 24  ] = 4 * t140 / t206 * t7 * t133 + 2 * t14 * t10 * t144 + t160 * t157 * t18 * t156;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 25, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJUxDxp_numRows() const { return 5; }
  integer PointMassCarModel_1::DJUxDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DJUxDxp_nnz()     const { return 9; }

  void
  PointMassCarModel_1::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
  }


  void
  PointMassCarModel_1::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t7   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t10  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 0   ] = t10 * t5 + t7 * t5;
    real_type t12  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    result__[ 1   ] = t10 * t12 + t7 * t12;
    real_type t15  = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    result__[ 2   ] = t10 * t15 + t7 * t15;
    result__[ 3   ] = result__[1];
    real_type t18  = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 4   ] = t10 * t18 + t7 * t18;
    real_type t21  = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    result__[ 5   ] = t10 * t21 + t7 * t21;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t24  = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    result__[ 8   ] = t10 * t24 + t7 * t24;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUxDxp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJPuDxp_numRows() const { return 2; }
  integer PointMassCarModel_1::DJPuDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DJPuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DLTuDxp_numRows() const { return 2; }
  integer PointMassCarModel_1::DLTuDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DLTuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJUuDxp_numRows() const { return 2; }
  integer PointMassCarModel_1::DJUuDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DJUuDxp_nnz()     const { return 6; }

  void
  PointMassCarModel_1::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
  }


  void
  PointMassCarModel_1::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t7   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t7 * t5;
    real_type t8   = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t7 * t8;
    real_type t9   = inv_zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t7 * t9;
    real_type t11  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 3   ] = t11 * t5;
    result__[ 4   ] = t11 * t8;
    result__[ 5   ] = t11 * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJPpDp_numRows() const { return 0; }
  integer PointMassCarModel_1::DJPpDp_numCols() const { return 0; }
  integer PointMassCarModel_1::DJPpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DLTpDp_numRows() const { return 0; }
  integer PointMassCarModel_1::DLTpDp_numCols() const { return 0; }
  integer PointMassCarModel_1::DLTpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJUpDp_numRows() const { return 0; }
  integer PointMassCarModel_1::DJUpDp_numCols() const { return 0; }
  integer PointMassCarModel_1::DJUpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DLTargsDxup_numRows() const { return 5; }
  integer PointMassCarModel_1::DLTargsDxup_numCols() const { return 7; }
  integer PointMassCarModel_1::DLTargsDxup_nnz()     const { return 8; }

  void
  PointMassCarModel_1::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::DLTargsDxup_sparse(
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
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    real_type t22  = ModelPars[iM_m];
    real_type t25  = 1.0 / ModelPars[iM_Pmax];
    result__[ 5   ] = t25 * t22 * t16;
    result__[ 6   ] = t25 * t22 * t3;
    result__[ 7   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 8, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::D2LTargsD2xup_numRows() const { return 7; }
  integer PointMassCarModel_1::D2LTargsD2xup_numCols() const { return 7; }
  integer PointMassCarModel_1::D2LTargsD2xup_nnz()     const { return 7; }

  void
  PointMassCarModel_1::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 4   ;
  }


  void
  PointMassCarModel_1::D2LTargsD2xup_sparse(
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
      Mechatronix::check_in_segment( result__, "D2LTargsD2xup_sparse", 7, i_segment );
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

  integer PointMassCarModel_1::Hx_numEqns() const { return 5; }

  void
  PointMassCarModel_1::Hx_eval(
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
    real_type t1   = ModelPars[iM_wT];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = inv_zeta__dot_D_3(t2, t3, t4, t5);
    real_type t8   = L__[iL_lambda1__xo];
    real_type t9   = t2 * t8;
    real_type t10  = sin(t3);
    real_type t13  = L__[iL_lambda2__xo];
    real_type t15  = X__[iX_Omega] * t13;
    real_type t17  = L__[iL_lambda3__xo];
    real_type t19  = ModelPars[iM_kD];
    real_type t20  = t2 * t2;
    real_type t23  = -t19 * t20 + X__[iX_fx];
    real_type t27  = L__[iL_lambda4__xo] * U__[iU_v__Omega];
    real_type t28  = ModelPars[iM_v__Omega__max];
    real_type t33  = L__[iL_lambda5__xo] * U__[iU_v__fx];
    real_type t34  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t10 * t6 * t9 + t17 * t23 * t6 + t27 * t28 * t6 + t33 * t34 * t6 + t1 * t6 + t15 * t6;
    real_type t37  = inv_zeta__dot_D_2(t2, t3, t4, t5);
    real_type t39  = cos(t3);
    real_type t40  = inv_zeta__dot(t2, t3, t4, t5);
    result__[ 1   ] = t10 * t37 * t9 + t17 * t23 * t37 + t27 * t28 * t37 + t33 * t34 * t37 + t39 * t40 * t9 + t1 * t37 + t15 * t37;
    real_type t52  = inv_zeta__dot_D_1(t2, t3, t4, t5);
    real_type t61  = t40 * t17;
    result__[ 2   ] = t10 * t40 * t8 + t10 * t52 * t9 + t17 * t23 * t52 - 2 * t19 * t2 * t61 + t27 * t28 * t52 + t33 * t34 * t52 + t1 * t52 + t15 * t52;
    result__[ 3   ] = t40 * t13;
    result__[ 4   ] = t61;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::Hp_numEqns() const { return 0; }

  void
  PointMassCarModel_1::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DHxDxp_numRows() const { return 5; }
  integer PointMassCarModel_1::DHxDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DHxDxp_nnz()     const { return 21; }

  void
  PointMassCarModel_1::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[18] = 4   ; jIndex[18] = 0   ;
    iIndex[19] = 4   ; jIndex[19] = 1   ;
    iIndex[20] = 4   ; jIndex[20] = 2   ;
  }


  void
  PointMassCarModel_1::DHxDxp_sparse(
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
    real_type t1   = ModelPars[iM_wT];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = inv_zeta__dot_D_3_3(t2, t3, t4, t5);
    real_type t8   = L__[iL_lambda1__xo];
    real_type t9   = t2 * t8;
    real_type t10  = sin(t3);
    real_type t13  = L__[iL_lambda2__xo];
    real_type t15  = X__[iX_Omega] * t13;
    real_type t17  = L__[iL_lambda3__xo];
    real_type t19  = ModelPars[iM_kD];
    real_type t20  = t2 * t2;
    real_type t23  = -t20 * t19 + X__[iX_fx];
    real_type t27  = L__[iL_lambda4__xo] * U__[iU_v__Omega];
    real_type t28  = ModelPars[iM_v__Omega__max];
    real_type t33  = L__[iL_lambda5__xo] * U__[iU_v__fx];
    real_type t34  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t6 * t10 * t9 + t23 * t6 * t17 + t6 * t28 * t27 + t6 * t34 * t33 + t6 * t1 + t6 * t15;
    real_type t37  = inv_zeta__dot_D_2_3(t2, t3, t4, t5);
    real_type t39  = cos(t3);
    real_type t40  = inv_zeta__dot_D_3(t2, t3, t4, t5);
    result__[ 1   ] = t37 * t10 * t9 + t23 * t37 * t17 + t37 * t28 * t27 + t37 * t34 * t33 + t40 * t39 * t9 + t37 * t1 + t37 * t15;
    real_type t52  = inv_zeta__dot_D_1_3(t2, t3, t4, t5);
    real_type t54  = t10 * t8;
    real_type t61  = t40 * t17;
    real_type t62  = t2 * t19;
    result__[ 2   ] = t52 * t10 * t9 + t23 * t52 * t17 + t52 * t28 * t27 + t52 * t34 * t33 + t52 * t1 + t52 * t15 + t40 * t54 - 2 * t62 * t61;
    result__[ 3   ] = t40 * t13;
    result__[ 4   ] = t61;
    result__[ 5   ] = result__[1];
    real_type t69  = inv_zeta__dot_D_2_2(t2, t3, t4, t5);
    real_type t71  = inv_zeta__dot(t2, t3, t4, t5);
    real_type t74  = inv_zeta__dot_D_2(t2, t3, t4, t5);
    result__[ 6   ] = t69 * t10 * t9 - t71 * t10 * t9 + t23 * t69 * t17 + t69 * t28 * t27 + t69 * t34 * t33 + 2 * t74 * t39 * t9 + t69 * t1 + t69 * t15;
    real_type t87  = inv_zeta__dot_D_1_2(t2, t3, t4, t5);
    real_type t91  = inv_zeta__dot_D_1(t2, t3, t4, t5);
    real_type t100 = t74 * t17;
    result__[ 7   ] = t87 * t10 * t9 + t23 * t87 * t17 + t87 * t28 * t27 + t87 * t34 * t33 + t71 * t39 * t8 + t91 * t39 * t9 + t87 * t1 - 2 * t62 * t100 + t87 * t15 + t74 * t54;
    result__[ 8   ] = t74 * t13;
    result__[ 9   ] = t100;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t107 = inv_zeta__dot_D_1_1(t2, t3, t4, t5);
    real_type t116 = t91 * t17;
    result__[ 12  ] = t107 * t10 * t9 + t23 * t107 * t17 + t107 * t28 * t27 + t107 * t34 * t33 - 2 * t19 * t71 * t17 + t107 * t1 + t107 * t15 - 4 * t62 * t116 + 2 * t91 * t54;
    result__[ 13  ] = t91 * t13;
    result__[ 14  ] = t116;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    result__[ 18  ] = result__[4];
    result__[ 19  ] = result__[9];
    result__[ 20  ] = result__[14];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 21, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DHpDp_numRows() const { return 0; }
  integer PointMassCarModel_1::DHpDp_numCols() const { return 0; }
  integer PointMassCarModel_1::DHpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DHpDp_sparse(
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

  integer PointMassCarModel_1::Hu_numEqns() const { return 2; }

  void
  PointMassCarModel_1::Hu_eval(
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
    real_type t8   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = t8 * ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo];
    result__[ 1   ] = t8 * ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DHuDxp_numRows() const { return 2; }
  integer PointMassCarModel_1::DHuDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DHuDxp_nnz()     const { return 6; }

  void
  PointMassCarModel_1::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
  }


  void
  PointMassCarModel_1::DHuDxp_sparse(
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
    real_type t3   = ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo];
    real_type t4   = X__[iX_V];
    real_type t5   = X__[iX_alpha];
    real_type t6   = X__[iX_n];
    real_type t7   = Q__[iQ_Kappa];
    real_type t8   = inv_zeta__dot_D_3(t4, t5, t6, t7);
    result__[ 0   ] = t8 * t3;
    real_type t9   = inv_zeta__dot_D_2(t4, t5, t6, t7);
    result__[ 1   ] = t9 * t3;
    real_type t10  = inv_zeta__dot_D_1(t4, t5, t6, t7);
    result__[ 2   ] = t10 * t3;
    real_type t13  = ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo];
    result__[ 3   ] = t8 * t13;
    result__[ 4   ] = t9 * t13;
    result__[ 5   ] = t10 * t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 6, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::eta_numEqns() const { return 5; }

  void
  PointMassCarModel_1::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DetaDxp_numRows() const { return 5; }
  integer PointMassCarModel_1::DetaDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DetaDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DetaDxp_sparse(
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

  integer PointMassCarModel_1::nu_numEqns() const { return 5; }

  void
  PointMassCarModel_1::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DnuDxp_numRows() const { return 5; }
  integer PointMassCarModel_1::DnuDxp_numCols() const { return 5; }
  integer PointMassCarModel_1::DnuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_1_Methods_AdjointODE.cc
