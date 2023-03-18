/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_AdjointODE.cc                             |
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


#include "stirred_tank.hh"
#include "stirred_tank_Pars.hh"

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
#define ALIAS_u4Control_D_3(__t1, __t2, __t3) u4Control.D_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2(__t1, __t2, __t3) u4Control.D_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1(__t1, __t2, __t3) u4Control.D_1( __t1, __t2, __t3)
#define ALIAS_u4Control_D_3_3(__t1, __t2, __t3) u4Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_3(__t1, __t2, __t3) u4Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_2(__t1, __t2, __t3) u4Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_3(__t1, __t2, __t3) u4Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_2(__t1, __t2, __t3) u4Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_1(__t1, __t2, __t3) u4Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace stirred_tankDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  stirred_tank::JP_eval(
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
  stirred_tank::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = u1Control(U__[iU_u1], 0, 20);
    real_type t4   = u2Control(U__[iU_u2], 0, 6);
    real_type t6   = u3Control(U__[iU_u3], 0, 4);
    real_type t8   = u4Control(U__[iU_u4], 0, 20);
    real_type result__ = t2 + t4 + t6 + t8;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  stirred_tank::LT_eval(
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
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::JPxpu_numEqns() const { return 12; }

  void
  stirred_tank::JPxpu_eval(
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
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::JUxpu_numEqns() const { return 12; }

  void
  stirred_tank::JUxpu_eval(
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
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = ALIAS_u1Control_D_1(U__[iU_u1], 0, 20);
    result__[ 9   ] = ALIAS_u2Control_D_1(U__[iU_u2], 0, 6);
    result__[ 10  ] = ALIAS_u3Control_D_1(U__[iU_u3], 0, 4);
    result__[ 11  ] = ALIAS_u4Control_D_1(U__[iU_u4], 0, 20);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::LTxpu_numEqns() const { return 12; }

  void
  stirred_tank::LTxpu_eval(
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
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer stirred_tank::LTargs_numEqns() const { return 0; }

  void
  stirred_tank::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::D2JPD2xpu_numRows() const { return 12; }
  integer stirred_tank::D2JPD2xpu_numCols() const { return 12; }
  integer stirred_tank::D2JPD2xpu_nnz()     const { return 0; }

  void
  stirred_tank::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::D2LTD2xpu_numRows() const { return 12; }
  integer stirred_tank::D2LTD2xpu_numCols() const { return 12; }
  integer stirred_tank::D2LTD2xpu_nnz()     const { return 0; }

  void
  stirred_tank::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::D2JUD2xpu_numRows() const { return 12; }
  integer stirred_tank::D2JUD2xpu_numCols() const { return 12; }
  integer stirred_tank::D2JUD2xpu_nnz()     const { return 4; }

  void
  stirred_tank::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 8   ; jIndex[0 ] = 8   ;
    iIndex[1 ] = 9   ; jIndex[1 ] = 9   ;
    iIndex[2 ] = 10  ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 11  ; jIndex[3 ] = 11  ;
  }


  void
  stirred_tank::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Control_D_1_1(U__[iU_u1], 0, 20);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(U__[iU_u2], 0, 6);
    result__[ 2   ] = ALIAS_u3Control_D_1_1(U__[iU_u3], 0, 4);
    result__[ 3   ] = ALIAS_u4Control_D_1_1(U__[iU_u4], 0, 20);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::DLTargsDxpu_numRows() const { return 0; }
  integer stirred_tank::DLTargsDxpu_numCols() const { return 12; }
  integer stirred_tank::DLTargsDxpu_nnz()     const { return 0; }

  void
  stirred_tank::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::D2LTargsD2xpu_numRows() const { return 12; }
  integer stirred_tank::D2LTargsD2xpu_numCols() const { return 12; }
  integer stirred_tank::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  stirred_tank::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: stirred_tank_Methods_AdjointODE.cc
