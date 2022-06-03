/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_AdjointODE.cc                                 |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JP_numEqns() const { return 0; }

  void
  RobotArm::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::LT_numEqns() const { return 0; }

  void
  RobotArm::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JU_numEqns() const { return 3; }

  void
  RobotArm::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = u_rhoControl(U__[iU_u_rho], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = u_thetaControl(U__[iU_u_theta], -1, 1);
    result__[ 1   ] = t5 * t1;
    real_type t7   = u_phiControl(U__[iU_u_phi], -1, 1);
    result__[ 2   ] = t7 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::LTargs_numEqns() const { return 0; }

  void
  RobotArm::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJPDxpu_numRows() const { return 0; }
  integer RobotArm::DJPDxpu_numCols() const { return 10; }
  integer RobotArm::DJPDxpu_nnz()     const { return 0; }

  void
  RobotArm::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DLTDxpu_numRows() const { return 0; }
  integer RobotArm::DLTDxpu_numCols() const { return 10; }
  integer RobotArm::DLTDxpu_nnz()     const { return 0; }

  void
  RobotArm::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJUDxpu_numRows() const { return 3; }
  integer RobotArm::DJUDxpu_numCols() const { return 10; }
  integer RobotArm::DJUDxpu_nnz()     const { return 6; }

  void
  RobotArm::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 9   ;
  }


  void
  RobotArm::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u_rho];
    result__[ 0   ] = u_rhoControl(t1, -1, 1);
    real_type t2   = P__[iP_T];
    real_type t3   = ALIAS_u_rhoControl_D_1(t1, -1, 1);
    result__[ 1   ] = t3 * t2;
    real_type t4   = U__[iU_u_theta];
    result__[ 2   ] = u_thetaControl(t4, -1, 1);
    real_type t5   = ALIAS_u_thetaControl_D_1(t4, -1, 1);
    result__[ 3   ] = t5 * t2;
    real_type t6   = U__[iU_u_phi];
    result__[ 4   ] = u_phiControl(t6, -1, 1);
    real_type t7   = ALIAS_u_phiControl_D_1(t6, -1, 1);
    result__[ 5   ] = t7 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DLTargsDxpu_numRows() const { return 0; }
  integer RobotArm::DLTargsDxpu_numCols() const { return 10; }
  integer RobotArm::DLTargsDxpu_nnz()     const { return 0; }

  void
  RobotArm::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::D2JPD2xpu_numRows() const { return 10; }
  integer RobotArm::D2JPD2xpu_numCols() const { return 10; }
  integer RobotArm::D2JPD2xpu_nnz()     const { return 0; }

  void
  RobotArm::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::D2LTD2xpu_numRows() const { return 10; }
  integer RobotArm::D2LTD2xpu_numCols() const { return 10; }
  integer RobotArm::D2LTD2xpu_nnz()     const { return 0; }

  void
  RobotArm::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::D2JUD2xpu_numRows() const { return 10; }
  integer RobotArm::D2JUD2xpu_numCols() const { return 10; }
  integer RobotArm::D2JUD2xpu_nnz()     const { return 9; }

  void
  RobotArm::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 6   ; jIndex[0 ] = 7   ;
    iIndex[1 ] = 6   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 6   ; jIndex[2 ] = 9   ;
    iIndex[3 ] = 7   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 7   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 8   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 8   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 9   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 9   ; jIndex[8 ] = 9   ;
  }


  void
  RobotArm::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u_rho];
    real_type t2   = ALIAS_u_rhoControl_D_1(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = t3 * t2;
    real_type t4   = U__[iU_u_theta];
    real_type t5   = ALIAS_u_thetaControl_D_1(t4, -1, 1);
    real_type t6   = OMEGA__[1];
    result__[ 1   ] = t6 * t5;
    real_type t7   = U__[iU_u_phi];
    real_type t8   = ALIAS_u_phiControl_D_1(t7, -1, 1);
    real_type t9   = OMEGA__[2];
    result__[ 2   ] = t9 * t8;
    result__[ 3   ] = result__[0];
    real_type t10  = P__[iP_T];
    real_type t11  = ALIAS_u_rhoControl_D_1_1(t1, -1, 1);
    result__[ 4   ] = t3 * t11 * t10;
    result__[ 5   ] = result__[1];
    real_type t13  = ALIAS_u_thetaControl_D_1_1(t4, -1, 1);
    result__[ 6   ] = t6 * t13 * t10;
    result__[ 7   ] = result__[2];
    real_type t15  = ALIAS_u_phiControl_D_1_1(t7, -1, 1);
    result__[ 8   ] = t9 * t15 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 9, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::D2LTargsD2xpu_numRows() const { return 10; }
  integer RobotArm::D2LTargsD2xpu_numCols() const { return 10; }
  integer RobotArm::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  RobotArm::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: RobotArm_Methods_AdjointODE.cc
