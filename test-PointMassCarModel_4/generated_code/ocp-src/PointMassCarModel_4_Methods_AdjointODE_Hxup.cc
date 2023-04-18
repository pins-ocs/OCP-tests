/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_AdjointODE.cc                      |
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


#include "PointMassCarModel_4.hh"
#include "PointMassCarModel_4_Pars.hh"

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


namespace PointMassCarModel_4Define {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::Hxp_numEqns() const { return 7; }

  void
  PointMassCarModel_4::Hxp_eval(
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
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_D(t6);
    real_type t8   = t2 * t7;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t11  = ALIAS_rightWidth(t4);
    real_type t12  = -t3 - t11;
    real_type t13  = ALIAS_RoadRightBorder_D(t12);
    real_type t14  = t13 * t2;
    real_type t15  = ALIAS_rightWidth_D(t4);
    real_type t18  = t2 * MU__[0];
    real_type t19  = X__[iX_V];
    real_type t20  = X__[iX_alpha];
    real_type t21  = ALIAS_Kappa(t4);
    real_type t22  = zeta__dot_D_4(t19, t20, t3, t21);
    real_type t23  = ALIAS_Kappa_D(t4);
    real_type t26  = MU__[2];
    real_type t27  = zeta__dot(t19, t20, t3, t21);
    result__[ 0   ] = -t9 * t8 - t15 * t14 + t23 * t22 * t18 - t2 * (t21 * t22 * t23 + t23 * t27) * t26;
    real_type t34  = zeta__dot_D_3(t19, t20, t3, t21);
    real_type t36  = t21 * t26;
    result__[ 1   ] = -t2 * t34 * t36 + t18 * t34 - t14 + t8;
    real_type t39  = zeta__dot_D_2(t19, t20, t3, t21);
    real_type t42  = t2 * MU__[1];
    real_type t43  = cos(t20);
    result__[ 2   ] = t19 * t42 * t43 - t2 * t36 * t39 + t18 * t39;
    real_type t48  = X__[iX_fx];
    real_type t49  = t48 * t48;
    real_type t51  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t52  = 1.0 / t51;
    real_type t55  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t56  = 1.0 / t55;
    real_type t58  = X__[iX_Omega];
    real_type t59  = t58 * t58;
    real_type t60  = t19 * t19;
    real_type t63  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t64  = 1.0 / t63;
    real_type t67  = t56 * t59 * t60 * t64 + t49 * t52 * t56 - 1;
    real_type t68  = ALIAS_AdherenceEllipse_D(t67);
    real_type t69  = t68 * t2;
    real_type t76  = ModelPars[iM_m];
    real_type t78  = 1.0 / ModelPars[iM_Pmax];
    real_type t81  = t19 * t48 * t76 * t78 - 1;
    real_type t82  = ALIAS_PowerLimit_D(t81);
    real_type t83  = t82 * t2;
    real_type t87  = zeta__dot_D_1(t19, t20, t3, t21);
    real_type t89  = sin(t20);
    real_type t93  = MU__[3];
    real_type t94  = ModelPars[iM_kD];
    result__[ 3   ] = 2 * t19 * t56 * t59 * t64 * t69 - 2 * t19 * t2 * t93 * t94 + t48 * t76 * t78 * t83 - t2 * t36 * t87 + t18 * t87 + t42 * t89;
    result__[ 4   ] = 2 * t56 * t58 * t60 * t64 * t69 + t2 * t26;
    result__[ 5   ] = t19 * t76 * t78 * t83 + 2 * t48 * t52 * t56 * t69 + t2 * t93;
    real_type t115 = U__[iU_v__fx];
    real_type t116 = v__fxControl(t115, -1, 1);
    real_type t118 = U__[iU_v__Omega];
    real_type t119 = v__OmegaControl(t118, -1, 1);
    real_type t121 = AdherenceEllipse(t67);
    real_type t123 = RoadLeftBorder(t6);
    real_type t125 = RoadRightBorder(t12);
    real_type t127 = PowerLimit(t81);
    result__[ 6   ] = t2 * ModelPars[iM_wT] + t116 * t2 + t119 * t2 + t121 * t2 + t123 * t2 + t125 * t2 + t127 * t2 + t27 * t18 + t89 * t19 * t42 - t2 * (t21 * t27 - t58) * t26 + t2 * (-t60 * t94 + t48) * t93 + ModelPars[iM_v__Omega__max] * t118 * t2 * MU__[4] + ModelPars[iM_v__fx__max] * t115 * t2 * MU__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DHxpDxpuv_numRows() const { return 7; }
  integer PointMassCarModel_4::DHxpDxpuv_numCols() const { return 16; }
  integer PointMassCarModel_4::DHxpDxpuv_nnz()     const { return 39; }

  void
  PointMassCarModel_4::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_4::DHxpDxpuv_sparse(
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
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_RoadLeftBorder_D(t6);
    real_type t13  = t12 * t2;
    real_type t14  = ALIAS_leftWidth_DD(t4);
    real_type t16  = ALIAS_rightWidth(t4);
    real_type t17  = -t3 - t16;
    real_type t18  = ALIAS_RoadRightBorder_DD(t17);
    real_type t19  = t18 * t2;
    real_type t20  = ALIAS_rightWidth_D(t4);
    real_type t21  = t20 * t20;
    real_type t23  = ALIAS_RoadRightBorder_D(t17);
    real_type t24  = t23 * t2;
    real_type t25  = ALIAS_rightWidth_DD(t4);
    real_type t28  = t2 * MU__[0];
    real_type t29  = X__[iX_V];
    real_type t30  = X__[iX_alpha];
    real_type t31  = ALIAS_Kappa(t4);
    real_type t32  = zeta__dot_D_4_4(t29, t30, t3, t31);
    real_type t33  = ALIAS_Kappa_D(t4);
    real_type t34  = t33 * t33;
    real_type t37  = zeta__dot_D_4(t29, t30, t3, t31);
    real_type t38  = ALIAS_Kappa_DD(t4);
    real_type t41  = MU__[2];
    real_type t42  = zeta__dot(t29, t30, t3, t31);
    real_type t48  = t37 * t31;
    result__[ 0   ] = t10 * t8 - t14 * t13 + t21 * t19 - t25 * t24 + t34 * t32 * t28 + t38 * t37 * t28 - t2 * (t31 * t32 * t34 + 2 * t34 * t37 + t38 * t42 + t38 * t48) * t41;
    real_type t53  = t9 * t8;
    real_type t54  = t20 * t19;
    real_type t55  = zeta__dot_D_3_4(t29, t30, t3, t31);
    real_type t56  = t33 * t55;
    real_type t57  = t56 * t28;
    real_type t58  = zeta__dot_D_3(t29, t30, t3, t31);
    result__[ 1   ] = -t53 + t54 + t57 - t2 * (t31 * t33 * t55 + t33 * t58) * t41;
    real_type t65  = zeta__dot_D_2_4(t29, t30, t3, t31);
    real_type t66  = t33 * t65;
    real_type t67  = t66 * t28;
    real_type t68  = zeta__dot_D_2(t29, t30, t3, t31);
    result__[ 2   ] = t67 - t2 * (t31 * t33 * t65 + t33 * t68) * t41;
    real_type t75  = zeta__dot_D_1_4(t29, t30, t3, t31);
    real_type t76  = t33 * t75;
    real_type t77  = t76 * t28;
    real_type t78  = zeta__dot_D_1(t29, t30, t3, t31);
    result__[ 3   ] = t77 - t2 * (t31 * t33 * t75 + t33 * t78) * t41;
    result__[ 4   ] = -t9 * t13 - t20 * t24 + t33 * t37 * t28 - t2 * (t33 * t42 + t33 * t48) * t41;
    real_type t94  = t33 * t41;
    real_type t95  = t2 * t58;
    real_type t97  = t31 * t41;
    result__[ 5   ] = -t2 * t56 * t97 - t94 * t95 - t53 + t54 + t57;
    real_type t100 = zeta__dot_D_3_3(t29, t30, t3, t31);
    result__[ 6   ] = -t100 * t2 * t97 + t100 * t28 + t19 + t8;
    real_type t104 = zeta__dot_D_2_3(t29, t30, t3, t31);
    result__[ 7   ] = -t104 * t2 * t97 + t104 * t28;
    real_type t108 = zeta__dot_D_1_3(t29, t30, t3, t31);
    result__[ 8   ] = -t108 * t2 * t97 + t108 * t28;
    result__[ 9   ] = t28 * t58 - t95 * t97 + t13 - t24;
    real_type t114 = t2 * t68;
    result__[ 10  ] = -t2 * t66 * t97 - t114 * t94 + t67;
    result__[ 11  ] = result__[7];
    real_type t118 = zeta__dot_D_2_2(t29, t30, t3, t31);
    real_type t121 = t2 * MU__[1];
    real_type t122 = sin(t30);
    real_type t124 = t122 * t29 * t121;
    result__[ 12  ] = -t118 * t2 * t97 + t118 * t28 - t124;
    real_type t127 = zeta__dot_D_1_2(t29, t30, t3, t31);
    real_type t129 = cos(t30);
    result__[ 13  ] = -t127 * t2 * t97 + t121 * t129 + t127 * t28;
    result__[ 14  ] = t121 * t129 * t29 - t114 * t97 + t28 * t68;
    real_type t137 = t2 * t78;
    result__[ 15  ] = -t2 * t76 * t97 - t137 * t94 + t77;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t141 = X__[iX_fx];
    real_type t142 = t141 * t141;
    real_type t144 = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t145 = 1.0 / t144;
    real_type t148 = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t149 = 1.0 / t148;
    real_type t151 = X__[iX_Omega];
    real_type t152 = t151 * t151;
    real_type t153 = t29 * t29;
    real_type t156 = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t157 = 1.0 / t156;
    real_type t160 = t149 * t152 * t153 * t157 + t142 * t145 * t149 - 1;
    real_type t161 = ALIAS_AdherenceEllipse_DD(t160);
    real_type t162 = t161 * t2;
    real_type t163 = t152 * t152;
    real_type t165 = t156 * t156;
    real_type t166 = 1.0 / t165;
    real_type t168 = t148 * t148;
    real_type t169 = 1.0 / t168;
    real_type t173 = ALIAS_AdherenceEllipse_D(t160);
    real_type t174 = t173 * t2;
    real_type t180 = ModelPars[iM_m];
    real_type t181 = ModelPars[iM_Pmax];
    real_type t182 = 1.0 / t181;
    real_type t183 = t182 * t180;
    real_type t185 = t141 * t183 * t29 - 1;
    real_type t186 = ALIAS_PowerLimit_DD(t185);
    real_type t187 = t186 * t2;
    real_type t188 = t180 * t180;
    real_type t190 = t181 * t181;
    real_type t191 = 1.0 / t190;
    real_type t194 = zeta__dot_D_1_1(t29, t30, t3, t31);
    real_type t198 = MU__[3];
    real_type t199 = ModelPars[iM_kD];
    real_type t200 = t199 * t198;
    result__[ 18  ] = 4 * t153 * t162 * t163 * t166 * t169 + t142 * t187 * t188 * t191 + 2 * t149 * t152 * t157 * t174 - t194 * t2 * t97 + t194 * t28 - 2 * t2 * t200;
    real_type t209 = t151 * t174;
    real_type t210 = t157 * t29;
    real_type t211 = t149 * t210;
    result__[ 19  ] = 4 * t151 * t152 * t153 * t162 * t166 * t169 * t29 + 4 * t209 * t211;
    real_type t214 = t145 * t141;
    real_type t215 = t214 * t162;
    real_type t224 = ALIAS_PowerLimit_D(t185);
    real_type t225 = t224 * t2;
    result__[ 20  ] = t141 * t187 * t188 * t191 * t29 + 4 * t152 * t169 * t210 * t215 + t183 * t225;
    result__[ 21  ] = t141 * t180 * t182 * t225 + 2 * t152 * t174 * t211 - 2 * t2 * t200 * t29 + t121 * t122 - t137 * t97 + t28 * t78;
    result__[ 22  ] = result__[19];
    real_type t240 = t153 * t153;
    real_type t245 = t157 * t153;
    real_type t246 = t149 * t245;
    result__[ 23  ] = 4 * t152 * t162 * t166 * t169 * t240 + 2 * t174 * t246;
    result__[ 24  ] = 4 * t245 * t151 * t169 * t215;
    result__[ 25  ] = t2 * t41 + 2 * t209 * t246;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t255 = t144 * t144;
    result__[ 28  ] = 4 * t169 / t255 * t142 * t162 + 2 * t149 * t145 * t174 + t191 * t188 * t153 * t187;
    result__[ 29  ] = t180 * t182 * t225 * t29 + 2 * t149 * t174 * t214 + t198 * t2;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t276 = U__[iU_v__fx];
    real_type t277 = v__fxControl(t276, -1, 1);
    real_type t279 = U__[iU_v__Omega];
    real_type t280 = v__OmegaControl(t279, -1, 1);
    real_type t282 = AdherenceEllipse(t160);
    real_type t284 = RoadLeftBorder(t6);
    real_type t286 = RoadRightBorder(t17);
    real_type t288 = PowerLimit(t185);
    real_type t300 = t2 * MU__[4];
    real_type t301 = ModelPars[iM_v__Omega__max];
    real_type t305 = t2 * MU__[5];
    real_type t306 = ModelPars[iM_v__fx__max];
    result__[ 36  ] = t2 * ModelPars[iM_wT] + t277 * t2 + t280 * t2 + t282 * t2 + t284 * t2 + t286 * t2 + t288 * t2 + t42 * t28 + t124 - t2 * (t31 * t42 - t151) * t41 + t2 * (-t153 * t199 + t141) * t198 + t301 * t279 * t300 + t306 * t276 * t305;
    real_type t309 = ALIAS_v__fxControl_D_1(t276, -1, 1);
    result__[ 37  ] = t2 * t309 + t305 * t306;
    real_type t312 = ALIAS_v__OmegaControl_D_1(t279, -1, 1);
    result__[ 38  ] = t2 * t312 + t300 * t301;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 39, i_segment );
  }

}

// EOF: PointMassCarModel_4_Methods_AdjointODE.cc
