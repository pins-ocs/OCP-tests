/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_boundary_conditions.cc                 |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

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
#define ALIAS_LowBound_DD(__t1) LowBound.DD( __t1)
#define ALIAS_LowBound_D(__t1) LowBound.D( __t1)
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


namespace BrachiostocronaDefine {

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

  integer Brachiostocrona::bc_numEqns() const { return 5; }

  void
  Brachiostocrona::bc_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_x];
    result__[ 1   ] = XL__[iX_y];
    result__[ 2   ] = XL__[iX_v];
    result__[ 3   ] = XR__[iX_x] - ModelPars[iM_xf];
    result__[ 4   ] = XR__[iX_y] - ModelPars[iM_yf];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 5, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DbcDxxp_numRows() const { return 5; }
  integer Brachiostocrona::DbcDxxp_numCols() const { return 9; }
  integer Brachiostocrona::DbcDxxp_nnz()     const { return 5; }

  void
  Brachiostocrona::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 5   ;
  }


  void
  Brachiostocrona::DbcDxxp_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 5, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::D2bcD2xxp_numRows() const { return 9; }
  integer Brachiostocrona::D2bcD2xxp_numCols() const { return 9; }
  integer Brachiostocrona::D2bcD2xxp_nnz()     const { return 0; }

  void
  Brachiostocrona::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Brachiostocrona::D2bcD2xxp_sparse(
    NodeQX const &          LEFT__,
    NodeQX const &          RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::fd_BC_numEqns() const { return 8; }

  void
  Brachiostocrona::fd_BC_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda3__xo];
    result__[ 3   ] = LL__[iL_lambda4__xo];
    result__[ 4   ] = OMEGA__[3] - LR__[iL_lambda1__xo];
    result__[ 5   ] = OMEGA__[4] - LR__[iL_lambda2__xo];
    result__[ 6   ] = -LR__[iL_lambda3__xo];
    result__[ 7   ] = -LR__[iL_lambda4__xo];
    result__[ 8   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "fd_BC_eval", 5, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::Dfd_BCDxlxlp_numRows() const { return 9; }
  integer Brachiostocrona::Dfd_BCDxlxlp_numCols() const { return 17; }
  integer Brachiostocrona::Dfd_BCDxlxlp_nnz()     const { return 8; }

  void
  Brachiostocrona::Dfd_BCDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 12  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 15  ;
  }


  void
  Brachiostocrona::Dfd_BCDxlxlp_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = -1;
    result__[ 6   ] = -1;
    result__[ 7   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "Dfd_BCDxlxlp_sparse", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: Brachiostocrona_Methods_boundary_conditions.cc
