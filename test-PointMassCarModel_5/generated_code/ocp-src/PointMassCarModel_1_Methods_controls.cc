/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
#pragma warning( disable : 4189 )
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
    real_type t1   = LM__[0];
    real_type t2   = XL__[iX_V];
    real_type t4   = XL__[iX_alpha];
    real_type t5   = sin(t4);
    real_type t6   = XL__[iX_n];
    real_type t7   = QL__[iQ_Kappa];
    real_type t8   = inv_zeta__dot(t2, t4, t6, t7);
    real_type t11  = XR__[iX_V];
    real_type t13  = XR__[iX_alpha];
    real_type t14  = sin(t13);
    real_type t15  = XR__[iX_n];
    real_type t16  = QR__[iQ_Kappa];
    real_type t17  = inv_zeta__dot(t11, t13, t15, t16);
    real_type t21  = UM__[1];
    real_type t22  = t21 * LM__[3];
    real_type t23  = ModelPars[iM_v__Omega__max];
    real_type t29  = UM__[0];
    real_type t30  = t29 * LM__[4];
    real_type t31  = ModelPars[iM_v__fx__max];
    real_type t36  = LM__[2];
    real_type t38  = t2 * t2;
    real_type t39  = ModelPars[iM_kD];
    real_type t41  = XL__[iX_fx];
    real_type t45  = t11 * t11;
    real_type t47  = XR__[iX_fx];
    real_type t50  = LimitMinSpeed(-t2);
    real_type t54  = RoadLeftBorder(t6 - QL__[iQ_leftWidth]);
    real_type t58  = RoadRightBorder(-t6 - QL__[iQ_rightWidth]);
    real_type t60  = LimitMinSpeed(-t11);
    real_type t64  = RoadLeftBorder(t15 - QR__[iQ_leftWidth]);
    real_type t66  = t8 * t5 * t2 * t1 + t17 * t14 * t11 * t1 + t8 * t23 * t22 + t17 * t23 * t22 + t8 * t31 * t30 + t17 * t31 * t30 + (-t38 * t39 + t41) * t8 * t36 + (-t39 * t45 + t47) * t17 * t36 + t50 * t8 + t54 * t8 + t58 * t8 + t60 * t17 + t64 * t17;
    real_type t69  = RoadRightBorder(-t15 - QR__[iQ_rightWidth]);
    real_type t71  = LM__[1];
    real_type t72  = XL__[iX_Omega];
    real_type t76  = XR__[iX_Omega];
    real_type t80  = v__fxControl(t29, -1, 1);
    real_type t83  = v__OmegaControl(t21, -1, 1);
    real_type t90  = ModelPars[iM_m] / ModelPars[iM_Pmax];
    real_type t93  = PowerLimit(t2 * t41 * t90 - 1);
    real_type t98  = PowerLimit(t11 * t47 * t90 - 1);
    real_type t100 = ModelPars[iM_wT];
    real_type t103 = t41 * t41;
    real_type t105 = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t106 = 1.0 / t105;
    real_type t109 = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t110 = 1.0 / t109;
    real_type t112 = t72 * t72;
    real_type t115 = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t117 = t110 / t115;
    real_type t120 = AdherenceEllipse(t103 * t106 * t110 + t112 * t117 * t38 - 1);
    real_type t122 = t47 * t47;
    real_type t125 = t76 * t76;
    real_type t129 = AdherenceEllipse(t106 * t110 * t122 + t117 * t125 * t45 - 1);
    real_type t131 = t69 * t17 + (t72 * t8 - t7) * t71 + (t17 * t76 - t16) * t71 + t80 * t8 + t80 * t17 + t83 * t8 + t83 * t17 + t93 * t8 + t98 * t17 + t8 * t100 + t17 * t100 + t120 * t8 + t129 * t17;
    real_type result__ = t66 + t131;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::g_numEqns() const { return 2; }

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
    real_type t3   = LM__[4] * ModelPars[iM_v__fx__max];
    real_type t8   = inv_zeta__dot(XL__[iX_V], XL__[iX_alpha], XL__[iX_n], QL__[iQ_Kappa]);
    real_type t11  = ALIAS_v__fxControl_D_1(UM__[0], -1, 1);
    real_type t17  = inv_zeta__dot(XR__[iX_V], XR__[iX_alpha], XR__[iX_n], QR__[iQ_Kappa]);
    result__[ 0   ] = t11 * t17 + t11 * t8 + t17 * t3 + t8 * t3;
    real_type t22  = LM__[3] * ModelPars[iM_v__Omega__max];
    real_type t25  = ALIAS_v__OmegaControl_D_1(UM__[1], -1, 1);
    result__[ 1   ] = t17 * t22 + t25 * t17 + t8 * t22 + t25 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DgDxlxlp_numRows() const { return 2; }
  integer PointMassCarModel_1::DgDxlxlp_numCols() const { return 20; }
  integer PointMassCarModel_1::DgDxlxlp_nnz()     const { return 16; }

  void
  PointMassCarModel_1::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
    real_type t2   = ModelPars[iM_v__fx__max];
    real_type t3   = t2 * LM__[4];
    real_type t4   = XL__[iX_V];
    real_type t5   = XL__[iX_alpha];
    real_type t6   = XL__[iX_n];
    real_type t7   = QL__[iQ_Kappa];
    real_type t8   = inv_zeta__dot_D_3(t4, t5, t6, t7);
    real_type t11  = ALIAS_v__fxControl_D_1(UM__[0], -1, 1);
    result__[ 0   ] = t11 * t8 + t3 * t8;
    real_type t13  = inv_zeta__dot_D_2(t4, t5, t6, t7);
    result__[ 1   ] = t11 * t13 + t13 * t3;
    real_type t16  = inv_zeta__dot_D_1(t4, t5, t6, t7);
    result__[ 2   ] = t11 * t16 + t16 * t3;
    real_type t19  = inv_zeta__dot(t4, t5, t6, t7);
    real_type t22  = XR__[iX_V];
    real_type t23  = XR__[iX_alpha];
    real_type t24  = XR__[iX_n];
    real_type t25  = QR__[iQ_Kappa];
    real_type t26  = inv_zeta__dot(t22, t23, t24, t25);
    result__[ 3   ] = 0.5e0 * t19 * t2 + 0.5e0 * t26 * t2;
    real_type t29  = inv_zeta__dot_D_3(t22, t23, t24, t25);
    result__[ 4   ] = t11 * t29 + t29 * t3;
    real_type t32  = inv_zeta__dot_D_2(t22, t23, t24, t25);
    result__[ 5   ] = t11 * t32 + t3 * t32;
    real_type t35  = inv_zeta__dot_D_1(t22, t23, t24, t25);
    result__[ 6   ] = t11 * t35 + t3 * t35;
    result__[ 7   ] = result__[3];
    real_type t39  = ModelPars[iM_v__Omega__max];
    real_type t40  = t39 * LM__[3];
    real_type t43  = ALIAS_v__OmegaControl_D_1(UM__[1], -1, 1);
    result__[ 8   ] = t40 * t8 + t43 * t8;
    result__[ 9   ] = t13 * t40 + t13 * t43;
    result__[ 10  ] = t16 * t40 + t16 * t43;
    result__[ 11  ] = 0.5e0 * t19 * t39 + 0.5e0 * t26 * t39;
    result__[ 12  ] = t29 * t40 + t29 * t43;
    result__[ 13  ] = t32 * t40 + t32 * t43;
    result__[ 14  ] = t35 * t40 + t35 * t43;
    result__[ 15  ] = result__[11];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DgDu_numRows() const { return 2; }
  integer PointMassCarModel_1::DgDu_numCols() const { return 2; }
  integer PointMassCarModel_1::DgDu_nnz()     const { return 2; }

  void
  PointMassCarModel_1::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    real_type t5   = inv_zeta__dot(XL__[iX_V], XL__[iX_alpha], XL__[iX_n], QL__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1_1(UM__[0], -1, 1);
    real_type t13  = inv_zeta__dot(XR__[iX_V], XR__[iX_alpha], XR__[iX_n], QR__[iQ_Kappa]);
    result__[ 0   ] = t7 * t13 + t7 * t5;
    real_type t16  = ALIAS_v__OmegaControl_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = t16 * t13 + t16 * t5;
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
    real_type t6   = U__[iU_v__fx];
    real_type t7   = v__fxControl(t6, -1, 1);
    real_type t9   = U__[iU_v__Omega];
    real_type t10  = v__OmegaControl(t9, -1, 1);
    real_type t12  = X__[iX_fx];
    real_type t13  = t12 * t12;
    real_type t15  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t19  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t20  = 1.0 / t19;
    real_type t22  = X__[iX_Omega];
    real_type t23  = t22 * t22;
    real_type t24  = t1 * t1;
    real_type t27  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t32  = AdherenceEllipse(t20 / t15 * t13 + t20 / t27 * t24 * t23 - 1);
    real_type t36  = RoadLeftBorder(t3 - Q__[iQ_leftWidth]);
    real_type t40  = RoadRightBorder(-t3 - Q__[iQ_rightWidth]);
    real_type t49  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t12 * t1 - 1);
    real_type t51  = LimitMinSpeed(-t1);
    real_type t54  = sin(t2);
    real_type t58  = pow(-t5 * t54 * t1 + V__[0], 2);
    real_type t62  = pow(-t5 * t22 + t4 + V__[1], 2);
    real_type t69  = pow(V__[2] - (-t24 * ModelPars[iM_kD] + t12) * t5, 2);
    real_type t75  = pow(-t5 * ModelPars[iM_v__Omega__max] * t9 + V__[3], 2);
    real_type t81  = pow(-t5 * ModelPars[iM_v__fx__max] * t6 + V__[4], 2);
    real_type result__ = t10 * t5 + t32 * t5 + t36 * t5 + t40 * t5 + t49 * t5 + t51 * t5 + t7 * t5 + t58 + t62 + t69 + t75 + t81;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::DmDu_numEqns() const { return 2; }

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
  integer PointMassCarModel_1::DmDuu_numRows() const { return 2; }
  integer PointMassCarModel_1::DmDuu_numCols() const { return 2; }
  integer PointMassCarModel_1::DmDuu_nnz()     const { return 2; }

  void
  PointMassCarModel_1::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


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
