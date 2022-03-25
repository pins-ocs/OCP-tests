/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Methods_boundary_conditions.cc             |
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

  integer EconomicGrowthModel::boundaryConditions_numEqns() const { return 3; }

  void
  EconomicGrowthModel::boundaryConditions_eval(
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
    result__[ 0   ] = XL__[iX_x1] - ModelPars[iM_x1_i];
    result__[ 1   ] = XL__[iX_x2] - ModelPars[iM_x2_i];
    real_type t7   = Q(XR__[iX_x1], XR__[iX_x2]);
    result__[ 2   ] = t7 - ModelPars[iM_Qc];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 3, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DbcDxxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DbcDxxp_numCols() const { return 6; }
  integer EconomicGrowthModel::DbcDxxp_nnz()     const { return 4; }

  void
  EconomicGrowthModel::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 4   ;
  }


  void
  EconomicGrowthModel::DbcDxxp_sparse(
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
    real_type t1   = XR__[iX_x1];
    real_type t2   = XR__[iX_x2];
    result__[ 2   ] = Q_D_1(t1, t2);
    result__[ 3   ] = Q_D_2(t1, t2);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::D2bcD2xxp_numRows() const { return 6; }
  integer EconomicGrowthModel::D2bcD2xxp_numCols() const { return 6; }
  integer EconomicGrowthModel::D2bcD2xxp_nnz()     const { return 4; }

  void
  EconomicGrowthModel::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 4   ; jIndex[3 ] = 4   ;
  }


  void
  EconomicGrowthModel::D2bcD2xxp_sparse(
    NodeType const         & LEFT__,
    NodeType const         & RIGHT__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type OMEGA__,
    real_type                result__[]
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
    real_type t1   = XR__[iX_x1];
    real_type t2   = XR__[iX_x2];
    result__[ 2   ] = Q_D_1(t1, t2);
    result__[ 3   ] = Q_D_2(t1, t2);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "D2bcD2xxp_sparse", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::adjointBC_numEqns() const { return 6; }

  void
  EconomicGrowthModel::adjointBC_eval(
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
    result__[ 2   ] = 0;
    real_type t1   = OMEGA__[2];
    real_type t2   = XR__[iX_x1];
    real_type t3   = XR__[iX_x2];
    real_type t4   = Q_D_1(t2, t3);
    result__[ 3   ] = t4 * t1;
    real_type t5   = Q_D_2(t2, t3);
    result__[ 4   ] = t5 * t1;
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DadjointBCDxxp_numRows() const { return 6; }
  integer EconomicGrowthModel::DadjointBCDxxp_numCols() const { return 6; }
  integer EconomicGrowthModel::DadjointBCDxxp_nnz()     const { return 4; }

  void
  EconomicGrowthModel::DadjointBCDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 4   ; jIndex[3 ] = 4   ;
  }


  void
  EconomicGrowthModel::DadjointBCDxxp_sparse(
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
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 4, i_segment_left, i_segment_right );
  }
}

// EOF: EconomicGrowthModel_Methods_boundary_conditions.cc
