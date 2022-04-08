/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_AdjointODE.cc                         |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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

  integer TwoPhaseSchwartz::JPx_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::LTx_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::LTx_eval(
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
    real_type t17  = ALIAS_bound2_D(-0.8e0 - t5);
    result__[ 1   ] = (-0.2222222222e2 * t5 + 0.8888888886e1) * t10 - t17;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JUx_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JPp_numEqns() const { return 0; }

  void
  TwoPhaseSchwartz::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::LTp_numEqns() const { return 0; }

  void
  TwoPhaseSchwartz::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JUp_numEqns() const { return 0; }

  void
  TwoPhaseSchwartz::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JPu_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::LTu_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::JUu_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::JUu_eval(
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
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
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
  integer TwoPhaseSchwartz::DJPxDxp_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DJPxDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DJPxDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DLTxDxp_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DLTxDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DLTxDxp_nnz()     const { return 4; }

  void
  TwoPhaseSchwartz::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::DLTxDxp_sparse(
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
    real_type t9   = 1 - 9 * t3 - t8;
    real_type t10  = ALIAS_bound1_DD(t9);
    real_type t12  = -18 * t2;
    real_type t13  = t12 * t12;
    real_type t15  = ALIAS_bound1_D(t9);
    result__[ 0   ] = t10 * t13 - 18 * t15;
    real_type t18  = -0.2222222222e2 * t5 + 0.8888888886e1;
    result__[ 1   ] = t12 * t18 * t10;
    result__[ 2   ] = result__[1];
    real_type t20  = t18 * t18;
    real_type t24  = ALIAS_bound2_DD(-0.8e0 - t5);
    result__[ 3   ] = t20 * t10 - 0.2222222222e2 * t15 + t24;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJUxDxp_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DJUxDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DJUxDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJPuDxp_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DJPuDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DJPuDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DLTuDxp_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DLTuDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DLTuDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJUuDxp_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DJUuDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DJUuDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJPpDp_numRows() const { return 0; }
  integer TwoPhaseSchwartz::DJPpDp_numCols() const { return 0; }
  integer TwoPhaseSchwartz::DJPpDp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DLTpDp_numRows() const { return 0; }
  integer TwoPhaseSchwartz::DLTpDp_numCols() const { return 0; }
  integer TwoPhaseSchwartz::DLTpDp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DJUpDp_numRows() const { return 0; }
  integer TwoPhaseSchwartz::DJUpDp_numCols() const { return 0; }
  integer TwoPhaseSchwartz::DJUpDp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DLTargsDxup_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DLTargsDxup_numCols() const { return 6; }
  integer TwoPhaseSchwartz::DLTargsDxup_nnz()     const { return 3; }

  void
  TwoPhaseSchwartz::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::DLTargsDxup_sparse(
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
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 3, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::D2LTargsD2xup_numRows() const { return 6; }
  integer TwoPhaseSchwartz::D2LTargsD2xup_numCols() const { return 6; }
  integer TwoPhaseSchwartz::D2LTargsD2xup_nnz()     const { return 2; }

  void
  TwoPhaseSchwartz::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  TwoPhaseSchwartz::D2LTargsD2xup_sparse(
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
      Mechatronix::check_in_segment( result__, "D2LTargsD2xup_sparse", 2, i_segment );
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::Hx_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_x1];
    result__[ 0   ] = -0.4e0 * X__[iX_x2] * t2 * t1;
    real_type t8   = t2 * t2;
    result__[ 1   ] = L__[iL_lambda1__xo] + (-0.1e0 - 0.2e0 * t8) * t1;
    real_type t13  = ModelPars[iM_T2];
    real_type t14  = t13 * L__[iL_lambda4__xo];
    real_type t15  = X__[iX_x3];
    result__[ 2   ] = -0.4e0 * X__[iX_x4] * t15 * t14;
    real_type t22  = t15 * t15;
    result__[ 3   ] = t13 * L__[iL_lambda3__xo] + (-0.1e0 - 0.2e0 * t22) * t14;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::Hp_numEqns() const { return 0; }

  void
  TwoPhaseSchwartz::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DHxDxp_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DHxDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DHxDxp_nnz()     const { return 6; }

  void
  TwoPhaseSchwartz::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
  }


  void
  TwoPhaseSchwartz::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    result__[ 0   ] = -0.4e0 * X__[iX_x2] * t1;
    result__[ 1   ] = -0.4e0 * X__[iX_x1] * t1;
    result__[ 2   ] = result__[1];
    real_type t10  = ModelPars[iM_T2] * L__[iL_lambda4__xo];
    result__[ 3   ] = -0.4e0 * X__[iX_x4] * t10;
    result__[ 4   ] = -0.4e0 * X__[iX_x3] * t10;
    result__[ 5   ] = result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DHpDp_numRows() const { return 0; }
  integer TwoPhaseSchwartz::DHpDp_numCols() const { return 0; }
  integer TwoPhaseSchwartz::DHpDp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::Hu_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda2__xo];
    result__[ 1   ] = L__[iL_lambda4__xo] * ModelPars[iM_T2] + 2 * ModelPars[iM_epsilon] * U__[iU_u2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DHuDxp_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DHuDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DHuDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::eta_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DetaDxp_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DetaDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DetaDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::nu_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DnuDxp_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DnuDxp_numCols() const { return 4; }
  integer TwoPhaseSchwartz::DnuDxp_nnz()     const { return 0; }

  void
  TwoPhaseSchwartz::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TwoPhaseSchwartz::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: TwoPhaseSchwartz_Methods_AdjointODE.cc
