/*-----------------------------------------------------------------------*\
 |  file: CNOC_Methods_Guess.cc                                          |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


using namespace std;

namespace CNOCDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer CNOC::fd_ode_numEqns() const { return 7; }

  void
  CNOC::fd_ode_eval(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[7], V__[7];
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
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t2   = XM__[2];
    real_type t5   = ALIAS_kappa(XM__[0]);
    real_type t8   = 1.0 / (-t5 * XM__[1] + 1);
    real_type t10  = XM__[6];
    result__[ 0   ] = -t10 * t8 * t2 + V__[0];
    real_type t12  = XM__[3];
    result__[ 1   ] = -t10 * t12 + V__[1];
    real_type t16  = XM__[4];
    real_type t18  = t8 * t5;
    result__[ 2   ] = V__[2] + t10 * (-t18 * t12 * t2 - t16);
    real_type t23  = XM__[5];
    real_type t24  = t2 * t2;
    result__[ 3   ] = V__[3] + t10 * (t8 * t5 * t24 - t23);
    result__[ 4   ] = V__[4] + t10 * (-t18 * t23 * t2 - UM__[0]);
    result__[ 5   ] = V__[5] + t10 * (t18 * t16 * t2 - UM__[1]);
    result__[ 6   ] = V__[6];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::Dfd_odeDxxup_numRows() const { return 7; }
  integer CNOC::Dfd_odeDxxup_numCols() const { return 16; }
  integer CNOC::Dfd_odeDxxup_nnz()     const { return 66; }

  void
  CNOC::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 9   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 13  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 8   ;
    iIndex[12] = 1   ; jIndex[12] = 10  ;
    iIndex[13] = 1   ; jIndex[13] = 13  ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 4   ;
    iIndex[19] = 2   ; jIndex[19] = 6   ;
    iIndex[20] = 2   ; jIndex[20] = 7   ;
    iIndex[21] = 2   ; jIndex[21] = 8   ;
    iIndex[22] = 2   ; jIndex[22] = 9   ;
    iIndex[23] = 2   ; jIndex[23] = 10  ;
    iIndex[24] = 2   ; jIndex[24] = 11  ;
    iIndex[25] = 2   ; jIndex[25] = 13  ;
    iIndex[26] = 3   ; jIndex[26] = 0   ;
    iIndex[27] = 3   ; jIndex[27] = 1   ;
    iIndex[28] = 3   ; jIndex[28] = 2   ;
    iIndex[29] = 3   ; jIndex[29] = 3   ;
    iIndex[30] = 3   ; jIndex[30] = 5   ;
    iIndex[31] = 3   ; jIndex[31] = 6   ;
    iIndex[32] = 3   ; jIndex[32] = 7   ;
    iIndex[33] = 3   ; jIndex[33] = 8   ;
    iIndex[34] = 3   ; jIndex[34] = 9   ;
    iIndex[35] = 3   ; jIndex[35] = 10  ;
    iIndex[36] = 3   ; jIndex[36] = 12  ;
    iIndex[37] = 3   ; jIndex[37] = 13  ;
    iIndex[38] = 4   ; jIndex[38] = 0   ;
    iIndex[39] = 4   ; jIndex[39] = 1   ;
    iIndex[40] = 4   ; jIndex[40] = 2   ;
    iIndex[41] = 4   ; jIndex[41] = 4   ;
    iIndex[42] = 4   ; jIndex[42] = 5   ;
    iIndex[43] = 4   ; jIndex[43] = 6   ;
    iIndex[44] = 4   ; jIndex[44] = 7   ;
    iIndex[45] = 4   ; jIndex[45] = 8   ;
    iIndex[46] = 4   ; jIndex[46] = 9   ;
    iIndex[47] = 4   ; jIndex[47] = 11  ;
    iIndex[48] = 4   ; jIndex[48] = 12  ;
    iIndex[49] = 4   ; jIndex[49] = 13  ;
    iIndex[50] = 4   ; jIndex[50] = 14  ;
    iIndex[51] = 5   ; jIndex[51] = 0   ;
    iIndex[52] = 5   ; jIndex[52] = 1   ;
    iIndex[53] = 5   ; jIndex[53] = 2   ;
    iIndex[54] = 5   ; jIndex[54] = 4   ;
    iIndex[55] = 5   ; jIndex[55] = 5   ;
    iIndex[56] = 5   ; jIndex[56] = 6   ;
    iIndex[57] = 5   ; jIndex[57] = 7   ;
    iIndex[58] = 5   ; jIndex[58] = 8   ;
    iIndex[59] = 5   ; jIndex[59] = 9   ;
    iIndex[60] = 5   ; jIndex[60] = 11  ;
    iIndex[61] = 5   ; jIndex[61] = 12  ;
    iIndex[62] = 5   ; jIndex[62] = 13  ;
    iIndex[63] = 5   ; jIndex[63] = 15  ;
    iIndex[64] = 6   ; jIndex[64] = 6   ;
    iIndex[65] = 6   ; jIndex[65] = 13  ;
  }


  void
  CNOC::Dfd_odeDxxup_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[7], V__[7];
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
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = XM__[2];
    real_type t2   = XM__[1];
    real_type t3   = XM__[0];
    real_type t4   = ALIAS_kappa(t3);
    real_type t6   = -t4 * t2 + 1;
    real_type t7   = t6 * t6;
    real_type t8   = 1.0 / t7;
    real_type t9   = t8 * t1;
    real_type t10  = XM__[6];
    real_type t12  = ALIAS_kappa_D(t3);
    real_type t15  = 0.5e0 * t12 * t2 * t10 * t9;
    result__[ 0   ] = -t15 - __INV_DZETA;
    result__[ 1   ] = -0.5e0 * t4 * t10 * t9;
    real_type t19  = 1.0 / t6;
    real_type t20  = t10 * t19;
    result__[ 2   ] = -0.5e0 * t20;
    result__[ 3   ] = -0.5e0 * t19 * t1;
    result__[ 4   ] = -t15 + __INV_DZETA;
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    result__[ 8   ] = -__INV_DZETA;
    result__[ 9   ] = -0.5e0 * t10;
    real_type t25  = XM__[3];
    result__[ 10  ] = -0.5e0 * t25;
    result__[ 11  ] = __INV_DZETA;
    result__[ 12  ] = result__[9];
    result__[ 13  ] = result__[10];
    real_type t27  = t25 * t1;
    real_type t28  = t19 * t12;
    real_type t32  = t12 * t2 * t8;
    result__[ 14  ] = 0.5e0 * t10 * (-t32 * t4 * t27 - t28 * t27);
    real_type t36  = t4 * t4;
    real_type t38  = t10 * t8 * t36;
    result__[ 15  ] = -0.5e0 * t38 * t27;
    real_type t43  = 0.5e0 * t20 * t4 * t25;
    result__[ 16  ] = -t43 + result__[8];
    real_type t45  = t20 * t4 * t1;
    real_type t46  = 0.5e0 * t45;
    result__[ 17  ] = -t46;
    result__[ 18  ] = result__[12];
    real_type t47  = XM__[4];
    real_type t49  = t19 * t4;
    result__[ 19  ] = -0.5e0 * t47 - 0.5e0 * t49 * t27;
    result__[ 20  ] = result__[14];
    result__[ 21  ] = result__[15];
    result__[ 22  ] = -t43 + __INV_DZETA;
    result__[ 23  ] = result__[17];
    result__[ 24  ] = result__[18];
    result__[ 25  ] = result__[19];
    real_type t52  = t1 * t1;
    real_type t55  = t4 * t52;
    result__[ 26  ] = 0.5e0 * t10 * (t19 * t12 * t52 + t32 * t55);
    result__[ 27  ] = 0.5e0 * t10 * t8 * t36 * t52;
    result__[ 28  ] = 0.10e1 * t45;
    result__[ 29  ] = result__[8];
    result__[ 30  ] = result__[24];
    real_type t62  = XM__[5];
    result__[ 31  ] = -0.5e0 * t62 + 0.5e0 * t19 * t55;
    result__[ 32  ] = result__[26];
    result__[ 33  ] = result__[27];
    result__[ 34  ] = result__[28];
    result__[ 35  ] = __INV_DZETA;
    result__[ 36  ] = result__[30];
    result__[ 37  ] = result__[31];
    real_type t66  = t62 * t1;
    result__[ 38  ] = 0.5e0 * t10 * (-t32 * t4 * t66 - t28 * t66);
    result__[ 39  ] = -0.5e0 * t38 * t66;
    result__[ 40  ] = -0.5e0 * t20 * t4 * t62;
    result__[ 41  ] = result__[29];
    result__[ 42  ] = result__[23];
    result__[ 43  ] = -0.5e0 * UM__[0] - 0.5e0 * t49 * t66;
    result__[ 44  ] = result__[38];
    result__[ 45  ] = result__[39];
    result__[ 46  ] = result__[40];
    result__[ 47  ] = __INV_DZETA;
    result__[ 48  ] = result__[42];
    result__[ 49  ] = result__[43];
    result__[ 50  ] = -t10;
    real_type t81  = t47 * t1;
    result__[ 51  ] = 0.5e0 * t10 * (t32 * t4 * t81 + t28 * t81);
    result__[ 52  ] = 0.5e0 * t38 * t81;
    result__[ 53  ] = 0.5e0 * t20 * t4 * t47;
    result__[ 54  ] = t46;
    result__[ 55  ] = result__[41];
    result__[ 56  ] = -0.5e0 * UM__[1] + 0.5e0 * t49 * t81;
    result__[ 57  ] = result__[51];
    result__[ 58  ] = result__[52];
    result__[ 59  ] = result__[53];
    result__[ 60  ] = result__[54];
    result__[ 61  ] = __INV_DZETA;
    result__[ 62  ] = result__[56];
    result__[ 63  ] = result__[50];
    result__[ 64  ] = result__[55];
    result__[ 65  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 66, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CNOC::D2fd_odeD2xxup_numRows() const { return 16; }
  integer CNOC::D2fd_odeD2xxup_numCols() const { return 16; }
  integer CNOC::D2fd_odeD2xxup_nnz()     const { return 164; }

  void
  CNOC::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 9   ;
    iIndex[10] = 0   ; jIndex[10] = 10  ;
    iIndex[11] = 0   ; jIndex[11] = 11  ;
    iIndex[12] = 0   ; jIndex[12] = 12  ;
    iIndex[13] = 0   ; jIndex[13] = 13  ;
    iIndex[14] = 1   ; jIndex[14] = 0   ;
    iIndex[15] = 1   ; jIndex[15] = 1   ;
    iIndex[16] = 1   ; jIndex[16] = 2   ;
    iIndex[17] = 1   ; jIndex[17] = 3   ;
    iIndex[18] = 1   ; jIndex[18] = 4   ;
    iIndex[19] = 1   ; jIndex[19] = 5   ;
    iIndex[20] = 1   ; jIndex[20] = 6   ;
    iIndex[21] = 1   ; jIndex[21] = 7   ;
    iIndex[22] = 1   ; jIndex[22] = 8   ;
    iIndex[23] = 1   ; jIndex[23] = 9   ;
    iIndex[24] = 1   ; jIndex[24] = 10  ;
    iIndex[25] = 1   ; jIndex[25] = 11  ;
    iIndex[26] = 1   ; jIndex[26] = 12  ;
    iIndex[27] = 1   ; jIndex[27] = 13  ;
    iIndex[28] = 2   ; jIndex[28] = 0   ;
    iIndex[29] = 2   ; jIndex[29] = 1   ;
    iIndex[30] = 2   ; jIndex[30] = 2   ;
    iIndex[31] = 2   ; jIndex[31] = 3   ;
    iIndex[32] = 2   ; jIndex[32] = 4   ;
    iIndex[33] = 2   ; jIndex[33] = 5   ;
    iIndex[34] = 2   ; jIndex[34] = 6   ;
    iIndex[35] = 2   ; jIndex[35] = 7   ;
    iIndex[36] = 2   ; jIndex[36] = 8   ;
    iIndex[37] = 2   ; jIndex[37] = 9   ;
    iIndex[38] = 2   ; jIndex[38] = 10  ;
    iIndex[39] = 2   ; jIndex[39] = 11  ;
    iIndex[40] = 2   ; jIndex[40] = 12  ;
    iIndex[41] = 2   ; jIndex[41] = 13  ;
    iIndex[42] = 3   ; jIndex[42] = 0   ;
    iIndex[43] = 3   ; jIndex[43] = 1   ;
    iIndex[44] = 3   ; jIndex[44] = 2   ;
    iIndex[45] = 3   ; jIndex[45] = 6   ;
    iIndex[46] = 3   ; jIndex[46] = 7   ;
    iIndex[47] = 3   ; jIndex[47] = 8   ;
    iIndex[48] = 3   ; jIndex[48] = 9   ;
    iIndex[49] = 3   ; jIndex[49] = 13  ;
    iIndex[50] = 4   ; jIndex[50] = 0   ;
    iIndex[51] = 4   ; jIndex[51] = 1   ;
    iIndex[52] = 4   ; jIndex[52] = 2   ;
    iIndex[53] = 4   ; jIndex[53] = 6   ;
    iIndex[54] = 4   ; jIndex[54] = 7   ;
    iIndex[55] = 4   ; jIndex[55] = 8   ;
    iIndex[56] = 4   ; jIndex[56] = 9   ;
    iIndex[57] = 4   ; jIndex[57] = 13  ;
    iIndex[58] = 5   ; jIndex[58] = 0   ;
    iIndex[59] = 5   ; jIndex[59] = 1   ;
    iIndex[60] = 5   ; jIndex[60] = 2   ;
    iIndex[61] = 5   ; jIndex[61] = 6   ;
    iIndex[62] = 5   ; jIndex[62] = 7   ;
    iIndex[63] = 5   ; jIndex[63] = 8   ;
    iIndex[64] = 5   ; jIndex[64] = 9   ;
    iIndex[65] = 5   ; jIndex[65] = 13  ;
    iIndex[66] = 6   ; jIndex[66] = 0   ;
    iIndex[67] = 6   ; jIndex[67] = 1   ;
    iIndex[68] = 6   ; jIndex[68] = 2   ;
    iIndex[69] = 6   ; jIndex[69] = 3   ;
    iIndex[70] = 6   ; jIndex[70] = 4   ;
    iIndex[71] = 6   ; jIndex[71] = 5   ;
    iIndex[72] = 6   ; jIndex[72] = 7   ;
    iIndex[73] = 6   ; jIndex[73] = 8   ;
    iIndex[74] = 6   ; jIndex[74] = 9   ;
    iIndex[75] = 6   ; jIndex[75] = 10  ;
    iIndex[76] = 6   ; jIndex[76] = 11  ;
    iIndex[77] = 6   ; jIndex[77] = 12  ;
    iIndex[78] = 6   ; jIndex[78] = 14  ;
    iIndex[79] = 6   ; jIndex[79] = 15  ;
    iIndex[80] = 7   ; jIndex[80] = 0   ;
    iIndex[81] = 7   ; jIndex[81] = 1   ;
    iIndex[82] = 7   ; jIndex[82] = 2   ;
    iIndex[83] = 7   ; jIndex[83] = 3   ;
    iIndex[84] = 7   ; jIndex[84] = 4   ;
    iIndex[85] = 7   ; jIndex[85] = 5   ;
    iIndex[86] = 7   ; jIndex[86] = 6   ;
    iIndex[87] = 7   ; jIndex[87] = 7   ;
    iIndex[88] = 7   ; jIndex[88] = 8   ;
    iIndex[89] = 7   ; jIndex[89] = 9   ;
    iIndex[90] = 7   ; jIndex[90] = 10  ;
    iIndex[91] = 7   ; jIndex[91] = 11  ;
    iIndex[92] = 7   ; jIndex[92] = 12  ;
    iIndex[93] = 7   ; jIndex[93] = 13  ;
    iIndex[94] = 8   ; jIndex[94] = 0   ;
    iIndex[95] = 8   ; jIndex[95] = 1   ;
    iIndex[96] = 8   ; jIndex[96] = 2   ;
    iIndex[97] = 8   ; jIndex[97] = 3   ;
    iIndex[98] = 8   ; jIndex[98] = 4   ;
    iIndex[99] = 8   ; jIndex[99] = 5   ;
    iIndex[100] = 8   ; jIndex[100] = 6   ;
    iIndex[101] = 8   ; jIndex[101] = 7   ;
    iIndex[102] = 8   ; jIndex[102] = 8   ;
    iIndex[103] = 8   ; jIndex[103] = 9   ;
    iIndex[104] = 8   ; jIndex[104] = 10  ;
    iIndex[105] = 8   ; jIndex[105] = 11  ;
    iIndex[106] = 8   ; jIndex[106] = 12  ;
    iIndex[107] = 8   ; jIndex[107] = 13  ;
    iIndex[108] = 9   ; jIndex[108] = 0   ;
    iIndex[109] = 9   ; jIndex[109] = 1   ;
    iIndex[110] = 9   ; jIndex[110] = 2   ;
    iIndex[111] = 9   ; jIndex[111] = 3   ;
    iIndex[112] = 9   ; jIndex[112] = 4   ;
    iIndex[113] = 9   ; jIndex[113] = 5   ;
    iIndex[114] = 9   ; jIndex[114] = 6   ;
    iIndex[115] = 9   ; jIndex[115] = 7   ;
    iIndex[116] = 9   ; jIndex[116] = 8   ;
    iIndex[117] = 9   ; jIndex[117] = 9   ;
    iIndex[118] = 9   ; jIndex[118] = 10  ;
    iIndex[119] = 9   ; jIndex[119] = 11  ;
    iIndex[120] = 9   ; jIndex[120] = 12  ;
    iIndex[121] = 9   ; jIndex[121] = 13  ;
    iIndex[122] = 10  ; jIndex[122] = 0   ;
    iIndex[123] = 10  ; jIndex[123] = 1   ;
    iIndex[124] = 10  ; jIndex[124] = 2   ;
    iIndex[125] = 10  ; jIndex[125] = 6   ;
    iIndex[126] = 10  ; jIndex[126] = 7   ;
    iIndex[127] = 10  ; jIndex[127] = 8   ;
    iIndex[128] = 10  ; jIndex[128] = 9   ;
    iIndex[129] = 10  ; jIndex[129] = 13  ;
    iIndex[130] = 11  ; jIndex[130] = 0   ;
    iIndex[131] = 11  ; jIndex[131] = 1   ;
    iIndex[132] = 11  ; jIndex[132] = 2   ;
    iIndex[133] = 11  ; jIndex[133] = 6   ;
    iIndex[134] = 11  ; jIndex[134] = 7   ;
    iIndex[135] = 11  ; jIndex[135] = 8   ;
    iIndex[136] = 11  ; jIndex[136] = 9   ;
    iIndex[137] = 11  ; jIndex[137] = 13  ;
    iIndex[138] = 12  ; jIndex[138] = 0   ;
    iIndex[139] = 12  ; jIndex[139] = 1   ;
    iIndex[140] = 12  ; jIndex[140] = 2   ;
    iIndex[141] = 12  ; jIndex[141] = 6   ;
    iIndex[142] = 12  ; jIndex[142] = 7   ;
    iIndex[143] = 12  ; jIndex[143] = 8   ;
    iIndex[144] = 12  ; jIndex[144] = 9   ;
    iIndex[145] = 12  ; jIndex[145] = 13  ;
    iIndex[146] = 13  ; jIndex[146] = 0   ;
    iIndex[147] = 13  ; jIndex[147] = 1   ;
    iIndex[148] = 13  ; jIndex[148] = 2   ;
    iIndex[149] = 13  ; jIndex[149] = 3   ;
    iIndex[150] = 13  ; jIndex[150] = 4   ;
    iIndex[151] = 13  ; jIndex[151] = 5   ;
    iIndex[152] = 13  ; jIndex[152] = 7   ;
    iIndex[153] = 13  ; jIndex[153] = 8   ;
    iIndex[154] = 13  ; jIndex[154] = 9   ;
    iIndex[155] = 13  ; jIndex[155] = 10  ;
    iIndex[156] = 13  ; jIndex[156] = 11  ;
    iIndex[157] = 13  ; jIndex[157] = 12  ;
    iIndex[158] = 13  ; jIndex[158] = 14  ;
    iIndex[159] = 13  ; jIndex[159] = 15  ;
    iIndex[160] = 14  ; jIndex[160] = 6   ;
    iIndex[161] = 14  ; jIndex[161] = 13  ;
    iIndex[162] = 15  ; jIndex[162] = 6   ;
    iIndex[163] = 15  ; jIndex[163] = 13  ;
  }


  void
  CNOC::D2fd_odeD2xxup_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[7], V__[7];
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
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    ToolPath2D::SegmentClass const & segment = pToolPath2D->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t5   = XR__[iX_vs] / 2 + XL__[iX_vs] / 2;
    real_type t6   = t5 * t1;
    real_type t10  = XR__[iX_n] / 2 + XL__[iX_n] / 2;
    real_type t14  = XR__[iX_s] / 2 + XL__[iX_s] / 2;
    real_type t15  = ALIAS_kappa(t14);
    real_type t17  = -t15 * t10 + 1;
    real_type t18  = t17 * t17;
    real_type t20  = 1.0 / t18 / t17;
    real_type t21  = t20 * t6;
    real_type t25  = XR__[iX_coV] / 2 + XL__[iX_coV] / 2;
    real_type t26  = t10 * t10;
    real_type t28  = ALIAS_kappa_D(t14);
    real_type t29  = t28 * t28;
    real_type t33  = 1.0 / t18;
    real_type t35  = t10 * t25;
    real_type t36  = ALIAS_kappa_DD(t14);
    real_type t40  = LM__[2];
    real_type t44  = XR__[iX_vn] / 2 + XL__[iX_vn] / 2;
    real_type t45  = t44 * t5;
    real_type t46  = 1.0 / t17;
    real_type t47  = t46 * t36;
    real_type t51  = t10 * t33 * t29;
    real_type t54  = t15 * t45;
    real_type t56  = t29 * t26 * t20;
    real_type t59  = t10 * t33;
    real_type t60  = t36 * t59;
    real_type t66  = LM__[3];
    real_type t67  = t5 * t5;
    real_type t74  = t15 * t67;
    real_type t82  = LM__[4];
    real_type t86  = XR__[iX_an] / 2 + XL__[iX_an] / 2;
    real_type t87  = t86 * t5;
    real_type t92  = t15 * t87;
    real_type t100 = LM__[5];
    real_type t104 = XR__[iX_as] / 2 + XL__[iX_as] / 2;
    real_type t105 = t104 * t5;
    real_type t110 = t15 * t105;
    result__[ 0   ] = -t29 * t26 * t25 * t21 / 2 - t36 * t35 * t33 * t6 / 4 + t25 * (-t47 * t45 / 4 - t51 * t45 / 2 - t56 * t54 / 2 - t60 * t54 / 4) * t40 + t25 * (t46 * t36 * t67 / 4 + t59 * t29 * t67 / 2 + t56 * t74 / 2 + t60 * t74 / 4) * t66 + t25 * (-t47 * t87 / 4 - t51 * t87 / 2 - t56 * t92 / 2 - t60 * t92 / 4) * t82 + t25 * (t47 * t105 / 4 + t51 * t105 / 2 + t56 * t110 / 2 + t60 * t110 / 4) * t100;
    real_type t121 = t15 * t28 * t35 * t21 / 2;
    real_type t122 = t25 * t33;
    real_type t123 = t28 * t122;
    real_type t125 = t123 * t6 / 4;
    real_type t127 = t15 * t33 * t28;
    real_type t129 = t15 * t15;
    real_type t132 = t28 * t10 * t20;
    real_type t138 = t28 * t67;
    real_type t139 = t15 * t33;
    result__[ 1   ] = -t121 - t125 + t25 * (-t132 * t129 * t45 / 2 - t127 * t45 / 2) * t40 + t25 * (t132 * t129 * t67 / 2 + t139 * t138 / 2) * t66 + t25 * (-t132 * t129 * t87 / 2 - t127 * t87 / 2) * t82 + t25 * (t132 * t129 * t105 / 2 + t127 * t105 / 2) * t100;
    real_type t161 = t33 * t1;
    real_type t164 = t28 * t35 * t161 / 4;
    real_type t168 = t28 * t59;
    real_type t178 = t168 * t15 * t5 + t46 * t28 * t5;
    result__[ 2   ] = -t164 + t25 * (-t168 * t15 * t44 / 4 - t46 * t28 * t44 / 4) * t40 + t25 * t178 * t66 / 2 + t25 * (-t168 * t15 * t86 / 4 - t46 * t28 * t86 / 4) * t82 + t25 * (t168 * t15 * t104 / 4 + t46 * t28 * t104 / 4) * t100;
    real_type t199 = -t178 / 4;
    result__[ 3   ] = t25 * t199 * t40;
    result__[ 4   ] = -t25 * t199 * t100;
    result__[ 5   ] = t25 * t199 * t82;
    real_type t205 = t168 * t6 / 4;
    real_type t206 = t46 * t28;
    real_type t209 = -t168 * t54 - t206 * t45;
    real_type t215 = t46 * t138 + t168 * t74;
    real_type t221 = -t168 * t92 - t206 * t87;
    real_type t227 = t206 * t105 + t168 * t110;
    result__[ 6   ] = -t205 + t209 * t40 / 4 + t215 * t66 / 4 + t221 * t82 / 4 + t227 * t100 / 4;
    result__[ 7   ] = result__[0];
    result__[ 8   ] = result__[1];
    result__[ 9   ] = result__[2];
    result__[ 10  ] = result__[3];
    result__[ 11  ] = result__[4];
    result__[ 12  ] = result__[5];
    result__[ 13  ] = result__[6];
    result__[ 14  ] = result__[8];
    real_type t231 = t25 * t20;
    real_type t234 = t5 * t40;
    real_type t235 = t44 * t234;
    real_type t238 = t25 * t20 * t129 * t15;
    real_type t240 = t67 * t66;
    real_type t242 = t5 * t82;
    real_type t243 = t86 * t242;
    real_type t245 = t5 * t100;
    real_type t246 = t104 * t245;
    result__[ 15  ] = -t129 * t231 * t6 / 2 - t238 * t235 / 2 + t238 * t240 / 2 - t238 * t243 / 2 + t238 * t246 / 2;
    real_type t252 = t44 * t40;
    real_type t253 = t33 * t129;
    real_type t254 = t25 * t253;
    real_type t257 = t5 * t66;
    real_type t260 = t86 * t82;
    real_type t263 = t104 * t100;
    result__[ 16  ] = -t15 * t25 * t161 / 4 - t254 * t252 / 4 + t254 * t257 / 2 - t254 * t260 / 4 + t254 * t263 / 4;
    result__[ 17  ] = -t254 * t234 / 4;
    result__[ 18  ] = t254 * t245 / 4;
    result__[ 19  ] = -t254 * t242 / 4;
    real_type t272 = t129 * t44;
    real_type t276 = t129 * t86;
    real_type t279 = t129 * t104;
    result__[ 20  ] = -t33 * t272 * t234 / 4 - t33 * t276 * t242 / 4 + t33 * t279 * t245 / 4 - t139 * t6 / 4 + t253 * t240 / 4;
    real_type t284 = t28 * t25 * t139;
    real_type t288 = t28 * t10;
    real_type t289 = t288 * t231;
    result__[ 21  ] = -t121 - t125 - t284 * t235 / 2 - t289 * t272 * t234 / 2 + t123 * t15 * t240 / 2 + t289 * t129 * t240 / 2 - t284 * t243 / 2 - t289 * t276 * t242 / 2 + t284 * t246 / 2 + t289 * t279 * t245 / 2;
    result__[ 22  ] = result__[15];
    result__[ 23  ] = result__[16];
    result__[ 24  ] = result__[17];
    result__[ 25  ] = result__[18];
    result__[ 26  ] = result__[19];
    result__[ 27  ] = result__[20];
    result__[ 28  ] = result__[9];
    result__[ 29  ] = result__[23];
    real_type t309 = t25 * t46;
    result__[ 30  ] = t309 * t15 * t66 / 2;
    result__[ 31  ] = -t309 * t15 * t40 / 4;
    result__[ 32  ] = t309 * t15 * t100 / 4;
    result__[ 33  ] = -t309 * t15 * t82 / 4;
    real_type t321 = t46 * t15;
    result__[ 34  ] = -t46 * t1 / 4 - t321 * t252 / 4 + t321 * t257 / 2 - t321 * t260 / 4 + t321 * t263 / 4;
    real_type t330 = t25 * t206;
    real_type t334 = t288 * t122;
    result__[ 35  ] = -t164 - t330 * t252 / 4 - t334 * t15 * t252 / 4 + t330 * t257 / 2 + t334 * t15 * t257 / 2 - t330 * t260 / 4 - t334 * t15 * t260 / 4 + t330 * t263 / 4 + t334 * t15 * t263 / 4;
    result__[ 36  ] = result__[29];
    result__[ 37  ] = result__[30];
    result__[ 38  ] = result__[31];
    result__[ 39  ] = result__[32];
    result__[ 40  ] = result__[33];
    result__[ 41  ] = result__[34];
    result__[ 42  ] = result__[10];
    result__[ 43  ] = result__[24];
    result__[ 44  ] = result__[38];
    result__[ 45  ] = -t321 * t234 / 4 - LM__[1] / 4;
    result__[ 46  ] = -t334 * t15 * t234 / 4 - t330 * t234 / 4;
    result__[ 47  ] = result__[43];
    result__[ 48  ] = result__[44];
    result__[ 49  ] = result__[45];
    result__[ 50  ] = result__[11];
    result__[ 51  ] = result__[25];
    result__[ 52  ] = result__[39];
    result__[ 53  ] = t321 * t245 / 4 - t40 / 4;
    result__[ 54  ] = t334 * t15 * t245 / 4 + t330 * t245 / 4;
    result__[ 55  ] = result__[51];
    result__[ 56  ] = result__[52];
    result__[ 57  ] = result__[53];
    result__[ 58  ] = result__[12];
    result__[ 59  ] = result__[26];
    result__[ 60  ] = result__[40];
    result__[ 61  ] = -t321 * t242 / 4 - t66 / 4;
    result__[ 62  ] = -t334 * t15 * t242 / 4 - t330 * t242 / 4;
    result__[ 63  ] = result__[59];
    result__[ 64  ] = result__[60];
    result__[ 65  ] = result__[61];
    result__[ 66  ] = result__[13];
    result__[ 67  ] = result__[27];
    result__[ 68  ] = result__[41];
    result__[ 69  ] = result__[49];
    result__[ 70  ] = result__[57];
    result__[ 71  ] = result__[65];
    result__[ 72  ] = -t205 + t209 * t40 / 4 + t215 * t66 / 4 + t221 * t82 / 4 + t227 * t100 / 4;
    result__[ 73  ] = result__[67];
    result__[ 74  ] = result__[68];
    result__[ 75  ] = result__[69];
    result__[ 76  ] = result__[70];
    result__[ 77  ] = result__[71];
    result__[ 78  ] = -t82 / 2;
    result__[ 79  ] = -t100 / 2;
    result__[ 80  ] = result__[7];
    result__[ 81  ] = result__[21];
    result__[ 82  ] = result__[35];
    result__[ 83  ] = result__[46];
    result__[ 84  ] = result__[54];
    result__[ 85  ] = result__[62];
    result__[ 86  ] = result__[72];
    result__[ 87  ] = result__[80];
    result__[ 88  ] = result__[14];
    result__[ 89  ] = result__[28];
    result__[ 90  ] = result__[42];
    result__[ 91  ] = result__[50];
    result__[ 92  ] = result__[58];
    result__[ 93  ] = result__[66];
    result__[ 94  ] = result__[88];
    result__[ 95  ] = result__[22];
    result__[ 96  ] = result__[36];
    result__[ 97  ] = result__[47];
    result__[ 98  ] = result__[55];
    result__[ 99  ] = result__[63];
    result__[ 100 ] = result__[73];
    result__[ 101 ] = result__[94];
    result__[ 102 ] = result__[95];
    result__[ 103 ] = result__[96];
    result__[ 104 ] = result__[97];
    result__[ 105 ] = result__[98];
    result__[ 106 ] = result__[99];
    result__[ 107 ] = result__[100];
    result__[ 108 ] = result__[89];
    result__[ 109 ] = result__[103];
    result__[ 110 ] = result__[37];
    result__[ 111 ] = result__[48];
    result__[ 112 ] = result__[56];
    result__[ 113 ] = result__[64];
    result__[ 114 ] = result__[74];
    result__[ 115 ] = result__[108];
    result__[ 116 ] = result__[109];
    result__[ 117 ] = result__[110];
    result__[ 118 ] = result__[111];
    result__[ 119 ] = result__[112];
    result__[ 120 ] = result__[113];
    result__[ 121 ] = result__[114];
    result__[ 122 ] = result__[90];
    result__[ 123 ] = result__[104];
    result__[ 124 ] = result__[118];
    result__[ 125 ] = result__[75];
    result__[ 126 ] = result__[122];
    result__[ 127 ] = result__[123];
    result__[ 128 ] = result__[124];
    result__[ 129 ] = result__[125];
    result__[ 130 ] = result__[91];
    result__[ 131 ] = result__[105];
    result__[ 132 ] = result__[119];
    result__[ 133 ] = result__[76];
    result__[ 134 ] = result__[130];
    result__[ 135 ] = result__[131];
    result__[ 136 ] = result__[132];
    result__[ 137 ] = result__[133];
    result__[ 138 ] = result__[92];
    result__[ 139 ] = result__[106];
    result__[ 140 ] = result__[120];
    result__[ 141 ] = result__[77];
    result__[ 142 ] = result__[138];
    result__[ 143 ] = result__[139];
    result__[ 144 ] = result__[140];
    result__[ 145 ] = result__[141];
    result__[ 146 ] = result__[93];
    result__[ 147 ] = result__[107];
    result__[ 148 ] = result__[121];
    result__[ 149 ] = result__[129];
    result__[ 150 ] = result__[137];
    result__[ 151 ] = result__[145];
    result__[ 152 ] = result__[146];
    result__[ 153 ] = result__[147];
    result__[ 154 ] = result__[148];
    result__[ 155 ] = result__[149];
    result__[ 156 ] = result__[150];
    result__[ 157 ] = result__[151];
    result__[ 158 ] = result__[78];
    result__[ 159 ] = result__[79];
    result__[ 160 ] = result__[158];
    result__[ 161 ] = result__[160];
    result__[ 162 ] = result__[159];
    result__[ 163 ] = result__[162];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 164, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: CNOC_Methods_Guess.cc
