/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_leftWidth(t3);
    real_type t5   = X__[iX_n];
    real_type t6   = t4 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_D(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t3);
    real_type t11  = ALIAS_rightWidth(t3);
    real_type t12  = t11 + t5;
    real_type t13  = ALIAS_RoadRightBorder_D(t12);
    real_type t14  = t13 * t2;
    real_type t15  = ALIAS_rightWidth_D(t3);
    real_type t17  = L__[iL_lambda1__xo];
    real_type t18  = X__[iX_V];
    real_type t19  = X__[iX_alpha];
    real_type t20  = ALIAS_Kappa(t3);
    real_type t21  = zeta__dot_D_4(t18, t19, t5, t20);
    real_type t23  = ALIAS_Kappa_D(t3);
    real_type t26  = L__[iL_lambda3__xo];
    real_type t27  = t2 * t26;
    real_type t30  = zeta__dot(t18, t19, t5, t20);
    result__[ 0   ] = t9 * t8 + t15 * t14 + t2 * t23 * t21 * t17 + (-t20 * t23 * t21 - t23 * t30) * t27;
    real_type t34  = zeta__dot_D_3(t18, t19, t5, t20);
    result__[ 1   ] = t2 * t34 * t17 - t20 * t34 * t27 + t14 - t8;
    real_type t39  = zeta__dot_D_2(t18, t19, t5, t20);
    real_type t42  = L__[iL_lambda2__xo];
    real_type t43  = t18 * t42;
    real_type t44  = cos(t19);
    result__[ 2   ] = t2 * t39 * t17 + t2 * t44 * t43 - t20 * t39 * t27;
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
    real_type t58  = t57 * t65;
    real_type t66  = t53 * t57;
    real_type t68  = -t61 * t60 * t58 - t50 * t66 + 1;
    real_type t69  = ALIAS_AdherenceEllipse_D(t68);
    real_type t70  = t69 * t2;
    real_type t77  = ModelPars[iM_m];
    real_type t79  = 1.0 / ModelPars[iM_Pmax];
    real_type t72  = t79 * t77;
    real_type t82  = -t49 * t18 * t72 + 1;
    real_type t83  = ALIAS_PowerLimit_D(t82);
    real_type t84  = t83 * t2;
    real_type t88  = zeta__dot_D_1(t18, t19, t5, t20);
    real_type t91  = sin(t19);
    real_type t96  = L__[iL_lambda4__xo];
    real_type t97  = t2 * t96;
    real_type t98  = ModelPars[iM_kD];
    result__[ 3   ] = -2 * t18 * t60 * t70 * t58 + t2 * t88 * t17 - 2 * t18 * t98 * t97 + t2 * t91 * t42 - t20 * t88 * t27 - t49 * t84 * t72;
    result__[ 4   ] = -2 * t61 * t59 * t70 * t58 + t27;
    result__[ 5   ] = -t18 * t84 * t72 - 2 * t49 * t70 * t66 + t97;
    real_type t114 = AdherenceEllipse(t68);
    real_type t116 = RoadLeftBorder(t6);
    real_type t118 = RoadRightBorder(t12);
    real_type t120 = PowerLimit(t82);
    real_type t122 = U__[iU_v__fx];
    real_type t123 = v__fxControl(t122, -1, 1);
    real_type t125 = U__[iU_v__Omega];
    real_type t126 = v__OmegaControl(t125, -1, 1);
    real_type t152 = t114 * t1 + t116 * t1 + t118 * t1 + t120 * t1 + t123 * t1 + t126 * t1 + t1 * ModelPars[iM_wT] + t1 * t30 * t17 + t1 * t91 * t43 + (-t20 * t30 + t59) * t1 * t26 + (-t61 * t98 + t49) * t1 * t96 + t1 * ModelPars[iM_v__Omega__max] * t125 * L__[iL_lambda5__xo] + t1 * ModelPars[iM_v__fx__max] * t122 * L__[iL_lambda6__xo];
    result__[ 6   ] = 2 * t152;
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_s];
    real_type t4   = ALIAS_leftWidth(t3);
    real_type t5   = X__[iX_n];
    real_type t6   = t4 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t3);
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_RoadLeftBorder_D(t6);
    real_type t14  = ALIAS_leftWidth_DD(t3);
    real_type t16  = ALIAS_rightWidth(t3);
    real_type t17  = t16 + t5;
    real_type t18  = ALIAS_RoadRightBorder_DD(t17);
    real_type t19  = t18 * t2;
    real_type t20  = ALIAS_rightWidth_D(t3);
    real_type t21  = t20 * t20;
    real_type t23  = ALIAS_RoadRightBorder_D(t17);
    real_type t25  = ALIAS_rightWidth_DD(t3);
    real_type t27  = L__[iL_lambda1__xo];
    real_type t28  = X__[iX_V];
    real_type t29  = X__[iX_alpha];
    real_type t30  = ALIAS_Kappa(t3);
    real_type t31  = zeta__dot_D_4_4(t28, t29, t5, t30);
    real_type t33  = ALIAS_Kappa_D(t3);
    real_type t34  = t33 * t33;
    real_type t37  = zeta__dot_D_4(t28, t29, t5, t30);
    real_type t38  = t37 * t27;
    real_type t39  = ALIAS_Kappa_DD(t3);
    real_type t42  = L__[iL_lambda3__xo];
    real_type t43  = t2 * t42;
    real_type t50  = zeta__dot(t28, t29, t5, t30);
    result__[ 0   ] = t10 * t8 + t14 * t12 * t2 + t21 * t19 + t25 * t23 * t2 + t2 * t34 * t31 * t27 + t2 * t39 * t38 + (-t30 * t34 * t31 - t30 * t39 * t37 - 2 * t34 * t37 - t39 * t50) * t43;
    real_type t54  = t9 * t8;
    real_type t55  = t20 * t19;
    real_type t56  = zeta__dot_D_3_4(t28, t29, t5, t30);
    real_type t58  = t2 * t33;
    real_type t59  = t58 * t56 * t27;
    real_type t60  = t33 * t30;
    real_type t61  = t56 * t60;
    real_type t62  = zeta__dot_D_3(t28, t29, t5, t30);
    real_type t63  = t33 * t62;
    result__[ 1   ] = -t54 + t55 + t59 + (-t61 - t63) * t43;
    real_type t66  = zeta__dot_D_2_4(t28, t29, t5, t30);
    real_type t68  = t58 * t66 * t27;
    real_type t70  = t66 * t60;
    real_type t71  = zeta__dot_D_2(t28, t29, t5, t30);
    real_type t72  = t33 * t71;
    result__[ 2   ] = t68 + (-t70 - t72) * t43;
    real_type t75  = zeta__dot_D_1_4(t28, t29, t5, t30);
    real_type t77  = t58 * t75 * t27;
    real_type t79  = t75 * t60;
    real_type t80  = zeta__dot_D_1(t28, t29, t5, t30);
    real_type t81  = t33 * t80;
    result__[ 3   ] = t77 + (-t79 - t81) * t43;
    real_type t84  = t12 * t1;
    real_type t86  = t23 * t1;
    real_type t90  = t1 * t42;
    result__[ 4   ] = 2 * t9 * t84 + 2 * t20 * t86 + 2 * t1 * t33 * t38 + 2 * t90 * (-t33 * t50 - t37 * t60);
    result__[ 5   ] = -t61 * t43 - t63 * t43 - t54 + t55 + t59;
    real_type t99  = zeta__dot_D_3_3(t28, t29, t5, t30);
    result__[ 6   ] = t2 * t99 * t27 - t30 * t99 * t43 + t19 + t8;
    real_type t104 = zeta__dot_D_2_3(t28, t29, t5, t30);
    result__[ 7   ] = t2 * t104 * t27 - t30 * t104 * t43;
    real_type t109 = zeta__dot_D_1_3(t28, t29, t5, t30);
    result__[ 8   ] = t2 * t109 * t27 - t30 * t109 * t43;
    result__[ 9   ] = 2 * t1 * t62 * t27 - 2 * t30 * t62 * t90 - 2 * t84 + 2 * t86;
    result__[ 10  ] = -t70 * t43 - t72 * t43 + t68;
    result__[ 11  ] = result__[7];
    real_type t121 = zeta__dot_D_2_2(t28, t29, t5, t30);
    real_type t124 = L__[iL_lambda2__xo];
    real_type t125 = t28 * t124;
    real_type t126 = sin(t29);
    result__[ 12  ] = t2 * t121 * t27 - t30 * t121 * t43 - t2 * t126 * t125;
    real_type t131 = zeta__dot_D_1_2(t28, t29, t5, t30);
    real_type t134 = cos(t29);
    result__[ 13  ] = t2 * t134 * t124 + t2 * t131 * t27 - t30 * t131 * t43;
    result__[ 14  ] = 2 * t1 * t134 * t125 + 2 * t1 * t71 * t27 - 2 * t30 * t71 * t90;
    result__[ 15  ] = -t79 * t43 - t81 * t43 + t77;
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
    real_type t150 = t156 * t164;
    real_type t157 = t152 * t156;
    real_type t167 = -t160 * t159 * t150 - t149 * t157 + 1;
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
    real_type t192 = -t190 * t148 * t28 + 1;
    real_type t193 = ALIAS_PowerLimit_DD(t192);
    real_type t194 = t193 * t2;
    real_type t195 = t187 * t187;
    real_type t197 = t188 * t188;
    real_type t198 = 1.0 / t197;
    real_type t201 = zeta__dot_D_1_1(t28, t29, t5, t30);
    real_type t206 = L__[iL_lambda4__xo];
    real_type t208 = ModelPars[iM_kD];
    real_type t166 = t176 * t173;
    real_type t179 = t198 * t195;
    result__[ 18  ] = 4 * t160 * t170 * t169 * t166 + t149 * t194 * t179 - 2 * t159 * t181 * t150 + t2 * t201 * t27 - 2 * t208 * t2 * t206 - t30 * t201 * t43;
    real_type t218 = t164 * t28;
    real_type t219 = t156 * t218;
    result__[ 19  ] = 4 * t28 * t159 * t158 * t169 * t160 * t166 - 4 * t219 * t158 * t181;
    real_type t222 = t152 * t148;
    real_type t223 = t222 * t169;
    real_type t232 = ALIAS_PowerLimit_D(t192);
    real_type t224 = t176 * t223;
    result__[ 20  ] = t148 * t198 * t195 * t28 * t194 + 4 * t224 * t218 * t159 - t190 * t232 * t2;
    real_type t235 = t180 * t1;
    real_type t239 = t232 * t1;
    real_type t253 = t1 * t206;
    result__[ 21  ] = 2 * t1 * t126 * t124 + 2 * t1 * t80 * t27 - 2 * t148 * t239 * t190 - 4 * t219 * t159 * t235 - 4 * t28 * t208 * t253 - 2 * t30 * t80 * t90;
    result__[ 22  ] = result__[19];
    real_type t258 = t160 * t160;
    real_type t263 = t164 * t160;
    real_type t264 = t156 * t263;
    result__[ 23  ] = 4 * t258 * t159 * t169 * t166 - 2 * t264 * t181;
    result__[ 24  ] = 4 * t224 * t263 * t158;
    result__[ 25  ] = -4 * t264 * t158 * t235 + 2 * t90;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t274 = t151 * t151;
    result__[ 28  ] = 4 * t176 / t274 * t149 * t169 - 2 * t181 * t157 + t160 * t194 * t179;
    result__[ 29  ] = -4 * t156 * t222 * t235 - 2 * t28 * t239 * t190 + 2 * t253;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t294 = AdherenceEllipse(t167);
    real_type t295 = RoadLeftBorder(t6);
    real_type t296 = RoadRightBorder(t17);
    real_type t297 = PowerLimit(t192);
    real_type t298 = U__[iU_v__fx];
    real_type t299 = v__fxControl(t298, -1, 1);
    real_type t300 = U__[iU_v__Omega];
    real_type t301 = v__OmegaControl(t300, -1, 1);
    real_type t319 = t294 + t295 + t296 + t297 + t299 + t301 + ModelPars[iM_wT] + t50 * t27 + t126 * t125 + (-t30 * t50 + t158) * t42 + (-t160 * t208 + t148) * t206 + ModelPars[iM_v__Omega__max] * t300 * L__[iL_lambda5__xo] + ModelPars[iM_v__fx__max] * t298 * L__[iL_lambda6__xo];
    result__[ 36  ] = 2 * t319;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t4   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t2 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo] + t4 * t2;
    real_type t11  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t2 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo] + t11 * t2;
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t3   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = 2 * t1 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo] + 2 * t3 * t1;
    real_type t11  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = 2 * t1 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo] + 2 * t11 * t1;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_3_Methods_AdjointODE.cc
