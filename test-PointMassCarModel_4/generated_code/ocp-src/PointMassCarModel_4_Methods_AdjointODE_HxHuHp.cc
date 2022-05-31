/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_4::Hxp_numEqns() const { return 7; }

  void
  PointMassCarModel_4::Hxp_eval(
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
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = t3 * L__[iL_lambda1__xo];
    real_type t5   = X__[iX_V];
    real_type t6   = X__[iX_alpha];
    real_type t7   = X__[iX_n];
    real_type t8   = X__[iX_s];
    real_type t9   = ALIAS_Kappa(t8);
    real_type t10  = zeta__dot_D_4(t5, t6, t7, t9);
    real_type t11  = ALIAS_Kappa_D(t8);
    real_type t14  = L__[iL_lambda3__xo];
    real_type t15  = zeta__dot(t5, t6, t7, t9);
    result__[ 0   ] = t11 * t10 * t4 - t3 * (t11 * t10 * t9 + t15 * t11) * t14;
    real_type t22  = zeta__dot_D_3(t5, t6, t7, t9);
    real_type t24  = t9 * t14;
    result__[ 1   ] = -t3 * t22 * t24 + t22 * t4;
    real_type t27  = zeta__dot_D_2(t5, t6, t7, t9);
    real_type t30  = t3 * L__[iL_lambda2__xo];
    real_type t31  = cos(t6);
    result__[ 2   ] = -t3 * t27 * t24 + t31 * t5 * t30 + t27 * t4;
    real_type t36  = zeta__dot_D_1(t5, t6, t7, t9);
    real_type t38  = sin(t6);
    real_type t42  = L__[iL_lambda4__xo];
    real_type t43  = ModelPars[iM_kD];
    result__[ 3   ] = -2 * t3 * t5 * t43 * t42 - t3 * t36 * t24 + t38 * t30 + t36 * t4;
    result__[ 4   ] = t3 * t14;
    result__[ 5   ] = t3 * t42;
    real_type t58  = t5 * t5;
    result__[ 6   ] = t3 * ModelPars[iM_wT] + t15 * t4 + t38 * t5 * t30 - t3 * (t15 * t9 - X__[iX_Omega]) * t14 + t3 * (-t58 * t43 + X__[iX_fx]) * t42 + U__[iU_v__Omega] * ModelPars[iM_v__Omega__max] * t3 * L__[iL_lambda5__xo] + U__[iU_v__fx] * ModelPars[iM_v__fx__max] * t3 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_4::DHxpDxpu_numRows() const { return 7; }
  integer PointMassCarModel_4::DHxpDxpu_numCols() const { return 9; }
  integer PointMassCarModel_4::DHxpDxpu_nnz()     const { return 31; }

  void
  PointMassCarModel_4::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_4::DHxpDxpu_sparse(
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
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = t3 * L__[iL_lambda1__xo];
    real_type t5   = X__[iX_V];
    real_type t6   = X__[iX_alpha];
    real_type t7   = X__[iX_n];
    real_type t8   = X__[iX_s];
    real_type t9   = ALIAS_Kappa(t8);
    real_type t10  = zeta__dot_D_4_4(t5, t6, t7, t9);
    real_type t11  = ALIAS_Kappa_D(t8);
    real_type t12  = t11 * t11;
    real_type t15  = zeta__dot_D_4(t5, t6, t7, t9);
    real_type t16  = ALIAS_Kappa_DD(t8);
    real_type t19  = L__[iL_lambda3__xo];
    real_type t20  = zeta__dot(t5, t6, t7, t9);
    real_type t26  = t15 * t9;
    result__[ 0   ] = t12 * t10 * t4 + t16 * t15 * t4 - t3 * (t12 * t10 * t9 + 2 * t15 * t12 + t20 * t16 + t16 * t26) * t19;
    real_type t31  = zeta__dot_D_3_4(t5, t6, t7, t9);
    real_type t32  = t11 * t31;
    real_type t33  = t32 * t4;
    real_type t34  = zeta__dot_D_3(t5, t6, t7, t9);
    result__[ 1   ] = t33 - t3 * (t11 * t31 * t9 + t34 * t11) * t19;
    real_type t41  = zeta__dot_D_2_4(t5, t6, t7, t9);
    real_type t42  = t11 * t41;
    real_type t43  = t42 * t4;
    real_type t44  = zeta__dot_D_2(t5, t6, t7, t9);
    result__[ 2   ] = t43 - t3 * (t11 * t41 * t9 + t44 * t11) * t19;
    real_type t51  = zeta__dot_D_1_4(t5, t6, t7, t9);
    real_type t52  = t11 * t51;
    real_type t53  = t52 * t4;
    real_type t54  = zeta__dot_D_1(t5, t6, t7, t9);
    result__[ 3   ] = t53 - t3 * (t11 * t51 * t9 + t54 * t11) * t19;
    result__[ 4   ] = t11 * t15 * t4 - t3 * (t20 * t11 + t11 * t26) * t19;
    real_type t68  = t11 * t19;
    real_type t69  = t3 * t34;
    real_type t71  = t9 * t19;
    result__[ 5   ] = -t3 * t32 * t71 - t69 * t68 + t33;
    real_type t74  = zeta__dot_D_3_3(t5, t6, t7, t9);
    result__[ 6   ] = -t3 * t74 * t71 + t74 * t4;
    real_type t78  = zeta__dot_D_2_3(t5, t6, t7, t9);
    result__[ 7   ] = -t3 * t78 * t71 + t78 * t4;
    real_type t82  = zeta__dot_D_1_3(t5, t6, t7, t9);
    result__[ 8   ] = -t3 * t82 * t71 + t82 * t4;
    result__[ 9   ] = t34 * t4 - t69 * t71;
    real_type t88  = t3 * t44;
    result__[ 10  ] = -t3 * t42 * t71 - t88 * t68 + t43;
    result__[ 11  ] = result__[7];
    real_type t92  = zeta__dot_D_2_2(t5, t6, t7, t9);
    real_type t95  = t3 * L__[iL_lambda2__xo];
    real_type t96  = sin(t6);
    real_type t98  = t96 * t5 * t95;
    result__[ 12  ] = -t3 * t92 * t71 + t92 * t4 - t98;
    real_type t101 = zeta__dot_D_1_2(t5, t6, t7, t9);
    real_type t103 = cos(t6);
    result__[ 13  ] = -t3 * t101 * t71 + t101 * t4 + t103 * t95;
    result__[ 14  ] = t103 * t5 * t95 + t44 * t4 - t88 * t71;
    real_type t111 = t3 * t54;
    result__[ 15  ] = -t3 * t52 * t71 - t111 * t68 + t53;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t115 = zeta__dot_D_1_1(t5, t6, t7, t9);
    real_type t119 = L__[iL_lambda4__xo];
    real_type t120 = ModelPars[iM_kD];
    real_type t121 = t120 * t119;
    result__[ 18  ] = -t3 * t115 * t71 + t115 * t4 - 2 * t3 * t121;
    result__[ 19  ] = -2 * t3 * t5 * t121 - t111 * t71 + t54 * t4 + t96 * t95;
    result__[ 20  ] = t3 * t19;
    result__[ 21  ] = t3 * t119;
    result__[ 22  ] = result__[4];
    result__[ 23  ] = result__[9];
    result__[ 24  ] = result__[14];
    result__[ 25  ] = result__[19];
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[21];
    real_type t138 = t5 * t5;
    real_type t145 = t3 * L__[iL_lambda5__xo];
    real_type t147 = ModelPars[iM_v__Omega__max];
    real_type t151 = t3 * L__[iL_lambda6__xo];
    real_type t153 = ModelPars[iM_v__fx__max];
    result__[ 28  ] = t3 * ModelPars[iM_wT] + t20 * t4 + t98 - t3 * (t20 * t9 - X__[iX_Omega]) * t19 + t3 * (-t138 * t120 + X__[iX_fx]) * t119 + t147 * U__[iU_v__Omega] * t145 + t153 * U__[iU_v__fx] * t151;
    result__[ 29  ] = t153 * t151;
    result__[ 30  ] = t147 * t145;
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

  integer PointMassCarModel_4::Hu_numEqns() const { return 2; }

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

}

// EOF: PointMassCarModel_4_Methods_AdjointODE.cc
