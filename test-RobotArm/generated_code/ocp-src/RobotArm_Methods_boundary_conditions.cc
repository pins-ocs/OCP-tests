/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_boundary_conditions.cc                        |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
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
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer
  RobotArm::boundaryConditions_numEqns() const
  { return 12; }

  void
  RobotArm::boundaryConditions_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_rho] - 0.45e1;
    result__[ 1   ] = XL__[iX_theta];
    real_type t3   = 0.314159265358979323846264338328e1 / 4;
    result__[ 2   ] = XL__[iX_phi] - t3;
    result__[ 3   ] = XL__[iX_rho1];
    result__[ 4   ] = XL__[iX_theta1];
    result__[ 5   ] = XL__[iX_phi1];
    result__[ 6   ] = XR__[iX_rho] - 0.45e1;
    result__[ 7   ] = XR__[iX_theta] - 2.0 / 3.0 * 0.314159265358979323846264338328e1;
    result__[ 8   ] = XR__[iX_phi] - t3;
    result__[ 9   ] = XR__[iX_rho1];
    result__[ 10  ] = XR__[iX_theta1];
    result__[ 11  ] = XR__[iX_phi1];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DboundaryConditionsDxxp_numRows() const
  { return 12; }

  integer
  RobotArm::DboundaryConditionsDxxp_numCols() const
  { return 13; }

  integer
  RobotArm::DboundaryConditionsDxxp_nnz() const
  { return 12; }

  void
  RobotArm::DboundaryConditionsDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 9   ;
    iIndex[10] = 10  ; jIndex[10] = 10  ;
    iIndex[11] = 11  ; jIndex[11] = 11  ;
  }

  void
  RobotArm::DboundaryConditionsDxxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = 1;
    result__[ 9   ] = 1;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxxp_sparse", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::adjointBC_numEqns() const
  { return 13; }

  void
  RobotArm::adjointBC_eval(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda4__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda5__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda6__xo];
    real_type t8   = ModelPars[iM_L];
    result__[ 3   ] = t8 * LL__[iL_lambda1__xo] + OMEGA__[3];
    real_type t12  = XL__[iX_rho];
    real_type t14  = I_theta(t12, XL__[iX_phi]);
    result__[ 4   ] = LL__[iL_lambda2__xo] * t14 + OMEGA__[4];
    real_type t18  = I_phi(t12);
    result__[ 5   ] = LL__[iL_lambda3__xo] * t18 + OMEGA__[5];
    result__[ 6   ] = OMEGA__[6] - LR__[iL_lambda4__xo];
    result__[ 7   ] = OMEGA__[7] - LR__[iL_lambda5__xo];
    result__[ 8   ] = OMEGA__[8] - LR__[iL_lambda6__xo];
    result__[ 9   ] = -t8 * LR__[iL_lambda1__xo] + OMEGA__[9];
    real_type t31  = XR__[iX_rho];
    real_type t33  = I_theta(t31, XR__[iX_phi]);
    result__[ 10  ] = -LR__[iL_lambda2__xo] * t33 + OMEGA__[10];
    real_type t37  = I_phi(t31);
    result__[ 11  ] = -LR__[iL_lambda3__xo] * t37 + OMEGA__[11];
    real_type t40  = ModelPars[iM_W];
    result__[ 12  ] = -2 * P__[iP_T] * (t40 - 1) + t40;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 13, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DadjointBCDxxp_numRows() const
  { return 13; }

  integer
  RobotArm::DadjointBCDxxp_numCols() const
  { return 13; }

  integer
  RobotArm::DadjointBCDxxp_nnz() const
  { return 7; }

  void
  RobotArm::DadjointBCDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 10  ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 10  ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 11  ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 12  ; jIndex[6 ] = 12  ;
  }

  void
  RobotArm::DadjointBCDxxp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = XL__[iX_rho];
    real_type t2   = XL__[iX_phi];
    real_type t3   = I_theta_D_1(t1, t2);
    real_type t4   = LL__[iL_lambda2__xo];
    result__[ 0   ] = t4 * t3;
    real_type t5   = I_theta_D_2(t1, t2);
    result__[ 1   ] = t5 * t4;
    real_type t6   = I_phi_D(t1);
    result__[ 2   ] = LL__[iL_lambda3__xo] * t6;
    real_type t8   = XR__[iX_rho];
    real_type t9   = XR__[iX_phi];
    real_type t10  = I_theta_D_1(t8, t9);
    real_type t11  = LR__[iL_lambda2__xo];
    result__[ 3   ] = -t11 * t10;
    real_type t13  = I_theta_D_2(t8, t9);
    result__[ 4   ] = -t11 * t13;
    real_type t15  = I_phi_D(t8);
    result__[ 5   ] = -LR__[iL_lambda3__xo] * t15;
    result__[ 6   ] = -2 * ModelPars[iM_W] + 2;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxxp_sparse", 7, i_segment_left, i_segment_right );
  }
}

// EOF: RobotArm_Methods_boundary_conditions.cc
