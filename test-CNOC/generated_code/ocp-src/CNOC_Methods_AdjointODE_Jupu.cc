/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_AdjointODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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
#pragma warning( disable : 4189 )
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

  real_type
  CNOC::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  CNOC::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t5   = jsControl(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t8   = ModelPars[iM_jn_max];
    real_type t9   = jnControl(U__[iU_jn], -t8, t8);
    real_type result__ = t5 * t1 + t9 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  CNOC::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t2   = timePositive(-t1);
    real_type t4   = X__[iX_vs] * X__[iX_vs];
    real_type t6   = X__[iX_vn] * X__[iX_vn];
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t13  = vLimit(1.0 / t9 * t8 - 0.101e1);
    real_type t18  = X__[iX_n] / ModelPars[iM_path_following_tolerance];
    real_type t20  = PathFollowingTolerance_min(-1 - t18);
    real_type t23  = PathFollowingTolerance_max(t18 - 1);
    real_type t25  = X__[iX_as];
    real_type t28  = 1.0 / ModelPars[iM_as_max] * t25;
    real_type t30  = as_limit_min(-1 - t28);
    real_type t33  = as_limit_max(t28 - 1);
    real_type t35  = X__[iX_an];
    real_type t38  = 1.0 / ModelPars[iM_an_max] * t35;
    real_type t40  = an_limit_min(-1 - t38);
    real_type t43  = an_limit_max(t38 - 1);
    real_type t46  = ALIAS_theta(X__[iX_s]);
    real_type t47  = cos(t46);
    real_type t49  = sin(t46);
    real_type t54  = 1.0 / ModelPars[iM_ax_max] * (t47 * t25 - t49 * t35);
    real_type t56  = ax_limit_min(-1 - t54);
    real_type t59  = ax_limit_max(t54 - 1);
    real_type t66  = 1.0 / ModelPars[iM_ay_max] * (t49 * t25 + t47 * t35);
    real_type t68  = ay_limit_min(-1 - t66);
    real_type t71  = ay_limit_max(t66 - 1);
    real_type result__ = t13 * t1 + t20 * t1 + t23 * t1 + t30 * t1 + t33 * t1 + t40 * t1 + t43 * t1 + t56 * t1 + t59 * t1 + t68 * t1 + t71 * t1 + t2;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JPxpu_numEqns() const { return 9; }

  void
  CNOC::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JUxpu_numEqns() const { return 9; }

  void
  CNOC::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    real_type t1   = U__[iU_js];
    real_type t2   = ModelPars[iM_js_min];
    real_type t3   = ModelPars[iM_js_max];
    real_type t4   = jsControl(t1, t2, t3);
    real_type t5   = U__[iU_jn];
    real_type t6   = ModelPars[iM_jn_max];
    real_type t7   = jnControl(t5, -t6, t6);
    result__[ 6   ] = t4 + t7;
    real_type t8   = X__[iX_coV];
    real_type t9   = ALIAS_jsControl_D_1(t1, t2, t3);
    result__[ 7   ] = t9 * t8;
    real_type t10  = ALIAS_jnControl_D_1(t5, -t6, t6);
    result__[ 8   ] = t10 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::LTxpu_numEqns() const { return 9; }

  void
  CNOC::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::LTargs_numEqns() const { return 12; }

  void
  CNOC::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
  integer CNOC::D2JPD2xpu_numRows() const { return 9; }
  integer CNOC::D2JPD2xpu_numCols() const { return 9; }
  integer CNOC::D2JPD2xpu_nnz()     const { return 0; }

  void
  CNOC::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::D2LTD2xpu_numRows() const { return 9; }
  integer CNOC::D2LTD2xpu_numCols() const { return 9; }
  integer CNOC::D2LTD2xpu_nnz()     const { return 27; }

  void
  CNOC::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  CNOC::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 27, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::D2JUD2xpu_numRows() const { return 9; }
  integer CNOC::D2JUD2xpu_numCols() const { return 9; }
  integer CNOC::D2JUD2xpu_nnz()     const { return 6; }

  void
  CNOC::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 6   ; jIndex[0 ] = 7   ;
    iIndex[1 ] = 6   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 7   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 7   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 8   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 8   ; jIndex[5 ] = 8   ;
  }


  void
  CNOC::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_js];
    real_type t2   = ModelPars[iM_js_min];
    real_type t3   = ModelPars[iM_js_max];
    result__[ 0   ] = ALIAS_jsControl_D_1(t1, t2, t3);
    real_type t4   = U__[iU_jn];
    real_type t5   = ModelPars[iM_jn_max];
    result__[ 1   ] = ALIAS_jnControl_D_1(t4, -t5, t5);
    result__[ 2   ] = result__[0];
    real_type t6   = X__[iX_coV];
    real_type t7   = ALIAS_jsControl_D_1_1(t1, t2, t3);
    result__[ 3   ] = t7 * t6;
    result__[ 4   ] = result__[1];
    real_type t8   = ALIAS_jnControl_D_1_1(t4, -t5, t5);
    result__[ 5   ] = t8 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DLTargsDxpu_numRows() const { return 12; }
  integer CNOC::DLTargsDxpu_numCols() const { return 9; }
  integer CNOC::DLTargsDxpu_nnz()     const { return 21; }

  void
  CNOC::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  CNOC::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    real_type t31  = t30 * (-t20 * t22 - t25 * t26);
    result__[ 9   ] = -t31;
    real_type t32  = t30 * t26;
    result__[ 10  ] = -t32;
    result__[ 11  ] = t30 * t22;
    result__[ 12  ] = t31;
    result__[ 13  ] = t32;
    result__[ 14  ] = -result__[11];
    real_type t37  = 1.0 / ModelPars[iM_ay_max];
    real_type t38  = t37 * (t20 * t26 - t22 * t25);
    result__[ 15  ] = -t38;
    real_type t39  = t37 * t22;
    result__[ 16  ] = -t39;
    real_type t40  = t37 * t26;
    result__[ 17  ] = -t40;
    result__[ 18  ] = t38;
    result__[ 19  ] = t39;
    result__[ 20  ] = t40;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 21, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::D2LTargsD2xpu_numRows() const { return 9; }
  integer CNOC::D2LTargsD2xpu_numCols() const { return 9; }
  integer CNOC::D2LTargsD2xpu_nnz()     const { return 9; }

  void
  CNOC::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  CNOC::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
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
    real_type t38  = t8 * t6;
    real_type t39  = t20 * t22;
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
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 9, i_segment );
  }

}

// EOF: CNOC_Methods_AdjointODE.cc
