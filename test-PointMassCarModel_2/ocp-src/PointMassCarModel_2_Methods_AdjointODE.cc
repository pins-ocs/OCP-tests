/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods.cc                                 |
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
    real_type t27  = -t16 * t24 * t20 * t19 - t16 * t12 * t9 + 1;
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
    real_type t53  = -t50 * t48 * t8 * t1 + 1;
    real_type t54  = PowerLimit(t53);
    real_type t55  = t54 * t7;
    real_type t57  = LimitMinSpeed(t1);
    real_type t58  = t57 * t7;
    real_type t61  = t7 * ModelPars[iM_wT];
    real_type t63  = L__[iL_lambda2__xo];
    real_type t64  = t4 * t63;
    real_type t66  = L__[iL_lambda1__xo];
    real_type t68  = V__[0];
    real_type t71  = V__[1];
    real_type t73  = L__[iL_lambda3__xo];
    real_type t75  = V__[2];
    real_type t77  = L__[iL_lambda4__xo];
    real_type t79  = V__[4];
    real_type t81  = L__[iL_lambda5__xo];
    real_type t83  = V__[3];
    result__[ 0   ] = -t71 * t30 * t63 - t68 * t30 * t66 - t75 * t30 * t73 - t79 * t30 * t77 - t83 * t30 * t81 - t30 * t29 - t30 * t35 - t30 * t43 - t30 * t55 - t30 * t58 - t30 * t61 - t30 * t64 - t38 * t37 + t45 * t37;
    real_type t85  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t93  = cos(t2);
    result__[ 1   ] = t93 * t1 * t66 - t71 * t85 * t63 - t68 * t85 * t66 - t75 * t85 * t73 - t79 * t85 * t77 - t83 * t85 * t81 - t85 * t29 - t85 * t35 - t85 * t43 - t85 * t55 - t85 * t58 - t85 * t61 - t85 * t64;
    real_type t106 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t108 = ALIAS_AdherenceEllipse_D(t27);
    real_type t109 = t108 * t37;
    real_type t118 = ALIAS_PowerLimit_D(t53);
    real_type t119 = t118 * t37;
    real_type t124 = ALIAS_LimitMinSpeed_D(t1);
    real_type t127 = sin(t2);
    result__[ 2   ] = -t106 * t29 - 2 * t16 * t24 * t1 * t19 * t109 - t106 * t35 - t106 * t43 - t106 * t55 - t50 * t48 * t8 * t119 - t106 * t58 + t124 * t37 - t106 * t61 + t127 * t66 - t106 * t64 - 2 * t1 * ModelPars[iM_kD] * t73 - t68 * t106 * t66 - t71 * t106 * t63 - t75 * t106 * t73 - t79 * t106 * t77 - t83 * t106 * t81;
    result__[ 3   ] = -2 * t16 * t24 * t20 * t18 * t109 + t63;
    result__[ 4   ] = -t50 * t48 * t1 * t119 - 2 * t16 * t12 * t8 * t109 + t73;
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
    real_type t8   = 1.0 / t6 / t5;
    real_type t9   = X__[iX_fx];
    real_type t10  = t9 * t9;
    real_type t12  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = 1.0 / t12;
    real_type t16  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t17  = 1.0 / t16;
    real_type t19  = X__[iX_Omega];
    real_type t20  = t19 * t19;
    real_type t21  = t1 * t1;
    real_type t24  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t25  = 1.0 / t24;
    real_type t28  = -t17 * t25 * t21 * t20 - t17 * t13 * t10 + 1;
    real_type t29  = AdherenceEllipse(t28);
    real_type t30  = t29 * t8;
    real_type t31  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t32  = t31 * t31;
    real_type t35  = 1.0 / t6;
    real_type t36  = t29 * t35;
    real_type t37  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t40  = Q__[iQ_leftWidth] - t3;
    real_type t41  = RoadLeftBorder(t40);
    real_type t42  = t41 * t8;
    real_type t45  = ALIAS_RoadLeftBorder_D(t40);
    real_type t46  = t45 * t35;
    real_type t49  = t41 * t35;
    real_type t51  = 1.0 / t5;
    real_type t52  = ALIAS_RoadLeftBorder_DD(t40);
    real_type t55  = Q__[iQ_rightWidth] + t3;
    real_type t56  = RoadRightBorder(t55);
    real_type t57  = t56 * t8;
    real_type t60  = ALIAS_RoadRightBorder_D(t55);
    real_type t61  = t60 * t35;
    real_type t64  = t56 * t35;
    real_type t66  = ALIAS_RoadRightBorder_DD(t55);
    real_type t69  = ModelPars[iM_m];
    real_type t70  = ModelPars[iM_Pmax];
    real_type t72  = 1.0 / t70 * t69;
    real_type t74  = -t72 * t9 * t1 + 1;
    real_type t75  = PowerLimit(t74);
    real_type t76  = t75 * t8;
    real_type t79  = 2 * t32 * t30 + 2 * t31 * t46 - 2 * t31 * t61 + 2 * t32 * t42 + 2 * t32 * t57 + 2 * t32 * t76 - t37 * t36 - t37 * t49 - t37 * t64 + t52 * t51 + t66 * t51;
    real_type t80  = t75 * t35;
    real_type t82  = LimitMinSpeed(t1);
    real_type t83  = t82 * t8;
    real_type t86  = t82 * t35;
    real_type t88  = ModelPars[iM_wT];
    real_type t89  = t8 * t88;
    real_type t92  = t35 * t88;
    real_type t94  = L__[iL_lambda2__xo];
    real_type t95  = t4 * t94;
    real_type t97  = L__[iL_lambda1__xo];
    real_type t99  = V__[0];
    real_type t102 = V__[1];
    real_type t104 = L__[iL_lambda3__xo];
    real_type t106 = V__[2];
    real_type t108 = L__[iL_lambda4__xo];
    real_type t110 = V__[4];
    real_type t112 = L__[iL_lambda5__xo];
    real_type t114 = V__[3];
    real_type t116 = -t102 * t37 * t94 - t106 * t37 * t104 - t110 * t37 * t108 - t114 * t37 * t112 - t99 * t37 * t97 + 2 * t32 * t83 + 2 * t32 * t89 - t37 * t80 - t37 * t86 - t37 * t92 - t37 * t95;
    result__[ 0   ] = t79 + t116;
    real_type t117 = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t118 = t117 * t31;
    real_type t121 = zeta__dot_D_2_3(t1, t2, t3, t4);
    result__[ 1   ] = -t102 * t121 * t94 - t106 * t121 * t104 - t110 * t121 * t108 - t114 * t121 * t112 - t99 * t121 * t97 + t117 * t46 - t117 * t61 + 2 * t118 * t30 + 2 * t118 * t42 + 2 * t118 * t57 + 2 * t118 * t76 + 2 * t118 * t83 + 2 * t118 * t89 - t121 * t36 - t121 * t49 - t121 * t64 - t121 * t80 - t121 * t86 - t121 * t92 - t121 * t95;
    real_type t151 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t152 = t151 * t31;
    real_type t155 = ALIAS_AdherenceEllipse_D(t28);
    real_type t156 = t155 * t35;
    real_type t157 = t20 * t156;
    real_type t158 = t25 * t1;
    real_type t159 = t31 * t17;
    real_type t163 = zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t175 = ALIAS_PowerLimit_D(t74);
    real_type t176 = t175 * t35;
    real_type t177 = t9 * t176;
    real_type t178 = t31 * t72;
    real_type t180 = 2 * t159 * t158 * t157 + t151 * t46 - t151 * t61 + 2 * t152 * t30 + 2 * t152 * t42 + 2 * t152 * t57 + 2 * t152 * t76 - t163 * t36 - t163 * t49 - t163 * t64 + t178 * t177;
    real_type t184 = ALIAS_LimitMinSpeed_D(t1);
    real_type t185 = t184 * t35;
    real_type t202 = -t102 * t163 * t94 - t106 * t163 * t104 - t110 * t163 * t108 - t114 * t163 * t112 - t99 * t163 * t97 + 2 * t152 * t83 + 2 * t152 * t89 - t163 * t80 - t163 * t86 - t163 * t92 - t163 * t95 - t31 * t185;
    result__[ 2   ] = t180 + t202;
    real_type t203 = t19 * t156;
    real_type t204 = t25 * t21;
    result__[ 3   ] = 2 * t159 * t204 * t203;
    real_type t207 = t9 * t156;
    real_type t208 = t17 * t13;
    real_type t212 = t1 * t176;
    result__[ 4   ] = 2 * t31 * t208 * t207 + t178 * t212;
    result__[ 5   ] = result__[1];
    real_type t214 = t117 * t117;
    real_type t217 = zeta__dot_D_2_2(t1, t2, t3, t4);
    real_type t235 = sin(t2);
    result__[ 6   ] = -t235 * t1 * t97 - t102 * t217 * t94 - t106 * t217 * t104 - t110 * t217 * t108 - t114 * t217 * t112 - t99 * t217 * t97 + 2 * t214 * t30 + 2 * t214 * t42 + 2 * t214 * t57 + 2 * t214 * t76 + 2 * t214 * t83 + 2 * t214 * t89 - t217 * t36 - t217 * t49 - t217 * t64 - t217 * t80 - t217 * t86 - t217 * t92 - t217 * t95;
    real_type t248 = t151 * t117;
    real_type t251 = t117 * t17;
    real_type t255 = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t265 = t117 * t72;
    real_type t270 = 2 * t251 * t158 * t157 + t265 * t177 + 2 * t248 * t30 + 2 * t248 * t42 + 2 * t248 * t57 + 2 * t248 * t76 + 2 * t248 * t83 - t255 * t36 - t255 * t49 - t255 * t64 - t255 * t80;
    real_type t276 = cos(t2);
    real_type t289 = -t102 * t255 * t94 - t106 * t255 * t104 - t110 * t255 * t108 - t114 * t255 * t112 - t99 * t255 * t97 - t117 * t185 + 2 * t248 * t89 - t255 * t86 - t255 * t92 - t255 * t95 + t276 * t97;
    result__[ 7   ] = t270 + t289;
    result__[ 8   ] = 2 * t251 * t204 * t203;
    result__[ 9   ] = 2 * t117 * t208 * t207 + t265 * t212;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t296 = t151 * t17;
    real_type t303 = ALIAS_LimitMinSpeed_DD(t1);
    real_type t305 = zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t321 = -t102 * t305 * t94 - t106 * t305 * t104 - t110 * t305 * t108 - t114 * t305 * t112 + 4 * t296 * t158 * t157 - t99 * t305 * t97 - 2 * ModelPars[iM_kD] * t104 + t303 * t51 - t305 * t36 - t305 * t64 - t305 * t80 - t305 * t86 - t305 * t95;
    real_type t326 = t151 * t151;
    real_type t339 = t151 * t72;
    real_type t342 = ALIAS_AdherenceEllipse_DD(t28);
    real_type t343 = t342 * t51;
    real_type t344 = t20 * t20;
    real_type t346 = t24 * t24;
    real_type t347 = 1.0 / t346;
    real_type t349 = t16 * t16;
    real_type t350 = 1.0 / t349;
    real_type t354 = ALIAS_PowerLimit_DD(t74);
    real_type t355 = t354 * t51;
    real_type t356 = t69 * t69;
    real_type t358 = t70 * t70;
    real_type t359 = 1.0 / t358;
    real_type t362 = t155 * t51;
    real_type t367 = 4 * t350 * t347 * t21 * t344 * t343 + t359 * t356 * t10 * t355 - 2 * t17 * t25 * t20 * t362 - 2 * t151 * t185 + 2 * t339 * t177 + 2 * t326 * t30 - t305 * t49 - t305 * t92 + 2 * t326 * t42 + 2 * t326 * t57 + 2 * t326 * t76 + 2 * t326 * t83 + 2 * t326 * t89;
    result__[ 12  ] = t321 + t367;
    result__[ 13  ] = 4 * t350 * t347 * t21 * t1 * t20 * t19 * t343 - 4 * t17 * t158 * t19 * t362 + 2 * t296 * t204 * t203;
    real_type t386 = t13 * t9 * t343;
    result__[ 14  ] = t9 * t359 * t356 * t1 * t355 + 4 * t158 * t20 * t350 * t386 + 2 * t151 * t208 * t207 - t72 * t175 * t51 + t339 * t212;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t399 = t21 * t21;
    result__[ 18  ] = 4 * t350 * t347 * t399 * t20 * t343 - 2 * t17 * t204 * t362;
    result__[ 19  ] = 4 * t204 * t19 * t350 * t386;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t410 = t12 * t12;
    result__[ 24  ] = 4 * t350 / t410 * t10 * t343 - 2 * t208 * t362 + t359 * t356 * t21 * t355;
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
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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

// EOF: PointMassCarModel_2_Methods.cc
