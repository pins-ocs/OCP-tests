/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_Guess.cc                         |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"

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


using namespace std;

namespace HypersonicProblem3DOFDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer HypersonicProblem3DOF::fd_ode_numEqns() const { return 7; }

  void
  HypersonicProblem3DOF::fd_ode_eval(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[7], V__[7];
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
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_Tf];
    real_type t3   = ModelPars[iM_ODE];
    real_type t4   = XM__[3];
    real_type t5   = t4 * t3;
    real_type t6   = XM__[4];
    real_type t7   = sin(t6);
    real_type t9   = ModelPars[iM_CTRL];
    result__[ 0   ] = V__[0] - (t7 * t5 + UM__[2] * t9) * t2;
    real_type t15  = cos(t6);
    real_type t17  = XM__[5];
    real_type t18  = cos(t17);
    real_type t20  = XM__[0];
    real_type t21  = ModelPars[iM_re] + t20;
    real_type t22  = 1.0 / t21;
    real_type t24  = XM__[2];
    real_type t25  = cos(t24);
    result__[ 1   ] = V__[1] - (1.0 / t25 * t22 * t18 * t15 * t5 + UM__[3] * t9) * t2;
    real_type t34  = sin(t17);
    result__[ 2   ] = V__[2] - (t22 * t34 * t15 * t5 + UM__[4] * t9) * t2;
    real_type t43  = ModelPars[iM_mu];
    real_type t45  = t21 * t21;
    real_type t46  = 1.0 / t45;
    real_type t52  = exp(-1.0 / ModelPars[iM_S] * t20);
    real_type t53  = t52 * ModelPars[iM_rho0];
    real_type t54  = t4 * t4;
    real_type t56  = UM__[0];
    real_type t57  = t56 * t56;
    real_type t64  = ModelPars[iM_Aref];
    real_type t67  = 1.0 / ModelPars[iM_m];
    result__[ 3   ] = V__[3] - ((-t46 * t43 * t7 - t67 * t64 * (ModelPars[iM_CD1] * t56 + ModelPars[iM_CD2] * t57 + ModelPars[iM_CD0]) * t54 * t53 / 2) * t3 + UM__[5] * t9) * t2;
    real_type t82  = ModelPars[iM_CL1] * t56 + ModelPars[iM_CL0];
    real_type t84  = XM__[6];
    real_type t85  = cos(t84);
    real_type t90  = t22 * t4;
    result__[ 4   ] = V__[4] - ((t85 * t67 * t64 * t82 * t4 * t53 / 2 + t15 * (t90 - 1.0 / t4 * t46 * t43)) * t3 + UM__[6] * t9) * t2;
    real_type t106 = sin(t84);
    real_type t113 = tan(t24);
    result__[ 5   ] = V__[5] - ((1.0 / t15 * t106 * t67 * t64 * t82 * t4 * t53 / 2 - t113 * t18 * t15 * t90) * t3 + UM__[7] * t9) * t2;
    result__[ 6   ] = V__[6] - (ModelPars[iM_sigma_dot_max] * t3 * UM__[1] + t9 * UM__[8]) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::Dfd_odeDxxpu_numRows() const { return 7; }
  integer HypersonicProblem3DOF::Dfd_odeDxxpu_numCols() const { return 24; }
  integer HypersonicProblem3DOF::Dfd_odeDxxpu_nnz()     const { return 74; }

  void
  HypersonicProblem3DOF::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 16  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 23  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 2   ;
    iIndex[11] = 1   ; jIndex[11] = 3   ;
    iIndex[12] = 1   ; jIndex[12] = 4   ;
    iIndex[13] = 1   ; jIndex[13] = 5   ;
    iIndex[14] = 1   ; jIndex[14] = 7   ;
    iIndex[15] = 1   ; jIndex[15] = 8   ;
    iIndex[16] = 1   ; jIndex[16] = 9   ;
    iIndex[17] = 1   ; jIndex[17] = 10  ;
    iIndex[18] = 1   ; jIndex[18] = 11  ;
    iIndex[19] = 1   ; jIndex[19] = 12  ;
    iIndex[20] = 1   ; jIndex[20] = 17  ;
    iIndex[21] = 1   ; jIndex[21] = 23  ;
    iIndex[22] = 2   ; jIndex[22] = 0   ;
    iIndex[23] = 2   ; jIndex[23] = 2   ;
    iIndex[24] = 2   ; jIndex[24] = 3   ;
    iIndex[25] = 2   ; jIndex[25] = 4   ;
    iIndex[26] = 2   ; jIndex[26] = 5   ;
    iIndex[27] = 2   ; jIndex[27] = 7   ;
    iIndex[28] = 2   ; jIndex[28] = 9   ;
    iIndex[29] = 2   ; jIndex[29] = 10  ;
    iIndex[30] = 2   ; jIndex[30] = 11  ;
    iIndex[31] = 2   ; jIndex[31] = 12  ;
    iIndex[32] = 2   ; jIndex[32] = 18  ;
    iIndex[33] = 2   ; jIndex[33] = 23  ;
    iIndex[34] = 3   ; jIndex[34] = 0   ;
    iIndex[35] = 3   ; jIndex[35] = 3   ;
    iIndex[36] = 3   ; jIndex[36] = 4   ;
    iIndex[37] = 3   ; jIndex[37] = 7   ;
    iIndex[38] = 3   ; jIndex[38] = 10  ;
    iIndex[39] = 3   ; jIndex[39] = 11  ;
    iIndex[40] = 3   ; jIndex[40] = 14  ;
    iIndex[41] = 3   ; jIndex[41] = 19  ;
    iIndex[42] = 3   ; jIndex[42] = 23  ;
    iIndex[43] = 4   ; jIndex[43] = 0   ;
    iIndex[44] = 4   ; jIndex[44] = 3   ;
    iIndex[45] = 4   ; jIndex[45] = 4   ;
    iIndex[46] = 4   ; jIndex[46] = 6   ;
    iIndex[47] = 4   ; jIndex[47] = 7   ;
    iIndex[48] = 4   ; jIndex[48] = 10  ;
    iIndex[49] = 4   ; jIndex[49] = 11  ;
    iIndex[50] = 4   ; jIndex[50] = 13  ;
    iIndex[51] = 4   ; jIndex[51] = 14  ;
    iIndex[52] = 4   ; jIndex[52] = 20  ;
    iIndex[53] = 4   ; jIndex[53] = 23  ;
    iIndex[54] = 5   ; jIndex[54] = 0   ;
    iIndex[55] = 5   ; jIndex[55] = 2   ;
    iIndex[56] = 5   ; jIndex[56] = 3   ;
    iIndex[57] = 5   ; jIndex[57] = 4   ;
    iIndex[58] = 5   ; jIndex[58] = 5   ;
    iIndex[59] = 5   ; jIndex[59] = 6   ;
    iIndex[60] = 5   ; jIndex[60] = 7   ;
    iIndex[61] = 5   ; jIndex[61] = 9   ;
    iIndex[62] = 5   ; jIndex[62] = 10  ;
    iIndex[63] = 5   ; jIndex[63] = 11  ;
    iIndex[64] = 5   ; jIndex[64] = 12  ;
    iIndex[65] = 5   ; jIndex[65] = 13  ;
    iIndex[66] = 5   ; jIndex[66] = 14  ;
    iIndex[67] = 5   ; jIndex[67] = 21  ;
    iIndex[68] = 5   ; jIndex[68] = 23  ;
    iIndex[69] = 6   ; jIndex[69] = 6   ;
    iIndex[70] = 6   ; jIndex[70] = 13  ;
    iIndex[71] = 6   ; jIndex[71] = 15  ;
    iIndex[72] = 6   ; jIndex[72] = 22  ;
    iIndex[73] = 6   ; jIndex[73] = 23  ;
  }


  void
  HypersonicProblem3DOF::Dfd_odeDxxpu_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[7], V__[7];
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
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    real_type t1   = P__[iP_Tf];
    real_type t2   = ModelPars[iM_ODE];
    real_type t3   = t2 * t1;
    real_type t4   = XM__[4];
    real_type t5   = sin(t4);
    result__[ 1   ] = -0.5e0 * t5 * t3;
    real_type t8   = XM__[3];
    real_type t9   = cos(t4);
    real_type t11  = t9 * t8 * t3;
    result__[ 2   ] = -0.5e0 * t11;
    result__[ 3   ] = __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t13  = ModelPars[iM_CTRL];
    result__[ 6   ] = -t13 * t1;
    real_type t15  = t8 * t2;
    result__[ 7   ] = -UM__[2] * t13 - t5 * t15;
    real_type t19  = t8 * t3;
    real_type t20  = XM__[5];
    real_type t21  = cos(t20);
    real_type t22  = t21 * t9;
    real_type t24  = XM__[0];
    real_type t25  = ModelPars[iM_re] + t24;
    real_type t26  = t25 * t25;
    real_type t27  = 1.0 / t26;
    real_type t28  = XM__[2];
    real_type t29  = cos(t28);
    real_type t30  = 1.0 / t29;
    result__[ 8   ] = 0.5e0 * t30 * t27 * t22 * t19;
    result__[ 9   ] = result__[0];
    real_type t34  = 1.0 / t25;
    real_type t35  = t34 * t21;
    real_type t36  = t29 * t29;
    real_type t38  = sin(t28);
    result__[ 10  ] = -0.5e0 * t38 / t36 * t35 * t11;
    real_type t44  = t30 * t35;
    result__[ 11  ] = -0.5e0 * t44 * t9 * t3;
    real_type t47  = t21 * t5;
    real_type t48  = t30 * t34;
    result__[ 12  ] = 0.5e0 * t48 * t47 * t19;
    real_type t51  = sin(t20);
    real_type t52  = t51 * t9;
    result__[ 13  ] = 0.5e0 * t48 * t52 * t19;
    result__[ 14  ] = result__[8];
    result__[ 15  ] = __INV_DZETA;
    result__[ 16  ] = result__[10];
    result__[ 17  ] = result__[11];
    result__[ 18  ] = result__[12];
    result__[ 19  ] = result__[13];
    result__[ 20  ] = result__[6];
    result__[ 21  ] = -t44 * t9 * t15 - UM__[3] * t13;
    result__[ 22  ] = 0.5e0 * t27 * t52 * t19;
    result__[ 23  ] = result__[9];
    real_type t61  = t34 * t52;
    result__[ 24  ] = -0.5e0 * t61 * t3;
    result__[ 25  ] = 0.5e0 * t34 * t51 * t5 * t19;
    result__[ 26  ] = -0.5e0 * t34 * t22 * t19;
    result__[ 27  ] = result__[22];
    result__[ 28  ] = __INV_DZETA;
    result__[ 29  ] = result__[24];
    result__[ 30  ] = result__[25];
    result__[ 31  ] = result__[26];
    result__[ 32  ] = result__[20];
    result__[ 33  ] = -UM__[4] * t13 - t61 * t15;
    real_type t73  = ModelPars[iM_mu];
    real_type t74  = t73 * t5;
    real_type t76  = 1.0 / t26 / t25;
    real_type t79  = ModelPars[iM_rho0];
    real_type t81  = 1.0 / ModelPars[iM_S];
    real_type t82  = t81 * t79;
    real_type t84  = exp(-t81 * t24);
    real_type t86  = t8 * t8;
    real_type t87  = UM__[0];
    real_type t88  = t87 * t87;
    real_type t89  = ModelPars[iM_CD2];
    real_type t91  = ModelPars[iM_CD1];
    real_type t94  = t91 * t87 + t89 * t88 + ModelPars[iM_CD0];
    real_type t96  = ModelPars[iM_Aref];
    real_type t98  = 1.0 / ModelPars[iM_m];
    real_type t99  = t98 * t96;
    result__[ 34  ] = -0.5e0 * (2 * t76 * t74 + t99 * t94 * t86 * t84 * t82 / 2) * t3;
    real_type t106 = t84 * t79;
    real_type t107 = t106 * t3;
    real_type t111 = 0.5e0 * t99 * t94 * t8 * t107;
    result__[ 35  ] = t111 + result__[23];
    result__[ 36  ] = 0.5e0 * t27 * t73 * t9 * t3;
    result__[ 37  ] = result__[34];
    result__[ 38  ] = t111 + __INV_DZETA;
    result__[ 39  ] = result__[36];
    result__[ 40  ] = t99 * (2 * t89 * t87 + t91) * t86 * t107 / 2;
    result__[ 41  ] = result__[32];
    result__[ 42  ] = -(-t27 * t74 - t98 * t96 * t94 * t86 * t106 / 2) * t2 - UM__[5] * t13;
    real_type t132 = t8 * t84 * t82;
    real_type t133 = ModelPars[iM_CL1];
    real_type t136 = t133 * t87 + ModelPars[iM_CL0];
    real_type t137 = t96 * t136;
    real_type t138 = XM__[6];
    real_type t139 = cos(t138);
    real_type t140 = t139 * t98;
    real_type t141 = t140 * t137;
    real_type t144 = t27 * t8;
    real_type t146 = 1.0 / t8;
    result__[ 43  ] = -0.5e0 * (-t141 * t132 / 2 + t9 * (2 * t146 * t76 * t73 - t144)) * t3;
    real_type t154 = t136 * t106;
    real_type t155 = t139 * t99;
    real_type t158 = t27 * t73;
    result__[ 44  ] = -0.5e0 * (t155 * t154 / 2 + t9 * (t34 + 1.0 / t86 * t158)) * t3;
    real_type t166 = t34 * t8;
    real_type t168 = -t146 * t158 + t166;
    real_type t171 = 0.5e0 * t5 * t168 * t3;
    result__[ 45  ] = t171 + result__[23];
    real_type t172 = t136 * t8;
    real_type t173 = sin(t138);
    result__[ 46  ] = 0.2500000000e0 * t173 * t99 * t172 * t107;
    result__[ 47  ] = result__[43];
    result__[ 48  ] = result__[44];
    result__[ 49  ] = t171 + __INV_DZETA;
    result__[ 50  ] = result__[46];
    result__[ 51  ] = -t155 * t133 * t8 * t107 / 2;
    result__[ 52  ] = result__[41];
    real_type t181 = t8 * t106;
    result__[ 53  ] = -(t141 * t181 / 2 + t9 * t168) * t2 - UM__[6] * t13;
    real_type t190 = 1.0 / t9;
    real_type t191 = t190 * t173 * t98;
    real_type t195 = tan(t28);
    real_type t196 = t195 * t22;
    result__[ 54  ] = -0.5e0 * (-t191 * t137 * t132 / 2 + t196 * t144) * t3;
    real_type t201 = t9 * t34;
    real_type t202 = t195 * t195;
    result__[ 55  ] = 0.5e0 * (1 + t202) * t21 * t201 * t19;
    real_type t208 = t190 * t173 * t99;
    result__[ 56  ] = -0.5e0 * (t208 * t154 / 2 - t195 * t21 * t201) * t3;
    real_type t216 = t172 * t106;
    real_type t217 = t9 * t9;
    result__[ 57  ] = -0.5e0 * (t5 / t217 * t173 * t99 * t216 / 2 + t195 * t47 * t166) * t3;
    real_type t232 = 0.5e0 * t195 * t51 * t201 * t19;
    result__[ 58  ] = -t232 + result__[23];
    real_type t233 = t181 * t3;
    result__[ 59  ] = -0.2500000000e0 * t190 * t140 * t137 * t233;
    result__[ 60  ] = result__[54];
    result__[ 61  ] = result__[55];
    result__[ 62  ] = result__[56];
    result__[ 63  ] = result__[57];
    result__[ 64  ] = -t232 + __INV_DZETA;
    result__[ 65  ] = result__[59];
    result__[ 66  ] = -t191 * t96 * t133 * t233 / 2;
    result__[ 67  ] = result__[52];
    result__[ 68  ] = -(t208 * t216 / 2 - t196 * t166) * t2 - UM__[7] * t13;
    result__[ 69  ] = result__[23];
    result__[ 70  ] = __INV_DZETA;
    real_type t249 = ModelPars[iM_sigma_dot_max];
    result__[ 71  ] = -t249 * t3;
    result__[ 72  ] = result__[67];
    result__[ 73  ] = -t249 * t2 * UM__[1] - t13 * UM__[8];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 74, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2fd_odeD2xxpu_numRows() const { return 24; }
  integer HypersonicProblem3DOF::D2fd_odeD2xxpu_numCols() const { return 24; }
  integer HypersonicProblem3DOF::D2fd_odeD2xxpu_nnz()     const { return 187; }

  void
  HypersonicProblem3DOF::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 10  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 11  ;
    iIndex[10] = 0   ; jIndex[10] = 12  ;
    iIndex[11] = 0   ; jIndex[11] = 13  ;
    iIndex[12] = 0   ; jIndex[12] = 14  ;
    iIndex[13] = 0   ; jIndex[13] = 23  ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 2   ;
    iIndex[16] = 2   ; jIndex[16] = 3   ;
    iIndex[17] = 2   ; jIndex[17] = 4   ;
    iIndex[18] = 2   ; jIndex[18] = 5   ;
    iIndex[19] = 2   ; jIndex[19] = 7   ;
    iIndex[20] = 2   ; jIndex[20] = 9   ;
    iIndex[21] = 2   ; jIndex[21] = 10  ;
    iIndex[22] = 2   ; jIndex[22] = 11  ;
    iIndex[23] = 2   ; jIndex[23] = 12  ;
    iIndex[24] = 2   ; jIndex[24] = 23  ;
    iIndex[25] = 3   ; jIndex[25] = 0   ;
    iIndex[26] = 3   ; jIndex[26] = 2   ;
    iIndex[27] = 3   ; jIndex[27] = 3   ;
    iIndex[28] = 3   ; jIndex[28] = 4   ;
    iIndex[29] = 3   ; jIndex[29] = 5   ;
    iIndex[30] = 3   ; jIndex[30] = 6   ;
    iIndex[31] = 3   ; jIndex[31] = 7   ;
    iIndex[32] = 3   ; jIndex[32] = 9   ;
    iIndex[33] = 3   ; jIndex[33] = 10  ;
    iIndex[34] = 3   ; jIndex[34] = 11  ;
    iIndex[35] = 3   ; jIndex[35] = 12  ;
    iIndex[36] = 3   ; jIndex[36] = 13  ;
    iIndex[37] = 3   ; jIndex[37] = 14  ;
    iIndex[38] = 3   ; jIndex[38] = 23  ;
    iIndex[39] = 4   ; jIndex[39] = 0   ;
    iIndex[40] = 4   ; jIndex[40] = 2   ;
    iIndex[41] = 4   ; jIndex[41] = 3   ;
    iIndex[42] = 4   ; jIndex[42] = 4   ;
    iIndex[43] = 4   ; jIndex[43] = 5   ;
    iIndex[44] = 4   ; jIndex[44] = 6   ;
    iIndex[45] = 4   ; jIndex[45] = 7   ;
    iIndex[46] = 4   ; jIndex[46] = 9   ;
    iIndex[47] = 4   ; jIndex[47] = 10  ;
    iIndex[48] = 4   ; jIndex[48] = 11  ;
    iIndex[49] = 4   ; jIndex[49] = 12  ;
    iIndex[50] = 4   ; jIndex[50] = 13  ;
    iIndex[51] = 4   ; jIndex[51] = 14  ;
    iIndex[52] = 4   ; jIndex[52] = 23  ;
    iIndex[53] = 5   ; jIndex[53] = 0   ;
    iIndex[54] = 5   ; jIndex[54] = 2   ;
    iIndex[55] = 5   ; jIndex[55] = 3   ;
    iIndex[56] = 5   ; jIndex[56] = 4   ;
    iIndex[57] = 5   ; jIndex[57] = 5   ;
    iIndex[58] = 5   ; jIndex[58] = 7   ;
    iIndex[59] = 5   ; jIndex[59] = 9   ;
    iIndex[60] = 5   ; jIndex[60] = 10  ;
    iIndex[61] = 5   ; jIndex[61] = 11  ;
    iIndex[62] = 5   ; jIndex[62] = 12  ;
    iIndex[63] = 5   ; jIndex[63] = 23  ;
    iIndex[64] = 6   ; jIndex[64] = 0   ;
    iIndex[65] = 6   ; jIndex[65] = 3   ;
    iIndex[66] = 6   ; jIndex[66] = 4   ;
    iIndex[67] = 6   ; jIndex[67] = 6   ;
    iIndex[68] = 6   ; jIndex[68] = 7   ;
    iIndex[69] = 6   ; jIndex[69] = 10  ;
    iIndex[70] = 6   ; jIndex[70] = 11  ;
    iIndex[71] = 6   ; jIndex[71] = 13  ;
    iIndex[72] = 6   ; jIndex[72] = 14  ;
    iIndex[73] = 6   ; jIndex[73] = 23  ;
    iIndex[74] = 7   ; jIndex[74] = 0   ;
    iIndex[75] = 7   ; jIndex[75] = 2   ;
    iIndex[76] = 7   ; jIndex[76] = 3   ;
    iIndex[77] = 7   ; jIndex[77] = 4   ;
    iIndex[78] = 7   ; jIndex[78] = 5   ;
    iIndex[79] = 7   ; jIndex[79] = 6   ;
    iIndex[80] = 7   ; jIndex[80] = 7   ;
    iIndex[81] = 7   ; jIndex[81] = 9   ;
    iIndex[82] = 7   ; jIndex[82] = 10  ;
    iIndex[83] = 7   ; jIndex[83] = 11  ;
    iIndex[84] = 7   ; jIndex[84] = 12  ;
    iIndex[85] = 7   ; jIndex[85] = 13  ;
    iIndex[86] = 7   ; jIndex[86] = 14  ;
    iIndex[87] = 7   ; jIndex[87] = 23  ;
    iIndex[88] = 9   ; jIndex[88] = 0   ;
    iIndex[89] = 9   ; jIndex[89] = 2   ;
    iIndex[90] = 9   ; jIndex[90] = 3   ;
    iIndex[91] = 9   ; jIndex[91] = 4   ;
    iIndex[92] = 9   ; jIndex[92] = 5   ;
    iIndex[93] = 9   ; jIndex[93] = 7   ;
    iIndex[94] = 9   ; jIndex[94] = 9   ;
    iIndex[95] = 9   ; jIndex[95] = 10  ;
    iIndex[96] = 9   ; jIndex[96] = 11  ;
    iIndex[97] = 9   ; jIndex[97] = 12  ;
    iIndex[98] = 9   ; jIndex[98] = 23  ;
    iIndex[99] = 10  ; jIndex[99] = 0   ;
    iIndex[100] = 10  ; jIndex[100] = 2   ;
    iIndex[101] = 10  ; jIndex[101] = 3   ;
    iIndex[102] = 10  ; jIndex[102] = 4   ;
    iIndex[103] = 10  ; jIndex[103] = 5   ;
    iIndex[104] = 10  ; jIndex[104] = 6   ;
    iIndex[105] = 10  ; jIndex[105] = 7   ;
    iIndex[106] = 10  ; jIndex[106] = 9   ;
    iIndex[107] = 10  ; jIndex[107] = 10  ;
    iIndex[108] = 10  ; jIndex[108] = 11  ;
    iIndex[109] = 10  ; jIndex[109] = 12  ;
    iIndex[110] = 10  ; jIndex[110] = 13  ;
    iIndex[111] = 10  ; jIndex[111] = 14  ;
    iIndex[112] = 10  ; jIndex[112] = 23  ;
    iIndex[113] = 11  ; jIndex[113] = 0   ;
    iIndex[114] = 11  ; jIndex[114] = 2   ;
    iIndex[115] = 11  ; jIndex[115] = 3   ;
    iIndex[116] = 11  ; jIndex[116] = 4   ;
    iIndex[117] = 11  ; jIndex[117] = 5   ;
    iIndex[118] = 11  ; jIndex[118] = 6   ;
    iIndex[119] = 11  ; jIndex[119] = 7   ;
    iIndex[120] = 11  ; jIndex[120] = 9   ;
    iIndex[121] = 11  ; jIndex[121] = 10  ;
    iIndex[122] = 11  ; jIndex[122] = 11  ;
    iIndex[123] = 11  ; jIndex[123] = 12  ;
    iIndex[124] = 11  ; jIndex[124] = 13  ;
    iIndex[125] = 11  ; jIndex[125] = 14  ;
    iIndex[126] = 11  ; jIndex[126] = 23  ;
    iIndex[127] = 12  ; jIndex[127] = 0   ;
    iIndex[128] = 12  ; jIndex[128] = 2   ;
    iIndex[129] = 12  ; jIndex[129] = 3   ;
    iIndex[130] = 12  ; jIndex[130] = 4   ;
    iIndex[131] = 12  ; jIndex[131] = 5   ;
    iIndex[132] = 12  ; jIndex[132] = 7   ;
    iIndex[133] = 12  ; jIndex[133] = 9   ;
    iIndex[134] = 12  ; jIndex[134] = 10  ;
    iIndex[135] = 12  ; jIndex[135] = 11  ;
    iIndex[136] = 12  ; jIndex[136] = 12  ;
    iIndex[137] = 12  ; jIndex[137] = 23  ;
    iIndex[138] = 13  ; jIndex[138] = 0   ;
    iIndex[139] = 13  ; jIndex[139] = 3   ;
    iIndex[140] = 13  ; jIndex[140] = 4   ;
    iIndex[141] = 13  ; jIndex[141] = 6   ;
    iIndex[142] = 13  ; jIndex[142] = 7   ;
    iIndex[143] = 13  ; jIndex[143] = 10  ;
    iIndex[144] = 13  ; jIndex[144] = 11  ;
    iIndex[145] = 13  ; jIndex[145] = 13  ;
    iIndex[146] = 13  ; jIndex[146] = 14  ;
    iIndex[147] = 13  ; jIndex[147] = 23  ;
    iIndex[148] = 14  ; jIndex[148] = 0   ;
    iIndex[149] = 14  ; jIndex[149] = 3   ;
    iIndex[150] = 14  ; jIndex[150] = 4   ;
    iIndex[151] = 14  ; jIndex[151] = 6   ;
    iIndex[152] = 14  ; jIndex[152] = 7   ;
    iIndex[153] = 14  ; jIndex[153] = 10  ;
    iIndex[154] = 14  ; jIndex[154] = 11  ;
    iIndex[155] = 14  ; jIndex[155] = 13  ;
    iIndex[156] = 14  ; jIndex[156] = 14  ;
    iIndex[157] = 14  ; jIndex[157] = 23  ;
    iIndex[158] = 15  ; jIndex[158] = 23  ;
    iIndex[159] = 16  ; jIndex[159] = 23  ;
    iIndex[160] = 17  ; jIndex[160] = 23  ;
    iIndex[161] = 18  ; jIndex[161] = 23  ;
    iIndex[162] = 19  ; jIndex[162] = 23  ;
    iIndex[163] = 20  ; jIndex[163] = 23  ;
    iIndex[164] = 21  ; jIndex[164] = 23  ;
    iIndex[165] = 22  ; jIndex[165] = 23  ;
    iIndex[166] = 23  ; jIndex[166] = 0   ;
    iIndex[167] = 23  ; jIndex[167] = 2   ;
    iIndex[168] = 23  ; jIndex[168] = 3   ;
    iIndex[169] = 23  ; jIndex[169] = 4   ;
    iIndex[170] = 23  ; jIndex[170] = 5   ;
    iIndex[171] = 23  ; jIndex[171] = 6   ;
    iIndex[172] = 23  ; jIndex[172] = 7   ;
    iIndex[173] = 23  ; jIndex[173] = 9   ;
    iIndex[174] = 23  ; jIndex[174] = 10  ;
    iIndex[175] = 23  ; jIndex[175] = 11  ;
    iIndex[176] = 23  ; jIndex[176] = 12  ;
    iIndex[177] = 23  ; jIndex[177] = 13  ;
    iIndex[178] = 23  ; jIndex[178] = 14  ;
    iIndex[179] = 23  ; jIndex[179] = 15  ;
    iIndex[180] = 23  ; jIndex[180] = 16  ;
    iIndex[181] = 23  ; jIndex[181] = 17  ;
    iIndex[182] = 23  ; jIndex[182] = 18  ;
    iIndex[183] = 23  ; jIndex[183] = 19  ;
    iIndex[184] = 23  ; jIndex[184] = 20  ;
    iIndex[185] = 23  ; jIndex[185] = 21  ;
    iIndex[186] = 23  ; jIndex[186] = 22  ;
  }


  void
  HypersonicProblem3DOF::D2fd_odeD2xxpu_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[7], V__[7];
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
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    V__[6] = __INV_DZETA*(XR__[6]-XL__[6]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[1];
    real_type t2   = P__[iP_Tf];
    real_type t3   = t2 * t1;
    real_type t4   = ModelPars[iM_ODE];
    real_type t8   = XR__[iX_V] / 2 + XL__[iX_V] / 2;
    real_type t9   = t8 * t4;
    real_type t10  = t9 * t3;
    real_type t14  = XR__[iX_G] / 2 + XL__[iX_G] / 2;
    real_type t15  = cos(t14);
    real_type t19  = XR__[iX_psi] / 2 + XL__[iX_psi] / 2;
    real_type t20  = cos(t19);
    real_type t21  = t20 * t15;
    real_type t23  = XR__[iX_h];
    real_type t25  = XL__[iX_h];
    real_type t27  = ModelPars[iM_re] + t23 / 2 + t25 / 2;
    real_type t28  = t27 * t27;
    real_type t30  = 1.0 / t28 / t27;
    real_type t34  = XR__[iX_phi] / 2 + XL__[iX_phi] / 2;
    real_type t35  = cos(t34);
    real_type t36  = 1.0 / t35;
    real_type t41  = LM__[2];
    real_type t43  = t4 * t2 * t41;
    real_type t44  = t15 * t8;
    real_type t45  = sin(t19);
    real_type t50  = LM__[3];
    real_type t51  = t2 * t50;
    real_type t52  = sin(t14);
    real_type t53  = ModelPars[iM_mu];
    real_type t54  = t53 * t52;
    real_type t55  = t28 * t28;
    real_type t56  = 1.0 / t55;
    real_type t59  = ModelPars[iM_rho0];
    real_type t60  = ModelPars[iM_S];
    real_type t61  = t60 * t60;
    real_type t63  = 1.0 / t61 * t59;
    real_type t66  = 1.0 / t60;
    real_type t68  = exp(-t66 * (t23 / 2 + t25 / 2));
    real_type t70  = t8 * t8;
    real_type t71  = UM__[0];
    real_type t72  = t71 * t71;
    real_type t73  = ModelPars[iM_CD2];
    real_type t75  = ModelPars[iM_CD1];
    real_type t78  = t75 * t71 + t73 * t72 + ModelPars[iM_CD0];
    real_type t80  = ModelPars[iM_Aref];
    real_type t82  = 1.0 / ModelPars[iM_m];
    real_type t83  = t82 * t80;
    real_type t84  = t83 * t78 * t70;
    real_type t90  = LM__[4];
    real_type t91  = t2 * t90;
    real_type t92  = t8 * t68;
    real_type t93  = t92 * t63;
    real_type t94  = ModelPars[iM_CL1];
    real_type t97  = t94 * t71 + ModelPars[iM_CL0];
    real_type t98  = t80 * t97;
    real_type t102 = XR__[iX_sigma] / 2 + XL__[iX_sigma] / 2;
    real_type t103 = cos(t102);
    real_type t104 = t103 * t82;
    real_type t105 = t104 * t98;
    real_type t108 = t30 * t8;
    real_type t111 = 1.0 / t8;
    real_type t119 = LM__[5];
    real_type t120 = t2 * t119;
    real_type t121 = sin(t102);
    real_type t122 = t121 * t82;
    real_type t123 = 1.0 / t15;
    real_type t124 = t123 * t122;
    real_type t125 = t124 * t98;
    real_type t128 = tan(t34);
    real_type t129 = t128 * t21;
    result__[ 0   ] = -t36 * t30 * t21 * t10 / 2 - t30 * t45 * t44 * t43 / 2 - (-3.0 / 2.0 * t56 * t54 - t84 * t68 * t63 / 8) * t4 * t51 - (t105 * t93 / 8 + t15 * (t108 / 2 - 3.0 / 2.0 * t111 * t56 * t53)) * t4 * t91 - (t125 * t93 / 8 - t129 * t108 / 2) * t4 * t120;
    real_type t135 = 1.0 / t28;
    real_type t136 = t35 * t35;
    real_type t137 = 1.0 / t136;
    real_type t139 = sin(t34);
    real_type t144 = t9 * t120;
    real_type t145 = t15 * t135;
    real_type t146 = t128 * t128;
    real_type t148 = 1.0 / 2.0 + t146 / 2;
    real_type t149 = t148 * t20;
    result__[ 1   ] = t139 * t137 * t135 * t21 * t10 / 4 - t149 * t145 * t144 / 2;
    real_type t153 = t4 * t3;
    real_type t154 = t36 * t135;
    real_type t155 = t154 * t21;
    real_type t158 = t45 * t15;
    real_type t159 = t135 * t158;
    real_type t162 = t59 * t4;
    real_type t163 = t66 * t162;
    real_type t164 = t163 * t51;
    real_type t170 = t66 * t59;
    real_type t171 = t68 * t170;
    real_type t175 = t30 * t53;
    real_type t176 = 1.0 / t70;
    real_type t184 = t97 * t68;
    real_type t187 = t123 * t121 * t83;
    real_type t190 = t128 * t20;
    result__[ 2   ] = t155 * t153 / 4 + t159 * t43 / 4 - t82 * t80 * t78 * t92 * t164 / 4 - (-t105 * t171 / 8 + t15 * (-t135 / 4 - t176 * t175 / 2)) * t4 * t91 - (-t187 * t184 * t170 / 8 + t190 * t145 / 4) * t4 * t120;
    real_type t196 = t20 * t52;
    real_type t200 = t52 * t8;
    real_type t205 = t4 * t51;
    real_type t206 = t53 * t15;
    real_type t210 = t135 * t8;
    real_type t213 = -t210 / 2 + t111 * t175;
    real_type t218 = t97 * t92;
    real_type t220 = t15 * t15;
    real_type t221 = 1.0 / t220;
    real_type t223 = t52 * t221 * t121;
    real_type t224 = t223 * t83;
    real_type t227 = t128 * t196;
    result__[ 3   ] = -t154 * t196 * t10 / 4 - t135 * t45 * t200 * t43 / 4 - t30 * t206 * t205 / 2 + t52 * t213 * t4 * t91 / 2 - (-t224 * t218 * t170 / 8 - t227 * t210 / 4) * t4 * t120;
    real_type t238 = t128 * t45;
    result__[ 4   ] = t135 * t20 * t44 * t43 / 4 - t154 * t158 * t10 / 4 + t238 * t145 * t144 / 4;
    real_type t242 = t163 * t91;
    real_type t243 = t83 * t121;
    real_type t246 = t4 * t120;
    real_type t247 = t171 * t246;
    real_type t248 = t97 * t8;
    real_type t249 = t80 * t248;
    real_type t250 = t123 * t104;
    result__[ 5   ] = -t243 * t218 * t242 / 8 + t250 * t249 * t247 / 8;
    result__[ 6   ] = result__[0];
    result__[ 7   ] = result__[1];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[3];
    result__[ 10  ] = result__[4];
    result__[ 11  ] = result__[5];
    real_type t254 = t70 * t68;
    real_type t257 = 2 * t73 * t71 + t75;
    real_type t259 = t82 * t80 * t257;
    real_type t263 = t103 * t83;
    real_type t266 = t94 * t8;
    real_type t267 = t80 * t266;
    result__[ 12  ] = t263 * t94 * t92 * t242 / 4 + t124 * t267 * t247 / 4 - t259 * t254 * t164 / 4;
    real_type t271 = t4 * t1;
    real_type t272 = t8 * t271;
    real_type t275 = t4 * t41;
    real_type t276 = t8 * t275;
    real_type t279 = t4 * t50;
    real_type t285 = t4 * t90;
    real_type t286 = t92 * t170;
    real_type t292 = t4 * t119;
    result__[ 13  ] = t155 * t272 / 2 + t159 * t276 / 2 - (t30 * t54 + t84 * t171 / 4) * t279 - (-t105 * t286 / 4 + t15 * t213) * t285 - (-t125 * t286 / 4 + t129 * t210 / 2) * t292;
    result__[ 14  ] = result__[7];
    real_type t299 = 1.0 / t27;
    real_type t303 = t139 * t139;
    real_type t308 = t36 * t299;
    real_type t310 = t308 * t21 * t10;
    real_type t311 = t310 / 4;
    real_type t312 = t15 * t299;
    result__[ 15  ] = -t303 / t136 / t35 * t299 * t21 * t10 / 2 - t311 + t148 * t190 * t312 * t144;
    real_type t316 = t15 * t4;
    real_type t318 = t299 * t20;
    real_type t320 = t139 * t137 * t318;
    real_type t323 = t149 * t312;
    result__[ 16  ] = -t320 * t316 * t3 / 4 + t323 * t246 / 2;
    real_type t327 = t139 * t137 * t299;
    real_type t331 = t52 * t299;
    result__[ 17  ] = t327 * t196 * t10 / 4 - t149 * t331 * t144 / 2;
    result__[ 18  ] = t327 * t158 * t10 / 4 - t148 * t45 * t312 * t144 / 2;
    result__[ 19  ] = result__[14];
    result__[ 20  ] = result__[15];
    result__[ 21  ] = result__[16];
    result__[ 22  ] = result__[17];
    result__[ 23  ] = result__[18];
    real_type t345 = t8 * t292;
    result__[ 24  ] = -t320 * t44 * t271 / 2 + t323 * t345;
    result__[ 25  ] = result__[8];
    result__[ 26  ] = result__[21];
    real_type t347 = t162 * t51;
    real_type t353 = t135 * t53;
    result__[ 27  ] = t83 * t78 * t68 * t347 / 4 + t15 / t70 / t8 * t353 * t4 * t91 / 2;
    real_type t360 = LM__[0];
    real_type t361 = t2 * t360;
    real_type t364 = t308 * t196;
    real_type t367 = t45 * t52;
    real_type t368 = t299 * t367;
    real_type t373 = t176 * t353 / 2 + t299 / 2;
    real_type t378 = t68 * t59;
    result__[ 28  ] = -t316 * t361 / 4 + t364 * t153 / 4 + t368 * t43 / 4 + t52 * t373 * t4 * t91 / 2 - (t52 * t221 * t122 * t98 * t378 / 8 + t190 * t331 / 4) * t4 * t120;
    real_type t389 = t308 * t158;
    real_type t391 = t299 * t21;
    real_type t393 = t238 * t312;
    result__[ 29  ] = t389 * t153 / 4 - t393 * t246 / 4 - t391 * t43 / 4;
    real_type t396 = t162 * t91;
    real_type t399 = t68 * t162;
    real_type t400 = t399 * t120;
    real_type t401 = t250 * t98;
    result__[ 30  ] = t243 * t184 * t396 / 8 - t401 * t400 / 8;
    result__[ 31  ] = result__[25];
    result__[ 32  ] = result__[26];
    result__[ 33  ] = result__[27];
    result__[ 34  ] = result__[28];
    result__[ 35  ] = result__[29];
    result__[ 36  ] = result__[30];
    real_type t411 = t80 * t94;
    real_type t412 = t124 * t411;
    result__[ 37  ] = t259 * t92 * t347 / 2 - t263 * t94 * t68 * t396 / 4 - t412 * t400 / 4;
    real_type t415 = t4 * t360;
    real_type t425 = t378 * t279;
    real_type t430 = t97 * t378;
    real_type t438 = t190 * t312;
    result__[ 38  ] = -t52 * t415 / 2 - t36 * t318 * t15 * t271 / 2 - t299 * t158 * t275 / 2 + t83 * t78 * t8 * t425 / 2 - (t263 * t430 / 4 + t15 * t373) * t285 - (t187 * t430 / 4 - t438 / 2) * t292;
    result__[ 39  ] = result__[9];
    result__[ 40  ] = result__[22];
    result__[ 41  ] = result__[34];
    real_type t447 = t299 * t45 * t44 * t43;
    real_type t452 = t299 * t8;
    real_type t454 = -t111 * t353 + t452;
    real_type t459 = t248 * t378;
    real_type t463 = t52 * t52;
    result__[ 42  ] = t52 * t9 * t361 / 4 + t311 + t447 / 4 - t135 * t54 * t205 / 4 + t15 * t454 * t4 * t91 / 4 - (t463 / t220 / t15 * t121 * t83 * t459 / 4 + t187 * t459 / 8 + t129 * t452 / 4) * t4 * t120;
    result__[ 43  ] = -t308 * t367 * t10 / 4 + t238 * t331 * t144 / 4 + t318 * t200 * t43 / 4;
    real_type t482 = t8 * t378;
    real_type t483 = t482 * t246;
    result__[ 44  ] = -t52 * t221 * t103 * t82 * t98 * t483 / 8;
    result__[ 45  ] = result__[39];
    result__[ 46  ] = result__[40];
    result__[ 47  ] = result__[41];
    result__[ 48  ] = result__[42];
    result__[ 49  ] = result__[43];
    result__[ 50  ] = result__[44];
    result__[ 51  ] = -t223 * t82 * t411 * t483 / 4;
    result__[ 52  ] = -t44 * t415 / 2 + t364 * t272 / 2 + t368 * t276 / 2 + t135 * t206 * t279 / 2 + t52 * t454 * t285 / 2 - (t224 * t459 / 4 + t227 * t452 / 2) * t292;
    result__[ 53  ] = result__[10];
    result__[ 54  ] = result__[23];
    result__[ 55  ] = result__[35];
    result__[ 56  ] = result__[49];
    result__[ 57  ] = -t438 * t144 / 4 + t310 / 4 + t447 / 4;
    result__[ 58  ] = result__[53];
    result__[ 59  ] = result__[54];
    result__[ 60  ] = result__[55];
    result__[ 61  ] = result__[56];
    result__[ 62  ] = result__[57];
    result__[ 63  ] = t389 * t272 / 2 - t391 * t276 / 2 - t393 * t345 / 2;
    result__[ 64  ] = result__[11];
    result__[ 65  ] = result__[36];
    result__[ 66  ] = result__[50];
    real_type t518 = t399 * t91;
    result__[ 67  ] = t124 * t249 * t400 / 8 + t263 * t248 * t518 / 8;
    result__[ 68  ] = result__[64];
    result__[ 69  ] = result__[65];
    result__[ 70  ] = result__[66];
    result__[ 71  ] = result__[67];
    result__[ 72  ] = t243 * t266 * t518 / 4 - t250 * t267 * t400 / 4;
    real_type t529 = t378 * t285;
    real_type t532 = t482 * t292;
    result__[ 73  ] = t243 * t248 * t529 / 4 - t401 * t532 / 4;
    result__[ 74  ] = result__[6];
    result__[ 75  ] = result__[19];
    result__[ 76  ] = result__[31];
    result__[ 77  ] = result__[45];
    result__[ 78  ] = result__[58];
    result__[ 79  ] = result__[68];
    result__[ 80  ] = result__[74];
    result__[ 81  ] = result__[75];
    result__[ 82  ] = result__[76];
    result__[ 83  ] = result__[77];
    result__[ 84  ] = result__[78];
    result__[ 85  ] = result__[79];
    result__[ 86  ] = result__[12];
    result__[ 87  ] = result__[13];
    result__[ 88  ] = result__[81];
    result__[ 89  ] = result__[20];
    result__[ 90  ] = result__[32];
    result__[ 91  ] = result__[46];
    result__[ 92  ] = result__[59];
    result__[ 93  ] = result__[88];
    result__[ 94  ] = result__[89];
    result__[ 95  ] = result__[90];
    result__[ 96  ] = result__[91];
    result__[ 97  ] = result__[92];
    result__[ 98  ] = result__[24];
    result__[ 99  ] = result__[82];
    result__[ 100 ] = result__[95];
    result__[ 101 ] = result__[33];
    result__[ 102 ] = result__[47];
    result__[ 103 ] = result__[60];
    result__[ 104 ] = result__[69];
    result__[ 105 ] = result__[99];
    result__[ 106 ] = result__[100];
    result__[ 107 ] = result__[101];
    result__[ 108 ] = result__[102];
    result__[ 109 ] = result__[103];
    result__[ 110 ] = result__[104];
    result__[ 111 ] = result__[37];
    result__[ 112 ] = result__[38];
    result__[ 113 ] = result__[83];
    result__[ 114 ] = result__[96];
    result__[ 115 ] = result__[108];
    result__[ 116 ] = result__[48];
    result__[ 117 ] = result__[61];
    result__[ 118 ] = result__[70];
    result__[ 119 ] = result__[113];
    result__[ 120 ] = result__[114];
    result__[ 121 ] = result__[115];
    result__[ 122 ] = result__[116];
    result__[ 123 ] = result__[117];
    result__[ 124 ] = result__[118];
    result__[ 125 ] = result__[51];
    result__[ 126 ] = result__[52];
    result__[ 127 ] = result__[84];
    result__[ 128 ] = result__[97];
    result__[ 129 ] = result__[109];
    result__[ 130 ] = result__[123];
    result__[ 131 ] = result__[62];
    result__[ 132 ] = result__[127];
    result__[ 133 ] = result__[128];
    result__[ 134 ] = result__[129];
    result__[ 135 ] = result__[130];
    result__[ 136 ] = result__[131];
    result__[ 137 ] = result__[63];
    result__[ 138 ] = result__[85];
    result__[ 139 ] = result__[110];
    result__[ 140 ] = result__[124];
    result__[ 141 ] = result__[71];
    result__[ 142 ] = result__[138];
    result__[ 143 ] = result__[139];
    result__[ 144 ] = result__[140];
    result__[ 145 ] = result__[141];
    result__[ 146 ] = result__[72];
    result__[ 147 ] = result__[73];
    result__[ 148 ] = result__[86];
    result__[ 149 ] = result__[111];
    result__[ 150 ] = result__[125];
    result__[ 151 ] = result__[146];
    result__[ 152 ] = result__[148];
    result__[ 153 ] = result__[149];
    result__[ 154 ] = result__[150];
    result__[ 155 ] = result__[151];
    result__[ 156 ] = t82 * t80 * t73 * t254 * t347;
    result__[ 157 ] = t83 * t257 * t70 * t425 / 2 - t263 * t266 * t529 / 2 - t412 * t532 / 2;
    real_type t545 = LM__[6];
    result__[ 158 ] = -ModelPars[iM_sigma_dot_max] * t4 * t545;
    real_type t549 = ModelPars[iM_CTRL];
    result__[ 159 ] = -t549 * t360;
    result__[ 160 ] = -t549 * t1;
    result__[ 161 ] = -t549 * t41;
    result__[ 162 ] = -t549 * t50;
    result__[ 163 ] = -t549 * t90;
    result__[ 164 ] = -t549 * t119;
    result__[ 165 ] = -t549 * t545;
    result__[ 166 ] = result__[87];
    result__[ 167 ] = result__[98];
    result__[ 168 ] = result__[112];
    result__[ 169 ] = result__[126];
    result__[ 170 ] = result__[137];
    result__[ 171 ] = result__[147];
    result__[ 172 ] = result__[166];
    result__[ 173 ] = result__[167];
    result__[ 174 ] = result__[168];
    result__[ 175 ] = result__[169];
    result__[ 176 ] = result__[170];
    result__[ 177 ] = result__[171];
    result__[ 178 ] = result__[157];
    result__[ 179 ] = result__[158];
    result__[ 180 ] = result__[159];
    result__[ 181 ] = result__[160];
    result__[ 182 ] = result__[161];
    result__[ 183 ] = result__[162];
    result__[ 184 ] = result__[163];
    result__[ 185 ] = result__[164];
    result__[ 186 ] = result__[165];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 187, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: HypersonicProblem3DOF_Methods_Guess.cc
