/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_AdjointODE.cc                                 |
 |                                                                       |
 |  version: 1.0   date 5/6/2021                                         |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
    real_type t1   = X__[iX_y1];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_y2];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_y3];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y4];
    real_type t8   = t7 * t7;
    real_type t10  = q(Q__[iQ_zeta]);
    real_type t11  = t2 + t4 + t6 + t8 - t10;
    real_type t12  = Ybound(t11);
    real_type t16  = ALIAS_Ybound_D(t11);
    real_type t17  = t16 * (t2 + t4 + t6 + t8 + 1);
    real_type t20  = ModelPars[iM_W];
    result__[ 0   ] = 2 * t12 * t1 + 2 * t1 * t17 + 2 * t1 * t20 - 10 * L__[iL_lambda1__xo];
    result__[ 1   ] = 2 * t12 * t3 + 2 * t3 * t17 + 2 * t3 * t20 - 2 * L__[iL_lambda2__xo];
    real_type t36  = L__[iL_lambda3__xo];
    real_type t38  = L__[iL_lambda4__xo];
    result__[ 2   ] = 2 * t12 * t5 + 2 * t5 * t17 + 2 * t5 * t20 - 3 * t36 + 5 * t38;
    result__[ 3   ] = 2 * t12 * t7 + 2 * t7 * t17 + 2 * t7 * t20 + 5 * t36 - 3 * t38;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
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
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
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
    real_type t1   = X__[iX_y1];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_y2];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_y3];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y4];
    real_type t8   = t7 * t7;
    real_type t10  = q(Q__[iQ_zeta]);
    real_type t11  = t2 + t4 + t6 + t8 - t10;
    real_type t12  = Ybound(t11);
    real_type t13  = 2 * t12;
    real_type t14  = ALIAS_Ybound_D(t11);
    real_type t17  = t2 + t4 + t6 + t8 + 1;
    real_type t18  = ALIAS_Ybound_DD(t11);
    real_type t19  = t18 * t17;
    real_type t23  = 2 * t14 * t17;
    real_type t25  = 2 * ModelPars[iM_W];
    result__[ 0   ] = 8 * t14 * t2 + 4 * t2 * t19 + t13 + t23 + t25;
    real_type t26  = t14 * t1;
    result__[ 1   ] = 4 * t1 * t3 * t19 + 8 * t3 * t26;
    result__[ 2   ] = 4 * t1 * t5 * t19 + 8 * t5 * t26;
    result__[ 3   ] = 4 * t1 * t7 * t19 + 8 * t7 * t26;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = 8 * t14 * t4 + 4 * t4 * t19 + t13 + t23 + t25;
    real_type t46  = t14 * t3;
    result__[ 6   ] = 4 * t3 * t5 * t19 + 8 * t5 * t46;
    result__[ 7   ] = 4 * t3 * t7 * t19 + 8 * t7 * t46;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = 8 * t14 * t6 + 4 * t6 * t19 + t13 + t23 + t25;
    result__[ 11  ] = 8 * t7 * t14 * t5 + 4 * t5 * t7 * t19;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = 8 * t14 * t8 + 4 * t8 * t19 + t13 + t23 + t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 16, i_segment );
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
    real_type t3   = L__[iL_lambda1__xo];
    real_type t4   = L__[iL_lambda2__xo];
    real_type t5   = L__[iL_lambda3__xo];
    real_type t6   = L__[iL_lambda4__xo];
    result__[ 0   ] = U__[iU_u1] / 50 + t3 + t4 + t5 + t6;
    result__[ 1   ] = U__[iU_u2] / 50 + t3 + 2 * t4 - t5 + 3 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
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
    // EMPTY!
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
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
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

// EOF: AlpRider_Methods_AdjointODE.cc
