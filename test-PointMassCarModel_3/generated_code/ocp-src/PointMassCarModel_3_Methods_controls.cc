/*-----------------------------------------------------------------------*\
 |  file: PointMassCarModel_3_Methods_controls.cc                        |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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
#pragma warning( disable : 4189 )
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  PointMassCarModel_3::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t5   = U__[iU_v__fx];
    real_type t6   = v__fxControl(t5, -1, 1);
    real_type t8   = U__[iU_v__Omega];
    real_type t9   = v__OmegaControl(t8, -1, 1);
    real_type t11  = X__[iX_fx];
    real_type t12  = t11 * t11;
    real_type t14  = ModelPars[iM_mu__x__max] * ModelPars[iM_mu__x__max];
    real_type t18  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t19  = 1.0 / t18;
    real_type t21  = X__[iX_Omega];
    real_type t22  = t21 * t21;
    real_type t23  = X__[iX_V];
    real_type t24  = t23 * t23;
    real_type t27  = ModelPars[iM_mu__y__max] * ModelPars[iM_mu__y__max];
    real_type t32  = AdherenceEllipse(t19 / t14 * t12 + t19 / t27 * t24 * t22 - 1);
    real_type t34  = X__[iX_n];
    real_type t35  = X__[iX_s];
    real_type t36  = ALIAS_leftWidth(t35);
    real_type t38  = RoadLeftBorder(t34 - t36);
    real_type t40  = ALIAS_rightWidth(t35);
    real_type t42  = RoadRightBorder(-t34 - t40);
    real_type t51  = PowerLimit(ModelPars[iM_m] / ModelPars[iM_Pmax] * t11 * t23 - 1);
    real_type t54  = X__[iX_alpha];
    real_type t55  = ALIAS_Kappa(t35);
    real_type t56  = zeta__dot(t23, t54, t34, t55);
    real_type t61  = sin(t54);
    real_type result__ = t3 * ModelPars[iM_wT] + t6 * t3 + t9 * t3 + t32 * t3 + t38 * t3 + t42 * t3 + t51 * t3 + t3 * t56 * MU__[0] + t3 * t61 * t23 * MU__[1] + (-t55 * t56 + t21) * t3 * MU__[2] + (-t24 * ModelPars[iM_kD] + t11) * t3 * MU__[3] + t3 * ModelPars[iM_v__Omega__max] * t8 * MU__[4] + t3 * ModelPars[iM_v__fx__max] * t5 * MU__[5];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer PointMassCarModel_3::g_numEqns() const { return 2; }

  void
  PointMassCarModel_3::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t4   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t2 * ModelPars[iM_v__fx__max] * MU__[5] + t4 * t2;
    real_type t11  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t2 * ModelPars[iM_v__Omega__max] * MU__[4] + t11 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DgDxpm_numRows() const { return 2; }
  integer PointMassCarModel_3::DgDxpm_numCols() const { return 14; }
  integer PointMassCarModel_3::DgDxpm_nnz()     const { return 4; }

  void
  PointMassCarModel_3::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 12  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 11  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_sqrt_inv_Vseg];
    real_type t3   = ALIAS_v__fxControl_D_1(U__[iU_v__fx], -1, 1);
    real_type t6   = ModelPars[iM_v__fx__max];
    result__[ 0   ] = 2 * t1 * t6 * MU__[5] + 2 * t3 * t1;
    real_type t10  = t1 * t1;
    result__[ 1   ] = t10 * t6;
    real_type t12  = ALIAS_v__OmegaControl_D_1(U__[iU_v__Omega], -1, 1);
    real_type t15  = ModelPars[iM_v__Omega__max];
    result__[ 2   ] = 2 * t1 * t15 * MU__[4] + 2 * t12 * t1;
    result__[ 3   ] = t10 * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer PointMassCarModel_3::DgDu_numRows() const { return 2; }
  integer PointMassCarModel_3::DgDu_numCols() const { return 2; }
  integer PointMassCarModel_3::DgDu_nnz()     const { return 2; }

  void
  PointMassCarModel_3::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  PointMassCarModel_3::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_sqrt_inv_Vseg] * X__[iX_sqrt_inv_Vseg];
    real_type t4   = ALIAS_v__fxControl_D_1_1(U__[iU_v__fx], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = ALIAS_v__OmegaControl_D_1_1(U__[iU_v__Omega], -1, 1);
    result__[ 1   ] = t6 * t2;
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
  PointMassCarModel_3::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    integer i_segment = NODE__.i_segment;
    Road2D::SegmentClass const & segment = m_pRoad->get_segment_by_index(i_segment);
    U__[ iU_v__fx    ] = v__OmegaControl.solve(-MU__[5] * ModelPars[iM_v__fx__max], -1, 1);
    U__[ iU_v__Omega ] = v__OmegaControl.solve(-MU__[4] * ModelPars[iM_v__Omega__max], -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

}

// EOF: PointMassCarModel_3_Methods_controls.cc
