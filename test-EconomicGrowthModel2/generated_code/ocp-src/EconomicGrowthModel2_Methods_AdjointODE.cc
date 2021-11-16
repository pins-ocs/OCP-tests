/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_AdjointODE.cc                     |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  EconomicGrowthModel2::Hx_numEqns() const
  { return 5; }

  void
  EconomicGrowthModel2::Hx_eval(
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
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda4__xo];
    result__[ 0   ] = t12 * t8 + t3 * t8;
    real_type t14  = Q_D_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t12 * t15 + t15 * t3;
    real_type t18  = L__[iL_lambda1__xo];
    result__[ 2   ] = t7 * t18;
    real_type t19  = L__[iL_lambda3__xo];
    result__[ 3   ] = t7 * t19;
    real_type t20  = ALIAS_Tpositive_D(t7);
    real_type t23  = Q(t4, t5);
    result__[ 4   ] = t12 * t23 + t18 * X__[iX_y1] + t19 * X__[iX_y2] + t23 * t3 + t20;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DHxDx_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::DHxDx_numCols() const
  { return 5; }

  integer
  EconomicGrowthModel2::DHxDx_nnz() const
  { return 13; }

  void
  EconomicGrowthModel2::DHxDx_pattern(
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
  EconomicGrowthModel2::DHxDx_sparse(
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
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda4__xo];
    result__[ 0   ] = t8 * t12 + t8 * t3;
    real_type t14  = Q_D_1_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t15 * t12 + t15 * t3;
    real_type t18  = Q_D_1(t4, t5);
    result__[ 2   ] = t18 * t12 + t18 * t3;
    result__[ 3   ] = result__[1];
    real_type t21  = Q_D_2_2(t4, t5);
    real_type t22  = t7 * t21;
    result__[ 4   ] = t22 * t12 + t22 * t3;
    real_type t25  = Q_D_2(t4, t5);
    result__[ 5   ] = t25 * t12 + t25 * t3;
    result__[ 6   ] = L__[iL_lambda1__xo];
    result__[ 7   ] = L__[iL_lambda3__xo];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    result__[ 12  ] = ALIAS_Tpositive_DD(t7);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 13, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DHxDp_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::DHxDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel2::DHxDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DHxDp_sparse(
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
  EconomicGrowthModel2::Hu_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel2::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = Q(X__[iX_x1], X__[iX_x2]);
    real_type t6   = X__[iX_T];
    result__[ 0   ] = t6 * t4 * L__[iL_lambda2__xo] - t6 * t4 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DHuDx_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel2::DHuDx_numCols() const
  { return 5; }

  integer
  EconomicGrowthModel2::DHuDx_nnz() const
  { return 3; }

  void
  EconomicGrowthModel2::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = Q_D_1(t2, t3);
    real_type t6   = X__[iX_T];
    real_type t8   = L__[iL_lambda4__xo];
    result__[ 0   ] = t1 * t4 * t6 - t4 * t6 * t8;
    real_type t11  = Q_D_2(t2, t3);
    result__[ 1   ] = t1 * t11 * t6 - t11 * t6 * t8;
    real_type t16  = Q(t2, t3);
    result__[ 2   ] = t1 * t16 - t16 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DHuDp_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel2::DHuDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel2::DHuDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DHuDp_sparse(
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
  EconomicGrowthModel2::Hp_numEqns() const
  { return 0; }

  void
  EconomicGrowthModel2::Hp_eval(
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
  EconomicGrowthModel2::DHpDp_numRows() const
  { return 0; }

  integer
  EconomicGrowthModel2::DHpDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel2::DHpDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DHpDp_sparse(
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
  EconomicGrowthModel2::eta_numEqns() const
  { return 5; }

  void
  EconomicGrowthModel2::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda3__xo];
    result__[ 2   ] = L__[iL_lambda2__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DetaDx_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::DetaDx_numCols() const
  { return 5; }

  integer
  EconomicGrowthModel2::DetaDx_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DetaDp_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::DetaDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel2::DetaDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DetaDp_sparse(
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
  EconomicGrowthModel2::nu_numEqns() const
  { return 5; }

  void
  EconomicGrowthModel2::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[2];
    result__[ 2   ] = V__[1];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DnuDx_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::DnuDx_numCols() const
  { return 5; }

  integer
  EconomicGrowthModel2::DnuDx_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DnuDp_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::DnuDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel2::DnuDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: EconomicGrowthModel2_Methods_AdjointODE.cc
