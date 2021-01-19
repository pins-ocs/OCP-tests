/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods1.cc                                |
 |                                                                       |
 |  version: 1.0   date 19/1/2021                                        |
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
#define ALIAS_rightWidth_R(__t1) segmentRight.rightWidth( __t1)
#define ALIAS_rightWidth_L(__t1) segmentLeft.rightWidth( __t1)
#define ALIAS_rightWidth(__t1) segment.rightWidth( __t1)
#define ALIAS_leftWidth_R_D(__t1) segmentRight.leftWidth_D( __t1)
#define ALIAS_leftWidth_R(__t1) segmentRight.leftWidth( __t1)
#define ALIAS_leftWidth_L_D(__t1) segmentLeft.leftWidth_D( __t1)
#define ALIAS_leftWidth_L(__t1) segmentLeft.leftWidth( __t1)
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_2::continuationStep0( real_type s ) {
    real_type t1   = ModelPars[8];
    ModelPars[7] = t1 + (ModelPars[9] - t1) * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_2::continuationStep1( real_type s ) {
    real_type t1   = ModelPars[5];
    real_type t5   = t1 + (ModelPars[6] - t1) * s;
    AdherenceEllipse.update_epsilon(t5);
    RoadRightBorder.update_epsilon(t5);
    RoadLeftBorder.update_epsilon(t5);
    PowerLimit.update_epsilon(t5);
    real_type t6   = ModelPars[12];
    real_type t10  = t6 + (ModelPars[13] - t6) * s;
    v__fxControl.update_epsilon(t10);
    v__OmegaControl.update_epsilon(t10);
  }

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  PointMassCarModel_2::zeta__dot( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    return -1.0 / (n__XO * Kappa__XO - 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_1( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    return -1.0 / (n__XO * Kappa__XO - 1) * t1;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_1_1( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    return 0;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_1_2( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    return 1.0 / (n__XO * Kappa__XO - 1) * t1;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_1_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t4   = pow(n__XO * Kappa__XO - 1, 2);
    return Kappa__XO / t4 * t1;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_1_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t4   = pow(n__XO * Kappa__XO - 1, 2);
    return n__XO / t4 * t1;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_2( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    return 1.0 / (n__XO * Kappa__XO - 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_2_2( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    return 1.0 / (n__XO * Kappa__XO - 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_2_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return -Kappa__XO / t5 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_2_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return -n__XO / t5 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return Kappa__XO / t5 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_3_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t4   = n__XO * Kappa__XO - 1;
    real_type t5   = t4 * t4;
    real_type t8   = Kappa__XO * Kappa__XO;
    return -2 * t8 / t5 / t4 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_3_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t3   = n__XO * Kappa__XO;
    real_type t5   = t3 - 1;
    real_type t6   = t5 * t5;
    return -1.0 / t6 / t5 * (t3 + 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return n__XO / t5 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_2::zeta__dot_D_4_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t4   = n__XO * Kappa__XO - 1;
    real_type t5   = t4 * t4;
    real_type t8   = n__XO * n__XO;
    return -2 * t8 / t5 / t4 * t1 * V__XO;
  }


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  PointMassCarModel_2::H_eval(
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
    real_type t1   = X__[2];
    real_type t2   = X__[1];
    real_type t3   = X__[0];
    real_type t4   = Q__[1];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = 1.0 / t5;
    real_type t7   = X__[4];
    real_type t8   = t7 * t7;
    real_type t10  = ModelPars[10] * ModelPars[10];
    real_type t14  = ModelPars[2] * ModelPars[2];
    real_type t15  = 1.0 / t14;
    real_type t17  = X__[3];
    real_type t18  = t17 * t17;
    real_type t19  = t1 * t1;
    real_type t22  = ModelPars[11] * ModelPars[11];
    real_type t27  = AdherenceEllipse(1 - t15 / t10 * t8 - t15 / t22 * t19 * t18);
    real_type t31  = RoadLeftBorder(Q__[2] - t3);
    real_type t35  = RoadRightBorder(Q__[3] + t3);
    real_type t44  = PowerLimit(1 - ModelPars[4] / ModelPars[0] * t7 * t1);
    real_type t46  = LimitMinSpeed(t1);
    real_type t52  = sin(t2);
    real_type t64  = U__[0];
    real_type t69  = U__[1];
    real_type t73  = v__fxControl(t64, -1, 1);
    real_type t75  = v__OmegaControl(t69, -1, 1);
    return t27 * t6 + t31 * t6 + t35 * t6 + t44 * t6 + t46 * t6 + t6 * ModelPars[7] + t52 * t1 * L__[0] + (-t5 * t4 + t17) * L__[1] + (-t19 * ModelPars[3] + t7) * L__[2] + ModelPars[15] * t64 * L__[3] + ModelPars[14] * t69 * L__[4] + t73 * t6 + t75 * t6;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  PointMassCarModel_2::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t1   = X__[2];
    real_type t3   = X__[0];
    real_type t5   = zeta__dot(t1, X__[1], t3, Q__[1]);
    real_type t6   = 1.0 / t5;
    real_type t7   = X__[4];
    real_type t8   = t7 * t7;
    real_type t10  = ModelPars[10] * ModelPars[10];
    real_type t14  = ModelPars[2] * ModelPars[2];
    real_type t15  = 1.0 / t14;
    real_type t18  = X__[3] * X__[3];
    real_type t19  = t1 * t1;
    real_type t22  = ModelPars[11] * ModelPars[11];
    real_type t27  = AdherenceEllipse(1 - t15 / t10 * t8 - t15 / t22 * t19 * t18);
    real_type t31  = RoadLeftBorder(Q__[2] - t3);
    real_type t35  = RoadRightBorder(Q__[3] + t3);
    real_type t44  = PowerLimit(1 - ModelPars[4] / ModelPars[0] * t7 * t1);
    real_type t46  = LimitMinSpeed(t1);
    return t27 * t6 + t31 * t6 + t35 * t6 + t44 * t6 + t46 * t6;
  }

  real_type
  PointMassCarModel_2::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t5   = zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
    real_type t6   = 1.0 / t5;
    real_type t8   = v__fxControl(U__[0], -1, 1);
    real_type t11  = v__OmegaControl(U__[1], -1, 1);
    return t11 * t6 + t8 * t6;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  PointMassCarModel_2::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t6   = zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
    return 1.0 / t6 * ModelPars[7];
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  PointMassCarModel_2::mayer_target(
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
    return 0;
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  PointMassCarModel_2::q_numEqns() const
  { return 11; }

  void
  PointMassCarModel_2::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    result__[ 0   ] = s;
    result__[ 1   ] = ALIAS_Kappa(s);
    result__[ 2   ] = ALIAS_leftWidth(s);
    result__[ 3   ] = ALIAS_rightWidth(s);
    result__[ 4   ] = ALIAS_xLane(s);
    result__[ 5   ] = ALIAS_yLane(s);
    result__[ 6   ] = ALIAS_theta(s);
    result__[ 7   ] = ALIAS_xL(s);
    result__[ 8   ] = ALIAS_yL(s);
    result__[ 9   ] = ALIAS_xR(s);
    result__[ 10  ] = ALIAS_yR(s);
  }

  /*\
   |    ___
   |   / __|_  _ ___ ______
   |  | (_ | || / -_|_-<_-<
   |   \___|\_,_\___/__/__/
  \*/

  integer
  PointMassCarModel_2::u_guess_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
      Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    std::fill_n( UGUESS__.pointer(), 2, 0 );
    UGUESS__[ iU_v__fx    ] = 0;
    UGUESS__[ iU_v__Omega ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 2, i_segment );
  }

  void
  PointMassCarModel_2::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[11];
    real_type X__[5];
    real_type L__[5];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    Q__[1] = (LEFT__.q[1]+RIGHT__.q[1])/2;
    Q__[2] = (LEFT__.q[2]+RIGHT__.q[2])/2;
    Q__[3] = (LEFT__.q[3]+RIGHT__.q[3])/2;
    Q__[4] = (LEFT__.q[4]+RIGHT__.q[4])/2;
    Q__[5] = (LEFT__.q[5]+RIGHT__.q[5])/2;
    Q__[6] = (LEFT__.q[6]+RIGHT__.q[6])/2;
    Q__[7] = (LEFT__.q[7]+RIGHT__.q[7])/2;
    Q__[8] = (LEFT__.q[8]+RIGHT__.q[8])/2;
    Q__[9] = (LEFT__.q[9]+RIGHT__.q[9])/2;
    Q__[10] = (LEFT__.q[10]+RIGHT__.q[10])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  PointMassCarModel_2::u_check_if_admissible(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    ok = ok && v__OmegaControl.check_range(U__[1], -1, 1);
    ok = ok && v__fxControl.check_range(U__[0], -1, 1);
    return ok;
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  PointMassCarModel_2::post_numEqns() const
  { return 14; }

  void
  PointMassCarModel_2::post_eval(
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
    result__[ 0   ] = v__fxControl(U__[0], -1, 1);
    result__[ 1   ] = v__OmegaControl(U__[1], -1, 1);
    real_type t3   = X__[4];
    real_type t4   = t3 * t3;
    real_type t5   = ModelPars[10];
    real_type t6   = t5 * t5;
    real_type t9   = ModelPars[2];
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[3];
    real_type t14  = t13 * t13;
    real_type t15  = X__[2];
    real_type t16  = t15 * t15;
    real_type t18  = ModelPars[11];
    real_type t19  = t18 * t18;
    result__[ 2   ] = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t25  = X__[0];
    result__[ 3   ] = RoadLeftBorder(Q__[2] - t25);
    result__[ 4   ] = RoadRightBorder(Q__[3] + t25);
    result__[ 5   ] = PowerLimit(1 - ModelPars[4] / ModelPars[0] * t3 * t15);
    result__[ 6   ] = LimitMinSpeed(t15);
    real_type t36  = Q__[0];
    result__[ 7   ] = ALIAS_xV(t36, t25);
    result__[ 8   ] = ALIAS_yV(t36, t25);
    result__[ 9   ] = t15 * t13;
    real_type t39  = 1.0 / t9;
    result__[ 10  ] = t39 / t5 * t3;
    result__[ 11  ] = t39 / t18 * result__[9];
    real_type t44  = zeta__dot(t15, X__[1], t25, Q__[1]);
    result__[ 12  ] = 1.0 / t44;
    result__[ 13  ] = t44;
    Mechatronix::check_in_segment( result__, "post_eval", 14, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::integrated_post_numEqns() const
  { return 1; }

  void
  PointMassCarModel_2::integrated_post_eval(
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
    real_type t5   = zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
    result__[ 0   ] = 1.0 / t5;
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods1.cc
