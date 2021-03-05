/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods_UserFunctions.cc                         |
 |                                                                       |
 |  version: 1.0   date 5/3/2021                                         |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  MaximumAscent::eta( real_type xo__tf ) const {
    real_type result__ = ModelPars[iM_v0] * xo__tf / ModelPars[iM_r0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_eta( tf={} ) return {}\n",
        xo__tf, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::eta_D( real_type xo__tf ) const {
    real_type result__ = ModelPars[iM_v0] / ModelPars[iM_r0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_eta_D( tf={} ) return {}\n",
        xo__tf, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::eta_DD( real_type xo__tf ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_eta_DD( tf={} ) return {}\n",
        xo__tf, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::Tbar( real_type xo__tf ) const {
    real_type result__ = ModelPars[iM_T] * xo__tf / ModelPars[iM_v0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Tbar( tf={} ) return {}\n",
        xo__tf, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::Tbar_D( real_type xo__tf ) const {
    real_type result__ = ModelPars[iM_T] / ModelPars[iM_v0];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Tbar_D( tf={} ) return {}\n",
        xo__tf, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::Tbar_DD( real_type xo__tf ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Tbar_DD( tf={} ) return {}\n",
        xo__tf, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::tf( real_type xo__days ) const {
    real_type result__ = 86400 * xo__days;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_tf( days={} ) return {}\n",
        xo__days, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::tf_D( real_type xo__days ) const {
    real_type result__ = 86400;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_tf_D( days={} ) return {}\n",
        xo__days, result__
      );
    }
    return result__;
  }

  real_type
  MaximumAscent::tf_DD( real_type xo__days ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_tf_DD( days={} ) return {}\n",
        xo__days, result__
      );
    }
    return result__;
  }

}

// EOF: MaximumAscent_Methods_UserFunctions.cc
