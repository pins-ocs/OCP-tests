/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::Hxp_numEqns() const { return 7; }

  void
  PointMassCarModel_3::Hxp_eval(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = X__[iX_s];
    real_type t6   = ALIAS_Kappa(t5);
    real_type t7   = zeta__dot_D_4(t2, t3, t4, t6);
    real_type t9   = ALIAS_Kappa_D(t5);
    real_type t10  = X__[iX_sqrt_inv_Vseg];
    real_type t11  = t10 * t10;
    real_type t14  = L__[iL_lambda3__xo];
    real_type t15  = t11 * t14;
    real_type t18  = zeta__dot(t2, t3, t4, t6);
    result__[ 0   ] = t11 * t9 * t7 * t1 + (-t6 * t9 * t7 - t9 * t18) * t15;
    real_type t22  = zeta__dot_D_3(t2, t3, t4, t6);
    result__[ 1   ] = t11 * t22 * t1 - t6 * t22 * t15;
    real_type t27  = zeta__dot_D_2(t2, t3, t4, t6);
    real_type t30  = L__[iL_lambda2__xo];
    real_type t31  = t2 * t30;
    real_type t32  = cos(t3);
    result__[ 2   ] = t11 * t27 * t1 + t11 * t32 * t31 - t6 * t27 * t15;
    real_type t37  = zeta__dot_D_1(t2, t3, t4, t6);
    real_type t40  = sin(t3);
    real_type t45  = L__[iL_lambda4__xo];
    real_type t46  = t11 * t45;
    real_type t47  = ModelPars[iM_kD];
    result__[ 3   ] = t11 * t37 * t1 + t11 * t40 * t30 - t6 * t37 * t15 - 2 * t2 * t47 * t46;
    result__[ 4   ] = t15;
    result__[ 5   ] = t46;
    real_type t63  = t2 * t2;
    result__[ 6   ] = 2 * t10 * ModelPars[iM_wT] + 2 * t10 * t18 * t1 + 2 * t10 * t40 * t31 + 2 * (-t6 * t18 + X__[iX_Omega]) * t10 * t14 + 2 * (-t63 * t47 + X__[iX_fx]) * t10 * t45 + 2 * t10 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo] * U__[iU_v__Omega] + 2 * t10 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo] * U__[iU_v__fx];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DHxpDxpu_numRows() const { return 7; }
  integer PointMassCarModel_3::DHxpDxpu_numCols() const { return 9; }
  integer PointMassCarModel_3::DHxpDxpu_nnz()     const { return 31; }

  void
  PointMassCarModel_3::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[19] = 3   ; jIndex[19] = 6   ;
    iIndex[20] = 4   ; jIndex[20] = 6   ;
    iIndex[21] = 5   ; jIndex[21] = 6   ;
    iIndex[22] = 6   ; jIndex[22] = 0   ;
    iIndex[23] = 6   ; jIndex[23] = 1   ;
    iIndex[24] = 6   ; jIndex[24] = 2   ;
    iIndex[25] = 6   ; jIndex[25] = 3   ;
    iIndex[26] = 6   ; jIndex[26] = 4   ;
    iIndex[27] = 6   ; jIndex[27] = 5   ;
    iIndex[28] = 6   ; jIndex[28] = 6   ;
    iIndex[29] = 6   ; jIndex[29] = 7   ;
    iIndex[30] = 6   ; jIndex[30] = 8   ;
  }


  void
  PointMassCarModel_3::DHxpDxpu_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_V];
    real_type t3   = X__[iX_alpha];
    real_type t4   = X__[iX_n];
    real_type t5   = X__[iX_s];
    real_type t6   = ALIAS_Kappa(t5);
    real_type t7   = zeta__dot_D_4_4(t2, t3, t4, t6);
    real_type t9   = ALIAS_Kappa_D(t5);
    real_type t10  = t9 * t9;
    real_type t11  = X__[iX_sqrt_inv_Vseg];
    real_type t12  = t11 * t11;
    real_type t15  = zeta__dot_D_4(t2, t3, t4, t6);
    real_type t16  = t15 * t1;
    real_type t17  = ALIAS_Kappa_DD(t5);
    real_type t20  = L__[iL_lambda3__xo];
    real_type t21  = t12 * t20;
    real_type t28  = zeta__dot(t2, t3, t4, t6);
    result__[ 0   ] = t12 * t10 * t7 * t1 + t12 * t17 * t16 + (-t6 * t10 * t7 - t6 * t17 * t15 - 2 * t10 * t15 - t17 * t28) * t21;
    real_type t32  = zeta__dot_D_3_4(t2, t3, t4, t6);
    real_type t34  = t12 * t9;
    real_type t35  = t34 * t32 * t1;
    real_type t37  = t6 * t9 * t32;
    real_type t38  = zeta__dot_D_3(t2, t3, t4, t6);
    real_type t39  = t9 * t38;
    result__[ 1   ] = t35 + (-t37 - t39) * t21;
    real_type t42  = zeta__dot_D_2_4(t2, t3, t4, t6);
    real_type t44  = t34 * t42 * t1;
    real_type t46  = t6 * t9 * t42;
    real_type t47  = zeta__dot_D_2(t2, t3, t4, t6);
    real_type t48  = t9 * t47;
    result__[ 2   ] = t44 + (-t46 - t48) * t21;
    real_type t51  = zeta__dot_D_1_4(t2, t3, t4, t6);
    real_type t53  = t34 * t51 * t1;
    real_type t55  = t6 * t9 * t51;
    real_type t56  = zeta__dot_D_1(t2, t3, t4, t6);
    real_type t57  = t9 * t56;
    result__[ 3   ] = t53 + (-t55 - t57) * t21;
    real_type t62  = t11 * t20;
    result__[ 4   ] = 2 * t11 * t9 * t16 + 2 * (-t6 * t9 * t15 - t9 * t28) * t62;
    result__[ 5   ] = -t37 * t21 - t39 * t21 + t35;
    real_type t71  = zeta__dot_D_3_3(t2, t3, t4, t6);
    result__[ 6   ] = t12 * t71 * t1 - t6 * t71 * t21;
    real_type t76  = zeta__dot_D_2_3(t2, t3, t4, t6);
    result__[ 7   ] = t12 * t76 * t1 - t6 * t76 * t21;
    real_type t81  = zeta__dot_D_1_3(t2, t3, t4, t6);
    result__[ 8   ] = t12 * t81 * t1 - t6 * t81 * t21;
    result__[ 9   ] = 2 * t11 * t38 * t1 - 2 * t6 * t38 * t62;
    result__[ 10  ] = -t46 * t21 - t48 * t21 + t44;
    result__[ 11  ] = result__[7];
    real_type t93  = zeta__dot_D_2_2(t2, t3, t4, t6);
    real_type t96  = L__[iL_lambda2__xo];
    real_type t97  = t2 * t96;
    real_type t98  = sin(t3);
    result__[ 12  ] = t12 * t93 * t1 - t12 * t98 * t97 - t6 * t93 * t21;
    real_type t103 = zeta__dot_D_1_2(t2, t3, t4, t6);
    real_type t106 = cos(t3);
    result__[ 13  ] = t12 * t103 * t1 - t6 * t103 * t21 + t12 * t106 * t96;
    result__[ 14  ] = 2 * t11 * t47 * t1 + 2 * t11 * t106 * t97 - 2 * t6 * t47 * t62;
    result__[ 15  ] = -t55 * t21 - t57 * t21 + t53;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t120 = zeta__dot_D_1_1(t2, t3, t4, t6);
    real_type t125 = L__[iL_lambda4__xo];
    real_type t127 = ModelPars[iM_kD];
    result__[ 18  ] = t12 * t120 * t1 - 2 * t127 * t12 * t125 - t6 * t120 * t21;
    real_type t139 = t11 * t125;
    result__[ 19  ] = 2 * t11 * t56 * t1 + 2 * t11 * t98 * t96 - 4 * t2 * t127 * t139 - 2 * t6 * t56 * t62;
    result__[ 20  ] = 2 * t62;
    result__[ 21  ] = 2 * t139;
    result__[ 22  ] = result__[4];
    result__[ 23  ] = result__[9];
    result__[ 24  ] = result__[14];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[21];
    real_type t150 = t2 * t2;
    real_type t155 = L__[iL_lambda5__xo];
    real_type t158 = ModelPars[iM_v__Omega__max];
    real_type t160 = L__[iL_lambda6__xo];
    real_type t163 = ModelPars[iM_v__fx__max];
    result__[ 28  ] = 2 * ModelPars[iM_wT] + 2 * t28 * t1 + 2 * t98 * t97 + 2 * (-t6 * t28 + X__[iX_Omega]) * t20 + 2 * (-t150 * t127 + X__[iX_fx]) * t125 + 2 * t158 * U__[iU_v__Omega] * t155 + 2 * t163 * U__[iU_v__fx] * t160;
    result__[ 29  ] = 2 * t11 * t163 * t160;
    result__[ 30  ] = 2 * t11 * t158 * t155;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 31, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::Hu_numEqns() const { return 2; }

  void
  PointMassCarModel_3::Hu_eval(
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
    real_type t5   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    result__[ 0   ] = t5 * ModelPars[iM_v__fx__max] * L__[iL_lambda6__xo];
    result__[ 1   ] = t5 * ModelPars[iM_v__Omega__max] * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

}

// EOF: PointMassCarModel_3_Methods_AdjointODE.cc
