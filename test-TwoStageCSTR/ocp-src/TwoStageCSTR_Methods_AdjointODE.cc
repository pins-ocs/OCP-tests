/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods_AdjointODE.cc                             |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoStageCSTRDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  TwoStageCSTR::Hx_numEqns() const
  { return 4; }

  void
  TwoStageCSTR::Hx_eval(
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
    real_type t1   = X__[iX_x1];
    real_type t3   = L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x2];
    real_type t5   = R1_D_1(t1, t4);
    real_type t6   = -1 - t5;
    real_type t8   = L__[iL_lambda2__xo];
    real_type t10  = L__[iL_lambda3__xo];
    real_type t11  = ModelPars[iM_tau];
    real_type t15  = L__[iL_lambda4__xo];
    result__[ 0   ] = 2 * t1 + t6 * t3 + t5 * t8 + (-t6 * t11 + 1) * t10 - t5 * t11 * t15;
    real_type t19  = R1_D_2(t1, t4);
    real_type t22  = t19 - 2 - U__[iU_u1];
    result__[ 1   ] = 2 * t4 - t19 * t3 + t22 * t8 + t19 * t11 * t10 + (-t22 * t11 + 1) * t15;
    real_type t29  = X__[iX_x3];
    real_type t31  = X__[iX_x4];
    real_type t32  = R2_D_1(t29, t31);
    result__[ 2   ] = 2 * t29 + (-1 - t32) * t10 + t32 * t15;
    real_type t37  = R2_D_2(t29, t31);
    result__[ 3   ] = 2 * t31 - t37 * t10 + (-2 - U__[iU_u2] + t37) * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::DHxDx_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::DHxDx_numCols() const
  { return 4; }

  integer
  TwoStageCSTR::DHxDx_nnz() const
  { return 8; }

  void
  TwoStageCSTR::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
  }

  void
  TwoStageCSTR::DHxDx_sparse(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = R1_D_1_1(t2, t3);
    real_type t6   = L__[iL_lambda2__xo];
    real_type t8   = L__[iL_lambda3__xo];
    real_type t9   = ModelPars[iM_tau];
    real_type t10  = t9 * t8;
    real_type t12  = L__[iL_lambda4__xo];
    real_type t13  = t9 * t12;
    result__[ 0   ] = -t4 * t1 + t4 * t10 - t4 * t13 + t4 * t6 + 2;
    real_type t15  = R1_D_1_2(t2, t3);
    result__[ 1   ] = -t15 * t1 + t15 * t10 - t15 * t13 + t15 * t6;
    result__[ 2   ] = result__[1];
    real_type t20  = R1_D_2_2(t2, t3);
    result__[ 3   ] = -t20 * t1 + t20 * t10 - t20 * t13 + t20 * t6 + 2;
    real_type t25  = X__[iX_x3];
    real_type t26  = X__[iX_x4];
    real_type t27  = R2_D_1_1(t25, t26);
    result__[ 4   ] = t27 * t12 - t27 * t8 + 2;
    real_type t30  = R2_D_1_2(t25, t26);
    result__[ 5   ] = t30 * t12 - t30 * t8;
    result__[ 6   ] = result__[5];
    real_type t33  = R2_D_2_2(t25, t26);
    result__[ 7   ] = t33 * t12 - t33 * t8 + 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::DHxDp_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::DHxDp_numCols() const
  { return 0; }

  integer
  TwoStageCSTR::DHxDp_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DHxDp_sparse(
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
  TwoStageCSTR::Hu_numEqns() const
  { return 2; }

  void
  TwoStageCSTR::Hu_eval(
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
    real_type t1   = ModelPars[iM_W];
    real_type t7   = -X__[iX_x2] - 0.25e0;
    real_type t9   = L__[iL_lambda4__xo];
    result__[ 0   ] = -t7 * ModelPars[iM_tau] * t9 + 2 * U__[iU_u1] * t1 + t7 * L__[iL_lambda2__xo];
    result__[ 1   ] = 2 * U__[iU_u2] * t1 + (-X__[iX_x4] - 0.25e0) * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::DHuDx_numRows() const
  { return 2; }

  integer
  TwoStageCSTR::DHuDx_numCols() const
  { return 4; }

  integer
  TwoStageCSTR::DHuDx_nnz() const
  { return 2; }

  void
  TwoStageCSTR::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DHuDx_sparse(
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
    real_type t1   = L__[iL_lambda4__xo];
    result__[ 0   ] = ModelPars[iM_tau] * t1 - L__[iL_lambda2__xo];
    result__[ 1   ] = -t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::DHuDp_numRows() const
  { return 2; }

  integer
  TwoStageCSTR::DHuDp_numCols() const
  { return 0; }

  integer
  TwoStageCSTR::DHuDp_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DHuDp_sparse(
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
  TwoStageCSTR::Hp_numEqns() const
  { return 0; }

  void
  TwoStageCSTR::Hp_eval(
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
  TwoStageCSTR::DHpDp_numRows() const
  { return 0; }

  integer
  TwoStageCSTR::DHpDp_numCols() const
  { return 0; }

  integer
  TwoStageCSTR::DHpDp_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DHpDp_sparse(
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
  TwoStageCSTR::eta_numEqns() const
  { return 4; }

  void
  TwoStageCSTR::eta_eval(
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
  TwoStageCSTR::DetaDx_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::DetaDx_numCols() const
  { return 4; }

  integer
  TwoStageCSTR::DetaDx_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::DetaDp_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::DetaDp_numCols() const
  { return 0; }

  integer
  TwoStageCSTR::DetaDp_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DetaDp_sparse(
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
  TwoStageCSTR::nu_numEqns() const
  { return 4; }

  void
  TwoStageCSTR::nu_eval(
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
  TwoStageCSTR::DnuDx_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::DnuDx_numCols() const
  { return 4; }

  integer
  TwoStageCSTR::DnuDx_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::DnuDp_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::DnuDp_numCols() const
  { return 0; }

  integer
  TwoStageCSTR::DnuDp_nnz() const
  { return 0; }

  void
  TwoStageCSTR::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: TwoStageCSTR_Methods_AdjointODE.cc
