/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_problem.cc                                        |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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
    real_type t2   = timePositive(-t1);
    real_type t3   = X__[iX_vs];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_vn];
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t13  = vLimit(1.0 / t9 * t8 - 0.101e1);
    real_type t15  = X__[iX_n];
    real_type t18  = 1.0 / ModelPars[iM_path_following_tolerance] * t15;
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
    real_type t45  = X__[iX_s];
    real_type t46  = ALIAS_theta(t45);
    real_type t47  = cos(t46);
    real_type t49  = sin(t46);
    real_type t54  = 1.0 / ModelPars[iM_ax_max] * (t47 * t25 - t49 * t35);
    real_type t56  = ax_limit_min(-1 - t54);
    real_type t59  = ax_limit_max(t54 - 1);
    real_type t66  = 1.0 / ModelPars[iM_ay_max] * (t49 * t25 + t47 * t35);
    real_type t68  = ay_limit_min(-1 - t66);
    real_type t71  = ay_limit_max(t66 - 1);
    real_type t74  = pow(t8 - t9, 2);
    real_type t77  = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t82  = ALIAS_kappa(t45);
    real_type t85  = 1.0 / (-t82 * t15 + 1);
    real_type t93  = t85 * t82;
    real_type result__ = t2 + t13 * t1 + t20 * t1 + t23 * t1 + t30 * t1 + t33 * t1 + t40 * t1 + t43 * t1 + t56 * t1 + t59 * t1 + t68 * t1 + t71 * t1 + 1.0 / t77 * t74 * t1 + t1 * t85 * t3 * L__[iL_lambda1__xo] + t1 * t5 * L__[iL_lambda2__xo] - t1 * (-t93 * t5 * t3 - t25) * L__[iL_lambda3__xo] - t1 * (t85 * t82 * t4 - t35) * L__[iL_lambda4__xo] - t1 * (-t93 * t35 * t3 - U__[iU_js]) * L__[iL_lambda5__xo] - t1 * (t93 * t25 * t3 - U__[iU_jn]) * L__[iL_lambda6__xo];
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
  CNOC::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JP_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  CNOC::JU_eval(
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
    real_type result__ = t5 * t1 + t9 * t1;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  CNOC::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
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
    real_type t54  = 1.0 / ModelPars[iM_ax_max] * (t25 * t47 - t35 * t49);
    real_type t56  = ax_limit_min(-1 - t54);
    real_type t59  = ax_limit_max(t54 - 1);
    real_type t66  = 1.0 / ModelPars[iM_ay_max] * (t25 * t49 + t35 * t47);
    real_type t68  = ay_limit_min(-1 - t66);
    real_type t71  = ay_limit_max(t66 - 1);
    real_type result__ = t1 * t13 + t1 * t20 + t1 * t23 + t1 * t30 + t1 * t33 + t1 * t40 + t1 * t43 + t1 * t56 + t1 * t59 + t1 * t68 + t1 * t71 + t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "LT_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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

  integer CNOC::DmayerDxxp_numEqns() const { return 14; }

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

  integer CNOC::DlagrangeDxup_numEqns() const { return 9; }

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

  /*\
   |   ___ ____   ___  ____ _____
   |  |_ _|  _ \ / _ \|  _ \_   _|
   |   | || |_) | | | | |_) || |
   |   | ||  __/| |_| |  __/ | |
   |  |___|_|    \___/|_|    |_|
  \*/
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::IPOPT_hess_numRows() const { return 9; }
  integer CNOC::IPOPT_hess_numCols() const { return 9; }
  integer CNOC::IPOPT_hess_nnz()     const { return 44; }

  void
  CNOC::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[42] = 7   ; jIndex[42] = 6   ;
    iIndex[43] = 8   ; jIndex[43] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::IPOPT_hess_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            sigma__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
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
    real_type t96  = t6 * t21 * t16;
    real_type t98  = t6 * t6;
    real_type t101 = t16 * t4 * t11;
    real_type t107 = t16 * t49;
    real_type t108 = t6 * t21;
    result__[ 1   ] = 2 * t6 * t16 * t23 * t12 + t16 * t13 * t21 * t3 - t13 * (-2 * t101 * t98 * t29 - 2 * t96 * t29) * t27 - t13 * (2 * t101 * t98 * t49 + 2 * t108 * t107) * t48 - t13 * (-2 * t101 * t98 * t64 - 2 * t96 * t64) * t62 - t13 * (2 * t101 * t98 * t77 + 2 * t96 * t77) * t75;
    real_type t130 = t21 * t1;
    real_type t136 = t16 * t42;
    real_type t145 = t136 * t6 * t2 + t30 * t16 * t2;
    result__[ 2   ] = t16 * t23 * t130 - t13 * (-t136 * t6 * t28 - t30 * t16 * t28) * t27 - 2 * t13 * t145 * t48 - t13 * (-t136 * t6 * t63 - t30 * t16 * t63) * t62 - t13 * (t136 * t6 * t76 + t30 * t16 * t76) * t75;
    real_type t163 = -t145;
    result__[ 3   ] = -t13 * t163 * t27;
    result__[ 4   ] = -t13 * t145 * t75;
    result__[ 5   ] = -t13 * t163 * t62;
    real_type t171 = t30 * t16;
    result__[ 6   ] = t136 * t3 - (-t136 * t37 - t171 * t29) * t27 - (t30 * t107 + t136 * t55) * t48 - (-t136 * t68 - t171 * t64) * t62 - (t136 * t81 + t171 * t77) * t75;
    result__[ 7   ] = result__[1];
    real_type t191 = t2 * t27;
    real_type t195 = t13 * t11 * t98 * t6;
    real_type t197 = t49 * t48;
    real_type t199 = t2 * t62;
    real_type t202 = t2 * t75;
    result__[ 8   ] = 2 * t98 * t13 * t11 * t3 + 2 * t195 * t28 * t191 + 2 * t195 * t63 * t199 - 2 * t195 * t76 * t202 - 2 * t195 * t197;
    real_type t208 = t28 * t27;
    real_type t209 = t21 * t98;
    real_type t210 = t13 * t209;
    real_type t212 = t2 * t48;
    real_type t215 = t63 * t62;
    real_type t217 = t76 * t75;
    result__[ 9   ] = t6 * t13 * t130 + t210 * t208 - 2 * t210 * t212 + t210 * t215 - t210 * t217;
    result__[ 10  ] = t210 * t191;
    result__[ 11  ] = -t210 * t202;
    result__[ 12  ] = t210 * t199;
    result__[ 13  ] = t21 * t98 * t28 * t191 + t21 * t98 * t63 * t199 - t21 * t98 * t76 * t202 + t108 * t3 - t209 * t197;
    result__[ 14  ] = result__[2];
    result__[ 15  ] = result__[9];
    real_type t231 = t13 * sigma__;
    real_type t232 = t28 * t28;
    real_type t233 = t49 + t232;
    real_type t234 = 1.0 / t233;
    real_type t237 = ModelPars[iM_deltaFeed] * ModelPars[iM_deltaFeed];
    real_type t238 = 1.0 / t237;
    real_type t241 = sqrt(t233);
    real_type t242 = ALIAS_nominalFeed();
    real_type t243 = t241 - t242;
    real_type t244 = t243 * t231;
    real_type t247 = 1.0 / t241 / t233 * t238;
    real_type t251 = 1.0 / t241;
    real_type t253 = t251 * t238 * t243 * t231;
    real_type t255 = t13 * t30;
    result__[ 16  ] = 2 * t238 * t49 * t234 * t231 - 2 * t49 * t247 * t244 - 2 * t255 * t6 * t48 + 2 * t253;
    result__[ 17  ] = 2 * t2 * t238 * t28 * t234 * t231 - 2 * t29 * t247 * t244 + t255 * t6 * t27;
    result__[ 18  ] = -t255 * t6 * t75;
    result__[ 19  ] = t255 * t6 * t62;
    real_type t271 = t243 * sigma__;
    real_type t272 = t251 * t238;
    real_type t277 = t30 * t6;
    result__[ 20  ] = 2 * t2 * t272 * t271 + t30 * t1 + t277 * t208 - 2 * t277 * t212 + t277 * t215 - t277 * t217;
    result__[ 21  ] = result__[3];
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    result__[ 24  ] = 2 * t238 * t232 * t234 * t231 - 2 * t232 * t247 * t244 + 2 * t253;
    result__[ 25  ] = 2 * t28 * t272 * t271 + t277 * t191 + L__[iL_lambda2__xo];
    result__[ 26  ] = result__[4];
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    result__[ 29  ] = -t277 * t202 + t27;
    result__[ 30  ] = result__[5];
    result__[ 31  ] = result__[12];
    result__[ 32  ] = result__[19];
    result__[ 33  ] = t277 * t199 + t48;
    result__[ 34  ] = result__[6];
    result__[ 35  ] = result__[13];
    result__[ 36  ] = result__[20];
    result__[ 37  ] = result__[25];
    result__[ 38  ] = result__[29];
    result__[ 39  ] = result__[33];
    result__[ 40  ] = t62;
    result__[ 41  ] = t75;
    result__[ 42  ] = result__[40];
    result__[ 43  ] = result__[41];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 44, i_segment );
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

  integer CNOC::segmentLink_numEqns() const { return 0; }

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

  integer CNOC::DsegmentLinkDxp_numRows() const { return 0; }
  integer CNOC::DsegmentLinkDxp_numCols() const { return 0; }
  integer CNOC::DsegmentLinkDxp_nnz() const { return 0; }

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

  integer CNOC::jump_numEqns() const { return 14; }

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
  integer CNOC::DjumpDxlxlp_numRows() const { return 14; }
  integer CNOC::DjumpDxlxlp_numCols() const { return 28; }
  integer CNOC::DjumpDxlxlp_nnz()     const { return 30; }

  void
  CNOC::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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

  integer CNOC::post_numEqns() const { return 17; }

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

  integer CNOC::integrated_post_numEqns() const { return 1; }

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
