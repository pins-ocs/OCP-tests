/*-----------------------------------------------------------------------*\
 |  file: SingularLuus04_FreeTime_Methods_AdjointODE.cc                  |
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


#include "SingularLuus04_FreeTime.hh"
#include "SingularLuus04_FreeTime_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace SingularLuus04_FreeTimeDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  SingularLuus04_FreeTime::Hx_numEqns() const
  { return 4; }

  void
  SingularLuus04_FreeTime::Hx_eval(
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
    real_type t1   = X__[iX_T];
    real_type t2   = X__[iX_x];
    result__[ 0   ] = 2 * t2 * t1;
    real_type t4   = L__[iL_lambda1__xo];
    result__[ 1   ] = t1 * t4;
    real_type t5   = L__[iL_lambda2__xo];
    result__[ 2   ] = t1 * t5;
    real_type t6   = U__[iU_u];
    real_type t7   = uControl(t6, -1, 1);
    real_type t11  = t2 * t2;
    result__[ 3   ] = 2 * t1 * ModelPars[iM_theta] + t4 * X__[iX_y] + t5 * X__[iX_z] + t6 * L__[iL_lambda3__xo] + t11 + t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularLuus04_FreeTime::DHxDx_numRows() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DHxDx_numCols() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DHxDx_nnz() const
  { return 8; }

  void
  SingularLuus04_FreeTime::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
  }

  void
  SingularLuus04_FreeTime::DHxDx_sparse(
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
    result__[ 0   ] = 2 * X__[iX_T];
    result__[ 1   ] = 2 * X__[iX_x];
    result__[ 2   ] = L__[iL_lambda1__xo];
    result__[ 3   ] = L__[iL_lambda2__xo];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[3];
    result__[ 7   ] = 2 * ModelPars[iM_theta];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularLuus04_FreeTime::DHxDp_numRows() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DHxDp_numCols() const
  { return 0; }

  integer
  SingularLuus04_FreeTime::DHxDp_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DHxDp_sparse(
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
  SingularLuus04_FreeTime::Hu_numEqns() const
  { return 1; }

  void
  SingularLuus04_FreeTime::Hu_eval(
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
    real_type t1   = X__[iX_T];
    real_type t3   = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 0   ] = t3 * t1 + t1 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularLuus04_FreeTime::DHuDx_numRows() const
  { return 1; }

  integer
  SingularLuus04_FreeTime::DHuDx_numCols() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DHuDx_nnz() const
  { return 1; }

  void
  SingularLuus04_FreeTime::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DHuDx_sparse(
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
    real_type t2   = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 0   ] = t2 + L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularLuus04_FreeTime::DHuDp_numRows() const
  { return 1; }

  integer
  SingularLuus04_FreeTime::DHuDp_numCols() const
  { return 0; }

  integer
  SingularLuus04_FreeTime::DHuDp_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DHuDp_sparse(
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
  SingularLuus04_FreeTime::Hp_numEqns() const
  { return 0; }

  void
  SingularLuus04_FreeTime::Hp_eval(
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
  SingularLuus04_FreeTime::DHpDp_numRows() const
  { return 0; }

  integer
  SingularLuus04_FreeTime::DHpDp_numCols() const
  { return 0; }

  integer
  SingularLuus04_FreeTime::DHpDp_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DHpDp_sparse(
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
  SingularLuus04_FreeTime::eta_numEqns() const
  { return 4; }

  void
  SingularLuus04_FreeTime::eta_eval(
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
  SingularLuus04_FreeTime::DetaDx_numRows() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DetaDx_numCols() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DetaDx_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularLuus04_FreeTime::DetaDp_numRows() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DetaDp_numCols() const
  { return 0; }

  integer
  SingularLuus04_FreeTime::DetaDp_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DetaDp_sparse(
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
  SingularLuus04_FreeTime::nu_numEqns() const
  { return 4; }

  void
  SingularLuus04_FreeTime::nu_eval(
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
  SingularLuus04_FreeTime::DnuDx_numRows() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DnuDx_numCols() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DnuDx_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularLuus04_FreeTime::DnuDp_numRows() const
  { return 4; }

  integer
  SingularLuus04_FreeTime::DnuDp_numCols() const
  { return 0; }

  integer
  SingularLuus04_FreeTime::DnuDp_nnz() const
  { return 0; }

  void
  SingularLuus04_FreeTime::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularLuus04_FreeTime::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: SingularLuus04_FreeTime_Methods_AdjointODE.cc
