/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_controls.cc                     |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
#pragma warning( disable : 4189 )
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
    real_type t12  = t2 * LM__[0];
    real_type t13  = XL__[iX_theta];
    real_type t14  = sin(t13);
    real_type t15  = cos(t13);
    real_type t16  = t15 * t14;
    real_type t17  = XL__[iX_omega__alpha];
    real_type t18  = t17 * t17;
    real_type t21  = XL__[iX_omega__beta];
    real_type t22  = t21 * t21;
    real_type t24  = 4.0 / 3.0 * t4;
    real_type t25  = 4.0 / 3.0 * t6;
    real_type t29  = t14 * t14;
    real_type t32  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t29);
    real_type t36  = t2 * LM__[1];
    real_type t40  = 7.0 / 3.0 * t6;
    real_type t41  = t4 - t6;
    real_type t48  = t2 * LM__[2];
    real_type t52  = t2 * LM__[3];
    real_type t54  = u1Control(t4, -1, 1);
    real_type t57  = u2Control(t6, -1, 1);
    real_type t60  = XR__[iX_theta];
    real_type t61  = sin(t60);
    real_type t62  = cos(t60);
    real_type t63  = t62 * t61;
    real_type t64  = XR__[iX_omega__alpha];
    real_type t65  = t64 * t64;
    real_type t68  = XR__[iX_omega__beta];
    real_type t69  = t68 * t68;
    real_type t74  = t61 * t61;
    real_type t77  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t74);
    real_type result__ = 2 * (t5 + t7) * t2 * ModelPars[iM_rho] + t32 * (9.0 / 4.0 * t18 * t16 + 2 * t22 + t24 - t25 - 3.0 / 2.0 * t6 * t15) * t12 - t32 * (9.0 / 4.0 * t22 * t16 + 7.0 / 2.0 * t18 - t40 + 3.0 / 2.0 * t41 * t15) * t36 + (t21 - t17) * t48 + t17 * t52 + 2 * t54 * t2 + 2 * t57 * t2 + t77 * (9.0 / 4.0 * t65 * t63 + 2 * t69 + t24 - t25 - 3.0 / 2.0 * t6 * t62) * t12 - t77 * (9.0 / 4.0 * t69 * t63 + 7.0 / 2.0 * t65 - t40 + 3.0 / 2.0 * t41 * t62) * t36 + (t68 - t64) * t48 + t64 * t52;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
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
    real_type t3   = cos(XL__[iX_theta]);
    real_type t4   = t3 * t3;
    real_type t5   = UM__[0];
    real_type t7   = ModelPars[iM_rho];
    real_type t10  = ALIAS_u1Control_D_1(t5, -1, 1);
    real_type t13  = LM__[1];
    real_type t15  = 54 * t3 * t13;
    real_type t17  = 224 * t5 * t7;
    real_type t18  = LM__[0];
    real_type t19  = 48 * t18;
    real_type t20  = 112 * t10;
    real_type t25  = 1.0 / (81 * t4 - 112);
    real_type t28  = cos(XR__[iX_theta]);
    real_type t29  = t28 * t28;
    real_type t36  = 54 * t28 * t13;
    real_type t41  = 1.0 / (81 * t29 - 112);
    result__[ 0   ] = t25 * (162 * t7 * t5 * t4 + 81 * t10 * t4 + t15 - t17 - t19 - t20) * t1 + t41 * (162 * t7 * t5 * t29 + 81 * t10 * t29 - t17 - t19 - t20 + t36) * t1;
    real_type t43  = UM__[1];
    real_type t47  = ALIAS_u2Control_D_1(t43, -1, 1);
    real_type t53  = 224 * t43 * t7;
    real_type t54  = 84 * t13;
    real_type t55  = 112 * t47;
    result__[ 1   ] = -t25 * (-162 * t7 * t43 * t4 - 54 * t3 * t18 - 81 * t47 * t4 + t15 - t19 + t53 + t54 + t55) * t1 - t41 * (-162 * t7 * t43 * t29 - 54 * t28 * t18 - 81 * t47 * t29 - t19 + t36 + t53 + t54 + t55) * t1;
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
    real_type t2   = XL__[iX_theta];
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
    real_type t31  = 54 * t3 * t15;
    real_type t33  = 224 * t4 * t6;
    real_type t34  = LM__[0];
    real_type t35  = 48 * t34;
    real_type t36  = 112 * t11;
    real_type t37  = 162 * t6 * t4 * t20 + 81 * t11 * t20 + t31 - t33 - t35 - t36;
    real_type t39  = t22 * t22;
    real_type t42  = t7 * t3 / t39;
    result__[ 0   ] = t23 * (-162 * t7 * t11 * t3 - 324 * t8 * t4 * t3 - t17) * t1 + 162 * t42 * t37 * t1;
    real_type t47  = XR__[iX_theta];
    real_type t48  = cos(t47);
    real_type t49  = t48 * t48;
    real_type t51  = 81 * t49 - 112;
    real_type t52  = 1.0 / t51;
    result__[ 1   ] = -0.240e2 * t23 * t1 - 0.240e2 * t52 * t1;
    result__[ 2   ] = 0.270e2 * t23 * t3 * t1 + 0.270e2 * t52 * t48 * t1;
    real_type t62  = sin(t47);
    real_type t63  = t62 * t6;
    real_type t70  = 54 * t62 * t15;
    real_type t80  = 54 * t48 * t15;
    real_type t81  = 162 * t6 * t4 * t49 + 81 * t11 * t49 - t33 - t35 - t36 + t80;
    real_type t83  = t51 * t51;
    real_type t86  = t62 * t48 / t83;
    result__[ 3   ] = t52 * (-162 * t62 * t11 * t48 - 324 * t63 * t4 * t48 - t70) * t1 + 162 * t86 * t81 * t1;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = t23 * t37 + t52 * t81;
    real_type t91  = UM__[1];
    real_type t95  = ALIAS_u2Control_D_1(t91, -1, 1);
    real_type t112 = 224 * t91 * t6;
    real_type t113 = 84 * t15;
    real_type t114 = 112 * t95;
    real_type t115 = -162 * t6 * t91 * t20 - 81 * t95 * t20 - 54 * t3 * t34 + t112 + t113 + t114 + t31 - t35;
    result__[ 7   ] = -t23 * (162 * t7 * t95 * t3 + 324 * t8 * t91 * t3 + 54 * t7 * t34 - t17) * t1 - 162 * t42 * t115 * t1;
    real_type t119 = 54 * t3;
    real_type t124 = 54 * t48;
    result__[ 8   ] = -0.5e0 * t23 * (-t119 - 48) * t1 - 0.5e0 * t52 * (-t124 - 48) * t1;
    result__[ 9   ] = -0.5e0 * t23 * (t119 + 84) * t1 - 0.5e0 * t52 * (t124 + 84) * t1;
    real_type t155 = -162 * t6 * t91 * t49 - 54 * t48 * t34 - 81 * t95 * t49 + t112 + t113 + t114 - t35 + t80;
    result__[ 10  ] = -t52 * (162 * t62 * t95 * t48 + 324 * t63 * t91 * t48 + 54 * t62 * t34 - t70) * t1 - 162 * t86 * t155 * t1;
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = -t23 * t115 - t52 * t155;
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
    real_type t3   = cos(XL__[iX_theta]);
    real_type t4   = t3 * t3;
    real_type t5   = ModelPars[iM_rho];
    real_type t7   = 162 * t5 * t4;
    real_type t9   = ALIAS_u1Control_D_1_1(UM__[0], -1, 1);
    real_type t12  = 224 * t5;
    real_type t13  = 112 * t9;
    real_type t18  = 1.0 / (81 * t4 - 112);
    real_type t21  = cos(XR__[iX_theta]);
    real_type t22  = t21 * t21;
    real_type t24  = 162 * t5 * t22;
    real_type t31  = 1.0 / (81 * t22 - 112);
    result__[ 0   ] = t18 * (81 * t9 * t4 - t12 - t13 + t7) * t1 + t31 * (81 * t9 * t22 - t12 - t13 + t24) * t1;
    real_type t34  = ALIAS_u2Control_D_1_1(UM__[1], -1, 1);
    real_type t37  = 112 * t34;
    result__[ 1   ] = -t18 * (-81 * t34 * t4 + t12 + t37 - t7) * t1 - t31 * (-81 * t34 * t22 + t12 - t24 + t37) * t1;
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
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
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
