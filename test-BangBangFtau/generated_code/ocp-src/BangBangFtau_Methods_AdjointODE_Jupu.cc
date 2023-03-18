/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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

  real_type
  BangBangFtau::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BangBangFtau::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BangBangFtau::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    real_type t2   = vsTpositive(-t1);
    real_type t3   = U__[iU_vsB];
    real_type t4   = vsBpositive(-t3);
    real_type t7   = vsTmax(t1 - ModelPars[iM_maxT]);
    real_type t9   = vsTBInterval_min(-1 - t1 + t3);
    real_type t11  = vsTBInterval_max(t1 - t3 - 1);
    real_type result__ = t2 + t4 + t7 + t9 + t11;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JPxpu_numEqns() const { return 6; }

  void
  BangBangFtau::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JUxpu_numEqns() const { return 6; }

  void
  BangBangFtau::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::LTxpu_numEqns() const { return 6; }

  void
  BangBangFtau::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    real_type t1   = U__[iU_vsT];
    real_type t2   = ALIAS_vsTpositive_D(-t1);
    real_type t5   = ALIAS_vsTmax_D(t1 - ModelPars[iM_maxT]);
    real_type t6   = U__[iU_vsB];
    real_type t8   = ALIAS_vsTBInterval_min_D(-1 - t1 + t6);
    real_type t10  = ALIAS_vsTBInterval_max_D(t1 - t6 - 1);
    result__[ 4   ] = -t2 + t5 - t8 + t10;
    real_type t11  = ALIAS_vsBpositive_D(-t6);
    result__[ 5   ] = -t11 + t8 - t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::LTargs_numEqns() const { return 5; }

  void
  BangBangFtau::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
  integer BangBangFtau::D2JPD2xpu_numRows() const { return 6; }
  integer BangBangFtau::D2JPD2xpu_numCols() const { return 6; }
  integer BangBangFtau::D2JPD2xpu_nnz()     const { return 0; }

  void
  BangBangFtau::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    real_type t2   = ALIAS_vsTpositive_DD(-t1);
    real_type t5   = ALIAS_vsTmax_DD(t1 - ModelPars[iM_maxT]);
    real_type t6   = U__[iU_vsB];
    real_type t8   = ALIAS_vsTBInterval_min_DD(-1 - t1 + t6);
    real_type t10  = ALIAS_vsTBInterval_max_DD(t1 - t6 - 1);
    result__[ 0   ] = t2 + t5 + t8 + t10;
    result__[ 1   ] = -t8 - t10;
    result__[ 2   ] = result__[1];
    real_type t11  = ALIAS_vsBpositive_DD(-t6);
    result__[ 3   ] = t11 + t8 + t10;
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
  integer BangBangFtau::D2LTargsD2xpu_numRows() const { return 6; }
  integer BangBangFtau::D2LTargsD2xpu_numCols() const { return 6; }
  integer BangBangFtau::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  BangBangFtau::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFtau_Methods_AdjointODE.cc
