/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_controls.cc                        |
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


#include "PointMassCarModel_2.hh"
#include "PointMassCarModel_2_Pars.hh"

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


namespace PointMassCarModel_2Define {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  PointMassCarModel_2::g_fun_eval(
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
    real_type t2   = XM__[2];
    real_type t3   = XM__[1];
    real_type t4   = XM__[0];
    real_type t5   = QM__[0];
    real_type t6   = ALIAS_Kappa(t5);
    real_type t7   = zeta__dot(t2, t3, t4, t6);
    real_type t8   = 1.0 / t7;
    real_type t12  = sin(t3);
    real_type t15  = XM__[3];
    real_type t20  = t2 * t2;
    real_type t23  = XM__[4];
    real_type t27  = UM__[0];
    real_type t32  = UM__[1];
    real_type t36  = v__fxControl(t27, -1, 1);
    real_type t38  = v__OmegaControl(t32, -1, 1);
    real_type t40  = t23 * t23;
    real_type t42  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t46  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t47  = 1.0 / t46;
    real_type t49  = t15 * t15;
    real_type t52  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t57  = AdherenceEllipse(t47 / t42 * t40 + t47 / t52 * t20 * t49 - 1);
    real_type t59  = ALIAS_leftWidth(t5);
    real_type t61  = RoadLeftBorder(t4 - t59);
    real_type t63  = ALIAS_rightWidth(t5);
    real_type t65  = RoadRightBorder(-t4 - t63);
    real_type t74  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t23 * t2 - 1);
    real_type t76  = LimitMinSpeed(-t2);
    real_type result__ = t8 * ModelPars[iM_wT] + t12 * t2 * LM__[0] + (-t7 * t6 + t15) * LM__[1] + (-t20 * ModelPars[iM_kD] + t23) * LM__[2] + ModelPars[iM_v__fx__max] * t27 * LM__[3] + ModelPars[iM_v__Omega__max] * t32 * LM__[4] + t36 * t8 + t38 * t8 + t57 * t8 + t61 * t8 + t65 * t8 + t74 * t8 + t76 * t8;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::g_numEqns() const { return 2; }

  void
  PointMassCarModel_2::g_eval(
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
    real_type t8   = ALIAS_Kappa(QM__[0]);
    real_type t9   = zeta__dot(XM__[2], XM__[1], XM__[0], t8);
    real_type t10  = 1.0 / t9;
    real_type t12  = ALIAS_v__fxControl_D_1(UM__[0], -1, 1);
    result__[ 0   ] = t12 * t10 + LM__[3] * ModelPars[iM_v__fx__max];
    real_type t18  = ALIAS_v__OmegaControl_D_1(UM__[1], -1, 1);
    result__[ 1   ] = t18 * t10 + LM__[4] * ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DgDxlxlp_numRows() const { return 2; }
  integer PointMassCarModel_2::DgDxlxlp_numCols() const { return 20; }
  integer PointMassCarModel_2::DgDxlxlp_nnz()     const { return 16; }

  void
  PointMassCarModel_2::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 18  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 2   ;
    iIndex[11] = 1   ; jIndex[11] = 9   ;
    iIndex[12] = 1   ; jIndex[12] = 10  ;
    iIndex[13] = 1   ; jIndex[13] = 11  ;
    iIndex[14] = 1   ; jIndex[14] = 12  ;
    iIndex[15] = 1   ; jIndex[15] = 19  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DgDxlxlp_sparse(
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
    real_type t6   = zeta__dot(t1, t2, t3, t5);
    real_type t7   = t6 * t6;
    real_type t8   = 1.0 / t7;
    real_type t10  = ALIAS_v__fxControl_D_1(UM__[0], -1, 1);
    real_type t11  = t10 * t8;
    real_type t12  = zeta__dot_D_3(t1, t2, t3, t5);
    result__[ 0   ] = -0.5e0 * t12 * t11;
    real_type t15  = zeta__dot_D_2(t1, t2, t3, t5);
    result__[ 1   ] = -0.5e0 * t15 * t11;
    real_type t18  = zeta__dot_D_1(t1, t2, t3, t5);
    result__[ 2   ] = -0.5e0 * t18 * t11;
    result__[ 3   ] = 0.5e0 * ModelPars[iM_v__fx__max];
    result__[ 4   ] = result__[0];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    real_type t23  = ALIAS_v__OmegaControl_D_1(UM__[1], -1, 1);
    real_type t24  = t23 * t8;
    result__[ 8   ] = -0.5e0 * t12 * t24;
    result__[ 9   ] = -0.5e0 * t15 * t24;
    result__[ 10  ] = -0.5e0 * t18 * t24;
    result__[ 11  ] = 0.5e0 * ModelPars[iM_v__Omega__max];
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[10];
    result__[ 15  ] = result__[11];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DgDu_numRows() const { return 2; }
  integer PointMassCarModel_2::DgDu_numCols() const { return 2; }
  integer PointMassCarModel_2::DgDu_nnz()     const { return 2; }

  void
  PointMassCarModel_2::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DgDu_sparse(
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
    real_type t6   = zeta__dot(XM__[2], XM__[1], XM__[0], t5);
    real_type t7   = 1.0 / t6;
    real_type t9   = ALIAS_v__fxControl_D_1_1(UM__[0], -1, 1);
    result__[ 0   ] = t9 * t7;
    real_type t11  = ALIAS_v__OmegaControl_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = t11 * t7;
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
  PointMassCarModel_2::u_eval_analytic(
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
    real_type t8   = ALIAS_Kappa(QM__[0]);
    real_type t9   = zeta__dot(XM__[2], XM__[1], XM__[0], t8);
    U__[ iU_v__fx    ] = v__OmegaControl.solve(-t9 * ModelPars[iM_v__fx__max] * LM__[3], -1, 1);
    U__[ iU_v__Omega ] = v__OmegaControl.solve(-t9 * ModelPars[iM_v__Omega__max] * LM__[4], -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  PointMassCarModel_2::m_eval(
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = 1.0 / t5;
    real_type t7   = U__[iU_v__fx];
    real_type t8   = v__fxControl(t7, -1, 1);
    real_type t10  = U__[iU_v__Omega];
    real_type t11  = v__OmegaControl(t10, -1, 1);
    real_type t13  = X__[iX_fx];
    real_type t14  = t13 * t13;
    real_type t16  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t20  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t21  = 1.0 / t20;
    real_type t23  = X__[iX_Omega];
    real_type t24  = t23 * t23;
    real_type t25  = t1 * t1;
    real_type t28  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t33  = AdherenceEllipse(t21 / t16 * t14 + t21 / t28 * t25 * t24 - 1);
    real_type t37  = RoadLeftBorder(t3 - Q__[iQ_leftWidth]);
    real_type t41  = RoadRightBorder(-t3 - Q__[iQ_rightWidth]);
    real_type t50  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t13 * t1 - 1);
    real_type t52  = LimitMinSpeed(-t1);
    real_type t56  = sin(t2);
    real_type t59  = pow(-t56 * t1 + V__[0] * t5, 2);
    real_type t64  = pow(t5 * t4 + V__[1] * t5 - t23, 2);
    real_type t70  = pow(t25 * ModelPars[iM_kD] + V__[2] * t5 - t13, 2);
    real_type t76  = pow(V__[4] * t5 - ModelPars[iM_v__fx__max] * t7, 2);
    real_type t82  = pow(-ModelPars[iM_v__Omega__max] * t10 + V__[3] * t5, 2);
    real_type result__ = t11 * t6 + t33 * t6 + t37 * t6 + t41 * t6 + t50 * t6 + t52 * t6 + t8 * t6 + t59 + t64 + t70 + t76 + t82;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::DmDu_numEqns() const { return 2; }

  void
  PointMassCarModel_2::DmDu_eval(
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
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t7   = U__[iU_v__fx];
    real_type t8   = ALIAS_v__fxControl_D_1(t7, -1, 1);
    real_type t12  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t8 * t6 - 2 * t12 * (-t12 * t7 + V__[4] * t5);
    real_type t17  = U__[iU_v__Omega];
    real_type t18  = ALIAS_v__OmegaControl_D_1(t17, -1, 1);
    real_type t22  = ModelPars[iM_v__Omega__max];
    result__[ 1   ] = t18 * t6 - 2 * t22 * (-t22 * t17 + V__[3] * t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DmDuu_numRows() const { return 2; }
  integer PointMassCarModel_2::DmDuu_numCols() const { return 2; }
  integer PointMassCarModel_2::DmDuu_nnz()     const { return 2; }

  void
  PointMassCarModel_2::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  PointMassCarModel_2::DmDuu_sparse(
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
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    real_type t11  = ModelPars[iM_v__fx__max] * ModelPars[iM_v__fx__max];
    result__[ 0   ] = t8 * t6 + 2 * t11;
    real_type t14  = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    real_type t17  = ModelPars[iM_v__Omega__max] * ModelPars[iM_v__Omega__max];
    result__[ 1   ] = t14 * t6 + 2 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_controls.cc
