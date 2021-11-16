/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods_controls.cc                            |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  TwoLinkRobotArm::g_numEqns() const
  { return 2; }

  void
  TwoLinkRobotArm::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x3];
    real_type t2   = sin(t1);
    real_type t3   = t2 * t2;
    real_type t5   = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    real_type t8   = L__[iL_lambda2__xo];
    real_type t9   = P__[iP_T];
    real_type t11  = cos(t1);
    real_type t14  = L__[iL_lambda1__xo];
    real_type t20  = 81 * t3 + 31;
    real_type t21  = 1.0 / t20;
    result__[ 0   ] = t21 * (-54 * t11 * t9 * t8 + 48 * t9 * t14 + 81 * t5 * t3 + 31 * t5);
    real_type t23  = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    result__[ 1   ] = t21 * (t23 * t20 - 54 * (t11 * (t14 - t8) + 8.0 / 9.0 * t14 - 0.14e2 / 9.0 * t8) * t9);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DgDxlp_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDxlp_numCols() const
  { return 9; }

  integer
  TwoLinkRobotArm::DgDxlp_nnz() const
  { return 8; }

  void
  TwoLinkRobotArm::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x3];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = L__[iL_lambda2__xo];
    real_type t6   = cos(t2);
    real_type t7   = t6 * t6;
    real_type t10  = t3 * t3;
    real_type t13  = L__[iL_lambda1__xo];
    real_type t19  = 81 * t10 + 31;
    real_type t20  = t19 * t19;
    real_type t21  = 1.0 / t20;
    result__[ 0   ] = 54 * t21 * (81 * t5 * t10 - 144 * t6 * t13 + 162 * t7 * t5 + 31 * t5) * t4;
    real_type t24  = 1.0 / t19;
    result__[ 1   ] = 48 * t24 * t1;
    result__[ 2   ] = -54 * t24 * t6 * t1;
    real_type t31  = 48 * t13;
    result__[ 3   ] = t24 * (-54 * t6 * t5 + t31);
    real_type t33  = t13 - t5;
    result__[ 4   ] = 8748 * t21 * (t7 * t33 + t6 * (8.0 / 9.0 * t13 - 0.14e2 / 9.0 * t5) + t33 * (t10 + 0.31e2 / 0.81e2) / 2) * t4;
    real_type t45  = 9 * t6;
    result__[ 5   ] = -6 * t24 * (8 + t45) * t1;
    result__[ 6   ] = 6 * t24 * (14 + t45) * t1;
    result__[ 7   ] = t24 * (-54 * t6 * t33 - t31 + 84 * t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DgDu_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDu_numCols() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDu_nnz() const
  { return 2; }

  void
  TwoLinkRobotArm::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DgDu_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  TwoLinkRobotArm::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LL__[iL_lambda2__xo];
    real_type t2   = XL__[iX_x3];
    real_type t3   = cos(t2);
    real_type t4   = t3 * t1;
    real_type t6   = LL__[iL_lambda1__xo];
    real_type t8   = XR__[iX_x3];
    real_type t9   = sin(t8);
    real_type t10  = t9 * t9;
    real_type t12  = sin(t2);
    real_type t13  = t12 * t12;
    real_type t14  = LR__[iL_lambda2__xo];
    real_type t19  = cos(t8);
    real_type t21  = LR__[iL_lambda1__xo];
    real_type t27  = P__[iP_T];
    real_type t35  = 1.0 / (81 * t13 + 31) / (81 * t10 + 31);
    U__[ iU_u1 ] = u1Control.solve(-1944 * t35 * t27 * (t10 * (-9.0 / 8.0 * t4 + t6) + t19 * (-9.0 / 8.0 * t14 * t13 - 0.31e2 / 0.72e2 * t14) + t21 * t13 - 0.31e2 / 0.72e2 * t4 + 0.31e2 / 0.81e2 * t6 + 0.31e2 / 0.81e2 * t21), -1, 1);
    U__[ iU_u2 ] = u2Control.solve(2187 * t35 * t27 * (t3 * (t10 + 0.31e2 / 0.81e2) * (t6 - t1) + t19 * (t13 + 0.31e2 / 0.81e2) * (t21 - t14) + t13 * (8.0 / 9.0 * t21 - 0.14e2 / 9.0 * t14) + t10 * (8.0 / 9.0 * t6 - 0.14e2 / 9.0 * t1) + 0.248e3 / 0.729e3 * t6 + 0.248e3 / 0.729e3 * t21 - 0.434e3 / 0.729e3 * t1 - 0.434e3 / 0.729e3 * t14), -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type tmp_0_0 = 0;
    real_type tmp_1_0 = 0;
    real_type tmp_0_1 = 0;
    real_type tmp_1_1 = 0;
    real_type t1   = XL__[iX_x3];
    real_type t2   = sin(t1);
    real_type t3   = t2 * t2;
    real_type t4   = LL__[iL_lambda2__xo];
    real_type t6   = cos(t1);
    real_type t7   = t6 * t6;
    real_type t10  = LL__[iL_lambda1__xo];
    real_type t16  = t6 * t4;
    real_type t19  = XR__[iX_x3];
    real_type t20  = sin(t19);
    real_type t21  = t20 * t20;
    real_type t22  = t21 * (-9.0 / 8.0 * t16 + t10);
    real_type t23  = LR__[iL_lambda2__xo];
    real_type t28  = cos(t19);
    real_type t30  = LR__[iL_lambda1__xo];
    real_type t32  = 0.31e2 / 0.72e2 * t16;
    real_type t33  = 0.31e2 / 0.81e2 * t10;
    real_type t34  = 0.31e2 / 0.81e2 * t30;
    real_type t36  = P__[iP_T];
    real_type t39  = 81 * t21 + 31;
    real_type t40  = 1.0 / t39;
    real_type t42  = 81 * t3 + 31;
    real_type t43  = 1.0 / t42;
    real_type t44  = t43 * t40;
    real_type t47  = u1Control.solve_rhs(-1944 * t44 * t36 * (t22 + t28 * (-9.0 / 8.0 * t23 * t3 - 0.31e2 / 0.72e2 * t23) + t30 * t3 - t32 + t33 + t34), -1, 1);
    real_type t48  = t36 * t47;
    real_type t49  = t42 * t42;
    real_type t50  = 1.0 / t49;
    real_type tmp_0_2 = -2187 * t50 * t48 * (t4 * t3 + 2 * t4 * t7 - 0.16e2 / 9.0 * t10 * t6 + 0.31e2 / 0.81e2 * t4) * t2;
    real_type t54  = t10 - t4;
    real_type t55  = t21 + 0.31e2 / 0.81e2;
    real_type t58  = t30 - t23;
    real_type t59  = t3 + 0.31e2 / 0.81e2;
    real_type t62  = 8.0 / 9.0 * t30;
    real_type t63  = 0.14e2 / 9.0 * t23;
    real_type t66  = 8.0 / 9.0 * t10;
    real_type t67  = 0.14e2 / 9.0 * t4;
    real_type t70  = 0.248e3 / 0.729e3 * t10;
    real_type t71  = 0.248e3 / 0.729e3 * t30;
    real_type t72  = 0.434e3 / 0.729e3 * t4;
    real_type t73  = 0.434e3 / 0.729e3 * t23;
    real_type t78  = u2Control.solve_rhs(2187 * t44 * t36 * (t6 * t55 * t54 + t28 * t59 * t58 + t3 * (t62 - t63) + t21 * (t66 - t67) + t70 + t71 - t72 - t73), -1, 1);
    real_type tmp_1_2 = -2187 * t50 * t36 * (2 * t7 * t54 + t6 * (0.16e2 / 9.0 * t10 - 0.28e2 / 9.0 * t4) + t59 * t54) * t78 * t2;
    real_type tmp_0_3 = 0;
    real_type tmp_1_3 = 0;
    real_type tmp_0_4 = -24 * t43 * t48;
    real_type t94  = 9 * t6;
    real_type t97  = t43 * t36;
    real_type tmp_1_4 = 3 * t97 * (t94 + 8) * t78;
    real_type tmp_0_5 = 27 * t97 * t6 * t47;
    real_type tmp_1_5 = -3 * t97 * t78 * (t94 + 14);
    real_type tmp_0_6 = 0;
    real_type tmp_1_6 = 0;
    real_type tmp_0_7 = 0;
    real_type tmp_1_7 = 0;
    real_type tmp_0_8 = 0;
    real_type tmp_1_8 = 0;
    real_type tmp_0_9 = 0;
    real_type tmp_1_9 = 0;
    real_type t107 = t28 * t28;
    real_type t115 = t39 * t39;
    real_type t116 = 1.0 / t115;
    real_type tmp_0_10 = -2187 * t116 * t36 * (t23 * t21 + 2 * t23 * t107 - 0.16e2 / 9.0 * t30 * t28 + 0.31e2 / 0.81e2 * t23) * t20 * t47;
    real_type tmp_1_10 = -2187 * t116 * t36 * (2 * t107 * t58 + t28 * (0.16e2 / 9.0 * t30 - 0.28e2 / 9.0 * t23) + t55 * t58) * t20 * t78;
    real_type tmp_0_11 = 0;
    real_type tmp_1_11 = 0;
    real_type tmp_0_12 = -24 * t40 * t48;
    real_type t135 = 9 * t28;
    real_type t138 = t40 * t36;
    real_type tmp_1_12 = 3 * t138 * (t135 + 8) * t78;
    real_type tmp_0_13 = 27 * t138 * t28 * t47;
    real_type tmp_1_13 = -3 * t138 * (t135 + 14) * t78;
    real_type tmp_0_14 = 0;
    real_type tmp_1_14 = 0;
    real_type tmp_0_15 = 0;
    real_type tmp_1_15 = 0;
    real_type t146 = t28 * t23;
    real_type tmp_0_16 = -1944 * t44 * (t3 * (-9.0 / 8.0 * t146 + t30) + t22 - t32 - 0.31e2 / 0.72e2 * t146 + t33 + t34) * t47;
    real_type tmp_1_16 = 2187 * t44 * (t3 * (t28 * t58 + t62 - t63) + t21 * (t6 * t54 + t66 - t67) + 0.31e2 / 0.81e2 * t6 * t54 + 0.31e2 / 0.81e2 * t28 * t58 + t70 + t71 - t72 - t73) * t78;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(1, 4) = tmp_1_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(1, 5) = tmp_1_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(1, 6) = tmp_1_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(1, 7) = tmp_1_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(1, 8) = tmp_1_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(1, 9) = tmp_1_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(1, 10) = tmp_1_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(1, 11) = tmp_1_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(1, 12) = tmp_1_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(1, 13) = tmp_1_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(1, 14) = tmp_1_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(1, 15) = tmp_1_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(1, 16) = tmp_1_16;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 34 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  TwoLinkRobotArm::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = u1Control(t1, -1, 1);
    real_type t3   = U__[iU_u2];
    real_type t4   = u2Control(t3, -1, 1);
    real_type t6   = P__[iP_T];
    real_type t7   = X__[iX_x3];
    real_type t8   = sin(t7);
    real_type t9   = cos(t7);
    real_type t10  = X__[iX_x1];
    real_type t11  = t10 * t10;
    real_type t14  = X__[iX_x2];
    real_type t15  = t14 * t14;
    real_type t25  = t8 * t8;
    real_type t28  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t25);
    real_type t31  = pow(V__[0] - t28 * ((9.0 / 4.0 * t11 * t9 + 2 * t15) * t8 + 4.0 / 3.0 * t1 - 4.0 / 3.0 * t3 - 3.0 / 2.0 * t3 * t9) * t6, 2);
    real_type t46  = pow(V__[1] + t28 * ((7.0 / 2.0 * t11 + 9.0 / 4.0 * t15 * t9) * t8 - 7.0 / 3.0 * t3 + 3.0 / 2.0 * (t1 - t3) * t9) * t6, 2);
    real_type t51  = pow(t6 * (t10 - t14) + V__[2], 2);
    real_type t55  = pow(-t10 * t6 + V__[3], 2);
    real_type result__ = t2 + t4 + t31 + t46 + t51 + t55;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DmDu_numEqns() const
  { return 2; }

  void
  TwoLinkRobotArm::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x3];
    real_type t2   = sin(t1);
    real_type t3   = t2 * t2;
    real_type t5   = pow(t3 + 0.31e2 / 0.81e2, 2);
    real_type t6   = U__[iU_u1];
    real_type t7   = ALIAS_u1Control_D_1(t6, -1, 1);
    real_type t10  = P__[iP_T];
    real_type t11  = V__[1];
    real_type t12  = cos(t1);
    real_type t15  = V__[0];
    real_type t20  = X__[iX_x2] * X__[iX_x2];
    real_type t21  = t12 * t12;
    real_type t25  = X__[iX_x1] * X__[iX_x1];
    real_type t31  = U__[iU_u2];
    real_type t32  = t6 - t31;
    real_type t50  = pow(81 * t3 + 31, 2);
    real_type t51  = 1.0 / t50;
    result__[ 0   ] = t51 * (6561 * t7 * t5 + 21384 * (t3 * (9.0 / 0.22e2 * t12 * t11 - 4.0 / 0.11e2 * t15) + t2 * (9.0 / 0.22e2 * t21 * t20 + t25 * t12 + 0.32e2 / 0.99e2 * t20) * t10 + 3.0 / 0.11e2 * t21 * t32 * t10 + t12 * (-2.0 / 3.0 * t31 * t10 + 0.31e2 / 0.198e3 * t11) + 0.64e2 / 0.297e3 * t32 * t10 - 0.124e3 / 0.891e3 * t15) * t10);
    real_type t52  = ALIAS_u2Control_D_1(t31, -1, 1);
    real_type t61  = t25 + t20;
    result__[ 1   ] = t51 * (6561 * t52 * t5 - 8748 * t10 * (t3 * (t12 * (-t15 + t11) - 8.0 / 9.0 * t15 + 0.14e2 / 9.0 * t11) + t2 * t10 * (t21 * t61 + 0.22e2 / 9.0 * t12 * t61 + 0.196e3 / 0.81e2 * t25 + 0.64e2 / 0.81e2 * t20) + 2.0 / 3.0 * t21 * (t6 - 2 * t31) * t10 + t12 * (t10 * (0.44e2 / 0.27e2 * t6 - 0.88e2 / 0.27e2 * t31) - 0.31e2 / 0.81e2 * t15 + 0.31e2 / 0.81e2 * t11) + t10 * (0.128e3 / 0.243e3 * t6 - 0.520e3 / 0.243e3 * t31) - 0.248e3 / 0.729e3 * t15 + 0.434e3 / 0.729e3 * t11));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DmDuu_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DmDuu_numCols() const
  { return 2; }

  integer
  TwoLinkRobotArm::DmDuu_nnz() const
  { return 4; }

  void
  TwoLinkRobotArm::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x3];
    real_type t2   = sin(t1);
    real_type t3   = t2 * t2;
    real_type t5   = pow(t3 + 0.31e2 / 0.81e2, 2);
    real_type t7   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    real_type t10  = cos(t1);
    real_type t11  = t10 * t10;
    real_type t13  = P__[iP_T] * P__[iP_T];
    real_type t20  = pow(81 * t3 + 31, 2);
    real_type t21  = 1.0 / t20;
    result__[ 0   ] = t21 * (5832 * t13 * t11 + 6561 * t7 * t5 + 4608 * t13);
    result__[ 1   ] = -72 * t21 * (81 * t11 + 198 * t10 + 64) * t13;
    result__[ 2   ] = result__[1];
    real_type t29  = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    result__[ 3   ] = t21 * (6561 * t29 * t5 + 11664 * t13 * (t11 + 0.22e2 / 9.0 * t10 + 0.130e3 / 0.81e2));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: TwoLinkRobotArm_Methods_controls.cc
