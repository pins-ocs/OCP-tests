/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods.cc                                    |
 |                                                                       |
 |  version: 1.0   date 19/1/2021                                        |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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


namespace Brachiostocrona2Define {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  Brachiostocrona2::Hx_numEqns() const
  { return 3; }

  void
  Brachiostocrona2::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    real_type t2   = P__[0];
    real_type t4   = U__[0];
    real_type t5   = cos(t4);
    real_type t9   = sin(t4);
    result__[ 2   ] = t5 * t2 * L__[0] + t9 * t2 * L__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DHxDx_numRows() const
  { return 3; }

  integer
  Brachiostocrona2::DHxDx_numCols() const
  { return 3; }

  integer
  Brachiostocrona2::DHxDx_nnz() const
  { return 0; }

  void
  Brachiostocrona2::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  Brachiostocrona2::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DHxDp_numRows() const
  { return 3; }

  integer
  Brachiostocrona2::DHxDp_numCols() const
  { return 1; }

  integer
  Brachiostocrona2::DHxDp_nnz() const
  { return 1; }

  void
  Brachiostocrona2::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = U__[0];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    result__[ 0   ] = t3 * L__[0] + t6 * L__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 1, i_segment );
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
  Brachiostocrona2::Hu_numEqns() const
  { return 1; }

  void
  Brachiostocrona2::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    real_type t4   = X__[2];
    real_type t5   = U__[0];
    real_type t6   = sin(t5);
    real_type t11  = cos(t5);
    result__[ 0   ] = t11 * t4 * t2 * L__[1] - t11 * ModelPars[2] * t2 * L__[2] - t6 * t4 * t2 * L__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DHuDx_numRows() const
  { return 1; }

  integer
  Brachiostocrona2::DHuDx_numCols() const
  { return 3; }

  integer
  Brachiostocrona2::DHuDx_nnz() const
  { return 1; }

  void
  Brachiostocrona2::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    real_type t4   = U__[0];
    real_type t5   = sin(t4);
    real_type t9   = cos(t4);
    result__[ 0   ] = -t5 * t2 * L__[0] + t9 * t2 * L__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DHuDp_numRows() const
  { return 1; }

  integer
  Brachiostocrona2::DHuDp_numCols() const
  { return 1; }

  integer
  Brachiostocrona2::DHuDp_nnz() const
  { return 1; }

  void
  Brachiostocrona2::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[2];
    real_type t4   = U__[0];
    real_type t5   = sin(t4);
    real_type t9   = cos(t4);
    result__[ 0   ] = -t5 * t2 * L__[0] + t9 * t2 * L__[1] - t9 * ModelPars[2] * L__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHuDp_sparse", 1, i_segment );
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
  Brachiostocrona2::Hp_numEqns() const
  { return 1; }

  void
  Brachiostocrona2::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[2];
    real_type t4   = U__[0];
    real_type t5   = cos(t4);
    real_type t9   = sin(t4);
    result__[ 0   ] = t5 * t2 * L__[0] + t9 * t2 * L__[1] - t9 * ModelPars[2] * L__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DHpDp_numRows() const
  { return 1; }

  integer
  Brachiostocrona2::DHpDp_numCols() const
  { return 1; }

  integer
  Brachiostocrona2::DHpDp_nnz() const
  { return 0; }

  void
  Brachiostocrona2::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
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

  integer
  Brachiostocrona2::eta_numEqns() const
  { return 3; }

  void
  Brachiostocrona2::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = ModelPars[4] * L__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DetaDx_numRows() const
  { return 3; }

  integer
  Brachiostocrona2::DetaDx_numCols() const
  { return 3; }

  integer
  Brachiostocrona2::DetaDx_nnz() const
  { return 0; }

  void
  Brachiostocrona2::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DetaDp_numRows() const
  { return 3; }

  integer
  Brachiostocrona2::DetaDp_numCols() const
  { return 1; }

  integer
  Brachiostocrona2::DetaDp_nnz() const
  { return 0; }

  void
  Brachiostocrona2::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DetaDp_sparse(
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

  integer
  Brachiostocrona2::nu_numEqns() const
  { return 3; }

  void
  Brachiostocrona2::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = ModelPars[4] * V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DnuDx_numRows() const
  { return 3; }

  integer
  Brachiostocrona2::DnuDx_numCols() const
  { return 3; }

  integer
  Brachiostocrona2::DnuDx_nnz() const
  { return 0; }

  void
  Brachiostocrona2::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brachiostocrona2::DnuDp_numRows() const
  { return 3; }

  integer
  Brachiostocrona2::DnuDp_numCols() const
  { return 1; }

  integer
  Brachiostocrona2::DnuDp_nnz() const
  { return 0; }

  void
  Brachiostocrona2::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Brachiostocrona2_Methods.cc
