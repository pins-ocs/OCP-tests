/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods.cc                                                |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  CNOC::rhs_ode_numEqns() const
  { return 7; }

  void
  CNOC::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t1   = X__[2];
    real_type t4   = ALIAS_kappa(X__[0]);
    real_type t7   = 1.0 / (-t4 * X__[1] + 1);
    real_type t9   = X__[6];
    result__[ 0   ] = t9 * t7 * t1;
    real_type t10  = X__[3];
    result__[ 1   ] = t9 * t10;
    real_type t11  = X__[4];
    real_type t13  = t7 * t4;
    result__[ 2   ] = -t9 * (-t13 * t10 * t1 - t11);
    real_type t17  = X__[5];
    real_type t18  = t1 * t1;
    result__[ 3   ] = -t9 * (t7 * t4 * t18 - t17);
    result__[ 4   ] = -t9 * (-t13 * t17 * t1 - U__[0]);
    result__[ 5   ] = -t9 * (t13 * t11 * t1 - U__[1]);
    result__[ 6   ] = 0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",7);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::Drhs_odeDx_numRows() const
  { return 7; }

  integer
  CNOC::Drhs_odeDx_numCols() const
  { return 7; }

  integer
  CNOC::Drhs_odeDx_nnz() const
  { return 27; }

  void
  CNOC::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 6   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 3   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 6   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 2   ;
    iIndex[ 9  ] = 2   ; jIndex[ 9  ] = 3   ;
    iIndex[ 10 ] = 2   ; jIndex[ 10 ] = 4   ;
    iIndex[ 11 ] = 2   ; jIndex[ 11 ] = 6   ;
    iIndex[ 12 ] = 3   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 3   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 3   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 3   ; jIndex[ 15 ] = 5   ;
    iIndex[ 16 ] = 3   ; jIndex[ 16 ] = 6   ;
    iIndex[ 17 ] = 4   ; jIndex[ 17 ] = 0   ;
    iIndex[ 18 ] = 4   ; jIndex[ 18 ] = 1   ;
    iIndex[ 19 ] = 4   ; jIndex[ 19 ] = 2   ;
    iIndex[ 20 ] = 4   ; jIndex[ 20 ] = 5   ;
    iIndex[ 21 ] = 4   ; jIndex[ 21 ] = 6   ;
    iIndex[ 22 ] = 5   ; jIndex[ 22 ] = 0   ;
    iIndex[ 23 ] = 5   ; jIndex[ 23 ] = 1   ;
    iIndex[ 24 ] = 5   ; jIndex[ 24 ] = 2   ;
    iIndex[ 25 ] = 5   ; jIndex[ 25 ] = 4   ;
    iIndex[ 26 ] = 5   ; jIndex[ 26 ] = 6   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    real_type t1   = X__[2];
    real_type t2   = X__[1];
    real_type t3   = X__[0];
    real_type t4   = ALIAS_kappa(t3);
    real_type t6   = -t4 * t2 + 1;
    real_type t7   = t6 * t6;
    real_type t8   = 1.0 / t7;
    real_type t9   = t8 * t1;
    real_type t10  = X__[6];
    real_type t12  = ALIAS_kappa_D(t3);
    result__[ 0   ] = t12 * t2 * t10 * t9;
    result__[ 1   ] = t4 * t10 * t9;
    real_type t15  = 1.0 / t6;
    result__[ 2   ] = t10 * t15;
    result__[ 3   ] = t15 * t1;
    result__[ 4   ] = t10;
    result__[ 5   ] = X__[3];
    real_type t16  = result__[5] * t1;
    real_type t17  = t15 * t12;
    real_type t21  = t12 * t2 * t8;
    result__[ 6   ] = -result__[4] * (-t21 * t4 * t16 - t17 * t16);
    real_type t25  = t4 * t4;
    real_type t27  = result__[4] * t8 * t25;
    result__[ 7   ] = t27 * t16;
    result__[ 8   ] = result__[2] * t4 * result__[5];
    result__[ 9   ] = result__[2] * t4 * t1;
    result__[ 10  ] = result__[4];
    real_type t30  = X__[4];
    real_type t31  = t15 * t4;
    result__[ 11  ] = t31 * t16 + t30;
    real_type t33  = t1 * t1;
    real_type t36  = t4 * t33;
    result__[ 12  ] = -result__[10] * (t15 * t12 * t33 + t21 * t36);
    result__[ 13  ] = -result__[10] * t8 * t25 * t33;
    result__[ 14  ] = -2 * result__[9];
    result__[ 15  ] = result__[10];
    real_type t44  = X__[5];
    result__[ 16  ] = -t15 * t36 + t44;
    real_type t46  = t44 * t1;
    result__[ 17  ] = -result__[15] * (-t21 * t4 * t46 - t17 * t46);
    result__[ 18  ] = t27 * t46;
    result__[ 19  ] = result__[2] * t4 * t44;
    result__[ 20  ] = result__[9];
    result__[ 21  ] = t31 * t46 + U__[0];
    real_type t55  = t30 * t1;
    result__[ 22  ] = -result__[15] * (t21 * t4 * t55 + t17 * t55);
    result__[ 23  ] = -t27 * t55;
    result__[ 24  ] = -result__[2] * t4 * t30;
    result__[ 25  ] = -result__[20];
    result__[ 26  ] = -t31 * t55 + U__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",27);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::Drhs_odeDp_numRows() const
  { return 7; }

  integer
  CNOC::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  CNOC::Drhs_odeDp_nnz() const
  { return 0; }

  void
  CNOC::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  CNOC::Drhs_odeDu_numRows() const
  { return 7; }

  integer
  CNOC::Drhs_odeDu_numCols() const
  { return 2; }

  integer
  CNOC::Drhs_odeDu_nnz() const
  { return 2; }

  void
  CNOC::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 4   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 5   ; jIndex[ 1  ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    result__[ 0   ] = X__[6];
    result__[ 1   ] = result__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",2);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  CNOC::A_numRows() const
  { return 7; }

  integer
  CNOC::A_numCols() const
  { return 7; }

  integer
  CNOC::A_nnz() const
  { return 7; }

  void
  CNOC::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 4   ; jIndex[ 4  ] = 4   ;
    iIndex[ 5  ] = 5   ; jIndex[ 5  ] = 5   ;
    iIndex[ 6  ] = 6   ; jIndex[ 6  ] = 6   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CNOC::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    ToolPath2D::SegmentClass const & segment = pToolPath2D->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",7);
    #endif
  }

}

// EOF: CNOC_Methods.cc
