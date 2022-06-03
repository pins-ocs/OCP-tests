/*-----------------------------------------------------------------------*\
 |  file: BertolazziCorsoExample1_Methods_AdjointODE.cc                  |
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


#include "BertolazziCorsoExample1.hh"
#include "BertolazziCorsoExample1_Pars.hh"

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


namespace BertolazziCorsoExample1Define {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BertolazziCorsoExample1::JP_numEqns() const { return 0; }

  void
  BertolazziCorsoExample1::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BertolazziCorsoExample1::LT_numEqns() const { return 0; }

  void
  BertolazziCorsoExample1::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BertolazziCorsoExample1::JU_numEqns() const { return 0; }

  void
  BertolazziCorsoExample1::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BertolazziCorsoExample1::LTargs_numEqns() const { return 0; }

  void
  BertolazziCorsoExample1::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::DJPDxpu_numRows() const { return 0; }
  integer BertolazziCorsoExample1::DJPDxpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::DJPDxpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::DLTDxpu_numRows() const { return 0; }
  integer BertolazziCorsoExample1::DLTDxpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::DLTDxpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::DJUDxpu_numRows() const { return 0; }
  integer BertolazziCorsoExample1::DJUDxpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::DJUDxpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::DLTargsDxpu_numRows() const { return 0; }
  integer BertolazziCorsoExample1::DLTargsDxpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::DLTargsDxpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::D2JPD2xpu_numRows() const { return 4; }
  integer BertolazziCorsoExample1::D2JPD2xpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::D2JPD2xpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::D2LTD2xpu_numRows() const { return 4; }
  integer BertolazziCorsoExample1::D2LTD2xpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::D2LTD2xpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::D2JUD2xpu_numRows() const { return 4; }
  integer BertolazziCorsoExample1::D2JUD2xpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::D2JUD2xpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BertolazziCorsoExample1::D2LTargsD2xpu_numRows() const { return 4; }
  integer BertolazziCorsoExample1::D2LTargsD2xpu_numCols() const { return 4; }
  integer BertolazziCorsoExample1::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  BertolazziCorsoExample1::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BertolazziCorsoExample1::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BertolazziCorsoExample1_Methods_AdjointODE.cc
