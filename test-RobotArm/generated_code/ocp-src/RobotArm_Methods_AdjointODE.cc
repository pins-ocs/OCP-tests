/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_AdjointODE.cc                                 |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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

  integer RobotArm::JPx_numEqns() const { return 6; }

  void
  RobotArm::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::LTx_numEqns() const { return 6; }

  void
  RobotArm::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JUx_numEqns() const { return 6; }

  void
  RobotArm::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JPp_numEqns() const { return 1; }

  void
  RobotArm::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::LTp_numEqns() const { return 1; }

  void
  RobotArm::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JUp_numEqns() const { return 1; }

  void
  RobotArm::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = u_rhoControl(U__[iU_u_rho], -1, 1);
    real_type t4   = u_thetaControl(U__[iU_u_theta], -1, 1);
    real_type t6   = u_phiControl(U__[iU_u_phi], -1, 1);
    result__[ 0   ] = t2 + t4 + t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JPu_numEqns() const { return 3; }

  void
  RobotArm::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::LTu_numEqns() const { return 3; }

  void
  RobotArm::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::JUu_numEqns() const { return 3; }

  void
  RobotArm::JUu_eval(
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
    real_type t3   = ALIAS_u_rhoControl_D_1(U__[iU_u_rho], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = ALIAS_u_thetaControl_D_1(U__[iU_u_theta], -1, 1);
    result__[ 1   ] = t5 * t1;
    real_type t7   = ALIAS_u_phiControl_D_1(U__[iU_u_phi], -1, 1);
    result__[ 2   ] = t7 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 3, i_segment );
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
  integer RobotArm::DJPxDxp_numRows() const { return 6; }
  integer RobotArm::DJPxDxp_numCols() const { return 7; }
  integer RobotArm::DJPxDxp_nnz()     const { return 0; }

  void
  RobotArm::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DLTxDxp_numRows() const { return 6; }
  integer RobotArm::DLTxDxp_numCols() const { return 7; }
  integer RobotArm::DLTxDxp_nnz()     const { return 0; }

  void
  RobotArm::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJUxDxp_numRows() const { return 6; }
  integer RobotArm::DJUxDxp_numCols() const { return 7; }
  integer RobotArm::DJUxDxp_nnz()     const { return 0; }

  void
  RobotArm::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJPuDxp_numRows() const { return 3; }
  integer RobotArm::DJPuDxp_numCols() const { return 7; }
  integer RobotArm::DJPuDxp_nnz()     const { return 0; }

  void
  RobotArm::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DLTuDxp_numRows() const { return 3; }
  integer RobotArm::DLTuDxp_numCols() const { return 7; }
  integer RobotArm::DLTuDxp_nnz()     const { return 0; }

  void
  RobotArm::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJUuDxp_numRows() const { return 3; }
  integer RobotArm::DJUuDxp_numCols() const { return 7; }
  integer RobotArm::DJUuDxp_nnz()     const { return 3; }

  void
  RobotArm::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 6   ;
  }


  void
  RobotArm::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u_rhoControl_D_1(U__[iU_u_rho], -1, 1);
    result__[ 1   ] = ALIAS_u_thetaControl_D_1(U__[iU_u_theta], -1, 1);
    result__[ 2   ] = ALIAS_u_phiControl_D_1(U__[iU_u_phi], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJPpDp_numRows() const { return 1; }
  integer RobotArm::DJPpDp_numCols() const { return 1; }
  integer RobotArm::DJPpDp_nnz()     const { return 0; }

  void
  RobotArm::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DLTpDp_numRows() const { return 1; }
  integer RobotArm::DLTpDp_numCols() const { return 1; }
  integer RobotArm::DLTpDp_nnz()     const { return 0; }

  void
  RobotArm::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DJUpDp_numRows() const { return 1; }
  integer RobotArm::DJUpDp_numCols() const { return 1; }
  integer RobotArm::DJUpDp_nnz()     const { return 0; }

  void
  RobotArm::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DLTargsDxup_numRows() const { return 0; }
  integer RobotArm::DLTargsDxup_numCols() const { return 10; }
  integer RobotArm::DLTargsDxup_nnz()     const { return 0; }

  void
  RobotArm::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::Hx_numEqns() const { return 6; }

  void
  RobotArm::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_rho];
    real_type t3   = X__[iX_phi];
    real_type t4   = I_theta_D_1(t2, t3);
    real_type t6   = V__[4];
    real_type t9   = I_phi_D(t2);
    result__[ 0   ] = -t6 * t4 * t1 - V__[5] * t9 * L__[iL_lambda3__xo];
    result__[ 1   ] = 0;
    real_type t13  = I_theta_D_2(t2, t3);
    result__[ 2   ] = -t6 * t13 * t1;
    real_type t17  = P__[iP_T];
    result__[ 3   ] = t17 * L__[iL_lambda4__xo];
    result__[ 4   ] = t17 * L__[iL_lambda5__xo];
    result__[ 5   ] = t17 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::Hp_numEqns() const { return 1; }

  void
  RobotArm::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo] * U__[iU_u_rho] + L__[iL_lambda2__xo] * U__[iU_u_theta] + L__[iL_lambda3__xo] * U__[iU_u_phi] + L__[iL_lambda4__xo] * X__[iX_rho1] + L__[iL_lambda5__xo] * X__[iX_theta1] + L__[iL_lambda6__xo] * X__[iX_phi1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DHxDxp_numRows() const { return 6; }
  integer RobotArm::DHxDxp_numCols() const { return 7; }
  integer RobotArm::DHxDxp_nnz()     const { return 7; }

  void
  RobotArm::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 6   ;
  }


  void
  RobotArm::DHxDxp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_rho];
    real_type t3   = X__[iX_phi];
    real_type t4   = I_theta_D_1_1(t2, t3);
    real_type t6   = V__[4];
    real_type t9   = I_phi_DD(t2);
    result__[ 0   ] = -t6 * t4 * t1 - V__[5] * t9 * L__[iL_lambda3__xo];
    real_type t13  = I_theta_D_1_2(t2, t3);
    result__[ 1   ] = -t6 * t13 * t1;
    result__[ 2   ] = result__[1];
    real_type t16  = I_theta_D_2_2(t2, t3);
    result__[ 3   ] = -t6 * t16 * t1;
    result__[ 4   ] = L__[iL_lambda4__xo];
    result__[ 5   ] = L__[iL_lambda5__xo];
    result__[ 6   ] = L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DHpDp_numRows() const { return 1; }
  integer RobotArm::DHpDp_numCols() const { return 1; }
  integer RobotArm::DHpDp_nnz()     const { return 0; }

  void
  RobotArm::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  RobotArm::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::Hu_numEqns() const { return 3; }

  void
  RobotArm::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    result__[ 0   ] = t2 * L__[iL_lambda1__xo];
    result__[ 1   ] = t2 * L__[iL_lambda2__xo];
    result__[ 2   ] = t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DHuDxp_numRows() const { return 3; }
  integer RobotArm::DHuDxp_numCols() const { return 7; }
  integer RobotArm::DHuDxp_nnz()     const { return 3; }

  void
  RobotArm::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 6   ;
  }


  void
  RobotArm::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 3, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::eta_numEqns() const { return 6; }

  void
  RobotArm::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda4__xo];
    result__[ 1   ] = L__[iL_lambda5__xo];
    result__[ 2   ] = L__[iL_lambda6__xo];
    result__[ 3   ] = ModelPars[iM_L] * L__[iL_lambda1__xo];
    real_type t3   = X__[iX_rho];
    real_type t5   = I_theta(t3, X__[iX_phi]);
    result__[ 4   ] = L__[iL_lambda2__xo] * t5;
    real_type t7   = I_phi(t3);
    result__[ 5   ] = L__[iL_lambda3__xo] * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DetaDxp_numRows() const { return 6; }
  integer RobotArm::DetaDxp_numCols() const { return 7; }
  integer RobotArm::DetaDxp_nnz()     const { return 3; }

  void
  RobotArm::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 0   ;
  }


  void
  RobotArm::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_rho];
    real_type t2   = X__[iX_phi];
    real_type t3   = I_theta_D_1(t1, t2);
    real_type t4   = L__[iL_lambda2__xo];
    result__[ 0   ] = t4 * t3;
    real_type t5   = I_theta_D_2(t1, t2);
    result__[ 1   ] = t4 * t5;
    real_type t6   = I_phi_D(t1);
    result__[ 2   ] = L__[iL_lambda3__xo] * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DetaDxp_sparse", 3, i_segment );
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer RobotArm::nu_numEqns() const { return 6; }

  void
  RobotArm::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_L] * V__[3];
    real_type t3   = X__[iX_rho];
    real_type t5   = I_theta(t3, X__[iX_phi]);
    result__[ 1   ] = V__[4] * t5;
    real_type t7   = I_phi(t3);
    result__[ 2   ] = V__[5] * t7;
    result__[ 3   ] = V__[0];
    result__[ 4   ] = V__[1];
    result__[ 5   ] = V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer RobotArm::DnuDxp_numRows() const { return 6; }
  integer RobotArm::DnuDxp_numCols() const { return 7; }
  integer RobotArm::DnuDxp_nnz()     const { return 3; }

  void
  RobotArm::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }


  void
  RobotArm::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_rho];
    real_type t2   = X__[iX_phi];
    real_type t3   = I_theta_D_1(t1, t2);
    real_type t4   = V__[4];
    result__[ 0   ] = t4 * t3;
    real_type t5   = I_theta_D_2(t1, t2);
    result__[ 1   ] = t4 * t5;
    real_type t6   = I_phi_D(t1);
    result__[ 2   ] = V__[5] * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DnuDxp_sparse", 3, i_segment );
  }

}

// EOF: RobotArm_Methods_AdjointODE.cc
