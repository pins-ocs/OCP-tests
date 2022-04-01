/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_Guess.cc                                      |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
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
    result__[ 0   ] = ModelPars[iM_L] * V__[3];
    real_type t3   = XM__[0];
    real_type t5   = I_theta(t3, XM__[2]);
    result__[ 1   ] = V__[4] * t5;
    real_type t7   = I_phi(t3);
    result__[ 2   ] = V__[5] * t7;
    result__[ 3   ] = V__[0];
    result__[ 4   ] = V__[1];
    result__[ 5   ] = V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::Dfd_odeDxxup_numRows() const { return 6; }
  integer RobotArm::Dfd_odeDxxup_numCols() const { return 16; }
  integer RobotArm::Dfd_odeDxxup_nnz()     const { return 18; }

  void
  RobotArm::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 9   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 10  ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 2   ; jIndex[10] = 6   ;
    iIndex[11] = 2   ; jIndex[11] = 11  ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 6   ;
    iIndex[14] = 4   ; jIndex[14] = 1   ;
    iIndex[15] = 4   ; jIndex[15] = 7   ;
    iIndex[16] = 5   ; jIndex[16] = 2   ;
    iIndex[17] = 5   ; jIndex[17] = 8   ;
  }


  void
  RobotArm::Dfd_odeDxxup_sparse(
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
    real_type t3   = XM__[0];
    real_type t4   = XM__[2];
    real_type t5   = I_theta_D_1(t3, t4);
    real_type t6   = V__[4];
    result__[ 2   ] = 0.5e0 * t6 * t5;
    real_type t8   = I_theta_D_2(t3, t4);
    result__[ 3   ] = 0.5e0 * t6 * t8;
    real_type t10  = I_theta(t3, t4);
    real_type t11  = t10 * __INV_DZETA;
    result__[ 4   ] = -t11;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[3];
    result__[ 7   ] = t11;
    real_type t12  = I_phi_D(t3);
    result__[ 8   ] = 0.5e0 * V__[5] * t12;
    real_type t15  = I_phi(t3);
    real_type t16  = t15 * __INV_DZETA;
    result__[ 9   ] = -t16;
    result__[ 10  ] = result__[8];
    result__[ 11  ] = t16;
    result__[ 12  ] = -__INV_DZETA;
    result__[ 13  ] = __INV_DZETA;
    result__[ 14  ] = result__[12];
    result__[ 15  ] = __INV_DZETA;
    result__[ 16  ] = result__[14];
    result__[ 17  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 18, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::D2fd_odeD2xxup_numRows() const { return 16; }
  integer RobotArm::D2fd_odeD2xxup_numCols() const { return 16; }
  integer RobotArm::D2fd_odeD2xxup_nnz()     const { return 16; }

  void
  RobotArm::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 6   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 6   ; jIndex[9 ] = 2   ;
    iIndex[10] = 6   ; jIndex[10] = 6   ;
    iIndex[11] = 6   ; jIndex[11] = 8   ;
    iIndex[12] = 8   ; jIndex[12] = 0   ;
    iIndex[13] = 8   ; jIndex[13] = 2   ;
    iIndex[14] = 8   ; jIndex[14] = 6   ;
    iIndex[15] = 8   ; jIndex[15] = 8   ;
  }


  void
  RobotArm::D2fd_odeD2xxup_sparse(
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
    real_type t15  = I_phi_DD(t5);
    result__[ 0   ] = t12 * t10 * t1 / 4 + V__[5] * t15 * LM__[2] / 4;
    real_type t20  = I_theta_D_1_2(t5, t9);
    result__[ 1   ] = t12 * t20 * t1 / 4;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[3];
    real_type t23  = I_theta_D_2_2(t5, t9);
    result__[ 5   ] = t12 * t23 * t1 / 4;
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[11];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: RobotArm_Methods_Guess.cc