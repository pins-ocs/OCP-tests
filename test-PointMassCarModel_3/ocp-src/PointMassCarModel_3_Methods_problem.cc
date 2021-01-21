/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods1.cc                                |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  PointMassCarModel_3::continuationStep0( real_type s ) {
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
  PointMassCarModel_3::continuationStep1( real_type s ) {
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
  PointMassCarModel_3::zeta__dot( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    return 1.0 / (-n__XO * Kappa__XO + 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_1( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    return 1.0 / (-n__XO * Kappa__XO + 1) * t1;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_1_1( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    return 0;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_1_2( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    return 1.0 / (n__XO * Kappa__XO - 1) * t1;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_1_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return 1.0 / t5 * Kappa__XO * t1;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_1_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return 1.0 / t5 * n__XO * t1;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_2( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    return 1.0 / (n__XO * Kappa__XO - 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_2_2( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    return 1.0 / (n__XO * Kappa__XO - 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_2_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return -Kappa__XO / t5 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_2_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = sin(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return -n__XO / t5 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return 1.0 / t5 * Kappa__XO * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_3_3( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t3   = Kappa__XO * Kappa__XO;
    real_type t5   = n__XO * Kappa__XO - 1;
    real_type t6   = t5 * t5;
    return -2 / t6 / t5 * t3 * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_3_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t3   = n__XO * Kappa__XO;
    real_type t5   = t3 - 1;
    real_type t6   = t5 * t5;
    return -1.0 / t6 / t5 * (t3 + 1) * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t5   = pow(n__XO * Kappa__XO - 1, 2);
    return 1.0 / t5 * n__XO * t1 * V__XO;
  }

  real_type
  PointMassCarModel_3::zeta__dot_D_4_4( real_type V__XO, real_type alpha__XO, real_type n__XO, real_type Kappa__XO ) const {
    real_type t1   = cos(alpha__XO);
    real_type t3   = n__XO * n__XO;
    real_type t5   = n__XO * Kappa__XO - 1;
    real_type t6   = t5 * t5;
    return -2 / t6 / t5 * t3 * t1 * V__XO;
  }


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  PointMassCarModel_3::H_eval(
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
    real_type t1   = X__[6];
    real_type t3   = 1.0 / Q__[1];
    real_type t4   = t3 * t1;
    real_type t5   = X__[5];
    real_type t6   = t5 * t5;
    real_type t8   = ModelPars[10] * ModelPars[10];
    real_type t12  = ModelPars[2] * ModelPars[2];
    real_type t13  = 1.0 / t12;
    real_type t15  = X__[4];
    real_type t16  = t15 * t15;
    real_type t17  = X__[3];
    real_type t18  = t17 * t17;
    real_type t21  = ModelPars[11] * ModelPars[11];
    real_type t26  = AdherenceEllipse(1 - t13 / t8 * t6 - t13 / t21 * t18 * t16);
    real_type t28  = X__[0];
    real_type t29  = ALIAS_leftWidth(t28);
    real_type t30  = X__[1];
    real_type t32  = RoadLeftBorder(t29 - t30);
    real_type t34  = ALIAS_rightWidth(t28);
    real_type t36  = RoadRightBorder(t34 + t30);
    real_type t45  = PowerLimit(1 - ModelPars[4] / ModelPars[0] * t5 * t17);
    real_type t47  = X__[2];
    real_type t48  = ALIAS_Kappa(t28);
    real_type t49  = zeta__dot(t17, t47, t30, t48);
    real_type t50  = Spos(t49);
    real_type t52  = Tmin(t1);
    real_type t63  = sin(t47);
    real_type t82  = U__[1];
    real_type t89  = U__[0];
    real_type t94  = v__fxControl(t89, -1, 1);
    real_type t96  = v__OmegaControl(t82, -1, 1);
    return t26 * t4 + t32 * t4 + t36 * t4 + t45 * t4 + t50 * t4 + t52 * t4 + t3 * t1 * ModelPars[7] + t1 * t49 * t3 * L__[0] + t1 * t63 * t17 * t3 * L__[1] - t3 * (t48 * t49 - t15) * t1 * L__[2] + t3 * (-t18 * ModelPars[3] + t5) * t1 * L__[3] + t1 * ModelPars[14] * t82 * t3 * L__[4] + t1 * ModelPars[15] * t89 * t3 * L__[5] + t94 * t4 + t96 * t4;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  PointMassCarModel_3::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t1   = X__[6];
    real_type t4   = 1.0 / Q__[1] * t1;
    real_type t5   = X__[5];
    real_type t6   = t5 * t5;
    real_type t8   = ModelPars[10] * ModelPars[10];
    real_type t12  = ModelPars[2] * ModelPars[2];
    real_type t13  = 1.0 / t12;
    real_type t16  = X__[4] * X__[4];
    real_type t17  = X__[3];
    real_type t18  = t17 * t17;
    real_type t21  = ModelPars[11] * ModelPars[11];
    real_type t26  = AdherenceEllipse(1 - t13 / t8 * t6 - t13 / t21 * t18 * t16);
    real_type t28  = X__[0];
    real_type t29  = ALIAS_leftWidth(t28);
    real_type t30  = X__[1];
    real_type t32  = RoadLeftBorder(t29 - t30);
    real_type t34  = ALIAS_rightWidth(t28);
    real_type t36  = RoadRightBorder(t34 + t30);
    real_type t45  = PowerLimit(1 - ModelPars[4] / ModelPars[0] * t5 * t17);
    real_type t48  = ALIAS_Kappa(t28);
    real_type t49  = zeta__dot(t17, X__[2], t30, t48);
    real_type t50  = Spos(t49);
    real_type t52  = Tmin(t1);
    return t26 * t4 + t32 * t4 + t36 * t4 + t45 * t4 + t50 * t4 + t52 * t4;
  }

  real_type
  PointMassCarModel_3::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t4   = 1.0 / Q__[1] * X__[6];
    real_type t6   = v__fxControl(U__[0], -1, 1);
    real_type t9   = v__OmegaControl(U__[1], -1, 1);
    return t6 * t4 + t9 * t4;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  PointMassCarModel_3::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    return ModelPars[7] * X__[6] / Q__[1];
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  PointMassCarModel_3::mayer_target(
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
  PointMassCarModel_3::q_numEqns() const
  { return 4; }

  void
  PointMassCarModel_3::q_eval(
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
   |    ___
   |   / __|_  _ ___ ______
   |  | (_ | || / -_|_-<_-<
   |   \___|\_,_\___/__/__/
  \*/

  integer
  PointMassCarModel_3::u_guess_numEqns() const
  { return 2; }

  void
  PointMassCarModel_3::u_guess_eval(
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
  PointMassCarModel_3::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[4];
    real_type X__[7];
    real_type L__[7];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    Q__[1] = (LEFT__.q[1]+RIGHT__.q[1])/2;
    Q__[2] = (LEFT__.q[2]+RIGHT__.q[2])/2;
    Q__[3] = (LEFT__.q[3]+RIGHT__.q[3])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    X__[6] = (LEFT__.x[6]+RIGHT__.x[6])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
    L__[6] = (LEFT__.lambda[6]+RIGHT__.lambda[6])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  PointMassCarModel_3::u_check_if_admissible(
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
  PointMassCarModel_3::post_numEqns() const
  { return 25; }

  void
  PointMassCarModel_3::post_eval(
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
    real_type t3   = X__[5];
    real_type t4   = t3 * t3;
    real_type t5   = ModelPars[10];
    real_type t6   = t5 * t5;
    real_type t9   = ModelPars[2];
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[4];
    real_type t14  = t13 * t13;
    real_type t15  = X__[3];
    real_type t16  = t15 * t15;
    real_type t18  = ModelPars[11];
    real_type t19  = t18 * t18;
    result__[ 2   ] = AdherenceEllipse(1 - t11 / t6 * t4 - t11 / t19 * t16 * t14);
    real_type t24  = X__[0];
    real_type t25  = ALIAS_leftWidth(t24);
    real_type t26  = X__[1];
    result__[ 3   ] = RoadLeftBorder(t25 - t26);
    real_type t28  = ALIAS_rightWidth(t24);
    result__[ 4   ] = RoadRightBorder(t28 + t26);
    result__[ 5   ] = PowerLimit(1 - ModelPars[4] / ModelPars[0] * t3 * t15);
    real_type t38  = ALIAS_Kappa(t24);
    real_type t39  = zeta__dot(t15, X__[2], t26, t38);
    result__[ 6   ] = Spos(t39);
    result__[ 7   ] = Tmin(X__[6]);
    result__[ 8   ] = t38;
    result__[ 9   ] = t25;
    result__[ 10  ] = t28;
    result__[ 11  ] = ALIAS_xLane(t24);
    result__[ 12  ] = ALIAS_yLane(t24);
    result__[ 13  ] = ALIAS_theta(t24);
    result__[ 14  ] = ALIAS_xV(t24, t26);
    result__[ 15  ] = ALIAS_yV(t24, t26);
    result__[ 16  ] = ALIAS_xL(t24);
    result__[ 17  ] = ALIAS_yL(t24);
    result__[ 18  ] = ALIAS_xR(t24);
    result__[ 19  ] = ALIAS_yR(t24);
    result__[ 20  ] = t15 * t13;
    real_type t43  = 1.0 / t9;
    result__[ 21  ] = t43 / t5 * t3;
    result__[ 22  ] = t43 / t18 * result__[20];
    result__[ 23  ] = 1.0 / t39;
    result__[ 24  ] = t39;
    Mechatronix::check_in_segment( result__, "post_eval", 25, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_3::integrated_post_numEqns() const
  { return 1; }

  void
  PointMassCarModel_3::integrated_post_eval(
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
    result__[ 0   ] = X__[6] / Q__[1];
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: PointMassCarModel_3_Methods1.cc
