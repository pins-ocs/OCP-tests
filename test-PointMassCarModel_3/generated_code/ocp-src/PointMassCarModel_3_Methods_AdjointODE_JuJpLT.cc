/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_AdjointODE.cc                      |
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
#define ALIAS_yV_R(__t1, __t2) segmentRight.iso_y( __t1, __t2)
#define ALIAS_yV_L(__t1, __t2) segmentLeft.iso_y( __t1, __t2)
#define ALIAS_yV(__t1, __t2) segment.iso_y( __t1, __t2)
#define ALIAS_xV_R(__t1, __t2) segmentRight.iso_x( __t1, __t2)
#define ALIAS_xV_L(__t1, __t2) segmentLeft.iso_x( __t1, __t2)
#define ALIAS_xV(__t1, __t2) segment.iso_x( __t1, __t2)
#define ALIAS_Kappa_R_DD(__t1) segmentRight.iso_curvature_DD( __t1)
#define ALIAS_Kappa_R_D(__t1) segmentRight.iso_curvature_D( __t1)
#define ALIAS_Kappa_R(__t1) segmentRight.iso_curvature( __t1)
#define ALIAS_Kappa_L_DD(__t1) segmentLeft.iso_curvature_DD( __t1)
#define ALIAS_Kappa_L_D(__t1) segmentLeft.iso_curvature_D( __t1)
#define ALIAS_Kappa_L(__t1) segmentLeft.iso_curvature( __t1)
#define ALIAS_Kappa_DD(__t1) segment.iso_curvature_DD( __t1)
#define ALIAS_Kappa_D(__t1) segment.iso_curvature_D( __t1)
#define ALIAS_Kappa(__t1) segment.iso_curvature( __t1)
#define ALIAS_ssSegmentMax_R(___dummy___) segmentRight.ss_segment_max()
#define ALIAS_ssSegmentMax_L(___dummy___) segmentLeft.ss_segment_max()
#define ALIAS_ssSegmentMax(___dummy___) segment.ss_segment_max()
#define ALIAS_ssSegmentMin_R(___dummy___) segmentRight.ss_segment_min()
#define ALIAS_ssSegmentMin_L(___dummy___) segmentLeft.ss_segment_min()
#define ALIAS_ssSegmentMin(___dummy___) segment.ss_segment_min()
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


namespace PointMassCarModel_3Define {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::JP_numEqns() const { return 0; }

  void
  PointMassCarModel_3::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::LT_numEqns() const { return 4; }

  void
  PointMassCarModel_3::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t14  = X__[iX_Omega] * X__[iX_Omega];
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t24  = AdherenceEllipse(t11 / t6 * t4 + t11 / t19 * t16 * t14 - 1);
    result__[ 0   ] = t24 * t2;
    real_type t25  = X__[iX_n];
    real_type t26  = X__[iX_s];
    real_type t27  = ALIAS_leftWidth(t26);
    real_type t29  = RoadLeftBorder(t25 - t27);
    result__[ 1   ] = t29 * t2;
    real_type t30  = ALIAS_rightWidth(t26);
    real_type t32  = RoadRightBorder(-t25 - t30);
    result__[ 2   ] = t32 * t2;
    real_type t40  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t3 * t15 - 1);
    result__[ 3   ] = t40 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::JU_numEqns() const { return 2; }

  void
  PointMassCarModel_3::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t4   = v__fxControl(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = v__OmegaControl(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::LTargs_numEqns() const { return 4; }

  void
  PointMassCarModel_3::LTargs_eval(
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
    real_type t22  = X__[iX_s];
    real_type t23  = ALIAS_leftWidth(t22);
    result__[ 1   ] = t21 - t23;
    real_type t24  = ALIAS_rightWidth(t22);
    result__[ 2   ] = -t21 - t24;
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13 - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DJPDxpu_numRows() const { return 0; }
  integer PointMassCarModel_3::DJPDxpu_numCols() const { return 9; }
  integer PointMassCarModel_3::DJPDxpu_nnz()     const { return 0; }

  void
  PointMassCarModel_3::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_3::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DLTDxpu_numRows() const { return 4; }
  integer PointMassCarModel_3::DLTDxpu_numCols() const { return 9; }
  integer PointMassCarModel_3::DLTDxpu_nnz()     const { return 13; }

  void
  PointMassCarModel_3::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 6   ;
    iIndex[10] = 3   ; jIndex[10] = 3   ;
    iIndex[11] = 3   ; jIndex[11] = 5   ;
    iIndex[12] = 3   ; jIndex[12] = 6   ;
  }


  void
  PointMassCarModel_3::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_fx];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t7   = 1.0 / t6;
    real_type t10  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t11  = 1.0 / t10;
    real_type t13  = X__[iX_Omega];
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_V];
    real_type t16  = t15 * t15;
    real_type t19  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t20  = 1.0 / t19;
    real_type t23  = t11 * t20 * t16 * t14 + t11 * t7 * t4 - 1;
    real_type t24  = ALIAS_AdherenceEllipse_D(t23);
    real_type t25  = t24 * t2;
    result__[ 0   ] = 2 * t11 * t20 * t15 * t14 * t25;
    result__[ 1   ] = 2 * t11 * t20 * t16 * t13 * t25;
    result__[ 2   ] = 2 * t11 * t7 * t3 * t25;
    real_type t37  = AdherenceEllipse(t23);
    result__[ 3   ] = 2 * t37 * t1;
    real_type t39  = X__[iX_n];
    real_type t40  = X__[iX_s];
    real_type t41  = ALIAS_leftWidth(t40);
    real_type t42  = t39 - t41;
    real_type t43  = ALIAS_RoadLeftBorder_D(t42);
    real_type t45  = ALIAS_leftWidth_D(t40);
    result__[ 4   ] = -t45 * t43 * t2;
    result__[ 5   ] = t43 * t2;
    real_type t47  = RoadLeftBorder(t42);
    result__[ 6   ] = 2 * t47 * t1;
    real_type t49  = ALIAS_rightWidth(t40);
    real_type t50  = -t39 - t49;
    real_type t51  = ALIAS_RoadRightBorder_D(t50);
    real_type t52  = t51 * t2;
    real_type t53  = ALIAS_rightWidth_D(t40);
    result__[ 7   ] = -t53 * t52;
    result__[ 8   ] = -t52;
    real_type t55  = RoadRightBorder(t50);
    result__[ 9   ] = 2 * t55 * t1;
    real_type t58  = ModelPars[iM_m];
    real_type t60  = 1.0 / ModelPars[iM_Pmax];
    real_type t63  = t60 * t58 * t3 * t15 - 1;
    real_type t64  = ALIAS_PowerLimit_D(t63);
    real_type t65  = t64 * t2;
    result__[ 10  ] = t60 * t58 * t3 * t65;
    result__[ 11  ] = t60 * t58 * t15 * t65;
    real_type t70  = PowerLimit(t63);
    result__[ 12  ] = 2 * t70 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 13, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DJUDxpu_numRows() const { return 2; }
  integer PointMassCarModel_3::DJUDxpu_numCols() const { return 9; }
  integer PointMassCarModel_3::DJUDxpu_nnz()     const { return 4; }

  void
  PointMassCarModel_3::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 8   ;
  }


  void
  PointMassCarModel_3::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = U__[iU_v__fx];
    real_type t3   = v__fxControl(t2, -1, 1);
    result__[ 0   ] = 2 * t3 * t1;
    real_type t5   = t1 * t1;
    real_type t6   = ALIAS_v__fxControl_D_1(t2, -1, 1);
    result__[ 1   ] = t6 * t5;
    real_type t7   = U__[iU_v__Omega];
    real_type t8   = v__OmegaControl(t7, -1, 1);
    result__[ 2   ] = 2 * t8 * t1;
    real_type t10  = ALIAS_v__OmegaControl_D_1(t7, -1, 1);
    result__[ 3   ] = t10 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DLTargsDxpu_numRows() const { return 4; }
  integer PointMassCarModel_3::DLTargsDxpu_numCols() const { return 9; }
  integer PointMassCarModel_3::DLTargsDxpu_nnz()     const { return 9; }

  void
  PointMassCarModel_3::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 5   ;
  }


  void
  PointMassCarModel_3::DLTargsDxpu_sparse(
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
    real_type t22  = X__[iX_s];
    real_type t23  = ALIAS_leftWidth_D(t22);
    result__[ 3   ] = -t23;
    result__[ 4   ] = 1;
    real_type t24  = ALIAS_rightWidth_D(t22);
    result__[ 5   ] = -t24;
    result__[ 6   ] = -1;
    real_type t25  = ModelPars[iM_m];
    real_type t28  = 1.0 / ModelPars[iM_Pmax];
    result__[ 7   ] = t28 * t25 * t16;
    result__[ 8   ] = t28 * t25 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 9, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2JPD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2JPD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2JPD2xpu_nnz()     const { return 0; }

  void
  PointMassCarModel_3::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  PointMassCarModel_3::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2LTD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2LTD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2LTD2xpu_nnz()     const { return 24; }

  void
  PointMassCarModel_3::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 6   ;
    iIndex[10] = 4   ; jIndex[10] = 3   ;
    iIndex[11] = 4   ; jIndex[11] = 4   ;
    iIndex[12] = 4   ; jIndex[12] = 5   ;
    iIndex[13] = 4   ; jIndex[13] = 6   ;
    iIndex[14] = 5   ; jIndex[14] = 3   ;
    iIndex[15] = 5   ; jIndex[15] = 4   ;
    iIndex[16] = 5   ; jIndex[16] = 5   ;
    iIndex[17] = 5   ; jIndex[17] = 6   ;
    iIndex[18] = 6   ; jIndex[18] = 0   ;
    iIndex[19] = 6   ; jIndex[19] = 1   ;
    iIndex[20] = 6   ; jIndex[20] = 3   ;
    iIndex[21] = 6   ; jIndex[21] = 4   ;
    iIndex[22] = 6   ; jIndex[22] = 5   ;
    iIndex[23] = 6   ; jIndex[23] = 6   ;
  }


  void
  PointMassCarModel_3::D2LTD2xpu_sparse(
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
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_n];
    real_type t4   = X__[iX_s];
    real_type t5   = ALIAS_leftWidth(t4);
    real_type t6   = t3 - t5;
    real_type t7   = ALIAS_RoadLeftBorder_DD(t6);
    real_type t8   = t7 * t2;
    real_type t9   = ALIAS_leftWidth_D(t4);
    real_type t10  = t9 * t9;
    real_type t11  = OMEGA__[1];
    real_type t14  = ALIAS_RoadLeftBorder_D(t6);
    real_type t16  = ALIAS_leftWidth_DD(t4);
    real_type t19  = ALIAS_rightWidth(t4);
    real_type t20  = -t3 - t19;
    real_type t21  = ALIAS_RoadRightBorder_DD(t20);
    real_type t22  = t21 * t2;
    real_type t23  = ALIAS_rightWidth_D(t4);
    real_type t24  = t23 * t23;
    real_type t25  = OMEGA__[2];
    real_type t28  = ALIAS_RoadRightBorder_D(t20);
    real_type t30  = ALIAS_rightWidth_DD(t4);
    result__[ 0   ] = -t11 * t16 * t14 * t2 - t25 * t30 * t28 * t2 + t11 * t10 * t8 + t25 * t24 * t22;
    real_type t33  = t11 * t9;
    real_type t35  = t25 * t23;
    result__[ 1   ] = t35 * t22 - t33 * t8;
    real_type t37  = t14 * t1;
    real_type t39  = t28 * t1;
    result__[ 2   ] = -2 * t33 * t37 - 2 * t35 * t39;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = t11 * t8 + t25 * t22;
    result__[ 5   ] = 2 * t11 * t37 - 2 * t25 * t39;
    real_type t47  = X__[iX_fx];
    real_type t48  = t47 * t47;
    real_type t50  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t51  = 1.0 / t50;
    real_type t54  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t55  = 1.0 / t54;
    real_type t57  = X__[iX_Omega];
    real_type t58  = t57 * t57;
    real_type t59  = X__[iX_V];
    real_type t60  = t59 * t59;
    real_type t63  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t64  = 1.0 / t63;
    real_type t65  = t55 * t64;
    real_type t67  = t55 * t51 * t48 + t65 * t60 * t58 - 1;
    real_type t68  = ALIAS_AdherenceEllipse_DD(t67);
    real_type t69  = t68 * t2;
    real_type t70  = t58 * t58;
    real_type t72  = t63 * t63;
    real_type t73  = 1.0 / t72;
    real_type t75  = t54 * t54;
    real_type t76  = 1.0 / t75;
    real_type t77  = OMEGA__[0];
    real_type t78  = t77 * t76;
    real_type t82  = ALIAS_AdherenceEllipse_D(t67);
    real_type t83  = t82 * t2;
    real_type t85  = t77 * t65;
    real_type t89  = ModelPars[iM_m];
    real_type t90  = ModelPars[iM_Pmax];
    real_type t92  = 1.0 / t90 * t89;
    real_type t94  = t92 * t47 * t59 - 1;
    real_type t95  = ALIAS_PowerLimit_DD(t94);
    real_type t96  = t95 * t2;
    real_type t98  = t89 * t89;
    real_type t99  = t90 * t90;
    real_type t101 = 1.0 / t99 * t98;
    real_type t102 = OMEGA__[3];
    real_type t103 = t102 * t101;
    result__[ 6   ] = 4 * t78 * t73 * t60 * t70 * t69 + t103 * t48 * t96 + 2 * t85 * t58 * t83;
    real_type t112 = t64 * t59;
    real_type t113 = t77 * t55;
    real_type t114 = t113 * t112;
    result__[ 7   ] = 4 * t78 * t73 * t60 * t59 * t58 * t57 * t69 + 4 * t114 * t57 * t83;
    real_type t118 = t51 * t47 * t69;
    real_type t128 = ALIAS_PowerLimit_D(t94);
    real_type t130 = t102 * t92;
    result__[ 8   ] = t102 * t47 * t101 * t59 * t96 + 4 * t77 * t112 * t58 * t76 * t118 + t130 * t128 * t2;
    real_type t132 = t82 * t1;
    real_type t136 = t128 * t1;
    result__[ 9   ] = 4 * t114 * t58 * t132 + 2 * t130 * t47 * t136;
    result__[ 10  ] = result__[7];
    real_type t141 = t60 * t60;
    result__[ 11  ] = 4 * t78 * t73 * t141 * t58 * t69 + 2 * t85 * t60 * t83;
    real_type t150 = t64 * t60;
    result__[ 12  ] = 4 * t77 * t150 * t57 * t76 * t118;
    result__[ 13  ] = 4 * t113 * t150 * t57 * t132;
    result__[ 14  ] = result__[8];
    result__[ 15  ] = result__[12];
    real_type t158 = t50 * t50;
    real_type t165 = t77 * t55 * t51;
    result__[ 16  ] = 4 * t77 * t76 / t158 * t48 * t69 + 2 * t165 * t83 + t103 * t60 * t96;
    result__[ 17  ] = 2 * t130 * t59 * t136 + 4 * t165 * t47 * t132;
    result__[ 18  ] = result__[2];
    result__[ 19  ] = result__[5];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[13];
    result__[ 22  ] = result__[17];
    real_type t176 = AdherenceEllipse(t67);
    real_type t178 = RoadLeftBorder(t6);
    real_type t180 = RoadRightBorder(t20);
    real_type t182 = PowerLimit(t94);
    result__[ 23  ] = 2 * t102 * t182 + 2 * t11 * t178 + 2 * t176 * t77 + 2 * t180 * t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 24, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2JUD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2JUD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2JUD2xpu_nnz()     const { return 7; }

  void
  PointMassCarModel_3::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 6   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 6   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 6   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 7   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 7   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 8   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 8   ; jIndex[6 ] = 8   ;
  }


  void
  PointMassCarModel_3::D2JUD2xpu_sparse(
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
    real_type t1   = U__[iU_v__fx];
    real_type t2   = v__fxControl(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    real_type t5   = U__[iU_v__Omega];
    real_type t6   = v__OmegaControl(t5, -1, 1);
    real_type t7   = OMEGA__[1];
    result__[ 0   ] = 2 * t3 * t2 + 2 * t7 * t6;
    real_type t10  = X__[iX_sqrt_inv_Vseg];
    real_type t11  = ALIAS_v__fxControl_D_1(t1, -1, 1);
    result__[ 1   ] = 2 * t3 * t11 * t10;
    real_type t14  = ALIAS_v__OmegaControl_D_1(t5, -1, 1);
    result__[ 2   ] = 2 * t7 * t14 * t10;
    result__[ 3   ] = result__[1];
    real_type t17  = t10 * t10;
    real_type t18  = ALIAS_v__fxControl_D_1_1(t1, -1, 1);
    result__[ 4   ] = t3 * t18 * t17;
    result__[ 5   ] = result__[2];
    real_type t20  = ALIAS_v__OmegaControl_D_1_1(t5, -1, 1);
    result__[ 6   ] = t7 * t20 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::D2LTargsD2xpu_numRows() const { return 9; }
  integer PointMassCarModel_3::D2LTargsD2xpu_numCols() const { return 9; }
  integer PointMassCarModel_3::D2LTargsD2xpu_nnz()     const { return 8; }

  void
  PointMassCarModel_3::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 5   ;
  }


  void
  PointMassCarModel_3::D2LTargsD2xpu_sparse(
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
    real_type t1   = X__[iX_s];
    real_type t2   = ALIAS_leftWidth_DD(t1);
    real_type t5   = ALIAS_rightWidth_DD(t1);
    result__[ 0   ] = -OMEGA__[1] * t2 - OMEGA__[2] * t5;
    real_type t8   = X__[iX_Omega];
    real_type t9   = t8 * t8;
    real_type t11  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t16  = 1.0 / t15;
    real_type t17  = OMEGA__[0];
    real_type t18  = t17 * t16;
    result__[ 1   ] = 2 * t18 * t12 * t9;
    real_type t20  = X__[iX_V];
    result__[ 2   ] = 4 * t17 * t16 * t12 * t20 * t8;
    result__[ 3   ] = ModelPars[iM_m] / ModelPars[iM_Pmax] * OMEGA__[3];
    result__[ 4   ] = result__[2];
    real_type t30  = t20 * t20;
    result__[ 5   ] = 2 * t18 * t12 * t30;
    result__[ 6   ] = result__[3];
    real_type t34  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    result__[ 7   ] = 2 * t17 * t16 / t34;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 8, i_segment );
  }

}

// EOF: PointMassCarModel_3_Methods_AdjointODE.cc
