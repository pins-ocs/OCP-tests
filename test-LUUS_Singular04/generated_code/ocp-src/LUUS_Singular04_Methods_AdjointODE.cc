/*-----------------------------------------------------------------------*\
 |  file: LUUS_Singular04_Methods_AdjointODE.cc                          |
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


#include "LUUS_Singular04.hh"
#include "LUUS_Singular04_Pars.hh"

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


namespace LUUS_Singular04Define {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::JPx_numEqns() const { return 3; }

  void
  LUUS_Singular04::JPx_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::LTx_numEqns() const { return 3; }

  void
  LUUS_Singular04::LTx_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::JUx_numEqns() const { return 3; }

  void
  LUUS_Singular04::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = uControl(U__[iU_u], -1, 1);
    result__[ 0   ] = 2 * t3 * X__[iX_x1];
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::JPp_numEqns() const { return 0; }

  void
  LUUS_Singular04::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::LTp_numEqns() const { return 0; }

  void
  LUUS_Singular04::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::JUp_numEqns() const { return 0; }

  void
  LUUS_Singular04::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::JPu_numEqns() const { return 1; }

  void
  LUUS_Singular04::JPu_eval(
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

  integer LUUS_Singular04::LTu_numEqns() const { return 1; }

  void
  LUUS_Singular04::LTu_eval(
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

  integer LUUS_Singular04::JUu_numEqns() const { return 1; }

  void
  LUUS_Singular04::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_x1] * X__[iX_x1];
    real_type t4   = ModelPars[iM_epsi_x] * ModelPars[iM_epsi_x];
    real_type t7   = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 0   ] = t7 * (t2 + t4);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::LTargs_numEqns() const { return 0; }

  void
  LUUS_Singular04::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DJPxDxp_numRows() const { return 3; }
  integer LUUS_Singular04::DJPxDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DJPxDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DLTxDxp_numRows() const { return 3; }
  integer LUUS_Singular04::DLTxDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DLTxDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DJUxDxp_numRows() const { return 3; }
  integer LUUS_Singular04::DJUxDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DJUxDxp_nnz()     const { return 1; }

  void
  LUUS_Singular04::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  LUUS_Singular04::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = uControl(U__[iU_u], -1, 1);
    result__[ 0   ] = 2 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DJPuDxp_numRows() const { return 1; }
  integer LUUS_Singular04::DJPuDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DJPuDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DLTuDxp_numRows() const { return 1; }
  integer LUUS_Singular04::DLTuDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DLTuDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DJUuDxp_numRows() const { return 1; }
  integer LUUS_Singular04::DJUuDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DJUuDxp_nnz()     const { return 1; }

  void
  LUUS_Singular04::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  LUUS_Singular04::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 0   ] = 2 * t3 * X__[iX_x1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DJPpDp_numRows() const { return 0; }
  integer LUUS_Singular04::DJPpDp_numCols() const { return 0; }
  integer LUUS_Singular04::DJPpDp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DLTpDp_numRows() const { return 0; }
  integer LUUS_Singular04::DLTpDp_numCols() const { return 0; }
  integer LUUS_Singular04::DLTpDp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DJUpDp_numRows() const { return 0; }
  integer LUUS_Singular04::DJUpDp_numCols() const { return 0; }
  integer LUUS_Singular04::DJUpDp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DLTargsDxup_numRows() const { return 0; }
  integer LUUS_Singular04::DLTargsDxup_numCols() const { return 4; }
  integer LUUS_Singular04::DLTargsDxup_nnz()     const { return 0; }

  void
  LUUS_Singular04::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::D2LTargsD2xup_numRows() const { return 4; }
  integer LUUS_Singular04::D2LTargsD2xup_numCols() const { return 4; }
  integer LUUS_Singular04::D2LTargsD2xup_nnz()     const { return 0; }

  void
  LUUS_Singular04::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::D2LTargsD2xup_sparse(
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

  integer LUUS_Singular04::Hx_numEqns() const { return 3; }

  void
  LUUS_Singular04::Hx_eval(
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
    result__[ 0   ] = 2 * X__[iX_x1];
    result__[ 1   ] = L__[iL_lambda1__xo];
    result__[ 2   ] = L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_Singular04::Hp_numEqns() const { return 0; }

  void
  LUUS_Singular04::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DHxDxp_numRows() const { return 3; }
  integer LUUS_Singular04::DHxDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DHxDxp_nnz()     const { return 1; }

  void
  LUUS_Singular04::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  LUUS_Singular04::DHxDxp_sparse(
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
    result__[ 0   ] = 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DHpDp_numRows() const { return 0; }
  integer LUUS_Singular04::DHpDp_numCols() const { return 0; }
  integer LUUS_Singular04::DHpDp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DHpDp_sparse(
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

  integer LUUS_Singular04::Hu_numEqns() const { return 1; }

  void
  LUUS_Singular04::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DHuDxp_numRows() const { return 1; }
  integer LUUS_Singular04::DHuDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DHuDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DHuDxp_sparse(
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

  integer LUUS_Singular04::eta_numEqns() const { return 3; }

  void
  LUUS_Singular04::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DetaDxp_numRows() const { return 3; }
  integer LUUS_Singular04::DetaDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DetaDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DetaDxp_sparse(
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

  integer LUUS_Singular04::nu_numEqns() const { return 3; }

  void
  LUUS_Singular04::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_Singular04::DnuDxp_numRows() const { return 3; }
  integer LUUS_Singular04::DnuDxp_numCols() const { return 3; }
  integer LUUS_Singular04::DnuDxp_nnz()     const { return 0; }

  void
  LUUS_Singular04::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_Singular04::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: LUUS_Singular04_Methods_AdjointODE.cc
