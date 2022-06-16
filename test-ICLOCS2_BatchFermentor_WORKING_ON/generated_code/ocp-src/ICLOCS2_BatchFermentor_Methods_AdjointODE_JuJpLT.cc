/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::PenaltyBarrier1DGreaterThan;
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
#define ALIAS_penalization_DD(__t1) Pen1D.evaluate_DD( __t1)
#define ALIAS_penalization_D(__t1) Pen1D.evaluate_D( __t1)
#define ALIAS_penalization(__t1) Pen1D.evaluate( __t1)


namespace ICLOCS2_BatchFermentorDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::JP_numEqns() const { return 0; }

  void
  ICLOCS2_BatchFermentor::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::LT_numEqns() const { return 0; }

  void
  ICLOCS2_BatchFermentor::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::JU_numEqns() const { return 0; }

  void
  ICLOCS2_BatchFermentor::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::LTargs_numEqns() const { return 0; }

  void
  ICLOCS2_BatchFermentor::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DJPDxpu_numRows() const { return 0; }
  integer ICLOCS2_BatchFermentor::DJPDxpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::DJPDxpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DLTDxpu_numRows() const { return 0; }
  integer ICLOCS2_BatchFermentor::DLTDxpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::DLTDxpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DJUDxpu_numRows() const { return 0; }
  integer ICLOCS2_BatchFermentor::DJUDxpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::DJUDxpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DLTargsDxpu_numRows() const { return 0; }
  integer ICLOCS2_BatchFermentor::DLTargsDxpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::DLTargsDxpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2JPD2xpu_numRows() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2JPD2xpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2JPD2xpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2LTD2xpu_numRows() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2LTD2xpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2LTD2xpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2JUD2xpu_numRows() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2JUD2xpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2JUD2xpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2LTargsD2xpu_numRows() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2LTargsD2xpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_AdjointODE.cc
