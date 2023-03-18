/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_problem.cc                             |
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


#include "ForwardBackward.hh"
#include "ForwardBackward_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Path2D;


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
#define ALIAS_theta_DD(__t1) pTrajectory -> heading_DD( __t1)
#define ALIAS_theta_D(__t1) pTrajectory -> heading_D( __t1)
#define ALIAS_theta(__t1) pTrajectory -> heading( __t1)
#define ALIAS_yLane_DD(__t1) pTrajectory -> y_trajectory_DD( __t1)
#define ALIAS_yLane_D(__t1) pTrajectory -> y_trajectory_D( __t1)
#define ALIAS_yLane(__t1) pTrajectory -> y_trajectory( __t1)
#define ALIAS_xLane_DD(__t1) pTrajectory -> x_trajectory_DD( __t1)
#define ALIAS_xLane_D(__t1) pTrajectory -> x_trajectory_D( __t1)
#define ALIAS_xLane(__t1) pTrajectory -> x_trajectory( __t1)
#define ALIAS_kappa_DD(__t1) pTrajectory -> curvature_DD( __t1)
#define ALIAS_kappa_D(__t1) pTrajectory -> curvature_D( __t1)
#define ALIAS_kappa(__t1) pTrajectory -> curvature( __t1)
#define ALIAS_LimitE_DD(__t1) LimitE.DD( __t1)
#define ALIAS_LimitE_D(__t1) LimitE.D( __t1)
#define ALIAS_LimitA_max_DD(__t1) LimitA_max.DD( __t1)
#define ALIAS_LimitA_max_D(__t1) LimitA_max.D( __t1)
#define ALIAS_LimitA_min_DD(__t1) LimitA_min.DD( __t1)
#define ALIAS_LimitA_min_D(__t1) LimitA_min.D( __t1)
#define ALIAS_LimitV_max_DD(__t1) LimitV_max.DD( __t1)
#define ALIAS_LimitV_max_D(__t1) LimitV_max.D( __t1)
#define ALIAS_LimitV_min_DD(__t1) LimitV_min.DD( __t1)
#define ALIAS_LimitV_min_D(__t1) LimitV_min.D( __t1)


namespace ForwardBackwardDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ForwardBackward::continuation_step_1( real_type s ) {
    real_type t2   = 1 - s;
    ModelPars[iM_c0] = ModelPars[iM_c0_1] * s + t2 * ModelPars[iM_c0_0];
    ModelPars[iM_c1] = ModelPars[iM_c1_1] * s + t2 * ModelPars[iM_c1_0];
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ForwardBackward::continuation_step_2( real_type s ) {
    real_type t2   = 1 - s;
    LimitE.update_epsilon(ModelPars[iM_E_epsi1] * s + t2 * ModelPars[iM_E_epsi0]);
    LimitE.update_tolerance(ModelPars[iM_E_tol1] * s + t2 * ModelPars[iM_E_tol0]);
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ForwardBackward::continuation_step_3( real_type s ) {
    ModelPars[iM_epsilon] = ModelPars[iM_epsilon0] * (1 - s) + ModelPars[iM_epsilon1] * s;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ForwardBackward::H_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t3   = 1.0 / t2;
    real_type t6   = U__[iU_a];
    real_type t7   = t6 * t6;
    real_type result__ = t3 * ModelPars[iM_wT] + t7 * ModelPars[iM_epsilon] + (-t2 * ModelPars[iM_c1] + t3 * t6 - ModelPars[iM_c0]) * MU__[0];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "H_eval(...) return {}\n", result__ );
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
  ForwardBackward::lagrange_target(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    real_type t7   = U__[iU_a] * U__[iU_a];
    real_type result__ = ModelPars[iM_wT] / X__[iX_v] + t7 * ModelPars[iM_epsilon];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "lagrange_target(...) return {}\n", result__ );
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
  ForwardBackward::mayer_target(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    Path2D::SegmentClass const & segmentLeft  = m_pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = m_pTrajectory->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::DmayerDxxp_numEqns() const { return 2; }

  void
  ForwardBackward::DmayerDxxp_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    Path2D::SegmentClass const & segmentLeft  = m_pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = m_pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2mayerD2xxp_numRows() const { return 2; }
  integer ForwardBackward::D2mayerD2xxp_numCols() const { return 2; }
  integer ForwardBackward::D2mayerD2xxp_nnz()     const { return 0; }

  void
  ForwardBackward::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::D2mayerD2xxp_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
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

  integer ForwardBackward::DlagrangeDxpu_numEqns() const { return 2; }

  void
  ForwardBackward::DlagrangeDxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_v] * X__[iX_v];
    result__[ 0   ] = -1.0 / t3 * ModelPars[iM_wT];
    result__[ 1   ] = 2 * ModelPars[iM_epsilon] * U__[iU_a];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2lagrangeD2xpu_numRows() const { return 2; }
  integer ForwardBackward::D2lagrangeD2xpu_numCols() const { return 2; }
  integer ForwardBackward::D2lagrangeD2xpu_nnz()     const { return 2; }

  void
  ForwardBackward::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  ForwardBackward::D2lagrangeD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t3   = t2 * t2;
    result__[ 0   ] = 2 / t3 / t2 * ModelPars[iM_wT];
    result__[ 1   ] = 2 * ModelPars[iM_epsilon];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xpu_eval", 2, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ForwardBackward::q_numEqns() const
  { return 1; }

  void
  ForwardBackward::q_eval(
    integer   i_segment,
    real_type s,
    Q_p_type  result__
  ) const {
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer ForwardBackward::segmentLink_numEqns() const { return 0; }

  void
  ForwardBackward::segmentLink_eval(
    NodeQX const & L,
    NodeQX const & R,
    P_const_p_type p,
    real_ptr        segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::DsegmentLinkDxxp_numRows() const { return 0; }
  integer ForwardBackward::DsegmentLinkDxxp_numCols() const { return 0; }
  integer ForwardBackward::DsegmentLinkDxxp_nnz() const { return 0; }

  void
  ForwardBackward::DsegmentLinkDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DsegmentLinkDxxp_sparse(
    NodeQX const & L,
    NodeQX const & R,
    P_const_p_type p,
    real_ptr       DsegmentLinkDxxp
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

  integer ForwardBackward::jump_numEqns() const { return 2; }

  void
  ForwardBackward::jump_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    real_ptr        result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    Path2D::SegmentClass const & segmentLeft  = m_pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = m_pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XR__[iX_v] - XL__[iX_v];
    result__[ 1   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DjumpDxlxlp_numRows() const { return 2; }
  integer ForwardBackward::DjumpDxlxlp_numCols() const { return 4; }
  integer ForwardBackward::DjumpDxlxlp_nnz()     const { return 4; }

  void
  ForwardBackward::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DjumpDxlxlp_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    real_ptr        result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    Path2D::SegmentClass const & segmentLeft  = m_pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = m_pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 4, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer ForwardBackward::post_numEqns() const { return 13; }

  void
  ForwardBackward::post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    result__[ 0   ] = LimitV_min(ModelPars[iM_v_min] - t2);
    result__[ 1   ] = LimitV_max(t2 - ModelPars[iM_v_max]);
    real_type t7   = U__[iU_a];
    result__[ 2   ] = LimitA_min(ModelPars[iM_a_min] - t7);
    result__[ 3   ] = LimitA_max(t7 - ModelPars[iM_a_max]);
    real_type t12  = t7 * t7;
    real_type t14  = Q__[iQ_zeta];
    real_type t15  = ALIAS_kappa(t14);
    real_type t16  = t15 * t15;
    real_type t17  = t2 * t2;
    real_type t18  = t17 * t17;
    real_type t20  = t12 * ModelPars[iM_WA] + t18 * t16;
    real_type t21  = ModelPars[iM_E_max];
    real_type t22  = t21 * t21;
    result__[ 4   ] = LimitE(1.0 / t22 * t20 - 1);
    result__[ 5   ] = t15;
    result__[ 6   ] = ALIAS_xLane(t14);
    result__[ 7   ] = ALIAS_yLane(t14);
    result__[ 8   ] = ALIAS_theta(t14);
    result__[ 9   ] = -t17 * ModelPars[iM_c1] - t2 * ModelPars[iM_c0] + t7;
    result__[ 10  ] = t17 * result__[5];
    result__[ 11  ] = sqrt(t20);
    result__[ 12  ] = t21;
    // do not check
    // Mechatronix::check_in_segment( result__, "post_eval", 13, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::integrated_post_numEqns() const { return 1; }

  void
  ForwardBackward::integrated_post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    Path2D::SegmentClass const & segment = m_pTrajectory->get_segment_by_index(i_segment);
    result__[ 0   ] = 1.0 / X__[iX_v];
    // do not check
    // Mechatronix::check_in_segment( result__, "integrated_post_eval", 1, i_segment );
  }

}

// EOF: ForwardBackward_Methods_problem.cc
