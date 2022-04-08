/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_Guess.cc                           |
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


#include "PointMassCarModel_1.hh"
#include "PointMassCarModel_1_Pars.hh"

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
#define ALIAS_yV_R(__t1, __t2) segmentRight.iso_y( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.iso_y( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.iso_y( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.iso_x( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.iso_x( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.iso_x( __t1, __t2)
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
#define ALIAS_Kappa_R_DD(__t1) segmentRight.iso_curvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.iso_curvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.iso_curvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.iso_curvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.iso_curvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.iso_curvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.iso_curvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.iso_curvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.iso_curvature( __t1)
#define ALIAS_LimitMinSpeed_DD(__t1) LimitMinSpeed.DD( __t1)
#define ALIAS_LimitMinSpeed_D(__t1) LimitMinSpeed.D( __t1)
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

namespace PointMassCarModel_1Define {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer PointMassCarModel_1::fd_ode_numEqns() const { return 5; }

  void
  PointMassCarModel_1::fd_ode_eval(
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
    real_type QM__[11], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    QM__[1] = (QL__[1]+QR__[1])/2;
    QM__[2] = (QL__[2]+QR__[2])/2;
    QM__[3] = (QL__[3]+QR__[3])/2;
    QM__[4] = (QL__[4]+QR__[4])/2;
    QM__[5] = (QL__[5]+QR__[5])/2;
    QM__[6] = (QL__[6]+QR__[6])/2;
    QM__[7] = (QL__[7]+QR__[7])/2;
    QM__[8] = (QL__[8]+QR__[8])/2;
    QM__[9] = (QL__[9]+QR__[9])/2;
    QM__[10] = (QL__[10]+QR__[10])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = XM__[2];
    real_type t3   = XM__[1];
    real_type t4   = sin(t3);
    real_type t8   = ALIAS_Kappa(QM__[0]);
    real_type t9   = inv_zeta__dot(t2, t3, XM__[0], t8);
    result__[ 0   ] = -t9 * t4 * t2 + V__[0];
    result__[ 1   ] = -t9 * XM__[3] + t8 + V__[1];
    real_type t15  = t2 * t2;
    result__[ 2   ] = V__[2] - (-ModelPars[iM_kD] * t15 + XM__[4]) * t9;
    result__[ 3   ] = -t9 * ModelPars[iM_v__Omega__max] * UM__[1] + V__[3];
    result__[ 4   ] = -t9 * ModelPars[iM_v__fx__max] * UM__[0] + V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::Dfd_odeDxxup_numRows() const { return 5; }
  integer PointMassCarModel_1::Dfd_odeDxxup_numCols() const { return 12; }
  integer PointMassCarModel_1::Dfd_odeDxxup_nnz()     const { return 40; }

  void
  PointMassCarModel_1::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 1   ; jIndex[13] = 8   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 4   ;
    iIndex[18] = 2   ; jIndex[18] = 5   ;
    iIndex[19] = 2   ; jIndex[19] = 6   ;
    iIndex[20] = 2   ; jIndex[20] = 7   ;
    iIndex[21] = 2   ; jIndex[21] = 9   ;
    iIndex[22] = 3   ; jIndex[22] = 0   ;
    iIndex[23] = 3   ; jIndex[23] = 1   ;
    iIndex[24] = 3   ; jIndex[24] = 2   ;
    iIndex[25] = 3   ; jIndex[25] = 3   ;
    iIndex[26] = 3   ; jIndex[26] = 5   ;
    iIndex[27] = 3   ; jIndex[27] = 6   ;
    iIndex[28] = 3   ; jIndex[28] = 7   ;
    iIndex[29] = 3   ; jIndex[29] = 8   ;
    iIndex[30] = 3   ; jIndex[30] = 11  ;
    iIndex[31] = 4   ; jIndex[31] = 0   ;
    iIndex[32] = 4   ; jIndex[32] = 1   ;
    iIndex[33] = 4   ; jIndex[33] = 2   ;
    iIndex[34] = 4   ; jIndex[34] = 4   ;
    iIndex[35] = 4   ; jIndex[35] = 5   ;
    iIndex[36] = 4   ; jIndex[36] = 6   ;
    iIndex[37] = 4   ; jIndex[37] = 7   ;
    iIndex[38] = 4   ; jIndex[38] = 9   ;
    iIndex[39] = 4   ; jIndex[39] = 10  ;
  }


  void
  PointMassCarModel_1::Dfd_odeDxxup_sparse(
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
    real_type QM__[11], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    QM__[1] = (QL__[1]+QR__[1])/2;
    QM__[2] = (QL__[2]+QR__[2])/2;
    QM__[3] = (QL__[3]+QR__[3])/2;
    QM__[4] = (QL__[4]+QR__[4])/2;
    QM__[5] = (QL__[5]+QR__[5])/2;
    QM__[6] = (QL__[6]+QR__[6])/2;
    QM__[7] = (QL__[7]+QR__[7])/2;
    QM__[8] = (QL__[8]+QR__[8])/2;
    QM__[9] = (QL__[9]+QR__[9])/2;
    QM__[10] = (QL__[10]+QR__[10])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = XM__[2];
    real_type t2   = XM__[1];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = XM__[0];
    real_type t7   = ALIAS_Kappa(QM__[0]);
    real_type t8   = inv_zeta__dot_D_3(t1, t2, t5, t7);
    real_type t10  = 0.5e0 * t8 * t4;
    result__[ 0   ] = -t10 - __INV_DZETA;
    real_type t11  = cos(t2);
    real_type t13  = inv_zeta__dot(t1, t2, t5, t7);
    real_type t16  = inv_zeta__dot_D_2(t1, t2, t5, t7);
    result__[ 1   ] = -0.5e0 * t13 * t11 * t1 - 0.5e0 * t16 * t4;
    real_type t21  = inv_zeta__dot_D_1(t1, t2, t5, t7);
    result__[ 2   ] = -0.5e0 * t13 * t3 - 0.5e0 * t21 * t4;
    result__[ 3   ] = -t10 + __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t24  = XM__[3];
    result__[ 6   ] = -0.5e0 * t8 * t24;
    real_type t28  = 0.5e0 * t16 * t24;
    result__[ 7   ] = -t28 - __INV_DZETA;
    result__[ 8   ] = -0.5e0 * t21 * t24;
    result__[ 9   ] = -0.5e0 * t13;
    result__[ 10  ] = result__[6];
    result__[ 11  ] = -t28 + __INV_DZETA;
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    real_type t32  = t1 * t1;
    real_type t33  = ModelPars[iM_kD];
    real_type t36  = -t33 * t32 + XM__[4];
    result__[ 14  ] = -0.5e0 * t36 * t8;
    result__[ 15  ] = -0.5e0 * t36 * t16;
    real_type t42  = 0.5e0 * t36 * t21;
    real_type t45  = 0.10e1 * t1 * t33 * t13;
    result__[ 16  ] = -t42 + t45 - __INV_DZETA;
    result__[ 17  ] = result__[13];
    result__[ 18  ] = result__[14];
    result__[ 19  ] = result__[15];
    result__[ 20  ] = -t42 + t45 + __INV_DZETA;
    result__[ 21  ] = result__[17];
    real_type t47  = ModelPars[iM_v__Omega__max];
    real_type t48  = t47 * UM__[1];
    result__[ 22  ] = -0.5e0 * t8 * t48;
    result__[ 23  ] = -0.5e0 * t16 * t48;
    result__[ 24  ] = -0.5e0 * t21 * t48;
    result__[ 25  ] = -__INV_DZETA;
    result__[ 26  ] = result__[22];
    result__[ 27  ] = result__[23];
    result__[ 28  ] = result__[24];
    result__[ 29  ] = __INV_DZETA;
    result__[ 30  ] = -t13 * t47;
    real_type t57  = ModelPars[iM_v__fx__max];
    real_type t58  = t57 * UM__[0];
    result__[ 31  ] = -0.5e0 * t8 * t58;
    result__[ 32  ] = -0.5e0 * t16 * t58;
    result__[ 33  ] = -0.5e0 * t21 * t58;
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[31];
    result__[ 36  ] = result__[32];
    result__[ 37  ] = result__[33];
    result__[ 38  ] = __INV_DZETA;
    result__[ 39  ] = -t13 * t57;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 40, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::D2fd_odeD2xxup_numRows() const { return 12; }
  integer PointMassCarModel_1::D2fd_odeD2xxup_numCols() const { return 12; }
  integer PointMassCarModel_1::D2fd_odeD2xxup_nnz()     const { return 108; }

  void
  PointMassCarModel_1::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[12] = 1   ; jIndex[12] = 0   ;
    iIndex[13] = 1   ; jIndex[13] = 1   ;
    iIndex[14] = 1   ; jIndex[14] = 2   ;
    iIndex[15] = 1   ; jIndex[15] = 3   ;
    iIndex[16] = 1   ; jIndex[16] = 4   ;
    iIndex[17] = 1   ; jIndex[17] = 5   ;
    iIndex[18] = 1   ; jIndex[18] = 6   ;
    iIndex[19] = 1   ; jIndex[19] = 7   ;
    iIndex[20] = 1   ; jIndex[20] = 8   ;
    iIndex[21] = 1   ; jIndex[21] = 9   ;
    iIndex[22] = 1   ; jIndex[22] = 10  ;
    iIndex[23] = 1   ; jIndex[23] = 11  ;
    iIndex[24] = 2   ; jIndex[24] = 0   ;
    iIndex[25] = 2   ; jIndex[25] = 1   ;
    iIndex[26] = 2   ; jIndex[26] = 2   ;
    iIndex[27] = 2   ; jIndex[27] = 3   ;
    iIndex[28] = 2   ; jIndex[28] = 4   ;
    iIndex[29] = 2   ; jIndex[29] = 5   ;
    iIndex[30] = 2   ; jIndex[30] = 6   ;
    iIndex[31] = 2   ; jIndex[31] = 7   ;
    iIndex[32] = 2   ; jIndex[32] = 8   ;
    iIndex[33] = 2   ; jIndex[33] = 9   ;
    iIndex[34] = 2   ; jIndex[34] = 10  ;
    iIndex[35] = 2   ; jIndex[35] = 11  ;
    iIndex[36] = 3   ; jIndex[36] = 0   ;
    iIndex[37] = 3   ; jIndex[37] = 1   ;
    iIndex[38] = 3   ; jIndex[38] = 2   ;
    iIndex[39] = 3   ; jIndex[39] = 5   ;
    iIndex[40] = 3   ; jIndex[40] = 6   ;
    iIndex[41] = 3   ; jIndex[41] = 7   ;
    iIndex[42] = 4   ; jIndex[42] = 0   ;
    iIndex[43] = 4   ; jIndex[43] = 1   ;
    iIndex[44] = 4   ; jIndex[44] = 2   ;
    iIndex[45] = 4   ; jIndex[45] = 5   ;
    iIndex[46] = 4   ; jIndex[46] = 6   ;
    iIndex[47] = 4   ; jIndex[47] = 7   ;
    iIndex[48] = 5   ; jIndex[48] = 0   ;
    iIndex[49] = 5   ; jIndex[49] = 1   ;
    iIndex[50] = 5   ; jIndex[50] = 2   ;
    iIndex[51] = 5   ; jIndex[51] = 3   ;
    iIndex[52] = 5   ; jIndex[52] = 4   ;
    iIndex[53] = 5   ; jIndex[53] = 5   ;
    iIndex[54] = 5   ; jIndex[54] = 6   ;
    iIndex[55] = 5   ; jIndex[55] = 7   ;
    iIndex[56] = 5   ; jIndex[56] = 8   ;
    iIndex[57] = 5   ; jIndex[57] = 9   ;
    iIndex[58] = 5   ; jIndex[58] = 10  ;
    iIndex[59] = 5   ; jIndex[59] = 11  ;
    iIndex[60] = 6   ; jIndex[60] = 0   ;
    iIndex[61] = 6   ; jIndex[61] = 1   ;
    iIndex[62] = 6   ; jIndex[62] = 2   ;
    iIndex[63] = 6   ; jIndex[63] = 3   ;
    iIndex[64] = 6   ; jIndex[64] = 4   ;
    iIndex[65] = 6   ; jIndex[65] = 5   ;
    iIndex[66] = 6   ; jIndex[66] = 6   ;
    iIndex[67] = 6   ; jIndex[67] = 7   ;
    iIndex[68] = 6   ; jIndex[68] = 8   ;
    iIndex[69] = 6   ; jIndex[69] = 9   ;
    iIndex[70] = 6   ; jIndex[70] = 10  ;
    iIndex[71] = 6   ; jIndex[71] = 11  ;
    iIndex[72] = 7   ; jIndex[72] = 0   ;
    iIndex[73] = 7   ; jIndex[73] = 1   ;
    iIndex[74] = 7   ; jIndex[74] = 2   ;
    iIndex[75] = 7   ; jIndex[75] = 3   ;
    iIndex[76] = 7   ; jIndex[76] = 4   ;
    iIndex[77] = 7   ; jIndex[77] = 5   ;
    iIndex[78] = 7   ; jIndex[78] = 6   ;
    iIndex[79] = 7   ; jIndex[79] = 7   ;
    iIndex[80] = 7   ; jIndex[80] = 8   ;
    iIndex[81] = 7   ; jIndex[81] = 9   ;
    iIndex[82] = 7   ; jIndex[82] = 10  ;
    iIndex[83] = 7   ; jIndex[83] = 11  ;
    iIndex[84] = 8   ; jIndex[84] = 0   ;
    iIndex[85] = 8   ; jIndex[85] = 1   ;
    iIndex[86] = 8   ; jIndex[86] = 2   ;
    iIndex[87] = 8   ; jIndex[87] = 5   ;
    iIndex[88] = 8   ; jIndex[88] = 6   ;
    iIndex[89] = 8   ; jIndex[89] = 7   ;
    iIndex[90] = 9   ; jIndex[90] = 0   ;
    iIndex[91] = 9   ; jIndex[91] = 1   ;
    iIndex[92] = 9   ; jIndex[92] = 2   ;
    iIndex[93] = 9   ; jIndex[93] = 5   ;
    iIndex[94] = 9   ; jIndex[94] = 6   ;
    iIndex[95] = 9   ; jIndex[95] = 7   ;
    iIndex[96] = 10  ; jIndex[96] = 0   ;
    iIndex[97] = 10  ; jIndex[97] = 1   ;
    iIndex[98] = 10  ; jIndex[98] = 2   ;
    iIndex[99] = 10  ; jIndex[99] = 5   ;
    iIndex[100] = 10  ; jIndex[100] = 6   ;
    iIndex[101] = 10  ; jIndex[101] = 7   ;
    iIndex[102] = 11  ; jIndex[102] = 0   ;
    iIndex[103] = 11  ; jIndex[103] = 1   ;
    iIndex[104] = 11  ; jIndex[104] = 2   ;
    iIndex[105] = 11  ; jIndex[105] = 5   ;
    iIndex[106] = 11  ; jIndex[106] = 6   ;
    iIndex[107] = 11  ; jIndex[107] = 7   ;
  }


  void
  PointMassCarModel_1::D2fd_odeD2xxup_sparse(
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
    real_type QM__[11], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    QM__[1] = (QL__[1]+QR__[1])/2;
    QM__[2] = (QL__[2]+QR__[2])/2;
    QM__[3] = (QL__[3]+QR__[3])/2;
    QM__[4] = (QL__[4]+QR__[4])/2;
    QM__[5] = (QL__[5]+QR__[5])/2;
    QM__[6] = (QL__[6]+QR__[6])/2;
    QM__[7] = (QL__[7]+QR__[7])/2;
    QM__[8] = (QL__[8]+QR__[8])/2;
    QM__[9] = (QL__[9]+QR__[9])/2;
    QM__[10] = (QL__[10]+QR__[10])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t5   = XR__[iX_V] / 2 + XL__[iX_V] / 2;
    real_type t6   = t5 * t1;
    real_type t10  = XR__[iX_alpha] / 2 + XL__[iX_alpha] / 2;
    real_type t11  = sin(t10);
    real_type t15  = XR__[iX_n] / 2 + XL__[iX_n] / 2;
    real_type t17  = ALIAS_Kappa(QM__[0]);
    real_type t18  = inv_zeta__dot_D_3_3(t5, t10, t15, t17);
    real_type t21  = LM__[1];
    real_type t26  = (XR__[iX_Omega] / 2 + XL__[iX_Omega] / 2) * t21;
    real_type t28  = LM__[2];
    real_type t34  = ModelPars[iM_kD];
    real_type t35  = t5 * t5;
    real_type t37  = XR__[iX_fx] / 2 + XL__[iX_fx] / 2 - t35 * t34;
    real_type t39  = LM__[3];
    real_type t41  = UM__[1] * t39;
    real_type t42  = ModelPars[iM_v__Omega__max];
    real_type t45  = LM__[4];
    real_type t47  = UM__[0] * t45;
    real_type t48  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = -t18 * t11 * t6 / 4 - t37 * t18 * t28 / 4 - t18 * t42 * t41 / 4 - t18 * t48 * t47 / 4 - t18 * t26 / 4;
    real_type t52  = cos(t10);
    real_type t53  = inv_zeta__dot_D_3(t5, t10, t15, t17);
    real_type t56  = inv_zeta__dot_D_2_3(t5, t10, t15, t17);
    real_type t59  = t56 * t26;
    real_type t61  = t37 * t56 * t28;
    real_type t63  = t56 * t42 * t41;
    real_type t65  = t56 * t48 * t47;
    result__[ 1   ] = -t56 * t11 * t6 / 4 - t53 * t52 * t6 / 4 - t59 / 4 - t61 / 4 - t63 / 4 - t65 / 4;
    real_type t70  = inv_zeta__dot_D_1_3(t5, t10, t15, t17);
    real_type t75  = t70 * t26 / 4;
    real_type t79  = t53 * t28;
    real_type t80  = t5 * t34;
    real_type t85  = t70 * t42 * t41 / 4;
    real_type t88  = t70 * t48 * t47 / 4;
    result__[ 2   ] = -t53 * t11 * t1 / 4 - t70 * t11 * t6 / 4 - t75 - t37 * t70 * t28 / 4 + t80 * t79 / 2 - t85 - t88;
    result__[ 3   ] = -t53 * t21 / 4;
    result__[ 4   ] = -t79 / 4;
    result__[ 5   ] = result__[0];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[3];
    result__[ 9   ] = result__[4];
    real_type t92  = t48 * t45;
    result__[ 10  ] = -t53 * t92 / 2;
    real_type t95  = t42 * t39;
    result__[ 11  ] = -t53 * t95 / 2;
    result__[ 12  ] = result__[6];
    real_type t98  = t11 * t5;
    real_type t99  = inv_zeta__dot(t5, t10, t15, t17);
    real_type t102 = t52 * t5;
    real_type t103 = inv_zeta__dot_D_2(t5, t10, t15, t17);
    real_type t106 = inv_zeta__dot_D_2_2(t5, t10, t15, t17);
    result__[ 13  ] = (t99 * t98 / 4 - t103 * t102 / 2 - t106 * t98 / 4) * t1 - t106 * t26 / 4 - t37 * t106 * t28 / 4 - t106 * t42 * t41 / 4 - t106 * t48 * t47 / 4;
    real_type t123 = inv_zeta__dot_D_1(t5, t10, t15, t17);
    real_type t126 = inv_zeta__dot_D_1_2(t5, t10, t15, t17);
    real_type t130 = (-t123 * t102 / 4 - t103 * t11 / 4 - t126 * t98 / 4 - t99 * t52 / 4) * t1;
    real_type t132 = t126 * t26 / 4;
    real_type t136 = t103 * t28;
    real_type t141 = t126 * t42 * t41 / 4;
    real_type t144 = t126 * t48 * t47 / 4;
    result__[ 14  ] = t130 - t132 - t37 * t126 * t28 / 4 + t80 * t136 / 2 - t141 - t144;
    result__[ 15  ] = -t103 * t21 / 4;
    result__[ 16  ] = -t136 / 4;
    result__[ 17  ] = (-t53 * t102 / 4 - t56 * t98 / 4) * t1 - t59 / 4 - t61 / 4 - t63 / 4 - t65 / 4;
    result__[ 18  ] = result__[13];
    result__[ 19  ] = result__[14];
    result__[ 20  ] = result__[15];
    result__[ 21  ] = result__[16];
    result__[ 22  ] = -t103 * t92 / 2;
    result__[ 23  ] = -t103 * t95 / 2;
    result__[ 24  ] = result__[7];
    result__[ 25  ] = result__[19];
    real_type t163 = inv_zeta__dot_D_1_1(t5, t10, t15, t17);
    result__[ 26  ] = (-t123 * t11 / 2 - t163 * t98 / 4) * t1 - t163 * t26 / 4 + (-t37 * t163 / 4 + t5 * t34 * t123 + t34 * t99 / 2) * t28 - t163 * t42 * t41 / 4 - t163 * t48 * t47 / 4;
    result__[ 27  ] = -t123 * t21 / 4;
    result__[ 28  ] = -t123 * t28 / 4;
    result__[ 29  ] = (-t53 * t11 / 4 - t70 * t98 / 4) * t1 - t75 + (-t37 * t70 / 4 + t5 * t34 * t53 / 2) * t28 - t85 - t88;
    result__[ 30  ] = t130 - t132 + (-t37 * t126 / 4 + t5 * t34 * t103 / 2) * t28 - t141 - t144;
    result__[ 31  ] = result__[26];
    result__[ 32  ] = result__[27];
    result__[ 33  ] = result__[28];
    result__[ 34  ] = -t123 * t92 / 2;
    result__[ 35  ] = -t123 * t95 / 2;
    result__[ 36  ] = result__[8];
    result__[ 37  ] = result__[20];
    result__[ 38  ] = result__[32];
    result__[ 39  ] = result__[36];
    result__[ 40  ] = result__[37];
    result__[ 41  ] = result__[38];
    result__[ 42  ] = result__[9];
    result__[ 43  ] = result__[21];
    result__[ 44  ] = result__[33];
    result__[ 45  ] = result__[42];
    result__[ 46  ] = result__[43];
    result__[ 47  ] = result__[44];
    result__[ 48  ] = result__[5];
    result__[ 49  ] = result__[17];
    result__[ 50  ] = result__[29];
    result__[ 51  ] = result__[39];
    result__[ 52  ] = result__[45];
    result__[ 53  ] = result__[48];
    result__[ 54  ] = result__[12];
    result__[ 55  ] = result__[24];
    result__[ 56  ] = result__[51];
    result__[ 57  ] = result__[52];
    result__[ 58  ] = result__[10];
    result__[ 59  ] = result__[11];
    result__[ 60  ] = result__[54];
    result__[ 61  ] = result__[18];
    result__[ 62  ] = result__[30];
    result__[ 63  ] = result__[40];
    result__[ 64  ] = result__[46];
    result__[ 65  ] = result__[60];
    result__[ 66  ] = result__[61];
    result__[ 67  ] = result__[25];
    result__[ 68  ] = result__[63];
    result__[ 69  ] = result__[64];
    result__[ 70  ] = result__[22];
    result__[ 71  ] = result__[23];
    result__[ 72  ] = result__[55];
    result__[ 73  ] = result__[67];
    result__[ 74  ] = result__[31];
    result__[ 75  ] = result__[41];
    result__[ 76  ] = result__[47];
    result__[ 77  ] = result__[72];
    result__[ 78  ] = result__[73];
    result__[ 79  ] = result__[74];
    result__[ 80  ] = result__[75];
    result__[ 81  ] = result__[76];
    result__[ 82  ] = result__[34];
    result__[ 83  ] = result__[35];
    result__[ 84  ] = result__[56];
    result__[ 85  ] = result__[68];
    result__[ 86  ] = result__[80];
    result__[ 87  ] = result__[84];
    result__[ 88  ] = result__[85];
    result__[ 89  ] = result__[86];
    result__[ 90  ] = result__[57];
    result__[ 91  ] = result__[69];
    result__[ 92  ] = result__[81];
    result__[ 93  ] = result__[90];
    result__[ 94  ] = result__[91];
    result__[ 95  ] = result__[92];
    result__[ 96  ] = result__[58];
    result__[ 97  ] = result__[70];
    result__[ 98  ] = result__[82];
    result__[ 99  ] = result__[96];
    result__[ 100 ] = result__[97];
    result__[ 101 ] = result__[98];
    result__[ 102 ] = result__[59];
    result__[ 103 ] = result__[71];
    result__[ 104 ] = result__[83];
    result__[ 105 ] = result__[102];
    result__[ 106 ] = result__[103];
    result__[ 107 ] = result__[104];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 108, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: PointMassCarModel_1_Methods_Guess.cc
