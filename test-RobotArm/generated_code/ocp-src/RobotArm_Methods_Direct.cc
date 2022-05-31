/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_Guess.cc                                      |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "RobotArm.hh"
#include "RobotArm_Pars.hh"

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
#define ALIAS_u_phiControl_D_3(__t1, __t2, __t3) u_phiControl.D_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_2(__t1, __t2, __t3) u_phiControl.D_2( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1(__t1, __t2, __t3) u_phiControl.D_1( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_3_3(__t1, __t2, __t3) u_phiControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_2_3(__t1, __t2, __t3) u_phiControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_2_2(__t1, __t2, __t3) u_phiControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1_3(__t1, __t2, __t3) u_phiControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1_2(__t1, __t2, __t3) u_phiControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1_1(__t1, __t2, __t3) u_phiControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_3(__t1, __t2, __t3) u_thetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_2(__t1, __t2, __t3) u_thetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1(__t1, __t2, __t3) u_thetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_3_3(__t1, __t2, __t3) u_thetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_2_3(__t1, __t2, __t3) u_thetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_2_2(__t1, __t2, __t3) u_thetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1_3(__t1, __t2, __t3) u_thetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1_2(__t1, __t2, __t3) u_thetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1_1(__t1, __t2, __t3) u_thetaControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_3(__t1, __t2, __t3) u_rhoControl.D_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_2(__t1, __t2, __t3) u_rhoControl.D_2( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1(__t1, __t2, __t3) u_rhoControl.D_1( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_3_3(__t1, __t2, __t3) u_rhoControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_2_3(__t1, __t2, __t3) u_rhoControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_2_2(__t1, __t2, __t3) u_rhoControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1_3(__t1, __t2, __t3) u_rhoControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1_2(__t1, __t2, __t3) u_rhoControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1_1(__t1, __t2, __t3) u_rhoControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace RobotArmDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer RobotArm::fd_ode_numEqns() const { return 6; }

  void
  RobotArm::fd_ode_eval(
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
    real_type t1   = P__[iP_T];
    result__[ 0   ] = -UM__[0] * t1 + ModelPars[iM_L] * V__[3];
    real_type t7   = XM__[0];
    real_type t9   = I_theta(t7, XM__[2]);
    result__[ 1   ] = -UM__[1] * t1 + V__[4] * t9;
    real_type t14  = I_phi(t7);
    result__[ 2   ] = -UM__[2] * t1 + V__[5] * t14;
    result__[ 3   ] = -XM__[3] * t1 + V__[0];
    result__[ 4   ] = -XM__[4] * t1 + V__[1];
    result__[ 5   ] = -XM__[5] * t1 + V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::Dfd_odeDxxpu_numRows() const { return 6; }
  integer RobotArm::Dfd_odeDxxpu_numCols() const { return 16; }
  integer RobotArm::Dfd_odeDxxpu_nnz()     const { return 33; }

  void
  RobotArm::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 9   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 12  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 15  ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 10  ;
    iIndex[10] = 1   ; jIndex[10] = 13  ;
    iIndex[11] = 1   ; jIndex[11] = 15  ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 5   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 2   ; jIndex[15] = 11  ;
    iIndex[16] = 2   ; jIndex[16] = 14  ;
    iIndex[17] = 2   ; jIndex[17] = 15  ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 3   ;
    iIndex[20] = 3   ; jIndex[20] = 6   ;
    iIndex[21] = 3   ; jIndex[21] = 9   ;
    iIndex[22] = 3   ; jIndex[22] = 15  ;
    iIndex[23] = 4   ; jIndex[23] = 1   ;
    iIndex[24] = 4   ; jIndex[24] = 4   ;
    iIndex[25] = 4   ; jIndex[25] = 7   ;
    iIndex[26] = 4   ; jIndex[26] = 10  ;
    iIndex[27] = 4   ; jIndex[27] = 15  ;
    iIndex[28] = 5   ; jIndex[28] = 2   ;
    iIndex[29] = 5   ; jIndex[29] = 5   ;
    iIndex[30] = 5   ; jIndex[30] = 8   ;
    iIndex[31] = 5   ; jIndex[31] = 11  ;
    iIndex[32] = 5   ; jIndex[32] = 15  ;
  }


  void
  RobotArm::Dfd_odeDxxpu_sparse(
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
    real_type t2   = __INV_DZETA * ModelPars[iM_L];
    result__[ 0   ] = -t2;
    result__[ 1   ] = t2;
    real_type t3   = P__[iP_T];
    result__[ 2   ] = -t3;
    result__[ 3   ] = -UM__[0];
    real_type t5   = XM__[0];
    real_type t6   = XM__[2];
    real_type t7   = I_theta_D_1(t5, t6);
    real_type t8   = V__[4];
    result__[ 4   ] = 0.5e0 * t8 * t7;
    real_type t10  = I_theta_D_2(t5, t6);
    result__[ 5   ] = 0.5e0 * t8 * t10;
    real_type t12  = I_theta(t5, t6);
    real_type t13  = t12 * __INV_DZETA;
    result__[ 6   ] = -t13;
    result__[ 7   ] = result__[4];
    result__[ 8   ] = result__[5];
    result__[ 9   ] = t13;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = -UM__[1];
    real_type t15  = I_phi_D(t5);
    result__[ 12  ] = 0.5e0 * V__[5] * t15;
    real_type t18  = I_phi(t5);
    real_type t19  = t18 * __INV_DZETA;
    result__[ 13  ] = -t19;
    result__[ 14  ] = result__[12];
    result__[ 15  ] = t19;
    result__[ 16  ] = result__[10];
    result__[ 17  ] = -UM__[2];
    result__[ 18  ] = -__INV_DZETA;
    result__[ 19  ] = -0.5e0 * t3;
    result__[ 20  ] = __INV_DZETA;
    result__[ 21  ] = result__[19];
    result__[ 22  ] = -XM__[3];
    result__[ 23  ] = result__[18];
    result__[ 24  ] = result__[21];
    result__[ 25  ] = __INV_DZETA;
    result__[ 26  ] = result__[24];
    result__[ 27  ] = -XM__[4];
    result__[ 28  ] = result__[23];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = __INV_DZETA;
    result__[ 31  ] = result__[29];
    result__[ 32  ] = -XM__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 33, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::D2fd_odeD2xxpu_numRows() const { return 16; }
  integer RobotArm::D2fd_odeD2xxpu_numCols() const { return 16; }
  integer RobotArm::D2fd_odeD2xxpu_nnz()     const { return 34; }

  void
  RobotArm::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 15  ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 15  ;
    iIndex[10] = 5   ; jIndex[10] = 15  ;
    iIndex[11] = 6   ; jIndex[11] = 0   ;
    iIndex[12] = 6   ; jIndex[12] = 2   ;
    iIndex[13] = 6   ; jIndex[13] = 6   ;
    iIndex[14] = 6   ; jIndex[14] = 8   ;
    iIndex[15] = 8   ; jIndex[15] = 0   ;
    iIndex[16] = 8   ; jIndex[16] = 2   ;
    iIndex[17] = 8   ; jIndex[17] = 6   ;
    iIndex[18] = 8   ; jIndex[18] = 8   ;
    iIndex[19] = 9   ; jIndex[19] = 15  ;
    iIndex[20] = 10  ; jIndex[20] = 15  ;
    iIndex[21] = 11  ; jIndex[21] = 15  ;
    iIndex[22] = 12  ; jIndex[22] = 15  ;
    iIndex[23] = 13  ; jIndex[23] = 15  ;
    iIndex[24] = 14  ; jIndex[24] = 15  ;
    iIndex[25] = 15  ; jIndex[25] = 3   ;
    iIndex[26] = 15  ; jIndex[26] = 4   ;
    iIndex[27] = 15  ; jIndex[27] = 5   ;
    iIndex[28] = 15  ; jIndex[28] = 9   ;
    iIndex[29] = 15  ; jIndex[29] = 10  ;
    iIndex[30] = 15  ; jIndex[30] = 11  ;
    iIndex[31] = 15  ; jIndex[31] = 12  ;
    iIndex[32] = 15  ; jIndex[32] = 13  ;
    iIndex[33] = 15  ; jIndex[33] = 14  ;
  }


  void
  RobotArm::D2fd_odeD2xxpu_sparse(
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
    real_type t5   = XR__[iX_rho] / 2 + XL__[iX_rho] / 2;
    real_type t9   = XR__[iX_phi] / 2 + XL__[iX_phi] / 2;
    real_type t10  = I_theta_D_1_1(t5, t9);
    real_type t12  = V__[4];
    real_type t14  = LM__[2];
    real_type t15  = I_phi_DD(t5);
    result__[ 0   ] = t12 * t10 * t1 / 4 + V__[5] * t15 * t14 / 4;
    real_type t20  = I_theta_D_1_2(t5, t9);
    result__[ 1   ] = t12 * t20 * t1 / 4;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[3];
    real_type t23  = I_theta_D_2_2(t5, t9);
    result__[ 5   ] = t12 * t23 * t1 / 4;
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = -LM__[3] / 2;
    result__[ 9   ] = -LM__[4] / 2;
    result__[ 10  ] = -LM__[5] / 2;
    result__[ 11  ] = result__[2];
    result__[ 12  ] = result__[6];
    result__[ 13  ] = result__[11];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[14];
    result__[ 16  ] = result__[7];
    result__[ 17  ] = result__[15];
    result__[ 18  ] = result__[16];
    result__[ 19  ] = result__[8];
    result__[ 20  ] = result__[9];
    result__[ 21  ] = result__[10];
    result__[ 22  ] = -LM__[0];
    result__[ 23  ] = -t1;
    result__[ 24  ] = -t14;
    result__[ 25  ] = result__[19];
    result__[ 26  ] = result__[20];
    result__[ 27  ] = result__[21];
    result__[ 28  ] = result__[25];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[22];
    result__[ 32  ] = result__[23];
    result__[ 33  ] = result__[24];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 34, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: RobotArm_Methods_Guess.cc
