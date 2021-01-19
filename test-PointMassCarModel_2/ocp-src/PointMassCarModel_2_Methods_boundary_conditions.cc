/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods.cc                                 |
 |                                                                       |
 |  version: 1.0   date 20/1/2021                                        |
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
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer
  PointMassCarModel_2::boundaryConditions_numEqns() const
  { return 6; }

  void
  PointMassCarModel_2::boundaryConditions_eval(
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
    real_type t1   = XL__[2];
    result__[ 0   ] = t1 - ModelPars[1];
    result__[ 1   ] = XR__[0] - XL__[0];
    result__[ 2   ] = XR__[1] - XL__[1];
    result__[ 3   ] = XR__[2] - t1;
    result__[ 4   ] = XR__[4] - XL__[4];
    result__[ 5   ] = XR__[3] - XL__[3];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DboundaryConditionsDx_numRows() const
  { return 6; }

  integer
  PointMassCarModel_2::DboundaryConditionsDx_numCols() const
  { return 10; }

  integer
  PointMassCarModel_2::DboundaryConditionsDx_nnz() const
  { return 11; }

  void
  PointMassCarModel_2::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 9   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 3   ;
    iIndex[10] = 5   ; jIndex[10] = 8   ;
  }

  void
  PointMassCarModel_2::DboundaryConditionsDx_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxp_sparse", 11, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DboundaryConditionsDp_numRows() const
  { return 6; }

  integer
  PointMassCarModel_2::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  PointMassCarModel_2::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::adjointBC_numEqns() const
  { return 10; }

  void
  PointMassCarModel_2::adjointBC_eval(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
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
    real_type t1   = OMEGA__[1];
    real_type t6   = ALIAS_Kappa_L(QL__[0]);
    real_type t7   = zeta__dot(XL__[2], XL__[1], XL__[0], t6);
    result__[ 0   ] = LL__[0] * t7 - t1;
    real_type t10  = OMEGA__[2];
    result__[ 1   ] = LL__[1] * t7 - t10;
    real_type t14  = OMEGA__[3];
    result__[ 2   ] = LL__[2] * t7 - t14 + OMEGA__[0];
    real_type t17  = OMEGA__[5];
    result__[ 3   ] = LL__[4] * t7 - t17;
    real_type t20  = OMEGA__[4];
    result__[ 4   ] = LL__[3] * t7 - t20;
    real_type t27  = ALIAS_Kappa_R(QR__[0]);
    real_type t28  = zeta__dot(XR__[2], XR__[1], XR__[0], t27);
    result__[ 5   ] = -LR__[0] * t28 + t1;
    result__[ 6   ] = -LR__[1] * t28 + t10;
    result__[ 7   ] = -LR__[2] * t28 + t14;
    result__[ 8   ] = -LR__[4] * t28 + t17;
    result__[ 9   ] = -LR__[3] * t28 + t20;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DadjointBCDx_numRows() const
  { return 10; }

  integer
  PointMassCarModel_2::DadjointBCDx_numCols() const
  { return 10; }

  integer
  PointMassCarModel_2::DadjointBCDx_nnz() const
  { return 30; }

  void
  PointMassCarModel_2::DadjointBCDx_pattern(
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
    iIndex[15] = 5   ; jIndex[15] = 5   ;
    iIndex[16] = 5   ; jIndex[16] = 6   ;
    iIndex[17] = 5   ; jIndex[17] = 7   ;
    iIndex[18] = 6   ; jIndex[18] = 5   ;
    iIndex[19] = 6   ; jIndex[19] = 6   ;
    iIndex[20] = 6   ; jIndex[20] = 7   ;
    iIndex[21] = 7   ; jIndex[21] = 5   ;
    iIndex[22] = 7   ; jIndex[22] = 6   ;
    iIndex[23] = 7   ; jIndex[23] = 7   ;
    iIndex[24] = 8   ; jIndex[24] = 5   ;
    iIndex[25] = 8   ; jIndex[25] = 6   ;
    iIndex[26] = 8   ; jIndex[26] = 7   ;
    iIndex[27] = 9   ; jIndex[27] = 5   ;
    iIndex[28] = 9   ; jIndex[28] = 6   ;
    iIndex[29] = 9   ; jIndex[29] = 7   ;
  }

  void
  PointMassCarModel_2::DadjointBCDx_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
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
    real_type t1   = XL__[2];
    real_type t2   = XL__[1];
    real_type t3   = XL__[0];
    real_type t5   = ALIAS_Kappa_L(QL__[0]);
    real_type t6   = zeta__dot_D_3(t1, t2, t3, t5);
    real_type t7   = LL__[0];
    result__[ 0   ] = t7 * t6;
    real_type t8   = zeta__dot_D_2(t1, t2, t3, t5);
    result__[ 1   ] = t7 * t8;
    real_type t9   = zeta__dot_D_1(t1, t2, t3, t5);
    result__[ 2   ] = t9 * t7;
    real_type t10  = LL__[1];
    result__[ 3   ] = t10 * t6;
    result__[ 4   ] = t10 * t8;
    result__[ 5   ] = t10 * t9;
    real_type t11  = LL__[2];
    result__[ 6   ] = t11 * t6;
    result__[ 7   ] = t11 * t8;
    result__[ 8   ] = t11 * t9;
    real_type t12  = LL__[4];
    result__[ 9   ] = t12 * t6;
    result__[ 10  ] = t12 * t8;
    result__[ 11  ] = t12 * t9;
    real_type t13  = LL__[3];
    result__[ 12  ] = t13 * t6;
    result__[ 13  ] = t13 * t8;
    result__[ 14  ] = t13 * t9;
    real_type t14  = XR__[2];
    real_type t15  = XR__[1];
    real_type t16  = XR__[0];
    real_type t18  = ALIAS_Kappa_R(QR__[0]);
    real_type t19  = zeta__dot_D_3(t14, t15, t16, t18);
    real_type t20  = LR__[0];
    result__[ 15  ] = -t20 * t19;
    real_type t22  = zeta__dot_D_2(t14, t15, t16, t18);
    result__[ 16  ] = -t20 * t22;
    real_type t24  = zeta__dot_D_1(t14, t15, t16, t18);
    result__[ 17  ] = -t20 * t24;
    real_type t26  = LR__[1];
    result__[ 18  ] = -t26 * t19;
    result__[ 19  ] = -t26 * t22;
    result__[ 20  ] = -t26 * t24;
    real_type t30  = LR__[2];
    result__[ 21  ] = -t30 * t19;
    result__[ 22  ] = -t30 * t22;
    result__[ 23  ] = -t30 * t24;
    real_type t34  = LR__[4];
    result__[ 24  ] = -t34 * t19;
    result__[ 25  ] = -t34 * t22;
    result__[ 26  ] = -t34 * t24;
    real_type t38  = LR__[3];
    result__[ 27  ] = -t38 * t19;
    result__[ 28  ] = -t38 * t22;
    result__[ 29  ] = -t38 * t24;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxp_sparse", 30, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DadjointBCDp_numRows() const
  { return 10; }

  integer
  PointMassCarModel_2::DadjointBCDp_numCols() const
  { return 0; }

  integer
  PointMassCarModel_2::DadjointBCDp_nnz() const
  { return 0; }

  void
  PointMassCarModel_2::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  PointMassCarModel_2::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: PointMassCarModel_2_Methods.cc
