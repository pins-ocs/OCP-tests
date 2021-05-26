/*-----------------------------------------------------------------------*\
 |  file: MultipleDubins_Methods_AdjointODE.cc                           |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#include "MultipleDubins.hh"
#include "MultipleDubins_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_diff2pi_DD(__t1) diff2pi.DD( __t1)
#define ALIAS_diff2pi_D(__t1) diff2pi.D( __t1)


namespace MultipleDubinsDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  MultipleDubins::Hx_numEqns() const
  { return 9; }

  void
  MultipleDubins::Hx_eval(
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
    result__[ 1   ] = 0;
    real_type t2   = P__[iP_L1];
    real_type t4   = X__[iX_theta1];
    real_type t5   = sin(t4);
    real_type t9   = cos(t4);
    result__[ 2   ] = -t5 * t2 * L__[iL_lambda1__xo] + t9 * t2 * L__[iL_lambda2__xo];
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    real_type t12  = P__[iP_L2];
    real_type t14  = X__[iX_theta2];
    real_type t15  = sin(t14);
    real_type t19  = cos(t14);
    result__[ 5   ] = -t15 * t12 * L__[iL_lambda4__xo] + t19 * t12 * L__[iL_lambda5__xo];
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    real_type t22  = P__[iP_L3];
    real_type t24  = X__[iX_theta3];
    real_type t25  = sin(t24);
    real_type t29  = cos(t24);
    result__[ 8   ] = -t25 * t22 * L__[iL_lambda7__xo] + t29 * t22 * L__[iL_lambda8__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DHxDx_numRows() const
  { return 9; }

  integer
  MultipleDubins::DHxDx_numCols() const
  { return 9; }

  integer
  MultipleDubins::DHxDx_nnz() const
  { return 3; }

  void
  MultipleDubins::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 5   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 8   ; jIndex[2 ] = 8   ;
  }

  void
  MultipleDubins::DHxDx_sparse(
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
    real_type t2   = P__[iP_L1];
    real_type t4   = X__[iX_theta1];
    real_type t5   = cos(t4);
    real_type t9   = sin(t4);
    result__[ 0   ] = -t5 * t2 * L__[iL_lambda1__xo] - t9 * t2 * L__[iL_lambda2__xo];
    real_type t12  = P__[iP_L2];
    real_type t14  = X__[iX_theta2];
    real_type t15  = cos(t14);
    real_type t19  = sin(t14);
    result__[ 1   ] = -t15 * t12 * L__[iL_lambda4__xo] - t19 * t12 * L__[iL_lambda5__xo];
    real_type t22  = P__[iP_L3];
    real_type t24  = X__[iX_theta3];
    real_type t25  = cos(t24);
    real_type t29  = sin(t24);
    result__[ 2   ] = -t25 * t22 * L__[iL_lambda7__xo] - t29 * t22 * L__[iL_lambda8__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DHxDp_numRows() const
  { return 9; }

  integer
  MultipleDubins::DHxDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DHxDp_nnz() const
  { return 3; }

  void
  MultipleDubins::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 5   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 8   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DHxDp_sparse(
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
    real_type t2   = X__[iX_theta1];
    real_type t3   = sin(t2);
    real_type t6   = cos(t2);
    result__[ 0   ] = -t3 * L__[iL_lambda1__xo] + t6 * L__[iL_lambda2__xo];
    real_type t9   = X__[iX_theta2];
    real_type t10  = sin(t9);
    real_type t13  = cos(t9);
    result__[ 1   ] = -t10 * L__[iL_lambda4__xo] + t13 * L__[iL_lambda5__xo];
    real_type t16  = X__[iX_theta3];
    real_type t17  = sin(t16);
    real_type t20  = cos(t16);
    result__[ 2   ] = -t17 * L__[iL_lambda7__xo] + t20 * L__[iL_lambda8__xo];
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
  MultipleDubins::Hu_numEqns() const
  { return 0; }

  void
  MultipleDubins::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DHuDx_numRows() const
  { return 0; }

  integer
  MultipleDubins::DHuDx_numCols() const
  { return 9; }

  integer
  MultipleDubins::DHuDx_nnz() const
  { return 0; }

  void
  MultipleDubins::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DHuDp_numRows() const
  { return 0; }

  integer
  MultipleDubins::DHuDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DHuDp_nnz() const
  { return 0; }

  void
  MultipleDubins::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DHuDp_sparse(
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
  MultipleDubins::Hp_numEqns() const
  { return 6; }

  void
  MultipleDubins::Hp_eval(
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
    real_type t1   = ModelPars[iM_epsilon_L];
    real_type t2   = P__[iP_L1];
    real_type t6   = X__[iX_theta1];
    real_type t7   = cos(t6);
    real_type t10  = sin(t6);
    real_type t12  = L__[iL_lambda3__xo];
    real_type t13  = P__[iP_kappa1];
    result__[ 0   ] = 2 * t1 * t2 + t10 * L__[iL_lambda2__xo] + t12 * t13 + t7 * L__[iL_lambda1__xo] + 1;
    real_type t15  = P__[iP_L2];
    real_type t19  = X__[iX_theta2];
    real_type t20  = cos(t19);
    real_type t23  = sin(t19);
    real_type t25  = L__[iL_lambda6__xo];
    real_type t26  = P__[iP_kappa2];
    result__[ 1   ] = 2 * t1 * t15 + t20 * L__[iL_lambda4__xo] + t23 * L__[iL_lambda5__xo] + t25 * t26 + 1;
    real_type t28  = P__[iP_L3];
    real_type t32  = X__[iX_theta3];
    real_type t33  = cos(t32);
    real_type t36  = sin(t32);
    real_type t38  = L__[iL_lambda9__xo];
    real_type t39  = P__[iP_kappa3];
    result__[ 2   ] = 2 * t1 * t28 + t33 * L__[iL_lambda7__xo] + t36 * L__[iL_lambda8__xo] + t38 * t39 + 1;
    real_type t42  = ModelPars[iM_epsilon_K];
    result__[ 3   ] = t12 * t2 + 2 * t13 * t42;
    result__[ 4   ] = t15 * t25 + 2 * t26 * t42;
    result__[ 5   ] = t28 * t38 + 2 * t39 * t42;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DHpDp_numRows() const
  { return 6; }

  integer
  MultipleDubins::DHpDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DHpDp_nnz() const
  { return 12; }

  void
  MultipleDubins::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 4   ;
    iIndex[10] = 5   ; jIndex[10] = 2   ;
    iIndex[11] = 5   ; jIndex[11] = 5   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DHpDp_sparse(
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
    result__[ 0   ] = 2 * ModelPars[iM_epsilon_L];
    result__[ 1   ] = L__[iL_lambda3__xo];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = L__[iL_lambda6__xo];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = L__[iL_lambda9__xo];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = 2 * ModelPars[iM_epsilon_K];
    result__[ 8   ] = result__[3];
    result__[ 9   ] = result__[7];
    result__[ 10  ] = result__[5];
    result__[ 11  ] = result__[9];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse" ,12, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  MultipleDubins::eta_numEqns() const
  { return 9; }

  void
  MultipleDubins::eta_eval(
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
    result__[ 5   ] = L__[iL_lambda6__xo];
    result__[ 6   ] = L__[iL_lambda7__xo];
    result__[ 7   ] = L__[iL_lambda8__xo];
    result__[ 8   ] = L__[iL_lambda9__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DetaDx_numRows() const
  { return 9; }

  integer
  MultipleDubins::DetaDx_numCols() const
  { return 9; }

  integer
  MultipleDubins::DetaDx_nnz() const
  { return 0; }

  void
  MultipleDubins::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DetaDp_numRows() const
  { return 9; }

  integer
  MultipleDubins::DetaDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DetaDp_nnz() const
  { return 0; }

  void
  MultipleDubins::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DetaDp_sparse(
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
  MultipleDubins::nu_numEqns() const
  { return 9; }

  void
  MultipleDubins::nu_eval(
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
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    result__[ 7   ] = V__[7];
    result__[ 8   ] = V__[8];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DnuDx_numRows() const
  { return 9; }

  integer
  MultipleDubins::DnuDx_numCols() const
  { return 9; }

  integer
  MultipleDubins::DnuDx_nnz() const
  { return 0; }

  void
  MultipleDubins::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DnuDp_numRows() const
  { return 9; }

  integer
  MultipleDubins::DnuDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DnuDp_nnz() const
  { return 0; }

  void
  MultipleDubins::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: MultipleDubins_Methods_AdjointODE.cc
