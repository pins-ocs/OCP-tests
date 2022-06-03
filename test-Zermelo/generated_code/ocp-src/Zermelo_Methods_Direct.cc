/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_Guess.cc                                       |
 |                                                                       |
 |  version: 1.0   date 4/6/2022                                         |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


using namespace std;

namespace ZermeloDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Zermelo::fd_ode_numEqns() const { return 5; }

  void
  Zermelo::fd_ode_eval(
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
    real_type QM__[1], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = XM__[4];
    real_type t4   = XM__[0];
    real_type t5   = XM__[1];
    real_type t6   = velX(t4, t5);
    result__[ 0   ] = V__[0] - (XM__[2] + t6) * t2;
    real_type t11  = velY(t4, t5);
    result__[ 1   ] = V__[1] - (XM__[3] + t11) * t2;
    real_type t16  = ModelPars[iM_S] * t2;
    real_type t17  = UM__[0];
    real_type t18  = cos(t17);
    result__[ 2   ] = -t18 * t16 + V__[2];
    real_type t21  = sin(t17);
    result__[ 3   ] = -t21 * t16 + V__[3];
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::Dfd_odeDxxpu_numRows() const { return 5; }
  integer Zermelo::Dfd_odeDxxpu_numCols() const { return 11; }
  integer Zermelo::Dfd_odeDxxpu_nnz()     const { return 28; }

  void
  Zermelo::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 1   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 1   ; jIndex[14] = 8   ;
    iIndex[15] = 1   ; jIndex[15] = 9   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 4   ;
    iIndex[18] = 2   ; jIndex[18] = 7   ;
    iIndex[19] = 2   ; jIndex[19] = 9   ;
    iIndex[20] = 2   ; jIndex[20] = 10  ;
    iIndex[21] = 3   ; jIndex[21] = 3   ;
    iIndex[22] = 3   ; jIndex[22] = 4   ;
    iIndex[23] = 3   ; jIndex[23] = 8   ;
    iIndex[24] = 3   ; jIndex[24] = 9   ;
    iIndex[25] = 3   ; jIndex[25] = 10  ;
    iIndex[26] = 4   ; jIndex[26] = 4   ;
    iIndex[27] = 4   ; jIndex[27] = 9   ;
  }


  void
  Zermelo::Dfd_odeDxxpu_sparse(
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
    real_type QM__[1], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XM__[4];
    real_type t2   = XM__[0];
    real_type t3   = XM__[1];
    real_type t4   = velX_D_1(t2, t3);
    real_type t6   = 0.5e0 * t4 * t1;
    result__[ 0   ] = -t6 - __INV_DZETA;
    real_type t7   = velX_D_2(t2, t3);
    result__[ 1   ] = -0.5e0 * t7 * t1;
    result__[ 2   ] = -0.5e0 * t1;
    real_type t13  = velX(t2, t3);
    result__[ 3   ] = -0.5e0 * XM__[2] - 0.5e0 * t13;
    result__[ 4   ] = -t6 + __INV_DZETA;
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    real_type t15  = velY_D_1(t2, t3);
    result__[ 8   ] = -0.5e0 * t15 * t1;
    real_type t18  = velY_D_2(t2, t3);
    real_type t20  = 0.5e0 * t18 * t1;
    result__[ 9   ] = -t20 - __INV_DZETA;
    result__[ 10  ] = result__[6];
    real_type t23  = velY(t2, t3);
    result__[ 11  ] = -0.5e0 * XM__[3] - 0.5e0 * t23;
    result__[ 12  ] = result__[8];
    result__[ 13  ] = -t20 + __INV_DZETA;
    result__[ 14  ] = result__[10];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = -__INV_DZETA;
    real_type t25  = ModelPars[iM_S];
    real_type t26  = UM__[0];
    real_type t27  = cos(t26);
    result__[ 17  ] = -0.5e0 * t27 * t25;
    result__[ 18  ] = __INV_DZETA;
    result__[ 19  ] = result__[17];
    real_type t30  = t25 * t1;
    real_type t31  = sin(t26);
    result__[ 20  ] = t31 * t30;
    result__[ 21  ] = result__[16];
    result__[ 22  ] = -0.5e0 * t31 * t25;
    result__[ 23  ] = __INV_DZETA;
    result__[ 24  ] = result__[22];
    result__[ 25  ] = -t27 * t30;
    result__[ 26  ] = result__[21];
    result__[ 27  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 28, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Zermelo::D2fd_odeD2xxpu_numRows() const { return 11; }
  integer Zermelo::D2fd_odeD2xxpu_numCols() const { return 11; }
  integer Zermelo::D2fd_odeD2xxpu_nnz()     const { return 53; }

  void
  Zermelo::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 9   ;
    iIndex[12] = 2   ; jIndex[12] = 4   ;
    iIndex[13] = 2   ; jIndex[13] = 9   ;
    iIndex[14] = 3   ; jIndex[14] = 4   ;
    iIndex[15] = 3   ; jIndex[15] = 9   ;
    iIndex[16] = 4   ; jIndex[16] = 0   ;
    iIndex[17] = 4   ; jIndex[17] = 1   ;
    iIndex[18] = 4   ; jIndex[18] = 2   ;
    iIndex[19] = 4   ; jIndex[19] = 3   ;
    iIndex[20] = 4   ; jIndex[20] = 5   ;
    iIndex[21] = 4   ; jIndex[21] = 6   ;
    iIndex[22] = 4   ; jIndex[22] = 7   ;
    iIndex[23] = 4   ; jIndex[23] = 8   ;
    iIndex[24] = 4   ; jIndex[24] = 10  ;
    iIndex[25] = 5   ; jIndex[25] = 0   ;
    iIndex[26] = 5   ; jIndex[26] = 1   ;
    iIndex[27] = 5   ; jIndex[27] = 4   ;
    iIndex[28] = 5   ; jIndex[28] = 5   ;
    iIndex[29] = 5   ; jIndex[29] = 6   ;
    iIndex[30] = 5   ; jIndex[30] = 9   ;
    iIndex[31] = 6   ; jIndex[31] = 0   ;
    iIndex[32] = 6   ; jIndex[32] = 1   ;
    iIndex[33] = 6   ; jIndex[33] = 4   ;
    iIndex[34] = 6   ; jIndex[34] = 5   ;
    iIndex[35] = 6   ; jIndex[35] = 6   ;
    iIndex[36] = 6   ; jIndex[36] = 9   ;
    iIndex[37] = 7   ; jIndex[37] = 4   ;
    iIndex[38] = 7   ; jIndex[38] = 9   ;
    iIndex[39] = 8   ; jIndex[39] = 4   ;
    iIndex[40] = 8   ; jIndex[40] = 9   ;
    iIndex[41] = 9   ; jIndex[41] = 0   ;
    iIndex[42] = 9   ; jIndex[42] = 1   ;
    iIndex[43] = 9   ; jIndex[43] = 2   ;
    iIndex[44] = 9   ; jIndex[44] = 3   ;
    iIndex[45] = 9   ; jIndex[45] = 5   ;
    iIndex[46] = 9   ; jIndex[46] = 6   ;
    iIndex[47] = 9   ; jIndex[47] = 7   ;
    iIndex[48] = 9   ; jIndex[48] = 8   ;
    iIndex[49] = 9   ; jIndex[49] = 10  ;
    iIndex[50] = 10  ; jIndex[50] = 4   ;
    iIndex[51] = 10  ; jIndex[51] = 9   ;
    iIndex[52] = 10  ; jIndex[52] = 10  ;
  }


  void
  Zermelo::D2fd_odeD2xxpu_sparse(
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
    real_type QM__[1], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t5   = XR__[iX_T] / 2 + XL__[iX_T] / 2;
    real_type t6   = t5 * t1;
    real_type t10  = XR__[iX_x] / 2 + XL__[iX_x] / 2;
    real_type t14  = XR__[iX_y] / 2 + XL__[iX_y] / 2;
    real_type t15  = velX_D_1_1(t10, t14);
    real_type t17  = LM__[1];
    real_type t18  = t5 * t17;
    real_type t19  = velY_D_1_1(t10, t14);
    result__[ 0   ] = -t15 * t6 / 4 - t19 * t18 / 4;
    real_type t22  = velX_D_1_2(t10, t14);
    real_type t24  = velY_D_1_2(t10, t14);
    result__[ 1   ] = -t24 * t18 / 4 - t22 * t6 / 4;
    real_type t27  = velX_D_1(t10, t14);
    real_type t29  = velY_D_1(t10, t14);
    result__[ 2   ] = -t27 * t1 / 4 - t29 * t17 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    real_type t32  = velX_D_2_2(t10, t14);
    real_type t34  = velY_D_2_2(t10, t14);
    result__[ 7   ] = -t34 * t18 / 4 - t32 * t6 / 4;
    real_type t37  = velX_D_2(t10, t14);
    real_type t39  = velY_D_2(t10, t14);
    result__[ 8   ] = -t37 * t1 / 4 - t39 * t17 / 4;
    result__[ 9   ] = result__[6];
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = -t1 / 4;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = -t17 / 4;
    result__[ 15  ] = result__[14];
    result__[ 16  ] = result__[5];
    result__[ 17  ] = result__[11];
    result__[ 18  ] = result__[13];
    result__[ 19  ] = result__[15];
    result__[ 20  ] = result__[16];
    result__[ 21  ] = result__[17];
    result__[ 22  ] = result__[18];
    result__[ 23  ] = result__[19];
    real_type t44  = LM__[2];
    real_type t45  = ModelPars[iM_S];
    real_type t47  = UM__[0];
    real_type t48  = sin(t47);
    real_type t50  = LM__[3];
    real_type t52  = cos(t47);
    result__[ 24  ] = t48 * t45 * t44 / 2 - t52 * t45 * t50 / 2;
    result__[ 25  ] = result__[3];
    result__[ 26  ] = result__[9];
    result__[ 27  ] = result__[20];
    result__[ 28  ] = result__[25];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[29];
    result__[ 32  ] = result__[10];
    result__[ 33  ] = result__[21];
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[32];
    result__[ 36  ] = result__[33];
    result__[ 37  ] = result__[22];
    result__[ 38  ] = result__[37];
    result__[ 39  ] = result__[23];
    result__[ 40  ] = result__[39];
    result__[ 41  ] = result__[30];
    result__[ 42  ] = result__[36];
    result__[ 43  ] = result__[38];
    result__[ 44  ] = result__[40];
    result__[ 45  ] = result__[41];
    result__[ 46  ] = result__[42];
    result__[ 47  ] = result__[43];
    result__[ 48  ] = result__[44];
    result__[ 49  ] = result__[24];
    result__[ 50  ] = result__[49];
    result__[ 51  ] = result__[50];
    result__[ 52  ] = t52 * t45 * t5 * t44 + t48 * t45 * t5 * t50;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 53, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Zermelo_Methods_Guess.cc
