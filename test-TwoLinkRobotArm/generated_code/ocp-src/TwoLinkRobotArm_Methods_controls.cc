/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods_controls.cc                            |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t1   = LM__[1];
    real_type t2   = P__[iP_T];
    real_type t5   = cos(XM__[2]);
    real_type t8   = t5 * t5;
    real_type t10  = ALIAS_u1Control_D_1(UM__[0], -1, 1);
    real_type t13  = LM__[0];
    real_type t19  = 81 * t8 - 112;
    real_type t20  = 1.0 / t19;
    result__[ 0   ] = t20 * (54 * t5 * t2 * t1 + 81 * t10 * t8 - 48 * t2 * t13 - 112 * t10);
    real_type t22  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    result__[ 1   ] = t20 * (t22 * t19 + 54 * t2 * (t5 * (t13 - t1) + 8.0 / 9.0 * t13 - 0.14e2 / 9.0 * t1));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DgDxlxlp_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDxlxlp_numCols() const
  { return 17; }

  integer
  TwoLinkRobotArm::DgDxlxlp_nnz() const
  { return 14; }

  void
  TwoLinkRobotArm::DgDxlxlp_pattern(
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
  TwoLinkRobotArm::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t1   = LM__[1];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = XM__[2];
    real_type t5   = sin(t4);
    real_type t8   = cos(t4);
    real_type t10  = ALIAS_u1Control_D_1(UM__[0], -1, 1);
    real_type t15  = t8 * t8;
    real_type t17  = 81 * t15 - 112;
    real_type t18  = 1.0 / t17;
    real_type t25  = LM__[0];
    real_type t30  = t17 * t17;
    real_type t31  = 1.0 / t30;
    real_type t33  = t5 * t8;
    result__[ 0   ] = 0.5e0 * t18 * (-162 * t5 * t10 * t8 - 54 * t5 * t3) + 0.810e2 * t33 * t31 * (81 * t10 * t15 - 48 * t2 * t25 + 54 * t8 * t3 - 112 * t10);
    result__[ 1   ] = -0.240e2 * t18 * t2;
    result__[ 2   ] = 0.270e2 * t18 * t8 * t2;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t42  = 48 * t25;
    result__[ 6   ] = t18 * (54 * t1 * t8 - t42);
    real_type t45  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    real_type t48  = t25 - t1;
    real_type t56  = t8 * t48;
    result__[ 7   ] = 0.5e0 * t18 * (-54 * t2 * t5 * t48 - 162 * t45 * t33) + 0.810e2 * t33 * t31 * (t45 * t17 + 54 * t2 * (t56 + 8.0 / 9.0 * t25 - 0.14e2 / 9.0 * t1));
    result__[ 8   ] = 0.270e2 * t18 * t2 * (t8 + 8.0 / 9.0);
    result__[ 9   ] = 0.270e2 * t18 * t2 * (-t8 - 0.14e2 / 9.0);
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = t18 * (54 * t56 + t42 - 84 * t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 14, i_segment );
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
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t2   = cos(XM__[2]);
    real_type t3   = t2 * t2;
    real_type t5   = ALIAS_u1Control_D_1_1(UM__[0], -1, 1);
    result__[ 0   ] = 1.0 / (81 * t3 - 112) * (81 * t5 * t3 - 112 * t5);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(UM__[1], -1, 1);
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
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t1   = P__[iP_T];
    real_type t3   = cos(XM__[2]);
    real_type t4   = LM__[1];
    real_type t7   = LM__[0];
    real_type t11  = t3 * t3;
    real_type t14  = 1.0 / (81 * t11 - 112);
    U__[ iU_u1 ] = u1Control.solve(-6 * t14 * (9 * t4 * t3 - 8 * t7) * t1, -1, 1);
    U__[ iU_u2 ] = u2Control.solve(-54 * t14 * t1 * (t3 * (t7 - t4) + 8.0 / 9.0 * t7 - 0.14e2 / 9.0 * t4), -1, 1);
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
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
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
    real_type t1   = P__[iP_T];
    real_type t2   = XM__[2];
    real_type t3   = cos(t2);
    real_type t4   = LM__[1];
    real_type t7   = LM__[0];
    real_type t9   = 9 * t4 * t3 - 8 * t7;
    real_type t10  = t9 * t1;
    real_type t11  = t3 * t3;
    real_type t13  = 81 * t11 - 112;
    real_type t14  = 1.0 / t13;
    real_type t17  = u1Control.solve_rhs(-6 * t14 * t10, -1, 1);
    real_type t18  = sin(t2);
    real_type t23  = t13 * t13;
    real_type t26  = t18 * t3 / t23;
    real_type tmp_0_2 = 0.5e0 * (54 * t14 * t4 * t18 * t1 - 972 * t26 * t10) * t17;
    real_type t31  = t7 - t4;
    real_type t35  = t3 * t31 + 8.0 / 9.0 * t7 - 0.14e2 / 9.0 * t4;
    real_type t36  = t1 * t35;
    real_type t39  = u2Control.solve_rhs(-54 * t14 * t36, -1, 1);
    real_type t41  = t14 * t1;
    real_type tmp_1_2 = 0.5e0 * (54 * t41 * t18 * t31 - 8748 * t26 * t36) * t39;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_1_3 = 0.0e0;
    real_type t48  = t1 * t17;
    real_type tmp_0_4 = 0.240e2 * t14 * t48;
    real_type tmp_1_4 = -0.270e2 * t41 * (t3 + 8.0 / 9.0) * t39;
    real_type tmp_0_5 = -0.270e2 * t14 * t3 * t48;
    real_type tmp_1_5 = -0.270e2 * t41 * (-t3 - 0.14e2 / 9.0) * t39;
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
    real_type tmp_0_16 = -6 * t14 * t9 * t17;
    real_type tmp_1_16 = -54 * t14 * t35 * t39;
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
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
    real_type t51  = pow(V__[2] - (t14 - t10) * t6, 2);
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
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = ALIAS_u1Control_D_1(t1, -1, 1);
    real_type t4   = P__[iP_T];
    real_type t5   = X__[iX_x3];
    real_type t6   = sin(t5);
    real_type t7   = cos(t5);
    real_type t9   = X__[iX_x1] * X__[iX_x1];
    real_type t13  = X__[iX_x2] * X__[iX_x2];
    real_type t18  = U__[iU_u2];
    real_type t24  = t6 * t6;
    real_type t27  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t24);
    real_type t30  = t4 * (V__[0] - t27 * ((9.0 / 4.0 * t9 * t7 + 2 * t13) * t6 + 4.0 / 3.0 * t1 - 4.0 / 3.0 * t18 - 3.0 / 2.0 * t18 * t7) * t4);
    real_type t47  = t4 * (V__[1] + t27 * ((7.0 / 2.0 * t9 + 9.0 / 4.0 * t13 * t7) * t6 - 7.0 / 3.0 * t18 + 3.0 / 2.0 * (t1 - t18) * t7) * t4);
    result__[ 0   ] = t2 - 8.0 / 3.0 * t27 * t30 + 3 * t27 * t7 * t47;
    real_type t51  = ALIAS_u2Control_D_1(t18, -1, 1);
    real_type t52  = 3.0 / 2.0 * t7;
    result__[ 1   ] = t51 - 2 * t27 * (-4.0 / 3.0 - t52) * t30 + 2 * t27 * (-7.0 / 3.0 - t52) * t47;
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
  TwoLinkRobotArm::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    real_type t4   = P__[iP_T] * P__[iP_T];
    real_type t5   = X__[iX_x3];
    real_type t6   = sin(t5);
    real_type t7   = t6 * t6;
    real_type t10  = pow(0.31e2 / 0.36e2 + 9.0 / 4.0 * t7, 2);
    real_type t11  = 1.0 / t10;
    real_type t14  = cos(t5);
    real_type t15  = t14 * t14;
    result__[ 0   ] = t2 + 0.32e2 / 9.0 * t11 * t4 + 9.0 / 2.0 * t11 * t15 * t4;
    real_type t19  = 3.0 / 2.0 * t14;
    real_type t20  = -4.0 / 3.0 - t19;
    real_type t24  = -7.0 / 3.0 - t19;
    result__[ 1   ] = 8.0 / 3.0 * t11 * t20 * t4 + 3 * t14 * t11 * t24 * t4;
    result__[ 2   ] = result__[1];
    real_type t30  = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    real_type t31  = t20 * t20;
    real_type t35  = t24 * t24;
    result__[ 3   ] = 2 * t11 * t31 * t4 + 2 * t11 * t35 * t4 + t30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: TwoLinkRobotArm_Methods_controls.cc
