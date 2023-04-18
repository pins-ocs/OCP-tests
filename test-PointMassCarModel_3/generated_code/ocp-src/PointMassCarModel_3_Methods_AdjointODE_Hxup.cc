/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_AdjointODE.cc                      |
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


#include "PointMassCarModel_3.hh"
#include "PointMassCarModel_3_Pars.hh"

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


namespace PointMassCarModel_3Define {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::Hxp_numEqns() const { return 7; }

  void
  PointMassCarModel_3::Hxp_eval(
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
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_D(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t11  = ALIAS_rightWidth(t4);
    real_type t12  = -t3 - t11;
    real_type t13  = ALIAS_RoadRightBorder_D(t12);
    real_type t14  = t13 * t2;
    real_type t15  = ALIAS_rightWidth_D(t4);
    real_type t17  = MU__[0];
    real_type t18  = X__[iX_V];
    real_type t19  = X__[iX_alpha];
    real_type t20  = ALIAS_Kappa(t4);
    real_type t21  = zeta__dot_D_4(t18, t19, t3, t20);
    real_type t23  = ALIAS_Kappa_D(t4);
    real_type t26  = MU__[2];
    real_type t27  = t2 * t26;
    real_type t30  = zeta__dot(t18, t19, t3, t20);
    result__[ 0   ] = -t8 * t9 - t14 * t15 + t2 * t23 * t21 * t17 + (-t20 * t21 * t23 - t23 * t30) * t27;
    real_type t34  = zeta__dot_D_3(t18, t19, t3, t20);
    result__[ 1   ] = t17 * t2 * t34 - t20 * t27 * t34 - t14 + t8;
    real_type t39  = zeta__dot_D_2(t18, t19, t3, t20);
    real_type t42  = MU__[1];
    real_type t43  = t18 * t42;
    real_type t44  = cos(t19);
    result__[ 2   ] = t17 * t2 * t39 + t2 * t43 * t44 - t20 * t27 * t39;
    real_type t49  = X__[iX_fx];
    real_type t50  = t49 * t49;
    real_type t52  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t53  = 1.0 / t52;
    real_type t56  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t57  = 1.0 / t56;
    real_type t59  = X__[iX_Omega];
    real_type t60  = t59 * t59;
    real_type t61  = t18 * t18;
    real_type t64  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t65  = 1.0 / t64;
    real_type t68  = t57 * t60 * t61 * t65 + t50 * t53 * t57 - 1;
    real_type t69  = ALIAS_AdherenceEllipse_D(t68);
    real_type t70  = t69 * t2;
    real_type t77  = ModelPars[iM_m];
    real_type t79  = 1.0 / ModelPars[iM_Pmax];
    real_type t82  = t18 * t49 * t77 * t79 - 1;
    real_type t83  = ALIAS_PowerLimit_D(t82);
    real_type t84  = t83 * t2;
    real_type t88  = zeta__dot_D_1(t18, t19, t3, t20);
    real_type t91  = sin(t19);
    real_type t96  = MU__[3];
    real_type t97  = t2 * t96;
    real_type t98  = ModelPars[iM_kD];
    result__[ 3   ] = 2 * t18 * t57 * t60 * t65 * t70 + t49 * t77 * t79 * t84 + t17 * t2 * t88 - 2 * t18 * t97 * t98 + t2 * t42 * t91 - t20 * t27 * t88;
    result__[ 4   ] = 2 * t57 * t59 * t61 * t65 * t70 + t27;
    result__[ 5   ] = t18 * t77 * t79 * t84 + 2 * t49 * t53 * t57 * t70 + t97;
    real_type t116 = U__[iU_v__fx];
    real_type t117 = v__fxControl(t116, -1, 1);
    real_type t119 = U__[iU_v__Omega];
    real_type t120 = v__OmegaControl(t119, -1, 1);
    real_type t122 = AdherenceEllipse(t68);
    real_type t124 = RoadLeftBorder(t6);
    real_type t126 = RoadRightBorder(t12);
    real_type t128 = PowerLimit(t82);
    real_type t152 = t1 * ModelPars[iM_wT] + t117 * t1 + t120 * t1 + t122 * t1 + t124 * t1 + t126 * t1 + t128 * t1 + t1 * t30 * t17 + t1 * t91 * t43 + (-t20 * t30 + t59) * t1 * t26 + (-t61 * t98 + t49) * t1 * t96 + t1 * ModelPars[iM_v__Omega__max] * t119 * MU__[4] + t1 * ModelPars[iM_v__fx__max] * t116 * MU__[5];
    result__[ 6   ] = 2 * t152;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DHxpDxpuv_numRows() const { return 7; }
  integer PointMassCarModel_3::DHxpDxpuv_numCols() const { return 16; }
  integer PointMassCarModel_3::DHxpDxpuv_nnz()     const { return 39; }

  void
  PointMassCarModel_3::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 3   ; jIndex[15] = 0   ;
    iIndex[16] = 3   ; jIndex[16] = 1   ;
    iIndex[17] = 3   ; jIndex[17] = 2   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 3   ; jIndex[20] = 5   ;
    iIndex[21] = 3   ; jIndex[21] = 6   ;
    iIndex[22] = 4   ; jIndex[22] = 3   ;
    iIndex[23] = 4   ; jIndex[23] = 4   ;
    iIndex[24] = 4   ; jIndex[24] = 5   ;
    iIndex[25] = 4   ; jIndex[25] = 6   ;
    iIndex[26] = 5   ; jIndex[26] = 3   ;
    iIndex[27] = 5   ; jIndex[27] = 4   ;
    iIndex[28] = 5   ; jIndex[28] = 5   ;
    iIndex[29] = 5   ; jIndex[29] = 6   ;
    iIndex[30] = 6   ; jIndex[30] = 0   ;
    iIndex[31] = 6   ; jIndex[31] = 1   ;
    iIndex[32] = 6   ; jIndex[32] = 2   ;
    iIndex[33] = 6   ; jIndex[33] = 3   ;
    iIndex[34] = 6   ; jIndex[34] = 4   ;
    iIndex[35] = 6   ; jIndex[35] = 5   ;
    iIndex[36] = 6   ; jIndex[36] = 6   ;
    iIndex[37] = 6   ; jIndex[37] = 7   ;
    iIndex[38] = 6   ; jIndex[38] = 8   ;
  }


  void
  PointMassCarModel_3::DHxpDxpuv_sparse(
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
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_RoadLeftBorder_D(t6);
    real_type t14  = ALIAS_leftWidth_DD(t4);
    real_type t16  = ALIAS_rightWidth(t4);
    real_type t17  = -t3 - t16;
    real_type t18  = ALIAS_RoadRightBorder_DD(t17);
    real_type t19  = t18 * t2;
    real_type t20  = ALIAS_rightWidth_D(t4);
    real_type t21  = t20 * t20;
    real_type t23  = ALIAS_RoadRightBorder_D(t17);
    real_type t25  = ALIAS_rightWidth_DD(t4);
    real_type t27  = MU__[0];
    real_type t28  = X__[iX_V];
    real_type t29  = X__[iX_alpha];
    real_type t30  = ALIAS_Kappa(t4);
    real_type t31  = zeta__dot_D_4_4(t28, t29, t3, t30);
    real_type t33  = ALIAS_Kappa_D(t4);
    real_type t34  = t33 * t33;
    real_type t37  = zeta__dot_D_4(t28, t29, t3, t30);
    real_type t38  = t37 * t27;
    real_type t39  = ALIAS_Kappa_DD(t4);
    real_type t42  = MU__[2];
    real_type t43  = t2 * t42;
    real_type t50  = zeta__dot(t28, t29, t3, t30);
    result__[ 0   ] = t10 * t8 - t14 * t12 * t2 + t21 * t19 - t25 * t23 * t2 + t2 * t34 * t31 * t27 + t2 * t39 * t38 + (-t30 * t31 * t34 - t30 * t37 * t39 - 2 * t34 * t37 - t39 * t50) * t43;
    real_type t54  = t9 * t8;
    real_type t55  = t20 * t19;
    real_type t56  = zeta__dot_D_3_4(t28, t29, t3, t30);
    real_type t58  = t2 * t33;
    real_type t59  = t58 * t56 * t27;
    real_type t61  = t30 * t33 * t56;
    real_type t62  = zeta__dot_D_3(t28, t29, t3, t30);
    real_type t63  = t33 * t62;
    result__[ 1   ] = -t54 + t55 + t59 + (-t61 - t63) * t43;
    real_type t66  = zeta__dot_D_2_4(t28, t29, t3, t30);
    real_type t68  = t58 * t66 * t27;
    real_type t70  = t30 * t33 * t66;
    real_type t71  = zeta__dot_D_2(t28, t29, t3, t30);
    real_type t72  = t33 * t71;
    result__[ 2   ] = t68 + (-t70 - t72) * t43;
    real_type t75  = zeta__dot_D_1_4(t28, t29, t3, t30);
    real_type t77  = t58 * t75 * t27;
    real_type t79  = t30 * t33 * t75;
    real_type t80  = zeta__dot_D_1(t28, t29, t3, t30);
    real_type t81  = t33 * t80;
    result__[ 3   ] = t77 + (-t79 - t81) * t43;
    real_type t84  = t12 * t1;
    real_type t86  = t23 * t1;
    real_type t90  = t1 * t42;
    result__[ 4   ] = -2 * t9 * t84 - 2 * t20 * t86 + 2 * t1 * t33 * t38 + 2 * (-t30 * t33 * t37 - t33 * t50) * t90;
    result__[ 5   ] = -t43 * t61 - t43 * t63 - t54 + t55 + t59;
    real_type t99  = zeta__dot_D_3_3(t28, t29, t3, t30);
    result__[ 6   ] = t2 * t27 * t99 - t30 * t43 * t99 + t19 + t8;
    real_type t104 = zeta__dot_D_2_3(t28, t29, t3, t30);
    result__[ 7   ] = t104 * t2 * t27 - t104 * t30 * t43;
    real_type t109 = zeta__dot_D_1_3(t28, t29, t3, t30);
    result__[ 8   ] = t109 * t2 * t27 - t109 * t30 * t43;
    result__[ 9   ] = 2 * t1 * t27 * t62 - 2 * t30 * t62 * t90 + 2 * t84 - 2 * t86;
    result__[ 10  ] = -t43 * t70 - t43 * t72 + t68;
    result__[ 11  ] = result__[7];
    real_type t121 = zeta__dot_D_2_2(t28, t29, t3, t30);
    real_type t124 = MU__[1];
    real_type t125 = t28 * t124;
    real_type t126 = sin(t29);
    result__[ 12  ] = t121 * t2 * t27 - t121 * t30 * t43 - t125 * t126 * t2;
    real_type t131 = zeta__dot_D_1_2(t28, t29, t3, t30);
    real_type t134 = cos(t29);
    result__[ 13  ] = t124 * t134 * t2 + t131 * t2 * t27 - t131 * t30 * t43;
    result__[ 14  ] = 2 * t1 * t125 * t134 + 2 * t1 * t27 * t71 - 2 * t30 * t71 * t90;
    result__[ 15  ] = -t43 * t79 - t43 * t81 + t77;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t148 = X__[iX_fx];
    real_type t149 = t148 * t148;
    real_type t151 = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t152 = 1.0 / t151;
    real_type t155 = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t156 = 1.0 / t155;
    real_type t158 = X__[iX_Omega];
    real_type t159 = t158 * t158;
    real_type t160 = t28 * t28;
    real_type t163 = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t164 = 1.0 / t163;
    real_type t167 = t156 * t159 * t160 * t164 + t149 * t152 * t156 - 1;
    real_type t168 = ALIAS_AdherenceEllipse_DD(t167);
    real_type t169 = t168 * t2;
    real_type t170 = t159 * t159;
    real_type t172 = t163 * t163;
    real_type t173 = 1.0 / t172;
    real_type t175 = t155 * t155;
    real_type t176 = 1.0 / t175;
    real_type t180 = ALIAS_AdherenceEllipse_D(t167);
    real_type t181 = t180 * t2;
    real_type t187 = ModelPars[iM_m];
    real_type t188 = ModelPars[iM_Pmax];
    real_type t189 = 1.0 / t188;
    real_type t190 = t189 * t187;
    real_type t192 = t148 * t190 * t28 - 1;
    real_type t193 = ALIAS_PowerLimit_DD(t192);
    real_type t194 = t193 * t2;
    real_type t195 = t187 * t187;
    real_type t197 = t188 * t188;
    real_type t198 = 1.0 / t197;
    real_type t201 = zeta__dot_D_1_1(t28, t29, t3, t30);
    real_type t206 = MU__[3];
    real_type t208 = ModelPars[iM_kD];
    result__[ 18  ] = 4 * t160 * t169 * t170 * t173 * t176 + t149 * t194 * t195 * t198 + 2 * t156 * t159 * t164 * t181 + t2 * t201 * t27 - 2 * t2 * t206 * t208 - t201 * t30 * t43;
    real_type t218 = t164 * t28;
    real_type t219 = t156 * t218;
    result__[ 19  ] = 4 * t158 * t159 * t160 * t169 * t173 * t176 * t28 + 4 * t158 * t181 * t219;
    real_type t222 = t152 * t148;
    real_type t223 = t222 * t169;
    real_type t232 = ALIAS_PowerLimit_D(t192);
    result__[ 20  ] = t148 * t194 * t195 * t198 * t28 + 4 * t159 * t176 * t218 * t223 + t190 * t2 * t232;
    real_type t235 = t180 * t1;
    real_type t239 = t232 * t1;
    real_type t253 = t1 * t206;
    result__[ 21  ] = 2 * t148 * t187 * t189 * t239 + 2 * t1 * t124 * t126 + 2 * t1 * t27 * t80 + 4 * t159 * t219 * t235 - 4 * t208 * t253 * t28 - 2 * t30 * t80 * t90;
    result__[ 22  ] = result__[19];
    real_type t258 = t160 * t160;
    real_type t263 = t164 * t160;
    real_type t264 = t156 * t263;
    result__[ 23  ] = 4 * t159 * t169 * t173 * t176 * t258 + 2 * t181 * t264;
    result__[ 24  ] = 4 * t263 * t158 * t176 * t223;
    result__[ 25  ] = 4 * t158 * t235 * t264 + 2 * t90;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t274 = t151 * t151;
    result__[ 28  ] = 4 * t176 / t274 * t149 * t169 + 2 * t156 * t152 * t181 + t198 * t195 * t160 * t194;
    result__[ 29  ] = 2 * t187 * t189 * t239 * t28 + 4 * t156 * t222 * t235 + 2 * t253;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t295 = U__[iU_v__fx];
    real_type t296 = v__fxControl(t295, -1, 1);
    real_type t297 = U__[iU_v__Omega];
    real_type t298 = v__OmegaControl(t297, -1, 1);
    real_type t299 = AdherenceEllipse(t167);
    real_type t300 = RoadLeftBorder(t6);
    real_type t301 = RoadRightBorder(t17);
    real_type t302 = PowerLimit(t192);
    real_type t311 = MU__[4];
    real_type t313 = ModelPars[iM_v__Omega__max];
    real_type t315 = MU__[5];
    real_type t317 = ModelPars[iM_v__fx__max];
    real_type t319 = ModelPars[iM_wT] + t296 + t298 + t299 + t300 + t301 + t302 + t50 * t27 + t126 * t125 + (-t30 * t50 + t158) * t42 + (-t160 * t208 + t148) * t206 + t313 * t297 * t311 + t317 * t295 * t315;
    result__[ 36  ] = 2 * t319;
    real_type t320 = ALIAS_v__fxControl_D_1(t295, -1, 1);
    result__[ 37  ] = 2 * t1 * t315 * t317 + 2 * t1 * t320;
    real_type t325 = ALIAS_v__OmegaControl_D_1(t297, -1, 1);
    result__[ 38  ] = 2 * t1 * t311 * t313 + 2 * t1 * t325;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 39, i_segment );
  }

}

// EOF: PointMassCarModel_3_Methods_AdjointODE.cc
