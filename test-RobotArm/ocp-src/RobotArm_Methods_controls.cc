/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_controls.cc                                   |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  RobotArm::g_numEqns() const
  { return 3; }

  void
  RobotArm::g_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[iP_T];
    real_type t5   = ALIAS_u_rhoControl_D_1(U__[iU_u_rho], -1, 1);
    result__[ 0   ] = t5 * t2 + t2 * L__[iL_lambda1__xo];
    real_type t10  = ALIAS_u_thetaControl_D_1(U__[iU_u_theta], -1, 1);
    result__[ 1   ] = t10 * t2 + t2 * L__[iL_lambda2__xo];
    real_type t15  = ALIAS_u_phiControl_D_1(U__[iU_u_phi], -1, 1);
    result__[ 2   ] = t15 * t2 + t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DgDxlp_numRows() const
  { return 3; }

  integer
  RobotArm::DgDxlp_numCols() const
  { return 13; }

  integer
  RobotArm::DgDxlp_nnz() const
  { return 6; }

  void
  RobotArm::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 12  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 12  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 12  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DgDxlp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = P__[iP_T];
    real_type t3   = ALIAS_u_rhoControl_D_1(U__[iU_u_rho], -1, 1);
    result__[ 1   ] = L__[iL_lambda1__xo] + t3;
    result__[ 2   ] = result__[0];
    real_type t6   = ALIAS_u_thetaControl_D_1(U__[iU_u_theta], -1, 1);
    result__[ 3   ] = L__[iL_lambda2__xo] + t6;
    result__[ 4   ] = result__[2];
    real_type t9   = ALIAS_u_phiControl_D_1(U__[iU_u_phi], -1, 1);
    result__[ 5   ] = L__[iL_lambda3__xo] + t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DgDu_numRows() const
  { return 3; }

  integer
  RobotArm::DgDu_numCols() const
  { return 3; }

  integer
  RobotArm::DgDu_nnz() const
  { return 3; }

  void
  RobotArm::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DgDu_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u_rhoControl_D_1_1(U__[iU_u_rho], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = ALIAS_u_thetaControl_D_1_1(U__[iU_u_theta], -1, 1);
    result__[ 1   ] = t5 * t1;
    real_type t7   = ALIAS_u_phiControl_D_1_1(U__[iU_u_phi], -1, 1);
    result__[ 2   ] = t7 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 3, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/
  integer
  RobotArm::u_numEqns() const
  { return 3; }

  void
  RobotArm::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_u_rho   ] = u_rhoControl.solve(-L__[iL_lambda1__xo], -1, 1);
    U__[ iU_u_theta ] = u_thetaControl.solve(-L__[iL_lambda2__xo], -1, 1);
    U__[ iU_u_phi   ] = u_phiControl.solve(-L__[iL_lambda3__xo], -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 3 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
    this->u_eval_analytic( NODE__, P__, U__ );
  }

  /*\
   |   ___       ___      _                       _      _   _
   |  |   \ _  _|   \__ _| |_ __   __ _ _ _  __ _| |_  _| |_(_)__
   |  | |) | || | |) \ \ / | '_ \ / _` | ' \/ _` | | || |  _| / _|
   |  |___/ \_,_|___//_\_\_| .__/ \__,_|_||_\__,_|_|\_, |\__|_\__|
   |                       |_|                      |__/
  \*/
  void
  RobotArm::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = 0;
    DuDxlp(1, 0) = 0;
    DuDxlp(2, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(2, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(1, 2) = 0;
    DuDxlp(2, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(2, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(2, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(2, 5) = 0;
    DuDxlp(0, 6) = -u_rhoControl.solve_rhs(-L__[iL_lambda1__xo], -1, 1);
    DuDxlp(1, 6) = 0;
    DuDxlp(2, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = -u_thetaControl.solve_rhs(-L__[iL_lambda2__xo], -1, 1);
    DuDxlp(2, 7) = 0;
    DuDxlp(0, 8) = 0;
    DuDxlp(1, 8) = 0;
    DuDxlp(2, 8) = -u_phiControl.solve_rhs(-L__[iL_lambda3__xo], -1, 1);
    DuDxlp(0, 9) = 0;
    DuDxlp(1, 9) = 0;
    DuDxlp(2, 9) = 0;
    DuDxlp(0, 10) = 0;
    DuDxlp(1, 10) = 0;
    DuDxlp(2, 10) = 0;
    DuDxlp(0, 11) = 0;
    DuDxlp(1, 11) = 0;
    DuDxlp(2, 11) = 0;
    DuDxlp(0, 12) = 0;
    DuDxlp(1, 12) = 0;
    DuDxlp(2, 12) = 0;
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 3 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  RobotArm::m_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u_rho];
    real_type t3   = u_rhoControl(t2, -1, 1);
    real_type t5   = U__[iU_u_theta];
    real_type t6   = u_thetaControl(t5, -1, 1);
    real_type t8   = U__[iU_u_phi];
    real_type t9   = u_phiControl(t8, -1, 1);
    real_type t16  = pow(-t2 * t1 + ModelPars[iM_L] * V__[3], 2);
    real_type t17  = X__[iX_rho];
    real_type t19  = I_theta(t17, X__[iX_phi]);
    real_type t24  = pow(-t5 * t1 + V__[4] * t19, 2);
    real_type t25  = I_phi(t17);
    real_type t30  = pow(-t8 * t1 + V__[5] * t25, 2);
    real_type t35  = pow(-X__[iX_rho1] * t1 + V__[0], 2);
    real_type t40  = pow(-X__[iX_theta1] * t1 + V__[1], 2);
    real_type t45  = pow(-X__[iX_phi1] * t1 + V__[2], 2);
    real_type result__ = t3 * t1 + t6 * t1 + t9 * t1 + t16 + t24 + t30 + t35 + t40 + t45;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DmDu_numEqns() const
  { return 3; }

  void
  RobotArm::DmDu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u_rho];
    real_type t3   = ALIAS_u_rhoControl_D_1(t2, -1, 1);
    result__[ 0   ] = t3 * t1 - 2 * t1 * (-t2 * t1 + ModelPars[iM_L] * V__[3]);
    real_type t12  = U__[iU_u_theta];
    real_type t13  = ALIAS_u_thetaControl_D_1(t12, -1, 1);
    real_type t15  = X__[iX_rho];
    real_type t17  = I_theta(t15, X__[iX_phi]);
    result__[ 1   ] = t13 * t1 - 2 * t1 * (-t12 * t1 + V__[4] * t17);
    real_type t24  = U__[iU_u_phi];
    real_type t25  = ALIAS_u_phiControl_D_1(t24, -1, 1);
    real_type t27  = I_phi(t15);
    result__[ 2   ] = t25 * t1 - 2 * t1 * (-t24 * t1 + V__[5] * t27);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DmDuu_numRows() const
  { return 3; }

  integer
  RobotArm::DmDuu_numCols() const
  { return 3; }

  integer
  RobotArm::DmDuu_nnz() const
  { return 3; }

  void
  RobotArm::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  RobotArm::DmDuu_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u_rhoControl_D_1_1(U__[iU_u_rho], -1, 1);
    real_type t5   = t1 * t1;
    real_type t6   = 2 * t5;
    result__[ 0   ] = t3 * t1 + t6;
    real_type t8   = ALIAS_u_thetaControl_D_1_1(U__[iU_u_theta], -1, 1);
    result__[ 1   ] = t8 * t1 + t6;
    real_type t11  = ALIAS_u_phiControl_D_1_1(U__[iU_u_phi], -1, 1);
    result__[ 2   ] = t11 * t1 + t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 3, i_segment );
  }

}

// EOF: RobotArm_Methods_controls.cc
