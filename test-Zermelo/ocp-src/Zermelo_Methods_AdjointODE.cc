/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_AdjointODE.cc                                  |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace ZermeloDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  Zermelo::Hx_numEqns() const
  { return 5; }

  void
  Zermelo::Hx_eval(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = velX_D_1(t4, t5);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = t2 * t8;
    real_type t10  = velY_D_1(t4, t5);
    result__[ 0   ] = t10 * t9 + t6 * t3;
    real_type t12  = velX_D_2(t4, t5);
    real_type t14  = velY_D_2(t4, t5);
    result__[ 1   ] = t12 * t3 + t14 * t9;
    result__[ 2   ] = t2 * t1;
    result__[ 3   ] = t2 * t8;
    real_type t16  = ALIAS_Tpositive_D(t2);
    real_type t18  = velX(t4, t5);
    real_type t22  = velY(t4, t5);
    real_type t26  = ModelPars[iM_S];
    real_type t28  = U__[iU_u];
    real_type t29  = cos(t28);
    real_type t33  = sin(t28);
    result__[ 4   ] = t16 + (X__[iX_vx] + t18) * t1 + (X__[iX_vy] + t22) * t8 + t29 * t26 * L__[iL_lambda3__xo] + t33 * t26 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DHxDx_numRows() const
  { return 5; }

  integer
  Zermelo::DHxDx_numCols() const
  { return 5; }

  integer
  Zermelo::DHxDx_nnz() const
  { return 13; }

  void
  Zermelo::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 1   ;
    iIndex[10] = 4   ; jIndex[10] = 2   ;
    iIndex[11] = 4   ; jIndex[11] = 3   ;
    iIndex[12] = 4   ; jIndex[12] = 4   ;
  }

  void
  Zermelo::DHxDx_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = velX_D_1_1(t4, t5);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = t2 * t8;
    real_type t10  = velY_D_1_1(t4, t5);
    result__[ 0   ] = t10 * t9 + t6 * t3;
    real_type t12  = velX_D_1_2(t4, t5);
    real_type t14  = velY_D_1_2(t4, t5);
    result__[ 1   ] = t12 * t3 + t14 * t9;
    real_type t16  = velX_D_1(t4, t5);
    real_type t18  = velY_D_1(t4, t5);
    result__[ 2   ] = t16 * t1 + t18 * t8;
    result__[ 3   ] = result__[1];
    real_type t20  = velX_D_2_2(t4, t5);
    real_type t22  = velY_D_2_2(t4, t5);
    result__[ 4   ] = t20 * t3 + t22 * t9;
    real_type t24  = velX_D_2(t4, t5);
    real_type t26  = velY_D_2(t4, t5);
    result__[ 5   ] = t24 * t1 + t26 * t8;
    result__[ 6   ] = t1;
    result__[ 7   ] = t8;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    result__[ 12  ] = ALIAS_Tpositive_DD(t2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 13, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DHxDp_numRows() const
  { return 5; }

  integer
  Zermelo::DHxDp_numCols() const
  { return 0; }

  integer
  Zermelo::DHxDp_nnz() const
  { return 0; }

  void
  Zermelo::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DHxDp_sparse(
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
  Zermelo::Hu_numEqns() const
  { return 1; }

  void
  Zermelo::Hu_eval(
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
    real_type t2   = X__[iX_T];
    real_type t4   = ModelPars[iM_S];
    real_type t5   = U__[iU_u];
    real_type t6   = sin(t5);
    real_type t11  = cos(t5);
    result__[ 0   ] = t11 * t4 * t2 * L__[iL_lambda4__xo] - t6 * t4 * t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DHuDx_numRows() const
  { return 1; }

  integer
  Zermelo::DHuDx_numCols() const
  { return 5; }

  integer
  Zermelo::DHuDx_nnz() const
  { return 1; }

  void
  Zermelo::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DHuDx_sparse(
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
    real_type t2   = ModelPars[iM_S];
    real_type t4   = U__[iU_u];
    real_type t5   = sin(t4);
    real_type t9   = cos(t4);
    result__[ 0   ] = -t5 * t2 * L__[iL_lambda3__xo] + t9 * t2 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DHuDp_numRows() const
  { return 1; }

  integer
  Zermelo::DHuDp_numCols() const
  { return 0; }

  integer
  Zermelo::DHuDp_nnz() const
  { return 0; }

  void
  Zermelo::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DHuDp_sparse(
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
  Zermelo::Hp_numEqns() const
  { return 0; }

  void
  Zermelo::Hp_eval(
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
  Zermelo::DHpDp_numRows() const
  { return 0; }

  integer
  Zermelo::DHpDp_numCols() const
  { return 0; }

  integer
  Zermelo::DHpDp_nnz() const
  { return 0; }

  void
  Zermelo::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DHpDp_sparse(
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
  Zermelo::eta_numEqns() const
  { return 5; }

  void
  Zermelo::eta_eval(
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
    result__[ 4   ] = L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DetaDx_numRows() const
  { return 5; }

  integer
  Zermelo::DetaDx_numCols() const
  { return 5; }

  integer
  Zermelo::DetaDx_nnz() const
  { return 0; }

  void
  Zermelo::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DetaDp_numRows() const
  { return 5; }

  integer
  Zermelo::DetaDp_numCols() const
  { return 0; }

  integer
  Zermelo::DetaDp_nnz() const
  { return 0; }

  void
  Zermelo::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DetaDp_sparse(
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
  Zermelo::nu_numEqns() const
  { return 5; }

  void
  Zermelo::nu_eval(
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
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DnuDx_numRows() const
  { return 5; }

  integer
  Zermelo::DnuDx_numCols() const
  { return 5; }

  integer
  Zermelo::DnuDx_nnz() const
  { return 0; }

  void
  Zermelo::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DnuDp_numRows() const
  { return 5; }

  integer
  Zermelo::DnuDp_numCols() const
  { return 0; }

  integer
  Zermelo::DnuDp_nnz() const
  { return 0; }

  void
  Zermelo::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Zermelo_Methods_AdjointODE.cc
