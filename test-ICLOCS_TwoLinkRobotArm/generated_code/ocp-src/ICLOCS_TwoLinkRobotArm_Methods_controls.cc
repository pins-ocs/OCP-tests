/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_controls.cc                     |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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

  real_type
  ICLOCS_TwoLinkRobotArm::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
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
    real_type t2   = P__[iP_T];
    real_type t4   = UM__[0];
    real_type t5   = t4 * t4;
    real_type t6   = UM__[1];
    real_type t7   = t6 * t6;
    real_type t12  = XM__[2];
    real_type t13  = sin(t12);
    real_type t14  = cos(t12);
    real_type t15  = t14 * t13;
    real_type t16  = XM__[0];
    real_type t17  = t16 * t16;
    real_type t20  = XM__[1];
    real_type t21  = t20 * t20;
    real_type t28  = t13 * t13;
    real_type t31  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t28);
    real_type t53  = u1Control(t4, -1, 1);
    real_type t55  = u2Control(t6, -1, 1);
    real_type result__ = (t5 + t7) * t2 * ModelPars[iM_rho] + t31 * (9.0 / 4.0 * t17 * t15 + 2 * t21 + 4.0 / 3.0 * t4 - 4.0 / 3.0 * t6 - 3.0 / 2.0 * t6 * t14) * t2 * LM__[0] - t31 * (9.0 / 4.0 * t21 * t15 + 7.0 / 2.0 * t17 - 7.0 / 3.0 * t6 + 3.0 / 2.0 * (t4 - t6) * t14) * t2 * LM__[1] + (t20 - t16) * t2 * LM__[2] + t16 * t2 * LM__[3] + t53 * t2 + t55 * t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::g_numEqns() const { return 2; }

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
    real_type t3   = cos(XM__[2]);
    real_type t4   = t3 * t3;
    real_type t5   = UM__[0];
    real_type t7   = ModelPars[iM_rho];
    real_type t10  = ALIAS_u1Control_D_1(t5, -1, 1);
    real_type t13  = LM__[1];
    real_type t15  = 54 * t3 * t13;
    real_type t18  = LM__[0];
    real_type t19  = 48 * t18;
    real_type t25  = 1.0 / (81 * t4 - 112);
    result__[ 0   ] = t25 * (162 * t7 * t5 * t4 + 81 * t10 * t4 - 224 * t5 * t7 - 112 * t10 + t15 - t19) * t1;
    real_type t26  = UM__[1];
    real_type t30  = ALIAS_u2Control_D_1(t26, -1, 1);
    result__[ 1   ] = -t25 * (-162 * t7 * t26 * t4 - 54 * t3 * t18 + 224 * t26 * t7 - 81 * t30 * t4 + 84 * t13 + t15 - t19 + 112 * t30) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DgDxlxlp_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DgDxlxlp_numCols() const { return 17; }
  integer ICLOCS_TwoLinkRobotArm::DgDxlxlp_nnz()     const { return 14; }

  void
  ICLOCS_TwoLinkRobotArm::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
    real_type t2   = XM__[2];
    real_type t3   = cos(t2);
    real_type t4   = UM__[0];
    real_type t6   = ModelPars[iM_rho];
    real_type t7   = sin(t2);
    real_type t8   = t7 * t6;
    real_type t11  = ALIAS_u1Control_D_1(t4, -1, 1);
    real_type t15  = LM__[1];
    real_type t17  = 54 * t7 * t15;
    real_type t20  = t3 * t3;
    real_type t22  = 81 * t20 - 112;
    real_type t23  = 1.0 / t22;
    real_type t32  = 54 * t3 * t15;
    real_type t35  = LM__[0];
    real_type t36  = 48 * t35;
    real_type t38  = 162 * t20 * t4 * t6 + 81 * t11 * t20 - 224 * t4 * t6 - 112 * t11 + t32 - t36;
    real_type t40  = t22 * t22;
    real_type t43  = t7 * t3 / t40;
    result__[ 0   ] = 0.5e0 * t23 * (-162 * t11 * t3 * t7 - 324 * t3 * t4 * t8 - t17) * t1 + 0.810e2 * t43 * t38 * t1;
    result__[ 1   ] = -0.240e2 * t23 * t1;
    result__[ 2   ] = 0.270e2 * t23 * t3 * t1;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = t23 * t38;
    real_type t50  = UM__[1];
    real_type t54  = ALIAS_u2Control_D_1(t50, -1, 1);
    real_type t75  = -162 * t20 * t50 * t6 - 81 * t20 * t54 - 54 * t3 * t35 + 224 * t50 * t6 + 84 * t15 + t32 - t36 + 112 * t54;
    result__[ 7   ] = -0.5e0 * t23 * (324 * t3 * t50 * t8 + 162 * t3 * t54 * t7 + 54 * t35 * t7 - t17) * t1 - 0.810e2 * t43 * t75 * t1;
    real_type t79  = 54 * t3;
    result__[ 8   ] = -0.5e0 * t23 * (-t79 - 48) * t1;
    result__[ 9   ] = -0.5e0 * t23 * (t79 + 84) * t1;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = -t23 * t75;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 14, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DgDu_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DgDu_numCols() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DgDu_nnz()     const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    real_type t3   = cos(XM__[2]);
    real_type t4   = t3 * t3;
    real_type t5   = ModelPars[iM_rho];
    real_type t7   = 162 * t5 * t4;
    real_type t9   = ALIAS_u1Control_D_1_1(UM__[0], -1, 1);
    real_type t12  = 224 * t5;
    real_type t18  = 1.0 / (81 * t4 - 112);
    result__[ 0   ] = t18 * (81 * t9 * t4 - t12 + t7 - 112 * t9) * t1;
    real_type t20  = ALIAS_u2Control_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = -t18 * (-81 * t20 * t4 + t12 + 112 * t20 - t7) * t1;
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
    UTILS_ERROR(
      "ICLOCS_TwoLinkRobotArm::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
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
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_1_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_1_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_1_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type tmp_1_5 = 0.0e0;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_1_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_1_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_1_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_1_9 = 0.0e0;
    real_type tmp_0_10 = 0.0e0;
    real_type tmp_1_10 = 0.0e0;
    real_type tmp_0_11 = 0.0e0;
    real_type tmp_1_11 = 0.0e0;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_1_12 = 0.0e0;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_1_13 = 0.0e0;
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
    real_type t12  = t11 * t10;
    real_type t13  = X__[iX_omega__alpha];
    real_type t14  = t13 * t13;
    real_type t17  = X__[iX_omega__beta];
    real_type t18  = t17 * t17;
    real_type t26  = t10 * t10;
    real_type t29  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t26);
    real_type t32  = pow(V__[0] - t29 * (9.0 / 4.0 * t14 * t12 + 2 * t18 + 4.0 / 3.0 * t2 - 4.0 / 3.0 * t5 - 3.0 / 2.0 * t5 * t11) * t1, 2);
    real_type t45  = pow(V__[1] + t29 * (9.0 / 4.0 * t18 * t12 + 7.0 / 2.0 * t14 - 7.0 / 3.0 * t5 + 3.0 / 2.0 * (t2 - t5) * t11) * t1, 2);
    real_type t50  = pow(V__[2] - (t17 - t13) * t1, 2);
    real_type t54  = pow(-t13 * t1 + V__[3], 2);
    real_type result__ = t3 * t1 + t6 * t1 + t32 + t45 + t50 + t54;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::DmDu_numEqns() const { return 2; }

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
    real_type t9   = t8 * t7;
    real_type t11  = X__[iX_omega__alpha] * X__[iX_omega__alpha];
    real_type t15  = X__[iX_omega__beta] * X__[iX_omega__beta];
    real_type t18  = U__[iU_u2];
    real_type t24  = t7 * t7;
    real_type t27  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t24);
    real_type t30  = t1 * (V__[0] - t27 * (9.0 / 4.0 * t11 * t9 + 2 * t15 + 4.0 / 3.0 * t2 - 4.0 / 3.0 * t18 - 3.0 / 2.0 * t18 * t8) * t1);
    real_type t45  = t1 * (V__[1] + t27 * (9.0 / 4.0 * t15 * t9 + 7.0 / 2.0 * t11 - 7.0 / 3.0 * t18 + 3.0 / 2.0 * (t2 - t18) * t8) * t1);
    result__[ 0   ] = t3 * t1 - 8.0 / 3.0 * t27 * t30 + 3 * t27 * t8 * t45;
    real_type t49  = ALIAS_u2Control_D_1(t18, -1, 1);
    real_type t51  = 3.0 / 2.0 * t8;
    result__[ 1   ] = t49 * t1 - 2 * t27 * (-4.0 / 3.0 - t51) * t30 + 2 * t27 * (-7.0 / 3.0 - t51) * t45;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DmDuu_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DmDuu_numCols() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DmDuu_nnz()     const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


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
