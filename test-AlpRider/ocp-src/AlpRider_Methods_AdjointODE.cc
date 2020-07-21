/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods.cc                                            |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  AlpRider::Hx_numEqns() const
  { return 4; }

  void
  AlpRider::Hx_eval(
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
    real_type t1   = X__[0];
    real_type t2   = t1 * t1;
    real_type t3   = X__[1];
    real_type t4   = t3 * t3;
    real_type t5   = X__[2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[3];
    real_type t8   = t7 * t7;
    real_type t10  = q(Q__[0]);
    real_type t12  = ALIAS_Ybound_D(t2 + t4 + t6 + t8 - t10);
    real_type t15  = ModelPars[0];
    result__[ 0   ] = 2 * t1 * t12 + 2 * t1 * t15 - 10 * L__[0];
    result__[ 1   ] = 2 * t3 * t12 + 2 * t3 * t15 - 2 * L__[1];
    real_type t28  = L__[2];
    real_type t30  = L__[3];
    result__[ 2   ] = 2 * t5 * t12 + 2 * t5 * t15 - 3 * t28 + 5 * t30;
    result__[ 3   ] = 2 * t7 * t12 + 2 * t7 * t15 + 5 * t28 - 3 * t30;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DHxDx_numRows() const
  { return 4; }

  integer
  AlpRider::DHxDx_numCols() const
  { return 4; }

  integer
  AlpRider::DHxDx_nnz() const
  { return 16; }

  void
  AlpRider::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 0   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 1   ;
    iIndex[ 6  ] = 1   ; jIndex[ 6  ] = 2   ;
    iIndex[ 7  ] = 1   ; jIndex[ 7  ] = 3   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 0   ;
    iIndex[ 9  ] = 2   ; jIndex[ 9  ] = 1   ;
    iIndex[ 10 ] = 2   ; jIndex[ 10 ] = 2   ;
    iIndex[ 11 ] = 2   ; jIndex[ 11 ] = 3   ;
    iIndex[ 12 ] = 3   ; jIndex[ 12 ] = 0   ;
    iIndex[ 13 ] = 3   ; jIndex[ 13 ] = 1   ;
    iIndex[ 14 ] = 3   ; jIndex[ 14 ] = 2   ;
    iIndex[ 15 ] = 3   ; jIndex[ 15 ] = 3   ;
  }

  void
  AlpRider::DHxDx_sparse(
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
    real_type t1   = X__[0];
    real_type t2   = t1 * t1;
    real_type t3   = X__[1];
    real_type t4   = t3 * t3;
    real_type t5   = X__[2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[3];
    real_type t8   = t7 * t7;
    real_type t10  = q(Q__[0]);
    real_type t11  = t2 + t4 + t6 + t8 - t10;
    real_type t12  = ALIAS_Ybound_DD(t11);
    real_type t15  = ALIAS_Ybound_D(t11);
    real_type t16  = 2 * t15;
    real_type t18  = 2 * ModelPars[0];
    result__[ 0   ] = 4 * t2 * t12 + t16 + t18;
    result__[ 1   ] = 4 * t1 * t3 * t12;
    real_type t21  = t5 * t12;
    result__[ 2   ] = 4 * t1 * t21;
    real_type t23  = t7 * t12;
    result__[ 3   ] = 4 * t1 * t23;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = 4 * t4 * t12 + t16 + t18;
    result__[ 6   ] = 4 * t3 * t21;
    result__[ 7   ] = 4 * t3 * t23;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = 4 * t6 * t12 + t16 + t18;
    result__[ 11  ] = 4 * t5 * t23;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = 4 * t8 * t12 + t16 + t18;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",16);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DHxDp_numRows() const
  { return 4; }

  integer
  AlpRider::DHxDp_numCols() const
  { return 0; }

  integer
  AlpRider::DHxDp_nnz() const
  { return 0; }

  void
  AlpRider::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DHxDp_sparse(
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
  AlpRider::Hu_numEqns() const
  { return 2; }

  void
  AlpRider::Hu_eval(
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
    real_type t3   = L__[0];
    real_type t4   = L__[1];
    real_type t5   = L__[2];
    real_type t6   = L__[3];
    result__[ 0   ] = 0.2e-1 * U__[0] + t3 + t4 + t5 + t6;
    result__[ 1   ] = 0.2e-1 * U__[1] + t3 + 2 * t4 - t5 + 3 * t6;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DHuDx_numRows() const
  { return 2; }

  integer
  AlpRider::DHuDx_numCols() const
  { return 4; }

  integer
  AlpRider::DHuDx_nnz() const
  { return 0; }

  void
  AlpRider::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DHuDp_numRows() const
  { return 2; }

  integer
  AlpRider::DHuDp_numCols() const
  { return 0; }

  integer
  AlpRider::DHuDp_nnz() const
  { return 0; }

  void
  AlpRider::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DHuDp_sparse(
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
  AlpRider::Hp_numEqns() const
  { return 0; }

  void
  AlpRider::Hp_eval(
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
  AlpRider::DHpDp_numRows() const
  { return 0; }

  integer
  AlpRider::DHpDp_numCols() const
  { return 0; }

  integer
  AlpRider::DHpDp_nnz() const
  { return 0; }

  void
  AlpRider::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DHpDp_sparse(
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
  AlpRider::eta_numEqns() const
  { return 4; }

  void
  AlpRider::eta_eval(
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
    result__[ 2   ] = L__[2];
    result__[ 3   ] = L__[3];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"eta_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DetaDx_numRows() const
  { return 4; }

  integer
  AlpRider::DetaDx_numCols() const
  { return 4; }

  integer
  AlpRider::DetaDx_nnz() const
  { return 0; }

  void
  AlpRider::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DetaDp_numRows() const
  { return 4; }

  integer
  AlpRider::DetaDp_numCols() const
  { return 0; }

  integer
  AlpRider::DetaDp_nnz() const
  { return 0; }

  void
  AlpRider::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DetaDp_sparse(
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
  AlpRider::nu_numEqns() const
  { return 4; }

  void
  AlpRider::nu_eval(
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
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"nu_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DnuDx_numRows() const
  { return 4; }

  integer
  AlpRider::DnuDx_numCols() const
  { return 4; }

  integer
  AlpRider::DnuDx_nnz() const
  { return 0; }

  void
  AlpRider::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DnuDp_numRows() const
  { return 4; }

  integer
  AlpRider::DnuDp_numCols() const
  { return 0; }

  integer
  AlpRider::DnuDp_nnz() const
  { return 0; }

  void
  AlpRider::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: AlpRider_Methods.cc
