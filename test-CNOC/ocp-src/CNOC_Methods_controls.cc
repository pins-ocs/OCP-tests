/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_controls.cc                                       |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  CNOC::g_numEqns() const
  { return 2; }

  void
  CNOC::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = XM__[6];
    real_type t5   = ALIAS_jsControl_D_1(UM__[0], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t5 * t1 + t1 * LM__[4];
    real_type t10  = ModelPars[iM_jn_max];
    real_type t11  = ALIAS_jnControl_D_1(UM__[1], -t10, t10);
    result__[ 1   ] = t11 * t1 + t1 * LM__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DgDxlxlp_numRows() const
  { return 2; }

  integer
  CNOC::DgDxlxlp_numCols() const
  { return 28; }

  integer
  CNOC::DgDxlxlp_nnz() const
  { return 8; }

  void
  CNOC::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 11  ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 20  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 25  ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 12  ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 20  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 26  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_jsControl_D_1(UM__[0], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = 0.5e0 * t4 + 0.5e0 * LM__[4];
    result__[ 1   ] = 0.5e0 * XM__[6];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    real_type t10  = ModelPars[iM_jn_max];
    real_type t11  = ALIAS_jnControl_D_1(UM__[1], -t10, t10);
    result__[ 4   ] = 0.5e0 * t11 + 0.5e0 * LM__[5];
    result__[ 5   ] = result__[3];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DgDu_numRows() const
  { return 2; }

  integer
  CNOC::DgDu_numCols() const
  { return 2; }

  integer
  CNOC::DgDu_nnz() const
  { return 2; }

  void
  CNOC::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = XM__[6];
    real_type t5   = ALIAS_jsControl_D_1_1(UM__[0], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    result__[ 0   ] = t5 * t1;
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = ALIAS_jnControl_D_1_1(UM__[1], -t7, t7);
    result__[ 1   ] = t8 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  CNOC::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    integer i_segment = LEFT__.i_segment;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    U__[ iU_js ] = jsControl.solve(-LM__[4], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t5   = ModelPars[iM_jn_max];
    U__[ iU_jn ] = jnControl.solve(-LM__[5], -t5, t5);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    // midpoint
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    integer i_segment = LEFT__.i_segment;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_1_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_1_1 = 0.0e0;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_1_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_1_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_1_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type tmp_1_5 = 0.0e0;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_1_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_1_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_1_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_1_9 = 0.0e0;
    real_type tmp_0_10 = 0.0e0;
    real_type tmp_1_10 = 0.0e0;
    real_type t4   = jsControl.solve_rhs(-LM__[4], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type tmp_0_11 = -0.5e0 * t4;
    real_type tmp_1_11 = 0.0e0;
    real_type tmp_0_12 = 0.0e0;
    real_type t7   = ModelPars[iM_jn_max];
    real_type t8   = jnControl.solve_rhs(-LM__[5], -t7, t7);
    real_type tmp_1_12 = -0.5e0 * t8;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_1_13 = 0.0e0;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_1_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_1_15 = 0.0e0;
    real_type tmp_0_16 = 0.0e0;
    real_type tmp_1_16 = 0.0e0;
    real_type tmp_0_17 = 0.0e0;
    real_type tmp_1_17 = 0.0e0;
    real_type tmp_0_18 = 0.0e0;
    real_type tmp_1_18 = 0.0e0;
    real_type tmp_0_19 = 0.0e0;
    real_type tmp_1_19 = 0.0e0;
    real_type tmp_0_20 = 0.0e0;
    real_type tmp_1_20 = 0.0e0;
    real_type tmp_0_21 = 0.0e0;
    real_type tmp_1_21 = 0.0e0;
    real_type tmp_0_22 = 0.0e0;
    real_type tmp_1_22 = 0.0e0;
    real_type tmp_0_23 = 0.0e0;
    real_type tmp_1_23 = 0.0e0;
    real_type tmp_0_24 = 0.0e0;
    real_type tmp_1_24 = 0.0e0;
    real_type tmp_0_25 = tmp_0_11;
    real_type tmp_1_25 = 0.0e0;
    real_type tmp_0_26 = 0.0e0;
    real_type tmp_1_26 = tmp_1_12;
    real_type tmp_0_27 = 0.0e0;
    real_type tmp_1_27 = 0.0e0;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(1, 4) = tmp_1_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(1, 5) = tmp_1_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(1, 6) = tmp_1_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(1, 7) = tmp_1_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(1, 8) = tmp_1_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(1, 9) = tmp_1_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(1, 10) = tmp_1_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(1, 11) = tmp_1_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(1, 12) = tmp_1_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(1, 13) = tmp_1_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(1, 14) = tmp_1_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(1, 15) = tmp_1_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(1, 16) = tmp_1_16;
    DuDxlxlp(0, 17) = tmp_0_17;
    DuDxlxlp(1, 17) = tmp_1_17;
    DuDxlxlp(0, 18) = tmp_0_18;
    DuDxlxlp(1, 18) = tmp_1_18;
    DuDxlxlp(0, 19) = tmp_0_19;
    DuDxlxlp(1, 19) = tmp_1_19;
    DuDxlxlp(0, 20) = tmp_0_20;
    DuDxlxlp(1, 20) = tmp_1_20;
    DuDxlxlp(0, 21) = tmp_0_21;
    DuDxlxlp(1, 21) = tmp_1_21;
    DuDxlxlp(0, 22) = tmp_0_22;
    DuDxlxlp(1, 22) = tmp_1_22;
    DuDxlxlp(0, 23) = tmp_0_23;
    DuDxlxlp(1, 23) = tmp_1_23;
    DuDxlxlp(0, 24) = tmp_0_24;
    DuDxlxlp(1, 24) = tmp_1_24;
    DuDxlxlp(0, 25) = tmp_0_25;
    DuDxlxlp(1, 25) = tmp_1_25;
    DuDxlxlp(0, 26) = tmp_0_26;
    DuDxlxlp(1, 26) = tmp_1_26;
    DuDxlxlp(0, 27) = tmp_0_27;
    DuDxlxlp(1, 27) = tmp_1_27;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 56 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  CNOC::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
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
    real_type t53  = U__[iU_js];
    real_type t56  = jsControl(t53, ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t58  = U__[iU_jn];
    real_type t59  = ModelPars[iM_jn_max];
    real_type t60  = jnControl(t58, -t59, t59);
    real_type t63  = ALIAS_kappa(t33);
    real_type t66  = 1.0 / (-t63 * t15 + 1);
    real_type t70  = pow(-t1 * t66 * t3 + V__[0], 2);
    real_type t74  = pow(-t5 * t1 + V__[1], 2);
    real_type t77  = t66 * t63;
    real_type t82  = pow(V__[2] + t1 * (-t77 * t5 * t3 - t21), 2);
    real_type t89  = pow(V__[3] + t1 * (t66 * t63 * t4 - t27), 2);
    real_type t96  = pow(V__[4] + t1 * (-t77 * t27 * t3 - t53), 2);
    real_type t103 = pow(V__[5] + t1 * (t77 * t21 * t3 - t58), 2);
    real_type t105 = V__[6] * V__[6];
    real_type result__ = t13 * t1 + t19 * t1 + t25 * t1 + t31 * t1 + t43 * t1 + t51 * t1 + t56 * t1 + t60 * t1 + t103 + t105 + t2 + t70 + t74 + t82 + t89 + t96;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DmDu_numEqns() const
  { return 2; }

  void
  CNOC::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t2   = U__[iU_js];
    real_type t5   = ALIAS_jsControl_D_1(t2, ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t8   = X__[iX_vs];
    real_type t12  = ALIAS_kappa(X__[iX_s]);
    real_type t17  = 1.0 / (-t12 * X__[iX_n] + 1) * t12;
    result__[ 0   ] = t5 * t1 - 2 * t1 * (V__[4] + t1 * (-t17 * X__[iX_an] * t8 - t2));
    real_type t24  = U__[iU_jn];
    real_type t25  = ModelPars[iM_jn_max];
    real_type t26  = ALIAS_jnControl_D_1(t24, -t25, t25);
    result__[ 1   ] = t26 * t1 - 2 * t1 * (V__[5] + t1 * (t17 * X__[iX_as] * t8 - t24));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DmDuu_numRows() const
  { return 2; }

  integer
  CNOC::DmDuu_numCols() const
  { return 2; }

  integer
  CNOC::DmDuu_nnz() const
  { return 2; }

  void
  CNOC::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_coV];
    real_type t5   = ALIAS_jsControl_D_1_1(U__[iU_js], ModelPars[iM_js_min], ModelPars[iM_js_max]);
    real_type t7   = t1 * t1;
    real_type t8   = 2 * t7;
    result__[ 0   ] = t5 * t1 + t8;
    real_type t10  = ModelPars[iM_jn_max];
    real_type t11  = ALIAS_jnControl_D_1_1(U__[iU_jn], -t10, t10);
    result__[ 1   ] = t11 * t1 + t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: CNOC_Methods_controls.cc
