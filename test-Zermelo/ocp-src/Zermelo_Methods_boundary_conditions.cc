/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_boundary_conditions.cc                         |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace ZermeloDefine {

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
  Zermelo::boundaryConditions_numEqns() const
  { return 7; }

  void
  Zermelo::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_x];
    result__[ 1   ] = XL__[iX_y];
    result__[ 2   ] = XL__[iX_vx];
    result__[ 3   ] = XL__[iX_vy];
    result__[ 4   ] = XR__[iX_y] - 5;
    result__[ 5   ] = XR__[iX_vx] - 45;
    result__[ 6   ] = XR__[iX_vy];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 7, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DboundaryConditionsDx_numRows() const
  { return 7; }

  integer
  Zermelo::DboundaryConditionsDx_numCols() const
  { return 10; }

  integer
  Zermelo::DboundaryConditionsDx_nnz() const
  { return 7; }

  void
  Zermelo::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 8   ;
  }

  void
  Zermelo::DboundaryConditionsDx_sparse(
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
    result__[ 6   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxp_sparse", 7, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DboundaryConditionsDp_numRows() const
  { return 7; }

  integer
  Zermelo::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  Zermelo::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  Zermelo::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  Zermelo::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::adjointBC_numEqns() const
  { return 10; }

  void
  Zermelo::adjointBC_eval(
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
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda3__xo];
    result__[ 3   ] = OMEGA__[3] + LL__[iL_lambda4__xo];
    result__[ 4   ] = LL__[iL_lambda5__xo];
    result__[ 5   ] = -LR__[iL_lambda1__xo];
    result__[ 6   ] = OMEGA__[4] - LR__[iL_lambda2__xo];
    result__[ 7   ] = OMEGA__[5] - LR__[iL_lambda3__xo];
    result__[ 8   ] = OMEGA__[6] - LR__[iL_lambda4__xo];
    result__[ 9   ] = 1 - LR__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DadjointBCDx_numRows() const
  { return 10; }

  integer
  Zermelo::DadjointBCDx_numCols() const
  { return 10; }

  integer
  Zermelo::DadjointBCDx_nnz() const
  { return 0; }

  void
  Zermelo::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  Zermelo::DadjointBCDx_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DadjointBCDp_numRows() const
  { return 10; }

  integer
  Zermelo::DadjointBCDp_numCols() const
  { return 0; }

  integer
  Zermelo::DadjointBCDp_nnz() const
  { return 0; }

  void
  Zermelo::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  Zermelo::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Zermelo_Methods_boundary_conditions.cc
