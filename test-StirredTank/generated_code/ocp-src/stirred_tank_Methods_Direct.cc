/*-----------------------------------------------------------------------*\
 |  file: stirred_tank_Methods_Guess.cc                                  |
 |                                                                       |
 |  version: 1.0   date 20/1/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "stirred_tank.hh"
#include "stirred_tank_Pars.hh"

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
#define ALIAS_u4Control_D_3(__t1, __t2, __t3) u4Control.D_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2(__t1, __t2, __t3) u4Control.D_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1(__t1, __t2, __t3) u4Control.D_1( __t1, __t2, __t3)
#define ALIAS_u4Control_D_3_3(__t1, __t2, __t3) u4Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_3(__t1, __t2, __t3) u4Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_2_2(__t1, __t2, __t3) u4Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_3(__t1, __t2, __t3) u4Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_2(__t1, __t2, __t3) u4Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u4Control_D_1_1(__t1, __t2, __t3) u4Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
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


using namespace std;

namespace stirred_tankDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer stirred_tank::fd_ode_numEqns() const { return 8; }

  void
  stirred_tank::fd_ode_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    U_const_p_type UM__,
    real_ptr       result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[8];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[8];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;
    V__[2] = (XR__[2]-XL__[2])/DZETA__xo;
    V__[3] = (XR__[3]-XL__[3])/DZETA__xo;
    V__[4] = (XR__[4]-XL__[4])/DZETA__xo;
    V__[5] = (XR__[5]-XL__[5])/DZETA__xo;
    V__[6] = (XR__[6]-XL__[6])/DZETA__xo;
    V__[7] = (XR__[7]-XL__[7])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[3];
    real_type t3   = UM__[0];
    real_type t4   = UM__[1];
    real_type t5   = t2 + t3 + t4;
    real_type t6   = XM__[0];
    real_type t7   = t6 * t5;
    real_type t8   = XM__[1];
    real_type t9   = t8 * t6;
    real_type t10  = 0.176e2 * t9;
    real_type t11  = XM__[5];
    real_type t13  = UM__[2];
    real_type t14  = t13 * t11 * t6;
    real_type t15  = 23 * t14;
    result__[ 0   ] = V__[0] - t2 + t7 + t10 + t15;
    real_type t18  = XM__[2];
    real_type t19  = t18 * t8;
    result__[ 1   ] = t8 * t5 + t10 + 146 * t19 - t3 + V__[1];
    result__[ 2   ] = t18 * t5 + 73 * t19 - t4 + V__[2];
    real_type t25  = XM__[3];
    real_type t28  = XM__[4];
    real_type t29  = t28 * t25;
    real_type t30  = 0.513e2 * t29;
    result__[ 3   ] = V__[3] + t25 * t5 - 0.352e2 * t9 + t30;
    result__[ 4   ] = t28 * t5 - 219 * t19 + t30 + V__[4];
    result__[ 5   ] = t11 * t5 + t15 - 102 * t29 + V__[5];
    real_type t38  = XM__[6];
    result__[ 6   ] = t38 * t5 - 46 * t14 + V__[6];
    real_type t52  = t13 * t13;
    result__[ 7   ] = V__[7] - 0.58e1 * t7 + 0.58e1 * t2 + 0.37e1 * t3 + 0.41e1 * t4 - (23 * t25 + 11 * t28 + 28 * t11 + 35 * t38) * t5 + 5 * t52 + 0.9e-1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::Dfd_odeDxxpu_numRows() const { return 8; }
  integer stirred_tank::Dfd_odeDxxpu_numCols() const { return 20; }
  integer stirred_tank::Dfd_odeDxxpu_nnz()     const { return 86; }

  void
  stirred_tank::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 9   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 16  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 17  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 18  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 19  ;
    iIndex[10] = 1   ; jIndex[10] = 0   ;
    iIndex[11] = 1   ; jIndex[11] = 1   ;
    iIndex[12] = 1   ; jIndex[12] = 2   ;
    iIndex[13] = 1   ; jIndex[13] = 8   ;
    iIndex[14] = 1   ; jIndex[14] = 9   ;
    iIndex[15] = 1   ; jIndex[15] = 10  ;
    iIndex[16] = 1   ; jIndex[16] = 16  ;
    iIndex[17] = 1   ; jIndex[17] = 17  ;
    iIndex[18] = 1   ; jIndex[18] = 19  ;
    iIndex[19] = 2   ; jIndex[19] = 1   ;
    iIndex[20] = 2   ; jIndex[20] = 2   ;
    iIndex[21] = 2   ; jIndex[21] = 9   ;
    iIndex[22] = 2   ; jIndex[22] = 10  ;
    iIndex[23] = 2   ; jIndex[23] = 16  ;
    iIndex[24] = 2   ; jIndex[24] = 17  ;
    iIndex[25] = 2   ; jIndex[25] = 19  ;
    iIndex[26] = 3   ; jIndex[26] = 0   ;
    iIndex[27] = 3   ; jIndex[27] = 1   ;
    iIndex[28] = 3   ; jIndex[28] = 3   ;
    iIndex[29] = 3   ; jIndex[29] = 4   ;
    iIndex[30] = 3   ; jIndex[30] = 8   ;
    iIndex[31] = 3   ; jIndex[31] = 9   ;
    iIndex[32] = 3   ; jIndex[32] = 11  ;
    iIndex[33] = 3   ; jIndex[33] = 12  ;
    iIndex[34] = 3   ; jIndex[34] = 16  ;
    iIndex[35] = 3   ; jIndex[35] = 17  ;
    iIndex[36] = 3   ; jIndex[36] = 19  ;
    iIndex[37] = 4   ; jIndex[37] = 1   ;
    iIndex[38] = 4   ; jIndex[38] = 2   ;
    iIndex[39] = 4   ; jIndex[39] = 3   ;
    iIndex[40] = 4   ; jIndex[40] = 4   ;
    iIndex[41] = 4   ; jIndex[41] = 9   ;
    iIndex[42] = 4   ; jIndex[42] = 10  ;
    iIndex[43] = 4   ; jIndex[43] = 11  ;
    iIndex[44] = 4   ; jIndex[44] = 12  ;
    iIndex[45] = 4   ; jIndex[45] = 16  ;
    iIndex[46] = 4   ; jIndex[46] = 17  ;
    iIndex[47] = 4   ; jIndex[47] = 19  ;
    iIndex[48] = 5   ; jIndex[48] = 0   ;
    iIndex[49] = 5   ; jIndex[49] = 3   ;
    iIndex[50] = 5   ; jIndex[50] = 4   ;
    iIndex[51] = 5   ; jIndex[51] = 5   ;
    iIndex[52] = 5   ; jIndex[52] = 8   ;
    iIndex[53] = 5   ; jIndex[53] = 11  ;
    iIndex[54] = 5   ; jIndex[54] = 12  ;
    iIndex[55] = 5   ; jIndex[55] = 13  ;
    iIndex[56] = 5   ; jIndex[56] = 16  ;
    iIndex[57] = 5   ; jIndex[57] = 17  ;
    iIndex[58] = 5   ; jIndex[58] = 18  ;
    iIndex[59] = 5   ; jIndex[59] = 19  ;
    iIndex[60] = 6   ; jIndex[60] = 0   ;
    iIndex[61] = 6   ; jIndex[61] = 5   ;
    iIndex[62] = 6   ; jIndex[62] = 6   ;
    iIndex[63] = 6   ; jIndex[63] = 8   ;
    iIndex[64] = 6   ; jIndex[64] = 13  ;
    iIndex[65] = 6   ; jIndex[65] = 14  ;
    iIndex[66] = 6   ; jIndex[66] = 16  ;
    iIndex[67] = 6   ; jIndex[67] = 17  ;
    iIndex[68] = 6   ; jIndex[68] = 18  ;
    iIndex[69] = 6   ; jIndex[69] = 19  ;
    iIndex[70] = 7   ; jIndex[70] = 0   ;
    iIndex[71] = 7   ; jIndex[71] = 3   ;
    iIndex[72] = 7   ; jIndex[72] = 4   ;
    iIndex[73] = 7   ; jIndex[73] = 5   ;
    iIndex[74] = 7   ; jIndex[74] = 6   ;
    iIndex[75] = 7   ; jIndex[75] = 7   ;
    iIndex[76] = 7   ; jIndex[76] = 8   ;
    iIndex[77] = 7   ; jIndex[77] = 11  ;
    iIndex[78] = 7   ; jIndex[78] = 12  ;
    iIndex[79] = 7   ; jIndex[79] = 13  ;
    iIndex[80] = 7   ; jIndex[80] = 14  ;
    iIndex[81] = 7   ; jIndex[81] = 15  ;
    iIndex[82] = 7   ; jIndex[82] = 16  ;
    iIndex[83] = 7   ; jIndex[83] = 17  ;
    iIndex[84] = 7   ; jIndex[84] = 18  ;
    iIndex[85] = 7   ; jIndex[85] = 19  ;
  }


  void
  stirred_tank::Dfd_odeDxxpu_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    U_const_p_type UM__,
    real_ptr       result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[8];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[8];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;
    V__[2] = (XR__[2]-XL__[2])/DZETA__xo;
    V__[3] = (XR__[3]-XL__[3])/DZETA__xo;
    V__[4] = (XR__[4]-XL__[4])/DZETA__xo;
    V__[5] = (XR__[5]-XL__[5])/DZETA__xo;
    V__[6] = (XR__[6]-XL__[6])/DZETA__xo;
    V__[7] = (XR__[7]-XL__[7])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = UM__[0];
    real_type t2   = t1 / 2;
    real_type t3   = UM__[1];
    real_type t4   = t3 / 2;
    real_type t5   = UM__[3];
    real_type t6   = t5 / 2;
    real_type t7   = XM__[1];
    real_type t8   = 0.8800000000e1 * t7;
    real_type t9   = XM__[5];
    real_type t10  = UM__[2];
    real_type t11  = t10 * t9;
    real_type t12  = 0.23e2 / 2.0 * t11;
    real_type t13  = 1.0 / DZETA__xo;
    result__[ 0   ] = t2 + t4 + t6 + t8 + t12 - t13;
    real_type t14  = XM__[0];
    result__[ 1   ] = 0.8800000000e1 * t14;
    real_type t15  = t10 * t14;
    result__[ 2   ] = 0.23e2 / 2.0 * t15;
    result__[ 3   ] = t2 + t4 + t6 + t8 + t12 + t13;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = t14;
    result__[ 7   ] = result__[6];
    real_type t16  = t9 * result__[7];
    result__[ 8   ] = 23 * t16;
    result__[ 9   ] = -1 + result__[7];
    result__[ 10  ] = t8;
    real_type t17  = XM__[2];
    real_type t18  = 73 * t17;
    result__[ 11  ] = t2 + t4 + t6 + result__[4] + t18 - t13;
    result__[ 12  ] = 73 * t7;
    result__[ 13  ] = result__[10];
    result__[ 14  ] = t2 + t4 + t6 + result__[4] + t18 + t13;
    result__[ 15  ] = result__[12];
    result__[ 16  ] = -1 + t7;
    result__[ 17  ] = t7;
    result__[ 18  ] = result__[17];
    result__[ 19  ] = 0.73e2 / 2.0 * t17;
    real_type t19  = 0.73e2 / 2.0 * result__[18];
    result__[ 20  ] = t2 + t4 + t6 + t19 - t13;
    result__[ 21  ] = result__[19];
    result__[ 22  ] = t2 + t4 + t6 + t19 + t13;
    result__[ 23  ] = t17;
    result__[ 24  ] = -1 + result__[23];
    result__[ 25  ] = result__[23];
    result__[ 26  ] = -0.1760000000e2 * result__[18];
    result__[ 27  ] = -0.1760000000e2 * result__[7];
    real_type t22  = XM__[4];
    real_type t23  = 0.2565000000e2 * t22;
    result__[ 28  ] = t2 + t4 + t6 + t23 - t13;
    real_type t24  = XM__[3];
    result__[ 29  ] = 0.2565000000e2 * t24;
    result__[ 30  ] = result__[26];
    result__[ 31  ] = result__[27];
    result__[ 32  ] = t2 + t4 + t6 + t23 + t13;
    result__[ 33  ] = result__[29];
    result__[ 34  ] = t24;
    result__[ 35  ] = result__[34];
    result__[ 36  ] = result__[35];
    result__[ 37  ] = -0.219e3 / 2.0 * result__[25];
    result__[ 38  ] = -0.219e3 / 2.0 * result__[18];
    result__[ 39  ] = t23;
    result__[ 40  ] = t2 + t4 + t6 + result__[33] - t13;
    result__[ 41  ] = result__[37];
    result__[ 42  ] = result__[38];
    result__[ 43  ] = result__[39];
    result__[ 44  ] = t2 + t4 + t6 + result__[33] + t13;
    result__[ 45  ] = t22;
    result__[ 46  ] = result__[45];
    result__[ 47  ] = result__[46];
    result__[ 48  ] = t12;
    result__[ 49  ] = -51 * result__[47];
    result__[ 50  ] = -51 * result__[36];
    result__[ 51  ] = t2 + t4 + t6 + result__[5] - t13;
    result__[ 52  ] = result__[48];
    result__[ 53  ] = result__[49];
    result__[ 54  ] = result__[50];
    result__[ 55  ] = t2 + t4 + t6 + result__[5] + t13;
    result__[ 56  ] = t9;
    result__[ 57  ] = result__[56];
    result__[ 58  ] = result__[8];
    result__[ 59  ] = result__[57];
    result__[ 60  ] = -23 * t11;
    result__[ 61  ] = -23 * t15;
    result__[ 62  ] = t2 + t4 + t6 - t13;
    result__[ 63  ] = result__[60];
    result__[ 64  ] = result__[61];
    result__[ 65  ] = t2 + t4 + t6 + t13;
    result__[ 66  ] = XM__[6];
    result__[ 67  ] = result__[66];
    result__[ 68  ] = -46 * t16;
    result__[ 69  ] = result__[67];
    result__[ 70  ] = -0.2900000000e1 * t1 - 0.2900000000e1 * t3 - 0.2900000000e1 * t5;
    real_type t35  = -t1 - t3 - t5;
    result__[ 71  ] = 0.23e2 / 2.0 * t35;
    result__[ 72  ] = 0.11e2 / 2.0 * t35;
    result__[ 73  ] = 14 * t35;
    result__[ 74  ] = 0.35e2 / 2.0 * t35;
    result__[ 75  ] = -t13;
    result__[ 76  ] = result__[70];
    result__[ 77  ] = result__[71];
    result__[ 78  ] = result__[72];
    result__[ 79  ] = result__[73];
    result__[ 80  ] = result__[74];
    result__[ 81  ] = t13;
    real_type t36  = 0.58e1 * result__[7];
    real_type t37  = 23 * result__[36];
    real_type t38  = 11 * result__[47];
    real_type t39  = 28 * result__[59];
    real_type t40  = 35 * result__[69];
    result__[ 82  ] = -t36 + 0.37e1 - t37 - t38 - t39 - t40;
    result__[ 83  ] = -t36 + 0.41e1 - t37 - t38 - t39 - t40;
    result__[ 84  ] = 10 * t10;
    result__[ 85  ] = -t36 + 0.58e1 - t37 - t38 - t39 - t40;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 86, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::D2fd_odeD2xxpu_numRows() const { return 20; }
  integer stirred_tank::D2fd_odeD2xxpu_numCols() const { return 20; }
  integer stirred_tank::D2fd_odeD2xxpu_nnz()     const { return 125; }

  void
  stirred_tank::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 9   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 13  ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 16  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 17  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 18  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 19  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 8   ;
    iIndex[11] = 1   ; jIndex[11] = 10  ;
    iIndex[12] = 1   ; jIndex[12] = 16  ;
    iIndex[13] = 1   ; jIndex[13] = 17  ;
    iIndex[14] = 1   ; jIndex[14] = 19  ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 9   ;
    iIndex[17] = 2   ; jIndex[17] = 16  ;
    iIndex[18] = 2   ; jIndex[18] = 17  ;
    iIndex[19] = 2   ; jIndex[19] = 19  ;
    iIndex[20] = 3   ; jIndex[20] = 4   ;
    iIndex[21] = 3   ; jIndex[21] = 12  ;
    iIndex[22] = 3   ; jIndex[22] = 16  ;
    iIndex[23] = 3   ; jIndex[23] = 17  ;
    iIndex[24] = 3   ; jIndex[24] = 19  ;
    iIndex[25] = 4   ; jIndex[25] = 3   ;
    iIndex[26] = 4   ; jIndex[26] = 11  ;
    iIndex[27] = 4   ; jIndex[27] = 16  ;
    iIndex[28] = 4   ; jIndex[28] = 17  ;
    iIndex[29] = 4   ; jIndex[29] = 19  ;
    iIndex[30] = 5   ; jIndex[30] = 0   ;
    iIndex[31] = 5   ; jIndex[31] = 8   ;
    iIndex[32] = 5   ; jIndex[32] = 16  ;
    iIndex[33] = 5   ; jIndex[33] = 17  ;
    iIndex[34] = 5   ; jIndex[34] = 18  ;
    iIndex[35] = 5   ; jIndex[35] = 19  ;
    iIndex[36] = 6   ; jIndex[36] = 16  ;
    iIndex[37] = 6   ; jIndex[37] = 17  ;
    iIndex[38] = 6   ; jIndex[38] = 19  ;
    iIndex[39] = 8   ; jIndex[39] = 1   ;
    iIndex[40] = 8   ; jIndex[40] = 5   ;
    iIndex[41] = 8   ; jIndex[41] = 9   ;
    iIndex[42] = 8   ; jIndex[42] = 13  ;
    iIndex[43] = 8   ; jIndex[43] = 16  ;
    iIndex[44] = 8   ; jIndex[44] = 17  ;
    iIndex[45] = 8   ; jIndex[45] = 18  ;
    iIndex[46] = 8   ; jIndex[46] = 19  ;
    iIndex[47] = 9   ; jIndex[47] = 0   ;
    iIndex[48] = 9   ; jIndex[48] = 2   ;
    iIndex[49] = 9   ; jIndex[49] = 8   ;
    iIndex[50] = 9   ; jIndex[50] = 10  ;
    iIndex[51] = 9   ; jIndex[51] = 16  ;
    iIndex[52] = 9   ; jIndex[52] = 17  ;
    iIndex[53] = 9   ; jIndex[53] = 19  ;
    iIndex[54] = 10  ; jIndex[54] = 1   ;
    iIndex[55] = 10  ; jIndex[55] = 9   ;
    iIndex[56] = 10  ; jIndex[56] = 16  ;
    iIndex[57] = 10  ; jIndex[57] = 17  ;
    iIndex[58] = 10  ; jIndex[58] = 19  ;
    iIndex[59] = 11  ; jIndex[59] = 4   ;
    iIndex[60] = 11  ; jIndex[60] = 12  ;
    iIndex[61] = 11  ; jIndex[61] = 16  ;
    iIndex[62] = 11  ; jIndex[62] = 17  ;
    iIndex[63] = 11  ; jIndex[63] = 19  ;
    iIndex[64] = 12  ; jIndex[64] = 3   ;
    iIndex[65] = 12  ; jIndex[65] = 11  ;
    iIndex[66] = 12  ; jIndex[66] = 16  ;
    iIndex[67] = 12  ; jIndex[67] = 17  ;
    iIndex[68] = 12  ; jIndex[68] = 19  ;
    iIndex[69] = 13  ; jIndex[69] = 0   ;
    iIndex[70] = 13  ; jIndex[70] = 8   ;
    iIndex[71] = 13  ; jIndex[71] = 16  ;
    iIndex[72] = 13  ; jIndex[72] = 17  ;
    iIndex[73] = 13  ; jIndex[73] = 18  ;
    iIndex[74] = 13  ; jIndex[74] = 19  ;
    iIndex[75] = 14  ; jIndex[75] = 16  ;
    iIndex[76] = 14  ; jIndex[76] = 17  ;
    iIndex[77] = 14  ; jIndex[77] = 19  ;
    iIndex[78] = 16  ; jIndex[78] = 0   ;
    iIndex[79] = 16  ; jIndex[79] = 1   ;
    iIndex[80] = 16  ; jIndex[80] = 2   ;
    iIndex[81] = 16  ; jIndex[81] = 3   ;
    iIndex[82] = 16  ; jIndex[82] = 4   ;
    iIndex[83] = 16  ; jIndex[83] = 5   ;
    iIndex[84] = 16  ; jIndex[84] = 6   ;
    iIndex[85] = 16  ; jIndex[85] = 8   ;
    iIndex[86] = 16  ; jIndex[86] = 9   ;
    iIndex[87] = 16  ; jIndex[87] = 10  ;
    iIndex[88] = 16  ; jIndex[88] = 11  ;
    iIndex[89] = 16  ; jIndex[89] = 12  ;
    iIndex[90] = 16  ; jIndex[90] = 13  ;
    iIndex[91] = 16  ; jIndex[91] = 14  ;
    iIndex[92] = 17  ; jIndex[92] = 0   ;
    iIndex[93] = 17  ; jIndex[93] = 1   ;
    iIndex[94] = 17  ; jIndex[94] = 2   ;
    iIndex[95] = 17  ; jIndex[95] = 3   ;
    iIndex[96] = 17  ; jIndex[96] = 4   ;
    iIndex[97] = 17  ; jIndex[97] = 5   ;
    iIndex[98] = 17  ; jIndex[98] = 6   ;
    iIndex[99] = 17  ; jIndex[99] = 8   ;
    iIndex[100] = 17  ; jIndex[100] = 9   ;
    iIndex[101] = 17  ; jIndex[101] = 10  ;
    iIndex[102] = 17  ; jIndex[102] = 11  ;
    iIndex[103] = 17  ; jIndex[103] = 12  ;
    iIndex[104] = 17  ; jIndex[104] = 13  ;
    iIndex[105] = 17  ; jIndex[105] = 14  ;
    iIndex[106] = 18  ; jIndex[106] = 0   ;
    iIndex[107] = 18  ; jIndex[107] = 5   ;
    iIndex[108] = 18  ; jIndex[108] = 8   ;
    iIndex[109] = 18  ; jIndex[109] = 13  ;
    iIndex[110] = 18  ; jIndex[110] = 18  ;
    iIndex[111] = 19  ; jIndex[111] = 0   ;
    iIndex[112] = 19  ; jIndex[112] = 1   ;
    iIndex[113] = 19  ; jIndex[113] = 2   ;
    iIndex[114] = 19  ; jIndex[114] = 3   ;
    iIndex[115] = 19  ; jIndex[115] = 4   ;
    iIndex[116] = 19  ; jIndex[116] = 5   ;
    iIndex[117] = 19  ; jIndex[117] = 6   ;
    iIndex[118] = 19  ; jIndex[118] = 8   ;
    iIndex[119] = 19  ; jIndex[119] = 9   ;
    iIndex[120] = 19  ; jIndex[120] = 10  ;
    iIndex[121] = 19  ; jIndex[121] = 11  ;
    iIndex[122] = 19  ; jIndex[122] = 12  ;
    iIndex[123] = 19  ; jIndex[123] = 13  ;
    iIndex[124] = 19  ; jIndex[124] = 14  ;
  }


  void
  stirred_tank::D2fd_odeD2xxpu_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    U_const_p_type UM__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[8];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    XM__[6] = (XL__[6]+XR__[6])/2;
    XM__[7] = (XL__[7]+XR__[7])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[8];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;
    V__[2] = (XR__[2]-XL__[2])/DZETA__xo;
    V__[3] = (XR__[3]-XL__[3])/DZETA__xo;
    V__[4] = (XR__[4]-XL__[4])/DZETA__xo;
    V__[5] = (XR__[5]-XL__[5])/DZETA__xo;
    V__[6] = (XR__[6]-XL__[6])/DZETA__xo;
    V__[7] = (XR__[7]-XL__[7])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = OMEGA__[0];
    real_type t3   = OMEGA__[1];
    real_type t5   = OMEGA__[3];
    result__[ 0   ] = 0.4400000000e1 * t1 + 0.4400000000e1 * t3 - 0.8800000000e1 * t5;
    real_type t7   = UM__[2];
    real_type t10  = OMEGA__[5];
    real_type t13  = OMEGA__[6];
    result__[ 1   ] = 0.23e2 / 4.0 * t1 * t7 + 0.23e2 / 4.0 * t10 * t7 - 0.23e2 / 2.0 * t13 * t7;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    real_type t17  = OMEGA__[7];
    result__[ 4   ] = t1 / 2 - 0.2900000000e1 * t17;
    result__[ 5   ] = result__[4];
    real_type t21  = XL__[iX_x6] + XR__[iX_x6];
    real_type t24  = t21 / 2;
    result__[ 6   ] = 0.23e2 / 4.0 * t1 * t21 + 0.23e2 / 2.0 * t10 * t24 - 23 * t13 * t24;
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[2];
    real_type t30  = OMEGA__[2];
    real_type t32  = OMEGA__[4];
    result__[ 9   ] = 0.73e2 / 2.0 * t3 + 0.73e2 / 4.0 * t30 - 0.219e3 / 4.0 * t32;
    result__[ 10  ] = result__[8];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = t3 / 2;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[13];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = result__[15];
    result__[ 17  ] = t30 / 2;
    result__[ 18  ] = result__[17];
    result__[ 19  ] = result__[18];
    result__[ 20  ] = 0.1282500000e2 * t5 + 0.1282500000e2 * t32 - 0.51e2 / 2.0 * t10;
    result__[ 21  ] = result__[20];
    result__[ 22  ] = t5 / 2 - 0.23e2 / 2.0 * t17;
    result__[ 23  ] = result__[22];
    result__[ 24  ] = result__[23];
    result__[ 25  ] = result__[21];
    result__[ 26  ] = result__[25];
    result__[ 27  ] = t32 / 2 - 0.11e2 / 2.0 * t17;
    result__[ 28  ] = result__[27];
    result__[ 29  ] = result__[28];
    result__[ 30  ] = result__[3];
    result__[ 31  ] = result__[30];
    result__[ 32  ] = t10 / 2 - 14 * t17;
    result__[ 33  ] = result__[32];
    real_type t45  = XL__[iX_x1] + XR__[iX_x1];
    real_type t46  = t45 / 2;
    result__[ 34  ] = 0.23e2 / 2.0 * t1 * t46 + 0.23e2 / 4.0 * t10 * t45 - 23 * t13 * t46;
    result__[ 35  ] = result__[33];
    result__[ 36  ] = t13 / 2 - 0.35e2 / 2.0 * t17;
    result__[ 37  ] = result__[36];
    result__[ 38  ] = result__[37];
    result__[ 39  ] = result__[10];
    result__[ 40  ] = result__[31];
    result__[ 41  ] = result__[39];
    result__[ 42  ] = result__[40];
    result__[ 43  ] = result__[7];
    result__[ 44  ] = result__[43];
    result__[ 45  ] = result__[6];
    result__[ 46  ] = result__[44];
    result__[ 47  ] = result__[41];
    result__[ 48  ] = result__[16];
    result__[ 49  ] = result__[47];
    result__[ 50  ] = result__[48];
    result__[ 51  ] = result__[14];
    result__[ 52  ] = result__[51];
    result__[ 53  ] = result__[52];
    result__[ 54  ] = result__[50];
    result__[ 55  ] = result__[54];
    result__[ 56  ] = result__[19];
    result__[ 57  ] = result__[56];
    result__[ 58  ] = result__[57];
    result__[ 59  ] = result__[26];
    result__[ 60  ] = result__[59];
    result__[ 61  ] = result__[24];
    result__[ 62  ] = result__[61];
    result__[ 63  ] = result__[62];
    result__[ 64  ] = result__[60];
    result__[ 65  ] = result__[64];
    result__[ 66  ] = result__[29];
    result__[ 67  ] = result__[66];
    result__[ 68  ] = result__[67];
    result__[ 69  ] = result__[42];
    result__[ 70  ] = result__[69];
    result__[ 71  ] = result__[35];
    result__[ 72  ] = result__[71];
    result__[ 73  ] = result__[34];
    result__[ 74  ] = result__[72];
    result__[ 75  ] = result__[38];
    result__[ 76  ] = result__[75];
    result__[ 77  ] = result__[76];
    result__[ 78  ] = result__[46];
    result__[ 79  ] = result__[53];
    result__[ 80  ] = result__[58];
    result__[ 81  ] = result__[63];
    result__[ 82  ] = result__[68];
    result__[ 83  ] = result__[74];
    result__[ 84  ] = result__[77];
    result__[ 85  ] = result__[78];
    result__[ 86  ] = result__[79];
    result__[ 87  ] = result__[80];
    result__[ 88  ] = result__[81];
    result__[ 89  ] = result__[82];
    result__[ 90  ] = result__[83];
    result__[ 91  ] = result__[84];
    result__[ 92  ] = result__[85];
    result__[ 93  ] = result__[86];
    result__[ 94  ] = result__[87];
    result__[ 95  ] = result__[88];
    result__[ 96  ] = result__[89];
    result__[ 97  ] = result__[90];
    result__[ 98  ] = result__[91];
    result__[ 99  ] = result__[92];
    result__[ 100 ] = result__[93];
    result__[ 101 ] = result__[94];
    result__[ 102 ] = result__[95];
    result__[ 103 ] = result__[96];
    result__[ 104 ] = result__[97];
    result__[ 105 ] = result__[98];
    result__[ 106 ] = result__[45];
    result__[ 107 ] = result__[73];
    result__[ 108 ] = result__[106];
    result__[ 109 ] = result__[107];
    result__[ 110 ] = 10 * t17;
    result__[ 111 ] = result__[99];
    result__[ 112 ] = result__[100];
    result__[ 113 ] = result__[101];
    result__[ 114 ] = result__[102];
    result__[ 115 ] = result__[103];
    result__[ 116 ] = result__[104];
    result__[ 117 ] = result__[105];
    result__[ 118 ] = result__[111];
    result__[ 119 ] = result__[112];
    result__[ 120 ] = result__[113];
    result__[ 121 ] = result__[114];
    result__[ 122 ] = result__[115];
    result__[ 123 ] = result__[116];
    result__[ 124 ] = result__[117];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 125, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: stirred_tank_Methods_Guess.cc
