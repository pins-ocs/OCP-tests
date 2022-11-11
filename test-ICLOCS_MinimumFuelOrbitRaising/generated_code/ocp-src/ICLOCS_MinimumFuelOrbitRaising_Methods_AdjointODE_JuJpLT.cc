/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc           |
 |                                                                       |
 |  version: 1.0   date 15/11/2022                                       |
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


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

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
#pragma warning( disable : 4189 )
#endif


namespace ICLOCS_MinimumFuelOrbitRaisingDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JP_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::LT_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JU_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::LTargs_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJPDxpu_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPDxpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPDxpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DLTDxpu_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTDxpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTDxpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJUDxpu_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUDxpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUDxpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DLTargsDxpu_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTargsDxpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTargsDxpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::D2JPD2xpu_numRows() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2JPD2xpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2JPD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTD2xpu_numRows() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTD2xpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::D2JUD2xpu_numRows() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2JUD2xpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2JUD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xpu_numRows() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xpu_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc
