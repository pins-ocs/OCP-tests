/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
    result__[ 0   ] = -t10 * t9 - t10 * t14 - t10 * t18 - t10 * t41 - t10 * t46 + t49 * t48 - t10 * t54 - t56 * t48 - t10 * t66 - t10 * t69 - t73 * t10 * t71 + (-t10 * t5 - t77 * t10) * t75 - t83 * t10 * t81 - t87 * t10 * t85 - t91 * t10 * t89;
    real_type t93  = zeta__dot_D_2(t2, t3, t4, t5);
    real_type t102 = cos(t3);
    result__[ 1   ] = -t93 * t9 - t93 * t14 - t93 * t18 - t93 * t41 - t93 * t46 - t93 * t54 - t93 * t66 - t93 * t69 + (t102 * t2 - t73 * t93) * t71 + (-t93 * t5 - t77 * t93) * t75 - t83 * t93 * t81 - t87 * t93 * t85 - t91 * t93 * t89;
    real_type t117 = zeta__dot_D_1(t2, t3, t4, t5);
    real_type t122 = ALIAS_AdherenceEllipse_D(t39);
    real_type t123 = t122 * t48;
    real_type t132 = ALIAS_PowerLimit_D(t64);
    real_type t133 = t132 * t48;
    real_type t138 = ALIAS_LimitMinSpeed_D(-t2);
    real_type t140 = sin(t3);
    result__[ 2   ] = -t117 * t9 - t117 * t14 - t117 * t18 - t117 * t41 + 2 * t28 * t36 * t2 * t31 * t123 - t117 * t46 - t117 * t54 - t117 * t66 + t61 * t59 * t20 * t133 - t117 * t69 - t138 * t48 + (-t73 * t117 + t140) * t71 + (-t117 * t5 - t77 * t117) * t75 + (-t83 * t117 - 2 * t2 * ModelPars[iM_kD]) * t81 - t87 * t117 * t85 - t91 * t117 * t89;
    result__[ 3   ] = 2 * t28 * t36 * t32 * t30 * t123 + t75;
    result__[ 4   ] = 2 * t28 * t24 * t20 * t123 + t61 * t59 * t2 * t133 + t81;
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
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = Q__[iQ_Kappa];
    real_type t3   = X__[iX_V];
    real_type t4   = X__[iX_alpha];
    real_type t5   = X__[iX_n];
    real_type t6   = zeta__dot_D_3_3(t3, t4, t5, t2);
    real_type t8   = V__[1];
    real_type t12  = zeta__dot(t3, t4, t5, t2);
    real_type t13  = 1.0 / t12;
    real_type t15  = -t5 - Q__[iQ_rightWidth];
    real_type t16  = ALIAS_RoadRightBorder_DD(t15);
    real_type t19  = t5 - Q__[iQ_leftWidth];
    real_type t20  = ALIAS_RoadLeftBorder_DD(t19);
    real_type t22  = ModelPars[iM_wT];
    real_type t23  = t12 * t12;
    real_type t25  = 1.0 / t23 / t12;
    real_type t26  = t25 * t22;
    real_type t27  = zeta__dot_D_3(t3, t4, t5, t2);
    real_type t28  = t27 * t27;
    real_type t31  = LimitMinSpeed(-t3);
    real_type t32  = t31 * t25;
    real_type t35  = RoadLeftBorder(t19);
    real_type t36  = t35 * t25;
    real_type t39  = RoadRightBorder(t15);
    real_type t40  = t39 * t25;
    real_type t43  = X__[iX_fx];
    real_type t45  = ModelPars[iM_m];
    real_type t46  = ModelPars[iM_Pmax];
    real_type t48  = 1.0 / t46 * t45;
    real_type t50  = t48 * t43 * t3 - 1;
    real_type t51  = PowerLimit(t50);
    real_type t52  = t51 * t25;
    real_type t55  = t43 * t43;
    real_type t57  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t58  = 1.0 / t57;
    real_type t61  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t62  = 1.0 / t61;
    real_type t64  = X__[iX_Omega];
    real_type t65  = t64 * t64;
    real_type t66  = t3 * t3;
    real_type t69  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t70  = 1.0 / t69;
    real_type t73  = t62 * t70 * t66 * t65 + t62 * t58 * t55 - 1;
    real_type t74  = AdherenceEllipse(t73);
    real_type t75  = t74 * t25;
    real_type t78  = U__[iU_v__fx];
    real_type t79  = v__fxControl(t78, -1, 1);
    real_type t80  = t79 * t25;
    real_type t83  = U__[iU_v__Omega];
    real_type t84  = v__OmegaControl(t83, -1, 1);
    real_type t85  = t84 * t25;
    real_type t88  = 1.0 / t23;
    real_type t89  = t88 * t22;
    real_type t91  = (-t6 * t2 - t8 * t6) * t1 + t16 * t13 + t20 * t13 + 2 * t28 * t26 + 2 * t28 * t32 + 2 * t28 * t36 + 2 * t28 * t40 + 2 * t28 * t52 + 2 * t28 * t75 + 2 * t28 * t80 + 2 * t28 * t85 - t6 * t89;
    real_type t92  = t31 * t88;
    real_type t94  = t35 * t88;
    real_type t96  = t39 * t88;
    real_type t98  = t51 * t88;
    real_type t100 = t74 * t88;
    real_type t102 = MU__[0];
    real_type t104 = V__[0];
    real_type t106 = MU__[2];
    real_type t108 = V__[2];
    real_type t110 = MU__[4];
    real_type t112 = V__[3];
    real_type t114 = MU__[3];
    real_type t116 = V__[4];
    real_type t118 = t79 * t88;
    real_type t120 = t84 * t88;
    real_type t122 = ALIAS_RoadRightBorder_D(t15);
    real_type t123 = t122 * t88;
    real_type t126 = ALIAS_RoadLeftBorder_D(t19);
    real_type t127 = t126 * t88;
    real_type t130 = -t104 * t6 * t102 - t108 * t6 * t106 - t112 * t6 * t110 - t116 * t6 * t114 - t6 * t100 - t6 * t118 - t6 * t120 + 2 * t27 * t123 - 2 * t27 * t127 - t6 * t92 - t6 * t94 - t6 * t96 - t6 * t98;
    result__[ 0   ] = t91 + t130;
    real_type t131 = zeta__dot_D_2(t3, t4, t5, t2);
    real_type t132 = t131 * t27;
    real_type t135 = zeta__dot_D_2_3(t3, t4, t5, t2);
    real_type t150 = -t135 * t100 - t135 * t118 - t135 * t120 - t131 * t127 + 2 * t132 * t26 + 2 * t132 * t36 + 2 * t132 * t75 + 2 * t132 * t80 + 2 * t132 * t85 - t135 * t89 - t135 * t94;
    real_type t173 = 2 * t132 * t40 - t135 * t96 + t131 * t123 + 2 * t132 * t52 - t135 * t98 + 2 * t132 * t32 - t135 * t92 - t104 * t135 * t102 + (-t135 * t2 - t8 * t135) * t1 - t108 * t135 * t106 - t116 * t135 * t114 - t112 * t135 * t110;
    result__[ 1   ] = t150 + t173;
    real_type t174 = ALIAS_PowerLimit_D(t50);
    real_type t175 = t174 * t88;
    real_type t176 = t43 * t175;
    real_type t177 = t27 * t48;
    real_type t179 = ALIAS_AdherenceEllipse_D(t73);
    real_type t180 = t179 * t88;
    real_type t181 = t65 * t180;
    real_type t182 = t70 * t3;
    real_type t183 = t27 * t62;
    real_type t187 = zeta__dot_D_1_3(t3, t4, t5, t2);
    real_type t206 = -t177 * t176 - 2 * t183 * t182 * t181 + (-t187 * t2 - t8 * t187) * t1 - t187 * t89 - t187 * t92 - t187 * t94 - t187 * t96 - t187 * t98 - t187 * t100 - t104 * t187 * t102 - t108 * t187 * t106 - t112 * t187 * t110 - t116 * t187 * t114;
    real_type t209 = ALIAS_LimitMinSpeed_D(-t3);
    real_type t210 = t209 * t88;
    real_type t212 = zeta__dot_D_1(t3, t4, t5, t2);
    real_type t215 = t212 * t27;
    real_type t232 = -t187 * t118 - t187 * t120 + t212 * t123 - t212 * t127 + t27 * t210 + 2 * t215 * t26 + 2 * t215 * t32 + 2 * t215 * t36 + 2 * t215 * t40 + 2 * t215 * t52 + 2 * t215 * t75 + 2 * t215 * t80 + 2 * t215 * t85;
    result__[ 2   ] = t206 + t232;
    real_type t233 = t64 * t180;
    real_type t234 = t70 * t66;
    result__[ 3   ] = -2 * t183 * t234 * t233;
    real_type t238 = t43 * t180;
    real_type t239 = t62 * t58;
    real_type t243 = t3 * t175;
    result__[ 4   ] = -2 * t27 * t239 * t238 - t177 * t243;
    real_type t245 = ALIAS_v__fxControl_D_1(t78, -1, 1);
    real_type t246 = t245 * t88;
    result__[ 5   ] = -t27 * t246;
    real_type t248 = ALIAS_v__OmegaControl_D_1(t83, -1, 1);
    real_type t249 = t248 * t88;
    result__[ 6   ] = -t27 * t249;
    result__[ 7   ] = -t27 * t102;
    result__[ 8   ] = -t27 * t1;
    result__[ 9   ] = -t27 * t106;
    result__[ 10  ] = -t27 * t110;
    result__[ 11  ] = -t27 * t114;
    result__[ 12  ] = result__[1];
    real_type t256 = t131 * t131;
    real_type t259 = zeta__dot_D_2_2(t3, t4, t5, t2);
    real_type t283 = sin(t4);
    real_type t298 = 2 * t256 * t40 - t259 * t96 + 2 * t256 * t52 - t259 * t98 + 2 * t256 * t32 - t259 * t92 + (-t104 * t259 - t283 * t3) * t102 + (-t259 * t2 - t8 * t259) * t1 - t108 * t259 * t106 - t116 * t259 * t114 - t112 * t259 * t110;
    result__[ 13  ] = -t259 * t100 - t259 * t118 - t259 * t120 + 2 * t256 * t26 + 2 * t256 * t36 + 2 * t256 * t75 + 2 * t256 * t80 + 2 * t256 * t85 - t259 * t89 - t259 * t94 + t298;
    real_type t299 = t212 * t131;
    real_type t302 = zeta__dot_D_1_2(t3, t4, t5, t2);
    real_type t312 = t131 * t62;
    real_type t322 = -2 * t312 * t182 * t181 - t302 * t100 - t302 * t118 - t302 * t120 + 2 * t299 * t26 + 2 * t299 * t36 + 2 * t299 * t40 + 2 * t299 * t75 + 2 * t299 * t80 + 2 * t299 * t85 - t302 * t89 - t302 * t94;
    real_type t326 = t131 * t48;
    real_type t333 = cos(t4);
    real_type t347 = -t302 * t96 + 2 * t299 * t52 - t326 * t176 - t302 * t98 + 2 * t299 * t32 + t131 * t210 - t302 * t92 + (-t104 * t302 + t333) * t102 + (-t302 * t2 - t8 * t302) * t1 - t108 * t302 * t106 - t116 * t302 * t114 - t112 * t302 * t110;
    result__[ 14  ] = t322 + t347;
    result__[ 15  ] = -2 * t312 * t234 * t233;
    result__[ 16  ] = -2 * t131 * t239 * t238 - t326 * t243;
    result__[ 17  ] = -t131 * t246;
    result__[ 18  ] = -t131 * t249;
    result__[ 19  ] = -t131 * t102;
    result__[ 20  ] = -t131 * t1;
    result__[ 21  ] = -t131 * t106;
    result__[ 22  ] = -t131 * t110;
    result__[ 23  ] = -t131 * t114;
    result__[ 24  ] = result__[2];
    result__[ 25  ] = result__[14];
    real_type t362 = ALIAS_AdherenceEllipse_DD(t73);
    real_type t363 = t362 * t13;
    real_type t364 = t65 * t65;
    real_type t366 = t69 * t69;
    real_type t367 = 1.0 / t366;
    real_type t369 = t61 * t61;
    real_type t370 = 1.0 / t369;
    real_type t374 = t212 * t48;
    real_type t377 = t212 * t62;
    real_type t381 = zeta__dot_D_1_1(t3, t4, t5, t2);
    real_type t391 = ALIAS_LimitMinSpeed_DD(-t3);
    real_type t393 = t212 * t212;
    real_type t410 = 4 * t370 * t367 * t66 * t364 * t363 - 2 * t374 * t176 - 4 * t377 * t182 * t181 + (-t381 * t2 - t8 * t381) * t1 + (-t108 * t381 - 2 * ModelPars[iM_kD]) * t106 + t391 * t13 + 2 * t393 * t32 + 2 * t393 * t26 + 2 * t393 * t36 + 2 * t393 * t40 + 2 * t393 * t52 + 2 * t393 * t75 + 2 * t393 * t80 + 2 * t393 * t85;
    real_type t427 = ALIAS_PowerLimit_DD(t50);
    real_type t428 = t427 * t13;
    real_type t429 = t45 * t45;
    real_type t431 = t46 * t46;
    real_type t432 = 1.0 / t431;
    real_type t435 = t179 * t13;
    real_type t440 = t432 * t429 * t55 * t428 + 2 * t62 * t70 * t65 * t435 - t104 * t381 * t102 - t112 * t381 * t110 - t116 * t381 * t114 - t381 * t100 - t381 * t118 - t381 * t120 + 2 * t212 * t210 - t381 * t89 - t381 * t92 - t381 * t94 - t381 * t96 - t381 * t98;
    result__[ 26  ] = t410 + t440;
    result__[ 27  ] = 4 * t370 * t367 * t66 * t3 * t65 * t64 * t363 + 4 * t62 * t182 * t64 * t435 - 2 * t377 * t234 * t233;
    real_type t459 = t58 * t43 * t363;
    result__[ 28  ] = t43 * t432 * t429 * t3 * t428 + 4 * t182 * t65 * t370 * t459 + t48 * t174 * t13 - 2 * t212 * t239 * t238 - t374 * t243;
    result__[ 29  ] = -t212 * t246;
    result__[ 30  ] = -t212 * t249;
    result__[ 31  ] = -t212 * t102;
    result__[ 32  ] = -t212 * t1;
    result__[ 33  ] = -t212 * t106;
    result__[ 34  ] = -t212 * t110;
    result__[ 35  ] = -t212 * t114;
    result__[ 36  ] = result__[3];
    result__[ 37  ] = result__[15];
    result__[ 38  ] = result__[27];
    real_type t479 = t66 * t66;
    result__[ 39  ] = 4 * t370 * t367 * t479 * t65 * t363 + 2 * t62 * t234 * t435;
    result__[ 40  ] = 4 * t234 * t64 * t370 * t459;
    result__[ 41  ] = result__[4];
    result__[ 42  ] = result__[16];
    result__[ 43  ] = result__[28];
    result__[ 44  ] = result__[40];
    real_type t490 = t57 * t57;
    result__[ 45  ] = 4 * t370 / t490 * t55 * t363 + 2 * t239 * t435 + t432 * t429 * t66 * t428;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 46, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
