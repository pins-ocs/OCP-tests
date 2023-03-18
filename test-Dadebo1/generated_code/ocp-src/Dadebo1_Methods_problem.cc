/*-----------------------------------------------------------------------*\
 |  file: Dadebo1_Methods_problem.cc                                     |
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


#include "Dadebo1.hh"
#include "Dadebo1_Pars.hh"

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


namespace Dadebo1Define {

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  Dadebo1::H_eval(
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
    real_type t2   = U__[iU_u];
    real_type t5   = t2 * t2;
    real_type t7   = X__[iX_x] * X__[iX_x];
    real_type result__ = t2 * MU__[0] + (t5 + t7) * MU__[1];
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
  Dadebo1::lagrange_target(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
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
  Dadebo1::mayer_target(
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
    real_type result__ = XR__[iX_y];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Dadebo1::DmayerDxxp_numEqns() const { return 4; }

  void
  Dadebo1::DmayerDxxp_eval(
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
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Dadebo1::D2mayerD2xxp_numRows() const { return 4; }
  integer Dadebo1::D2mayerD2xxp_numCols() const { return 4; }
  integer Dadebo1::D2mayerD2xxp_nnz()     const { return 0; }

  void
  Dadebo1::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Dadebo1::D2mayerD2xxp_sparse(
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

  integer Dadebo1::DlagrangeDxpu_numEqns() const { return 3; }

  void
  Dadebo1::DlagrangeDxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Dadebo1::D2lagrangeD2xpu_numRows() const { return 3; }
  integer Dadebo1::D2lagrangeD2xpu_numCols() const { return 3; }
  integer Dadebo1::D2lagrangeD2xpu_nnz()     const { return 0; }

  void
  Dadebo1::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Dadebo1::D2lagrangeD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  Dadebo1::q_numEqns() const
  { return 1; }

  void
  Dadebo1::q_eval(
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

  integer Dadebo1::segmentLink_numEqns() const { return 0; }

  void
  Dadebo1::segmentLink_eval(
    NodeQX const & L,
    NodeQX const & R,
    P_const_p_type p,
    real_ptr        segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Dadebo1::DsegmentLinkDxxp_numRows() const { return 0; }
  integer Dadebo1::DsegmentLinkDxxp_numCols() const { return 0; }
  integer Dadebo1::DsegmentLinkDxxp_nnz() const { return 0; }

  void
  Dadebo1::DsegmentLinkDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Dadebo1::DsegmentLinkDxxp_sparse(
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

  integer Dadebo1::jump_numEqns() const { return 4; }

  void
  Dadebo1::jump_eval(
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
    result__[ 0   ] = XR__[iX_x] - XL__[iX_x];
    result__[ 1   ] = XR__[iX_y] - XL__[iX_y];
    result__[ 2   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 3   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Dadebo1::DjumpDxlxlp_numRows() const { return 4; }
  integer Dadebo1::DjumpDxlxlp_numCols() const { return 8; }
  integer Dadebo1::DjumpDxlxlp_nnz()     const { return 8; }

  void
  Dadebo1::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  Dadebo1::DjumpDxlxlp_sparse(
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

  integer Dadebo1::post_numEqns() const { return 0; }

  void
  Dadebo1::post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Dadebo1::integrated_post_numEqns() const { return 0; }

  void
  Dadebo1::integrated_post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

}

// EOF: Dadebo1_Methods_problem.cc
