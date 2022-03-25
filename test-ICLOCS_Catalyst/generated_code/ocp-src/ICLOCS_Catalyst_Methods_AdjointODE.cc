/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_Catalyst_Methods_AdjointODE.cc                          |
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


#include "ICLOCS_Catalyst.hh"
#include "ICLOCS_Catalyst_Pars.hh"

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


namespace ICLOCS_CatalystDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::JPx_numEqns() const { return 2; }

  void
  ICLOCS_Catalyst::JPx_eval(
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

  integer ICLOCS_Catalyst::LTx_numEqns() const { return 2; }

  void
  ICLOCS_Catalyst::LTx_eval(
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
      Mechatronix::check_in_segment( result__, "LTx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::JUx_numEqns() const { return 2; }

  void
  ICLOCS_Catalyst::JUx_eval(
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

  integer ICLOCS_Catalyst::JPp_numEqns() const { return 0; }

  void
  ICLOCS_Catalyst::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::LTp_numEqns() const { return 0; }

  void
  ICLOCS_Catalyst::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::JUp_numEqns() const { return 0; }

  void
  ICLOCS_Catalyst::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::JPu_numEqns() const { return 1; }

  void
  ICLOCS_Catalyst::JPu_eval(
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

  integer ICLOCS_Catalyst::LTu_numEqns() const { return 1; }

  void
  ICLOCS_Catalyst::LTu_eval(
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

  integer ICLOCS_Catalyst::JUu_numEqns() const { return 1; }

  void
  ICLOCS_Catalyst::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::LTargs_numEqns() const { return 0; }

  void
  ICLOCS_Catalyst::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DJPxDxp_numRows() const { return 2; }
  integer ICLOCS_Catalyst::DJPxDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DJPxDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DLTxDxp_numRows() const { return 2; }
  integer ICLOCS_Catalyst::DLTxDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DLTxDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DJUxDxp_numRows() const { return 2; }
  integer ICLOCS_Catalyst::DJUxDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DJUxDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DJPuDxp_numRows() const { return 1; }
  integer ICLOCS_Catalyst::DJPuDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DJPuDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DLTuDxp_numRows() const { return 1; }
  integer ICLOCS_Catalyst::DLTuDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DLTuDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DJUuDxp_numRows() const { return 1; }
  integer ICLOCS_Catalyst::DJUuDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DJUuDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DJPpDp_numRows() const { return 0; }
  integer ICLOCS_Catalyst::DJPpDp_numCols() const { return 0; }
  integer ICLOCS_Catalyst::DJPpDp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DLTpDp_numRows() const { return 0; }
  integer ICLOCS_Catalyst::DLTpDp_numCols() const { return 0; }
  integer ICLOCS_Catalyst::DLTpDp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DJUpDp_numRows() const { return 0; }
  integer ICLOCS_Catalyst::DJUpDp_numCols() const { return 0; }
  integer ICLOCS_Catalyst::DJUpDp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DLTargsDxup_numRows() const { return 0; }
  integer ICLOCS_Catalyst::DLTargsDxup_numCols() const { return 3; }
  integer ICLOCS_Catalyst::DLTargsDxup_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::D2LTargsD2xup_numRows() const { return 3; }
  integer ICLOCS_Catalyst::D2LTargsD2xup_numCols() const { return 3; }
  integer ICLOCS_Catalyst::D2LTargsD2xup_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
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

  integer ICLOCS_Catalyst::Hx_numEqns() const { return 2; }

  void
  ICLOCS_Catalyst::Hx_eval(
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
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = L__[iL_lambda2__xo];
    result__[ 0   ] = t2 * t4 - t3;
    result__[ 1   ] = 10 * t3 + (-9 * t2 - 1) * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::Hp_numEqns() const { return 0; }

  void
  ICLOCS_Catalyst::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DHxDxp_numRows() const { return 2; }
  integer ICLOCS_Catalyst::DHxDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DHxDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DHpDp_numRows() const { return 0; }
  integer ICLOCS_Catalyst::DHpDp_numCols() const { return 0; }
  integer ICLOCS_Catalyst::DHpDp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DHpDp_sparse(
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

  integer ICLOCS_Catalyst::Hu_numEqns() const { return 1; }

  void
  ICLOCS_Catalyst::Hu_eval(
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
    real_type t2   = X__[iX_x2];
    real_type t4   = X__[iX_x1];
    result__[ 0   ] = (10 * t2 - t4) * L__[iL_lambda1__xo] + (t4 - 9 * t2) * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_Catalyst::DHuDxp_numRows() const { return 1; }
  integer ICLOCS_Catalyst::DHuDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DHuDxp_nnz()     const { return 2; }

  void
  ICLOCS_Catalyst::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }


  void
  ICLOCS_Catalyst::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = L__[iL_lambda2__xo];
    result__[ 0   ] = -t1 + t2;
    result__[ 1   ] = 10 * t1 - 9 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 2, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_Catalyst::eta_numEqns() const { return 2; }

  void
  ICLOCS_Catalyst::eta_eval(
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
  integer ICLOCS_Catalyst::DetaDxp_numRows() const { return 2; }
  integer ICLOCS_Catalyst::DetaDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DetaDxp_sparse(
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

  integer ICLOCS_Catalyst::nu_numEqns() const { return 2; }

  void
  ICLOCS_Catalyst::nu_eval(
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
  integer ICLOCS_Catalyst::DnuDxp_numRows() const { return 2; }
  integer ICLOCS_Catalyst::DnuDxp_numCols() const { return 2; }
  integer ICLOCS_Catalyst::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS_Catalyst::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_Catalyst::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_Catalyst_Methods_AdjointODE.cc
