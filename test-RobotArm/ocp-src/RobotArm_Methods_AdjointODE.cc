/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods.cc                                            |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  RobotArm::Hx_numEqns() const
  { return 6; }

  void
  RobotArm::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = L__[1];
    real_type t2   = X__[0];
    real_type t3   = X__[2];
    real_type t4   = I_theta_D_1(t2, t3);
    real_type t6   = V__[4];
    real_type t9   = I_phi_D(t2);
    result__[ 0   ] = -t6 * t4 * t1 - V__[5] * t9 * L__[2];
    result__[ 1   ] = 0;
    real_type t13  = I_theta_D_2(t2, t3);
    result__[ 2   ] = -t6 * t13 * t1;
    real_type t17  = P__[0];
    result__[ 3   ] = t17 * L__[3];
    result__[ 4   ] = t17 * L__[4];
    result__[ 5   ] = t17 * L__[5];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DHxDx_numRows() const
  { return 6; }

  integer
  RobotArm::DHxDx_numCols() const
  { return 6; }

  integer
  RobotArm::DHxDx_nnz() const
  { return 4; }

  void
  RobotArm::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 2   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 2   ; jIndex[ 3  ] = 2   ;
  }

  void
  RobotArm::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = L__[1];
    real_type t2   = X__[0];
    real_type t3   = X__[2];
    real_type t4   = I_theta_D_1_1(t2, t3);
    real_type t6   = V__[4];
    real_type t9   = I_phi_DD(t2);
    result__[ 0   ] = -t6 * t4 * t1 - V__[5] * t9 * L__[2];
    real_type t13  = I_theta_D_1_2(t2, t3);
    result__[ 1   ] = -t6 * t13 * t1;
    result__[ 2   ] = result__[1];
    real_type t16  = I_theta_D_2_2(t2, t3);
    result__[ 3   ] = -t6 * t16 * t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DHxDp_numRows() const
  { return 6; }

  integer
  RobotArm::DHxDp_numCols() const
  { return 1; }

  integer
  RobotArm::DHxDp_nnz() const
  { return 3; }

  void
  RobotArm::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 3   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 4   ; jIndex[ 1  ] = 0   ;
    iIndex[ 2  ] = 5   ; jIndex[ 2  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[3];
    result__[ 1   ] = L__[4];
    result__[ 2   ] = L__[5];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDp_sparse",3);
    #endif
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  integer
  RobotArm::Hu_numEqns() const
  { return 3; }

  void
  RobotArm::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    result__[ 0   ] = t2 * L__[0];
    result__[ 1   ] = t2 * L__[1];
    result__[ 2   ] = t2 * L__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DHuDx_numRows() const
  { return 3; }

  integer
  RobotArm::DHuDx_numCols() const
  { return 6; }

  integer
  RobotArm::DHuDx_nnz() const
  { return 0; }

  void
  RobotArm::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DHuDp_numRows() const
  { return 3; }

  integer
  RobotArm::DHuDp_numCols() const
  { return 1; }

  integer
  RobotArm::DHuDp_nnz() const
  { return 3; }

  void
  RobotArm::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 0   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = L__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHuDp_sparse",3);
    #endif
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  RobotArm::Hp_numEqns() const
  { return 1; }

  void
  RobotArm::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0] * U__[0] + L__[1] * U__[1] + L__[2] * U__[2] + L__[3] * X__[3] + L__[4] * X__[4] + L__[5] * X__[5];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hp_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DHpDp_numRows() const
  { return 1; }

  integer
  RobotArm::DHpDp_numCols() const
  { return 1; }

  integer
  RobotArm::DHpDp_nnz() const
  { return 0; }

  void
  RobotArm::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  integer
  RobotArm::eta_numEqns() const
  { return 6; }

  void
  RobotArm::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[3];
    result__[ 1   ] = L__[4];
    result__[ 2   ] = L__[5];
    result__[ 3   ] = ModelPars[0] * L__[0];
    real_type t3   = X__[0];
    real_type t5   = I_theta(t3, X__[2]);
    result__[ 4   ] = L__[1] * t5;
    real_type t7   = I_phi(t3);
    result__[ 5   ] = L__[2] * t7;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"eta_eval",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DetaDx_numRows() const
  { return 6; }

  integer
  RobotArm::DetaDx_numCols() const
  { return 6; }

  integer
  RobotArm::DetaDx_nnz() const
  { return 3; }

  void
  RobotArm::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 4   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 4   ; jIndex[ 1  ] = 2   ;
    iIndex[ 2  ] = 5   ; jIndex[ 2  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[2];
    real_type t3   = I_theta_D_1(t1, t2);
    real_type t4   = L__[1];
    result__[ 0   ] = t4 * t3;
    real_type t5   = I_theta_D_2(t1, t2);
    result__[ 1   ] = t4 * t5;
    real_type t6   = I_phi_D(t1);
    result__[ 2   ] = L__[2] * t6;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DetaDx_sparse",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DetaDp_numRows() const
  { return 6; }

  integer
  RobotArm::DetaDp_numCols() const
  { return 1; }

  integer
  RobotArm::DetaDp_nnz() const
  { return 0; }

  void
  RobotArm::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  RobotArm::nu_numEqns() const
  { return 6; }

  void
  RobotArm::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = ModelPars[0] * V__[3];
    real_type t3   = X__[0];
    real_type t5   = I_theta(t3, X__[2]);
    result__[ 1   ] = V__[4] * t5;
    real_type t7   = I_phi(t3);
    result__[ 2   ] = V__[5] * t7;
    result__[ 3   ] = V__[0];
    result__[ 4   ] = V__[1];
    result__[ 5   ] = V__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"nu_eval",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DnuDx_numRows() const
  { return 6; }

  integer
  RobotArm::DnuDx_numCols() const
  { return 6; }

  integer
  RobotArm::DnuDx_nnz() const
  { return 3; }

  void
  RobotArm::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 1   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 2   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[2];
    real_type t3   = I_theta_D_1(t1, t2);
    real_type t4   = V__[4];
    result__[ 0   ] = t4 * t3;
    real_type t5   = I_theta_D_2(t1, t2);
    result__[ 1   ] = t4 * t5;
    real_type t6   = I_phi_D(t1);
    result__[ 2   ] = V__[5] * t6;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DnuDx_sparse",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DnuDp_numRows() const
  { return 6; }

  integer
  RobotArm::DnuDp_numCols() const
  { return 1; }

  integer
  RobotArm::DnuDp_nnz() const
  { return 0; }

  void
  RobotArm::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: RobotArm_Methods.cc
