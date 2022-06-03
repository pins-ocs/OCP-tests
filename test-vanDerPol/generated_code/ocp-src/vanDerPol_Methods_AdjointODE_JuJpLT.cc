/*-----------------------------------------------------------------------*\
 |  file: vanDerPol_Methods_AdjointODE.cc                                |
 |                                                                       |
 |  version: 1.0   date 4/6/2022                                         |
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


#include "vanDerPol.hh"
#include "vanDerPol_Pars.hh"

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


namespace vanDerPolDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer vanDerPol::JP_numEqns() const { return 0; }

  void
  vanDerPol::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer vanDerPol::LT_numEqns() const { return 0; }

  void
  vanDerPol::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer vanDerPol::JU_numEqns() const { return 1; }

  void
  vanDerPol::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_x1] * X__[iX_x1];
    real_type t4   = X__[iX_x2] * X__[iX_x2];
    real_type t8   = uControl(U__[iU_u], -1, 1);
    result__[ 0   ] = t8 * (t2 + t4 + ModelPars[iM_epsilon]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer vanDerPol::LTargs_numEqns() const { return 0; }

  void
  vanDerPol::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::DJPDxpu_numRows() const { return 0; }
  integer vanDerPol::DJPDxpu_numCols() const { return 3; }
  integer vanDerPol::DJPDxpu_nnz()     const { return 0; }

  void
  vanDerPol::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  vanDerPol::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::DLTDxpu_numRows() const { return 0; }
  integer vanDerPol::DLTDxpu_numCols() const { return 3; }
  integer vanDerPol::DLTDxpu_nnz()     const { return 0; }

  void
  vanDerPol::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  vanDerPol::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::DJUDxpu_numRows() const { return 1; }
  integer vanDerPol::DJUDxpu_numCols() const { return 3; }
  integer vanDerPol::DJUDxpu_nnz()     const { return 3; }

  void
  vanDerPol::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }


  void
  vanDerPol::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = U__[iU_u];
    real_type t3   = uControl(t2, -1, 1);
    result__[ 0   ] = 2 * t3 * t1;
    real_type t5   = X__[iX_x2];
    result__[ 1   ] = 2 * t3 * t5;
    real_type t7   = t1 * t1;
    real_type t8   = t5 * t5;
    real_type t11  = ALIAS_uControl_D_1(t2, -1, 1);
    result__[ 2   ] = t11 * (t7 + t8 + ModelPars[iM_epsilon]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::DLTargsDxpu_numRows() const { return 0; }
  integer vanDerPol::DLTargsDxpu_numCols() const { return 3; }
  integer vanDerPol::DLTargsDxpu_nnz()     const { return 0; }

  void
  vanDerPol::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  vanDerPol::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::D2JPD2xpu_numRows() const { return 3; }
  integer vanDerPol::D2JPD2xpu_numCols() const { return 3; }
  integer vanDerPol::D2JPD2xpu_nnz()     const { return 0; }

  void
  vanDerPol::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  vanDerPol::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::D2LTD2xpu_numRows() const { return 3; }
  integer vanDerPol::D2LTD2xpu_numCols() const { return 3; }
  integer vanDerPol::D2LTD2xpu_nnz()     const { return 0; }

  void
  vanDerPol::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  vanDerPol::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::D2JUD2xpu_numRows() const { return 3; }
  integer vanDerPol::D2JUD2xpu_numCols() const { return 3; }
  integer vanDerPol::D2JUD2xpu_nnz()     const { return 7; }

  void
  vanDerPol::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
  }


  void
  vanDerPol::D2JUD2xpu_sparse(
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
    real_type t2   = uControl(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = 2 * t3 * t2;
    real_type t5   = X__[iX_x1];
    real_type t6   = ALIAS_uControl_D_1(t1, -1, 1);
    result__[ 1   ] = 2 * t3 * t6 * t5;
    result__[ 2   ] = result__[0];
    real_type t9   = X__[iX_x2];
    result__[ 3   ] = 2 * t3 * t6 * t9;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[3];
    real_type t12  = t5 * t5;
    real_type t13  = t9 * t9;
    real_type t16  = ALIAS_uControl_D_1_1(t1, -1, 1);
    result__[ 6   ] = t3 * t16 * (t12 + t13 + ModelPars[iM_epsilon]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer vanDerPol::D2LTargsD2xpu_numRows() const { return 3; }
  integer vanDerPol::D2LTargsD2xpu_numCols() const { return 3; }
  integer vanDerPol::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  vanDerPol::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  vanDerPol::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: vanDerPol_Methods_AdjointODE.cc
