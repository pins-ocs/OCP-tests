/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::Hxp_numEqns() const { return 5; }

  void
  PointMassCarModel_1::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_wT];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = inv_zeta__dot_D_3(t2, t3, t4, t5);
    real_type t8   = U__[iU_v__fx];
    real_type t9   = v__fxControl(t8, -1, 1);
    real_type t11  = U__[iU_v__Omega];
    real_type t12  = v__OmegaControl(t11, -1, 1);
    real_type t14  = X__[iX_fx];
    real_type t15  = t14 * t14;
    real_type t17  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t18  = 1.0 / t17;
    real_type t21  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t22  = 1.0 / t21;
    real_type t24  = X__[iX_Omega];
    real_type t25  = t24 * t24;
    real_type t26  = t2 * t2;
    real_type t29  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t30  = 1.0 / t29;
    real_type t33  = t22 * t30 * t26 * t25 + t22 * t18 * t15 - 1;
    real_type t34  = AdherenceEllipse(t33);
    real_type t37  = t4 - Q__[iQ_leftWidth];
    real_type t38  = RoadLeftBorder(t37);
    real_type t40  = inv_zeta__dot(t2, t3, t4, t5);
    real_type t41  = ALIAS_RoadLeftBorder_D(t37);
    real_type t44  = -t4 - Q__[iQ_rightWidth];
    real_type t45  = RoadRightBorder(t44);
    real_type t47  = ALIAS_RoadRightBorder_D(t44);
    real_type t50  = ModelPars[iM_m];
    real_type t52  = 1.0 / ModelPars[iM_Pmax];
    real_type t55  = t52 * t50 * t14 * t2 - 1;
    real_type t56  = PowerLimit(t55);
    real_type t58  = LimitMinSpeed(-t2);
    real_type t60  = MU__[0];
    real_type t62  = sin(t3);
    real_type t65  = MU__[1];
    real_type t66  = t24 * t65;
    real_type t68  = MU__[2];
    real_type t70  = ModelPars[iM_kD];
    real_type t72  = -t26 * t70 + t14;
    real_type t75  = t11 * MU__[3];
    real_type t76  = ModelPars[iM_v__Omega__max];
    real_type t80  = t8 * MU__[4];
    real_type t81  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t2 * t6 * t60 * t62 + t6 * t68 * t72 + t6 * t75 * t76 + t6 * t80 * t81 + t1 * t6 + t12 * t6 + t34 * t6 + t38 * t6 + t40 * t41 - t40 * t47 + t45 * t6 + t56 * t6 + t58 * t6 + t6 * t66 + t6 * t9;
    real_type t84  = inv_zeta__dot_D_2(t2, t3, t4, t5);
    real_type t93  = cos(t3);
    real_type t96  = t62 * t2;
    result__[ 1   ] = t84 * t1 + t9 * t84 + t12 * t84 + t34 * t84 + t38 * t84 + t45 * t84 + t56 * t84 + t58 * t84 + (t2 * t40 * t93 + t84 * t96) * t60 + t84 * t66 + t72 * t84 * t68 + t84 * t76 * t75 + t84 * t81 * t80;
    real_type t107 = inv_zeta__dot_D_1(t2, t3, t4, t5);
    real_type t112 = ALIAS_AdherenceEllipse_D(t33);
    real_type t113 = t112 * t40;
    real_type t122 = ALIAS_PowerLimit_D(t55);
    real_type t123 = t122 * t40;
    real_type t128 = ALIAS_LimitMinSpeed_D(-t2);
    result__[ 2   ] = t107 * t1 + t9 * t107 + t12 * t107 + t34 * t107 + 2 * t22 * t30 * t2 * t25 * t113 + t38 * t107 + t45 * t107 + t56 * t107 + t52 * t50 * t14 * t123 + t58 * t107 - t128 * t40 + (t107 * t96 + t40 * t62) * t60 + t107 * t66 + (-2 * t2 * t40 * t70 + t107 * t72) * t68 + t107 * t76 * t75 + t107 * t81 * t80;
    result__[ 3   ] = 2 * t113 * t22 * t24 * t26 * t30 + t40 * t65;
    result__[ 4   ] = 2 * t113 * t14 * t18 * t22 + t123 * t2 * t50 * t52 + t40 * t68;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DHxpDxpuv_numRows() const { return 5; }
  integer PointMassCarModel_1::DHxpDxpuv_numCols() const { return 12; }
  integer PointMassCarModel_1::DHxpDxpuv_nnz()     const { return 31; }

  void
  PointMassCarModel_1::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 4   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
    iIndex[21] = 3   ; jIndex[21] = 0   ;
    iIndex[22] = 3   ; jIndex[22] = 1   ;
    iIndex[23] = 3   ; jIndex[23] = 2   ;
    iIndex[24] = 3   ; jIndex[24] = 3   ;
    iIndex[25] = 3   ; jIndex[25] = 4   ;
    iIndex[26] = 4   ; jIndex[26] = 0   ;
    iIndex[27] = 4   ; jIndex[27] = 1   ;
    iIndex[28] = 4   ; jIndex[28] = 2   ;
    iIndex[29] = 4   ; jIndex[29] = 3   ;
    iIndex[30] = 4   ; jIndex[30] = 4   ;
  }


  void
  PointMassCarModel_1::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_wT];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = inv_zeta__dot_D_3_3(t2, t3, t4, t5);
    real_type t8   = U__[iU_v__fx];
    real_type t9   = v__fxControl(t8, -1, 1);
    real_type t11  = U__[iU_v__Omega];
    real_type t12  = v__OmegaControl(t11, -1, 1);
    real_type t14  = X__[iX_fx];
    real_type t15  = t14 * t14;
    real_type t17  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t18  = 1.0 / t17;
    real_type t21  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t22  = 1.0 / t21;
    real_type t24  = X__[iX_Omega];
    real_type t25  = t24 * t24;
    real_type t26  = t2 * t2;
    real_type t29  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t30  = 1.0 / t29;
    real_type t33  = t22 * t30 * t26 * t25 + t22 * t18 * t15 - 1;
    real_type t34  = AdherenceEllipse(t33);
    real_type t37  = t4 - Q__[iQ_leftWidth];
    real_type t38  = RoadLeftBorder(t37);
    real_type t40  = inv_zeta__dot_D_3(t2, t3, t4, t5);
    real_type t41  = ALIAS_RoadLeftBorder_D(t37);
    real_type t44  = inv_zeta__dot(t2, t3, t4, t5);
    real_type t45  = ALIAS_RoadLeftBorder_DD(t37);
    real_type t48  = -t4 - Q__[iQ_rightWidth];
    real_type t49  = RoadRightBorder(t48);
    real_type t51  = ALIAS_RoadRightBorder_D(t48);
    real_type t54  = ALIAS_RoadRightBorder_DD(t48);
    real_type t57  = ModelPars[iM_m];
    real_type t58  = ModelPars[iM_Pmax];
    real_type t59  = 1.0 / t58;
    real_type t60  = t59 * t57;
    real_type t62  = t60 * t14 * t2 - 1;
    real_type t63  = PowerLimit(t62);
    real_type t65  = LimitMinSpeed(-t2);
    real_type t67  = MU__[0];
    real_type t68  = t2 * t67;
    real_type t69  = sin(t3);
    real_type t72  = MU__[1];
    real_type t73  = t24 * t72;
    real_type t75  = MU__[2];
    real_type t77  = ModelPars[iM_kD];
    real_type t79  = -t26 * t77 + t14;
    real_type t81  = MU__[3];
    real_type t82  = t11 * t81;
    real_type t83  = ModelPars[iM_v__Omega__max];
    real_type t86  = MU__[4];
    real_type t87  = t8 * t86;
    real_type t88  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t6 * t69 * t68 + t79 * t6 * t75 + t6 * t83 * t82 + t6 * t88 * t87 + t6 * t1 + t12 * t6 + t34 * t6 + t38 * t6 + 2 * t41 * t40 - 2 * t51 * t40 + t45 * t44 + t54 * t44 + t49 * t6 + t63 * t6 + t65 * t6 + t6 * t73 + t9 * t6;
    real_type t91  = inv_zeta__dot_D_2_3(t2, t3, t4, t5);
    real_type t92  = t91 * t1;
    real_type t93  = t9 * t91;
    real_type t94  = t12 * t91;
    real_type t95  = t34 * t91;
    real_type t96  = t38 * t91;
    real_type t97  = inv_zeta__dot_D_2(t2, t3, t4, t5);
    real_type t98  = t41 * t97;
    real_type t99  = t49 * t91;
    real_type t100 = t51 * t97;
    real_type t101 = t63 * t91;
    real_type t102 = t65 * t91;
    real_type t103 = cos(t3);
    real_type t108 = t91 * t73;
    real_type t110 = t79 * t91 * t75;
    real_type t112 = t91 * t83 * t82;
    real_type t114 = t91 * t88 * t87;
    result__[ 1   ] = t40 * t103 * t68 + t91 * t69 * t68 - t100 + t101 + t102 + t108 + t110 + t112 + t114 + t92 + t93 + t94 + t95 + t96 + t98 + t99;
    real_type t115 = inv_zeta__dot_D_1_3(t2, t3, t4, t5);
    real_type t116 = t115 * t1;
    real_type t117 = t9 * t115;
    real_type t118 = t12 * t115;
    real_type t119 = t34 * t115;
    real_type t120 = ALIAS_AdherenceEllipse_D(t33);
    real_type t121 = t120 * t40;
    real_type t123 = t30 * t2;
    real_type t124 = t22 * t123;
    real_type t126 = 2 * t124 * t25 * t121;
    real_type t127 = t38 * t115;
    real_type t128 = inv_zeta__dot_D_1(t2, t3, t4, t5);
    real_type t129 = t41 * t128;
    real_type t130 = t49 * t115;
    real_type t131 = t51 * t128;
    real_type t132 = t63 * t115;
    real_type t133 = ALIAS_PowerLimit_D(t62);
    real_type t134 = t133 * t40;
    real_type t136 = t59 * t57 * t14;
    real_type t137 = t136 * t134;
    real_type t138 = t65 * t115;
    real_type t139 = ALIAS_LimitMinSpeed_D(-t2);
    real_type t140 = t139 * t40;
    real_type t145 = t115 * t73;
    real_type t148 = t40 * t75;
    real_type t149 = t2 * t77;
    real_type t153 = t115 * t83 * t82;
    real_type t155 = t115 * t88 * t87;
    result__[ 2   ] = t115 * t68 * t69 + t115 * t75 * t79 + t40 * t67 * t69 - 2 * t148 * t149 + t116 + t117 + t118 + t119 + t126 + t127 + t129 + t130 - t131 + t132 + t137 + t138 - t140 + t145 + t153 + t155;
    real_type t157 = t30 * t26;
    real_type t158 = t22 * t157;
    result__[ 3   ] = 2 * t121 * t158 * t24 + t40 * t72;
    real_type t162 = t18 * t14;
    real_type t163 = t22 * t162;
    real_type t167 = t59 * t57 * t2;
    result__[ 4   ] = 2 * t121 * t163 + t134 * t167 + t148;
    real_type t169 = ALIAS_v__fxControl_D_1(t8, -1, 1);
    real_type t171 = t88 * t86;
    result__[ 5   ] = t169 * t40 + t171 * t40;
    real_type t173 = ALIAS_v__OmegaControl_D_1(t11, -1, 1);
    real_type t175 = t83 * t81;
    result__[ 6   ] = t173 * t40 + t175 * t40;
    real_type t177 = t103 * t2;
    real_type t179 = t69 * t2;
    result__[ 7   ] = t92 + t93 + t94 + t95 + t96 + t98 + t99 - t100 + t101 + t102 + (t177 * t40 + t179 * t91) * t67 + t108 + t110 + t112 + t114;
    real_type t183 = inv_zeta__dot_D_2_2(t2, t3, t4, t5);
    result__[ 8   ] = t183 * t1 + t9 * t183 + t12 * t183 + t34 * t183 + t38 * t183 + t49 * t183 + t63 * t183 + t65 * t183 + (2 * t177 * t97 + t179 * t183 - t179 * t44) * t67 + t183 * t73 + t79 * t183 * t75 + t183 * t83 * t82 + t183 * t88 * t87;
    real_type t205 = inv_zeta__dot_D_1_2(t2, t3, t4, t5);
    real_type t206 = t205 * t1;
    real_type t207 = t9 * t205;
    real_type t208 = t12 * t205;
    real_type t209 = t34 * t205;
    real_type t210 = t120 * t97;
    real_type t213 = 2 * t124 * t25 * t210;
    real_type t214 = t38 * t205;
    real_type t215 = t49 * t205;
    real_type t216 = t63 * t205;
    real_type t217 = t133 * t97;
    real_type t218 = t136 * t217;
    real_type t219 = t65 * t205;
    real_type t220 = t139 * t97;
    real_type t226 = (t103 * t44 + t128 * t177 + t179 * t205 + t69 * t97) * t67;
    real_type t227 = t205 * t73;
    real_type t230 = t97 * t75;
    real_type t234 = t205 * t83 * t82;
    real_type t236 = t205 * t88 * t87;
    result__[ 9   ] = t205 * t75 * t79 - 2 * t149 * t230 + t206 + t207 + t208 + t209 + t213 + t214 + t215 + t216 + t218 + t219 - t220 + t226 + t227 + t234 + t236;
    result__[ 10  ] = 2 * t158 * t210 * t24 + t72 * t97;
    result__[ 11  ] = 2 * t163 * t210 + t167 * t217 + t230;
    result__[ 12  ] = t169 * t97 + t171 * t97;
    result__[ 13  ] = t173 * t97 + t175 * t97;
    result__[ 14  ] = t116 + t117 + t118 + t119 + t126 + t127 + t129 + t130 - t131 + t132 + t137 + t138 - t140 + (t115 * t179 + t40 * t69) * t67 + t145 + (-2 * t2 * t40 * t77 + t115 * t79) * t75 + t153 + t155;
    result__[ 15  ] = t206 + t207 + t208 + t209 + t213 + t214 + t215 + t216 + t218 + t219 - t220 + t226 + t227 + (-2 * t2 * t77 * t97 + t205 * t79) * t75 + t234 + t236;
    real_type t264 = inv_zeta__dot_D_1_1(t2, t3, t4, t5);
    real_type t269 = t120 * t128;
    real_type t273 = ALIAS_AdherenceEllipse_DD(t33);
    real_type t274 = t273 * t44;
    real_type t275 = t25 * t25;
    real_type t277 = t29 * t29;
    real_type t278 = 1.0 / t277;
    real_type t280 = t21 * t21;
    real_type t281 = 1.0 / t280;
    real_type t285 = t120 * t44;
    real_type t293 = t133 * t128;
    real_type t296 = ALIAS_PowerLimit_DD(t62);
    real_type t297 = t296 * t44;
    real_type t298 = t57 * t57;
    real_type t300 = t58 * t58;
    real_type t301 = 1.0 / t300;
    real_type t307 = ALIAS_LimitMinSpeed_DD(-t2);
    result__[ 16  ] = t264 * t1 + t9 * t264 + t12 * t264 + t34 * t264 + 4 * t124 * t25 * t269 + 4 * t281 * t278 * t26 * t275 * t274 + 2 * t22 * t30 * t25 * t285 + t38 * t264 + t49 * t264 + t63 * t264 + 2 * t136 * t293 + t301 * t298 * t15 * t297 + t65 * t264 - 2 * t139 * t128 + t307 * t44 + (2 * t128 * t69 + t179 * t264) * t67 + t264 * t73 + (-4 * t128 * t2 * t77 + t264 * t79 - 2 * t44 * t77) * t75 + t264 * t83 * t82 + t264 * t88 * t87;
    result__[ 17  ] = 4 * t2 * t24 * t25 * t26 * t274 * t278 * t281 + 4 * t124 * t24 * t285 + 2 * t158 * t24 * t269 + t128 * t72;
    real_type t343 = t162 * t274;
    result__[ 18  ] = t14 * t2 * t297 * t298 * t301 + 4 * t123 * t25 * t281 * t343 + t133 * t44 * t60 + t128 * t75 + 2 * t163 * t269 + t167 * t293;
    result__[ 19  ] = t128 * t169 + t128 * t171;
    result__[ 20  ] = t128 * t173 + t128 * t175;
    result__[ 21  ] = result__[3];
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[17];
    real_type t361 = t26 * t26;
    result__[ 24  ] = 4 * t25 * t274 * t278 * t281 * t361 + 2 * t158 * t285;
    result__[ 25  ] = 4 * t157 * t24 * t281 * t343;
    result__[ 26  ] = result__[4];
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[18];
    result__[ 29  ] = result__[25];
    real_type t371 = t17 * t17;
    result__[ 30  ] = 4 * t281 / t371 * t15 * t274 + 2 * t22 * t18 * t285 + t301 * t298 * t26 * t297;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 31, i_segment );
  }

}

// EOF: PointMassCarModel_1_Methods_AdjointODE.cc
