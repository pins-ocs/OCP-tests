/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods.cc                                 |
 |                                                                       |
 |  version: 1.0   date 21/1/2021                                        |
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
#define ALIAS_rightWidth_D_R_D(__t1) segmentRight.rightWidth_D_D( __t1)
#define ALIAS_rightWidth_D_R(__t1) segmentRight.rightWidth_D( __t1)
#define ALIAS_rightWidth_D_L_D(__t1) segmentLeft.rightWidth_D_D( __t1)
#define ALIAS_rightWidth_D_L(__t1) segmentLeft.rightWidth_D( __t1)
#define ALIAS_rightWidth_D_D(__t1) segment.rightWidth_D_D( __t1)
#define ALIAS_rightWidth_D(__t1) segment.rightWidth_D( __t1)
#define ALIAS_rightWidth_R_DD(__t1) segmentRight.rightWidth_DD( __t1)
#define ALIAS_rightWidth_R_D(__t1) segmentRight.rightWidth_D( __t1)
#define ALIAS_rightWidth_R(__t1) segmentRight.rightWidth( __t1)
#define ALIAS_rightWidth_L_DD(__t1) segmentLeft.rightWidth_DD( __t1)
#define ALIAS_rightWidth_L_D(__t1) segmentLeft.rightWidth_D( __t1)
#define ALIAS_rightWidth_L(__t1) segmentLeft.rightWidth( __t1)
#define ALIAS_rightWidth_DD(__t1) segment.rightWidth_DD( __t1)
#define ALIAS_rightWidth_D(__t1) segment.rightWidth_D( __t1)
#define ALIAS_rightWidth(__t1) segment.rightWidth( __t1)
#define ALIAS_leftWidth_D_R_D(__t1) segmentRight.leftWidth_D_D( __t1)
#define ALIAS_leftWidth_D_R(__t1) segmentRight.leftWidth_D( __t1)
#define ALIAS_leftWidth_D_L_D(__t1) segmentLeft.leftWidth_D_D( __t1)
#define ALIAS_leftWidth_D_L(__t1) segmentLeft.leftWidth_D( __t1)
#define ALIAS_leftWidth_D_D(__t1) segment.leftWidth_D_D( __t1)
#define ALIAS_leftWidth_D(__t1) segment.leftWidth_D( __t1)
#define ALIAS_leftWidth_R_DD(__t1) segmentRight.leftWidth_DD( __t1)
#define ALIAS_leftWidth_R_D(__t1) segmentRight.leftWidth_D( __t1)
#define ALIAS_leftWidth_R(__t1) segmentRight.leftWidth( __t1)
#define ALIAS_leftWidth_L_DD(__t1) segmentLeft.leftWidth_DD( __t1)
#define ALIAS_leftWidth_L_D(__t1) segmentLeft.leftWidth_D( __t1)
#define ALIAS_leftWidth_L(__t1) segmentLeft.leftWidth( __t1)
#define ALIAS_leftWidth_DD(__t1) segment.leftWidth_DD( __t1)
#define ALIAS_leftWidth_D(__t1) segment.leftWidth_D( __t1)
#define ALIAS_leftWidth(__t1) segment.leftWidth( __t1)
#define ALIAS_yV_R(__t1, __t2) segmentRight.isoY( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.isoY( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.isoY( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.isoX( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.isoX( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.isoX( __t1, __t2)
#define ALIAS_Kappa_R_DD(__t1) segmentRight.isoCurvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.isoCurvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.isoCurvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.isoCurvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.isoCurvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.isoCurvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.isoCurvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.isoCurvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.isoCurvature( __t1)
#define ALIAS_ssSegmentMax_R(___dummy___) segmentRight.ssSegmentMax()
#define ALIAS_ssSegmentMax_L(___dummy___) segmentLeft.ssSegmentMax()
#define ALIAS_ssSegmentMax(___dummy___) segment.ssSegmentMax()
#define ALIAS_ssSegmentMin_R(___dummy___) segmentRight.ssSegmentMin()
#define ALIAS_ssSegmentMin_L(___dummy___) segmentLeft.ssSegmentMin()
#define ALIAS_ssSegmentMin(___dummy___) segment.ssSegmentMin()
#define ALIAS_L_R(___dummy___) segmentRight.length()
#define ALIAS_L_L(___dummy___) segmentLeft.length()
#define ALIAS_L(___dummy___) segment.length()
#define ALIAS_Tmin_DD(__t1) Tmin.DD( __t1)
#define ALIAS_Tmin_D(__t1) Tmin.D( __t1)
#define ALIAS_Spos_DD(__t1) Spos.DD( __t1)
#define ALIAS_Spos_D(__t1) Spos.D( __t1)
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t1   = X__[6];
    real_type t3   = 1.0 / Q__[1];
    real_type t4   = t3 * t1;
    real_type t5   = X__[0];
    real_type t6   = ALIAS_leftWidth(t5);
    real_type t7   = X__[1];
    real_type t8   = t6 - t7;
    real_type t9   = ALIAS_RoadLeftBorder_D(t8);
    real_type t10  = ALIAS_leftWidth_D(t5);
    real_type t13  = ALIAS_rightWidth(t5);
    real_type t14  = t13 + t7;
    real_type t15  = ALIAS_RoadRightBorder_D(t14);
    real_type t16  = ALIAS_rightWidth_D(t5);
    real_type t19  = X__[3];
    real_type t20  = X__[2];
    real_type t21  = ALIAS_Kappa(t5);
    real_type t22  = zeta__dot(t19, t20, t7, t21);
    real_type t23  = ALIAS_Spos_D(t22);
    real_type t24  = zeta__dot_D_4(t19, t20, t7, t21);
    real_type t26  = ALIAS_Kappa_D(t5);
    real_type t30  = t3 * L__[0];
    real_type t31  = t26 * t24;
    real_type t34  = L__[2];
    real_type t35  = t1 * t34;
    result__[ 0   ] = t10 * t9 * t4 + t16 * t15 * t4 + t26 * t24 * t23 * t4 + t1 * t31 * t30 - t3 * (t21 * t31 + t26 * t22) * t35;
    real_type t43  = zeta__dot_D_3(t19, t20, t7, t21);
    result__[ 1   ] = -t3 * t21 * t43 * t35 + t1 * t43 * t30 + t43 * t23 * t4 + t15 * t4 - t9 * t4;
    real_type t51  = zeta__dot_D_2(t19, t20, t7, t21);
    real_type t57  = t3 * L__[1];
    real_type t58  = cos(t20);
    result__[ 2   ] = t1 * t58 * t19 * t57 - t3 * t21 * t51 * t35 + t1 * t51 * t30 + t51 * t23 * t4;
    real_type t65  = X__[5];
    real_type t66  = t65 * t65;
    real_type t68  = ModelPars[10] * ModelPars[10];
    real_type t69  = 1.0 / t68;
    real_type t72  = ModelPars[2] * ModelPars[2];
    real_type t73  = 1.0 / t72;
    real_type t75  = X__[4];
    real_type t76  = t75 * t75;
    real_type t77  = t19 * t19;
    real_type t80  = ModelPars[11] * ModelPars[11];
    real_type t82  = t73 / t80;
    real_type t84  = -t73 * t69 * t66 - t82 * t77 * t76 + 1;
    real_type t85  = ALIAS_AdherenceEllipse_D(t84);
    real_type t86  = t85 * t4;
    real_type t92  = ModelPars[4];
    real_type t94  = 1.0 / ModelPars[0];
    real_type t97  = -t94 * t92 * t65 * t19 + 1;
    real_type t98  = ALIAS_PowerLimit_D(t97);
    real_type t99  = t98 * t4;
    real_type t103 = zeta__dot_D_1(t19, t20, t7, t21);
    real_type t108 = sin(t20);
    real_type t114 = L__[3];
    real_type t115 = t1 * t114;
    real_type t116 = ModelPars[3];
    result__[ 3   ] = -t3 * t21 * t103 * t35 - 2 * t3 * t19 * t116 * t115 - 2 * t82 * t19 * t76 * t86 - t94 * t92 * t65 * t99 + t1 * t103 * t30 + t1 * t108 * t57 + t103 * t23 * t4;
    result__[ 4   ] = -2 * t82 * t77 * t75 * t86 + t3 * t35;
    result__[ 5   ] = -t94 * t92 * t19 * t99 - 2 * t73 * t69 * t65 * t86 + t3 * t115;
    real_type t134 = AdherenceEllipse(t84);
    real_type t136 = RoadLeftBorder(t8);
    real_type t138 = RoadRightBorder(t14);
    real_type t140 = PowerLimit(t97);
    real_type t142 = Spos(t22);
    real_type t144 = Tmin(t1);
    real_type t146 = ALIAS_Tmin_D(t1);
    result__[ 6   ] = t134 * t3 + t136 * t3 + t138 * t3 + t140 * t3 + t142 * t3 + t144 * t3 + t146 * t4 + t3 * ModelPars[7] + t22 * t30 + t108 * t19 * t57 - t3 * (t21 * t22 - t75) * t34 + t3 * (-t77 * t116 + t65) * t114 + U__[1] * ModelPars[14] * t3 * L__[4] + U__[0] * ModelPars[15] * t3 * L__[5];
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t1   = X__[6];
    real_type t3   = 1.0 / Q__[1];
    real_type t4   = t3 * t1;
    real_type t5   = X__[0];
    real_type t6   = ALIAS_leftWidth(t5);
    real_type t7   = X__[1];
    real_type t8   = t6 - t7;
    real_type t9   = ALIAS_RoadLeftBorder_DD(t8);
    real_type t10  = ALIAS_leftWidth_D(t5);
    real_type t11  = t10 * t10;
    real_type t14  = ALIAS_RoadLeftBorder_D(t8);
    real_type t15  = ALIAS_leftWidth_DD(t5);
    real_type t18  = ALIAS_rightWidth(t5);
    real_type t19  = t18 + t7;
    real_type t20  = ALIAS_RoadRightBorder_DD(t19);
    real_type t21  = ALIAS_rightWidth_D(t5);
    real_type t22  = t21 * t21;
    real_type t25  = ALIAS_RoadRightBorder_D(t19);
    real_type t26  = ALIAS_rightWidth_DD(t5);
    real_type t29  = X__[3];
    real_type t30  = X__[2];
    real_type t31  = ALIAS_Kappa(t5);
    real_type t32  = zeta__dot(t29, t30, t7, t31);
    real_type t33  = ALIAS_Spos_DD(t32);
    real_type t34  = zeta__dot_D_4(t29, t30, t7, t31);
    real_type t35  = t34 * t34;
    real_type t37  = ALIAS_Kappa_D(t5);
    real_type t38  = t37 * t37;
    real_type t41  = ALIAS_Spos_D(t32);
    real_type t42  = zeta__dot_D_4_4(t29, t30, t7, t31);
    real_type t47  = ALIAS_Kappa_DD(t5);
    real_type t51  = t3 * L__[0];
    real_type t52  = t38 * t42;
    real_type t55  = t47 * t34;
    real_type t58  = L__[2];
    real_type t59  = t1 * t58;
    result__[ 0   ] = t11 * t9 * t4 + t15 * t14 * t4 + t22 * t20 * t4 + t26 * t25 * t4 + t38 * t35 * t33 * t4 + t38 * t42 * t41 * t4 + t47 * t34 * t41 * t4 + t1 * t52 * t51 + t1 * t55 * t51 - t3 * (t31 * t52 + t31 * t55 + t47 * t32 + 2 * t38 * t34) * t59;
    real_type t69  = t10 * t9 * t4;
    real_type t71  = t21 * t20 * t4;
    real_type t72  = t33 * t4;
    real_type t73  = zeta__dot_D_3(t29, t30, t7, t31);
    real_type t76  = t37 * t34 * t73 * t72;
    real_type t77  = zeta__dot_D_3_4(t29, t30, t7, t31);
    real_type t80  = t37 * t77 * t41 * t4;
    real_type t81  = t37 * t77;
    real_type t83  = t1 * t81 * t51;
    real_type t85  = t37 * t73;
    result__[ 1   ] = -t69 + t71 + t76 + t80 + t83 - t3 * (t31 * t81 + t85) * t59;
    real_type t89  = zeta__dot_D_2(t29, t30, t7, t31);
    real_type t92  = t37 * t34 * t89 * t72;
    real_type t93  = zeta__dot_D_2_4(t29, t30, t7, t31);
    real_type t96  = t37 * t93 * t41 * t4;
    real_type t97  = t37 * t93;
    real_type t99  = t1 * t97 * t51;
    real_type t101 = t37 * t89;
    result__[ 2   ] = t92 + t96 + t99 - t3 * (t31 * t97 + t101) * t59;
    real_type t105 = zeta__dot_D_1(t29, t30, t7, t31);
    real_type t108 = t37 * t34 * t105 * t72;
    real_type t109 = zeta__dot_D_1_4(t29, t30, t7, t31);
    real_type t112 = t37 * t109 * t41 * t4;
    real_type t113 = t37 * t109;
    real_type t115 = t1 * t113 * t51;
    real_type t117 = t37 * t105;
    result__[ 3   ] = t108 + t112 + t115 - t3 * (t31 * t113 + t117) * t59;
    real_type t121 = t14 * t3;
    real_type t123 = t25 * t3;
    real_type t125 = t41 * t3;
    real_type t126 = t37 * t34;
    result__[ 4   ] = t10 * t121 + t21 * t123 + t126 * t125 + t126 * t51 - t3 * (t31 * t126 + t37 * t32) * t58;
    real_type t136 = t3 * t31 * t37;
    result__[ 5   ] = -t136 * t77 * t59 - t3 * t85 * t59 - t69 + t71 + t76 + t80 + t83;
    real_type t142 = t73 * t73;
    real_type t145 = zeta__dot_D_3_3(t29, t30, t7, t31);
    result__[ 6   ] = -t3 * t31 * t145 * t59 + t1 * t145 * t51 + t142 * t33 * t4 + t145 * t41 * t4 + t20 * t4 + t9 * t4;
    real_type t156 = zeta__dot_D_2_3(t29, t30, t7, t31);
    result__[ 7   ] = -t3 * t31 * t156 * t59 + t73 * t89 * t33 * t4 + t1 * t156 * t51 + t156 * t41 * t4;
    real_type t164 = t105 * t33;
    real_type t167 = zeta__dot_D_1_3(t29, t30, t7, t31);
    result__[ 8   ] = -t3 * t31 * t167 * t59 + t1 * t167 * t51 + t73 * t164 * t4 + t167 * t41 * t4;
    real_type t178 = t3 * t31;
    result__[ 9   ] = -t178 * t73 * t58 + t73 * t125 + t73 * t51 - t121 + t123;
    result__[ 10  ] = -t3 * t101 * t59 - t136 * t93 * t59 + t92 + t96 + t99;
    result__[ 11  ] = result__[7];
    real_type t184 = t89 * t89;
    real_type t187 = zeta__dot_D_2_2(t29, t30, t7, t31);
    real_type t193 = t3 * L__[1];
    real_type t194 = sin(t30);
    result__[ 12  ] = -t1 * t194 * t29 * t193 - t3 * t31 * t187 * t59 + t1 * t187 * t51 + t184 * t33 * t4 + t187 * t41 * t4;
    real_type t203 = zeta__dot_D_1_2(t29, t30, t7, t31);
    real_type t208 = cos(t30);
    result__[ 13  ] = -t3 * t31 * t203 * t59 + t1 * t208 * t193 + t1 * t203 * t51 + t89 * t164 * t4 + t203 * t41 * t4;
    result__[ 14  ] = -t178 * t89 * t58 + t208 * t29 * t193 + t89 * t125 + t89 * t51;
    result__[ 15  ] = -t136 * t109 * t59 - t3 * t117 * t59 + t108 + t112 + t115;
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t224 = X__[5];
    real_type t225 = t224 * t224;
    real_type t227 = ModelPars[10] * ModelPars[10];
    real_type t228 = 1.0 / t227;
    real_type t231 = ModelPars[2] * ModelPars[2];
    real_type t232 = 1.0 / t231;
    real_type t234 = X__[4];
    real_type t235 = t234 * t234;
    real_type t236 = t29 * t29;
    real_type t239 = ModelPars[11] * ModelPars[11];
    real_type t240 = 1.0 / t239;
    real_type t241 = t232 * t240;
    real_type t243 = -t232 * t228 * t225 - t241 * t236 * t235 + 1;
    real_type t244 = ALIAS_AdherenceEllipse_DD(t243);
    real_type t245 = t244 * t4;
    real_type t246 = t235 * t235;
    real_type t248 = t239 * t239;
    real_type t250 = t231 * t231;
    real_type t251 = 1.0 / t250;
    real_type t252 = t251 / t248;
    real_type t256 = ALIAS_AdherenceEllipse_D(t243);
    real_type t257 = t256 * t4;
    real_type t263 = ModelPars[4];
    real_type t264 = ModelPars[0];
    real_type t265 = 1.0 / t264;
    real_type t268 = -t265 * t263 * t224 * t29 + 1;
    real_type t269 = ALIAS_PowerLimit_DD(t268);
    real_type t270 = t269 * t4;
    real_type t271 = t263 * t263;
    real_type t273 = t264 * t264;
    real_type t274 = 1.0 / t273;
    real_type t277 = t105 * t105;
    real_type t280 = zeta__dot_D_1_1(t29, t30, t7, t31);
    real_type t288 = L__[3];
    real_type t290 = ModelPars[3];
    result__[ 18  ] = -2 * t3 * t290 * t1 * t288 + t274 * t271 * t225 * t270 - 2 * t232 * t240 * t235 * t257 + 4 * t252 * t236 * t246 * t245 - t3 * t31 * t280 * t59 + t1 * t280 * t51 + t277 * t33 * t4 + t280 * t41 * t4;
    result__[ 19  ] = 4 * t252 * t236 * t29 * t235 * t234 * t245 - 4 * t241 * t29 * t234 * t257;
    real_type t304 = t224 * t244 * t4;
    real_type t305 = t251 * t228;
    real_type t315 = ALIAS_PowerLimit_D(t268);
    result__[ 20  ] = t224 * t274 * t271 * t29 * t270 + 4 * t240 * t29 * t235 * t305 * t304 - t265 * t263 * t315 * t4;
    real_type t319 = t256 * t3;
    real_type t325 = t315 * t3;
    result__[ 21  ] = -2 * t232 * t240 * t29 * t235 * t319 - t265 * t263 * t224 * t325 - 2 * t3 * t29 * t290 * t288 - t178 * t105 * t58 + t105 * t125 + t105 * t51 + t194 * t193;
    result__[ 22  ] = result__[19];
    real_type t338 = t236 * t236;
    real_type t344 = t232 * t240 * t236;
    result__[ 23  ] = 4 * t252 * t338 * t235 * t245 - 2 * t344 * t257;
    result__[ 24  ] = 4 * t240 * t236 * t234 * t305 * t304;
    result__[ 25  ] = -2 * t344 * t234 * t319 + t3 * t58;
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[24];
    real_type t355 = t227 * t227;
    result__[ 28  ] = 4 * t251 / t355 * t225 * t245 - 2 * t232 * t228 * t256 * t4 + t274 * t271 * t236 * t270;
    result__[ 29  ] = -2 * t232 * t228 * t224 * t319 - t265 * t263 * t29 * t325 + t3 * t288;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[9];
    result__[ 32  ] = result__[14];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[25];
    result__[ 35  ] = result__[29];
    real_type t376 = ALIAS_Tmin_D(t1);
    real_type t379 = ALIAS_Tmin_DD(t1);
    result__[ 36  ] = 2 * t376 * t3 + t379 * t4;
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t3   = 1.0 / Q__[1];
    real_type t6   = X__[6];
    result__[ 0   ] = t6 * ModelPars[15] * t3 * L__[5];
    result__[ 1   ] = t6 * ModelPars[14] * t3 * L__[4];
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t3   = 1.0 / Q__[1];
    result__[ 0   ] = ModelPars[15] * t3 * L__[5];
    result__[ 1   ] = ModelPars[14] * t3 * L__[4];
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = L__[2];
    result__[ 3   ] = L__[3];
    result__[ 4   ] = L__[4];
    result__[ 5   ] = L__[5];
    result__[ 6   ] = L__[6];
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
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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

// EOF: PointMassCarModel_3_Methods.cc
