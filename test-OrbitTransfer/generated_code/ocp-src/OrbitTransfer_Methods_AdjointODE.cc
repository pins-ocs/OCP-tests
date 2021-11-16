/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_AdjointODE.cc                            |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  OrbitTransfer::Hx_numEqns() const
  { return 5; }

  void
  OrbitTransfer::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = U__[iU_theta];
    real_type t5   = sin(t4);
    real_type t6   = L__[iL_lambda2__xo];
    real_type t8   = cos(t4);
    real_type t9   = L__[iL_lambda3__xo];
    real_type t13  = X__[iX_m] * X__[iX_m];
    result__[ 0   ] = -1.0 / t13 * (t6 * t5 + t9 * t8) * t2 * ModelPars[iM_T];
    result__[ 1   ] = 0;
    real_type t17  = X__[iX_v];
    real_type t18  = t17 * t6;
    real_type t20  = X__[iX_u] * t9;
    real_type t21  = L__[iL_lambda5__xo];
    real_type t24  = X__[iX_r];
    real_type t31  = t24 * t24;
    result__[ 2   ] = -1.0 / t31 / t24 * (t24 * (t18 - t20 + t21) * t17 - 2 * ModelPars[iM_mu] * t6) * t2;
    real_type t38  = 1.0 / t24;
    result__[ 3   ] = -t38 * t17 * t2 * t9 + t2 * L__[iL_lambda1__xo];
    result__[ 4   ] = t38 * (2 * t18 - t20 + t21) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DHxDx_numRows() const
  { return 5; }

  integer
  OrbitTransfer::DHxDx_numCols() const
  { return 5; }

  integer
  OrbitTransfer::DHxDx_nnz() const
  { return 9; }

  void
  OrbitTransfer::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
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
  OrbitTransfer::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = U__[iU_theta];
    real_type t5   = cos(t4);
    real_type t6   = L__[iL_lambda3__xo];
    real_type t8   = sin(t4);
    real_type t9   = L__[iL_lambda2__xo];
    real_type t12  = X__[iX_m];
    real_type t13  = t12 * t12;
    result__[ 0   ] = 2 / t13 / t12 * (t6 * t5 + t9 * t8) * t2 * ModelPars[iM_T];
    real_type t18  = X__[iX_v];
    real_type t19  = t18 * t9;
    real_type t21  = X__[iX_u] * t6;
    real_type t22  = L__[iL_lambda5__xo];
    real_type t25  = X__[iX_r];
    real_type t32  = t25 * t25;
    real_type t33  = t32 * t32;
    result__[ 1   ] = 2 / t33 * (t25 * (t19 - t21 + t22) * t18 - 3 * t9 * ModelPars[iM_mu]) * t2;
    real_type t36  = t2 * t6;
    real_type t37  = 1.0 / t32;
    result__[ 2   ] = t37 * t18 * t36;
    result__[ 3   ] = t37 * t2 * (-2 * t19 + t21 - t22);
    result__[ 4   ] = result__[2];
    real_type t42  = 1.0 / t25;
    result__[ 5   ] = -t42 * t36;
    result__[ 6   ] = result__[3];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = 2 * t42 * t2 * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DHxDp_numRows() const
  { return 5; }

  integer
  OrbitTransfer::DHxDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DHxDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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

  integer
  OrbitTransfer::Hu_numEqns() const
  { return 1; }

  void
  OrbitTransfer::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = U__[iU_theta];
    real_type t5   = cos(t4);
    real_type t8   = sin(t4);
    result__[ 0   ] = 1.0 / X__[iX_m] * (L__[iL_lambda2__xo] * t5 - L__[iL_lambda3__xo] * t8) * ModelPars[iM_T] * ModelPars[iM_tf];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DHuDx_numRows() const
  { return 1; }

  integer
  OrbitTransfer::DHuDx_numCols() const
  { return 5; }

  integer
  OrbitTransfer::DHuDx_nnz() const
  { return 1; }

  void
  OrbitTransfer::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = U__[iU_theta];
    real_type t5   = cos(t4);
    real_type t8   = sin(t4);
    real_type t13  = X__[iX_m] * X__[iX_m];
    result__[ 0   ] = -1.0 / t13 * (L__[iL_lambda2__xo] * t5 - L__[iL_lambda3__xo] * t8) * ModelPars[iM_T] * ModelPars[iM_tf];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DHuDp_numRows() const
  { return 1; }

  integer
  OrbitTransfer::DHuDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DHuDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  OrbitTransfer::Hp_numEqns() const
  { return 0; }

  void
  OrbitTransfer::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DHpDp_numRows() const
  { return 0; }

  integer
  OrbitTransfer::DHpDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DHpDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
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
  integer
  OrbitTransfer::eta_numEqns() const
  { return 5; }

  void
  OrbitTransfer::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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

  integer
  OrbitTransfer::DetaDx_numRows() const
  { return 5; }

  integer
  OrbitTransfer::DetaDx_numCols() const
  { return 5; }

  integer
  OrbitTransfer::DetaDx_nnz() const
  { return 0; }

  void
  OrbitTransfer::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DetaDp_numRows() const
  { return 5; }

  integer
  OrbitTransfer::DetaDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DetaDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  OrbitTransfer::nu_numEqns() const
  { return 5; }

  void
  OrbitTransfer::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
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

  integer
  OrbitTransfer::DnuDx_numRows() const
  { return 5; }

  integer
  OrbitTransfer::DnuDx_numCols() const
  { return 5; }

  integer
  OrbitTransfer::DnuDx_nnz() const
  { return 0; }

  void
  OrbitTransfer::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DnuDp_numRows() const
  { return 5; }

  integer
  OrbitTransfer::DnuDp_numCols() const
  { return 0; }

  integer
  OrbitTransfer::DnuDp_nnz() const
  { return 0; }

  void
  OrbitTransfer::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: OrbitTransfer_Methods_AdjointODE.cc
