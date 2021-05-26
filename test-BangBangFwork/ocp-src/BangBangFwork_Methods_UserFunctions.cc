/*-----------------------------------------------------------------------*\
 |  file: BangBangFwork_Methods_UserFunctions.cc                         |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#include "BangBangFwork.hh"
#include "BangBangFwork_Pars.hh"

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
#define ALIAS_Fcontrol_D_3(__t1, __t2, __t3) Fcontrol.D_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_2(__t1, __t2, __t3) Fcontrol.D_2( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1(__t1, __t2, __t3) Fcontrol.D_1( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_3_3(__t1, __t2, __t3) Fcontrol.D_3_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_2_3(__t1, __t2, __t3) Fcontrol.D_2_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_2_2(__t1, __t2, __t3) Fcontrol.D_2_2( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1_3(__t1, __t2, __t3) Fcontrol.D_1_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1_2(__t1, __t2, __t3) Fcontrol.D_1_2( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1_1(__t1, __t2, __t3) Fcontrol.D_1_1( __t1, __t2, __t3)


namespace BangBangFworkDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  BangBangFwork::fMax( real_type xo__zeta ) const {
    real_type t2   = sin(xo__zeta);
    real_type t6   = sin(10 * xo__zeta);
    real_type result__ = t2 * ModelPars[iM_amp1] + t6 * ModelPars[iM_amp2] + 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_fMax( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  BangBangFwork::fMax_D( real_type xo__zeta ) const {
    real_type t1   = ModelPars[iM_amp2];
    real_type t2   = cos(xo__zeta);
    real_type t3   = t2 * t2;
    real_type t4   = t3 * t3;
    real_type t5   = t4 * t4;
    real_type result__ = 11200 * t4 * t3 * t1 + 5120 * t5 * t3 * t1 + 500 * t3 * t1 - 4000 * t4 * t1 - 12800 * t5 * t1 + t2 * ModelPars[iM_amp1] - 10 * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_fMax_D( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

  real_type
  BangBangFwork::fMax_DD( real_type xo__zeta ) const {
    real_type t1   = sin(xo__zeta);
    real_type t2   = cos(xo__zeta);
    real_type t3   = t2 * t2;
    real_type t4   = t3 * t3;
    real_type t5   = t4 * t4;
    real_type t7   = ModelPars[iM_amp2];
    real_type t10  = t3 * t2;
    real_type result__ = -(-102400 * t7 * t4 * t10 + 67200 * t7 * t4 * t2 + 51200 * t7 * t5 * t2 - 16000 * t7 * t10 + 1000 * t7 * t2 + ModelPars[iM_amp1]) * t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_fMax_DD( zeta={} ) return {}\n",
        xo__zeta, result__
      );
    }
    return result__;
  }

}

// EOF: BangBangFwork_Methods_UserFunctions.cc
