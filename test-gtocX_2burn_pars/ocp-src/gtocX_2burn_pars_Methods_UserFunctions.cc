/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_UserFunctions.cc                      |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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


#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burn_parsDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  gtocX_2burn_pars::cont( real_type xo__s, real_type xo__eps0, real_type xo__eps1 ) const {
    real_type t2   = log(xo__eps0);
    real_type t4   = log(xo__eps1);
    real_type result__ = exp(t2 * (1 - xo__s) + t4 * xo__s);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_cont( s={}, eps0={}, eps1={} ) return {}\n",
        xo__s, xo__eps0, xo__eps1, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type result__ = 1.0 / (t1 + t2 + 1) / (t4 * xo__f + t7 * xo__g + 1) * (t4 * (t1 - t2 + 1) + 2 * t7 * xo__k * xo__retrograde * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type result__ = 1.0 / (t1 + t2 + 1) / (t4 * xo__f + t7 * xo__g + 1) * (t4 * (t1 - t2 + 1) + 2 * t7 * xo__k * xo__retrograde * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = sin(xo__L);
    real_type t10  = cos(xo__L);
    real_type t19  = t10 * t10;
    real_type t20  = xo__f * xo__f;
    real_type t22  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t10 * t6 + 2 * t10 * xo__f + t20 * t19 - t22 * t19 + 2 * t6 * xo__g + t22 + 1) * t10 * (2 * t6 * xo__k * xo__retrograde * xo__h + t1 * t10 - t2 * t10 + t10) / (t1 + t2 + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = sin(xo__L);
    real_type t10  = cos(xo__L);
    real_type t19  = t10 * t10;
    real_type t20  = xo__f * xo__f;
    real_type t22  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t10 * t6 + 2 * t10 * xo__f + t20 * t19 - t22 * t19 + 2 * t6 * xo__g + t22 + 1) * t6 * (2 * t6 * xo__k * xo__retrograde * xo__h + t1 * t10 - t2 * t10 + t10) / (t1 + t2 + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t18  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t18 / (t5 * xo__g + t7 * xo__f + 1) * xo__k * (t5 * (t1 - t2 - 1) * xo__retrograde - 2 * xo__k * xo__h * t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t9   = cos(xo__L);
    real_type t21  = pow(t2 + t3 + 1, 2);
    real_type result__ = 1.0 / t21 / (t5 * xo__g + t9 * xo__f + 1) * (2 * t5 * (t2 - t3 + 1) * xo__h * xo__retrograde - 4 * (t2 + 1) * xo__k * t9);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__k * xo__retrograde;
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t8   = -t6 + t7 - 1;
    real_type t9   = sin(xo__L);
    real_type t16  = xo__f * xo__f;
    real_type t17  = xo__g * xo__g;
    real_type t19  = t1 * t1;
    real_type result__ = 1.0 / (t6 + t7 + 1) / (t19 * (t16 - t17) + t1 * (2 * t9 * xo__g * xo__f + 2 * xo__f) + t17 + 2 * t9 * xo__g + 1) * (2 * t3 * xo__h * t1 + 2 * t3 * xo__f * xo__h + t9 * t8 + xo__g * t8);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_1_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sin(xo__L);
    real_type t3   = cos(xo__L);
    real_type t9   = xo__h * xo__h;
    real_type t10  = xo__k * xo__k;
    real_type result__ = 2 / (t9 + t10 + 1) / (t2 * xo__g + t3 * xo__f + 1) * t2 * xo__h * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_1_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t11  = cos(xo__L);
    real_type t20  = t11 * t11;
    real_type t21  = xo__f * xo__f;
    real_type t23  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t11 * t7 + 2 * t11 * xo__f + t21 * t20 - t23 * t20 + 2 * t7 * xo__g + t23 + 1) * t11 * (2 * t7 * xo__k * xo__retrograde * xo__h + t1 * t11 - t2 * t11 + t11) / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t13  = t4 * t4;
    real_type t17  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t27  = t19 * xo__g;
    real_type t31  = 3 * t19;
    real_type result__ = 2 / (t13 * t4 * (t17 * xo__f - 3 * t19 * xo__f) + t13 * (t7 * (3 * xo__g * t17 - t27) + 3 * t17 - t31) + 3 * t4 * (2 * t7 * xo__g + t19 + 1) * xo__f + t7 * (t27 + 3 * xo__g) + t31 + 1) / (t1 + t2 + 1) * t13 * (t4 * (t1 - t2 + 1) + 2 * t7 * xo__k * xo__retrograde * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t7   = sin(xo__L);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type t21  = xo__f * xo__f;
    real_type t23  = xo__g * xo__g;
    real_type t31  = t23 * xo__g;
    real_type t35  = 3 * t23;
    real_type result__ = 2 / (t2 * t1 * (t21 * xo__f - 3 * t23 * xo__f) + t2 * (t7 * (3 * xo__g * t21 - t31) + 3 * t21 - t35) + 3 * t1 * (2 * t7 * xo__g + t23 + 1) * xo__f + t7 * (t31 + 3 * xo__g) + t35 + 1) / (t8 + t9 + 1) * t1 * (-2 * xo__k * xo__retrograde * xo__h * t2 + t1 * (t8 - t9 + 1) * t7 + 2 * xo__h * xo__k * xo__retrograde) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t14  = xo__f * xo__f;
    real_type t15  = xo__g * xo__g;
    real_type t17  = t1 * t1;
    real_type t30  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t30 / (t17 * (t14 - t15) + t1 * (2 * t7 * xo__g * xo__f + 2 * xo__f) + t15 + 2 * t7 * xo__g + 1) * xo__k * (t7 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t1) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t5   = cos(xo__L);
    real_type t8   = xo__k * xo__k;
    real_type t10  = sin(xo__L);
    real_type t15  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t18  = t5 * t5;
    real_type t31  = pow(t1 + t8 + 1, 2);
    real_type result__ = -2 / t31 / (t18 * (t15 - t16) + t5 * (2 * t10 * xo__g * xo__f + 2 * xo__f) + t16 + 2 * t10 * xo__g + 1) * t5 * (t5 * (-2 * xo__k * t1 - 2 * xo__k) + t10 * (t1 - t8 + 1) * xo__h * xo__retrograde) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = xo__k * xo__retrograde;
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t9   = -t7 + t8 - 1;
    real_type t10  = sin(xo__L);
    real_type t18  = t10 * xo__g;
    real_type t26  = xo__f * xo__f;
    real_type t28  = xo__g * xo__g;
    real_type t36  = t28 * xo__g;
    real_type t40  = 3 * t28;
    real_type result__ = -2 / (t2 * t1 * (t26 * xo__f - 3 * t28 * xo__f) + t2 * (t10 * (3 * xo__g * t26 - t36) + 3 * t26 - t40) + 3 * t1 * (t28 + 2 * t18 + 1) * xo__f + t10 * (t36 + 3 * xo__g) + t40 + 1) / (t7 + t8 + 1) * (2 * t4 * xo__h * t2 + t1 * (t4 * xo__f * xo__h + t10 * t9 + xo__g * t9) - (t18 + 1) * xo__retrograde * xo__h * xo__k) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_2_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t9   = cos(xo__L);
    real_type t14  = t9 * t9;
    real_type t15  = xo__f * xo__f;
    real_type t17  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t9 * t7 + t15 * t14 - t17 * t14 + 2 * t7 * xo__g + 2 * t9 * xo__f + t17 + 1) * t9 * t7 * xo__k * xo__h / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_2_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t11  = cos(xo__L);
    real_type t20  = t11 * t11;
    real_type t21  = xo__f * xo__f;
    real_type t23  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t11 * t7 + 2 * t11 * xo__f + t21 * t20 - t23 * t20 + 2 * t7 * xo__g + t23 + 1) * t7 * (2 * t7 * xo__k * xo__retrograde * xo__h + t1 * t11 - t2 * t11 + t11) / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t17  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t23  = t7 * t7;
    real_type t28  = t19 * xo__g;
    real_type t32  = 3 * t19;
    real_type result__ = 2 / (t23 * t7 * (t17 * xo__f - 3 * t19 * xo__f) + t23 * (t1 * (3 * xo__g * t17 - t28) + 3 * t17 - t32) + 3 * t7 * (2 * t1 * xo__g + t19 + 1) * xo__f + t1 * (t28 + 3 * xo__g) + t32 + 1) / (t4 + t5 + 1) * (t7 * (t4 - t5 + 1) + 2 * t1 * xo__k * xo__retrograde * xo__h) * t2 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_3_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t8   = cos(xo__L);
    real_type t14  = xo__f * t8;
    real_type t19  = xo__f * xo__f;
    real_type t20  = xo__g * xo__g;
    real_type t22  = t8 * t8;
    real_type t29  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t29 / (t1 * (2 * xo__g * t14 + 2 * xo__g) + t22 * (t19 - t20) + 2 * t14 + t20 + 1) * xo__k * (t1 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t8) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_3_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t7   = cos(xo__L);
    real_type t10  = xo__k * xo__k;
    real_type t15  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t18  = t7 * t7;
    real_type t31  = pow(t3 + t10 + 1, 2);
    real_type result__ = -2 / t31 / (t18 * (t15 - t16) + t7 * (2 * t1 * xo__g * xo__f + 2 * xo__f) + t16 + 2 * t1 * xo__g + 1) * (t7 * (-2 * xo__k * t3 - 2 * xo__k) + t1 * (t3 - t10 + 1) * xo__h * xo__retrograde) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_3_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_3_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 + 1;
    real_type t5   = cos(xo__L);
    real_type t6   = t5 * t5;
    real_type t9   = sin(xo__L);
    real_type t28  = xo__f * xo__f;
    real_type t30  = xo__g * xo__g;
    real_type t38  = t30 * xo__g;
    real_type t42  = 3 * t30;
    real_type result__ = -1.0 / (t6 * t5 * (t28 * xo__f - 3 * t30 * xo__f) + t6 * (t9 * (3 * xo__g * t28 - t38) + 3 * t28 - t42) + 3 * t5 * (2 * t9 * xo__g + t30 + 1) * xo__f + t9 * (t38 + 3 * xo__g) + t42 + 1) / (t1 + t2 + 1) * (2 * t6 * t3 + t5 * (4 * t9 * xo__k * xo__retrograde * xo__h + t3 * xo__f) + t9 * (4 * xo__f * xo__h * xo__k * xo__retrograde - xo__g * t3) - t1 + t2 - 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_3_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_3_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t8   = t7 * t7;
    real_type t10  = cos(xo__L);
    real_type t15  = t10 * t10;
    real_type t16  = xo__f * xo__f;
    real_type t18  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t10 * t7 + 2 * t10 * xo__f + t16 * t15 - t18 * t15 + 2 * t7 * xo__g + t18 + 1) * t8 * xo__k * xo__h / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_3_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t19 / (t5 * xo__g + t7 * xo__f + 1) * xo__k * (t5 * (t1 - t2 - 1) * xo__retrograde - 2 * xo__k * xo__h * t7) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t8   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t22  = t2 + t5 + 1;
    real_type t23  = t22 * t22;
    real_type result__ = 4 / t23 / t22 / (t11 * xo__g + t8 * xo__f + 1) * (t8 * (-3 * xo__k * t2 + t5 * xo__k + xo__k) + (t2 - 3 * t5 - 3) * t11 * xo__retrograde * xo__h) * xo__p * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_4_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = t1 * t1;
    real_type t3   = xo__k * xo__k;
    real_type t6   = t3 * t3;
    real_type t9   = sin(xo__L);
    real_type t11  = cos(xo__L);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    real_type result__ = -2 / t24 / t23 / (t11 * xo__f + t9 * xo__g + 1) * (t9 * (-6 * t3 * t1 + t2 + t6 - 1) * xo__retrograde - 4 * (t1 - t3 + 1) * xo__k * xo__h * t11) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_4_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_4_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t18  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t21  = t5 * t5;
    real_type t34  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t34 / (t21 * (t18 - t19) + t5 * (2 * t8 * xo__g * xo__f + 2 * xo__f) + t19 + 2 * t8 * xo__g + 1) * xo__k * xo__p * (t5 * t3 * xo__retrograde + xo__retrograde * t3 * xo__f + 2 * t8 * xo__k * xo__h + 2 * xo__g * xo__h * xo__k);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_4_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_4_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t14  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t14 / (t5 * xo__g + t7 * xo__f + 1) * xo__k * t5 * (t1 - t2 - 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_4_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t8   = cos(xo__L);
    real_type t20  = pow(t2 + t3 + 1, 2);
    real_type result__ = 2 / t20 / (t5 * xo__g + t8 * xo__f + 1) * (t5 * (t2 - t3 + 1) * xo__h * xo__retrograde - 2 * (t2 + 1) * xo__k * t8) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t9   = sin(xo__L);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    real_type result__ = -4 / t24 / t23 / (t7 * xo__f + t9 * xo__g + 1) * (t7 * (t1 - 3 * t3 + 1) * (t1 + 1) + 3 * xo__k * (t1 - t3 / 3 + 1) * xo__retrograde * xo__h * t9) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_5_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_5_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t28  = xo__f * xo__f;
    real_type t29  = xo__g * xo__g;
    real_type t31  = t5 * t5;
    real_type t43  = pow(t2 + t3 + 1, 2);
    real_type result__ = 2 / t43 / (t31 * (t28 - t29) + t5 * (2 * t11 * xo__g * xo__f + 2 * xo__f) + t29 + 2 * t11 * xo__g + 1) * (t5 * (t2 - t3 + 1) * xo__h * xo__retrograde + t11 * (2 * xo__k * t2 + 2 * xo__k) + xo__retrograde * t2 * xo__h * xo__f + 2 * xo__k * t2 * xo__g + xo__h * (-xo__retrograde * t3 * xo__f + xo__f * xo__retrograde) + 2 * xo__g * xo__k) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_5_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_5_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t6   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t14  = pow(t2 + t3 + 1, 2);
    real_type result__ = 2 / t14 / (t6 * xo__g + t7 * xo__f + 1) * t6 * (t2 - t3 + 1) * xo__h * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_5_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t3   = cos(xo__L);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t10  = (-t7 + t8 - 1) * xo__p;
    real_type t11  = sin(xo__L);
    real_type t20  = xo__f * xo__f;
    real_type t21  = xo__g * xo__g;
    real_type t23  = t3 * t3;
    real_type result__ = 1.0 / (t7 + t8 + 1) / (t23 * (t20 - t21) + t3 * (2 * t11 * xo__g * xo__f + 2 * xo__f) + t21 + 2 * t11 * xo__g + 1) * (2 * t3 * xo__retrograde * xo__k * xo__p * xo__h + 2 * xo__p * xo__f * xo__h * xo__k * xo__retrograde + t11 * t10 + xo__g * t10);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_6_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__k * xo__retrograde;
    real_type t4   = t2 * xo__g * xo__h / 2;
    real_type t5   = xo__h * xo__h;
    real_type t6   = xo__k * xo__k;
    real_type t7   = t5 - t6 + 1;
    real_type t8   = t7 * xo__f;
    real_type t11  = cos(xo__L);
    real_type t12  = t11 * t11;
    real_type t20  = sin(xo__L);
    real_type t23  = xo__g * xo__g;
    real_type t26  = xo__h * xo__k;
    real_type t35  = xo__f * xo__f;
    real_type t54  = t23 * xo__g;
    real_type t58  = 3 * t23;
    real_type result__ = 4 / (t12 * t11 * (-3 * t23 * xo__f + t35 * xo__f) + t12 * (t20 * (3 * xo__g * t35 - t54) + 3 * t35 - t58) + 3 * t11 * (2 * t20 * xo__g + t23 + 1) * xo__f + t20 * (t54 + 3 * xo__g) + t58 + 1) / (t5 + t6 + 1) * (t12 * (-t4 + t8 / 4) + t11 * (t20 * (xo__g * t7 / 4 + t2 * xo__f * xo__h / 2) + t23 * t7 / 2 - xo__retrograde * t26 * xo__f * xo__g - t5 / 4 + t6 / 4 - 1.0 / 4.0) + t20 * (-xo__g * t8 / 2 + (t35 - 1.0 / 2.0) * xo__retrograde * t26) - t4 - t8 / 2) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_6_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_6_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t15  = t7 * t7;
    real_type t16  = xo__f * xo__f;
    real_type t18  = xo__g * xo__g;
    real_type result__ = 2 / (2 * xo__f * xo__g * t7 * t10 + 2 * xo__g * t10 + t16 * t15 - t18 * t15 + 2 * t7 * xo__f + t18 + 1) * (t7 + xo__f) * xo__p * xo__k * xo__h / (t1 + t2 + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_6_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t3   = sin(xo__L);
    real_type t4   = cos(xo__L);
    real_type t10  = xo__h * xo__h;
    real_type t11  = xo__k * xo__k;
    real_type result__ = 2 / (t10 + t11 + 1) / (t3 * xo__g + t4 * xo__f + 1) * t3 * xo__p * xo__h * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_position_D_7_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_position_D_7_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type result__ = -1.0 / (t1 + t2 + 1) / (t5 * xo__g + t7 * xo__f + 1) * (t5 * (t1 - t2 - 1) * xo__retrograde - 2 * xo__k * xo__h * t7) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type result__ = 1.0 / (t1 + t2 + 1) / (t5 * xo__g + t7 * xo__f + 1) * (-t5 * (t1 - t2 - 1) * xo__retrograde + 2 * xo__k * xo__h * t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = t7 * t7;
    real_type result__ = 1.0 / (t1 + t2 + 1) / (t16 * (t13 - t14) + t7 * (2 * t5 * xo__g * xo__f + 2 * xo__f) + t14 + 2 * t5 * xo__g + 1) * t7 * (t5 * (t1 - t2 - 1) * xo__retrograde - 2 * xo__k * xo__h * t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t13  = t7 * xo__f;
    real_type t18  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t21  = t7 * t7;
    real_type result__ = 1.0 / (t1 + t2 + 1) / (t5 * (2 * xo__g * t13 + 2 * xo__g) + t21 * (t18 - t19) + 2 * t13 + t19 + 1) * t5 * (t5 * (t1 - t2 - 1) * xo__retrograde - 2 * xo__k * xo__h * t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t22  = pow(t1 + t3 + 1, 2);
    real_type result__ = 1.0 / t22 / (t10 * xo__g + t7 * xo__f + 1) * (t7 * (-2 * xo__k * t1 + 2 * t3 * xo__k + 2 * xo__k) - 4 * (t3 + 1) * t10 * xo__retrograde * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t18  = pow(t1 + t2 + 1, 2);
    real_type result__ = 2 * xo__h / t18 / (t4 * xo__f + t7 * xo__g + 1) * (t4 * (t1 - t2 + 1) + 2 * t7 * xo__k * xo__retrograde * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t17  = xo__f * xo__f;
    real_type t18  = xo__g * xo__g;
    real_type t20  = t5 * t5;
    real_type result__ = 1.0 / (t1 + t2 + 1) / (t20 * (t17 - t18) + t5 * (2 * t8 * xo__g * xo__f + 2 * xo__f) + t18 + 2 * t8 * xo__g + 1) * (-t5 * t3 * xo__retrograde - xo__retrograde * t3 * xo__f - 2 * t8 * xo__k * xo__h - 2 * xo__g * xo__h * xo__k);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_1_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = sin(xo__L);
    real_type t6   = cos(xo__L);
    real_type result__ = -1.0 / (t1 + t2 + 1) / (t4 * xo__g + t6 * xo__f + 1) * t4 * (t1 - t2 - 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_1_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = t1 * t1;
    real_type result__ = 1.0 / (t3 + t4 + 1) / (t16 * (t13 - t14) + t1 * (2 * t7 * xo__g * xo__f + 2 * xo__f) + t14 + 2 * t7 * xo__g + 1) * (t7 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t1) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t8   = sin(xo__L);
    real_type t17  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t27  = t19 * xo__g;
    real_type t31  = 3 * t19;
    real_type result__ = -2 / (t2 * t1 * (t17 * xo__f - 3 * t19 * xo__f) + t2 * (t8 * (3 * xo__g * t17 - t27) + 3 * t17 - t31) + 3 * t1 * (2 * t8 * xo__g + t19 + 1) * xo__f + t8 * (t27 + 3 * xo__g) + t31 + 1) / (t4 + t5 + 1) * (t8 * (t4 - t5 - 1) * xo__retrograde - 2 * xo__k * xo__h * t1) * t2 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t6   = (t3 - t4 - 1) * xo__retrograde;
    real_type t7   = t1 * t1;
    real_type t9   = sin(xo__L);
    real_type t18  = xo__f * xo__f;
    real_type t20  = xo__g * xo__g;
    real_type t28  = t20 * xo__g;
    real_type t32  = 3 * t20;
    real_type result__ = 2 / (t7 * t1 * (t18 * xo__f - 3 * t20 * xo__f) + t7 * (t9 * (3 * xo__g * t18 - t28) + 3 * t18 - t32) + 3 * t1 * (2 * t9 * xo__g + t20 + 1) * xo__f + t9 * (t28 + 3 * xo__g) + t32 + 1) / (t3 + t4 + 1) * (2 * xo__h * xo__k * t1 * t9 + t7 * t6 - t6) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t9   = sin(xo__L);
    real_type t15  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t18  = t1 * t1;
    real_type t31  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t31 / (t18 * (t15 - t16) + t1 * (2 * t9 * xo__g * xo__f + 2 * xo__f) + t16 + 2 * t9 * xo__g + 1) * (t1 * (t3 - t4 - 1) * xo__k + 2 * (t4 + 1) * t9 * xo__retrograde * xo__h) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t5   = sin(xo__L);
    real_type t9   = xo__h * xo__h;
    real_type t11  = xo__k * xo__k;
    real_type t18  = t1 * t1;
    real_type t19  = xo__f * xo__f;
    real_type t21  = xo__g * xo__g;
    real_type t31  = pow(t9 + t11 + 1, 2);
    real_type result__ = -2 / t31 / (2 * xo__f * xo__g * t1 * t5 + 2 * t1 * xo__f + t19 * t18 - t21 * t18 + 2 * t5 * xo__g + t21 + 1) * (2 * t5 * xo__k * xo__retrograde * xo__h - t11 * t1 + t9 * t1 + t1) * xo__h * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 - 1;
    real_type t4   = t3 * xo__retrograde;
    real_type t5   = cos(xo__L);
    real_type t6   = t5 * t5;
    real_type t10  = sin(xo__L);
    real_type t20  = t10 * xo__g;
    real_type t27  = xo__f * xo__f;
    real_type t29  = xo__g * xo__g;
    real_type t37  = t29 * xo__g;
    real_type t41  = 3 * t29;
    real_type result__ = 1.0 / (t6 * t5 * (t27 * xo__f - 3 * t29 * xo__f) + t6 * (t10 * (3 * xo__g * t27 - t37) + 3 * t27 - t41) + 3 * t5 * (t29 + 2 * t20 + 1) * xo__f + t10 * (t37 + 3 * xo__g) + t41 + 1) / (t1 + t2 + 1) * (2 * t6 * t4 + t5 * (4 * t10 * xo__k * xo__h + xo__retrograde * t3 * xo__f + 4 * xo__g * xo__h * xo__k) - (t20 + 1) * t4) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_2_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t12  = t1 * t1;
    real_type t13  = xo__f * xo__f;
    real_type t15  = xo__g * xo__g;
    real_type result__ = 1.0 / (t3 + t4 + 1) / (2 * xo__f * xo__g * t1 * t7 + 2 * t1 * xo__f + t13 * t12 - t15 * t12 + 2 * t7 * xo__g + t15 + 1) * t7 * (t3 - t4 - 1) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_2_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t8   = cos(xo__L);
    real_type t13  = xo__f * t8;
    real_type t18  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t21  = t8 * t8;
    real_type result__ = 1.0 / (t3 + t4 + 1) / (t1 * (2 * xo__g * t13 + 2 * xo__g) + t21 * (t18 - t19) + 2 * t13 + t19 + 1) * (t1 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t8) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t9   = cos(xo__L);
    real_type t17  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t23  = t9 * t9;
    real_type t28  = t19 * xo__g;
    real_type t32  = 3 * t19;
    real_type result__ = -2 / (t23 * t9 * (t17 * xo__f - 3 * t19 * xo__f) + t23 * (t1 * (3 * xo__g * t17 - t28) + 3 * t17 - t32) + 3 * t9 * (2 * t1 * xo__g + t19 + 1) * xo__f + t1 * (t28 + 3 * xo__g) + t32 + 1) / (t4 + t5 + 1) * (t1 * (t4 - t5 - 1) * xo__retrograde - 2 * xo__k * xo__h * t9) * t2 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_3_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t15  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t18  = t7 * t7;
    real_type t31  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t31 / (t18 * (t15 - t16) + t7 * (2 * t1 * xo__g * xo__f + 2 * xo__f) + t16 + 2 * t1 * xo__g + 1) * (t7 * (t3 - t4 - 1) * xo__k + 2 * (t4 + 1) * t1 * xo__retrograde * xo__h) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_3_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t8   = cos(xo__L);
    real_type t9   = xo__h * xo__h;
    real_type t11  = xo__k * xo__k;
    real_type t18  = t8 * t8;
    real_type t19  = xo__f * xo__f;
    real_type t21  = xo__g * xo__g;
    real_type t31  = pow(t9 + t11 + 1, 2);
    real_type result__ = -2 / t31 / (2 * xo__f * xo__g * t8 * t1 + 2 * t1 * xo__g + t19 * t18 - t21 * t18 + 2 * t8 * xo__f + t21 + 1) * (2 * t1 * xo__k * xo__retrograde * xo__h - t11 * t8 + t9 * t8 + t8) * xo__h * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_3_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_3_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t8   = t6 - t7 - 1;
    real_type t10  = sin(xo__L);
    real_type t27  = xo__f * xo__f;
    real_type t29  = xo__g * xo__g;
    real_type t37  = t29 * xo__g;
    real_type t41  = 3 * t29;
    real_type result__ = 2 / (t2 * t1 * (t27 * xo__f - 3 * t29 * xo__f) + t2 * (t10 * (3 * xo__g * t27 - t37) + 3 * t27 - t41) + 3 * t1 * (2 * t10 * xo__g + t29 + 1) * xo__f + t10 * (t37 + 3 * xo__g) + t41 + 1) / (t6 + t7 + 1) * (-2 * xo__k * xo__h * t2 + t1 * (t10 * t8 * xo__retrograde - xo__f * xo__h * xo__k) + t10 * (xo__retrograde * t8 * xo__f + xo__g * xo__h * xo__k) + xo__h * xo__k) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_3_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_3_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t12  = t7 * t7;
    real_type t13  = xo__f * xo__f;
    real_type t15  = xo__g * xo__g;
    real_type result__ = 1.0 / (t4 + t5 + 1) / (2 * xo__f * xo__g * t7 * t1 + 2 * t1 * xo__g + t13 * t12 - t15 * t12 + 2 * t7 * xo__f + t15 + 1) * (t4 - t5 - 1) * t2 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_3_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t20  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t20 / (t5 * xo__f + t8 * xo__g + 1) * (t5 * (t1 - t2 - 1) * xo__k + 2 * (t2 + 1) * t8 * xo__retrograde * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t11  = cos(xo__L);
    real_type t23  = t1 + t2 + 1;
    real_type t24  = t23 * t23;
    real_type result__ = 4 / t24 / t23 / (t11 * xo__f + t7 * xo__g + 1) * (3 * t7 * (t2 + 1) * xo__retrograde * (t1 - t2 / 3 - 1.0 / 3.0) + (t1 - 3 * t2 - 3) * xo__k * xo__h * t11) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_4_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = t1 * t1;
    real_type t3   = xo__k * xo__k;
    real_type t6   = t3 * t3;
    real_type t8   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    real_type result__ = -2 / t24 / t23 / (t11 * xo__g + t8 * xo__f + 1) * (t8 * (-6 * t3 * t1 + t2 + t6 - 1) + 4 * (t1 - t3 - 1) * t11 * xo__k * xo__retrograde * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_4_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_4_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = cos(xo__L);
    real_type t3   = xo__k * xo__k;
    real_type t7   = xo__h * xo__h;
    real_type t10  = sin(xo__L);
    real_type t16  = xo__f * xo__h;
    real_type t26  = xo__f * xo__f;
    real_type t27  = xo__g * xo__g;
    real_type t29  = t2 * t2;
    real_type t41  = pow(t7 + t3 + 1, 2);
    real_type result__ = -4 / t41 / (t29 * (t26 - t27) + t2 * (2 * t10 * xo__g * xo__f + 2 * xo__f) + t27 + 2 * t10 * xo__g + 1) * ((t3 + 1) * t2 * xo__retrograde * xo__h - t10 * (t7 - t3 - 1) * xo__k / 2 + t3 * xo__k * xo__g / 2 + xo__retrograde * t3 * t16 + xo__k * (-t7 / 2 + 1.0 / 2.0) * xo__g + xo__retrograde * t16) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_4_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_4_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sin(xo__L);
    real_type t4   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t12  = xo__h * xo__h;
    real_type t14  = pow(t12 + t4 + 1, 2);
    real_type result__ = -4 / t14 / (t2 * xo__g + t6 * xo__f + 1) * (t4 + 1) * t2 * xo__h * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_4_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type result__ = 2 / t19 / (t4 * xo__f + t7 * xo__g + 1) * xo__h * (t4 * (t1 - t2 + 1) + 2 * t7 * xo__k * xo__retrograde * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t8   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t23  = t1 + t4 + 1;
    real_type t24  = t23 * t23;
    real_type result__ = 4 / t24 / t23 / (t11 * xo__g + t8 * xo__f + 1) * xo__h * xo__p * (t8 * (-3 * xo__k * t1 + t4 * xo__k - 3 * xo__k) + (t1 - 3 * t4 + 1) * t11 * xo__retrograde * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_5_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_5_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = cos(xo__L);
    real_type t4   = xo__k * xo__retrograde;
    real_type t10  = sin(xo__L);
    real_type t11  = xo__h * xo__h;
    real_type t13  = xo__k * xo__k;
    real_type t19  = pow(t11 + t13 + 1, 2);
    real_type t26  = t2 * t2;
    real_type t27  = xo__f * xo__f;
    real_type t29  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t2 * t10 + 2 * t10 * xo__g + 2 * t2 * xo__f + t27 * t26 - t29 * t26 + t29 + 1) / t19 * (-2 * t4 * xo__h * t2 - 2 * t4 * xo__f * xo__h + t11 * t10 - t13 * t10 + t11 * xo__g - t13 * xo__g + t10 + xo__g) * xo__p * xo__h;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_5_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_5_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t4   = sin(xo__L);
    real_type t5   = cos(xo__L);
    real_type t11  = xo__k * xo__k;
    real_type t13  = pow(t1 + t11 + 1, 2);
    real_type result__ = 4 / t13 / (t4 * xo__g + t5 * xo__f + 1) * t4 * xo__k * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_5_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t18  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t21  = t5 * t5;
    real_type result__ = -1.0 / (t1 + t2 + 1) / (t21 * (t18 - t19) + t5 * (2 * t8 * xo__g * xo__f + 2 * xo__f) + t19 + 2 * t8 * xo__g + 1) * xo__p * (t5 * t3 * xo__retrograde + xo__retrograde * t3 * xo__f + 2 * t8 * xo__k * xo__h + 2 * xo__g * xo__h * xo__k);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_6_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 - 1;
    real_type t6   = xo__g * t3 * xo__retrograde / 2;
    real_type t8   = xo__f * xo__h * xo__k;
    real_type t10  = cos(xo__L);
    real_type t11  = t10 * t10;
    real_type t19  = sin(xo__L);
    real_type t21  = xo__g * xo__g;
    real_type t28  = xo__h * xo__k;
    real_type t34  = xo__f * xo__f;
    real_type t53  = t21 * xo__g;
    real_type t57  = 3 * t21;
    real_type result__ = -2 / (t11 * t10 * (-3 * t21 * xo__f + t34 * xo__f) + t11 * (t19 * (3 * xo__g * t34 - t53) + 3 * t34 - t57) + 3 * t10 * (2 * t19 * xo__g + t21 + 1) * xo__f + t19 * (t53 + 3 * xo__g) + t57 + 1) / (t1 + t2 + 1) * (t11 * (-t6 - t8) + t10 * (t19 * (-xo__g * xo__h * xo__k + xo__retrograde * t3 * xo__f / 2) - 2 * xo__k * xo__h * t21 - xo__g * t3 * xo__f * xo__retrograde + t28) + t19 * (2 * t28 * xo__f * xo__g + xo__retrograde * (t34 - 1.0 / 2.0) * t3) - t6 + 2 * t8) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_6_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_6_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t15  = t7 * t7;
    real_type t16  = xo__f * xo__f;
    real_type t18  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t7 * t10 + 2 * t10 * xo__g + t16 * t15 - t18 * t15 + 2 * t7 * xo__f + t18 + 1) * (t7 + xo__f) * (t1 - t2 - 1) / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_6_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t6   = cos(xo__L);
    real_type result__ = -1.0 / (t1 + t2 + 1) / (t5 * xo__g + t6 * xo__f + 1) * t5 * (t1 - t2 - 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_position_D_7_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_position_D_7_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t12  = xo__h * xo__h;
    real_type t13  = xo__k * xo__k;
    real_type result__ = 2 / (t12 + t13 + 1) / (t1 * xo__f + t4 * xo__g + 1) * (-xo__retrograde * xo__k * t1 + t4 * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t13  = xo__h * xo__h;
    real_type t14  = xo__k * xo__k;
    real_type result__ = 1.0 / (t13 + t14 + 1) / (t1 * xo__f + t4 * xo__g + 1) * (-2 * xo__retrograde * xo__k * t1 + 2 * t4 * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t16  = t5 * t5;
    real_type t17  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t5 * t8 + t17 * t16 - t19 * t16 + 2 * t5 * xo__f + 2 * t8 * xo__g + t19 + 1) * t5 * (-xo__retrograde * xo__k * t5 + t8 * xo__h) / (t1 + t2 + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t16  = t5 * t5;
    real_type t17  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t5 * t8 + t17 * t16 - t19 * t16 + 2 * t5 * xo__f + 2 * t8 * xo__g + t19 + 1) * t8 * (-xo__retrograde * xo__k * t5 + t8 * xo__h) / (t1 + t2 + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type result__ = 1.0 / t19 / (t5 * xo__g + t7 * xo__f + 1) * (t5 * (-2 * t1 + 2 * t2 + 2) + 4 * xo__k * xo__retrograde * xo__h * t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t9   = sin(xo__L);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type result__ = 1.0 / t19 / (t5 * xo__f + t9 * xo__g + 1) * (-2 * t5 * (t1 - t2 + 1) * xo__retrograde - 4 * t9 * xo__k * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sin(xo__L);
    real_type t6   = cos(xo__L);
    real_type t11  = xo__h * xo__h;
    real_type t12  = xo__k * xo__k;
    real_type t20  = t6 * t6;
    real_type t21  = xo__f * xo__f;
    real_type t23  = xo__g * xo__g;
    real_type result__ = 1.0 / (2 * xo__f * xo__g * t6 * t2 + 2 * t2 * xo__g + t21 * t20 - t23 * t20 + 2 * t6 * xo__f + t23 + 1) / (t11 + t12 + 1) * (2 * t2 * xo__k * xo__retrograde + 2 * xo__g * xo__k * xo__retrograde + 2 * t6 * xo__h + 2 * xo__f * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_1_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type result__ = -2 / (t8 + t9 + 1) / (t1 * xo__f + t4 * xo__g + 1) * t1 * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_1_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t9   = sin(xo__L);
    real_type t17  = t6 * t6;
    real_type t18  = xo__f * xo__f;
    real_type t20  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t6 * t9 + t18 * t17 - t20 * t17 + 2 * t6 * xo__f + 2 * t9 * xo__g + t20 + 1) * t6 * (-xo__retrograde * xo__k * t6 + t9 * xo__h) / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t8   = t1 * t1;
    real_type t9   = xo__h * xo__h;
    real_type t10  = xo__k * xo__k;
    real_type t14  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t24  = t16 * xo__g;
    real_type t28  = 3 * t16;
    real_type result__ = 4 / (t8 * t1 * (t14 * xo__f - 3 * t16 * xo__f) + t8 * (t4 * (3 * xo__g * t14 - t24) + 3 * t14 - t28) + 3 * t1 * (2 * t4 * xo__g + t16 + 1) * xo__f + t4 * (t24 + 3 * xo__g) + t28 + 1) / (t9 + t10 + 1) * t8 * (-xo__retrograde * xo__k * t1 + t4 * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = cos(xo__L);
    real_type t6   = t2 * t2;
    real_type t10  = xo__h * xo__h;
    real_type t11  = xo__k * xo__k;
    real_type t15  = xo__f * xo__f;
    real_type t17  = xo__g * xo__g;
    real_type t25  = t17 * xo__g;
    real_type t29  = 3 * t17;
    real_type result__ = -4 / (t6 * t2 * (t15 * xo__f - 3 * t17 * xo__f) + t6 * (t1 * (3 * xo__g * t15 - t25) + 3 * t15 - t29) + 3 * t2 * (2 * t1 * xo__g + t17 + 1) * xo__f + t1 * (t25 + 3 * xo__g) + t29 + 1) / (t10 + t11 + 1) * t2 * (xo__k * xo__retrograde * t2 * t1 + xo__h * t6 - xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = t1 * t1;
    real_type t29  = pow(t6 + t7 + 1, 2);
    real_type result__ = 2 / t29 / (t16 * (t13 - t14) + t1 * (2 * t9 * xo__g * xo__f + 2 * xo__f) + t14 + 2 * t9 * xo__g + 1) * t1 * (-2 * xo__k * xo__retrograde * xo__h * t1 + t9 * (t6 - t7 - 1)) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t9   = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = t1 * t1;
    real_type t29  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t29 / (t16 * (t13 - t14) + t1 * (2 * t9 * xo__g * xo__f + 2 * xo__f) + t14 + 2 * t9 * xo__g + 1) * (t1 * (t3 - t4 + 1) * xo__retrograde + 2 * t9 * xo__k * xo__h) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t9   = sin(xo__L);
    real_type t19  = xo__h * xo__h;
    real_type t20  = xo__k * xo__k;
    real_type t23  = xo__f * xo__f;
    real_type t25  = xo__g * xo__g;
    real_type t33  = t25 * xo__g;
    real_type t37  = 3 * t25;
    real_type result__ = -2 / (t2 * t1 * (t23 * xo__f - 3 * t25 * xo__f) + t2 * (t9 * (3 * xo__g * t23 - t33) + 3 * t23 - t37) + 3 * t1 * (2 * t9 * xo__g + t25 + 1) * xo__f + t9 * (t33 + 3 * xo__g) + t37 + 1) / (t19 + t20 + 1) * (2 * xo__h * t2 + t1 * (2 * t9 * xo__k * xo__retrograde + 2 * xo__g * xo__k * xo__retrograde + xo__f * xo__h) - t9 * xo__h * xo__g - xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_2_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t7   = t6 * t6;
    real_type t9   = sin(xo__L);
    real_type t14  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type result__ = 2 / (2 * xo__f * xo__g * t6 * t9 + t14 * t7 - t16 * t7 + 2 * t6 * xo__f + 2 * t9 * xo__g + t16 + 1) * t7 * xo__k / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_2_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t9   = sin(xo__L);
    real_type t17  = t6 * t6;
    real_type t18  = xo__f * xo__f;
    real_type t20  = xo__g * xo__g;
    real_type result__ = -2 / (2 * xo__f * xo__g * t6 * t9 + t18 * t17 - t20 * t17 + 2 * t6 * xo__f + 2 * t9 * xo__g + t20 + 1) * t9 * (-xo__retrograde * xo__k * t6 + t9 * xo__h) / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = cos(xo__L);
    real_type t9   = xo__h * xo__h;
    real_type t10  = xo__k * xo__k;
    real_type t14  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t20  = t4 * t4;
    real_type t25  = t16 * xo__g;
    real_type t29  = 3 * t16;
    real_type result__ = 4 / (t20 * t4 * (t14 * xo__f - 3 * t16 * xo__f) + t20 * (t1 * (3 * xo__g * t14 - t25) + 3 * t14 - t29) + 3 * t4 * (2 * t1 * xo__g + t16 + 1) * xo__f + t1 * (t25 + 3 * xo__g) + t29 + 1) / (t9 + t10 + 1) * (-xo__retrograde * xo__k * t4 + t1 * xo__h) * t2 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_3_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = cos(xo__L);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type t13  = xo__f * t3;
    real_type t18  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t21  = t3 * t3;
    real_type t28  = pow(t8 + t9 + 1, 2);
    real_type result__ = 2 / t28 / (t1 * (2 * xo__g * t13 + 2 * xo__g) + t21 * (t18 - t19) + 2 * t13 + t19 + 1) * (-2 * xo__k * xo__retrograde * xo__h * t3 + t1 * (t8 - t9 - 1)) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_3_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = t7 * t7;
    real_type t29  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t29 / (t16 * (t13 - t14) + t7 * (2 * t1 * xo__g * xo__f + 2 * xo__f) + t14 + 2 * t1 * xo__g + 1) * (t7 * (t3 - t4 + 1) * xo__retrograde + 2 * t1 * xo__k * xo__h) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_3_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_3_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = t1 * xo__g;
    real_type t3   = xo__k * xo__retrograde;
    real_type t5   = cos(xo__L);
    real_type t6   = t5 * t5;
    real_type t20  = xo__h * xo__h;
    real_type t21  = xo__k * xo__k;
    real_type t24  = xo__f * xo__f;
    real_type t26  = xo__g * xo__g;
    real_type t34  = t26 * xo__g;
    real_type t38  = 3 * t26;
    real_type result__ = -2 / (t6 * t5 * (t24 * xo__f - 3 * t26 * xo__f) + t6 * (t1 * (3 * xo__g * t24 - t34) + 3 * t24 - t38) + 3 * t5 * (t26 + 2 * t2 + 1) * xo__f + t1 * (t34 + 3 * xo__g) + t38 + 1) / (t20 + t21 + 1) * xo__p * (2 * xo__h * t5 * t1 + 2 * xo__h * xo__f * t1 - t3 * xo__f * t5 - 2 * xo__retrograde * xo__k * t6 + t3 * t2 + t3);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_3_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_3_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t9   = t8 * t7;
    real_type t13  = t7 * t7;
    real_type t14  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type result__ = 2 / (2 * xo__f * xo__g * t9 + t14 * t13 - t16 * t13 + 2 * t7 * xo__f + 2 * t8 * xo__g + t16 + 1) * t9 * xo__k / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_3_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = sin(xo__L);
    real_type t18  = pow(t6 + t7 + 1, 2);
    real_type result__ = -2 / t18 / (t1 * xo__f + t9 * xo__g + 1) * (-2 * xo__k * xo__retrograde * xo__h * t1 + t9 * (t6 - t7 - 1)) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t21  = t1 + t2 + 1;
    real_type t22  = t21 * t21;
    real_type result__ = 4 / t22 / t21 / (t10 * xo__g + t6 * xo__f + 1) * (-3 * t6 * xo__k * xo__retrograde * (t1 - t2 / 3 - 1.0 / 3.0) + (t1 - 3 * t2 - 3) * t10 * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_4_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t21  = t2 + t3 + 1;
    real_type t22  = t21 * t21;
    real_type result__ = 4 / t22 / t21 / (t11 * xo__g + t6 * xo__f + 1) * (t6 * (t2 - 3 * t3 + 1) * xo__h * xo__retrograde + 3 * xo__k * t11 * (t2 - t3 / 3 - 1.0 / 3.0)) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_4_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_4_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t3   = t1 - t2 - 1;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t18  = xo__f * xo__f;
    real_type t19  = xo__g * xo__g;
    real_type t21  = t4 * t4;
    real_type t33  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t33 / (t21 * (t18 - t19) + t4 * (2 * t7 * xo__g * xo__f + 2 * xo__f) + t19 + 2 * t7 * xo__g + 1) * (2 * t7 * xo__k * xo__retrograde * xo__h + 2 * xo__g * xo__h * xo__k * xo__retrograde + t4 * t3 + t3 * xo__f) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_4_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_4_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t5   = sin(xo__L);
    real_type t10  = xo__h * xo__h;
    real_type t11  = xo__k * xo__k;
    real_type t13  = pow(t10 + t11 + 1, 2);
    real_type result__ = 4 / t13 / (t1 * xo__f + t5 * xo__g + 1) * xo__k * xo__h * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_4_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t8   = sin(xo__L);
    real_type t18  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t18 / (t5 * xo__f + t8 * xo__g + 1) * (t5 * (t1 - t2 + 1) * xo__retrograde + 2 * t8 * xo__k * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t21  = t1 + t2 + 1;
    real_type t22  = t21 * t21;
    real_type result__ = -4 / t22 / t21 / (t10 * xo__g + t6 * xo__f + 1) * xo__p * (-3 * t6 * xo__k * (t1 - t2 / 3 + 1) * xo__retrograde + (t1 - 3 * t2 + 1) * t10 * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_5_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_5_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t7   = (t4 - t5 + 1) * xo__retrograde;
    real_type t8   = sin(xo__L);
    real_type t17  = xo__f * xo__f;
    real_type t18  = xo__g * xo__g;
    real_type t20  = t1 * t1;
    real_type t32  = pow(t4 + t5 + 1, 2);
    real_type result__ = -4 / t32 / (t20 * (t17 - t18) + t1 * (2 * t8 * xo__g * xo__f + 2 * xo__f) + t18 + 2 * t8 * xo__g + 1) * (xo__k * xo__h * t1 - t8 * t7 / 2 - xo__g * t7 / 2 + xo__f * xo__h * xo__k) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_5_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_5_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t13  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t13 / (t5 * xo__f + xo__g * t7 + 1) * t5 * (t1 - t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_5_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sin(xo__L);
    real_type t6   = cos(xo__L);
    real_type t11  = xo__h * xo__h;
    real_type t12  = xo__k * xo__k;
    real_type t19  = t6 * t6;
    real_type t20  = xo__f * xo__f;
    real_type t22  = xo__g * xo__g;
    real_type result__ = 2 / (2 * xo__f * xo__g * t6 * t2 + t20 * t19 - t22 * t19 + 2 * t2 * xo__g + 2 * t6 * xo__f + t22 + 1) / (t11 + t12 + 1) * (t2 * xo__k * xo__retrograde + xo__g * xo__k * xo__retrograde + t6 * xo__h + xo__f * xo__h) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_6_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__f * xo__k * xo__retrograde;
    real_type t3   = xo__g * xo__h;
    real_type t6   = cos(xo__L);
    real_type t7   = t6 * t6;
    real_type t14  = sin(xo__L);
    real_type t16  = xo__g * xo__g;
    real_type t19  = xo__f * xo__g;
    real_type t21  = xo__k * xo__retrograde;
    real_type t26  = xo__f * xo__f;
    real_type t34  = xo__h * xo__h;
    real_type t35  = xo__k * xo__k;
    real_type t46  = t16 * xo__g;
    real_type t50  = 3 * t16;
    real_type result__ = 4 / (t7 * t6 * (-3 * t16 * xo__f + t26 * xo__f) + t7 * (t14 * (3 * xo__g * t26 - t46) + 3 * t26 - t50) + 3 * t6 * (2 * t14 * xo__g + t16 + 1) * xo__f + t14 * (t46 + 3 * xo__g) + t50 + 1) / (t34 + t35 + 1) * (t7 * (-t2 / 2 - t3 / 2) + t6 * (t14 * (-xo__g * xo__k * xo__retrograde / 2 + xo__f * xo__h / 2) - xo__retrograde * xo__k * t16 - xo__h * t19 + t21 / 2) + t14 * (t21 * t19 + xo__h * t26 - xo__h / 2) + t2 - t3 / 2) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_6_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_6_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = sin(xo__L);
    real_type t9   = cos(xo__L);
    real_type t14  = t9 * t9;
    real_type t15  = xo__f * xo__f;
    real_type t17  = xo__g * xo__g;
    real_type result__ = 2 / (2 * xo__f * xo__g * t9 * t6 + t15 * t14 - t17 * t14 + 2 * t6 * xo__g + 2 * t9 * xo__f + t17 + 1) * (t6 + xo__g) * xo__k / (t1 + t2 + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_6_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t9   = xo__h * xo__h;
    real_type t10  = xo__k * xo__k;
    real_type result__ = -2 / (t9 + t10 + 1) / (t2 * xo__f + t4 * xo__g + 1) * t2 * xo__p * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_position_D_7_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_position_D_7_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = sin(xo__L);
    real_type t12  = xo__k * xo__retrograde;
    real_type t15  = cos(xo__L);
    real_type result__ = -1.0 / (t6 + t7 + 1) * (t9 * (t6 - t7 + 1) - 2 * t12 * xo__f * xo__h - 2 * t12 * xo__h * t15 + t6 * xo__g - xo__g * t7 + xo__g) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = sin(xo__L);
    real_type t7   = xo__k * xo__retrograde;
    real_type t10  = cos(xo__L);
    real_type t18  = sqrt(ModelPars[iM_muS]);
    real_type t20  = sqrt(xo__p);
    real_type result__ = 1.0 / (2 * t1 + 2 * t2 + 2) / t20 / xo__p * t18 * (t4 * (t1 - t2 + 1) - 2 * t7 * xo__f * xo__h - 2 * t7 * xo__h * t10 + t1 * xo__g - t2 * xo__g + xo__g);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t9   = xo__k * xo__retrograde;
    real_type t22  = sqrt(ModelPars[iM_muS]);
    real_type t24  = xo__p * xo__p;
    real_type t25  = sqrt(xo__p);
    real_type result__ = 1.0 / (4 * t1 + 4 * t2 + 4) / t25 / t24 * t22 * (t5 * (-3 * t1 + 3 * t2 - 3) + 6 * t9 * xo__h * t7 + 6 * t9 * xo__f * xo__h - 3 * t1 * xo__g + 3 * t2 * xo__g - 3 * xo__g);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t4   = sqrt(ModelPars[iM_muS]);
    real_type t5   = sqrt(xo__p);
    real_type t9   = xo__h * xo__h;
    real_type t10  = xo__k * xo__k;
    real_type result__ = -1.0 / (t9 + t10 + 1) / t5 / xo__p * t4 * xo__h * xo__k * xo__retrograde;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sqrt(ModelPars[iM_muS]);
    real_type t7   = sqrt(xo__p);
    real_type result__ = 1.0 / (2 * t1 + 2 * t2 + 2) / t7 / xo__p * t5 * (t1 - t2 + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t9   = t7 - t8 - 1;
    real_type t11  = cos(xo__L);
    real_type t14  = sin(xo__L);
    real_type t25  = pow(t7 + t8 + 1, 2);
    real_type result__ = 1.0 / t25 * (t11 * t9 * xo__retrograde + 2 * t14 * xo__k * xo__h + xo__retrograde * t9 * xo__f + 2 * xo__g * xo__h * xo__k) / t4 / xo__p * t2 * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t28  = sqrt(ModelPars[iM_muS]);
    real_type t30  = sqrt(xo__p);
    real_type t34  = pow(t2 + t3 + 1, 2);
    real_type result__ = -1.0 / t34 / t30 / xo__p * t28 * (t5 * (t2 - t3 + 1) * xo__h * xo__retrograde + t11 * (2 * xo__k * t2 + 2 * xo__k) + xo__retrograde * t2 * xo__h * xo__f + 2 * xo__k * t2 * xo__g + xo__h * (-xo__retrograde * t3 * xo__f + xo__f * xo__retrograde) + 2 * xo__g * xo__k);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t13  = sqrt(ModelPars[iM_muS]);
    real_type t15  = sqrt(xo__p);
    real_type result__ = 1.0 / (2 * t1 + 2 * t2 + 2) / t15 / xo__p * t13 * (t4 * (t1 - t2 + 1) + 2 * t7 * xo__k * xo__retrograde * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_1_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t5   = cos(xo__L);
    real_type t7   = sqrt(xo__p);
    real_type t11  = xo__h * xo__h;
    real_type t12  = xo__k * xo__k;
    real_type result__ = -1.0 / (t11 + t12 + 1) / t7 / xo__p * (t5 + xo__f) * xo__k * xo__h * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_1_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type result__ = 2 / (t8 + t9 + 1) * xo__retrograde * xo__k * xo__h / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t5   = xo__h * xo__h;
    real_type t6   = xo__k * xo__k;
    real_type t8   = sqrt(xo__p);
    real_type t12  = pow(t5 + t6 + 1, 2);
    real_type result__ = -2 / t12 / t8 * (t5 - t6 - 1) * xo__retrograde * xo__k * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t5   = xo__h * xo__h;
    real_type t6   = xo__k * xo__k;
    real_type t8   = sqrt(xo__p);
    real_type t12  = pow(t5 + t6 + 1, 2);
    real_type result__ = 2 / t12 / t8 * (t5 - t6 + 1) * xo__retrograde * xo__h * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_2_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type result__ = 2 / (t7 + t8 + 1) * xo__k * xo__h / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_2_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type result__ = -1.0 / (t6 + t7 + 1) * (t6 - t7 + 1) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_3_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = xo__k * xo__k;
    real_type t5   = sqrt(xo__p);
    real_type t8   = xo__h * xo__h;
    real_type t10  = pow(t8 + t4 + 1, 2);
    real_type result__ = -4 / t10 / t5 * t4 * xo__h * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_3_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = xo__h * xo__h;
    real_type t6   = sqrt(xo__p);
    real_type t9   = xo__k * xo__k;
    real_type t11  = pow(t4 + t9 + 1, 2);
    real_type result__ = 4 / t11 / t6 * (t4 + 1) * xo__k * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_3_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_3_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_3_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_3_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_3_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t8   = t6 - t7 - 1;
    real_type t10  = cos(xo__L);
    real_type t13  = sin(xo__L);
    real_type t24  = pow(t6 + t7 + 1, 2);
    real_type result__ = -2 / t24 * (t10 * t8 * xo__retrograde + 2 * t13 * xo__k * xo__h + xo__retrograde * t8 * xo__f + 2 * xo__g * xo__h * xo__k) / t4 * t2 * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t11  = cos(xo__L);
    real_type t16  = t8 * xo__k;
    real_type t18  = sin(xo__L);
    real_type t21  = xo__f * xo__h;
    real_type t34  = t7 + t8 + 1;
    real_type t35  = t34 * t34;
    real_type result__ = 4 / t35 / t34 * (t11 * (t7 - 3 * t8 - 3) * xo__retrograde * xo__h + t18 * (3 * xo__k * t7 - t16 - xo__k) - t16 * xo__g - 3 * xo__retrograde * t8 * t21 + xo__k * (3 * t7 * xo__g - xo__g) + (t7 - 3) * xo__retrograde * t21) / t4 * t2 * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_4_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = t6 * t6;
    real_type t8   = xo__k * xo__k;
    real_type t11  = t8 * t8;
    real_type t14  = cos(xo__L);
    real_type t18  = sin(xo__L);
    real_type t42  = t6 + t8 + 1;
    real_type t43  = t42 * t42;
    real_type result__ = -2 / t43 / t42 * (t14 * (-6 * t8 * t6 + t11 + t7 - 1) * xo__retrograde + 4 * t18 * (t6 - t8 + 1) * xo__h * xo__k + xo__retrograde * t7 * xo__f + 4 * xo__k * t6 * xo__h * xo__g - 6 * xo__retrograde * t8 * t6 * xo__f + xo__h * (-4 * t8 * xo__k * xo__g + 4 * xo__g * xo__k) + xo__retrograde * t11 * xo__f - xo__f * xo__retrograde) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_4_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_4_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t9   = cos(xo__L);
    real_type t15  = sqrt(xo__p);
    real_type t19  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t19 / t15 * xo__k * (t7 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t9) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_4_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_4_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t10  = pow(t7 + t8 + 1, 2);
    real_type t14  = cos(xo__L);
    real_type result__ = -2 * (t14 + xo__f) * (t7 - t8 - 1) / t10 / t4 * t2 * xo__k;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_4_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t28  = sqrt(ModelPars[iM_muS]);
    real_type t30  = sqrt(xo__p);
    real_type t33  = pow(t2 + t3 + 1, 2);
    real_type result__ = 2 / t33 / t30 * t28 * (t5 * (t2 - t3 + 1) * xo__h * xo__retrograde + t11 * (2 * xo__k * t2 + 2 * xo__k) + xo__retrograde * t2 * xo__h * xo__f + 2 * xo__k * t2 * xo__g + xo__h * (-xo__retrograde * t3 * xo__f + xo__f * xo__retrograde) + 2 * xo__g * xo__k);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t3   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t14  = cos(xo__L);
    real_type t17  = t1 * t1;
    real_type t37  = sqrt(ModelPars[iM_muS]);
    real_type t39  = sqrt(xo__p);
    real_type t41  = t1 + t3 + 1;
    real_type t42  = t41 * t41;
    real_type result__ = -12 / t42 / t41 / t39 * t37 * (-t7 * (t1 - 3 * t3 + 1) * (t1 + 1) / 3 + t14 * (t1 - t3 / 3 + 1) * xo__retrograde * xo__h * xo__k - t17 * xo__g / 3 + xo__k * xo__retrograde * t1 * xo__h * xo__f + t1 * (t3 - 2.0 / 3.0) * xo__g - xo__h * (t3 - 3) * xo__retrograde * xo__f * xo__k / 3 + (t3 - 1.0 / 3.0) * xo__g);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_5_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_5_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t10  = sin(xo__L);
    real_type t13  = cos(xo__L);
    real_type t20  = pow(t7 + t8 + 1, 2);
    real_type result__ = -2 / t20 * (t10 * (t7 - t8 + 1) * xo__h * xo__retrograde - 2 * (t7 + 1) * xo__k * t13) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_5_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_5_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t14  = cos(xo__L);
    real_type result__ = 2 * (t14 + xo__f) * (t6 - t7 + 1) * xo__h / t9 / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_5_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = cos(xo__L);
    real_type t7   = sin(xo__L);
    real_type t13  = sqrt(ModelPars[iM_muS]);
    real_type t15  = sqrt(xo__p);
    real_type result__ = 1.0 / (t1 + t2 + 1) / t15 * t13 * (t4 * (-t1 + t2 - 1) - 2 * t7 * xo__k * xo__retrograde * xo__h);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_6_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t4   = sin(xo__L);
    real_type t6   = cos(xo__L);
    real_type t13  = sqrt(ModelPars[iM_muS]);
    real_type t15  = sqrt(xo__p);
    real_type result__ = 1.0 / (t1 + t2 + 1) / t15 * t13 * (t4 * (t1 - t2 + 1) - 2 * xo__k * xo__retrograde * xo__h * t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_6_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_6_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sin(xo__L);
    real_type t5   = sqrt(ModelPars[iM_muS]);
    real_type t6   = sqrt(xo__p);
    real_type t9   = xo__h * xo__h;
    real_type t10  = xo__k * xo__k;
    real_type result__ = -2 / (t9 + t10 + 1) / t6 * t5 * t2 * xo__k * xo__h;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_6_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t12  = cos(xo__L);
    real_type result__ = 2 * (t12 + xo__f) * xo__k * xo__h / (t6 + t7 + 1) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::x_velocity_D_7_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_x_velocity_D_7_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t5   = t3 - t4 - 1;
    real_type t7   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t20  = sqrt(xo__p);
    real_type result__ = -2 / (t3 + t4 + 1) / t20 * (t7 * t5 * xo__retrograde / 2 + t11 * xo__k * xo__h + xo__retrograde * t5 * xo__f / 2 + xo__g * xo__h * xo__k) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t9   = t7 - t8 - 1;
    real_type t11  = cos(xo__L);
    real_type t14  = sin(xo__L);
    real_type result__ = 1.0 / (2 * t7 + 2 * t8 + 2) * (t11 * t9 * xo__retrograde + 2 * t14 * xo__k * xo__h + xo__retrograde * t9 * xo__f + 2 * xo__g * xo__h * xo__k) / t3 / xo__p * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__p * xo__p;
    real_type t4   = sqrt(xo__p);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type t10  = t8 - t9 - 1;
    real_type t12  = cos(xo__L);
    real_type t15  = sin(xo__L);
    real_type result__ = -3 / (4 * t8 + 4 * t9 + 4) * (t12 * t10 * xo__retrograde + xo__retrograde * t10 * xo__f + 2 * t15 * xo__k * xo__h + 2 * xo__g * xo__h * xo__k) / t4 / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type result__ = 1.0 / (2 * t7 + 2 * t8 + 2) * (t7 - t8 - 1) * xo__retrograde / t3 / xo__p * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type result__ = 1.0 / (t8 + t9 + 1) / t4 / xo__p * xo__k * xo__h * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t11  = cos(xo__L);
    real_type t18  = xo__f * xo__h;
    real_type t28  = sqrt(xo__p);
    real_type t32  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t32 / t28 / xo__p * (-t7 * (t3 - t4 - 1) * xo__k / 2 + (t4 + 1) * t11 * xo__retrograde * xo__h + t4 * xo__k * xo__g / 2 + xo__retrograde * t4 * t18 + xo__k * (-t3 * xo__g / 2 + xo__g / 2) + xo__retrograde * t18) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t23  = sqrt(ModelPars[iM_muS]);
    real_type t25  = sqrt(xo__p);
    real_type t29  = pow(t1 + t2 + 1, 2);
    real_type result__ = 1.0 / t29 / t25 / xo__p * t23 * (t5 * (t1 - t2 + 1) * xo__h - 2 * xo__k * xo__retrograde * t1 * t7 + t1 * xo__h * xo__g - 2 * t1 * xo__retrograde * xo__f * xo__k + xo__h * (-t2 * xo__g + xo__g));
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t9   = cos(xo__L);
    real_type t15  = sqrt(xo__p);
    real_type result__ = -1.0 / (2 * t3 + 2 * t4 + 2) / t15 / xo__p * (t7 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t9) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_1_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t9   = sqrt(xo__p);
    real_type result__ = 1.0 / (2 * t3 + 2 * t4 + 2) / t9 / xo__p * (t7 + xo__f) * (t3 - t4 - 1) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_1_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t7   = sqrt(xo__p);
    real_type result__ = -1.0 / (t4 + t5 + 1) / t7 * (t4 - t5 - 1) * xo__retrograde * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t5   = xo__k * xo__k;
    real_type t7   = sqrt(xo__p);
    real_type t10  = xo__h * xo__h;
    real_type t12  = pow(t10 + t5 + 1, 2);
    real_type result__ = -4 / t12 / t7 * (t5 + 1) * xo__h * xo__retrograde * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t5   = xo__h * xo__h;
    real_type t6   = sqrt(xo__p);
    real_type t9   = xo__k * xo__k;
    real_type t11  = pow(t5 + t9 + 1, 2);
    real_type result__ = 4 / t11 / t6 * t5 * xo__k * xo__retrograde * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_2_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sqrt(xo__p);
    real_type result__ = -1.0 / (t3 + t4 + 1) / t7 * (t3 - t4 - 1) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_2_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type result__ = -2 / (t7 + t8 + 1) * xo__k * xo__h / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_3_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sqrt(ModelPars[iM_muS]);
    real_type t7   = sqrt(xo__p);
    real_type t11  = pow(t1 + t2 + 1, 2);
    real_type result__ = 2 / t11 / t7 * xo__k * t5 * (t1 - t2 - 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_3_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t10  = pow(t6 + t7 + 1, 2);
    real_type result__ = -2 * xo__h / t10 * (t6 - t7 + 1) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_3_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_3_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_3_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_3_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_3_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t11  = cos(xo__L);
    real_type t18  = xo__f * xo__h;
    real_type t28  = sqrt(xo__p);
    real_type t31  = pow(t3 + t4 + 1, 2);
    real_type result__ = -4 / t31 / t28 * (-t7 * (t3 - t4 - 1) * xo__k / 2 + (t4 + 1) * t11 * xo__retrograde * xo__h + t4 * xo__k * xo__g / 2 + xo__retrograde * t4 * t18 + xo__k * (-t3 * xo__g / 2 + xo__g / 2) + xo__retrograde * t18) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t12  = cos(xo__L);
    real_type t18  = sin(xo__L);
    real_type t22  = t7 * t7;
    real_type t26  = xo__g * xo__h;
    real_type t29  = xo__f * xo__retrograde;
    real_type t40  = t6 + t7 + 1;
    real_type t41  = t40 * t40;
    real_type result__ = 12 / t41 / t40 * (t12 * (t7 + 1) * (t6 - t7 / 3 - 1.0 / 3.0) * xo__retrograde - t18 * (t6 - 3 * t7 - 3) * xo__h * xo__k / 3 - xo__retrograde * t22 * xo__f / 3 + t7 * xo__k * t26 + t7 * (t6 - 2.0 / 3.0) * t29 - xo__k * (t6 - 3) * t26 / 3 + (t6 - 1.0 / 3.0) * t29) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_4_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = t3 * t3;
    real_type t6   = xo__k * xo__k;
    real_type t9   = t6 * t6;
    real_type t12  = sin(xo__L);
    real_type t17  = cos(xo__L);
    real_type t39  = sqrt(xo__p);
    real_type t41  = t3 + t6 + 1;
    real_type t42  = t41 * t41;
    real_type result__ = -8 / t42 / t41 / t39 * (t12 * (-t4 / 4 + 3.0 / 2.0 * t6 * t3 - t9 / 4 + 1.0 / 4.0) + t17 * (t3 - t6 - 1) * xo__retrograde * xo__h * xo__k - t4 * xo__g / 4 + xo__k * xo__retrograde * t3 * xo__h * xo__f + 3.0 / 2.0 * t6 * t3 * xo__g - xo__h * (t6 + 1) * xo__retrograde * xo__f * xo__k - t9 * xo__g / 4 + xo__g / 4) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_4_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_4_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t10  = cos(xo__L);
    real_type t14  = sin(xo__L);
    real_type t20  = pow(t6 + t7 + 1, 2);
    real_type result__ = 4 / t20 * (t10 * (t6 - t7 - 1) * xo__k / 2 + (t7 + 1) * t14 * xo__retrograde * xo__h) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_4_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_4_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t14  = cos(xo__L);
    real_type result__ = -4 * (t14 + xo__f) * (t7 + 1) * xo__h / t9 / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_4_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = cos(xo__L);
    real_type t6   = xo__k * xo__retrograde;
    real_type t12  = sin(xo__L);
    real_type t13  = xo__h * xo__h;
    real_type t15  = xo__k * xo__k;
    real_type t20  = sqrt(xo__p);
    real_type t24  = pow(t13 + t15 + 1, 2);
    real_type result__ = 2 / t24 / t20 * (2 * t6 * xo__h * t4 + 2 * t6 * xo__f * xo__h - t13 * t12 + t15 * t12 - t13 * xo__g + t15 * xo__g - t12 - xo__g) * xo__h * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t8   = cos(xo__L);
    real_type t16  = sin(xo__L);
    real_type t34  = sqrt(xo__p);
    real_type t37  = t4 + t5 + 1;
    real_type t38  = t37 * t37;
    real_type result__ = 4 / t38 / t37 * xo__h / t34 * (t8 * (t4 - 3 * t5 + 1) * xo__h * xo__retrograde + t16 * (3 * xo__k * t4 - t5 * xo__k + 3 * xo__k) + xo__retrograde * t4 * xo__h * xo__f + 3 * xo__k * t4 * xo__g - 3 * xo__f * xo__h * (t5 - 1.0 / 3.0) * xo__retrograde - (t5 - 3) * xo__k * xo__g) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_5_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_5_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = cos(xo__L);
    real_type t9   = sin(xo__L);
    real_type t15  = sqrt(ModelPars[iM_muS]);
    real_type t17  = sqrt(xo__p);
    real_type t20  = pow(t1 + t2 + 1, 2);
    real_type result__ = 1.0 / t20 / t17 * t15 * (-2 * t5 * (t1 - t2 + 1) * xo__h - 4 * t9 * xo__k * xo__retrograde * t1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_5_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_5_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t5   = sqrt(xo__p);
    real_type t8   = xo__k * xo__k;
    real_type t10  = pow(t3 + t8 + 1, 2);
    real_type t13  = cos(xo__L);
    real_type result__ = 4 * (t13 + xo__f) * xo__k / t10 / t5 * t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_5_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t9   = cos(xo__L);
    real_type t15  = sqrt(xo__p);
    real_type result__ = 1.0 / (t3 + t4 + 1) / t15 * (t7 * (t3 - t4 - 1) * xo__retrograde - 2 * xo__k * xo__h * t9) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_6_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t15  = sqrt(xo__p);
    real_type result__ = 1.0 / (t3 + t4 + 1) / t15 * (t7 * (t3 - t4 - 1) * xo__retrograde + 2 * t10 * xo__k * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_6_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_6_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t8   = sqrt(xo__p);
    real_type result__ = 1.0 / (t3 + t4 + 1) / t8 * t7 * (t3 - t4 - 1) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_6_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t9   = sqrt(xo__p);
    real_type result__ = -1.0 / (t3 + t4 + 1) / t9 * (t7 + xo__f) * (t3 - t4 - 1) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::y_velocity_D_7_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_y_velocity_D_7_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sin(xo__L);
    real_type t8   = cos(xo__L);
    real_type t13  = sqrt(xo__p);
    real_type t15  = xo__h * xo__h;
    real_type t16  = xo__k * xo__k;
    real_type result__ = 2 / (t15 + t16 + 1) / t13 * (t4 * xo__k * xo__retrograde + xo__g * xo__k * xo__retrograde + t8 * xo__h + xo__f * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sin(xo__L);
    real_type t8   = cos(xo__L);
    real_type t13  = sqrt(xo__p);
    real_type t16  = xo__h * xo__h;
    real_type t17  = xo__k * xo__k;
    real_type result__ = -1.0 / (t16 + t17 + 1) / t13 / xo__p * (t4 * xo__k * xo__retrograde + xo__g * xo__k * xo__retrograde + t8 * xo__h + xo__f * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sin(xo__L);
    real_type t8   = cos(xo__L);
    real_type t13  = xo__p * xo__p;
    real_type t14  = sqrt(xo__p);
    real_type t17  = xo__h * xo__h;
    real_type t18  = xo__k * xo__k;
    real_type result__ = 3 / (2 * t17 + 2 * t18 + 2) / t14 / t13 * (t4 * xo__k * xo__retrograde + xo__g * xo__k * xo__retrograde + t8 * xo__h + xo__f * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_1( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type result__ = -1.0 / (t7 + t8 + 1) / t4 / xo__p * xo__h * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type result__ = -1.0 / (t8 + t9 + 1) / t4 / xo__p * xo__retrograde * xo__k * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t8   = sin(xo__L);
    real_type t12  = xo__h * xo__h;
    real_type t13  = xo__k * xo__k;
    real_type t15  = cos(xo__L);
    real_type t25  = pow(t12 + t13 + 1, 2);
    real_type result__ = 1.0 / t25 * (2 * t8 * xo__k * xo__retrograde * xo__h + t15 * (t12 - t13 - 1) + 2 * xo__g * xo__h * xo__k * xo__retrograde + t12 * xo__f - t13 * xo__f - xo__f) / t3 / xo__p * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = cos(xo__L);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = (t6 - t7 + 1) * xo__retrograde;
    real_type t10  = sin(xo__L);
    real_type t19  = sqrt(xo__p);
    real_type t23  = pow(t6 + t7 + 1, 2);
    real_type result__ = 2 / t23 / t19 / xo__p * (xo__k * xo__h * t3 - t10 * t9 / 2 - xo__g * t9 / 2 + xo__f * xo__h * xo__k) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = cos(xo__L);
    real_type t6   = sin(xo__L);
    real_type t10  = sqrt(xo__p);
    real_type t13  = xo__h * xo__h;
    real_type t14  = xo__k * xo__k;
    real_type result__ = -1.0 / (t13 + t14 + 1) / t10 / xo__p * (xo__retrograde * xo__k * t3 - t6 * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_1_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t12  = sin(xo__L);
    real_type result__ = -(t12 + xo__g) * xo__k / (t7 + t8 + 1) / t3 / xo__p * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_1_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type result__ = 2 / (t6 + t7 + 1) * xo__h / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2_2( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sqrt(ModelPars[iM_muS]);
    real_type t7   = sqrt(xo__p);
    real_type t10  = pow(t1 + t2 + 1, 2);
    real_type result__ = -2 / t10 / t7 * t5 * (t1 - t2 - 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type result__ = -4 * xo__k / t9 * xo__h / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_2_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_2_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type result__ = 2 / (t7 + t8 + 1) / t4 * xo__k * xo__retrograde * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_3_3( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t5   = sqrt(xo__p);
    real_type t7   = xo__h * xo__h;
    real_type t8   = xo__k * xo__k;
    real_type t10  = pow(t7 + t8 + 1, 2);
    real_type result__ = -4 * xo__h / t10 / t5 * xo__k * xo__retrograde * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_3_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = xo__h * xo__h;
    real_type t5   = xo__k * xo__k;
    real_type t7   = sqrt(xo__p);
    real_type t11  = pow(t4 + t5 + 1, 2);
    real_type result__ = 2 / t11 / t7 * (t4 - t5 + 1) * t2 * xo__retrograde;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_3_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_3_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_3_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_3_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type result__ = 2 / (t6 + t7 + 1) * xo__k / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_3_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t7   = sin(xo__L);
    real_type t11  = xo__h * xo__h;
    real_type t12  = xo__k * xo__k;
    real_type t14  = cos(xo__L);
    real_type t24  = pow(t11 + t12 + 1, 2);
    real_type result__ = -2 / t24 * (2 * t7 * xo__k * xo__retrograde * xo__h + t14 * (t11 - t12 - 1) + 2 * xo__g * xo__h * xo__k * xo__retrograde + t11 * xo__f - t12 * xo__f - xo__f) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t6   = cos(xo__L);
    real_type t8   = xo__k * xo__retrograde;
    real_type t11  = sin(xo__L);
    real_type t30  = sqrt(ModelPars[iM_muS]);
    real_type t32  = sqrt(xo__p);
    real_type t34  = t1 + t2 + 1;
    real_type t35  = t34 * t34;
    real_type result__ = 4 / t35 / t34 / t32 * t30 * (t6 * (t1 - 3 * t2 - 3) * xo__h + 3 * t11 * (t1 - t2 / 3 - 1.0 / 3.0) * t8 + t1 * xo__h * xo__f + 3 * t8 * t1 * xo__g + xo__h * (-3 * t2 * xo__f - 3 * xo__f) - (t2 + 1) * xo__retrograde * xo__g * xo__k);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_4_4( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t8   = cos(xo__L);
    real_type t11  = sin(xo__L);
    real_type t33  = sqrt(xo__p);
    real_type t35  = t3 + t4 + 1;
    real_type t36  = t35 * t35;
    real_type result__ = 12 / t36 / t35 / t33 * (t8 * (t3 - t4 / 3 - 1.0 / 3.0) * xo__k - (t3 - 3 * t4 + 1) * t11 * xo__retrograde * xo__h / 3 - xo__retrograde * t3 * xo__h * xo__g / 3 + xo__k * t3 * xo__f + xo__h * (t4 - 1.0 / 3.0) * xo__retrograde * xo__g - (t4 + 1) * xo__k * xo__f / 3) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_4_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_4_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t1   = xo__h * xo__h;
    real_type t2   = xo__k * xo__k;
    real_type t5   = sin(xo__L);
    real_type t7   = cos(xo__L);
    real_type t14  = sqrt(ModelPars[iM_muS]);
    real_type t16  = sqrt(xo__p);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type result__ = 1.0 / t19 / t16 * t14 * (t5 * (2 * t1 - 2 * t2 - 2) - 4 * xo__k * xo__retrograde * xo__h * t7);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_4_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_4_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t13  = sin(xo__L);
    real_type result__ = -4 * (t13 + xo__g) * xo__k * xo__h / t9 / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_4_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = cos(xo__L);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t9   = (t6 - t7 + 1) * xo__retrograde;
    real_type t10  = sin(xo__L);
    real_type t19  = sqrt(xo__p);
    real_type t22  = pow(t6 + t7 + 1, 2);
    real_type result__ = -4 / t22 / t19 * (xo__k * xo__h * t3 - t10 * t9 / 2 - xo__g * t9 / 2 + xo__f * xo__h * xo__k) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t11  = cos(xo__L);
    real_type t13  = xo__k * xo__retrograde;
    real_type t16  = sin(xo__L);
    real_type t34  = t6 + t7 + 1;
    real_type t35  = t34 * t34;
    real_type result__ = -4 / t35 / t34 * (t11 * (t6 - 3 * t7 + 1) * xo__h + 3 * t16 * (t6 - t7 / 3 + 1) * t13 + t6 * xo__h * xo__f + 3 * t13 * t6 * xo__g + xo__h * (-3 * t7 * xo__f + xo__f) - (t7 - 3) * xo__retrograde * xo__g * xo__k) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_5_5( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_5_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t15  = sqrt(xo__p);
    real_type t18  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t18 / t15 * (t7 * (t3 - t4 + 1) * xo__retrograde + 2 * t10 * xo__k * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_5_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_5_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = xo__h * xo__h;
    real_type t4   = xo__k * xo__k;
    real_type t7   = sin(xo__L);
    real_type t9   = sqrt(xo__p);
    real_type t13  = pow(t3 + t4 + 1, 2);
    real_type result__ = 2 / t13 / t9 * (t7 + xo__g) * (t3 - t4 + 1) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_5_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = cos(xo__L);
    real_type t6   = sin(xo__L);
    real_type t10  = sqrt(xo__p);
    real_type t12  = xo__h * xo__h;
    real_type t13  = xo__k * xo__k;
    real_type result__ = 2 / (t12 + t13 + 1) / t10 * (xo__retrograde * xo__k * t3 - t6 * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_6_6( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = sin(xo__L);
    real_type t6   = cos(xo__L);
    real_type t10  = sqrt(xo__p);
    real_type t12  = xo__h * xo__h;
    real_type t13  = xo__k * xo__k;
    real_type result__ = -2 / (t12 + t13 + 1) / t10 * (t4 * xo__k * xo__retrograde + t6 * xo__h) * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_6_6( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_6_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t4   = cos(xo__L);
    real_type t5   = sqrt(xo__p);
    real_type t8   = xo__h * xo__h;
    real_type t9   = xo__k * xo__k;
    real_type result__ = 2 / (t8 + t9 + 1) / t5 * t4 * xo__k * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_6_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type t2   = sqrt(ModelPars[iM_muS]);
    real_type t3   = sqrt(xo__p);
    real_type t6   = xo__h * xo__h;
    real_type t7   = xo__k * xo__k;
    real_type t11  = sin(xo__L);
    real_type result__ = 2 * (t11 + xo__g) * xo__k / (t6 + t7 + 1) / t3 * t2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::z_velocity_D_7_7( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__h, real_type xo__k, real_type xo__L, real_type xo__retrograde ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_z_velocity_D_7_7( p={}, f={}, g={}, h={}, k={}, L={}, retrograde={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__h, xo__k, xo__L, xo__retrograde, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type result__ = sqrt(t1 + t2 + t3 + t5);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t7   = sqrt(t1 + t2 + t3 + t5);
    real_type result__ = xo__x / t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_1( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1_1( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__y * xo__y;
    real_type t2   = xo__z * xo__z;
    real_type t4   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t6   = xo__x * xo__x;
    real_type t7   = t6 + t1 + t2 + t4;
    real_type t8   = sqrt(t7);
    real_type result__ = 1.0 / t8 / t7 * (t1 + t2 + t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_1_1( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1_2( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t6   = t1 + t2 + t3 + t5;
    real_type t7   = sqrt(t6);
    real_type result__ = -xo__y * xo__x / t7 / t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_1_2( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1_3( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t6   = t1 + t2 + t3 + t5;
    real_type t7   = sqrt(t6);
    real_type result__ = -xo__z * xo__x / t7 / t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_1_3( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_2( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t7   = sqrt(t1 + t2 + t3 + t5);
    real_type result__ = xo__y / t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_2( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_2_2( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__z * xo__z;
    real_type t4   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t6   = xo__y * xo__y;
    real_type t7   = t6 + t1 + t2 + t4;
    real_type t8   = sqrt(t7);
    real_type result__ = 1.0 / t8 / t7 * (t1 + t2 + t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_2_2( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_2_3( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t6   = t1 + t2 + t3 + t5;
    real_type t7   = sqrt(t6);
    real_type result__ = -xo__z * xo__y / t7 / t6;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_2_3( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_3( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t3   = xo__z * xo__z;
    real_type t5   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t7   = sqrt(t1 + t2 + t3 + t5);
    real_type result__ = xo__z / t7;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_3( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_3_3( real_type xo__x, real_type xo__y, real_type xo__z ) const {
    real_type t1   = xo__x * xo__x;
    real_type t2   = xo__y * xo__y;
    real_type t4   = ModelPars[iM_epsi_norm] * ModelPars[iM_epsi_norm];
    real_type t6   = xo__z * xo__z;
    real_type t7   = t6 + t1 + t2 + t4;
    real_type t8   = sqrt(t7);
    real_type result__ = 1.0 / t8 / t7 * (t1 + t2 + t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_norm_reg_D_3_3( x={}, y={}, z={} ) return {}\n",
        xo__x, xo__y, xo__z, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = sin(xo__L);
    real_type result__ = 1.0 / (t1 * xo__f + t3 * xo__g + 1) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = sin(xo__L);
    real_type result__ = 1.0 / (t1 * xo__f + t3 * xo__g + 1);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_1( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_1_1( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = sin(xo__L);
    real_type t7   = t1 * t1;
    real_type t8   = xo__f * xo__f;
    real_type t10  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t1 * t2 + 2 * t1 * xo__f - t10 * t7 + 2 * t2 * xo__g + t8 * t7 + t10 + 1) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_1_2( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = sin(xo__L);
    real_type t2   = cos(xo__L);
    real_type t7   = t2 * t2;
    real_type t8   = xo__f * xo__f;
    real_type t10  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t1 * t2 + 2 * t1 * xo__g - t10 * t7 + 2 * t2 * xo__f + t8 * t7 + t10 + 1) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_1_3( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = cos(xo__L);
    real_type t10  = t3 * t3;
    real_type t11  = xo__f * xo__f;
    real_type t13  = xo__g * xo__g;
    real_type result__ = 1.0 / (2 * xo__f * xo__g * t3 * t1 + 2 * t1 * xo__g + t11 * t10 - t13 * t10 + 2 * t3 * xo__f + t13 + 1) * (t1 * xo__f - t3 * xo__g);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_1_4( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = sin(xo__L);
    real_type t8   = t1 * t1;
    real_type t9   = xo__f * xo__f;
    real_type t11  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t3 * t1 + 2 * t1 * xo__f - t11 * t8 + 2 * t3 * xo__g + t9 * t8 + t11 + 1) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_2( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = xo__f * xo__f;
    real_type t6   = xo__g * xo__g;
    real_type t14  = t6 * xo__g;
    real_type t16  = sin(xo__L);
    real_type t19  = 3 * t6;
    real_type result__ = 2 / (t2 * t1 * (t4 * xo__f - 3 * t6 * xo__f) + t2 * (t16 * (3 * xo__g * t4 - t14) + 3 * t4 - t19) + 3 * t1 * (2 * t16 * xo__g + t6 + 1) * xo__f + t16 * (t14 + 3 * xo__g) + t19 + 1) * t2 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_2_2( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t3   = sin(xo__L);
    real_type t4   = xo__f * xo__f;
    real_type t6   = xo__g * xo__g;
    real_type t10  = t1 * t1;
    real_type t15  = t6 * xo__g;
    real_type t19  = 3 * t6;
    real_type result__ = 2 / (t10 * t1 * (t4 * xo__f - 3 * t6 * xo__f) + t10 * (t3 * (3 * xo__g * t4 - t15) + 3 * t4 - t19) + 3 * t1 * (2 * t3 * xo__g + t6 + 1) * xo__f + t3 * (t15 + 3 * xo__g) + t19 + 1) * t3 * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_2_3( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = sin(xo__L);
    real_type t9   = xo__f * xo__f;
    real_type t11  = xo__g * xo__g;
    real_type t19  = t11 * xo__g;
    real_type t23  = 3 * t11;
    real_type result__ = -1.0 / (t2 * t1 * (-3 * t11 * xo__f + t9 * xo__f) + t2 * (t4 * (3 * xo__g * t9 - t19) + 3 * t9 - t23) + 3 * t1 * (2 * xo__g * t4 + t11 + 1) * xo__f + t4 * (t19 + 3 * xo__g) + t23 + 1) * xo__p * (xo__f * t1 * t4 - t2 * xo__g - t4 - xo__g);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_2_4( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = cos(xo__L);
    real_type t8   = t3 * t3;
    real_type t9   = xo__f * xo__f;
    real_type t11  = xo__g * xo__g;
    real_type result__ = -1.0 / (2 * xo__f * xo__g * t3 * t1 + 2 * t1 * xo__g - t11 * t8 + 2 * t3 * xo__f + t9 * t8 + t11 + 1) * t1 * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_3( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t6   = xo__f * xo__f;
    real_type t8   = xo__g * xo__g;
    real_type t16  = t8 * xo__g;
    real_type t18  = sin(xo__L);
    real_type t21  = 3 * t8;
    real_type result__ = 1.0 / (t2 * t1 * (t6 * xo__f - 3 * t8 * xo__f) + t2 * (t18 * (3 * t6 * xo__g - t16) + 3 * t6 - t21) + 3 * t1 * (2 * t18 * xo__g + t8 + 1) * xo__f + t18 * (t16 + 3 * xo__g) + t21 + 1) * (-2 * t2 * xo__p + 2 * xo__p);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_3_3( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = cos(xo__L);
    real_type t2   = t1 * t1;
    real_type t4   = sin(xo__L);
    real_type t5   = xo__g * t4;
    real_type t11  = xo__f * xo__f;
    real_type t13  = xo__g * xo__g;
    real_type t21  = t13 * xo__g;
    real_type t25  = 3 * t13;
    real_type result__ = 1.0 / (t2 * t1 * (t11 * xo__f - 3 * t13 * xo__f) + t2 * (t4 * (3 * t11 * xo__g - t21) + 3 * t11 - t25) + 3 * t1 * (t13 + 2 * t5 + 1) * xo__f + t4 * (t21 + 3 * xo__g) + t25 + 1) * xo__p * (t2 * xo__f + t1 * (t5 - 1) - 2 * xo__f);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_3_4( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = sin(xo__L);
    real_type t3   = cos(xo__L);
    real_type t7   = xo__f * xo__f;
    real_type t8   = xo__g * xo__g;
    real_type t10  = t3 * t3;
    real_type result__ = 1.0 / (t10 * (t7 - t8) + t3 * (2 * t1 * xo__g * xo__f + 2 * xo__f) + t8 + 2 * t1 * xo__g + 1) * (t1 * xo__f - xo__g * t3) * xo__p;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_4( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::ray_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L ) const {
    real_type t1   = xo__f * xo__f;
    real_type t2   = xo__g * xo__g;
    real_type t4   = cos(xo__L);
    real_type t5   = t4 * t4;
    real_type t8   = sin(xo__L);
    real_type t14  = t8 * xo__g;
    real_type t25  = t2 * xo__g;
    real_type t29  = 3 * t2;
    real_type result__ = -1.0 / (t5 * t4 * (t1 * xo__f - 3 * t2 * xo__f) + t5 * (t8 * (3 * t1 * xo__g - t25) + 3 * t1 - t29) + 3 * t4 * (t2 + 2 * t14 + 1) * xo__f + t8 * (t25 + 3 * xo__g) + t29 + 1) * xo__p * (t5 * (t1 - t2) + t4 * (2 * t8 * xo__g * xo__f - xo__f) - 2 * t1 - t2 - t14);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ray_D_4_4( p={}, f={}, g={}, L={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = cos(xo__L);
    real_type t5   = sin(xo__L);
    real_type result__ = sqrt(1.0 / xo__p * ((2 * t1 + xo__f) * xo__f + (2 * t5 + xo__g) * xo__g + 1) * xo__muS);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = sqrt(xo__p);
    real_type t6   = cos(xo__L);
    real_type t9   = sin(xo__L);
    real_type t12  = xo__f * xo__f;
    real_type t13  = xo__g * xo__g;
    real_type t15  = sqrt(2 * t6 * xo__f + 2 * t9 * xo__g + t12 + t13 + 1);
    real_type result__ = -t15 / t2 / xo__p * t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_1( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_1( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = xo__p * xo__p;
    real_type t3   = sqrt(xo__p);
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = sqrt(2 * t10 * xo__g + 2 * t7 * xo__f + t13 + t14 + 1);
    real_type result__ = 3.0 / 4.0 * t16 / t3 / t2 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_1_1( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = cos(xo__L);
    real_type t5   = sqrt(xo__p);
    real_type t10  = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = sqrt(2 * t10 * xo__g + 2 * t2 * xo__f + t13 + t14 + 1);
    real_type result__ = -1.0 / t16 / t5 / xo__p * (t2 + xo__f) * t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_1_2( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = sin(xo__L);
    real_type t5   = sqrt(xo__p);
    real_type t8   = cos(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = sqrt(2 * t2 * xo__g + 2 * t8 * xo__f + t13 + t14 + 1);
    real_type result__ = -1.0 / t16 / t5 / xo__p * (t2 + xo__g) * t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_1_3( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = sin(xo__L);
    real_type t4   = cos(xo__L);
    real_type t8   = sqrt(xo__p);
    real_type t15  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t18  = sqrt(2 * t2 * xo__g + 2 * t4 * xo__f + t15 + t16 + 1);
    real_type result__ = -1.0 / t18 / t8 / xo__p * (-t2 * xo__f + xo__g * t4) * t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_1_4( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t3   = sqrt(xo__p);
    real_type t7   = cos(xo__L);
    real_type t10  = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = sqrt(2 * t10 * xo__g + 2 * t7 * xo__f + t13 + t14 + 1);
    real_type result__ = -t16 / t3 / xo__p / t1 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_1_5( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = cos(xo__L);
    real_type t5   = sqrt(xo__p);
    real_type t9   = sin(xo__L);
    real_type t12  = xo__f * xo__f;
    real_type t13  = xo__g * xo__g;
    real_type t15  = sqrt(2 * t2 * xo__f + 2 * t9 * xo__g + t12 + t13 + 1);
    real_type result__ = 1.0 / t15 / t5 * (t2 + xo__f) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_2( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_2( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = cos(xo__L);
    real_type t3   = t2 * t2;
    real_type t4   = sin(xo__L);
    real_type t6   = 2 * xo__g * t4;
    real_type t7   = xo__g * xo__g;
    real_type t10  = sqrt(xo__p);
    real_type t14  = xo__f * xo__f;
    real_type t15  = 2 * t2 * xo__f + t14 + t6 + t7 + 1;
    real_type t16  = sqrt(t15);
    real_type result__ = 1.0 / t16 / t15 / t10 * (-t3 + t6 + t7 + 1) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_2_2( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = cos(xo__L);
    real_type t5   = sin(xo__L);
    real_type t7   = sqrt(xo__p);
    real_type t14  = xo__f * xo__f;
    real_type t15  = xo__g * xo__g;
    real_type t16  = 2 * t2 * xo__f + 2 * t5 * xo__g + t14 + t15 + 1;
    real_type t17  = sqrt(t16);
    real_type result__ = -1.0 / t17 / t16 / t7 * (t5 + xo__g) * (t2 + xo__f) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_2_3( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__p);
    real_type t3   = cos(xo__L);
    real_type t6   = sin(xo__L);
    real_type t9   = xo__f * xo__f;
    real_type t10  = xo__g * xo__g;
    real_type t11  = 2 * t3 * xo__f + 2 * t6 * xo__g + t10 + t9 + 1;
    real_type t12  = sqrt(t11);
    real_type t16  = sqrt(xo__muS);
    real_type t17  = t3 * t3;
    real_type result__ = -(-xo__g * t17 + t3 * (t6 + xo__g) * xo__f + t10 * t6 + 2 * xo__g + t6) * t16 / t12 / t11 / t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_2_4( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t3   = cos(xo__L);
    real_type t6   = sqrt(xo__p);
    real_type t10  = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = sqrt(2 * t10 * xo__g + 2 * t3 * xo__f + t13 + t14 + 1);
    real_type result__ = 1.0 / t16 / t6 * (t3 + xo__f) / t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_2_5( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = sin(xo__L);
    real_type t5   = sqrt(xo__p);
    real_type t7   = cos(xo__L);
    real_type t12  = xo__f * xo__f;
    real_type t13  = xo__g * xo__g;
    real_type t15  = sqrt(2 * t2 * xo__g + 2 * t7 * xo__f + t12 + t13 + 1);
    real_type result__ = 1.0 / t15 / t5 * (t2 + xo__g) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_3( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_3_3( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = cos(xo__L);
    real_type t4   = pow(t2 + xo__f, 2);
    real_type t6   = sqrt(xo__p);
    real_type t10  = sin(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t15  = 2 * t10 * xo__g + 2 * t2 * xo__f + t13 + t14 + 1;
    real_type t16  = sqrt(t15);
    real_type result__ = 1.0 / t16 / t15 / t6 * t4 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_3_3( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_3_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = cos(xo__L);
    real_type t5   = t2 * xo__f;
    real_type t6   = sin(xo__L);
    real_type t7   = t6 * xo__g;
    real_type t9   = sqrt(xo__p);
    real_type t14  = xo__f * xo__f;
    real_type t15  = xo__g * xo__g;
    real_type t16  = 2 * t5 + 2 * t7 + t14 + t15 + 1;
    real_type t17  = sqrt(t16);
    real_type result__ = 1.0 / t17 / t16 / t9 * (1 + t5 + t7) * (t2 + xo__f) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_3_4( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_3_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t3   = sin(xo__L);
    real_type t6   = sqrt(xo__p);
    real_type t8   = cos(xo__L);
    real_type t13  = xo__f * xo__f;
    real_type t14  = xo__g * xo__g;
    real_type t16  = sqrt(2 * t3 * xo__g + 2 * t8 * xo__f + t13 + t14 + 1);
    real_type result__ = 1.0 / t16 / t6 * (t3 + xo__g) / t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_3_5( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t2   = sin(xo__L);
    real_type t4   = cos(xo__L);
    real_type t8   = sqrt(xo__p);
    real_type t14  = xo__f * xo__f;
    real_type t15  = xo__g * xo__g;
    real_type t17  = sqrt(2 * t2 * xo__g + 2 * t4 * xo__f + t14 + t15 + 1);
    real_type result__ = 1.0 / t17 / t8 * (-t2 * xo__f + xo__g * t4) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_4( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_4_4( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__p);
    real_type t3   = cos(xo__L);
    real_type t6   = sin(xo__L);
    real_type t8   = 2 * t6 * xo__g;
    real_type t9   = xo__f * xo__f;
    real_type t10  = xo__g * xo__g;
    real_type t11  = 2 * t3 * xo__f + t10 + t8 + t9 + 1;
    real_type t12  = sqrt(t11);
    real_type t17  = t3 * t3;
    real_type t27  = sqrt(xo__muS);
    real_type result__ = -t27 * (t17 * (t9 - t10) + t3 * (t9 + t10 + t8 + 1) * xo__f + t6 * (t9 + t10 + 1) * xo__g + t9 + 2 * t10) / t12 / t11 / t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_4_4( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_4_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = sqrt(xo__muS);
    real_type t3   = sin(xo__L);
    real_type t5   = cos(xo__L);
    real_type t9   = sqrt(xo__p);
    real_type t15  = xo__f * xo__f;
    real_type t16  = xo__g * xo__g;
    real_type t18  = sqrt(2 * t3 * xo__g + 2 * t5 * xo__f + t15 + t16 + 1);
    real_type result__ = 1.0 / t18 / t9 * (-t3 * xo__f + xo__g * t5) / t1 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_4_5( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t7   = xo__f * xo__f;
    real_type t8   = xo__g * xo__g;
    real_type t10  = sqrt(2 * t1 * xo__f + 2 * xo__g * t4 + t7 + t8 + 1);
    real_type t11  = sqrt(xo__muS);
    real_type t14  = sqrt(xo__p);
    real_type result__ = 1.0 / t14 / t11 * t10 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_5( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::vel_D_5_5( real_type xo__p, real_type xo__f, real_type xo__g, real_type xo__L, real_type xo__muS ) const {
    real_type t1   = cos(xo__L);
    real_type t4   = sin(xo__L);
    real_type t7   = xo__f * xo__f;
    real_type t8   = xo__g * xo__g;
    real_type t10  = sqrt(2 * t1 * xo__f + 2 * xo__g * t4 + t7 + t8 + 1);
    real_type t11  = sqrt(xo__muS);
    real_type t15  = sqrt(xo__p);
    real_type result__ = -1.0 / t15 / t11 / xo__muS * t10 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_vel_D_5_5( p={}, f={}, g={}, L={}, muS={} ) return {}\n",
        xo__p, xo__f, xo__g, xo__L, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::acceleration_r( real_type xo__r, real_type xo__muS ) const {
    real_type t1   = 1.0 / xo__r;
    real_type t3   = vc(xo__r);
    real_type t4   = t3 * t3;
    real_type result__ = t1 * (t1 * xo__muS - t4);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acceleration_r( r={}, muS={} ) return {}\n",
        xo__r, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_1( real_type xo__r, real_type xo__muS ) const {
    real_type t1   = vc(xo__r);
    real_type t2   = vc_D(xo__r);
    real_type t4   = xo__r * xo__r;
    real_type t7   = t1 * t1;
    real_type result__ = 1.0 / t4 / xo__r * (-2 * t4 * t2 * t1 + xo__r * t7 - 2 * xo__muS);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acceleration_r_D_1( r={}, muS={} ) return {}\n",
        xo__r, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_1_1( real_type xo__r, real_type xo__muS ) const {
    real_type t1   = vc(xo__r);
    real_type t2   = vc_DD(xo__r);
    real_type t4   = xo__r * xo__r;
    real_type t5   = t4 * xo__r;
    real_type t8   = vc_D(xo__r);
    real_type t9   = t8 * t8;
    real_type t15  = t1 * t1;
    real_type t20  = t4 * t4;
    real_type result__ = 1.0 / t20 * (-2 * t5 * t2 * t1 + 4 * t4 * t8 * t1 - 2 * xo__r * t15 - 2 * t5 * t9 + 6 * xo__muS);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acceleration_r_D_1_1( r={}, muS={} ) return {}\n",
        xo__r, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_1_2( real_type xo__r, real_type xo__muS ) const {
    real_type t1   = xo__r * xo__r;
    real_type result__ = -2 / t1 / xo__r;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acceleration_r_D_1_2( r={}, muS={} ) return {}\n",
        xo__r, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_2( real_type xo__r, real_type xo__muS ) const {
    real_type t1   = xo__r * xo__r;
    real_type result__ = 1.0 / t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acceleration_r_D_2( r={}, muS={} ) return {}\n",
        xo__r, xo__muS, result__
      );
    }
    return result__;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_2_2( real_type xo__r, real_type xo__muS ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_acceleration_r_D_2_2( r={}, muS={} ) return {}\n",
        xo__r, xo__muS, result__
      );
    }
    return result__;
  }

}

// EOF: gtocX_2burn_pars_Methods_UserFunctions.cc