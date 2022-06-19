/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vsTBInterval_max_DD(__t1) vsTBInterval_max.DD( __t1)
#define ALIAS_vsTBInterval_max_D(__t1) vsTBInterval_max.D( __t1)
#define ALIAS_vsTBInterval_min_DD(__t1) vsTBInterval_min.DD( __t1)
#define ALIAS_vsTBInterval_min_D(__t1) vsTBInterval_min.D( __t1)
#define ALIAS_vsTmax_DD(__t1) vsTmax.DD( __t1)
#define ALIAS_vsTmax_D(__t1) vsTmax.D( __t1)
#define ALIAS_vsBpositive_DD(__t1) vsBpositive.DD( __t1)
#define ALIAS_vsBpositive_D(__t1) vsBpositive.D( __t1)
#define ALIAS_vsTpositive_DD(__t1) vsTpositive.DD( __t1)
#define ALIAS_vsTpositive_D(__t1) vsTpositive.D( __t1)


namespace BangBangFtauDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JP_numEqns() const { return 0; }

  void
  BangBangFtau::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::LT_numEqns() const { return 5; }

  void
  BangBangFtau::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    result__[ 0   ] = vsTpositive(-t1);
    real_type t2   = U__[iU_vsB];
    result__[ 1   ] = vsBpositive(-t2);
    result__[ 2   ] = vsTmax(t1 - ModelPars[iM_maxT]);
    result__[ 3   ] = vsTBInterval_min(-1 - t1 + t2);
    result__[ 4   ] = vsTBInterval_max(t1 - t2 - 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JU_numEqns() const { return 0; }

  void
  BangBangFtau::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::LTargs_numEqns() const { return 5; }

  void
  BangBangFtau::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    result__[ 0   ] = -t1;
    real_type t2   = U__[iU_vsB];
    result__[ 1   ] = -t2;
    result__[ 2   ] = t1 - ModelPars[iM_maxT];
    result__[ 3   ] = -1 + result__[0] + t2;
    result__[ 4   ] = t1 + result__[1] - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJPDxpu_numRows() const { return 0; }
  integer BangBangFtau::DJPDxpu_numCols() const { return 6; }
  integer BangBangFtau::DJPDxpu_nnz()     const { return 0; }

  void
  BangBangFtau::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DLTDxpu_numRows() const { return 5; }
  integer BangBangFtau::DLTDxpu_numCols() const { return 6; }
  integer BangBangFtau::DLTDxpu_nnz()     const { return 7; }

  void
  BangBangFtau::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 5   ;
  }


  void
  BangBangFtau::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    real_type t2   = ALIAS_vsTpositive_D(-t1);
    result__[ 0   ] = -t2;
    real_type t3   = U__[iU_vsB];
    real_type t4   = ALIAS_vsBpositive_D(-t3);
    result__[ 1   ] = -t4;
    result__[ 2   ] = ALIAS_vsTmax_D(t1 - ModelPars[iM_maxT]);
    real_type t8   = ALIAS_vsTBInterval_min_D(-1 - t1 + t3);
    result__[ 3   ] = -t8;
    result__[ 4   ] = t8;
    result__[ 5   ] = ALIAS_vsTBInterval_max_D(t1 - t3 - 1);
    result__[ 6   ] = -result__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJUDxpu_numRows() const { return 0; }
  integer BangBangFtau::DJUDxpu_numCols() const { return 6; }
  integer BangBangFtau::DJUDxpu_nnz()     const { return 0; }

  void
  BangBangFtau::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DLTargsDxpu_numRows() const { return 5; }
  integer BangBangFtau::DLTargsDxpu_numCols() const { return 6; }
  integer BangBangFtau::DLTargsDxpu_nnz()     const { return 7; }

  void
  BangBangFtau::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 5   ;
  }


  void
  BangBangFtau::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 7, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::D2JPD2xpu_numRows() const { return 6; }
  integer BangBangFtau::D2JPD2xpu_numCols() const { return 6; }
  integer BangBangFtau::D2JPD2xpu_nnz()     const { return 0; }

  void
  BangBangFtau::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::D2LTD2xpu_numRows() const { return 6; }
  integer BangBangFtau::D2LTD2xpu_numCols() const { return 6; }
  integer BangBangFtau::D2LTD2xpu_nnz()     const { return 4; }

  void
  BangBangFtau::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 5   ;
  }


  void
  BangBangFtau::D2LTD2xpu_sparse(
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
    real_type t1   = U__[iU_vsT];
    real_type t2   = ALIAS_vsTpositive_DD(-t1);
    real_type t7   = ALIAS_vsTmax_DD(t1 - ModelPars[iM_maxT]);
    real_type t10  = U__[iU_vsB];
    real_type t12  = ALIAS_vsTBInterval_min_DD(-1 - t1 + t10);
    real_type t14  = OMEGA__[3] * t12;
    real_type t16  = ALIAS_vsTBInterval_max_DD(t1 - t10 - 1);
    real_type t18  = OMEGA__[4] * t16;
    result__[ 0   ] = OMEGA__[0] * t2 + OMEGA__[2] * t7 + t14 + t18;
    result__[ 1   ] = -t14 - t18;
    result__[ 2   ] = result__[1];
    real_type t19  = ALIAS_vsBpositive_DD(-t10);
    result__[ 3   ] = OMEGA__[1] * t19 + t14 + t18;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::D2JUD2xpu_numRows() const { return 6; }
  integer BangBangFtau::D2JUD2xpu_numCols() const { return 6; }
  integer BangBangFtau::D2JUD2xpu_nnz()     const { return 0; }

  void
  BangBangFtau::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::D2LTargsD2xpu_numRows() const { return 6; }
  integer BangBangFtau::D2LTargsD2xpu_numCols() const { return 6; }
  integer BangBangFtau::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  BangBangFtau::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFtau_Methods_AdjointODE.cc
