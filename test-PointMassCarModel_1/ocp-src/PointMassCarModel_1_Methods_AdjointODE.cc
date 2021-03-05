/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods.cc                                 |
 |                                                                       |
 |  version: 1.0   date 5/3/2021                                         |
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
#define ALIAS_yV_R(__t1, __t2) segmentRight.isoY( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.isoY( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.isoY( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.isoX( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.isoX( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.isoX( __t1, __t2)
#define ALIAS_yR_R(__t1) segmentRight.isoRightY( __t1)
#define ALIAS_yR_L(__t1) segmentLeft.isoRightY( __t1)
#define ALIAS_yR(__t1) segment.isoRightY( __t1)
#define ALIAS_xR_R(__t1) segmentRight.isoRightX( __t1)
#define ALIAS_xR_L(__t1) segmentLeft.isoRightX( __t1)
#define ALIAS_xR(__t1) segment.isoRightX( __t1)
#define ALIAS_yL_R(__t1) segmentRight.isoLeftY( __t1)
#define ALIAS_yL_L(__t1) segmentLeft.isoLeftY( __t1)
#define ALIAS_yL(__t1) segment.isoLeftY( __t1)
#define ALIAS_xL_R(__t1) segmentRight.isoLeftX( __t1)
#define ALIAS_xL_L(__t1) segmentLeft.isoLeftX( __t1)
#define ALIAS_xL(__t1) segment.isoLeftX( __t1)
#define ALIAS_theta_R_DD(__t1) segmentRight.isoAngle_DD( __t1)
#define ALIAS_theta_R_D(__t1) segmentRight.isoAngle_D( __t1)
#define ALIAS_theta_R(__t1) segmentRight.isoAngle( __t1)
#define ALIAS_theta_L_DD(__t1) segmentLeft.isoAngle_DD( __t1)
#define ALIAS_theta_L_D(__t1) segmentLeft.isoAngle_D( __t1)
#define ALIAS_theta_L(__t1) segmentLeft.isoAngle( __t1)
#define ALIAS_theta_DD(__t1) segment.isoAngle_DD( __t1)
#define ALIAS_theta_D(__t1) segment.isoAngle_D( __t1)
#define ALIAS_theta(__t1) segment.isoAngle( __t1)
#define ALIAS_yLane_R_DD(__t1) segmentRight.isoY_DD( __t1)
#define ALIAS_yLane_R_D(__t1) segmentRight.isoY_D( __t1)
#define ALIAS_yLane_R(__t1) segmentRight.isoY( __t1)
#define ALIAS_yLane_L_DD(__t1) segmentLeft.isoY_DD( __t1)
#define ALIAS_yLane_L_D(__t1) segmentLeft.isoY_D( __t1)
#define ALIAS_yLane_L(__t1) segmentLeft.isoY( __t1)
#define ALIAS_yLane_DD(__t1) segment.isoY_DD( __t1)
#define ALIAS_yLane_D(__t1) segment.isoY_D( __t1)
#define ALIAS_yLane(__t1) segment.isoY( __t1)
#define ALIAS_xLane_R_DD(__t1) segmentRight.isoX_DD( __t1)
#define ALIAS_xLane_R_D(__t1) segmentRight.isoX_D( __t1)
#define ALIAS_xLane_R(__t1) segmentRight.isoX( __t1)
#define ALIAS_xLane_L_DD(__t1) segmentLeft.isoX_DD( __t1)
#define ALIAS_xLane_L_D(__t1) segmentLeft.isoX_D( __t1)
#define ALIAS_xLane_L(__t1) segmentLeft.isoX( __t1)
#define ALIAS_xLane_DD(__t1) segment.isoX_DD( __t1)
#define ALIAS_xLane_D(__t1) segment.isoX_D( __t1)
#define ALIAS_xLane(__t1) segment.isoX( __t1)
#define ALIAS_rightWidth_R_DD(__t1) segmentRight.rightWidth_DD( __t1)
#define ALIAS_rightWidth_R_D(__t1) segmentRight.rightWidth_D( __t1)
#define ALIAS_rightWidth_R(__t1) segmentRight.rightWidth( __t1)
#define ALIAS_rightWidth_L_DD(__t1) segmentLeft.rightWidth_DD( __t1)
#define ALIAS_rightWidth_L_D(__t1) segmentLeft.rightWidth_D( __t1)
#define ALIAS_rightWidth_L(__t1) segmentLeft.rightWidth( __t1)
#define ALIAS_rightWidth_DD(__t1) segment.rightWidth_DD( __t1)
#define ALIAS_rightWidth_D(__t1) segment.rightWidth_D( __t1)
#define ALIAS_rightWidth(__t1) segment.rightWidth( __t1)
#define ALIAS_leftWidth_R_DD(__t1) segmentRight.leftWidth_DD( __t1)
#define ALIAS_leftWidth_R_D(__t1) segmentRight.leftWidth_D( __t1)
#define ALIAS_leftWidth_R(__t1) segmentRight.leftWidth( __t1)
#define ALIAS_leftWidth_L_DD(__t1) segmentLeft.leftWidth_DD( __t1)
#define ALIAS_leftWidth_L_D(__t1) segmentLeft.leftWidth_D( __t1)
#define ALIAS_leftWidth_L(__t1) segmentLeft.leftWidth( __t1)
#define ALIAS_leftWidth_DD(__t1) segment.leftWidth_DD( __t1)
#define ALIAS_leftWidth_D(__t1) segment.leftWidth_D( __t1)
#define ALIAS_leftWidth(__t1) segment.leftWidth( __t1)
#define ALIAS_Kappa_R_DD(__t1) segmentRight.isoCurvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.isoCurvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.isoCurvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.isoCurvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.isoCurvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.isoCurvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.isoCurvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.isoCurvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.isoCurvature( __t1)
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    real_type t25  = -t14 * t22 * t18 * t17 - t14 * t10 * t7 + 1;
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
    real_type t47  = -t44 * t42 * t6 * t1 + 1;
    real_type t48  = PowerLimit(t47);
    real_type t50  = LimitMinSpeed(t1);
    real_type t52  = ModelPars[iM_wT];
    real_type t54  = L__[iL_lambda1__xo];
    real_type t55  = t1 * t54;
    real_type t56  = sin(t2);
    real_type t59  = L__[iL_lambda2__xo];
    real_type t60  = t16 * t59;
    real_type t62  = L__[iL_lambda3__xo];
    real_type t64  = ModelPars[iM_kD];
    real_type t66  = -t18 * t64 + t6;
    real_type t70  = L__[iL_lambda4__xo] * U__[iU_v__Omega];
    real_type t71  = ModelPars[iM_v__Omega__max];
    real_type t76  = L__[iL_lambda5__xo] * U__[iU_v__fx];
    real_type t77  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t5 * t56 * t55 + t66 * t5 * t62 + t5 * t71 * t70 + t5 * t77 * t76 + t26 * t5 + t30 * t5 - t33 * t32 + t39 * t32 + t37 * t5 + t48 * t5 + t50 * t5 + t5 * t52 + t5 * t60;
    real_type t80  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    real_type t87  = cos(t2);
    result__[ 1   ] = t32 * t87 * t55 + t80 * t56 * t55 + t66 * t80 * t62 + t80 * t71 * t70 + t80 * t77 * t76 + t26 * t80 + t30 * t80 + t37 * t80 + t48 * t80 + t50 * t80 + t80 * t52 + t80 * t60;
    real_type t99  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t101 = ALIAS_AdherenceEllipse_D(t25);
    real_type t102 = t101 * t32;
    real_type t111 = ALIAS_PowerLimit_D(t47);
    real_type t112 = t111 * t32;
    real_type t117 = ALIAS_LimitMinSpeed_D(t1);
    real_type t127 = t32 * t62;
    result__[ 2   ] = -2 * t14 * t22 * t1 * t17 * t102 - t44 * t42 * t6 * t112 - 2 * t1 * t64 * t127 + t32 * t56 * t54 + t99 * t56 * t55 + t66 * t99 * t62 + t99 * t71 * t70 + t99 * t77 * t76 + t117 * t32 + t26 * t99 + t30 * t99 + t37 * t99 + t48 * t99 + t50 * t99 + t99 * t52 + t99 * t60;
    result__[ 3   ] = -2 * t14 * t22 * t18 * t16 * t102 + t32 * t59;
    result__[ 4   ] = -t44 * t42 * t1 * t112 - 2 * t14 * t10 * t6 * t102 + t127;
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    real_type t25  = -t14 * t22 * t18 * t17 - t14 * t10 * t7 + 1;
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
    real_type t59  = ModelPars[iM_wT];
    real_type t61  = L__[iL_lambda1__xo];
    real_type t62  = t1 * t61;
    real_type t63  = sin(t2);
    real_type t66  = L__[iL_lambda2__xo];
    real_type t67  = t16 * t66;
    real_type t69  = L__[iL_lambda3__xo];
    real_type t71  = ModelPars[iM_kD];
    real_type t73  = -t71 * t18 + t6;
    real_type t77  = L__[iL_lambda4__xo] * U__[iU_v__Omega];
    real_type t78  = ModelPars[iM_v__Omega__max];
    real_type t83  = L__[iL_lambda5__xo] * U__[iU_v__fx];
    real_type t84  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t5 * t63 * t62 + t73 * t5 * t69 + t5 * t78 * t77 + t5 * t84 * t83 + t26 * t5 + t30 * t5 - 2 * t33 * t32 + 2 * t43 * t32 + t37 * t36 + t46 * t36 + t41 * t5 + t55 * t5 + t57 * t5 + t5 * t59 + t5 * t67;
    real_type t87  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t90  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    real_type t97  = cos(t2);
    result__[ 1   ] = t32 * t97 * t62 + t87 * t63 * t62 + t73 * t87 * t69 + t87 * t78 * t77 + t87 * t84 * t83 + t26 * t87 + t30 * t87 - t33 * t90 + t41 * t87 + t43 * t90 + t55 * t87 + t57 * t87 + t87 * t59 + t87 * t67;
    real_type t109 = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t111 = ALIAS_AdherenceEllipse_D(t25);
    real_type t112 = t111 * t32;
    real_type t114 = t22 * t1;
    real_type t115 = t14 * t114;
    real_type t119 = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t124 = ALIAS_PowerLimit_D(t54);
    real_type t125 = t124 * t32;
    real_type t127 = t51 * t49 * t6;
    real_type t130 = ALIAS_LimitMinSpeed_D(t1);
    real_type t133 = t63 * t61;
    real_type t140 = t32 * t69;
    real_type t141 = t1 * t71;
    result__[ 2   ] = t109 * t63 * t62 + t73 * t109 * t69 + t109 * t78 * t77 + t109 * t84 * t83 - 2 * t115 * t17 * t112 + t26 * t109 + t30 * t109 + t41 * t109 + t55 * t109 + t57 * t109 + t109 * t59 + t109 * t67 - t33 * t119 + t43 * t119 - t127 * t125 + t130 * t32 + t32 * t133 - 2 * t141 * t140;
    real_type t149 = t22 * t18;
    real_type t150 = t14 * t149;
    result__[ 3   ] = -2 * t150 * t16 * t112 + t32 * t66;
    real_type t154 = t10 * t6;
    real_type t155 = t14 * t154;
    real_type t159 = t51 * t49 * t1;
    result__[ 4   ] = -2 * t155 * t112 - t159 * t125 + t140;
    result__[ 5   ] = result__[1];
    real_type t161 = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = t161 * t63 * t62 + t73 * t161 * t69 + t161 * t78 * t77 + t161 * t84 * t83 - t36 * t63 * t62 + 2 * t90 * t97 * t62 + t26 * t161 + t30 * t161 + t41 * t161 + t55 * t161 + t57 * t161 + t161 * t59 + t161 * t67;
    real_type t182 = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t184 = t111 * t90;
    real_type t191 = t124 * t90;
    real_type t206 = t90 * t69;
    result__[ 7   ] = -2 * t115 * t17 * t184 + t119 * t97 * t62 + t182 * t63 * t62 + t73 * t182 * t69 + t182 * t78 * t77 + t182 * t84 * t83 + t36 * t97 * t61 - t127 * t191 + t130 * t90 + t90 * t133 - 2 * t141 * t206 + t26 * t182 + t30 * t182 + t41 * t182 + t55 * t182 + t57 * t182 + t182 * t59 + t182 * t67;
    result__[ 8   ] = -2 * t150 * t16 * t184 + t90 * t66;
    result__[ 9   ] = -2 * t155 * t184 - t159 * t191 + t206;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t220 = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t228 = ALIAS_LimitMinSpeed_DD(t1);
    real_type t231 = t111 * t36;
    real_type t236 = ALIAS_AdherenceEllipse_DD(t25);
    real_type t237 = t236 * t36;
    real_type t238 = t17 * t17;
    real_type t240 = t21 * t21;
    real_type t241 = 1.0 / t240;
    real_type t243 = t13 * t13;
    real_type t244 = 1.0 / t243;
    real_type t249 = t111 * t119;
    real_type t253 = t124 * t119;
    real_type t256 = ALIAS_PowerLimit_DD(t54);
    real_type t257 = t256 * t36;
    real_type t258 = t49 * t49;
    real_type t260 = t50 * t50;
    real_type t261 = 1.0 / t260;
    real_type t273 = t119 * t69;
    real_type t281 = t261 * t258 * t7 * t257 - 4 * t115 * t17 * t249 + t220 * t63 * t62 + t73 * t220 * t69 + t220 * t78 * t77 + t220 * t84 * t83 - 2 * t71 * t36 * t69 + 2 * t119 * t133 - 2 * t127 * t253 - 4 * t141 * t273 + t220 * t67;
    result__[ 12  ] = 4 * t244 * t241 * t18 * t238 * t237 - 2 * t14 * t22 * t17 * t231 + 2 * t130 * t119 + t26 * t220 + t30 * t220 + t41 * t220 + t55 * t220 + t57 * t220 + t220 * t59 + t228 * t36 + t281;
    result__[ 13  ] = 4 * t244 * t241 * t18 * t1 * t17 * t16 * t237 - 4 * t115 * t16 * t231 - 2 * t150 * t16 * t249 + t119 * t66;
    real_type t298 = t154 * t237;
    result__[ 14  ] = t6 * t261 * t258 * t1 * t257 + 4 * t114 * t17 * t244 * t298 - t52 * t124 * t36 - 2 * t155 * t249 - t159 * t253 + t273;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t311 = t18 * t18;
    result__[ 18  ] = 4 * t244 * t241 * t311 * t17 * t237 - 2 * t150 * t231;
    result__[ 19  ] = 4 * t149 * t16 * t244 * t298;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t321 = t9 * t9;
    result__[ 24  ] = 4 * t244 / t321 * t7 * t237 - 2 * t14 * t10 * t231 + t261 * t258 * t18 * t257;
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t3   = ModelPars[iM_v__fx__max] * L__[iL_lambda5__xo];
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
    real_type t13  = ModelPars[iM_v__Omega__max] * L__[iL_lambda4__xo];
    result__[ 3   ] = t8 * t13;
    result__[ 4   ] = t9 * t13;
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
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 0, i_segment );
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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

// EOF: PointMassCarModel_1_Methods.cc
