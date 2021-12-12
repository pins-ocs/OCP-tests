/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_problem.cc                                        |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  CNOC::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t2   = timePositive(t1);
    real_type t3   = X__[iX_vs];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_vn];
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t13  = vLimit(0.101e1 - 1.0 / t9 * t8);
    real_type t15  = X__[iX_n];
    real_type t19  = PathFollowingTolerance(1.0 / ModelPars[iM_path_following_tolerance] * t15);
    real_type t21  = X__[iX_as];
    real_type t25  = as_limit(1.0 / ModelPars[iM_as_max] * t21);
    real_type t27  = X__[iX_an];
    real_type t31  = an_limit(1.0 / ModelPars[iM_an_max] * t27);
    real_type t33  = X__[iX_s];
    real_type t34  = ALIAS_theta(t33);
    real_type t35  = cos(t34);
    real_type t37  = sin(t34);
    real_type t43  = ax_limit(1.0 / ModelPars[iM_ax_max] * (t35 * t21 - t37 * t27));
    real_type t51  = ay_limit(1.0 / ModelPars[iM_ay_max] * (t37 * t21 + t35 * t27));
    real_type t54  = pow(t8 - t9, 2);
    real_type t57  = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t62  = ALIAS_kappa(t33);
    real_type t65  = 1.0 / (-t62 * t15 + 1);
    real_type t73  = t65 * t62;
    real_type result__ = t2 + t13 * t1 + t19 * t1 + t25 * t1 + t31 * t1 + t43 * t1 + t51 * t1 + 1.0 / t57 * t54 * t1 + t1 * t65 * t3 * L__[iL_lambda1__xo] + t1 * t5 * L__[iL_lambda2__xo] - t1 * (-t73 * t5 * t3 - t21) * L__[iL_lambda3__xo] - t1 * (t65 * t62 * t4 - t27) * L__[iL_lambda4__xo] - t1 * (-t73 * t27 * t3 - U__[iU_js]) * L__[iL_lambda5__xo] - t1 * (t73 * t21 * t3 - U__[iU_jn]) * L__[iL_lambda6__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  CNOC::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t2   = timePositive(t1);
    real_type t4   = X__[iX_vs] * X__[iX_vs];
    real_type t6   = X__[iX_vn] * X__[iX_vn];
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t13  = vLimit(0.101e1 - 1.0 / t9 * t8);
    real_type t19  = PathFollowingTolerance(X__[iX_n] / ModelPars[iM_path_following_tolerance]);
    real_type t21  = X__[iX_as];
    real_type t25  = as_limit(1.0 / ModelPars[iM_as_max] * t21);
    real_type t27  = X__[iX_an];
    real_type t31  = an_limit(1.0 / ModelPars[iM_an_max] * t27);
    real_type t34  = ALIAS_theta(X__[iX_s]);
    real_type t35  = cos(t34);
    real_type t37  = sin(t34);
    real_type t43  = ax_limit(1.0 / ModelPars[iM_ax_max] * (t35 * t21 - t37 * t27));
    real_type t51  = ay_limit(1.0 / ModelPars[iM_ay_max] * (t37 * t21 + t35 * t27));
    real_type result__ = t13 * t1 + t19 * t1 + t25 * t1 + t31 * t1 + t43 * t1 + t51 * t1 + t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  CNOC::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t5   = jsControl(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t8   = ModelPars[iM_jn_max];
    real_type t9   = jnControl(U__[iU_jn], -t8, t8);
    real_type result__ = t1 * t5 + t1 * t9;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  CNOC::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_vs] * X__[iX_vs];
    real_type t5   = X__[iX_vn] * X__[iX_vn];
    real_type t7   = sqrt(t3 + t5);
    real_type t8   = ALIAS_nominalFeed();
    real_type t10  = pow(t7 - t8, 2);
    real_type t13  = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type result__ = 1.0 / t13 * t10 * X__[iX_coV];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  CNOC::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->get_segment_by_index(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DmayerDxxp_numEqns() const
  { return 14; }

  void
  CNOC::DmayerDxxp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->get_segment_by_index(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 14, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer
  CNOC::DlagrangeDxup_numEqns() const
  { return 9; }

  void
  CNOC::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    real_type t2   = X__[iX_vs];
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_vn];
    real_type t5   = t4 * t4;
    real_type t7   = sqrt(t3 + t5);
    real_type t8   = ALIAS_nominalFeed();
    real_type t9   = t7 - t8;
    real_type t10  = t9 * X__[iX_coV];
    real_type t12  = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t13  = 1.0 / t12;
    real_type t15  = 1.0 / t7 * t13;
    result__[ 2   ] = 2 * t2 * t15 * t10;
    result__[ 3   ] = 2 * t4 * t15 * t10;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    real_type t20  = t9 * t9;
    result__[ 6   ] = t13 * t20;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 9, i_segment );
  }

  integer
  CNOC::DJDx_numEqns() const
  { return 7; }

  void
  CNOC::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
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
    real_type t14  = ALIAS_ax_limit_D(t13);
    real_type t15  = t14 * t1;
    real_type t16  = ALIAS_theta_D(t3);
    real_type t17  = t16 * t2;
    real_type t19  = t16 * t7;
    real_type t28  = 1.0 / ModelPars[iM_ay_max];
    real_type t29  = t28 * (t8 * t2 + t7 * t5);
    real_type t30  = ALIAS_ay_limit_D(t29);
    real_type t31  = t30 * t1;
    result__[ 0   ] = t12 * (-t8 * t17 - t5 * t19) * t15 + t28 * (t5 * t17 - t8 * t19) * t31;
    real_type t39  = 1.0 / ModelPars[iM_path_following_tolerance];
    real_type t40  = t39 * X__[iX_n];
    real_type t41  = ALIAS_PathFollowingTolerance_D(t40);
    result__[ 1   ] = t39 * t41 * t1;
    real_type t43  = X__[iX_vs];
    real_type t44  = t43 * t43;
    real_type t45  = X__[iX_vn];
    real_type t46  = t45 * t45;
    real_type t48  = sqrt(t44 + t46);
    real_type t49  = ALIAS_nominalFeed();
    real_type t50  = 1.0 / t49;
    real_type t52  = 0.101e1 - t50 * t48;
    real_type t53  = ALIAS_vLimit_D(t52);
    real_type t54  = t53 * t1;
    real_type t56  = t50 / t48;
    result__[ 2   ] = -t43 * t56 * t54;
    result__[ 3   ] = -t45 * t56 * t54;
    real_type t62  = 1.0 / ModelPars[iM_as_max];
    real_type t63  = t62 * t2;
    real_type t64  = ALIAS_as_limit_D(t63);
    result__[ 4   ] = t62 * t64 * t1 + t12 * t5 * t15 + t28 * t8 * t31;
    real_type t72  = 1.0 / ModelPars[iM_an_max];
    real_type t73  = t72 * t7;
    real_type t74  = ALIAS_an_limit_D(t73);
    result__[ 5   ] = t72 * t74 * t1 - t12 * t8 * t15 + t28 * t5 * t31;
    real_type t81  = ALIAS_timePositive_D(t1);
    real_type t82  = vLimit(t52);
    real_type t83  = PathFollowingTolerance(t40);
    real_type t84  = as_limit(t63);
    real_type t85  = an_limit(t73);
    real_type t86  = ax_limit(t13);
    real_type t87  = ay_limit(t29);
    real_type t91  = jsControl(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t93  = ModelPars[iM_jn_max];
    real_type t94  = jnControl(U__[iU_jn], -t93, t93);
    result__[ 6   ] = t81 + t82 + t83 + t84 + t85 + t86 + t87 + t91 + t94;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DJDp_numEqns() const
  { return 0; }

  void
  CNOC::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DJDu_numEqns() const
  { return 2; }

  void
  CNOC::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t5   = ALIAS_jsControl_D_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t1 * t5;
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = ALIAS_jnControl_D_1(U__[iU_jn], -t7, t7);
    result__[ 1   ] = t8 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDu_eval", 2, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  CNOC::q_numEqns() const
  { return 1; }

  void
  CNOC::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  CNOC::segmentLink_numEqns() const
  { return 0; }

  void
  CNOC::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  CNOC::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  CNOC::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  CNOC::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  CNOC::jump_numEqns() const
  { return 14; }

  void
  CNOC::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->get_segment_by_index(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->get_segment_by_index(i_segment_right);
    real_type t2   = QL__[iQ_zeta];
    result__[ 0   ] = XL__[iX_s] - t2;
    result__[ 1   ] = XL__[iX_n];
    real_type t4   = XL__[iX_vn];
    real_type t5   = ALIAS_theta_L(t2);
    real_type t6   = QR__[iQ_zeta];
    real_type t7   = ALIAS_theta_R(t6);
    real_type t8   = t5 - t7;
    real_type t9   = sin(t8);
    real_type t11  = XL__[iX_vs];
    real_type t12  = cos(t8);
    result__[ 2   ] = -t12 * t11 + t9 * t4 + XR__[iX_vs];
    result__[ 3   ] = -t9 * t11 - t12 * t4 + XR__[iX_vn];
    real_type t18  = XL__[iX_an];
    real_type t20  = XL__[iX_as];
    result__[ 4   ] = -t12 * t20 + t9 * t18 + XR__[iX_as];
    result__[ 5   ] = -t12 * t18 - t9 * t20 + XR__[iX_an];
    result__[ 6   ] = LL__[iL_lambda7__xo];
    result__[ 7   ] = XR__[iX_s] - t6;
    result__[ 8   ] = XR__[iX_n];
    real_type t27  = LR__[iL_lambda4__xo];
    real_type t29  = LR__[iL_lambda3__xo];
    result__[ 9   ] = -t12 * t29 - t9 * t27 + LL__[iL_lambda3__xo];
    result__[ 10  ] = -t12 * t27 + t9 * t29 + LL__[iL_lambda4__xo];
    real_type t35  = LR__[iL_lambda6__xo];
    real_type t37  = LR__[iL_lambda5__xo];
    result__[ 11  ] = -t12 * t37 - t9 * t35 + LL__[iL_lambda5__xo];
    result__[ 12  ] = -t12 * t35 + t9 * t37 + LL__[iL_lambda6__xo];
    result__[ 13  ] = LR__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 14, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DjumpDxlxlp_numRows() const
  { return 14; }

  integer
  CNOC::DjumpDxlxlp_numCols() const
  { return 28; }

  integer
  CNOC::DjumpDxlxlp_nnz() const
  { return 30; }

  void
  CNOC::DjumpDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 16  ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 17  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 5   ;
    iIndex[10] = 4   ; jIndex[10] = 18  ;
    iIndex[11] = 5   ; jIndex[11] = 4   ;
    iIndex[12] = 5   ; jIndex[12] = 5   ;
    iIndex[13] = 5   ; jIndex[13] = 19  ;
    iIndex[14] = 6   ; jIndex[14] = 13  ;
    iIndex[15] = 7   ; jIndex[15] = 14  ;
    iIndex[16] = 8   ; jIndex[16] = 15  ;
    iIndex[17] = 9   ; jIndex[17] = 9   ;
    iIndex[18] = 9   ; jIndex[18] = 23  ;
    iIndex[19] = 9   ; jIndex[19] = 24  ;
    iIndex[20] = 10  ; jIndex[20] = 10  ;
    iIndex[21] = 10  ; jIndex[21] = 23  ;
    iIndex[22] = 10  ; jIndex[22] = 24  ;
    iIndex[23] = 11  ; jIndex[23] = 11  ;
    iIndex[24] = 11  ; jIndex[24] = 25  ;
    iIndex[25] = 11  ; jIndex[25] = 26  ;
    iIndex[26] = 12  ; jIndex[26] = 12  ;
    iIndex[27] = 12  ; jIndex[27] = 25  ;
    iIndex[28] = 12  ; jIndex[28] = 26  ;
    iIndex[29] = 13  ; jIndex[29] = 27  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->get_segment_by_index(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    real_type t2   = ALIAS_theta_L(QL__[iQ_zeta]);
    real_type t4   = ALIAS_theta_R(QR__[iQ_zeta]);
    real_type t5   = t2 - t4;
    real_type t6   = cos(t5);
    result__[ 2   ] = -t6;
    result__[ 3   ] = sin(t5);
    result__[ 4   ] = 1;
    result__[ 5   ] = -result__[3];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = 1;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = result__[3];
    result__[ 10  ] = 1;
    result__[ 11  ] = result__[5];
    result__[ 12  ] = result__[8];
    result__[ 13  ] = 1;
    result__[ 14  ] = 1;
    result__[ 15  ] = 1;
    result__[ 16  ] = 1;
    result__[ 17  ] = 1;
    result__[ 18  ] = result__[12];
    result__[ 19  ] = result__[11];
    result__[ 20  ] = 1;
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[18];
    result__[ 23  ] = 1;
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = 1;
    result__[ 27  ] = result__[21];
    result__[ 28  ] = result__[24];
    result__[ 29  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 30, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  CNOC::post_numEqns() const
  { return 17; }

  void
  CNOC::post_eval(
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
    real_type t1   = X__[iX_vs];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_vn];
    real_type t4   = t3 * t3;
    result__[ 0   ] = sqrt(t2 + t4);
    real_type t6   = X__[iX_as];
    real_type t7   = t6 * t6;
    real_type t8   = X__[iX_an];
    real_type t9   = t8 * t8;
    result__[ 1   ] = sqrt(t7 + t9);
    real_type t11  = U__[iU_js];
    real_type t12  = t11 * t11;
    real_type t13  = U__[iU_jn];
    real_type t14  = t13 * t13;
    result__[ 2   ] = sqrt(t12 + t14);
    real_type t16  = X__[iX_s];
    real_type t17  = ALIAS_theta(t16);
    real_type t18  = cos(t17);
    real_type t20  = sin(t17);
    result__[ 3   ] = t1 * t18 - t20 * t3;
    result__[ 4   ] = t1 * t20 + t18 * t3;
    result__[ 5   ] = t18 * t6 - t20 * t8;
    result__[ 6   ] = t18 * t8 + t20 * t6;
    result__[ 7   ] = t11 * t18 - t13 * t20;
    result__[ 8   ] = t11 * t20 + t13 * t18;
    result__[ 9   ] = ALIAS_xPath(t16);
    result__[ 10  ] = ALIAS_yPath(t16);
    real_type t32  = X__[iX_n];
    result__[ 11  ] = ALIAS_xTraj(t16, t32);
    result__[ 12  ] = ALIAS_yTraj(t16, t32);
    real_type t33  = ModelPars[iM_pf_error];
    result__[ 13  ] = ALIAS_xLimitLeft(t16, t33);
    result__[ 14  ] = ALIAS_yLimitLeft(t16, t33);
    result__[ 15  ] = ALIAS_xLimitRight(t16, t33);
    result__[ 16  ] = ALIAS_yLimitRight(t16, t33);
    Mechatronix::check_in_segment( result__, "post_eval", 17, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::integrated_post_numEqns() const
  { return 1; }

  void
  CNOC::integrated_post_eval(
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
    result__[ 0   ] = X__[iX_coV];
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: CNOC_Methods_problem.cc
