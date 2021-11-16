/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_problem.cc                         |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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
#define ALIAS_yV_R(__t1, __t2) segmentRight.iso_y( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.iso_y( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.iso_y( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.iso_x( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.iso_x( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.iso_x( __t1, __t2)
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
#define ALIAS_Kappa_R_DD(__t1) segmentRight.iso_curvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.iso_curvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.iso_curvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.iso_curvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.iso_curvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.iso_curvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.iso_curvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.iso_curvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.iso_curvature( __t1)
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
  PointMassCarModel_2::continuationStep1( real_type s ) {
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
  PointMassCarModel_2::H_eval(
    integer              i_segment,
    CellType const &     CELL__,
    P_const_pointer_type P__
  ) const {
    integer     i_cell = CELL__.i_cell;
    real_const_ptr Q__ = CELL__.qM;
    real_const_ptr X__ = CELL__.xM;
    real_const_ptr L__ = CELL__.lambdaM;
    real_const_ptr U__ = CELL__.uM;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_fx];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t11  = X__[iX_Omega];
    real_type t12  = t11 * t11;
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = AdherenceEllipse(1 - t9 / t4 * t2 - t9 / t17 * t14 * t12);
    real_type t30  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13);
    real_type t32  = X__[iX_n];
    real_type t34  = RoadLeftBorder(Q__[iQ_leftWidth] - t32);
    real_type t35  = X__[iX_alpha];
    real_type t36  = Q__[iQ_Kappa];
    real_type t37  = zeta__dot(t13, t35, t32, t36);
    real_type t38  = t37 * t37;
    real_type t39  = L__[iL_lambda2__xo];
    real_type t44  = sin(t35);
    real_type t53  = U__[iU_v__Omega];
    real_type t58  = U__[iU_v__fx];
    real_type t65  = LimitMinSpeed(t13);
    real_type t66  = v__fxControl(t58, -1, 1);
    real_type t67  = v__OmegaControl(t53, -1, 1);
    real_type t70  = RoadRightBorder(Q__[iQ_rightWidth] + t32);
    real_type result__ = 1.0 / t37 * (t22 + t30 + t34 - t36 * t39 * t38 + t37 * (t44 * t13 * L__[iL_lambda1__xo] + t39 * t11 + (-t14 * ModelPars[iM_kD] + t1) * L__[iL_lambda3__xo] + ModelPars[iM_v__Omega__max] * t53 * L__[iL_lambda5__xo] + ModelPars[iM_v__fx__max] * t58 * L__[iL_lambda4__xo]) + ModelPars[iM_wT] + t65 + t66 + t67 + t70);
    return result__;
  }
#else
  real_type
  PointMassCarModel_2::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_fx];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t11  = X__[iX_Omega];
    real_type t12  = t11 * t11;
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = AdherenceEllipse(1 - t9 / t4 * t2 - t9 / t17 * t14 * t12);
    real_type t30  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13);
    real_type t32  = X__[iX_n];
    real_type t34  = RoadLeftBorder(Q__[iQ_leftWidth] - t32);
    real_type t35  = X__[iX_alpha];
    real_type t36  = Q__[iQ_Kappa];
    real_type t37  = zeta__dot(t13, t35, t32, t36);
    real_type t38  = t37 * t37;
    real_type t39  = L__[iL_lambda2__xo];
    real_type t44  = sin(t35);
    real_type t53  = U__[iU_v__Omega];
    real_type t58  = U__[iU_v__fx];
    real_type t65  = LimitMinSpeed(t13);
    real_type t66  = v__fxControl(t58, -1, 1);
    real_type t67  = v__OmegaControl(t53, -1, 1);
    real_type t70  = RoadRightBorder(Q__[iQ_rightWidth] + t32);
    real_type result__ = 1.0 / t37 * (t22 + t30 + t34 - t36 * t39 * t38 + t37 * (t44 * t13 * L__[iL_lambda1__xo] + t39 * t11 + (-t14 * ModelPars[iM_kD] + t1) * L__[iL_lambda3__xo] + ModelPars[iM_v__Omega__max] * t53 * L__[iL_lambda5__xo] + ModelPars[iM_v__fx__max] * t58 * L__[iL_lambda4__xo]) + ModelPars[iM_wT] + t65 + t66 + t67 + t70);
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
  PointMassCarModel_2::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_fx];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t12  = X__[iX_Omega] * X__[iX_Omega];
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = AdherenceEllipse(1 - t9 / t4 * t2 - t9 / t17 * t14 * t12);
    real_type t24  = X__[iX_n];
    real_type t26  = RoadLeftBorder(Q__[iQ_leftWidth] - t24);
    real_type t29  = RoadRightBorder(Q__[iQ_rightWidth] + t24);
    real_type t37  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13);
    real_type t38  = LimitMinSpeed(t13);
    real_type t42  = zeta__dot(t13, X__[iX_alpha], t24, Q__[iQ_Kappa]);
    real_type result__ = 1.0 / t42 * (t22 + t26 + t29 + t37 + t38);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  PointMassCarModel_2::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t4   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t10  = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type result__ = 1.0 / t10 * (t2 + t4);
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
  PointMassCarModel_2::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t6   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type result__ = 1.0 / t6 * ModelPars[iM_wT];
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
  PointMassCarModel_2::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DmayerDx_numEqns() const
  { return 10; }

  void
  PointMassCarModel_2::DmayerDx_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDx_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DmayerDp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_2::DmayerDp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
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
  PointMassCarModel_2::DJDx_numEqns() const
  { return 5; }

  void
  PointMassCarModel_2::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_fx];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t5   = 1.0 / t4;
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t11  = X__[iX_Omega];
    real_type t12  = t11 * t11;
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t18  = 1.0 / t17;
    real_type t19  = t9 * t18;
    real_type t21  = -t19 * t14 * t12 - t9 * t5 * t2 + 1;
    real_type t22  = AdherenceEllipse(t21);
    real_type t23  = X__[iX_alpha];
    real_type t24  = X__[iX_n];
    real_type t25  = Q__[iQ_Kappa];
    real_type t26  = zeta__dot_D_3(t13, t23, t24, t25);
    real_type t29  = ModelPars[iM_m];
    real_type t30  = ModelPars[iM_Pmax];
    real_type t31  = 1.0 / t30;
    real_type t34  = -t31 * t29 * t1 * t13 + 1;
    real_type t35  = PowerLimit(t34);
    real_type t38  = Q__[iQ_leftWidth] - t24;
    real_type t39  = ALIAS_RoadLeftBorder_D(t38);
    real_type t40  = zeta__dot(t13, t23, t24, t25);
    real_type t42  = RoadLeftBorder(t38);
    real_type t44  = LimitMinSpeed(t13);
    real_type t46  = v__fxControl(U__[iU_v__fx], -1, 1);
    real_type t48  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    real_type t50  = Q__[iQ_rightWidth] + t24;
    real_type t51  = RoadRightBorder(t50);
    real_type t52  = -t44 - t46 - t48 - t51;
    real_type t54  = ALIAS_RoadRightBorder_D(t50);
    real_type t57  = t40 * t40;
    real_type t58  = 1.0 / t57;
    result__[ 0   ] = t58 * (-t26 * t22 - t26 * t35 - t26 * t42 + t26 * t52 - t40 * t39 + t40 * t54);
    real_type t59  = zeta__dot_D_2(t13, t23, t24, t25);
    result__[ 1   ] = -t58 * (t22 + t42 + t51 + t35 + t44 + t46 + t48) * t59;
    real_type t63  = ALIAS_AdherenceEllipse_D(t21);
    real_type t70  = zeta__dot_D_1(t13, t23, t24, t25);
    real_type t74  = ALIAS_PowerLimit_D(t34);
    real_type t81  = ALIAS_LimitMinSpeed_D(t13);
    result__[ 2   ] = t31 * t19 * t58 * (-2 * t30 * t40 * t13 * t12 * t63 - (t22 * t70 * t30 + t74 * t40 * t29 * t1 + t30 * (t35 * t70 - t40 * t81 + t42 * t70 - t70 * t52)) * t8 * t17);
    real_type t90  = 1.0 / t40;
    result__[ 3   ] = -2 * t9 * t18 * t14 * t11 * t63 * t90;
    result__[ 4   ] = t31 * t9 * t5 * t90 * (-t8 * t4 * t29 * t13 * t74 - 2 * t30 * t1 * t63);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DJDp_numEqns() const
  { return 0; }

  void
  PointMassCarModel_2::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DJDu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t8 * t6;
    real_type t10  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t10 * t6;
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
  PointMassCarModel_2::q_numEqns() const
  { return 11; }

  void
  PointMassCarModel_2::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  PointMassCarModel_2::segmentLink_numEqns() const
  { return 0; }

  void
  PointMassCarModel_2::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_ptr             segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  PointMassCarModel_2::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DsegmentLinkDxp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_ptr             DsegmentLinkDxp
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
  PointMassCarModel_2::jump_numEqns() const
  { return 10; }

  void
  PointMassCarModel_2::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    real_const_ptr    LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    real_const_ptr    LR__  = RIGHT__.lambda;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    real_type t1   = XR__[iX_n];
    real_type t2   = XL__[iX_n];
    result__[ 0   ] = t1 - t2;
    real_type t3   = XR__[iX_alpha];
    real_type t4   = XL__[iX_alpha];
    result__[ 1   ] = t3 - t4;
    real_type t5   = XR__[iX_V];
    real_type t6   = XL__[iX_V];
    result__[ 2   ] = t5 - t6;
    result__[ 3   ] = XR__[iX_Omega] - XL__[iX_Omega];
    result__[ 4   ] = XR__[iX_fx] - XL__[iX_fx];
    real_type t12  = ALIAS_Kappa_R(QR__[iQ_zeta]);
    real_type t13  = zeta__dot(t5, t3, t1, t12);
    real_type t17  = ALIAS_Kappa_L(QL__[iQ_zeta]);
    real_type t18  = zeta__dot(t6, t4, t2, t17);
    result__[ 5   ] = LR__[iL_lambda1__xo] * t13 - LL__[iL_lambda1__xo] * t18;
    result__[ 6   ] = LR__[iL_lambda2__xo] * t13 - LL__[iL_lambda2__xo] * t18;
    result__[ 7   ] = LR__[iL_lambda3__xo] * t13 - LL__[iL_lambda3__xo] * t18;
    result__[ 8   ] = LR__[iL_lambda5__xo] * t13 - LL__[iL_lambda5__xo] * t18;
    result__[ 9   ] = LR__[iL_lambda4__xo] * t13 - LL__[iL_lambda4__xo] * t18;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DjumpDxlxlp_numRows() const
  { return 10; }

  integer
  PointMassCarModel_2::DjumpDxlxlp_numCols() const
  { return 20; }

  integer
  PointMassCarModel_2::DjumpDxlxlp_nnz() const
  { return 50; }

  void
  PointMassCarModel_2::DjumpDxlxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 10  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 11  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 12  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 13  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 14  ;
    iIndex[10] = 5   ; jIndex[10] = 0   ;
    iIndex[11] = 5   ; jIndex[11] = 1   ;
    iIndex[12] = 5   ; jIndex[12] = 2   ;
    iIndex[13] = 5   ; jIndex[13] = 5   ;
    iIndex[14] = 5   ; jIndex[14] = 10  ;
    iIndex[15] = 5   ; jIndex[15] = 11  ;
    iIndex[16] = 5   ; jIndex[16] = 12  ;
    iIndex[17] = 5   ; jIndex[17] = 15  ;
    iIndex[18] = 6   ; jIndex[18] = 0   ;
    iIndex[19] = 6   ; jIndex[19] = 1   ;
    iIndex[20] = 6   ; jIndex[20] = 2   ;
    iIndex[21] = 6   ; jIndex[21] = 6   ;
    iIndex[22] = 6   ; jIndex[22] = 10  ;
    iIndex[23] = 6   ; jIndex[23] = 11  ;
    iIndex[24] = 6   ; jIndex[24] = 12  ;
    iIndex[25] = 6   ; jIndex[25] = 16  ;
    iIndex[26] = 7   ; jIndex[26] = 0   ;
    iIndex[27] = 7   ; jIndex[27] = 1   ;
    iIndex[28] = 7   ; jIndex[28] = 2   ;
    iIndex[29] = 7   ; jIndex[29] = 7   ;
    iIndex[30] = 7   ; jIndex[30] = 10  ;
    iIndex[31] = 7   ; jIndex[31] = 11  ;
    iIndex[32] = 7   ; jIndex[32] = 12  ;
    iIndex[33] = 7   ; jIndex[33] = 17  ;
    iIndex[34] = 8   ; jIndex[34] = 0   ;
    iIndex[35] = 8   ; jIndex[35] = 1   ;
    iIndex[36] = 8   ; jIndex[36] = 2   ;
    iIndex[37] = 8   ; jIndex[37] = 9   ;
    iIndex[38] = 8   ; jIndex[38] = 10  ;
    iIndex[39] = 8   ; jIndex[39] = 11  ;
    iIndex[40] = 8   ; jIndex[40] = 12  ;
    iIndex[41] = 8   ; jIndex[41] = 19  ;
    iIndex[42] = 9   ; jIndex[42] = 0   ;
    iIndex[43] = 9   ; jIndex[43] = 1   ;
    iIndex[44] = 9   ; jIndex[44] = 2   ;
    iIndex[45] = 9   ; jIndex[45] = 8   ;
    iIndex[46] = 9   ; jIndex[46] = 10  ;
    iIndex[47] = 9   ; jIndex[47] = 11  ;
    iIndex[48] = 9   ; jIndex[48] = 12  ;
    iIndex[49] = 9   ; jIndex[49] = 18  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    real_const_ptr    LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    real_const_ptr    LR__  = RIGHT__.lambda;
    Road2D::SegmentClass const & segmentLeft  = pRoad->get_segment_by_index(i_segment_left);
    Road2D::SegmentClass const & segmentRight = pRoad->get_segment_by_index(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    real_type t1   = XL__[iX_V];
    real_type t2   = XL__[iX_alpha];
    real_type t3   = XL__[iX_n];
    real_type t5   = ALIAS_Kappa_L(QL__[iQ_zeta]);
    real_type t6   = zeta__dot_D_3(t1, t2, t3, t5);
    real_type t7   = LL__[iL_lambda1__xo];
    result__[ 10  ] = -t7 * t6;
    real_type t9   = zeta__dot_D_2(t1, t2, t3, t5);
    result__[ 11  ] = -t9 * t7;
    real_type t11  = zeta__dot_D_1(t1, t2, t3, t5);
    result__[ 12  ] = -t7 * t11;
    real_type t13  = zeta__dot(t1, t2, t3, t5);
    result__[ 13  ] = -t13;
    real_type t14  = XR__[iX_V];
    real_type t15  = XR__[iX_alpha];
    real_type t16  = XR__[iX_n];
    real_type t18  = ALIAS_Kappa_R(QR__[iQ_zeta]);
    real_type t19  = zeta__dot_D_3(t14, t15, t16, t18);
    real_type t20  = LR__[iL_lambda1__xo];
    result__[ 14  ] = t20 * t19;
    real_type t21  = zeta__dot_D_2(t14, t15, t16, t18);
    result__[ 15  ] = t20 * t21;
    real_type t22  = zeta__dot_D_1(t14, t15, t16, t18);
    result__[ 16  ] = t20 * t22;
    result__[ 17  ] = zeta__dot(t14, t15, t16, t18);
    real_type t23  = LL__[iL_lambda2__xo];
    result__[ 18  ] = -t23 * t6;
    result__[ 19  ] = -t23 * t9;
    result__[ 20  ] = -t23 * t11;
    result__[ 21  ] = result__[13];
    real_type t27  = LR__[iL_lambda2__xo];
    result__[ 22  ] = t27 * t19;
    result__[ 23  ] = t27 * t21;
    result__[ 24  ] = t27 * t22;
    result__[ 25  ] = result__[17];
    real_type t28  = LL__[iL_lambda3__xo];
    result__[ 26  ] = -t28 * t6;
    result__[ 27  ] = -t28 * t9;
    result__[ 28  ] = -t28 * t11;
    result__[ 29  ] = result__[21];
    real_type t32  = LR__[iL_lambda3__xo];
    result__[ 30  ] = t32 * t19;
    result__[ 31  ] = t32 * t21;
    result__[ 32  ] = t32 * t22;
    result__[ 33  ] = result__[25];
    real_type t33  = LL__[iL_lambda5__xo];
    result__[ 34  ] = -t33 * t6;
    result__[ 35  ] = -t33 * t9;
    result__[ 36  ] = -t33 * t11;
    result__[ 37  ] = result__[29];
    real_type t37  = LR__[iL_lambda5__xo];
    result__[ 38  ] = t37 * t19;
    result__[ 39  ] = t37 * t21;
    result__[ 40  ] = t37 * t22;
    result__[ 41  ] = result__[33];
    real_type t38  = LL__[iL_lambda4__xo];
    result__[ 42  ] = -t38 * t6;
    result__[ 43  ] = -t38 * t9;
    result__[ 44  ] = -t38 * t11;
    result__[ 45  ] = result__[37];
    real_type t42  = LR__[iL_lambda4__xo];
    result__[ 46  ] = t42 * t19;
    result__[ 47  ] = t42 * t21;
    result__[ 48  ] = t42 * t22;
    result__[ 49  ] = result__[41];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 50, i_segment_left, i_segment_right );
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
    real_type t25  = X__[iX_n];
    result__[ 3   ] = RoadLeftBorder(Q__[iQ_leftWidth] - t25);
    result__[ 4   ] = RoadRightBorder(Q__[iQ_rightWidth] + t25);
    result__[ 5   ] = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15);
    result__[ 6   ] = LimitMinSpeed(t15);
    real_type t36  = Q__[iQ_zeta];
    result__[ 7   ] = ALIAS_xV(t36, t25);
    result__[ 8   ] = ALIAS_yV(t36, t25);
    result__[ 9   ] = t15 * t13;
    real_type t39  = 1.0 / t9;
    result__[ 10  ] = t39 / t5 * t3;
    result__[ 11  ] = t39 / t18 * result__[9];
    real_type t44  = zeta__dot(t15, X__[iX_alpha], t25, Q__[iQ_Kappa]);
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    result__[ 0   ] = 1.0 / t5;
    Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_problem.cc
