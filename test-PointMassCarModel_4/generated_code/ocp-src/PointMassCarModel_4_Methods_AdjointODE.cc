/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 4/12/2021                                        |
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
    real_type            result__[]
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
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t3);
    real_type t11  = ALIAS_rightWidth(t3);
    real_type t12  = t11 + t5;
    real_type t13  = ALIAS_RoadRightBorder_D(t12);
    real_type t14  = t13 * t2;
    real_type t15  = ALIAS_rightWidth_D(t3);
    real_type t18  = t2 * L__[iL_lambda1__xo];
    real_type t19  = X__[iX_V];
    real_type t20  = X__[iX_alpha];
    real_type t21  = ALIAS_Kappa(t3);
    real_type t22  = zeta__dot_D_4(t19, t20, t5, t21);
    real_type t23  = ALIAS_Kappa_D(t3);
    real_type t26  = L__[iL_lambda3__xo];
    real_type t27  = zeta__dot(t19, t20, t5, t21);
    result__[ 0   ] = t9 * t8 + t15 * t14 + t23 * t22 * t18 - t2 * (t23 * t22 * t21 + t27 * t23) * t26;
    real_type t34  = zeta__dot_D_3(t19, t20, t5, t21);
    real_type t36  = t21 * t26;
    result__[ 1   ] = -t2 * t34 * t36 + t34 * t18 + t14 - t8;
    real_type t39  = zeta__dot_D_2(t19, t20, t5, t21);
    real_type t42  = t2 * L__[iL_lambda2__xo];
    real_type t43  = cos(t20);
    result__[ 2   ] = t43 * t19 * t42 - t2 * t39 * t36 + t39 * t18;
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
    real_type t67  = -t56 * t64 * t60 * t59 - t56 * t52 * t49 + 1;
    real_type t68  = ALIAS_AdherenceEllipse_D(t67);
    real_type t69  = t68 * t2;
    real_type t76  = ModelPars[iM_m];
    real_type t78  = 1.0 / ModelPars[iM_Pmax];
    real_type t81  = -t78 * t76 * t48 * t19 + 1;
    real_type t82  = ALIAS_PowerLimit_D(t81);
    real_type t83  = t82 * t2;
    real_type t87  = zeta__dot_D_1(t19, t20, t5, t21);
    real_type t89  = sin(t20);
    real_type t93  = L__[iL_lambda4__xo];
    real_type t94  = ModelPars[iM_kD];
    result__[ 3   ] = -2 * t56 * t64 * t19 * t59 * t69 - 2 * t2 * t19 * t94 * t93 - t78 * t76 * t48 * t83 - t2 * t87 * t36 + t87 * t18 + t89 * t42;
    result__[ 4   ] = -2 * t56 * t64 * t60 * t58 * t69 + t2 * t26;
    result__[ 5   ] = -t78 * t76 * t19 * t83 - 2 * t56 * t52 * t48 * t69 + t2 * t93;
    real_type t113 = AdherenceEllipse(t67);
    real_type t115 = RoadLeftBorder(t6);
    real_type t117 = RoadRightBorder(t12);
    real_type t119 = PowerLimit(t81);
    result__[ 6   ] = t113 * t2 + t115 * t2 + t117 * t2 + t119 * t2 + t2 * ModelPars[iM_wT] + t27 * t18 + t89 * t19 * t42 - t2 * (t27 * t21 - t58) * t26 + t2 * (-t60 * t94 + t48) * t93 + U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] * t2 * L__[iL_lambda5__xo] + U__[iU_v__fx] * ModelPars[iM_v__fx__max] * t2 * L__[iL_lambda6__xo];
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
  PointMassCarModel_4::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t3);
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_RoadLeftBorder_D(t6);
    real_type t13  = t12 * t2;
    real_type t14  = ALIAS_leftWidth_DD(t3);
    real_type t16  = ALIAS_rightWidth(t3);
    real_type t17  = t16 + t5;
    real_type t18  = ALIAS_RoadRightBorder_DD(t17);
    real_type t19  = t18 * t2;
    real_type t20  = ALIAS_rightWidth_D(t3);
    real_type t21  = t20 * t20;
    real_type t23  = ALIAS_RoadRightBorder_D(t17);
    real_type t24  = t23 * t2;
    real_type t25  = ALIAS_rightWidth_DD(t3);
    real_type t28  = t2 * L__[iL_lambda1__xo];
    real_type t29  = X__[iX_V];
    real_type t30  = X__[iX_alpha];
    real_type t31  = ALIAS_Kappa(t3);
    real_type t32  = zeta__dot_D_4_4(t29, t30, t5, t31);
    real_type t33  = ALIAS_Kappa_D(t3);
    real_type t34  = t33 * t33;
    real_type t37  = zeta__dot_D_4(t29, t30, t5, t31);
    real_type t38  = ALIAS_Kappa_DD(t3);
    real_type t41  = L__[iL_lambda3__xo];
    real_type t42  = zeta__dot(t29, t30, t5, t31);
    real_type t48  = t37 * t31;
    result__[ 0   ] = t10 * t8 + t14 * t13 + t21 * t19 + t25 * t24 + t34 * t32 * t28 + t38 * t37 * t28 - t2 * (t34 * t32 * t31 + 2 * t37 * t34 + t42 * t38 + t38 * t48) * t41;
    real_type t53  = t9 * t8;
    real_type t54  = t20 * t19;
    real_type t55  = zeta__dot_D_3_4(t29, t30, t5, t31);
    real_type t56  = t33 * t55;
    real_type t57  = t56 * t28;
    real_type t58  = zeta__dot_D_3(t29, t30, t5, t31);
    result__[ 1   ] = -t53 + t54 + t57 - t2 * (t33 * t55 * t31 + t58 * t33) * t41;
    real_type t65  = zeta__dot_D_2_4(t29, t30, t5, t31);
    real_type t66  = t33 * t65;
    real_type t67  = t66 * t28;
    real_type t68  = zeta__dot_D_2(t29, t30, t5, t31);
    result__[ 2   ] = t67 - t2 * (t33 * t65 * t31 + t68 * t33) * t41;
    real_type t75  = zeta__dot_D_1_4(t29, t30, t5, t31);
    real_type t76  = t33 * t75;
    real_type t77  = t76 * t28;
    real_type t78  = zeta__dot_D_1(t29, t30, t5, t31);
    result__[ 3   ] = t77 - t2 * (t33 * t75 * t31 + t78 * t33) * t41;
    result__[ 4   ] = t9 * t13 + t20 * t24 + t33 * t37 * t28 - t2 * (t42 * t33 + t33 * t48) * t41;
    real_type t94  = t33 * t41;
    real_type t95  = t2 * t58;
    real_type t97  = t31 * t41;
    result__[ 5   ] = -t2 * t56 * t97 - t95 * t94 - t53 + t54 + t57;
    real_type t100 = zeta__dot_D_3_3(t29, t30, t5, t31);
    result__[ 6   ] = -t2 * t100 * t97 + t100 * t28 + t19 + t8;
    real_type t104 = zeta__dot_D_2_3(t29, t30, t5, t31);
    result__[ 7   ] = -t2 * t104 * t97 + t104 * t28;
    real_type t108 = zeta__dot_D_1_3(t29, t30, t5, t31);
    result__[ 8   ] = -t2 * t108 * t97 + t108 * t28;
    result__[ 9   ] = t58 * t28 - t95 * t97 - t13 + t24;
    real_type t114 = t2 * t68;
    result__[ 10  ] = -t2 * t66 * t97 - t114 * t94 + t67;
    result__[ 11  ] = result__[7];
    real_type t118 = zeta__dot_D_2_2(t29, t30, t5, t31);
    real_type t121 = t2 * L__[iL_lambda2__xo];
    real_type t122 = sin(t30);
    real_type t124 = t122 * t29 * t121;
    result__[ 12  ] = -t2 * t118 * t97 + t118 * t28 - t124;
    real_type t127 = zeta__dot_D_1_2(t29, t30, t5, t31);
    real_type t129 = cos(t30);
    result__[ 13  ] = -t2 * t127 * t97 + t129 * t121 + t127 * t28;
    result__[ 14  ] = t129 * t29 * t121 - t114 * t97 + t68 * t28;
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
    real_type t160 = -t149 * t157 * t153 * t152 - t149 * t145 * t142 + 1;
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
    real_type t185 = -t183 * t141 * t29 + 1;
    real_type t186 = ALIAS_PowerLimit_DD(t185);
    real_type t187 = t186 * t2;
    real_type t188 = t180 * t180;
    real_type t190 = t181 * t181;
    real_type t191 = 1.0 / t190;
    real_type t194 = zeta__dot_D_1_1(t29, t30, t5, t31);
    real_type t198 = L__[iL_lambda4__xo];
    real_type t199 = ModelPars[iM_kD];
    real_type t200 = t199 * t198;
    result__[ 18  ] = 4 * t169 * t166 * t153 * t163 * t162 + t191 * t188 * t142 * t187 - 2 * t149 * t157 * t152 * t174 - t2 * t194 * t97 + t194 * t28 - 2 * t2 * t200;
    real_type t209 = t151 * t174;
    real_type t210 = t157 * t29;
    real_type t211 = t149 * t210;
    result__[ 19  ] = 4 * t169 * t166 * t153 * t29 * t152 * t151 * t162 - 4 * t211 * t209;
    real_type t214 = t145 * t141;
    real_type t215 = t214 * t162;
    real_type t224 = ALIAS_PowerLimit_D(t185);
    real_type t225 = t224 * t2;
    result__[ 20  ] = t141 * t191 * t188 * t29 * t187 + 4 * t210 * t152 * t169 * t215 - t183 * t225;
    result__[ 21  ] = -t182 * t180 * t141 * t225 - 2 * t211 * t152 * t174 - 2 * t2 * t29 * t200 + t122 * t121 - t137 * t97 + t78 * t28;
    result__[ 22  ] = result__[19];
    real_type t240 = t153 * t153;
    real_type t245 = t157 * t153;
    real_type t246 = t149 * t245;
    result__[ 23  ] = 4 * t169 * t166 * t240 * t152 * t162 - 2 * t246 * t174;
    result__[ 24  ] = 4 * t245 * t151 * t169 * t215;
    result__[ 25  ] = t2 * t41 - 2 * t246 * t209;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t255 = t144 * t144;
    result__[ 28  ] = 4 * t169 / t255 * t142 * t162 - 2 * t149 * t145 * t174 + t191 * t188 * t153 * t187;
    result__[ 29  ] = -t182 * t180 * t29 * t225 - 2 * t149 * t214 * t174 + t2 * t198;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t274 = AdherenceEllipse(t160);
    real_type t276 = RoadLeftBorder(t6);
    real_type t278 = RoadRightBorder(t17);
    real_type t280 = PowerLimit(t185);
    result__[ 36  ] = t274 * t2 + t276 * t2 + t278 * t2 + t280 * t2 + t2 * ModelPars[iM_wT] + t42 * t28 + t124 - t2 * (t42 * t31 - t151) * t41 + t2 * (-t153 * t199 + t141) * t198 + U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] * t2 * L__[iL_lambda5__xo] + U__[iU_v__fx] * ModelPars[iM_v__fx__max] * t2 * L__[iL_lambda6__xo];
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHxDp_sparse(
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
  PointMassCarModel_4::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_4::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHuDp_sparse(
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
  PointMassCarModel_4::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_4::Hp_eval(
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DHpDp_sparse(
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
  PointMassCarModel_4::eta_numEqns() const
  { return 7; }

  void
  PointMassCarModel_4::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DetaDp_sparse(
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
  PointMassCarModel_4::nu_numEqns() const
  { return 7; }

  void
  PointMassCarModel_4::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_4_Methods_AdjointODE.cc
