/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_PathConstrained_Methods_problem.cc                      |
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


#include "ICLOCS_PathConstrained.hh"
#include "ICLOCS_PathConstrained_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


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
#define ALIAS_x2bound_DD(__t1) x2bound.DD( __t1)
#define ALIAS_x2bound_D(__t1) x2bound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_PathConstrainedDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_PathConstrained::continuation_step_1( real_type s ) {
    real_type t2   = 1 - s;
    real_type t3   = pow(ModelPars[iM_epsi_ctrl0], t2);
    real_type t5   = pow(ModelPars[iM_epsi_ctrl1], s);
    real_type t6   = t5 * t3;
    x2bound.update_epsilon(t6);
    real_type t8   = pow(ModelPars[iM_tol_ctrl0], t2);
    real_type t10  = pow(ModelPars[iM_tol_ctrl1], s);
    real_type t11  = t10 * t8;
    x2bound.update_tolerance(t11);
    uControl.update_epsilon(t6);
    uControl.update_tolerance(t11);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ICLOCS_PathConstrained::H_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u];
    real_type t2   = t1 * t1;
    real_type t5   = X__[iX_x1] * X__[iX_x1];
    real_type t6   = X__[iX_x2];
    real_type t7   = t6 * t6;
    real_type result__ = 0.5e-2 * t2 + t5 + t7 + t6 * MU__[0] + (-t6 + t1) * MU__[1];
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
  ICLOCS_PathConstrained::lagrange_target(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_u] * U__[iU_u];
    real_type t5   = X__[iX_x1] * X__[iX_x1];
    real_type t7   = X__[iX_x2] * X__[iX_x2];
    real_type result__ = 0.5e-2 * t2 + t5 + t7;
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
  ICLOCS_PathConstrained::mayer_target(
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
    MeshStd::SegmentClass const & segmentLeft  = m_pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = m_pMesh->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_PathConstrained::DmayerDxxp_numEqns() const { return 4; }

  void
  ICLOCS_PathConstrained::DmayerDxxp_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = m_pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = m_pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_PathConstrained::D2mayerD2xxp_numRows() const { return 4; }
  integer ICLOCS_PathConstrained::D2mayerD2xxp_numCols() const { return 4; }
  integer ICLOCS_PathConstrained::D2mayerD2xxp_nnz()     const { return 0; }

  void
  ICLOCS_PathConstrained::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_PathConstrained::D2mayerD2xxp_sparse(
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

  integer ICLOCS_PathConstrained::DlagrangeDxpu_numEqns() const { return 3; }

  void
  ICLOCS_PathConstrained::DlagrangeDxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 2 * X__[iX_x1];
    result__[ 1   ] = 2 * X__[iX_x2];
    result__[ 2   ] = 0.10e-1 * U__[iU_u];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_PathConstrained::D2lagrangeD2xpu_numRows() const { return 3; }
  integer ICLOCS_PathConstrained::D2lagrangeD2xpu_numCols() const { return 3; }
  integer ICLOCS_PathConstrained::D2lagrangeD2xpu_nnz()     const { return 3; }

  void
  ICLOCS_PathConstrained::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  void
  ICLOCS_PathConstrained::D2lagrangeD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 2;
    result__[ 1   ] = 2;
    result__[ 2   ] = 0.10e-1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xpu_eval", 3, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ICLOCS_PathConstrained::q_numEqns() const
  { return 1; }

  void
  ICLOCS_PathConstrained::q_eval(
    integer   i_segment,
    real_type s,
    Q_p_type  result__
  ) const {
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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

  integer ICLOCS_PathConstrained::segmentLink_numEqns() const { return 0; }

  void
  ICLOCS_PathConstrained::segmentLink_eval(
    NodeQX const & L,
    NodeQX const & R,
    P_const_p_type p,
    real_ptr        segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_PathConstrained::DsegmentLinkDxxp_numRows() const { return 0; }
  integer ICLOCS_PathConstrained::DsegmentLinkDxxp_numCols() const { return 0; }
  integer ICLOCS_PathConstrained::DsegmentLinkDxxp_nnz() const { return 0; }

  void
  ICLOCS_PathConstrained::DsegmentLinkDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_PathConstrained::DsegmentLinkDxxp_sparse(
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

  integer ICLOCS_PathConstrained::jump_numEqns() const { return 4; }

  void
  ICLOCS_PathConstrained::jump_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = m_pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = m_pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XR__[iX_x1] - XL__[iX_x1];
    result__[ 1   ] = XR__[iX_x2] - XL__[iX_x2];
    result__[ 2   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 3   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_PathConstrained::DjumpDxlxlp_numRows() const { return 4; }
  integer ICLOCS_PathConstrained::DjumpDxlxlp_numCols() const { return 8; }
  integer ICLOCS_PathConstrained::DjumpDxlxlp_nnz()     const { return 8; }

  void
  ICLOCS_PathConstrained::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_PathConstrained::DjumpDxlxlp_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = m_pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = m_pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 8, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer ICLOCS_PathConstrained::post_numEqns() const { return 2; }

  void
  ICLOCS_PathConstrained::post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = uControl(U__[iU_u], -20, 20);
    real_type t4   = pow(Q__[iQ_zeta] - 0.5e0, 2);
    result__[ 1   ] = x2bound(0.5e0 - 8 * t4 + X__[iX_x2]);
    // do not check
    // Mechatronix::check_in_segment( result__, "post_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_PathConstrained::integrated_post_numEqns() const { return 0; }

  void
  ICLOCS_PathConstrained::integrated_post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_PathConstrained_Methods_problem.cc
