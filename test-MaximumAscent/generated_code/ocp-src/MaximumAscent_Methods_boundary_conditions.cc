/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods_boundary_conditions.cc                   |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {

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

  integer MaximumAscent::boundaryConditions_numEqns() const { return 6; }

  void
  MaximumAscent::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_r] - ModelPars[iM_r0_bar];
    result__[ 1   ] = XL__[iX_u] - ModelPars[iM_u0_bar];
    result__[ 2   ] = XL__[iX_v] - ModelPars[iM_v0_bar];
    result__[ 3   ] = XL__[iX_theta] - ModelPars[iM_theta0];
    result__[ 4   ] = XR__[iX_u] - ModelPars[iM_uf_bar];
    real_type t13  = sqrt(XR__[iX_r]);
    result__[ 5   ] = t13 * XR__[iX_v] - 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DbcDxxp_numRows() const { return 6; }
  integer MaximumAscent::DbcDxxp_numCols() const { return 8; }
  integer MaximumAscent::DbcDxxp_nnz()     const { return 7; }

  void
  MaximumAscent::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 6   ;
  }


  void
  MaximumAscent::DbcDxxp_sparse(
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
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    real_type t3   = sqrt(XR__[iX_r]);
    result__[ 5   ] = 1.0 / t3 * XR__[iX_v] / 2;
    result__[ 6   ] = t3;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 7, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::D2bcD2xxp_numRows() const { return 8; }
  integer MaximumAscent::D2bcD2xxp_numCols() const { return 8; }
  integer MaximumAscent::D2bcD2xxp_nnz()     const { return 3; }

  void
  MaximumAscent::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 6   ; jIndex[2 ] = 4   ;
  }


  void
  MaximumAscent::D2bcD2xxp_sparse(
    NodeType const         & LEFT__,
    NodeType const         & RIGHT__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type OMEGA__,
    real_type                result__[]
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
    real_type t3   = sqrt(XR__[iX_r]);
    result__[ 5   ] = 1.0 / t3 * XR__[iX_v] / 2;
    result__[ 6   ] = t3;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "D2bcD2xxp_sparse", 3, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::adjointBC_numEqns() const { return 8; }

  void
  MaximumAscent::adjointBC_eval(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[0];
    result__[ 1   ] = OMEGA__[1];
    result__[ 2   ] = OMEGA__[2];
    result__[ 3   ] = OMEGA__[3];
    real_type t1   = OMEGA__[5];
    real_type t5   = sqrt(XR__[iX_r]);
    result__[ 4   ] = -1 + 1.0 / t5 * XR__[iX_v] * t1 / 2;
    result__[ 5   ] = OMEGA__[4];
    result__[ 6   ] = t5 * t1;
    result__[ 7   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DadjointBCDxxp_numRows() const { return 8; }
  integer MaximumAscent::DadjointBCDxxp_numCols() const { return 8; }
  integer MaximumAscent::DadjointBCDxxp_nnz()     const { return 3; }

  void
  MaximumAscent::DadjointBCDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 6   ; jIndex[2 ] = 4   ;
  }


  void
  MaximumAscent::DadjointBCDxxp_sparse(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = OMEGA__[5];
    real_type t4   = XR__[iX_r];
    real_type t5   = sqrt(t4);
    result__[ 0   ] = -1.0 / t5 / t4 * XR__[iX_v] * t1 / 4;
    result__[ 1   ] = 1.0 / t5 * t1 / 2;
    result__[ 2   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 3, i_segment_left, i_segment_right );
  }
}

// EOF: MaximumAscent_Methods_boundary_conditions.cc
