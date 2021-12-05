/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_controls.cc                     |
 |                                                                       |
 |  version: 1.0   date 10/12/2021                                       |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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


namespace ICLOCS_TwoLinkRobotArmDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  ICLOCS_TwoLinkRobotArm::g_numEqns() const
  { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1(UM__[0], -1, 1);
    real_type t5   = cos(XM__[2]);
    real_type t6   = t5 * t5;
    real_type t9   = LM__[1];
    real_type t11  = 54 * t5 * t9;
    real_type t13  = LM__[0];
    real_type t14  = 48 * t13;
    real_type t19  = 1.0 / (81 * t6 - 112);
    result__[ 0   ] = t19 * (81 * t6 * t3 + t11 - t14 - 112 * t3) * t1;
    real_type t21  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    result__[ 1   ] = t19 * (54 * t5 * t13 + 81 * t6 * t21 - t11 + t14 - 112 * t21 - 84 * t9) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DgDxlxlp_numRows() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DgDxlxlp_numCols() const
  { return 17; }

  integer
  ICLOCS_TwoLinkRobotArm::DgDxlxlp_nnz() const
  { return 14; }

  void
  ICLOCS_TwoLinkRobotArm::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 10  ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 12  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 16  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 10  ;
    iIndex[11] = 1   ; jIndex[11] = 12  ;
    iIndex[12] = 1   ; jIndex[12] = 13  ;
    iIndex[13] = 1   ; jIndex[13] = 16  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1(UM__[0], -1, 1);
    real_type t4   = XM__[2];
    real_type t5   = cos(t4);
    real_type t7   = sin(t4);
    real_type t10  = LM__[1];
    real_type t12  = 54 * t7 * t10;
    real_type t15  = t5 * t5;
    real_type t17  = 81 * t15 - 112;
    real_type t18  = 1.0 / t17;
    real_type t24  = 54 * t5 * t10;
    real_type t26  = LM__[0];
    real_type t27  = 48 * t26;
    real_type t28  = 81 * t15 * t3 + t24 - t27 - 112 * t3;
    real_type t30  = t17 * t17;
    real_type t33  = t7 * t5 / t30;
    result__[ 0   ] = 0.5e0 * t18 * (-162 * t7 * t5 * t3 - t12) * t1 + 0.810e2 * t33 * t28 * t1;
    result__[ 1   ] = -0.240e2 * t18 * t1;
    result__[ 2   ] = 0.270e2 * t18 * t5 * t1;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = t18 * t28;
    real_type t41  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    real_type t57  = 81 * t15 * t41 + 54 * t5 * t26 - 84 * t10 - t24 + t27 - 112 * t41;
    result__[ 7   ] = 0.5e0 * t18 * (-162 * t7 * t5 * t41 - 54 * t7 * t26 + t12) * t1 + 0.810e2 * t33 * t57 * t1;
    real_type t61  = 54 * t5;
    result__[ 8   ] = 0.5e0 * t18 * (t61 + 48) * t1;
    result__[ 9   ] = 0.5e0 * t18 * (-t61 - 84) * t1;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = t18 * t57;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 14, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DgDu_numRows() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DgDu_numCols() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DgDu_nnz() const
  { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1_1(UM__[0], -1, 1);
    real_type t5   = cos(XM__[2]);
    real_type t6   = t5 * t5;
    real_type t14  = 1.0 / (81 * t6 - 112);
    result__[ 0   ] = t14 * (81 * t6 * t3 - 112 * t3) * t1;
    real_type t16  = ALIAS_u2Control_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = t14 * (81 * t6 * t16 - 112 * t16) * t1;
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
  ICLOCS_TwoLinkRobotArm::u_eval_analytic(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[1];
    real_type t3   = cos(XM__[2]);
    real_type t6   = LM__[0];
    real_type t7   = 48 * t6;
    real_type t9   = t3 * t3;
    real_type t12  = 1.0 / (81 * t9 - 112);
    U__[ iU_u1 ] = u1Control.solve(t12 * (-54 * t3 * t1 + t7), -1, 1);
    U__[ iU_u2 ] = u2Control.solve(t12 * (t3 * (-54 * t6 + 54 * t1) - t7 + 84 * t1), -1, 1);
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
  ICLOCS_TwoLinkRobotArm::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_1_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_1_1 = 0.0e0;
    real_type t1   = LM__[1];
    real_type t2   = XM__[2];
    real_type t3   = cos(t2);
    real_type t6   = LM__[0];
    real_type t7   = 48 * t6;
    real_type t8   = -54 * t3 * t1 + t7;
    real_type t9   = t3 * t3;
    real_type t11  = 81 * t9 - 112;
    real_type t12  = 1.0 / t11;
    real_type t14  = u1Control.solve_rhs(t12 * t8, -1, 1);
    real_type t15  = sin(t2);
    real_type t19  = t11 * t11;
    real_type t20  = 1.0 / t19;
    real_type t22  = t15 * t3;
    real_type tmp_0_2 = 0.5e0 * (54 * t12 * t15 * t1 + 162 * t22 * t20 * t8) * t14;
    real_type t28  = -54 * t6 + 54 * t1;
    real_type t31  = t3 * t28 + 84 * t1 - t7;
    real_type t33  = u2Control.solve_rhs(t12 * t31, -1, 1);
    real_type tmp_1_2 = 0.5e0 * (-t12 * t15 * t28 + 162 * t22 * t20 * t31) * t33;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_1_3 = 0.0e0;
    real_type tmp_0_4 = 0.240e2 * t12 * t14;
    real_type t42  = 54 * t3;
    real_type tmp_1_4 = 0.5e0 * t12 * (-t42 - 48) * t33;
    real_type tmp_0_5 = -0.270e2 * t12 * t3 * t14;
    real_type tmp_1_5 = 0.5e0 * t12 * (t42 + 84) * t33;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_1_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_1_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_1_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_1_9 = 0.0e0;
    real_type tmp_0_10 = tmp_0_2;
    real_type tmp_1_10 = tmp_1_2;
    real_type tmp_0_11 = 0.0e0;
    real_type tmp_1_11 = 0.0e0;
    real_type tmp_0_12 = tmp_0_4;
    real_type tmp_1_12 = tmp_1_4;
    real_type tmp_0_13 = tmp_0_5;
    real_type tmp_1_13 = tmp_1_5;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_1_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_1_15 = 0.0e0;
    real_type tmp_0_16 = 0.0e0;
    real_type tmp_1_16 = 0.0e0;
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
  ICLOCS_TwoLinkRobotArm::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u1];
    real_type t3   = u1Control(t2, -1, 1);
    real_type t5   = U__[iU_u2];
    real_type t6   = u2Control(t5, -1, 1);
    real_type t9   = X__[iX_theta];
    real_type t10  = sin(t9);
    real_type t11  = cos(t9);
    real_type t12  = X__[iX_omega__alpha];
    real_type t13  = t12 * t12;
    real_type t16  = X__[iX_omega__beta];
    real_type t17  = t16 * t16;
    real_type t27  = t10 * t10;
    real_type t30  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t27);
    real_type t33  = pow(V__[0] - t30 * ((9.0 / 4.0 * t13 * t11 + 2 * t17) * t10 + 4.0 / 3.0 * t2 - 4.0 / 3.0 * t5 - 3.0 / 2.0 * t5 * t11) * t1, 2);
    real_type t48  = pow(V__[1] + t30 * ((9.0 / 4.0 * t17 * t11 + 7.0 / 2.0 * t13) * t10 - 7.0 / 3.0 * t5 + 3.0 / 2.0 * (t2 - t5) * t11) * t1, 2);
    real_type t53  = pow(V__[2] - (t12 - t16) * t1, 2);
    real_type t57  = pow(-t12 * t1 + V__[3], 2);
    real_type result__ = t3 * t1 + t6 * t1 + t33 + t48 + t53 + t57;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DmDu_numEqns() const
  { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u1];
    real_type t3   = ALIAS_u1Control_D_1(t2, -1, 1);
    real_type t6   = X__[iX_theta];
    real_type t7   = sin(t6);
    real_type t8   = cos(t6);
    real_type t10  = X__[iX_omega__alpha] * X__[iX_omega__alpha];
    real_type t14  = X__[iX_omega__beta] * X__[iX_omega__beta];
    real_type t19  = U__[iU_u2];
    real_type t25  = t7 * t7;
    real_type t28  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t25);
    real_type t31  = t1 * (V__[0] - t28 * ((9.0 / 4.0 * t10 * t8 + 2 * t14) * t7 + 4.0 / 3.0 * t2 - 4.0 / 3.0 * t19 - 3.0 / 2.0 * t19 * t8) * t1);
    real_type t48  = t1 * (V__[1] + t28 * ((9.0 / 4.0 * t14 * t8 + 7.0 / 2.0 * t10) * t7 - 7.0 / 3.0 * t19 + 3.0 / 2.0 * (t2 - t19) * t8) * t1);
    result__[ 0   ] = t3 * t1 - 8.0 / 3.0 * t28 * t31 + 3 * t28 * t8 * t48;
    real_type t52  = ALIAS_u2Control_D_1(t19, -1, 1);
    real_type t54  = 3.0 / 2.0 * t8;
    result__[ 1   ] = t52 * t1 - 2 * t28 * (-4.0 / 3.0 - t54) * t31 + 2 * t28 * (-7.0 / 3.0 - t54) * t48;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DmDuu_numRows() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DmDuu_numCols() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DmDuu_nnz() const
  { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    real_type t5   = t1 * t1;
    real_type t6   = X__[iX_theta];
    real_type t7   = sin(t6);
    real_type t8   = t7 * t7;
    real_type t11  = pow(0.31e2 / 0.36e2 + 9.0 / 4.0 * t8, 2);
    real_type t12  = 1.0 / t11;
    real_type t15  = cos(t6);
    real_type t16  = t15 * t15;
    result__[ 0   ] = t3 * t1 + 0.32e2 / 9.0 * t12 * t5 + 9.0 / 2.0 * t12 * t16 * t5;
    real_type t20  = 3.0 / 2.0 * t15;
    real_type t21  = -4.0 / 3.0 - t20;
    real_type t25  = -7.0 / 3.0 - t20;
    result__[ 1   ] = 8.0 / 3.0 * t12 * t21 * t5 + 3 * t15 * t12 * t25 * t5;
    result__[ 2   ] = result__[1];
    real_type t31  = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    real_type t33  = t21 * t21;
    real_type t37  = t25 * t25;
    result__[ 3   ] = 2 * t12 * t33 * t5 + 2 * t12 * t37 * t5 + t31 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_controls.cc
