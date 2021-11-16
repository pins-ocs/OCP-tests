/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods_AdjointODE.cc                            |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  MaximumAscent::Hx_numEqns() const
  { return 4; }

  void
  MaximumAscent::Hx_eval(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = eta(t2);
    real_type t4   = X__[iX_v];
    real_type t5   = L__[iL_lambda2__xo];
    real_type t6   = t4 * t5;
    real_type t7   = L__[iL_lambda3__xo];
    real_type t9   = X__[iX_u] * t7;
    real_type t10  = L__[iL_lambda4__xo];
    real_type t13  = X__[iX_r];
    real_type t18  = t13 * t13;
    result__[ 0   ] = -1.0 / t18 / t13 * (t13 * (t6 - t9 + t10) * t4 - 2 * t5) * t3;
    real_type t27  = 1.0 / t13;
    result__[ 1   ] = t27 * (t13 * L__[iL_lambda1__xo] - t4 * t7) * t3;
    result__[ 2   ] = t27 * (2 * t6 - t9 + t10) * t3;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DHxDx_numRows() const
  { return 4; }

  integer
  MaximumAscent::DHxDx_numCols() const
  { return 4; }

  integer
  MaximumAscent::DHxDx_nnz() const
  { return 8; }

  void
  MaximumAscent::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 2   ;
  }

  void
  MaximumAscent::DHxDx_sparse(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = eta(t2);
    real_type t4   = X__[iX_v];
    real_type t5   = L__[iL_lambda2__xo];
    real_type t6   = t4 * t5;
    real_type t7   = L__[iL_lambda3__xo];
    real_type t9   = X__[iX_u] * t7;
    real_type t10  = L__[iL_lambda4__xo];
    real_type t13  = X__[iX_r];
    real_type t18  = t13 * t13;
    real_type t19  = t18 * t18;
    result__[ 0   ] = 2 / t19 * (t13 * (t6 - t9 + t10) * t4 - 3 * t5) * t3;
    real_type t22  = t3 * t7;
    real_type t23  = 1.0 / t18;
    result__[ 1   ] = t23 * t4 * t22;
    result__[ 2   ] = t23 * t3 * (-2 * t6 + t9 - t10);
    result__[ 3   ] = result__[1];
    real_type t28  = 1.0 / t13;
    result__[ 4   ] = -t28 * t22;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 2 * t28 * t3 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DHxDp_numRows() const
  { return 4; }

  integer
  MaximumAscent::DHxDp_numCols() const
  { return 0; }

  integer
  MaximumAscent::DHxDp_nnz() const
  { return 0; }

  void
  MaximumAscent::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DHxDp_sparse(
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
  MaximumAscent::Hu_numEqns() const
  { return 1; }

  void
  MaximumAscent::Hu_eval(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = Tbar(t2);
    real_type t4   = U__[iU_alpha];
    real_type t5   = sin(t4);
    real_type t8   = cos(t4);
    result__[ 0   ] = 1.0 / (Q__[iQ_zeta] * ModelPars[iM_mdot] * t2 - ModelPars[iM_m0]) * (L__[iL_lambda3__xo] * t5 - L__[iL_lambda2__xo] * t8) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DHuDx_numRows() const
  { return 1; }

  integer
  MaximumAscent::DHuDx_numCols() const
  { return 4; }

  integer
  MaximumAscent::DHuDx_nnz() const
  { return 0; }

  void
  MaximumAscent::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DHuDp_numRows() const
  { return 1; }

  integer
  MaximumAscent::DHuDp_numCols() const
  { return 0; }

  integer
  MaximumAscent::DHuDp_nnz() const
  { return 0; }

  void
  MaximumAscent::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DHuDp_sparse(
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
  MaximumAscent::Hp_numEqns() const
  { return 0; }

  void
  MaximumAscent::Hp_eval(
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
  MaximumAscent::DHpDp_numRows() const
  { return 0; }

  integer
  MaximumAscent::DHpDp_numCols() const
  { return 0; }

  integer
  MaximumAscent::DHpDp_nnz() const
  { return 0; }

  void
  MaximumAscent::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DHpDp_sparse(
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
  MaximumAscent::eta_numEqns() const
  { return 4; }

  void
  MaximumAscent::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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

  integer
  MaximumAscent::DetaDx_numRows() const
  { return 4; }

  integer
  MaximumAscent::DetaDx_numCols() const
  { return 4; }

  integer
  MaximumAscent::DetaDx_nnz() const
  { return 0; }

  void
  MaximumAscent::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DetaDp_numRows() const
  { return 4; }

  integer
  MaximumAscent::DetaDp_numCols() const
  { return 0; }

  integer
  MaximumAscent::DetaDp_nnz() const
  { return 0; }

  void
  MaximumAscent::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DetaDp_sparse(
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
  MaximumAscent::nu_numEqns() const
  { return 4; }

  void
  MaximumAscent::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
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

  integer
  MaximumAscent::DnuDx_numRows() const
  { return 4; }

  integer
  MaximumAscent::DnuDx_numCols() const
  { return 4; }

  integer
  MaximumAscent::DnuDx_nnz() const
  { return 0; }

  void
  MaximumAscent::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::DnuDp_numRows() const
  { return 4; }

  integer
  MaximumAscent::DnuDp_numCols() const
  { return 0; }

  integer
  MaximumAscent::DnuDp_nnz() const
  { return 0; }

  void
  MaximumAscent::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: MaximumAscent_Methods_AdjointODE.cc
