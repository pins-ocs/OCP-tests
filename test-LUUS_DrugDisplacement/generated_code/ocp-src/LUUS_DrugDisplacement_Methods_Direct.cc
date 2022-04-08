/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_Guess.cc                         |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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

namespace LUUS_DrugDisplacementDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer LUUS_DrugDisplacement::fd_ode_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::fd_ode_eval(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = XM__[0];
    real_type t4   = XM__[1];
    real_type t5   = g1(t3, t4);
    real_type t6   = t5 * P__[iP_T];
    real_type t7   = g4(t3, t4);
    real_type t12  = UM__[0] - 2 * t4;
    result__[ 0   ] = V__[0] - ((0.2e-1 - t3) * t7 + 0.464e2 * t12 * t3) * t6;
    real_type t18  = g3(t3, t4);
    result__[ 1   ] = V__[1] - (t12 * t18 + 0.928e0 - 0.464e2 * t3) * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::Dfd_odeDxxup_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::Dfd_odeDxxup_numCols() const { return 6; }
  integer LUUS_DrugDisplacement::Dfd_odeDxxup_nnz()     const { return 12; }

  void
  LUUS_DrugDisplacement::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 4   ;
    iIndex[11] = 1   ; jIndex[11] = 5   ;
  }


  void
  LUUS_DrugDisplacement::Dfd_odeDxxup_sparse(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = XM__[0];
    real_type t3   = XM__[1];
    real_type t4   = g1_D_1(t2, t3);
    real_type t5   = t4 * t1;
    real_type t6   = g4(t2, t3);
    real_type t7   = 0.2e-1 - t2;
    real_type t9   = UM__[0];
    real_type t11  = t9 - 2 * t3;
    real_type t14  = t7 * t6 + 0.464e2 * t11 * t2;
    real_type t16  = 0.5e0 * t14 * t5;
    real_type t17  = g1(t2, t3);
    real_type t18  = t17 * t1;
    real_type t19  = g4_D_1(t2, t3);
    real_type t25  = 0.5e0 * (t7 * t19 - t6 + 0.464e2 * t9 - 0.928e2 * t3) * t18;
    result__[ 0   ] = -t16 - t25 - __INV_DZETA;
    real_type t26  = g1_D_2(t2, t3);
    real_type t27  = t26 * t1;
    real_type t30  = g4_D_2(t2, t3);
    result__[ 1   ] = -0.5e0 * t14 * t27 - 0.5e0 * (t7 * t30 - 0.928e2 * t2) * t18;
    result__[ 2   ] = -t16 - t25 + __INV_DZETA;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = -0.464e2 * t2 * t18;
    result__[ 5   ] = -t14 * t17;
    real_type t39  = g3(t2, t3);
    real_type t42  = t11 * t39 + 0.928e0 - 0.464e2 * t2;
    real_type t45  = g3_D_1(t2, t3);
    result__[ 6   ] = -0.5e0 * t42 * t5 - 0.5e0 * (t11 * t45 - 0.464e2) * t18;
    real_type t51  = 0.5e0 * t42 * t27;
    real_type t52  = g3_D_2(t2, t3);
    real_type t57  = 0.5e0 * (t11 * t52 - 2 * t39) * t18;
    result__[ 7   ] = -t51 - t57 - __INV_DZETA;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = -t51 - t57 + __INV_DZETA;
    result__[ 10  ] = -t39 * t18;
    result__[ 11  ] = -t42 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::D2fd_odeD2xxup_numRows() const { return 6; }
  integer LUUS_DrugDisplacement::D2fd_odeD2xxup_numCols() const { return 6; }
  integer LUUS_DrugDisplacement::D2fd_odeD2xxup_nnz()     const { return 34; }

  void
  LUUS_DrugDisplacement::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 4   ;
    iIndex[11] = 1   ; jIndex[11] = 5   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 3   ;
    iIndex[16] = 2   ; jIndex[16] = 4   ;
    iIndex[17] = 2   ; jIndex[17] = 5   ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 1   ;
    iIndex[20] = 3   ; jIndex[20] = 2   ;
    iIndex[21] = 3   ; jIndex[21] = 3   ;
    iIndex[22] = 3   ; jIndex[22] = 4   ;
    iIndex[23] = 3   ; jIndex[23] = 5   ;
    iIndex[24] = 4   ; jIndex[24] = 0   ;
    iIndex[25] = 4   ; jIndex[25] = 1   ;
    iIndex[26] = 4   ; jIndex[26] = 2   ;
    iIndex[27] = 4   ; jIndex[27] = 3   ;
    iIndex[28] = 4   ; jIndex[28] = 5   ;
    iIndex[29] = 5   ; jIndex[29] = 0   ;
    iIndex[30] = 5   ; jIndex[30] = 1   ;
    iIndex[31] = 5   ; jIndex[31] = 2   ;
    iIndex[32] = 5   ; jIndex[32] = 3   ;
    iIndex[33] = 5   ; jIndex[33] = 4   ;
  }


  void
  LUUS_DrugDisplacement::D2fd_odeD2xxup_sparse(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = XR__[iX_x1];
    real_type t4   = XL__[iX_x1];
    real_type t6   = t3 / 2 + t4 / 2;
    real_type t7   = XR__[iX_x2];
    real_type t8   = XL__[iX_x2];
    real_type t10  = t7 / 2 + t8 / 2;
    real_type t11  = g1_D_1_1(t6, t10);
    real_type t12  = t11 * t2;
    real_type t13  = g4(t6, t10);
    real_type t16  = 0.2e-1 - t3 / 2 - t4 / 2;
    real_type t18  = UM__[0];
    real_type t19  = t18 - t7 - t8;
    real_type t22  = t16 * t13 + 0.464e2 * t19 * t6;
    real_type t25  = g1_D_1(t6, t10);
    real_type t26  = t25 * t2;
    real_type t27  = g4_D_1(t6, t10);
    real_type t34  = t16 * t27 / 2 - t13 / 2 + 0.2320000000e2 * t18 - 0.2320000000e2 * t7 - 0.2320000000e2 * t8;
    real_type t36  = g1(t6, t10);
    real_type t37  = t36 * t2;
    real_type t38  = g4_D_1_1(t6, t10);
    real_type t46  = LM__[1];
    real_type t47  = g3(t6, t10);
    real_type t49  = 0.2320000000e2 * t3;
    real_type t50  = 0.2320000000e2 * t4;
    real_type t51  = t19 * t47 + 0.928e0 - t49 - t50;
    real_type t54  = g3_D_1(t6, t10);
    real_type t57  = t19 * t54 / 2 - 0.2320000000e2;
    real_type t59  = g3_D_1_1(t6, t10);
    result__[ 0   ] = (-t22 * t12 / 4 - t34 * t26 - (t16 * t38 / 4 - t27 / 2) * t37) * t1 + (-t51 * t12 / 4 - t57 * t26 - t19 * t59 * t37 / 4) * t46;
    real_type t65  = g1_D_1_2(t6, t10);
    real_type t66  = t65 * t2;
    real_type t69  = g4_D_2(t6, t10);
    real_type t72  = t16 * t69 / 2 - t49 - t50;
    real_type t75  = g1_D_2(t6, t10);
    real_type t76  = t75 * t2;
    real_type t79  = g4_D_1_2(t6, t10);
    real_type t89  = g3_D_2(t6, t10);
    real_type t92  = t19 * t89 / 2 - t47;
    real_type t97  = g3_D_1_2(t6, t10);
    result__[ 1   ] = (-t22 * t66 / 4 - t72 * t26 / 2 - t34 * t76 / 2 - (t16 * t79 / 4 - t69 / 4 - 0.2320000000e2) * t37) * t1 + (-t51 * t66 / 4 - t92 * t26 / 2 - t57 * t76 / 2 - (t19 * t97 / 4 - t54 / 2) * t37) * t46;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    real_type t105 = t49 + t50;
    result__[ 4   ] = (-t105 * t26 / 2 - 0.2320000000e2 * t37) * t1 + (-t47 * t26 / 2 - t54 * t37 / 2) * t46;
    result__[ 5   ] = (-t22 * t25 / 2 - t34 * t36) * t1 + (-t51 * t25 / 2 - t57 * t36) * t46;
    result__[ 6   ] = result__[3];
    real_type t126 = g1_D_2_2(t6, t10);
    real_type t127 = t126 * t2;
    real_type t131 = g4_D_2_2(t6, t10);
    real_type t140 = g3_D_2_2(t6, t10);
    result__[ 7   ] = (-t22 * t127 / 4 - t72 * t76 - t16 * t131 * t37 / 4) * t1 + (-t51 * t127 / 4 - t92 * t76 - (t19 * t140 / 4 - t89) * t37) * t46;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = result__[7];
    result__[ 10  ] = -t105 * t75 * t2 * t1 / 2 + (-t89 * t37 / 2 - t47 * t76 / 2) * t46;
    result__[ 11  ] = (-t22 * t75 / 2 - t72 * t36) * t1 + (-t51 * t75 / 2 - t92 * t36) * t46;
    result__[ 12  ] = result__[2];
    result__[ 13  ] = result__[8];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    result__[ 16  ] = result__[4];
    result__[ 17  ] = result__[5];
    result__[ 18  ] = result__[15];
    result__[ 19  ] = result__[9];
    result__[ 20  ] = result__[18];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[11];
    result__[ 24  ] = result__[16];
    result__[ 25  ] = result__[22];
    result__[ 26  ] = result__[24];
    result__[ 27  ] = result__[25];
    result__[ 28  ] = -t105 * t36 * t1 - t47 * t36 * t46;
    result__[ 29  ] = result__[17];
    result__[ 30  ] = result__[23];
    result__[ 31  ] = result__[29];
    result__[ 32  ] = result__[30];
    result__[ 33  ] = result__[28];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 34, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: LUUS_DrugDisplacement_Methods_Guess.cc
