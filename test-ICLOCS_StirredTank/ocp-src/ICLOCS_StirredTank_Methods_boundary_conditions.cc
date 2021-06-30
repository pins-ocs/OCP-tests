/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_boundary_conditions.cc              |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_DD(__t1) x2bound.DD( __t1)
#define ALIAS_x2bound_D(__t1) x2bound.D( __t1)
#define ALIAS_x1bound_DD(__t1) x1bound.DD( __t1)
#define ALIAS_x1bound_D(__t1) x1bound.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_StirredTankDefine {

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
  ICLOCS_StirredTank::boundaryConditions_numEqns() const
  { return 0; }

  void
  ICLOCS_StirredTank::boundaryConditions_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DboundaryConditionsDxxp_numRows() const
  { return 0; }

  integer
  ICLOCS_StirredTank::DboundaryConditionsDxxp_numCols() const
  { return 5; }

  integer
  ICLOCS_StirredTank::DboundaryConditionsDxxp_nnz() const
  { return 0; }

  void
  ICLOCS_StirredTank::DboundaryConditionsDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  ICLOCS_StirredTank::DboundaryConditionsDxxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::adjointBC_numEqns() const
  { return 5; }

  void
  ICLOCS_StirredTank::adjointBC_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = ModelPars[iM_w];
    result__[ 0   ] = 2 * (XL__[iX_x1] - ModelPars[iM_x1_i]) * t1 + LL__[iL_lambda1__xo];
    result__[ 1   ] = 2 * (XL__[iX_x2] - ModelPars[iM_x2_i]) * t1 + LL__[iL_lambda2__xo];
    result__[ 2   ] = 2 * (XR__[iX_x1] - ModelPars[iM_x1_f]) * t1 - LR__[iL_lambda1__xo];
    result__[ 3   ] = 2 * (XR__[iX_x2] - ModelPars[iM_x2_f]) * t1 - LR__[iL_lambda2__xo];
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 5, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DadjointBCDxxp_numRows() const
  { return 5; }

  integer
  ICLOCS_StirredTank::DadjointBCDxxp_numCols() const
  { return 5; }

  integer
  ICLOCS_StirredTank::DadjointBCDxxp_nnz() const
  { return 4; }

  void
  ICLOCS_StirredTank::DadjointBCDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  void
  ICLOCS_StirredTank::DadjointBCDxxp_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 2 * ModelPars[iM_w];
    result__[ 1   ] = result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 4, i_segment_left, i_segment_right );
  }
}

// EOF: ICLOCS_StirredTank_Methods_boundary_conditions.cc