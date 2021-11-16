/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_AdjointODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_ay_max];
    real_type t2   = X__[iX_s];
    real_type t3   = ALIAS_theta_D(t2);
    real_type t5   = X__[iX_n];
    real_type t6   = ALIAS_kappa(t2);
    real_type t8   = t6 * t5 - 1;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_as];
    real_type t11  = ALIAS_theta(t2);
    real_type t12  = sin(t11);
    real_type t14  = X__[iX_an];
    real_type t15  = cos(t11);
    real_type t17  = t12 * t10 + t15 * t14;
    real_type t21  = t15 * t10 - t12 * t14;
    real_type t22  = ModelPars[iM_ax_max];
    real_type t23  = 1.0 / t22;
    real_type t24  = t23 * t21;
    real_type t25  = ALIAS_ax_limit_D(t24);
    real_type t29  = 1.0 / t1;
    real_type t30  = t29 * t17;
    real_type t31  = ALIAS_ay_limit_D(t30);
    real_type t34  = ALIAS_kappa_D(t2);
    real_type t36  = X__[iX_vs];
    real_type t37  = L__[iL_lambda1__xo];
    real_type t39  = L__[iL_lambda3__xo];
    real_type t40  = X__[iX_vn];
    real_type t41  = t40 * t39;
    real_type t42  = L__[iL_lambda4__xo];
    real_type t43  = t36 * t42;
    real_type t44  = L__[iL_lambda5__xo];
    real_type t45  = t14 * t44;
    real_type t46  = L__[iL_lambda6__xo];
    real_type t47  = t10 * t46;
    real_type t54  = X__[iX_coV];
    real_type t57  = 1.0 / t9;
    result__[ 0   ] = t57 * t29 * t23 * t54 * (-t25 * t17 * t9 * t3 * t1 + (t31 * t21 * t9 * t3 + (t5 * t37 + t41 - t43 + t45 - t47) * t36 * t34 * t1) * t22);
    real_type t59  = ModelPars[iM_path_following_tolerance];
    real_type t60  = 1.0 / t59;
    real_type t61  = t60 * t5;
    real_type t62  = ALIAS_PathFollowingTolerance_D(t61);
    result__[ 1   ] = t57 * t60 * t54 * (t62 * t9 + t36 * t6 * (t6 * (t41 - t43 + t45 - t47) + t37) * t59);
    real_type t73  = t36 * t36;
    real_type t74  = t40 * t40;
    real_type t76  = sqrt(t73 + t74);
    real_type t77  = 1.0 / t76;
    real_type t79  = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t81  = ALIAS_nominalFeed();
    real_type t82  = 1.0 / t81;
    real_type t84  = 0.101e1 - t82 * t76;
    real_type t85  = ALIAS_vLimit_D(t84);
    real_type t107 = 1.0 / t79;
    real_type t109 = 1.0 / t8;
    result__[ 2   ] = -t109 * t107 * t82 * t54 * (t85 * t8 * t36 * t79 + (t76 * (t6 * (t79 * (t41 - 2 * t43 + t45 - t47) - 2 * t36 * t5) + t79 * t37 + 2 * t36) + 2 * t8 * t36 * t81) * t81) * t77;
    real_type t116 = t76 - t81;
    real_type t122 = L__[iL_lambda2__xo];
    real_type t126 = t109 * t54 * t6;
    result__[ 3   ] = 2 * t40 * t77 * t107 * t116 * t54 - t40 * t82 * t77 * t85 * t54 - t126 * t36 * t39 + t54 * t122;
    real_type t129 = 1.0 / ModelPars[iM_as_max];
    real_type t130 = t129 * t10;
    real_type t131 = ALIAS_as_limit_D(t130);
    real_type t134 = t25 * t54;
    real_type t137 = t31 * t54;
    result__[ 4   ] = t29 * t12 * t137 + t126 * t36 * t46 + t129 * t131 * t54 + t23 * t15 * t134 + t54 * t39;
    real_type t144 = 1.0 / ModelPars[iM_an_max];
    real_type t145 = t144 * t14;
    real_type t146 = ALIAS_an_limit_D(t145);
    result__[ 5   ] = -t23 * t12 * t134 - t126 * t36 * t44 + t29 * t15 * t137 + t144 * t146 * t54 + t54 * t42;
    real_type t156 = ALIAS_timePositive_D(t54);
    real_type t157 = vLimit(t84);
    real_type t158 = PathFollowingTolerance(t61);
    real_type t159 = as_limit(t130);
    real_type t160 = an_limit(t145);
    real_type t161 = ax_limit(t24);
    real_type t162 = ay_limit(t30);
    real_type t163 = t116 * t116;
    real_type t170 = -1.0 / t8;
    real_type t171 = t170 * t6;
    result__[ 6   ] = t156 + t157 + t158 + t159 + t160 + t161 + t162 + t107 * t163 - t109 * t36 * t37 + t40 * t122 - (-t171 * t40 * t36 - t10) * t39 - (t170 * t6 * t73 - t14) * t42 - (-t171 * t14 * t36 - U__[iU_js]) * t44 - (t171 * t10 * t36 - U__[iU_jn]) * t46;
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_ax_max];
    real_type t2   = X__[iX_n];
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_kappa(t3);
    real_type t6   = t4 * t2 - 1;
    real_type t7   = t6 * t6;
    real_type t8   = t7 * t6;
    real_type t10  = ModelPars[iM_ay_max];
    real_type t11  = t10 * t10;
    real_type t12  = X__[iX_as];
    real_type t13  = ALIAS_theta_D(t3);
    real_type t14  = t13 * t13;
    real_type t16  = X__[iX_an];
    real_type t17  = ALIAS_theta_DD(t3);
    real_type t19  = t14 * t12 + t17 * t16;
    real_type t20  = ALIAS_theta(t3);
    real_type t21  = cos(t20);
    real_type t23  = sin(t20);
    real_type t26  = t17 * t12 - t14 * t16;
    real_type t32  = t21 * t12 - t23 * t16;
    real_type t33  = 1.0 / t1;
    real_type t34  = t33 * t32;
    real_type t35  = ALIAS_ax_limit_D(t34);
    real_type t41  = t23 * t12 + t21 * t16;
    real_type t42  = t41 * t41;
    real_type t44  = ALIAS_ax_limit_DD(t34);
    real_type t47  = t1 * t1;
    real_type t53  = 1.0 / t10;
    real_type t54  = t53 * t41;
    real_type t55  = ALIAS_ay_limit_D(t54);
    real_type t59  = t32 * t32;
    real_type t60  = ALIAS_ay_limit_DD(t54);
    real_type t63  = X__[iX_vs];
    real_type t65  = ALIAS_kappa_DD(t3);
    real_type t68  = ALIAS_kappa_D(t3);
    real_type t69  = t68 * t68;
    real_type t73  = L__[iL_lambda1__xo];
    real_type t74  = t2 * t73;
    real_type t75  = L__[iL_lambda3__xo];
    real_type t76  = X__[iX_vn];
    real_type t77  = t76 * t75;
    real_type t78  = L__[iL_lambda4__xo];
    real_type t79  = t63 * t78;
    real_type t80  = L__[iL_lambda5__xo];
    real_type t81  = t16 * t80;
    real_type t82  = L__[iL_lambda6__xo];
    real_type t83  = t12 * t82;
    real_type t84  = t74 + t77 - t79 + t81 - t83;
    real_type t90  = X__[iX_coV];
    real_type t92  = 1.0 / t47;
    real_type t93  = 1.0 / t11;
    real_type t94  = t93 * t92;
    real_type t95  = 1.0 / t8;
    result__[ 0   ] = t95 * t94 * t90 * (-t35 * (t21 * t19 + t26 * t23) * t11 * t8 * t1 + t44 * t42 * t8 * t14 * t11 + (-t55 * (t19 * t23 - t21 * t26) * t10 * t8 + t60 * t59 * t8 * t14 + t84 * (t2 * t65 * t4 - 2 * t2 * t69 - t65) * t63 * t11) * t47);
    real_type t99  = 2 * t79;
    result__[ 1   ] = -t95 * (t4 * (t74 + 2 * t77 - t99 + 2 * t81 - 2 * t83) + t73) * t90 * t63 * t68;
    real_type t108 = t90 * t68;
    real_type t110 = 1.0 / t7;
    result__[ 2   ] = t110 * (t74 + t77 - t99 + t81 - t83) * t108;
    real_type t112 = t63 * t75;
    result__[ 3   ] = t110 * t108 * t112;
    real_type t114 = t21 * t13;
    real_type t116 = t41 * t7;
    real_type t117 = t44 * t116;
    real_type t119 = t23 * t13;
    real_type t121 = t35 * t7 * t11;
    real_type t124 = t60 * t32 * t7;
    real_type t126 = t55 * t7;
    real_type t129 = t10 * t63;
    real_type t139 = t110 * t94;
    result__[ 4   ] = -t139 * t90 * (t117 * t11 * t114 + (t121 * t119 + (-t124 * t119 + t10 * (t129 * t68 * t82 - t126 * t114)) * t1) * t1);
    result__[ 5   ] = t139 * (t117 * t11 * t119 + (-t121 * t114 + t1 * (t124 * t114 + (t129 * t68 * t80 - t126 * t119) * t10)) * t1) * t90;
    result__[ 6   ] = t110 * t53 * t33 * (-t35 * t116 * t13 * t10 + t1 * (t84 * t63 * t68 * t10 + t55 * t32 * t7 * t13));
    result__[ 7   ] = result__[1];
    real_type t170 = ModelPars[iM_path_following_tolerance];
    real_type t171 = 1.0 / t170;
    real_type t172 = t171 * t2;
    real_type t173 = ALIAS_PathFollowingTolerance_DD(t172);
    real_type t176 = t170 * t170;
    real_type t179 = t4 * (t77 - t79 + t81 - t83) + t73;
    real_type t181 = t4 * t4;
    result__[ 8   ] = -2 * t95 / t176 * t90 * (-t173 * t8 / 2 + t63 * t181 * t179 * t176);
    real_type t190 = t77 - t99 + t81 - t83;
    result__[ 9   ] = t110 * t90 * (t4 * t190 + t73) * t4;
    real_type t196 = t110 * t90 * t181;
    result__[ 10  ] = t196 * t112;
    real_type t197 = t63 * t82;
    result__[ 11  ] = -t196 * t197;
    real_type t199 = t63 * t80;
    result__[ 12  ] = t196 * t199;
    real_type t200 = ALIAS_PathFollowingTolerance_D(t172);
    result__[ 13  ] = t110 * t171 * (t170 * t63 * t179 * t4 + t200 * t7);
    result__[ 14  ] = result__[2];
    result__[ 15  ] = result__[9];
    real_type t207 = t63 * t63;
    real_type t208 = t76 * t76;
    real_type t209 = t207 + t208;
    real_type t210 = sqrt(t209);
    real_type t211 = ALIAS_nominalFeed();
    real_type t212 = 1.0 / t211;
    real_type t214 = 0.101e1 - t212 * t210;
    real_type t215 = ALIAS_vLimit_DD(t214);
    real_type t216 = t215 * t90;
    real_type t217 = 1.0 / t209;
    real_type t218 = t211 * t211;
    real_type t219 = 1.0 / t218;
    real_type t223 = ALIAS_vLimit_D(t214);
    real_type t224 = t223 * t90;
    real_type t225 = t210 * t209;
    real_type t226 = 1.0 / t225;
    real_type t230 = 1.0 / t210;
    real_type t233 = t217 * t90;
    real_type t235 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t236 = 1.0 / t235;
    real_type t240 = t210 - t211;
    real_type t241 = t240 * t90;
    real_type t250 = 1.0 / t6;
    real_type t251 = t250 * t4;
    result__[ 16  ] = t207 * t212 * t226 * t224 + t207 * t219 * t217 * t216 - 2 * t207 * t226 * t236 * t241 + 2 * t236 * t207 * t233 - t212 * t230 * t224 + 2 * t230 * t236 * t241 + 2 * t251 * t90 * t78;
    result__[ 17  ] = t76 * t63 * t212 * t226 * t224 + t63 * t76 * t219 * t217 * t216 - 2 * t76 * t63 * t226 * t236 * t241 + 2 * t63 * t236 * t76 * t233 - t251 * t90 * t75;
    result__[ 18  ] = t250 * t90 * t4 * t82;
    result__[ 19  ] = -t90 / t6 * t4 * t80;
    result__[ 20  ] = -t250 * t236 * t212 * t230 * (t223 * t6 * t63 * t235 + t211 * (t210 * (t4 * (t235 * t190 - 2 * t63 * t2) + t235 * t73 + 2 * t63) + 2 * t6 * t63 * t211));
    result__[ 21  ] = result__[3];
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    real_type t302 = t207 * t211;
    real_type t311 = t208 * t208;
    real_type t323 = t209 * t209;
    result__[ 24  ] = 2 * t236 * t219 / t210 / t323 * t90 * (-t235 * t302 * t209 * t223 / 2 + t235 * t225 * t208 * t215 / 2 + (t210 * (-t208 * t207 - t311) + t208 * (2 * t225 - t302) + t207 * (t225 - t302)) * t218);
    result__[ 25  ] = -t76 * t212 * t230 * t223 + 2 * t76 * t230 * t236 * t240 - t251 * t112 + L__[iL_lambda2__xo];
    result__[ 26  ] = result__[4];
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    real_type t338 = ModelPars[iM_as_max];
    real_type t339 = 1.0 / t338;
    real_type t340 = t339 * t12;
    real_type t341 = ALIAS_as_limit_DD(t340);
    real_type t343 = t338 * t338;
    real_type t346 = t44 * t90;
    real_type t347 = t21 * t21;
    real_type t350 = t60 * t90;
    real_type t351 = t23 * t23;
    result__[ 29  ] = 1.0 / t343 * t341 * t90 + t92 * t347 * t346 + t93 * t351 * t350;
    result__[ 30  ] = -t93 * t92 * (t11 * t44 - t47 * t60) * t90 * t21 * t23;
    real_type t362 = ALIAS_as_limit_D(t340);
    result__[ 31  ] = t33 * t21 * t35 + t53 * t23 * t55 + t251 * t197 + t339 * t362 + t75;
    result__[ 32  ] = result__[5];
    result__[ 33  ] = result__[12];
    result__[ 34  ] = result__[19];
    result__[ 35  ] = result__[30];
    real_type t369 = ModelPars[iM_an_max];
    real_type t370 = 1.0 / t369;
    real_type t371 = t370 * t16;
    real_type t372 = ALIAS_an_limit_DD(t371);
    real_type t374 = t369 * t369;
    result__[ 36  ] = 1.0 / t374 * t372 * t90 + t92 * t351 * t346 + t93 * t347 * t350;
    real_type t381 = ALIAS_an_limit_D(t371);
    result__[ 37  ] = t53 * t21 * t55 - t33 * t23 * t35 - t251 * t199 + t370 * t381 + t78;
    result__[ 38  ] = result__[6];
    result__[ 39  ] = result__[13];
    result__[ 40  ] = result__[20];
    result__[ 41  ] = result__[25];
    result__[ 42  ] = result__[31];
    result__[ 43  ] = result__[37];
    result__[ 44  ] = ALIAS_timePositive_DD(t90);
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda5__xo];
    result__[ 1   ] = L__[iL_lambda6__xo];
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: CNOC_Methods_AdjointODE.cc
