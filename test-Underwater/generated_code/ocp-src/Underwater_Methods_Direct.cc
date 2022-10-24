/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_Guess.cc                                    |
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


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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

namespace UnderwaterDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Underwater::fd_ode_numEqns() const { return 6; }

  void
  Underwater::fd_ode_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = XM__[3];
    real_type t4   = XM__[2];
    real_type t5   = cos(t4);
    real_type t7   = XM__[4];
    real_type t8   = sin(t4);
    result__[ 0   ] = V__[0] - (t5 * t3 + t8 * t7) * t2;
    result__[ 1   ] = V__[1] - (-t8 * t3 + t5 * t7) * t2;
    real_type t17  = XM__[5];
    result__[ 2   ] = -t17 * t2 + V__[2];
    real_type t22  = ModelPars[iM_m1];
    real_type t23  = 1.0 / t22;
    real_type t26  = ModelPars[iM_m3];
    result__[ 3   ] = V__[3] - (-t17 * t23 * t26 * t7 + t23 * UM__[0]) * t2;
    real_type t33  = 1.0 / t26;
    result__[ 4   ] = V__[4] - (t17 * t22 * t3 * t33 + t33 * UM__[1]) * t2;
    real_type t43  = 1.0 / ModelPars[iM_inertia];
    result__[ 5   ] = V__[5] - (t43 * UM__[2] + t43 * (t26 - t22) * t7 * t3) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::Dfd_odeDxxpu_numRows() const { return 6; }
  integer Underwater::Dfd_odeDxxpu_numCols() const { return 16; }
  integer Underwater::Dfd_odeDxxpu_nnz()     const { return 47; }

  void
  Underwater::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 9   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 10  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 15  ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 2   ;
    iIndex[11] = 1   ; jIndex[11] = 3   ;
    iIndex[12] = 1   ; jIndex[12] = 4   ;
    iIndex[13] = 1   ; jIndex[13] = 7   ;
    iIndex[14] = 1   ; jIndex[14] = 8   ;
    iIndex[15] = 1   ; jIndex[15] = 9   ;
    iIndex[16] = 1   ; jIndex[16] = 10  ;
    iIndex[17] = 1   ; jIndex[17] = 15  ;
    iIndex[18] = 2   ; jIndex[18] = 2   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 8   ;
    iIndex[21] = 2   ; jIndex[21] = 11  ;
    iIndex[22] = 2   ; jIndex[22] = 15  ;
    iIndex[23] = 3   ; jIndex[23] = 3   ;
    iIndex[24] = 3   ; jIndex[24] = 4   ;
    iIndex[25] = 3   ; jIndex[25] = 5   ;
    iIndex[26] = 3   ; jIndex[26] = 9   ;
    iIndex[27] = 3   ; jIndex[27] = 10  ;
    iIndex[28] = 3   ; jIndex[28] = 11  ;
    iIndex[29] = 3   ; jIndex[29] = 12  ;
    iIndex[30] = 3   ; jIndex[30] = 15  ;
    iIndex[31] = 4   ; jIndex[31] = 3   ;
    iIndex[32] = 4   ; jIndex[32] = 4   ;
    iIndex[33] = 4   ; jIndex[33] = 5   ;
    iIndex[34] = 4   ; jIndex[34] = 9   ;
    iIndex[35] = 4   ; jIndex[35] = 10  ;
    iIndex[36] = 4   ; jIndex[36] = 11  ;
    iIndex[37] = 4   ; jIndex[37] = 13  ;
    iIndex[38] = 4   ; jIndex[38] = 15  ;
    iIndex[39] = 5   ; jIndex[39] = 3   ;
    iIndex[40] = 5   ; jIndex[40] = 4   ;
    iIndex[41] = 5   ; jIndex[41] = 5   ;
    iIndex[42] = 5   ; jIndex[42] = 9   ;
    iIndex[43] = 5   ; jIndex[43] = 10  ;
    iIndex[44] = 5   ; jIndex[44] = 11  ;
    iIndex[45] = 5   ; jIndex[45] = 14  ;
    iIndex[46] = 5   ; jIndex[46] = 15  ;
  }


  void
  Underwater::Dfd_odeDxxpu_sparse(
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
    real_type t1   = P__[iP_T];
    real_type t2   = XM__[4];
    real_type t3   = XM__[2];
    real_type t4   = cos(t3);
    real_type t6   = XM__[3];
    real_type t7   = sin(t3);
    real_type t9   = t2 * t4 - t6 * t7;
    result__[ 1   ] = -0.5e0 * t9 * t1;
    result__[ 2   ] = -0.5e0 * t4 * t1;
    real_type t15  = 0.5e0 * t7 * t1;
    result__[ 3   ] = -t15;
    result__[ 4   ] = __INV_DZETA;
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    result__[ 8   ] = -t2 * t7 - t4 * t6;
    result__[ 9   ] = result__[0];
    result__[ 10  ] = -0.5e0 * result__[8] * t1;
    result__[ 11  ] = t15;
    result__[ 12  ] = result__[6];
    result__[ 13  ] = __INV_DZETA;
    result__[ 14  ] = result__[10];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = result__[12];
    result__[ 17  ] = -t9;
    result__[ 18  ] = result__[9];
    result__[ 19  ] = -0.5e0 * t1;
    result__[ 20  ] = __INV_DZETA;
    result__[ 21  ] = result__[19];
    real_type t21  = XM__[5];
    result__[ 22  ] = -t21;
    result__[ 23  ] = result__[18];
    real_type t22  = t21 * t1;
    real_type t23  = ModelPars[iM_m3];
    real_type t24  = ModelPars[iM_m1];
    real_type t25  = 1.0 / t24;
    real_type t26  = t25 * t23;
    result__[ 24  ] = 0.5e0 * t26 * t22;
    real_type t28  = t2 * t1;
    result__[ 25  ] = 0.5e0 * t26 * t28;
    result__[ 26  ] = __INV_DZETA;
    result__[ 27  ] = result__[24];
    result__[ 28  ] = result__[25];
    result__[ 29  ] = -t25 * t1;
    result__[ 30  ] = t2 * t21 * t26 - t25 * UM__[0];
    real_type t35  = 1.0 / t23;
    real_type t36  = t35 * t24;
    result__[ 31  ] = -0.5e0 * t36 * t22;
    result__[ 32  ] = result__[23];
    real_type t39  = t6 * t1;
    result__[ 33  ] = -0.5e0 * t36 * t39;
    result__[ 34  ] = result__[31];
    result__[ 35  ] = __INV_DZETA;
    result__[ 36  ] = result__[33];
    result__[ 37  ] = -t35 * t1;
    result__[ 38  ] = -t21 * t36 * t6 - t35 * UM__[1];
    real_type t49  = 1.0 / ModelPars[iM_inertia];
    real_type t50  = t49 * (t23 - t24);
    result__[ 39  ] = -0.5e0 * t50 * t28;
    result__[ 40  ] = -0.5e0 * t50 * t39;
    result__[ 41  ] = result__[32];
    result__[ 42  ] = result__[39];
    result__[ 43  ] = result__[40];
    result__[ 44  ] = __INV_DZETA;
    result__[ 45  ] = -t49 * t1;
    result__[ 46  ] = -t2 * t50 * t6 - t49 * UM__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 47, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::D2fd_odeD2xxpu_numRows() const { return 16; }
  integer Underwater::D2fd_odeD2xxpu_numCols() const { return 16; }
  integer Underwater::D2fd_odeD2xxpu_nnz()     const { return 66; }

  void
  Underwater::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 9   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 10  ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 15  ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 5   ;
    iIndex[10] = 3   ; jIndex[10] = 8   ;
    iIndex[11] = 3   ; jIndex[11] = 10  ;
    iIndex[12] = 3   ; jIndex[12] = 11  ;
    iIndex[13] = 3   ; jIndex[13] = 15  ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
    iIndex[15] = 4   ; jIndex[15] = 3   ;
    iIndex[16] = 4   ; jIndex[16] = 5   ;
    iIndex[17] = 4   ; jIndex[17] = 8   ;
    iIndex[18] = 4   ; jIndex[18] = 9   ;
    iIndex[19] = 4   ; jIndex[19] = 11  ;
    iIndex[20] = 4   ; jIndex[20] = 15  ;
    iIndex[21] = 5   ; jIndex[21] = 3   ;
    iIndex[22] = 5   ; jIndex[22] = 4   ;
    iIndex[23] = 5   ; jIndex[23] = 9   ;
    iIndex[24] = 5   ; jIndex[24] = 10  ;
    iIndex[25] = 5   ; jIndex[25] = 15  ;
    iIndex[26] = 8   ; jIndex[26] = 2   ;
    iIndex[27] = 8   ; jIndex[27] = 3   ;
    iIndex[28] = 8   ; jIndex[28] = 4   ;
    iIndex[29] = 8   ; jIndex[29] = 8   ;
    iIndex[30] = 8   ; jIndex[30] = 9   ;
    iIndex[31] = 8   ; jIndex[31] = 10  ;
    iIndex[32] = 8   ; jIndex[32] = 15  ;
    iIndex[33] = 9   ; jIndex[33] = 2   ;
    iIndex[34] = 9   ; jIndex[34] = 4   ;
    iIndex[35] = 9   ; jIndex[35] = 5   ;
    iIndex[36] = 9   ; jIndex[36] = 8   ;
    iIndex[37] = 9   ; jIndex[37] = 10  ;
    iIndex[38] = 9   ; jIndex[38] = 11  ;
    iIndex[39] = 9   ; jIndex[39] = 15  ;
    iIndex[40] = 10  ; jIndex[40] = 2   ;
    iIndex[41] = 10  ; jIndex[41] = 3   ;
    iIndex[42] = 10  ; jIndex[42] = 5   ;
    iIndex[43] = 10  ; jIndex[43] = 8   ;
    iIndex[44] = 10  ; jIndex[44] = 9   ;
    iIndex[45] = 10  ; jIndex[45] = 11  ;
    iIndex[46] = 10  ; jIndex[46] = 15  ;
    iIndex[47] = 11  ; jIndex[47] = 3   ;
    iIndex[48] = 11  ; jIndex[48] = 4   ;
    iIndex[49] = 11  ; jIndex[49] = 9   ;
    iIndex[50] = 11  ; jIndex[50] = 10  ;
    iIndex[51] = 11  ; jIndex[51] = 15  ;
    iIndex[52] = 12  ; jIndex[52] = 15  ;
    iIndex[53] = 13  ; jIndex[53] = 15  ;
    iIndex[54] = 14  ; jIndex[54] = 15  ;
    iIndex[55] = 15  ; jIndex[55] = 2   ;
    iIndex[56] = 15  ; jIndex[56] = 3   ;
    iIndex[57] = 15  ; jIndex[57] = 4   ;
    iIndex[58] = 15  ; jIndex[58] = 5   ;
    iIndex[59] = 15  ; jIndex[59] = 8   ;
    iIndex[60] = 15  ; jIndex[60] = 9   ;
    iIndex[61] = 15  ; jIndex[61] = 10  ;
    iIndex[62] = 15  ; jIndex[62] = 11  ;
    iIndex[63] = 15  ; jIndex[63] = 12  ;
    iIndex[64] = 15  ; jIndex[64] = 13  ;
    iIndex[65] = 15  ; jIndex[65] = 14  ;
  }


  void
  Underwater::D2fd_odeD2xxpu_sparse(
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
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t7   = XR__[iX_vx] / 2 + XL__[iX_vx] / 2;
    real_type t11  = XR__[iX_theta] / 2 + XL__[iX_theta] / 2;
    real_type t12  = cos(t11);
    real_type t17  = XR__[iX_vz] / 2 + XL__[iX_vz] / 2;
    real_type t18  = sin(t11);
    real_type t20  = -t12 * t7 - t18 * t17;
    real_type t23  = LM__[1];
    real_type t24  = t2 * t23;
    real_type t27  = -t12 * t17 + t18 * t7;
    result__[ 0   ] = -t20 * t3 / 4 - t27 * t24 / 4;
    result__[ 1   ] = t12 * t24 / 4 + t18 * t3 / 4;
    result__[ 2   ] = -t12 * t3 / 4 + t18 * t24 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = t27 * t1 / 2 - t20 * t23 / 2;
    result__[ 7   ] = result__[4];
    real_type t41  = LM__[5];
    real_type t43  = ModelPars[iM_m3];
    real_type t44  = ModelPars[iM_m1];
    real_type t47  = 1.0 / ModelPars[iM_inertia];
    real_type t48  = t47 * (t43 - t44);
    result__[ 8   ] = -t48 * t2 * t41 / 4;
    real_type t51  = LM__[4];
    real_type t53  = 1.0 / t43;
    real_type t54  = t53 * t44;
    result__[ 9   ] = -t54 * t2 * t51 / 4;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    real_type t62  = XR__[iX_Omega] / 2 + XL__[iX_Omega] / 2;
    result__[ 13  ] = -t48 * t17 * t41 / 2 - t54 * t62 * t51 / 2 - t12 * t1 / 2 + t18 * t23 / 2;
    result__[ 14  ] = result__[5];
    result__[ 15  ] = result__[11];
    real_type t68  = LM__[3];
    real_type t70  = 1.0 / t44;
    real_type t71  = t70 * t43;
    result__[ 16  ] = t71 * t2 * t68 / 4;
    result__[ 17  ] = result__[14];
    result__[ 18  ] = result__[15];
    result__[ 19  ] = result__[16];
    result__[ 20  ] = -t48 * t7 * t41 / 2 + t71 * t62 * t68 / 2 - t18 * t1 / 2 - t12 * t23 / 2;
    result__[ 21  ] = result__[12];
    result__[ 22  ] = result__[19];
    result__[ 23  ] = result__[21];
    result__[ 24  ] = result__[22];
    result__[ 25  ] = t71 * t17 * t68 / 2 - t54 * t7 * t51 / 2 - LM__[2] / 2;
    result__[ 26  ] = result__[3];
    result__[ 27  ] = result__[10];
    result__[ 28  ] = result__[17];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[28];
    result__[ 32  ] = result__[6];
    result__[ 33  ] = result__[30];
    result__[ 34  ] = result__[18];
    result__[ 35  ] = result__[23];
    result__[ 36  ] = result__[33];
    result__[ 37  ] = result__[34];
    result__[ 38  ] = result__[35];
    result__[ 39  ] = result__[13];
    result__[ 40  ] = result__[31];
    result__[ 41  ] = result__[37];
    result__[ 42  ] = result__[24];
    result__[ 43  ] = result__[40];
    result__[ 44  ] = result__[41];
    result__[ 45  ] = result__[42];
    result__[ 46  ] = result__[20];
    result__[ 47  ] = result__[38];
    result__[ 48  ] = result__[45];
    result__[ 49  ] = result__[47];
    result__[ 50  ] = result__[48];
    result__[ 51  ] = result__[25];
    result__[ 52  ] = -t68 * t70;
    result__[ 53  ] = -t51 * t53;
    result__[ 54  ] = -t41 * t47;
    result__[ 55  ] = result__[32];
    result__[ 56  ] = result__[39];
    result__[ 57  ] = result__[46];
    result__[ 58  ] = result__[51];
    result__[ 59  ] = result__[55];
    result__[ 60  ] = result__[56];
    result__[ 61  ] = result__[57];
    result__[ 62  ] = result__[58];
    result__[ 63  ] = result__[52];
    result__[ 64  ] = result__[53];
    result__[ 65  ] = result__[54];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 66, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Underwater_Methods_Guess.cc
