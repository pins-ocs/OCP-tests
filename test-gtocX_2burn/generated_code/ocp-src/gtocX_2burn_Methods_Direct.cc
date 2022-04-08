/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_Guess.cc                                   |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


using namespace std;

namespace gtocX_2burnDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer gtocX_2burn::fd_ode_numEqns() const { return 6; }

  void
  gtocX_2burn::fd_ode_eval(
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
    real_type QM__[1], XM__[6], V__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    real_type t4   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t5   = XM__[0];
    real_type t6   = sqrt(t5);
    real_type t8   = ModelPars[iM_muS];
    real_type t9   = sqrt(t8);
    real_type t11  = 1.0 / t9 * t6 * t4;
    real_type t13  = XM__[1];
    real_type t14  = XM__[2];
    real_type t15  = XM__[5];
    real_type t16  = ray(t5, t13, t14, t15);
    real_type t17  = acceleration_r(t16, t8);
    real_type t18  = t17 * ModelPars[iM_w_nonlin];
    real_type t19  = sin(t15);
    result__[ 1   ] = -t19 * t18 * t11 + V__[1];
    real_type t23  = cos(t15);
    result__[ 2   ] = t23 * t18 * t11 + V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    real_type t30  = pow(t23 * t13 + t19 * t14 + 1, 2);
    result__[ 5   ] = V__[5] - t9 / t6 / t5 * t30 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::Dfd_odeDxxup_numRows() const { return 6; }
  integer gtocX_2burn::Dfd_odeDxxup_numCols() const { return 12; }
  integer gtocX_2burn::Dfd_odeDxxup_nnz()     const { return 30; }

  void
  gtocX_2burn::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 11  ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 5   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 2   ; jIndex[15] = 7   ;
    iIndex[16] = 2   ; jIndex[16] = 8   ;
    iIndex[17] = 2   ; jIndex[17] = 11  ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 9   ;
    iIndex[20] = 4   ; jIndex[20] = 4   ;
    iIndex[21] = 4   ; jIndex[21] = 10  ;
    iIndex[22] = 5   ; jIndex[22] = 0   ;
    iIndex[23] = 5   ; jIndex[23] = 1   ;
    iIndex[24] = 5   ; jIndex[24] = 2   ;
    iIndex[25] = 5   ; jIndex[25] = 5   ;
    iIndex[26] = 5   ; jIndex[26] = 6   ;
    iIndex[27] = 5   ; jIndex[27] = 7   ;
    iIndex[28] = 5   ; jIndex[28] = 8   ;
    iIndex[29] = 5   ; jIndex[29] = 11  ;
  }


  void
  gtocX_2burn::Dfd_odeDxxup_sparse(
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
    real_type QM__[1], XM__[6], V__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    result__[ 1   ] = __INV_DZETA;
    real_type t3   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t4   = XM__[0];
    real_type t5   = sqrt(t4);
    real_type t8   = ModelPars[iM_muS];
    real_type t9   = sqrt(t8);
    real_type t10  = 1.0 / t9;
    real_type t11  = t10 / t5 * t3;
    real_type t12  = ModelPars[iM_w_nonlin];
    real_type t13  = XM__[1];
    real_type t14  = XM__[2];
    real_type t15  = XM__[5];
    real_type t16  = ray(t4, t13, t14, t15);
    real_type t17  = acceleration_r(t16, t8);
    real_type t18  = t17 * t12;
    real_type t19  = sin(t15);
    real_type t20  = t19 * t18;
    real_type t24  = t10 * t5 * t3;
    real_type t25  = acceleration_r_D_1(t16, t8);
    real_type t26  = t25 * t12;
    real_type t27  = ray_D_1(t4, t13, t14, t15);
    result__[ 2   ] = -0.2500000000e0 * t20 * t11 - 0.5e0 * t19 * t27 * t26 * t24;
    real_type t32  = ray_D_2(t4, t13, t14, t15);
    real_type t36  = 0.5e0 * t19 * t32 * t26 * t24;
    result__[ 3   ] = -t36 + result__[0];
    real_type t37  = ray_D_3(t4, t13, t14, t15);
    result__[ 4   ] = -0.5e0 * t19 * t37 * t26 * t24;
    real_type t42  = ray_D_4(t4, t13, t14, t15);
    real_type t47  = cos(t15);
    real_type t48  = t47 * t18;
    result__[ 5   ] = -0.5e0 * t19 * t42 * t26 * t24 - 0.5e0 * t48 * t24;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = -t36 + __INV_DZETA;
    result__[ 8   ] = result__[4];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = 0.2500000000e0 * t48 * t11 + 0.5e0 * t47 * t27 * t26 * t24;
    result__[ 11  ] = 0.5e0 * t47 * t32 * t26 * t24;
    real_type t63  = 0.5e0 * t47 * t37 * t26 * t24;
    result__[ 12  ] = t63 + result__[0];
    result__[ 13  ] = 0.5e0 * t47 * t42 * t26 * t24 - 0.5e0 * t20 * t24;
    result__[ 14  ] = result__[10];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = t63 + __INV_DZETA;
    result__[ 17  ] = result__[13];
    result__[ 18  ] = result__[0];
    result__[ 19  ] = __INV_DZETA;
    result__[ 20  ] = result__[18];
    result__[ 21  ] = __INV_DZETA;
    real_type t72  = t13 * t47 + t14 * t19 + 1;
    real_type t73  = t72 * t72;
    real_type t75  = t4 * t4;
    result__[ 22  ] = 0.7500000000e0 * t9 / t5 / t75 * t73 * t3;
    real_type t80  = t72 * t3;
    real_type t83  = t9 / t5 / t4;
    result__[ 23  ] = -0.10e1 * t47 * t83 * t80;
    result__[ 24  ] = -0.10e1 * t19 * t83 * t80;
    real_type t95  = 0.10e1 * (-t13 * t19 + t14 * t47) * t83 * t80;
    result__[ 25  ] = -t95 + result__[20];
    result__[ 26  ] = result__[22];
    result__[ 27  ] = result__[23];
    result__[ 28  ] = result__[24];
    result__[ 29  ] = -t95 + __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 30, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2fd_odeD2xxup_numRows() const { return 12; }
  integer gtocX_2burn::D2fd_odeD2xxup_numCols() const { return 12; }
  integer gtocX_2burn::D2fd_odeD2xxup_nnz()     const { return 64; }

  void
  gtocX_2burn::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 11  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 2   ;
    iIndex[11] = 1   ; jIndex[11] = 5   ;
    iIndex[12] = 1   ; jIndex[12] = 6   ;
    iIndex[13] = 1   ; jIndex[13] = 7   ;
    iIndex[14] = 1   ; jIndex[14] = 8   ;
    iIndex[15] = 1   ; jIndex[15] = 11  ;
    iIndex[16] = 2   ; jIndex[16] = 0   ;
    iIndex[17] = 2   ; jIndex[17] = 1   ;
    iIndex[18] = 2   ; jIndex[18] = 2   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
    iIndex[21] = 2   ; jIndex[21] = 7   ;
    iIndex[22] = 2   ; jIndex[22] = 8   ;
    iIndex[23] = 2   ; jIndex[23] = 11  ;
    iIndex[24] = 5   ; jIndex[24] = 0   ;
    iIndex[25] = 5   ; jIndex[25] = 1   ;
    iIndex[26] = 5   ; jIndex[26] = 2   ;
    iIndex[27] = 5   ; jIndex[27] = 5   ;
    iIndex[28] = 5   ; jIndex[28] = 6   ;
    iIndex[29] = 5   ; jIndex[29] = 7   ;
    iIndex[30] = 5   ; jIndex[30] = 8   ;
    iIndex[31] = 5   ; jIndex[31] = 11  ;
    iIndex[32] = 6   ; jIndex[32] = 0   ;
    iIndex[33] = 6   ; jIndex[33] = 1   ;
    iIndex[34] = 6   ; jIndex[34] = 2   ;
    iIndex[35] = 6   ; jIndex[35] = 5   ;
    iIndex[36] = 6   ; jIndex[36] = 6   ;
    iIndex[37] = 6   ; jIndex[37] = 7   ;
    iIndex[38] = 6   ; jIndex[38] = 8   ;
    iIndex[39] = 6   ; jIndex[39] = 11  ;
    iIndex[40] = 7   ; jIndex[40] = 0   ;
    iIndex[41] = 7   ; jIndex[41] = 1   ;
    iIndex[42] = 7   ; jIndex[42] = 2   ;
    iIndex[43] = 7   ; jIndex[43] = 5   ;
    iIndex[44] = 7   ; jIndex[44] = 6   ;
    iIndex[45] = 7   ; jIndex[45] = 7   ;
    iIndex[46] = 7   ; jIndex[46] = 8   ;
    iIndex[47] = 7   ; jIndex[47] = 11  ;
    iIndex[48] = 8   ; jIndex[48] = 0   ;
    iIndex[49] = 8   ; jIndex[49] = 1   ;
    iIndex[50] = 8   ; jIndex[50] = 2   ;
    iIndex[51] = 8   ; jIndex[51] = 5   ;
    iIndex[52] = 8   ; jIndex[52] = 6   ;
    iIndex[53] = 8   ; jIndex[53] = 7   ;
    iIndex[54] = 8   ; jIndex[54] = 8   ;
    iIndex[55] = 8   ; jIndex[55] = 11  ;
    iIndex[56] = 11  ; jIndex[56] = 0   ;
    iIndex[57] = 11  ; jIndex[57] = 1   ;
    iIndex[58] = 11  ; jIndex[58] = 2   ;
    iIndex[59] = 11  ; jIndex[59] = 5   ;
    iIndex[60] = 11  ; jIndex[60] = 6   ;
    iIndex[61] = 11  ; jIndex[61] = 7   ;
    iIndex[62] = 11  ; jIndex[62] = 8   ;
    iIndex[63] = 11  ; jIndex[63] = 11  ;
  }


  void
  gtocX_2burn::D2fd_odeD2xxup_sparse(
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
    real_type QM__[1], XM__[6], V__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    V__[5] = __INV_DZETA*(XR__[5]-XL__[5]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[1];
    real_type t4   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t8   = XR__[iX_p] / 2 + XL__[iX_p] / 2;
    real_type t9   = sqrt(t8);
    real_type t11  = 1.0 / t9 / t8;
    real_type t13  = ModelPars[iM_muS];
    real_type t14  = sqrt(t13);
    real_type t15  = 1.0 / t14;
    real_type t16  = t15 * t11 * t4;
    real_type t17  = ModelPars[iM_w_nonlin];
    real_type t21  = XR__[iX_f] / 2 + XL__[iX_f] / 2;
    real_type t25  = XR__[iX_g] / 2 + XL__[iX_g] / 2;
    real_type t29  = XR__[iX_L] / 2 + XL__[iX_L] / 2;
    real_type t30  = ray(t8, t21, t25, t29);
    real_type t31  = acceleration_r(t30, t13);
    real_type t32  = t31 * t17;
    real_type t33  = sin(t29);
    real_type t34  = t33 * t32;
    real_type t37  = 1.0 / t9;
    real_type t39  = t15 * t37 * t4;
    real_type t40  = acceleration_r_D_1(t30, t13);
    real_type t41  = t40 * t17;
    real_type t42  = ray_D_1(t8, t21, t25, t29);
    real_type t43  = t33 * t42;
    real_type t44  = t43 * t41;
    real_type t47  = t9 * t4;
    real_type t48  = t15 * t47;
    real_type t49  = acceleration_r_D_1_1(t30, t13);
    real_type t50  = t49 * t17;
    real_type t51  = t42 * t42;
    real_type t56  = ray_D_1_1(t8, t21, t25, t29);
    real_type t63  = LM__[2];
    real_type t64  = cos(t29);
    real_type t65  = t64 * t32;
    real_type t68  = t64 * t42;
    real_type t69  = t68 * t41;
    real_type t83  = t4 * LM__[5];
    real_type t84  = t64 * t21;
    real_type t85  = t33 * t25;
    real_type t86  = 1 + t84 + t85;
    real_type t87  = t86 * t86;
    real_type t88  = t8 * t8;
    result__[ 0   ] = (t34 * t16 / 16 - t44 * t39 / 4 - t33 * t51 * t50 * t48 / 4 - t33 * t56 * t41 * t48 / 4) * t1 + (-t65 * t16 / 16 + t69 * t39 / 4 + t64 * t51 * t50 * t48 / 4 + t64 * t56 * t41 * t48 / 4) * t63 - 0.15e2 / 0.16e2 * t14 / t9 / t88 / t8 * t87 * t83;
    real_type t96  = ray_D_2(t8, t21, t25, t29);
    real_type t98  = t33 * t96 * t41;
    real_type t102 = t17 * t15 * t47;
    real_type t103 = t96 * t49;
    real_type t107 = ray_D_1_2(t8, t21, t25, t29);
    real_type t109 = t33 * t107 * t41;
    real_type t115 = t64 * t96 * t41;
    real_type t122 = t64 * t107 * t41;
    real_type t127 = t86 * t83;
    real_type t130 = t14 / t9 / t88;
    real_type t133 = 3.0 / 4.0 * t64 * t130 * t127;
    result__[ 1   ] = (-t98 * t39 / 8 - t43 * t103 * t102 / 4 - t109 * t48 / 4) * t1 + (t115 * t39 / 8 + t68 * t103 * t102 / 4 + t122 * t48 / 4) * t63 + t133;
    real_type t134 = ray_D_3(t8, t21, t25, t29);
    real_type t136 = t33 * t134 * t41;
    real_type t139 = t134 * t49;
    real_type t143 = ray_D_1_3(t8, t21, t25, t29);
    real_type t145 = t33 * t143 * t41;
    real_type t151 = t64 * t134 * t41;
    real_type t158 = t64 * t143 * t41;
    real_type t165 = 3.0 / 4.0 * t33 * t130 * t127;
    result__[ 2   ] = (-t136 * t39 / 8 - t43 * t139 * t102 / 4 - t145 * t48 / 4) * t1 + (t151 * t39 / 8 + t68 * t139 * t102 / 4 + t158 * t48 / 4) * t63 + t165;
    real_type t166 = ray_D_4(t8, t21, t25, t29);
    real_type t167 = t33 * t166;
    real_type t168 = t167 * t41;
    real_type t173 = t166 * t49;
    real_type t177 = ray_D_1_4(t8, t21, t25, t29);
    real_type t186 = t64 * t166;
    real_type t187 = t186 * t41;
    real_type t206 = -t33 * t21 / 2 + t64 * t25 / 2;
    result__[ 3   ] = (-t168 * t39 / 8 - t65 * t39 / 8 - t43 * t173 * t102 / 4 - t33 * t177 * t41 * t48 / 4 - t69 * t48 / 4) * t1 + (t187 * t39 / 8 - t34 * t39 / 8 + t68 * t173 * t102 / 4 + t64 * t177 * t41 * t48 / 4 - t44 * t48 / 4) * t63 + 3.0 / 2.0 * t206 * t130 * t127;
    result__[ 4   ] = result__[0];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    result__[ 8   ] = result__[5];
    real_type t210 = t4 * t1;
    real_type t211 = t15 * t9;
    real_type t212 = t211 * t210;
    real_type t213 = t96 * t96;
    real_type t218 = ray_D_2_2(t8, t21, t25, t29);
    real_type t223 = t4 * t63;
    real_type t224 = t211 * t223;
    real_type t233 = t64 * t64;
    result__[ 9   ] = -t33 * t213 * t50 * t212 / 4 - t33 * t218 * t41 * t212 / 4 + t64 * t213 * t50 * t224 / 4 + t64 * t218 * t41 * t224 / 4 - t14 * t11 * t233 * t83 / 2;
    real_type t238 = t96 * t134;
    real_type t243 = ray_D_2_3(t8, t21, t25, t29);
    real_type t257 = t14 * t11;
    real_type t258 = t64 * t257;
    result__[ 10  ] = -t33 * t238 * t50 * t212 / 4 - t33 * t243 * t41 * t212 / 4 + t64 * t238 * t50 * t224 / 4 + t64 * t243 * t41 * t224 / 4 - t258 * t33 * t83 / 2;
    real_type t261 = t96 * t166;
    real_type t266 = ray_D_2_4(t8, t21, t25, t29);
    real_type t268 = t33 * t266 * t41;
    real_type t278 = t64 * t266 * t41;
    real_type t283 = t206 * t83;
    real_type t284 = t258 * t283;
    real_type t285 = t33 * t257;
    real_type t287 = t285 * t127 / 2;
    result__[ 11  ] = -t33 * t261 * t50 * t212 / 4 - t268 * t212 / 4 - t115 * t212 / 4 + t64 * t261 * t50 * t224 / 4 + t278 * t224 / 4 - t98 * t224 / 4 - t284 + t287;
    real_type t288 = t15 * t37;
    real_type t289 = t288 * t210;
    real_type t292 = t96 * t42;
    real_type t299 = t288 * t223;
    result__[ 12  ] = -t98 * t289 / 8 - t33 * t292 * t50 * t212 / 4 - t109 * t212 / 4 + t115 * t299 / 8 + t64 * t292 * t50 * t224 / 4 + t122 * t224 / 4 + t133;
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[10];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = result__[6];
    result__[ 17  ] = result__[14];
    real_type t308 = t134 * t134;
    real_type t313 = ray_D_3_3(t8, t21, t25, t29);
    real_type t326 = t33 * t33;
    result__[ 18  ] = -t33 * t308 * t50 * t212 / 4 - t33 * t313 * t41 * t212 / 4 + t64 * t308 * t50 * t224 / 4 + t64 * t313 * t41 * t224 / 4 - t14 * t11 * t326 * t83 / 2;
    real_type t331 = t134 * t166;
    real_type t336 = ray_D_3_4(t8, t21, t25, t29);
    real_type t338 = t33 * t336 * t41;
    real_type t348 = t64 * t336 * t41;
    real_type t353 = t285 * t283;
    real_type t355 = t258 * t127 / 2;
    result__[ 19  ] = -t33 * t331 * t50 * t212 / 4 - t338 * t212 / 4 - t151 * t212 / 4 + t64 * t331 * t50 * t224 / 4 + t348 * t224 / 4 - t136 * t224 / 4 - t353 - t355;
    real_type t358 = t134 * t42;
    result__[ 20  ] = -t136 * t289 / 8 - t33 * t358 * t50 * t212 / 4 - t145 * t212 / 4 + t151 * t299 / 8 + t64 * t358 * t50 * t224 / 4 + t158 * t224 / 4 + t165;
    result__[ 21  ] = result__[17];
    result__[ 22  ] = result__[18];
    result__[ 23  ] = result__[19];
    result__[ 24  ] = result__[7];
    result__[ 25  ] = result__[15];
    result__[ 26  ] = result__[23];
    real_type t373 = t166 * t166;
    real_type t378 = ray_D_4_4(t8, t21, t25, t29);
    real_type t403 = t206 * t206;
    result__[ 27  ] = (-t33 * t373 * t50 * t48 / 4 - t33 * t378 * t41 * t48 / 4 - t187 * t48 / 2 + t34 * t48 / 4) * t1 + (t64 * t373 * t50 * t48 / 4 + t64 * t378 * t41 * t48 / 4 - t168 * t48 / 2 - t65 * t48 / 4) * t63 - 2 * t14 * t11 * t403 * t83 - 2 * (-t84 / 4 - t85 / 4) * t257 * t127;
    result__[ 28  ] = result__[24];
    result__[ 29  ] = (-t167 * t103 * t102 / 4 - t115 * t48 / 4 - t268 * t48 / 4) * t1 + (t186 * t103 * t102 / 4 + t278 * t48 / 4 - t98 * t48 / 4) * t63 - t284 + t287;
    result__[ 30  ] = (-t167 * t139 * t102 / 4 - t151 * t48 / 4 - t338 * t48 / 4) * t1 + (t186 * t139 * t102 / 4 - t136 * t48 / 4 + t348 * t48 / 4) * t63 - t353 - t355;
    result__[ 31  ] = result__[27];
    result__[ 32  ] = result__[4];
    result__[ 33  ] = result__[12];
    result__[ 34  ] = result__[20];
    result__[ 35  ] = result__[28];
    result__[ 36  ] = result__[32];
    result__[ 37  ] = result__[8];
    result__[ 38  ] = result__[16];
    result__[ 39  ] = result__[35];
    result__[ 40  ] = result__[37];
    result__[ 41  ] = result__[13];
    result__[ 42  ] = result__[21];
    result__[ 43  ] = result__[29];
    result__[ 44  ] = result__[40];
    result__[ 45  ] = result__[41];
    result__[ 46  ] = result__[42];
    result__[ 47  ] = result__[25];
    result__[ 48  ] = result__[38];
    result__[ 49  ] = result__[46];
    result__[ 50  ] = result__[22];
    result__[ 51  ] = result__[30];
    result__[ 52  ] = result__[48];
    result__[ 53  ] = result__[49];
    result__[ 54  ] = result__[50];
    result__[ 55  ] = result__[26];
    result__[ 56  ] = result__[39];
    result__[ 57  ] = result__[47];
    result__[ 58  ] = result__[55];
    result__[ 59  ] = result__[31];
    result__[ 60  ] = result__[56];
    result__[ 61  ] = result__[57];
    result__[ 62  ] = result__[58];
    result__[ 63  ] = result__[59];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 64, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: gtocX_2burn_Methods_Guess.cc
