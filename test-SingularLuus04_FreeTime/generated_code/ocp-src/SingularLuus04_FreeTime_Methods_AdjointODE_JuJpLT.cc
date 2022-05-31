/*-----------------------------------------------------------------------*\
 |  file: SingularLuus04_FreeTime_Methods_AdjointODE.cc                  |
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


#include "SingularLuus04_FreeTime.hh"
#include "SingularLuus04_FreeTime_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace SingularLuus04_FreeTimeDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularLuus04_FreeTime::JP_numEqns() const { return 0; }

  void
  SingularLuus04_FreeTime::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularLuus04_FreeTime::LT_numEqns() const { return 0; }

  void
  SingularLuus04_FreeTime::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularLuus04_FreeTime::JU_numEqns() const { return 1; }

  void
  SingularLuus04_FreeTime::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = uControl(U__[iU_u], -1, 1);
    result__[ 0   ] = t3 * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularLuus04_FreeTime::LTargs_numEqns() const { return 0; }

  void
  SingularLuus04_FreeTime::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::DJPDxpu_numRows() const { return 0; }
  integer SingularLuus04_FreeTime::DJPDxpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::DJPDxpu_nnz()     const { return 0; }

  void
  SingularLuus04_FreeTime::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularLuus04_FreeTime::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::DLTDxpu_numRows() const { return 0; }
  integer SingularLuus04_FreeTime::DLTDxpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::DLTDxpu_nnz()     const { return 0; }

  void
  SingularLuus04_FreeTime::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularLuus04_FreeTime::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::DJUDxpu_numRows() const { return 1; }
  integer SingularLuus04_FreeTime::DJUDxpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::DJUDxpu_nnz()     const { return 2; }

  void
  SingularLuus04_FreeTime::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
  }


  void
  SingularLuus04_FreeTime::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u];
    result__[ 0   ] = uControl(t1, -1, 1);
    real_type t3   = ALIAS_uControl_D_1(t1, -1, 1);
    result__[ 1   ] = t3 * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::DLTargsDxpu_numRows() const { return 0; }
  integer SingularLuus04_FreeTime::DLTargsDxpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::DLTargsDxpu_nnz()     const { return 0; }

  void
  SingularLuus04_FreeTime::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularLuus04_FreeTime::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::D2JPD2xpu_numRows() const { return 5; }
  integer SingularLuus04_FreeTime::D2JPD2xpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::D2JPD2xpu_nnz()     const { return 0; }

  void
  SingularLuus04_FreeTime::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularLuus04_FreeTime::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::D2LTD2xpu_numRows() const { return 5; }
  integer SingularLuus04_FreeTime::D2LTD2xpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::D2LTD2xpu_nnz()     const { return 0; }

  void
  SingularLuus04_FreeTime::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularLuus04_FreeTime::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::D2JUD2xpu_numRows() const { return 5; }
  integer SingularLuus04_FreeTime::D2JUD2xpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::D2JUD2xpu_nnz()     const { return 3; }

  void
  SingularLuus04_FreeTime::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 4   ;
  }


  void
  SingularLuus04_FreeTime::D2JUD2xpu_sparse(
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
    real_type t1   = U__[iU_u];
    real_type t2   = ALIAS_uControl_D_1(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = t3 * t2;
    result__[ 1   ] = result__[0];
    real_type t5   = ALIAS_uControl_D_1_1(t1, -1, 1);
    result__[ 2   ] = t3 * t5 * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularLuus04_FreeTime::D2LTargsD2xpu_numRows() const { return 5; }
  integer SingularLuus04_FreeTime::D2LTargsD2xpu_numCols() const { return 5; }
  integer SingularLuus04_FreeTime::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  SingularLuus04_FreeTime::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularLuus04_FreeTime::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: SingularLuus04_FreeTime_Methods_AdjointODE.cc
