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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::Hxp_numEqns() const { return 7; }

  void
  CNOC::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
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
    real_type t47  = MU__[0];
    real_type t48  = X__[iX_vs];
    real_type t49  = t48 * t47;
    real_type t50  = X__[iX_n];
    real_type t51  = ALIAS_kappa(t3);
    real_type t53  = -t51 * t50 + 1;
    real_type t54  = t53 * t53;
    real_type t55  = 1.0 / t54;
    real_type t58  = ALIAS_kappa_D(t3);
    real_type t61  = MU__[2];
    real_type t62  = X__[iX_vn];
    real_type t63  = t62 * t48;
    real_type t64  = 1.0 / t53;
    real_type t65  = t64 * t58;
    real_type t69  = t58 * t50 * t55;
    real_type t74  = MU__[3];
    real_type t75  = t48 * t48;
    real_type t78  = t51 * t75;
    real_type t83  = MU__[4];
    real_type t84  = t7 * t48;
    real_type t91  = MU__[5];
    real_type t92  = t2 * t48;
    result__[ 0   ] = -t23 * t16 + t23 * t27 - t41 * t37 + t41 * t45 + t58 * t50 * t1 * t55 * t49 - t1 * (-t69 * t51 * t63 - t65 * t63) * t61 - t1 * (t64 * t58 * t75 + t69 * t78) * t74 - t1 * (-t69 * t51 * t84 - t65 * t84) * t83 - t1 * (t69 * t51 * t92 + t65 * t92) * t91;
    real_type t100 = 1.0 / ModelPars[iM_path_following_tolerance];
    real_type t101 = t100 * t50;
    real_type t102 = -1 - t101;
    real_type t103 = ALIAS_PathFollowingTolerance_min_D(t102);
    real_type t106 = t101 - 1;
    real_type t107 = ALIAS_PathFollowingTolerance_max_D(t106);
    real_type t113 = t48 * t61;
    real_type t115 = t51 * t51;
    real_type t117 = t1 * t55 * t115;
    real_type t121 = t48 * t83;
    real_type t124 = t48 * t91;
    result__[ 1   ] = t51 * t1 * t55 * t49 - t100 * t103 * t1 + t100 * t107 * t1 + t117 * t62 * t113 + t117 * t7 * t121 - t117 * t2 * t124 - t117 * t75 * t74;
    real_type t127 = t62 * t62;
    real_type t129 = sqrt(t75 + t127);
    real_type t130 = ALIAS_nominalFeed();
    real_type t131 = t129 - t130;
    real_type t132 = t131 * t1;
    real_type t134 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t135 = 1.0 / t134;
    real_type t136 = 1.0 / t129;
    real_type t137 = t136 * t135;
    real_type t141 = 1.0 / t130;
    real_type t143 = t141 * t129 - 0.101e1;
    real_type t144 = ALIAS_vLimit_D(t143);
    real_type t145 = t144 * t1;
    real_type t146 = t141 * t136;
    real_type t152 = t64 * t51;
    real_type t153 = t1 * t152;
    result__[ 2   ] = t1 * t64 * t47 + 2 * t48 * t137 * t132 + t48 * t146 * t145 - t153 * t2 * t91 - 2 * t153 * t48 * t74 + t153 * t62 * t61 + t153 * t7 * t83;
    real_type t167 = MU__[1];
    result__[ 3   ] = 2 * t62 * t137 * t132 + t62 * t146 * t145 + t1 * t167 + t153 * t113;
    real_type t171 = 1.0 / ModelPars[iM_as_max];
    real_type t172 = t171 * t2;
    real_type t173 = -1 - t172;
    real_type t174 = ALIAS_as_limit_min_D(t173);
    real_type t177 = t172 - 1;
    real_type t178 = ALIAS_as_limit_max_D(t177);
    real_type t181 = t12 * t5;
    real_type t184 = t33 * t8;
    result__[ 4   ] = -t171 * t174 * t1 + t171 * t178 * t1 + t1 * t61 - t153 * t124 - t181 * t16 + t181 * t27 - t184 * t37 + t184 * t45;
    real_type t190 = 1.0 / ModelPars[iM_an_max];
    real_type t191 = t190 * t7;
    real_type t192 = -1 - t191;
    real_type t193 = ALIAS_an_limit_min_D(t192);
    real_type t196 = t191 - 1;
    real_type t197 = ALIAS_an_limit_max_D(t196);
    real_type t200 = t12 * t8;
    real_type t203 = t33 * t5;
    result__[ 5   ] = -t190 * t193 * t1 + t190 * t197 * t1 + t1 * t74 + t153 * t121 + t200 * t16 - t200 * t27 - t203 * t37 + t203 * t45;
    real_type t208 = t131 * t131;
    real_type t210 = U__[iU_js];
    real_type t213 = jsControl(t210, ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t214 = U__[iU_jn];
    real_type t215 = ModelPars[iM_jn_max];
    real_type t216 = jnControl(t214, -t215, t215);
    real_type t217 = ALIAS_timePositive_D(-t1);
    real_type t218 = vLimit(t143);
    real_type t219 = PathFollowingTolerance_min(t102);
    real_type t220 = PathFollowingTolerance_max(t106);
    real_type t221 = as_limit_min(t173);
    real_type t222 = as_limit_max(t177);
    real_type t223 = an_limit_min(t192);
    real_type t225 = an_limit_max(t196);
    real_type t226 = ax_limit_min(t14);
    real_type t227 = ax_limit_max(t25);
    real_type t228 = ay_limit_min(t35);
    real_type t229 = ay_limit_max(t43);
    real_type t244 = t225 + t226 + t227 + t228 + t229 + t64 * t49 + t62 * t167 + (t152 * t63 + t2) * t61 + (-t64 * t78 + t7) * t74 + (t152 * t84 + t210) * t83 + (-t152 * t92 + t214) * t91;
    result__[ 6   ] = t135 * t208 + t213 + t216 - t217 + t218 + t219 + t220 + t221 + t222 + t223 + t244;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DHxpDxpuv_numRows() const { return 7; }
  integer CNOC::DHxpDxpuv_numCols() const { return 16; }
  integer CNOC::DHxpDxpuv_nnz()     const { return 47; }

  void
  CNOC::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[29] = 4   ; jIndex[29] = 4   ;
    iIndex[30] = 4   ; jIndex[30] = 5   ;
    iIndex[31] = 4   ; jIndex[31] = 6   ;
    iIndex[32] = 5   ; jIndex[32] = 0   ;
    iIndex[33] = 5   ; jIndex[33] = 1   ;
    iIndex[34] = 5   ; jIndex[34] = 2   ;
    iIndex[35] = 5   ; jIndex[35] = 4   ;
    iIndex[36] = 5   ; jIndex[36] = 5   ;
    iIndex[37] = 5   ; jIndex[37] = 6   ;
    iIndex[38] = 6   ; jIndex[38] = 0   ;
    iIndex[39] = 6   ; jIndex[39] = 1   ;
    iIndex[40] = 6   ; jIndex[40] = 2   ;
    iIndex[41] = 6   ; jIndex[41] = 3   ;
    iIndex[42] = 6   ; jIndex[42] = 4   ;
    iIndex[43] = 6   ; jIndex[43] = 5   ;
    iIndex[44] = 6   ; jIndex[44] = 6   ;
    iIndex[45] = 6   ; jIndex[45] = 7   ;
    iIndex[46] = 6   ; jIndex[46] = 8   ;
  }


  void
  CNOC::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
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
    real_type t83  = MU__[0];
    real_type t84  = X__[iX_vs];
    real_type t85  = t84 * t83;
    real_type t86  = X__[iX_n];
    real_type t87  = ALIAS_kappa(t3);
    real_type t89  = -t87 * t86 + 1;
    real_type t90  = t89 * t89;
    real_type t92  = 1.0 / t90 / t89;
    real_type t93  = t92 * t85;
    real_type t94  = t86 * t86;
    real_type t96  = ALIAS_kappa_D(t3);
    real_type t97  = t96 * t96;
    real_type t101 = 1.0 / t90;
    real_type t103 = t86 * t1;
    real_type t104 = ALIAS_kappa_DD(t3);
    real_type t107 = MU__[2];
    real_type t108 = X__[iX_vn];
    real_type t109 = t108 * t84;
    real_type t110 = 1.0 / t89;
    real_type t111 = t110 * t104;
    real_type t114 = t86 * t101 * t97;
    real_type t117 = t87 * t109;
    real_type t119 = t97 * t94 * t92;
    real_type t122 = t86 * t101;
    real_type t123 = t104 * t122;
    real_type t128 = MU__[3];
    real_type t129 = t84 * t84;
    real_type t135 = t87 * t129;
    real_type t142 = MU__[4];
    real_type t143 = t7 * t84;
    real_type t147 = t87 * t143;
    real_type t154 = MU__[5];
    real_type t155 = t2 * t84;
    real_type t159 = t87 * t155;
    result__[ 0   ] = t26 * t16 - t41 * t29 + t26 * t45 + t41 * t48 + t65 * t58 - t74 * t68 + t65 * t78 + t74 * t81 + 2 * t97 * t94 * t1 * t93 + t104 * t103 * t101 * t85 - t1 * (-t111 * t109 - 2 * t114 * t109 - 2 * t119 * t117 - t123 * t117) * t107 - t1 * (t110 * t104 * t129 + 2 * t122 * t97 * t129 + 2 * t119 * t135 + t123 * t135) * t128 - t1 * (-t111 * t143 - 2 * t114 * t143 - 2 * t119 * t147 - t123 * t147) * t142 - t1 * (t111 * t155 + 2 * t114 * t155 + 2 * t119 * t159 + t123 * t159) * t154;
    real_type t169 = 2 * t87 * t96 * t103 * t93;
    real_type t170 = t1 * t101;
    real_type t171 = t96 * t170;
    real_type t172 = t171 * t85;
    real_type t174 = t87 * t101 * t96;
    real_type t176 = t87 * t87;
    real_type t179 = t96 * t86 * t92;
    real_type t185 = t96 * t129;
    real_type t186 = t87 * t101;
    result__[ 1   ] = t169 + t172 - t1 * (-2 * t179 * t176 * t109 - 2 * t174 * t109) * t107 - t1 * (2 * t179 * t176 * t129 + 2 * t186 * t185) * t128 - t1 * (-2 * t179 * t176 * t143 - 2 * t174 * t143) * t142 - t1 * (2 * t179 * t176 * t155 + 2 * t174 * t155) * t154;
    real_type t208 = t101 * t83;
    real_type t210 = t96 * t103 * t208;
    real_type t214 = t96 * t122;
    real_type t223 = t110 * t96 * t84 + t214 * t87 * t84;
    result__[ 2   ] = t210 - t1 * (-t110 * t96 * t108 - t214 * t87 * t108) * t107 - 2 * t1 * t223 * t128 - t1 * (-t110 * t96 * t7 - t214 * t87 * t7) * t142 - t1 * (t110 * t96 * t2 + t214 * t87 * t2) * t154;
    real_type t241 = -t223;
    result__[ 3   ] = -t1 * t241 * t107;
    real_type t245 = t22 * t25 * t5;
    real_type t246 = t245 * t16;
    real_type t247 = t8 * t17;
    real_type t248 = t12 * t247;
    real_type t249 = t248 * t29;
    real_type t250 = t245 * t45;
    real_type t251 = t248 * t48;
    real_type t253 = t61 * t64 * t8;
    real_type t254 = t253 * t58;
    real_type t255 = t5 * t17;
    real_type t256 = t54 * t255;
    real_type t257 = t256 * t68;
    real_type t258 = t253 * t78;
    real_type t259 = t256 * t81;
    result__[ 4   ] = -t1 * t223 * t154 + t246 + t249 + t250 - t251 + t254 - t257 + t258 + t259;
    real_type t262 = t25 * t8;
    real_type t263 = t22 * t262;
    real_type t264 = t263 * t16;
    real_type t265 = t12 * t255;
    real_type t266 = t265 * t29;
    real_type t267 = t263 * t45;
    real_type t268 = t265 * t48;
    real_type t269 = t64 * t5;
    real_type t270 = t61 * t269;
    real_type t271 = t270 * t58;
    real_type t272 = t54 * t247;
    real_type t273 = t272 * t68;
    real_type t274 = t270 * t78;
    real_type t275 = t272 * t81;
    result__[ 5   ] = -t1 * t241 * t142 - t264 + t266 - t267 - t268 + t271 + t273 + t274 - t275;
    real_type t279 = t12 * t22 * t28;
    real_type t281 = t12 * t22 * t47;
    real_type t283 = t54 * t61 * t67;
    real_type t285 = t54 * t61 * t80;
    real_type t286 = t214 * t85;
    real_type t287 = t110 * t96;
    real_type t290 = -t287 * t109 - t214 * t117;
    real_type t294 = t110 * t185 + t214 * t135;
    real_type t298 = -t287 * t143 - t214 * t147;
    real_type t302 = t287 * t155 + t214 * t159;
    result__[ 6   ] = -t290 * t107 - t294 * t128 - t298 * t142 - t302 * t154 - t279 + t281 - t283 + t285 + t286;
    real_type t304 = t84 * t107;
    real_type t305 = t108 * t304;
    real_type t307 = t96 * t1 * t186;
    real_type t310 = t176 * t108;
    real_type t312 = t1 * t92;
    real_type t313 = t96 * t86;
    real_type t314 = t313 * t312;
    real_type t317 = t129 * t128;
    real_type t324 = t84 * t142;
    real_type t325 = t7 * t324;
    real_type t328 = t176 * t7;
    real_type t332 = t84 * t154;
    real_type t333 = t2 * t332;
    real_type t336 = t176 * t2;
    result__[ 7   ] = -2 * t171 * t87 * t317 - 2 * t314 * t176 * t317 + 2 * t314 * t310 * t304 + 2 * t314 * t328 * t324 - 2 * t314 * t336 * t332 + 2 * t307 * t305 + 2 * t307 * t325 - 2 * t307 * t333 + t169 + t172;
    real_type t340 = ModelPars[iM_path_following_tolerance];
    real_type t341 = 1.0 / t340;
    real_type t342 = t341 * t86;
    real_type t343 = -1 - t342;
    real_type t344 = ALIAS_PathFollowingTolerance_min_DD(t343);
    real_type t346 = t340 * t340;
    real_type t347 = 1.0 / t346;
    real_type t349 = t342 - 1;
    real_type t350 = ALIAS_PathFollowingTolerance_max_DD(t349);
    real_type t358 = t1 * t92 * t176 * t87;
    result__[ 8   ] = t347 * t344 * t1 + t347 * t350 * t1 + 2 * t176 * t312 * t85 + 2 * t358 * t305 - 2 * t358 * t317 + 2 * t358 * t325 - 2 * t358 * t333;
    real_type t369 = t108 * t107;
    real_type t370 = t101 * t176;
    real_type t371 = t1 * t370;
    real_type t373 = t84 * t128;
    real_type t376 = t7 * t142;
    real_type t378 = t2 * t154;
    result__[ 9   ] = t87 * t1 * t208 + t371 * t369 - 2 * t371 * t373 + t371 * t376 - t371 * t378;
    result__[ 10  ] = t371 * t304;
    result__[ 11  ] = -t371 * t332;
    result__[ 12  ] = t371 * t324;
    real_type t381 = ALIAS_PathFollowingTolerance_min_D(t343);
    real_type t383 = ALIAS_PathFollowingTolerance_max_D(t349);
    result__[ 13  ] = t101 * t310 * t304 + t101 * t328 * t324 - t101 * t336 * t332 + t186 * t85 - t370 * t317 - t341 * t381 + t341 * t383;
    real_type t393 = t1 * t287;
    real_type t396 = t313 * t170;
    result__[ 14  ] = t396 * t87 * t369 - 2 * t396 * t87 * t373 + t396 * t87 * t376 - t396 * t87 * t378 + t393 * t369 - 2 * t393 * t373 + t393 * t376 - t393 * t378 + t210;
    result__[ 15  ] = result__[9];
    real_type t409 = t108 * t108;
    real_type t410 = t129 + t409;
    real_type t411 = 1.0 / t410;
    real_type t412 = t411 * t1;
    real_type t414 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t415 = 1.0 / t414;
    real_type t419 = sqrt(t410);
    real_type t420 = ALIAS_nominalFeed();
    real_type t421 = t419 - t420;
    real_type t422 = t421 * t1;
    real_type t424 = 1.0 / t419 / t410;
    real_type t425 = t424 * t415;
    real_type t429 = 1.0 / t419;
    real_type t432 = 2 * t429 * t415 * t422;
    real_type t433 = 1.0 / t420;
    real_type t435 = t433 * t419 - 0.101e1;
    real_type t436 = ALIAS_vLimit_DD(t435);
    real_type t437 = t436 * t1;
    real_type t438 = t420 * t420;
    real_type t439 = 1.0 / t438;
    real_type t440 = t439 * t411;
    real_type t443 = ALIAS_vLimit_D(t435);
    real_type t444 = t443 * t1;
    real_type t445 = t433 * t424;
    real_type t449 = t433 * t429 * t444;
    real_type t451 = t1 * t110;
    result__[ 16  ] = -2 * t451 * t87 * t128 + 2 * t415 * t129 * t412 - 2 * t129 * t425 * t422 + t129 * t440 * t437 - t129 * t445 * t444 + t432 + t449;
    real_type t468 = t84 * t433;
    result__[ 17  ] = t84 * t108 * t439 * t411 * t437 - 2 * t108 * t84 * t424 * t415 * t422 + 2 * t84 * t415 * t108 * t412 - t108 * t468 * t424 * t444 + t451 * t87 * t107;
    result__[ 18  ] = -t451 * t87 * t154;
    result__[ 19  ] = t451 * t87 * t142;
    real_type t476 = t415 * t421;
    real_type t480 = t429 * t443;
    real_type t483 = t110 * t87;
    result__[ 20  ] = 2 * t84 * t429 * t476 + t110 * t83 + t483 * t369 - 2 * t483 * t373 + t483 * t376 - t483 * t378 + t468 * t480;
    result__[ 21  ] = t396 * t87 * t304 + t393 * t304;
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    result__[ 24  ] = 2 * t415 * t409 * t412 - 2 * t409 * t425 * t422 + t409 * t440 * t437 - t409 * t445 * t444 + t432 + t449;
    result__[ 25  ] = 2 * t108 * t429 * t476 + t108 * t433 * t480 + t483 * t304 + MU__[1];
    result__[ 26  ] = -t396 * t87 * t332 - t393 * t332 + t246 + t249 + t250 - t251 + t254 - t257 + t258 + t259;
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    real_type t512 = ModelPars[iM_as_max];
    real_type t513 = 1.0 / t512;
    real_type t514 = t513 * t2;
    real_type t515 = -1 - t514;
    real_type t516 = ALIAS_as_limit_min_DD(t515);
    real_type t518 = t512 * t512;
    real_type t519 = 1.0 / t518;
    real_type t521 = t514 - 1;
    real_type t522 = ALIAS_as_limit_max_DD(t521);
    real_type t525 = t5 * t5;
    real_type t526 = t25 * t525;
    real_type t529 = t8 * t8;
    real_type t530 = t64 * t529;
    result__[ 29  ] = t519 * t516 * t1 + t519 * t522 * t1 + t526 * t16 + t526 * t45 + t530 * t58 + t530 * t78;
    real_type t533 = t5 * t262;
    real_type t536 = t8 * t269;
    result__[ 30  ] = -t533 * t16 - t533 * t45 + t536 * t58 + t536 * t78;
    real_type t539 = ALIAS_as_limit_min_D(t515);
    real_type t541 = ALIAS_as_limit_max_D(t521);
    result__[ 31  ] = -t12 * t5 * t28 + t12 * t5 * t47 - t54 * t8 * t67 + t54 * t8 * t80 - t483 * t332 - t513 * t539 + t513 * t541 + t107;
    result__[ 32  ] = t396 * t87 * t324 + t393 * t324 - t264 + t266 - t267 - t268 + t271 + t273 + t274 - t275;
    result__[ 33  ] = result__[12];
    result__[ 34  ] = result__[19];
    result__[ 35  ] = result__[30];
    real_type t555 = ModelPars[iM_an_max];
    real_type t556 = 1.0 / t555;
    real_type t557 = t556 * t7;
    real_type t558 = -1 - t557;
    real_type t559 = ALIAS_an_limit_min_DD(t558);
    real_type t561 = t555 * t555;
    real_type t562 = 1.0 / t561;
    real_type t564 = t557 - 1;
    real_type t565 = ALIAS_an_limit_max_DD(t564);
    real_type t568 = t25 * t529;
    real_type t571 = t64 * t525;
    result__[ 36  ] = t562 * t559 * t1 + t562 * t565 * t1 + t568 * t16 + t568 * t45 + t571 * t58 + t571 * t78;
    real_type t574 = ALIAS_an_limit_min_D(t558);
    real_type t576 = ALIAS_an_limit_max_D(t564);
    result__[ 37  ] = t12 * t8 * t28 - t12 * t8 * t47 - t54 * t5 * t67 + t54 * t5 * t80 + t483 * t324 - t556 * t574 + t556 * t576 + t128;
    result__[ 38  ] = -t290 * t107 - t294 * t128 - t298 * t142 - t302 * t154 - t279 + t281 - t283 + t285 + t286;
    result__[ 39  ] = result__[13];
    result__[ 40  ] = result__[20];
    result__[ 41  ] = result__[25];
    result__[ 42  ] = result__[31];
    result__[ 43  ] = result__[37];
    result__[ 44  ] = ALIAS_timePositive_DD(-t1);
    real_type t598 = ALIAS_jsControl_D_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 45  ] = t598 + t142;
    real_type t600 = ModelPars[iM_jn_max];
    real_type t601 = ALIAS_jnControl_D_1(U__[iU_jn], -t600, t600);
    result__[ 46  ] = t601 + t154;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 47, i_segment );
  }

}

// EOF: CNOC_Methods_AdjointODE.cc
