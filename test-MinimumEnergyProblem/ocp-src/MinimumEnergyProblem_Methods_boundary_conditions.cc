/*-----------------------------------------------------------------------*\
 |  file: MinimumEnergyProblem_Methods_boundary_conditions.cc            |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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


#include "MinimumEnergyProblem.hh"
#include "MinimumEnergyProblem_Pars.hh"

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
#define ALIAS_x1Limitation_DD(__t1) x1Limitation.DD( __t1)
#define ALIAS_x1Limitation_D(__t1) x1Limitation.D( __t1)


namespace MinimumEnergyProblemDefine {

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
  MinimumEnergyProblem::boundaryConditions_numEqns() const
  { return 4; }

  void
  MinimumEnergyProblem::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_x1] - ModelPars[iM_x1_i];
    result__[ 1   ] = XL__[iX_x2] - ModelPars[iM_x2_i];
    result__[ 2   ] = XR__[iX_x1] - ModelPars[iM_x1_f];
    result__[ 3   ] = XR__[iX_x2] - ModelPars[iM_x2_f];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumEnergyProblem::DboundaryConditionsDx_numRows() const
  { return 4; }

  integer
  MinimumEnergyProblem::DboundaryConditionsDx_numCols() const
  { return 4; }

  integer
  MinimumEnergyProblem::DboundaryConditionsDx_nnz() const
  { return 4; }

  void
  MinimumEnergyProblem::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  void
  MinimumEnergyProblem::DboundaryConditionsDx_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxp_sparse", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumEnergyProblem::DboundaryConditionsDp_numRows() const
  { return 4; }

  integer
  MinimumEnergyProblem::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  MinimumEnergyProblem::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  MinimumEnergyProblem::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  MinimumEnergyProblem::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumEnergyProblem::adjointBC_numEqns() const
  { return 4; }

  void
  MinimumEnergyProblem::adjointBC_eval(
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
    result__[ 2   ] = OMEGA__[2] - LR__[iL_lambda1__xo];
    result__[ 3   ] = OMEGA__[3] - LR__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumEnergyProblem::DadjointBCDx_numRows() const
  { return 4; }

  integer
  MinimumEnergyProblem::DadjointBCDx_numCols() const
  { return 4; }

  integer
  MinimumEnergyProblem::DadjointBCDx_nnz() const
  { return 0; }

  void
  MinimumEnergyProblem::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  MinimumEnergyProblem::DadjointBCDx_sparse(
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
  MinimumEnergyProblem::DadjointBCDp_numRows() const
  { return 4; }

  integer
  MinimumEnergyProblem::DadjointBCDp_numCols() const
  { return 0; }

  integer
  MinimumEnergyProblem::DadjointBCDp_nnz() const
  { return 0; }

  void
  MinimumEnergyProblem::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  MinimumEnergyProblem::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: MinimumEnergyProblem_Methods_boundary_conditions.cc
