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
    real_type t8   = zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
    real_type t9   = 1.0 / t8;
    real_type t11  = ALIAS_v__fxControl_D_1(U__[0], -1, 1);
    result__[ 0   ] = t11 * t9 + L__[3] * ModelPars[15];
    real_type t17  = ALIAS_v__OmegaControl_D_1(U__[1], -1, 1);
    result__[ 1   ] = t17 * t9 + L__[4] * ModelPars[14];
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
    integer iIndex[],
    integer jIndex[]
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

  void
  PointMassCarModel_2::DgDxlp_sparse(
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
    real_type t1   = X__[2];
    real_type t2   = X__[1];
    real_type t3   = X__[0];
    real_type t4   = Q__[1];
    real_type t5   = zeta__dot(t1, t2, t3, t4);
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t9   = ALIAS_v__fxControl_D_1(U__[0], -1, 1);
    real_type t10  = t9 * t7;
    real_type t11  = zeta__dot_D_3(t1, t2, t3, t4);
    result__[ 0   ] = -t11 * t10;
    real_type t13  = zeta__dot_D_2(t1, t2, t3, t4);
    result__[ 1   ] = -t13 * t10;
    real_type t15  = zeta__dot_D_1(t1, t2, t3, t4);
    result__[ 2   ] = -t15 * t10;
    result__[ 3   ] = ModelPars[15];
    real_type t18  = ALIAS_v__OmegaControl_D_1(U__[1], -1, 1);
    real_type t19  = t18 * t7;
    result__[ 4   ] = -t11 * t19;
    result__[ 5   ] = -t13 * t19;
    result__[ 6   ] = -t15 * t19;
    result__[ 7   ] = ModelPars[14];
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
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  void
  PointMassCarModel_2::DgDu_sparse(
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
    real_type t6   = 1.0 / t5;
    real_type t8   = ALIAS_v__fxControl_D_1_1(U__[0], -1, 1);
    result__[ 0   ] = t8 * t6;
    real_type t10  = ALIAS_v__OmegaControl_D_1_1(U__[1], -1, 1);
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
  integer
  PointMassCarModel_2::u_numEqns() const
  { return 2; }

  void
  PointMassCarModel_2::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    Road2D::SegmentClass const & segment = pRoad->getSegmentByIndex(i_segment);
    real_type t8   = zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
    U__[ iU_v__fx    ] = v__fxControl.solve(-t8 * ModelPars[15] * L__[3], -1, 1);
    U__[ iU_v__Omega ] = v__OmegaControl.solve(-t8 * ModelPars[14] * L__[4], -1, 1);
  }

  void
  PointMassCarModel_2::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[11];
    real_type X__[5];
    real_type L__[5];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
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
    this->u_eval_analytic( NODE__, P__, U__ );
  }

  /*\
   |   ___       ___      _                       _      _   _
   |  |   \ _  _|   \__ _| |_ __   __ _ _ _  __ _| |_  _| |_(_)__
   |  | |) | || | |) \ \ / | '_ \ / _` | ' \/ _` | | || |  _| / _|
   |  |___/ \_,_|___//_\_\_| .__/ \__,_|_||_\__,_|_|\_, |\__|_\__|
   |                       |_|                      |__/
  \*/
  void
  PointMassCarModel_2::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = -v__fxControl.solve_rhs(-L__[3] * ModelPars[15] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * L__[3] * ModelPars[15] * zeta__dot_D_3(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(1, 0) = -v__OmegaControl.solve_rhs(-L__[4] * ModelPars[14] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * L__[4] * ModelPars[14] * zeta__dot_D_3(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(0, 1) = -v__fxControl.solve_rhs(-L__[3] * ModelPars[15] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * L__[3] * ModelPars[15] * zeta__dot_D_2(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(1, 1) = -v__OmegaControl.solve_rhs(-L__[4] * ModelPars[14] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * L__[4] * ModelPars[14] * zeta__dot_D_2(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(0, 2) = -v__fxControl.solve_rhs(-L__[3] * ModelPars[15] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * L__[3] * ModelPars[15] * zeta__dot_D_1(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(1, 2) = -v__OmegaControl.solve_rhs(-L__[4] * ModelPars[14] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * L__[4] * ModelPars[14] * zeta__dot_D_1(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
    DuDxlp(0, 8) = -v__fxControl.solve_rhs(-L__[3] * ModelPars[15] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * ModelPars[15] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
    DuDxlp(1, 8) = 0;
    DuDxlp(0, 9) = 0;
    DuDxlp(1, 9) = -v__OmegaControl.solve_rhs(-L__[4] * ModelPars[14] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]), -1, 1) * ModelPars[14] * zeta__dot(X__[2], X__[1], X__[0], Q__[1]);
  }

  void
  PointMassCarModel_2::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[11];
    real_type X__[5];
    real_type L__[5];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
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
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
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
    real_type            segmentLink[]
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
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  void
  PointMassCarModel_2::DsegmentLinkDxp_sparse(
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
  PointMassCarModel_2::jump_numEqns() const
  { return 10; }

  void
  PointMassCarModel_2::jump_eval(
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
    real_type t1   = XR__[0];
    real_type t2   = XL__[0];
    result__[ 0   ] = t1 - t2;
    real_type t3   = XR__[1];
    real_type t4   = XL__[1];
    result__[ 1   ] = t3 - t4;
    real_type t5   = XR__[2];
    real_type t6   = XL__[2];
    result__[ 2   ] = t5 - t6;
    result__[ 3   ] = XR__[3] - XL__[3];
    result__[ 4   ] = XR__[4] - XL__[4];
    real_type t12  = ALIAS_Kappa_R(QR__[0]);
    real_type t13  = zeta__dot(t5, t3, t1, t12);
    real_type t17  = ALIAS_Kappa_L(QL__[0]);
    real_type t18  = zeta__dot(t6, t4, t2, t17);
    result__[ 5   ] = LR__[0] * t13 - LL__[0] * t18;
    result__[ 6   ] = LR__[1] * t13 - LL__[1] * t18;
    result__[ 7   ] = LR__[2] * t13 - LL__[2] * t18;
    result__[ 8   ] = LR__[4] * t13 - LL__[4] * t18;
    result__[ 9   ] = LR__[3] * t13 - LL__[3] * t18;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  PointMassCarModel_2::DjumpDxlp_numRows() const
  { return 10; }

  integer
  PointMassCarModel_2::DjumpDxlp_numCols() const
  { return 20; }

  integer
  PointMassCarModel_2::DjumpDxlp_nnz() const
  { return 50; }

  void
  PointMassCarModel_2::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
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

  void
  PointMassCarModel_2::DjumpDxlp_sparse(
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
    real_type t1   = XL__[2];
    real_type t2   = XL__[1];
    real_type t3   = XL__[0];
    real_type t5   = ALIAS_Kappa_L(QL__[0]);
    real_type t6   = zeta__dot_D_3(t1, t2, t3, t5);
    real_type t7   = LL__[0];
    result__[ 10  ] = -t7 * t6;
    real_type t9   = zeta__dot_D_2(t1, t2, t3, t5);
    result__[ 11  ] = -t9 * t7;
    real_type t11  = zeta__dot_D_1(t1, t2, t3, t5);
    result__[ 12  ] = -t7 * t11;
    real_type t13  = zeta__dot(t1, t2, t3, t5);
    result__[ 13  ] = -t13;
    real_type t14  = XR__[2];
    real_type t15  = XR__[1];
    real_type t16  = XR__[0];
    real_type t18  = ALIAS_Kappa_R(QR__[0]);
    real_type t19  = zeta__dot_D_3(t14, t15, t16, t18);
    real_type t20  = LR__[0];
    result__[ 14  ] = t20 * t19;
    real_type t21  = zeta__dot_D_2(t14, t15, t16, t18);
    result__[ 15  ] = t20 * t21;
    real_type t22  = zeta__dot_D_1(t14, t15, t16, t18);
    result__[ 16  ] = t20 * t22;
    result__[ 17  ] = zeta__dot(t14, t15, t16, t18);
    real_type t23  = LL__[1];
    result__[ 18  ] = -t23 * t6;
    result__[ 19  ] = -t23 * t9;
    result__[ 20  ] = -t23 * t11;
    result__[ 21  ] = result__[13];
    real_type t27  = LR__[1];
    result__[ 22  ] = t27 * t19;
    result__[ 23  ] = t27 * t21;
    result__[ 24  ] = t27 * t22;
    result__[ 25  ] = result__[17];
    real_type t28  = LL__[2];
    result__[ 26  ] = -t28 * t6;
    result__[ 27  ] = -t28 * t9;
    result__[ 28  ] = -t28 * t11;
    result__[ 29  ] = result__[21];
    real_type t32  = LR__[2];
    result__[ 30  ] = t32 * t19;
    result__[ 31  ] = t32 * t21;
    result__[ 32  ] = t32 * t22;
    result__[ 33  ] = result__[25];
    real_type t33  = LL__[4];
    result__[ 34  ] = -t33 * t6;
    result__[ 35  ] = -t33 * t9;
    result__[ 36  ] = -t33 * t11;
    result__[ 37  ] = result__[29];
    real_type t37  = LR__[4];
    result__[ 38  ] = t37 * t19;
    result__[ 39  ] = t37 * t21;
    result__[ 40  ] = t37 * t22;
    result__[ 41  ] = result__[33];
    real_type t38  = LL__[3];
    result__[ 42  ] = -t38 * t6;
    result__[ 43  ] = -t38 * t9;
    result__[ 44  ] = -t38 * t11;
    result__[ 45  ] = result__[37];
    real_type t42  = LR__[3];
    result__[ 46  ] = t42 * t19;
    result__[ 47  ] = t42 * t21;
    result__[ 48  ] = t42 * t22;
    result__[ 49  ] = result__[41];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlp_sparse", 50, i_segment_left, i_segment_right );
  }

}

// EOF: PointMassCarModel_2_Methods.cc
