/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


namespace PointMassCarModel_2Define {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::Hxp_numEqns() const { return 5; }

  void
  PointMassCarModel_2::Hxp_eval(
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
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = Q__[iQ_Kappa];
    real_type t6   = zeta__dot(t2, t3, t4, t5);
    real_type t7   = t6 * t6;
    real_type t8   = 1.0 / t7;
    real_type t9   = t8 * ModelPars[iM_wT];
    real_type t10  = zeta__dot_D_3(t2, t3, t4, t5);
    real_type t13  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t14  = t13 * t8;
    real_type t17  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t18  = t17 * t8;
    real_type t20  = X__[iX_fx];
    real_type t21  = t20 * t20;
    real_type t23  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t24  = 1.0 / t23;
    real_type t27  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t28  = 1.0 / t27;
    real_type t30  = X__[iX_Omega];
    real_type t31  = t30 * t30;
    real_type t32  = t2 * t2;
    real_type t35  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t36  = 1.0 / t35;
    real_type t39  = t28 * t36 * t32 * t31 + t28 * t24 * t21 - 1;
    real_type t40  = AdherenceEllipse(t39);
    real_type t41  = t40 * t8;
    real_type t44  = t4 - Q__[iQ_leftWidth];
    real_type t45  = RoadLeftBorder(t44);
    real_type t46  = t45 * t8;
    real_type t48  = 1.0 / t6;
    real_type t49  = ALIAS_RoadLeftBorder_D(t44);
    real_type t52  = -t4 - Q__[iQ_rightWidth];
    real_type t53  = RoadRightBorder(t52);
    real_type t54  = t53 * t8;
    real_type t56  = ALIAS_RoadRightBorder_D(t52);
    real_type t59  = ModelPars[iM_m];
    real_type t61  = 1.0 / ModelPars[iM_Pmax];
    real_type t64  = t61 * t59 * t20 * t2 - 1;
    real_type t65  = PowerLimit(t64);
    real_type t66  = t65 * t8;
    real_type t68  = LimitMinSpeed(-t2);
    real_type t69  = t68 * t8;
    real_type t71  = MU__[0];
    real_type t73  = V__[0];
    real_type t75  = MU__[1];
    real_type t77  = V__[1];
    real_type t81  = MU__[2];
    real_type t83  = V__[2];
    real_type t85  = MU__[3];
    real_type t87  = V__[4];
    real_type t89  = MU__[4];
    real_type t91  = V__[3];
    result__[ 0   ] = -t10 * t9 - t10 * t14 - t10 * t18 - t10 * t41 - t10 * t46 + t49 * t48 - t10 * t54 - t56 * t48 - t10 * t66 - t10 * t69 - t73 * t10 * t71 + (-t10 * t5 - t10 * t77) * t75 - t83 * t10 * t81 - t87 * t10 * t85 - t91 * t10 * t89;
    real_type t93  = zeta__dot_D_2(t2, t3, t4, t5);
    real_type t102 = cos(t3);
    result__[ 1   ] = -t93 * t9 - t93 * t14 - t93 * t18 - t93 * t41 - t93 * t46 - t93 * t54 - t93 * t66 - t93 * t69 + (t102 * t2 - t73 * t93) * t71 + (-t5 * t93 - t77 * t93) * t75 - t83 * t93 * t81 - t87 * t93 * t85 - t91 * t93 * t89;
    real_type t117 = zeta__dot_D_1(t2, t3, t4, t5);
    real_type t122 = ALIAS_AdherenceEllipse_D(t39);
    real_type t123 = t122 * t48;
    real_type t132 = ALIAS_PowerLimit_D(t64);
    real_type t133 = t132 * t48;
    real_type t138 = ALIAS_LimitMinSpeed_D(-t2);
    real_type t140 = sin(t3);
    result__[ 2   ] = -t117 * t9 - t117 * t14 - t117 * t18 - t117 * t41 + 2 * t28 * t36 * t2 * t31 * t123 - t117 * t46 - t117 * t54 - t117 * t66 + t61 * t59 * t20 * t133 - t117 * t69 - t138 * t48 + (-t117 * t73 + t140) * t71 + (-t117 * t5 - t117 * t77) * t75 + (-t117 * t83 - 2 * t2 * ModelPars[iM_kD]) * t81 - t87 * t117 * t85 - t91 * t117 * t89;
    result__[ 3   ] = 2 * t123 * t28 * t30 * t32 * t36 + t75;
    result__[ 4   ] = 2 * t123 * t20 * t24 * t28 + t133 * t2 * t59 * t61 + t81;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DHxpDxpuv_numRows() const { return 5; }
  integer PointMassCarModel_2::DHxpDxpuv_numCols() const { return 12; }
  integer PointMassCarModel_2::DHxpDxpuv_nnz()     const { return 46; }

  void
  PointMassCarModel_2::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[39] = 3   ; jIndex[39] = 3   ;
    iIndex[40] = 3   ; jIndex[40] = 4   ;
    iIndex[41] = 4   ; jIndex[41] = 0   ;
    iIndex[42] = 4   ; jIndex[42] = 1   ;
    iIndex[43] = 4   ; jIndex[43] = 2   ;
    iIndex[44] = 4   ; jIndex[44] = 3   ;
    iIndex[45] = 4   ; jIndex[45] = 4   ;
  }


  void
  PointMassCarModel_2::DHxpDxpuv_sparse(
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
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t8   = 1.0 / t6 / t5;
    real_type t9   = LimitMinSpeed(-t1);
    real_type t10  = t8 * t9;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_wT];
    real_type t16  = t8 * t15;
    real_type t20  = t3 - Q__[iQ_leftWidth];
    real_type t21  = RoadLeftBorder(t20);
    real_type t22  = t21 * t8;
    real_type t26  = -t3 - Q__[iQ_rightWidth];
    real_type t27  = RoadRightBorder(t26);
    real_type t28  = t27 * t8;
    real_type t31  = X__[iX_fx];
    real_type t33  = ModelPars[iM_m];
    real_type t34  = ModelPars[iM_Pmax];
    real_type t36  = 1.0 / t34 * t33;
    real_type t38  = t1 * t31 * t36 - 1;
    real_type t39  = PowerLimit(t38);
    real_type t40  = t39 * t8;
    real_type t43  = t31 * t31;
    real_type t45  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t46  = 1.0 / t45;
    real_type t49  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t50  = 1.0 / t49;
    real_type t52  = X__[iX_Omega];
    real_type t53  = t52 * t52;
    real_type t54  = t1 * t1;
    real_type t57  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t58  = 1.0 / t57;
    real_type t61  = t50 * t53 * t54 * t58 + t43 * t46 * t50 - 1;
    real_type t62  = AdherenceEllipse(t61);
    real_type t63  = t62 * t8;
    real_type t66  = U__[iU_v__fx];
    real_type t67  = v__fxControl(t66, -1, 1);
    real_type t68  = t67 * t8;
    real_type t71  = U__[iU_v__Omega];
    real_type t72  = v__OmegaControl(t71, -1, 1);
    real_type t73  = t72 * t8;
    real_type t76  = 1.0 / t6;
    real_type t77  = t9 * t76;
    real_type t78  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t80  = t76 * t15;
    real_type t82  = t21 * t76;
    real_type t84  = t27 * t76;
    real_type t86  = 2 * t10 * t12 + 2 * t12 * t16 + 2 * t12 * t22 + 2 * t12 * t28 + 2 * t12 * t40 + 2 * t12 * t63 + 2 * t12 * t68 + 2 * t12 * t73 - t77 * t78 - t78 * t80 - t78 * t82 - t78 * t84;
    real_type t87  = t39 * t76;
    real_type t89  = t62 * t76;
    real_type t91  = MU__[0];
    real_type t93  = V__[0];
    real_type t95  = MU__[2];
    real_type t97  = V__[2];
    real_type t99  = MU__[4];
    real_type t101 = V__[3];
    real_type t103 = MU__[3];
    real_type t105 = V__[4];
    real_type t107 = t67 * t76;
    real_type t109 = t72 * t76;
    real_type t111 = ALIAS_RoadRightBorder_D(t26);
    real_type t112 = t111 * t76;
    real_type t115 = ALIAS_RoadLeftBorder_D(t20);
    real_type t116 = t115 * t76;
    real_type t119 = MU__[1];
    real_type t121 = V__[1];
    real_type t125 = 1.0 / t5;
    real_type t126 = ALIAS_RoadRightBorder_DD(t26);
    real_type t128 = ALIAS_RoadLeftBorder_DD(t20);
    real_type t130 = -t78 * t87 - t78 * t89 - t93 * t78 * t91 - t97 * t78 * t95 - t101 * t78 * t99 - t105 * t78 * t103 - t78 * t107 - t78 * t109 + 2 * t11 * t112 - 2 * t11 * t116 + (-t121 * t78 - t4 * t78) * t119 + t126 * t125 + t128 * t125;
    result__[ 0   ] = t86 + t130;
    real_type t131 = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t132 = t131 * t11;
    real_type t135 = zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t150 = -t107 * t135 - t109 * t135 - t116 * t131 + 2 * t132 * t16 + 2 * t132 * t22 + 2 * t132 * t63 + 2 * t132 * t68 + 2 * t132 * t73 - t135 * t80 - t135 * t82 - t135 * t89;
    real_type t173 = 2 * t132 * t28 - t135 * t84 + t131 * t112 + 2 * t132 * t40 - t135 * t87 + 2 * t132 * t10 - t135 * t77 - t93 * t135 * t91 + (-t121 * t135 - t135 * t4) * t119 - t97 * t135 * t95 - t105 * t135 * t103 - t101 * t135 * t99;
    result__[ 1   ] = t150 + t173;
    real_type t174 = ALIAS_PowerLimit_D(t38);
    real_type t175 = t174 * t76;
    real_type t176 = t31 * t175;
    real_type t177 = t11 * t36;
    real_type t179 = ALIAS_AdherenceEllipse_D(t61);
    real_type t180 = t179 * t76;
    real_type t181 = t53 * t180;
    real_type t182 = t58 * t1;
    real_type t183 = t11 * t50;
    real_type t187 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t188 = t187 * t11;
    real_type t205 = zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t209 = -2 * t181 * t182 * t183 + 2 * t10 * t188 + 2 * t16 * t188 - t176 * t177 + 2 * t188 * t22 + 2 * t188 * t28 + 2 * t188 * t40 + 2 * t188 * t63 + 2 * t188 * t68 + 2 * t188 * t73 - t205 * t77 - t205 * t80 - t205 * t82;
    real_type t223 = ALIAS_LimitMinSpeed_D(-t1);
    real_type t224 = t223 * t76;
    real_type t232 = -t205 * t84 - t205 * t87 - t205 * t89 - t93 * t205 * t91 - t97 * t205 * t95 - t101 * t205 * t99 - t105 * t205 * t103 - t205 * t107 - t205 * t109 + t11 * t224 + t187 * t112 - t187 * t116 + (-t121 * t205 - t205 * t4) * t119;
    result__[ 2   ] = t209 + t232;
    real_type t233 = t52 * t180;
    real_type t234 = t58 * t54;
    result__[ 3   ] = -2 * t183 * t234 * t233;
    real_type t238 = t31 * t180;
    real_type t239 = t50 * t46;
    real_type t243 = t1 * t175;
    result__[ 4   ] = -2 * t11 * t238 * t239 - t177 * t243;
    real_type t245 = ALIAS_v__fxControl_D_1(t66, -1, 1);
    real_type t246 = t245 * t76;
    result__[ 5   ] = -t11 * t246;
    real_type t248 = ALIAS_v__OmegaControl_D_1(t71, -1, 1);
    real_type t249 = t248 * t76;
    result__[ 6   ] = -t11 * t249;
    result__[ 7   ] = -t11 * t91;
    result__[ 8   ] = -t11 * t119;
    result__[ 9   ] = -t11 * t95;
    result__[ 10  ] = -t11 * t99;
    result__[ 11  ] = -t11 * t103;
    result__[ 12  ] = result__[1];
    real_type t256 = t131 * t131;
    real_type t259 = zeta__dot_D_2_2(t1, t2, t3, t4);
    real_type t283 = sin(t2);
    real_type t298 = 2 * t256 * t28 - t259 * t84 + 2 * t256 * t40 - t259 * t87 + 2 * t256 * t10 - t259 * t77 + (-t1 * t283 - t259 * t93) * t91 + (-t121 * t259 - t259 * t4) * t119 - t97 * t259 * t95 - t105 * t259 * t103 - t101 * t259 * t99;
    result__[ 13  ] = -t107 * t259 - t109 * t259 + 2 * t16 * t256 + 2 * t22 * t256 + 2 * t256 * t63 + 2 * t256 * t68 + 2 * t256 * t73 - t259 * t80 - t259 * t82 - t259 * t89 + t298;
    real_type t299 = t187 * t131;
    real_type t302 = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t312 = t131 * t50;
    real_type t322 = -2 * t181 * t182 * t312 - t107 * t302 - t109 * t302 + 2 * t16 * t299 + 2 * t22 * t299 + 2 * t28 * t299 + 2 * t299 * t63 + 2 * t299 * t68 + 2 * t299 * t73 - t302 * t80 - t302 * t82 - t302 * t89;
    real_type t326 = t131 * t36;
    real_type t333 = cos(t2);
    real_type t347 = -t302 * t84 + 2 * t299 * t40 - t326 * t176 - t302 * t87 + 2 * t299 * t10 + t131 * t224 - t302 * t77 + (-t302 * t93 + t333) * t91 + (-t121 * t302 - t302 * t4) * t119 - t97 * t302 * t95 - t105 * t302 * t103 - t101 * t302 * t99;
    result__[ 14  ] = t322 + t347;
    result__[ 15  ] = -2 * t312 * t234 * t233;
    result__[ 16  ] = -2 * t131 * t238 * t239 - t243 * t326;
    result__[ 17  ] = -t131 * t246;
    result__[ 18  ] = -t131 * t249;
    result__[ 19  ] = -t131 * t91;
    result__[ 20  ] = -t131 * t119;
    result__[ 21  ] = -t131 * t95;
    result__[ 22  ] = -t131 * t99;
    result__[ 23  ] = -t131 * t103;
    result__[ 24  ] = result__[2];
    result__[ 25  ] = result__[14];
    real_type t362 = t187 * t36;
    real_type t365 = ALIAS_AdherenceEllipse_DD(t61);
    real_type t366 = t365 * t125;
    real_type t367 = t53 * t53;
    real_type t369 = t57 * t57;
    real_type t370 = 1.0 / t369;
    real_type t372 = t49 * t49;
    real_type t373 = 1.0 / t372;
    real_type t377 = ALIAS_PowerLimit_DD(t38);
    real_type t378 = t377 * t125;
    real_type t379 = t33 * t33;
    real_type t381 = t34 * t34;
    real_type t382 = 1.0 / t381;
    real_type t385 = t179 * t125;
    real_type t390 = t187 * t50;
    real_type t394 = t187 * t187;
    real_type t411 = zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t413 = 4 * t366 * t367 * t370 * t373 * t54 + t378 * t379 * t382 * t43 + 2 * t385 * t50 * t53 * t58 - 4 * t181 * t182 * t390 + 2 * t10 * t394 + 2 * t16 * t394 - 2 * t176 * t362 + 2 * t22 * t394 + 2 * t28 * t394 + 2 * t394 * t40 + 2 * t394 * t63 + 2 * t394 * t68 + 2 * t394 * t73 - t411 * t77;
    real_type t438 = ALIAS_LimitMinSpeed_DD(-t1);
    real_type t440 = -t411 * t80 - t411 * t82 - t411 * t84 - t411 * t87 - t411 * t89 - t93 * t411 * t91 - t101 * t411 * t99 - t105 * t411 * t103 - t411 * t107 - t411 * t109 + 2 * t187 * t224 + (-t121 * t411 - t4 * t411) * t119 + (-t411 * t97 - 2 * ModelPars[iM_kD]) * t95 + t438 * t125;
    result__[ 26  ] = t413 + t440;
    result__[ 27  ] = 4 * t1 * t366 * t370 * t373 * t52 * t53 * t54 + 4 * t182 * t385 * t50 * t52 - 2 * t233 * t234 * t390;
    real_type t459 = t46 * t31 * t366;
    result__[ 28  ] = t1 * t31 * t378 * t379 * t382 + 4 * t182 * t373 * t459 * t53 + t125 * t174 * t36 - 2 * t187 * t238 * t239 - t243 * t362;
    result__[ 29  ] = -t187 * t246;
    result__[ 30  ] = -t187 * t249;
    result__[ 31  ] = -t187 * t91;
    result__[ 32  ] = -t187 * t119;
    result__[ 33  ] = -t187 * t95;
    result__[ 34  ] = -t187 * t99;
    result__[ 35  ] = -t187 * t103;
    result__[ 36  ] = result__[3];
    result__[ 37  ] = result__[15];
    result__[ 38  ] = result__[27];
    real_type t479 = t54 * t54;
    result__[ 39  ] = 4 * t366 * t370 * t373 * t479 * t53 + 2 * t234 * t385 * t50;
    result__[ 40  ] = 4 * t234 * t52 * t373 * t459;
    result__[ 41  ] = result__[4];
    result__[ 42  ] = result__[16];
    result__[ 43  ] = result__[28];
    result__[ 44  ] = result__[40];
    real_type t490 = t45 * t45;
    result__[ 45  ] = 4 * t373 / t490 * t43 * t366 + 2 * t239 * t385 + t382 * t379 * t54 * t378;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 46, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
