/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_AdjointODE.cc                            |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  GoddardRocket::Hx_numEqns() const
  { return 3; }

  void
  GoddardRocket::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_TimeSize];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    real_type t10  = gg_D(t4);
    result__[ 0   ] = (-t8 * t6 - t10) * t3;
    real_type t12  = ALIAS_vPositive_D(t5);
    real_type t15  = DD_D_2(t4, t5);
    result__[ 1   ] = -t8 * t15 * t3 + t2 * L__[iL_lambda1__xo] + t12;
    real_type t18  = ALIAS_massPositive_D(t7);
    real_type t20  = DD(t4, t5);
    real_type t22  = t7 * t7;
    result__[ 2   ] = t18 - 1.0 / t22 * (U__[iU_T] - t20) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DHxDx_numRows() const
  { return 3; }

  integer
  GoddardRocket::DHxDx_numCols() const
  { return 3; }

  integer
  GoddardRocket::DHxDx_nnz() const
  { return 9; }

  void
  GoddardRocket::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
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
  GoddardRocket::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = L__[iL_lambda2__xo] * P__[iP_TimeSize];
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    real_type t10  = gg_DD(t4);
    result__[ 0   ] = (-t8 * t6 - t10) * t3;
    real_type t12  = DD_D_1_2(t4, t5);
    result__[ 1   ] = -t8 * t12 * t3;
    real_type t15  = DD_D_1(t4, t5);
    real_type t16  = t7 * t7;
    real_type t17  = 1.0 / t16;
    result__[ 2   ] = t17 * t15 * t3;
    result__[ 3   ] = result__[1];
    real_type t19  = ALIAS_vPositive_DD(t5);
    real_type t20  = DD_D_2_2(t4, t5);
    result__[ 4   ] = -t8 * t20 * t3 + t19;
    real_type t23  = DD_D_2(t4, t5);
    result__[ 5   ] = t17 * t23 * t3;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t25  = ALIAS_massPositive_DD(t7);
    real_type t27  = DD(t4, t5);
    result__[ 8   ] = t25 + 2 / t16 / t7 * (U__[iU_T] - t27) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DHxDp_numRows() const
  { return 3; }

  integer
  GoddardRocket::DHxDp_numCols() const
  { return 1; }

  integer
  GoddardRocket::DHxDp_nnz() const
  { return 3; }

  void
  GoddardRocket::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_h];
    real_type t3   = X__[iX_v];
    real_type t4   = DD_D_1(t2, t3);
    real_type t5   = X__[iX_m];
    real_type t6   = 1.0 / t5;
    real_type t8   = gg_D(t2);
    result__[ 0   ] = (-t6 * t4 - t8) * t1;
    real_type t11  = DD_D_2(t2, t3);
    result__[ 1   ] = -t6 * t11 * t1 + L__[iL_lambda1__xo];
    real_type t15  = DD(t2, t3);
    real_type t18  = t5 * t5;
    result__[ 2   ] = -1.0 / t18 * (U__[iU_T] - t15) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 3, i_segment );
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
  GoddardRocket::Hu_numEqns() const
  { return 1; }

  void
  GoddardRocket::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_TimeSize];
    result__[ 0   ] = 1.0 / X__[iX_m] * t2 * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DHuDx_numRows() const
  { return 1; }

  integer
  GoddardRocket::DHuDx_numCols() const
  { return 3; }

  integer
  GoddardRocket::DHuDx_nnz() const
  { return 1; }

  void
  GoddardRocket::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t5   = X__[iX_m] * X__[iX_m];
    result__[ 0   ] = -1.0 / t5 * P__[iP_TimeSize] * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DHuDp_numRows() const
  { return 1; }

  integer
  GoddardRocket::DHuDp_numCols() const
  { return 1; }

  integer
  GoddardRocket::DHuDp_nnz() const
  { return 1; }

  void
  GoddardRocket::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda2__xo] / X__[iX_m] - L__[iL_lambda3__xo] / ModelPars[iM_c];
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
  GoddardRocket::Hp_numEqns() const
  { return 1; }

  void
  GoddardRocket::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_TSPositive_D(P__[iP_TimeSize]);
    real_type t4   = X__[iX_v];
    real_type t7   = U__[iU_T];
    real_type t8   = X__[iX_h];
    real_type t9   = DD(t8, t4);
    real_type t14  = gg(t8);
    result__[ 0   ] = t2 + t4 * L__[iL_lambda1__xo] + (1.0 / X__[iX_m] * (t7 - t9) - t14) * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t7 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DHpDp_numRows() const
  { return 1; }

  integer
  GoddardRocket::DHpDp_numCols() const
  { return 1; }

  integer
  GoddardRocket::DHpDp_nnz() const
  { return 1; }

  void
  GoddardRocket::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_TSPositive_DD(P__[iP_TimeSize]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse" ,1, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  GoddardRocket::eta_numEqns() const
  { return 3; }

  void
  GoddardRocket::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  GoddardRocket::DetaDx_numRows() const
  { return 3; }

  integer
  GoddardRocket::DetaDx_numCols() const
  { return 3; }

  integer
  GoddardRocket::DetaDx_nnz() const
  { return 0; }

  void
  GoddardRocket::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DetaDp_numRows() const
  { return 3; }

  integer
  GoddardRocket::DetaDp_numCols() const
  { return 1; }

  integer
  GoddardRocket::DetaDp_nnz() const
  { return 0; }

  void
  GoddardRocket::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DetaDp_sparse(
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
  GoddardRocket::nu_numEqns() const
  { return 3; }

  void
  GoddardRocket::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  GoddardRocket::DnuDx_numRows() const
  { return 3; }

  integer
  GoddardRocket::DnuDx_numCols() const
  { return 3; }

  integer
  GoddardRocket::DnuDx_nnz() const
  { return 0; }

  void
  GoddardRocket::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DnuDp_numRows() const
  { return 3; }

  integer
  GoddardRocket::DnuDp_numCols() const
  { return 1; }

  integer
  GoddardRocket::DnuDp_nnz() const
  { return 0; }

  void
  GoddardRocket::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: GoddardRocket_Methods_AdjointODE.cc
