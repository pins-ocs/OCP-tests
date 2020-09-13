/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods.cc                                       |
 |                                                                       |
 |  version: 1.0   date 13/9/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = XL__[0] - ModelPars[1];
    result__[ 1   ] = XL__[1];
    result__[ 2   ] = XL__[2] - ModelPars[4];
    result__[ 3   ] = XL__[3];
    result__[ 4   ] = XL__[4] - ModelPars[6];
    result__[ 5   ] = XR__[3];
    real_type t12  = sqrt(ModelPars[3] / XR__[2]);
    result__[ 6   ] = XR__[4] - t12;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",7);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DboundaryConditionsDx_numRows() const
  { return 7; }

  integer
  OrbitTransfer::DboundaryConditionsDx_numCols() const
  { return 10; }

  integer
  OrbitTransfer::DboundaryConditionsDx_nnz() const
  { return 8; }

  void
  OrbitTransfer::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 4   ; jIndex[ 4  ] = 4   ;
    iIndex[ 5  ] = 5   ; jIndex[ 5  ] = 8   ;
    iIndex[ 6  ] = 6   ; jIndex[ 6  ] = 7   ;
    iIndex[ 7  ] = 6   ; jIndex[ 7  ] = 9   ;
  }

  void
  OrbitTransfer::DboundaryConditionsDx_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    real_type t1   = ModelPars[3];
    real_type t2   = XR__[2];
    real_type t5   = sqrt(1.0 / t2 * t1);
    real_type t8   = t2 * t2;
    result__[ 6   ] = 1.0 / t8 * t1 / t5 / 2;
    result__[ 7   ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",8);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DboundaryConditionsDp_numRows() const
  { return 7; }

  integer
  OrbitTransfer::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  OrbitTransfer::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

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
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = OMEGA__[0] + LL__[3];
    result__[ 1   ] = OMEGA__[1] + LL__[4];
    result__[ 2   ] = OMEGA__[2] + LL__[0];
    result__[ 3   ] = OMEGA__[3] + LL__[1];
    result__[ 4   ] = OMEGA__[4] + LL__[2];
    result__[ 5   ] = -LR__[3];
    result__[ 6   ] = -LR__[4];
    real_type t13  = OMEGA__[6];
    real_type t14  = ModelPars[3];
    real_type t15  = XR__[2];
    real_type t18  = sqrt(1.0 / t15 * t14);
    real_type t21  = t15 * t15;
    result__[ 7   ] = -1 + 1.0 / t21 * t14 / t18 * t13 / 2 - LR__[0];
    result__[ 8   ] = OMEGA__[5] - LR__[1];
    result__[ 9   ] = t13 - LR__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",10);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DadjointBCDx_numRows() const
  { return 10; }

  integer
  OrbitTransfer::DadjointBCDx_numCols() const
  { return 10; }

  integer
  OrbitTransfer::DadjointBCDx_nnz() const
  { return 1; }

  void
  OrbitTransfer::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 7   ; jIndex[ 0  ] = 7   ;
  }

  void
  OrbitTransfer::DadjointBCDx_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type t1   = OMEGA__[6];
    real_type t2   = ModelPars[3];
    real_type t3   = XR__[2];
    real_type t5   = 1.0 / t3 * t2;
    real_type t6   = sqrt(t5);
    real_type t10  = t2 * t2;
    real_type t11  = t3 * t3;
    real_type t12  = t11 * t11;
    result__[ 0   ] = 1.0 / t12 * t10 / t6 / t5 * t1 / 4 - 1.0 / t11 / t3 * t2 / t6 * t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DadjointBCDxp_sparse",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DadjointBCDp_numRows() const
  { return 10; }

  integer
  OrbitTransfer::DadjointBCDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DadjointBCDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  OrbitTransfer::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: OrbitTransfer_Methods.cc
