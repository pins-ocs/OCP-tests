/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_AdjointODE.cc                    |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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


namespace LUUS_DrugDisplacementDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  LUUS_DrugDisplacement::Hx_numEqns() const
  { return 2; }

  void
  LUUS_DrugDisplacement::Hx_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t8   = 0.2e-1 - t4;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t5;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t4;
    real_type t18  = g1(t4, t5);
    real_type t19  = g4_D_1(t4, t5);
    real_type t27  = t2 * L__[iL_lambda2__xo];
    real_type t28  = g3(t4, t5);
    real_type t31  = t12 * t28 + 0.928e0 - 0.464e2 * t4;
    real_type t34  = g3_D_1(t4, t5);
    result__[ 0   ] = t15 * t6 * t3 + (t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t5) * t18 * t3 + t31 * t6 * t27 + (t12 * t34 - 0.464e2) * t18 * t27;
    real_type t39  = g1_D_2(t4, t5);
    real_type t42  = g4_D_2(t4, t5);
    real_type t50  = g3_D_2(t4, t5);
    result__[ 1   ] = t15 * t39 * t3 + (t8 * t42 - 0.928e2 * t4) * t18 * t3 + t31 * t39 * t27 + (t12 * t50 - 2 * t28) * t18 * t27;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DHxDx_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DHxDx_numCols() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DHxDx_nnz() const
  { return 4; }

  void
  LUUS_DrugDisplacement::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  void
  LUUS_DrugDisplacement::DHxDx_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1_1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t8   = 0.2e-1 - t4;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t5;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t4;
    real_type t18  = g1_D_1(t4, t5);
    real_type t19  = g4_D_1(t4, t5);
    real_type t23  = t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t5;
    real_type t27  = g1(t4, t5);
    real_type t28  = g4_D_1_1(t4, t5);
    real_type t35  = t2 * L__[iL_lambda2__xo];
    real_type t36  = g3(t4, t5);
    real_type t39  = t12 * t36 + 0.928e0 - 0.464e2 * t4;
    real_type t42  = g3_D_1(t4, t5);
    real_type t44  = t12 * t42 - 0.464e2;
    real_type t48  = g3_D_1_1(t4, t5);
    result__[ 0   ] = t15 * t6 * t3 + 2 * t23 * t18 * t3 + (t8 * t28 - 2 * t19) * t27 * t3 + t39 * t6 * t35 + 2 * t44 * t18 * t35 + t12 * t48 * t27 * t35;
    real_type t52  = g1_D_1_2(t4, t5);
    real_type t55  = g4_D_2(t4, t5);
    real_type t58  = t8 * t55 - 0.928e2 * t4;
    real_type t61  = g1_D_2(t4, t5);
    real_type t64  = g4_D_1_2(t4, t5);
    real_type t71  = g3_D_2(t4, t5);
    real_type t74  = t12 * t71 - 2 * t36;
    real_type t79  = g3_D_1_2(t4, t5);
    result__[ 1   ] = t15 * t52 * t3 + t58 * t18 * t3 + t23 * t61 * t3 + (t8 * t64 - t55 - 0.928e2) * t27 * t3 + t39 * t52 * t35 + t74 * t18 * t35 + t44 * t61 * t35 + (t12 * t79 - 2 * t42) * t27 * t35;
    result__[ 2   ] = result__[1];
    real_type t85  = g1_D_2_2(t4, t5);
    real_type t91  = g4_D_2_2(t4, t5);
    real_type t100 = g3_D_2_2(t4, t5);
    result__[ 3   ] = t15 * t85 * t3 + 2 * t58 * t61 * t3 + t8 * t91 * t27 * t3 + t39 * t85 * t35 + 2 * t74 * t61 * t35 + (t12 * t100 - 4 * t71) * t27 * t35;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DHxDp_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DHxDp_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DHxDp_nnz() const
  { return 2; }

  void
  LUUS_DrugDisplacement::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DHxDp_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1_D_1(t2, t3);
    real_type t6   = g4(t2, t3);
    real_type t7   = 0.2e-1 - t2;
    real_type t9   = U__[iU_u];
    real_type t11  = t9 - 2 * t3;
    real_type t14  = t7 * t6 + 0.464e2 * t11 * t2;
    real_type t16  = g1(t2, t3);
    real_type t17  = t16 * t1;
    real_type t18  = g4_D_1(t2, t3);
    real_type t24  = L__[iL_lambda2__xo];
    real_type t26  = g3(t2, t3);
    real_type t29  = t11 * t26 + 0.928e0 - 0.464e2 * t2;
    real_type t31  = t16 * t24;
    real_type t32  = g3_D_1(t2, t3);
    result__[ 0   ] = t14 * t4 * t1 + (t7 * t18 - t6 + 0.464e2 * t9 - 0.928e2 * t3) * t17 + t29 * t4 * t24 + (t11 * t32 - 0.464e2) * t31;
    real_type t36  = g1_D_2(t2, t3);
    real_type t39  = g4_D_2(t2, t3);
    real_type t46  = g3_D_2(t2, t3);
    result__[ 1   ] = t14 * t36 * t1 + (t7 * t39 - 0.928e2 * t2) * t17 + t29 * t36 * t24 + (t11 * t46 - 2 * t26) * t31;
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
  LUUS_DrugDisplacement::Hu_numEqns() const
  { return 1; }

  void
  LUUS_DrugDisplacement::Hu_eval(
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
    real_type t2   = P__[iP_T];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1(t4, t5);
    real_type t12  = g3(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t2 * L__[iL_lambda1__xo] + t12 * t6 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DHuDx_numRows() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DHuDx_numCols() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DHuDx_nnz() const
  { return 2; }

  void
  LUUS_DrugDisplacement::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DHuDx_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t10  = g1(t4, t5);
    real_type t14  = t2 * L__[iL_lambda2__xo];
    real_type t15  = g3(t4, t5);
    real_type t18  = g3_D_1(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t3 + 0.464e2 * t10 * t3 + t15 * t6 * t14 + t18 * t10 * t14;
    real_type t21  = g1_D_2(t4, t5);
    real_type t27  = g3_D_2(t4, t5);
    result__[ 1   ] = 0.464e2 * t4 * t21 * t3 + t15 * t21 * t14 + t27 * t10 * t14;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DHuDp_numRows() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DHuDp_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DHuDp_nnz() const
  { return 1; }

  void
  LUUS_DrugDisplacement::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DHuDp_sparse(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1(t2, t3);
    real_type t10  = g3(t2, t3);
    result__[ 0   ] = 0.464e2 * t2 * t4 * L__[iL_lambda1__xo] + t10 * t4 * L__[iL_lambda2__xo];
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
  LUUS_DrugDisplacement::Hp_numEqns() const
  { return 1; }

  void
  LUUS_DrugDisplacement::Hp_eval(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1(t2, t3);
    real_type t6   = g4(t2, t3);
    real_type t11  = U__[iU_u] - 2 * t3;
    real_type t18  = g3(t2, t3);
    result__[ 0   ] = ((0.2e-1 - t2) * t6 + 0.464e2 * t11 * t2) * t4 * L__[iL_lambda1__xo] + (t11 * t18 + 0.928e0 - 0.464e2 * t2) * t4 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DHpDp_numRows() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DHpDp_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DHpDp_nnz() const
  { return 0; }

  void
  LUUS_DrugDisplacement::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DHpDp_sparse(
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
  LUUS_DrugDisplacement::eta_numEqns() const
  { return 2; }

  void
  LUUS_DrugDisplacement::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DetaDx_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DetaDx_numCols() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DetaDx_nnz() const
  { return 0; }

  void
  LUUS_DrugDisplacement::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DetaDp_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DetaDp_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DetaDp_nnz() const
  { return 0; }

  void
  LUUS_DrugDisplacement::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DetaDp_sparse(
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
  LUUS_DrugDisplacement::nu_numEqns() const
  { return 2; }

  void
  LUUS_DrugDisplacement::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DnuDx_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DnuDx_numCols() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DnuDx_nnz() const
  { return 0; }

  void
  LUUS_DrugDisplacement::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DnuDp_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::DnuDp_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DnuDp_nnz() const
  { return 0; }

  void
  LUUS_DrugDisplacement::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: LUUS_DrugDisplacement_Methods_AdjointODE.cc
