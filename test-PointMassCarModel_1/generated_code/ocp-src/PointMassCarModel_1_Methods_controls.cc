/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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


#include "PointMassCarModel_1.hh"
#include "PointMassCarModel_1_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Road2D;


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


namespace PointMassCarModel_1Define {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  PointMassCarModel_1::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[11], XM__[5], LM__[5];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = XM__[2];
    real_type t2   = XM__[1];
    real_type t3   = XM__[0];
    real_type t4   = QM__[0];
    real_type t5   = ALIAS_Kappa(t4);
    real_type t6   = inv_zeta__dot(t1, t2, t3, t5);
    real_type t7   = t1 * t1;
    real_type t8   = XM__[3];
    real_type t9   = t8 * t8;
    real_type t12  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t15  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t18  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t20  = XM__[4];
    real_type t21  = t20 * t20;
    real_type t30  = AdherenceEllipse(1.0 / t18 / t15 / t12 * (t18 * t12 * t15 - t12 * t9 * t7 - t18 * t21));
    real_type t35  = ModelPars[iM_Pmax];
    real_type t39  = PowerLimit(1.0 / t35 * (-ModelPars[iM_m] * t20 * t1 + t35));
    real_type t41  = ALIAS_leftWidth(t4);
    real_type t43  = RoadLeftBorder(t41 - t3);
    real_type t45  = ALIAS_rightWidth(t4);
    real_type t47  = RoadRightBorder(t45 + t3);
    real_type t48  = LimitMinSpeed(t1);
    real_type t51  = sin(t2);
    real_type t53  = LM__[1];
    real_type t61  = UM__[0];
    real_type t66  = UM__[1];
    real_type t71  = v__fxControl(t61, -1, 1);
    real_type t72  = v__OmegaControl(t66, -1, 1);
    real_type result__ = t30 * t6 + t39 * t6 + t43 * t6 + t6 * (t47 + t48 + t51 * LM__[0] * t1 + t53 * t8 + LM__[2] * (-ModelPars[iM_kD] * t7 + t20) + LM__[4] * t61 * ModelPars[iM_v__fx__max] + LM__[3] * t66 * ModelPars[iM_v__Omega__max] + ModelPars[iM_wT] + t71 + t72) - t5 * t53;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  integer
  PointMassCarModel_1::g_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[11], XM__[5], LM__[5];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = ALIAS_Kappa(QM__[0]);
    real_type t6   = inv_zeta__dot(XM__[2], XM__[1], XM__[0], t5);
    real_type t11  = ALIAS_v__fxControl_D_1(UM__[0], -1, 1);
    result__[ 0   ] = (LM__[4] * ModelPars[iM_v__fx__max] + t11) * t6;
    real_type t17  = ALIAS_v__OmegaControl_D_1(UM__[1], -1, 1);
    result__[ 1   ] = (LM__[3] * ModelPars[iM_v__Omega__max] + t17) * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DgDxlxlp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DgDxlxlp_numCols() const
  { return 20; }

  integer
  PointMassCarModel_1::DgDxlxlp_nnz() const
  { return 16; }

  void
  PointMassCarModel_1::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 19  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 2   ;
    iIndex[11] = 1   ; jIndex[11] = 8   ;
    iIndex[12] = 1   ; jIndex[12] = 10  ;
    iIndex[13] = 1   ; jIndex[13] = 11  ;
    iIndex[14] = 1   ; jIndex[14] = 12  ;
    iIndex[15] = 1   ; jIndex[15] = 18  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[11], XM__[5], LM__[5];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = XM__[2];
    real_type t2   = XM__[1];
    real_type t3   = XM__[0];
    real_type t5   = ALIAS_Kappa(QM__[0]);
    real_type t6   = inv_zeta__dot_D_3(t1, t2, t3, t5);
    real_type t8   = ModelPars[iM_v__fx__max];
    real_type t11  = ALIAS_v__fxControl_D_1(UM__[0], -1, 1);
    real_type t12  = t8 * LM__[4] + t11;
    result__[ 0   ] = 0.5e0 * t12 * t6;
    real_type t14  = inv_zeta__dot_D_2(t1, t2, t3, t5);
    result__[ 1   ] = 0.5e0 * t12 * t14;
    real_type t16  = inv_zeta__dot_D_1(t1, t2, t3, t5);
    result__[ 2   ] = 0.5e0 * t12 * t16;
    real_type t18  = inv_zeta__dot(t1, t2, t3, t5);
    result__[ 3   ] = 0.5e0 * t8 * t18;
    result__[ 4   ] = result__[0];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    real_type t21  = ModelPars[iM_v__Omega__max];
    real_type t24  = ALIAS_v__OmegaControl_D_1(UM__[1], -1, 1);
    real_type t25  = t21 * LM__[3] + t24;
    result__[ 8   ] = 0.5e0 * t25 * t6;
    result__[ 9   ] = 0.5e0 * t25 * t14;
    result__[ 10  ] = 0.5e0 * t25 * t16;
    result__[ 11  ] = 0.5e0 * t21 * t18;
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[10];
    result__[ 15  ] = result__[11];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DgDu_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DgDu_numCols() const
  { return 2; }

  integer
  PointMassCarModel_1::DgDu_nnz() const
  { return 2; }

  void
  PointMassCarModel_1::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[11], XM__[5], LM__[5];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = ALIAS_Kappa(QM__[0]);
    real_type t6   = inv_zeta__dot(XM__[2], XM__[1], XM__[0], t5);
    real_type t8   = ALIAS_v__fxControl_D_1_1(UM__[0], -1, 1);
    result__[ 0   ] = t8 * t6;
    real_type t10  = ALIAS_v__OmegaControl_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = t10 * t6;
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
  PointMassCarModel_1::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[11], XM__[5], LM__[5];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    U__[ iU_v__fx    ] = v__OmegaControl.solve(-LM__[4] * ModelPars[iM_v__fx__max], -1, 1);
    U__[ iU_v__Omega ] = v__OmegaControl.solve(-LM__[3] * ModelPars[iM_v__Omega__max], -1, 1);
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
  PointMassCarModel_1::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[11], XM__[5], LM__[5];
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
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
    real_type t2   = ModelPars[iM_v__Omega__max];
    real_type t4   = v__OmegaControl.solve_rhs(-t2 * LM__[3], -1, 1);
    real_type tmp_1_8 = -0.5e0 * t2 * t4;
    real_type t8   = ModelPars[iM_v__fx__max];
    real_type t10  = v__OmegaControl.solve_rhs(-t8 * LM__[4], -1, 1);
    real_type tmp_0_9 = -0.5e0 * t8 * t10;
    real_type tmp_1_9 = 0.0e0;
    real_type tmp_0_10 = 0.0e0;
    real_type tmp_1_10 = 0.0e0;
    real_type tmp_0_11 = 0.0e0;
    real_type tmp_1_11 = 0.0e0;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_1_12 = 0.0e0;
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
    real_type tmp_1_18 = tmp_1_8;
    real_type tmp_0_19 = tmp_0_9;
    real_type tmp_1_19 = 0.0e0;
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
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 40 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  PointMassCarModel_1::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot(t1, t2, t3, t4);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t16  = X__[iX_Omega];
    real_type t17  = t16 * t16;
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t26  = AdherenceEllipse(1 - t14 / t9 * t7 - t14 / t21 * t18 * t17);
    real_type t30  = RoadLeftBorder(Q__[iQ_leftWidth] - t3);
    real_type t34  = RoadRightBorder(Q__[iQ_rightWidth] + t3);
    real_type t43  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t6 * t1);
    real_type t45  = LimitMinSpeed(t1);
    real_type t47  = U__[iU_v__fx];
    real_type t48  = v__fxControl(t47, -1, 1);
    real_type t50  = U__[iU_v__Omega];
    real_type t51  = v__OmegaControl(t50, -1, 1);
    real_type t54  = sin(t2);
    real_type t58  = pow(-t1 * t5 * t54 + V__[0], 2);
    real_type t62  = pow(-t16 * t5 + t4 + V__[1], 2);
    real_type t69  = pow(V__[2] - (-t18 * ModelPars[iM_kD] + t6) * t5, 2);
    real_type t75  = pow(-t5 * t50 * ModelPars[iM_v__Omega__max] + V__[3], 2);
    real_type t81  = pow(-t47 * t5 * ModelPars[iM_v__fx__max] + V__[4], 2);
    real_type result__ = t26 * t5 + t30 * t5 + t34 * t5 + t43 * t5 + t45 * t5 + t48 * t5 + t5 * t51 + t58 + t62 + t69 + t75 + t81;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DmDu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = U__[iU_v__fx];
    real_type t7   = ALIAS_v__fxControl_D_1(t6, -1, 1);
    real_type t10  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t7 * t5 - 2 * t5 * t10 * (-t5 * t10 * t6 + V__[4]);
    real_type t17  = U__[iU_v__Omega];
    real_type t18  = ALIAS_v__OmegaControl_D_1(t17, -1, 1);
    real_type t21  = ModelPars[iM_v__Omega__max];
    result__[ 1   ] = t18 * t5 - 2 * t5 * t21 * (-t5 * t21 * t17 + V__[3]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DmDuu_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DmDuu_numCols() const
  { return 2; }

  integer
  PointMassCarModel_1::DmDuu_nnz() const
  { return 2; }

  void
  PointMassCarModel_1::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    real_type t10  = ModelPars[iM_v__fx__max] * ModelPars[iM_v__fx__max];
    real_type t11  = t5 * t5;
    result__[ 0   ] = 2 * t11 * t10 + t7 * t5;
    real_type t15  = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    real_type t18  = ModelPars[iM_v__Omega__max] * ModelPars[iM_v__Omega__max];
    result__[ 1   ] = 2 * t11 * t18 + t15 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: PointMassCarModel_1_Methods_controls.cc
