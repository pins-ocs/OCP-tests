/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_1_Methods_controls.cc                        |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  PointMassCarModel_1::g_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::g_eval(
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
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t10  = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = (L__[iL_lambda5__xo] * ModelPars[iM_v__fx__max] + t10) * t5;
    real_type t16  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = (L__[iL_lambda4__xo] * ModelPars[iM_v__Omega__max] + t16) * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DgDxlp_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DgDxlp_numCols() const
  { return 10; }

  integer
  PointMassCarModel_1::DgDxlp_nnz() const
  { return 8; }

  void
  PointMassCarModel_1::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DgDxlp_sparse(
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
    real_type t5   = inv_zeta__dot_D_3(t1, t2, t3, t4);
    real_type t7   = ModelPars[iM_v__fx__max];
    real_type t10  = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    real_type t11  = t7 * L__[iL_lambda5__xo] + t10;
    result__[ 0   ] = t11 * t5;
    real_type t12  = inv_zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = t11 * t12;
    real_type t13  = inv_zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = t11 * t13;
    real_type t14  = inv_zeta__dot(t1, t2, t3, t4);
    result__[ 3   ] = t14 * t7;
    real_type t16  = ModelPars[iM_v__Omega__max];
    real_type t19  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    real_type t20  = t16 * L__[iL_lambda4__xo] + t19;
    result__[ 4   ] = t20 * t5;
    result__[ 5   ] = t20 * t12;
    result__[ 6   ] = t20 * t13;
    result__[ 7   ] = t14 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DgDu_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DgDu_numCols() const
  { return 2; }

  integer
  PointMassCarModel_1::DgDu_nnz() const
  { return 2; }

  void
  PointMassCarModel_1::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DgDu_sparse(
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
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t7 * t5;
    real_type t9   = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t9 * t5;
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
  PointMassCarModel_1::u_eval_analytic(
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
    real_type t6   = inv_zeta__dot(XL__[iX_V], XL__[iX_alpha], XL__[iX_n], QL__[iQ_Kappa]);
    real_type t13  = inv_zeta__dot(XR__[iX_V], XR__[iX_alpha], XR__[iX_n], QR__[iQ_Kappa]);
    real_type t19  = 1.0 / (t6 + t13);
    U__[ iU_v__fx    ] = v__fxControl.solve(-t19 * (LR__[iL_lambda5__xo] * t13 + LL__[iL_lambda5__xo] * t6) * ModelPars[iM_v__fx__max], -1, 1);
    U__[ iU_v__Omega ] = v__OmegaControl.solve(-t19 * (t13 * LR__[iL_lambda4__xo] + t6 * LL__[iL_lambda4__xo]) * ModelPars[iM_v__Omega__max], -1, 1);
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
  PointMassCarModel_1::DuDxlxlp_full_analytic(
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
    real_type t1   = ModelPars[iM_v__fx__max];
    real_type t2   = XL__[iX_V];
    real_type t3   = XL__[iX_alpha];
    real_type t4   = XL__[iX_n];
    real_type t5   = QL__[iQ_Kappa];
    real_type t6   = inv_zeta__dot(t2, t3, t4, t5);
    real_type t7   = LL__[iL_lambda5__xo];
    real_type t9   = XR__[iX_V];
    real_type t10  = XR__[iX_alpha];
    real_type t11  = XR__[iX_n];
    real_type t12  = QR__[iQ_Kappa];
    real_type t13  = inv_zeta__dot(t9, t10, t11, t12);
    real_type t14  = LR__[iL_lambda5__xo];
    real_type t18  = t6 + t13;
    real_type t19  = 1.0 / t18;
    real_type t21  = v__fxControl.solve_rhs(-t19 * (t14 * t13 + t7 * t6) * t1, -1, 1);
    real_type t22  = t1 * t21;
    real_type t23  = inv_zeta__dot_D_3(t2, t3, t4, t5);
    real_type t25  = t7 - t14;
    real_type t27  = t18 * t18;
    real_type t28  = 1.0 / t27;
    real_type t29  = t28 * t25 * t13;
    real_type tmp_0_0 = -t29 * t23 * t22;
    real_type t31  = ModelPars[iM_v__Omega__max];
    real_type t32  = LL__[iL_lambda4__xo];
    real_type t34  = LR__[iL_lambda4__xo];
    real_type t39  = v__OmegaControl.solve_rhs(-t19 * (t34 * t13 + t32 * t6) * t31, -1, 1);
    real_type t40  = t31 * t39;
    real_type t42  = t32 - t34;
    real_type t44  = t28 * t42 * t13;
    real_type tmp_1_0 = -t44 * t23 * t40;
    real_type t46  = inv_zeta__dot_D_2(t2, t3, t4, t5);
    real_type tmp_0_1 = -t29 * t46 * t22;
    real_type tmp_1_1 = -t44 * t46 * t40;
    real_type t51  = inv_zeta__dot_D_1(t2, t3, t4, t5);
    real_type tmp_0_2 = -t29 * t51 * t22;
    real_type tmp_1_2 = -t44 * t51 * t40;
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
    real_type tmp_0_8 = 0;
    real_type t56  = t19 * t6;
    real_type tmp_1_8 = -t56 * t40;
    real_type tmp_0_9 = -t56 * t22;
    real_type tmp_1_9 = 0;
    real_type t59  = inv_zeta__dot_D_3(t9, t10, t11, t12);
    real_type t62  = t28 * t25 * t6;
    real_type tmp_0_10 = t62 * t59 * t22;
    real_type t65  = t28 * t42 * t6;
    real_type tmp_1_10 = t65 * t59 * t40;
    real_type t66  = inv_zeta__dot_D_2(t9, t10, t11, t12);
    real_type tmp_0_11 = t62 * t66 * t22;
    real_type tmp_1_11 = t65 * t66 * t40;
    real_type t69  = inv_zeta__dot_D_1(t9, t10, t11, t12);
    real_type tmp_0_12 = t62 * t69 * t22;
    real_type tmp_1_12 = t65 * t69 * t40;
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
    real_type tmp_0_18 = 0;
    real_type t72  = t19 * t13;
    real_type tmp_1_18 = -t72 * t40;
    real_type tmp_0_19 = -t72 * t22;
    real_type tmp_1_19 = 0;
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
  PointMassCarModel_1::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_V];
    real_type t2   = X__[iX_alpha];
    real_type t3   = X__[iX_n];
    real_type t4   = Q__[iQ_Kappa];
    real_type t5   = inv_zeta__dot(t1, t2, t3, t4);
    real_type t6   = X__[iX_fx];
    real_type t7   = t6 * t6;
    real_type t9   = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t13  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t14  = 1.0 / t13;
    real_type t16  = X__[iX_Omega];
    real_type t17  = t16 * t16;
    real_type t18  = t1 * t1;
    real_type t21  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t26  = AdherenceEllipse(1 - t14 / t9 * t7 - t14 / t21 * t18 * t17);
    real_type t35  = PowerLimit(1 - ModelPars[iM_m] / ModelPars[iM_Pmax] * t6 * t1);
    real_type t39  = RoadLeftBorder(Q__[iQ_leftWidth] - t3);
    real_type t41  = t18 * t18;
    real_type t42  = ModelPars[iM_kD];
    real_type t43  = t42 * t42;
    real_type t48  = sin(t2);
    real_type t49  = t48 * t48;
    real_type t51  = U__[iU_v__Omega];
    real_type t52  = t51 * t51;
    real_type t53  = ModelPars[iM_v__Omega__max];
    real_type t54  = t53 * t53;
    real_type t56  = U__[iU_v__fx];
    real_type t57  = t56 * t56;
    real_type t58  = ModelPars[iM_v__fx__max];
    real_type t59  = t58 * t58;
    real_type t62  = t5 * t5;
    real_type t65  = V__[2];
    real_type t68  = V__[4];
    real_type t72  = V__[0];
    real_type t76  = V__[3];
    real_type t82  = V__[1];
    real_type t87  = LimitMinSpeed(t1);
    real_type t88  = v__fxControl(t56, -1, 1);
    real_type t89  = v__OmegaControl(t51, -1, 1);
    real_type t92  = RoadRightBorder(Q__[iQ_rightWidth] + t3);
    real_type t93  = -2 * t48 * t72 * t1 + 2 * t65 * t18 * t42 - 2 * t51 * t76 * t53 - 2 * t58 * t56 * t68 - 2 * t4 * t16 - 2 * t82 * t16 - 2 * t65 * t6 + t87 + t88 + t89 + t92;
    real_type t95  = t4 * t4;
    real_type t98  = t68 * t68;
    real_type t99  = t72 * t72;
    real_type t100 = t82 * t82;
    real_type t101 = t65 * t65;
    real_type t102 = t76 * t76;
    real_type result__ = t26 * t5 + t35 * t5 + t39 * t5 + t62 * (-2 * t42 * t6 * t18 + t49 * t18 + t43 * t41 + t54 * t52 + t59 * t57 + t17 + t7) + t5 * t93 + t95 + 2 * t82 * t4 + t98 + t99 + t100 + t101 + t102;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DmDu_numEqns() const
  { return 2; }

  void
  PointMassCarModel_1::DmDu_eval(
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
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t6   = U__[iU_v__fx];
    real_type t8   = ModelPars[iM_v__fx__max];
    real_type t9   = t8 * t8;
    real_type t15  = ALIAS_v__fxControl_D_1(t6, -1, 1);
    result__[ 0   ] = (2 * t9 * t6 * t5 - 2 * t8 * V__[4] + t15) * t5;
    real_type t17  = U__[iU_v__Omega];
    real_type t19  = ModelPars[iM_v__Omega__max];
    real_type t20  = t19 * t19;
    real_type t26  = ALIAS_v__OmegaControl_D_1(t17, -1, 1);
    result__[ 1   ] = (2 * t20 * t17 * t5 - 2 * t19 * V__[3] + t26) * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_1::DmDuu_numRows() const
  { return 2; }

  integer
  PointMassCarModel_1::DmDuu_numCols() const
  { return 2; }

  integer
  PointMassCarModel_1::DmDuu_nnz() const
  { return 2; }

  void
  PointMassCarModel_1::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_1::DmDuu_sparse(
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
    real_type t5   = inv_zeta__dot(X__[iX_V], X__[iX_alpha], X__[iX_n], Q__[iQ_Kappa]);
    real_type t7   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    real_type t10  = ModelPars[iM_v__fx__max] * ModelPars[iM_v__fx__max];
    real_type t11  = t5 * t5;
    result__[ 0   ] = 2 * t11 * t10 + t7 * t5;
    real_type t15  = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    real_type t18  = ModelPars[iM_v__Omega__max] * ModelPars[iM_v__Omega__max];
    result__[ 1   ] = 2 * t11 * t18 + t15 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: PointMassCarModel_1_Methods_controls.cc