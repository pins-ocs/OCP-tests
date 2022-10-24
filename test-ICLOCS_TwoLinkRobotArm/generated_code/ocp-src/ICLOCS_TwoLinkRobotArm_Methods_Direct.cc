/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_Guess.cc                        |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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

namespace ICLOCS_TwoLinkRobotArmDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer ICLOCS_TwoLinkRobotArm::fd_ode_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::fd_ode_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = XM__[2];
    real_type t4   = sin(t3);
    real_type t5   = cos(t3);
    real_type t6   = t5 * t4;
    real_type t7   = XM__[0];
    real_type t8   = t7 * t7;
    real_type t11  = XM__[1];
    real_type t12  = t11 * t11;
    real_type t14  = UM__[0];
    real_type t16  = UM__[1];
    real_type t22  = t4 * t4;
    real_type t25  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t22);
    result__[ 0   ] = V__[0] - t25 * (9.0 / 4.0 * t8 * t6 + 2 * t12 + 4.0 / 3.0 * t14 - 4.0 / 3.0 * t16 - 3.0 / 2.0 * t16 * t5) * t2;
    result__[ 1   ] = V__[1] + t25 * (9.0 / 4.0 * t12 * t6 + 7.0 / 2.0 * t8 - 7.0 / 3.0 * t16 + 3.0 / 2.0 * (t14 - t16) * t5) * t2;
    result__[ 2   ] = V__[2] - (t11 - t7) * t2;
    result__[ 3   ] = -t7 * t2 + V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::Dfd_odeDxxpu_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::Dfd_odeDxxpu_numCols() const { return 11; }
  integer ICLOCS_TwoLinkRobotArm::Dfd_odeDxxpu_nnz()     const { return 30; }

  void
  ICLOCS_TwoLinkRobotArm::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 10  ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 0   ;
    iIndex[10] = 1   ; jIndex[10] = 1   ;
    iIndex[11] = 1   ; jIndex[11] = 2   ;
    iIndex[12] = 1   ; jIndex[12] = 4   ;
    iIndex[13] = 1   ; jIndex[13] = 5   ;
    iIndex[14] = 1   ; jIndex[14] = 6   ;
    iIndex[15] = 1   ; jIndex[15] = 8   ;
    iIndex[16] = 1   ; jIndex[16] = 9   ;
    iIndex[17] = 1   ; jIndex[17] = 10  ;
    iIndex[18] = 2   ; jIndex[18] = 0   ;
    iIndex[19] = 2   ; jIndex[19] = 1   ;
    iIndex[20] = 2   ; jIndex[20] = 2   ;
    iIndex[21] = 2   ; jIndex[21] = 4   ;
    iIndex[22] = 2   ; jIndex[22] = 5   ;
    iIndex[23] = 2   ; jIndex[23] = 6   ;
    iIndex[24] = 2   ; jIndex[24] = 10  ;
    iIndex[25] = 3   ; jIndex[25] = 0   ;
    iIndex[26] = 3   ; jIndex[26] = 3   ;
    iIndex[27] = 3   ; jIndex[27] = 4   ;
    iIndex[28] = 3   ; jIndex[28] = 7   ;
    iIndex[29] = 3   ; jIndex[29] = 10  ;
  }


  void
  ICLOCS_TwoLinkRobotArm::Dfd_odeDxxpu_sparse(
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
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = cos(t2);
    real_type t6   = XM__[0];
    real_type t8   = t3 * t3;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t14  = 0.2250000000e1 * t11 * t6 * t5 * t4;
    result__[ 0   ] = -t14 - __INV_DZETA;
    real_type t15  = XM__[1];
    result__[ 1   ] = -0.20e1 * t11 * t15 * t1;
    real_type t19  = t5 * t5;
    real_type t20  = t6 * t6;
    real_type t25  = UM__[1];
    real_type t32  = t5 * t3;
    real_type t35  = t15 * t15;
    real_type t37  = UM__[0];
    real_type t42  = 9.0 / 4.0 * t20 * t32 + 2 * t35 + 4.0 / 3.0 * t37 - 4.0 / 3.0 * t25 - 3.0 / 2.0 * t25 * t5;
    real_type t44  = t10 * t10;
    real_type t47  = t5 * t3 / t44;
    result__[ 2   ] = -0.5e0 * t11 * (9.0 / 4.0 * t20 * t19 - 9.0 / 4.0 * t20 * t8 + 3.0 / 2.0 * t25 * t3) * t1 + 0.2250000000e1 * t47 * t42 * t1;
    result__[ 3   ] = -t14 + __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = -4.0 / 3.0 * t11 * t1;
    real_type t52  = 3.0 / 2.0 * t5;
    result__[ 7   ] = -t11 * (-4.0 / 3.0 - t52) * t1;
    result__[ 8   ] = -t11 * t42;
    result__[ 9   ] = 0.35e1 * t11 * t6 * t1;
    real_type t62  = 0.2250000000e1 * t11 * t15 * t5 * t4;
    result__[ 10  ] = t62 - __INV_DZETA;
    real_type t67  = t37 - t25;
    real_type t80  = 9.0 / 4.0 * t35 * t32 + 7.0 / 2.0 * t20 - 7.0 / 3.0 * t25 + 3.0 / 2.0 * t67 * t5;
    result__[ 11  ] = 0.5e0 * t11 * (9.0 / 4.0 * t35 * t19 - 9.0 / 4.0 * t35 * t8 - 3.0 / 2.0 * t67 * t3) * t1 - 0.2250000000e1 * t47 * t80 * t1;
    result__[ 12  ] = result__[9];
    result__[ 13  ] = t62 + __INV_DZETA;
    result__[ 14  ] = result__[11];
    result__[ 15  ] = 3.0 / 2.0 * t11 * t5 * t1;
    result__[ 16  ] = t11 * (-7.0 / 3.0 - t52) * t1;
    result__[ 17  ] = t11 * t80;
    result__[ 18  ] = 0.5e0 * t1;
    result__[ 19  ] = -result__[18];
    result__[ 20  ] = -__INV_DZETA;
    result__[ 21  ] = result__[18];
    result__[ 22  ] = result__[19];
    result__[ 23  ] = __INV_DZETA;
    result__[ 24  ] = -t15 + t6;
    result__[ 25  ] = result__[22];
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[25];
    result__[ 28  ] = __INV_DZETA;
    result__[ 29  ] = -t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 30, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2fd_odeD2xxpu_numRows() const { return 11; }
  integer ICLOCS_TwoLinkRobotArm::D2fd_odeD2xxpu_numCols() const { return 11; }
  integer ICLOCS_TwoLinkRobotArm::D2fd_odeD2xxpu_nnz()     const { return 52; }

  void
  ICLOCS_TwoLinkRobotArm::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 10  ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 5   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 2   ; jIndex[16] = 8   ;
    iIndex[17] = 2   ; jIndex[17] = 9   ;
    iIndex[18] = 2   ; jIndex[18] = 10  ;
    iIndex[19] = 4   ; jIndex[19] = 0   ;
    iIndex[20] = 4   ; jIndex[20] = 2   ;
    iIndex[21] = 4   ; jIndex[21] = 4   ;
    iIndex[22] = 4   ; jIndex[22] = 6   ;
    iIndex[23] = 4   ; jIndex[23] = 10  ;
    iIndex[24] = 5   ; jIndex[24] = 1   ;
    iIndex[25] = 5   ; jIndex[25] = 2   ;
    iIndex[26] = 5   ; jIndex[26] = 5   ;
    iIndex[27] = 5   ; jIndex[27] = 6   ;
    iIndex[28] = 5   ; jIndex[28] = 10  ;
    iIndex[29] = 6   ; jIndex[29] = 0   ;
    iIndex[30] = 6   ; jIndex[30] = 1   ;
    iIndex[31] = 6   ; jIndex[31] = 2   ;
    iIndex[32] = 6   ; jIndex[32] = 4   ;
    iIndex[33] = 6   ; jIndex[33] = 5   ;
    iIndex[34] = 6   ; jIndex[34] = 6   ;
    iIndex[35] = 6   ; jIndex[35] = 8   ;
    iIndex[36] = 6   ; jIndex[36] = 9   ;
    iIndex[37] = 6   ; jIndex[37] = 10  ;
    iIndex[38] = 8   ; jIndex[38] = 2   ;
    iIndex[39] = 8   ; jIndex[39] = 6   ;
    iIndex[40] = 8   ; jIndex[40] = 10  ;
    iIndex[41] = 9   ; jIndex[41] = 2   ;
    iIndex[42] = 9   ; jIndex[42] = 6   ;
    iIndex[43] = 9   ; jIndex[43] = 10  ;
    iIndex[44] = 10  ; jIndex[44] = 0   ;
    iIndex[45] = 10  ; jIndex[45] = 1   ;
    iIndex[46] = 10  ; jIndex[46] = 2   ;
    iIndex[47] = 10  ; jIndex[47] = 4   ;
    iIndex[48] = 10  ; jIndex[48] = 5   ;
    iIndex[49] = 10  ; jIndex[49] = 6   ;
    iIndex[50] = 10  ; jIndex[50] = 8   ;
    iIndex[51] = 10  ; jIndex[51] = 9   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::D2fd_odeD2xxpu_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t7   = XR__[iX_theta] / 2 + XL__[iX_theta] / 2;
    real_type t8   = sin(t7);
    real_type t9   = cos(t7);
    real_type t10  = t9 * t8;
    real_type t11  = t8 * t8;
    real_type t13  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t11;
    real_type t14  = 1.0 / t13;
    real_type t15  = t14 * t10;
    real_type t18  = LM__[1];
    real_type t19  = t2 * t18;
    result__[ 0   ] = -9.0 / 8.0 * t15 * t3 + 7.0 / 4.0 * t14 * t19;
    real_type t22  = t9 * t9;
    real_type t25  = XR__[iX_omega__alpha] + XL__[iX_omega__alpha];
    real_type t26  = t25 / 2;
    real_type t27  = t26 * t22;
    real_type t31  = t26 * t11;
    real_type t36  = t13 * t13;
    real_type t37  = 1.0 / t36;
    real_type t38  = t37 * t27;
    real_type t41  = 7.0 / 4.0 * t25;
    real_type t43  = t8 * t37;
    real_type t44  = t9 * t43;
    real_type t46  = 9.0 / 4.0 * t44 * t41 * t19;
    result__[ 1   ] = -9.0 / 8.0 * t14 * t27 * t3 + 9.0 / 8.0 * t14 * t31 * t3 + 0.81e2 / 0.16e2 * t38 * t11 * t3 - t46;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    real_type t55  = LM__[2] / 2;
    result__[ 4   ] = -9.0 / 4.0 * t14 * t26 * t9 * t8 * t1 + t14 * t41 * t18 + t55 - LM__[3] / 2;
    result__[ 5   ] = -t14 * t3 + 9.0 / 8.0 * t15 * t19;
    real_type t63  = XR__[iX_omega__beta] + XL__[iX_omega__beta];
    real_type t66  = 9.0 / 4.0 * t44 * t63 * t3;
    real_type t67  = t63 / 2;
    real_type t68  = t67 * t22;
    real_type t72  = t67 * t11;
    real_type t77  = t37 * t68;
    result__[ 6   ] = t66 + 9.0 / 8.0 * t14 * t68 * t19 - 9.0 / 8.0 * t14 * t72 * t19 - 0.81e2 / 0.16e2 * t77 * t11 * t19;
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[6];
    result__[ 9   ] = -t14 * t63 * t1 + 9.0 / 4.0 * t14 * t67 * t9 * t8 * t18 - t55;
    result__[ 10  ] = result__[3];
    result__[ 11  ] = result__[8];
    real_type t87  = t26 * t26;
    real_type t89  = 9.0 / 4.0 * t87 * t10;
    real_type t90  = UM__[1];
    real_type t91  = t90 * t9;
    real_type t102 = 9.0 / 8.0 * t87 * t22 - 9.0 / 8.0 * t87 * t11 + 3.0 / 4.0 * t90 * t8;
    real_type t106 = t67 * t67;
    real_type t108 = UM__[0];
    real_type t112 = t89 + 2 * t106 + 4.0 / 3.0 * t108 - 4.0 / 3.0 * t90 - 3.0 / 2.0 * t91;
    real_type t113 = t112 * t2;
    real_type t117 = t22 * t11 / t36 / t13;
    real_type t120 = t22 * t37;
    real_type t123 = t11 * t37;
    real_type t129 = 9.0 / 4.0 * t106 * t10;
    real_type t130 = t108 - t90;
    real_type t131 = t130 * t9;
    real_type t142 = 9.0 / 8.0 * t106 * t22 - 9.0 / 8.0 * t106 * t11 - 3.0 / 4.0 * t130 * t8;
    real_type t149 = t129 + 7.0 / 2.0 * t87 - 7.0 / 3.0 * t90 + 3.0 / 2.0 * t131;
    real_type t150 = t149 * t2;
    result__[ 12  ] = (-t14 * (-t89 + 3.0 / 8.0 * t91) * t2 + 9.0 / 2.0 * t44 * t102 * t2 - 0.81e2 / 8.0 * t117 * t113 + 9.0 / 8.0 * t120 * t113 - 9.0 / 8.0 * t123 * t113) * t1 + (t14 * (-t129 - 3.0 / 8.0 * t131) * t2 - 9.0 / 2.0 * t44 * t142 * t2 + 0.81e2 / 8.0 * t117 * t150 - 9.0 / 8.0 * t120 * t150 + 9.0 / 8.0 * t123 * t150) * t18;
    real_type t163 = t11 * t2;
    result__[ 13  ] = (-t14 * (9.0 / 8.0 * t27 - 9.0 / 8.0 * t31) * t2 + 0.81e2 / 0.16e2 * t38 * t163) * t1 - t46;
    result__[ 14  ] = t66 + (t14 * (9.0 / 8.0 * t68 - 9.0 / 8.0 * t72) * t2 - 0.81e2 / 0.16e2 * t77 * t163) * t18;
    result__[ 15  ] = result__[12];
    real_type t180 = 3.0 / 4.0 * t14 * t8 * t2;
    result__[ 16  ] = 3 * t44 * t3 + (-t180 - 0.27e2 / 8.0 * t43 * t22 * t2) * t18;
    real_type t186 = 3.0 / 2.0 * t9;
    real_type t187 = -4.0 / 3.0 - t186;
    real_type t193 = -7.0 / 3.0 - t186;
    result__[ 17  ] = (-t180 + 9.0 / 4.0 * t44 * t187 * t2) * t1 + (t180 - 9.0 / 4.0 * t44 * t193 * t2) * t18;
    result__[ 18  ] = (-t14 * t102 + 9.0 / 4.0 * t10 * t37 * t112) * t1 + (t14 * t142 - 9.0 / 4.0 * t10 * t37 * t149) * t18;
    result__[ 19  ] = result__[2];
    result__[ 20  ] = result__[13];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = result__[10];
    result__[ 23  ] = result__[4];
    result__[ 24  ] = result__[7];
    result__[ 25  ] = result__[14];
    result__[ 26  ] = result__[24];
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[9];
    result__[ 29  ] = result__[22];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[15];
    result__[ 32  ] = result__[29];
    result__[ 33  ] = result__[30];
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[16];
    result__[ 36  ] = result__[17];
    result__[ 37  ] = result__[18];
    result__[ 38  ] = result__[35];
    result__[ 39  ] = result__[38];
    result__[ 40  ] = -4.0 / 3.0 * t14 * t1 + 3.0 / 2.0 * t14 * t9 * t18;
    result__[ 41  ] = result__[36];
    result__[ 42  ] = result__[41];
    result__[ 43  ] = -t14 * t187 * t1 + t14 * t193 * t18;
    result__[ 44  ] = result__[23];
    result__[ 45  ] = result__[28];
    result__[ 46  ] = result__[37];
    result__[ 47  ] = result__[44];
    result__[ 48  ] = result__[45];
    result__[ 49  ] = result__[46];
    result__[ 50  ] = result__[40];
    result__[ 51  ] = result__[43];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 52, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_Guess.cc
