/*-----------------------------------------------------------------------*\
 |  file: BangBangF_Methods_AdjointODE.cc                                |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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


#include "BangBangF.hh"
#include "BangBangF_Pars.hh"

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
#define ALIAS_C1_constr_DD(__t1) C1_constr.DD( __t1)
#define ALIAS_C1_constr_D(__t1) C1_constr.D( __t1)
#define ALIAS_FControl_D_3(__t1, __t2, __t3) FControl.D_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2(__t1, __t2, __t3) FControl.D_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1(__t1, __t2, __t3) FControl.D_1( __t1, __t2, __t3)
#define ALIAS_FControl_D_3_3(__t1, __t2, __t3) FControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2_3(__t1, __t2, __t3) FControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_2_2(__t1, __t2, __t3) FControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_3(__t1, __t2, __t3) FControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_2(__t1, __t2, __t3) FControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FControl_D_1_1(__t1, __t2, __t3) FControl.D_1_1( __t1, __t2, __t3)


namespace BangBangFDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JPx_numEqns() const { return 2; }

  void
  BangBangF::JPx_eval(
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
      Mechatronix::check_in_segment( result__, "JPx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::LTx_numEqns() const { return 2; }

  void
  BangBangF::LTx_eval(
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
    real_type t1   = X__[iX_v];
    real_type t2   = C1(t1);
    real_type t3   = ALIAS_C1_constr_D(t2);
    real_type t4   = C1_D(t1);
    result__[ 1   ] = t4 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JUx_numEqns() const { return 2; }

  void
  BangBangF::JUx_eval(
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
      Mechatronix::check_in_segment( result__, "JUx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JPp_numEqns() const { return 0; }

  void
  BangBangF::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::LTp_numEqns() const { return 0; }

  void
  BangBangF::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JUp_numEqns() const { return 0; }

  void
  BangBangF::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JPu_numEqns() const { return 1; }

  void
  BangBangF::JPu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::LTu_numEqns() const { return 1; }

  void
  BangBangF::LTu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::JUu_numEqns() const { return 1; }

  void
  BangBangF::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_FControl_D_1(U__[iU_F], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::LTargs_numEqns() const { return 1; }

  void
  BangBangF::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = C1(X__[iX_v]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJPxDxp_numRows() const { return 2; }
  integer BangBangF::DJPxDxp_numCols() const { return 2; }
  integer BangBangF::DJPxDxp_nnz()     const { return 0; }

  void
  BangBangF::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DLTxDxp_numRows() const { return 2; }
  integer BangBangF::DLTxDxp_numCols() const { return 2; }
  integer BangBangF::DLTxDxp_nnz()     const { return 1; }

  void
  BangBangF::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = C1(t1);
    real_type t3   = ALIAS_C1_constr_DD(t2);
    real_type t4   = C1_D(t1);
    real_type t5   = t4 * t4;
    real_type t7   = ALIAS_C1_constr_D(t2);
    real_type t8   = C1_DD(t1);
    result__[ 0   ] = t5 * t3 + t8 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJUxDxp_numRows() const { return 2; }
  integer BangBangF::DJUxDxp_numCols() const { return 2; }
  integer BangBangF::DJUxDxp_nnz()     const { return 0; }

  void
  BangBangF::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJPuDxp_numRows() const { return 1; }
  integer BangBangF::DJPuDxp_numCols() const { return 2; }
  integer BangBangF::DJPuDxp_nnz()     const { return 0; }

  void
  BangBangF::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DLTuDxp_numRows() const { return 1; }
  integer BangBangF::DLTuDxp_numCols() const { return 2; }
  integer BangBangF::DLTuDxp_nnz()     const { return 0; }

  void
  BangBangF::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJUuDxp_numRows() const { return 1; }
  integer BangBangF::DJUuDxp_numCols() const { return 2; }
  integer BangBangF::DJUuDxp_nnz()     const { return 0; }

  void
  BangBangF::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJPpDp_numRows() const { return 0; }
  integer BangBangF::DJPpDp_numCols() const { return 0; }
  integer BangBangF::DJPpDp_nnz()     const { return 0; }

  void
  BangBangF::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DLTpDp_numRows() const { return 0; }
  integer BangBangF::DLTpDp_numCols() const { return 0; }
  integer BangBangF::DLTpDp_nnz()     const { return 0; }

  void
  BangBangF::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DJUpDp_numRows() const { return 0; }
  integer BangBangF::DJUpDp_numCols() const { return 0; }
  integer BangBangF::DJUpDp_nnz()     const { return 0; }

  void
  BangBangF::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DLTargsDxup_numRows() const { return 1; }
  integer BangBangF::DLTargsDxup_numCols() const { return 3; }
  integer BangBangF::DLTargsDxup_nnz()     const { return 1; }

  void
  BangBangF::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = C1_D(X__[iX_v]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 1, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::D2LTargsD2xup_numRows() const { return 3; }
  integer BangBangF::D2LTargsD2xup_numCols() const { return 3; }
  integer BangBangF::D2LTargsD2xup_nnz()     const { return 1; }

  void
  BangBangF::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
  }


  void
  BangBangF::D2LTargsD2xup_sparse(
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
    real_type t2   = C1_DD(X__[iX_v]);
    result__[ 0   ] = OMEGA__[0] * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xup_sparse", 1, i_segment );
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

  integer BangBangF::Hx_numEqns() const { return 2; }

  void
  BangBangF::Hx_eval(
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
    result__[ 0   ] = 0;
    result__[ 1   ] = L__[iL_lambda1__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangF::Hp_numEqns() const { return 0; }

  void
  BangBangF::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DHxDxp_numRows() const { return 2; }
  integer BangBangF::DHxDxp_numCols() const { return 2; }
  integer BangBangF::DHxDxp_nnz()     const { return 0; }

  void
  BangBangF::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DHpDp_numRows() const { return 0; }
  integer BangBangF::DHpDp_numCols() const { return 0; }
  integer BangBangF::DHpDp_nnz()     const { return 0; }

  void
  BangBangF::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DHpDp_sparse(
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

  integer BangBangF::Hu_numEqns() const { return 1; }

  void
  BangBangF::Hu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DHuDxp_numRows() const { return 1; }
  integer BangBangF::DHuDxp_numCols() const { return 2; }
  integer BangBangF::DHuDxp_nnz()     const { return 0; }

  void
  BangBangF::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DHuDxp_sparse(
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

  integer BangBangF::eta_numEqns() const { return 2; }

  void
  BangBangF::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DetaDxp_numRows() const { return 2; }
  integer BangBangF::DetaDxp_numCols() const { return 2; }
  integer BangBangF::DetaDxp_nnz()     const { return 0; }

  void
  BangBangF::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DetaDxp_sparse(
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

  integer BangBangF::nu_numEqns() const { return 2; }

  void
  BangBangF::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangF::DnuDxp_numRows() const { return 2; }
  integer BangBangF::DnuDxp_numCols() const { return 2; }
  integer BangBangF::DnuDxp_nnz()     const { return 0; }

  void
  BangBangF::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangF::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangF_Methods_AdjointODE.cc
