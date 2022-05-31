/*-----------------------------------------------------------------------*\
 |  file: FlowInAchannel_Methods_AdjointODE.cc                           |
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


#include "FlowInAchannel.hh"
#include "FlowInAchannel_Pars.hh"

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


namespace FlowInAchannelDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer FlowInAchannel::JP_numEqns() const { return 0; }

  void
  FlowInAchannel::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer FlowInAchannel::LT_numEqns() const { return 0; }

  void
  FlowInAchannel::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer FlowInAchannel::JU_numEqns() const { return 0; }

  void
  FlowInAchannel::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer FlowInAchannel::LTargs_numEqns() const { return 0; }

  void
  FlowInAchannel::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::DJPDxpu_numRows() const { return 0; }
  integer FlowInAchannel::DJPDxpu_numCols() const { return 4; }
  integer FlowInAchannel::DJPDxpu_nnz()     const { return 0; }

  void
  FlowInAchannel::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::DLTDxpu_numRows() const { return 0; }
  integer FlowInAchannel::DLTDxpu_numCols() const { return 4; }
  integer FlowInAchannel::DLTDxpu_nnz()     const { return 0; }

  void
  FlowInAchannel::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::DJUDxpu_numRows() const { return 0; }
  integer FlowInAchannel::DJUDxpu_numCols() const { return 4; }
  integer FlowInAchannel::DJUDxpu_nnz()     const { return 0; }

  void
  FlowInAchannel::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::DLTargsDxpu_numRows() const { return 0; }
  integer FlowInAchannel::DLTargsDxpu_numCols() const { return 4; }
  integer FlowInAchannel::DLTargsDxpu_nnz()     const { return 0; }

  void
  FlowInAchannel::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::D2JPD2xpu_numRows() const { return 4; }
  integer FlowInAchannel::D2JPD2xpu_numCols() const { return 4; }
  integer FlowInAchannel::D2JPD2xpu_nnz()     const { return 0; }

  void
  FlowInAchannel::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::D2LTD2xpu_numRows() const { return 4; }
  integer FlowInAchannel::D2LTD2xpu_numCols() const { return 4; }
  integer FlowInAchannel::D2LTD2xpu_nnz()     const { return 0; }

  void
  FlowInAchannel::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::D2JUD2xpu_numRows() const { return 4; }
  integer FlowInAchannel::D2JUD2xpu_numCols() const { return 4; }
  integer FlowInAchannel::D2JUD2xpu_nnz()     const { return 0; }

  void
  FlowInAchannel::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::D2LTargsD2xpu_numRows() const { return 4; }
  integer FlowInAchannel::D2LTargsD2xpu_numCols() const { return 4; }
  integer FlowInAchannel::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  FlowInAchannel::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  FlowInAchannel::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: FlowInAchannel_Methods_AdjointODE.cc
