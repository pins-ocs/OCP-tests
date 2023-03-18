/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_boundary_conditions.cc                    |
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


#include "stirred_tank.hh"
#include "stirred_tank_Pars.hh"

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
#define ALIAS_u4Control_D_3(__t1, __t2, __t3) u4Control.D_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2(__t1, __t2, __t3) u4Control.D_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1(__t1, __t2, __t3) u4Control.D_1( __t1, __t2, __t3)
#define ALIAS_u4Control_D_3_3(__t1, __t2, __t3) u4Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_3(__t1, __t2, __t3) u4Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_2(__t1, __t2, __t3) u4Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_3(__t1, __t2, __t3) u4Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_2(__t1, __t2, __t3) u4Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_1(__t1, __t2, __t3) u4Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace stirred_tankDefine {

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

  integer stirred_tank::bc_numEqns() const { return 8; }

  void
  stirred_tank::bc_eval(
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
    result__[ 0   ] = XL__[iX_x1] - 0.1883e0;
    result__[ 1   ] = XL__[iX_x2] - 0.2507e0;
    result__[ 2   ] = XL__[iX_x3] - 0.467e-1;
    result__[ 3   ] = XL__[iX_x4] - 0.899e-1;
    result__[ 4   ] = XL__[iX_x5] - 0.1804e0;
    result__[ 5   ] = XL__[iX_x6] - 0.1394e0;
    result__[ 6   ] = XL__[iX_x7] - 0.1046e0;
    result__[ 7   ] = XL__[iX_x8];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DbcDxxp_numRows() const { return 8; }
  integer stirred_tank::DbcDxxp_numCols() const { return 16; }
  integer stirred_tank::DbcDxxp_nnz()     const { return 8; }

  void
  stirred_tank::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
  }


  void
  stirred_tank::DbcDxxp_sparse(
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
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::D2bcD2xxp_numRows() const { return 16; }
  integer stirred_tank::D2bcD2xxp_numCols() const { return 16; }
  integer stirred_tank::D2bcD2xxp_nnz()     const { return 0; }

  void
  stirred_tank::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::D2bcD2xxp_sparse(
    NodeQX const &          LEFT__,
    NodeQX const &          RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::fd_BC_numEqns() const { return 16; }

  void
  stirred_tank::fd_BC_eval(
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
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda3__xo];
    result__[ 3   ] = OMEGA__[3] + LL__[iL_lambda4__xo];
    result__[ 4   ] = OMEGA__[4] + LL__[iL_lambda5__xo];
    result__[ 5   ] = OMEGA__[5] + LL__[iL_lambda6__xo];
    result__[ 6   ] = OMEGA__[6] + LL__[iL_lambda7__xo];
    result__[ 7   ] = OMEGA__[7] + LL__[iL_lambda8__xo];
    result__[ 8   ] = -LR__[iL_lambda1__xo];
    result__[ 9   ] = -LR__[iL_lambda2__xo];
    result__[ 10  ] = -LR__[iL_lambda3__xo];
    result__[ 11  ] = -LR__[iL_lambda4__xo];
    result__[ 12  ] = -LR__[iL_lambda5__xo];
    result__[ 13  ] = -LR__[iL_lambda6__xo];
    result__[ 14  ] = -LR__[iL_lambda7__xo];
    result__[ 15  ] = -1 - LR__[iL_lambda8__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "fd_BC_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::Dfd_BCDxlxlp_numRows() const { return 16; }
  integer stirred_tank::Dfd_BCDxlxlp_numCols() const { return 32; }
  integer stirred_tank::Dfd_BCDxlxlp_nnz()     const { return 16; }

  void
  stirred_tank::Dfd_BCDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 8   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 9   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 11  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 12  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 24  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 25  ;
    iIndex[10] = 10  ; jIndex[10] = 26  ;
    iIndex[11] = 11  ; jIndex[11] = 27  ;
    iIndex[12] = 12  ; jIndex[12] = 28  ;
    iIndex[13] = 13  ; jIndex[13] = 29  ;
    iIndex[14] = 14  ; jIndex[14] = 30  ;
    iIndex[15] = 15  ; jIndex[15] = 31  ;
  }


  void
  stirred_tank::Dfd_BCDxlxlp_sparse(
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
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = -1;
    result__[ 10  ] = -1;
    result__[ 11  ] = -1;
    result__[ 12  ] = -1;
    result__[ 13  ] = -1;
    result__[ 14  ] = -1;
    result__[ 15  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "Dfd_BCDxlxlp_sparse", 16, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: stirred_tank_Methods_boundary_conditions.cc
