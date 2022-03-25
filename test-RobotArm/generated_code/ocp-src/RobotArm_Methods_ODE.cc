/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_ODE.cc                                        |
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

  integer RobotArm::rhs_ode_numEqns() const { return 6; }

  void
  RobotArm::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    result__[ 0   ] = U__[iU_u_rho] * t1;
    result__[ 1   ] = U__[iU_u_theta] * t1;
    result__[ 2   ] = U__[iU_u_phi] * t1;
    result__[ 3   ] = X__[iX_rho1] * t1;
    result__[ 4   ] = X__[iX_theta1] * t1;
    result__[ 5   ] = X__[iX_phi1] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::Drhs_odeDxup_numRows() const { return 6; }
  integer RobotArm::Drhs_odeDxup_numCols() const { return 10; }
  integer RobotArm::Drhs_odeDxup_nnz()     const { return 12; }

  void
  RobotArm::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 9   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 9   ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = P__[iP_T];
    result__[ 1   ] = U__[iU_u_rho];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = U__[iU_u_theta];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = U__[iU_u_phi];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = X__[iX_rho1];
    result__[ 8   ] = result__[6];
    result__[ 9   ] = X__[iX_theta1];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = X__[iX_phi1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 12, i_segment );
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
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
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
