/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods_AdjointODE.cc                          |
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


#include "TwoLinkRobotArm.hh"
#include "TwoLinkRobotArm_Pars.hh"

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


namespace TwoLinkRobotArmDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  TwoLinkRobotArm::Hx_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::Hx_eval(
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
    real_type t1   = P__[iP_T];
    real_type t2   = L__[iL_lambda1__xo];
    real_type t3   = X__[iX_x3];
    real_type t4   = sin(t3);
    real_type t6   = cos(t3);
    real_type t7   = X__[iX_x1];
    real_type t11  = L__[iL_lambda2__xo];
    real_type t15  = t4 * t4;
    real_type t16  = L__[iL_lambda3__xo];
    real_type t17  = t16 * t15;
    real_type t19  = L__[iL_lambda4__xo];
    real_type t27  = 81 * t15 + 31;
    real_type t28  = 1.0 / t27;
    result__[ 0   ] = t28 * (162 * t7 * t6 * t4 * t2 - 252 * t7 * t4 * t11 + 81 * t19 * t15 - 31 * t16 - 81 * t17 + 31 * t19) * t1;
    real_type t30  = X__[iX_x2];
    result__[ 1   ] = 144 * t28 * (9.0 / 0.16e2 * t17 + t4 * (-9.0 / 8.0 * t6 * t11 + t2) * t30 + 0.31e2 / 0.144e3 * t16) * t1;
    real_type t40  = t7 * t7;
    real_type t41  = t40 * t2;
    real_type t42  = t30 * t30;
    real_type t43  = t42 * t11;
    real_type t44  = t41 - t43;
    real_type t45  = t15 * t15;
    real_type t48  = U__[iU_u2];
    real_type t49  = -U__[iU_u1] + t48;
    real_type t52  = t48 * t2;
    real_type t57  = t6 * t6;
    real_type t60  = 8.0 / 9.0 * t42 * t2;
    real_type t62  = 0.14e2 / 9.0 * t40 * t11;
    real_type t92  = t27 * t27;
    result__[ 2   ] = -6561 / t92 * (t45 * t44 + t15 * t4 * (2.0 / 3.0 * t11 * t49 - 2.0 / 3.0 * t52) + t15 * (t57 * t44 + t6 * (t60 - t62) + 0.31e2 / 0.81e2 * t41 - 0.31e2 / 0.81e2 * t43) + t4 * (t57 * (4.0 / 3.0 * t11 * t49 - 4.0 / 3.0 * t52) + t6 * (0.56e2 / 0.27e2 * t48 * t11 - 0.32e2 / 0.27e2 * t49 * t2) + 0.62e2 / 0.243e3 * t11 * t49 - 0.62e2 / 0.243e3 * t52) - 0.31e2 / 0.81e2 * t6 * (t6 * t44 + t60 - t62)) * t1;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHxDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHxDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHxDx_nnz() const
  { return 7; }

  void
  TwoLinkRobotArm::DHxDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
  }

  void
  TwoLinkRobotArm::DHxDx_sparse(
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
    real_type t1   = X__[iX_x3];
    real_type t2   = sin(t1);
    real_type t3   = P__[iP_T];
    real_type t4   = t3 * t2;
    real_type t5   = L__[iL_lambda1__xo];
    real_type t6   = cos(t1);
    real_type t9   = L__[iL_lambda2__xo];
    real_type t12  = t2 * t2;
    real_type t14  = 81 * t12 + 31;
    real_type t15  = 1.0 / t14;
    result__[ 0   ] = 18 * t15 * (9 * t6 * t5 - 14 * t9) * t4;
    real_type t18  = X__[iX_x1];
    real_type t20  = (t12 - 0.31e2 / 0.81e2) * t5;
    real_type t21  = t6 * t6;
    real_type t23  = t9 * t12;
    real_type t29  = t12 + 0.31e2 / 0.81e2;
    real_type t33  = t14 * t14;
    real_type t35  = 1.0 / t33 * t3;
    result__[ 1   ] = -13122 * t35 * (t21 * t20 + t6 * (-0.14e2 / 9.0 * t23 + 0.434e3 / 0.729e3 * t9) + t29 * t12 * t5) * t18;
    result__[ 2   ] = -18 * t15 * (9 * t6 * t9 - 8 * t5) * t4;
    real_type t54  = X__[iX_x2];
    result__[ 3   ] = -11664 * t35 * t54 * (t21 * (-9.0 / 8.0 * t23 + 0.31e2 / 0.72e2 * t9) + t6 * t20 - 9.0 / 8.0 * t9 * t29 * t12);
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[3];
    real_type t58  = t18 * t18;
    real_type t59  = t58 * t5;
    real_type t60  = t54 * t54;
    real_type t61  = t60 * t9;
    real_type t62  = t59 - t61;
    real_type t64  = t60 * t5;
    real_type t66  = t58 * t9;
    real_type t69  = t12 * t12;
    real_type t73  = U__[iU_u2];
    real_type t74  = -U__[iU_u1] + t73;
    real_type t77  = t73 * t5;
    real_type t81  = t73 * t9;
    real_type t84  = -t74 * t5;
    real_type t103 = t21 * t6;
    real_type t118 = -t62;
    result__[ 6   ] = 1062882 / t33 / t14 * (t69 * t2 * (t6 * t62 + 4.0 / 9.0 * t64 - 7.0 / 9.0 * t66) + t69 * (t6 * (5.0 / 3.0 * t9 * t74 - 5.0 / 3.0 * t77) + 0.28e2 / 0.27e2 * t81 + 0.16e2 / 0.27e2 * t84) + t12 * t2 * t6 * (t21 * t62 + t6 * (8.0 / 9.0 * t64 - 0.14e2 / 9.0 * t66) - 0.31e2 / 0.81e2 * t59 + 0.31e2 / 0.81e2 * t61) + t12 * (t103 * (2 * t9 * t74 - 2 * t77) + t21 * (0.28e2 / 9.0 * t81 + 0.16e2 / 9.0 * t84) + t6 * (0.124e3 / 0.243e3 * t9 * t74 - 0.124e3 / 0.243e3 * t77) + 0.868e3 / 0.2187e4 * t81 + 0.496e3 / 0.2187e4 * t84) + t2 * (0.31e2 / 0.27e2 * t103 * t118 + t21 * (-0.248e3 / 0.243e3 * t64 + 0.434e3 / 0.243e3 * t66) + 0.1922e4 / 0.6561e4 * t6 * t118 - 0.3844e4 / 0.59049e5 * t64 + 0.6727e4 / 0.59049e5 * t66) - 0.496e3 / 0.2187e4 * (t21 * (9.0 / 8.0 * t9 * t74 - 9.0 / 8.0 * t77) + t6 * (7.0 / 4.0 * t81 + t84) + 0.31e2 / 0.144e3 * t9 * t74 - 0.31e2 / 0.144e3 * t77) * t6) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHxDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHxDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHxDp_nnz() const
  { return 3; }

  void
  TwoLinkRobotArm::DHxDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHxDp_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = L__[iL_lambda4__xo];
    real_type t5   = X__[iX_x3];
    real_type t6   = sin(t5);
    real_type t7   = t6 * t6;
    real_type t9   = L__[iL_lambda1__xo];
    real_type t10  = cos(t5);
    real_type t12  = L__[iL_lambda2__xo];
    real_type t15  = X__[iX_x1];
    real_type t19  = 31 * t1;
    real_type t23  = 81 * t7 + 31;
    real_type t24  = 1.0 / t23;
    result__[ 0   ] = t24 * (t7 * (-81 * t1 + 81 * t2) + 162 * t6 * t15 * (t10 * t9 - 0.14e2 / 9.0 * t12) - t19 + 31 * t2);
    real_type t27  = X__[iX_x2];
    result__[ 1   ] = t24 * (81 * t1 * t7 + 144 * t6 * (-9.0 / 8.0 * t10 * t12 + t9) * t27 + t19);
    real_type t35  = t15 * t15;
    real_type t36  = t35 * t9;
    real_type t37  = t27 * t27;
    real_type t38  = t37 * t12;
    real_type t39  = -t36 + t38;
    real_type t40  = 6561 * t39;
    real_type t41  = t7 * t7;
    real_type t44  = U__[iU_u2];
    real_type t45  = U__[iU_u1] - t44;
    real_type t48  = t44 * t9;
    real_type t53  = t10 * t10;
    real_type t55  = t37 * t9;
    real_type t57  = t35 * t12;
    real_type t89  = t23 * t23;
    result__[ 2   ] = 1.0 / t89 * (t41 * t40 + t7 * t6 * (4374 * t12 * t45 + 4374 * t48) + t7 * (t53 * t40 + t10 * (-5832 * t55 + 10206 * t57) - 2511 * t36 + 2511 * t38) + t6 * (t53 * (8748 * t12 * t45 + 8748 * t48) + t10 * (-13608 * t44 * t12 - 7776 * t45 * t9) + 1674 * t12 * t45 + 1674 * t48) + 2511 * (-t10 * t39 + 8.0 / 9.0 * t55 - 0.14e2 / 9.0 * t57) * t10);
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
  TwoLinkRobotArm::Hu_numEqns() const
  { return 2; }

  void
  TwoLinkRobotArm::Hu_eval(
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
    real_type t1   = P__[iP_T];
    real_type t2   = L__[iL_lambda2__xo];
    real_type t3   = X__[iX_x3];
    real_type t4   = cos(t3);
    real_type t7   = L__[iL_lambda1__xo];
    real_type t11  = sin(t3);
    real_type t12  = t11 * t11;
    real_type t15  = 1.0 / (81 * t12 + 31);
    result__[ 0   ] = -6 * t15 * (9 * t4 * t2 - 8 * t7) * t1;
    result__[ 1   ] = -54 * t15 * (t4 * (t7 - t2) + 8.0 / 9.0 * t7 - 0.14e2 / 9.0 * t2) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHuDx_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DHuDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHuDx_nnz() const
  { return 2; }

  void
  TwoLinkRobotArm::DHuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHuDx_sparse(
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
    real_type t1   = X__[iX_x3];
    real_type t2   = sin(t1);
    real_type t3   = P__[iP_T];
    real_type t5   = t2 * t2;
    real_type t6   = L__[iL_lambda2__xo];
    real_type t9   = cos(t1);
    real_type t10  = t9 * t9;
    real_type t13  = L__[iL_lambda1__xo];
    real_type t20  = pow(81 * t5 + 31, 2);
    real_type t21  = 1.0 / t20;
    result__[ 0   ] = 54 * t21 * (162 * t6 * t10 - 144 * t9 * t13 + 81 * t6 * t5 + 31 * t6) * t3 * t2;
    real_type t24  = t13 - t6;
    result__[ 1   ] = 8748 * t21 * t2 * t3 * (t10 * t24 + t9 * (8.0 / 9.0 * t13 - 0.14e2 / 9.0 * t6) + t24 * (t5 + 0.31e2 / 0.81e2) / 2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHuDp_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DHuDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHuDp_nnz() const
  { return 2; }

  void
  TwoLinkRobotArm::DHuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHuDp_sparse(
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
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_x3];
    real_type t3   = cos(t2);
    real_type t6   = L__[iL_lambda1__xo];
    real_type t7   = 48 * t6;
    real_type t9   = sin(t2);
    real_type t10  = t9 * t9;
    real_type t13  = 1.0 / (81 * t10 + 31);
    result__[ 0   ] = t13 * (-54 * t3 * t1 + t7);
    result__[ 1   ] = t13 * (t3 * (-54 * t6 + 54 * t1) - t7 + 84 * t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHuDp_sparse", 2, i_segment );
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
  TwoLinkRobotArm::Hp_numEqns() const
  { return 1; }

  void
  TwoLinkRobotArm::Hp_eval(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t3   = -t1 + L__[iL_lambda4__xo];
    real_type t5   = X__[iX_x1];
    real_type t7   = X__[iX_x2];
    real_type t8   = t7 * t1;
    real_type t11  = X__[iX_x3];
    real_type t12  = sin(t11);
    real_type t13  = t12 * t12;
    real_type t15  = L__[iL_lambda1__xo];
    real_type t16  = t5 * t5;
    real_type t18  = L__[iL_lambda2__xo];
    real_type t19  = t7 * t7;
    real_type t23  = cos(t11);
    real_type t31  = U__[iU_u2];
    real_type t34  = U__[iU_u1] - t31;
    result__[ 0   ] = 1.0 / (81 * t13 + 31) * (t13 * (81 * t5 * t3 + 81 * t8) + t12 * (t23 * (81 * t16 * t15 - 81 * t19 * t18) + 72 * t19 * t15 - 126 * t16 * t18) + t23 * (-54 * t31 * t15 - 54 * t34 * t18) + 31 * t5 * t3 + 48 * t15 * t34 + 84 * t31 * t18 + 31 * t8);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHpDp_numRows() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHpDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHpDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DHpDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHpDp_sparse(
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
  TwoLinkRobotArm::eta_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::eta_eval(
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
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DetaDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DetaDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DetaDx_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DetaDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DetaDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DetaDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DetaDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DetaDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DetaDp_sparse(
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
  TwoLinkRobotArm::nu_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::nu_eval(
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
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DnuDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DnuDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DnuDx_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DnuDx_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DnuDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DnuDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DnuDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DnuDp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: TwoLinkRobotArm_Methods_AdjointODE.cc
