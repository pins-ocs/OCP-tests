/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Methods.cc                                     |
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


#include "BangBangFmodule.hh"
#include "BangBangFmodule_Pars.hh"

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

// map user defined functions and objects with macros
#define ALIAS_controlM_D_3(__t1, __t2, __t3) controlM.D_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2(__t1, __t2, __t3) controlM.D_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1(__t1, __t2, __t3) controlM.D_1( __t1, __t2, __t3)
#define ALIAS_controlM_D_3_3(__t1, __t2, __t3) controlM.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2_3(__t1, __t2, __t3) controlM.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2_2(__t1, __t2, __t3) controlM.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_3(__t1, __t2, __t3) controlM.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_2(__t1, __t2, __t3) controlM.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_1(__t1, __t2, __t3) controlM.D_1_1( __t1, __t2, __t3)
#define ALIAS_controlP_D_3(__t1, __t2, __t3) controlP.D_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2(__t1, __t2, __t3) controlP.D_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1(__t1, __t2, __t3) controlP.D_1( __t1, __t2, __t3)
#define ALIAS_controlP_D_3_3(__t1, __t2, __t3) controlP.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2_3(__t1, __t2, __t3) controlP.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2_2(__t1, __t2, __t3) controlP.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_3(__t1, __t2, __t3) controlP.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_2(__t1, __t2, __t3) controlP.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_1(__t1, __t2, __t3) controlP.D_1_1( __t1, __t2, __t3)


namespace BangBangFmoduleDefine {

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
  BangBangFmodule::boundaryConditions_numEqns() const
  { return 4; }

  void
  BangBangFmodule::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[0];
    result__[ 1   ] = XL__[1];
    result__[ 2   ] = XR__[0] - 1;
    result__[ 3   ] = XR__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"boundaryConditions_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  BangBangFmodule::DboundaryConditionsDx_numRows() const
  { return 4; }

  integer
  BangBangFmodule::DboundaryConditionsDx_numCols() const
  { return 4; }

  integer
  BangBangFmodule::DboundaryConditionsDx_nnz() const
  { return 4; }

  void
  BangBangFmodule::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
  }

  void
  BangBangFmodule::DboundaryConditionsDx_sparse(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DboundaryConditionsDxp_sparse",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  BangBangFmodule::DboundaryConditionsDp_numRows() const
  { return 4; }

  integer
  BangBangFmodule::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  BangBangFmodule::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFmodule::adjointBC_numEqns() const
  { return 4; }

  void
  BangBangFmodule::adjointBC_eval(
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
    result__[ 2   ] = OMEGA__[2] - LR__[0];
    result__[ 3   ] = OMEGA__[3] - LR__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"adjointBC_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer
  BangBangFmodule::DadjointBCDx_numRows() const
  { return 4; }

  integer
  BangBangFmodule::DadjointBCDx_numCols() const
  { return 4; }

  integer
  BangBangFmodule::DadjointBCDx_nnz() const
  { return 0; }

  void
  BangBangFmodule::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  BangBangFmodule::DadjointBCDx_sparse(
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
  BangBangFmodule::DadjointBCDp_numRows() const
  { return 4; }

  integer
  BangBangFmodule::DadjointBCDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DadjointBCDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  BangBangFmodule::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFmodule_Methods.cc
