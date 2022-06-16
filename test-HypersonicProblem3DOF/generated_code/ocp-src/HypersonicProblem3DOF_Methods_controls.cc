/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_controls.cc                      |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"

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
#define ALIAS_G_bound_max_DD(__t1) G_bound_max.DD( __t1)
#define ALIAS_G_bound_max_D(__t1) G_bound_max.D( __t1)
#define ALIAS_G_bound_min_DD(__t1) G_bound_min.DD( __t1)
#define ALIAS_G_bound_min_D(__t1) G_bound_min.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)


namespace HypersonicProblem3DOFDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  HypersonicProblem3DOF::g_fun_eval(
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
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = UM__[0];
    real_type t3   = t2 * t2;
    real_type t5   = XM__[4];
    real_type t7   = cos(t5 / 2);
    real_type t8   = log(t7);
    real_type t10  = UM__[2];
    real_type t11  = t10 * t10;
    real_type t12  = UM__[3];
    real_type t13  = t12 * t12;
    real_type t14  = UM__[4];
    real_type t15  = t14 * t14;
    real_type t16  = UM__[5];
    real_type t17  = t16 * t16;
    real_type t18  = UM__[6];
    real_type t19  = t18 * t18;
    real_type t20  = UM__[7];
    real_type t21  = t20 * t20;
    real_type t22  = UM__[8];
    real_type t23  = t22 * t22;
    real_type t28  = ModelPars[iM_ODE];
    real_type t29  = XM__[3];
    real_type t30  = t29 * t28;
    real_type t31  = sin(t5);
    real_type t33  = ModelPars[iM_CTRL];
    real_type t39  = cos(t5);
    real_type t41  = XM__[5];
    real_type t42  = cos(t41);
    real_type t44  = XM__[0];
    real_type t45  = ModelPars[iM_re] + t44;
    real_type t46  = 1.0 / t45;
    real_type t48  = XM__[2];
    real_type t49  = cos(t48);
    real_type t58  = sin(t41);
    real_type t67  = ModelPars[iM_mu];
    real_type t69  = t45 * t45;
    real_type t70  = 1.0 / t69;
    real_type t76  = exp(-1.0 / ModelPars[iM_S] * t44);
    real_type t77  = t76 * ModelPars[iM_rho0];
    real_type t78  = t29 * t29;
    real_type t86  = ModelPars[iM_Aref];
    real_type t89  = 1.0 / ModelPars[iM_m];
    real_type t104 = t2 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t106 = XM__[6];
    real_type t107 = cos(t106);
    real_type t112 = t46 * t29;
    real_type t128 = sin(t106);
    real_type t135 = tan(t48);
    real_type t145 = UM__[1];
    real_type t152 = u2Control(t145, -1, 1);
    real_type t155 = G_bound_min(-0.314159265358979323846264338328e1 - t5);
    real_type t158 = G_bound_max(t5 - 0.314159265358979323846264338328e1);
    real_type result__ = t3 * t1 - t8 * t1 + (t11 + t13 + t15 + t17 + t19 + t21 + t23) * t1 + (t10 * t33 + t31 * t30) * t1 * LM__[0] + (1.0 / t49 * t46 * t42 * t39 * t30 + t12 * t33) * t1 * LM__[1] + (t46 * t58 * t39 * t30 + t14 * t33) * t1 * LM__[2] + ((-t70 * t67 * t31 - t89 * t86 * (t2 * ModelPars[iM_CD1] + t3 * ModelPars[iM_CD2] + ModelPars[iM_CD0]) * t78 * t77 / 2) * t28 + t16 * t33) * t1 * LM__[3] + ((t107 * t89 * t86 * t104 * t29 * t77 / 2 + t39 * (t112 - 1.0 / t29 * t70 * t67)) * t28 + t18 * t33) * t1 * LM__[4] + ((1.0 / t39 * t128 * t89 * t86 * t104 * t29 * t77 / 2 - t135 * t42 * t39 * t112) * t28 + t20 * t33) * t1 * LM__[5] + (ModelPars[iM_sigma_dot_max] * t28 * t145 + t22 * t33) * t1 * LM__[6] + t152 * t1 + t155 * t1 + t158 * t1;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::g_numEqns() const { return 9; }

  void
  HypersonicProblem3DOF::g_eval(
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
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = ModelPars[iM_Aref];
    real_type t5   = XM__[3];
    real_type t6   = t5 * t5;
    real_type t8   = cos(XM__[4]);
    real_type t9   = t8 * t6;
    real_type t15  = exp(-XM__[0] / ModelPars[iM_S]);
    real_type t16  = UM__[0];
    real_type t18  = LM__[3];
    real_type t19  = ModelPars[iM_ODE];
    real_type t21  = ModelPars[iM_rho0];
    real_type t33  = LM__[4];
    real_type t35  = t15 * t21;
    real_type t38  = ModelPars[iM_CL1] * t5;
    real_type t39  = XM__[6];
    real_type t40  = cos(t39);
    real_type t45  = LM__[5];
    real_type t48  = sin(t39);
    real_type t52  = ModelPars[iM_m];
    result__[ 0   ] = -1.0 / t8 / t52 * (2 * t21 * t19 * t18 * t16 * t15 * t9 * ModelPars[iM_CD2] * t2 + t21 * t19 * t18 * t15 * t9 * ModelPars[iM_CD1] * t2 - t8 * t40 * t2 * t38 * t35 * t19 * t33 - t48 * t2 * t38 * t35 * t19 * t45 - 4 * t8 * t52 * t16) * t1 / 2;
    real_type t64  = t1 * LM__[6];
    real_type t69  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    result__[ 1   ] = ModelPars[iM_sigma_dot_max] * t19 * t64 + t69 * t1;
    real_type t73  = ModelPars[iM_CTRL];
    result__[ 2   ] = t73 * t1 * LM__[0] + 2 * UM__[2] * t1;
    result__[ 3   ] = t73 * t1 * LM__[1] + 2 * UM__[3] * t1;
    result__[ 4   ] = t73 * t1 * LM__[2] + 2 * UM__[4] * t1;
    result__[ 5   ] = t73 * t1 * t18 + 2 * UM__[5] * t1;
    result__[ 6   ] = t73 * t1 * t33 + 2 * UM__[6] * t1;
    result__[ 7   ] = t73 * t1 * t45 + 2 * UM__[7] * t1;
    result__[ 8   ] = 2 * UM__[8] * t1 + t73 * t64;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DgDxlxlp_numRows() const { return 9; }
  integer HypersonicProblem3DOF::DgDxlxlp_numCols() const { return 29; }
  integer HypersonicProblem3DOF::DgDxlxlp_nnz()     const { return 39; }

  void
  HypersonicProblem3DOF::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 14  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 17  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 18  ;
    iIndex[10] = 0   ; jIndex[10] = 20  ;
    iIndex[11] = 0   ; jIndex[11] = 24  ;
    iIndex[12] = 0   ; jIndex[12] = 25  ;
    iIndex[13] = 0   ; jIndex[13] = 26  ;
    iIndex[14] = 0   ; jIndex[14] = 28  ;
    iIndex[15] = 1   ; jIndex[15] = 13  ;
    iIndex[16] = 1   ; jIndex[16] = 27  ;
    iIndex[17] = 1   ; jIndex[17] = 28  ;
    iIndex[18] = 2   ; jIndex[18] = 7   ;
    iIndex[19] = 2   ; jIndex[19] = 21  ;
    iIndex[20] = 2   ; jIndex[20] = 28  ;
    iIndex[21] = 3   ; jIndex[21] = 8   ;
    iIndex[22] = 3   ; jIndex[22] = 22  ;
    iIndex[23] = 3   ; jIndex[23] = 28  ;
    iIndex[24] = 4   ; jIndex[24] = 9   ;
    iIndex[25] = 4   ; jIndex[25] = 23  ;
    iIndex[26] = 4   ; jIndex[26] = 28  ;
    iIndex[27] = 5   ; jIndex[27] = 10  ;
    iIndex[28] = 5   ; jIndex[28] = 24  ;
    iIndex[29] = 5   ; jIndex[29] = 28  ;
    iIndex[30] = 6   ; jIndex[30] = 11  ;
    iIndex[31] = 6   ; jIndex[31] = 25  ;
    iIndex[32] = 6   ; jIndex[32] = 28  ;
    iIndex[33] = 7   ; jIndex[33] = 12  ;
    iIndex[34] = 7   ; jIndex[34] = 26  ;
    iIndex[35] = 7   ; jIndex[35] = 28  ;
    iIndex[36] = 8   ; jIndex[36] = 13  ;
    iIndex[37] = 8   ; jIndex[37] = 27  ;
    iIndex[38] = 8   ; jIndex[38] = 28  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = ModelPars[iM_Aref];
    real_type t4   = ModelPars[iM_CD2] * t2;
    real_type t5   = XM__[3];
    real_type t6   = t5 * t5;
    real_type t7   = XM__[4];
    real_type t8   = cos(t7);
    real_type t9   = t8 * t6;
    real_type t11  = 1.0 / ModelPars[iM_S];
    real_type t16  = exp(-t11 * XM__[0]);
    real_type t17  = UM__[0];
    real_type t18  = t17 * t16;
    real_type t19  = LM__[3];
    real_type t20  = ModelPars[iM_ODE];
    real_type t22  = ModelPars[iM_rho0];
    real_type t23  = t22 * t20 * t19;
    real_type t24  = t23 * t18;
    real_type t28  = ModelPars[iM_CD1] * t2;
    real_type t29  = t9 * t28;
    real_type t33  = LM__[4];
    real_type t34  = t20 * t33;
    real_type t35  = t11 * t22;
    real_type t38  = ModelPars[iM_CL1];
    real_type t39  = t38 * t5;
    real_type t40  = XM__[6];
    real_type t41  = cos(t40);
    real_type t42  = t41 * t2;
    real_type t44  = t8 * t42 * t39;
    real_type t46  = LM__[5];
    real_type t47  = t20 * t46;
    real_type t50  = t2 * t38;
    real_type t51  = sin(t40);
    real_type t57  = ModelPars[iM_m];
    real_type t58  = 1.0 / t57;
    real_type t59  = 1.0 / t8;
    real_type t60  = t59 * t58;
    result__[ 0   ] = -0.2500000000e0 * t60 * (t51 * t50 * t5 * t16 * t35 * t47 - t23 * t16 * t11 * t29 - 2 * t24 * t11 * t9 * t4 + t44 * t16 * t35 * t34) * t1;
    real_type t63  = t8 * t5;
    real_type t69  = t22 * t20;
    real_type t70  = t69 * t19 * t16;
    real_type t73  = t16 * t22;
    real_type t74  = t73 * t34;
    real_type t80  = t51 * t2;
    result__[ 1   ] = -0.2500000000e0 * t60 * (-t80 * t38 * t16 * t22 * t47 - t8 * t41 * t50 * t74 + 4 * t24 * t63 * t4 + 2 * t70 * t63 * t28) * t1;
    real_type t87  = sin(t7);
    real_type t88  = t87 * t6;
    real_type t97  = t57 * t17;
    real_type t104 = t9 * t4;
    real_type t109 = t73 * t47;
    real_type t114 = -t80 * t39 * t109 + 2 * t24 * t104 + t70 * t29 - t44 * t74 - 4 * t8 * t97;
    real_type t116 = t8 * t8;
    result__[ 2   ] = -0.2500000000e0 * t60 * (t87 * t42 * t39 * t74 - 2 * t24 * t88 * t4 - t70 * t88 * t28 + 4 * t87 * t97) * t1 - 0.2500000000e0 * t87 / t116 * t58 * t114 * t1;
    result__[ 3   ] = -0.2500000000e0 * t60 * (t8 * t80 * t39 * t74 - t42 * t39 * t109) * t1;
    result__[ 4   ] = -0.2500000000e0 * t60 * (t69 * t16 * t8 * t6 * t28 + 2 * t69 * t18 * t104) * t1;
    real_type t142 = t20 * t1;
    result__[ 5   ] = 0.2500000000e0 * t58 * t42 * t39 * t73 * t142;
    result__[ 6   ] = 0.2500000000e0 * t59 * t58 * t51 * t50 * t5 * t73 * t142;
    result__[ 7   ] = result__[0];
    result__[ 8   ] = result__[1];
    result__[ 9   ] = result__[2];
    result__[ 10  ] = result__[3];
    result__[ 11  ] = result__[4];
    result__[ 12  ] = result__[5];
    result__[ 13  ] = result__[6];
    result__[ 14  ] = -t59 * t58 * t114 / 2;
    real_type t156 = ModelPars[iM_sigma_dot_max];
    result__[ 15  ] = 0.5e0 * t156 * t142;
    result__[ 16  ] = result__[15];
    real_type t158 = LM__[6];
    real_type t162 = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    result__[ 17  ] = t156 * t20 * t158 + t162;
    real_type t163 = ModelPars[iM_CTRL];
    result__[ 18  ] = 0.5e0 * t163 * t1;
    result__[ 19  ] = result__[18];
    result__[ 20  ] = t163 * LM__[0] + 2 * UM__[2];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = result__[21];
    result__[ 23  ] = t163 * LM__[1] + 2 * UM__[3];
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[24];
    result__[ 26  ] = t163 * LM__[2] + 2 * UM__[4];
    result__[ 27  ] = result__[25];
    result__[ 28  ] = result__[27];
    result__[ 29  ] = t163 * t19 + 2 * UM__[5];
    result__[ 30  ] = result__[28];
    result__[ 31  ] = result__[30];
    result__[ 32  ] = t163 * t33 + 2 * UM__[6];
    result__[ 33  ] = result__[31];
    result__[ 34  ] = result__[33];
    result__[ 35  ] = t163 * t46 + 2 * UM__[7];
    result__[ 36  ] = result__[34];
    result__[ 37  ] = result__[36];
    result__[ 38  ] = t163 * t158 + 2 * UM__[8];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 39, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DgDu_numRows() const { return 9; }
  integer HypersonicProblem3DOF::DgDu_numCols() const { return 9; }
  integer HypersonicProblem3DOF::DgDu_nnz()     const { return 9; }

  void
  HypersonicProblem3DOF::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 8   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::DgDu_sparse(
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
    real_type QM__[1], XM__[7], LM__[7];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t6   = XM__[3] * XM__[3];
    real_type t8   = cos(XM__[4]);
    real_type t15  = exp(-XM__[0] / ModelPars[iM_S]);
    real_type t24  = ModelPars[iM_m];
    result__[ 0   ] = -1.0 / t8 / t24 * (2 * ModelPars[iM_ODE] * ModelPars[iM_rho0] * LM__[3] * t15 * t8 * t6 * ModelPars[iM_Aref] * ModelPars[iM_CD2] - 4 * t8 * t24) * t1 / 2;
    real_type t35  = ALIAS_u2Control_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = t35 * t1;
    result__[ 2   ] = 2 * t1;
    result__[ 3   ] = result__[2];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = result__[4];
    result__[ 6   ] = result__[5];
    result__[ 7   ] = result__[6];
    result__[ 8   ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 9, i_segment );
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
  HypersonicProblem3DOF::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "HypersonicProblem3DOF::u_eval_analytic\n"
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
  HypersonicProblem3DOF::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = U__[iU_u2];
    real_type t3   = u2Control(t2, -1, 1);
    real_type t5   = X__[iX_G];
    real_type t7   = G_bound_min(-0.314159265358979323846264338328e1 - t5);
    real_type t10  = G_bound_max(t5 - 0.314159265358979323846264338328e1);
    real_type t13  = ModelPars[iM_ODE];
    real_type t14  = X__[iX_V];
    real_type t15  = t14 * t13;
    real_type t16  = sin(t5);
    real_type t18  = ModelPars[iM_CTRL];
    real_type t24  = pow(V__[0] - (t16 * t15 + U__[iU_c_h] * t18) * t1, 2);
    real_type t26  = cos(t5);
    real_type t28  = X__[iX_psi];
    real_type t29  = cos(t28);
    real_type t31  = X__[iX_h];
    real_type t32  = ModelPars[iM_re] + t31;
    real_type t33  = 1.0 / t32;
    real_type t35  = X__[iX_phi];
    real_type t36  = cos(t35);
    real_type t45  = pow(V__[1] - (1.0 / t36 * t33 * t29 * t26 * t15 + U__[iU_c_theta] * t18) * t1, 2);
    real_type t47  = sin(t28);
    real_type t56  = pow(V__[2] - (t33 * t47 * t26 * t15 + U__[iU_c_phi] * t18) * t1, 2);
    real_type t58  = ModelPars[iM_mu];
    real_type t60  = t32 * t32;
    real_type t61  = 1.0 / t60;
    real_type t67  = exp(-1.0 / ModelPars[iM_S] * t31);
    real_type t68  = t67 * ModelPars[iM_rho0];
    real_type t69  = t14 * t14;
    real_type t72  = U__[iU_alpha];
    real_type t73  = t72 * t72;
    real_type t79  = ModelPars[iM_Aref];
    real_type t82  = 1.0 / ModelPars[iM_m];
    real_type t93  = pow(V__[3] - ((-t61 * t58 * t16 - t82 * t79 * (t72 * ModelPars[iM_CD1] + t73 * ModelPars[iM_CD2] + ModelPars[iM_CD0]) * t69 * t68 / 2) * t13 + U__[iU_c_V] * t18) * t1, 2);
    real_type t99  = t72 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t101 = X__[iX_sigma];
    real_type t102 = cos(t101);
    real_type t107 = t14 * t33;
    real_type t120 = pow(V__[4] - ((t102 * t82 * t79 * t99 * t14 * t68 / 2 + t26 * (t107 - 1.0 / t14 * t61 * t58)) * t13 + U__[iU_c_G] * t18) * t1, 2);
    real_type t125 = sin(t101);
    real_type t132 = tan(t35);
    real_type t142 = pow(V__[5] - ((1.0 / t26 * t125 * t82 * t79 * t99 * t14 * t68 / 2 - t132 * t29 * t26 * t107) * t13 + U__[iU_c_psi] * t18) * t1, 2);
    real_type t152 = pow(V__[6] - (t2 * ModelPars[iM_sigma_dot_max] * t13 + U__[iU_c_sigma] * t18) * t1, 2);
    real_type result__ = t10 * t1 + t3 * t1 + t7 * t1 + t120 + t142 + t152 + t24 + t45 + t56 + t93;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::DmDu_numEqns() const { return 9; }

  void
  HypersonicProblem3DOF::DmDu_eval(
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
    real_type t2   = P__[iP_Tf];
    real_type t3   = ModelPars[iM_ODE];
    real_type t4   = X__[iX_G];
    real_type t5   = sin(t4);
    real_type t6   = ModelPars[iM_mu];
    real_type t9   = X__[iX_h];
    real_type t10  = ModelPars[iM_re] + t9;
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t14  = ModelPars[iM_rho0];
    real_type t18  = exp(-1.0 / ModelPars[iM_S] * t9);
    real_type t19  = t18 * t14;
    real_type t20  = X__[iX_V];
    real_type t21  = t20 * t20;
    real_type t23  = ModelPars[iM_CD2];
    real_type t24  = U__[iU_alpha];
    real_type t25  = t24 * t24;
    real_type t27  = ModelPars[iM_CD1];
    real_type t31  = ModelPars[iM_Aref];
    real_type t34  = 1.0 / ModelPars[iM_m];
    real_type t40  = ModelPars[iM_CTRL];
    real_type t46  = t2 * (V__[3] - ((-t12 * t6 * t5 - t34 * t31 * (t25 * t23 + t24 * t27 + ModelPars[iM_CD0]) * t21 * t19 / 2) * t3 + U__[iU_c_V] * t40) * t2);
    real_type t47  = t14 * t3;
    real_type t59  = ModelPars[iM_CL1];
    real_type t62  = t24 * t59 + ModelPars[iM_CL0];
    real_type t64  = X__[iX_sigma];
    real_type t65  = cos(t64);
    real_type t70  = 1.0 / t10;
    real_type t71  = t70 * t20;
    real_type t76  = cos(t4);
    real_type t85  = t2 * (V__[4] - ((t65 * t34 * t31 * t62 * t20 * t19 / 2 + t76 * (t71 - 1.0 / t20 * t12 * t6)) * t3 + U__[iU_c_G] * t40) * t2);
    real_type t86  = t18 * t47;
    real_type t88  = t59 * t20;
    real_type t89  = t34 * t31;
    real_type t96  = sin(t64);
    real_type t97  = 1.0 / t76;
    real_type t102 = X__[iX_psi];
    real_type t103 = cos(t102);
    real_type t105 = X__[iX_phi];
    real_type t106 = tan(t105);
    real_type t116 = t2 * (V__[5] - ((t97 * t96 * t89 * t62 * t20 * t19 / 2 - t106 * t103 * t76 * t71) * t3 + U__[iU_c_psi] * t40) * t2);
    result__[ 0   ] = t34 * t31 * (2 * t24 * t23 + t27) * t21 * t18 * t47 * t46 - t65 * t89 * t88 * t86 * t85 - t97 * t96 * t34 * t31 * t88 * t86 * t116;
    real_type t123 = U__[iU_u2];
    real_type t124 = ALIAS_u2Control_D_1(t123, -1, 1);
    real_type t128 = ModelPars[iM_sigma_dot_max] * t3;
    real_type t135 = t2 * (V__[6] - (t123 * t128 + U__[iU_c_sigma] * t40) * t2);
    result__[ 1   ] = t124 * t2 - 2 * t128 * t135;
    real_type t139 = t20 * t3;
    result__[ 2   ] = -2 * t40 * t2 * (V__[0] - (t5 * t139 + U__[iU_c_h] * t40) * t2);
    real_type t152 = cos(t105);
    result__[ 3   ] = -2 * t40 * t2 * (V__[1] - (1.0 / t152 * t70 * t103 * t76 * t139 + U__[iU_c_theta] * t40) * t2);
    real_type t165 = sin(t102);
    result__[ 4   ] = -2 * t40 * t2 * (V__[2] - (t70 * t165 * t76 * t139 + U__[iU_c_phi] * t40) * t2);
    result__[ 5   ] = -2 * t40 * t46;
    result__[ 6   ] = -2 * t40 * t85;
    result__[ 7   ] = -2 * t40 * t116;
    result__[ 8   ] = -2 * t40 * t135;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DmDuu_numRows() const { return 9; }
  integer HypersonicProblem3DOF::DmDuu_numCols() const { return 9; }
  integer HypersonicProblem3DOF::DmDuu_nnz()     const { return 17; }

  void
  HypersonicProblem3DOF::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 0   ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 6   ; jIndex[11] = 0   ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 7   ; jIndex[13] = 0   ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 8   ; jIndex[15] = 1   ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
  }


  void
  HypersonicProblem3DOF::DmDuu_sparse(
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
    real_type t1   = P__[iP_Tf];
    real_type t2   = t1 * t1;
    real_type t3   = ModelPars[iM_ODE];
    real_type t4   = t3 * t3;
    real_type t5   = t4 * t2;
    real_type t6   = ModelPars[iM_rho0];
    real_type t7   = t6 * t6;
    real_type t8   = X__[iX_h];
    real_type t12  = exp(-1.0 / ModelPars[iM_S] * t8);
    real_type t13  = t12 * t12;
    real_type t14  = t13 * t7;
    real_type t15  = t14 * t5;
    real_type t16  = X__[iX_V];
    real_type t17  = t16 * t16;
    real_type t18  = t17 * t17;
    real_type t19  = ModelPars[iM_CD2];
    real_type t20  = U__[iU_alpha];
    real_type t23  = ModelPars[iM_CD1];
    real_type t24  = 2 * t20 * t19 + t23;
    real_type t25  = t24 * t24;
    real_type t27  = ModelPars[iM_Aref];
    real_type t28  = t27 * t27;
    real_type t29  = ModelPars[iM_m];
    real_type t30  = t29 * t29;
    real_type t31  = 1.0 / t30;
    real_type t32  = t31 * t28;
    real_type t37  = X__[iX_G];
    real_type t38  = sin(t37);
    real_type t43  = pow(ModelPars[iM_re] + t8, 2);
    real_type t48  = t20 * t20;
    real_type t54  = 1.0 / t29;
    real_type t60  = ModelPars[iM_CTRL];
    real_type t67  = t6 * t3;
    real_type t69  = t17 * t12;
    real_type t75  = ModelPars[iM_CL1];
    real_type t76  = t75 * t75;
    real_type t78  = X__[iX_sigma];
    real_type t79  = cos(t78);
    real_type t80  = t79 * t79;
    real_type t88  = sin(t78);
    real_type t89  = t88 * t88;
    real_type t91  = cos(t37);
    real_type t92  = t91 * t91;
    result__[ 0   ] = t32 * t25 * t18 * t15 / 2 + 2 * t54 * t27 * t19 * t69 * t67 * t1 * (V__[3] - ((-1.0 / t43 * ModelPars[iM_mu] * t38 - t54 * t27 * (t48 * t19 + t20 * t23 + ModelPars[iM_CD0]) * t17 * t12 * t6 / 2) * t3 + U__[iU_c_V] * t60) * t1) + t80 * t32 * t76 * t17 * t15 / 2 + 1.0 / t92 * t89 * t31 * t28 * t76 * t17 * t14 * t5 / 2;
    real_type t98  = t60 * t2;
    result__[ 1   ] = -t54 * t27 * t24 * t69 * t67 * t98;
    real_type t105 = t12 * t67 * t98;
    real_type t106 = t75 * t16;
    result__[ 2   ] = t79 * t54 * t27 * t106 * t105;
    result__[ 3   ] = 1.0 / t91 * t88 * t54 * t27 * t106 * t105;
    real_type t116 = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    real_type t118 = ModelPars[iM_sigma_dot_max];
    real_type t119 = t118 * t118;
    result__[ 4   ] = t116 * t1 + 2 * t119 * t5;
    result__[ 5   ] = 2 * t118 * t3 * t98;
    real_type t124 = t60 * t60;
    result__[ 6   ] = 2 * t124 * t2;
    result__[ 7   ] = result__[6];
    result__[ 8   ] = result__[7];
    result__[ 9   ] = result__[1];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = result__[2];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = result__[3];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[5];
    result__[ 16  ] = result__[14];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 17, i_segment );
  }

}

// EOF: HypersonicProblem3DOF_Methods_controls.cc
