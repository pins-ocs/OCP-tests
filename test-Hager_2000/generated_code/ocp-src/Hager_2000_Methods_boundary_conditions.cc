/*-----------------------------------------------------------------------*\
 |  file: Hager_2000_Methods_boundary_conditions.cc                      |
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


#include "Hager_2000.hh"
#include "Hager_2000_Pars.hh"

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


namespace Hager_2000Define {

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

  integer Hager_2000::bc_numEqns() const { return 1; }

  void
  Hager_2000::bc_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = m_pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = m_pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_x] - 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 1, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Hager_2000::DbcDxxp_numRows() const { return 1; }
  integer Hager_2000::DbcDxxp_numCols() const { return 2; }
  integer Hager_2000::DbcDxxp_nnz()     const { return 1; }

  void
  Hager_2000::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Hager_2000::DbcDxxp_sparse(
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
    result__[ 0   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 1, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Hager_2000::D2bcD2xxp_numRows() const { return 2; }
  integer Hager_2000::D2bcD2xxp_numCols() const { return 2; }
  integer Hager_2000::D2bcD2xxp_nnz()     const { return 0; }

  void
  Hager_2000::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Hager_2000::D2bcD2xxp_sparse(
    NodeQX const &          LEFT__,
    NodeQX const &          RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Hager_2000::fd_BC_numEqns() const { return 2; }

  void
  Hager_2000::fd_BC_eval(
    NodeQXL const &         LEFT__,
    NodeQXL const &         RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
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
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = -LR__[iL_lambda1__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "fd_BC_eval", 1, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Hager_2000::Dfd_BCDxlxlp_numRows() const { return 2; }
  integer Hager_2000::Dfd_BCDxlxlp_numCols() const { return 4; }
  integer Hager_2000::Dfd_BCDxlxlp_nnz()     const { return 2; }

  void
  Hager_2000::Dfd_BCDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
  }


  void
  Hager_2000::Dfd_BCDxlxlp_sparse(
    NodeQXL const &         LEFT__,
    NodeQXL const &         RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
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
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "Dfd_BCDxlxlp_sparse", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: Hager_2000_Methods_boundary_conditions.cc
