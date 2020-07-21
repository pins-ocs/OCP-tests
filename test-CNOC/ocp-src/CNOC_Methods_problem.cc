/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods1.cc                                               |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
    return t2 + t13 * t1 + t19 * t1 + t25 * t1 + t31 * t1 + t43 * t1 + t51 * t1 + 1.0 / t57 * t54 * t1 + t1 * t65 * t3 * L__[0] + t1 * t5 * L__[1] - t1 * (-t73 * t5 * t3 - t21) * L__[2] - t1 * (t65 * t62 * t4 - t27) * L__[3] - t1 * (-t73 * t27 * t3 - U__[0]) * L__[4] - t1 * (t73 * t21 * t3 - U__[1]) * L__[5];
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
    integer        i_node,
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    result__[ 0   ] = s;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__.pointer(),"q_eval",1);
    #endif
  }

  /*\
   |    ___
   |   / __|_  _ ___ ______
   |  | (_ | || / -_|_-<_-<
   |   \___|\_,_\___/__/__/
  \*/

  integer
  CNOC::u_guess_numEqns() const
  { return 2; }

  void
  CNOC::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
      ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    std::fill_n( UGUESS__.pointer(), 2, 0 );
    UGUESS__[ iU_js ] = 0;
    UGUESS__[ iU_jn ] = 0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(UGUESS__.pointer(),"u_guess_eval",2);
    #endif
  }

  void
  CNOC::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[7];
    real_type L__[7];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    X__[6] = (LEFT__.x[6]+RIGHT__.x[6])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
    L__[6] = (LEFT__.lambda[6]+RIGHT__.lambda[6])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  CNOC::u_check_if_admissible(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[8];
    ok = ok && jnControl.check_range(U__[1], -t2, t2);
    ok = ok && jsControl.check_range(U__[0], ModelPars[10], ModelPars[9]);
    return ok;
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"post_eval",17);
    #endif
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"integrated_post_eval",1);
    #endif
  }

}

// EOF: CNOC_Methods1.cc
