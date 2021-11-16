/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  PointMassCarModel_2::Hx_numEqns() const
  { return 5; }

  void
  PointMassCarModel_2::Hx_eval(
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
    real_type t1   = X__[iX_fx];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t5   = 1.0 / t4;
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t11  = X__[iX_Omega];
    real_type t12  = t11 * t11;
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t18  = 1.0 / t17;
    real_type t19  = t9 * t18;
    real_type t21  = -t19 * t14 * t12 - t9 * t5 * t2 + 1;
    real_type t22  = AdherenceEllipse(t21);
    real_type t23  = X__[iX_alpha];
    real_type t24  = X__[iX_n];
    real_type t25  = Q__[iQ_Kappa];
    real_type t26  = zeta__dot_D_3(t13, t23, t24, t25);
    real_type t29  = ModelPars[iM_m];
    real_type t30  = ModelPars[iM_Pmax];
    real_type t31  = 1.0 / t30;
    real_type t34  = -t31 * t29 * t1 * t13 + 1;
    real_type t35  = PowerLimit(t34);
    real_type t38  = Q__[iQ_leftWidth] - t24;
    real_type t39  = ALIAS_RoadLeftBorder_D(t38);
    real_type t40  = zeta__dot(t13, t23, t24, t25);
    real_type t42  = RoadLeftBorder(t38);
    real_type t46  = L__[iL_lambda2__xo];
    real_type t48  = L__[iL_lambda1__xo];
    real_type t52  = L__[iL_lambda3__xo];
    real_type t61  = t40 * t40;
    real_type t64  = LimitMinSpeed(t13);
    real_type t66  = Q__[iQ_rightWidth] + t24;
    real_type t67  = RoadRightBorder(t66);
    real_type t68  = t61 * (t46 * (-V__[1] - t25) - V__[0] * t48 - t52 * V__[2] - V__[3] * L__[iL_lambda5__xo] - V__[4] * L__[iL_lambda4__xo]) - ModelPars[iM_wT] - t64 - t67;
    real_type t70  = ALIAS_RoadRightBorder_D(t66);
    real_type t73  = 1.0 / t61;
    result__[ 0   ] = t73 * (-t26 * t22 - t26 * t35 - t26 * t42 + t26 * t68 - t40 * t39 + t40 * t70);
    real_type t74  = zeta__dot_D_2(t13, t23, t24, t25);
    real_type t80  = cos(t23);
    result__[ 1   ] = t73 * (t61 * t80 * t13 * t48 - t74 * t22 - t74 * t35 - t74 * t42 + t74 * t68);
    real_type t84  = ALIAS_AdherenceEllipse_D(t21);
    real_type t90  = zeta__dot_D_1(t13, t23, t24, t25);
    real_type t94  = ALIAS_PowerLimit_D(t34);
    real_type t104 = sin(t23);
    real_type t108 = ALIAS_LimitMinSpeed_D(t13);
    result__[ 2   ] = t31 * t19 * t73 * (-2 * t30 * t40 * t13 * t12 * t84 + t8 * (-t22 * t90 * t30 - t94 * t40 * t29 * t1 + t30 * (-t35 * t90 - t42 * t90 + t90 * t68 + (t40 * (-2 * t13 * ModelPars[iM_kD] * t52 + t104 * t48) + t108) * t40)) * t17);
    real_type t119 = 1.0 / t40;
    real_type t120 = t84 * t119;
    result__[ 3   ] = -2 * t9 * t18 * t14 * t11 * t120 + t46;
    result__[ 4   ] = -t31 * t29 * t13 * t94 * t119 - 2 * t9 * t5 * t1 * t120 + t52;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DHxDx_numRows() const
  { return 5; }

  integer
  PointMassCarModel_2::DHxDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_2::DHxDx_nnz() const
  { return 25; }

  void
  PointMassCarModel_2::DHxDx_pattern(
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
  PointMassCarModel_2::DHxDx_sparse(
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t8   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t9   = t8 * t8;
    real_type t11  = -t6 * t5 + 2 * t9;
    real_type t12  = X__[iX_fx];
    real_type t13  = t12 * t12;
    real_type t15  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t16  = 1.0 / t15;
    real_type t19  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t20  = 1.0 / t19;
    real_type t22  = X__[iX_Omega];
    real_type t23  = t22 * t22;
    real_type t24  = t1 * t1;
    real_type t25  = t24 * t23;
    real_type t27  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t28  = 1.0 / t27;
    real_type t29  = t20 * t28;
    real_type t31  = -t20 * t16 * t13 - t29 * t25 + 1;
    real_type t32  = AdherenceEllipse(t31);
    real_type t34  = t12 * t1;
    real_type t35  = ModelPars[iM_m];
    real_type t36  = ModelPars[iM_Pmax];
    real_type t37  = 1.0 / t36;
    real_type t40  = -t37 * t35 * t34 + 1;
    real_type t41  = PowerLimit(t40);
    real_type t44  = Q__[iQ_leftWidth] - t3;
    real_type t45  = RoadLeftBorder(t44);
    real_type t47  = ALIAS_RoadLeftBorder_DD(t44);
    real_type t48  = t5 * t5;
    real_type t50  = ALIAS_RoadLeftBorder_D(t44);
    real_type t55  = V__[1] + t4;
    real_type t56  = L__[iL_lambda2__xo];
    real_type t58  = L__[iL_lambda1__xo];
    real_type t60  = V__[0] * t58;
    real_type t62  = L__[iL_lambda3__xo];
    real_type t63  = t62 * V__[2];
    real_type t66  = V__[3] * L__[iL_lambda5__xo];
    real_type t69  = V__[4] * L__[iL_lambda4__xo];
    real_type t70  = t56 * t55 + t60 + t63 + t66 + t69;
    real_type t72  = t48 * t5;
    real_type t75  = Q__[iQ_rightWidth] + t3;
    real_type t76  = ALIAS_RoadRightBorder_DD(t75);
    real_type t79  = LimitMinSpeed(t1);
    real_type t80  = RoadRightBorder(t75);
    real_type t81  = -ModelPars[iM_wT] - t79 - t80;
    real_type t83  = ALIAS_RoadRightBorder_D(t75);
    real_type t88  = -t81;
    real_type t92  = 1.0 / t72;
    result__[ 0   ] = t92 * (t32 * t11 + t41 * t11 + t45 * t11 + t48 * t47 + 2 * t5 * t8 * t50 - t72 * t6 * t70 + t48 * t76 + t5 * (t6 * t81 - 2 * t83 * t8) + 2 * t88 * t9);
    real_type t93  = zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t95  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t96  = t8 * t95;
    real_type t98  = -t5 * t93 + 2 * t96;
    result__[ 1   ] = t92 * (t32 * t98 + t41 * t98 + t45 * t98 + t5 * t95 * t50 - t72 * t93 * t70 + t5 * (t93 * t81 - t95 * t83) + 2 * t88 * t96);
    real_type t113 = t19 * t36;
    real_type t114 = zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t116 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t117 = t8 * t116;
    real_type t119 = t114 * t5 - 2 * t117;
    real_type t123 = ALIAS_AdherenceEllipse_D(t31);
    real_type t125 = t1 * t23 * t123;
    real_type t126 = t5 * t8;
    real_type t132 = t35 * t12;
    real_type t133 = ALIAS_PowerLimit_D(t40);
    real_type t137 = t116 * t5;
    real_type t142 = ALIAS_LimitMinSpeed_D(t1);
    real_type t156 = t37 * t29;
    result__[ 2   ] = t156 * t92 * (-t32 * t119 * t27 * t113 + 2 * t36 * t126 * t125 - t19 * (t41 * t119 * t36 - t133 * t126 * t132 + (t45 * t119 - t50 * t137 + t72 * t114 * t70 + t5 * (t114 * t88 + t83 * t116 + t142 * t8) - 2 * t88 * t117) * t36) * t27);
    real_type t157 = 1.0 / t48;
    real_type t159 = t22 * t123 * t157;
    real_type t160 = t28 * t24;
    result__[ 3   ] = 2 * t8 * t20 * t160 * t159;
    real_type t171 = t15 * t35 * t19 * t1 * t133 + 2 * t36 * t12 * t123;
    real_type t175 = t37 * t20 * t16;
    result__[ 4   ] = t175 * t157 * t171 * t8;
    result__[ 5   ] = result__[1];
    real_type t176 = zeta__dot_D_2_2(t1, t2, t3, t4);
    real_type t178 = t95 * t95;
    real_type t180 = -t176 * t5 + 2 * t178;
    real_type t186 = -t56 * t55 - t60 - t63 - t66 - t69;
    real_type t189 = sin(t2);
    result__[ 6   ] = t92 * (t32 * t180 + t41 * t180 + t45 * t180 + t72 * (-t189 * t1 * t58 + t176 * t186) - t5 * t88 * t176 + 2 * t88 * t178);
    real_type t198 = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t200 = t95 * t116;
    real_type t202 = t5 * t198 - 2 * t200;
    real_type t206 = t5 * t95;
    real_type t217 = cos(t2);
    result__[ 7   ] = t156 * t92 * (-t32 * t202 * t27 * t113 + 2 * t36 * t206 * t125 + t19 * (-t41 * t202 * t36 + t133 * t206 * t132 + (-t45 * t202 + t72 * (t198 * t186 + t217 * t58) + t5 * (-t142 * t95 + t198 * t81) + 2 * t88 * t200) * t36) * t27);
    result__[ 8   ] = 2 * t95 * t20 * t160 * t159;
    result__[ 9   ] = t175 * t157 * t171 * t95;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t241 = t36 * t36;
    real_type t242 = t1 * t116;
    real_type t246 = t123 * t19;
    real_type t250 = t27 * t27;
    real_type t252 = t19 * t19;
    real_type t253 = zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t255 = t116 * t116;
    real_type t257 = t253 * t5 - 2 * t255;
    real_type t261 = ALIAS_AdherenceEllipse_DD(t31);
    real_type t262 = t23 * t23;
    real_type t270 = ALIAS_PowerLimit_DD(t40);
    real_type t272 = t35 * t35;
    real_type t285 = ALIAS_LimitMinSpeed_DD(t1);
    real_type t303 = 1.0 / t241;
    real_type t304 = 1.0 / t250;
    real_type t306 = 1.0 / t252;
    result__[ 12  ] = t306 * t304 * t303 * t92 * (4 * t246 * (t242 - t5 / 2) * t241 * t27 * t5 * t23 - t32 * t257 * t252 * t250 * t241 + 4 * t241 * t48 * t24 * t262 * t261 - t252 * (t41 * t257 * t241 - t48 * t272 * t13 * t270 + t36 * (-2 * t133 * t137 * t132 + t36 * (t45 * t257 + t72 * (t253 * t70 + 2 * ModelPars[iM_kD] * t62) - t48 * t285 + t5 * (2 * t142 * t116 + t253 * t88) - 2 * t88 * t255))) * t250);
    real_type t308 = t27 * t19;
    result__[ 13  ] = -4 * t306 * t304 * t157 * t1 * t22 * (t123 * (-t242 / 2 + t5) * t308 - t25 * t261 * t5);
    result__[ 14  ] = t303 * t28 * t306 * t16 * t157 * (4 * t241 * t5 * t1 * t23 * t12 * t261 - (-2 * t123 * t241 * t12 * t116 + t35 * (t133 * (-t242 + t5) * t36 - t35 * t34 * t270 * t5) * t15 * t19) * t308);
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t355 = 1.0 / t5;
    result__[ 18  ] = -2 * t306 * t304 * t355 * (-2 * t23 * t24 * t261 + t27 * t246) * t24;
    result__[ 19  ] = 4 * t160 * t22 * t306 * t16 * t12 * t261 * t355;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t367 = t15 * t15;
    result__[ 24  ] = t303 * t306 / t367 * t355 * (t252 * t367 * t272 * t24 * t270 - 2 * t241 * t19 * t15 * t123 + 4 * t241 * t13 * t261);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 25, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DHxDp_numRows() const
  { return 5; }

  integer
  PointMassCarModel_2::DHxDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DHxDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHxDp_sparse(
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
  PointMassCarModel_2::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda4__xo] * ModelPars[iM_v__fx__max];
    result__[ 1   ] = L__[iL_lambda5__xo] * ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DHuDx_numRows() const
  { return 2; }

  integer
  PointMassCarModel_2::DHuDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_2::DHuDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DHuDp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_2::DHuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DHuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHuDp_sparse(
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
  PointMassCarModel_2::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_2::Hp_eval(
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
  PointMassCarModel_2::DHpDp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_2::DHpDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DHpDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHpDp_sparse(
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
  PointMassCarModel_2::eta_numEqns() const
  { return 5; }

  void
  PointMassCarModel_2::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = L__[iL_lambda1__xo] * t5;
    result__[ 1   ] = L__[iL_lambda2__xo] * t5;
    result__[ 2   ] = L__[iL_lambda3__xo] * t5;
    result__[ 3   ] = L__[iL_lambda5__xo] * t5;
    result__[ 4   ] = L__[iL_lambda4__xo] * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DetaDx_numRows() const
  { return 5; }

  integer
  PointMassCarModel_2::DetaDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_2::DetaDx_nnz() const
  { return 15; }

  void
  PointMassCarModel_2::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 0   ;
    iIndex[10] = 3   ; jIndex[10] = 1   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DetaDx_sparse(
    NodeType2 const    & NODE__,
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
    real_type t5   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = L__[iL_lambda1__xo];
    result__[ 0   ] = t6 * t5;
    real_type t7   = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t6 * t7;
    real_type t8   = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t6 * t8;
    real_type t9   = L__[iL_lambda2__xo];
    result__[ 3   ] = t9 * t5;
    result__[ 4   ] = t9 * t7;
    result__[ 5   ] = t9 * t8;
    real_type t10  = L__[iL_lambda3__xo];
    result__[ 6   ] = t10 * t5;
    result__[ 7   ] = t10 * t7;
    result__[ 8   ] = t10 * t8;
    real_type t11  = L__[iL_lambda5__xo];
    result__[ 9   ] = t11 * t5;
    result__[ 10  ] = t11 * t7;
    result__[ 11  ] = t11 * t8;
    real_type t12  = L__[iL_lambda4__xo];
    result__[ 12  ] = t12 * t5;
    result__[ 13  ] = t12 * t7;
    result__[ 14  ] = t12 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DetaDx_sparse", 15, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DetaDp_numRows() const
  { return 5; }

  integer
  PointMassCarModel_2::DetaDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DetaDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DetaDp_sparse(
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
  PointMassCarModel_2::nu_numEqns() const
  { return 5; }

  void
  PointMassCarModel_2::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = V__[0] * t5;
    result__[ 1   ] = V__[1] * t5;
    result__[ 2   ] = V__[2] * t5;
    result__[ 3   ] = V__[4] * t5;
    result__[ 4   ] = V__[3] * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DnuDx_numRows() const
  { return 5; }

  integer
  PointMassCarModel_2::DnuDx_numCols() const
  { return 5; }

  integer
  PointMassCarModel_2::DnuDx_nnz() const
  { return 15; }

  void
  PointMassCarModel_2::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 0   ;
    iIndex[10] = 3   ; jIndex[10] = 1   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = V__[0];
    result__[ 0   ] = t6 * t5;
    real_type t7   = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t6 * t7;
    real_type t8   = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t6 * t8;
    real_type t9   = V__[1];
    result__[ 3   ] = t9 * t5;
    result__[ 4   ] = t9 * t7;
    result__[ 5   ] = t9 * t8;
    real_type t10  = V__[2];
    result__[ 6   ] = t10 * t5;
    result__[ 7   ] = t10 * t7;
    result__[ 8   ] = t10 * t8;
    real_type t11  = V__[4];
    result__[ 9   ] = t11 * t5;
    result__[ 10  ] = t11 * t7;
    result__[ 11  ] = t11 * t8;
    real_type t12  = V__[3];
    result__[ 12  ] = t12 * t5;
    result__[ 13  ] = t12 * t7;
    result__[ 14  ] = t12 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DnuDx_sparse", 15, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DnuDp_numRows() const
  { return 5; }

  integer
  PointMassCarModel_2::DnuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DnuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
