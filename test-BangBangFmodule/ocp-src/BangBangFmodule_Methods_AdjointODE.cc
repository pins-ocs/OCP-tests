/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Methods.cc                                     |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#include "BangBangFmodule.hh"
#include "BangBangFmodule_Pars.hh"

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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  BangBangFmodule::Hx_numEqns() const
  { return 2; }

  void
  BangBangFmodule::Hx_eval(
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
    result__[ 1   ] = L__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFmodule::DHxDx_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DHxDx_numCols() const
  { return 2; }

  integer
  BangBangFmodule::DHxDx_nnz() const
  { return 0; }

  void
  BangBangFmodule::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  void
  BangBangFmodule::DHxDx_sparse(
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
  BangBangFmodule::DHxDp_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DHxDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DHxDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DHxDp_sparse(
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
  BangBangFmodule::Hu_numEqns() const
  { return 2; }

  void
  BangBangFmodule::Hu_eval(
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
    real_type t1   = L__[1];
    result__[ 0   ] = 1 + t1;
    result__[ 1   ] = 1 - t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFmodule::DHuDx_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DHuDx_numCols() const
  { return 2; }

  integer
  BangBangFmodule::DHuDx_nnz() const
  { return 0; }

  void
  BangBangFmodule::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFmodule::DHuDp_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DHuDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DHuDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DHuDp_sparse(
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
  BangBangFmodule::Hp_numEqns() const
  { return 0; }

  void
  BangBangFmodule::Hp_eval(
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
  BangBangFmodule::DHpDp_numRows() const
  { return 0; }

  integer
  BangBangFmodule::DHpDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DHpDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  integer
  BangBangFmodule::eta_numEqns() const
  { return 2; }

  void
  BangBangFmodule::eta_eval(
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
  BangBangFmodule::DetaDx_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DetaDx_numCols() const
  { return 2; }

  integer
  BangBangFmodule::DetaDx_nnz() const
  { return 0; }

  void
  BangBangFmodule::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFmodule::DetaDp_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DetaDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DetaDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DetaDp_sparse(
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
  BangBangFmodule::nu_numEqns() const
  { return 2; }

  void
  BangBangFmodule::nu_eval(
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
  BangBangFmodule::DnuDx_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DnuDx_numCols() const
  { return 2; }

  integer
  BangBangFmodule::DnuDx_nnz() const
  { return 0; }

  void
  BangBangFmodule::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFmodule::DnuDp_numRows() const
  { return 2; }

  integer
  BangBangFmodule::DnuDp_numCols() const
  { return 0; }

  integer
  BangBangFmodule::DnuDp_nnz() const
  { return 0; }

  void
  BangBangFmodule::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFmodule::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFmodule_Methods.cc
