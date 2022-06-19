/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_Guess.cc                           |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "PointMassCarModel_2.hh"
#include "PointMassCarModel_2_Pars.hh"

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

namespace PointMassCarModel_2Define {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer PointMassCarModel_2::fd_ode_numEqns() const { return 5; }

  void
  PointMassCarModel_2::fd_ode_eval(
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
    real_type t5   = ALIAS_Kappa(QM__[0]);
    real_type t6   = zeta__dot(t1, t2, XM__[0], t5);
    real_type t9   = sin(t2);
    result__[ 0   ] = -t1 * t9 + t6 * V__[0];
    result__[ 1   ] = t5 * t6 + t6 * V__[1] - XM__[3];
    real_type t19  = t1 * t1;
    result__[ 2   ] = t19 * ModelPars[iM_kD] + t6 * V__[2] - XM__[4];
    result__[ 3   ] = t6 * V__[4] - UM__[0] * ModelPars[iM_v__fx__max];
    result__[ 4   ] = t6 * V__[3] - UM__[1] * ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::Dfd_odeDxxpu_numRows() const { return 5; }
  integer PointMassCarModel_2::Dfd_odeDxxpu_numCols() const { return 12; }
  integer PointMassCarModel_2::Dfd_odeDxxpu_nnz()     const { return 40; }

  void
  PointMassCarModel_2::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[25] = 3   ; jIndex[25] = 4   ;
    iIndex[26] = 3   ; jIndex[26] = 5   ;
    iIndex[27] = 3   ; jIndex[27] = 6   ;
    iIndex[28] = 3   ; jIndex[28] = 7   ;
    iIndex[29] = 3   ; jIndex[29] = 9   ;
    iIndex[30] = 3   ; jIndex[30] = 10  ;
    iIndex[31] = 4   ; jIndex[31] = 0   ;
    iIndex[32] = 4   ; jIndex[32] = 1   ;
    iIndex[33] = 4   ; jIndex[33] = 2   ;
    iIndex[34] = 4   ; jIndex[34] = 3   ;
    iIndex[35] = 4   ; jIndex[35] = 5   ;
    iIndex[36] = 4   ; jIndex[36] = 6   ;
    iIndex[37] = 4   ; jIndex[37] = 7   ;
    iIndex[38] = 4   ; jIndex[38] = 8   ;
    iIndex[39] = 4   ; jIndex[39] = 11  ;
  }


  void
  PointMassCarModel_2::Dfd_odeDxxpu_sparse(
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
    real_type t3   = XM__[0];
    real_type t5   = ALIAS_Kappa(QM__[0]);
    real_type t6   = zeta__dot_D_3(t1, t2, t3, t5);
    real_type t7   = V__[0];
    real_type t9   = 0.5e0 * t6 * t7;
    real_type t10  = zeta__dot(t1, t2, t3, t5);
    real_type t11  = t10 * __INV_DZETA;
    result__[ 0   ] = t9 - t11;
    real_type t12  = zeta__dot_D_2(t1, t2, t3, t5);
    real_type t15  = cos(t2);
    result__[ 1   ] = 0.5e0 * t12 * t7 - 0.5e0 * t15 * t1;
    real_type t18  = zeta__dot_D_1(t1, t2, t3, t5);
    real_type t21  = sin(t2);
    result__[ 2   ] = 0.5e0 * t7 * t18 - 0.5e0 * t21;
    result__[ 3   ] = t9 + t11;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t23  = V__[1];
    result__[ 6   ] = 0.5e0 * t23 * t6 + 0.5e0 * t6 * t5;
    real_type t29  = 0.5e0 * t23 * t12;
    real_type t31  = 0.5e0 * t12 * t5;
    result__[ 7   ] = t29 + t31 - t11;
    result__[ 8   ] = 0.5e0 * t23 * t18 + 0.5e0 * t18 * t5;
    result__[ 9   ] = -0.5e0;
    result__[ 10  ] = result__[6];
    result__[ 11  ] = t29 + t31 + t11;
    result__[ 12  ] = result__[8];
    result__[ 13  ] = -0.5e0;
    real_type t36  = V__[2];
    result__[ 14  ] = 0.5e0 * t36 * t6;
    result__[ 15  ] = 0.5e0 * t36 * t12;
    real_type t40  = 0.5e0 * t36 * t18;
    real_type t43  = 0.10e1 * t1 * ModelPars[iM_kD];
    result__[ 16  ] = t40 + t43 - t11;
    result__[ 17  ] = -0.5e0;
    result__[ 18  ] = result__[14];
    result__[ 19  ] = result__[15];
    result__[ 20  ] = t40 + t43 + t11;
    result__[ 21  ] = -0.5e0;
    real_type t44  = V__[4];
    result__[ 22  ] = 0.5e0 * t44 * t6;
    result__[ 23  ] = 0.5e0 * t44 * t12;
    result__[ 24  ] = 0.5e0 * t44 * t18;
    result__[ 25  ] = -t11;
    result__[ 26  ] = result__[22];
    result__[ 27  ] = result__[23];
    result__[ 28  ] = result__[24];
    result__[ 29  ] = t11;
    result__[ 30  ] = -ModelPars[iM_v__fx__max];
    real_type t49  = V__[3];
    result__[ 31  ] = 0.5e0 * t49 * t6;
    result__[ 32  ] = 0.5e0 * t49 * t12;
    result__[ 33  ] = 0.5e0 * t49 * t18;
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[31];
    result__[ 36  ] = result__[32];
    result__[ 37  ] = result__[33];
    result__[ 38  ] = result__[29];
    result__[ 39  ] = -ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 40, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2fd_odeD2xxpu_numRows() const { return 12; }
  integer PointMassCarModel_2::D2fd_odeD2xxpu_numCols() const { return 12; }
  integer PointMassCarModel_2::D2fd_odeD2xxpu_nnz()     const { return 36; }

  void
  PointMassCarModel_2::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 7   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 5   ;
    iIndex[16] = 2   ; jIndex[16] = 6   ;
    iIndex[17] = 2   ; jIndex[17] = 7   ;
    iIndex[18] = 5   ; jIndex[18] = 0   ;
    iIndex[19] = 5   ; jIndex[19] = 1   ;
    iIndex[20] = 5   ; jIndex[20] = 2   ;
    iIndex[21] = 5   ; jIndex[21] = 5   ;
    iIndex[22] = 5   ; jIndex[22] = 6   ;
    iIndex[23] = 5   ; jIndex[23] = 7   ;
    iIndex[24] = 6   ; jIndex[24] = 0   ;
    iIndex[25] = 6   ; jIndex[25] = 1   ;
    iIndex[26] = 6   ; jIndex[26] = 2   ;
    iIndex[27] = 6   ; jIndex[27] = 5   ;
    iIndex[28] = 6   ; jIndex[28] = 6   ;
    iIndex[29] = 6   ; jIndex[29] = 7   ;
    iIndex[30] = 7   ; jIndex[30] = 0   ;
    iIndex[31] = 7   ; jIndex[31] = 1   ;
    iIndex[32] = 7   ; jIndex[32] = 2   ;
    iIndex[33] = 7   ; jIndex[33] = 5   ;
    iIndex[34] = 7   ; jIndex[34] = 6   ;
    iIndex[35] = 7   ; jIndex[35] = 7   ;
  }


  void
  PointMassCarModel_2::D2fd_odeD2xxpu_sparse(
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
    real_type t9   = XR__[iX_alpha] / 2 + XL__[iX_alpha] / 2;
    real_type t13  = XR__[iX_n] / 2 + XL__[iX_n] / 2;
    real_type t15  = ALIAS_Kappa(QM__[0]);
    real_type t16  = zeta__dot_D_3_3(t5, t9, t13, t15);
    real_type t18  = V__[0];
    real_type t21  = LM__[1];
    real_type t22  = V__[1];
    real_type t28  = LM__[2];
    real_type t30  = V__[2];
    real_type t33  = LM__[3];
    real_type t35  = V__[4];
    real_type t38  = LM__[4];
    real_type t40  = V__[3];
    result__[ 0   ] = t18 * t16 * t1 / 4 + (t16 * t15 / 4 + t22 * t16 / 4) * t21 + t30 * t16 * t28 / 4 + t35 * t16 * t33 / 4 + t40 * t16 * t38 / 4;
    real_type t43  = zeta__dot_D_2_3(t5, t9, t13, t15);
    result__[ 1   ] = t18 * t43 * t1 / 4 + (t43 * t15 / 4 + t22 * t43 / 4) * t21 + t30 * t43 * t28 / 4 + t35 * t43 * t33 / 4 + t40 * t43 * t38 / 4;
    real_type t61  = zeta__dot_D_1_3(t5, t9, t13, t15);
    result__[ 2   ] = t18 * t61 * t1 / 4 + (t61 * t15 / 4 + t22 * t61 / 4) * t21 + t30 * t61 * t28 / 4 + t35 * t61 * t33 / 4 + t40 * t61 * t38 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    real_type t79  = zeta__dot_D_2_2(t5, t9, t13, t15);
    real_type t81  = sin(t9);
    result__[ 7   ] = (t18 * t79 / 4 + t81 * t5 / 4) * t1 + (t79 * t15 / 4 + t22 * t79 / 4) * t21 + t30 * t79 * t28 / 4 + t35 * t79 * t33 / 4 + t40 * t79 * t38 / 4;
    real_type t100 = zeta__dot_D_1_2(t5, t9, t13, t15);
    real_type t102 = cos(t9);
    result__[ 8   ] = (t18 * t100 / 4 - t102 / 4) * t1 + (t100 * t15 / 4 + t22 * t100 / 4) * t21 + t30 * t100 * t28 / 4 + t35 * t100 * t33 / 4 + t40 * t100 * t38 / 4;
    result__[ 9   ] = result__[6];
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[5];
    result__[ 13  ] = result__[11];
    real_type t120 = zeta__dot_D_1_1(t5, t9, t13, t15);
    result__[ 14  ] = t18 * t120 * t1 / 4 + (t120 * t15 / 4 + t22 * t120 / 4) * t21 + (t30 * t120 / 4 + ModelPars[iM_kD] / 2) * t28 + t35 * t120 * t33 / 4 + t40 * t120 * t38 / 4;
    result__[ 15  ] = result__[12];
    result__[ 16  ] = result__[13];
    result__[ 17  ] = result__[14];
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[9];
    result__[ 20  ] = result__[15];
    result__[ 21  ] = result__[18];
    result__[ 22  ] = result__[19];
    result__[ 23  ] = result__[20];
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[10];
    result__[ 26  ] = result__[16];
    result__[ 27  ] = result__[24];
    result__[ 28  ] = result__[25];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[23];
    result__[ 31  ] = result__[29];
    result__[ 32  ] = result__[17];
    result__[ 33  ] = result__[30];
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[32];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 36, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: PointMassCarModel_2_Methods_Guess.cc
