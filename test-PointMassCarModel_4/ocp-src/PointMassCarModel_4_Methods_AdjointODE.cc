/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_AdjointODE.cc                      |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  PointMassCarModel_4::Hx_numEqns() const
  { return 7; }

  void
  PointMassCarModel_4::Hx_eval(
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
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_leftWidth(t3);
    real_type t5   = X__[iX_n];
    real_type t6   = t4 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_D(t6);
    real_type t8   = ALIAS_leftWidth_D(t3);
    real_type t10  = ALIAS_Kappa_D(t3);
    real_type t11  = L__[iL_lambda3__xo];
    real_type t12  = ALIAS_Kappa(t3);
    real_type t15  = -t12 * t11 + L__[iL_lambda1__xo];
    real_type t17  = X__[iX_V];
    real_type t18  = X__[iX_alpha];
    real_type t19  = zeta__dot_D_4(t17, t18, t5, t12);
    real_type t21  = zeta__dot(t17, t18, t5, t12);
    real_type t24  = ALIAS_rightWidth(t3);
    real_type t25  = t24 + t5;
    real_type t26  = ALIAS_RoadRightBorder_D(t25);
    real_type t27  = ALIAS_rightWidth_D(t3);
    result__[ 0   ] = (-t11 * t21 * t10 + t19 * t15 * t10 + t27 * t26 + t7 * t8) * t2;
    real_type t30  = zeta__dot_D_3(t17, t18, t5, t12);
    result__[ 1   ] = (t30 * t15 + t26 - t7) * t2;
    real_type t33  = zeta__dot_D_2(t17, t18, t5, t12);
    real_type t35  = cos(t18);
    real_type t36  = L__[iL_lambda2__xo];
    result__[ 2   ] = (t17 * t36 * t35 + t33 * t15) * t2;
    real_type t40  = X__[iX_fx];
    real_type t41  = t40 * t40;
    real_type t43  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t44  = 1.0 / t43;
    real_type t47  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t48  = 1.0 / t47;
    real_type t50  = X__[iX_Omega];
    real_type t51  = t50 * t50;
    real_type t52  = t17 * t17;
    real_type t55  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t57  = t48 / t55;
    real_type t59  = -t48 * t44 * t41 - t57 * t52 * t51 + 1;
    real_type t60  = ALIAS_AdherenceEllipse_D(t59);
    real_type t62  = ModelPars[iM_Pmax];
    real_type t66  = ModelPars[iM_m];
    real_type t69  = 1.0 / t62;
    real_type t72  = -t69 * t66 * t40 * t17 + 1;
    real_type t73  = ALIAS_PowerLimit_D(t72);
    real_type t75  = zeta__dot_D_1(t17, t18, t5, t12);
    real_type t77  = ModelPars[iM_kD];
    real_type t78  = L__[iL_lambda4__xo];
    real_type t82  = sin(t18);
    result__[ 3   ] = t69 * t57 * (-2 * t62 * t51 * t17 * t60 + t47 * t55 * (-t73 * t66 * t40 + (-2 * t17 * t78 * t77 + t75 * t15 + t36 * t82) * t62)) * t2;
    result__[ 4   ] = t57 * (t55 * t47 * t11 - 2 * t50 * t52 * t60) * t2;
    result__[ 5   ] = t69 * t48 * t44 * (-2 * t62 * t40 * t60 + (-t73 * t66 * t17 + t62 * t78) * t43 * t47) * t2;
    real_type t112 = AdherenceEllipse(t59);
    real_type t113 = PowerLimit(t72);
    real_type t114 = RoadLeftBorder(t6);
    real_type t116 = RoadRightBorder(t25);
    real_type t134 = t112 + t113 + t114 + t21 * t15 + t116 + t82 * t17 * t36 + t50 * t11 + (-t52 * t77 + t40) * t78 + L__[iL_lambda5__xo] * U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] + L__[iL_lambda6__xo] * U__[iU_v__fx] * ModelPars[iM_v__fx__max] + ModelPars[iM_wT];
    result__[ 6   ] = t2 * t134;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DHxDx_numRows() const
  { return 7; }

  integer
  PointMassCarModel_4::DHxDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_4::DHxDx_nnz() const
  { return 37; }

  void
  PointMassCarModel_4::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
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
  }

  void
  PointMassCarModel_4::DHxDx_sparse(
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
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_leftWidth(t3);
    real_type t5   = X__[iX_n];
    real_type t6   = t4 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = ALIAS_leftWidth_D(t3);
    real_type t9   = t8 * t8;
    real_type t11  = ALIAS_RoadLeftBorder_D(t6);
    real_type t12  = ALIAS_leftWidth_DD(t3);
    real_type t14  = L__[iL_lambda3__xo];
    real_type t15  = ALIAS_Kappa(t3);
    real_type t18  = -t15 * t14 + L__[iL_lambda1__xo];
    real_type t19  = ALIAS_Kappa_DD(t3);
    real_type t21  = ALIAS_Kappa_D(t3);
    real_type t22  = t21 * t21;
    real_type t26  = X__[iX_V];
    real_type t27  = X__[iX_alpha];
    real_type t28  = zeta__dot_D_4(t26, t27, t5, t15);
    real_type t31  = zeta__dot_D_4_4(t26, t27, t5, t15);
    real_type t33  = zeta__dot(t26, t27, t5, t15);
    real_type t36  = ALIAS_rightWidth(t3);
    real_type t37  = t36 + t5;
    real_type t38  = ALIAS_RoadRightBorder_DD(t37);
    real_type t39  = ALIAS_rightWidth_D(t3);
    real_type t40  = t39 * t39;
    real_type t42  = ALIAS_RoadRightBorder_D(t37);
    real_type t43  = ALIAS_rightWidth_DD(t3);
    result__[ 0   ] = (t9 * t7 + t12 * t11 + t28 * (-2 * t14 * t22 + t19 * t18) + t31 * t18 * t22 - t14 * t19 * t33 + t40 * t38 + t43 * t42) * t2;
    real_type t47  = t18 * t21;
    real_type t48  = zeta__dot_D_3_4(t26, t27, t5, t15);
    real_type t50  = zeta__dot_D_3(t26, t27, t5, t15);
    result__[ 1   ] = (-t14 * t21 * t50 + t39 * t38 + t48 * t47 - t8 * t7) * t2;
    real_type t55  = t2 * t21;
    real_type t56  = zeta__dot_D_2_4(t26, t27, t5, t15);
    real_type t58  = zeta__dot_D_2(t26, t27, t5, t15);
    result__[ 2   ] = (-t14 * t58 + t56 * t18) * t55;
    real_type t61  = zeta__dot_D_1_4(t26, t27, t5, t15);
    real_type t63  = zeta__dot_D_1(t26, t27, t5, t15);
    result__[ 3   ] = (-t14 * t63 + t61 * t18) * t55;
    result__[ 4   ] = (-t14 * t21 * t33 + t8 * t11 + t28 * t47 + t39 * t42) * t2;
    result__[ 5   ] = result__[1];
    real_type t72  = zeta__dot_D_3_3(t26, t27, t5, t15);
    result__[ 6   ] = (t72 * t18 + t38 + t7) * t2;
    real_type t75  = zeta__dot_D_2_3(t26, t27, t5, t15);
    result__[ 7   ] = t18 * t75 * t2;
    real_type t77  = zeta__dot_D_1_3(t26, t27, t5, t15);
    result__[ 8   ] = t18 * t77 * t2;
    result__[ 9   ] = (t50 * t18 - t11 + t42) * t2;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t81  = zeta__dot_D_2_2(t26, t27, t5, t15);
    real_type t83  = L__[iL_lambda2__xo];
    real_type t85  = sin(t27);
    real_type t86  = t85 * t26 * t83;
    result__[ 12  ] = (t81 * t18 - t86) * t2;
    real_type t88  = zeta__dot_D_1_2(t26, t27, t5, t15);
    real_type t90  = cos(t27);
    real_type t91  = t83 * t90;
    result__[ 13  ] = (t88 * t18 + t91) * t2;
    result__[ 14  ] = (t58 * t18 + t26 * t91) * t2;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t96  = X__[iX_fx];
    real_type t97  = t96 * t96;
    real_type t99  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t100 = 1.0 / t99;
    real_type t103 = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t104 = 1.0 / t103;
    real_type t106 = X__[iX_Omega];
    real_type t107 = t106 * t106;
    real_type t108 = t26 * t26;
    real_type t111 = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t112 = 1.0 / t111;
    real_type t113 = t104 * t112;
    real_type t115 = -t104 * t100 * t97 - t113 * t108 * t107 + 1;
    real_type t116 = ALIAS_AdherenceEllipse_DD(t115);
    real_type t117 = t108 * t116;
    real_type t118 = t107 * t107;
    real_type t119 = ModelPars[iM_Pmax];
    real_type t120 = t119 * t119;
    real_type t125 = ALIAS_AdherenceEllipse_D(t115);
    real_type t129 = ModelPars[iM_m];
    real_type t130 = t129 * t129;
    real_type t133 = 1.0 / t119;
    real_type t136 = -t133 * t129 * t96 * t26 + 1;
    real_type t137 = ALIAS_PowerLimit_DD(t136);
    real_type t139 = zeta__dot_D_1_1(t26, t27, t5, t15);
    real_type t141 = L__[iL_lambda4__xo];
    real_type t142 = ModelPars[iM_kD];
    real_type t143 = t142 * t141;
    real_type t154 = t111 * t111;
    real_type t155 = 1.0 / t154;
    real_type t156 = t103 * t103;
    real_type t157 = 1.0 / t156;
    real_type t159 = 1.0 / t120;
    result__[ 18  ] = t159 * t157 * t155 * (4 * t120 * t118 * t117 + t103 * t111 * (-2 * t125 * t107 * t120 + (t137 * t97 * t130 + (t139 * t18 - 2 * t143) * t120) * t103 * t111)) * t2;
    real_type t163 = t107 * t117;
    real_type t165 = t111 * t103 * t125;
    result__[ 19  ] = 4 * t157 * t155 * (t163 - t165) * t106 * t26 * t2;
    real_type t178 = t129 * t96;
    real_type t180 = ALIAS_PowerLimit_D(t136);
    result__[ 20  ] = t159 * t112 * t157 * t100 * (4 * t120 * t96 * t107 * t26 * t116 + (t178 * t137 * t26 - t119 * t180) * t111 * t99 * t129 * t156) * t2;
    result__[ 21  ] = t133 * t113 * (-2 * t119 * t107 * t26 * t125 + t103 * t111 * (-t180 * t178 + (-2 * t26 * t143 + t63 * t18 + t83 * t85) * t119)) * t2;
    result__[ 22  ] = result__[19];
    result__[ 23  ] = 4 * t157 * t155 * (t163 - t165 / 2) * t2 * t108;
    result__[ 24  ] = 4 * t112 * t108 * t106 * t157 * t100 * t96 * t116 * t2;
    result__[ 25  ] = t113 * (t111 * t103 * t14 - 2 * t106 * t108 * t125) * t2;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t229 = t99 * t99;
    real_type t233 = t99 * t103;
    result__[ 28  ] = t159 * t157 / t229 * (t229 * t130 * t156 * t108 * t137 + 4 * t120 * t97 * t116 - 2 * t233 * t120 * t125) * t2;
    result__[ 29  ] = t133 * t104 * t100 * (-2 * t119 * t96 * t125 + (-t180 * t129 * t26 + t119 * t141) * t233) * t2;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t256 = AdherenceEllipse(t115);
    real_type t257 = PowerLimit(t136);
    real_type t258 = RoadLeftBorder(t6);
    real_type t260 = RoadRightBorder(t37);
    real_type t276 = t256 + t257 + t258 + t33 * t18 + t260 + t86 + t106 * t14 + (-t108 * t142 + t96) * t141 + L__[iL_lambda5__xo] * U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] + L__[iL_lambda6__xo] * U__[iU_v__fx] * ModelPars[iM_v__fx__max] + ModelPars[iM_wT];
    result__[ 36  ] = t2 * t276;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 37, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DHxDp_numRows() const
  { return 7; }

  integer
  PointMassCarModel_4::DHxDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_4::DHxDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHxDp_sparse(
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
  PointMassCarModel_4::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_4::Hu_eval(
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
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    result__[ 0   ] = ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    result__[ 1   ] = ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DHuDx_numRows() const
  { return 2; }

  integer
  PointMassCarModel_4::DHuDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_4::DHuDx_nnz() const
  { return 2; }

  void
  PointMassCarModel_4::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHuDx_sparse(
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
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    result__[ 0   ] = ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    result__[ 1   ] = ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DHuDp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_4::DHuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_4::DHuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHuDp_sparse(
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
  PointMassCarModel_4::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_4::Hp_eval(
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
  PointMassCarModel_4::DHpDp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_4::DHpDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_4::DHpDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHpDp_sparse(
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
  PointMassCarModel_4::eta_numEqns() const
  { return 7; }

  void
  PointMassCarModel_4::eta_eval(
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
    result__[ 5   ] = L__[iL_lambda6__xo];
    result__[ 6   ] = L__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DetaDx_numRows() const
  { return 7; }

  integer
  PointMassCarModel_4::DetaDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_4::DetaDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DetaDp_numRows() const
  { return 7; }

  integer
  PointMassCarModel_4::DetaDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_4::DetaDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DetaDp_sparse(
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
  PointMassCarModel_4::nu_numEqns() const
  { return 7; }

  void
  PointMassCarModel_4::nu_eval(
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
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DnuDx_numRows() const
  { return 7; }

  integer
  PointMassCarModel_4::DnuDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_4::DnuDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DnuDp_numRows() const
  { return 7; }

  integer
  PointMassCarModel_4::DnuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_4::DnuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_4_Methods_AdjointODE.cc
