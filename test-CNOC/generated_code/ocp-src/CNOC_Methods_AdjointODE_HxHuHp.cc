/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_AdjointODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::Hxp_numEqns() const { return 7; }

  void
  CNOC::Hxp_eval(
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
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DHxpDxpu_numRows() const { return 7; }
  integer CNOC::DHxpDxpu_numCols() const { return 9; }
  integer CNOC::DHxpDxpu_nnz()     const { return 42; }

  void
  CNOC::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[40] = 6   ; jIndex[40] = 7   ;
    iIndex[41] = 6   ; jIndex[41] = 8   ;
  }


  void
  CNOC::DHxpDxpu_sparse(
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
    result__[ 14  ] = t236 * t259 * t6 - 2 * t240 * t259 * t6 + t243 * t259 * t6 - t245 * t259 * t6 + t236 * t256 - 2 * t240 * t256 + t243 * t256 - t245 * t256 + t132;
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
    result__[ 16  ] = 2 * t275 * t278 * t49 - 2 * t284 * t287 * t49 - 2 * t294 * t48 * t6 + 2 * t292;
    result__[ 17  ] = -2 * t2 * t278 * t28 * t284 * t286 + 2 * t2 * t275 * t278 * t28 + t27 * t294 * t6;
    result__[ 18  ] = -t294 * t6 * t75;
    result__[ 19  ] = t294 * t6 * t62;
    real_type t311 = t278 * t283;
    real_type t316 = t30 * t6;
    result__[ 20  ] = 2 * t2 * t290 * t311 + t1 * t30 + t236 * t316 - 2 * t240 * t316 + t243 * t316 - t245 * t316;
    result__[ 21  ] = t188 * t259 * t6 + t188 * t256;
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    result__[ 24  ] = 2 * t272 * t275 * t278 - 2 * t272 * t284 * t287 + 2 * t292;
    result__[ 25  ] = 2 * t28 * t290 * t311 + t188 * t316 + L__[iL_lambda2__xo];
    result__[ 26  ] = -t216 * t259 * t6 - t216 * t256;
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    result__[ 29  ] = -t216 * t316 + t27;
    result__[ 30  ] = t208 * t259 * t6 + t208 * t256;
    result__[ 31  ] = result__[12];
    result__[ 32  ] = result__[19];
    result__[ 33  ] = t208 * t316 + t48;
    result__[ 34  ] = result__[6];
    result__[ 35  ] = result__[13];
    result__[ 36  ] = result__[20];
    result__[ 37  ] = result__[25];
    result__[ 38  ] = result__[29];
    result__[ 39  ] = result__[33];
    result__[ 40  ] = t62;
    result__[ 41  ] = t75;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 42, i_segment );
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

}

// EOF: CNOC_Methods_AdjointODE.cc
