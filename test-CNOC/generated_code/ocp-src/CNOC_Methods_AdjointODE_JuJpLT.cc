/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_AdjointODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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

  integer CNOC::JP_numEqns() const { return 0; }

  void
  CNOC::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::LT_numEqns() const { return 12; }

  void
  CNOC::LT_eval(
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
    result__[ 0   ] = timePositive(-t1);
    real_type t3   = X__[iX_vs] * X__[iX_vs];
    real_type t5   = X__[iX_vn] * X__[iX_vn];
    real_type t7   = sqrt(t3 + t5);
    real_type t8   = ALIAS_nominalFeed();
    real_type t12  = vLimit(1.0 / t8 * t7 - 0.101e1);
    result__[ 1   ] = t12 * t1;
    real_type t16  = X__[iX_n] / ModelPars[iM_path_following_tolerance];
    real_type t18  = PathFollowingTolerance_min(-1 - t16);
    result__[ 2   ] = t18 * t1;
    real_type t20  = PathFollowingTolerance_max(t16 - 1);
    result__[ 3   ] = t20 * t1;
    real_type t21  = X__[iX_as];
    real_type t24  = 1.0 / ModelPars[iM_as_max] * t21;
    real_type t26  = as_limit_min(-1 - t24);
    result__[ 4   ] = t26 * t1;
    real_type t28  = as_limit_max(t24 - 1);
    result__[ 5   ] = t28 * t1;
    real_type t29  = X__[iX_an];
    real_type t32  = 1.0 / ModelPars[iM_an_max] * t29;
    real_type t34  = an_limit_min(-1 - t32);
    result__[ 6   ] = t34 * t1;
    real_type t36  = an_limit_max(t32 - 1);
    result__[ 7   ] = t36 * t1;
    real_type t38  = ALIAS_theta(X__[iX_s]);
    real_type t39  = cos(t38);
    real_type t41  = sin(t38);
    real_type t46  = 1.0 / ModelPars[iM_ax_max] * (t39 * t21 - t41 * t29);
    real_type t48  = ax_limit_min(-1 - t46);
    result__[ 8   ] = t48 * t1;
    real_type t50  = ax_limit_max(t46 - 1);
    result__[ 9   ] = t50 * t1;
    real_type t56  = 1.0 / ModelPars[iM_ay_max] * (t41 * t21 + t39 * t29);
    real_type t58  = ay_limit_min(-1 - t56);
    result__[ 10  ] = t58 * t1;
    real_type t60  = ay_limit_max(t56 - 1);
    result__[ 11  ] = t60 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CNOC::JU_numEqns() const { return 2; }

  void
  CNOC::JU_eval(
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
    real_type t5   = jsControl(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t1 * t5;
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = jnControl(U__[iU_jn], -t7, t7);
    result__[ 1   ] = t8 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
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
  integer CNOC::DJPDxpu_numRows() const { return 0; }
  integer CNOC::DJPDxpu_numCols() const { return 9; }
  integer CNOC::DJPDxpu_nnz()     const { return 0; }

  void
  CNOC::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  CNOC::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DLTDxpu_numRows() const { return 12; }
  integer CNOC::DLTDxpu_numCols() const { return 9; }
  integer CNOC::DLTDxpu_nnz()     const { return 32; }

  void
  CNOC::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 6   ;
    iIndex[10] = 5   ; jIndex[10] = 4   ;
    iIndex[11] = 5   ; jIndex[11] = 6   ;
    iIndex[12] = 6   ; jIndex[12] = 5   ;
    iIndex[13] = 6   ; jIndex[13] = 6   ;
    iIndex[14] = 7   ; jIndex[14] = 5   ;
    iIndex[15] = 7   ; jIndex[15] = 6   ;
    iIndex[16] = 8   ; jIndex[16] = 0   ;
    iIndex[17] = 8   ; jIndex[17] = 4   ;
    iIndex[18] = 8   ; jIndex[18] = 5   ;
    iIndex[19] = 8   ; jIndex[19] = 6   ;
    iIndex[20] = 9   ; jIndex[20] = 0   ;
    iIndex[21] = 9   ; jIndex[21] = 4   ;
    iIndex[22] = 9   ; jIndex[22] = 5   ;
    iIndex[23] = 9   ; jIndex[23] = 6   ;
    iIndex[24] = 10  ; jIndex[24] = 0   ;
    iIndex[25] = 10  ; jIndex[25] = 4   ;
    iIndex[26] = 10  ; jIndex[26] = 5   ;
    iIndex[27] = 10  ; jIndex[27] = 6   ;
    iIndex[28] = 11  ; jIndex[28] = 0   ;
    iIndex[29] = 11  ; jIndex[29] = 4   ;
    iIndex[30] = 11  ; jIndex[30] = 5   ;
    iIndex[31] = 11  ; jIndex[31] = 6   ;
  }


  void
  CNOC::DLTDxpu_sparse(
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
    real_type t2   = ALIAS_timePositive_D(-t1);
    result__[ 0   ] = -t2;
    real_type t3   = X__[iX_vs];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_vn];
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t10  = 1.0 / t9;
    real_type t12  = t10 * t8 - 0.101e1;
    real_type t13  = ALIAS_vLimit_D(t12);
    real_type t14  = t13 * t1;
    real_type t16  = t10 / t8;
    result__[ 1   ] = t3 * t16 * t14;
    result__[ 2   ] = t5 * t16 * t14;
    result__[ 3   ] = vLimit(t12);
    real_type t21  = 1.0 / ModelPars[iM_path_following_tolerance];
    real_type t22  = t21 * X__[iX_n];
    real_type t23  = -1 - t22;
    real_type t24  = ALIAS_PathFollowingTolerance_min_D(t23);
    result__[ 4   ] = -t21 * t24 * t1;
    result__[ 5   ] = PathFollowingTolerance_min(t23);
    real_type t27  = t22 - 1;
    real_type t28  = ALIAS_PathFollowingTolerance_max_D(t27);
    result__[ 6   ] = t21 * t28 * t1;
    result__[ 7   ] = PathFollowingTolerance_max(t27);
    real_type t30  = X__[iX_as];
    real_type t32  = 1.0 / ModelPars[iM_as_max];
    real_type t33  = t32 * t30;
    real_type t34  = -1 - t33;
    real_type t35  = ALIAS_as_limit_min_D(t34);
    result__[ 8   ] = -t32 * t35 * t1;
    result__[ 9   ] = as_limit_min(t34);
    real_type t38  = t33 - 1;
    real_type t39  = ALIAS_as_limit_max_D(t38);
    result__[ 10  ] = t32 * t39 * t1;
    result__[ 11  ] = as_limit_max(t38);
    real_type t41  = X__[iX_an];
    real_type t43  = 1.0 / ModelPars[iM_an_max];
    real_type t44  = t43 * t41;
    real_type t45  = -1 - t44;
    real_type t46  = ALIAS_an_limit_min_D(t45);
    result__[ 12  ] = -t43 * t46 * t1;
    result__[ 13  ] = an_limit_min(t45);
    real_type t49  = t44 - 1;
    real_type t50  = ALIAS_an_limit_max_D(t49);
    result__[ 14  ] = t43 * t50 * t1;
    result__[ 15  ] = an_limit_max(t49);
    real_type t52  = X__[iX_s];
    real_type t53  = ALIAS_theta(t52);
    real_type t54  = cos(t53);
    real_type t56  = sin(t53);
    real_type t60  = 1.0 / ModelPars[iM_ax_max];
    real_type t61  = t60 * (t30 * t54 - t41 * t56);
    real_type t62  = -1 - t61;
    real_type t63  = ALIAS_ax_limit_min_D(t62);
    real_type t64  = t63 * t1;
    real_type t65  = ALIAS_theta_D(t52);
    real_type t66  = t65 * t30;
    real_type t68  = t65 * t41;
    real_type t71  = t60 * (-t54 * t68 - t56 * t66);
    result__[ 16  ] = -t71 * t64;
    real_type t73  = t60 * t54;
    result__[ 17  ] = -t73 * t64;
    real_type t75  = t60 * t56;
    result__[ 18  ] = t75 * t64;
    result__[ 19  ] = ax_limit_min(t62);
    real_type t76  = t61 - 1;
    real_type t77  = ALIAS_ax_limit_max_D(t76);
    real_type t78  = t77 * t1;
    result__[ 20  ] = t71 * t78;
    result__[ 21  ] = t73 * t78;
    result__[ 22  ] = -t75 * t78;
    result__[ 23  ] = ax_limit_max(t76);
    real_type t84  = 1.0 / ModelPars[iM_ay_max];
    real_type t85  = t84 * (t30 * t56 + t41 * t54);
    real_type t86  = -1 - t85;
    real_type t87  = ALIAS_ay_limit_min_D(t86);
    real_type t88  = t87 * t1;
    real_type t92  = t84 * (t54 * t66 - t56 * t68);
    result__[ 24  ] = -t92 * t88;
    real_type t94  = t84 * t56;
    result__[ 25  ] = -t94 * t88;
    real_type t96  = t84 * t54;
    result__[ 26  ] = -t96 * t88;
    result__[ 27  ] = ay_limit_min(t86);
    real_type t98  = t85 - 1;
    real_type t99  = ALIAS_ay_limit_max_D(t98);
    real_type t100 = t99 * t1;
    result__[ 28  ] = t92 * t100;
    result__[ 29  ] = t94 * t100;
    result__[ 30  ] = t96 * t100;
    result__[ 31  ] = ay_limit_max(t98);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 32, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::DJUDxpu_numRows() const { return 2; }
  integer CNOC::DJUDxpu_numCols() const { return 9; }
  integer CNOC::DJUDxpu_nnz()     const { return 4; }

  void
  CNOC::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 8   ;
  }


  void
  CNOC::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_js];
    real_type t2   = ModelPars[iM_js_min];
    real_type t3   = ModelPars[iM_js_max];
    result__[ 0   ] = jsControl(t1, t2, t3);
    real_type t4   = X__[iX_coV];
    real_type t5   = ALIAS_jsControl_D_1(t1, t2, t3);
    result__[ 1   ] = t5 * t4;
    real_type t6   = U__[iU_jn];
    real_type t7   = ModelPars[iM_jn_max];
    result__[ 2   ] = jnControl(t6, -t7, t7);
    real_type t8   = ALIAS_jnControl_D_1(t6, -t7, t7);
    result__[ 3   ] = t8 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 4, i_segment );
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
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 21, i_segment );
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
    real_type t27  = OMEGA__[8];
    real_type t30  = ALIAS_ax_limit_min_D(t14);
    real_type t31  = t30 * t1;
    real_type t32  = ALIAS_theta_DD(t3);
    real_type t33  = t32 * t2;
    real_type t35  = t17 * t17;
    real_type t36  = t35 * t2;
    real_type t38  = t32 * t7;
    real_type t40  = t35 * t7;
    real_type t43  = t12 * (-t8 * t33 - t5 * t36 - t5 * t38 + t8 * t40);
    real_type t46  = t13 - 1;
    real_type t47  = ALIAS_ax_limit_max_DD(t46);
    real_type t48  = t47 * t1;
    real_type t49  = OMEGA__[9];
    real_type t52  = ALIAS_ax_limit_max_D(t46);
    real_type t53  = t52 * t1;
    real_type t59  = ModelPars[iM_ay_max];
    real_type t60  = 1.0 / t59;
    real_type t61  = t60 * (t8 * t2 + t5 * t7);
    real_type t62  = -1 - t61;
    real_type t63  = ALIAS_ay_limit_min_DD(t62);
    real_type t64  = t63 * t1;
    real_type t67  = t5 * t18 - t8 * t20;
    real_type t68  = t67 * t67;
    real_type t69  = t59 * t59;
    real_type t70  = 1.0 / t69;
    real_type t71  = t70 * t68;
    real_type t72  = OMEGA__[10];
    real_type t75  = ALIAS_ay_limit_min_D(t62);
    real_type t76  = t75 * t1;
    real_type t82  = t60 * (t5 * t33 - t8 * t36 - t8 * t38 - t5 * t40);
    real_type t85  = t61 - 1;
    real_type t86  = ALIAS_ay_limit_max_DD(t85);
    real_type t87  = t86 * t1;
    real_type t88  = OMEGA__[11];
    real_type t91  = ALIAS_ay_limit_max_D(t85);
    real_type t92  = t91 * t1;
    result__[ 0   ] = t27 * t26 * t16 + t49 * t26 * t48 - t27 * t43 * t31 + t49 * t43 * t53 + t72 * t71 * t64 + t88 * t71 * t87 - t72 * t82 * t76 + t88 * t82 * t92;
    real_type t96  = t22 * t25;
    real_type t97  = t27 * t96;
    real_type t99  = t17 * t31;
    real_type t100 = t12 * t8;
    real_type t104 = t49 * t96;
    real_type t106 = t17 * t53;
    real_type t110 = t67 * t70;
    real_type t111 = t72 * t110;
    real_type t113 = t17 * t76;
    real_type t114 = t60 * t5;
    real_type t118 = t88 * t110;
    real_type t120 = t17 * t92;
    result__[ 1   ] = -t49 * t100 * t106 + t27 * t100 * t99 + t104 * t5 * t48 + t111 * t8 * t64 - t72 * t114 * t113 + t88 * t114 * t120 + t118 * t8 * t87 + t97 * t5 * t16;
    real_type t123 = t8 * t16;
    real_type t125 = t12 * t5;
    real_type t128 = t8 * t48;
    real_type t132 = t5 * t64;
    real_type t134 = t60 * t8;
    real_type t137 = t5 * t87;
    result__[ 2   ] = -t49 * t125 * t106 + t72 * t134 * t113 - t88 * t134 * t120 + t27 * t125 * t99 - t104 * t128 + t111 * t132 + t118 * t137 - t97 * t123;
    real_type t142 = t27 * t12;
    real_type t145 = t49 * t12;
    real_type t148 = t72 * t60;
    real_type t151 = t88 * t60;
    result__[ 3   ] = -t142 * t22 * t30 + t145 * t22 * t52 - t148 * t67 * t75 + t151 * t67 * t91;
    real_type t154 = ModelPars[iM_path_following_tolerance];
    real_type t155 = 1.0 / t154;
    real_type t156 = t155 * X__[iX_n];
    real_type t157 = -1 - t156;
    real_type t158 = ALIAS_PathFollowingTolerance_min_DD(t157);
    real_type t160 = t154 * t154;
    real_type t161 = 1.0 / t160;
    real_type t162 = OMEGA__[2];
    real_type t165 = t156 - 1;
    real_type t166 = ALIAS_PathFollowingTolerance_max_DD(t165);
    real_type t168 = OMEGA__[3];
    result__[ 4   ] = t162 * t161 * t158 * t1 + t168 * t161 * t166 * t1;
    real_type t171 = ALIAS_PathFollowingTolerance_min_D(t157);
    real_type t174 = ALIAS_PathFollowingTolerance_max_D(t165);
    result__[ 5   ] = -t162 * t155 * t171 + t168 * t155 * t174;
    real_type t177 = X__[iX_vs];
    real_type t178 = t177 * t177;
    real_type t179 = X__[iX_vn];
    real_type t180 = t179 * t179;
    real_type t181 = t178 + t180;
    real_type t182 = sqrt(t181);
    real_type t183 = ALIAS_nominalFeed();
    real_type t184 = 1.0 / t183;
    real_type t186 = t184 * t182 - 0.101e1;
    real_type t187 = ALIAS_vLimit_DD(t186);
    real_type t190 = 1.0 / t181 * t187 * t1;
    real_type t191 = t183 * t183;
    real_type t192 = 1.0 / t191;
    real_type t194 = OMEGA__[1];
    real_type t197 = ALIAS_vLimit_D(t186);
    real_type t198 = t197 * t1;
    real_type t201 = 1.0 / t182 / t181 * t198;
    real_type t205 = 1.0 / t182;
    real_type t208 = t194 * t184 * t205 * t198;
    result__[ 6   ] = -t194 * t178 * t184 * t201 + t194 * t178 * t192 * t190 + t208;
    real_type t213 = t177 * t184;
    result__[ 7   ] = t194 * t177 * t179 * t192 * t190 - t179 * t194 * t213 * t201;
    real_type t217 = t205 * t197;
    result__[ 8   ] = t194 * t213 * t217;
    result__[ 9   ] = result__[7];
    result__[ 10  ] = -t194 * t180 * t184 * t201 + t194 * t180 * t192 * t190 + t208;
    result__[ 11  ] = t194 * t179 * t184 * t217;
    result__[ 12  ] = result__[1];
    real_type t227 = ModelPars[iM_as_max];
    real_type t228 = 1.0 / t227;
    real_type t229 = t228 * t2;
    real_type t230 = -1 - t229;
    real_type t231 = ALIAS_as_limit_min_DD(t230);
    real_type t233 = t227 * t227;
    real_type t234 = 1.0 / t233;
    real_type t235 = OMEGA__[4];
    real_type t238 = t229 - 1;
    real_type t239 = ALIAS_as_limit_max_DD(t238);
    real_type t241 = OMEGA__[5];
    real_type t244 = t5 * t5;
    real_type t245 = t25 * t244;
    real_type t250 = t8 * t8;
    real_type t251 = t70 * t250;
    result__[ 13  ] = t235 * t234 * t231 * t1 + t241 * t234 * t239 * t1 + t27 * t245 * t16 + t49 * t245 * t48 + t72 * t251 * t64 + t88 * t251 * t87;
    real_type t256 = t5 * t25;
    real_type t261 = t8 * t70;
    result__[ 14  ] = -t27 * t256 * t123 - t49 * t256 * t128 + t72 * t261 * t132 + t88 * t261 * t137;
    real_type t266 = ALIAS_as_limit_min_D(t230);
    real_type t269 = ALIAS_as_limit_max_D(t238);
    result__[ 15  ] = -t142 * t5 * t30 + t145 * t5 * t52 - t148 * t8 * t75 + t151 * t8 * t91 - t235 * t228 * t266 + t241 * t228 * t269;
    result__[ 16  ] = result__[2];
    result__[ 17  ] = result__[14];
    real_type t280 = ModelPars[iM_an_max];
    real_type t281 = 1.0 / t280;
    real_type t282 = t281 * t7;
    real_type t283 = -1 - t282;
    real_type t284 = ALIAS_an_limit_min_DD(t283);
    real_type t286 = t280 * t280;
    real_type t287 = 1.0 / t286;
    real_type t288 = OMEGA__[6];
    real_type t291 = t282 - 1;
    real_type t292 = ALIAS_an_limit_max_DD(t291);
    real_type t294 = OMEGA__[7];
    real_type t297 = t25 * t250;
    real_type t302 = t70 * t244;
    result__[ 18  ] = t288 * t287 * t284 * t1 + t294 * t287 * t292 * t1 + t27 * t297 * t16 + t49 * t297 * t48 + t72 * t302 * t64 + t88 * t302 * t87;
    real_type t307 = ALIAS_an_limit_min_D(t283);
    real_type t310 = ALIAS_an_limit_max_D(t291);
    result__[ 19  ] = t142 * t8 * t30 - t145 * t8 * t52 - t148 * t5 * t75 + t151 * t5 * t91 - t288 * t281 * t307 + t294 * t281 * t310;
    result__[ 20  ] = result__[3];
    result__[ 21  ] = result__[5];
    result__[ 22  ] = result__[8];
    result__[ 23  ] = result__[11];
    result__[ 24  ] = result__[15];
    result__[ 25  ] = result__[19];
    real_type t321 = ALIAS_timePositive_DD(-t1);
    result__[ 26  ] = OMEGA__[0] * t321;
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
    real_type t1   = U__[iU_js];
    real_type t2   = ModelPars[iM_js_min];
    real_type t3   = ModelPars[iM_js_max];
    real_type t4   = ALIAS_jsControl_D_1(t1, t2, t3);
    real_type t5   = OMEGA__[0];
    result__[ 0   ] = t5 * t4;
    real_type t6   = U__[iU_jn];
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = ALIAS_jnControl_D_1(t6, -t7, t7);
    real_type t9   = OMEGA__[1];
    result__[ 1   ] = t9 * t8;
    result__[ 2   ] = result__[0];
    real_type t10  = X__[iX_coV];
    real_type t11  = ALIAS_jsControl_D_1_1(t1, t2, t3);
    result__[ 3   ] = t5 * t11 * t10;
    result__[ 4   ] = result__[1];
    real_type t13  = ALIAS_jnControl_D_1_1(t6, -t7, t7);
    result__[ 5   ] = t9 * t13 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 6, i_segment );
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
    result__[ 2   ] = t44 * t38 - t46 * t38 + t39 * t43 - t43 * t41;
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
