/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_Guess.cc                                 |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace GoddardRocketDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer GoddardRocket::fd_ode_numEqns() const { return 3; }

  void
  GoddardRocket::fd_ode_eval(
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
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = XM__[1];
    result__[ 0   ] = -t2 * t1 + V__[0];
    real_type t6   = UM__[0];
    real_type t7   = XM__[0];
    real_type t8   = DD(t7, t2);
    real_type t13  = gg(t7);
    result__[ 1   ] = V__[1] - (1.0 / XM__[2] * (t6 - t8) - t13) * t1;
    result__[ 2   ] = V__[2] + 1.0 / ModelPars[iM_c] * t6 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::Dfd_odeDxxup_numRows() const { return 3; }
  integer GoddardRocket::Dfd_odeDxxup_numCols() const { return 8; }
  integer GoddardRocket::Dfd_odeDxxup_nnz()     const { return 17; }

  void
  GoddardRocket::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 2   ; jIndex[13] = 2   ;
    iIndex[14] = 2   ; jIndex[14] = 5   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 2   ; jIndex[16] = 7   ;
  }


  void
  GoddardRocket::Dfd_odeDxxup_sparse(
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
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    real_type t1   = P__[iP_TimeSize];
    result__[ 1   ] = -0.5e0 * t1;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = result__[1];
    real_type t3   = XM__[1];
    result__[ 4   ] = -t3;
    real_type t4   = XM__[0];
    real_type t5   = DD_D_1(t4, t3);
    real_type t6   = XM__[2];
    real_type t7   = 1.0 / t6;
    real_type t9   = gg_D(t4);
    result__[ 5   ] = -0.5e0 * (-t7 * t5 - t9) * t1;
    real_type t13  = DD_D_2(t4, t3);
    real_type t16  = 0.5e0 * t7 * t13 * t1;
    result__[ 6   ] = t16 + result__[0];
    real_type t17  = UM__[0];
    real_type t18  = DD(t4, t3);
    real_type t19  = t17 - t18;
    real_type t21  = t6 * t6;
    result__[ 7   ] = 0.5e0 / t21 * t19 * t1;
    result__[ 8   ] = result__[5];
    result__[ 9   ] = t16 + __INV_DZETA;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = -t7 * t1;
    real_type t26  = gg(t4);
    result__[ 12  ] = -t7 * t19 + t26;
    result__[ 13  ] = result__[0];
    result__[ 14  ] = __INV_DZETA;
    real_type t28  = 1.0 / ModelPars[iM_c];
    result__[ 15  ] = t28 * t1;
    result__[ 16  ] = t28 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 17, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::D2fd_odeD2xxup_numRows() const { return 8; }
  integer GoddardRocket::D2fd_odeD2xxup_numCols() const { return 8; }
  integer GoddardRocket::D2fd_odeD2xxup_nnz()     const { return 54; }

  void
  GoddardRocket::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 7   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 4   ;
    iIndex[19] = 2   ; jIndex[19] = 5   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
    iIndex[21] = 2   ; jIndex[21] = 7   ;
    iIndex[22] = 3   ; jIndex[22] = 0   ;
    iIndex[23] = 3   ; jIndex[23] = 1   ;
    iIndex[24] = 3   ; jIndex[24] = 2   ;
    iIndex[25] = 3   ; jIndex[25] = 3   ;
    iIndex[26] = 3   ; jIndex[26] = 4   ;
    iIndex[27] = 3   ; jIndex[27] = 5   ;
    iIndex[28] = 3   ; jIndex[28] = 7   ;
    iIndex[29] = 4   ; jIndex[29] = 0   ;
    iIndex[30] = 4   ; jIndex[30] = 1   ;
    iIndex[31] = 4   ; jIndex[31] = 2   ;
    iIndex[32] = 4   ; jIndex[32] = 3   ;
    iIndex[33] = 4   ; jIndex[33] = 4   ;
    iIndex[34] = 4   ; jIndex[34] = 5   ;
    iIndex[35] = 4   ; jIndex[35] = 7   ;
    iIndex[36] = 5   ; jIndex[36] = 0   ;
    iIndex[37] = 5   ; jIndex[37] = 1   ;
    iIndex[38] = 5   ; jIndex[38] = 2   ;
    iIndex[39] = 5   ; jIndex[39] = 3   ;
    iIndex[40] = 5   ; jIndex[40] = 4   ;
    iIndex[41] = 5   ; jIndex[41] = 5   ;
    iIndex[42] = 5   ; jIndex[42] = 6   ;
    iIndex[43] = 5   ; jIndex[43] = 7   ;
    iIndex[44] = 6   ; jIndex[44] = 2   ;
    iIndex[45] = 6   ; jIndex[45] = 5   ;
    iIndex[46] = 6   ; jIndex[46] = 7   ;
    iIndex[47] = 7   ; jIndex[47] = 0   ;
    iIndex[48] = 7   ; jIndex[48] = 1   ;
    iIndex[49] = 7   ; jIndex[49] = 2   ;
    iIndex[50] = 7   ; jIndex[50] = 3   ;
    iIndex[51] = 7   ; jIndex[51] = 4   ;
    iIndex[52] = 7   ; jIndex[52] = 5   ;
    iIndex[53] = 7   ; jIndex[53] = 6   ;
  }


  void
  GoddardRocket::D2fd_odeD2xxup_sparse(
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
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[1];
    real_type t3   = P__[iP_TimeSize] * t1;
    real_type t7   = XR__[iX_h] / 2 + XL__[iX_h] / 2;
    real_type t11  = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t12  = DD_D_1_1(t7, t11);
    real_type t16  = XR__[iX_m] / 2 + XL__[iX_m] / 2;
    real_type t17  = 1.0 / t16;
    real_type t19  = gg_DD(t7);
    result__[ 0   ] = -(-t17 * t12 / 4 - t19 / 4) * t3;
    real_type t23  = DD_D_1_2(t7, t11);
    result__[ 1   ] = t17 * t23 * t3 / 4;
    real_type t26  = DD_D_1(t7, t11);
    real_type t27  = t16 * t16;
    real_type t28  = 1.0 / t27;
    result__[ 2   ] = -t28 * t26 * t3 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t33  = gg_D(t7);
    result__[ 6   ] = -(-t17 * t26 / 2 - t33 / 2) * t1;
    result__[ 7   ] = result__[4];
    real_type t37  = DD_D_2_2(t7, t11);
    result__[ 8   ] = t17 * t37 * t3 / 4;
    real_type t40  = DD_D_2(t7, t11);
    result__[ 9   ] = -t28 * t40 * t3 / 4;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = t17 * t40 * t1 / 2 - LM__[0] / 2;
    result__[ 14  ] = result__[5];
    result__[ 15  ] = result__[12];
    real_type t49  = DD(t7, t11);
    real_type t50  = UM__[0] - t49;
    result__[ 16  ] = -1.0 / t27 / t16 * t50 * t3 / 2;
    result__[ 17  ] = result__[14];
    result__[ 18  ] = result__[15];
    result__[ 19  ] = result__[16];
    result__[ 20  ] = t28 * t3 / 2;
    result__[ 21  ] = t28 * t50 * t1 / 2;
    result__[ 22  ] = result__[3];
    result__[ 23  ] = result__[10];
    result__[ 24  ] = result__[17];
    result__[ 25  ] = result__[22];
    result__[ 26  ] = result__[23];
    result__[ 27  ] = result__[24];
    result__[ 28  ] = result__[6];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[11];
    result__[ 31  ] = result__[18];
    result__[ 32  ] = result__[29];
    result__[ 33  ] = result__[30];
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[13];
    result__[ 36  ] = result__[27];
    result__[ 37  ] = result__[34];
    result__[ 38  ] = result__[19];
    result__[ 39  ] = result__[36];
    result__[ 40  ] = result__[37];
    result__[ 41  ] = result__[38];
    result__[ 42  ] = result__[20];
    result__[ 43  ] = result__[21];
    result__[ 44  ] = result__[42];
    result__[ 45  ] = result__[44];
    result__[ 46  ] = -t17 * t1 + LM__[2] / ModelPars[iM_c];
    result__[ 47  ] = result__[28];
    result__[ 48  ] = result__[35];
    result__[ 49  ] = result__[43];
    result__[ 50  ] = result__[47];
    result__[ 51  ] = result__[48];
    result__[ 52  ] = result__[49];
    result__[ 53  ] = result__[46];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 54, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: GoddardRocket_Methods_Guess.cc
