/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_UserFunctions.cc                 |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"
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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_G_bound_max_DD(__t1) G_bound_max.DD( __t1)
#define ALIAS_G_bound_max_D(__t1) G_bound_max.D( __t1)
#define ALIAS_G_bound_min_DD(__t1) G_bound_min.DD( __t1)
#define ALIAS_G_bound_min_D(__t1) G_bound_min.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)


namespace HypersonicProblem3DOFDefine {
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
  HypersonicProblem3DOF::h_guess( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_h_i] * (1 - xo__s) + ModelPars[iM_h_f] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_h_guess( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::h_guess_D( real_type xo__s ) const {
    real_type result__ = -ModelPars[iM_h_i] + ModelPars[iM_h_f];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_h_guess_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::h_guess_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_h_guess_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::theta_guess( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_theta_i] * (1 - xo__s) + ModelPars[iM_theta_f] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_theta_guess( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::theta_guess_D( real_type xo__s ) const {
    real_type result__ = -ModelPars[iM_theta_i] + ModelPars[iM_theta_f];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_theta_guess_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::theta_guess_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_theta_guess_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::phi_guess( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_phi_i] * (1 - xo__s) + ModelPars[iM_phi_f] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_phi_guess( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::phi_guess_D( real_type xo__s ) const {
    real_type result__ = -ModelPars[iM_phi_i] + ModelPars[iM_phi_f];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_phi_guess_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::phi_guess_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_phi_guess_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::V_guess( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_V_i] * (1 - xo__s) + ModelPars[iM_V_f] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_V_guess( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::V_guess_D( real_type xo__s ) const {
    real_type result__ = -ModelPars[iM_V_i] + ModelPars[iM_V_f];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_V_guess_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::V_guess_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_V_guess_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::G_guess( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_G_i] * (1 - xo__s) + ModelPars[iM_G_f] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_G_guess( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::G_guess_D( real_type xo__s ) const {
    real_type result__ = -ModelPars[iM_G_i] + ModelPars[iM_G_f];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_G_guess_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::G_guess_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_G_guess_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::psi_guess( real_type xo__s ) const {
    real_type result__ = ModelPars[iM_psi_i] * (1 - xo__s) + ModelPars[iM_psi_f] * xo__s;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_psi_guess( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::psi_guess_D( real_type xo__s ) const {
    real_type result__ = -ModelPars[iM_psi_i] + ModelPars[iM_psi_f];
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_psi_guess_D( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::psi_guess_DD( real_type xo__s ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_psi_guess_DD( s={} ) return {}\n",
        xo__s, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::G_bound( real_type xo___V ) const {
    real_type t2   = G_bound_min(-0.314159265358979323846264338328e1 - xo___V);
    real_type t4   = G_bound_max(xo___V - 0.314159265358979323846264338328e1);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_G_bound( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::G_bound_D( real_type xo___V ) const {
    real_type t2   = ALIAS_G_bound_min_D(-0.314159265358979323846264338328e1 - xo___V);
    real_type t4   = ALIAS_G_bound_max_D(xo___V - 0.314159265358979323846264338328e1);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_G_bound_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  HypersonicProblem3DOF::G_bound_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_G_bound_min_DD(-0.314159265358979323846264338328e1 - xo___V);
    real_type t4   = ALIAS_G_bound_max_DD(xo___V - 0.314159265358979323846264338328e1);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_G_bound_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

}

// EOF: HypersonicProblem3DOF_Methods_UserFunctions.cc
