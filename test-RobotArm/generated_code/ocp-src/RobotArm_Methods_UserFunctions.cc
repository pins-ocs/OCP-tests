/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods_UserFunctions.cc                              |
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
#include <cmath>

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
  using std::acos;
  using std::acosh;
  using std::asin;
  using std::asinh;
  using std::atan;
  using std::atan2;
  using std::atanh;
  using std::cbrt;
  using std::ceil;
  using std::abs;
  using std::cos;
  using std::cosh;
  using std::exp;
  using std::exp2;
  using std::expm1;
  using std::floor;
  using std::log;
  using std::log10;
  using std::log1p;
  using std::log2;
  using std::logb;
  using std::pow;
  using std::hypot;
  using std::floor;
  using std::round;
  using std::sin;
  using std::sinh;
  using std::sqrt;
  using std::tan;
  using std::tanh;
  using std::trunc;
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  RobotArm::I_phi( real_type xo__rho ) const {
    real_type t2   = ModelPars[iM_L] - xo__rho;
    real_type t3   = t2 * t2;
    real_type t5   = xo__rho * xo__rho;
    real_type result__ = t3 * t2 / 3 + t5 * xo__rho / 3;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_phi( rho={} ) return {}\n",
        xo__rho, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_phi_D( real_type xo__rho ) const {
    real_type t3   = pow(ModelPars[iM_L] - xo__rho, 2);
    real_type t4   = xo__rho * xo__rho;
    real_type result__ = -t3 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_phi_D( rho={} ) return {}\n",
        xo__rho, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_phi_DD( real_type xo__rho ) const {
    real_type result__ = 2 * ModelPars[iM_L];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_phi_DD( rho={} ) return {}\n",
        xo__rho, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_theta( real_type xo__rho, real_type xo__phi ) const {
    real_type t1   = I_phi(xo__rho);
    real_type t2   = sin(xo__phi);
    real_type t3   = t2 * t2;
    real_type result__ = t3 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_theta( rho={}, phi={} ) return {}\n",
        xo__rho, xo__phi, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_theta_D_1( real_type xo__rho, real_type xo__phi ) const {
    real_type t1   = I_phi_D(xo__rho);
    real_type t2   = sin(xo__phi);
    real_type t3   = t2 * t2;
    real_type result__ = t3 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_theta_D_1( rho={}, phi={} ) return {}\n",
        xo__rho, xo__phi, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_theta_D_1_1( real_type xo__rho, real_type xo__phi ) const {
    real_type t1   = I_phi_DD(xo__rho);
    real_type t2   = sin(xo__phi);
    real_type t3   = t2 * t2;
    real_type result__ = t3 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_theta_D_1_1( rho={}, phi={} ) return {}\n",
        xo__rho, xo__phi, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_theta_D_1_2( real_type xo__rho, real_type xo__phi ) const {
    real_type t1   = I_phi_D(xo__rho);
    real_type t2   = sin(xo__phi);
    real_type t4   = cos(xo__phi);
    real_type result__ = 2 * t4 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_theta_D_1_2( rho={}, phi={} ) return {}\n",
        xo__rho, xo__phi, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_theta_D_2( real_type xo__rho, real_type xo__phi ) const {
    real_type t1   = I_phi(xo__rho);
    real_type t2   = sin(xo__phi);
    real_type t4   = cos(xo__phi);
    real_type result__ = 2 * t4 * t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_theta_D_2( rho={}, phi={} ) return {}\n",
        xo__rho, xo__phi, result__
      );
    }
    return result__;
  }

  real_type
  RobotArm::I_theta_D_2_2( real_type xo__rho, real_type xo__phi ) const {
    real_type t1   = I_phi(xo__rho);
    real_type t2   = cos(xo__phi);
    real_type t3   = t2 * t2;
    real_type t5   = sin(xo__phi);
    real_type t6   = t5 * t5;
    real_type result__ = 2 * t3 * t1 - 2 * t6 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_I_theta_D_2_2( rho={}, phi={} ) return {}\n",
        xo__rho, xo__phi, result__
      );
    }
    return result__;
  }

}

// EOF: RobotArm_Methods_UserFunctions.cc
