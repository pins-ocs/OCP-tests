/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods.cc                                        |
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


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vsTBInterval_DD(__t1) vsTBInterval.DD( __t1)
#define ALIAS_vsTBInterval_D(__t1) vsTBInterval.D( __t1)
#define ALIAS_vsTmax_DD(__t1) vsTmax.DD( __t1)
#define ALIAS_vsTmax_D(__t1) vsTmax.D( __t1)
#define ALIAS_vsBpositive_DD(__t1) vsBpositive.DD( __t1)
#define ALIAS_vsBpositive_D(__t1) vsBpositive.D( __t1)
#define ALIAS_vsTpositive_DD(__t1) vsTpositive.DD( __t1)
#define ALIAS_vsTpositive_D(__t1) vsTpositive.D( __t1)


namespace BangBangFtauDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  BangBangFtau::Hx_numEqns() const
  { return 4; }

  void
  BangBangFtau::Hx_eval(
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
    real_type t7   = ALIAS_clip_D_1(X__[2] - X__[3], ModelPars[3], ModelPars[1]);
    real_type t8   = t7 * L__[1];
    result__[ 2   ] = t8 - L__[2] / ModelPars[5];
    result__[ 3   ] = -t8 - L__[3] / ModelPars[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DHxDx_numRows() const
  { return 4; }

  integer
  BangBangFtau::DHxDx_numCols() const
  { return 4; }

  integer
  BangBangFtau::DHxDx_nnz() const
  { return 4; }

  void
  BangBangFtau::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 2   ; jIndex[ 0  ] = 2   ;
    iIndex[ 1  ] = 2   ; jIndex[ 1  ] = 3   ;
    iIndex[ 2  ] = 3   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
  }

  void
  BangBangFtau::DHxDx_sparse(
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
    real_type t7   = ALIAS_clip_D_1_1(X__[2] - X__[3], ModelPars[3], ModelPars[1]);
    result__[ 0   ] = t7 * L__[1];
    result__[ 1   ] = -result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DHxDp_numRows() const
  { return 4; }

  integer
  BangBangFtau::DHxDp_numCols() const
  { return 0; }

  integer
  BangBangFtau::DHxDp_nnz() const
  { return 0; }

  void
  BangBangFtau::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DHxDp_sparse(
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
  BangBangFtau::Hu_numEqns() const
  { return 2; }

  void
  BangBangFtau::Hu_eval(
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
    real_type t1   = U__[0];
    real_type t2   = ALIAS_vsTpositive_D(t1);
    real_type t5   = ALIAS_vsTmax_D(ModelPars[2] - t1);
    real_type t6   = U__[1];
    real_type t8   = ALIAS_vsTBInterval_D(t1 - t6);
    real_type t9   = ModelPars[0];
    result__[ 0   ] = t2 - t5 + t8 + 2 * t1 * t9 + L__[2] / ModelPars[5];
    real_type t16  = ALIAS_vsBpositive_D(t6);
    result__[ 1   ] = t16 - t8 + 2 * t6 * t9 + L__[3] / ModelPars[4];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DHuDx_numRows() const
  { return 2; }

  integer
  BangBangFtau::DHuDx_numCols() const
  { return 4; }

  integer
  BangBangFtau::DHuDx_nnz() const
  { return 0; }

  void
  BangBangFtau::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DHuDp_numRows() const
  { return 2; }

  integer
  BangBangFtau::DHuDp_numCols() const
  { return 0; }

  integer
  BangBangFtau::DHuDp_nnz() const
  { return 0; }

  void
  BangBangFtau::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DHuDp_sparse(
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
  BangBangFtau::Hp_numEqns() const
  { return 0; }

  void
  BangBangFtau::Hp_eval(
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
  BangBangFtau::DHpDp_numRows() const
  { return 0; }

  integer
  BangBangFtau::DHpDp_numCols() const
  { return 0; }

  integer
  BangBangFtau::DHpDp_nnz() const
  { return 0; }

  void
  BangBangFtau::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DHpDp_sparse(
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
  BangBangFtau::eta_numEqns() const
  { return 4; }

  void
  BangBangFtau::eta_eval(
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
  BangBangFtau::DetaDx_numRows() const
  { return 4; }

  integer
  BangBangFtau::DetaDx_numCols() const
  { return 4; }

  integer
  BangBangFtau::DetaDx_nnz() const
  { return 0; }

  void
  BangBangFtau::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DetaDp_numRows() const
  { return 4; }

  integer
  BangBangFtau::DetaDp_numCols() const
  { return 0; }

  integer
  BangBangFtau::DetaDp_nnz() const
  { return 0; }

  void
  BangBangFtau::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DetaDp_sparse(
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
  BangBangFtau::nu_numEqns() const
  { return 4; }

  void
  BangBangFtau::nu_eval(
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
  BangBangFtau::DnuDx_numRows() const
  { return 4; }

  integer
  BangBangFtau::DnuDx_numCols() const
  { return 4; }

  integer
  BangBangFtau::DnuDx_nnz() const
  { return 0; }

  void
  BangBangFtau::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DnuDp_numRows() const
  { return 4; }

  integer
  BangBangFtau::DnuDp_numCols() const
  { return 0; }

  integer
  BangBangFtau::DnuDp_nnz() const
  { return 0; }

  void
  BangBangFtau::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFtau_Methods.cc
