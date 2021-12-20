/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_AdjointODE.cc                         |
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


#include "TwoPhaseSchwartz.hh"
#include "TwoPhaseSchwartz_Pars.hh"

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
#define ALIAS_bound2_DD(__t1) bound2.DD( __t1)
#define ALIAS_bound2_D(__t1) bound2.D( __t1)
#define ALIAS_bound1_DD(__t1) bound1.DD( __t1)
#define ALIAS_bound1_D(__t1) bound1.D( __t1)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoPhaseSchwartzDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  TwoPhaseSchwartz::Hx_numEqns() const
  { return 4; }

  void
  TwoPhaseSchwartz::Hx_eval(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = t1 - 1;
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    real_type t10  = ALIAS_bound1_D(-1 + 9 * t3 + t8);
    real_type t13  = L__[iL_lambda2__xo];
    result__[ 0   ] = 18 * t2 * t10 - 0.4e0 * t5 * t1 * t13;
    real_type t21  = ALIAS_bound2_D(0.8e0 + t5);
    real_type t23  = t1 * t1;
    result__[ 1   ] = (0.2222222222e2 * t5 - 0.8888888886e1) * t10 + t21 + L__[iL_lambda1__xo] + (-0.1e0 - 0.2e0 * t23) * t13;
    real_type t28  = ModelPars[iM_T2];
    real_type t29  = t28 * L__[iL_lambda4__xo];
    real_type t30  = X__[iX_x3];
    result__[ 2   ] = -0.4e0 * X__[iX_x4] * t30 * t29;
    real_type t37  = t30 * t30;
    result__[ 3   ] = t28 * L__[iL_lambda3__xo] + (-0.1e0 - 0.2e0 * t37) * t29;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DHxDx_numRows() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DHxDx_numCols() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DHxDx_nnz() const
  { return 7; }

  void
  TwoPhaseSchwartz::DHxDx_pattern(
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
  }

  void
  TwoPhaseSchwartz::DHxDx_sparse(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = t1 - 1;
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    real_type t9   = -1 + 9 * t3 + t8;
    real_type t10  = ALIAS_bound1_DD(t9);
    real_type t11  = 18 * t2;
    real_type t12  = t11 * t11;
    real_type t14  = ALIAS_bound1_D(t9);
    real_type t16  = L__[iL_lambda2__xo];
    result__[ 0   ] = t12 * t10 + 18 * t14 - 0.4e0 * t5 * t16;
    real_type t20  = 0.2222222222e2 * t5 - 0.8888888886e1;
    result__[ 1   ] = t11 * t20 * t10 - 0.4e0 * t1 * t16;
    result__[ 2   ] = result__[1];
    real_type t25  = t20 * t20;
    real_type t29  = ALIAS_bound2_DD(0.8e0 + t5);
    result__[ 3   ] = t25 * t10 + 0.2222222222e2 * t14 + t29;
    real_type t32  = ModelPars[iM_T2] * L__[iL_lambda4__xo];
    result__[ 4   ] = -0.4e0 * X__[iX_x4] * t32;
    result__[ 5   ] = -0.4e0 * X__[iX_x3] * t32;
    result__[ 6   ] = result__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DHxDp_numRows() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DHxDp_numCols() const
  { return 0; }

  integer
  TwoPhaseSchwartz::DHxDp_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DHxDp_sparse(
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
  TwoPhaseSchwartz::Hu_numEqns() const
  { return 2; }

  void
  TwoPhaseSchwartz::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda2__xo];
    result__[ 1   ] = L__[iL_lambda4__xo] * ModelPars[iM_T2] + 2 * ModelPars[iM_epsilon] * U__[iU_u2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DHuDx_numRows() const
  { return 2; }

  integer
  TwoPhaseSchwartz::DHuDx_numCols() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DHuDx_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DHuDp_numRows() const
  { return 2; }

  integer
  TwoPhaseSchwartz::DHuDp_numCols() const
  { return 0; }

  integer
  TwoPhaseSchwartz::DHuDp_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DHuDp_sparse(
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
  TwoPhaseSchwartz::Hp_numEqns() const
  { return 0; }

  void
  TwoPhaseSchwartz::Hp_eval(
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
  TwoPhaseSchwartz::DHpDp_numRows() const
  { return 0; }

  integer
  TwoPhaseSchwartz::DHpDp_numCols() const
  { return 0; }

  integer
  TwoPhaseSchwartz::DHpDp_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DHpDp_sparse(
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
  TwoPhaseSchwartz::eta_numEqns() const
  { return 4; }

  void
  TwoPhaseSchwartz::eta_eval(
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
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DetaDx_numRows() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DetaDx_numCols() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DetaDx_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DetaDp_numRows() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DetaDp_numCols() const
  { return 0; }

  integer
  TwoPhaseSchwartz::DetaDp_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DetaDp_sparse(
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
  TwoPhaseSchwartz::nu_numEqns() const
  { return 4; }

  void
  TwoPhaseSchwartz::nu_eval(
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
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DnuDx_numRows() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DnuDx_numCols() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DnuDx_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoPhaseSchwartz::DnuDp_numRows() const
  { return 4; }

  integer
  TwoPhaseSchwartz::DnuDp_numCols() const
  { return 0; }

  integer
  TwoPhaseSchwartz::DnuDp_nnz() const
  { return 0; }

  void
  TwoPhaseSchwartz::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: TwoPhaseSchwartz_Methods_AdjointODE.cc
