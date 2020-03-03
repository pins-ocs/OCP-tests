/*-----------------------------------------------------------------------*\
 |  file: MinimumFuelOrbitRaising_Methods.cc                             |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#include "MinimumFuelOrbitRaising.hh"
#include "MinimumFuelOrbitRaising_Pars.hh"

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


namespace MinimumFuelOrbitRaisingDefine {

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
  MinimumFuelOrbitRaising::boundaryConditions_numEqns() const
  { return 5; }

  void
  MinimumFuelOrbitRaising::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[0] - 1;
    result__[ 1   ] = XL__[1];
    result__[ 2   ] = XL__[2] - 1;
    result__[ 3   ] = XR__[1];
    real_type t5   = XR__[2] * XR__[2];
    result__[ 4   ] = t5 * XR__[0] - 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",5);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  MinimumFuelOrbitRaising::DboundaryConditionsDx_numRows() const
  { return 5; }

  integer
  MinimumFuelOrbitRaising::DboundaryConditionsDx_numCols() const
  { return 6; }

  integer
  MinimumFuelOrbitRaising::DboundaryConditionsDx_nnz() const
  { return 6; }

  void
  MinimumFuelOrbitRaising::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 4   ;
    iIndex[ 4  ] = 4   ; jIndex[ 4  ] = 3   ;
    iIndex[ 5  ] = 4   ; jIndex[ 5  ] = 5   ;
  }

  void
  MinimumFuelOrbitRaising::DboundaryConditionsDx_sparse(
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
    real_type t1   = XR__[2];
    result__[ 4   ] = t1 * t1;
    result__[ 5   ] = 2 * t1 * XR__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  MinimumFuelOrbitRaising::DboundaryConditionsDp_numRows() const
  { return 5; }

  integer
  MinimumFuelOrbitRaising::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  MinimumFuelOrbitRaising::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::adjointBC_numEqns() const
  { return 6; }

  void
  MinimumFuelOrbitRaising::adjointBC_eval(
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
    result__[ 0   ] = OMEGA__[0] + LL__[0];
    result__[ 1   ] = OMEGA__[1] + LL__[1];
    result__[ 2   ] = OMEGA__[2] + LL__[2];
    real_type t7   = OMEGA__[4];
    real_type t8   = XR__[2];
    real_type t9   = t8 * t8;
    result__[ 3   ] = t9 * t7 - LR__[0];
    result__[ 4   ] = OMEGA__[3] - LR__[1];
    result__[ 5   ] = 2 * t8 * XR__[0] * t7 - LR__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  MinimumFuelOrbitRaising::DadjointBCDx_numRows() const
  { return 6; }

  integer
  MinimumFuelOrbitRaising::DadjointBCDx_numCols() const
  { return 6; }

  integer
  MinimumFuelOrbitRaising::DadjointBCDx_nnz() const
  { return 3; }

  void
  MinimumFuelOrbitRaising::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 3   ; jIndex[ 0  ] = 5   ;
    iIndex[ 1  ] = 5   ; jIndex[ 1  ] = 3   ;
    iIndex[ 2  ] = 5   ; jIndex[ 2  ] = 5   ;
  }

  void
  MinimumFuelOrbitRaising::DadjointBCDx_sparse(
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
    real_type t1   = OMEGA__[4];
    result__[ 0   ] = 2 * XR__[2] * t1;
    result__[ 1   ] = result__[0];
    result__[ 2   ] = 2 * t1 * XR__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DadjointBCDxp_sparse",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  MinimumFuelOrbitRaising::DadjointBCDp_numRows() const
  { return 6; }

  integer
  MinimumFuelOrbitRaising::DadjointBCDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DadjointBCDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  MinimumFuelOrbitRaising::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: MinimumFuelOrbitRaising_Methods.cc
