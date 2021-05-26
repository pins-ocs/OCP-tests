/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_4_Methods_problem.cc                         |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_4::continuationStep0( real_type s ) {
    real_type t1   = ModelPars[iM_wT0];
    ModelPars[iM_wT] = t1 + (ModelPars[iM_wT1] - t1) * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_4::continuationStep1( real_type s ) {
    real_type t1   = ModelPars[iM_p_epsi0];
    real_type t5   = t1 + (ModelPars[iM_p_epsi1] - t1) * s;
    AdherenceEllipse.update_epsilon(t5);
    RoadRightBorder.update_epsilon(t5);
    RoadLeftBorder.update_epsilon(t5);
    PowerLimit.update_epsilon(t5);
    real_type t6   = ModelPars[iM_up_epsi0];
    real_type t10  = t6 + (ModelPars[iM_up_epsi1] - t6) * s;
    v__fxControl.update_epsilon(t10);
    v__OmegaControl.update_epsilon(t10);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

#if 0
  real_type
  PointMassCarModel_4::H_eval(
    integer              i_segment,
    CellType const &     CELL__,
    P_const_pointer_type P__
  ) const {
    integer        i_cell = CELL__.i_cell;
    real_type const * Q__ = CELL__.qM;
    real_type const * X__ = CELL__.xM;
    real_type const * L__ = CELL__.lambdaM;
    real_type const * U__ = CELL__.uM;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[iX_Omega];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t26  = X__[iX_s];
    real_type t27  = ALIAS_leftWidth(t26);
    real_type t28  = X__[iX_n];
    real_type t30  = RoadLeftBorder(t27 - t28);
    real_type t32  = ALIAS_rightWidth(t26);
    real_type t34  = RoadRightBorder(t32 + t28);
    real_type t43  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15);
    real_type t45  = U__[iU_v__fx];
    real_type t46  = v__fxControl(t45, -1, 1);
    real_type t48  = U__[iU_v__Omega];
    real_type t49  = v__OmegaControl(t48, -1, 1);
    real_type t55  = X__[iX_alpha];
    real_type t56  = ALIAS_Kappa(t26);
    real_type t57  = zeta__dot(t15, t55, t28, t56);
    real_type t61  = sin(t55);
    real_type result__ = t24 * t2 + t30 * t2 + t34 * t2 + t43 * t2 + t46 * t2 + t49 * t2 + t2 * ModelPars[iM_wT] + t57 * t2 * L__[iL_lambda1__xo] + t61 * t15 * t2 * L__[iL_lambda2__xo] - t2 * (t57 * t56 - t13) * L__[iL_lambda3__xo] + t2 * (-ModelPars[iM_kD] * t16 + t3) * L__[iL_lambda4__xo] + ModelPars[iM_v__Omega__max] * t48 * t2 * L__[iL_lambda5__xo] + ModelPars[iM_v__fx__max] * t45 * t2 * L__[iL_lambda6__xo];
    return result__;
  }
#else
  real_type
  PointMassCarModel_4::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[iX_Omega];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t26  = X__[iX_s];
    real_type t27  = ALIAS_leftWidth(t26);
    real_type t28  = X__[iX_n];
    real_type t30  = RoadLeftBorder(t27 - t28);
    real_type t32  = ALIAS_rightWidth(t26);
    real_type t34  = RoadRightBorder(t32 + t28);
    real_type t43  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15);
    real_type t45  = U__[iU_v__fx];
    real_type t46  = v__fxControl(t45, -1, 1);
    real_type t48  = U__[iU_v__Omega];
    real_type t49  = v__OmegaControl(t48, -1, 1);
    real_type t55  = X__[iX_alpha];
    real_type t56  = ALIAS_Kappa(t26);
    real_type t57  = zeta__dot(t15, t55, t28, t56);
    real_type t61  = sin(t55);
    real_type result__ = t24 * t2 + t30 * t2 + t34 * t2 + t43 * t2 + t46 * t2 + t49 * t2 + t2 * ModelPars[iM_wT] + t57 * t2 * L__[iL_lambda1__xo] + t61 * t15 * t2 * L__[iL_lambda2__xo] - t2 * (t57 * t56 - t13) * L__[iL_lambda3__xo] + t2 * (-ModelPars[iM_kD] * t16 + t3) * L__[iL_lambda4__xo] + ModelPars[iM_v__Omega__max] * t48 * t2 * L__[iL_lambda5__xo] + ModelPars[iM_v__fx__max] * t45 * t2 * L__[iL_lambda6__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }
#endif

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  PointMassCarModel_4::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t14  = X__[iX_Omega] * X__[iX_Omega];
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t26  = X__[iX_s];
    real_type t27  = ALIAS_leftWidth(t26);
    real_type t28  = X__[iX_n];
    real_type t30  = RoadLeftBorder(t27 - t28);
    real_type t32  = ALIAS_rightWidth(t26);
    real_type t34  = RoadRightBorder(t32 + t28);
    real_type t43  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15);
    real_type result__ = t24 * t2 + t30 * t2 + t34 * t2 + t43 * t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_4::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t7   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type result__ = t4 * t2 + t7 * t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  PointMassCarModel_4::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t3   = exp(X__[iX_log_inv_Vseg]);
    real_type result__ = t3 * ModelPars[iM_wT];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  PointMassCarModel_4::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    Road2D::SegmentClass const & segmentLeft  = pRoad->getSegmentByIndex(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->getSegmentByIndex(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DmayerDx_numEqns() const
  { return 14; }

  void
  PointMassCarModel_4::DmayerDx_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    Road2D::SegmentClass const & segmentLeft  = pRoad->getSegmentByIndex(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDx_eval", 14, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DmayerDp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_4::DmayerDp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer
  PointMassCarModel_4::DJDx_numEqns() const
  { return 7; }

  void
  PointMassCarModel_4::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
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
    result__[ 0   ] = t15 * t14 + t9 * t8;
    result__[ 1   ] = -t8 + t14;
    result__[ 2   ] = 0;
    real_type t17  = X__[iX_fx];
    real_type t18  = t17 * t17;
    real_type t20  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t21  = 1.0 / t20;
    real_type t24  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t25  = 1.0 / t24;
    real_type t27  = X__[iX_Omega];
    real_type t28  = t27 * t27;
    real_type t29  = X__[iX_V];
    real_type t30  = t29 * t29;
    real_type t33  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t34  = 1.0 / t33;
    real_type t26  = t25 * t34;
    real_type t35  = t21 * t25;
    real_type t37  = -t30 * t28 * t26 - t18 * t35 + 1;
    real_type t38  = ALIAS_AdherenceEllipse_D(t37);
    real_type t39  = t38 * t2;
    real_type t46  = ModelPars[iM_m];
    real_type t48  = 1.0 / ModelPars[iM_Pmax];
    real_type t41  = t48 * t46;
    real_type t51  = -t17 * t29 * t41 + 1;
    real_type t52  = ALIAS_PowerLimit_D(t51);
    real_type t53  = t52 * t2;
    result__[ 3   ] = -2 * t29 * t28 * t39 * t26 - t17 * t53 * t41;
    result__[ 4   ] = -2 * t30 * t27 * t39 * t26;
    result__[ 5   ] = -2 * t17 * t39 * t35 - t29 * t53 * t41;
    real_type t69  = AdherenceEllipse(t37);
    real_type t71  = RoadLeftBorder(t6);
    real_type t73  = RoadRightBorder(t12);
    real_type t75  = PowerLimit(t51);
    real_type t78  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t81  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 6   ] = t69 * t2 + t71 * t2 + t73 * t2 + t75 * t2 + t78 * t2 + t81 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DJDp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_4::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DJDu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_4::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t2   = exp(X__[iX_log_inv_Vseg]);
    real_type t4   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDu_eval", 2, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  PointMassCarModel_4::q_numEqns() const
  { return 4; }

  void
  PointMassCarModel_4::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    result__[ 0   ] = s;
    result__[ 1   ] = ALIAS_L();
    result__[ 2   ] = ALIAS_ssSegmentMin();
    result__[ 3   ] = ALIAS_ssSegmentMax();
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  PointMassCarModel_4::segmentLink_numEqns() const
  { return 0; }

  void
  PointMassCarModel_4::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_4::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_4::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  PointMassCarModel_4::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  PointMassCarModel_4::jump_numEqns() const
  { return 14; }

  void
  PointMassCarModel_4::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    Road2D::SegmentClass const & segmentLeft  = pRoad->getSegmentByIndex(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = XL__[iX_s] - QL__[iQ_zeta];
    result__[ 1   ] = XR__[iX_n] - XL__[iX_n];
    result__[ 2   ] = XR__[iX_alpha] - XL__[iX_alpha];
    result__[ 3   ] = XR__[iX_V] - XL__[iX_V];
    result__[ 4   ] = XR__[iX_Omega] - XL__[iX_Omega];
    result__[ 5   ] = XR__[iX_fx] - XL__[iX_fx];
    result__[ 6   ] = LL__[iL_lambda7__xo];
    result__[ 7   ] = XR__[iX_s] - QR__[iQ_zeta];
    result__[ 8   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 9   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 10  ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 11  ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    result__[ 12  ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo];
    result__[ 13  ] = LR__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 14, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::DjumpDxlxlp_numRows() const
  { return 14; }

  integer
  PointMassCarModel_4::DjumpDxlxlp_numCols() const
  { return 28; }

  integer
  PointMassCarModel_4::DjumpDxlxlp_nnz() const
  { return 24; }

  void
  PointMassCarModel_4::DjumpDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 15  ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 16  ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 17  ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 18  ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 5   ;
    iIndex[10] = 5   ; jIndex[10] = 19  ;
    iIndex[11] = 6   ; jIndex[11] = 13  ;
    iIndex[12] = 7   ; jIndex[12] = 14  ;
    iIndex[13] = 8   ; jIndex[13] = 8   ;
    iIndex[14] = 8   ; jIndex[14] = 22  ;
    iIndex[15] = 9   ; jIndex[15] = 9   ;
    iIndex[16] = 9   ; jIndex[16] = 23  ;
    iIndex[17] = 10  ; jIndex[17] = 10  ;
    iIndex[18] = 10  ; jIndex[18] = 24  ;
    iIndex[19] = 11  ; jIndex[19] = 11  ;
    iIndex[20] = 11  ; jIndex[20] = 25  ;
    iIndex[21] = 12  ; jIndex[21] = 12  ;
    iIndex[22] = 12  ; jIndex[22] = 26  ;
    iIndex[23] = 13  ; jIndex[23] = 27  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_4::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    Road2D::SegmentClass const & segmentLeft  = pRoad->getSegmentByIndex(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    result__[ 5   ] = -1;
    result__[ 6   ] = 1;
    result__[ 7   ] = -1;
    result__[ 8   ] = 1;
    result__[ 9   ] = -1;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    result__[ 12  ] = 1;
    result__[ 13  ] = -1;
    result__[ 14  ] = 1;
    result__[ 15  ] = -1;
    result__[ 16  ] = 1;
    result__[ 17  ] = -1;
    result__[ 18  ] = 1;
    result__[ 19  ] = -1;
    result__[ 20  ] = 1;
    result__[ 21  ] = -1;
    result__[ 22  ] = 1;
    result__[ 23  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 24, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  PointMassCarModel_4::post_numEqns() const
  { return 24; }

  void
  PointMassCarModel_4::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    result__[ 0   ] = v__fxControl(U__[iU_v__fx], -1, 1);
    result__[ 1   ] = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t5   = ModelPars[iM_mu__x__max];
    real_type t6   = t5 * t5;
    real_type t9   = ModelPars[iM_g];
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[iX_Omega];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t18  = ModelPars[iM_mu__y__max];
    real_type t19  = t18 * t18;
    result__[ 2   ] = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t24  = X__[iX_s];
    real_type t25  = ALIAS_leftWidth(t24);
    real_type t26  = X__[iX_n];
    result__[ 3   ] = RoadLeftBorder(t25 - t26);
    real_type t28  = ALIAS_rightWidth(t24);
    result__[ 4   ] = RoadRightBorder(t28 + t26);
    result__[ 5   ] = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15);
    result__[ 6   ] = ALIAS_Kappa(t24);
    result__[ 7   ] = t25;
    result__[ 8   ] = t28;
    result__[ 9   ] = ALIAS_xLane(t24);
    result__[ 10  ] = ALIAS_yLane(t24);
    result__[ 11  ] = ALIAS_theta(t24);
    result__[ 12  ] = ALIAS_xV(t24, t26);
    result__[ 13  ] = ALIAS_yV(t24, t26);
    result__[ 14  ] = ALIAS_xL(t24);
    result__[ 15  ] = ALIAS_yL(t24);
    result__[ 16  ] = ALIAS_xR(t24);
    result__[ 17  ] = ALIAS_yR(t24);
    result__[ 18  ] = t15 * t13;
    real_type t39  = 1.0 / t9;
    result__[ 19  ] = t39 / t5 * t3;
    result__[ 20  ] = t39 / t18 * result__[18];
    real_type t42  = X__[iX_log_inv_Vseg];
    result__[ 21  ] = exp(t42);
    real_type t44  = exp(-t42);
    result__[ 22  ] = t44 * Q__[iQ_L];
    result__[ 23  ] = zeta__dot(t15, X__[iX_alpha], t26, result__[6]);
    Mechatronix::check_in_segment( result__, "post_eval", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_4::integrated_post_numEqns() const
  { return 1; }

  void
  PointMassCarModel_4::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    result__[ 0   ] = exp(X__[iX_log_inv_Vseg]);
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: PointMassCarModel_4_Methods_problem.cc
