/*-----------------------------------------------------------------------*\
 |  file: BangBangF_Methods_AdjointODE.cc                                |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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


#include "BangBangF.hh"
#include "BangBangF_Pars.hh"

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
#define ALIAS_C1_constr_DD(__t1) C1_constr.DD( __t1)
#define ALIAS_C1_constr_D(__t1) C1_constr.D( __t1)
#define ALIAS_FControl_D_3(__t1, __t2, __t3) FControl.D_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2(__t1, __t2, __t3) FControl.D_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1(__t1, __t2, __t3) FControl.D_1( __t1, __t2, __t3)
#define ALIAS_FControl_D_3_3(__t1, __t2, __t3) FControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2_3(__t1, __t2, __t3) FControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2_2(__t1, __t2, __t3) FControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_3(__t1, __t2, __t3) FControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_2(__t1, __t2, __t3) FControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_1(__t1, __t2, __t3) FControl.D_1_1( __t1, __t2, __t3)


namespace BangBangFDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JP_numEqns() const { return 0; }

  void
  BangBangF::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::LT_numEqns() const { return 1; }

  void
  BangBangF::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = C1(X__[iX_v]);
    result__[ 0   ] = C1_constr(t2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JU_numEqns() const { return 1; }

  void
  BangBangF::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = FControl(U__[iU_F], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::LTargs_numEqns() const { return 1; }

  void
  BangBangF::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = C1(X__[iX_v]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJPDxpu_numRows() const { return 0; }
  integer BangBangF::DJPDxpu_numCols() const { return 3; }
  integer BangBangF::DJPDxpu_nnz()     const { return 0; }

  void
  BangBangF::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DLTDxpu_numRows() const { return 1; }
  integer BangBangF::DLTDxpu_numCols() const { return 3; }
  integer BangBangF::DLTDxpu_nnz()     const { return 1; }

  void
  BangBangF::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = C1(t1);
    real_type t3   = ALIAS_C1_constr_D(t2);
    real_type t4   = C1_D(t1);
    result__[ 0   ] = t4 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJUDxpu_numRows() const { return 1; }
  integer BangBangF::DJUDxpu_numCols() const { return 3; }
  integer BangBangF::DJUDxpu_nnz()     const { return 1; }

  void
  BangBangF::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }


  void
  BangBangF::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_FControl_D_1(U__[iU_F], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DLTargsDxpu_numRows() const { return 1; }
  integer BangBangF::DLTargsDxpu_numCols() const { return 3; }
  integer BangBangF::DLTargsDxpu_nnz()     const { return 1; }

  void
  BangBangF::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = C1_D(X__[iX_v]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 1, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::D2JPD2xpu_numRows() const { return 3; }
  integer BangBangF::D2JPD2xpu_numCols() const { return 3; }
  integer BangBangF::D2JPD2xpu_nnz()     const { return 0; }

  void
  BangBangF::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::D2LTD2xpu_numRows() const { return 3; }
  integer BangBangF::D2LTD2xpu_numCols() const { return 3; }
  integer BangBangF::D2LTD2xpu_nnz()     const { return 1; }

  void
  BangBangF::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::D2LTD2xpu_sparse(
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
    real_type t1   = X__[iX_v];
    real_type t2   = C1(t1);
    real_type t3   = ALIAS_C1_constr_DD(t2);
    real_type t4   = C1_D(t1);
    real_type t5   = t4 * t4;
    real_type t7   = OMEGA__[0];
    real_type t9   = ALIAS_C1_constr_D(t2);
    real_type t10  = C1_DD(t1);
    result__[ 0   ] = t7 * t10 * t9 + t7 * t5 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::D2JUD2xpu_numRows() const { return 3; }
  integer BangBangF::D2JUD2xpu_numCols() const { return 3; }
  integer BangBangF::D2JUD2xpu_nnz()     const { return 1; }

  void
  BangBangF::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
  }


  void
  BangBangF::D2JUD2xpu_sparse(
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
    real_type t2   = ALIAS_FControl_D_1_1(U__[iU_F], -1, 1);
    result__[ 0   ] = OMEGA__[0] * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::D2LTargsD2xpu_numRows() const { return 3; }
  integer BangBangF::D2LTargsD2xpu_numCols() const { return 3; }
  integer BangBangF::D2LTargsD2xpu_nnz()     const { return 1; }

  void
  BangBangF::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::D2LTargsD2xpu_sparse(
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
    real_type t2   = C1_DD(X__[iX_v]);
    result__[ 0   ] = OMEGA__[0] * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 1, i_segment );
  }

}

// EOF: BangBangF_Methods_AdjointODE.cc
