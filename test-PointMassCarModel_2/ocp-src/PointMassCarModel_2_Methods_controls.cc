/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_2_Methods_controls.cc                        |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  PointMassCarModel_2::g_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t8   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t9   = 1.0 / t8;
    real_type t11  = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t11 * t9 + L__[iL_lambda4__xo] * ModelPars[iM_v__fx__max];
    real_type t17  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t17 * t9 + L__[iL_lambda5__xo] * ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DgDxlp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_2::DgDxlp_numCols() const
  { return 10; }

  integer
  PointMassCarModel_2::DgDxlp_nnz() const
  { return 8; }

  void
  PointMassCarModel_2::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 9   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t9   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    real_type t10  = t9 * t7;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    result__[ 0   ] = -t11 * t10;
    real_type t13  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t13 * t10;
    real_type t15  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t15 * t10;
    result__[ 3   ] = ModelPars[iM_v__fx__max];
    real_type t18  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    real_type t19  = t18 * t7;
    result__[ 4   ] = -t11 * t19;
    result__[ 5   ] = -t13 * t19;
    result__[ 6   ] = -t15 * t19;
    result__[ 7   ] = ModelPars[iM_v__Omega__max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DgDu_numRows() const
  { return 2; }

  integer
  PointMassCarModel_2::DgDu_numCols() const
  { return 2; }

  integer
  PointMassCarModel_2::DgDu_nnz() const
  { return 2; }

  void
  PointMassCarModel_2::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DgDu_sparse(
    NodeType2 const &    NODE__,
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
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t8 * t6;
    real_type t10  = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t10 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  PointMassCarModel_2::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[11];
    real_type X__[5];
    real_type L__[5];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    Q__[1] = (QL__[1]+QR__[1])/2;
    Q__[2] = (QL__[2]+QR__[2])/2;
    Q__[3] = (QL__[3]+QR__[3])/2;
    Q__[4] = (QL__[4]+QR__[4])/2;
    Q__[5] = (QL__[5]+QR__[5])/2;
    Q__[6] = (QL__[6]+QR__[6])/2;
    Q__[7] = (QL__[7]+QR__[7])/2;
    Q__[8] = (QL__[8]+QR__[8])/2;
    Q__[9] = (QL__[9]+QR__[9])/2;
    Q__[10] = (QL__[10]+QR__[10])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    L__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(XL__[iX_V], XL__[iX_alpha], XL__[iX_n], QL__[iQ_Kappa]);
    real_type t10  = zeta__dot(XR__[iX_V], XR__[iX_alpha], XR__[iX_n], QR__[iQ_Kappa]);
    real_type t11  = t10 * t5;
    real_type t18  = 1.0 / (t5 + t10);
    U__[ iU_v__fx    ] = v__fxControl.solve(-t18 * (LL__[iL_lambda4__xo] + LR__[iL_lambda4__xo]) * ModelPars[iM_v__fx__max] * t11, -1, 1);
    U__[ iU_v__Omega ] = v__OmegaControl.solve(-t18 * (LL__[iL_lambda5__xo] + LR__[iL_lambda5__xo]) * ModelPars[iM_v__Omega__max] * t11, -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[11];
    real_type X__[5];
    real_type L__[5];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    Q__[1] = (QL__[1]+QR__[1])/2;
    Q__[2] = (QL__[2]+QR__[2])/2;
    Q__[3] = (QL__[3]+QR__[3])/2;
    Q__[4] = (QL__[4]+QR__[4])/2;
    Q__[5] = (QL__[5]+QR__[5])/2;
    Q__[6] = (QL__[6]+QR__[6])/2;
    Q__[7] = (QL__[7]+QR__[7])/2;
    Q__[8] = (QL__[8]+QR__[8])/2;
    Q__[9] = (QL__[9]+QR__[9])/2;
    Q__[10] = (QL__[10]+QR__[10])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    L__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_V];
    real_type t2   = XL__[iX_alpha];
    real_type t3   = XL__[iX_n];
    real_type t4   = QL__[iQ_Kappa];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = XR__[iX_V];
    real_type t7   = XR__[iX_alpha];
    real_type t8   = XR__[iX_n];
    real_type t9   = QR__[iQ_Kappa];
    real_type t10  = zeta__dot(t6, t7, t8, t9);
    real_type t11  = t10 * t5;
    real_type t12  = ModelPars[iM_v__fx__max];
    real_type t16  = (LL__[iL_lambda4__xo] + LR__[iL_lambda4__xo]) * t12;
    real_type t17  = t5 + t10;
    real_type t18  = 1.0 / t17;
    real_type t21  = v__fxControl.solve_rhs(-t18 * t16 * t11, -1, 1);
    real_type t22  = zeta__dot_D_3(t1, t2, t3, t4);
    real_type t24  = t10 * t10;
    real_type t26  = t17 * t17;
    real_type t27  = 1.0 / t26;
    real_type t28  = t27 * t16;
    real_type tmp_0_0 = -t28 * t24 * t22 * t21;
    real_type t30  = ModelPars[iM_v__Omega__max];
    real_type t34  = (LL__[iL_lambda5__xo] + LR__[iL_lambda5__xo]) * t30;
    real_type t37  = v__OmegaControl.solve_rhs(-t18 * t34 * t11, -1, 1);
    real_type t40  = t27 * t34;
    real_type tmp_1_0 = -t40 * t24 * t22 * t37;
    real_type t42  = zeta__dot_D_2(t1, t2, t3, t4);
    real_type tmp_0_1 = -t28 * t24 * t42 * t21;
    real_type tmp_1_1 = -t40 * t24 * t42 * t37;
    real_type t49  = zeta__dot_D_1(t1, t2, t3, t4);
    real_type tmp_0_2 = -t28 * t24 * t49 * t21;
    real_type tmp_1_2 = -t40 * t24 * t49 * t37;
    real_type tmp_0_3 = 0;
    real_type tmp_1_3 = 0;
    real_type tmp_0_4 = 0;
    real_type tmp_1_4 = 0;
    real_type tmp_0_5 = 0;
    real_type tmp_1_5 = 0;
    real_type tmp_0_6 = 0;
    real_type tmp_1_6 = 0;
    real_type tmp_0_7 = 0;
    real_type tmp_1_7 = 0;
    real_type tmp_0_8 = -t18 * t12 * t10 * t5 * t21;
    real_type tmp_1_8 = 0;
    real_type tmp_0_9 = 0;
    real_type tmp_1_9 = -t18 * t30 * t10 * t5 * t37;
    real_type t64  = t5 * t5;
    real_type t65  = t64 * t21;
    real_type t66  = zeta__dot_D_3(t6, t7, t8, t9);
    real_type tmp_0_10 = -t28 * t66 * t65;
    real_type t69  = t64 * t37;
    real_type tmp_1_10 = -t40 * t66 * t69;
    real_type t72  = zeta__dot_D_2(t6, t7, t8, t9);
    real_type tmp_0_11 = -t28 * t72 * t65;
    real_type tmp_1_11 = -t40 * t72 * t69;
    real_type t77  = zeta__dot_D_1(t6, t7, t8, t9);
    real_type tmp_0_12 = -t28 * t77 * t65;
    real_type tmp_1_12 = -t40 * t77 * t69;
    real_type tmp_0_13 = 0;
    real_type tmp_1_13 = 0;
    real_type tmp_0_14 = 0;
    real_type tmp_1_14 = 0;
    real_type tmp_0_15 = 0;
    real_type tmp_1_15 = 0;
    real_type tmp_0_16 = 0;
    real_type tmp_1_16 = 0;
    real_type tmp_0_17 = 0;
    real_type tmp_1_17 = 0;
    real_type tmp_0_18 = tmp_0_8;
    real_type tmp_1_18 = 0;
    real_type tmp_0_19 = 0;
    real_type tmp_1_19 = tmp_1_9;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(1, 4) = tmp_1_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(1, 5) = tmp_1_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(1, 6) = tmp_1_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(1, 7) = tmp_1_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(1, 8) = tmp_1_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(1, 9) = tmp_1_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(1, 10) = tmp_1_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(1, 11) = tmp_1_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(1, 12) = tmp_1_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(1, 13) = tmp_1_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(1, 14) = tmp_1_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(1, 15) = tmp_1_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(1, 16) = tmp_1_16;
    DuDxlxlp(0, 17) = tmp_0_17;
    DuDxlxlp(1, 17) = tmp_1_17;
    DuDxlxlp(0, 18) = tmp_0_18;
    DuDxlxlp(1, 18) = tmp_1_18;
    DuDxlxlp(0, 19) = tmp_0_19;
    DuDxlxlp(1, 19) = tmp_1_19;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 40 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  PointMassCarModel_2::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
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
    real_type t11  = X__[iX_Omega];
    real_type t12  = t11 * t11;
    real_type t13  = X__[iX_V];
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t22  = AdherenceEllipse(1 - t9 / t4 * t2 - t9 / t17 * t14 * t12);
    real_type t30  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t1 * t13);
    real_type t32  = X__[iX_n];
    real_type t34  = RoadLeftBorder(Q__[iQ_leftWidth] - t32);
    real_type t35  = Q__[iQ_Kappa];
    real_type t36  = t35 * t35;
    real_type t37  = V__[1];
    real_type t40  = V__[0];
    real_type t41  = t40 * t40;
    real_type t42  = t37 * t37;
    real_type t43  = V__[2];
    real_type t44  = t43 * t43;
    real_type t45  = V__[3];
    real_type t46  = t45 * t45;
    real_type t47  = V__[4];
    real_type t48  = t47 * t47;
    real_type t50  = X__[iX_alpha];
    real_type t51  = zeta__dot(t13, t50, t32, t35);
    real_type t52  = t51 * t51;
    real_type t55  = ModelPars[iM_kD];
    real_type t58  = ModelPars[iM_v__fx__max];
    real_type t60  = U__[iU_v__fx];
    real_type t63  = sin(t50);
    real_type t65  = U__[iU_v__Omega];
    real_type t67  = ModelPars[iM_v__Omega__max];
    real_type t75  = t55 * t55;
    real_type t76  = t14 * t14;
    real_type t81  = t63 * t63;
    real_type t83  = t65 * t65;
    real_type t84  = t67 * t67;
    real_type t86  = t58 * t58;
    real_type t87  = t60 * t60;
    real_type t91  = LimitMinSpeed(t13);
    real_type t92  = v__fxControl(t60, -1, 1);
    real_type t93  = v__OmegaControl(t65, -1, 1);
    real_type t96  = RoadRightBorder(Q__[iQ_rightWidth] + t32);
    real_type result__ = 1.0 / t51 * (t22 + t30 + t34 + t52 * t51 * (2 * t37 * t35 + t36 + t41 + t42 + t44 + t46 + t48) + t52 * (-2 * t63 * t40 * t13 + 2 * t14 * t43 * t55 - 2 * t67 * t45 * t65 - 2 * t60 * t58 * t47 - 2 * t43 * t1 - 2 * t35 * t11 - 2 * t37 * t11) + t51 * (-2 * t14 * t55 * t1 + t81 * t14 + t76 * t75 + t84 * t83 + t87 * t86 + t12 + t2) + t91 + t92 + t93 + t96);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DmDu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t7   = U__[iU_v__fx];
    real_type t8   = ALIAS_v__fxControl_D_1(t7, -1, 1);
    real_type t12  = ModelPars[iM_v__fx__max];
    result__[ 0   ] = t8 * t6 - 2 * t12 * (-t12 * t7 + V__[4] * t5);
    real_type t17  = U__[iU_v__Omega];
    real_type t18  = ALIAS_v__OmegaControl_D_1(t17, -1, 1);
    real_type t22  = ModelPars[iM_v__Omega__max];
    result__[ 1   ] = t18 * t6 - 2 * t22 * (-t22 * t17 + V__[3] * t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DmDuu_numRows() const
  { return 2; }

  integer
  PointMassCarModel_2::DmDuu_numCols() const
  { return 2; }

  integer
  PointMassCarModel_2::DmDuu_nnz() const
  { return 2; }

  void
  PointMassCarModel_2::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_2::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t5   = zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    real_type t11  = ModelPars[iM_v__fx__max] * ModelPars[iM_v__fx__max];
    result__[ 0   ] = t8 * t6 + 2 * t11;
    real_type t14  = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    real_type t17  = ModelPars[iM_v__Omega__max] * ModelPars[iM_v__Omega__max];
    result__[ 1   ] = t14 * t6 + 2 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: PointMassCarModel_2_Methods_controls.cc
