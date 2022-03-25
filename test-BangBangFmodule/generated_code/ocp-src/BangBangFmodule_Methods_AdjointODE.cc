/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Methods_AdjointODE.cc                          |
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

  integer BangBangFmodule::JPx_numEqns() const { return 2; }

  void
  BangBangFmodule::JPx_eval(
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

  integer BangBangFmodule::LTx_numEqns() const { return 2; }

  void
  BangBangFmodule::LTx_eval(
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

  integer BangBangFmodule::JUx_numEqns() const { return 2; }

  void
  BangBangFmodule::JUx_eval(
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

  integer BangBangFmodule::JPp_numEqns() const { return 0; }

  void
  BangBangFmodule::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::LTp_numEqns() const { return 0; }

  void
  BangBangFmodule::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::JUp_numEqns() const { return 0; }

  void
  BangBangFmodule::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::JPu_numEqns() const { return 2; }

  void
  BangBangFmodule::JPu_eval(
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

  integer BangBangFmodule::LTu_numEqns() const { return 2; }

  void
  BangBangFmodule::LTu_eval(
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

  integer BangBangFmodule::JUu_numEqns() const { return 2; }

  void
  BangBangFmodule::JUu_eval(
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
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
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
  integer BangBangFmodule::DJPxDxp_numRows() const { return 2; }
  integer BangBangFmodule::DJPxDxp_numCols() const { return 2; }
  integer BangBangFmodule::DJPxDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DLTxDxp_numRows() const { return 2; }
  integer BangBangFmodule::DLTxDxp_numCols() const { return 2; }
  integer BangBangFmodule::DLTxDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJUxDxp_numRows() const { return 2; }
  integer BangBangFmodule::DJUxDxp_numCols() const { return 2; }
  integer BangBangFmodule::DJUxDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJPuDxp_numRows() const { return 2; }
  integer BangBangFmodule::DJPuDxp_numCols() const { return 2; }
  integer BangBangFmodule::DJPuDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DLTuDxp_numRows() const { return 2; }
  integer BangBangFmodule::DLTuDxp_numCols() const { return 2; }
  integer BangBangFmodule::DLTuDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJUuDxp_numRows() const { return 2; }
  integer BangBangFmodule::DJUuDxp_numCols() const { return 2; }
  integer BangBangFmodule::DJUuDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJPpDp_numRows() const { return 0; }
  integer BangBangFmodule::DJPpDp_numCols() const { return 0; }
  integer BangBangFmodule::DJPpDp_nnz()     const { return 0; }

  void
  BangBangFmodule::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DLTpDp_numRows() const { return 0; }
  integer BangBangFmodule::DLTpDp_numCols() const { return 0; }
  integer BangBangFmodule::DLTpDp_nnz()     const { return 0; }

  void
  BangBangFmodule::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DJUpDp_numRows() const { return 0; }
  integer BangBangFmodule::DJUpDp_numCols() const { return 0; }
  integer BangBangFmodule::DJUpDp_nnz()     const { return 0; }

  void
  BangBangFmodule::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DLTargsDxup_numRows() const { return 0; }
  integer BangBangFmodule::DLTargsDxup_numCols() const { return 4; }
  integer BangBangFmodule::DLTargsDxup_nnz()     const { return 0; }

  void
  BangBangFmodule::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::D2LTargsD2xup_numRows() const { return 4; }
  integer BangBangFmodule::D2LTargsD2xup_numCols() const { return 4; }
  integer BangBangFmodule::D2LTargsD2xup_nnz()     const { return 0; }

  void
  BangBangFmodule::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::D2LTargsD2xup_sparse(
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

  integer BangBangFmodule::Hx_numEqns() const { return 2; }

  void
  BangBangFmodule::Hx_eval(
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

  integer BangBangFmodule::Hp_numEqns() const { return 0; }

  void
  BangBangFmodule::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DHxDxp_numRows() const { return 2; }
  integer BangBangFmodule::DHxDxp_numCols() const { return 2; }
  integer BangBangFmodule::DHxDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DHpDp_numRows() const { return 0; }
  integer BangBangFmodule::DHpDp_numCols() const { return 0; }
  integer BangBangFmodule::DHpDp_nnz()     const { return 0; }

  void
  BangBangFmodule::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DHpDp_sparse(
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

  integer BangBangFmodule::Hu_numEqns() const { return 2; }

  void
  BangBangFmodule::Hu_eval(
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
    real_type t1   = L__[iL_lambda2__xo];
    result__[ 0   ] = 1 + t1;
    result__[ 1   ] = 1 - t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DHuDxp_numRows() const { return 2; }
  integer BangBangFmodule::DHuDxp_numCols() const { return 2; }
  integer BangBangFmodule::DHuDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DHuDxp_sparse(
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

  integer BangBangFmodule::eta_numEqns() const { return 2; }

  void
  BangBangFmodule::eta_eval(
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
  integer BangBangFmodule::DetaDxp_numRows() const { return 2; }
  integer BangBangFmodule::DetaDxp_numCols() const { return 2; }
  integer BangBangFmodule::DetaDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DetaDxp_sparse(
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

  integer BangBangFmodule::nu_numEqns() const { return 2; }

  void
  BangBangFmodule::nu_eval(
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
  integer BangBangFmodule::DnuDxp_numRows() const { return 2; }
  integer BangBangFmodule::DnuDxp_numCols() const { return 2; }
  integer BangBangFmodule::DnuDxp_nnz()     const { return 0; }

  void
  BangBangFmodule::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFmodule_Methods_AdjointODE.cc
