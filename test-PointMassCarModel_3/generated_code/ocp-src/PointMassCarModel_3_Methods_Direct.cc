/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_Guess.cc                           |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "PointMassCarModel_3.hh"
#include "PointMassCarModel_3_Pars.hh"

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
#define ALIAS_yR_R(__t1) segmentRight.iso_right_y( __t1)
#define ALIAS_yR_L(__t1) segmentLeft.iso_right_y( __t1)
#define ALIAS_yR(__t1) segment.iso_right_y( __t1)
#define ALIAS_xR_R(__t1) segmentRight.iso_right_x( __t1)
#define ALIAS_xR_L(__t1) segmentLeft.iso_right_x( __t1)
#define ALIAS_xR(__t1) segment.iso_right_x( __t1)
#define ALIAS_yL_R(__t1) segmentRight.iso_left_y( __t1)
#define ALIAS_yL_L(__t1) segmentLeft.iso_left_y( __t1)
#define ALIAS_yL(__t1) segment.iso_left_y( __t1)
#define ALIAS_xL_R(__t1) segmentRight.iso_left_x( __t1)
#define ALIAS_xL_L(__t1) segmentLeft.iso_left_x( __t1)
#define ALIAS_xL(__t1) segment.iso_left_x( __t1)
#define ALIAS_theta_R_DD(__t1) segmentRight.iso_angle_DD( __t1)
#define ALIAS_theta_R_D(__t1) segmentRight.iso_angle_D( __t1)
#define ALIAS_theta_R(__t1) segmentRight.iso_angle( __t1)
#define ALIAS_theta_L_DD(__t1) segmentLeft.iso_angle_DD( __t1)
#define ALIAS_theta_L_D(__t1) segmentLeft.iso_angle_D( __t1)
#define ALIAS_theta_L(__t1) segmentLeft.iso_angle( __t1)
#define ALIAS_theta_DD(__t1) segment.iso_angle_DD( __t1)
#define ALIAS_theta_D(__t1) segment.iso_angle_D( __t1)
#define ALIAS_theta(__t1) segment.iso_angle( __t1)
#define ALIAS_yLane_R_DD(__t1) segmentRight.iso_y_DD( __t1)
#define ALIAS_yLane_R_D(__t1) segmentRight.iso_y_D( __t1)
#define ALIAS_yLane_R(__t1) segmentRight.iso_y( __t1)
#define ALIAS_yLane_L_DD(__t1) segmentLeft.iso_y_DD( __t1)
#define ALIAS_yLane_L_D(__t1) segmentLeft.iso_y_D( __t1)
#define ALIAS_yLane_L(__t1) segmentLeft.iso_y( __t1)
#define ALIAS_yLane_DD(__t1) segment.iso_y_DD( __t1)
#define ALIAS_yLane_D(__t1) segment.iso_y_D( __t1)
#define ALIAS_yLane(__t1) segment.iso_y( __t1)
#define ALIAS_xLane_R_DD(__t1) segmentRight.iso_x_DD( __t1)
#define ALIAS_xLane_R_D(__t1) segmentRight.iso_x_D( __t1)
#define ALIAS_xLane_R(__t1) segmentRight.iso_x( __t1)
#define ALIAS_xLane_L_DD(__t1) segmentLeft.iso_x_DD( __t1)
#define ALIAS_xLane_L_D(__t1) segmentLeft.iso_x_D( __t1)
#define ALIAS_xLane_L(__t1) segmentLeft.iso_x( __t1)
#define ALIAS_xLane_DD(__t1) segment.iso_x_DD( __t1)
#define ALIAS_xLane_D(__t1) segment.iso_x_D( __t1)
#define ALIAS_xLane(__t1) segment.iso_x( __t1)
#define ALIAS_rightWidth_R_DD(__t1) segmentRight.right_width_DD( __t1)
#define ALIAS_rightWidth_R_D(__t1) segmentRight.right_width_D( __t1)
#define ALIAS_rightWidth_R(__t1) segmentRight.right_width( __t1)
#define ALIAS_rightWidth_L_DD(__t1) segmentLeft.right_width_DD( __t1)
#define ALIAS_rightWidth_L_D(__t1) segmentLeft.right_width_D( __t1)
#define ALIAS_rightWidth_L(__t1) segmentLeft.right_width( __t1)
#define ALIAS_rightWidth_DD(__t1) segment.right_width_DD( __t1)
#define ALIAS_rightWidth_D(__t1) segment.right_width_D( __t1)
#define ALIAS_rightWidth(__t1) segment.right_width( __t1)
#define ALIAS_leftWidth_R_DD(__t1) segmentRight.left_width_DD( __t1)
#define ALIAS_leftWidth_R_D(__t1) segmentRight.left_width_D( __t1)
#define ALIAS_leftWidth_R(__t1) segmentRight.left_width( __t1)
#define ALIAS_leftWidth_L_DD(__t1) segmentLeft.left_width_DD( __t1)
#define ALIAS_leftWidth_L_D(__t1) segmentLeft.left_width_D( __t1)
#define ALIAS_leftWidth_L(__t1) segmentLeft.left_width( __t1)
#define ALIAS_leftWidth_DD(__t1) segment.left_width_DD( __t1)
#define ALIAS_leftWidth_D(__t1) segment.left_width_D( __t1)
#define ALIAS_leftWidth(__t1) segment.left_width( __t1)
#define ALIAS_yV_R(__t1, __t2) segmentRight.iso_y( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.iso_y( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.iso_y( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.iso_x( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.iso_x( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.iso_x( __t1, __t2)
#define ALIAS_Kappa_R_DD(__t1) segmentRight.iso_curvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.iso_curvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.iso_curvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.iso_curvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.iso_curvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.iso_curvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.iso_curvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.iso_curvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.iso_curvature( __t1)
#define ALIAS_ssSegmentMax_R(___dummy___) segmentRight.ss_segment_max()
#define ALIAS_ssSegmentMax_L(___dummy___) segmentLeft.ss_segment_max()
#define ALIAS_ssSegmentMax(___dummy___) segment.ss_segment_max()
#define ALIAS_ssSegmentMin_R(___dummy___) segmentRight.ss_segment_min()
#define ALIAS_ssSegmentMin_L(___dummy___) segmentLeft.ss_segment_min()
#define ALIAS_ssSegmentMin(___dummy___) segment.ss_segment_min()
#define ALIAS_L_R(___dummy___) segmentRight.length()
#define ALIAS_L_L(___dummy___) segmentLeft.length()
#define ALIAS_L(___dummy___) segment.length()
#define ALIAS_PowerLimit_DD(__t1) PowerLimit.DD( __t1)
#define ALIAS_PowerLimit_D(__t1) PowerLimit.D( __t1)
#define ALIAS_RoadRightBorder_DD(__t1) RoadRightBorder.DD( __t1)
#define ALIAS_RoadRightBorder_D(__t1) RoadRightBorder.D( __t1)
#define ALIAS_RoadLeftBorder_DD(__t1) RoadLeftBorder.DD( __t1)
#define ALIAS_RoadLeftBorder_D(__t1) RoadLeftBorder.D( __t1)
#define ALIAS_AdherenceEllipse_DD(__t1) AdherenceEllipse.DD( __t1)
#define ALIAS_AdherenceEllipse_D(__t1) AdherenceEllipse.D( __t1)
#define ALIAS_v__OmegaControl_D_3(__t1, __t2, __t3) v__OmegaControl.D_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_2(__t1, __t2, __t3) v__OmegaControl.D_2( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1(__t1, __t2, __t3) v__OmegaControl.D_1( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_3_3(__t1, __t2, __t3) v__OmegaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_2_3(__t1, __t2, __t3) v__OmegaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_2_2(__t1, __t2, __t3) v__OmegaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1_3(__t1, __t2, __t3) v__OmegaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1_2(__t1, __t2, __t3) v__OmegaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_v__OmegaControl_D_1_1(__t1, __t2, __t3) v__OmegaControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_3(__t1, __t2, __t3) v__fxControl.D_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_2(__t1, __t2, __t3) v__fxControl.D_2( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1(__t1, __t2, __t3) v__fxControl.D_1( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_3_3(__t1, __t2, __t3) v__fxControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_2_3(__t1, __t2, __t3) v__fxControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_2_2(__t1, __t2, __t3) v__fxControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1_3(__t1, __t2, __t3) v__fxControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1_2(__t1, __t2, __t3) v__fxControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_v__fxControl_D_1_1(__t1, __t2, __t3) v__fxControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace PointMassCarModel_3Define {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer PointMassCarModel_3::fd_ode_numEqns() const { return 7; }

  void
  PointMassCarModel_3::fd_ode_eval(
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
    real_type QM__[4], XM__[7], V__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    QM__[1] = (QL__[1]+QR__[1])/2;
    QM__[2] = (QL__[2]+QR__[2])/2;
    QM__[3] = (QL__[3]+QR__[3])/2;
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
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = XM__[3];
    real_type t3   = XM__[2];
    real_type t6   = ALIAS_Kappa(XM__[0]);
    real_type t7   = zeta__dot(t2, t3, XM__[1], t6);
    real_type t9   = XM__[6] * XM__[6];
    result__[ 0   ] = -t9 * t7 + V__[0];
    real_type t12  = sin(t3);
    result__[ 1   ] = -t9 * t12 * t2 + V__[1];
    result__[ 2   ] = V__[2] - (-t6 * t7 + XM__[4]) * t9;
    real_type t21  = t2 * t2;
    result__[ 3   ] = V__[3] - (-ModelPars[iM_kD] * t21 + XM__[5]) * t9;
    result__[ 4   ] = -ModelPars[iM_v__Omega__max] * t9 * UM__[1] + V__[4];
    result__[ 5   ] = -ModelPars[iM_v__fx__max] * t9 * UM__[0] + V__[5];
    result__[ 6   ] = V__[6];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::Dfd_odeDxxup_numRows() const { return 7; }
  integer PointMassCarModel_3::Dfd_odeDxxup_numCols() const { return 16; }
  integer PointMassCarModel_3::Dfd_odeDxxup_nnz()     const { return 48; }

  void
  PointMassCarModel_3::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 10  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 13  ;
    iIndex[10] = 1   ; jIndex[10] = 1   ;
    iIndex[11] = 1   ; jIndex[11] = 2   ;
    iIndex[12] = 1   ; jIndex[12] = 3   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 1   ; jIndex[14] = 8   ;
    iIndex[15] = 1   ; jIndex[15] = 9   ;
    iIndex[16] = 1   ; jIndex[16] = 10  ;
    iIndex[17] = 1   ; jIndex[17] = 13  ;
    iIndex[18] = 2   ; jIndex[18] = 0   ;
    iIndex[19] = 2   ; jIndex[19] = 1   ;
    iIndex[20] = 2   ; jIndex[20] = 2   ;
    iIndex[21] = 2   ; jIndex[21] = 3   ;
    iIndex[22] = 2   ; jIndex[22] = 4   ;
    iIndex[23] = 2   ; jIndex[23] = 6   ;
    iIndex[24] = 2   ; jIndex[24] = 7   ;
    iIndex[25] = 2   ; jIndex[25] = 8   ;
    iIndex[26] = 2   ; jIndex[26] = 9   ;
    iIndex[27] = 2   ; jIndex[27] = 10  ;
    iIndex[28] = 2   ; jIndex[28] = 11  ;
    iIndex[29] = 2   ; jIndex[29] = 13  ;
    iIndex[30] = 3   ; jIndex[30] = 3   ;
    iIndex[31] = 3   ; jIndex[31] = 5   ;
    iIndex[32] = 3   ; jIndex[32] = 6   ;
    iIndex[33] = 3   ; jIndex[33] = 10  ;
    iIndex[34] = 3   ; jIndex[34] = 12  ;
    iIndex[35] = 3   ; jIndex[35] = 13  ;
    iIndex[36] = 4   ; jIndex[36] = 4   ;
    iIndex[37] = 4   ; jIndex[37] = 6   ;
    iIndex[38] = 4   ; jIndex[38] = 11  ;
    iIndex[39] = 4   ; jIndex[39] = 13  ;
    iIndex[40] = 4   ; jIndex[40] = 15  ;
    iIndex[41] = 5   ; jIndex[41] = 5   ;
    iIndex[42] = 5   ; jIndex[42] = 6   ;
    iIndex[43] = 5   ; jIndex[43] = 12  ;
    iIndex[44] = 5   ; jIndex[44] = 13  ;
    iIndex[45] = 5   ; jIndex[45] = 14  ;
    iIndex[46] = 6   ; jIndex[46] = 6   ;
    iIndex[47] = 6   ; jIndex[47] = 13  ;
  }


  void
  PointMassCarModel_3::Dfd_odeDxxup_sparse(
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
    real_type QM__[4], XM__[7], V__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    QM__[1] = (QL__[1]+QR__[1])/2;
    QM__[2] = (QL__[2]+QR__[2])/2;
    QM__[3] = (QL__[3]+QR__[3])/2;
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
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = XM__[3];
    real_type t2   = XM__[2];
    real_type t3   = XM__[1];
    real_type t4   = XM__[0];
    real_type t5   = ALIAS_Kappa(t4);
    real_type t6   = zeta__dot_D_4(t1, t2, t3, t5);
    real_type t7   = ALIAS_Kappa_D(t4);
    real_type t8   = t7 * t6;
    real_type t9   = XM__[6];
    real_type t10  = t9 * t9;
    real_type t12  = 0.5e0 * t10 * t8;
    result__[ 0   ] = -t12 - __INV_DZETA;
    real_type t13  = zeta__dot_D_3(t1, t2, t3, t5);
    real_type t14  = t10 * t13;
    result__[ 1   ] = -0.5e0 * t14;
    real_type t16  = zeta__dot_D_2(t1, t2, t3, t5);
    real_type t17  = t10 * t16;
    result__[ 2   ] = -0.5e0 * t17;
    real_type t19  = zeta__dot_D_1(t1, t2, t3, t5);
    real_type t20  = t10 * t19;
    result__[ 3   ] = -0.5e0 * t20;
    real_type t22  = zeta__dot(t1, t2, t3, t5);
    result__[ 4   ] = -0.10e1 * t9 * t22;
    result__[ 5   ] = -t12 + __INV_DZETA;
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[3];
    result__[ 9   ] = result__[4];
    result__[ 10  ] = -__INV_DZETA;
    real_type t25  = cos(t2);
    result__[ 11  ] = -0.5e0 * t10 * t25 * t1;
    real_type t29  = sin(t2);
    result__[ 12  ] = -0.5e0 * t10 * t29;
    result__[ 13  ] = -0.10e1 * t9 * t29 * t1;
    result__[ 14  ] = __INV_DZETA;
    result__[ 15  ] = result__[11];
    result__[ 16  ] = result__[12];
    result__[ 17  ] = result__[13];
    result__[ 18  ] = -0.5e0 * (-t7 * t22 - t5 * t8) * t10;
    result__[ 19  ] = 0.5e0 * t5 * t14;
    real_type t42  = 0.5e0 * t5 * t17;
    result__[ 20  ] = t42 + result__[10];
    result__[ 21  ] = 0.5e0 * t5 * t20;
    result__[ 22  ] = -0.5e0 * t10;
    result__[ 23  ] = -0.10e1 * (-t5 * t22 + XM__[4]) * t9;
    result__[ 24  ] = result__[18];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = t42 + __INV_DZETA;
    result__[ 27  ] = result__[21];
    result__[ 28  ] = result__[22];
    result__[ 29  ] = result__[23];
    real_type t50  = ModelPars[iM_kD];
    real_type t53  = 0.10e1 * t1 * t50 * t10;
    result__[ 30  ] = t53 + result__[10];
    result__[ 31  ] = result__[28];
    real_type t54  = t1 * t1;
    result__[ 32  ] = -0.10e1 * (-t50 * t54 + XM__[5]) * t9;
    result__[ 33  ] = t53 + __INV_DZETA;
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[32];
    result__[ 36  ] = result__[10];
    real_type t61  = ModelPars[iM_v__Omega__max];
    result__[ 37  ] = -0.10e1 * t9 * t61 * UM__[1];
    result__[ 38  ] = __INV_DZETA;
    result__[ 39  ] = result__[37];
    result__[ 40  ] = -t10 * t61;
    result__[ 41  ] = result__[36];
    real_type t67  = ModelPars[iM_v__fx__max];
    result__[ 42  ] = -0.10e1 * t9 * t67 * UM__[0];
    result__[ 43  ] = __INV_DZETA;
    result__[ 44  ] = result__[42];
    result__[ 45  ] = -t10 * t67;
    result__[ 46  ] = result__[41];
    result__[ 47  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 48, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2fd_odeD2xxup_numRows() const { return 16; }
  integer PointMassCarModel_3::D2fd_odeD2xxup_numCols() const { return 16; }
  integer PointMassCarModel_3::D2fd_odeD2xxup_nnz()     const { return 124; }

  void
  PointMassCarModel_3::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 10  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 13  ;
    iIndex[10] = 1   ; jIndex[10] = 0   ;
    iIndex[11] = 1   ; jIndex[11] = 1   ;
    iIndex[12] = 1   ; jIndex[12] = 2   ;
    iIndex[13] = 1   ; jIndex[13] = 3   ;
    iIndex[14] = 1   ; jIndex[14] = 6   ;
    iIndex[15] = 1   ; jIndex[15] = 7   ;
    iIndex[16] = 1   ; jIndex[16] = 8   ;
    iIndex[17] = 1   ; jIndex[17] = 9   ;
    iIndex[18] = 1   ; jIndex[18] = 10  ;
    iIndex[19] = 1   ; jIndex[19] = 13  ;
    iIndex[20] = 2   ; jIndex[20] = 0   ;
    iIndex[21] = 2   ; jIndex[21] = 1   ;
    iIndex[22] = 2   ; jIndex[22] = 2   ;
    iIndex[23] = 2   ; jIndex[23] = 3   ;
    iIndex[24] = 2   ; jIndex[24] = 6   ;
    iIndex[25] = 2   ; jIndex[25] = 7   ;
    iIndex[26] = 2   ; jIndex[26] = 8   ;
    iIndex[27] = 2   ; jIndex[27] = 9   ;
    iIndex[28] = 2   ; jIndex[28] = 10  ;
    iIndex[29] = 2   ; jIndex[29] = 13  ;
    iIndex[30] = 3   ; jIndex[30] = 0   ;
    iIndex[31] = 3   ; jIndex[31] = 1   ;
    iIndex[32] = 3   ; jIndex[32] = 2   ;
    iIndex[33] = 3   ; jIndex[33] = 3   ;
    iIndex[34] = 3   ; jIndex[34] = 6   ;
    iIndex[35] = 3   ; jIndex[35] = 7   ;
    iIndex[36] = 3   ; jIndex[36] = 8   ;
    iIndex[37] = 3   ; jIndex[37] = 9   ;
    iIndex[38] = 3   ; jIndex[38] = 10  ;
    iIndex[39] = 3   ; jIndex[39] = 13  ;
    iIndex[40] = 4   ; jIndex[40] = 6   ;
    iIndex[41] = 4   ; jIndex[41] = 13  ;
    iIndex[42] = 5   ; jIndex[42] = 6   ;
    iIndex[43] = 5   ; jIndex[43] = 13  ;
    iIndex[44] = 6   ; jIndex[44] = 0   ;
    iIndex[45] = 6   ; jIndex[45] = 1   ;
    iIndex[46] = 6   ; jIndex[46] = 2   ;
    iIndex[47] = 6   ; jIndex[47] = 3   ;
    iIndex[48] = 6   ; jIndex[48] = 4   ;
    iIndex[49] = 6   ; jIndex[49] = 5   ;
    iIndex[50] = 6   ; jIndex[50] = 6   ;
    iIndex[51] = 6   ; jIndex[51] = 7   ;
    iIndex[52] = 6   ; jIndex[52] = 8   ;
    iIndex[53] = 6   ; jIndex[53] = 9   ;
    iIndex[54] = 6   ; jIndex[54] = 10  ;
    iIndex[55] = 6   ; jIndex[55] = 11  ;
    iIndex[56] = 6   ; jIndex[56] = 12  ;
    iIndex[57] = 6   ; jIndex[57] = 13  ;
    iIndex[58] = 6   ; jIndex[58] = 14  ;
    iIndex[59] = 6   ; jIndex[59] = 15  ;
    iIndex[60] = 7   ; jIndex[60] = 0   ;
    iIndex[61] = 7   ; jIndex[61] = 1   ;
    iIndex[62] = 7   ; jIndex[62] = 2   ;
    iIndex[63] = 7   ; jIndex[63] = 3   ;
    iIndex[64] = 7   ; jIndex[64] = 6   ;
    iIndex[65] = 7   ; jIndex[65] = 7   ;
    iIndex[66] = 7   ; jIndex[66] = 8   ;
    iIndex[67] = 7   ; jIndex[67] = 9   ;
    iIndex[68] = 7   ; jIndex[68] = 10  ;
    iIndex[69] = 7   ; jIndex[69] = 13  ;
    iIndex[70] = 8   ; jIndex[70] = 0   ;
    iIndex[71] = 8   ; jIndex[71] = 1   ;
    iIndex[72] = 8   ; jIndex[72] = 2   ;
    iIndex[73] = 8   ; jIndex[73] = 3   ;
    iIndex[74] = 8   ; jIndex[74] = 6   ;
    iIndex[75] = 8   ; jIndex[75] = 7   ;
    iIndex[76] = 8   ; jIndex[76] = 8   ;
    iIndex[77] = 8   ; jIndex[77] = 9   ;
    iIndex[78] = 8   ; jIndex[78] = 10  ;
    iIndex[79] = 8   ; jIndex[79] = 13  ;
    iIndex[80] = 9   ; jIndex[80] = 0   ;
    iIndex[81] = 9   ; jIndex[81] = 1   ;
    iIndex[82] = 9   ; jIndex[82] = 2   ;
    iIndex[83] = 9   ; jIndex[83] = 3   ;
    iIndex[84] = 9   ; jIndex[84] = 6   ;
    iIndex[85] = 9   ; jIndex[85] = 7   ;
    iIndex[86] = 9   ; jIndex[86] = 8   ;
    iIndex[87] = 9   ; jIndex[87] = 9   ;
    iIndex[88] = 9   ; jIndex[88] = 10  ;
    iIndex[89] = 9   ; jIndex[89] = 13  ;
    iIndex[90] = 10  ; jIndex[90] = 0   ;
    iIndex[91] = 10  ; jIndex[91] = 1   ;
    iIndex[92] = 10  ; jIndex[92] = 2   ;
    iIndex[93] = 10  ; jIndex[93] = 3   ;
    iIndex[94] = 10  ; jIndex[94] = 6   ;
    iIndex[95] = 10  ; jIndex[95] = 7   ;
    iIndex[96] = 10  ; jIndex[96] = 8   ;
    iIndex[97] = 10  ; jIndex[97] = 9   ;
    iIndex[98] = 10  ; jIndex[98] = 10  ;
    iIndex[99] = 10  ; jIndex[99] = 13  ;
    iIndex[100] = 11  ; jIndex[100] = 6   ;
    iIndex[101] = 11  ; jIndex[101] = 13  ;
    iIndex[102] = 12  ; jIndex[102] = 6   ;
    iIndex[103] = 12  ; jIndex[103] = 13  ;
    iIndex[104] = 13  ; jIndex[104] = 0   ;
    iIndex[105] = 13  ; jIndex[105] = 1   ;
    iIndex[106] = 13  ; jIndex[106] = 2   ;
    iIndex[107] = 13  ; jIndex[107] = 3   ;
    iIndex[108] = 13  ; jIndex[108] = 4   ;
    iIndex[109] = 13  ; jIndex[109] = 5   ;
    iIndex[110] = 13  ; jIndex[110] = 6   ;
    iIndex[111] = 13  ; jIndex[111] = 7   ;
    iIndex[112] = 13  ; jIndex[112] = 8   ;
    iIndex[113] = 13  ; jIndex[113] = 9   ;
    iIndex[114] = 13  ; jIndex[114] = 10  ;
    iIndex[115] = 13  ; jIndex[115] = 11  ;
    iIndex[116] = 13  ; jIndex[116] = 12  ;
    iIndex[117] = 13  ; jIndex[117] = 13  ;
    iIndex[118] = 13  ; jIndex[118] = 14  ;
    iIndex[119] = 13  ; jIndex[119] = 15  ;
    iIndex[120] = 14  ; jIndex[120] = 6   ;
    iIndex[121] = 14  ; jIndex[121] = 13  ;
    iIndex[122] = 15  ; jIndex[122] = 6   ;
    iIndex[123] = 15  ; jIndex[123] = 13  ;
  }


  void
  PointMassCarModel_3::D2fd_odeD2xxup_sparse(
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
    real_type QM__[4], XM__[7], V__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    QM__[1] = (QL__[1]+QR__[1])/2;
    QM__[2] = (QL__[2]+QR__[2])/2;
    QM__[3] = (QL__[3]+QR__[3])/2;
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
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t5   = XR__[iX_V] / 2 + XL__[iX_V] / 2;
    real_type t9   = XR__[iX_alpha] / 2 + XL__[iX_alpha] / 2;
    real_type t13  = XR__[iX_n] / 2 + XL__[iX_n] / 2;
    real_type t17  = XR__[iX_s] / 2 + XL__[iX_s] / 2;
    real_type t18  = ALIAS_Kappa(t17);
    real_type t19  = zeta__dot_D_4_4(t5, t9, t13, t18);
    real_type t21  = ALIAS_Kappa_D(t17);
    real_type t22  = t21 * t21;
    real_type t26  = XR__[iX_sqrt_inv_Vseg] / 2 + XL__[iX_sqrt_inv_Vseg] / 2;
    real_type t27  = t26 * t26;
    real_type t31  = zeta__dot_D_4(t5, t9, t13, t18);
    real_type t32  = t31 * t1;
    real_type t33  = ALIAS_Kappa_DD(t17);
    real_type t37  = LM__[2];
    real_type t38  = t27 * t37;
    real_type t47  = zeta__dot(t5, t9, t13, t18);
    result__[ 0   ] = -t27 * t22 * t19 * t1 / 4 - t27 * t33 * t32 / 4 - (-t18 * t22 * t19 / 4 - t18 * t33 * t31 / 4 - t22 * t31 / 2 - t33 * t47 / 4) * t38;
    real_type t52  = zeta__dot_D_3_4(t5, t9, t13, t18);
    real_type t54  = t27 * t21;
    real_type t55  = t54 * t52 * t1;
    real_type t58  = t18 * t21 * t52;
    real_type t59  = zeta__dot_D_3(t5, t9, t13, t18);
    real_type t60  = t21 * t59;
    result__[ 1   ] = -t55 / 4 - (-t58 / 4 - t60 / 4) * t38;
    real_type t64  = zeta__dot_D_2_4(t5, t9, t13, t18);
    real_type t66  = t54 * t64 * t1;
    real_type t69  = t18 * t21 * t64;
    real_type t70  = zeta__dot_D_2(t5, t9, t13, t18);
    real_type t71  = t21 * t70;
    result__[ 2   ] = -t66 / 4 - (-t69 / 4 - t71 / 4) * t38;
    real_type t75  = zeta__dot_D_1_4(t5, t9, t13, t18);
    real_type t77  = t54 * t75 * t1;
    real_type t80  = t18 * t21 * t75;
    real_type t81  = zeta__dot_D_1(t5, t9, t13, t18);
    real_type t82  = t21 * t81;
    result__[ 3   ] = -t77 / 4 - (-t80 / 4 - t82 / 4) * t38;
    real_type t89  = t26 * t37;
    result__[ 4   ] = -t26 * t21 * t32 / 2 - (-t18 * t21 * t31 / 2 - t21 * t47 / 2) * t89;
    result__[ 5   ] = result__[0];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[3];
    result__[ 9   ] = result__[4];
    result__[ 10  ] = result__[6];
    real_type t96  = zeta__dot_D_3_3(t5, t9, t13, t18);
    result__[ 11  ] = -t27 * t96 * t1 / 4 + t18 * t96 * t38 / 4;
    real_type t102 = zeta__dot_D_2_3(t5, t9, t13, t18);
    result__[ 12  ] = -t27 * t102 * t1 / 4 + t18 * t102 * t38 / 4;
    real_type t108 = zeta__dot_D_1_3(t5, t9, t13, t18);
    result__[ 13  ] = -t27 * t108 * t1 / 4 + t18 * t108 * t38 / 4;
    result__[ 14  ] = -t26 * t59 * t1 / 2 + t18 * t59 * t89 / 2;
    result__[ 15  ] = t58 * t38 / 4 + t60 * t38 / 4 - t55 / 4;
    result__[ 16  ] = result__[11];
    result__[ 17  ] = result__[12];
    result__[ 18  ] = result__[13];
    result__[ 19  ] = result__[14];
    result__[ 20  ] = result__[7];
    result__[ 21  ] = result__[17];
    real_type t122 = zeta__dot_D_2_2(t5, t9, t13, t18);
    real_type t125 = LM__[1];
    real_type t126 = t5 * t125;
    real_type t127 = sin(t9);
    result__[ 22  ] = -t27 * t122 * t1 / 4 + t18 * t122 * t38 / 4 + t27 * t127 * t126 / 4;
    real_type t133 = zeta__dot_D_1_2(t5, t9, t13, t18);
    real_type t136 = cos(t9);
    result__[ 23  ] = -t27 * t133 * t1 / 4 - t27 * t136 * t125 / 4 + t18 * t133 * t38 / 4;
    result__[ 24  ] = -t26 * t70 * t1 / 2 - t26 * t136 * t126 / 2 + t18 * t70 * t89 / 2;
    result__[ 25  ] = t69 * t38 / 4 + t71 * t38 / 4 - t66 / 4;
    result__[ 26  ] = result__[21];
    result__[ 27  ] = result__[22];
    result__[ 28  ] = result__[23];
    result__[ 29  ] = result__[24];
    result__[ 30  ] = result__[8];
    result__[ 31  ] = result__[18];
    result__[ 32  ] = result__[28];
    real_type t152 = zeta__dot_D_1_1(t5, t9, t13, t18);
    real_type t159 = LM__[3];
    real_type t161 = ModelPars[iM_kD];
    result__[ 33  ] = -t27 * t152 * t1 / 4 + t18 * t152 * t38 / 4 + t161 * t27 * t159 / 2;
    real_type t173 = t26 * t159;
    result__[ 34  ] = -t26 * t81 * t1 / 2 - t26 * t127 * t125 / 2 + t18 * t81 * t89 / 2 + t5 * t161 * t173;
    result__[ 35  ] = t80 * t38 / 4 + t82 * t38 / 4 - t77 / 4;
    result__[ 36  ] = result__[31];
    result__[ 37  ] = result__[32];
    result__[ 38  ] = result__[33];
    result__[ 39  ] = result__[34];
    result__[ 40  ] = -t89 / 2;
    result__[ 41  ] = result__[40];
    result__[ 42  ] = -t173 / 2;
    result__[ 43  ] = result__[42];
    result__[ 44  ] = result__[9];
    result__[ 45  ] = result__[19];
    result__[ 46  ] = result__[29];
    result__[ 47  ] = result__[39];
    result__[ 48  ] = result__[41];
    result__[ 49  ] = result__[43];
    real_type t194 = t5 * t5;
    real_type t198 = LM__[4];
    real_type t201 = ModelPars[iM_v__Omega__max];
    real_type t203 = LM__[5];
    real_type t206 = ModelPars[iM_v__fx__max];
    result__[ 50  ] = -t47 * t1 / 2 - t127 * t126 / 2 - (-t18 * t47 + XR__[iX_Omega] / 2 + XL__[iX_Omega] / 2) * t37 / 2 - (XR__[iX_fx] / 2 + XL__[iX_fx] / 2 - t194 * t161) * t159 / 2 - t201 * UM__[1] * t198 / 2 - t206 * UM__[0] * t203 / 2;
    result__[ 51  ] = result__[44];
    result__[ 52  ] = result__[45];
    result__[ 53  ] = result__[46];
    result__[ 54  ] = result__[47];
    result__[ 55  ] = result__[48];
    result__[ 56  ] = result__[49];
    result__[ 57  ] = result__[50];
    result__[ 58  ] = -t26 * t206 * t203;
    result__[ 59  ] = -t26 * t201 * t198;
    result__[ 60  ] = result__[5];
    result__[ 61  ] = result__[15];
    result__[ 62  ] = result__[25];
    result__[ 63  ] = result__[35];
    result__[ 64  ] = result__[51];
    result__[ 65  ] = result__[60];
    result__[ 66  ] = result__[10];
    result__[ 67  ] = result__[20];
    result__[ 68  ] = result__[30];
    result__[ 69  ] = result__[64];
    result__[ 70  ] = result__[66];
    result__[ 71  ] = result__[16];
    result__[ 72  ] = result__[26];
    result__[ 73  ] = result__[36];
    result__[ 74  ] = result__[52];
    result__[ 75  ] = result__[70];
    result__[ 76  ] = result__[71];
    result__[ 77  ] = result__[72];
    result__[ 78  ] = result__[73];
    result__[ 79  ] = result__[74];
    result__[ 80  ] = result__[67];
    result__[ 81  ] = result__[77];
    result__[ 82  ] = result__[27];
    result__[ 83  ] = result__[37];
    result__[ 84  ] = result__[53];
    result__[ 85  ] = result__[80];
    result__[ 86  ] = result__[81];
    result__[ 87  ] = result__[82];
    result__[ 88  ] = result__[83];
    result__[ 89  ] = result__[84];
    result__[ 90  ] = result__[68];
    result__[ 91  ] = result__[78];
    result__[ 92  ] = result__[88];
    result__[ 93  ] = result__[38];
    result__[ 94  ] = result__[54];
    result__[ 95  ] = result__[90];
    result__[ 96  ] = result__[91];
    result__[ 97  ] = result__[92];
    result__[ 98  ] = result__[93];
    result__[ 99  ] = result__[94];
    result__[ 100 ] = result__[55];
    result__[ 101 ] = result__[100];
    result__[ 102 ] = result__[56];
    result__[ 103 ] = result__[102];
    result__[ 104 ] = result__[69];
    result__[ 105 ] = result__[79];
    result__[ 106 ] = result__[89];
    result__[ 107 ] = result__[99];
    result__[ 108 ] = result__[101];
    result__[ 109 ] = result__[103];
    result__[ 110 ] = result__[57];
    result__[ 111 ] = result__[104];
    result__[ 112 ] = result__[105];
    result__[ 113 ] = result__[106];
    result__[ 114 ] = result__[107];
    result__[ 115 ] = result__[108];
    result__[ 116 ] = result__[109];
    result__[ 117 ] = result__[110];
    result__[ 118 ] = result__[58];
    result__[ 119 ] = result__[59];
    result__[ 120 ] = result__[118];
    result__[ 121 ] = result__[120];
    result__[ 122 ] = result__[119];
    result__[ 123 ] = result__[122];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 124, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: PointMassCarModel_3_Methods_Guess.cc
