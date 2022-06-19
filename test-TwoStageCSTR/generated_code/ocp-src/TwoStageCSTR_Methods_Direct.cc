/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods_Guess.cc                                  |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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


using namespace std;

namespace TwoStageCSTRDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer TwoStageCSTR::fd_ode_numEqns() const { return 4; }

  void
  TwoStageCSTR::fd_ode_eval(
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
    real_type t2   = XM__[0];
    real_type t3   = XM__[1];
    real_type t4   = R1(t2, t3);
    result__[ 0   ] = V__[0] - 0.5e0 + t2 + t4;
    real_type t9   = (2 + UM__[0]) * (t3 + 0.25e0);
    result__[ 1   ] = V__[1] - t4 + t9;
    real_type t11  = XM__[2];
    real_type t12  = ModelPars[iM_tau];
    real_type t15  = XM__[3];
    real_type t16  = R2(t11, t15);
    result__[ 2   ] = V__[2] - t2 + t11 + (0.5e0 - t2 - t4) * t12 + t16 - 0.25e0;
    result__[ 3   ] = V__[3] - t3 + 2 * t15 + (t15 + 0.25e0) * UM__[1] + (t4 - t9) * t12 - t16 + 0.25e0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::Dfd_odeDxxpu_numRows() const { return 4; }
  integer TwoStageCSTR::Dfd_odeDxxpu_numCols() const { return 10; }
  integer TwoStageCSTR::Dfd_odeDxxpu_nnz()     const { return 27; }

  void
  TwoStageCSTR::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 0   ;
    iIndex[10] = 2   ; jIndex[10] = 1   ;
    iIndex[11] = 2   ; jIndex[11] = 2   ;
    iIndex[12] = 2   ; jIndex[12] = 3   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 5   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 2   ; jIndex[16] = 7   ;
    iIndex[17] = 3   ; jIndex[17] = 0   ;
    iIndex[18] = 3   ; jIndex[18] = 1   ;
    iIndex[19] = 3   ; jIndex[19] = 2   ;
    iIndex[20] = 3   ; jIndex[20] = 3   ;
    iIndex[21] = 3   ; jIndex[21] = 4   ;
    iIndex[22] = 3   ; jIndex[22] = 5   ;
    iIndex[23] = 3   ; jIndex[23] = 6   ;
    iIndex[24] = 3   ; jIndex[24] = 7   ;
    iIndex[25] = 3   ; jIndex[25] = 8   ;
    iIndex[26] = 3   ; jIndex[26] = 9   ;
  }


  void
  TwoStageCSTR::Dfd_odeDxxpu_sparse(
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
    real_type t1   = XM__[0];
    real_type t2   = XM__[1];
    real_type t3   = R1_D_1(t1, t2);
    real_type t4   = 0.5e0 * t3;
    result__[ 0   ] = 0.5e0 + t4 - __INV_DZETA;
    real_type t5   = R1_D_2(t1, t2);
    result__[ 1   ] = 0.5e0 * t5;
    result__[ 2   ] = 0.5e0 + t4 + __INV_DZETA;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = -t4;
    real_type t6   = UM__[0];
    real_type t7   = 0.5e0 * t6;
    result__[ 5   ] = -result__[3] + 0.10e1 + t7 - __INV_DZETA;
    result__[ 6   ] = result__[4];
    result__[ 7   ] = -result__[3] + 0.10e1 + t7 + __INV_DZETA;
    result__[ 8   ] = t2 + 0.25e0;
    real_type t8   = ModelPars[iM_tau];
    result__[ 9   ] = -0.5e0 + 0.5e0 * (-1 - t3) * t8;
    result__[ 10  ] = -0.5e0 * t5 * t8;
    real_type t14  = XM__[2];
    real_type t15  = XM__[3];
    real_type t16  = R2_D_1(t14, t15);
    real_type t17  = 0.5e0 * t16;
    result__[ 11  ] = 0.5e0 + t17 - __INV_DZETA;
    real_type t18  = R2_D_2(t14, t15);
    result__[ 12  ] = 0.5e0 * t18;
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[10];
    result__[ 15  ] = 0.5e0 + t17 + __INV_DZETA;
    result__[ 16  ] = result__[12];
    result__[ 17  ] = 0.5e0 * t3 * t8;
    result__[ 18  ] = -0.5e0 + 0.5e0 * (t5 - 2 - t6) * t8;
    result__[ 19  ] = -t17;
    real_type t24  = 0.5e0 * UM__[1];
    result__[ 20  ] = 0.10e1 + t24 - result__[16] - __INV_DZETA;
    result__[ 21  ] = result__[17];
    result__[ 22  ] = result__[18];
    result__[ 23  ] = result__[19];
    result__[ 24  ] = 0.10e1 + t24 - result__[16] + __INV_DZETA;
    result__[ 25  ] = -result__[8] * t8;
    result__[ 26  ] = t15 + 0.25e0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 27, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::D2fd_odeD2xxpu_numRows() const { return 10; }
  integer TwoStageCSTR::D2fd_odeD2xxpu_numCols() const { return 10; }
  integer TwoStageCSTR::D2fd_odeD2xxpu_nnz()     const { return 40; }

  void
  TwoStageCSTR::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 2   ; jIndex[11] = 6   ;
    iIndex[12] = 2   ; jIndex[12] = 7   ;
    iIndex[13] = 3   ; jIndex[13] = 2   ;
    iIndex[14] = 3   ; jIndex[14] = 3   ;
    iIndex[15] = 3   ; jIndex[15] = 6   ;
    iIndex[16] = 3   ; jIndex[16] = 7   ;
    iIndex[17] = 3   ; jIndex[17] = 9   ;
    iIndex[18] = 4   ; jIndex[18] = 0   ;
    iIndex[19] = 4   ; jIndex[19] = 1   ;
    iIndex[20] = 4   ; jIndex[20] = 4   ;
    iIndex[21] = 4   ; jIndex[21] = 5   ;
    iIndex[22] = 5   ; jIndex[22] = 0   ;
    iIndex[23] = 5   ; jIndex[23] = 1   ;
    iIndex[24] = 5   ; jIndex[24] = 4   ;
    iIndex[25] = 5   ; jIndex[25] = 5   ;
    iIndex[26] = 5   ; jIndex[26] = 8   ;
    iIndex[27] = 6   ; jIndex[27] = 2   ;
    iIndex[28] = 6   ; jIndex[28] = 3   ;
    iIndex[29] = 6   ; jIndex[29] = 6   ;
    iIndex[30] = 6   ; jIndex[30] = 7   ;
    iIndex[31] = 7   ; jIndex[31] = 2   ;
    iIndex[32] = 7   ; jIndex[32] = 3   ;
    iIndex[33] = 7   ; jIndex[33] = 6   ;
    iIndex[34] = 7   ; jIndex[34] = 7   ;
    iIndex[35] = 7   ; jIndex[35] = 9   ;
    iIndex[36] = 8   ; jIndex[36] = 1   ;
    iIndex[37] = 8   ; jIndex[37] = 5   ;
    iIndex[38] = 9   ; jIndex[38] = 3   ;
    iIndex[39] = 9   ; jIndex[39] = 7   ;
  }


  void
  TwoStageCSTR::D2fd_odeD2xxpu_sparse(
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
    real_type t1   = LM__[0];
    real_type t5   = XR__[iX_x1] / 2 + XL__[iX_x1] / 2;
    real_type t9   = XR__[iX_x2] / 2 + XL__[iX_x2] / 2;
    real_type t10  = R1_D_1_1(t5, t9);
    real_type t12  = LM__[1];
    real_type t14  = LM__[2];
    real_type t15  = ModelPars[iM_tau];
    real_type t16  = t15 * t14;
    real_type t18  = LM__[3];
    real_type t19  = t15 * t18;
    result__[ 0   ] = t10 * t1 / 4 - t10 * t12 / 4 - t10 * t16 / 4 + t10 * t19 / 4;
    real_type t22  = R1_D_1_2(t5, t9);
    result__[ 1   ] = t22 * t1 / 4 - t22 * t12 / 4 - t22 * t16 / 4 + t22 * t19 / 4;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[3];
    real_type t28  = R1_D_2_2(t5, t9);
    result__[ 5   ] = t28 * t1 / 4 - t28 * t12 / 4 - t28 * t16 / 4 + t28 * t19 / 4;
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = -t19 / 2 + t12 / 2;
    real_type t38  = XR__[iX_x3] / 2 + XL__[iX_x3] / 2;
    real_type t42  = XR__[iX_x4] / 2 + XL__[iX_x4] / 2;
    real_type t43  = R2_D_1_1(t38, t42);
    result__[ 9   ] = t43 * t14 / 4 - t43 * t18 / 4;
    real_type t47  = R2_D_1_2(t38, t42);
    result__[ 10  ] = t47 * t14 / 4 - t47 * t18 / 4;
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = result__[12];
    real_type t51  = R2_D_2_2(t38, t42);
    result__[ 14  ] = t51 * t14 / 4 - t51 * t18 / 4;
    result__[ 15  ] = result__[13];
    result__[ 16  ] = result__[14];
    result__[ 17  ] = t18 / 2;
    result__[ 18  ] = result__[2];
    result__[ 19  ] = result__[6];
    result__[ 20  ] = result__[18];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = result__[21];
    result__[ 23  ] = result__[7];
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[23];
    result__[ 26  ] = result__[8];
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[15];
    result__[ 29  ] = result__[27];
    result__[ 30  ] = result__[28];
    result__[ 31  ] = result__[30];
    result__[ 32  ] = result__[16];
    result__[ 33  ] = result__[31];
    result__[ 34  ] = result__[32];
    result__[ 35  ] = result__[17];
    result__[ 36  ] = result__[26];
    result__[ 37  ] = result__[36];
    result__[ 38  ] = result__[35];
    result__[ 39  ] = result__[38];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 40, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: TwoStageCSTR_Methods_Guess.cc
