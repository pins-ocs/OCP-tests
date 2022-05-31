/*-----------------------------------------------------------------------*\
 |  file: SingularCalogero_Methods_AdjointODE.cc                         |
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


#include "SingularCalogero.hh"
#include "SingularCalogero_Pars.hh"

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


namespace SingularCalogeroDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogero::JP_numEqns() const { return 0; }

  void
  SingularCalogero::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogero::LT_numEqns() const { return 0; }

  void
  SingularCalogero::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogero::JU_numEqns() const { return 1; }

  void
  SingularCalogero::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = uControl(U__[iU_u], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SingularCalogero::LTargs_numEqns() const { return 0; }

  void
  SingularCalogero::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::DJPDxpu_numRows() const { return 0; }
  integer SingularCalogero::DJPDxpu_numCols() const { return 2; }
  integer SingularCalogero::DJPDxpu_nnz()     const { return 0; }

  void
  SingularCalogero::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogero::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::DLTDxpu_numRows() const { return 0; }
  integer SingularCalogero::DLTDxpu_numCols() const { return 2; }
  integer SingularCalogero::DLTDxpu_nnz()     const { return 0; }

  void
  SingularCalogero::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogero::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::DJUDxpu_numRows() const { return 1; }
  integer SingularCalogero::DJUDxpu_numCols() const { return 2; }
  integer SingularCalogero::DJUDxpu_nnz()     const { return 1; }

  void
  SingularCalogero::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
  }


  void
  SingularCalogero::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::DLTargsDxpu_numRows() const { return 0; }
  integer SingularCalogero::DLTargsDxpu_numCols() const { return 2; }
  integer SingularCalogero::DLTargsDxpu_nnz()     const { return 0; }

  void
  SingularCalogero::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogero::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::D2JPD2xpu_numRows() const { return 2; }
  integer SingularCalogero::D2JPD2xpu_numCols() const { return 2; }
  integer SingularCalogero::D2JPD2xpu_nnz()     const { return 0; }

  void
  SingularCalogero::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogero::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::D2LTD2xpu_numRows() const { return 2; }
  integer SingularCalogero::D2LTD2xpu_numCols() const { return 2; }
  integer SingularCalogero::D2LTD2xpu_nnz()     const { return 0; }

  void
  SingularCalogero::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogero::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::D2JUD2xpu_numRows() const { return 2; }
  integer SingularCalogero::D2JUD2xpu_numCols() const { return 2; }
  integer SingularCalogero::D2JUD2xpu_nnz()     const { return 1; }

  void
  SingularCalogero::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
  }


  void
  SingularCalogero::D2JUD2xpu_sparse(
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
    real_type t2   = ALIAS_uControl_D_1_1(U__[iU_u], -1, 1);
    result__[ 0   ] = OMEGA__[0] * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SingularCalogero::D2LTargsD2xpu_numRows() const { return 2; }
  integer SingularCalogero::D2LTargsD2xpu_numCols() const { return 2; }
  integer SingularCalogero::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  SingularCalogero::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SingularCalogero::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: SingularCalogero_Methods_AdjointODE.cc
