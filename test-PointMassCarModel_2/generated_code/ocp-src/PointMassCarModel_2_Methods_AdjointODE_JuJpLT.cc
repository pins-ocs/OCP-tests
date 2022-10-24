/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
#pragma warning( disable : 4189 )
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JP_numEqns() const { return 0; }

  void
  PointMassCarModel_2::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::LT_numEqns() const { return 5; }

  void
  PointMassCarModel_2::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t3   = X__[iX_n];
    real_type t5   = zeta__dot(t1, X__[iX_alpha], t3, Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t7   = X__[iX_fx];
    real_type t8   = t7 * t7;
    real_type t10  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t14  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t15  = 1.0 / t14;
    real_type t18  = X__[iX_Omega] * X__[iX_Omega];
    real_type t19  = t1 * t1;
    real_type t22  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t27  = AdherenceEllipse(t15 / t10 * t8 + t15 / t22 * t19 * t18 - 1);
    result__[ 0   ] = t27 * t6;
    real_type t30  = RoadLeftBorder(t3 - Q__[iQ_leftWidth]);
    result__[ 1   ] = t30 * t6;
    real_type t33  = RoadRightBorder(-t3 - Q__[iQ_rightWidth]);
    result__[ 2   ] = t33 * t6;
    real_type t41  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t7 * t1 - 1);
    result__[ 3   ] = t41 * t6;
    real_type t42  = LimitMinSpeed(-t1);
    result__[ 4   ] = t42 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::JU_numEqns() const { return 2; }

  void
  PointMassCarModel_2::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = v__fxControl(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t8 * t6;
    real_type t10  = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t10 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_2::LTargs_numEqns() const { return 5; }

  void
  PointMassCarModel_2::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
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
    result__[ 0   ] = t9 / t4 * t2 + t9 / t17 * t14 * t12 - 1;
    real_type t21  = X__[iX_n];
    result__[ 1   ] = t21 - Q__[iQ_leftWidth];
    result__[ 2   ] = -t21 - Q__[iQ_rightWidth];
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13 - 1;
    result__[ 4   ] = -t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJPDxpu_numRows() const { return 0; }
  integer PointMassCarModel_2::DJPDxpu_numCols() const { return 7; }
  integer PointMassCarModel_2::DJPDxpu_nnz()     const { return 0; }

  void
  PointMassCarModel_2::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTDxpu_numRows() const { return 5; }
  integer PointMassCarModel_2::DLTDxpu_numCols() const { return 7; }
  integer PointMassCarModel_2::DLTDxpu_nnz()     const { return 18; }

  void
  PointMassCarModel_2::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 3   ; jIndex[11] = 0   ;
    iIndex[12] = 3   ; jIndex[12] = 1   ;
    iIndex[13] = 3   ; jIndex[13] = 2   ;
    iIndex[14] = 3   ; jIndex[14] = 4   ;
    iIndex[15] = 4   ; jIndex[15] = 0   ;
    iIndex[16] = 4   ; jIndex[16] = 1   ;
    iIndex[17] = 4   ; jIndex[17] = 2   ;
  }


  void
  PointMassCarModel_2::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
    real_type t27  = t16 * t24 * t20 * t19 + t16 * t12 * t9 - 1;
    real_type t28  = AdherenceEllipse(t27);
    real_type t29  = t28 * t7;
    real_type t30  = zeta__dot_D_3(t1, t2, t3, t4);
    result__[ 0   ] = -t30 * t29;
    real_type t32  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t32 * t29;
    real_type t34  = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t36  = 1.0 / t5;
    real_type t37  = ALIAS_AdherenceEllipse_D(t27);
    real_type t38  = t37 * t36;
    result__[ 2   ] = 2 * t16 * t24 * t1 * t19 * t38 - t34 * t29;
    result__[ 3   ] = 2 * t16 * t24 * t20 * t18 * t38;
    result__[ 4   ] = 2 * t16 * t12 * t8 * t38;
    real_type t52  = t3 - Q__[iQ_leftWidth];
    real_type t53  = RoadLeftBorder(t52);
    real_type t54  = t53 * t7;
    real_type t56  = ALIAS_RoadLeftBorder_D(t52);
    result__[ 5   ] = -t30 * t54 + t56 * t36;
    result__[ 6   ] = -t32 * t54;
    result__[ 7   ] = -t34 * t54;
    real_type t61  = -t3 - Q__[iQ_rightWidth];
    real_type t62  = RoadRightBorder(t61);
    real_type t63  = t62 * t7;
    real_type t65  = ALIAS_RoadRightBorder_D(t61);
    result__[ 8   ] = -t30 * t63 - t65 * t36;
    result__[ 9   ] = -t32 * t63;
    result__[ 10  ] = -t34 * t63;
    real_type t70  = ModelPars[iM_m];
    real_type t72  = 1.0 / ModelPars[iM_Pmax];
    real_type t75  = t72 * t70 * t8 * t1 - 1;
    real_type t76  = PowerLimit(t75);
    real_type t77  = t76 * t7;
    result__[ 11  ] = -t30 * t77;
    result__[ 12  ] = -t32 * t77;
    real_type t81  = ALIAS_PowerLimit_D(t75);
    real_type t82  = t81 * t36;
    result__[ 13  ] = t72 * t70 * t8 * t82 - t34 * t77;
    result__[ 14  ] = t72 * t70 * t1 * t82;
    real_type t88  = LimitMinSpeed(-t1);
    real_type t89  = t88 * t7;
    result__[ 15  ] = -t30 * t89;
    result__[ 16  ] = -t32 * t89;
    real_type t93  = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 17  ] = -t34 * t89 - t93 * t36;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 18, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DJUDxpu_numRows() const { return 2; }
  integer PointMassCarModel_2::DJUDxpu_numCols() const { return 7; }
  integer PointMassCarModel_2::DJUDxpu_nnz()     const { return 8; }

  void
  PointMassCarModel_2::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 6   ;
  }


  void
  PointMassCarModel_2::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t8   = U__[iU_v__fx];
    real_type t9   = v__fxControl(t8, -1, 1);
    real_type t10  = t9 * t7;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    result__[ 0   ] = -t11 * t10;
    real_type t13  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t13 * t10;
    real_type t15  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t15 * t10;
    real_type t17  = 1.0 / t5;
    real_type t18  = ALIAS_v__fxControl_D_1(t8, -1, 1);
    result__[ 3   ] = t18 * t17;
    real_type t19  = U__[iU_v__Omega];
    real_type t20  = v__OmegaControl(t19, -1, 1);
    real_type t21  = t20 * t7;
    result__[ 4   ] = -t11 * t21;
    result__[ 5   ] = -t13 * t21;
    result__[ 6   ] = -t15 * t21;
    real_type t25  = ALIAS_v__OmegaControl_D_1(t19, -1, 1);
    result__[ 7   ] = t17 * t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::DLTargsDxpu_numRows() const { return 5; }
  integer PointMassCarModel_2::DLTargsDxpu_numCols() const { return 7; }
  integer PointMassCarModel_2::DLTargsDxpu_nnz()     const { return 8; }

  void
  PointMassCarModel_2::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 2   ;
  }


  void
  PointMassCarModel_2::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_Omega];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_V];
    real_type t6   = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t9   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t10  = 1.0 / t9;
    real_type t11  = t10 / t6;
    result__[ 0   ] = 2 * t11 * t3 * t2;
    real_type t13  = t3 * t3;
    result__[ 1   ] = 2 * t11 * t13 * t1;
    real_type t16  = X__[iX_fx];
    real_type t18  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    result__[ 2   ] = 2 * t10 / t18 * t16;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    real_type t22  = ModelPars[iM_m];
    real_type t25  = 1.0 / ModelPars[iM_Pmax];
    result__[ 5   ] = t25 * t22 * t16;
    result__[ 6   ] = t25 * t22 * t3;
    result__[ 7   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 8, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2JPD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2JPD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2JPD2xpu_nnz()     const { return 0; }

  void
  PointMassCarModel_2::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_2::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2LTD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2LTD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2LTD2xpu_nnz()     const { return 25; }

  void
  PointMassCarModel_2::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_2::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
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
    real_type t26  = t17 * t25;
    real_type t28  = t10 * t13 * t17 + t20 * t21 * t26 - 1;
    real_type t29  = AdherenceEllipse(t28);
    real_type t30  = t29 * t8;
    real_type t31  = OMEGA__[0];
    real_type t32  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t33  = t32 * t32;
    real_type t37  = 1.0 / t6;
    real_type t38  = t29 * t37;
    real_type t39  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t43  = t3 - Q__[iQ_leftWidth];
    real_type t44  = RoadLeftBorder(t43);
    real_type t45  = t44 * t8;
    real_type t46  = OMEGA__[1];
    real_type t50  = ALIAS_RoadLeftBorder_D(t43);
    real_type t51  = t50 * t37;
    real_type t52  = t32 * t46;
    real_type t55  = t44 * t37;
    real_type t58  = 1.0 / t5;
    real_type t59  = ALIAS_RoadLeftBorder_DD(t43);
    real_type t63  = -t3 - Q__[iQ_rightWidth];
    real_type t64  = RoadRightBorder(t63);
    real_type t65  = t64 * t8;
    real_type t66  = OMEGA__[2];
    real_type t70  = ALIAS_RoadRightBorder_D(t63);
    real_type t71  = t70 * t37;
    real_type t72  = t32 * t66;
    real_type t75  = t64 * t37;
    real_type t78  = ALIAS_RoadRightBorder_DD(t63);
    real_type t82  = ModelPars[iM_m];
    real_type t83  = ModelPars[iM_Pmax];
    real_type t85  = 1.0 / t83 * t82;
    real_type t87  = t1 * t85 * t9 - 1;
    real_type t88  = PowerLimit(t87);
    real_type t89  = t88 * t8;
    real_type t90  = OMEGA__[3];
    real_type t94  = t88 * t37;
    real_type t97  = LimitMinSpeed(-t1);
    real_type t98  = t97 * t8;
    real_type t99  = OMEGA__[4];
    real_type t103 = t97 * t37;
    result__[ 0   ] = -t103 * t39 * t99 + 2 * t30 * t31 * t33 - t31 * t38 * t39 + 2 * t33 * t45 * t46 + 2 * t33 * t65 * t66 + 2 * t33 * t89 * t90 + 2 * t33 * t98 * t99 - t39 * t46 * t55 - t39 * t66 * t75 - t39 * t90 * t94 + t46 * t58 * t59 + t58 * t66 * t78 - 2 * t51 * t52 + 2 * t71 * t72;
    real_type t106 = t32 * t31;
    real_type t107 = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t111 = zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t119 = t107 * t46;
    real_type t126 = t107 * t66;
    real_type t128 = t32 * t90;
    real_type t134 = t32 * t99;
    result__[ 1   ] = -t103 * t111 * t99 + 2 * t106 * t107 * t30 + 2 * t107 * t128 * t89 + 2 * t107 * t134 * t98 + 2 * t107 * t45 * t52 + 2 * t107 * t65 * t72 - t111 * t31 * t38 - t111 * t46 * t55 - t111 * t66 * t75 - t111 * t90 * t94 - t119 * t51 + t126 * t71;
    real_type t140 = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t144 = ALIAS_AdherenceEllipse_D(t28);
    real_type t145 = t144 * t37;
    real_type t147 = t1 * t20 * t145;
    real_type t148 = t106 * t26;
    real_type t151 = zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t171 = ALIAS_PowerLimit_D(t87);
    real_type t172 = t171 * t37;
    real_type t173 = t9 * t172;
    real_type t174 = t128 * t85;
    real_type t181 = ALIAS_LimitMinSpeed_D(-t1);
    real_type t182 = t181 * t37;
    result__[ 2   ] = -t103 * t151 * t99 + 2 * t106 * t140 * t30 + 2 * t128 * t140 * t89 + 2 * t134 * t140 * t98 + 2 * t140 * t45 * t52 - t140 * t46 * t51 + 2 * t140 * t65 * t72 + t140 * t66 * t71 - t151 * t31 * t38 - t151 * t46 * t55 - t151 * t66 * t75 - t151 * t90 * t94 + t134 * t182 - 2 * t147 * t148 - t173 * t174;
    real_type t187 = t21 * t19 * t145;
    result__[ 3   ] = -2 * t148 * t187;
    real_type t190 = t9 * t145;
    real_type t191 = t17 * t13;
    real_type t195 = t1 * t172;
    result__[ 4   ] = -2 * t106 * t190 * t191 - t174 * t195;
    result__[ 5   ] = result__[1];
    real_type t197 = t107 * t107;
    real_type t201 = zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = -t103 * t201 * t99 + 2 * t197 * t30 * t31 + 2 * t197 * t45 * t46 + 2 * t197 * t65 * t66 + 2 * t197 * t89 * t90 + 2 * t197 * t98 * t99 - t201 * t31 * t38 - t201 * t46 * t55 - t201 * t66 * t75 - t201 * t90 * t94;
    real_type t224 = t107 * t31;
    real_type t228 = t224 * t26;
    real_type t231 = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t244 = t107 * t90;
    real_type t248 = t244 * t85;
    real_type t252 = t107 * t99;
    result__[ 7   ] = -t103 * t231 * t99 + 2 * t119 * t140 * t45 + 2 * t126 * t140 * t65 + 2 * t140 * t224 * t30 + 2 * t140 * t244 * t89 + 2 * t140 * t252 * t98 - t231 * t31 * t38 - t231 * t46 * t55 - t231 * t66 * t75 - t231 * t90 * t94 - 2 * t147 * t228 - t173 * t248 + t182 * t252;
    result__[ 8   ] = -2 * t228 * t187;
    result__[ 9   ] = -2 * t190 * t191 * t224 - t195 * t248;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t265 = t140 * t140;
    real_type t269 = t140 * t31;
    real_type t270 = t269 * t26;
    real_type t273 = zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t276 = ALIAS_AdherenceEllipse_DD(t28);
    real_type t277 = t276 * t58;
    real_type t278 = t20 * t20;
    real_type t280 = t24 * t24;
    real_type t281 = 1.0 / t280;
    real_type t283 = t16 * t16;
    real_type t284 = 1.0 / t283;
    real_type t285 = t31 * t284;
    real_type t289 = t144 * t58;
    real_type t291 = t31 * t26;
    real_type t308 = t140 * t90 * t85;
    real_type t313 = ALIAS_PowerLimit_DD(t87);
    real_type t314 = t313 * t58;
    real_type t316 = t82 * t82;
    real_type t317 = t83 * t83;
    real_type t319 = 1.0 / t317 * t316;
    real_type t320 = t90 * t319;
    real_type t330 = ALIAS_LimitMinSpeed_DD(-t1);
    result__[ 12  ] = 2 * t265 * t31 * t30 - 4 * t270 * t147 - t273 * t31 * t38 + 4 * t285 * t281 * t21 * t278 * t277 + 2 * t291 * t20 * t289 + 2 * t265 * t46 * t45 - t273 * t46 * t55 + 2 * t265 * t66 * t65 - t273 * t66 * t75 + 2 * t265 * t90 * t89 - 2 * t308 * t173 - t273 * t90 * t94 + t320 * t10 * t314 + 2 * t265 * t99 * t98 + 2 * t140 * t99 * t182 - t273 * t99 * t103 + t99 * t330 * t58;
    real_type t343 = t25 * t1;
    result__[ 13  ] = 4 * t1 * t19 * t20 * t21 * t277 * t281 * t285 + 4 * t17 * t19 * t289 * t31 * t343 - 2 * t187 * t270;
    real_type t352 = t13 * t9 * t277;
    result__[ 14  ] = t1 * t314 * t319 * t9 * t90 + 4 * t20 * t284 * t31 * t343 * t352 + t171 * t58 * t85 * t90 - 2 * t190 * t191 * t269 - t195 * t308;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t367 = t21 * t21;
    result__[ 18  ] = 4 * t20 * t277 * t281 * t285 * t367 + 2 * t21 * t289 * t291;
    result__[ 19  ] = 4 * t31 * t25 * t21 * t19 * t284 * t352;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t381 = t12 * t12;
    result__[ 24  ] = 4 * t31 * t284 / t381 * t10 * t277 + 2 * t31 * t191 * t289 + t320 * t21 * t314;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 25, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2JUD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2JUD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2JUD2xpu_nnz()     const { return 23; }

  void
  PointMassCarModel_2::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 5   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 5   ; jIndex[15] = 0   ;
    iIndex[16] = 5   ; jIndex[16] = 1   ;
    iIndex[17] = 5   ; jIndex[17] = 2   ;
    iIndex[18] = 5   ; jIndex[18] = 5   ;
    iIndex[19] = 6   ; jIndex[19] = 0   ;
    iIndex[20] = 6   ; jIndex[20] = 1   ;
    iIndex[21] = 6   ; jIndex[21] = 2   ;
    iIndex[22] = 6   ; jIndex[22] = 6   ;
  }


  void
  PointMassCarModel_2::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t8   = 1.0 / t6 / t5;
    real_type t9   = U__[iU_v__fx];
    real_type t10  = v__fxControl(t9, -1, 1);
    real_type t11  = t10 * t8;
    real_type t12  = OMEGA__[0];
    real_type t13  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t14  = t13 * t13;
    real_type t18  = 1.0 / t6;
    real_type t19  = t10 * t18;
    real_type t20  = zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t23  = U__[iU_v__Omega];
    real_type t24  = v__OmegaControl(t23, -1, 1);
    real_type t25  = t24 * t8;
    real_type t26  = OMEGA__[1];
    real_type t30  = t24 * t18;
    result__[ 0   ] = 2 * t14 * t12 * t11 - t20 * t12 * t19 + 2 * t14 * t26 * t25 - t20 * t26 * t30;
    real_type t33  = t13 * t12;
    real_type t34  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type t38  = zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t41  = t13 * t26;
    result__[ 1   ] = 2 * t34 * t33 * t11 - t38 * t12 * t19 + 2 * t34 * t41 * t25 - t38 * t26 * t30;
    real_type t47  = zeta__dot_D_1(t1, t2, t3, t4);
    real_type t51  = zeta__dot_D_1_3(t1, t2, t3, t4);
    result__[ 2   ] = 2 * t47 * t33 * t11 - t51 * t12 * t19 + 2 * t47 * t41 * t25 - t51 * t26 * t30;
    real_type t59  = ALIAS_v__fxControl_D_1(t9, -1, 1);
    real_type t60  = t59 * t18;
    result__[ 3   ] = -t33 * t60;
    real_type t62  = ALIAS_v__OmegaControl_D_1(t23, -1, 1);
    real_type t63  = t62 * t18;
    result__[ 4   ] = -t41 * t63;
    result__[ 5   ] = result__[1];
    real_type t65  = t34 * t34;
    real_type t69  = zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = 2 * t65 * t12 * t11 - t69 * t12 * t19 + 2 * t65 * t26 * t25 - t69 * t26 * t30;
    real_type t77  = t34 * t12;
    real_type t81  = zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t84  = t34 * t26;
    result__[ 7   ] = 2 * t47 * t77 * t11 - t81 * t12 * t19 + 2 * t47 * t84 * t25 - t81 * t26 * t30;
    result__[ 8   ] = -t77 * t60;
    result__[ 9   ] = -t84 * t63;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t92  = t47 * t47;
    real_type t96  = zeta__dot_D_1_1(t1, t2, t3, t4);
    result__[ 12  ] = 2 * t92 * t12 * t11 - t96 * t12 * t19 + 2 * t92 * t26 * t25 - t96 * t26 * t30;
    result__[ 13  ] = -t47 * t12 * t60;
    result__[ 14  ] = -t47 * t26 * t63;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t108 = 1.0 / t5;
    real_type t109 = ALIAS_v__fxControl_D_1_1(t9, -1, 1);
    result__[ 18  ] = t12 * t109 * t108;
    result__[ 19  ] = result__[4];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[14];
    real_type t111 = ALIAS_v__OmegaControl_D_1_1(t23, -1, 1);
    result__[ 22  ] = t26 * t111 * t108;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 23, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_2::D2LTargsD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_2::D2LTargsD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_2::D2LTargsD2xpu_nnz()     const { return 7; }

  void
  PointMassCarModel_2::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 4   ;
  }


  void
  PointMassCarModel_2::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_Omega];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t5   = 1.0 / t4;
    real_type t8   = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t9   = 1.0 / t8;
    real_type t10  = OMEGA__[0];
    real_type t11  = t10 * t9;
    result__[ 0   ] = 2 * t11 * t5 * t2;
    real_type t13  = X__[iX_V];
    result__[ 1   ] = 4 * t10 * t9 * t5 * t13 * t1;
    result__[ 2   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * OMEGA__[3];
    result__[ 3   ] = result__[1];
    real_type t23  = t13 * t13;
    result__[ 4   ] = 2 * t11 * t5 * t23;
    result__[ 5   ] = result__[2];
    real_type t27  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    result__[ 6   ] = 2 * t10 * t9 / t27;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 7, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_AdjointODE.cc
