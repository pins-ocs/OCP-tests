/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_boundary_conditions.cc            |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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


namespace EconomicGrowthModel2Define {

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

  integer EconomicGrowthModel2::boundaryConditions_numEqns() const { return 7; }

  void
  EconomicGrowthModel2::boundaryConditions_eval(
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
    result__[ 2   ] = XL__[iX_y1] - ModelPars[iM_y1_i];
    result__[ 3   ] = XL__[iX_y2] - ModelPars[iM_y2_i];
    result__[ 4   ] = XR__[iX_x1] - XR__[iX_x2];
    real_type t12  = ModelPars[iM_Yc];
    result__[ 5   ] = XR__[iX_y1] - t12;
    result__[ 6   ] = XR__[iX_y2] - t12;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 7, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DbcDxxp_numRows() const { return 7; }
  integer EconomicGrowthModel2::DbcDxxp_numCols() const { return 10; }
  integer EconomicGrowthModel2::DbcDxxp_nnz()     const { return 8; }

  void
  EconomicGrowthModel2::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 6   ; jIndex[7 ] = 8   ;
  }


  void
  EconomicGrowthModel2::DbcDxxp_sparse(
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
    result__[ 5   ] = -1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::D2bcD2xxp_numRows() const { return 10; }
  integer EconomicGrowthModel2::D2bcD2xxp_numCols() const { return 10; }
  integer EconomicGrowthModel2::D2bcD2xxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::D2bcD2xxp_sparse(
    NodeType const         & LEFT__,
    NodeType const         & RIGHT__,
    P_const_pointer_type     P__,
    OMEGA_const_pointer_type OMEGA__,
    real_type                result__[]
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::adjointBC_numEqns() const { return 10; }

  void
  EconomicGrowthModel2::adjointBC_eval(
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
    result__[ 4   ] = 0;
    result__[ 5   ] = OMEGA__[4];
    result__[ 6   ] = -result__[5];
    result__[ 7   ] = OMEGA__[5];
    result__[ 8   ] = OMEGA__[6];
    result__[ 9   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DadjointBCDxxp_numRows() const { return 10; }
  integer EconomicGrowthModel2::DadjointBCDxxp_numCols() const { return 10; }
  integer EconomicGrowthModel2::DadjointBCDxxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DadjointBCDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DadjointBCDxxp_sparse(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }
}

// EOF: EconomicGrowthModel2_Methods_boundary_conditions.cc
