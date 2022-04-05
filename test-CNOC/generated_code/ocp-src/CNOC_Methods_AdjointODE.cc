/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_AdjointODE.cc                                     |
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


#include "CNOC.hh"
#include "CNOC_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::ToolPath2D;


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
#define ALIAS_nominalFeed_R(___dummy___) segmentRight.feed_reference_rate()
#define ALIAS_nominalFeed_L(___dummy___) segmentLeft.feed_reference_rate()
#define ALIAS_nominalFeed(___dummy___) segment.feed_reference_rate()
#define ALIAS_yLimitRight_R(__t1, __t2) segmentRight.y_ISO( __t1, __t2)
#define ALIAS_yLimitRight_L(__t1, __t2) segmentLeft.y_ISO( __t1, __t2)
#define ALIAS_yLimitRight(__t1, __t2) segment.y_ISO( __t1, __t2)
#define ALIAS_xLimitRight_R(__t1, __t2) segmentRight.x_ISO( __t1, __t2)
#define ALIAS_xLimitRight_L(__t1, __t2) segmentLeft.x_ISO( __t1, __t2)
#define ALIAS_xLimitRight(__t1, __t2) segment.x_ISO( __t1, __t2)
#define ALIAS_yLimitLeft_R(__t1, __t2) segmentRight.y_ISO( __t1, __t2)
#define ALIAS_yLimitLeft_L(__t1, __t2) segmentLeft.y_ISO( __t1, __t2)
#define ALIAS_yLimitLeft(__t1, __t2) segment.y_ISO( __t1, __t2)
#define ALIAS_xLimitLeft_R(__t1, __t2) segmentRight.x_ISO( __t1, __t2)
#define ALIAS_xLimitLeft_L(__t1, __t2) segmentLeft.x_ISO( __t1, __t2)
#define ALIAS_xLimitLeft(__t1, __t2) segment.x_ISO( __t1, __t2)
#define ALIAS_yTraj_R(__t1, __t2) segmentRight.y_ISO( __t1, __t2)
#define ALIAS_yTraj_L(__t1, __t2) segmentLeft.y_ISO( __t1, __t2)
#define ALIAS_yTraj(__t1, __t2) segment.y_ISO( __t1, __t2)
#define ALIAS_xTraj_R(__t1, __t2) segmentRight.x_ISO( __t1, __t2)
#define ALIAS_xTraj_L(__t1, __t2) segmentLeft.x_ISO( __t1, __t2)
#define ALIAS_xTraj(__t1, __t2) segment.x_ISO( __t1, __t2)
#define ALIAS_yPath_R_DD(__t1) segmentRight.y_DD( __t1)
#define ALIAS_yPath_R_D(__t1) segmentRight.y_D( __t1)
#define ALIAS_yPath_R(__t1) segmentRight.y( __t1)
#define ALIAS_yPath_L_DD(__t1) segmentLeft.y_DD( __t1)
#define ALIAS_yPath_L_D(__t1) segmentLeft.y_D( __t1)
#define ALIAS_yPath_L(__t1) segmentLeft.y( __t1)
#define ALIAS_yPath_DD(__t1) segment.y_DD( __t1)
#define ALIAS_yPath_D(__t1) segment.y_D( __t1)
#define ALIAS_yPath(__t1) segment.y( __t1)
#define ALIAS_xPath_R_DD(__t1) segmentRight.x_DD( __t1)
#define ALIAS_xPath_R_D(__t1) segmentRight.x_D( __t1)
#define ALIAS_xPath_R(__t1) segmentRight.x( __t1)
#define ALIAS_xPath_L_DD(__t1) segmentLeft.x_DD( __t1)
#define ALIAS_xPath_L_D(__t1) segmentLeft.x_D( __t1)
#define ALIAS_xPath_L(__t1) segmentLeft.x( __t1)
#define ALIAS_xPath_DD(__t1) segment.x_DD( __t1)
#define ALIAS_xPath_D(__t1) segment.x_D( __t1)
#define ALIAS_xPath(__t1) segment.x( __t1)
#define ALIAS_theta_R_DD(__t1) segmentRight.angle_DD( __t1)
#define ALIAS_theta_R_D(__t1) segmentRight.angle_D( __t1)
#define ALIAS_theta_R(__t1) segmentRight.angle( __t1)
#define ALIAS_theta_L_DD(__t1) segmentLeft.angle_DD( __t1)
#define ALIAS_theta_L_D(__t1) segmentLeft.angle_D( __t1)
#define ALIAS_theta_L(__t1) segmentLeft.angle( __t1)
#define ALIAS_theta_DD(__t1) segment.angle_DD( __t1)
#define ALIAS_theta_D(__t1) segment.angle_D( __t1)
#define ALIAS_theta(__t1) segment.angle( __t1)
#define ALIAS_kappa_R_DD(__t1) segmentRight.curvature_DD( __t1)
#define ALIAS_kappa_R_D(__t1) segmentRight.curvature_D( __t1)
#define ALIAS_kappa_R(__t1) segmentRight.curvature( __t1)
#define ALIAS_kappa_L_DD(__t1) segmentLeft.curvature_DD( __t1)
#define ALIAS_kappa_L_D(__t1) segmentLeft.curvature_D( __t1)
#define ALIAS_kappa_L(__t1) segmentLeft.curvature( __t1)
#define ALIAS_kappa_DD(__t1) segment.curvature_DD( __t1)
#define ALIAS_kappa_D(__t1) segment.curvature_D( __t1)
#define ALIAS_kappa(__t1) segment.curvature( __t1)
#define ALIAS_lenSeg_R(___dummy___) segmentRight.ss_length()
#define ALIAS_lenSeg_L(___dummy___) segmentLeft.ss_length()
#define ALIAS_lenSeg(___dummy___) segment.ss_length()
#define ALIAS_ay_limit_max_DD(__t1) ay_limit_max.DD( __t1)
#define ALIAS_ay_limit_max_D(__t1) ay_limit_max.D( __t1)
#define ALIAS_ay_limit_min_DD(__t1) ay_limit_min.DD( __t1)
#define ALIAS_ay_limit_min_D(__t1) ay_limit_min.D( __t1)
#define ALIAS_ax_limit_max_DD(__t1) ax_limit_max.DD( __t1)
#define ALIAS_ax_limit_max_D(__t1) ax_limit_max.D( __t1)
#define ALIAS_ax_limit_min_DD(__t1) ax_limit_min.DD( __t1)
#define ALIAS_ax_limit_min_D(__t1) ax_limit_min.D( __t1)
#define ALIAS_an_limit_max_DD(__t1) an_limit_max.DD( __t1)
#define ALIAS_an_limit_max_D(__t1) an_limit_max.D( __t1)
#define ALIAS_an_limit_min_DD(__t1) an_limit_min.DD( __t1)
#define ALIAS_an_limit_min_D(__t1) an_limit_min.D( __t1)
#define ALIAS_as_limit_max_DD(__t1) as_limit_max.DD( __t1)
#define ALIAS_as_limit_max_D(__t1) as_limit_max.D( __t1)
#define ALIAS_as_limit_min_DD(__t1) as_limit_min.DD( __t1)
#define ALIAS_as_limit_min_D(__t1) as_limit_min.D( __t1)
#define ALIAS_PathFollowingTolerance_max_DD(__t1) PathFollowingTolerance_max.DD( __t1)
#define ALIAS_PathFollowingTolerance_max_D(__t1) PathFollowingTolerance_max.D( __t1)
#define ALIAS_PathFollowingTolerance_min_DD(__t1) PathFollowingTolerance_min.DD( __t1)
#define ALIAS_PathFollowingTolerance_min_D(__t1) PathFollowingTolerance_min.D( __t1)
#define ALIAS_vLimit_DD(__t1) vLimit.DD( __t1)
#define ALIAS_vLimit_D(__t1) vLimit.D( __t1)
#define ALIAS_timePositive_DD(__t1) timePositive.DD( __t1)
#define ALIAS_timePositive_D(__t1) timePositive.D( __t1)
#define ALIAS_jnControl_D_3(__t1, __t2, __t3) jnControl.D_3( __t1, __t2, __t3)
#define ALIAS_jnControl_D_2(__t1, __t2, __t3) jnControl.D_2( __t1, __t2, __t3)
#define ALIAS_jnControl_D_1(__t1, __t2, __t3) jnControl.D_1( __t1, __t2, __t3)
#define ALIAS_jnControl_D_3_3(__t1, __t2, __t3) jnControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jnControl_D_2_3(__t1, __t2, __t3) jnControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jnControl_D_2_2(__t1, __t2, __t3) jnControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jnControl_D_1_3(__t1, __t2, __t3) jnControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jnControl_D_1_2(__t1, __t2, __t3) jnControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jnControl_D_1_1(__t1, __t2, __t3) jnControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_jsControl_D_3(__t1, __t2, __t3) jsControl.D_3( __t1, __t2, __t3)
#define ALIAS_jsControl_D_2(__t1, __t2, __t3) jsControl.D_2( __t1, __t2, __t3)
#define ALIAS_jsControl_D_1(__t1, __t2, __t3) jsControl.D_1( __t1, __t2, __t3)
#define ALIAS_jsControl_D_3_3(__t1, __t2, __t3) jsControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jsControl_D_2_3(__t1, __t2, __t3) jsControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jsControl_D_2_2(__t1, __t2, __t3) jsControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jsControl_D_1_3(__t1, __t2, __t3) jsControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jsControl_D_1_2(__t1, __t2, __t3) jsControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jsControl_D_1_1(__t1, __t2, __t3) jsControl.D_1_1( __t1, __t2, __t3)


namespace CNOCDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JPx_numEqns() const { return 7; }

  void
  CNOC::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
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

  integer CNOC::LTx_numEqns() const { return 7; }

  void
  CNOC::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t2   = X__[iX_as];
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_theta(t3);
    real_type t5   = cos(t4);
    real_type t7   = X__[iX_an];
    real_type t8   = sin(t4);
    real_type t12  = 1.0 / ModelPars[iM_ax_max];
    real_type t13  = t12 * (t5 * t2 - t8 * t7);
    real_type t14  = -1 - t13;
    real_type t15  = ALIAS_ax_limit_min_D(t14);
    real_type t16  = t15 * t1;
    real_type t17  = ALIAS_theta_D(t3);
    real_type t18  = t17 * t2;
    real_type t20  = t17 * t7;
    real_type t23  = t12 * (-t8 * t18 - t5 * t20);
    real_type t25  = t13 - 1;
    real_type t26  = ALIAS_ax_limit_max_D(t25);
    real_type t27  = t26 * t1;
    real_type t33  = 1.0 / ModelPars[iM_ay_max];
    real_type t34  = t33 * (t8 * t2 + t5 * t7);
    real_type t35  = -1 - t34;
    real_type t36  = ALIAS_ay_limit_min_D(t35);
    real_type t37  = t36 * t1;
    real_type t41  = t33 * (t5 * t18 - t8 * t20);
    real_type t43  = t34 - 1;
    real_type t44  = ALIAS_ay_limit_max_D(t43);
    real_type t45  = t44 * t1;
    result__[ 0   ] = -t23 * t16 + t23 * t27 - t41 * t37 + t41 * t45;
    real_type t49  = 1.0 / ModelPars[iM_path_following_tolerance];
    real_type t50  = t49 * X__[iX_n];
    real_type t51  = -1 - t50;
    real_type t52  = ALIAS_PathFollowingTolerance_min_D(t51);
    real_type t55  = t50 - 1;
    real_type t56  = ALIAS_PathFollowingTolerance_max_D(t55);
    result__[ 1   ] = -t49 * t52 * t1 + t49 * t56 * t1;
    real_type t59  = X__[iX_vs];
    real_type t60  = t59 * t59;
    real_type t61  = X__[iX_vn];
    real_type t62  = t61 * t61;
    real_type t64  = sqrt(t60 + t62);
    real_type t65  = ALIAS_nominalFeed();
    real_type t66  = 1.0 / t65;
    real_type t68  = t66 * t64 - 0.101e1;
    real_type t69  = ALIAS_vLimit_D(t68);
    real_type t70  = t69 * t1;
    real_type t72  = t66 / t64;
    result__[ 2   ] = t59 * t72 * t70;
    result__[ 3   ] = t61 * t72 * t70;
    real_type t76  = 1.0 / ModelPars[iM_as_max];
    real_type t77  = t76 * t2;
    real_type t78  = -1 - t77;
    real_type t79  = ALIAS_as_limit_min_D(t78);
    real_type t82  = t77 - 1;
    real_type t83  = ALIAS_as_limit_max_D(t82);
    real_type t86  = t12 * t5;
    real_type t89  = t33 * t8;
    result__[ 4   ] = -t76 * t79 * t1 + t76 * t83 * t1 - t86 * t16 + t86 * t27 - t89 * t37 + t89 * t45;
    real_type t93  = 1.0 / ModelPars[iM_an_max];
    real_type t94  = t93 * t7;
    real_type t95  = -1 - t94;
    real_type t96  = ALIAS_an_limit_min_D(t95);
    real_type t99  = t94 - 1;
    real_type t100 = ALIAS_an_limit_max_D(t99);
    real_type t103 = t12 * t8;
    real_type t106 = t33 * t5;
    result__[ 5   ] = t93 * t100 * t1 - t93 * t96 * t1 + t103 * t16 - t103 * t27 - t106 * t37 + t106 * t45;
    real_type t109 = ALIAS_timePositive_D(-t1);
    real_type t110 = vLimit(t68);
    real_type t111 = PathFollowingTolerance_min(t51);
    real_type t112 = PathFollowingTolerance_max(t55);
    real_type t113 = as_limit_min(t78);
    real_type t114 = as_limit_max(t82);
    real_type t115 = an_limit_min(t95);
    real_type t116 = an_limit_max(t99);
    real_type t117 = ax_limit_min(t14);
    real_type t118 = ax_limit_max(t25);
    real_type t119 = ay_limit_min(t35);
    real_type t120 = ay_limit_max(t43);
    result__[ 6   ] = -t109 + t110 + t111 + t112 + t113 + t114 + t115 + t116 + t117 + t118 + t119 + t120;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JUx_numEqns() const { return 7; }

  void
  CNOC::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    real_type t4   = jsControl(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t6   = ModelPars[iM_jn_max];
    real_type t7   = jnControl(U__[iU_jn], -t6, t6);
    result__[ 6   ] = t4 + t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JPp_numEqns() const { return 0; }

  void
  CNOC::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::LTp_numEqns() const { return 0; }

  void
  CNOC::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JUp_numEqns() const { return 0; }

  void
  CNOC::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JPu_numEqns() const { return 2; }

  void
  CNOC::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::LTu_numEqns() const { return 2; }

  void
  CNOC::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JUu_numEqns() const { return 2; }

  void
  CNOC::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t5   = ALIAS_jsControl_D_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t5 * t1;
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = ALIAS_jnControl_D_1(U__[iU_jn], -t7, t7);
    result__[ 1   ] = t8 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::LTargs_numEqns() const { return 12; }

  void
  CNOC::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_coV];
    real_type t3   = X__[iX_vs] * X__[iX_vs];
    real_type t5   = X__[iX_vn] * X__[iX_vn];
    real_type t7   = sqrt(t3 + t5);
    real_type t8   = ALIAS_nominalFeed();
    result__[ 1   ] = 1.0 / t8 * t7 - 0.101e1;
    real_type t14  = X__[iX_n] / ModelPars[iM_path_following_tolerance];
    result__[ 2   ] = -1 - t14;
    result__[ 3   ] = t14 - 1;
    real_type t15  = X__[iX_as];
    real_type t18  = 1.0 / ModelPars[iM_as_max] * t15;
    result__[ 4   ] = -1 - t18;
    result__[ 5   ] = t18 - 1;
    real_type t19  = X__[iX_an];
    real_type t22  = 1.0 / ModelPars[iM_an_max] * t19;
    result__[ 6   ] = -1 - t22;
    result__[ 7   ] = t22 - 1;
    real_type t24  = ALIAS_theta(X__[iX_s]);
    real_type t25  = cos(t24);
    real_type t27  = sin(t24);
    real_type t32  = 1.0 / ModelPars[iM_ax_max] * (t25 * t15 - t27 * t19);
    result__[ 8   ] = -1 - t32;
    result__[ 9   ] = t32 - 1;
    real_type t38  = 1.0 / ModelPars[iM_ay_max] * (t27 * t15 + t25 * t19);
    result__[ 10  ] = -1 - t38;
    result__[ 11  ] = t38 - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 12, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJPxDxp_numRows() const { return 7; }
  integer CNOC::DJPxDxp_numCols() const { return 7; }
  integer CNOC::DJPxDxp_nnz()     const { return 0; }

  void
  CNOC::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DLTxDxp_numRows() const { return 7; }
  integer CNOC::DLTxDxp_numCols() const { return 7; }
  integer CNOC::DLTxDxp_nnz()     const { return 27; }

  void
  CNOC::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 2   ;
    iIndex[10] = 3   ; jIndex[10] = 3   ;
    iIndex[11] = 3   ; jIndex[11] = 6   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 4   ;
    iIndex[14] = 4   ; jIndex[14] = 5   ;
    iIndex[15] = 4   ; jIndex[15] = 6   ;
    iIndex[16] = 5   ; jIndex[16] = 0   ;
    iIndex[17] = 5   ; jIndex[17] = 4   ;
    iIndex[18] = 5   ; jIndex[18] = 5   ;
    iIndex[19] = 5   ; jIndex[19] = 6   ;
    iIndex[20] = 6   ; jIndex[20] = 0   ;
    iIndex[21] = 6   ; jIndex[21] = 1   ;
    iIndex[22] = 6   ; jIndex[22] = 2   ;
    iIndex[23] = 6   ; jIndex[23] = 3   ;
    iIndex[24] = 6   ; jIndex[24] = 4   ;
    iIndex[25] = 6   ; jIndex[25] = 5   ;
    iIndex[26] = 6   ; jIndex[26] = 6   ;
  }


  void
  CNOC::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t2   = X__[iX_as];
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_theta(t3);
    real_type t5   = cos(t4);
    real_type t7   = X__[iX_an];
    real_type t8   = sin(t4);
    real_type t11  = ModelPars[iM_ax_max];
    real_type t12  = 1.0 / t11;
    real_type t13  = t12 * (t5 * t2 - t8 * t7);
    real_type t14  = -1 - t13;
    real_type t15  = ALIAS_ax_limit_min_DD(t14);
    real_type t16  = t15 * t1;
    real_type t17  = ALIAS_theta_D(t3);
    real_type t18  = t17 * t2;
    real_type t20  = t17 * t7;
    real_type t22  = -t8 * t18 - t5 * t20;
    real_type t23  = t22 * t22;
    real_type t24  = t11 * t11;
    real_type t25  = 1.0 / t24;
    real_type t26  = t25 * t23;
    real_type t28  = ALIAS_ax_limit_min_D(t14);
    real_type t29  = t28 * t1;
    real_type t30  = ALIAS_theta_DD(t3);
    real_type t31  = t30 * t2;
    real_type t33  = t17 * t17;
    real_type t34  = t33 * t2;
    real_type t36  = t30 * t7;
    real_type t38  = t33 * t7;
    real_type t41  = t12 * (-t8 * t31 - t5 * t34 - t5 * t36 + t8 * t38);
    real_type t43  = t13 - 1;
    real_type t44  = ALIAS_ax_limit_max_DD(t43);
    real_type t45  = t44 * t1;
    real_type t47  = ALIAS_ax_limit_max_D(t43);
    real_type t48  = t47 * t1;
    real_type t53  = ModelPars[iM_ay_max];
    real_type t54  = 1.0 / t53;
    real_type t55  = t54 * (t8 * t2 + t5 * t7);
    real_type t56  = -1 - t55;
    real_type t57  = ALIAS_ay_limit_min_DD(t56);
    real_type t58  = t57 * t1;
    real_type t61  = t5 * t18 - t8 * t20;
    real_type t62  = t61 * t61;
    real_type t63  = t53 * t53;
    real_type t64  = 1.0 / t63;
    real_type t65  = t64 * t62;
    real_type t67  = ALIAS_ay_limit_min_D(t56);
    real_type t68  = t67 * t1;
    real_type t74  = t54 * (t5 * t31 - t8 * t34 - t8 * t36 - t5 * t38);
    real_type t76  = t55 - 1;
    real_type t77  = ALIAS_ay_limit_max_DD(t76);
    real_type t78  = t77 * t1;
    real_type t80  = ALIAS_ay_limit_max_D(t76);
    real_type t81  = t80 * t1;
    result__[ 0   ] = t26 * t16 + t26 * t45 - t41 * t29 + t41 * t48 + t65 * t58 + t65 * t78 - t74 * t68 + t74 * t81;
    real_type t84  = t22 * t25 * t5;
    real_type t86  = t8 * t17;
    real_type t87  = t12 * t86;
    real_type t92  = t61 * t64 * t8;
    real_type t94  = t5 * t17;
    real_type t95  = t54 * t94;
    result__[ 1   ] = t84 * t16 + t87 * t29 + t84 * t45 - t87 * t48 + t92 * t58 - t95 * t68 + t92 * t78 + t95 * t81;
    real_type t99  = t25 * t8;
    real_type t100 = t22 * t99;
    real_type t102 = t12 * t94;
    real_type t106 = t64 * t5;
    real_type t107 = t61 * t106;
    real_type t109 = t54 * t86;
    result__[ 2   ] = -t100 * t16 - t100 * t45 + t102 * t29 - t102 * t48 + t107 * t58 + t107 * t78 + t109 * t68 - t109 * t81;
    result__[ 3   ] = -t12 * t22 * t28 + t12 * t22 * t47 - t54 * t61 * t67 + t54 * t61 * t80;
    real_type t122 = ModelPars[iM_path_following_tolerance];
    real_type t123 = 1.0 / t122;
    real_type t124 = t123 * X__[iX_n];
    real_type t125 = -1 - t124;
    real_type t126 = ALIAS_PathFollowingTolerance_min_DD(t125);
    real_type t128 = t122 * t122;
    real_type t129 = 1.0 / t128;
    real_type t131 = t124 - 1;
    real_type t132 = ALIAS_PathFollowingTolerance_max_DD(t131);
    result__[ 4   ] = t129 * t126 * t1 + t129 * t132 * t1;
    real_type t135 = ALIAS_PathFollowingTolerance_min_D(t125);
    real_type t137 = ALIAS_PathFollowingTolerance_max_D(t131);
    result__[ 5   ] = -t123 * t135 + t123 * t137;
    real_type t139 = X__[iX_vs];
    real_type t140 = t139 * t139;
    real_type t141 = X__[iX_vn];
    real_type t142 = t141 * t141;
    real_type t143 = t140 + t142;
    real_type t144 = sqrt(t143);
    real_type t145 = ALIAS_nominalFeed();
    real_type t146 = 1.0 / t145;
    real_type t148 = t146 * t144 - 0.101e1;
    real_type t149 = ALIAS_vLimit_DD(t148);
    real_type t150 = t149 * t1;
    real_type t151 = 1.0 / t143;
    real_type t152 = t145 * t145;
    real_type t153 = 1.0 / t152;
    real_type t154 = t153 * t151;
    real_type t157 = ALIAS_vLimit_D(t148);
    real_type t158 = t157 * t1;
    real_type t160 = 1.0 / t144 / t143;
    real_type t161 = t146 * t160;
    real_type t164 = 1.0 / t144;
    real_type t166 = t146 * t164 * t158;
    result__[ 6   ] = t140 * t154 * t150 - t140 * t161 * t158 + t166;
    real_type t172 = t139 * t146;
    result__[ 7   ] = t139 * t141 * t153 * t151 * t150 - t141 * t172 * t160 * t158;
    real_type t175 = t164 * t157;
    result__[ 8   ] = t172 * t175;
    result__[ 9   ] = result__[7];
    result__[ 10  ] = t142 * t154 * t150 - t142 * t161 * t158 + t166;
    result__[ 11  ] = t141 * t146 * t175;
    result__[ 12  ] = result__[1];
    real_type t181 = ModelPars[iM_as_max];
    real_type t182 = 1.0 / t181;
    real_type t183 = t182 * t2;
    real_type t184 = -1 - t183;
    real_type t185 = ALIAS_as_limit_min_DD(t184);
    real_type t187 = t181 * t181;
    real_type t188 = 1.0 / t187;
    real_type t190 = t183 - 1;
    real_type t191 = ALIAS_as_limit_max_DD(t190);
    real_type t194 = t5 * t5;
    real_type t195 = t25 * t194;
    real_type t198 = t8 * t8;
    real_type t199 = t64 * t198;
    result__[ 13  ] = t188 * t185 * t1 + t188 * t191 * t1 + t195 * t16 + t195 * t45 + t199 * t58 + t199 * t78;
    real_type t202 = t5 * t99;
    real_type t205 = t8 * t106;
    result__[ 14  ] = -t202 * t16 - t202 * t45 + t205 * t58 + t205 * t78;
    real_type t208 = ALIAS_as_limit_min_D(t184);
    real_type t210 = ALIAS_as_limit_max_D(t190);
    result__[ 15  ] = -t12 * t5 * t28 + t12 * t5 * t47 - t54 * t8 * t67 + t54 * t8 * t80 - t182 * t208 + t182 * t210;
    result__[ 16  ] = result__[2];
    result__[ 17  ] = result__[14];
    real_type t220 = ModelPars[iM_an_max];
    real_type t221 = 1.0 / t220;
    real_type t222 = t221 * t7;
    real_type t223 = -1 - t222;
    real_type t224 = ALIAS_an_limit_min_DD(t223);
    real_type t226 = t220 * t220;
    real_type t227 = 1.0 / t226;
    real_type t229 = t222 - 1;
    real_type t230 = ALIAS_an_limit_max_DD(t229);
    real_type t233 = t25 * t198;
    real_type t236 = t64 * t194;
    result__[ 18  ] = t227 * t224 * t1 + t227 * t230 * t1 + t233 * t16 + t233 * t45 + t236 * t58 + t236 * t78;
    real_type t239 = ALIAS_an_limit_min_D(t223);
    real_type t241 = ALIAS_an_limit_max_D(t229);
    result__[ 19  ] = t12 * t8 * t28 - t12 * t8 * t47 - t54 * t5 * t67 + t54 * t5 * t80 - t221 * t239 + t221 * t241;
    result__[ 20  ] = result__[3];
    result__[ 21  ] = result__[5];
    result__[ 22  ] = result__[8];
    result__[ 23  ] = result__[11];
    result__[ 24  ] = result__[15];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = ALIAS_timePositive_DD(-t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 27, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJUxDxp_numRows() const { return 7; }
  integer CNOC::DJUxDxp_numCols() const { return 7; }
  integer CNOC::DJUxDxp_nnz()     const { return 0; }

  void
  CNOC::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJPuDxp_numRows() const { return 2; }
  integer CNOC::DJPuDxp_numCols() const { return 7; }
  integer CNOC::DJPuDxp_nnz()     const { return 0; }

  void
  CNOC::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DLTuDxp_numRows() const { return 2; }
  integer CNOC::DLTuDxp_numCols() const { return 7; }
  integer CNOC::DLTuDxp_nnz()     const { return 0; }

  void
  CNOC::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJUuDxp_numRows() const { return 2; }
  integer CNOC::DJUuDxp_numCols() const { return 7; }
  integer CNOC::DJUuDxp_nnz()     const { return 2; }

  void
  CNOC::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }


  void
  CNOC::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_jsControl_D_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t5   = ModelPars[iM_jn_max];
    result__[ 1   ] = ALIAS_jnControl_D_1(U__[iU_jn], -t5, t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJPpDp_numRows() const { return 0; }
  integer CNOC::DJPpDp_numCols() const { return 0; }
  integer CNOC::DJPpDp_nnz()     const { return 0; }

  void
  CNOC::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DLTpDp_numRows() const { return 0; }
  integer CNOC::DLTpDp_numCols() const { return 0; }
  integer CNOC::DLTpDp_nnz()     const { return 0; }

  void
  CNOC::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJUpDp_numRows() const { return 0; }
  integer CNOC::DJUpDp_numCols() const { return 0; }
  integer CNOC::DJUpDp_nnz()     const { return 0; }

  void
  CNOC::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DLTargsDxup_numRows() const { return 12; }
  integer CNOC::DLTargsDxup_numCols() const { return 9; }
  integer CNOC::DLTargsDxup_nnz()     const { return 21; }

  void
  CNOC::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 6   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 7   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 8   ; jIndex[9 ] = 0   ;
    iIndex[10] = 8   ; jIndex[10] = 4   ;
    iIndex[11] = 8   ; jIndex[11] = 5   ;
    iIndex[12] = 9   ; jIndex[12] = 0   ;
    iIndex[13] = 9   ; jIndex[13] = 4   ;
    iIndex[14] = 9   ; jIndex[14] = 5   ;
    iIndex[15] = 10  ; jIndex[15] = 0   ;
    iIndex[16] = 10  ; jIndex[16] = 4   ;
    iIndex[17] = 10  ; jIndex[17] = 5   ;
    iIndex[18] = 11  ; jIndex[18] = 0   ;
    iIndex[19] = 11  ; jIndex[19] = 4   ;
    iIndex[20] = 11  ; jIndex[20] = 5   ;
  }


  void
  CNOC::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    real_type t1   = X__[iX_vs];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_vn];
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = ALIAS_nominalFeed();
    real_type t10  = 1.0 / t8 / t6;
    result__[ 1   ] = t1 * t10;
    result__[ 2   ] = t3 * t10;
    real_type t12  = 1.0 / ModelPars[iM_path_following_tolerance];
    result__[ 3   ] = -t12;
    result__[ 4   ] = t12;
    real_type t14  = 1.0 / ModelPars[iM_as_max];
    result__[ 5   ] = -t14;
    result__[ 6   ] = t14;
    real_type t16  = 1.0 / ModelPars[iM_an_max];
    result__[ 7   ] = -t16;
    result__[ 8   ] = t16;
    real_type t18  = X__[iX_s];
    real_type t19  = ALIAS_theta_D(t18);
    real_type t20  = t19 * X__[iX_as];
    real_type t21  = ALIAS_theta(t18);
    real_type t22  = sin(t21);
    real_type t25  = t19 * X__[iX_an];
    real_type t26  = cos(t21);
    real_type t30  = 1.0 / ModelPars[iM_ax_max];
    real_type t31  = t30 * (-t22 * t20 - t26 * t25);
    result__[ 9   ] = -t31;
    real_type t32  = t30 * t26;
    result__[ 10  ] = -t32;
    result__[ 11  ] = t30 * t22;
    result__[ 12  ] = t31;
    result__[ 13  ] = t32;
    result__[ 14  ] = -result__[11];
    real_type t37  = 1.0 / ModelPars[iM_ay_max];
    real_type t38  = t37 * (t26 * t20 - t22 * t25);
    result__[ 15  ] = -t38;
    real_type t39  = t37 * t22;
    result__[ 16  ] = -t39;
    real_type t40  = t37 * t26;
    result__[ 17  ] = -t40;
    result__[ 18  ] = t38;
    result__[ 19  ] = t39;
    result__[ 20  ] = t40;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 21, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::D2LTargsD2xup_numRows() const { return 9; }
  integer CNOC::D2LTargsD2xup_numCols() const { return 9; }
  integer CNOC::D2LTargsD2xup_nnz()     const { return 9; }

  void
  CNOC::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 5   ; jIndex[8 ] = 0   ;
  }


  void
  CNOC::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_as];
    real_type t2   = X__[iX_s];
    real_type t3   = ALIAS_theta_DD(t2);
    real_type t4   = t3 * t1;
    real_type t5   = ALIAS_theta(t2);
    real_type t6   = sin(t5);
    real_type t8   = ALIAS_theta_D(t2);
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t1;
    real_type t11  = cos(t5);
    real_type t13  = X__[iX_an];
    real_type t14  = t3 * t13;
    real_type t16  = t9 * t13;
    real_type t20  = 1.0 / ModelPars[iM_ax_max];
    real_type t21  = t20 * (-t11 * t10 - t11 * t14 + t6 * t16 - t6 * t4);
    real_type t22  = OMEGA__[8];
    real_type t24  = OMEGA__[9];
    real_type t32  = 1.0 / ModelPars[iM_ay_max];
    real_type t33  = t32 * (-t6 * t10 - t11 * t16 + t11 * t4 - t6 * t14);
    real_type t34  = OMEGA__[10];
    real_type t36  = OMEGA__[11];
    result__[ 0   ] = -t22 * t21 + t24 * t21 - t34 * t33 + t36 * t33;
    real_type t38  = t6 * t8;
    real_type t39  = t22 * t20;
    real_type t41  = t24 * t20;
    real_type t43  = t11 * t8;
    real_type t44  = t34 * t32;
    real_type t46  = t36 * t32;
    result__[ 1   ] = t39 * t38 - t41 * t38 - t44 * t43 + t46 * t43;
    result__[ 2   ] = t44 * t38 - t46 * t38 + t39 * t43 - t41 * t43;
    real_type t52  = X__[iX_vs];
    real_type t53  = t52 * t52;
    real_type t54  = X__[iX_vn];
    real_type t55  = t54 * t54;
    real_type t56  = t53 + t55;
    real_type t57  = sqrt(t56);
    real_type t60  = ALIAS_nominalFeed();
    real_type t61  = 1.0 / t60;
    real_type t62  = t61 / t57 / t56;
    real_type t63  = OMEGA__[1];
    real_type t68  = t63 * t61 / t57;
    result__[ 3   ] = -t63 * t53 * t62 + t68;
    result__[ 4   ] = -t54 * t63 * t52 * t62;
    result__[ 5   ] = result__[4];
    result__[ 6   ] = -t63 * t55 * t62 + t68;
    result__[ 7   ] = result__[1];
    result__[ 8   ] = result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xup_sparse", 9, i_segment );
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

  integer CNOC::Hx_numEqns() const { return 7; }

  void
  CNOC::Hx_eval(
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
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_vs];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_n];
    real_type t5   = X__[iX_s];
    real_type t6   = ALIAS_kappa(t5);
    real_type t8   = -t6 * t4 + 1;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = X__[iX_coV];
    real_type t14  = ALIAS_kappa_D(t5);
    real_type t17  = L__[iL_lambda3__xo];
    real_type t18  = X__[iX_vn];
    real_type t19  = t18 * t2;
    real_type t20  = 1.0 / t8;
    real_type t21  = t20 * t14;
    real_type t25  = t14 * t4 * t10;
    real_type t30  = L__[iL_lambda4__xo];
    real_type t31  = t2 * t2;
    real_type t34  = t6 * t31;
    real_type t39  = L__[iL_lambda5__xo];
    real_type t40  = X__[iX_an];
    real_type t41  = t40 * t2;
    real_type t48  = L__[iL_lambda6__xo];
    real_type t49  = X__[iX_as];
    real_type t50  = t49 * t2;
    result__[ 0   ] = t14 * t4 * t12 * t10 * t3 - t12 * (-t25 * t6 * t19 - t21 * t19) * t17 - t12 * (t20 * t14 * t31 + t25 * t34) * t30 - t12 * (-t25 * t6 * t41 - t21 * t41) * t39 - t12 * (t25 * t6 * t50 + t21 * t50) * t48;
    real_type t60  = t2 * t17;
    real_type t62  = t6 * t6;
    real_type t64  = t12 * t10 * t62;
    real_type t68  = t2 * t39;
    real_type t71  = t2 * t48;
    result__[ 1   ] = t6 * t12 * t10 * t3 + t64 * t18 * t60 - t64 * t31 * t30 + t64 * t40 * t68 - t64 * t49 * t71;
    real_type t74  = t18 * t18;
    real_type t76  = sqrt(t31 + t74);
    real_type t77  = ALIAS_nominalFeed();
    real_type t78  = t76 - t77;
    real_type t79  = t78 * t12;
    real_type t81  = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t82  = 1.0 / t81;
    real_type t84  = 1.0 / t76 * t82;
    real_type t91  = t20 * t6;
    real_type t92  = t12 * t91;
    result__[ 2   ] = t12 * t20 * t1 + t92 * t18 * t17 - 2 * t92 * t2 * t30 + 2 * t2 * t84 * t79 + t92 * t40 * t39 - t92 * t49 * t48;
    real_type t104 = L__[iL_lambda2__xo];
    result__[ 3   ] = 2 * t18 * t84 * t79 + t12 * t104 + t92 * t60;
    result__[ 4   ] = t12 * t17 - t92 * t71;
    result__[ 5   ] = t12 * t30 + t92 * t68;
    real_type t111 = t78 * t78;
    result__[ 6   ] = t82 * t111 + t20 * t3 + t18 * t104 - (-t91 * t19 - t49) * t17 - (t20 * t34 - t40) * t30 - (-t91 * t41 - U__[iU_js]) * t39 - (t91 * t50 - U__[iU_jn]) * t48;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::Hp_numEqns() const { return 0; }

  void
  CNOC::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DHxDxp_numRows() const { return 7; }
  integer CNOC::DHxDxp_numCols() const { return 7; }
  integer CNOC::DHxDxp_nnz()     const { return 40; }

  void
  CNOC::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 4   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
    iIndex[21] = 3   ; jIndex[21] = 0   ;
    iIndex[22] = 3   ; jIndex[22] = 1   ;
    iIndex[23] = 3   ; jIndex[23] = 2   ;
    iIndex[24] = 3   ; jIndex[24] = 3   ;
    iIndex[25] = 3   ; jIndex[25] = 6   ;
    iIndex[26] = 4   ; jIndex[26] = 0   ;
    iIndex[27] = 4   ; jIndex[27] = 1   ;
    iIndex[28] = 4   ; jIndex[28] = 2   ;
    iIndex[29] = 4   ; jIndex[29] = 6   ;
    iIndex[30] = 5   ; jIndex[30] = 0   ;
    iIndex[31] = 5   ; jIndex[31] = 1   ;
    iIndex[32] = 5   ; jIndex[32] = 2   ;
    iIndex[33] = 5   ; jIndex[33] = 6   ;
    iIndex[34] = 6   ; jIndex[34] = 0   ;
    iIndex[35] = 6   ; jIndex[35] = 1   ;
    iIndex[36] = 6   ; jIndex[36] = 2   ;
    iIndex[37] = 6   ; jIndex[37] = 3   ;
    iIndex[38] = 6   ; jIndex[38] = 4   ;
    iIndex[39] = 6   ; jIndex[39] = 5   ;
  }


  void
  CNOC::DHxDxp_sparse(
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
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_vs];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_n];
    real_type t5   = X__[iX_s];
    real_type t6   = ALIAS_kappa(t5);
    real_type t8   = -t6 * t4 + 1;
    real_type t9   = t8 * t8;
    real_type t11  = 1.0 / t9 / t8;
    real_type t12  = t11 * t3;
    real_type t13  = X__[iX_coV];
    real_type t14  = t4 * t4;
    real_type t16  = ALIAS_kappa_D(t5);
    real_type t17  = t16 * t16;
    real_type t21  = 1.0 / t9;
    real_type t23  = t4 * t13;
    real_type t24  = ALIAS_kappa_DD(t5);
    real_type t27  = L__[iL_lambda3__xo];
    real_type t28  = X__[iX_vn];
    real_type t29  = t28 * t2;
    real_type t30  = 1.0 / t8;
    real_type t31  = t30 * t24;
    real_type t34  = t4 * t21 * t17;
    real_type t37  = t6 * t29;
    real_type t39  = t17 * t14 * t11;
    real_type t42  = t4 * t21;
    real_type t43  = t24 * t42;
    real_type t48  = L__[iL_lambda4__xo];
    real_type t49  = t2 * t2;
    real_type t55  = t6 * t49;
    real_type t62  = L__[iL_lambda5__xo];
    real_type t63  = X__[iX_an];
    real_type t64  = t63 * t2;
    real_type t68  = t6 * t64;
    real_type t75  = L__[iL_lambda6__xo];
    real_type t76  = X__[iX_as];
    real_type t77  = t76 * t2;
    real_type t81  = t6 * t77;
    result__[ 0   ] = 2 * t17 * t14 * t13 * t12 + t24 * t23 * t21 * t3 - t13 * (-t31 * t29 - 2 * t34 * t29 - 2 * t39 * t37 - t43 * t37) * t27 - t13 * (2 * t42 * t17 * t49 + t30 * t24 * t49 + 2 * t39 * t55 + t43 * t55) * t48 - t13 * (-t31 * t64 - 2 * t34 * t64 - 2 * t39 * t68 - t43 * t68) * t62 - t13 * (t31 * t77 + 2 * t34 * t77 + 2 * t39 * t81 + t43 * t81) * t75;
    real_type t91  = 2 * t6 * t16 * t23 * t12;
    real_type t92  = t13 * t21;
    real_type t93  = t16 * t92;
    real_type t94  = t93 * t3;
    real_type t96  = t6 * t21 * t16;
    real_type t98  = t6 * t6;
    real_type t101 = t16 * t4 * t11;
    real_type t107 = t16 * t49;
    real_type t108 = t6 * t21;
    result__[ 1   ] = t91 + t94 - t13 * (-2 * t101 * t98 * t29 - 2 * t96 * t29) * t27 - t13 * (2 * t101 * t98 * t49 + 2 * t108 * t107) * t48 - t13 * (-2 * t101 * t98 * t64 - 2 * t96 * t64) * t62 - t13 * (2 * t101 * t98 * t77 + 2 * t96 * t77) * t75;
    real_type t130 = t21 * t1;
    real_type t132 = t16 * t23 * t130;
    real_type t136 = t16 * t42;
    real_type t145 = t136 * t6 * t2 + t30 * t16 * t2;
    result__[ 2   ] = t132 - t13 * (-t136 * t6 * t28 - t30 * t16 * t28) * t27 - 2 * t13 * t145 * t48 - t13 * (-t136 * t6 * t63 - t30 * t16 * t63) * t62 - t13 * (t136 * t6 * t76 + t30 * t16 * t76) * t75;
    real_type t163 = -t145;
    result__[ 3   ] = -t13 * t163 * t27;
    result__[ 4   ] = -t13 * t145 * t75;
    result__[ 5   ] = -t13 * t163 * t62;
    real_type t171 = t30 * t16;
    result__[ 6   ] = t136 * t3 - (-t136 * t37 - t171 * t29) * t27 - (t30 * t107 + t136 * t55) * t48 - (-t136 * t68 - t171 * t64) * t62 - (t136 * t81 + t171 * t77) * t75;
    real_type t188 = t2 * t27;
    real_type t189 = t28 * t188;
    real_type t191 = t16 * t13 * t108;
    real_type t194 = t98 * t28;
    real_type t196 = t13 * t11;
    real_type t197 = t16 * t4;
    real_type t198 = t197 * t196;
    real_type t201 = t49 * t48;
    real_type t208 = t2 * t62;
    real_type t209 = t63 * t208;
    real_type t212 = t98 * t63;
    real_type t216 = t2 * t75;
    real_type t217 = t76 * t216;
    real_type t220 = t98 * t76;
    result__[ 7   ] = 2 * t198 * t194 * t188 - 2 * t198 * t98 * t201 + 2 * t198 * t212 * t208 - 2 * t198 * t220 * t216 - 2 * t93 * t6 * t201 + 2 * t191 * t189 + 2 * t191 * t209 - 2 * t191 * t217 + t91 + t94;
    real_type t228 = t13 * t11 * t98 * t6;
    result__[ 8   ] = 2 * t98 * t196 * t3 + 2 * t228 * t189 - 2 * t228 * t201 + 2 * t228 * t209 - 2 * t228 * t217;
    real_type t236 = t28 * t27;
    real_type t237 = t21 * t98;
    real_type t238 = t13 * t237;
    real_type t240 = t2 * t48;
    real_type t243 = t63 * t62;
    real_type t245 = t76 * t75;
    result__[ 9   ] = t6 * t13 * t130 + t238 * t236 - 2 * t238 * t240 + t238 * t243 - t238 * t245;
    result__[ 10  ] = t238 * t188;
    result__[ 11  ] = -t238 * t216;
    result__[ 12  ] = t238 * t208;
    result__[ 13  ] = t21 * t194 * t188 + t21 * t212 * t208 - t21 * t220 * t216 + t108 * t3 - t237 * t201;
    real_type t256 = t13 * t171;
    real_type t259 = t197 * t92;
    result__[ 14  ] = t259 * t6 * t236 - 2 * t259 * t6 * t240 + t259 * t6 * t243 - t259 * t6 * t245 + t256 * t236 - 2 * t256 * t240 + t256 * t243 - t256 * t245 + t132;
    result__[ 15  ] = result__[9];
    real_type t272 = t28 * t28;
    real_type t273 = t49 + t272;
    real_type t275 = 1.0 / t273 * t13;
    real_type t277 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t278 = 1.0 / t277;
    real_type t281 = sqrt(t273);
    real_type t282 = ALIAS_nominalFeed();
    real_type t283 = t281 - t282;
    real_type t284 = t283 * t13;
    real_type t286 = 1.0 / t281 / t273;
    real_type t287 = t286 * t278;
    real_type t290 = 1.0 / t281;
    real_type t292 = t290 * t278 * t284;
    real_type t294 = t13 * t30;
    result__[ 16  ] = 2 * t278 * t49 * t275 - 2 * t49 * t287 * t284 - 2 * t294 * t6 * t48 + 2 * t292;
    result__[ 17  ] = -2 * t28 * t2 * t286 * t278 * t284 + 2 * t2 * t278 * t28 * t275 + t294 * t6 * t27;
    result__[ 18  ] = -t294 * t6 * t75;
    result__[ 19  ] = t294 * t6 * t62;
    real_type t311 = t278 * t283;
    real_type t316 = t30 * t6;
    result__[ 20  ] = 2 * t2 * t290 * t311 + t30 * t1 + t316 * t236 - 2 * t316 * t240 + t316 * t243 - t316 * t245;
    result__[ 21  ] = t259 * t6 * t188 + t256 * t188;
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    result__[ 24  ] = 2 * t278 * t272 * t275 - 2 * t272 * t287 * t284 + 2 * t292;
    result__[ 25  ] = 2 * t28 * t290 * t311 + t316 * t188 + L__[iL_lambda2__xo];
    result__[ 26  ] = -t259 * t6 * t216 - t256 * t216;
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    result__[ 29  ] = -t316 * t216 + t27;
    result__[ 30  ] = t259 * t6 * t208 + t256 * t208;
    result__[ 31  ] = result__[12];
    result__[ 32  ] = result__[19];
    result__[ 33  ] = t316 * t208 + t48;
    result__[ 34  ] = result__[6];
    result__[ 35  ] = result__[13];
    result__[ 36  ] = result__[20];
    result__[ 37  ] = result__[25];
    result__[ 38  ] = result__[29];
    result__[ 39  ] = result__[33];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 40, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DHpDp_numRows() const { return 0; }
  integer CNOC::DHpDp_numCols() const { return 0; }
  integer CNOC::DHpDp_nnz()     const { return 0; }

  void
  CNOC::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DHpDp_sparse(
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

  integer CNOC::Hu_numEqns() const { return 2; }

  void
  CNOC::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_coV];
    result__[ 0   ] = t2 * L__[iL_lambda5__xo];
    result__[ 1   ] = t2 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DHuDxp_numRows() const { return 2; }
  integer CNOC::DHuDxp_numCols() const { return 7; }
  integer CNOC::DHuDxp_nnz()     const { return 2; }

  void
  CNOC::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }


  void
  CNOC::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda5__xo];
    result__[ 1   ] = L__[iL_lambda6__xo];
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

  integer CNOC::eta_numEqns() const { return 7; }

  void
  CNOC::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
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
  integer CNOC::DetaDxp_numRows() const { return 7; }
  integer CNOC::DetaDxp_numCols() const { return 7; }
  integer CNOC::DetaDxp_nnz()     const { return 0; }

  void
  CNOC::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DetaDxp_sparse(
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

  integer CNOC::nu_numEqns() const { return 7; }

  void
  CNOC::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
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
  integer CNOC::DnuDxp_numRows() const { return 7; }
  integer CNOC::DnuDxp_numCols() const { return 7; }
  integer CNOC::DnuDxp_nnz()     const { return 0; }

  void
  CNOC::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: CNOC_Methods_AdjointODE.cc
