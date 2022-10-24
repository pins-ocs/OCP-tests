/*-----------------------------------------------------------------------*\
 |  file: BangBangFclip_Methods_AdjointODE.cc                            |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "BangBangFclip.hh"
#include "BangBangFclip_Pars.hh"

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

// map user defined functions and objects with macros
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_controlForce_D_3(__t1, __t2, __t3) controlForce.D_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_2(__t1, __t2, __t3) controlForce.D_2( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1(__t1, __t2, __t3) controlForce.D_1( __t1, __t2, __t3)
#define ALIAS_controlForce_D_3_3(__t1, __t2, __t3) controlForce.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_2_3(__t1, __t2, __t3) controlForce.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_2_2(__t1, __t2, __t3) controlForce.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1_3(__t1, __t2, __t3) controlForce.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1_2(__t1, __t2, __t3) controlForce.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1_1(__t1, __t2, __t3) controlForce.D_1_1( __t1, __t2, __t3)


namespace BangBangFclipDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFclip::JP_numEqns() const { return 0; }

  void
  BangBangFclip::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFclip::LT_numEqns() const { return 0; }

  void
  BangBangFclip::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFclip::JU_numEqns() const { return 1; }

  void
  BangBangFclip::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_vFmax];
    result__[ 0   ] = controlForce(U__[iU_vF], -t2, t2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFclip::LTargs_numEqns() const { return 0; }

  void
  BangBangFclip::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::DJPDxpu_numRows() const { return 0; }
  integer BangBangFclip::DJPDxpu_numCols() const { return 4; }
  integer BangBangFclip::DJPDxpu_nnz()     const { return 0; }

  void
  BangBangFclip::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFclip::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::DLTDxpu_numRows() const { return 0; }
  integer BangBangFclip::DLTDxpu_numCols() const { return 4; }
  integer BangBangFclip::DLTDxpu_nnz()     const { return 0; }

  void
  BangBangFclip::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFclip::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::DJUDxpu_numRows() const { return 1; }
  integer BangBangFclip::DJUDxpu_numCols() const { return 4; }
  integer BangBangFclip::DJUDxpu_nnz()     const { return 1; }

  void
  BangBangFclip::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
  }


  void
  BangBangFclip::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_vFmax];
    result__[ 0   ] = ALIAS_controlForce_D_1(U__[iU_vF], -t2, t2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::DLTargsDxpu_numRows() const { return 0; }
  integer BangBangFclip::DLTargsDxpu_numCols() const { return 4; }
  integer BangBangFclip::DLTargsDxpu_nnz()     const { return 0; }

  void
  BangBangFclip::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFclip::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::D2JPD2xpu_numRows() const { return 4; }
  integer BangBangFclip::D2JPD2xpu_numCols() const { return 4; }
  integer BangBangFclip::D2JPD2xpu_nnz()     const { return 0; }

  void
  BangBangFclip::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFclip::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::D2LTD2xpu_numRows() const { return 4; }
  integer BangBangFclip::D2LTD2xpu_numCols() const { return 4; }
  integer BangBangFclip::D2LTD2xpu_nnz()     const { return 0; }

  void
  BangBangFclip::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFclip::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::D2JUD2xpu_numRows() const { return 4; }
  integer BangBangFclip::D2JUD2xpu_numCols() const { return 4; }
  integer BangBangFclip::D2JUD2xpu_nnz()     const { return 1; }

  void
  BangBangFclip::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 3   ;
  }


  void
  BangBangFclip::D2JUD2xpu_sparse(
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
    real_type t2   = ModelPars[iM_vFmax];
    real_type t3   = ALIAS_controlForce_D_1_1(U__[iU_vF], -t2, t2);
    result__[ 0   ] = OMEGA__[0] * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::D2LTargsD2xpu_numRows() const { return 4; }
  integer BangBangFclip::D2LTargsD2xpu_numCols() const { return 4; }
  integer BangBangFclip::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  BangBangFclip::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFclip::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFclip_Methods_AdjointODE.cc
