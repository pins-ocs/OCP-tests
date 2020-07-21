/*-----------------------------------------------------------------------*\
 |  file: AliChan_Methods.cc                                             |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "AliChan.hh"
#include "AliChan_Pars.hh"

using namespace std;
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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


namespace AliChanDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  AliChan::Hx_numEqns() const
  { return 2; }

  void
  AliChan::Hx_eval(
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
    result__[ 0   ] = -2 * X__[0];
    result__[ 1   ] = 2 * X__[1] + L__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DHxDx_numRows() const
  { return 2; }

  integer
  AliChan::DHxDx_numCols() const
  { return 2; }

  integer
  AliChan::DHxDx_nnz() const
  { return 2; }

  void
  AliChan::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  void
  AliChan::DHxDx_sparse(
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
    result__[ 0   ] = -2;
    result__[ 1   ] = 2;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DHxDp_numRows() const
  { return 2; }

  integer
  AliChan::DHxDp_numCols() const
  { return 0; }

  integer
  AliChan::DHxDp_nnz() const
  { return 0; }

  void
  AliChan::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DHxDp_sparse(
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

  integer
  AliChan::Hu_numEqns() const
  { return 1; }

  void
  AliChan::Hu_eval(
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
    result__[ 0   ] = L__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DHuDx_numRows() const
  { return 1; }

  integer
  AliChan::DHuDx_numCols() const
  { return 2; }

  integer
  AliChan::DHuDx_nnz() const
  { return 0; }

  void
  AliChan::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DHuDp_numRows() const
  { return 1; }

  integer
  AliChan::DHuDp_numCols() const
  { return 0; }

  integer
  AliChan::DHuDp_nnz() const
  { return 0; }

  void
  AliChan::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  AliChan::Hp_numEqns() const
  { return 0; }

  void
  AliChan::Hp_eval(
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

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hp_eval",0);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DHpDp_numRows() const
  { return 0; }

  integer
  AliChan::DHpDp_numCols() const
  { return 0; }

  integer
  AliChan::DHpDp_nnz() const
  { return 0; }

  void
  AliChan::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DHpDp_sparse(
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
  AliChan::eta_numEqns() const
  { return 2; }

  void
  AliChan::eta_eval(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"eta_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DetaDx_numRows() const
  { return 2; }

  integer
  AliChan::DetaDx_numCols() const
  { return 2; }

  integer
  AliChan::DetaDx_nnz() const
  { return 0; }

  void
  AliChan::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DetaDp_numRows() const
  { return 2; }

  integer
  AliChan::DetaDp_numCols() const
  { return 0; }

  integer
  AliChan::DetaDp_nnz() const
  { return 0; }

  void
  AliChan::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DetaDp_sparse(
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
  AliChan::nu_numEqns() const
  { return 2; }

  void
  AliChan::nu_eval(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"nu_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DnuDx_numRows() const
  { return 2; }

  integer
  AliChan::DnuDx_numCols() const
  { return 2; }

  integer
  AliChan::DnuDx_nnz() const
  { return 0; }

  void
  AliChan::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AliChan::DnuDp_numRows() const
  { return 2; }

  integer
  AliChan::DnuDp_numCols() const
  { return 0; }

  integer
  AliChan::DnuDp_nnz() const
  { return 0; }

  void
  AliChan::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AliChan::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: AliChan_Methods.cc
