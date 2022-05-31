/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_Guess.cc                                    |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace HangGliderDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer HangGlider::fd_ode_numEqns() const { return 4; }

  void
  HangGlider::fd_ode_eval(
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
    real_type QM__[1], XM__[4], V__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = XM__[2];
    result__[ 0   ] = -t2 * t1 + V__[0];
    real_type t5   = XM__[3];
    result__[ 1   ] = -t5 * t1 + V__[1];
    real_type t11  = 1.0 / ModelPars[iM_m] * t1;
    real_type t12  = XM__[0];
    real_type t13  = v(t12, t2, t5);
    real_type t14  = 1.0 / t13;
    real_type t15  = UM__[0];
    real_type t16  = t15 * t15;
    real_type t21  = Dfun(t12, t2, t5);
    real_type t22  = t21 * (ModelPars[iM_c1] * t16 + ModelPars[iM_c0]);
    real_type t24  = Lfun(t12, t2, t5);
    real_type t25  = t24 * t15;
    real_type t26  = w(t12, t5);
    result__[ 2   ] = V__[2] - (-t2 * t22 - t26 * t25) * t14 * t11;
    result__[ 3   ] = V__[3] - (t2 * t25 - t26 * t22) * t14 * t11 + ModelPars[iM_g] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::Dfd_odeDxxpu_numRows() const { return 4; }
  integer HangGlider::Dfd_odeDxxpu_numCols() const { return 10; }
  integer HangGlider::Dfd_odeDxxpu_nnz()     const { return 26; }

  void
  HangGlider::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 9   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 7   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 9   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 2   ;
    iIndex[12] = 2   ; jIndex[12] = 3   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 2   ; jIndex[15] = 7   ;
    iIndex[16] = 2   ; jIndex[16] = 8   ;
    iIndex[17] = 2   ; jIndex[17] = 9   ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 2   ;
    iIndex[20] = 3   ; jIndex[20] = 3   ;
    iIndex[21] = 3   ; jIndex[21] = 4   ;
    iIndex[22] = 3   ; jIndex[22] = 6   ;
    iIndex[23] = 3   ; jIndex[23] = 7   ;
    iIndex[24] = 3   ; jIndex[24] = 8   ;
    iIndex[25] = 3   ; jIndex[25] = 9   ;
  }


  void
  HangGlider::Dfd_odeDxxpu_sparse(
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
    real_type QM__[1], XM__[4], V__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    real_type t1   = P__[iP_T];
    result__[ 1   ] = -0.5e0 * t1;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = result__[1];
    real_type t3   = XM__[2];
    result__[ 4   ] = -t3;
    result__[ 5   ] = result__[0];
    result__[ 6   ] = result__[3];
    result__[ 7   ] = __INV_DZETA;
    result__[ 8   ] = result__[6];
    real_type t4   = XM__[3];
    result__[ 9   ] = -t4;
    real_type t6   = 1.0 / ModelPars[iM_m];
    real_type t7   = t6 * t1;
    real_type t8   = XM__[0];
    real_type t9   = v(t8, t3, t4);
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t12  = UM__[0];
    real_type t13  = t12 * t12;
    real_type t14  = ModelPars[iM_c1];
    real_type t17  = t14 * t13 + ModelPars[iM_c0];
    real_type t18  = Dfun(t8, t3, t4);
    real_type t19  = t18 * t17;
    real_type t21  = Lfun(t8, t3, t4);
    real_type t22  = t21 * t12;
    real_type t23  = w(t8, t4);
    real_type t25  = -t3 * t19 - t23 * t22;
    real_type t26  = t25 * t11;
    real_type t27  = v_D_1(t8, t3, t4);
    real_type t31  = 1.0 / t9;
    real_type t32  = Dfun_D_1(t8, t3, t4);
    real_type t33  = t32 * t17;
    real_type t35  = Lfun_D_1(t8, t3, t4);
    real_type t36  = t35 * t12;
    real_type t38  = w_D_1(t8, t4);
    result__[ 10  ] = 0.5e0 * t27 * t26 * t7 - 0.5e0 * (-t38 * t22 - t23 * t36 - t3 * t33) * t31 * t7;
    real_type t44  = v_D_2(t8, t3, t4);
    real_type t47  = 0.5e0 * t44 * t26 * t7;
    real_type t48  = Dfun_D_2(t8, t3, t4);
    real_type t49  = t48 * t17;
    real_type t51  = Lfun_D_2(t8, t3, t4);
    real_type t52  = t51 * t12;
    real_type t57  = 0.5e0 * (-t23 * t52 - t3 * t49 - t19) * t31 * t7;
    result__[ 11  ] = t47 - t57 + result__[5];
    real_type t58  = v_D_3(t8, t3, t4);
    real_type t62  = Dfun_D_3(t8, t3, t4);
    real_type t63  = t62 * t17;
    real_type t65  = Lfun_D_3(t8, t3, t4);
    real_type t66  = t65 * t12;
    real_type t68  = w_D_2(t8, t4);
    result__[ 12  ] = 0.5e0 * t58 * t26 * t7 - 0.5e0 * (-t68 * t22 - t23 * t66 - t3 * t63) * t31 * t7;
    result__[ 13  ] = result__[10];
    result__[ 14  ] = t47 - t57 + __INV_DZETA;
    result__[ 15  ] = result__[12];
    real_type t74  = t12 * t14;
    result__[ 16  ] = -(-2 * t3 * t18 * t74 - t23 * t21) * t31 * t7;
    real_type t82  = t31 * t6;
    result__[ 17  ] = -t25 * t82;
    real_type t86  = -t23 * t19 + t3 * t22;
    real_type t87  = t86 * t11;
    result__[ 18  ] = 0.5e0 * t27 * t87 * t7 - 0.5e0 * (-t38 * t19 - t23 * t33 + t3 * t36) * t31 * t7;
    result__[ 19  ] = 0.5e0 * t44 * t87 * t7 - 0.5e0 * (-t23 * t49 + t3 * t52 + t22) * t31 * t7;
    real_type t109 = 0.5e0 * t58 * t87 * t7;
    real_type t116 = 0.5e0 * (-t68 * t19 - t23 * t63 + t3 * t66) * t31 * t7;
    result__[ 20  ] = t109 - t116 + result__[5];
    result__[ 21  ] = result__[18];
    result__[ 22  ] = result__[19];
    result__[ 23  ] = t109 - t116 + __INV_DZETA;
    result__[ 24  ] = -(-2 * t23 * t18 * t74 + t3 * t21) * t31 * t7;
    result__[ 25  ] = -t86 * t82 + ModelPars[iM_g];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 26, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::D2fd_odeD2xxpu_numRows() const { return 10; }
  integer HangGlider::D2fd_odeD2xxpu_numCols() const { return 10; }
  integer HangGlider::D2fd_odeD2xxpu_nnz()     const { return 63; }

  void
  HangGlider::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 2   ; jIndex[11] = 4   ;
    iIndex[12] = 2   ; jIndex[12] = 6   ;
    iIndex[13] = 2   ; jIndex[13] = 7   ;
    iIndex[14] = 2   ; jIndex[14] = 8   ;
    iIndex[15] = 2   ; jIndex[15] = 9   ;
    iIndex[16] = 3   ; jIndex[16] = 0   ;
    iIndex[17] = 3   ; jIndex[17] = 2   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 3   ; jIndex[20] = 6   ;
    iIndex[21] = 3   ; jIndex[21] = 7   ;
    iIndex[22] = 3   ; jIndex[22] = 8   ;
    iIndex[23] = 3   ; jIndex[23] = 9   ;
    iIndex[24] = 4   ; jIndex[24] = 0   ;
    iIndex[25] = 4   ; jIndex[25] = 2   ;
    iIndex[26] = 4   ; jIndex[26] = 3   ;
    iIndex[27] = 4   ; jIndex[27] = 4   ;
    iIndex[28] = 4   ; jIndex[28] = 6   ;
    iIndex[29] = 4   ; jIndex[29] = 7   ;
    iIndex[30] = 4   ; jIndex[30] = 8   ;
    iIndex[31] = 4   ; jIndex[31] = 9   ;
    iIndex[32] = 6   ; jIndex[32] = 0   ;
    iIndex[33] = 6   ; jIndex[33] = 2   ;
    iIndex[34] = 6   ; jIndex[34] = 3   ;
    iIndex[35] = 6   ; jIndex[35] = 4   ;
    iIndex[36] = 6   ; jIndex[36] = 6   ;
    iIndex[37] = 6   ; jIndex[37] = 7   ;
    iIndex[38] = 6   ; jIndex[38] = 8   ;
    iIndex[39] = 6   ; jIndex[39] = 9   ;
    iIndex[40] = 7   ; jIndex[40] = 0   ;
    iIndex[41] = 7   ; jIndex[41] = 2   ;
    iIndex[42] = 7   ; jIndex[42] = 3   ;
    iIndex[43] = 7   ; jIndex[43] = 4   ;
    iIndex[44] = 7   ; jIndex[44] = 6   ;
    iIndex[45] = 7   ; jIndex[45] = 7   ;
    iIndex[46] = 7   ; jIndex[46] = 8   ;
    iIndex[47] = 7   ; jIndex[47] = 9   ;
    iIndex[48] = 8   ; jIndex[48] = 0   ;
    iIndex[49] = 8   ; jIndex[49] = 2   ;
    iIndex[50] = 8   ; jIndex[50] = 3   ;
    iIndex[51] = 8   ; jIndex[51] = 4   ;
    iIndex[52] = 8   ; jIndex[52] = 6   ;
    iIndex[53] = 8   ; jIndex[53] = 7   ;
    iIndex[54] = 8   ; jIndex[54] = 8   ;
    iIndex[55] = 8   ; jIndex[55] = 9   ;
    iIndex[56] = 9   ; jIndex[56] = 0   ;
    iIndex[57] = 9   ; jIndex[57] = 2   ;
    iIndex[58] = 9   ; jIndex[58] = 3   ;
    iIndex[59] = 9   ; jIndex[59] = 4   ;
    iIndex[60] = 9   ; jIndex[60] = 6   ;
    iIndex[61] = 9   ; jIndex[61] = 7   ;
    iIndex[62] = 9   ; jIndex[62] = 8   ;
  }


  void
  HangGlider::D2fd_odeD2xxpu_sparse(
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
    real_type QM__[1], XM__[4], V__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[2];
    real_type t2   = P__[iP_T];
    real_type t4   = 1.0 / ModelPars[iM_m];
    real_type t5   = t4 * t2;
    real_type t9   = XR__[iX_x] / 2 + XL__[iX_x] / 2;
    real_type t13  = XR__[iX_vx] / 2 + XL__[iX_vx] / 2;
    real_type t17  = XR__[iX_vy] / 2 + XL__[iX_vy] / 2;
    real_type t18  = v(t9, t13, t17);
    real_type t19  = t18 * t18;
    real_type t21  = 1.0 / t19 / t18;
    real_type t22  = UM__[0];
    real_type t23  = t22 * t22;
    real_type t24  = ModelPars[iM_c1];
    real_type t27  = t24 * t23 + ModelPars[iM_c0];
    real_type t28  = Dfun(t9, t13, t17);
    real_type t29  = t28 * t27;
    real_type t31  = Lfun(t9, t13, t17);
    real_type t32  = t31 * t22;
    real_type t33  = w(t9, t17);
    real_type t35  = -t13 * t29 - t33 * t32;
    real_type t36  = t35 * t21;
    real_type t37  = v_D_1(t9, t13, t17);
    real_type t38  = t37 * t37;
    real_type t42  = 1.0 / t19;
    real_type t43  = Dfun_D_1(t9, t13, t17);
    real_type t44  = t43 * t27;
    real_type t46  = Lfun_D_1(t9, t13, t17);
    real_type t47  = t46 * t22;
    real_type t49  = w_D_1(t9, t17);
    real_type t52  = -t13 * t44 / 2 - t49 * t32 / 2 - t33 * t47 / 2;
    real_type t53  = t52 * t42;
    real_type t56  = t35 * t42;
    real_type t57  = v_D_1_1(t9, t13, t17);
    real_type t61  = 1.0 / t18;
    real_type t62  = Dfun_D_1_1(t9, t13, t17);
    real_type t63  = t62 * t27;
    real_type t66  = Lfun_D_1_1(t9, t13, t17);
    real_type t67  = t66 * t22;
    real_type t72  = w_D_1_1(t9, t17);
    real_type t80  = LM__[3];
    real_type t83  = t13 * t32 - t33 * t29;
    real_type t84  = t83 * t21;
    real_type t92  = t13 * t47 / 2 - t49 * t29 / 2 - t33 * t44 / 2;
    real_type t93  = t92 * t42;
    real_type t96  = t83 * t42;
    result__[ 0   ] = (-t38 * t36 * t5 / 2 + t37 * t53 * t5 + t57 * t56 * t5 / 4 - (-t13 * t63 / 4 - t33 * t67 / 4 - t49 * t47 / 2 - t72 * t32 / 4) * t61 * t5) * t1 + (-t38 * t84 * t5 / 2 + t37 * t93 * t5 + t57 * t96 * t5 / 4 - (-t33 * t63 / 4 - t49 * t44 / 2 - t72 * t29 / 4 + t13 * t67 / 4) * t61 * t5) * t80;
    real_type t113 = t21 * t5;
    real_type t114 = t37 * t35;
    real_type t115 = v_D_2(t9, t13, t17);
    real_type t119 = Dfun_D_2(t9, t13, t17);
    real_type t120 = t119 * t27;
    real_type t122 = Lfun_D_2(t9, t13, t17);
    real_type t123 = t122 * t22;
    real_type t126 = -t13 * t120 / 2 - t33 * t123 / 2 - t29 / 2;
    real_type t127 = t126 * t42;
    real_type t131 = v_D_1_2(t9, t13, t17);
    real_type t138 = Dfun_D_1_2(t9, t13, t17);
    real_type t139 = t138 * t27;
    real_type t141 = Lfun_D_1_2(t9, t13, t17);
    real_type t142 = t141 * t22;
    real_type t151 = t37 * t83;
    real_type t158 = -t33 * t120 / 2 + t13 * t123 / 2 + t32 / 2;
    real_type t159 = t158 * t42;
    result__[ 1   ] = (-t115 * t114 * t113 / 2 + t37 * t127 * t5 / 2 + t131 * t56 * t5 / 4 + t115 * t53 * t5 / 2 - (-t49 * t123 / 4 - t13 * t139 / 4 - t33 * t142 / 4 - t44 / 4) * t61 * t5) * t1 + (-t115 * t151 * t113 / 2 + t37 * t159 * t5 / 2 + t131 * t96 * t5 / 4 + t115 * t93 * t5 / 2 - (-t49 * t120 / 4 + t13 * t142 / 4 - t33 * t139 / 4 + t47 / 4) * t61 * t5) * t80;
    real_type t178 = v_D_3(t9, t13, t17);
    real_type t182 = Dfun_D_3(t9, t13, t17);
    real_type t183 = t182 * t27;
    real_type t185 = Lfun_D_3(t9, t13, t17);
    real_type t186 = t185 * t22;
    real_type t188 = w_D_2(t9, t17);
    real_type t191 = -t13 * t183 / 2 - t33 * t186 / 2 - t188 * t32 / 2;
    real_type t192 = t191 * t42;
    real_type t196 = v_D_1_3(t9, t13, t17);
    real_type t203 = Dfun_D_1_3(t9, t13, t17);
    real_type t204 = t203 * t27;
    real_type t206 = Lfun_D_1_3(t9, t13, t17);
    real_type t207 = t206 * t22;
    real_type t211 = w_D_1_2(t9, t17);
    real_type t226 = t13 * t186 / 2 - t33 * t183 / 2 - t188 * t29 / 2;
    real_type t227 = t226 * t42;
    result__[ 2   ] = (-t178 * t114 * t113 / 2 + t37 * t192 * t5 / 2 + t196 * t56 * t5 / 4 + t178 * t53 * t5 / 2 - (-t13 * t204 / 4 - t49 * t186 / 4 - t188 * t47 / 4 - t33 * t207 / 4 - t211 * t32 / 4) * t61 * t5) * t1 + (-t178 * t151 * t113 / 2 + t37 * t227 * t5 / 2 + t196 * t96 * t5 / 4 + t178 * t93 * t5 / 2 - (t13 * t207 / 4 - t49 * t183 / 4 - t188 * t44 / 4 - t33 * t204 / 4 - t211 * t29 / 4) * t61 * t5) * t80;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t248 = t22 * t24;
    real_type t249 = t13 * t28;
    real_type t253 = -2 * t248 * t249 - t31 * t33;
    real_type t254 = t253 * t42;
    real_type t269 = t33 * t28;
    real_type t273 = t13 * t31 - 2 * t248 * t269;
    real_type t274 = t273 * t42;
    result__[ 6   ] = (t37 * t254 * t5 / 2 - (-t13 * t43 * t248 - t33 * t46 / 2 - t49 * t31 / 2) * t61 * t5) * t1 + (t37 * t274 * t5 / 2 - (-t33 * t43 * t248 - t49 * t28 * t248 + t13 * t46 / 2) * t61 * t5) * t80;
    real_type t289 = t42 * t4;
    real_type t292 = t61 * t4;
    result__[ 7   ] = (t114 * t289 / 2 - t52 * t292) * t1 + (t151 * t289 / 2 - t92 * t292) * t80;
    result__[ 8   ] = result__[4];
    real_type t301 = t115 * t115;
    real_type t307 = v_D_2_2(t9, t13, t17);
    real_type t311 = Dfun_D_2_2(t9, t13, t17);
    real_type t312 = t311 * t27;
    real_type t316 = Lfun_D_2_2(t9, t13, t17);
    real_type t317 = t316 * t22;
    result__[ 9   ] = (-t301 * t36 * t5 / 2 + t115 * t127 * t5 + t307 * t56 * t5 / 4 - (-t13 * t312 / 4 - t120 / 2 - t33 * t317 / 4) * t61 * t5) * t1 + (-t301 * t84 * t5 / 2 + t115 * t159 * t5 + t307 * t96 * t5 / 4 - (-t33 * t312 / 4 + t13 * t317 / 4 + t123 / 2) * t61 * t5) * t80;
    real_type t343 = t115 * t35;
    real_type t350 = v_D_2_3(t9, t13, t17);
    real_type t357 = Dfun_D_2_3(t9, t13, t17);
    real_type t358 = t357 * t27;
    real_type t360 = Lfun_D_2_3(t9, t13, t17);
    real_type t361 = t360 * t22;
    real_type t370 = t115 * t83;
    result__[ 10  ] = (-t178 * t343 * t113 / 2 + t115 * t192 * t5 / 2 + t350 * t56 * t5 / 4 + t178 * t127 * t5 / 2 - (-t188 * t123 / 4 - t13 * t358 / 4 - t33 * t361 / 4 - t183 / 4) * t61 * t5) * t1 + (-t178 * t370 * t113 / 2 + t115 * t227 * t5 / 2 + t350 * t96 * t5 / 4 + t178 * t159 * t5 / 2 - (-t188 * t120 / 4 + t13 * t361 / 4 - t33 * t358 / 4 + t186 / 4) * t61 * t5) * t80;
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = result__[10];
    result__[ 14  ] = (t115 * t254 * t5 / 2 - (-t13 * t119 * t248 - t28 * t248 - t33 * t122 / 2) * t61 * t5) * t1 + (t115 * t274 * t5 / 2 - (-t33 * t119 * t248 + t13 * t122 / 2 + t31 / 2) * t61 * t5) * t80;
    result__[ 15  ] = -LM__[0] / 2 + (t343 * t289 / 2 - t126 * t292) * t1 + (t370 * t289 / 2 - t158 * t292) * t80;
    result__[ 16  ] = result__[5];
    result__[ 17  ] = result__[13];
    real_type t430 = t178 * t178;
    real_type t436 = v_D_3_3(t9, t13, t17);
    real_type t440 = Dfun_D_3_3(t9, t13, t17);
    real_type t441 = t440 * t27;
    real_type t444 = Lfun_D_3_3(t9, t13, t17);
    real_type t445 = t444 * t22;
    real_type t450 = w_D_2_2(t9, t17);
    result__[ 18  ] = (-t430 * t36 * t5 / 2 + t178 * t192 * t5 + t436 * t56 * t5 / 4 - (-t13 * t441 / 4 - t33 * t445 / 4 - t188 * t186 / 2 - t450 * t32 / 4) * t61 * t5) * t1 + (-t430 * t84 * t5 / 2 + t178 * t227 * t5 + t436 * t96 * t5 / 4 - (-t33 * t441 / 4 - t188 * t183 / 2 - t450 * t29 / 4 + t13 * t445 / 4) * t61 * t5) * t80;
    result__[ 19  ] = result__[16];
    result__[ 20  ] = result__[17];
    result__[ 21  ] = result__[18];
    result__[ 22  ] = (t178 * t254 * t5 / 2 - (-t13 * t182 * t248 - t33 * t185 / 2 - t188 * t31 / 2) * t61 * t5) * t1 + (t178 * t274 * t5 / 2 - (-t33 * t182 * t248 - t188 * t28 * t248 + t13 * t185 / 2) * t61 * t5) * t80;
    result__[ 23  ] = -LM__[1] / 2 + (t178 * t35 * t289 / 2 - t191 * t292) * t1 + (t178 * t83 * t289 / 2 - t226 * t292) * t80;
    result__[ 24  ] = result__[3];
    result__[ 25  ] = result__[11];
    result__[ 26  ] = result__[19];
    result__[ 27  ] = result__[24];
    result__[ 28  ] = result__[25];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[6];
    result__[ 31  ] = result__[7];
    result__[ 32  ] = result__[28];
    result__[ 33  ] = result__[12];
    result__[ 34  ] = result__[20];
    result__[ 35  ] = result__[32];
    result__[ 36  ] = result__[33];
    result__[ 37  ] = result__[34];
    result__[ 38  ] = result__[14];
    result__[ 39  ] = result__[15];
    result__[ 40  ] = result__[29];
    result__[ 41  ] = result__[37];
    result__[ 42  ] = result__[21];
    result__[ 43  ] = result__[40];
    result__[ 44  ] = result__[41];
    result__[ 45  ] = result__[42];
    result__[ 46  ] = result__[22];
    result__[ 47  ] = result__[23];
    result__[ 48  ] = result__[30];
    result__[ 49  ] = result__[38];
    result__[ 50  ] = result__[46];
    result__[ 51  ] = result__[48];
    result__[ 52  ] = result__[49];
    result__[ 53  ] = result__[50];
    real_type t523 = t24 * t61;
    result__[ 54  ] = 2 * t1 * t2 * t249 * t4 * t523 + 2 * t2 * t269 * t4 * t523 * t80;
    result__[ 55  ] = -t1 * t253 * t4 * t61 - t273 * t4 * t61 * t80;
    result__[ 56  ] = result__[31];
    result__[ 57  ] = result__[39];
    result__[ 58  ] = result__[47];
    result__[ 59  ] = result__[56];
    result__[ 60  ] = result__[57];
    result__[ 61  ] = result__[58];
    result__[ 62  ] = result__[55];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 63, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: HangGlider_Methods_Guess.cc
