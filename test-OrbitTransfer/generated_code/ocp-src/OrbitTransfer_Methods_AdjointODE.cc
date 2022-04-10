/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_AdjointODE.cc                            |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


#include "OrbitTransfer.hh"
#include "OrbitTransfer_Pars.hh"

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


namespace OrbitTransferDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::JPx_numEqns() const { return 5; }

  void
  OrbitTransfer::JPx_eval(
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
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::LTx_numEqns() const { return 5; }

  void
  OrbitTransfer::LTx_eval(
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
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::JUx_numEqns() const { return 5; }

  void
  OrbitTransfer::JUx_eval(
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
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::JPp_numEqns() const { return 0; }

  void
  OrbitTransfer::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::LTp_numEqns() const { return 0; }

  void
  OrbitTransfer::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::JUp_numEqns() const { return 0; }

  void
  OrbitTransfer::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::JPu_numEqns() const { return 1; }

  void
  OrbitTransfer::JPu_eval(
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

  integer OrbitTransfer::LTu_numEqns() const { return 1; }

  void
  OrbitTransfer::LTu_eval(
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

  integer OrbitTransfer::JUu_numEqns() const { return 1; }

  void
  OrbitTransfer::JUu_eval(
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
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::LTargs_numEqns() const { return 0; }

  void
  OrbitTransfer::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DJPxDxp_numRows() const { return 5; }
  integer OrbitTransfer::DJPxDxp_numCols() const { return 5; }
  integer OrbitTransfer::DJPxDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DLTxDxp_numRows() const { return 5; }
  integer OrbitTransfer::DLTxDxp_numCols() const { return 5; }
  integer OrbitTransfer::DLTxDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DJUxDxp_numRows() const { return 5; }
  integer OrbitTransfer::DJUxDxp_numCols() const { return 5; }
  integer OrbitTransfer::DJUxDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DJPuDxp_numRows() const { return 1; }
  integer OrbitTransfer::DJPuDxp_numCols() const { return 5; }
  integer OrbitTransfer::DJPuDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DLTuDxp_numRows() const { return 1; }
  integer OrbitTransfer::DLTuDxp_numCols() const { return 5; }
  integer OrbitTransfer::DLTuDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DJUuDxp_numRows() const { return 1; }
  integer OrbitTransfer::DJUuDxp_numCols() const { return 5; }
  integer OrbitTransfer::DJUuDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DJPpDp_numRows() const { return 0; }
  integer OrbitTransfer::DJPpDp_numCols() const { return 0; }
  integer OrbitTransfer::DJPpDp_nnz()     const { return 0; }

  void
  OrbitTransfer::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DLTpDp_numRows() const { return 0; }
  integer OrbitTransfer::DLTpDp_numCols() const { return 0; }
  integer OrbitTransfer::DLTpDp_nnz()     const { return 0; }

  void
  OrbitTransfer::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DJUpDp_numRows() const { return 0; }
  integer OrbitTransfer::DJUpDp_numCols() const { return 0; }
  integer OrbitTransfer::DJUpDp_nnz()     const { return 0; }

  void
  OrbitTransfer::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DLTargsDxup_numRows() const { return 0; }
  integer OrbitTransfer::DLTargsDxup_numCols() const { return 6; }
  integer OrbitTransfer::DLTargsDxup_nnz()     const { return 0; }

  void
  OrbitTransfer::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::D2LTargsD2xup_numRows() const { return 6; }
  integer OrbitTransfer::D2LTargsD2xup_numCols() const { return 6; }
  integer OrbitTransfer::D2LTargsD2xup_nnz()     const { return 0; }

  void
  OrbitTransfer::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::D2LTargsD2xup_sparse(
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

  integer OrbitTransfer::Hx_numEqns() const { return 5; }

  void
  OrbitTransfer::Hx_eval(
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
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = sin(t5);
    real_type t9   = X__[iX_m] * X__[iX_m];
    real_type t10  = 1.0 / t9;
    real_type t14  = t2 * L__[iL_lambda3__xo];
    real_type t15  = cos(t5);
    result__[ 0   ] = -t10 * t15 * t4 * t14 - t10 * t6 * t4 * t3;
    result__[ 1   ] = 0;
    real_type t19  = X__[iX_v];
    real_type t20  = t19 * t19;
    real_type t21  = X__[iX_r];
    real_type t22  = t21 * t21;
    real_type t23  = 1.0 / t22;
    real_type t32  = X__[iX_u];
    real_type t37  = t2 * L__[iL_lambda5__xo];
    result__[ 2   ] = (-t23 * t20 + 2 / t22 / t21 * ModelPars[iM_mu]) * t3 + t23 * t32 * t19 * t14 - t23 * t19 * t37;
    real_type t42  = 1.0 / t21;
    real_type t43  = t42 * t19;
    result__[ 3   ] = -t43 * t14 + t2 * L__[iL_lambda1__xo];
    result__[ 4   ] = -t42 * t32 * t14 + 2 * t43 * t3 + t42 * t37;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::Hp_numEqns() const { return 0; }

  void
  OrbitTransfer::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DHxDxp_numRows() const { return 5; }
  integer OrbitTransfer::DHxDxp_numCols() const { return 5; }
  integer OrbitTransfer::DHxDxp_nnz()     const { return 9; }

  void
  OrbitTransfer::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
  }


  void
  OrbitTransfer::DHxDxp_sparse(
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
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = sin(t5);
    real_type t8   = X__[iX_m];
    real_type t9   = t8 * t8;
    real_type t11  = 1.0 / t9 / t8;
    real_type t15  = t2 * L__[iL_lambda3__xo];
    real_type t16  = cos(t5);
    result__[ 0   ] = 2 * t11 * t16 * t4 * t15 + 2 * t11 * t6 * t4 * t3;
    real_type t21  = X__[iX_v];
    real_type t22  = t21 * t21;
    real_type t23  = X__[iX_r];
    real_type t24  = t23 * t23;
    real_type t26  = 1.0 / t24 / t23;
    real_type t30  = t24 * t24;
    real_type t36  = X__[iX_u];
    real_type t42  = t2 * L__[iL_lambda5__xo];
    result__[ 1   ] = (2 * t26 * t22 - 6 / t30 * ModelPars[iM_mu]) * t3 - 2 * t26 * t36 * t21 * t15 + 2 * t26 * t21 * t42;
    real_type t46  = 1.0 / t24;
    real_type t47  = t46 * t21;
    result__[ 2   ] = t47 * t15;
    result__[ 3   ] = t46 * t36 * t15 - 2 * t47 * t3 - t46 * t42;
    result__[ 4   ] = result__[2];
    real_type t53  = 1.0 / t23;
    result__[ 5   ] = -t53 * t15;
    result__[ 6   ] = result__[3];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = 2 * t53 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DHpDp_numRows() const { return 0; }
  integer OrbitTransfer::DHpDp_numCols() const { return 0; }
  integer OrbitTransfer::DHpDp_nnz()     const { return 0; }

  void
  OrbitTransfer::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DHpDp_sparse(
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

  integer OrbitTransfer::Hu_numEqns() const { return 1; }

  void
  OrbitTransfer::Hu_eval(
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
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = cos(t5);
    real_type t9   = 1.0 / X__[iX_m];
    real_type t14  = sin(t5);
    result__[ 0   ] = -t9 * t14 * t4 * t2 * L__[iL_lambda3__xo] + t9 * t6 * t4 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DHuDxp_numRows() const { return 1; }
  integer OrbitTransfer::DHuDxp_numCols() const { return 5; }
  integer OrbitTransfer::DHuDxp_nnz()     const { return 1; }

  void
  OrbitTransfer::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  OrbitTransfer::DHuDxp_sparse(
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
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = cos(t5);
    real_type t9   = X__[iX_m] * X__[iX_m];
    real_type t10  = 1.0 / t9;
    real_type t15  = sin(t5);
    result__[ 0   ] = t10 * t15 * t4 * t2 * L__[iL_lambda3__xo] - t10 * t6 * t4 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 1, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::eta_numEqns() const { return 5; }

  void
  OrbitTransfer::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda4__xo];
    result__[ 1   ] = L__[iL_lambda5__xo];
    result__[ 2   ] = L__[iL_lambda1__xo];
    result__[ 3   ] = L__[iL_lambda2__xo];
    result__[ 4   ] = L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DetaDxp_numRows() const { return 5; }
  integer OrbitTransfer::DetaDxp_numCols() const { return 5; }
  integer OrbitTransfer::DetaDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DetaDxp_sparse(
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

  integer OrbitTransfer::nu_numEqns() const { return 5; }

  void
  OrbitTransfer::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[2];
    result__[ 1   ] = V__[3];
    result__[ 2   ] = V__[4];
    result__[ 3   ] = V__[0];
    result__[ 4   ] = V__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DnuDxp_numRows() const { return 5; }
  integer OrbitTransfer::DnuDxp_numCols() const { return 5; }
  integer OrbitTransfer::DnuDxp_nnz()     const { return 0; }

  void
  OrbitTransfer::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  OrbitTransfer::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: OrbitTransfer_Methods_AdjointODE.cc
