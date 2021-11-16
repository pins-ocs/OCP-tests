/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_AdjointODE.cc                      |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  PointMassCarModel_3::Hx_numEqns() const
  { return 7; }

  void
  PointMassCarModel_3::Hx_eval(
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
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
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
    result__[ 0   ] = (-t11 * t10 * t21 + t19 * t15 * t10 + t27 * t26 + t8 * t7) * t2;
    real_type t30  = zeta__dot_D_3(t17, t18, t5, t12);
    result__[ 1   ] = t2 * (t30 * t15 + t26 - t7);
    real_type t33  = zeta__dot_D_2(t17, t18, t5, t12);
    real_type t35  = cos(t18);
    real_type t36  = L__[iL_lambda2__xo];
    result__[ 2   ] = t2 * (t17 * t36 * t35 + t33 * t15);
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
    result__[ 3   ] = t69 * t57 * (-2 * t62 * t51 * t17 * t60 + t55 * (-t73 * t66 * t40 + (-2 * t17 * t78 * t77 + t75 * t15 + t36 * t82) * t62) * t47) * t2;
    result__[ 4   ] = t57 * (t55 * t47 * t11 - 2 * t50 * t52 * t60) * t2;
    result__[ 5   ] = -t69 * t66 * t17 * t73 * t2 - 2 * t48 * t44 * t40 * t60 * t2 + t2 * t78;
    real_type t109 = AdherenceEllipse(t59);
    real_type t110 = PowerLimit(t72);
    real_type t111 = RoadLeftBorder(t6);
    real_type t113 = RoadRightBorder(t25);
    real_type t131 = t109 + t110 + t111 + t21 * t15 + t113 + t82 * t17 * t36 + t50 * t11 + (-t52 * t77 + t40) * t78 + L__[iL_lambda5__xo] * U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] + L__[iL_lambda6__xo] * U__[iU_v__fx] * ModelPars[iM_v__fx__max] + ModelPars[iM_wT];
    result__[ 6   ] = 2 * t1 * t131;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::DHxDx_numRows() const
  { return 7; }

  integer
  PointMassCarModel_3::DHxDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_3::DHxDx_nnz() const
  { return 37; }

  void
  PointMassCarModel_3::DHxDx_pattern(
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
  PointMassCarModel_3::DHxDx_sparse(
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
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
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
    result__[ 0   ] = (t9 * t7 + t12 * t11 + t28 * (-2 * t22 * t14 + t19 * t18) + t31 * t18 * t22 - t14 * t19 * t33 + t40 * t38 + t43 * t42) * t2;
    real_type t47  = t18 * t21;
    real_type t48  = zeta__dot_D_3_4(t26, t27, t5, t15);
    real_type t50  = zeta__dot_D_3(t26, t27, t5, t15);
    result__[ 1   ] = (-t14 * t50 * t21 + t39 * t38 + t48 * t47 - t8 * t7) * t2;
    real_type t55  = t21 * t2;
    real_type t56  = zeta__dot_D_2_4(t26, t27, t5, t15);
    real_type t58  = zeta__dot_D_2(t26, t27, t5, t15);
    result__[ 2   ] = (-t14 * t58 + t56 * t18) * t55;
    real_type t61  = zeta__dot_D_1_4(t26, t27, t5, t15);
    real_type t63  = zeta__dot_D_1(t26, t27, t5, t15);
    result__[ 3   ] = (-t14 * t63 + t61 * t18) * t55;
    result__[ 4   ] = 2 * (-t14 * t33 * t21 + t8 * t11 + t28 * t47 + t39 * t42) * t1;
    result__[ 5   ] = result__[1];
    real_type t73  = zeta__dot_D_3_3(t26, t27, t5, t15);
    result__[ 6   ] = (t73 * t18 + t38 + t7) * t2;
    real_type t76  = zeta__dot_D_2_3(t26, t27, t5, t15);
    result__[ 7   ] = t18 * t2 * t76;
    real_type t78  = zeta__dot_D_1_3(t26, t27, t5, t15);
    result__[ 8   ] = t18 * t2 * t78;
    result__[ 9   ] = 2 * t1 * (t50 * t18 - t11 + t42);
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t83  = zeta__dot_D_2_2(t26, t27, t5, t15);
    real_type t85  = L__[iL_lambda2__xo];
    real_type t87  = sin(t27);
    real_type t88  = t87 * t26 * t85;
    result__[ 12  ] = t2 * (t83 * t18 - t88);
    real_type t90  = zeta__dot_D_1_2(t26, t27, t5, t15);
    real_type t92  = cos(t27);
    real_type t93  = t85 * t92;
    result__[ 13  ] = t2 * (t90 * t18 + t93);
    result__[ 14  ] = 2 * t1 * (t58 * t18 + t26 * t93);
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t99  = X__[iX_fx];
    real_type t100 = t99 * t99;
    real_type t102 = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t103 = 1.0 / t102;
    real_type t106 = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t107 = 1.0 / t106;
    real_type t109 = X__[iX_Omega];
    real_type t110 = t109 * t109;
    real_type t111 = t26 * t26;
    real_type t114 = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t115 = 1.0 / t114;
    real_type t116 = t107 * t115;
    real_type t118 = -t107 * t103 * t100 - t116 * t111 * t110 + 1;
    real_type t119 = ALIAS_AdherenceEllipse_DD(t118);
    real_type t120 = t111 * t119;
    real_type t121 = t110 * t110;
    real_type t122 = ModelPars[iM_Pmax];
    real_type t123 = t122 * t122;
    real_type t128 = ALIAS_AdherenceEllipse_D(t118);
    real_type t131 = ModelPars[iM_m];
    real_type t132 = t131 * t131;
    real_type t135 = 1.0 / t122;
    real_type t136 = t135 * t131;
    real_type t138 = -t136 * t99 * t26 + 1;
    real_type t139 = ALIAS_PowerLimit_DD(t138);
    real_type t141 = zeta__dot_D_1_1(t26, t27, t5, t15);
    real_type t143 = L__[iL_lambda4__xo];
    real_type t144 = ModelPars[iM_kD];
    real_type t145 = t144 * t143;
    real_type t157 = t114 * t114;
    real_type t158 = 1.0 / t157;
    real_type t159 = t106 * t106;
    real_type t160 = 1.0 / t159;
    real_type t162 = 1.0 / t123;
    result__[ 18  ] = t162 * t160 * t158 * t2 * (4 * t123 * t121 * t120 + t106 * (-2 * t128 * t110 * t123 + t106 * t114 * (t139 * t100 * t132 + t123 * (t141 * t18 - 2 * t145))) * t114);
    real_type t164 = t119 * t2;
    real_type t171 = t128 * t2;
    real_type t173 = t115 * t26;
    result__[ 19  ] = 4 * t160 * t158 * t111 * t26 * t110 * t109 * t164 - 4 * t107 * t173 * t109 * t171;
    real_type t177 = t103 * t99;
    real_type t178 = t177 * t164;
    real_type t183 = t139 * t2;
    real_type t188 = ALIAS_PowerLimit_D(t138);
    result__[ 20  ] = t99 * t162 * t132 * t26 * t183 + 4 * t173 * t110 * t160 * t178 - t136 * t188 * t2;
    result__[ 21  ] = 2 * t135 * t116 * (-2 * t122 * t110 * t26 * t128 + t114 * (-t188 * t131 * t99 + (-2 * t26 * t145 + t63 * t18 + t85 * t87) * t122) * t106) * t1;
    result__[ 22  ] = result__[19];
    result__[ 23  ] = 4 * t160 * t158 * (t110 * t120 - t114 * t106 * t128 / 2) * t111 * t2;
    real_type t220 = t115 * t111;
    result__[ 24  ] = 4 * t220 * t109 * t160 * t178;
    real_type t223 = t128 * t1;
    result__[ 25  ] = -4 * t107 * t220 * t109 * t223 + 2 * t1 * t14;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t230 = t102 * t102;
    result__[ 28  ] = 4 * t160 / t230 * t100 * t164 - 2 * t107 * t103 * t171 + t162 * t132 * t111 * t183;
    result__[ 29  ] = -2 * t135 * t131 * t26 * t188 * t1 - 4 * t107 * t177 * t223 + 2 * t1 * t143;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t252 = AdherenceEllipse(t118);
    real_type t254 = PowerLimit(t138);
    real_type t256 = RoadLeftBorder(t6);
    real_type t260 = RoadRightBorder(t37);
    result__[ 36  ] = 2 * t252 + 2 * t254 + 2 * t256 + 2 * t33 * t18 + 2 * t260 + 2 * t88 + 2 * t109 * t14 + t143 * (-2 * t111 * t144 + 2 * t99) + 2 * L__[iL_lambda5__xo] * U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] + 2 * L__[iL_lambda6__xo] * U__[iU_v__fx] * ModelPars[iM_v__fx__max] + 2 * ModelPars[iM_wT];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 37, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::DHxDp_numRows() const
  { return 7; }

  integer
  PointMassCarModel_3::DHxDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_3::DHxDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHxDp_sparse(
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
  PointMassCarModel_3::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_3::Hu_eval(
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
    real_type t5   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    result__[ 0   ] = t5 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo];
    result__[ 1   ] = t5 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::DHuDx_numRows() const
  { return 2; }

  integer
  PointMassCarModel_3::DHuDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_3::DHuDx_nnz() const
  { return 2; }

  void
  PointMassCarModel_3::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHuDx_sparse(
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
    real_type t4   = X__[iX_sqrt_inv_Vseg];
    result__[ 0   ] = 2 * t4 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo];
    result__[ 1   ] = 2 * t4 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::DHuDp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_3::DHuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_3::DHuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHuDp_sparse(
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
  PointMassCarModel_3::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_3::Hp_eval(
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
  PointMassCarModel_3::DHpDp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_3::DHpDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_3::DHpDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHpDp_sparse(
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
  PointMassCarModel_3::eta_numEqns() const
  { return 7; }

  void
  PointMassCarModel_3::eta_eval(
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
  PointMassCarModel_3::DetaDx_numRows() const
  { return 7; }

  integer
  PointMassCarModel_3::DetaDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_3::DetaDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::DetaDp_numRows() const
  { return 7; }

  integer
  PointMassCarModel_3::DetaDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_3::DetaDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DetaDp_sparse(
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
  PointMassCarModel_3::nu_numEqns() const
  { return 7; }

  void
  PointMassCarModel_3::nu_eval(
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
  PointMassCarModel_3::DnuDx_numRows() const
  { return 7; }

  integer
  PointMassCarModel_3::DnuDx_numCols() const
  { return 7; }

  integer
  PointMassCarModel_3::DnuDx_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::DnuDp_numRows() const
  { return 7; }

  integer
  PointMassCarModel_3::DnuDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_3::DnuDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_3::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_3_Methods_AdjointODE.cc
