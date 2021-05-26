/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t8   = X__[iX_fx];
    real_type t9   = t8 * t8;
    real_type t11  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t16  = 1.0 / t15;
    real_type t18  = X__[iX_Omega];
    real_type t19  = t18 * t18;
    real_type t20  = t1 * t1;
    real_type t23  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = 1.0 / t23;
    real_type t25  = t16 * t12;
    real_type t27  = -t16 * t19 * t20 * t24 - t9 * t25 + 1;
    real_type t28  = AdherenceEllipse(t27);
    real_type t29  = t28 * t7;
    real_type t30  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t33  = Q__[iQ_leftWidth] - t3;
    real_type t34  = RoadLeftBorder(t33);
    real_type t35  = t34 * t7;
    real_type t37  = 1.0 / t5;
    real_type t38  = ALIAS_RoadLeftBorder_D(t33);
    real_type t41  = Q__[iQ_rightWidth] + t3;
    real_type t42  = RoadRightBorder(t41);
    real_type t43  = t42 * t7;
    real_type t45  = ALIAS_RoadRightBorder_D(t41);
    real_type t48  = ModelPars[iM_m];
    real_type t50  = 1.0 / ModelPars[iM_Pmax];
    real_type t53  = -t1 * t48 * t50 * t8 + 1;
    real_type t54  = PowerLimit(t53);
    real_type t55  = t54 * t7;
    real_type t57  = LimitMinSpeed(t1);
    real_type t58  = t57 * t7;
    real_type t61  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t62  = t61 * t7;
    real_type t65  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t66  = t65 * t7;
    real_type t69  = t7 * ModelPars[iM_wT];
    real_type t71  = L__[iL_lambda2__xo];
    real_type t72  = t4 * t71;
    real_type t74  = L__[iL_lambda1__xo];
    real_type t76  = V__[0];
    real_type t79  = V__[1];
    real_type t81  = L__[iL_lambda3__xo];
    real_type t83  = V__[2];
    real_type t85  = L__[iL_lambda4__xo];
    real_type t87  = V__[4];
    real_type t89  = L__[iL_lambda5__xo];
    real_type t91  = V__[3];
    result__[ 0   ] = -t79 * t30 * t71 - t76 * t30 * t74 - t83 * t30 * t81 - t87 * t30 * t85 - t91 * t30 * t89 - t29 * t30 - t30 * t35 - t30 * t43 - t30 * t55 - t30 * t58 - t30 * t62 - t30 * t66 - t30 * t69 - t30 * t72 - t37 * t38 + t37 * t45;
    real_type t93  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t103 = cos(t2);
    result__[ 1   ] = t103 * t1 * t74 - t79 * t93 * t71 - t76 * t93 * t74 - t83 * t93 * t81 - t87 * t93 * t85 - t91 * t93 * t89 - t93 * t29 - t93 * t35 - t93 * t43 - t93 * t55 - t93 * t58 - t93 * t62 - t93 * t66 - t93 * t69 - t93 * t72;
    real_type t116 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t118 = ALIAS_AdherenceEllipse_D(t27);
    real_type t119 = t118 * t37;
    real_type t128 = ALIAS_PowerLimit_D(t53);
    real_type t129 = t128 * t37;
    real_type t134 = ALIAS_LimitMinSpeed_D(t1);
    real_type t139 = sin(t2);
    real_type t120 = t16 * t24;
    real_type t130 = t50 * t48;
    result__[ 2   ] = -t116 * t29 - 2 * t1 * t19 * t119 * t120 - t116 * t35 - t116 * t43 - t116 * t55 - t8 * t129 * t130 - t116 * t58 + t134 * t37 - t116 * t62 - t116 * t66 - t116 * t69 + t139 * t74 - t116 * t72 - 2 * t1 * ModelPars[iM_kD] * t81 - t76 * t116 * t74 - t79 * t116 * t71 - t83 * t116 * t81 - t87 * t116 * t85 - t91 * t116 * t89;
    result__[ 3   ] = -2 * t20 * t18 * t119 * t120 + t71;
    result__[ 4   ] = -t1 * t129 * t130 - 2 * t8 * t119 * t25 + t81;
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
  PointMassCarModel_2::DHxDx_sparse(
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
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t13  = 1.0 / t5;
    real_type t8   = t13 * t7;
    real_type t9   = LimitMinSpeed(t1);
    real_type t10  = t9 * t8;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_wT];
    real_type t16  = t8 * t15;
    real_type t20  = Q__[iQ_rightWidth] + t3;
    real_type t21  = RoadRightBorder(t20);
    real_type t22  = t21 * t8;
    real_type t26  = Q__[iQ_leftWidth] - t3;
    real_type t27  = RoadLeftBorder(t26);
    real_type t28  = t27 * t8;
    real_type t31  = X__[iX_fx];
    real_type t32  = t31 * t31;
    real_type t34  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t35  = 1.0 / t34;
    real_type t38  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t39  = 1.0 / t38;
    real_type t41  = X__[iX_Omega];
    real_type t42  = t41 * t41;
    real_type t43  = t1 * t1;
    real_type t46  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t47  = 1.0 / t46;
    real_type t24  = t39 * t47;
    real_type t50  = -t43 * t42 * t24 - t39 * t35 * t32 + 1;
    real_type t51  = AdherenceEllipse(t50);
    real_type t52  = t51 * t8;
    real_type t56  = ModelPars[iM_m];
    real_type t57  = ModelPars[iM_Pmax];
    real_type t59  = 1.0 / t57 * t56;
    real_type t61  = -t59 * t31 * t1 + 1;
    real_type t62  = PowerLimit(t61);
    real_type t63  = t62 * t8;
    real_type t67  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t68  = t67 * t8;
    real_type t72  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t73  = t72 * t8;
    real_type t76  = t7;
    real_type t77  = t76 * t15;
    real_type t78  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t80  = t9 * t76;
    real_type t82  = t21 * t76;
    real_type t84  = t27 * t76;
    real_type t86  = t51 * t76;
    real_type t88  = 2 * t12 * t10 + 2 * t12 * t16 + 2 * t12 * t22 + 2 * t12 * t28 + 2 * t12 * t52 + 2 * t12 * t63 + 2 * t12 * t68 + 2 * t12 * t73 - t78 * t77 - t78 * t80 - t78 * t82 - t78 * t84 - t78 * t86;
    real_type t89  = t62 * t76;
    real_type t91  = L__[iL_lambda2__xo];
    real_type t92  = t4 * t91;
    real_type t94  = L__[iL_lambda1__xo];
    real_type t96  = V__[0];
    real_type t99  = V__[1];
    real_type t101 = L__[iL_lambda3__xo];
    real_type t103 = V__[2];
    real_type t105 = L__[iL_lambda5__xo];
    real_type t107 = V__[3];
    real_type t109 = L__[iL_lambda4__xo];
    real_type t111 = V__[4];
    real_type t113 = t67 * t76;
    real_type t115 = t72 * t76;
    real_type t117 = ALIAS_RoadRightBorder_D(t20);
    real_type t118 = t117 * t76;
    real_type t121 = ALIAS_RoadLeftBorder_D(t26);
    real_type t122 = t121 * t76;
    real_type t125 = t13;
    real_type t126 = ALIAS_RoadRightBorder_DD(t20);
    real_type t128 = ALIAS_RoadLeftBorder_DD(t26);
    real_type t130 = -t103 * t78 * t101 - t107 * t78 * t105 - t111 * t78 * t109 - t99 * t78 * t91 - t96 * t78 * t94 - 2 * t11 * t118 + 2 * t11 * t122 - t78 * t113 - t78 * t115 + t126 * t125 + t128 * t125 - t78 * t89 - t78 * t92;
    result__[ 0   ] = t88 + t130;
    real_type t131 = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t132 = t131 * t11;
    real_type t135 = zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t151 = 2 * t132 * t10 - t131 * t118 + t131 * t122 + 2 * t132 * t22 + 2 * t132 * t28 + 2 * t132 * t52 + 2 * t132 * t63 - t135 * t80 - t135 * t82 - t135 * t84 - t135 * t86 - t135 * t89;
    real_type t172 = -t103 * t135 * t101 - t107 * t135 * t105 - t111 * t135 * t109 - t99 * t135 * t91 - t96 * t135 * t94 - t135 * t113 - t135 * t115 + 2 * t132 * t16 + 2 * t132 * t68 + 2 * t132 * t73 - t135 * t77 - t135 * t92;
    result__[ 1   ] = t151 + t172;
    real_type t173 = zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t192 = -t103 * t173 * t101 - t107 * t173 * t105 - t111 * t173 * t109 - t99 * t173 * t91 - t96 * t173 * t94 - t173 * t113 - t173 * t115 - t173 * t77 - t173 * t80 - t173 * t82 - t173 * t86 - t173 * t89 - t173 * t92;
    real_type t194 = ALIAS_LimitMinSpeed_D(t1);
    real_type t195 = t194 * t76;
    real_type t197 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t200 = ALIAS_PowerLimit_D(t61);
    real_type t201 = t200 * t76;
    real_type t202 = t31 * t201;
    real_type t203 = t11 * t59;
    real_type t205 = ALIAS_AdherenceEllipse_D(t50);
    real_type t206 = t205 * t76;
    real_type t207 = t42 * t206;
    real_type t208 = t47 * t1;
    real_type t209 = t11 * t39;
    real_type t213 = t197 * t11;
    real_type t230 = 2 * t209 * t208 * t207 + 2 * t213 * t10 - t11 * t195 - t197 * t118 + t197 * t122 + 2 * t213 * t16 - t173 * t84 + t203 * t202 + 2 * t213 * t22 + 2 * t213 * t28 + 2 * t213 * t52 + 2 * t213 * t63 + 2 * t213 * t68 + 2 * t213 * t73;
    result__[ 2   ] = t192 + t230;
    real_type t231 = t41 * t206;
    real_type t232 = t47 * t43;
    result__[ 3   ] = 2 * t209 * t232 * t231;
    real_type t235 = t31 * t206;
    real_type t236 = t39 * t35;
    real_type t240 = t1 * t201;
    result__[ 4   ] = 2 * t11 * t236 * t235 + t203 * t240;
    result__[ 5   ] = result__[1];
    real_type t242 = t131 * t131;
    real_type t245 = zeta__dot_D_2_2(t1, t2, t3, t4);
    real_type t261 = 2 * t242 * t10 + 2 * t242 * t22 + 2 * t242 * t28 + 2 * t242 * t52 + 2 * t242 * t63 + 2 * t242 * t68 - t245 * t80 - t245 * t82 - t245 * t84 - t245 * t86 - t245 * t89;
    real_type t270 = sin(t2);
    real_type t283 = -t270 * t1 * t94 - t103 * t245 * t101 - t107 * t245 * t105 - t111 * t245 * t109 - t99 * t245 * t91 - t96 * t245 * t94 - t245 * t113 - t245 * t115 + 2 * t242 * t16 + 2 * t242 * t73 - t245 * t77 - t245 * t92;
    result__[ 6   ] = t261 + t283;
    real_type t284 = t131 * t59;
    real_type t286 = t131 * t39;
    real_type t290 = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t307 = -t103 * t290 * t101 - t107 * t290 * t105 - t111 * t290 * t109 + 2 * t286 * t208 * t207 - t99 * t290 * t91 - t96 * t290 * t94 - t290 * t113 - t290 * t115 + t284 * t202 - t290 * t82 - t290 * t86 - t290 * t89 - t290 * t92;
    real_type t312 = cos(t2);
    real_type t314 = t197 * t131;
    real_type t331 = 2 * t314 * t10 - t131 * t195 + 2 * t314 * t16 + 2 * t314 * t22 + 2 * t314 * t28 - t290 * t77 - t290 * t80 - t290 * t84 + t312 * t94 + 2 * t314 * t52 + 2 * t314 * t63 + 2 * t314 * t68 + 2 * t314 * t73;
    result__[ 7   ] = t307 + t331;
    result__[ 8   ] = 2 * t286 * t232 * t231;
    result__[ 9   ] = 2 * t131 * t236 * t235 + t284 * t240;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t338 = ALIAS_AdherenceEllipse_DD(t50);
    real_type t339 = t338 * t125;
    real_type t340 = t42 * t42;
    real_type t342 = t46 * t46;
    real_type t343 = 1.0 / t342;
    real_type t345 = t38 * t38;
    real_type t346 = 1.0 / t345;
    real_type t350 = t197 * t59;
    real_type t353 = t197 * t39;
    real_type t357 = t197 * t197;
    real_type t374 = zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t344 = t346 * t343;
    real_type t379 = 4 * t43 * t340 * t339 * t344 + 4 * t353 * t208 * t207 + 2 * t357 * t10 + 2 * t357 * t16 + 2 * t350 * t202 + 2 * t357 * t22 + 2 * t357 * t28 + 2 * t357 * t52 + 2 * t357 * t63 + 2 * t357 * t68 + 2 * t357 * t73 - t374 * t80 - t374 * t84 - t374 * t86 - t374 * t89;
    real_type t400 = ALIAS_LimitMinSpeed_DD(t1);
    real_type t402 = ALIAS_PowerLimit_DD(t61);
    real_type t403 = t402 * t125;
    real_type t404 = t56 * t56;
    real_type t406 = t57 * t57;
    real_type t407 = 1.0 / t406;
    real_type t410 = t205 * t125;
    real_type t381 = t407 * t404;
    real_type t415 = -t103 * t374 * t101 - t107 * t374 * t105 - t111 * t374 * t109 - 2 * t42 * t410 * t24 + t32 * t403 * t381 - t99 * t374 * t91 - t96 * t374 * t94 - 2 * ModelPars[iM_kD] * t101 - t374 * t113 - t374 * t115 + t400 * t125 - 2 * t197 * t195 - t374 * t77 - t374 * t82 - t374 * t92;
    result__[ 12  ] = t379 + t415;
    result__[ 13  ] = 4 * t1 * t42 * t41 * t339 * t43 * t344 - 4 * t39 * t208 * t41 * t410 + 2 * t353 * t232 * t231;
    real_type t434 = t35 * t31 * t339;
    real_type t436 = t346 * t434;
    result__[ 14  ] = t31 * t407 * t404 * t1 * t403 - t59 * t200 * t125 + 2 * t197 * t236 * t235 + 4 * t436 * t208 * t42 + t350 * t240;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t447 = t43 * t43;
    result__[ 18  ] = 4 * t447 * t42 * t339 * t344 - 2 * t39 * t232 * t410;
    result__[ 19  ] = 4 * t436 * t232 * t41;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t458 = t34 * t34;
    result__[ 24  ] = 4 * t346 / t458 * t32 * t339 - 2 * t236 * t410 + t43 * t403 * t381;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHxDp_sparse(
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
  PointMassCarModel_2::Hu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::Hu_eval(
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
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t8 * t6 + L__[iL_lambda4__xo] * ModelPars[iM_v__fx__max];
    real_type t14  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t14 * t6 + L__[iL_lambda5__xo] * ModelPars[iM_v__Omega__max];
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
  { return 6; }

  void
  PointMassCarModel_2::DHuDx_pattern(
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
  PointMassCarModel_2::DHuDx_sparse(
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
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t9   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    real_type t10  = t7 * t9;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    result__[ 0   ] = -t11 * t10;
    real_type t13  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t13 * t10;
    real_type t15  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t15 * t10;
    real_type t18  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    real_type t19  = t18 * t7;
    result__[ 3   ] = -t11 * t19;
    result__[ 4   ] = -t13 * t19;
    result__[ 5   ] = -t15 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 6, i_segment );
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHuDp_sparse(
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
  PointMassCarModel_2::Hp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_2::Hp_eval(
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHpDp_sparse(
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
  PointMassCarModel_2::eta_numEqns() const
  { return 5; }

  void
  PointMassCarModel_2::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    integer iIndex[],
    integer jIndex[]
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
    real_type t5   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = L__[iL_lambda1__xo];
    result__[ 0   ] = t6 * t5;
    real_type t7   = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t7 * t6;
    real_type t8   = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t8 * t6;
    real_type t9   = L__[iL_lambda2__xo];
    result__[ 3   ] = t9 * t5;
    result__[ 4   ] = t7 * t9;
    result__[ 5   ] = t9 * t8;
    real_type t10  = L__[iL_lambda3__xo];
    result__[ 6   ] = t10 * t5;
    result__[ 7   ] = t10 * t7;
    result__[ 8   ] = t10 * t8;
    real_type t11  = L__[iL_lambda5__xo];
    result__[ 9   ] = t11 * t5;
    result__[ 10  ] = t7 * t11;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DetaDp_sparse(
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
  PointMassCarModel_2::nu_numEqns() const
  { return 5; }

  void
  PointMassCarModel_2::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = V__[0];
    result__[ 0   ] = t6 * t5;
    real_type t7   = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t7 * t6;
    real_type t8   = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t8 * t6;
    real_type t9   = V__[1];
    result__[ 3   ] = t9 * t5;
    result__[ 4   ] = t7 * t9;
    result__[ 5   ] = t9 * t8;
    real_type t10  = V__[2];
    result__[ 6   ] = t10 * t5;
    result__[ 7   ] = t10 * t7;
    result__[ 8   ] = t10 * t8;
    real_type t11  = V__[4];
    result__[ 9   ] = t11 * t5;
    result__[ 10  ] = t7 * t11;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
