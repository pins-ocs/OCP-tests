/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_Guess.cc                          |
 |                                                                       |
 |  version: 1.0   date 3/6/2022                                         |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace EconomicGrowthModel2Define {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer EconomicGrowthModel2::fd_ode_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::fd_ode_eval(
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
    result__[ 0   ] = -t2 * XM__[2] + V__[0];
    real_type t6   = UM__[0];
    real_type t9   = Q(XM__[0], XM__[1]);
    result__[ 1   ] = -t2 * t9 * t6 + V__[2];
    result__[ 2   ] = -t2 * XM__[3] + V__[1];
    result__[ 3   ] = V__[3] - t2 * t9 * (1 - t6);
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::Dfd_odeDxxpu_numRows() const { return 5; }
  integer EconomicGrowthModel2::Dfd_odeDxxpu_numCols() const { return 11; }
  integer EconomicGrowthModel2::Dfd_odeDxxpu_nnz()     const { return 32; }

  void
  EconomicGrowthModel2::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 1   ; jIndex[13] = 9   ;
    iIndex[14] = 1   ; jIndex[14] = 10  ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 3   ;
    iIndex[17] = 2   ; jIndex[17] = 4   ;
    iIndex[18] = 2   ; jIndex[18] = 6   ;
    iIndex[19] = 2   ; jIndex[19] = 8   ;
    iIndex[20] = 2   ; jIndex[20] = 9   ;
    iIndex[21] = 3   ; jIndex[21] = 0   ;
    iIndex[22] = 3   ; jIndex[22] = 1   ;
    iIndex[23] = 3   ; jIndex[23] = 3   ;
    iIndex[24] = 3   ; jIndex[24] = 4   ;
    iIndex[25] = 3   ; jIndex[25] = 5   ;
    iIndex[26] = 3   ; jIndex[26] = 6   ;
    iIndex[27] = 3   ; jIndex[27] = 8   ;
    iIndex[28] = 3   ; jIndex[28] = 9   ;
    iIndex[29] = 3   ; jIndex[29] = 10  ;
    iIndex[30] = 4   ; jIndex[30] = 4   ;
    iIndex[31] = 4   ; jIndex[31] = 9   ;
  }


  void
  EconomicGrowthModel2::Dfd_odeDxxpu_sparse(
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
    result__[ 0   ] = -__INV_DZETA;
    real_type t1   = XM__[4];
    result__[ 1   ] = -0.5e0 * t1;
    result__[ 2   ] = -0.5e0 * XM__[2];
    result__[ 3   ] = __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t5   = UM__[0];
    real_type t6   = XM__[0];
    real_type t7   = XM__[1];
    real_type t8   = Q_D_1(t6, t7);
    result__[ 6   ] = -0.5e0 * t1 * t8 * t5;
    real_type t12  = Q_D_2(t6, t7);
    result__[ 7   ] = -0.5e0 * t1 * t12 * t5;
    result__[ 8   ] = result__[0];
    real_type t16  = Q(t6, t7);
    result__[ 9   ] = -0.5e0 * t16 * t5;
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    result__[ 12  ] = __INV_DZETA;
    result__[ 13  ] = result__[9];
    real_type t19  = t1 * t16;
    result__[ 14  ] = -t19;
    result__[ 15  ] = result__[8];
    result__[ 16  ] = result__[4];
    result__[ 17  ] = -0.5e0 * XM__[3];
    result__[ 18  ] = __INV_DZETA;
    result__[ 19  ] = result__[16];
    result__[ 20  ] = result__[17];
    real_type t22  = 1 - t5;
    result__[ 21  ] = -0.5e0 * t1 * t8 * t22;
    result__[ 22  ] = -0.5e0 * t1 * t12 * t22;
    result__[ 23  ] = result__[15];
    result__[ 24  ] = -0.5e0 * t16 * t22;
    result__[ 25  ] = result__[21];
    result__[ 26  ] = result__[22];
    result__[ 27  ] = __INV_DZETA;
    result__[ 28  ] = result__[24];
    result__[ 29  ] = t19;
    result__[ 30  ] = result__[23];
    result__[ 31  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 32, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::D2fd_odeD2xxpu_numRows() const { return 11; }
  integer EconomicGrowthModel2::D2fd_odeD2xxpu_numCols() const { return 11; }
  integer EconomicGrowthModel2::D2fd_odeD2xxpu_nnz()     const { return 60; }

  void
  EconomicGrowthModel2::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 10  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 9   ;
    iIndex[13] = 1   ; jIndex[13] = 10  ;
    iIndex[14] = 2   ; jIndex[14] = 4   ;
    iIndex[15] = 2   ; jIndex[15] = 9   ;
    iIndex[16] = 3   ; jIndex[16] = 4   ;
    iIndex[17] = 3   ; jIndex[17] = 9   ;
    iIndex[18] = 4   ; jIndex[18] = 0   ;
    iIndex[19] = 4   ; jIndex[19] = 1   ;
    iIndex[20] = 4   ; jIndex[20] = 2   ;
    iIndex[21] = 4   ; jIndex[21] = 3   ;
    iIndex[22] = 4   ; jIndex[22] = 5   ;
    iIndex[23] = 4   ; jIndex[23] = 6   ;
    iIndex[24] = 4   ; jIndex[24] = 7   ;
    iIndex[25] = 4   ; jIndex[25] = 8   ;
    iIndex[26] = 4   ; jIndex[26] = 10  ;
    iIndex[27] = 5   ; jIndex[27] = 0   ;
    iIndex[28] = 5   ; jIndex[28] = 1   ;
    iIndex[29] = 5   ; jIndex[29] = 4   ;
    iIndex[30] = 5   ; jIndex[30] = 5   ;
    iIndex[31] = 5   ; jIndex[31] = 6   ;
    iIndex[32] = 5   ; jIndex[32] = 9   ;
    iIndex[33] = 5   ; jIndex[33] = 10  ;
    iIndex[34] = 6   ; jIndex[34] = 0   ;
    iIndex[35] = 6   ; jIndex[35] = 1   ;
    iIndex[36] = 6   ; jIndex[36] = 4   ;
    iIndex[37] = 6   ; jIndex[37] = 5   ;
    iIndex[38] = 6   ; jIndex[38] = 6   ;
    iIndex[39] = 6   ; jIndex[39] = 9   ;
    iIndex[40] = 6   ; jIndex[40] = 10  ;
    iIndex[41] = 7   ; jIndex[41] = 4   ;
    iIndex[42] = 7   ; jIndex[42] = 9   ;
    iIndex[43] = 8   ; jIndex[43] = 4   ;
    iIndex[44] = 8   ; jIndex[44] = 9   ;
    iIndex[45] = 9   ; jIndex[45] = 0   ;
    iIndex[46] = 9   ; jIndex[46] = 1   ;
    iIndex[47] = 9   ; jIndex[47] = 2   ;
    iIndex[48] = 9   ; jIndex[48] = 3   ;
    iIndex[49] = 9   ; jIndex[49] = 5   ;
    iIndex[50] = 9   ; jIndex[50] = 6   ;
    iIndex[51] = 9   ; jIndex[51] = 7   ;
    iIndex[52] = 9   ; jIndex[52] = 8   ;
    iIndex[53] = 9   ; jIndex[53] = 10  ;
    iIndex[54] = 10  ; jIndex[54] = 0   ;
    iIndex[55] = 10  ; jIndex[55] = 1   ;
    iIndex[56] = 10  ; jIndex[56] = 4   ;
    iIndex[57] = 10  ; jIndex[57] = 5   ;
    iIndex[58] = 10  ; jIndex[58] = 6   ;
    iIndex[59] = 10  ; jIndex[59] = 9   ;
  }


  void
  EconomicGrowthModel2::D2fd_odeD2xxpu_sparse(
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
    real_type t1   = LM__[1];
    real_type t2   = UM__[0];
    real_type t3   = t2 * t1;
    real_type t7   = XR__[iX_x1] / 2 + XL__[iX_x1] / 2;
    real_type t11  = XR__[iX_x2] / 2 + XL__[iX_x2] / 2;
    real_type t12  = Q_D_1_1(t7, t11);
    real_type t16  = XR__[iX_T] / 2 + XL__[iX_T] / 2;
    real_type t17  = t16 * t12;
    real_type t19  = LM__[3];
    real_type t21  = (1 - t2) * t19;
    result__[ 0   ] = -t17 * t21 / 4 - t17 * t3 / 4;
    real_type t24  = Q_D_1_2(t7, t11);
    real_type t25  = t16 * t24;
    result__[ 1   ] = -t25 * t21 / 4 - t25 * t3 / 4;
    real_type t29  = Q_D_1(t7, t11);
    result__[ 2   ] = -t29 * t21 / 4 - t29 * t3 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = -t16 * t29 * t1 / 2 + t16 * t29 * t19 / 2;
    result__[ 7   ] = result__[4];
    real_type t38  = Q_D_2_2(t7, t11);
    real_type t39  = t16 * t38;
    result__[ 8   ] = -t39 * t21 / 4 - t39 * t3 / 4;
    real_type t43  = Q_D_2(t7, t11);
    result__[ 9   ] = -t43 * t21 / 4 - t43 * t3 / 4;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = -t16 * t43 * t1 / 2 + t16 * t43 * t19 / 2;
    result__[ 14  ] = -LM__[0] / 4;
    result__[ 15  ] = result__[14];
    result__[ 16  ] = -LM__[2] / 4;
    result__[ 17  ] = result__[16];
    result__[ 18  ] = result__[5];
    result__[ 19  ] = result__[12];
    result__[ 20  ] = result__[15];
    result__[ 21  ] = result__[17];
    result__[ 22  ] = result__[18];
    result__[ 23  ] = result__[19];
    result__[ 24  ] = result__[20];
    result__[ 25  ] = result__[21];
    real_type t56  = Q(t7, t11);
    result__[ 26  ] = -t56 * t1 / 2 + t56 * t19 / 2;
    result__[ 27  ] = result__[3];
    result__[ 28  ] = result__[10];
    result__[ 29  ] = result__[22];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[28];
    result__[ 32  ] = result__[29];
    result__[ 33  ] = result__[6];
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[11];
    result__[ 36  ] = result__[23];
    result__[ 37  ] = result__[34];
    result__[ 38  ] = result__[35];
    result__[ 39  ] = result__[36];
    result__[ 40  ] = result__[13];
    result__[ 41  ] = result__[24];
    result__[ 42  ] = result__[41];
    result__[ 43  ] = result__[25];
    result__[ 44  ] = result__[43];
    result__[ 45  ] = result__[32];
    result__[ 46  ] = result__[39];
    result__[ 47  ] = result__[42];
    result__[ 48  ] = result__[44];
    result__[ 49  ] = result__[45];
    result__[ 50  ] = result__[46];
    result__[ 51  ] = result__[47];
    result__[ 52  ] = result__[48];
    result__[ 53  ] = result__[26];
    result__[ 54  ] = result__[33];
    result__[ 55  ] = result__[40];
    result__[ 56  ] = result__[53];
    result__[ 57  ] = result__[54];
    result__[ 58  ] = result__[55];
    result__[ 59  ] = result__[56];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 60, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: EconomicGrowthModel2_Methods_Guess.cc
