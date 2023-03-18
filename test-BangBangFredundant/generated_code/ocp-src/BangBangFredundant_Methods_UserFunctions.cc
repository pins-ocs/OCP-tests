/*-----------------------------------------------------------------------*\
 |  file: BangBangFredundant_Methods_UserFunctions.cc                    |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "BangBangFredundant.hh"
#include "BangBangFredundant_Pars.hh"
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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_Flim_max_DD(__t1) Flim_max.DD( __t1)
#define ALIAS_Flim_max_D(__t1) Flim_max.D( __t1)
#define ALIAS_Flim_min_DD(__t1) Flim_min.DD( __t1)
#define ALIAS_Flim_min_D(__t1) Flim_min.D( __t1)
#define ALIAS_aF2Control_D_3(__t1, __t2, __t3) aF2Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2(__t1, __t2, __t3) aF2Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1(__t1, __t2, __t3) aF2Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_3_3(__t1, __t2, __t3) aF2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_3(__t1, __t2, __t3) aF2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_2(__t1, __t2, __t3) aF2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_3(__t1, __t2, __t3) aF2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_2(__t1, __t2, __t3) aF2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_1(__t1, __t2, __t3) aF2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3(__t1, __t2, __t3) aF1Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2(__t1, __t2, __t3) aF1Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1(__t1, __t2, __t3) aF1Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3_3(__t1, __t2, __t3) aF1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_3(__t1, __t2, __t3) aF1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_2(__t1, __t2, __t3) aF1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_3(__t1, __t2, __t3) aF1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_2(__t1, __t2, __t3) aF1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_1(__t1, __t2, __t3) aF1Control.D_1_1( __t1, __t2, __t3)


namespace BangBangFredundantDefine {
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
  BangBangFredundant::Flim( real_type xo___V ) const {
    real_type t2   = Flim_min(-1 - xo___V);
    real_type t4   = Flim_max(xo___V - 1);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Flim( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  BangBangFredundant::Flim_D( real_type xo___V ) const {
    real_type t2   = ALIAS_Flim_min_D(-1 - xo___V);
    real_type t4   = ALIAS_Flim_max_D(xo___V - 1);
    real_type result__ = -t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Flim_D( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

  real_type
  BangBangFredundant::Flim_DD( real_type xo___V ) const {
    real_type t2   = ALIAS_Flim_min_DD(-1 - xo___V);
    real_type t4   = ALIAS_Flim_max_DD(xo___V - 1);
    real_type result__ = t2 + t4;
    if ( m_debug ) {
      UTILS_ASSERT(
        Utils::is_finite(result__),
        "UserFunctions_Flim_DD( _V={} ) return {}\n",
        xo___V, result__
      );
    }
    return result__;
  }

}

// EOF: BangBangFredundant_Methods_UserFunctions.cc
