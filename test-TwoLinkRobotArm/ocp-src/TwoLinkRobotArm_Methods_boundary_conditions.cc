/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods_boundary_conditions.cc                 |
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


#include "TwoLinkRobotArm.hh"
#include "TwoLinkRobotArm_Pars.hh"

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
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoLinkRobotArmDefine {

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
  TwoLinkRobotArm::boundaryConditions_numEqns() const
  { return 8; }

  void
  TwoLinkRobotArm::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_x1];
    result__[ 1   ] = XL__[iX_x2];
    result__[ 2   ] = XL__[iX_x3] - 0.5e0;
    result__[ 3   ] = XL__[iX_x4];
    result__[ 4   ] = XR__[iX_x1];
    result__[ 5   ] = XR__[iX_x2];
    result__[ 6   ] = XR__[iX_x3] - 0.5e0;
    result__[ 7   ] = XR__[iX_x4] - 0.522e0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DboundaryConditionsDx_numRows() const
  { return 8; }

  integer
  TwoLinkRobotArm::DboundaryConditionsDx_numCols() const
  { return 8; }

  integer
  TwoLinkRobotArm::DboundaryConditionsDx_nnz() const
  { return 8; }

  void
  TwoLinkRobotArm::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
  }

  void
  TwoLinkRobotArm::DboundaryConditionsDx_sparse(
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
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxp_sparse", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DboundaryConditionsDp_numRows() const
  { return 8; }

  integer
  TwoLinkRobotArm::DboundaryConditionsDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  TwoLinkRobotArm::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::adjointBC_numEqns() const
  { return 9; }

  void
  TwoLinkRobotArm::adjointBC_eval(
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
    result__[ 4   ] = OMEGA__[4] - LR__[iL_lambda1__xo];
    result__[ 5   ] = OMEGA__[5] - LR__[iL_lambda2__xo];
    result__[ 6   ] = OMEGA__[6] - LR__[iL_lambda3__xo];
    result__[ 7   ] = OMEGA__[7] - LR__[iL_lambda4__xo];
    real_type t17  = P__[iP_T];
    real_type t18  = ModelPars[iM_W];
    result__[ 8   ] = -2 * t18 * t17 + 2 * t17 + 21 * t18 - 20;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 9, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DadjointBCDx_numRows() const
  { return 9; }

  integer
  TwoLinkRobotArm::DadjointBCDx_numCols() const
  { return 8; }

  integer
  TwoLinkRobotArm::DadjointBCDx_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  TwoLinkRobotArm::DadjointBCDx_sparse(
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
  TwoLinkRobotArm::DadjointBCDp_numRows() const
  { return 9; }

  integer
  TwoLinkRobotArm::DadjointBCDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DadjointBCDp_nnz() const
  { return 1; }

  void
  TwoLinkRobotArm::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 8   ; jIndex[0 ] = 0   ;
  }

  void
  TwoLinkRobotArm::DadjointBCDp_sparse(
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
    result__[ 0   ] = -2 * ModelPars[iM_W] + 2;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxp_sparse", 1, i_segment_left, i_segment_right );
  }

}

// EOF: TwoLinkRobotArm_Methods_boundary_conditions.cc
