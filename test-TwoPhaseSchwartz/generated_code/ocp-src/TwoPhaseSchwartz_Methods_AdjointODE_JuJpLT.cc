/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_AdjointODE.cc                         |
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


#include "TwoPhaseSchwartz.hh"
#include "TwoPhaseSchwartz_Pars.hh"

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
#define ALIAS_bound2_DD(__t1) bound2.DD( __t1)
#define ALIAS_bound2_D(__t1) bound2.D( __t1)
#define ALIAS_bound1_DD(__t1) bound1.DD( __t1)
#define ALIAS_bound1_D(__t1) bound1.D( __t1)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoPhaseSchwartzDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JP_numEqns() const { return 0; }

  void
  TwoPhaseSchwartz::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::LT_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = pow(X__[iX_x1] - 1, 2);
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    result__[ 0   ] = bound1(1 - 9 * t3 - t8);
    result__[ 1   ] = bound2(-0.8e0 - t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JU_numEqns() const { return 1; }

  void
  TwoPhaseSchwartz::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = u1Control(U__[iU_u1], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::LTargs_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = pow(X__[iX_x1] - 1, 2);
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    result__[ 0   ] = 1 - 9 * t3 - t8;
    result__[ 1   ] = -0.8e0 - t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 2, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJPDxpu_numRows() const { return 0; }
  integer TwoPhaseSchwartz::DJPDxpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::DJPDxpu_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DLTDxpu_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DLTDxpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::DLTDxpu_nnz()     const { return 3; }

  void
  TwoPhaseSchwartz::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_x1] - 1;
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    real_type t10  = ALIAS_bound1_D(1 - 9 * t3 - t8);
    result__[ 0   ] = -18 * t2 * t10;
    result__[ 1   ] = (-0.2222222222e2 * t5 + 0.8888888886e1) * t10;
    real_type t16  = ALIAS_bound2_D(-0.8e0 - t5);
    result__[ 2   ] = -t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJUDxpu_numRows() const { return 1; }
  integer TwoPhaseSchwartz::DJUDxpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::DJUDxpu_nnz()     const { return 1; }

  void
  TwoPhaseSchwartz::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }


  void
  TwoPhaseSchwartz::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DLTargsDxpu_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DLTargsDxpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::DLTargsDxpu_nnz()     const { return 3; }

  void
  TwoPhaseSchwartz::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -18 * X__[iX_x1] + 18;
    result__[ 1   ] = -0.2222222222e2 * X__[iX_x2] + 0.8888888886e1;
    result__[ 2   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 3, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::D2JPD2xpu_numRows() const { return 6; }
  integer TwoPhaseSchwartz::D2JPD2xpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::D2JPD2xpu_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::D2LTD2xpu_numRows() const { return 6; }
  integer TwoPhaseSchwartz::D2LTD2xpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::D2LTD2xpu_nnz()     const { return 4; }

  void
  TwoPhaseSchwartz::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::D2LTD2xpu_sparse(
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
    real_type t2   = X__[iX_x1] - 1;
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    real_type t9   = 1 - 9 * t3 - t8;
    real_type t10  = ALIAS_bound1_DD(t9);
    real_type t12  = -18 * t2;
    real_type t13  = t12 * t12;
    real_type t15  = OMEGA__[0];
    real_type t17  = ALIAS_bound1_D(t9);
    real_type t18  = t15 * t17;
    result__[ 0   ] = t15 * t13 * t10 - 18 * t18;
    real_type t21  = -0.2222222222e2 * t5 + 0.8888888886e1;
    result__[ 1   ] = t15 * t12 * t21 * t10;
    result__[ 2   ] = result__[1];
    real_type t24  = t21 * t21;
    real_type t29  = ALIAS_bound2_DD(-0.8e0 - t5);
    result__[ 3   ] = t15 * t24 * t10 - 0.2222222222e2 * t18 + OMEGA__[1] * t29;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::D2JUD2xpu_numRows() const { return 6; }
  integer TwoPhaseSchwartz::D2JUD2xpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::D2JUD2xpu_nnz()     const { return 1; }

  void
  TwoPhaseSchwartz::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
  }


  void
  TwoPhaseSchwartz::D2JUD2xpu_sparse(
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
    real_type t2   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    result__[ 0   ] = OMEGA__[0] * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::D2LTargsD2xpu_numRows() const { return 6; }
  integer TwoPhaseSchwartz::D2LTargsD2xpu_numCols() const { return 6; }
  integer TwoPhaseSchwartz::D2LTargsD2xpu_nnz()     const { return 2; }

  void
  TwoPhaseSchwartz::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::D2LTargsD2xpu_sparse(
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
    real_type t1   = OMEGA__[0];
    result__[ 0   ] = -18 * t1;
    result__[ 1   ] = -0.2222222222e2 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 2, i_segment );
  }

}

// EOF: TwoPhaseSchwartz_Methods_AdjointODE.cc
