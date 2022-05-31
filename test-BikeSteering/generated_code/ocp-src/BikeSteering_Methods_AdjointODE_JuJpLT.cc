/*-----------------------------------------------------------------------*\
 |  file: BikeSteering_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "BikeSteering.hh"
#include "BikeSteering_Pars.hh"

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
#define ALIAS_minimumTimeSize_DD(__t1) minimumTimeSize.DD( __t1)
#define ALIAS_minimumTimeSize_D(__t1) minimumTimeSize.D( __t1)
#define ALIAS_FyControl_D_3(__t1, __t2, __t3) FyControl.D_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2(__t1, __t2, __t3) FyControl.D_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1(__t1, __t2, __t3) FyControl.D_1( __t1, __t2, __t3)
#define ALIAS_FyControl_D_3_3(__t1, __t2, __t3) FyControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_3(__t1, __t2, __t3) FyControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_2(__t1, __t2, __t3) FyControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_3(__t1, __t2, __t3) FyControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_2(__t1, __t2, __t3) FyControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_1(__t1, __t2, __t3) FyControl.D_1_1( __t1, __t2, __t3)


namespace BikeSteeringDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BikeSteering::JP_numEqns() const { return 0; }

  void
  BikeSteering::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BikeSteering::LT_numEqns() const { return 1; }

  void
  BikeSteering::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = minimumTimeSize(-X__[iX_TimeSize]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BikeSteering::JU_numEqns() const { return 1; }

  void
  BikeSteering::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ModelPars[iM_Fmax];
    real_type t4   = FyControl(U__[iU_Fy], -t3, t3);
    result__[ 0   ] = t4 * X__[iX_TimeSize];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BikeSteering::LTargs_numEqns() const { return 1; }

  void
  BikeSteering::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_TimeSize];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::DJPDxpu_numRows() const { return 0; }
  integer BikeSteering::DJPDxpu_numCols() const { return 4; }
  integer BikeSteering::DJPDxpu_nnz()     const { return 0; }

  void
  BikeSteering::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BikeSteering::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::DLTDxpu_numRows() const { return 1; }
  integer BikeSteering::DLTDxpu_numCols() const { return 4; }
  integer BikeSteering::DLTDxpu_nnz()     const { return 1; }

  void
  BikeSteering::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }


  void
  BikeSteering::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_minimumTimeSize_D(-X__[iX_TimeSize]);
    result__[ 0   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::DJUDxpu_numRows() const { return 1; }
  integer BikeSteering::DJUDxpu_numCols() const { return 4; }
  integer BikeSteering::DJUDxpu_nnz()     const { return 2; }

  void
  BikeSteering::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
  }


  void
  BikeSteering::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_Fy];
    real_type t2   = ModelPars[iM_Fmax];
    result__[ 0   ] = FyControl(t1, -t2, t2);
    real_type t4   = ALIAS_FyControl_D_1(t1, -t2, t2);
    result__[ 1   ] = t4 * X__[iX_TimeSize];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::DLTargsDxpu_numRows() const { return 1; }
  integer BikeSteering::DLTargsDxpu_numCols() const { return 4; }
  integer BikeSteering::DLTargsDxpu_nnz()     const { return 1; }

  void
  BikeSteering::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }


  void
  BikeSteering::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 1, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::D2JPD2xpu_numRows() const { return 4; }
  integer BikeSteering::D2JPD2xpu_numCols() const { return 4; }
  integer BikeSteering::D2JPD2xpu_nnz()     const { return 0; }

  void
  BikeSteering::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BikeSteering::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::D2LTD2xpu_numRows() const { return 4; }
  integer BikeSteering::D2LTD2xpu_numCols() const { return 4; }
  integer BikeSteering::D2LTD2xpu_nnz()     const { return 1; }

  void
  BikeSteering::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
  }


  void
  BikeSteering::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_minimumTimeSize_DD(-X__[iX_TimeSize]);
    result__[ 0   ] = OMEGA__[0] * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::D2JUD2xpu_numRows() const { return 4; }
  integer BikeSteering::D2JUD2xpu_numCols() const { return 4; }
  integer BikeSteering::D2JUD2xpu_nnz()     const { return 3; }

  void
  BikeSteering::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 3   ;
  }


  void
  BikeSteering::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_Fy];
    real_type t2   = ModelPars[iM_Fmax];
    real_type t3   = ALIAS_FyControl_D_1(t1, -t2, t2);
    real_type t4   = OMEGA__[0];
    result__[ 0   ] = t4 * t3;
    result__[ 1   ] = result__[0];
    real_type t6   = ALIAS_FyControl_D_1_1(t1, -t2, t2);
    result__[ 2   ] = t4 * t6 * X__[iX_TimeSize];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BikeSteering::D2LTargsD2xpu_numRows() const { return 4; }
  integer BikeSteering::D2LTargsD2xpu_numCols() const { return 4; }
  integer BikeSteering::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  BikeSteering::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BikeSteering::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BikeSteering_Methods_AdjointODE.cc
