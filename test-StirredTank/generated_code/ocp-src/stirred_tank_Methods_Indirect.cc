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
  :|:   ___           _ _               _
  :|:  |_ _|_ __   __| (_)_ __ ___  ___| |_
  :|:   | || '_ \ / _` | | '__/ _ \/ __| __|
  :|:   | || | | | (_| | | | |  __/ (__| |_
  :|:  |___|_| |_|\__,_|_|_|  \___|\___|\__|
  \*/


  integer stirred_tank::fd_ode2_numEqns() const { return 8; }

  void
  stirred_tank::fd_ode2_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
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
    // LM -------------------------------
    real_type LM__[8];
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
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
    real_type t3   = LM__[0];
    real_type t4   = UM__[0];
    real_type t5   = UM__[1];
    real_type t6   = UM__[3];
    real_type t7   = XM__[1];
    real_type t9   = XM__[5];
    real_type t10  = UM__[2];
    real_type t15  = LM__[1];
    real_type t16  = t7 * t15;
    real_type t18  = LM__[3];
    real_type t21  = LM__[5];
    real_type t25  = LM__[6];
    real_type t29  = LM__[7];
    result__[ 0   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo] + ((-t4 - t5 - t6 - 0.176e2 * t7 - 23 * t10 * t9) * t3 - 0.176e2 * t16 + 0.352e2 * t7 * t18 - 23 * t10 * t9 * t21 + 46 * t10 * t9 * t25 + (0.58e1 * t4 + 0.58e1 * t5 + 0.58e1 * t6) * t29) * DZETA__xo;
    real_type t39  = XM__[0];
    real_type t40  = t39 * t3;
    real_type t43  = XM__[2];
    real_type t47  = LM__[2];
    real_type t52  = LM__[4];
    result__[ 1   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo] + (-0.176e2 * t40 + (-t4 - t5 - t6 - 0.176e2 * t39 - 146 * t43) * t15 - 73 * t43 * t47 + 0.352e2 * t39 * t18 + 219 * t43 * t52) * DZETA__xo;
    result__[ 2   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo] + (-146 * t16 + (-t4 - t5 - t6 - 73 * t7) * t47 + 219 * t7 * t52) * DZETA__xo;
    real_type t69  = XM__[4];
    real_type t77  = t4 + t5 + t6;
    result__[ 3   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo] + ((-t4 - t5 - t6 - 0.513e2 * t69) * t18 - 0.513e2 * t69 * t52 + 102 * t69 * t21 + 23 * t77 * t29) * DZETA__xo;
    real_type t84  = XM__[3];
    result__[ 4   ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo] + (-0.513e2 * t84 * t18 + (-t4 - t5 - t6 - 0.513e2 * t84) * t52 + 102 * t84 * t21 + 11 * t77 * t29) * DZETA__xo;
    result__[ 5   ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo] + (-23 * t10 * t40 + (-23 * t10 * t39 - t4 - t5 - t6) * t21 + 46 * t10 * t39 * t25 + 28 * t77 * t29) * DZETA__xo;
    result__[ 6   ] = LR__[iL_lambda7__xo] - LL__[iL_lambda7__xo] + (-t77 * t25 + 35 * t77 * t29) * DZETA__xo;
    result__[ 7   ] = LR__[iL_lambda8__xo] - LL__[iL_lambda8__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode2_eval", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::Dfd_ode2Dxlxlpu_numRows() const { return 8; }
  integer stirred_tank::Dfd_ode2Dxlxlpu_numCols() const { return 36; }
  integer stirred_tank::Dfd_ode2Dxlxlpu_nnz()     const { return 97; }

  void
  stirred_tank::Dfd_ode2Dxlxlpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 11  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 17  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 21  ;
    iIndex[10] = 0   ; jIndex[10] = 24  ;
    iIndex[11] = 0   ; jIndex[11] = 25  ;
    iIndex[12] = 0   ; jIndex[12] = 27  ;
    iIndex[13] = 0   ; jIndex[13] = 29  ;
    iIndex[14] = 0   ; jIndex[14] = 30  ;
    iIndex[15] = 0   ; jIndex[15] = 31  ;
    iIndex[16] = 0   ; jIndex[16] = 32  ;
    iIndex[17] = 0   ; jIndex[17] = 33  ;
    iIndex[18] = 0   ; jIndex[18] = 34  ;
    iIndex[19] = 0   ; jIndex[19] = 35  ;
    iIndex[20] = 1   ; jIndex[20] = 0   ;
    iIndex[21] = 1   ; jIndex[21] = 2   ;
    iIndex[22] = 1   ; jIndex[22] = 8   ;
    iIndex[23] = 1   ; jIndex[23] = 9   ;
    iIndex[24] = 1   ; jIndex[24] = 10  ;
    iIndex[25] = 1   ; jIndex[25] = 11  ;
    iIndex[26] = 1   ; jIndex[26] = 12  ;
    iIndex[27] = 1   ; jIndex[27] = 16  ;
    iIndex[28] = 1   ; jIndex[28] = 18  ;
    iIndex[29] = 1   ; jIndex[29] = 24  ;
    iIndex[30] = 1   ; jIndex[30] = 25  ;
    iIndex[31] = 1   ; jIndex[31] = 26  ;
    iIndex[32] = 1   ; jIndex[32] = 27  ;
    iIndex[33] = 1   ; jIndex[33] = 28  ;
    iIndex[34] = 1   ; jIndex[34] = 32  ;
    iIndex[35] = 1   ; jIndex[35] = 33  ;
    iIndex[36] = 1   ; jIndex[36] = 35  ;
    iIndex[37] = 2   ; jIndex[37] = 1   ;
    iIndex[38] = 2   ; jIndex[38] = 9   ;
    iIndex[39] = 2   ; jIndex[39] = 10  ;
    iIndex[40] = 2   ; jIndex[40] = 12  ;
    iIndex[41] = 2   ; jIndex[41] = 17  ;
    iIndex[42] = 2   ; jIndex[42] = 25  ;
    iIndex[43] = 2   ; jIndex[43] = 26  ;
    iIndex[44] = 2   ; jIndex[44] = 28  ;
    iIndex[45] = 2   ; jIndex[45] = 32  ;
    iIndex[46] = 2   ; jIndex[46] = 33  ;
    iIndex[47] = 2   ; jIndex[47] = 35  ;
    iIndex[48] = 3   ; jIndex[48] = 4   ;
    iIndex[49] = 3   ; jIndex[49] = 11  ;
    iIndex[50] = 3   ; jIndex[50] = 12  ;
    iIndex[51] = 3   ; jIndex[51] = 13  ;
    iIndex[52] = 3   ; jIndex[52] = 15  ;
    iIndex[53] = 3   ; jIndex[53] = 20  ;
    iIndex[54] = 3   ; jIndex[54] = 27  ;
    iIndex[55] = 3   ; jIndex[55] = 28  ;
    iIndex[56] = 3   ; jIndex[56] = 29  ;
    iIndex[57] = 3   ; jIndex[57] = 31  ;
    iIndex[58] = 3   ; jIndex[58] = 32  ;
    iIndex[59] = 3   ; jIndex[59] = 33  ;
    iIndex[60] = 3   ; jIndex[60] = 35  ;
    iIndex[61] = 4   ; jIndex[61] = 3   ;
    iIndex[62] = 4   ; jIndex[62] = 11  ;
    iIndex[63] = 4   ; jIndex[63] = 12  ;
    iIndex[64] = 4   ; jIndex[64] = 13  ;
    iIndex[65] = 4   ; jIndex[65] = 15  ;
    iIndex[66] = 4   ; jIndex[66] = 19  ;
    iIndex[67] = 4   ; jIndex[67] = 27  ;
    iIndex[68] = 4   ; jIndex[68] = 28  ;
    iIndex[69] = 4   ; jIndex[69] = 29  ;
    iIndex[70] = 4   ; jIndex[70] = 31  ;
    iIndex[71] = 4   ; jIndex[71] = 32  ;
    iIndex[72] = 4   ; jIndex[72] = 33  ;
    iIndex[73] = 4   ; jIndex[73] = 35  ;
    iIndex[74] = 5   ; jIndex[74] = 0   ;
    iIndex[75] = 5   ; jIndex[75] = 8   ;
    iIndex[76] = 5   ; jIndex[76] = 13  ;
    iIndex[77] = 5   ; jIndex[77] = 14  ;
    iIndex[78] = 5   ; jIndex[78] = 15  ;
    iIndex[79] = 5   ; jIndex[79] = 16  ;
    iIndex[80] = 5   ; jIndex[80] = 24  ;
    iIndex[81] = 5   ; jIndex[81] = 29  ;
    iIndex[82] = 5   ; jIndex[82] = 30  ;
    iIndex[83] = 5   ; jIndex[83] = 31  ;
    iIndex[84] = 5   ; jIndex[84] = 32  ;
    iIndex[85] = 5   ; jIndex[85] = 33  ;
    iIndex[86] = 5   ; jIndex[86] = 34  ;
    iIndex[87] = 5   ; jIndex[87] = 35  ;
    iIndex[88] = 6   ; jIndex[88] = 14  ;
    iIndex[89] = 6   ; jIndex[89] = 15  ;
    iIndex[90] = 6   ; jIndex[90] = 30  ;
    iIndex[91] = 6   ; jIndex[91] = 31  ;
    iIndex[92] = 6   ; jIndex[92] = 32  ;
    iIndex[93] = 6   ; jIndex[93] = 33  ;
    iIndex[94] = 6   ; jIndex[94] = 35  ;
    iIndex[95] = 7   ; jIndex[95] = 15  ;
    iIndex[96] = 7   ; jIndex[96] = 31  ;
  }


  void
  stirred_tank::Dfd_ode2Dxlxlpu_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
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
    // LM -------------------------------
    real_type LM__[8];
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    LM__[6] = (LL__[6]+LR__[6])/2;
    LM__[7] = (LL__[7]+LR__[7])/2;
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
    real_type t1   = LM__[0];
    real_type t3   = LM__[1];
    real_type t5   = LM__[3];
    result__[ 0   ] = (-0.176e2 * t1 - 0.176e2 * t3 + 0.352e2 * t5) * DZETA__xo / 2;
    real_type t9   = UM__[2];
    real_type t12  = LM__[5];
    real_type t15  = LM__[6];
    result__[ 1   ] = (-23 * t9 * t1 - 23 * t9 * t12 + 46 * t9 * t15) * DZETA__xo / 2;
    real_type t20  = UM__[0];
    real_type t21  = UM__[1];
    real_type t22  = UM__[3];
    real_type t23  = XM__[1];
    real_type t25  = XM__[5];
    real_type t30  = (-t20 - t21 - t22 - 0.176e2 * t23 - 23 * t9 * t25) * DZETA__xo / 2;
    result__[ 2   ] = -1 + t30;
    real_type t31  = t23 * DZETA__xo;
    result__[ 3   ] = -0.8800000000e1 * t31;
    result__[ 4   ] = 0.1760000000e2 * t31;
    real_type t34  = t9 * t25 * DZETA__xo;
    result__[ 5   ] = -0.23e2 / 2.0 * t34;
    result__[ 6   ] = 23 * t34;
    result__[ 7   ] = (0.58e1 * t20 + 0.58e1 * t21 + 0.58e1 * t22) * DZETA__xo / 2;
    result__[ 8   ] = result__[0];
    result__[ 9   ] = result__[1];
    result__[ 10  ] = 1 + t30;
    result__[ 11  ] = result__[3];
    result__[ 12  ] = result__[4];
    result__[ 13  ] = result__[5];
    result__[ 14  ] = result__[6];
    result__[ 15  ] = result__[7];
    real_type t41  = LM__[7];
    result__[ 16  ] = (-t1 + 0.58e1 * t41) * DZETA__xo;
    result__[ 17  ] = result__[16];
    result__[ 18  ] = (-23 * t25 * t1 - 23 * t25 * t12 + 46 * t25 * t15) * DZETA__xo;
    result__[ 19  ] = result__[17];
    result__[ 20  ] = result__[8];
    real_type t52  = LM__[2];
    real_type t54  = LM__[4];
    result__[ 21  ] = (-146 * t3 - 73 * t52 + 219 * t54) * DZETA__xo / 2;
    real_type t58  = XM__[0];
    real_type t59  = t58 * DZETA__xo;
    result__[ 22  ] = -0.8800000000e1 * t59;
    real_type t62  = XM__[2];
    real_type t66  = (-t20 - t21 - t22 - 0.176e2 * t58 - 146 * t62) * DZETA__xo / 2;
    result__[ 23  ] = -1 + t66;
    real_type t67  = t62 * DZETA__xo;
    result__[ 24  ] = -0.73e2 / 2.0 * t67;
    result__[ 25  ] = 0.1760000000e2 * t59;
    result__[ 26  ] = 0.219e3 / 2.0 * t67;
    result__[ 27  ] = result__[20];
    result__[ 28  ] = result__[21];
    result__[ 29  ] = result__[22];
    result__[ 30  ] = 1 + t66;
    result__[ 31  ] = result__[24];
    result__[ 32  ] = result__[25];
    result__[ 33  ] = result__[26];
    result__[ 34  ] = -t3 * DZETA__xo;
    result__[ 35  ] = result__[34];
    result__[ 36  ] = result__[35];
    result__[ 37  ] = result__[28];
    result__[ 38  ] = -73 * t31;
    real_type t74  = (-t20 - t21 - t22 - 73 * t23) * DZETA__xo / 2;
    result__[ 39  ] = -1 + t74;
    result__[ 40  ] = 0.219e3 / 2.0 * t31;
    result__[ 41  ] = result__[37];
    result__[ 42  ] = result__[38];
    result__[ 43  ] = 1 + t74;
    result__[ 44  ] = result__[40];
    result__[ 45  ] = -t52 * DZETA__xo;
    result__[ 46  ] = result__[45];
    result__[ 47  ] = result__[46];
    result__[ 48  ] = (-0.513e2 * t5 - 0.513e2 * t54 + 102 * t12) * DZETA__xo / 2;
    real_type t81  = XM__[4];
    real_type t85  = (-t20 - t21 - t22 - 0.513e2 * t81) * DZETA__xo / 2;
    result__[ 49  ] = -1 + t85;
    real_type t86  = t81 * DZETA__xo;
    result__[ 50  ] = -0.2565000000e2 * t86;
    result__[ 51  ] = 51 * t86;
    real_type t88  = t20 + t21 + t22;
    result__[ 52  ] = 0.23e2 / 2.0 * t88 * DZETA__xo;
    result__[ 53  ] = result__[48];
    result__[ 54  ] = 1 + t85;
    result__[ 55  ] = result__[50];
    result__[ 56  ] = result__[51];
    result__[ 57  ] = result__[52];
    result__[ 58  ] = (-t5 + 23 * t41) * DZETA__xo;
    result__[ 59  ] = result__[58];
    result__[ 60  ] = result__[59];
    result__[ 61  ] = result__[53];
    real_type t93  = XM__[3];
    real_type t94  = t93 * DZETA__xo;
    result__[ 62  ] = -0.2565000000e2 * t94;
    real_type t99  = (-t20 - t21 - t22 - 0.513e2 * t93) * DZETA__xo / 2;
    result__[ 63  ] = -1 + t99;
    result__[ 64  ] = 51 * t94;
    result__[ 65  ] = 0.11e2 / 2.0 * t88 * DZETA__xo;
    result__[ 66  ] = result__[61];
    result__[ 67  ] = result__[62];
    result__[ 68  ] = 1 + t99;
    result__[ 69  ] = result__[64];
    result__[ 70  ] = result__[65];
    result__[ 71  ] = (-t54 + 11 * t41) * DZETA__xo;
    result__[ 72  ] = result__[71];
    result__[ 73  ] = result__[72];
    result__[ 74  ] = result__[9];
    real_type t104 = t9 * t59;
    result__[ 75  ] = -0.23e2 / 2.0 * t104;
    real_type t110 = (-23 * t9 * t58 - t20 - t21 - t22) * DZETA__xo / 2;
    result__[ 76  ] = -1 + t110;
    result__[ 77  ] = 23 * t104;
    result__[ 78  ] = 14 * t88 * DZETA__xo;
    result__[ 79  ] = result__[74];
    result__[ 80  ] = result__[75];
    result__[ 81  ] = 1 + t110;
    result__[ 82  ] = result__[77];
    result__[ 83  ] = result__[78];
    result__[ 84  ] = (-t12 + 28 * t41) * DZETA__xo;
    result__[ 85  ] = result__[84];
    result__[ 86  ] = (-23 * t58 * t1 - 23 * t58 * t12 + 46 * t58 * t15) * DZETA__xo;
    result__[ 87  ] = result__[85];
    real_type t124 = -t88 * DZETA__xo / 2;
    result__[ 88  ] = -1 + t124;
    result__[ 89  ] = 0.35e2 / 2.0 * t88 * DZETA__xo;
    result__[ 90  ] = 1 + t124;
    result__[ 91  ] = result__[89];
    result__[ 92  ] = (-t15 + 35 * t41) * DZETA__xo;
    result__[ 93  ] = result__[92];
    result__[ 94  ] = result__[93];
    result__[ 95  ] = -1;
    result__[ 96  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_ode2Dxlxlpu_eval", 97, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer stirred_tank::fd_int_numEqns() const { return 0; }

  void
  stirred_tank::fd_int_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer stirred_tank::Dfd_intDxlxlpu_numRows() const { return 0; }
  integer stirred_tank::Dfd_intDxlxlpu_numCols() const { return 36; }
  integer stirred_tank::Dfd_intDxlxlpu_nnz()     const { return 0; }

  void
  stirred_tank::Dfd_intDxlxlpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  stirred_tank::Dfd_intDxlxlpu_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::node_LR_to_cell(
    NodeQX const & LEFT,
    NodeQX const & RIGHT,
    NodeQX       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    X[6] = (LEFT.x[6]+RIGHT.x[6])/2;
    X[7] = (LEFT.x[7]+RIGHT.x[7])/2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  stirred_tank::node_LR_to_cell(
    NodeQXL const & LEFT,
    NodeQXL const & RIGHT,
    NodeQXL       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    real_ptr L = const_cast<real_ptr>(NODE.lambda);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    X[6] = (LEFT.x[6]+RIGHT.x[6])/2;
    X[7] = (LEFT.x[7]+RIGHT.x[7])/2;
    L[0] = (LEFT.lambda[0]+RIGHT.lambda[0])/2;
    L[1] = (LEFT.lambda[1]+RIGHT.lambda[1])/2;
    L[2] = (LEFT.lambda[2]+RIGHT.lambda[2])/2;
    L[3] = (LEFT.lambda[3]+RIGHT.lambda[3])/2;
    L[4] = (LEFT.lambda[4]+RIGHT.lambda[4])/2;
    L[5] = (LEFT.lambda[5]+RIGHT.lambda[5])/2;
    L[6] = (LEFT.lambda[6]+RIGHT.lambda[6])/2;
    L[7] = (LEFT.lambda[7]+RIGHT.lambda[7])/2;
  }
}

// EOF: stirred_tank_Methods_Guess.cc
