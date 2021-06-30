/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_AdjointODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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
#define ALIAS_ay_limit_DD(__t1) ay_limit.DD( __t1)
#define ALIAS_ay_limit_D(__t1) ay_limit.D( __t1)
#define ALIAS_ax_limit_DD(__t1) ax_limit.DD( __t1)
#define ALIAS_ax_limit_D(__t1) ax_limit.D( __t1)
#define ALIAS_an_limit_DD(__t1) an_limit.DD( __t1)
#define ALIAS_an_limit_D(__t1) an_limit.D( __t1)
#define ALIAS_as_limit_DD(__t1) as_limit.DD( __t1)
#define ALIAS_as_limit_D(__t1) as_limit.D( __t1)
#define ALIAS_PathFollowingTolerance_DD(__t1) PathFollowingTolerance.DD( __t1)
#define ALIAS_PathFollowingTolerance_D(__t1) PathFollowingTolerance.D( __t1)
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  CNOC::Hx_numEqns() const
  { return 7; }

  void
  CNOC::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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
    real_type t14  = ALIAS_ax_limit_D(t13);
    real_type t15  = t14 * t1;
    real_type t16  = ALIAS_theta_D(t3);
    real_type t17  = t16 * t2;
    real_type t19  = t16 * t7;
    real_type t28  = 1.0 / ModelPars[iM_ay_max];
    real_type t29  = t28 * (t8 * t2 + t5 * t7);
    real_type t30  = ALIAS_ay_limit_D(t29);
    real_type t31  = t30 * t1;
    real_type t37  = L__[iL_lambda1__xo];
    real_type t38  = X__[iX_vs];
    real_type t39  = t38 * t37;
    real_type t40  = X__[iX_n];
    real_type t41  = ALIAS_kappa(t3);
    real_type t43  = -t41 * t40 + 1;
    real_type t44  = t43 * t43;
    real_type t45  = 1.0 / t44;
    real_type t48  = ALIAS_kappa_D(t3);
    real_type t51  = L__[iL_lambda3__xo];
    real_type t52  = X__[iX_vn];
    real_type t53  = t52 * t38;
    real_type t54  = 1.0 / t43;
    real_type t55  = t54 * t48;
    real_type t24  = t40 * t48;
    real_type t59  = t45 * t24;
    real_type t64  = L__[iL_lambda4__xo];
    real_type t65  = t38 * t38;
    real_type t68  = t41 * t65;
    real_type t73  = L__[iL_lambda5__xo];
    real_type t74  = t7 * t38;
    real_type t81  = L__[iL_lambda6__xo];
    real_type t82  = t2 * t38;
    real_type t47  = t45 * t1;
    real_type t56  = t41 * t59;
    result__[ 0   ] = t12 * (-t8 * t17 - t5 * t19) * t15 + t28 * (t5 * t17 - t8 * t19) * t31 + t39 * t47 * t24 - t51 * (-t55 * t53 - t53 * t56) * t1 - t1 * (t54 * t48 * t65 + t59 * t68) * t64 - t73 * (-t55 * t74 - t74 * t56) * t1 - t81 * (t55 * t82 + t82 * t56) * t1;
    real_type t90  = 1.0 / ModelPars[iM_path_following_tolerance];
    real_type t91  = t90 * t40;
    real_type t92  = ALIAS_PathFollowingTolerance_D(t91);
    real_type t98  = t38 * t51;
    real_type t100 = t41 * t41;
    real_type t102 = t100 * t47;
    real_type t106 = t38 * t73;
    real_type t109 = t38 * t81;
    result__[ 1   ] = t41 * t1 * t45 * t39 + t90 * t92 * t1 + t102 * t7 * t106 - t102 * t2 * t109 + t102 * t52 * t98 - t102 * t65 * t64;
    real_type t112 = t52 * t52;
    real_type t114 = sqrt(t65 + t112);
    real_type t115 = ALIAS_nominalFeed();
    real_type t116 = 1.0 / t115;
    real_type t118 = 0.101e1 - t116 * t114;
    real_type t119 = ALIAS_vLimit_D(t118);
    real_type t120 = t119 * t1;
    real_type t121 = 1.0 / t114;
    real_type t122 = t116 * t121;
    real_type t125 = t114 - t115;
    real_type t126 = t125 * t1;
    real_type t128 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t129 = 1.0 / t128;
    real_type t130 = t121 * t129;
    real_type t137 = t54 * t41;
    real_type t138 = t1 * t137;
    result__[ 2   ] = t1 * t54 * t37 - t38 * t122 * t120 + 2 * t38 * t130 * t126 - t138 * t2 * t81 - 2 * t138 * t38 * t64 + t138 * t52 * t51 + t138 * t7 * t73;
    real_type t152 = L__[iL_lambda2__xo];
    result__[ 3   ] = -t52 * t122 * t120 + 2 * t52 * t130 * t126 + t1 * t152 + t138 * t98;
    real_type t156 = 1.0 / ModelPars[iM_as_max];
    real_type t157 = t156 * t2;
    real_type t158 = ALIAS_as_limit_D(t157);
    result__[ 4   ] = t156 * t158 * t1 + t12 * t5 * t15 + t28 * t8 * t31 + t1 * t51 - t138 * t109;
    real_type t168 = 1.0 / ModelPars[iM_an_max];
    real_type t169 = t168 * t7;
    real_type t170 = ALIAS_an_limit_D(t169);
    result__[ 5   ] = t168 * t170 * t1 - t12 * t8 * t15 + t28 * t5 * t31 + t1 * t64 + t138 * t106;
    real_type t179 = ALIAS_timePositive_D(t1);
    real_type t180 = vLimit(t118);
    real_type t181 = PathFollowingTolerance(t91);
    real_type t182 = as_limit(t157);
    real_type t183 = an_limit(t169);
    real_type t184 = ax_limit(t13);
    real_type t185 = ay_limit(t29);
    real_type t186 = U__[iU_js];
    real_type t189 = jsControl(t186, ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t190 = U__[iU_jn];
    real_type t191 = ModelPars[iM_jn_max];
    real_type t192 = jnControl(t190, -t191, t191);
    real_type t193 = t125 * t125;
    result__[ 6   ] = t179 + t180 + t181 + t182 + t183 + t184 + t185 + t189 + t192 + t129 * t193 + t54 * t39 + t52 * t152 - (-t137 * t53 - t2) * t51 - (t54 * t68 - t7) * t64 - (-t137 * t74 - t186) * t73 - (t137 * t82 - t190) * t81;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DHxDx_numRows() const
  { return 7; }

  integer
  CNOC::DHxDx_numCols() const
  { return 7; }

  integer
  CNOC::DHxDx_nnz() const
  { return 45; }

  void
  CNOC::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
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
  }

  void
  CNOC::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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
    real_type t14  = ALIAS_ax_limit_DD(t13);
    real_type t15  = t14 * t1;
    real_type t16  = ALIAS_theta_D(t3);
    real_type t17  = t16 * t2;
    real_type t19  = t16 * t7;
    real_type t21  = -t8 * t17 - t5 * t19;
    real_type t22  = t21 * t21;
    real_type t23  = t11 * t11;
    real_type t24  = 1.0 / t23;
    real_type t27  = ALIAS_ax_limit_D(t13);
    real_type t28  = t27 * t1;
    real_type t29  = ALIAS_theta_DD(t3);
    real_type t30  = t29 * t2;
    real_type t32  = t16 * t16;
    real_type t33  = t32 * t2;
    real_type t35  = t29 * t7;
    real_type t37  = t32 * t7;
    real_type t45  = ModelPars[iM_ay_max];
    real_type t46  = 1.0 / t45;
    real_type t47  = t46 * (t8 * t2 + t5 * t7);
    real_type t48  = ALIAS_ay_limit_DD(t47);
    real_type t49  = t48 * t1;
    real_type t52  = t5 * t17 - t8 * t19;
    real_type t53  = t52 * t52;
    real_type t54  = t45 * t45;
    real_type t55  = 1.0 / t54;
    real_type t58  = ALIAS_ay_limit_D(t47);
    real_type t59  = t58 * t1;
    real_type t67  = L__[iL_lambda1__xo];
    real_type t68  = X__[iX_vs];
    real_type t69  = t68 * t67;
    real_type t70  = X__[iX_n];
    real_type t71  = ALIAS_kappa(t3);
    real_type t73  = -t71 * t70 + 1;
    real_type t74  = t73 * t73;
    real_type t39  = 1.0 / t74;
    real_type t40  = 1.0 / t73;
    real_type t76  = t40 * t39;
    real_type t77  = t76 * t69;
    real_type t78  = t70 * t70;
    real_type t80  = ALIAS_kappa_D(t3);
    real_type t81  = t80 * t80;
    real_type t85  = t39;
    real_type t87  = t70 * t1;
    real_type t88  = ALIAS_kappa_DD(t3);
    real_type t91  = L__[iL_lambda3__xo];
    real_type t92  = X__[iX_vn];
    real_type t93  = t92 * t68;
    real_type t94  = t40;
    real_type t95  = t94 * t88;
    real_type t98  = t70 * t85 * t81;
    real_type t101 = t71 * t93;
    real_type t42  = t78 * t81;
    real_type t103 = t76 * t42;
    real_type t106 = t70 * t85;
    real_type t107 = t88 * t106;
    real_type t112 = L__[iL_lambda4__xo];
    real_type t113 = t68 * t68;
    real_type t119 = t71 * t113;
    real_type t126 = L__[iL_lambda5__xo];
    real_type t127 = t7 * t68;
    real_type t131 = t71 * t127;
    real_type t138 = L__[iL_lambda6__xo];
    real_type t139 = t2 * t68;
    real_type t143 = t71 * t139;
    result__[ 0   ] = t24 * t22 * t15 + t12 * (-t8 * t30 - t5 * t33 - t5 * t35 + t8 * t37) * t28 + t55 * t53 * t49 + t46 * (t5 * t30 - t8 * t33 - t8 * t35 - t5 * t37) * t59 + 2 * t1 * t77 * t42 + t88 * t87 * t85 * t69 - t1 * (-2 * t103 * t101 - t107 * t101 - t95 * t93 - 2 * t98 * t93) * t91 - t1 * (2 * t106 * t81 * t113 + t94 * t88 * t113 + 2 * t103 * t119 + t107 * t119) * t112 - t1 * (-2 * t103 * t131 - t107 * t131 - t95 * t127 - 2 * t98 * t127) * t126 - t1 * (2 * t103 * t143 + t107 * t143 + t95 * t139 + 2 * t98 * t139) * t138;
    real_type t153 = 2 * t71 * t80 * t87 * t77;
    real_type t154 = t1 * t85;
    real_type t155 = t80 * t154;
    real_type t156 = t155 * t69;
    real_type t158 = t71 * t85 * t80;
    real_type t160 = t71 * t71;
    real_type t163 = t80 * t70 * t76;
    real_type t169 = t80 * t113;
    real_type t170 = t71 * t85;
    real_type t161 = t160 * t163;
    result__[ 1   ] = t153 + t156 - t91 * (-2 * t158 * t93 - 2 * t93 * t161) * t1 - t112 * (2 * t113 * t161 + 2 * t170 * t169) * t1 - t126 * (-2 * t158 * t127 - 2 * t127 * t161) * t1 - t138 * (2 * t158 * t139 + 2 * t139 * t161) * t1;
    real_type t192 = t85 * t67;
    real_type t194 = t80 * t87 * t192;
    real_type t198 = t80 * t106;
    real_type t190 = t71 * t198;
    real_type t193 = t94 * t80;
    real_type t207 = t68 * t190 + t68 * t193;
    real_type t202 = t207 * t1;
    result__[ 2   ] = t194 - t91 * (-t92 * t190 - t92 * t193) * t1 - 2 * t112 * t202 - t126 * (-t7 * t190 - t7 * t193) * t1 - t138 * (t2 * t190 + t2 * t193) * t1;
    real_type t225 = -t207;
    real_type t216 = t225 * t1;
    result__[ 3   ] = -t91 * t216;
    real_type t230 = t21 * t24 * t5 * t15;
    real_type t231 = t8 * t16;
    real_type t233 = t12 * t231 * t28;
    real_type t236 = t52 * t55 * t8 * t49;
    real_type t237 = t5 * t16;
    real_type t239 = t46 * t237 * t59;
    result__[ 4   ] = -t138 * t202 + t230 - t233 + t236 + t239;
    real_type t242 = t24 * t8;
    real_type t244 = t21 * t242 * t15;
    real_type t246 = t12 * t237 * t28;
    real_type t247 = t55 * t5;
    real_type t249 = t52 * t247 * t49;
    real_type t251 = t46 * t231 * t59;
    result__[ 5   ] = -t126 * t216 - t244 - t246 + t249 - t251;
    real_type t259 = t94 * t80;
    result__[ 6   ] = t12 * t21 * t27 + t46 * t52 * t58 + t198 * t69 - (-t198 * t101 - t259 * t93) * t91 - (t198 * t119 + t94 * t169) * t112 - (-t259 * t127 - t198 * t131) * t126 - (t259 * t139 + t198 * t143) * t138;
    real_type t276 = t68 * t91;
    real_type t277 = t92 * t276;
    real_type t279 = t80 * t1 * t170;
    real_type t282 = t160 * t92;
    real_type t284 = t1 * t76;
    real_type t285 = t80 * t70;
    real_type t286 = t285 * t284;
    real_type t289 = t113 * t112;
    real_type t296 = t68 * t126;
    real_type t297 = t7 * t296;
    real_type t300 = t160 * t7;
    real_type t304 = t68 * t138;
    real_type t305 = t2 * t304;
    real_type t308 = t160 * t2;
    result__[ 7   ] = -2 * t155 * t71 * t289 - 2 * t286 * t160 * t289 + 2 * t286 * t282 * t276 + 2 * t286 * t300 * t296 - 2 * t286 * t308 * t304 + 2 * t279 * t277 + 2 * t279 * t297 - 2 * t279 * t305 + t153 + t156;
    real_type t312 = ModelPars[iM_path_following_tolerance];
    real_type t313 = 1.0 / t312;
    real_type t314 = t313 * t70;
    real_type t315 = ALIAS_PathFollowingTolerance_DD(t314);
    real_type t317 = t312 * t312;
    real_type t325 = t160 * t71 * t284;
    result__[ 8   ] = 1.0 / t317 * t315 * t1 + 2 * t160 * t284 * t69 + 2 * t325 * t277 - 2 * t325 * t289 + 2 * t325 * t297 - 2 * t325 * t305;
    real_type t336 = t92 * t91;
    real_type t337 = t85 * t160;
    real_type t338 = t1 * t337;
    real_type t340 = t68 * t112;
    real_type t343 = t7 * t126;
    real_type t345 = t2 * t138;
    result__[ 9   ] = t71 * t1 * t192 + t338 * t336 - 2 * t338 * t340 + t338 * t343 - t338 * t345;
    result__[ 10  ] = t338 * t276;
    result__[ 11  ] = -t338 * t304;
    result__[ 12  ] = t338 * t296;
    real_type t348 = ALIAS_PathFollowingTolerance_D(t314);
    result__[ 13  ] = t85 * t282 * t276 + t85 * t300 * t296 - t85 * t308 * t304 + t170 * t69 - t337 * t289 + t313 * t348;
    real_type t358 = t1 * t259;
    real_type t361 = t285 * t154;
    real_type t344 = t71 * t361;
    result__[ 14  ] = t336 * t344 + t358 * t336 - 2 * t340 * t344 - 2 * t358 * t340 + t343 * t344 + t358 * t343 - t345 * t344 - t358 * t345 + t194;
    result__[ 15  ] = result__[9];
    real_type t374 = t92 * t92;
    real_type t375 = t113 + t374;
    real_type t376 = sqrt(t375);
    real_type t377 = ALIAS_nominalFeed();
    real_type t378 = 1.0 / t377;
    real_type t380 = 0.101e1 - t378 * t376;
    real_type t381 = ALIAS_vLimit_DD(t380);
    real_type t382 = t381 * t1;
    real_type t383 = 1.0 / t375;
    real_type t384 = t377 * t377;
    real_type t385 = 1.0 / t384;
    real_type t386 = t385 * t383;
    real_type t389 = ALIAS_vLimit_D(t380);
    real_type t390 = t389 * t1;
    real_type t359 = 1.0 / t376;
    real_type t392 = t383 * t359;
    real_type t393 = t378 * t392;
    real_type t396 = t359;
    real_type t398 = t378 * t396 * t390;
    real_type t399 = t383 * t1;
    real_type t401 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t402 = 1.0 / t401;
    real_type t406 = t376 - t377;
    real_type t407 = t406 * t1;
    real_type t408 = t392 * t402;
    real_type t414 = 2 * t396 * t402 * t407;
    real_type t416 = t1 * t94;
    real_type t365 = t71 * t416;
    result__[ 16  ] = t113 * t386 * t382 + t113 * t393 * t390 + 2 * t402 * t113 * t399 - 2 * t113 * t408 * t407 - 2 * t112 * t365 - t398 + t414;
    real_type t424 = t68 * t378;
    result__[ 17  ] = t385 * t383 * t382 * t93 + t92 * t424 * t392 * t390 - 2 * t392 * t402 * t407 * t93 + 2 * t68 * t402 * t92 * t399 + t91 * t365;
    result__[ 18  ] = -t138 * t365;
    result__[ 19  ] = t126 * t365;
    real_type t441 = t396 * t389;
    real_type t443 = t402 * t406;
    real_type t448 = t94 * t71;
    result__[ 20  ] = 2 * t68 * t396 * t443 + t448 * t336 - 2 * t448 * t340 + t448 * t343 - t448 * t345 - t424 * t441 + t94 * t67;
    result__[ 21  ] = t276 * t344 + t358 * t276;
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    result__[ 24  ] = t374 * t386 * t382 + t374 * t393 * t390 + 2 * t402 * t374 * t399 - 2 * t374 * t408 * t407 - t398 + t414;
    result__[ 25  ] = -t92 * t378 * t441 + 2 * t92 * t396 * t443 + t448 * t276 + L__[iL_lambda2__xo];
    result__[ 26  ] = -t304 * t344 - t358 * t304 + t230 - t233 + t236 + t239;
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    real_type t477 = ModelPars[iM_as_max];
    real_type t478 = 1.0 / t477;
    real_type t479 = t478 * t2;
    real_type t480 = ALIAS_as_limit_DD(t479);
    real_type t482 = t477 * t477;
    real_type t485 = t5 * t5;
    real_type t488 = t8 * t8;
    result__[ 29  ] = 1.0 / t482 * t480 * t1 + t24 * t485 * t15 + t55 * t488 * t49;
    result__[ 30  ] = -t5 * t242 * t15 + t8 * t247 * t49;
    real_type t495 = ALIAS_as_limit_D(t479);
    result__[ 31  ] = t12 * t5 * t27 + t46 * t8 * t58 - t448 * t304 + t478 * t495 + t91;
    result__[ 32  ] = t296 * t344 + t358 * t296 - t244 - t246 + t249 - t251;
    result__[ 33  ] = result__[12];
    result__[ 34  ] = result__[19];
    result__[ 35  ] = result__[30];
    real_type t505 = ModelPars[iM_an_max];
    real_type t506 = 1.0 / t505;
    real_type t507 = t506 * t7;
    real_type t508 = ALIAS_an_limit_DD(t507);
    real_type t510 = t505 * t505;
    result__[ 36  ] = 1.0 / t510 * t508 * t1 + t24 * t488 * t15 + t55 * t485 * t49;
    real_type t517 = ALIAS_an_limit_D(t507);
    result__[ 37  ] = -t12 * t8 * t27 + t46 * t5 * t58 + t448 * t296 + t506 * t517 + t112;
    result__[ 38  ] = result__[6];
    result__[ 39  ] = result__[13];
    result__[ 40  ] = result__[20];
    result__[ 41  ] = result__[25];
    result__[ 42  ] = result__[31];
    result__[ 43  ] = result__[37];
    result__[ 44  ] = ALIAS_timePositive_DD(t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 45, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DHxDp_numRows() const
  { return 7; }

  integer
  CNOC::DHxDp_numCols() const
  { return 0; }

  integer
  CNOC::DHxDp_nnz() const
  { return 0; }

  void
  CNOC::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DHxDp_sparse(
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

  integer
  CNOC::Hu_numEqns() const
  { return 2; }

  void
  CNOC::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t5   = ALIAS_jsControl_D_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t5 * t1 + t1 * L__[iL_lambda5__xo];
    real_type t10  = ModelPars[iM_jn_max];
    real_type t11  = ALIAS_jnControl_D_1(U__[iU_jn], -t10, t10);
    result__[ 1   ] = t11 * t1 + t1 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DHuDx_numRows() const
  { return 2; }

  integer
  CNOC::DHuDx_numCols() const
  { return 7; }

  integer
  CNOC::DHuDx_nnz() const
  { return 2; }

  void
  CNOC::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_jsControl_D_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t4 + L__[iL_lambda5__xo];
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = ALIAS_jnControl_D_1(U__[iU_jn], -t7, t7);
    result__[ 1   ] = t8 + L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DHuDp_numRows() const
  { return 2; }

  integer
  CNOC::DHuDp_numCols() const
  { return 0; }

  integer
  CNOC::DHuDp_nnz() const
  { return 0; }

  void
  CNOC::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  CNOC::Hp_numEqns() const
  { return 0; }

  void
  CNOC::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DHpDp_numRows() const
  { return 0; }

  integer
  CNOC::DHpDp_numCols() const
  { return 0; }

  integer
  CNOC::DHpDp_nnz() const
  { return 0; }

  void
  CNOC::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  CNOC::eta_numEqns() const
  { return 7; }

  void
  CNOC::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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

  integer
  CNOC::DetaDx_numRows() const
  { return 7; }

  integer
  CNOC::DetaDx_numCols() const
  { return 7; }

  integer
  CNOC::DetaDx_nnz() const
  { return 0; }

  void
  CNOC::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DetaDp_numRows() const
  { return 7; }

  integer
  CNOC::DetaDp_numCols() const
  { return 0; }

  integer
  CNOC::DetaDp_nnz() const
  { return 0; }

  void
  CNOC::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DetaDp_sparse(
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

  integer
  CNOC::nu_numEqns() const
  { return 7; }

  void
  CNOC::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
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

  integer
  CNOC::DnuDx_numRows() const
  { return 7; }

  integer
  CNOC::DnuDx_numCols() const
  { return 7; }

  integer
  CNOC::DnuDx_nnz() const
  { return 0; }

  void
  CNOC::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DnuDp_numRows() const
  { return 7; }

  integer
  CNOC::DnuDp_numCols() const
  { return 0; }

  integer
  CNOC::DnuDp_nnz() const
  { return 0; }

  void
  CNOC::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: CNOC_Methods_AdjointODE.cc
