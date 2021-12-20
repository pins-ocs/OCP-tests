/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_boundary_conditions.cc                   |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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


#include "OrbitTransfer.hh"
#include "OrbitTransfer_Pars.hh"

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


namespace OrbitTransferDefine {

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

  integer
  OrbitTransfer::boundaryConditions_numEqns() const
  { return 7; }

  void
  OrbitTransfer::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_m] - ModelPars[iM_m0];
    result__[ 1   ] = XL__[iX_alpha];
    result__[ 2   ] = XL__[iX_r] - ModelPars[iM_r0];
    result__[ 3   ] = XL__[iX_u];
    result__[ 4   ] = XL__[iX_v] - ModelPars[iM_v0];
    result__[ 5   ] = XR__[iX_u];
    real_type t12  = sqrt(ModelPars[iM_mu] / XR__[iX_r]);
    result__[ 6   ] = XR__[iX_v] - t12;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 7, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DboundaryConditionsDxxp_numRows() const
  { return 7; }

  integer
  OrbitTransfer::DboundaryConditionsDxxp_numCols() const
  { return 10; }

  integer
  OrbitTransfer::DboundaryConditionsDxxp_nnz() const
  { return 8; }

  void
  OrbitTransfer::DboundaryConditionsDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 6   ; jIndex[7 ] = 9   ;
  }

  void
  OrbitTransfer::DboundaryConditionsDxxp_sparse(
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
    result__[ 5   ] = 1;
    real_type t1   = ModelPars[iM_mu];
    real_type t2   = XR__[iX_r];
    real_type t5   = sqrt(1.0 / t2 * t1);
    real_type t8   = t2 * t2;
    result__[ 6   ] = 1.0 / t8 * t1 / t5 / 2;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxxp_sparse", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::adjointBC_numEqns() const
  { return 10; }

  void
  OrbitTransfer::adjointBC_eval(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
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
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda4__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda5__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda1__xo];
    result__[ 3   ] = OMEGA__[3] + LL__[iL_lambda2__xo];
    result__[ 4   ] = OMEGA__[4] + LL__[iL_lambda3__xo];
    result__[ 5   ] = -LR__[iL_lambda4__xo];
    result__[ 6   ] = -LR__[iL_lambda5__xo];
    real_type t13  = OMEGA__[6];
    real_type t14  = ModelPars[iM_mu];
    real_type t15  = XR__[iX_r];
    real_type t18  = sqrt(1.0 / t15 * t14);
    real_type t21  = t15 * t15;
    result__[ 7   ] = -1 + 1.0 / t21 * t14 / t18 * t13 / 2 - LR__[iL_lambda1__xo];
    result__[ 8   ] = OMEGA__[5] - LR__[iL_lambda2__xo];
    result__[ 9   ] = t13 - LR__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DadjointBCDxxp_numRows() const
  { return 10; }

  integer
  OrbitTransfer::DadjointBCDxxp_numCols() const
  { return 10; }

  integer
  OrbitTransfer::DadjointBCDxxp_nnz() const
  { return 1; }

  void
  OrbitTransfer::DadjointBCDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 7   ; jIndex[0 ] = 7   ;
  }

  void
  OrbitTransfer::DadjointBCDxxp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
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
    real_type t1   = OMEGA__[6];
    real_type t2   = ModelPars[iM_mu];
    real_type t3   = XR__[iX_r];
    real_type t5   = 1.0 / t3 * t2;
    real_type t6   = sqrt(t5);
    real_type t10  = t2 * t2;
    real_type t11  = t3 * t3;
    real_type t12  = t11 * t11;
    result__[ 0   ] = 1.0 / t12 * t10 / t6 / t5 * t1 / 4 - 1.0 / t11 / t3 * t2 / t6 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 1, i_segment_left, i_segment_right );
  }
}

// EOF: OrbitTransfer_Methods_boundary_conditions.cc
