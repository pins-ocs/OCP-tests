/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_AdjointODE.cc                      |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


namespace PointMassCarModel_1Define {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JP_numEqns() const { return 0; }

  void
  PointMassCarModel_1::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::LT_numEqns() const { return 5; }

  void
  PointMassCarModel_1::LT_eval(
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
    real_type t5   = inv_zeta__dot(t1, X__[iX_alpha], t3, Q__[iQ_Kappa]);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t17  = X__[iX_Omega] * X__[iX_Omega];
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t26  = AdherenceEllipse(t14 / t9 * t7 + t14 / t21 * t18 * t17 - 1);
    result__[ 0   ] = t26 * t5;
    real_type t29  = RoadLeftBorder(t3 - Q__[iQ_leftWidth]);
    result__[ 1   ] = t29 * t5;
    real_type t32  = RoadRightBorder(-t3 - Q__[iQ_rightWidth]);
    result__[ 2   ] = t32 * t5;
    real_type t40  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t6 * t1 - 1);
    result__[ 3   ] = t40 * t5;
    real_type t41  = LimitMinSpeed(-t1);
    result__[ 4   ] = t41 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::JU_numEqns() const { return 2; }

  void
  PointMassCarModel_1::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = v__fxControl(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t7 * t5;
    real_type t9   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t9 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_1::LTargs_numEqns() const { return 5; }

  void
  PointMassCarModel_1::LTargs_eval(
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
  integer PointMassCarModel_1::DJPDxpu_numRows() const { return 0; }
  integer PointMassCarModel_1::DJPDxpu_numCols() const { return 7; }
  integer PointMassCarModel_1::DJPDxpu_nnz()     const { return 0; }

  void
  PointMassCarModel_1::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DLTDxpu_numRows() const { return 5; }
  integer PointMassCarModel_1::DLTDxpu_numCols() const { return 7; }
  integer PointMassCarModel_1::DLTDxpu_nnz()     const { return 18; }

  void
  PointMassCarModel_1::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::DLTDxpu_sparse(
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
    real_type t25  = t14 * t22 * t18 * t17 + t14 * t10 * t7 - 1;
    real_type t26  = AdherenceEllipse(t25);
    result__[ 0   ] = t26 * t5;
    real_type t27  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t26 * t27;
    real_type t28  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t30  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t31  = ALIAS_AdherenceEllipse_D(t25);
    real_type t32  = t31 * t30;
    result__[ 2   ] = 2 * t14 * t22 * t1 * t17 * t32 + t26 * t28;
    result__[ 3   ] = 2 * t14 * t22 * t18 * t16 * t32;
    result__[ 4   ] = 2 * t14 * t10 * t6 * t32;
    real_type t46  = t3 - Q__[iQ_leftWidth];
    real_type t47  = RoadLeftBorder(t46);
    real_type t49  = ALIAS_RoadLeftBorder_D(t46);
    result__[ 5   ] = t49 * t30 + t47 * t5;
    result__[ 6   ] = t47 * t27;
    result__[ 7   ] = t47 * t28;
    real_type t52  = -t3 - Q__[iQ_rightWidth];
    real_type t53  = RoadRightBorder(t52);
    real_type t55  = ALIAS_RoadRightBorder_D(t52);
    result__[ 8   ] = -t55 * t30 + t53 * t5;
    result__[ 9   ] = t53 * t27;
    result__[ 10  ] = t53 * t28;
    real_type t58  = ModelPars[iM_m];
    real_type t60  = 1.0 / ModelPars[iM_Pmax];
    real_type t63  = t60 * t58 * t6 * t1 - 1;
    real_type t64  = PowerLimit(t63);
    result__[ 11  ] = t64 * t5;
    result__[ 12  ] = t64 * t27;
    real_type t66  = ALIAS_PowerLimit_D(t63);
    real_type t67  = t66 * t30;
    result__[ 13  ] = t60 * t58 * t6 * t67 + t64 * t28;
    result__[ 14  ] = t60 * t58 * t1 * t67;
    real_type t73  = LimitMinSpeed(-t1);
    result__[ 15  ] = t73 * t5;
    result__[ 16  ] = t73 * t27;
    real_type t75  = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 17  ] = t73 * t28 - t75 * t30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 18, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DJUDxpu_numRows() const { return 2; }
  integer PointMassCarModel_1::DJUDxpu_numCols() const { return 7; }
  integer PointMassCarModel_1::DJUDxpu_nnz()     const { return 8; }

  void
  PointMassCarModel_1::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::DJUDxpu_sparse(
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
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t6   = U__[iU_v__fx];
    real_type t7   = v__fxControl(t6, -1, 1);
    result__[ 0   ] = t7 * t5;
    real_type t8   = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t7 * t8;
    real_type t9   = inv_zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t7 * t9;
    real_type t10  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t11  = ALIAS_v__fxControl_D_1(t6, -1, 1);
    result__[ 3   ] = t11 * t10;
    real_type t12  = U__[iU_v__Omega];
    real_type t13  = v__OmegaControl(t12, -1, 1);
    result__[ 4   ] = t13 * t5;
    result__[ 5   ] = t13 * t8;
    result__[ 6   ] = t13 * t9;
    real_type t14  = ALIAS_v__OmegaControl_D_1(t12, -1, 1);
    result__[ 7   ] = t14 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::DLTargsDxpu_numRows() const { return 5; }
  integer PointMassCarModel_1::DLTargsDxpu_numCols() const { return 7; }
  integer PointMassCarModel_1::DLTargsDxpu_nnz()     const { return 8; }

  void
  PointMassCarModel_1::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::DLTargsDxpu_sparse(
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
  integer PointMassCarModel_1::D2JPD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_1::D2JPD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_1::D2JPD2xpu_nnz()     const { return 0; }

  void
  PointMassCarModel_1::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_1::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::D2LTD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_1::D2LTD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_1::D2LTD2xpu_nnz()     const { return 25; }

  void
  PointMassCarModel_1::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::D2LTD2xpu_sparse(
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
    real_type t23  = t14 * t22;
    real_type t25  = t14 * t10 * t7 + t23 * t18 * t17 - 1;
    real_type t26  = AdherenceEllipse(t25);
    real_type t28  = OMEGA__[0];
    real_type t31  = t3 - Q__[iQ_leftWidth];
    real_type t32  = RoadLeftBorder(t31);
    real_type t34  = OMEGA__[1];
    real_type t36  = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t37  = ALIAS_RoadLeftBorder_D(t31);
    real_type t41  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t42  = ALIAS_RoadLeftBorder_DD(t31);
    real_type t46  = -t3 - Q__[iQ_rightWidth];
    real_type t47  = RoadRightBorder(t46);
    real_type t49  = OMEGA__[2];
    real_type t51  = ALIAS_RoadRightBorder_D(t46);
    real_type t55  = ALIAS_RoadRightBorder_DD(t46);
    real_type t59  = ModelPars[iM_m];
    real_type t60  = ModelPars[iM_Pmax];
    real_type t62  = 1.0 / t60 * t59;
    real_type t64  = t1 * t6 * t62 - 1;
    real_type t65  = PowerLimit(t64);
    real_type t67  = OMEGA__[3];
    real_type t69  = LimitMinSpeed(-t1);
    real_type t71  = OMEGA__[4];
    result__[ 0   ] = t26 * t28 * t5 + t32 * t34 * t5 + 2 * t34 * t36 * t37 + t34 * t41 * t42 - 2 * t36 * t49 * t51 + t41 * t49 * t55 + t47 * t49 * t5 + t5 * t65 * t67 + t5 * t69 * t71;
    real_type t73  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    real_type t78  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t26 * t28 * t73 + t32 * t34 * t73 + t34 * t37 * t78 + t47 * t49 * t73 - t49 * t51 * t78 + t65 * t67 * t73 + t69 * t71 * t73;
    real_type t89  = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    real_type t92  = ALIAS_AdherenceEllipse_D(t25);
    real_type t93  = t92 * t36;
    real_type t95  = t22 * t1;
    real_type t96  = t28 * t14;
    real_type t97  = t96 * t95;
    real_type t102 = inv_zeta__dot_D_1(t1, t2, t3, t4);
    real_type t111 = ALIAS_PowerLimit_D(t64);
    real_type t112 = t111 * t36;
    real_type t114 = t67 * t62;
    real_type t118 = ALIAS_LimitMinSpeed_D(-t1);
    result__[ 2   ] = t102 * t34 * t37 - t102 * t49 * t51 + t112 * t114 * t6 - t118 * t36 * t71 + 2 * t17 * t93 * t97 + t26 * t28 * t89 + t32 * t34 * t89 + t47 * t49 * t89 + t65 * t67 * t89 + t69 * t71 * t89;
    real_type t122 = t22 * t18;
    real_type t123 = t96 * t122;
    result__[ 3   ] = 2 * t123 * t16 * t93;
    real_type t127 = t28 * t14 * t10;
    result__[ 4   ] = t1 * t112 * t114 + 2 * t127 * t6 * t93;
    result__[ 5   ] = result__[1];
    real_type t132 = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = t132 * t26 * t28 + t132 * t32 * t34 + t132 * t47 * t49 + t132 * t65 * t67 + t132 * t69 * t71;
    real_type t143 = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    real_type t146 = t92 * t78;
    real_type t156 = t111 * t78;
    result__[ 7   ] = t114 * t156 * t6 - t118 * t71 * t78 + t143 * t26 * t28 + t143 * t32 * t34 + t143 * t47 * t49 + t143 * t65 * t67 + t143 * t69 * t71 + 2 * t146 * t17 * t97;
    result__[ 8   ] = 2 * t123 * t16 * t146;
    result__[ 9   ] = t1 * t114 * t156 + 2 * t127 * t146 * t6;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t170 = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    real_type t173 = t92 * t102;
    real_type t177 = ALIAS_AdherenceEllipse_DD(t25);
    real_type t178 = t177 * t41;
    real_type t179 = t17 * t17;
    real_type t181 = t21 * t21;
    real_type t182 = 1.0 / t181;
    real_type t184 = t13 * t13;
    real_type t185 = 1.0 / t184;
    real_type t186 = t28 * t185;
    real_type t190 = t92 * t41;
    real_type t192 = t28 * t23;
    real_type t201 = t111 * t102;
    real_type t205 = ALIAS_PowerLimit_DD(t64);
    real_type t206 = t205 * t41;
    real_type t208 = t59 * t59;
    real_type t209 = t60 * t60;
    real_type t211 = 1.0 / t209 * t208;
    real_type t212 = t67 * t211;
    real_type t219 = ALIAS_LimitMinSpeed_DD(-t1);
    result__[ 12  ] = t28 * t26 * t170 + 4 * t97 * t17 * t173 + 4 * t186 * t182 * t18 * t179 * t178 + 2 * t192 * t17 * t190 + t34 * t32 * t170 + t49 * t47 * t170 + t67 * t65 * t170 + 2 * t114 * t6 * t201 + t212 * t7 * t206 + t71 * t69 * t170 - 2 * t71 * t118 * t102 + t71 * t219 * t41;
    result__[ 13  ] = 4 * t1 * t16 * t17 * t178 * t18 * t182 * t186 + 2 * t123 * t16 * t173 + 4 * t16 * t190 * t97;
    real_type t239 = t10 * t6 * t178;
    result__[ 14  ] = t1 * t206 * t211 * t6 * t67 + 4 * t17 * t185 * t239 * t28 * t95 + t1 * t114 * t201 + t111 * t114 * t41 + 2 * t127 * t173 * t6;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t254 = t18 * t18;
    result__[ 18  ] = 4 * t17 * t178 * t182 * t186 * t254 + 2 * t18 * t190 * t192;
    result__[ 19  ] = 4 * t28 * t122 * t16 * t185 * t239;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    real_type t267 = t9 * t9;
    result__[ 24  ] = 4 * t28 * t185 / t267 * t7 * t178 + 2 * t127 * t190 + t212 * t18 * t206;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 25, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::D2JUD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_1::D2JUD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_1::D2JUD2xpu_nnz()     const { return 23; }

  void
  PointMassCarModel_1::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  PointMassCarModel_1::D2JUD2xpu_sparse(
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
    real_type t5   = inv_zeta__dot_D_3_3(t1, t2, t3, t4);
    real_type t6   = U__[iU_v__fx];
    real_type t7   = v__fxControl(t6, -1, 1);
    real_type t9   = OMEGA__[0];
    real_type t11  = U__[iU_v__Omega];
    real_type t12  = v__OmegaControl(t11, -1, 1);
    real_type t14  = OMEGA__[1];
    result__[ 0   ] = t14 * t12 * t5 + t9 * t7 * t5;
    real_type t16  = inv_zeta__dot_D_2_3(t1, t2, t3, t4);
    result__[ 1   ] = t14 * t12 * t16 + t9 * t7 * t16;
    real_type t21  = inv_zeta__dot_D_1_3(t1, t2, t3, t4);
    result__[ 2   ] = t14 * t12 * t21 + t9 * t7 * t21;
    real_type t26  = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t27  = ALIAS_v__fxControl_D_1(t6, -1, 1);
    result__[ 3   ] = t9 * t27 * t26;
    real_type t29  = ALIAS_v__OmegaControl_D_1(t11, -1, 1);
    result__[ 4   ] = t14 * t29 * t26;
    result__[ 5   ] = result__[1];
    real_type t31  = inv_zeta__dot_D_2_2(t1, t2, t3, t4);
    result__[ 6   ] = t14 * t12 * t31 + t9 * t7 * t31;
    real_type t36  = inv_zeta__dot_D_1_2(t1, t2, t3, t4);
    result__[ 7   ] = t14 * t12 * t36 + t9 * t7 * t36;
    real_type t41  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 8   ] = t9 * t27 * t41;
    result__[ 9   ] = t14 * t29 * t41;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t44  = inv_zeta__dot_D_1_1(t1, t2, t3, t4);
    result__[ 12  ] = t14 * t12 * t44 + t9 * t7 * t44;
    real_type t49  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 13  ] = t9 * t27 * t49;
    result__[ 14  ] = t14 * t29 * t49;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t52  = inv_zeta__dot(t1, t2, t3, t4);
    real_type t53  = ALIAS_v__fxControl_D_1_1(t6, -1, 1);
    result__[ 18  ] = t9 * t53 * t52;
    result__[ 19  ] = result__[4];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[14];
    real_type t55  = ALIAS_v__OmegaControl_D_1_1(t11, -1, 1);
    result__[ 22  ] = t14 * t55 * t52;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 23, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_1::D2LTargsD2xpu_numRows() const { return 7; }
  integer PointMassCarModel_1::D2LTargsD2xpu_numCols() const { return 7; }
  integer PointMassCarModel_1::D2LTargsD2xpu_nnz()     const { return 7; }

  void
  PointMassCarModel_1::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 4   ;
  }


  void
  PointMassCarModel_1::D2LTargsD2xpu_sparse(
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

// EOF: PointMassCarModel_1_Methods_AdjointODE.cc
