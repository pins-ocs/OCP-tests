/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  PointMassCarModel_1::Hx_numEqns() const
  { return 5; }

  void
  PointMassCarModel_1::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = 1.0 / t9;
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t16  = X__[iX_Omega];
    real_type t17  = t16 * t16;
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = 1.0 / t21;
    real_type t23  = t14 * t22;
    real_type t25  = -t14 * t10 * t7 - t23 * t18 * t17 + 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = ModelPars[iM_m];
    real_type t30  = ModelPars[iM_Pmax];
    real_type t31  = 1.0 / t30;
    real_type t34  = -t31 * t29 * t6 * t1 + 1;
    real_type t35  = PowerLimit(t34);
    real_type t37  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t39  = Q__[iQ_leftWidth] - t3;
    real_type t40  = ALIAS_RoadLeftBorder_D(t39);
    real_type t42  = RoadLeftBorder(t39);
    real_type t45  = Q__[iQ_rightWidth] + t3;
    real_type t46  = RoadRightBorder(t45);
    real_type t47  = LimitMinSpeed(t1);
    real_type t48  = L__[iL_lambda1__xo];
    real_type t49  = t1 * t48;
    real_type t50  = sin(t2);
    real_type t51  = t50 * t49;
    real_type t52  = ModelPars[iM_kD];
    real_type t55  = L__[iL_lambda3__xo];
    real_type t61  = U__[iU_v__Omega] * L__[iL_lambda4__xo] * ModelPars[iM_v__Omega__max];
    real_type t66  = L__[iL_lambda5__xo] * U__[iU_v__fx] * ModelPars[iM_v__fx__max];
    real_type t67  = L__[iL_lambda2__xo];
    real_type t68  = t67 * t16;
    real_type t69  = ModelPars[iM_wT];
    real_type t72  = ALIAS_RoadRightBorder_D(t45);
    result__[ 0   ] = t26 * t5 + t35 * t5 - t40 * t37 + t42 * t5 + t5 * (t46 + t47 + t51 + t55 * (-t18 * t52 + t6) + t61 + t66 + t68 + t69) + t72 * t37;
    real_type t74  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    real_type t81  = -t52 * t18 * t55 + t6 * t55 + t46 + t47 + t51 + t61 + t66 + t68 + t69;
    real_type t83  = cos(t2);
    result__[ 1   ] = t37 * t83 * t49 + t26 * t74 + t35 * t74 + t42 * t74 + t74 * t81;
    real_type t86  = ALIAS_AdherenceEllipse_D(t25);
    real_type t93  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t97  = ALIAS_PowerLimit_D(t34);
    real_type t107 = ALIAS_LimitMinSpeed_D(t1);
    result__[ 2   ] = t31 * t14 * t22 * (-2 * t30 * t1 * t17 * t86 * t37 + (t26 * t93 * t30 - t97 * t37 * t29 * t6 + (t35 * t93 + t42 * t93 + t93 * t81 + (-2 * t55 * t52 * t1 + t50 * t48 + t107) * t37) * t30) * t13 * t21);
    result__[ 3   ] = t23 * (t21 * t13 * t67 - 2 * t16 * t18 * t86) * t37;
    result__[ 4   ] = t31 * t14 * t10 * t37 * (-2 * t30 * t6 * t86 + (-t97 * t1 * t29 + t30 * t55) * t13 * t9);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DHxDx_numRows() const
  { return 5; }

  integer
  PointMassCarModel_1::DHxDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_1::DHxDx_nnz() const
  { return 25; }

  void
  PointMassCarModel_1::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 4   ;
    iIndex[15] = 3   ; jIndex[15] = 0   ;
    iIndex[16] = 3   ; jIndex[16] = 1   ;
    iIndex[17] = 3   ; jIndex[17] = 2   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 4   ; jIndex[20] = 0   ;
    iIndex[21] = 4   ; jIndex[21] = 1   ;
    iIndex[22] = 4   ; jIndex[22] = 2   ;
    iIndex[23] = 4   ; jIndex[23] = 3   ;
    iIndex[24] = 4   ; jIndex[24] = 4   ;
  }

  void
  PointMassCarModel_1::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = 1.0 / t9;
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t16  = X__[iX_Omega];
    real_type t17  = t16 * t16;
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = 1.0 / t21;
    real_type t23  = t14 * t22;
    real_type t25  = -t14 * t10 * t7 - t23 * t18 * t17 + 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = ModelPars[iM_m];
    real_type t30  = ModelPars[iM_Pmax];
    real_type t31  = 1.0 / t30;
    real_type t34  = -t31 * t29 * t6 * t1 + 1;
    real_type t35  = PowerLimit(t34);
    real_type t37  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t39  = Q__[iQ_leftWidth] - t3;
    real_type t40  = ALIAS_RoadLeftBorder_DD(t39);
    real_type t42  = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t43  = ALIAS_RoadLeftBorder_D(t39);
    real_type t46  = RoadLeftBorder(t39);
    real_type t49  = Q__[iQ_rightWidth] + t3;
    real_type t50  = RoadRightBorder(t49);
    real_type t51  = LimitMinSpeed(t1);
    real_type t52  = L__[iL_lambda1__xo];
    real_type t53  = t1 * t52;
    real_type t54  = sin(t2);
    real_type t55  = t54 * t53;
    real_type t56  = ModelPars[iM_kD];
    real_type t57  = t18 * t56;
    real_type t59  = L__[iL_lambda3__xo];
    real_type t65  = ModelPars[iM_v__Omega__max] * U__[iU_v__Omega] * L__[iL_lambda4__xo];
    real_type t70  = ModelPars[iM_v__fx__max] * U__[iU_v__fx] * L__[iL_lambda5__xo];
    real_type t71  = L__[iL_lambda2__xo];
    real_type t72  = t71 * t16;
    real_type t73  = ModelPars[iM_wT];
    real_type t76  = ALIAS_RoadRightBorder_D(t49);
    real_type t79  = ALIAS_RoadRightBorder_DD(t49);
    result__[ 0   ] = t26 * t5 + t35 * t5 + t40 * t37 - 2 * t43 * t42 + t46 * t5 + t5 * (t50 + t51 + t55 + t59 * (-t57 + t6) + t65 + t70 + t72 + t73) + 2 * t76 * t42 + t79 * t37;
    real_type t81  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t84  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    real_type t89  = -t59 * t57 + t59 * t6 + t50 + t51 + t55 + t65 + t70 + t72 + t73;
    real_type t91  = cos(t2);
    result__[ 1   ] = t42 * t91 * t53 + t26 * t81 + t35 * t81 - t43 * t84 + t46 * t81 + t76 * t84 + t81 * t89;
    real_type t95  = ALIAS_AdherenceEllipse_D(t25);
    real_type t97  = t1 * t17;
    real_type t98  = t30 * t97;
    real_type t101 = t13 * t21;
    real_type t102 = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t105 = ALIAS_PowerLimit_D(t34);
    real_type t107 = t29 * t6;
    real_type t110 = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t115 = t59 * t56 * t1;
    real_type t117 = t54 * t52;
    real_type t118 = ALIAS_LimitMinSpeed_D(t1);
    real_type t119 = -2 * t115 + t117 + t118;
    real_type t128 = t31 * t14;
    result__[ 2   ] = t128 * t22 * (-2 * t98 * t95 * t42 + (t30 * t26 * t102 - t107 * t105 * t42 + (t35 * t102 + t46 * t102 + t102 * t89 - t43 * t110 + t76 * t110 + t42 * t119) * t30) * t101);
    real_type t134 = t21 * t13 * t71 - 2 * t16 * t18 * t95;
    result__[ 3   ] = t23 * t134 * t42;
    real_type t139 = t13 * t9;
    real_type t145 = -2 * t30 * t6 * t95 + (-t105 * t1 * t29 + t30 * t59) * t139;
    real_type t148 = t14 * t31 * t10;
    result__[ 4   ] = t148 * t42 * t145;
    result__[ 5   ] = result__[1];
    real_type t149 = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = t26 * t149 + t35 * t149 + t46 * t149 + t149 * t89 + 2 * (t84 * t91 - t54 * t37 / 2) * t53;
    real_type t163 = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t173 = t110 * t1;
    real_type t174 = t173 + t37;
    result__[ 7   ] = t128 * t22 * (-2 * t98 * t95 * t84 + (t30 * t26 * t163 - t107 * t105 * t84 + t30 * (t174 * t91 * t52 + t84 * t119 + t35 * t163 + t46 * t163 + t163 * t89)) * t101);
    result__[ 8   ] = t23 * t134 * t84;
    result__[ 9   ] = t148 * t84 * t145;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t187 = t30 * t30;
    real_type t192 = ALIAS_AdherenceEllipse_DD(t25);
    real_type t193 = t192 * t37;
    real_type t194 = t17 * t17;
    real_type t199 = t21 * t21;
    real_type t200 = t13 * t13;
    real_type t201 = t200 * t199;
    real_type t202 = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t205 = t29 * t29;
    real_type t207 = ALIAS_PowerLimit_DD(t34);
    real_type t222 = ALIAS_LimitMinSpeed_DD(t1);
    real_type t234 = 1.0 / t199;
    real_type t236 = 1.0 / t200;
    real_type t237 = 1.0 / t187;
    result__[ 12  ] = t237 * t236 * t234 * (-4 * t95 * t187 * t17 * (t173 + t37 / 2) * t101 + 4 * t187 * t18 * t194 * t193 + (t187 * t26 * t202 + t37 * t207 * t7 * t205 + t30 * (-2 * t105 * t110 * t107 + (t35 * t202 + t46 * t202 + t202 * t89 + t110 * (-4 * t115 + 2 * t117 + 2 * t118) - 2 * (t59 * t56 - t222 / 2) * t37) * t30)) * t201);
    result__[ 13  ] = t236 * t234 * (-4 * t95 * (t173 / 2 + t37) * t1 * t21 * t16 * t13 + t201 * t110 * t71 + 4 * t18 * t1 * t17 * t16 * t193);
    real_type t261 = t95 * t187;
    result__[ 14  ] = t237 * t22 * t236 * t10 * (4 * t187 * t97 * t6 * t193 + (-2 * t261 * t6 * t110 + t9 * t13 * (t6 * t1 * t207 * t37 * t205 - t105 * t174 * t30 * t29 + t187 * t110 * t59)) * t101);
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    result__[ 18  ] = -2 * t236 * t234 * (t21 * t13 * t95 - 2 * t17 * t18 * t192) * t18 * t37;
    result__[ 19  ] = 4 * t22 * t18 * t16 * t236 * t10 * t6 * t193;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t301 = t9 * t9;
    result__[ 24  ] = t237 * t236 / t301 * (t301 * t205 * t200 * t18 * t207 + 4 * t187 * t7 * t192 - 2 * t139 * t261) * t37;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 25, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DHxDp_numRows() const
  { return 5; }

  integer
  PointMassCarModel_1::DHxDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_1::DHxDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  integer
  PointMassCarModel_1::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t8   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = t8 * ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo];
    result__[ 1   ] = t8 * ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DHuDx_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DHuDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_1::DHuDx_nnz() const
  { return 6; }

  void
  PointMassCarModel_1::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t3   = L__[iL_lambda5__xo] * ModelPars[iM_v__fx__max];
    real_type t4   = X__[iX_V];
    real_type t5   = X__[iX_alpha];
    real_type t6   = X__[iX_n];
    real_type t7   = Q__[iQ_Kappa];
    real_type t8   = inv_zeta__dot_D_3(t4, t5, t6, t7);
    result__[ 0   ] = t8 * t3;
    real_type t9   = inv_zeta__dot_D_2(t4, t5, t6, t7);
    result__[ 1   ] = t9 * t3;
    real_type t10  = inv_zeta__dot_D_1(t4, t5, t6, t7);
    result__[ 2   ] = t10 * t3;
    real_type t13  = L__[iL_lambda4__xo] * ModelPars[iM_v__Omega__max];
    result__[ 3   ] = t8 * t13;
    result__[ 4   ] = t13 * t9;
    result__[ 5   ] = t10 * t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DHuDp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DHuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_1::DHuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  PointMassCarModel_1::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_1::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DHpDp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_1::DHpDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_1::DHpDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  PointMassCarModel_1::eta_numEqns() const
  { return 5; }

  void
  PointMassCarModel_1::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DetaDx_numRows() const
  { return 5; }

  integer
  PointMassCarModel_1::DetaDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_1::DetaDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DetaDp_numRows() const
  { return 5; }

  integer
  PointMassCarModel_1::DetaDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_1::DetaDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  PointMassCarModel_1::nu_numEqns() const
  { return 5; }

  void
  PointMassCarModel_1::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DnuDx_numRows() const
  { return 5; }

  integer
  PointMassCarModel_1::DnuDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_1::DnuDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DnuDp_numRows() const
  { return 5; }

  integer
  PointMassCarModel_1::DnuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_1::DnuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_1::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_1_Methods_AdjointODE.cc
