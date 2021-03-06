/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods.cc                                           |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_DD(__t1) VelBound.DD( __t1)
#define ALIAS_VelBound_D(__t1) VelBound.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  Crossroad::Hx_numEqns() const
  { return 4; }

  void
  Crossroad::Hx_eval(
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
    real_type t1   = X__[2];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[14] * ModelPars[14];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[1];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[0];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[13] * ModelPars[13];
    real_type t16  = 1.0 / t15;
    real_type t19  = ALIAS_AccBound_D(-t16 * t12 * t9 - t5 * t2 + 1);
    real_type t22  = kappa_D(t10);
    result__[ 0   ] = -2 * t22 * t16 * t11 * t9 * t19;
    real_type t31  = ALIAS_VelBound_D(t7);
    real_type t32  = L__[0];
    real_type t33  = X__[3];
    result__[ 1   ] = -4 * t16 * t12 * t8 * t7 * t19 + t33 * t32 + t31;
    real_type t38  = L__[1];
    result__[ 2   ] = -2 * t5 * t1 * t19 + t33 * t38;
    real_type t40  = ALIAS_Tpositive_D(t33);
    real_type t43  = U__[0];
    real_type t44  = t43 * t43;
    result__[ 3   ] = t1 * t38 + t7 * t32 + t43 * L__[2] + t44 * ModelPars[11] + t40 + ModelPars[12];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHxDx_numRows() const
  { return 4; }

  integer
  Crossroad::DHxDx_numCols() const
  { return 4; }

  integer
  Crossroad::DHxDx_nnz() const
  { return 14; }

  void
  Crossroad::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 1   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 0   ;
    iIndex[ 8  ] = 2   ; jIndex[ 8  ] = 1   ;
    iIndex[ 9  ] = 2   ; jIndex[ 9  ] = 2   ;
    iIndex[ 10 ] = 2   ; jIndex[ 10 ] = 3   ;
    iIndex[ 11 ] = 3   ; jIndex[ 11 ] = 1   ;
    iIndex[ 12 ] = 3   ; jIndex[ 12 ] = 2   ;
    iIndex[ 13 ] = 3   ; jIndex[ 13 ] = 3   ;
  }

  void
  Crossroad::DHxDx_sparse(
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
    real_type t1   = X__[2];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[14] * ModelPars[14];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[1];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[0];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[13] * ModelPars[13];
    real_type t16  = 1.0 / t15;
    real_type t18  = -t16 * t12 * t9 - t5 * t2 + 1;
    real_type t19  = ALIAS_AccBound_DD(t18);
    real_type t20  = t9 * t9;
    real_type t22  = t15 * t15;
    real_type t23  = 1.0 / t22;
    real_type t25  = kappa_D(t10);
    real_type t26  = t25 * t25;
    real_type t30  = ALIAS_AccBound_D(t18);
    real_type t31  = t9 * t30;
    real_type t35  = t16 * t11;
    real_type t36  = kappa_DD(t10);
    result__[ 0   ] = 4 * t26 * t23 * t12 * t20 * t19 - 2 * t16 * t26 * t31 - 2 * t36 * t35 * t31;
    real_type t40  = t8 * t7;
    result__[ 1   ] = 8 * t25 * t23 * t12 * t11 * t9 * t40 * t19 - 8 * t25 * t35 * t40 * t30;
    real_type t52  = t5 * t1 * t19;
    result__[ 2   ] = 4 * t25 * t16 * t11 * t9 * t52;
    result__[ 3   ] = result__[1];
    real_type t59  = t12 * t12;
    real_type t67  = ALIAS_VelBound_DD(t7);
    result__[ 4   ] = 16 * t23 * t59 * t9 * t8 * t19 - 12 * t16 * t12 * t8 * t30 + t67;
    result__[ 5   ] = 8 * t16 * t12 * t40 * t52;
    result__[ 6   ] = L__[0];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[5];
    real_type t72  = t4 * t4;
    result__[ 9   ] = 4 / t72 * t2 * t19 - 2 * t5 * t30;
    result__[ 10  ] = L__[1];
    result__[ 11  ] = result__[6];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = ALIAS_Tpositive_DD(X__[3]);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",14);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHxDp_numRows() const
  { return 4; }

  integer
  Crossroad::DHxDp_numCols() const
  { return 0; }

  integer
  Crossroad::DHxDp_nnz() const
  { return 0; }

  void
  Crossroad::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHxDp_sparse(
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
  Crossroad::Hu_numEqns() const
  { return 1; }

  void
  Crossroad::Hu_eval(
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
    real_type t4   = X__[3];
    result__[ 0   ] = 2 * t4 * ModelPars[11] * U__[0] + t4 * L__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHuDx_numRows() const
  { return 1; }

  integer
  Crossroad::DHuDx_numCols() const
  { return 4; }

  integer
  Crossroad::DHuDx_nnz() const
  { return 1; }

  void
  Crossroad::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHuDx_sparse(
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
    result__[ 0   ] = 2 * U__[0] * ModelPars[11] + L__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHuDx_sparse",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DHuDp_numRows() const
  { return 1; }

  integer
  Crossroad::DHuDp_numCols() const
  { return 0; }

  integer
  Crossroad::DHuDp_nnz() const
  { return 0; }

  void
  Crossroad::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHuDp_sparse(
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
  Crossroad::Hp_numEqns() const
  { return 0; }

  void
  Crossroad::Hp_eval(
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
  Crossroad::DHpDp_numRows() const
  { return 0; }

  integer
  Crossroad::DHpDp_numCols() const
  { return 0; }

  integer
  Crossroad::DHpDp_nnz() const
  { return 0; }

  void
  Crossroad::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DHpDp_sparse(
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
  Crossroad::eta_numEqns() const
  { return 4; }

  void
  Crossroad::eta_eval(
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
  Crossroad::DetaDx_numRows() const
  { return 4; }

  integer
  Crossroad::DetaDx_numCols() const
  { return 4; }

  integer
  Crossroad::DetaDx_nnz() const
  { return 0; }

  void
  Crossroad::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DetaDp_numRows() const
  { return 4; }

  integer
  Crossroad::DetaDp_numCols() const
  { return 0; }

  integer
  Crossroad::DetaDp_nnz() const
  { return 0; }

  void
  Crossroad::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DetaDp_sparse(
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
  Crossroad::nu_numEqns() const
  { return 4; }

  void
  Crossroad::nu_eval(
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
  Crossroad::DnuDx_numRows() const
  { return 4; }

  integer
  Crossroad::DnuDx_numCols() const
  { return 4; }

  integer
  Crossroad::DnuDx_nnz() const
  { return 0; }

  void
  Crossroad::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DnuDp_numRows() const
  { return 4; }

  integer
  Crossroad::DnuDp_numCols() const
  { return 0; }

  integer
  Crossroad::DnuDp_nnz() const
  { return 0; }

  void
  Crossroad::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Crossroad_Methods.cc
