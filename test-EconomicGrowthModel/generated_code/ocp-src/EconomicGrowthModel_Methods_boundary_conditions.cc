/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Methods_boundary_conditions.cc             |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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


#include "EconomicGrowthModel.hh"
#include "EconomicGrowthModel_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModelDefine {

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
  EconomicGrowthModel::boundaryConditions_numEqns() const
  { return 3; }

  void
  EconomicGrowthModel::boundaryConditions_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_x1] - ModelPars[iM_x1_i];
    result__[ 1   ] = XL__[iX_x2] - ModelPars[iM_x2_i];
    real_type t7   = Q(XR__[iX_x1], XR__[iX_x2]);
    result__[ 2   ] = t7 - ModelPars[iM_Qc];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 3, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DboundaryConditionsDx_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DboundaryConditionsDx_numCols() const
  { return 6; }

  integer
  EconomicGrowthModel::DboundaryConditionsDx_nnz() const
  { return 4; }

  void
  EconomicGrowthModel::DboundaryConditionsDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 4   ;
  }

  void
  EconomicGrowthModel::DboundaryConditionsDx_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    real_type t1   = XR__[iX_x1];
    real_type t2   = XR__[iX_x2];
    result__[ 2   ] = Q_D_1(t1, t2);
    result__[ 3   ] = Q_D_2(t1, t2);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxp_sparse", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DboundaryConditionsDp_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DboundaryConditionsDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DboundaryConditionsDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  void
  EconomicGrowthModel::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::adjointBC_numEqns() const
  { return 6; }

  void
  EconomicGrowthModel::adjointBC_eval(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_ptr                      result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    real_const_ptr    LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    real_const_ptr    LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = LL__[iL_lambda3__xo];
    real_type t5   = OMEGA__[2];
    real_type t6   = XR__[iX_x1];
    real_type t7   = XR__[iX_x2];
    real_type t8   = Q_D_1(t6, t7);
    result__[ 3   ] = t8 * t5 - LR__[iL_lambda1__xo];
    real_type t11  = Q_D_2(t6, t7);
    result__[ 4   ] = t11 * t5 - LR__[iL_lambda2__xo];
    result__[ 5   ] = 1 - LR__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DadjointBCDx_numRows() const
  { return 6; }

  integer
  EconomicGrowthModel::DadjointBCDx_numCols() const
  { return 6; }

  integer
  EconomicGrowthModel::DadjointBCDx_nnz() const
  { return 4; }

  void
  EconomicGrowthModel::DadjointBCDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 4   ; jIndex[3 ] = 4   ;
  }

  void
  EconomicGrowthModel::DadjointBCDx_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_ptr                      result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    real_const_ptr    LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    real_const_ptr    LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = OMEGA__[2];
    real_type t2   = XR__[iX_x1];
    real_type t3   = XR__[iX_x2];
    real_type t4   = Q_D_1_1(t2, t3);
    result__[ 0   ] = t4 * t1;
    real_type t5   = Q_D_1_2(t2, t3);
    result__[ 1   ] = t5 * t1;
    result__[ 2   ] = result__[1];
    real_type t6   = Q_D_2_2(t2, t3);
    result__[ 3   ] = t6 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxp_sparse", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DadjointBCDp_numRows() const
  { return 6; }

  integer
  EconomicGrowthModel::DadjointBCDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DadjointBCDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DadjointBCDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  void
  EconomicGrowthModel::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_ptr                      result__
  ) const {
    // EMPTY!
  }

}

// EOF: EconomicGrowthModel_Methods_boundary_conditions.cc
