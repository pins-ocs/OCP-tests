/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Methods_AdjointODE.cc                      |
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


#include "EconomicGrowthModel.hh"
#include "EconomicGrowthModel_Pars.hh"

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


namespace EconomicGrowthModelDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  EconomicGrowthModel::Hx_numEqns() const
  { return 3; }

  void
  EconomicGrowthModel::Hx_eval(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    real_type t3   = Q_D_1(t1, t2);
    real_type t4   = X__[iX_T];
    real_type t7   = U__[iU_u];
    real_type t8   = t7 * L__[iL_lambda1__xo];
    real_type t9   = L__[iL_lambda2__xo];
    real_type t11  = -t7 * t9 + t8 + t9;
    result__[ 0   ] = t11 * t4 * t3;
    real_type t12  = Q_D_2(t1, t2);
    result__[ 1   ] = t11 * t4 * t12;
    real_type t17  = Q(t1, t2);
    real_type t19  = ALIAS_Tpositive_D(t4);
    result__[ 2   ] = t17 * (t8 + (1 - t7) * t9) + t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DHxDx_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DHxDx_numCols() const
  { return 3; }

  integer
  EconomicGrowthModel::DHxDx_nnz() const
  { return 9; }

  void
  EconomicGrowthModel::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
  }

  void
  EconomicGrowthModel::DHxDx_sparse(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    real_type t3   = Q_D_1_1(t1, t2);
    real_type t4   = X__[iX_T];
    real_type t7   = U__[iU_u];
    real_type t9   = L__[iL_lambda2__xo];
    real_type t11  = -t7 * t9 + t7 * L__[iL_lambda1__xo] + t9;
    result__[ 0   ] = t11 * t4 * t3;
    real_type t12  = Q_D_1_2(t1, t2);
    result__[ 1   ] = t11 * t4 * t12;
    real_type t14  = Q_D_1(t1, t2);
    result__[ 2   ] = t11 * t14;
    result__[ 3   ] = result__[1];
    real_type t15  = Q_D_2_2(t1, t2);
    result__[ 4   ] = t11 * t4 * t15;
    real_type t17  = Q_D_2(t1, t2);
    result__[ 5   ] = t11 * t17;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = ALIAS_Tpositive_DD(t4);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DHxDp_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DHxDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DHxDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DHxDp_sparse(
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
  EconomicGrowthModel::Hu_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel::Hu_eval(
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
    real_type t3   = Q(X__[iX_x1], X__[iX_x2]);
    result__[ 0   ] = (L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * X__[iX_T] * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DHuDx_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel::DHuDx_numCols() const
  { return 3; }

  integer
  EconomicGrowthModel::DHuDx_nnz() const
  { return 3; }

  void
  EconomicGrowthModel::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DHuDx_sparse(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    real_type t3   = Q_D_1(t1, t2);
    real_type t4   = X__[iX_T];
    real_type t8   = L__[iL_lambda1__xo] - L__[iL_lambda2__xo];
    result__[ 0   ] = t8 * t4 * t3;
    real_type t9   = Q_D_2(t1, t2);
    result__[ 1   ] = t8 * t4 * t9;
    real_type t11  = Q(t1, t2);
    result__[ 2   ] = t11 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DHuDp_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel::DHuDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DHuDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DHuDp_sparse(
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
  EconomicGrowthModel::Hp_numEqns() const
  { return 0; }

  void
  EconomicGrowthModel::Hp_eval(
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
  EconomicGrowthModel::DHpDp_numRows() const
  { return 0; }

  integer
  EconomicGrowthModel::DHpDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DHpDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DHpDp_sparse(
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
  EconomicGrowthModel::eta_numEqns() const
  { return 3; }

  void
  EconomicGrowthModel::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DetaDx_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DetaDx_numCols() const
  { return 3; }

  integer
  EconomicGrowthModel::DetaDx_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DetaDp_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DetaDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DetaDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DetaDp_sparse(
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
  EconomicGrowthModel::nu_numEqns() const
  { return 3; }

  void
  EconomicGrowthModel::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DnuDx_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DnuDx_numCols() const
  { return 3; }

  integer
  EconomicGrowthModel::DnuDx_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel::DnuDp_numRows() const
  { return 3; }

  integer
  EconomicGrowthModel::DnuDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel::DnuDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: EconomicGrowthModel_Methods_AdjointODE.cc
