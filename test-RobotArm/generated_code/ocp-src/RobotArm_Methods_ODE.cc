/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_ODE.cc                                        |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "RobotArm.hh"
#include "RobotArm_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


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


namespace RobotArmDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer RobotArm::ode_numEqns() const { return 6; }

  void
  RobotArm::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    result__[ 0   ] = U__[iU_u_rho] * t1 - ModelPars[iM_L] * V__[3];
    real_type t9   = X__[iX_rho];
    real_type t11  = I_theta(t9, X__[iX_phi]);
    result__[ 1   ] = U__[iU_u_theta] * t1 - V__[4] * t11;
    real_type t16  = I_phi(t9);
    result__[ 2   ] = U__[iU_u_phi] * t1 - V__[5] * t16;
    result__[ 3   ] = X__[iX_rho1] * t1 - V__[0];
    result__[ 4   ] = X__[iX_theta1] * t1 - V__[1];
    result__[ 5   ] = X__[iX_phi1] * t1 - V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DodeDxpuv_numRows() const { return 6; }
  integer RobotArm::DodeDxpuv_numCols() const { return 16; }
  integer RobotArm::DodeDxpuv_nnz()     const { return 21; }

  void
  RobotArm::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 13  ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 14  ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 9   ;
    iIndex[11] = 2   ; jIndex[11] = 15  ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 3   ; jIndex[13] = 6   ;
    iIndex[14] = 3   ; jIndex[14] = 10  ;
    iIndex[15] = 4   ; jIndex[15] = 4   ;
    iIndex[16] = 4   ; jIndex[16] = 6   ;
    iIndex[17] = 4   ; jIndex[17] = 11  ;
    iIndex[18] = 5   ; jIndex[18] = 5   ;
    iIndex[19] = 5   ; jIndex[19] = 6   ;
    iIndex[20] = 5   ; jIndex[20] = 12  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = U__[iU_u_rho];
    result__[ 1   ] = P__[iP_T];
    result__[ 2   ] = -ModelPars[iM_L];
    real_type t2   = X__[iX_rho];
    real_type t3   = X__[iX_phi];
    real_type t4   = I_theta_D_1(t2, t3);
    real_type t5   = V__[4];
    result__[ 3   ] = -t5 * t4;
    real_type t7   = I_theta_D_2(t2, t3);
    result__[ 4   ] = -t5 * t7;
    result__[ 5   ] = U__[iU_u_theta];
    result__[ 6   ] = result__[1];
    real_type t9   = I_theta(t2, t3);
    result__[ 7   ] = -t9;
    real_type t10  = I_phi_D(t2);
    result__[ 8   ] = -V__[5] * t10;
    result__[ 9   ] = U__[iU_u_phi];
    result__[ 10  ] = result__[6];
    real_type t13  = I_phi(t2);
    result__[ 11  ] = -t13;
    result__[ 12  ] = result__[10];
    result__[ 13  ] = X__[iX_rho1];
    result__[ 14  ] = -1;
    result__[ 15  ] = result__[12];
    result__[ 16  ] = X__[iX_theta1];
    result__[ 17  ] = -1;
    result__[ 18  ] = result__[15];
    result__[ 19  ] = X__[iX_phi1];
    result__[ 20  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 21, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::A_numRows() const { return 6; }
  integer RobotArm::A_numCols() const { return 6; }
  integer RobotArm::A_nnz()     const { return 6; }

  void
  RobotArm::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 2   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_L];
    real_type t1   = X__[iX_rho];
    result__[ 1   ] = I_theta(t1, X__[iX_phi]);
    result__[ 2   ] = I_phi(t1);
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 6, i_segment );
  }

}

// EOF: RobotArm_Methods_ODE.cc
