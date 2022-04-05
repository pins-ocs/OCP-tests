/*-----------------------------------------------------------------------*\
 |  file: BangBangF_Methods_boundary_conditions.cc                       |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "BangBangF.hh"
#include "BangBangF_Pars.hh"

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
#endif

// map user defined functions and objects with macros
#define ALIAS_C1_constr_DD(__t1) C1_constr.DD( __t1)
#define ALIAS_C1_constr_D(__t1) C1_constr.D( __t1)
#define ALIAS_FControl_D_3(__t1, __t2, __t3) FControl.D_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2(__t1, __t2, __t3) FControl.D_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1(__t1, __t2, __t3) FControl.D_1( __t1, __t2, __t3)
#define ALIAS_FControl_D_3_3(__t1, __t2, __t3) FControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2_3(__t1, __t2, __t3) FControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2_2(__t1, __t2, __t3) FControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_3(__t1, __t2, __t3) FControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_2(__t1, __t2, __t3) FControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_1(__t1, __t2, __t3) FControl.D_1_1( __t1, __t2, __t3)


namespace BangBangFDefine {

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

  integer BangBangF::bc_numEqns() const { return 3; }

  void
  BangBangF::bc_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_x] - ModelPars[iM_x_i];
    result__[ 1   ] = XL__[iX_v] - ModelPars[iM_v_i];
    result__[ 2   ] = XR__[iX_v] - ModelPars[iM_v_f];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 3, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DbcDxxp_numRows() const { return 3; }
  integer BangBangF::DbcDxxp_numCols() const { return 4; }
  integer BangBangF::DbcDxxp_nnz()     const { return 3; }

  void
  BangBangF::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
  }


  void
  BangBangF::DbcDxxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 3, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::D2bcD2xxp_numRows() const { return 4; }
  integer BangBangF::D2bcD2xxp_numCols() const { return 4; }
  integer BangBangF::D2bcD2xxp_nnz()     const { return 0; }

  void
  BangBangF::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::D2bcD2xxp_sparse(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: BangBangF_Methods_boundary_conditions.cc
