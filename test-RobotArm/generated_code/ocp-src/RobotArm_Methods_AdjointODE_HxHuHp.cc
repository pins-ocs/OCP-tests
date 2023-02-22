/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_AdjointODE.cc                                 |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::Hxp_numEqns() const { return 7; }

  void
  RobotArm::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = X__[iX_rho];
    real_type t3   = X__[iX_phi];
    real_type t4   = I_theta_D_1(t2, t3);
    real_type t6   = V__[4];
    real_type t8   = MU__[2];
    real_type t9   = I_phi_D(t2);
    result__[ 0   ] = -t6 * t4 * t1 - V__[5] * t9 * t8;
    result__[ 1   ] = 0;
    real_type t13  = I_theta_D_2(t2, t3);
    result__[ 2   ] = -t6 * t13 * t1;
    real_type t16  = MU__[3];
    real_type t17  = P__[iP_T];
    result__[ 3   ] = t17 * t16;
    real_type t18  = MU__[4];
    result__[ 4   ] = t17 * t18;
    real_type t19  = MU__[5];
    result__[ 5   ] = t17 * t19;
    real_type t20  = U__[iU_u_rho];
    real_type t21  = u_rhoControl(t20, -1, 1);
    real_type t22  = U__[iU_u_theta];
    real_type t23  = u_thetaControl(t22, -1, 1);
    real_type t24  = U__[iU_u_phi];
    real_type t25  = u_phiControl(t24, -1, 1);
    result__[ 6   ] = t22 * t1 + X__[iX_rho1] * t16 + X__[iX_theta1] * t18 + X__[iX_phi1] * t19 + t20 * MU__[0] + t24 * t8 + t21 + t23 + t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 7, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DHxpDxpuv_numRows() const { return 7; }
  integer RobotArm::DHxpDxpuv_numCols() const { return 16; }
  integer RobotArm::DHxpDxpuv_nnz()     const { return 16; }

  void
  RobotArm::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 14  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 15  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 6   ;
    iIndex[10] = 6   ; jIndex[10] = 3   ;
    iIndex[11] = 6   ; jIndex[11] = 4   ;
    iIndex[12] = 6   ; jIndex[12] = 5   ;
    iIndex[13] = 6   ; jIndex[13] = 7   ;
    iIndex[14] = 6   ; jIndex[14] = 8   ;
    iIndex[15] = 6   ; jIndex[15] = 9   ;
  }


  void
  RobotArm::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = X__[iX_rho];
    real_type t3   = X__[iX_phi];
    real_type t4   = I_theta_D_1_1(t2, t3);
    real_type t6   = V__[4];
    real_type t8   = MU__[2];
    real_type t9   = I_phi_DD(t2);
    result__[ 0   ] = -t6 * t4 * t1 - V__[5] * t9 * t8;
    real_type t13  = I_theta_D_1_2(t2, t3);
    result__[ 1   ] = -t6 * t13 * t1;
    real_type t16  = I_theta_D_1(t2, t3);
    result__[ 2   ] = -t16 * t1;
    real_type t18  = I_phi_D(t2);
    result__[ 3   ] = -t18 * t8;
    result__[ 4   ] = result__[1];
    real_type t20  = I_theta_D_2_2(t2, t3);
    result__[ 5   ] = -t6 * t20 * t1;
    real_type t23  = I_theta_D_2(t2, t3);
    result__[ 6   ] = -t23 * t1;
    result__[ 7   ] = MU__[3];
    result__[ 8   ] = MU__[4];
    result__[ 9   ] = MU__[5];
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    real_type t26  = ALIAS_u_rhoControl_D_1(U__[iU_u_rho], -1, 1);
    result__[ 13  ] = t26 + MU__[0];
    real_type t29  = ALIAS_u_thetaControl_D_1(U__[iU_u_theta], -1, 1);
    result__[ 14  ] = t29 + t1;
    real_type t31  = ALIAS_u_phiControl_D_1(U__[iU_u_phi], -1, 1);
    result__[ 15  ] = t31 + t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 16, i_segment );
  }

}

// EOF: RobotArm_Methods_AdjointODE.cc
