/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods1.cc                                               |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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
#define ALIAS_nominalFeed_R(___dummy___) segmentRight.feedReferenceRate()
#define ALIAS_nominalFeed_L(___dummy___) segmentLeft.feedReferenceRate()
#define ALIAS_nominalFeed(___dummy___) segment.feedReferenceRate()
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
#define ALIAS_lenSeg_R(___dummy___) segmentRight.ssLength()
#define ALIAS_lenSeg_L(___dummy___) segmentLeft.ssLength()
#define ALIAS_lenSeg(___dummy___) segment.ssLength()
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
    integer              i_segment,
    CellType const &     CELL__,
    P_const_pointer_type P__
  ) const {
    integer        i_cell = CELL__.i_cell;
    real_type const * Q__ = CELL__.qM;
    real_type const * X__ = CELL__.xM;
    real_type const * L__ = CELL__.lambdaM;
    real_type const * U__ = CELL__.uM;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t1   = X__[6];
    real_type t2   = timePositive(t1);
    real_type t3   = X__[2];
    real_type t4   = t3 * t3;
    real_type t5   = X__[3];
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t13  = vLimit(0.101e1 - 1.0 / t9 * t8);
    real_type t15  = X__[1];
    real_type t19  = PathFollowingTolerance(1.0 / ModelPars[19] * t15);
    real_type t21  = X__[4];
    real_type t25  = as_limit(1.0 / ModelPars[5] * t21);
    real_type t27  = X__[5];
    real_type t31  = an_limit(1.0 / ModelPars[2] * t27);
    real_type t33  = X__[0];
    real_type t34  = ALIAS_theta(t33);
    real_type t35  = cos(t34);
    real_type t37  = sin(t34);
    real_type t43  = ax_limit(1.0 / ModelPars[6] * (t35 * t21 - t37 * t27));
    real_type t51  = ay_limit(1.0 / ModelPars[7] * (t37 * t21 + t35 * t27));
    real_type t54  = pow(t8 - t9, 2);
    real_type t57  = ModelPars[17] * ModelPars[17];
    real_type t62  = ALIAS_kappa(t33);
    real_type t65  = 1.0 / (-t62 * t15 + 1);
    real_type t73  = t65 * t62;
    real_type t85  = U__[0];
    real_type t92  = U__[1];
    real_type t100 = jsControl(t85, ModelPars[10], ModelPars[9]);
    real_type t102 = ModelPars[8];
    real_type t103 = jnControl(t92, -t102, t102);
    return t2 + t13 * t1 + t19 * t1 + t25 * t1 + t31 * t1 + t43 * t1 + t51 * t1 + 1.0 / t57 * t54 * t1 + t1 * t65 * t3 * L__[0] + t1 * t5 * L__[1] - t1 * (-t73 * t5 * t3 - t21) * L__[2] - t1 * (t65 * t62 * t4 - t27) * L__[3] - t1 * (-t73 * t27 * t3 - t85) * L__[4] - t1 * (t73 * t21 * t3 - t92) * L__[5] + t100 * t1 + t103 * t1;
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t1   = X__[6];
    real_type t2   = timePositive(t1);
    real_type t4   = X__[2] * X__[2];
    real_type t6   = X__[3] * X__[3];
    real_type t8   = sqrt(t4 + t6);
    real_type t9   = ALIAS_nominalFeed();
    real_type t13  = vLimit(0.101e1 - 1.0 / t9 * t8);
    real_type t19  = PathFollowingTolerance(X__[1] / ModelPars[19]);
    real_type t21  = X__[4];
    real_type t25  = as_limit(1.0 / ModelPars[5] * t21);
    real_type t27  = X__[5];
    real_type t31  = an_limit(1.0 / ModelPars[2] * t27);
    real_type t34  = ALIAS_theta(X__[0]);
    real_type t35  = cos(t34);
    real_type t37  = sin(t34);
    real_type t43  = ax_limit(1.0 / ModelPars[6] * (t35 * t21 - t37 * t27));
    real_type t51  = ay_limit(1.0 / ModelPars[7] * (t37 * t21 + t35 * t27));
    return t13 * t1 + t19 * t1 + t25 * t1 + t31 * t1 + t43 * t1 + t51 * t1 + t2;
  }

  real_type
  CNOC::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t1   = X__[6];
    real_type t5   = jsControl(U__[0], ModelPars[10], ModelPars[9]);
    real_type t8   = ModelPars[8];
    real_type t9   = jnControl(U__[1], -t8, t8);
    return t5 * t1 + t9 * t1;
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t3   = X__[2] * X__[2];
    real_type t5   = X__[3] * X__[3];
    real_type t7   = sqrt(t3 + t5);
    real_type t8   = ALIAS_nominalFeed();
    real_type t10  = pow(t7 - t8, 2);
    real_type t13  = ModelPars[17] * ModelPars[17];
    return 1.0 / t13 * t10 * X__[6];
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
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->getSegmentByIndex(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->getSegmentByIndex(i_segment_right);
    return 0;
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
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
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
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->getSegmentByIndex(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->getSegmentByIndex(i_segment_right);
    real_type t2   = QL__[0];
    result__[ 0   ] = XL__[0] - t2;
    result__[ 1   ] = XL__[1];
    real_type t4   = ALIAS_theta_L(t2);
    real_type t5   = QR__[0];
    real_type t6   = ALIAS_theta_R(t5);
    real_type t7   = t4 - t6;
    real_type t8   = sin(t7);
    real_type t9   = XL__[3];
    real_type t11  = cos(t7);
    real_type t12  = XL__[2];
    result__[ 2   ] = -t12 * t11 + t9 * t8 + XR__[2];
    result__[ 3   ] = -t9 * t11 - t12 * t8 + XR__[3];
    real_type t18  = XL__[5];
    real_type t20  = XL__[4];
    result__[ 4   ] = -t20 * t11 + t18 * t8 + XR__[4];
    result__[ 5   ] = -t18 * t11 - t20 * t8 + XR__[5];
    result__[ 6   ] = LL__[6];
    result__[ 7   ] = XR__[0] - t5;
    result__[ 8   ] = XR__[1];
    real_type t27  = LR__[3];
    real_type t29  = LR__[2];
    result__[ 9   ] = -t11 * t29 - t8 * t27 + LL__[2];
    result__[ 10  ] = -t11 * t27 + t8 * t29 + LL__[3];
    real_type t35  = LR__[5];
    real_type t37  = LR__[4];
    result__[ 11  ] = -t11 * t37 - t8 * t35 + LL__[4];
    result__[ 12  ] = -t11 * t35 + t8 * t37 + LL__[5];
    result__[ 13  ] = LR__[6];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 14, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::DjumpDxlp_numRows() const
  { return 14; }

  integer
  CNOC::DjumpDxlp_numCols() const
  { return 28; }

  integer
  CNOC::DjumpDxlp_nnz() const
  { return 30; }

  void
  CNOC::DjumpDxlp_pattern(
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
  CNOC::DjumpDxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    ToolPath2D::SegmentClass const & segmentLeft  = pToolPath2D->getSegmentByIndex(i_segment_left);
    ToolPath2D::SegmentClass const & segmentRight = pToolPath2D->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    real_type t2   = ALIAS_theta_L(QL__[0]);
    real_type t4   = ALIAS_theta_R(QR__[0]);
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
      Mechatronix::check_in_segment2( result__, "DjumpDxlp_sparse", 30, i_segment_left, i_segment_right );
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t1   = X__[2];
    real_type t2   = t1 * t1;
    real_type t3   = X__[3];
    real_type t4   = t3 * t3;
    result__[ 0   ] = sqrt(t2 + t4);
    real_type t6   = X__[4];
    real_type t7   = t6 * t6;
    real_type t8   = X__[5];
    real_type t9   = t8 * t8;
    result__[ 1   ] = sqrt(t7 + t9);
    real_type t11  = U__[0];
    real_type t12  = t11 * t11;
    real_type t13  = U__[1];
    real_type t14  = t13 * t13;
    result__[ 2   ] = sqrt(t12 + t14);
    real_type t16  = X__[0];
    real_type t17  = ALIAS_theta(t16);
    real_type t18  = cos(t17);
    real_type t20  = sin(t17);
    result__[ 3   ] = t18 * t1 - t20 * t3;
    result__[ 4   ] = t20 * t1 + t18 * t3;
    result__[ 5   ] = t18 * t6 - t20 * t8;
    result__[ 6   ] = t18 * t8 + t20 * t6;
    result__[ 7   ] = t18 * t11 - t20 * t13;
    result__[ 8   ] = t20 * t11 + t18 * t13;
    result__[ 9   ] = ALIAS_xPath(t16);
    result__[ 10  ] = ALIAS_yPath(t16);
    real_type t32  = X__[1];
    result__[ 11  ] = ALIAS_xTraj(t16, t32);
    result__[ 12  ] = ALIAS_yTraj(t16, t32);
    real_type t33  = ModelPars[18];
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    result__[ 0   ] = X__[6];
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: CNOC_Methods1.cc
