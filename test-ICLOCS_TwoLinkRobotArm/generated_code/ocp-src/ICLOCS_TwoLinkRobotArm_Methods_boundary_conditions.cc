/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_boundary_conditions.cc          |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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


namespace ICLOCS_TwoLinkRobotArmDefine {

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

  integer ICLOCS_TwoLinkRobotArm::boundaryConditions_numEqns() const { return 8; }

  void
  ICLOCS_TwoLinkRobotArm::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_omega__alpha] - ModelPars[iM_omega__alpha_i];
    result__[ 1   ] = XL__[iX_omega__beta] - ModelPars[iM_omega__beta_i];
    result__[ 2   ] = XL__[iX_theta] - ModelPars[iM_theta_i];
    result__[ 3   ] = XL__[iX_alpha] - ModelPars[iM_alpha_i];
    result__[ 4   ] = XR__[iX_omega__alpha] - ModelPars[iM_omega__alpha_f];
    result__[ 5   ] = XR__[iX_omega__beta] - ModelPars[iM_omega__beta_f];
    result__[ 6   ] = XR__[iX_theta] - ModelPars[iM_theta_f];
    result__[ 7   ] = XR__[iX_alpha] - ModelPars[iM_alpha_f];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DbcDxxp_numRows() const { return 8; }
  integer ICLOCS_TwoLinkRobotArm::DbcDxxp_numCols() const { return 9; }
  integer ICLOCS_TwoLinkRobotArm::DbcDxxp_nnz()     const { return 8; }

  void
  ICLOCS_TwoLinkRobotArm::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_TwoLinkRobotArm::DbcDxxp_sparse(
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
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2bcD2xxp_numRows() const { return 9; }
  integer ICLOCS_TwoLinkRobotArm::D2bcD2xxp_numCols() const { return 9; }
  integer ICLOCS_TwoLinkRobotArm::D2bcD2xxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::D2bcD2xxp_sparse(
    NodeType const         & LEFT__,
    NodeType const         & RIGHT__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type OMEGA__,
    real_type                result__[]
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::adjointBC_numEqns() const { return 9; }

  void
  ICLOCS_TwoLinkRobotArm::adjointBC_eval(
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
    result__[ 4   ] = OMEGA__[4];
    result__[ 5   ] = OMEGA__[5];
    result__[ 6   ] = OMEGA__[6];
    result__[ 7   ] = OMEGA__[7];
    real_type t2   = -1 + ModelPars[iM_W];
    real_type t3   = ModelPars[iM_T_guess];
    real_type t5   = P__[iP_T];
    real_type t11  = t3 * t3;
    real_type t16  = t5 * t5;
    result__[ 8   ] = 1.0 / t5 * (2 * t3 * t2 + 2 * t5) - 1.0 / t16 * (2 * t3 * t2 * t5 - t11 * t2 + t16);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 9, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DadjointBCDxxp_numRows() const { return 9; }
  integer ICLOCS_TwoLinkRobotArm::DadjointBCDxxp_numCols() const { return 9; }
  integer ICLOCS_TwoLinkRobotArm::DadjointBCDxxp_nnz()     const { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::DadjointBCDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 8   ; jIndex[0 ] = 8   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::DadjointBCDxxp_sparse(
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
    real_type t1   = P__[iP_T];
    real_type t4   = -1 + ModelPars[iM_W];
    real_type t5   = ModelPars[iM_T_guess];
    real_type t9   = t1 * t1;
    real_type t13  = t5 * t5;
    result__[ 0   ] = 2 / t1 - 2 / t9 * (2 * t5 * t4 + 2 * t1) + 2 / t9 / t1 * (2 * t5 * t4 * t1 - t13 * t4 + t9);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 1, i_segment_left, i_segment_right );
  }
}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_boundary_conditions.cc
