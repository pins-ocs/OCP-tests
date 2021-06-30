/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_AdjointODE.cc                      |
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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
    real_type t15  = t14 * t22;
    real_type t23  = t10 * t14;
    real_type t25  = -t18 * t17 * t15 - t7 * t23 + 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = Q__[iQ_leftWidth] - t3;
    real_type t30  = RoadLeftBorder(t29);
    real_type t32  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t33  = ALIAS_RoadLeftBorder_D(t29);
    real_type t36  = Q__[iQ_rightWidth] + t3;
    real_type t37  = RoadRightBorder(t36);
    real_type t39  = ALIAS_RoadRightBorder_D(t36);
    real_type t42  = ModelPars[iM_m];
    real_type t44  = 1.0 / ModelPars[iM_Pmax];
    real_type t34  = t44 * t42;
    real_type t47  = -t6 * t1 * t34 + 1;
    real_type t48  = PowerLimit(t47);
    real_type t50  = LimitMinSpeed(t1);
    real_type t52  = U__[iU_v__fx];
    real_type t53  = v__fxControl(t52, -1, 1);
    real_type t55  = U__[iU_v__Omega];
    real_type t56  = v__OmegaControl(t55, -1, 1);
    real_type t58  = ModelPars[iM_wT];
    real_type t60  = L__[iL_lambda1__xo];
    real_type t61  = t1 * t60;
    real_type t62  = sin(t2);
    real_type t65  = L__[iL_lambda2__xo];
    real_type t66  = t16 * t65;
    real_type t68  = L__[iL_lambda3__xo];
    real_type t70  = ModelPars[iM_kD];
    real_type t72  = -t18 * t70 + t6;
    real_type t75  = t55 * L__[iL_lambda4__xo];
    real_type t76  = ModelPars[iM_v__Omega__max];
    real_type t80  = t52 * L__[iL_lambda5__xo];
    real_type t81  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t5 * t62 * t61 + t72 * t5 * t68 + t5 * t76 * t75 + t5 * t81 * t80 + t26 * t5 + t30 * t5 - t33 * t32 + t39 * t32 + t37 * t5 + t48 * t5 + t50 * t5 + t53 * t5 + t56 * t5 + t5 * t58 + t5 * t66;
    real_type t84  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    real_type t93  = cos(t2);
    result__[ 1   ] = t32 * t93 * t61 + t84 * t62 * t61 + t72 * t84 * t68 + t84 * t76 * t75 + t84 * t81 * t80 + t26 * t84 + t30 * t84 + t37 * t84 + t48 * t84 + t50 * t84 + t53 * t84 + t56 * t84 + t84 * t58 + t84 * t66;
    real_type t105 = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t107 = ALIAS_AdherenceEllipse_D(t25);
    real_type t108 = t107 * t32;
    real_type t117 = ALIAS_PowerLimit_D(t47);
    real_type t118 = t117 * t32;
    real_type t123 = ALIAS_LimitMinSpeed_D(t1);
    real_type t135 = t68 * t32;
    result__[ 2   ] = -2 * t1 * t17 * t108 * t15 - 2 * t1 * t70 * t135 + t105 * t62 * t61 + t72 * t105 * t68 + t105 * t76 * t75 + t105 * t81 * t80 - t6 * t118 * t34 + t32 * t62 * t60 + t26 * t105 + t30 * t105 + t37 * t105 + t48 * t105 + t50 * t105 + t53 * t105 + t56 * t105 + t105 * t58 + t105 * t66 + t123 * t32;
    result__[ 3   ] = -2 * t18 * t16 * t108 * t15 + t32 * t65;
    result__[ 4   ] = -t1 * t118 * t34 - 2 * t6 * t108 * t23 + t135;
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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
    real_type t15  = t14 * t22;
    real_type t23  = t10 * t14;
    real_type t25  = -t18 * t17 * t15 - t7 * t23 + 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t29  = Q__[iQ_leftWidth] - t3;
    real_type t30  = RoadLeftBorder(t29);
    real_type t32  = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t33  = ALIAS_RoadLeftBorder_D(t29);
    real_type t36  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t37  = ALIAS_RoadLeftBorder_DD(t29);
    real_type t40  = Q__[iQ_rightWidth] + t3;
    real_type t41  = RoadRightBorder(t40);
    real_type t43  = ALIAS_RoadRightBorder_D(t40);
    real_type t46  = ALIAS_RoadRightBorder_DD(t40);
    real_type t49  = ModelPars[iM_m];
    real_type t50  = ModelPars[iM_Pmax];
    real_type t51  = 1.0 / t50;
    real_type t52  = t51 * t49;
    real_type t54  = -t52 * t6 * t1 + 1;
    real_type t55  = PowerLimit(t54);
    real_type t57  = LimitMinSpeed(t1);
    real_type t59  = U__[iU_v__fx];
    real_type t60  = v__fxControl(t59, -1, 1);
    real_type t62  = U__[iU_v__Omega];
    real_type t63  = v__OmegaControl(t62, -1, 1);
    real_type t65  = ModelPars[iM_wT];
    real_type t67  = L__[iL_lambda1__xo];
    real_type t68  = t1 * t67;
    real_type t69  = sin(t2);
    real_type t72  = L__[iL_lambda2__xo];
    real_type t73  = t16 * t72;
    real_type t75  = L__[iL_lambda3__xo];
    real_type t77  = ModelPars[iM_kD];
    real_type t79  = -t18 * t77 + t6;
    real_type t82  = t62 * L__[iL_lambda4__xo];
    real_type t83  = ModelPars[iM_v__Omega__max];
    real_type t87  = t59 * L__[iL_lambda5__xo];
    real_type t88  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t5 * t69 * t68 + t79 * t5 * t75 + t5 * t83 * t82 + t5 * t88 * t87 + t26 * t5 + t30 * t5 - 2 * t33 * t32 + 2 * t43 * t32 + t37 * t36 + t46 * t36 + t41 * t5 + t55 * t5 + t57 * t5 + t60 * t5 + t63 * t5 + t5 * t65 + t5 * t73;
    real_type t91  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t94  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    real_type t103 = cos(t2);
    result__[ 1   ] = t32 * t103 * t68 + t91 * t69 * t68 + t79 * t91 * t75 + t91 * t83 * t82 + t91 * t88 * t87 + t26 * t91 + t30 * t91 - t33 * t94 + t41 * t91 + t43 * t94 + t55 * t91 + t57 * t91 + t60 * t91 + t63 * t91 + t91 * t65 + t91 * t73;
    real_type t115 = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t117 = ALIAS_AdherenceEllipse_D(t25);
    real_type t118 = t117 * t32;
    real_type t120 = t22 * t1;
    real_type t121 = t14 * t120;
    real_type t125 = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t130 = ALIAS_PowerLimit_D(t54);
    real_type t131 = t130 * t32;
    real_type t116 = t51 * t49;
    real_type t133 = t6 * t116;
    real_type t136 = ALIAS_LimitMinSpeed_D(t1);
    real_type t141 = t69 * t67;
    real_type t148 = t32 * t75;
    real_type t149 = t1 * t77;
    real_type t132 = t17 * t121;
    result__[ 2   ] = t115 * t69 * t68 + t79 * t115 * t75 + t115 * t83 * t82 + t115 * t88 * t87 + t26 * t115 + t30 * t115 + t41 * t115 + t55 * t115 + t57 * t115 + t60 * t115 + t63 * t115 + t115 * t65 + t115 * t73 - 2 * t118 * t132 - t33 * t125 + t43 * t125 - t133 * t131 + t136 * t32 + t32 * t141 - 2 * t149 * t148;
    real_type t157 = t22 * t18;
    real_type t158 = t14 * t157;
    real_type t156 = t16 * t158;
    result__[ 3   ] = -2 * t118 * t156 + t32 * t72;
    real_type t162 = t10 * t6;
    real_type t163 = t14 * t162;
    real_type t167 = t1 * t116;
    result__[ 4   ] = -2 * t163 * t118 - t167 * t131 + t148;
    result__[ 5   ] = result__[1];
    real_type t169 = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = 2 * t94 * t103 * t68 + t169 * t69 * t68 + t79 * t169 * t75 + t169 * t83 * t82 + t169 * t88 * t87 - t36 * t69 * t68 + t26 * t169 + t30 * t169 + t41 * t169 + t55 * t169 + t57 * t169 + t60 * t169 + t63 * t169 + t169 * t65 + t169 * t73;
    real_type t192 = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t194 = t117 * t94;
    real_type t201 = t130 * t94;
    real_type t218 = t94 * t75;
    result__[ 7   ] = t125 * t103 * t68 + t36 * t103 * t67 + t192 * t69 * t68 + t79 * t192 * t75 + t192 * t83 * t82 + t192 * t88 * t87 - 2 * t194 * t132 - t133 * t201 + t136 * t94 + t94 * t141 - 2 * t149 * t218 + t26 * t192 + t30 * t192 + t41 * t192 + t55 * t192 + t57 * t192 + t60 * t192 + t63 * t192 + t192 * t65 + t192 * t73;
    result__[ 8   ] = -2 * t194 * t156 + t94 * t72;
    result__[ 9   ] = -2 * t163 * t194 - t167 * t201 + t218;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t232 = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t235 = t125 * t75;
    real_type t245 = t117 * t125;
    real_type t249 = t117 * t36;
    real_type t254 = ALIAS_AdherenceEllipse_DD(t25);
    real_type t255 = t254 * t36;
    real_type t256 = t17 * t17;
    real_type t258 = t21 * t21;
    real_type t259 = 1.0 / t258;
    real_type t261 = t13 * t13;
    real_type t262 = 1.0 / t261;
    real_type t229 = t262 * t259;
    real_type t271 = 4 * t18 * t256 * t255 * t229 - 2 * t17 * t249 * t15 + t232 * t69 * t68 + t79 * t232 * t75 + t232 * t83 * t82 + t232 * t88 * t87 - 2 * t77 * t36 * t75 + 2 * t125 * t141 - 4 * t245 * t132 - 4 * t149 * t235 + t232 * t73;
    real_type t275 = ALIAS_LimitMinSpeed_DD(t1);
    real_type t284 = ALIAS_PowerLimit_DD(t54);
    real_type t285 = t284 * t36;
    real_type t286 = t49 * t49;
    real_type t288 = t50 * t50;
    real_type t289 = 1.0 / t288;
    real_type t292 = t130 * t125;
    real_type t266 = t289 * t286;
    real_type t295 = t7 * t285 * t266 + 2 * t136 * t125 - 2 * t133 * t292 + t26 * t232 + t30 * t232 + t41 * t232 + t55 * t232 + t57 * t232 + t60 * t232 + t63 * t232 + t232 * t65 + t275 * t36;
    result__[ 12  ] = t271 + t295;
    result__[ 13  ] = 4 * t1 * t17 * t16 * t255 * t18 * t229 - 4 * t121 * t16 * t249 + t125 * t72 - 2 * t245 * t156;
    real_type t312 = t162 * t255;
    real_type t308 = t262 * t312;
    result__[ 14  ] = t6 * t289 * t286 * t1 * t285 + 4 * t308 * t120 * t17 - t52 * t130 * t36 - 2 * t163 * t245 - t167 * t292 + t235;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t325 = t18 * t18;
    result__[ 18  ] = 4 * t325 * t17 * t255 * t229 - 2 * t158 * t249;
    result__[ 19  ] = 4 * t308 * t157 * t16;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t335 = t9 * t9;
    result__[ 24  ] = 4 * t262 / t335 * t7 * t255 - 2 * t249 * t23 + t18 * t285 * t266;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHxDp_sparse(
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
  PointMassCarModel_1::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::Hu_eval(
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
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t5 * ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo] + t7 * t5;
    real_type t14  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t5 * ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo] + t14 * t5;
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t7   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    real_type t11  = ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo];
    result__[ 0   ] = t5 * t11 + t7 * t5;
    real_type t13  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t13 * t11 + t7 * t13;
    real_type t16  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t16 * t11 + t7 * t16;
    real_type t20  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    real_type t24  = ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo];
    result__[ 3   ] = t20 * t5 + t5 * t24;
    result__[ 4   ] = t20 * t13 + t13 * t24;
    result__[ 5   ] = t20 * t16 + t16 * t24;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHuDp_sparse(
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
  PointMassCarModel_1::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_1::Hp_eval(
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DHpDp_sparse(
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
  PointMassCarModel_1::eta_numEqns() const
  { return 5; }

  void
  PointMassCarModel_1::eta_eval(
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DetaDp_sparse(
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
  PointMassCarModel_1::nu_numEqns() const
  { return 5; }

  void
  PointMassCarModel_1::nu_eval(
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_1_Methods_AdjointODE.cc
