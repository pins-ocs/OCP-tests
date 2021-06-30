/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_AdjointODE.cc                       |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_DD(__t1) x2bound.DD( __t1)
#define ALIAS_x2bound_D(__t1) x2bound.D( __t1)
#define ALIAS_x1bound_DD(__t1) x1bound.DD( __t1)
#define ALIAS_x1bound_D(__t1) x1bound.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_StirredTankDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  ICLOCS_StirredTank::Hx_numEqns() const
  { return 2; }

  void
  ICLOCS_StirredTank::Hx_eval(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = ALIAS_x1bound_D(t1);
    real_type t4   = P__[iP_T];
    real_type t5   = t4 * L__[iL_lambda1__xo];
    real_type t7   = 1.0 / ModelPars[iM_theta];
    real_type t8   = ModelPars[iM_k];
    real_type t9   = ModelPars[iM_En];
    real_type t10  = X__[iX_x2];
    real_type t13  = exp(-1.0 / t10 * t9);
    real_type t14  = t13 * t8;
    real_type t18  = t4 * L__[iL_lambda2__xo];
    result__[ 0   ] = t2 + (-t7 - t14) * t5 + t14 * t18;
    real_type t20  = ALIAS_x2bound_D(t10);
    real_type t23  = t10 * t10;
    real_type t24  = 1.0 / t23;
    real_type t21  = t24 * t13;
    result__[ 1   ] = t20 - t1 * t8 * t5 * t9 * t21 + t18 * (t9 * t1 * t8 * t21 - ModelPars[iM_a] * U__[iU_u] - t7);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DHxDx_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DHxDx_numCols() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DHxDx_nnz() const
  { return 4; }

  void
  ICLOCS_StirredTank::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  void
  ICLOCS_StirredTank::DHxDx_sparse(
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
    real_type t1   = X__[iX_x1];
    result__[ 0   ] = ALIAS_x1bound_DD(t1);
    real_type t3   = P__[iP_T];
    real_type t5   = ModelPars[iM_k];
    real_type t6   = t5 * t3 * L__[iL_lambda1__xo];
    real_type t7   = ModelPars[iM_En];
    real_type t8   = X__[iX_x2];
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t8;
    real_type t14  = exp(-t7 * t10);
    real_type t12  = 1.0 / t9;
    real_type t15  = t7 * t12 * t14;
    real_type t18  = t3 * L__[iL_lambda2__xo];
    result__[ 1   ] = t15 * t5 * t18 - t15 * t6;
    result__[ 2   ] = result__[1];
    real_type t21  = ALIAS_x2bound_DD(t8);
    real_type t24  = t10 * t12;
    real_type t29  = t7 * t7;
    real_type t31  = t9 * t9;
    real_type t32  = 1.0 / t31;
    real_type t36  = t1 * t5;
    real_type t22  = t14 * t24;
    real_type t28  = t14 * t32;
    result__[ 3   ] = t21 + 2 * t7 * t1 * t6 * t22 - t29 * t1 * t6 * t28 + t18 * (-2 * t7 * t36 * t22 + t29 * t36 * t28);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DHxDp_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DHxDp_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DHxDp_nnz() const
  { return 2; }

  void
  ICLOCS_StirredTank::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DHxDp_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t3   = 1.0 / ModelPars[iM_theta];
    real_type t4   = ModelPars[iM_k];
    real_type t5   = ModelPars[iM_En];
    real_type t6   = X__[iX_x2];
    real_type t9   = exp(-1.0 / t6 * t5);
    real_type t13  = L__[iL_lambda2__xo];
    real_type t10  = t9 * t4;
    result__[ 0   ] = t1 * (-t10 - t3) + t13 * t10;
    real_type t17  = X__[iX_x1];
    real_type t19  = t6 * t6;
    real_type t22  = t9 / t19 * t5;
    real_type t18  = t22 * t17;
    result__[ 1   ] = -t4 * t1 * t18 + t13 * (t4 * t18 - ModelPars[iM_a] * U__[iU_u] - t3);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 2, i_segment );
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
  ICLOCS_StirredTank::Hu_numEqns() const
  { return 1; }

  void
  ICLOCS_StirredTank::Hu_eval(
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
    real_type t2   = ALIAS_uControl_D_1(U__[iU_u], 0, 2);
    result__[ 0   ] = t2 - L__[iL_lambda2__xo] * P__[iP_T] * ModelPars[iM_a] * (X__[iX_x2] - ModelPars[iM_Tc]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DHuDx_numRows() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DHuDx_numCols() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DHuDx_nnz() const
  { return 1; }

  void
  ICLOCS_StirredTank::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DHuDx_sparse(
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
    result__[ 0   ] = -L__[iL_lambda2__xo] * P__[iP_T] * ModelPars[iM_a];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DHuDp_numRows() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DHuDp_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DHuDp_nnz() const
  { return 1; }

  void
  ICLOCS_StirredTank::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DHuDp_sparse(
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
    result__[ 0   ] = -L__[iL_lambda2__xo] * ModelPars[iM_a] * (X__[iX_x2] - ModelPars[iM_Tc]);
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
  ICLOCS_StirredTank::Hp_numEqns() const
  { return 1; }

  void
  ICLOCS_StirredTank::Hp_eval(
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
    real_type t2   = ALIAS_tfbound_D(P__[iP_T]);
    real_type t5   = X__[iX_x1];
    real_type t8   = 1.0 / ModelPars[iM_theta];
    real_type t13  = X__[iX_x2];
    real_type t16  = exp(-1.0 / t13 * ModelPars[iM_En]);
    real_type t17  = t16 * t5 * ModelPars[iM_k];
    result__[ 0   ] = t2 + ModelPars[iM_wT] + (t8 * (1 - t5) - t17) * L__[iL_lambda1__xo] + (t8 * (ModelPars[iM_Tf] - t13) + t17 - (t13 - ModelPars[iM_Tc]) * U__[iU_u] * ModelPars[iM_a]) * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DHpDp_numRows() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DHpDp_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DHpDp_nnz() const
  { return 1; }

  void
  ICLOCS_StirredTank::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DHpDp_sparse(
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
    result__[ 0   ] = ALIAS_tfbound_DD(P__[iP_T]);
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
  ICLOCS_StirredTank::eta_numEqns() const
  { return 2; }

  void
  ICLOCS_StirredTank::eta_eval(
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
    result__[ 1   ] = L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DetaDx_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DetaDx_numCols() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DetaDx_nnz() const
  { return 0; }

  void
  ICLOCS_StirredTank::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DetaDp_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DetaDp_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DetaDp_nnz() const
  { return 0; }

  void
  ICLOCS_StirredTank::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DetaDp_sparse(
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
  ICLOCS_StirredTank::nu_numEqns() const
  { return 2; }

  void
  ICLOCS_StirredTank::nu_eval(
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
    result__[ 1   ] = V__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DnuDx_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DnuDx_numCols() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DnuDx_nnz() const
  { return 0; }

  void
  ICLOCS_StirredTank::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::DnuDp_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::DnuDp_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::DnuDp_nnz() const
  { return 0; }

  void
  ICLOCS_StirredTank::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_StirredTank_Methods_AdjointODE.cc
