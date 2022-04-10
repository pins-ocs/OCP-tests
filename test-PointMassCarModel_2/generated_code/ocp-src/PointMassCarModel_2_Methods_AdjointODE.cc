/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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

  integer PointMassCarModel_2::JPx_numEqns() const { return 5; }

  void
  PointMassCarModel_2::JPx_eval(
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

  integer PointMassCarModel_2::LTx_numEqns() const { return 5; }

  void
  PointMassCarModel_2::LTx_eval(
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
    real_type t27  = t16 * t19 * t20 * t24 + t12 * t16 * t9 - 1;
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
    real_type t53  = t1 * t48 * t50 * t8 - 1;
    real_type t54  = PowerLimit(t53);
    real_type t55  = t54 * t7;
    real_type t57  = LimitMinSpeed(-t1);
    real_type t58  = t57 * t7;
    result__[ 0   ] = -t29 * t30 - t30 * t35 - t30 * t43 - t30 * t55 - t30 * t58 + t37 * t38 - t37 * t45;
    real_type t60  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t29 * t60 - t35 * t60 - t43 * t60 - t55 * t60 - t58 * t60;
    real_type t66  = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t68  = ALIAS_AdherenceEllipse_D(t27);
    real_type t69  = t68 * t37;
    real_type t78  = ALIAS_PowerLimit_D(t53);
    real_type t79  = t78 * t37;
    real_type t84  = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 2   ] = 2 * t1 * t16 * t19 * t24 * t69 + t48 * t50 * t79 * t8 - t29 * t66 - t35 * t66 - t37 * t84 - t43 * t66 - t55 * t66 - t58 * t66;
    result__[ 3   ] = 2 * t16 * t24 * t20 * t18 * t69;
    result__[ 4   ] = t1 * t48 * t50 * t79 + 2 * t12 * t16 * t69 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JUx_numEqns() const { return 5; }

  void
  PointMassCarModel_2::JUx_eval(
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t9   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t10  = t9 * t7;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t14  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t15  = t14 * t7;
    result__[ 0   ] = -t11 * t10 - t11 * t15;
    real_type t17  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t17 * t10 - t17 * t15;
    real_type t20  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t20 * t10 - t20 * t15;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JPp_numEqns() const { return 0; }

  void
  PointMassCarModel_2::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::LTp_numEqns() const { return 0; }

  void
  PointMassCarModel_2::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JUp_numEqns() const { return 0; }

  void
  PointMassCarModel_2::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JPu_numEqns() const { return 2; }

  void
  PointMassCarModel_2::JPu_eval(
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

  integer PointMassCarModel_2::LTu_numEqns() const { return 2; }

  void
  PointMassCarModel_2::LTu_eval(
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

  integer PointMassCarModel_2::JUu_numEqns() const { return 2; }

  void
  PointMassCarModel_2::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t8 * t6;
    real_type t10  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t10 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::LTargs_numEqns() const { return 5; }

  void
  PointMassCarModel_2::LTargs_eval(
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
  integer PointMassCarModel_2::DJPxDxp_numRows() const { return 5; }
  integer PointMassCarModel_2::DJPxDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DJPxDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTxDxp_numRows() const { return 5; }
  integer PointMassCarModel_2::DLTxDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DLTxDxp_nnz()     const { return 25; }

  void
  PointMassCarModel_2::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_2::DLTxDxp_sparse(
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
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 25, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJUxDxp_numRows() const { return 5; }
  integer PointMassCarModel_2::DJUxDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DJUxDxp_nnz()     const { return 9; }

  void
  PointMassCarModel_2::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_2::DJUxDxp_sparse(
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t8   = 1.0 / t6 / t5;
    real_type t10  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t11  = t10 * t8;
    real_type t12  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t13  = t12 * t12;
    real_type t16  = 1.0 / t6;
    real_type t17  = t10 * t16;
    real_type t18  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t21  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
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
    result__[ 2   ] = 2 * t37 * t11 - t40 * t17 + 2 * t37 * t22 - t40 * t25;
    result__[ 3   ] = result__[1];
    real_type t45  = t27 * t27;
    real_type t48  = zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 4   ] = 2 * t45 * t11 - t48 * t17 + 2 * t45 * t22 - t48 * t25;
    real_type t53  = t36 * t27;
    real_type t56  = zeta__dot_D_1_2(t1, t2, t3, t4);
    result__[ 5   ] = 2 * t53 * t11 - t56 * t17 + 2 * t53 * t22 - t56 * t25;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t61  = t36 * t36;
    real_type t64  = zeta__dot_D_1_1(t1, t2, t3, t4);
    result__[ 8   ] = 2 * t61 * t11 - t64 * t17 + 2 * t61 * t22 - t64 * t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUxDxp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJPuDxp_numRows() const { return 2; }
  integer PointMassCarModel_2::DJPuDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DJPuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTuDxp_numRows() const { return 2; }
  integer PointMassCarModel_2::DLTuDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DLTuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJUuDxp_numRows() const { return 2; }
  integer PointMassCarModel_2::DJUuDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DJUuDxp_nnz()     const { return 6; }

  void
  PointMassCarModel_2::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
  }


  void
  PointMassCarModel_2::DJUuDxp_sparse(
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t9   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    real_type t10  = t9 * t7;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    result__[ 0   ] = -t11 * t10;
    real_type t13  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t13 * t10;
    real_type t15  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t15 * t10;
    real_type t18  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    real_type t19  = t18 * t7;
    result__[ 3   ] = -t11 * t19;
    result__[ 4   ] = -t13 * t19;
    result__[ 5   ] = -t15 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJPpDp_numRows() const { return 0; }
  integer PointMassCarModel_2::DJPpDp_numCols() const { return 0; }
  integer PointMassCarModel_2::DJPpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTpDp_numRows() const { return 0; }
  integer PointMassCarModel_2::DLTpDp_numCols() const { return 0; }
  integer PointMassCarModel_2::DLTpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJUpDp_numRows() const { return 0; }
  integer PointMassCarModel_2::DJUpDp_numCols() const { return 0; }
  integer PointMassCarModel_2::DJUpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTargsDxup_numRows() const { return 5; }
  integer PointMassCarModel_2::DLTargsDxup_numCols() const { return 7; }
  integer PointMassCarModel_2::DLTargsDxup_nnz()     const { return 8; }

  void
  PointMassCarModel_2::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_2::DLTargsDxup_sparse(
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
  integer PointMassCarModel_2::D2LTargsD2xup_numRows() const { return 7; }
  integer PointMassCarModel_2::D2LTargsD2xup_numCols() const { return 7; }
  integer PointMassCarModel_2::D2LTargsD2xup_nnz()     const { return 7; }

  void
  PointMassCarModel_2::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 4   ;
  }


  void
  PointMassCarModel_2::D2LTargsD2xup_sparse(
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

  integer PointMassCarModel_2::Hx_numEqns() const { return 5; }

  void
  PointMassCarModel_2::Hx_eval(
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
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = zeta__dot(t2, t3, t4, t5);
    real_type t7   = t6 * t6;
    real_type t9   = 1.0 / t7 * ModelPars[iM_wT];
    real_type t10  = zeta__dot_D_3(t2, t3, t4, t5);
    real_type t12  = L__[iL_lambda2__xo];
    real_type t13  = t5 * t12;
    real_type t15  = L__[iL_lambda1__xo];
    real_type t17  = V__[0];
    real_type t20  = V__[1];
    real_type t22  = L__[iL_lambda3__xo];
    real_type t24  = V__[2];
    real_type t26  = L__[iL_lambda4__xo];
    real_type t28  = V__[4];
    real_type t30  = L__[iL_lambda5__xo];
    real_type t32  = V__[3];
    result__[ 0   ] = -t20 * t10 * t12 - t17 * t10 * t15 - t24 * t10 * t22 - t28 * t10 * t26 - t32 * t10 * t30 - t10 * t13 - t10 * t9;
    real_type t34  = zeta__dot_D_2(t2, t3, t4, t5);
    real_type t37  = cos(t3);
    result__[ 1   ] = -t20 * t34 * t12 - t17 * t34 * t15 + t37 * t2 * t15 - t24 * t34 * t22 - t28 * t34 * t26 - t32 * t34 * t30 - t34 * t13 - t34 * t9;
    real_type t50  = zeta__dot_D_1(t2, t3, t4, t5);
    real_type t52  = sin(t3);
    result__[ 2   ] = -t20 * t50 * t12 - t17 * t50 * t15 - 2 * t2 * ModelPars[iM_kD] * t22 - t24 * t50 * t22 - t28 * t50 * t26 - t32 * t50 * t30 - t50 * t13 + t52 * t15 - t50 * t9;
    result__[ 3   ] = t12;
    result__[ 4   ] = t22;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::Hp_numEqns() const { return 0; }

  void
  PointMassCarModel_2::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DHxDxp_numRows() const { return 5; }
  integer PointMassCarModel_2::DHxDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DHxDxp_nnz()     const { return 9; }

  void
  PointMassCarModel_2::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_2::DHxDxp_sparse(
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
    real_type t6   = zeta__dot(t2, t3, t4, t5);
    real_type t7   = t6 * t6;
    real_type t10  = 1.0 / t7 / t6 * t1;
    real_type t11  = zeta__dot_D_3(t2, t3, t4, t5);
    real_type t12  = t11 * t11;
    real_type t16  = 1.0 / t7 * t1;
    real_type t17  = zeta__dot_D_3_3(t2, t3, t4, t5);
    real_type t19  = L__[iL_lambda2__xo];
    real_type t20  = t5 * t19;
    real_type t22  = L__[iL_lambda1__xo];
    real_type t24  = V__[0];
    real_type t27  = V__[1];
    real_type t29  = L__[iL_lambda3__xo];
    real_type t31  = V__[2];
    real_type t33  = L__[iL_lambda4__xo];
    real_type t35  = V__[4];
    real_type t37  = L__[iL_lambda5__xo];
    real_type t39  = V__[3];
    result__[ 0   ] = -t27 * t17 * t19 - t24 * t17 * t22 - t31 * t17 * t29 - t35 * t17 * t33 - t39 * t17 * t37 + 2 * t12 * t10 - t17 * t16 - t17 * t20;
    real_type t41  = zeta__dot_D_2(t2, t3, t4, t5);
    real_type t45  = zeta__dot_D_2_3(t2, t3, t4, t5);
    result__[ 1   ] = 2 * t41 * t11 * t10 - t27 * t45 * t19 - t24 * t45 * t22 - t31 * t45 * t29 - t35 * t45 * t33 - t39 * t45 * t37 - t45 * t16 - t45 * t20;
    real_type t58  = zeta__dot_D_1(t2, t3, t4, t5);
    real_type t62  = zeta__dot_D_1_3(t2, t3, t4, t5);
    result__[ 2   ] = 2 * t58 * t11 * t10 - t27 * t62 * t19 - t24 * t62 * t22 - t31 * t62 * t29 - t35 * t62 * t33 - t39 * t62 * t37 - t62 * t16 - t62 * t20;
    result__[ 3   ] = result__[1];
    real_type t75  = t41 * t41;
    real_type t78  = zeta__dot_D_2_2(t2, t3, t4, t5);
    real_type t81  = sin(t3);
    result__[ 4   ] = -t27 * t78 * t19 - t81 * t2 * t22 - t24 * t78 * t22 - t31 * t78 * t29 - t35 * t78 * t33 - t39 * t78 * t37 + 2 * t75 * t10 - t78 * t16 - t78 * t20;
    real_type t97  = zeta__dot_D_1_2(t2, t3, t4, t5);
    real_type t99  = cos(t3);
    result__[ 5   ] = 2 * t58 * t41 * t10 - t27 * t97 * t19 - t24 * t97 * t22 - t31 * t97 * t29 - t35 * t97 * t33 - t39 * t97 * t37 - t97 * t16 - t97 * t20 + t99 * t22;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t112 = t58 * t58;
    real_type t115 = zeta__dot_D_1_1(t2, t3, t4, t5);
    result__[ 8   ] = -t27 * t115 * t19 - t24 * t115 * t22 - t31 * t115 * t29 - t35 * t115 * t33 - t39 * t115 * t37 + 2 * t112 * t10 - t115 * t16 - t115 * t20 - 2 * ModelPars[iM_kD] * t29;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DHpDp_numRows() const { return 0; }
  integer PointMassCarModel_2::DHpDp_numCols() const { return 0; }
  integer PointMassCarModel_2::DHpDp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DHpDp_sparse(
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

  integer PointMassCarModel_2::Hu_numEqns() const { return 2; }

  void
  PointMassCarModel_2::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda4__xo] * ModelPars[iM_v__fx__max];
    result__[ 1   ] = L__[iL_lambda5__xo] * ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DHuDxp_numRows() const { return 2; }
  integer PointMassCarModel_2::DHuDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DHuDxp_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::eta_numEqns() const { return 5; }

  void
  PointMassCarModel_2::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = L__[iL_lambda1__xo] * t5;
    result__[ 1   ] = L__[iL_lambda2__xo] * t5;
    result__[ 2   ] = L__[iL_lambda3__xo] * t5;
    result__[ 3   ] = L__[iL_lambda5__xo] * t5;
    result__[ 4   ] = L__[iL_lambda4__xo] * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DetaDxp_numRows() const { return 5; }
  integer PointMassCarModel_2::DetaDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DetaDxp_nnz()     const { return 15; }

  void
  PointMassCarModel_2::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 0   ;
    iIndex[10] = 3   ; jIndex[10] = 1   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
  }


  void
  PointMassCarModel_2::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = L__[iL_lambda1__xo];
    result__[ 0   ] = t6 * t5;
    real_type t7   = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t6 * t7;
    real_type t8   = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t6 * t8;
    real_type t9   = L__[iL_lambda2__xo];
    result__[ 3   ] = t9 * t5;
    result__[ 4   ] = t9 * t7;
    result__[ 5   ] = t9 * t8;
    real_type t10  = L__[iL_lambda3__xo];
    result__[ 6   ] = t10 * t5;
    result__[ 7   ] = t10 * t7;
    result__[ 8   ] = t10 * t8;
    real_type t11  = L__[iL_lambda5__xo];
    result__[ 9   ] = t11 * t5;
    result__[ 10  ] = t11 * t7;
    result__[ 11  ] = t11 * t8;
    real_type t12  = L__[iL_lambda4__xo];
    result__[ 12  ] = t12 * t5;
    result__[ 13  ] = t12 * t7;
    result__[ 14  ] = t12 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DetaDxp_sparse", 15, i_segment );
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::nu_numEqns() const { return 5; }

  void
  PointMassCarModel_2::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = V__[0] * t5;
    result__[ 1   ] = V__[1] * t5;
    result__[ 2   ] = V__[2] * t5;
    result__[ 3   ] = V__[4] * t5;
    result__[ 4   ] = V__[3] * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DnuDxp_numRows() const { return 5; }
  integer PointMassCarModel_2::DnuDxp_numCols() const { return 5; }
  integer PointMassCarModel_2::DnuDxp_nnz()     const { return 15; }

  void
  PointMassCarModel_2::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 0   ;
    iIndex[10] = 3   ; jIndex[10] = 1   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
  }


  void
  PointMassCarModel_2::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
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
    real_type t5   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = V__[0];
    result__[ 0   ] = t6 * t5;
    real_type t7   = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t6 * t7;
    real_type t8   = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t6 * t8;
    real_type t9   = V__[1];
    result__[ 3   ] = t9 * t5;
    result__[ 4   ] = t9 * t7;
    result__[ 5   ] = t9 * t8;
    real_type t10  = V__[2];
    result__[ 6   ] = t10 * t5;
    result__[ 7   ] = t10 * t7;
    result__[ 8   ] = t10 * t8;
    real_type t11  = V__[4];
    result__[ 9   ] = t11 * t5;
    result__[ 10  ] = t11 * t7;
    result__[ 11  ] = t11 * t8;
    real_type t12  = V__[3];
    result__[ 12  ] = t12 * t5;
    result__[ 13  ] = t12 * t7;
    result__[ 14  ] = t12 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DnuDxp_sparse", 15, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
