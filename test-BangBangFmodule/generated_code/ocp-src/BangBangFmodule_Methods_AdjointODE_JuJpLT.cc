/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Methods_AdjointODE.cc                          |
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


#include "BangBangFmodule.hh"
#include "BangBangFmodule_Pars.hh"

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
#define ALIAS_controlM_D_3(__t1, __t2, __t3) controlM.D_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2(__t1, __t2, __t3) controlM.D_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1(__t1, __t2, __t3) controlM.D_1( __t1, __t2, __t3)
#define ALIAS_controlM_D_3_3(__t1, __t2, __t3) controlM.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2_3(__t1, __t2, __t3) controlM.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2_2(__t1, __t2, __t3) controlM.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_3(__t1, __t2, __t3) controlM.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_2(__t1, __t2, __t3) controlM.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_1(__t1, __t2, __t3) controlM.D_1_1( __t1, __t2, __t3)
#define ALIAS_controlP_D_3(__t1, __t2, __t3) controlP.D_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2(__t1, __t2, __t3) controlP.D_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1(__t1, __t2, __t3) controlP.D_1( __t1, __t2, __t3)
#define ALIAS_controlP_D_3_3(__t1, __t2, __t3) controlP.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2_3(__t1, __t2, __t3) controlP.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2_2(__t1, __t2, __t3) controlP.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_3(__t1, __t2, __t3) controlP.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_2(__t1, __t2, __t3) controlP.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_1(__t1, __t2, __t3) controlP.D_1_1( __t1, __t2, __t3)


namespace BangBangFmoduleDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::JP_numEqns() const { return 0; }

  void
  BangBangFmodule::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::LT_numEqns() const { return 0; }

  void
  BangBangFmodule::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::JU_numEqns() const { return 2; }

  void
  BangBangFmodule::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = controlP(U__[iU_Fp], 0, ModelPars[iM_FpMax]);
    result__[ 1   ] = controlM(U__[iU_Fm], 0, ModelPars[iM_FmMax]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::LTargs_numEqns() const { return 0; }

  void
  BangBangFmodule::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJPDxpu_numRows() const { return 0; }
  integer BangBangFmodule::DJPDxpu_numCols() const { return 4; }
  integer BangBangFmodule::DJPDxpu_nnz()     const { return 0; }

  void
  BangBangFmodule::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DLTDxpu_numRows() const { return 0; }
  integer BangBangFmodule::DLTDxpu_numCols() const { return 4; }
  integer BangBangFmodule::DLTDxpu_nnz()     const { return 0; }

  void
  BangBangFmodule::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJUDxpu_numRows() const { return 2; }
  integer BangBangFmodule::DJUDxpu_numCols() const { return 4; }
  integer BangBangFmodule::DJUDxpu_nnz()     const { return 2; }

  void
  BangBangFmodule::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
  }


  void
  BangBangFmodule::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_controlP_D_1(U__[iU_Fp], 0, ModelPars[iM_FpMax]);
    result__[ 1   ] = ALIAS_controlM_D_1(U__[iU_Fm], 0, ModelPars[iM_FmMax]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DLTargsDxpu_numRows() const { return 0; }
  integer BangBangFmodule::DLTargsDxpu_numCols() const { return 4; }
  integer BangBangFmodule::DLTargsDxpu_nnz()     const { return 0; }

  void
  BangBangFmodule::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::D2JPD2xpu_numRows() const { return 4; }
  integer BangBangFmodule::D2JPD2xpu_numCols() const { return 4; }
  integer BangBangFmodule::D2JPD2xpu_nnz()     const { return 0; }

  void
  BangBangFmodule::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::D2LTD2xpu_numRows() const { return 4; }
  integer BangBangFmodule::D2LTD2xpu_numCols() const { return 4; }
  integer BangBangFmodule::D2LTD2xpu_nnz()     const { return 0; }

  void
  BangBangFmodule::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::D2JUD2xpu_numRows() const { return 4; }
  integer BangBangFmodule::D2JUD2xpu_numCols() const { return 4; }
  integer BangBangFmodule::D2JUD2xpu_nnz()     const { return 2; }

  void
  BangBangFmodule::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 3   ;
  }


  void
  BangBangFmodule::D2JUD2xpu_sparse(
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
    real_type t3   = ALIAS_controlP_D_1_1(U__[iU_Fp], 0, ModelPars[iM_FpMax]);
    result__[ 0   ] = OMEGA__[0] * t3;
    real_type t7   = ALIAS_controlM_D_1_1(U__[iU_Fm], 0, ModelPars[iM_FmMax]);
    result__[ 1   ] = OMEGA__[1] * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 2, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::D2LTargsD2xpu_numRows() const { return 4; }
  integer BangBangFmodule::D2LTargsD2xpu_numCols() const { return 4; }
  integer BangBangFmodule::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  BangBangFmodule::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFmodule_Methods_AdjointODE.cc
