/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking_Methods_UserFunctions.cc                |
 |                                                                       |
 |  version: 1.0   date 5/12/2021                                        |
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


#include "ICLOCS_ParallelParking.hh"
#include "ICLOCS_ParallelParking_Pars.hh"

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
#define ALIAS_phi_bound_DD(__t1) phi_bound.DD( __t1)
#define ALIAS_phi_bound_D(__t1) phi_bound.D( __t1)
#define ALIAS_acc_bound_DD(__t1) acc_bound.DD( __t1)
#define ALIAS_acc_bound_D(__t1) acc_bound.D( __t1)
#define ALIAS_vel_bound_DD(__t1) vel_bound.DD( __t1)
#define ALIAS_vel_bound_D(__t1) vel_bound.D( __t1)
#define ALIAS_EXTRA2_bound_DD(__t1) EXTRA2_bound.DD( __t1)
#define ALIAS_EXTRA2_bound_D(__t1) EXTRA2_bound.D( __t1)
#define ALIAS_EXTRA1_bound_DD(__t1) EXTRA1_bound.DD( __t1)
#define ALIAS_EXTRA1_bound_D(__t1) EXTRA1_bound.D( __t1)
#define ALIAS_D_bound_DD(__t1) D_bound.DD( __t1)
#define ALIAS_D_bound_D(__t1) D_bound.D( __t1)
#define ALIAS_C_bound_DD(__t1) C_bound.DD( __t1)
#define ALIAS_C_bound_D(__t1) C_bound.D( __t1)
#define ALIAS_B_bound_DD(__t1) B_bound.DD( __t1)
#define ALIAS_B_bound_D(__t1) B_bound.D( __t1)
#define ALIAS_A_bound_DD(__t1) A_bound.DD( __t1)
#define ALIAS_A_bound_D(__t1) A_bound.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_ParallelParkingDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  ICLOCS_ParallelParking::Ax( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = cos(xo__theta);
    real_type t7   = sin(xo__theta);
    real_type result__ = xo__x + t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) - t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = sin(xo__theta);
    real_type t7   = cos(xo__theta);
    real_type result__ = -t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) - t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ax_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = cos(xo__theta);
    real_type t7   = sin(xo__theta);
    real_type result__ = -t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) + t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ax_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = sin(xo__theta);
    real_type t7   = cos(xo__theta);
    real_type result__ = xo__y + t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) + t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = cos(xo__theta);
    real_type t7   = sin(xo__theta);
    real_type result__ = t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) - t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ay_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = sin(xo__theta);
    real_type t7   = cos(xo__theta);
    real_type result__ = -t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) - t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ay_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = cos(xo__theta);
    real_type t7   = sin(xo__theta);
    real_type result__ = xo__x + t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) + t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = sin(xo__theta);
    real_type t7   = cos(xo__theta);
    real_type result__ = -t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) + t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Bx_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = cos(xo__theta);
    real_type t7   = sin(xo__theta);
    real_type result__ = -t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) - t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Bx_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = sin(xo__theta);
    real_type t7   = cos(xo__theta);
    real_type result__ = xo__y + t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) - t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = cos(xo__theta);
    real_type t7   = sin(xo__theta);
    real_type result__ = t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) + t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::By_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t4   = sin(xo__theta);
    real_type t7   = cos(xo__theta);
    real_type result__ = -t4 * (ModelPars[iM_len_a] + ModelPars[iM_len_f]) + t7 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_By_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = cos(xo__theta);
    real_type t5   = sin(xo__theta);
    real_type result__ = -t2 * ModelPars[iM_len_r] + t5 * ModelPars[iM_b] + xo__x;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = sin(xo__theta);
    real_type t5   = cos(xo__theta);
    real_type result__ = t2 * ModelPars[iM_len_r] + t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cx_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = cos(xo__theta);
    real_type t5   = sin(xo__theta);
    real_type result__ = t2 * ModelPars[iM_len_r] - t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cx_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = sin(xo__theta);
    real_type t5   = cos(xo__theta);
    real_type result__ = -t2 * ModelPars[iM_len_r] - t5 * ModelPars[iM_b] + xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = cos(xo__theta);
    real_type t5   = sin(xo__theta);
    real_type result__ = -t2 * ModelPars[iM_len_r] + t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Cy_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = sin(xo__theta);
    real_type t5   = cos(xo__theta);
    real_type result__ = t2 * ModelPars[iM_len_r] + t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Cy_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = cos(xo__theta);
    real_type t5   = sin(xo__theta);
    real_type result__ = -t2 * ModelPars[iM_len_r] - t5 * ModelPars[iM_b] + xo__x;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = sin(xo__theta);
    real_type t5   = cos(xo__theta);
    real_type result__ = t2 * ModelPars[iM_len_r] - t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dx_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = cos(xo__theta);
    real_type t5   = sin(xo__theta);
    real_type result__ = t2 * ModelPars[iM_len_r] + t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dx_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = sin(xo__theta);
    real_type t5   = cos(xo__theta);
    real_type result__ = -t2 * ModelPars[iM_len_r] + t5 * ModelPars[iM_b] + xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = cos(xo__theta);
    real_type t5   = sin(xo__theta);
    real_type result__ = -t2 * ModelPars[iM_len_r] - t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Dy_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t2   = sin(xo__theta);
    real_type t5   = cos(xo__theta);
    real_type result__ = t2 * ModelPars[iM_len_r] - t5 * ModelPars[iM_b];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Dy_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = cos(xo__theta);
    real_type t3   = sin(xo__theta);
    real_type result__ = -t1 * xo__x - t3 * xo__y - ModelPars[iM_len_a] / 2 - ModelPars[iM_len_f] / 2 + ModelPars[iM_len_r] / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = cos(xo__theta);
    real_type result__ = -t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = sin(xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = sin(xo__theta);
    real_type result__ = -t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = cos(xo__theta);
    real_type result__ = -t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = sin(xo__theta);
    real_type t3   = cos(xo__theta);
    real_type result__ = t1 * xo__x - t3 * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ox_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = cos(xo__theta);
    real_type t3   = sin(xo__theta);
    real_type result__ = t1 * xo__x + t3 * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ox_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = sin(xo__theta);
    real_type t3   = cos(xo__theta);
    real_type result__ = t1 * xo__x - t3 * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = sin(xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = cos(xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = cos(xo__theta);
    real_type result__ = -t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = sin(xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = cos(xo__theta);
    real_type t3   = sin(xo__theta);
    real_type result__ = t1 * xo__x + t3 * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Oy_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = sin(xo__theta);
    real_type t3   = cos(xo__theta);
    real_type result__ = -t1 * xo__x + t3 * xo__y;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Oy_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ox(xo__x, xo__y, xo__theta);
    real_type result__ = t1 + ModelPars[iM_len_SL];
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_1(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_1_1(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_1_2(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_1_3(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_2(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_2_2(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_2_3(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_3(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ex_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Ox_D_3_3(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ex_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Oy(xo__x, xo__y, xo__theta);
    real_type t3   = sin(xo__theta);
    real_type result__ = -t3 * ModelPars[iM_len_SL] + t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_1(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_1_1(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_1_2(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_1_3(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_2(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_2_2(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type result__ = Oy_D_2_3(xo__x, xo__y, xo__theta);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t3   = cos(xo__theta);
    real_type result__ = -t3 * ModelPars[iM_len_SL] + t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::Ey_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Oy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t3   = sin(xo__theta);
    real_type result__ = t3 * ModelPars[iM_len_SL] + t1;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_Ey_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type result__ = sqrt((xo__a / 2 + xo__b / 2 + xo__c / 2) * (-xo__a / 2 + xo__b / 2 + xo__c / 2) * (xo__a / 2 - xo__b / 2 + xo__c / 2) * (xo__a / 2 + xo__b / 2 - xo__c / 2));
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_1( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t12  = sqrt(t9 * t7 * t5);
    real_type result__ = (-t9 * t7 * t2 / 2 + t9 * t7 * t4 / 2 + t7 * t5 / 2 + t9 * t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_1( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_1_1( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t10  = t9 * t7;
    real_type t11  = t10 * t5;
    real_type t12  = sqrt(t11);
    real_type t15  = t7 * t4;
    real_type t17  = t7 * t2;
    real_type t23  = pow(t9 * t15 / 2 - t9 * t17 / 2 + t7 * t5 / 2 + t9 * t5 / 2, 2);
    real_type result__ = -t23 / t12 / t11 / 4 + (-t9 * t2 / 2 + t9 * t4 / 2 - t10 / 2 + t15 / 2 - t17 / 2 + t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_1_1( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_1_2( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t11  = t9 * t7 * t5;
    real_type t12  = sqrt(t11);
    real_type t15  = t7 * t4;
    real_type t16  = t9 * t15;
    real_type t18  = t9 * t7 * t2;
    real_type t19  = t9 * t5;
    real_type t20  = t7 * t5;
    real_type result__ = -(t16 / 2 + t18 / 2 - t19 / 2 + t20 / 2) * (t16 / 2 - t18 / 2 + t19 / 2 + t20 / 2) / t12 / t11 / 4 + (t9 * t2 / 2 + t15 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_1_2( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_1_3( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t11  = t9 * t7 * t5;
    real_type t12  = sqrt(t11);
    real_type t16  = t9 * t7 * t4;
    real_type t17  = t7 * t2;
    real_type t18  = t9 * t17;
    real_type t19  = t9 * t5;
    real_type t20  = t7 * t5;
    real_type result__ = -(t16 / 2 + t18 / 2 + t19 / 2 - t20 / 2) * (t16 / 2 - t18 / 2 + t19 / 2 + t20 / 2) / t12 / t11 / 4 + (t9 * t4 / 2 + t17 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_1_3( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_2( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t12  = sqrt(t9 * t7 * t5);
    real_type result__ = (t9 * t7 * t2 / 2 + t9 * t7 * t4 / 2 + t7 * t5 / 2 - t9 * t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_2( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_2_2( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t10  = t9 * t7;
    real_type t11  = t10 * t5;
    real_type t12  = sqrt(t11);
    real_type t15  = t7 * t4;
    real_type t17  = t7 * t2;
    real_type t23  = pow(t9 * t15 / 2 + t9 * t17 / 2 + t7 * t5 / 2 - t9 * t5 / 2, 2);
    real_type result__ = -t23 / t12 / t11 / 4 + (-t9 * t2 / 2 - t9 * t4 / 2 + t10 / 2 + t15 / 2 + t17 / 2 - t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_2_2( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_2_3( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t10  = t9 * t7;
    real_type t11  = t10 * t5;
    real_type t12  = sqrt(t11);
    real_type t16  = t9 * t7 * t4;
    real_type t18  = t9 * t7 * t2;
    real_type t19  = t9 * t5;
    real_type t20  = t7 * t5;
    real_type result__ = -(t16 / 2 + t18 / 2 + t19 / 2 - t20 / 2) * (t16 / 2 + t18 / 2 - t19 / 2 + t20 / 2) / t12 / t11 / 4 + (t10 / 2 + t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_2_3( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_3( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t12  = sqrt(t9 * t7 * t5);
    real_type result__ = (t9 * t7 * t2 / 2 + t9 * t7 * t4 / 2 - t7 * t5 / 2 + t9 * t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_3( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area_D_3_3( real_type xo__a, real_type xo__b, real_type xo__c ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2;
    real_type t10  = t9 * t7;
    real_type t11  = t10 * t5;
    real_type t12  = sqrt(t11);
    real_type t15  = t7 * t4;
    real_type t17  = t7 * t2;
    real_type t23  = pow(t9 * t15 / 2 + t9 * t17 / 2 - t7 * t5 / 2 + t9 * t5 / 2, 2);
    real_type result__ = -t23 / t12 / t11 / 4 + (t9 * t2 / 2 + t9 * t4 / 2 + t10 / 2 - t15 / 2 - t17 / 2 - t5 / 2) / t12 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area_D_3_3( a={}, b={}, c={} ) return {}\n",
        xo__a, xo__b, xo__c, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type result__ = area(t6, t12, t18);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1(t6, t12, t18);
    real_type t24  = area_D_3(t6, t12, t18);
    real_type result__ = t1 / t6 * t19 - t13 / t18 * t24;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1_1( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t22  = 2 * t1;
    real_type t24  = area_D_1_3(t6, t12, t18);
    real_type t25  = 1.0 / t18;
    real_type t28  = -2 * t13;
    real_type t35  = area_D_1(t6, t12, t18);
    real_type t39  = t22 * t22;
    real_type t45  = area_D_3_3(t6, t12, t18);
    real_type t53  = area_D_3(t6, t12, t18);
    real_type t57  = t28 * t28;
    real_type result__ = t22 * t20 * (t22 * t20 * t19 / 2 + t28 * t25 * t24 / 2) / 2 - t39 / t6 / t5 * t35 / 4 + t20 * t35 + t28 * t25 * (t22 * t20 * t24 / 2 + t28 * t25 * t45 / 2) / 2 - t57 / t18 / t17 * t53 / 4 + t25 * t53;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1_1( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t22  = 2 * t3;
    real_type t24  = area_D_1_3(t6, t12, t18);
    real_type t25  = 1.0 / t18;
    real_type t28  = -2 * t15;
    real_type t33  = 2 * t1;
    real_type t36  = area_D_1(t6, t12, t18);
    real_type t45  = area_D_3_3(t6, t12, t18);
    real_type t52  = -2 * t13;
    real_type t55  = area_D_3(t6, t12, t18);
    real_type result__ = t33 * t20 * (t22 * t20 * t19 / 2 + t28 * t25 * t24 / 2) / 2 - t22 * t33 / t6 / t5 * t36 / 4 + t52 * t25 * (t22 * t20 * t24 / 2 + t28 * t25 * t45 / 2) / 2 - t28 * t52 / t18 / t17 * t55 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1_2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t1;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t7;
    real_type t33  = -t23;
    real_type t36  = area_D_1(t6, t12, t18);
    real_type t44  = area_D_1_3(t6, t12, t18);
    real_type t47  = area_D_2_3(t6, t12, t18);
    real_type result__ = t33 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t23 * t33 / t6 / t5 * t36 / 4 - t20 * t36 - t13 / t18 * (t23 * t20 * t44 / 2 + t28 * t26 * t47 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t3;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t9;
    real_type t33  = 2 * t1;
    real_type t36  = area_D_1(t6, t12, t18);
    real_type t43  = area_D_1_3(t6, t12, t18);
    real_type t46  = area_D_2_3(t6, t12, t18);
    real_type result__ = t33 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t23 * t33 / t6 / t5 * t36 / 4 - t13 / t18 * (t23 * t20 * t43 / 2 + t28 * t26 * t46 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t7;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t13;
    real_type t37  = area_D_2_3(t6, t12, t18);
    real_type t40  = area_D_3_3(t6, t12, t18);
    real_type t46  = -t28;
    real_type t49  = area_D_3(t6, t12, t18);
    real_type result__ = t1 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t46 * t26 * (t23 * t20 * t37 / 2 + t28 * t26 * t40 / 2) / 2 - t28 * t46 / t18 / t17 * t49 / 4 - t26 * t49;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_1_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t9;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t15;
    real_type t37  = area_D_2_3(t6, t12, t18);
    real_type t40  = area_D_3_3(t6, t12, t18);
    real_type t47  = -2 * t13;
    real_type t50  = area_D_3(t6, t12, t18);
    real_type result__ = t1 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t47 * t26 * (t23 * t20 * t37 / 2 + t28 * t26 * t40 / 2) / 2 - t28 * t47 / t18 / t17 * t50 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_1_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1(t6, t12, t18);
    real_type t24  = area_D_3(t6, t12, t18);
    real_type result__ = t3 / t6 * t19 - t15 / t18 * t24;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_2_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t22  = 2 * t3;
    real_type t24  = area_D_1_3(t6, t12, t18);
    real_type t25  = 1.0 / t18;
    real_type t28  = -2 * t15;
    real_type t35  = area_D_1(t6, t12, t18);
    real_type t39  = t22 * t22;
    real_type t45  = area_D_3_3(t6, t12, t18);
    real_type t53  = area_D_3(t6, t12, t18);
    real_type t57  = t28 * t28;
    real_type result__ = t22 * t20 * (t22 * t20 * t19 / 2 + t28 * t25 * t24 / 2) / 2 - t39 / t6 / t5 * t35 / 4 + t20 * t35 + t28 * t25 * (t22 * t20 * t24 / 2 + t28 * t25 * t45 / 2) / 2 - t57 / t18 / t17 * t53 / 4 + t25 * t53;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_2_2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_2_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t1;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t7;
    real_type t33  = 2 * t3;
    real_type t36  = area_D_1(t6, t12, t18);
    real_type t43  = area_D_1_3(t6, t12, t18);
    real_type t46  = area_D_2_3(t6, t12, t18);
    real_type result__ = t33 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t23 * t33 / t6 / t5 * t36 / 4 - t15 / t18 * (t23 * t20 * t43 / 2 + t28 * t26 * t46 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_2_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_2_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t3;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t9;
    real_type t33  = -t23;
    real_type t36  = area_D_1(t6, t12, t18);
    real_type t44  = area_D_1_3(t6, t12, t18);
    real_type t47  = area_D_2_3(t6, t12, t18);
    real_type result__ = t33 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t23 * t33 / t6 / t5 * t36 / 4 - t20 * t36 - t15 / t18 * (t23 * t20 * t44 / 2 + t28 * t26 * t47 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_2_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_2_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t7;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t13;
    real_type t37  = area_D_2_3(t6, t12, t18);
    real_type t40  = area_D_3_3(t6, t12, t18);
    real_type t47  = -2 * t15;
    real_type t50  = area_D_3(t6, t12, t18);
    real_type result__ = t3 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t47 * t26 * (t23 * t20 * t37 / 2 + t28 * t26 * t40 / 2) / 2 - t28 * t47 / t18 / t17 * t50 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_2_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_2_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t9;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t15;
    real_type t37  = area_D_2_3(t6, t12, t18);
    real_type t40  = area_D_3_3(t6, t12, t18);
    real_type t46  = -t28;
    real_type t49  = area_D_3(t6, t12, t18);
    real_type result__ = t3 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t46 * t26 * (t23 * t20 * t37 / 2 + t28 * t26 * t40 / 2) / 2 - t28 * t46 / t18 / t17 * t49 / 4 - t26 * t49;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_2_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1(t6, t12, t18);
    real_type t25  = area_D_2(t6, t12, t18);
    real_type result__ = -t1 / t6 * t19 + t7 / t12 * t25;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_3_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t1;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t7;
    real_type t35  = area_D_1(t6, t12, t18);
    real_type t39  = t23 * t23;
    real_type t45  = area_D_2_2(t6, t12, t18);
    real_type t53  = area_D_2(t6, t12, t18);
    real_type t57  = t28 * t28;
    real_type result__ = t23 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t39 / t6 / t5 * t35 / 4 + t20 * t35 + t28 * t26 * (t23 * t20 * t25 / 2 + t28 * t26 * t45 / 2) / 2 - t57 / t12 / t11 * t53 / 4 + t26 * t53;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_3_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_3_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t3;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t9;
    real_type t34  = -2 * t1;
    real_type t37  = area_D_1(t6, t12, t18);
    real_type t46  = area_D_2_2(t6, t12, t18);
    real_type t52  = 2 * t7;
    real_type t55  = area_D_2(t6, t12, t18);
    real_type result__ = t34 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t23 * t34 / t6 / t5 * t37 / 4 + t52 * t26 * (t23 * t20 * t25 / 2 + t28 * t26 * t46 / 2) / 2 - t28 * t52 / t12 / t11 * t55 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_3_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_3_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t7;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t13;
    real_type t38  = area_D_2_2(t6, t12, t18);
    real_type t41  = area_D_2_3(t6, t12, t18);
    real_type t47  = -t23;
    real_type t50  = area_D_2(t6, t12, t18);
    real_type result__ = -t1 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t47 * t20 * (t23 * t20 * t38 / 2 + t28 * t26 * t41 / 2) / 2 - t23 * t47 / t12 / t11 * t50 / 4 - t20 * t50;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_3_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_3_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t9;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t15;
    real_type t38  = area_D_2_2(t6, t12, t18);
    real_type t41  = area_D_2_3(t6, t12, t18);
    real_type t47  = 2 * t7;
    real_type t50  = area_D_2(t6, t12, t18);
    real_type result__ = -t1 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t47 * t20 * (t23 * t20 * t38 / 2 + t28 * t26 * t41 / 2) / 2 - t23 * t47 / t12 / t11 * t50 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_3_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1(t6, t12, t18);
    real_type t25  = area_D_2(t6, t12, t18);
    real_type result__ = -t3 / t6 * t19 + t9 / t12 * t25;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_4_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_1(t6, t12, t18);
    real_type t20  = 1.0 / t6;
    real_type t23  = -2 * t3;
    real_type t25  = area_D_1_2(t6, t12, t18);
    real_type t26  = 1.0 / t12;
    real_type t28  = 2 * t9;
    real_type t35  = area_D_1(t6, t12, t18);
    real_type t39  = t23 * t23;
    real_type t45  = area_D_2_2(t6, t12, t18);
    real_type t53  = area_D_2(t6, t12, t18);
    real_type t57  = t28 * t28;
    real_type result__ = t23 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t39 / t6 / t5 * t35 / 4 + t20 * t35 + t28 * t26 * (t23 * t20 * t25 / 2 + t28 * t26 * t45 / 2) / 2 - t57 / t12 / t11 * t53 / 4 + t26 * t53;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_4_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_4_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t7;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t13;
    real_type t38  = area_D_2_2(t6, t12, t18);
    real_type t41  = area_D_2_3(t6, t12, t18);
    real_type t47  = 2 * t9;
    real_type t50  = area_D_2(t6, t12, t18);
    real_type result__ = -t3 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t47 * t20 * (t23 * t20 * t38 / 2 + t28 * t26 * t41 / 2) / 2 - t23 * t47 / t12 / t11 * t50 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_4_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_4_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_1_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t9;
    real_type t25  = area_D_1_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t15;
    real_type t38  = area_D_2_2(t6, t12, t18);
    real_type t41  = area_D_2_3(t6, t12, t18);
    real_type t47  = -t23;
    real_type t50  = area_D_2(t6, t12, t18);
    real_type result__ = -t3 / t6 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) + t47 * t20 * (t23 * t20 * t38 / 2 + t28 * t26 * t41 / 2) / 2 - t23 * t47 / t12 / t11 * t50 / 4 - t20 * t50;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_4_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_2(t6, t12, t18);
    real_type t25  = area_D_3(t6, t12, t18);
    real_type result__ = -t7 / t12 * t19 + t13 / t18 * t25;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_5_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p1y, 2);
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_2_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t7;
    real_type t25  = area_D_2_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t13;
    real_type t35  = area_D_2(t6, t12, t18);
    real_type t39  = t23 * t23;
    real_type t45  = area_D_3_3(t6, t12, t18);
    real_type t53  = area_D_3(t6, t12, t18);
    real_type t57  = t28 * t28;
    real_type result__ = t23 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t39 / t12 / t11 * t35 / 4 + t20 * t35 + t28 * t26 * (t23 * t20 * t25 / 2 + t28 * t26 * t45 / 2) / 2 - t57 / t18 / t17 * t53 / 4 + t26 * t53;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_5_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_5_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p1x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_2_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t9;
    real_type t25  = area_D_2_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t15;
    real_type t34  = -2 * t7;
    real_type t37  = area_D_2(t6, t12, t18);
    real_type t46  = area_D_3_3(t6, t12, t18);
    real_type t52  = 2 * t13;
    real_type t55  = area_D_3(t6, t12, t18);
    real_type result__ = t34 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t23 * t34 / t12 / t11 * t37 / 4 + t52 * t26 * (t23 * t20 * t25 / 2 + t28 * t26 * t46 / 2) / 2 - t28 * t52 / t18 / t17 * t55 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_5_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = area_D_2(t6, t12, t18);
    real_type t25  = area_D_3(t6, t12, t18);
    real_type result__ = -t9 / t12 * t19 + t15 / t18 * t25;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::area2_D_6_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p1x, 2);
    real_type t15  = xo__p3y - xo__p1y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = area_D_2_2(t6, t12, t18);
    real_type t20  = 1.0 / t12;
    real_type t23  = -2 * t9;
    real_type t25  = area_D_2_3(t6, t12, t18);
    real_type t26  = 1.0 / t18;
    real_type t28  = 2 * t15;
    real_type t35  = area_D_2(t6, t12, t18);
    real_type t39  = t23 * t23;
    real_type t45  = area_D_3_3(t6, t12, t18);
    real_type t53  = area_D_3(t6, t12, t18);
    real_type t57  = t28 * t28;
    real_type result__ = t23 * t20 * (t23 * t20 * t19 / 2 + t28 * t26 * t25 / 2) / 2 - t39 / t12 / t11 * t35 / 4 + t20 * t35 + t28 * t26 * (t23 * t20 * t25 / 2 + t28 * t26 * t45 / 2) / 2 - t57 / t18 / t17 * t53 / 4 + t26 * t53;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_area2_D_6_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type result__ = sqrt((xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2) * (-xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2) * (xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2) * (xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2) * (xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2));
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_1( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t15  = sqrt(t12 * t10 * t5);
    real_type t18  = t12 * t9;
    real_type result__ = (t12 * t7 * t5 / 2 - t18 * t7 * t2 / 2 + t18 * t7 * t4 / 2 + t10 * t5 / 2 + t18 * t5 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_1( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_1_1( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t21  = t7 * t2;
    real_type t29  = pow(t12 * t7 * t5 / 2 + t10 * t5 / 2 + t19 * t18 / 2 - t19 * t21 / 2 + t19 * t5 / 2, 2);
    real_type result__ = -t29 / t15 / t14 / 4 + (-t12 * t9 * t2 / 2 + t12 * t9 * t4 / 2 + t12 * t18 / 2 - t12 * t21 / 2 + t12 * t5 / 2 + t9 * t18 / 2 - t9 * t21 / 2 + t7 * t5 / 2 + t9 * t5 / 2 - t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_1_1( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_1_2( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t14  = t12 * t10 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t20  = t19 * t18;
    real_type t22  = t19 * t7 * t2;
    real_type t23  = t19 * t5;
    real_type t25  = t12 * t7 * t5;
    real_type t26  = t10 * t5;
    real_type result__ = -(t20 / 2 + t22 / 2 - t23 / 2 + t25 / 2 + t26 / 2) * (t20 / 2 - t22 / 2 + t23 / 2 + t25 / 2 + t26 / 2) / t15 / t14 / 4 + (t12 * t9 * t2 / 2 + t12 * t18 / 2 + t9 * t18 / 2 + t7 * t5 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_1_2( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_1_3( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t14  = t12 * t10 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t20  = t19 * t18;
    real_type t21  = t7 * t2;
    real_type t22  = t19 * t21;
    real_type t23  = t19 * t5;
    real_type t25  = t12 * t7 * t5;
    real_type t26  = t10 * t5;
    real_type result__ = -(t20 / 2 + t22 / 2 + t23 / 2 - t25 / 2 + t26 / 2) * (t20 / 2 - t22 / 2 + t23 / 2 + t25 / 2 + t26 / 2) / t15 / t14 / 4 + (t12 * t9 * t4 / 2 + t12 * t21 / 2 + t9 * t18 / 2 + t9 * t5 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_1_3( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_1_4( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t14  = t12 * t10 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t20  = t19 * t18;
    real_type t21  = t7 * t2;
    real_type t22  = t19 * t21;
    real_type t23  = t19 * t5;
    real_type t25  = t12 * t7 * t5;
    real_type t26  = t10 * t5;
    real_type result__ = -(t20 / 2 + t22 / 2 + t23 / 2 + t25 / 2 - t26 / 2) * (t20 / 2 - t22 / 2 + t23 / 2 + t25 / 2 + t26 / 2) / t15 / t14 / 4 + (t12 * t9 * t4 / 2 + t12 * t18 / 2 + t12 * t5 / 2 + t9 * t21 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_1_4( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_2( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t15  = sqrt(t12 * t10 * t5);
    real_type t18  = t12 * t9;
    real_type result__ = (t12 * t7 * t5 / 2 + t18 * t7 * t2 / 2 + t18 * t7 * t4 / 2 + t10 * t5 / 2 - t18 * t5 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_2( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_2_2( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t21  = t7 * t2;
    real_type t29  = pow(t12 * t7 * t5 / 2 + t10 * t5 / 2 + t19 * t18 / 2 + t19 * t21 / 2 - t19 * t5 / 2, 2);
    real_type result__ = -t29 / t15 / t14 / 4 + (-t12 * t9 * t2 / 2 - t12 * t9 * t4 / 2 + t12 * t18 / 2 + t12 * t21 / 2 - t12 * t5 / 2 + t9 * t18 / 2 + t9 * t21 / 2 + t7 * t5 / 2 - t9 * t5 / 2 + t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_2_2( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_2_3( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t20  = t19 * t18;
    real_type t21  = t7 * t2;
    real_type t22  = t19 * t21;
    real_type t23  = t19 * t5;
    real_type t25  = t12 * t7 * t5;
    real_type t26  = t10 * t5;
    real_type result__ = -(t20 / 2 + t22 / 2 + t23 / 2 - t25 / 2 + t26 / 2) * (t20 / 2 + t22 / 2 - t23 / 2 + t25 / 2 + t26 / 2) / t15 / t14 / 4 + (t12 * t5 / 2 + t9 * t18 / 2 + t9 * t21 / 2 + t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_2_3( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_2_4( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t20  = t19 * t18;
    real_type t21  = t7 * t2;
    real_type t22  = t19 * t21;
    real_type t23  = t19 * t5;
    real_type t25  = t12 * t7 * t5;
    real_type t26  = t10 * t5;
    real_type result__ = -(t20 / 2 + t22 / 2 + t23 / 2 + t25 / 2 - t26 / 2) * (t20 / 2 + t22 / 2 - t23 / 2 + t25 / 2 + t26 / 2) / t15 / t14 / 4 + (t12 * t18 / 2 + t12 * t21 / 2 + t9 * t5 / 2 + t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_2_4( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_3( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t15  = sqrt(t12 * t10 * t5);
    real_type t18  = t12 * t9;
    real_type result__ = (-t12 * t7 * t5 / 2 + t18 * t7 * t2 / 2 + t18 * t7 * t4 / 2 + t10 * t5 / 2 + t18 * t5 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_3( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_3_3( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t21  = t7 * t2;
    real_type t29  = pow(-t12 * t7 * t5 / 2 + t10 * t5 / 2 + t19 * t18 / 2 + t19 * t21 / 2 + t19 * t5 / 2, 2);
    real_type result__ = -t29 / t15 / t14 / 4 + (t12 * t9 * t2 / 2 + t12 * t9 * t4 / 2 - t12 * t18 / 2 - t12 * t21 / 2 - t12 * t5 / 2 + t9 * t18 / 2 + t9 * t21 / 2 - t7 * t5 / 2 + t9 * t5 / 2 + t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_3_3( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_3_4( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t19  = t12 * t9;
    real_type t20  = t19 * t7 * t4;
    real_type t22  = t19 * t7 * t2;
    real_type t23  = t19 * t5;
    real_type t25  = t12 * t7 * t5;
    real_type t26  = t10 * t5;
    real_type result__ = -(t20 / 2 + t22 / 2 + t23 / 2 + t25 / 2 - t26 / 2) * (t20 / 2 + t22 / 2 + t23 / 2 - t25 / 2 + t26 / 2) / t15 / t14 / 4 + (t12 * t9 * t2 / 2 + t12 * t9 * t4 / 2 + t7 * t5 / 2 + t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_3_4( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_4( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t15  = sqrt(t12 * t10 * t5);
    real_type t18  = t12 * t9;
    real_type result__ = (t12 * t7 * t5 / 2 + t18 * t7 * t2 / 2 + t18 * t7 * t4 / 2 - t10 * t5 / 2 + t18 * t5 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_4( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ_D_4_4( real_type xo__a, real_type xo__b, real_type xo__c, real_type xo__d ) const {
    real_type t2   = xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t4   = -xo__a / 2 + xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t5   = t4 * t2;
    real_type t7   = xo__a / 2 - xo__b / 2 + xo__c / 2 + xo__d / 2;
    real_type t9   = xo__a / 2 + xo__b / 2 - xo__c / 2 + xo__d / 2;
    real_type t10  = t9 * t7;
    real_type t12  = xo__a / 2 + xo__b / 2 + xo__c / 2 - xo__d / 2;
    real_type t13  = t12 * t10;
    real_type t14  = t13 * t5;
    real_type t15  = sqrt(t14);
    real_type t18  = t7 * t4;
    real_type t19  = t12 * t9;
    real_type t21  = t7 * t2;
    real_type t29  = pow(t12 * t7 * t5 / 2 - t10 * t5 / 2 + t19 * t18 / 2 + t19 * t21 / 2 + t19 * t5 / 2, 2);
    real_type result__ = -t29 / t15 / t14 / 4 + (t12 * t9 * t2 / 2 + t12 * t9 * t4 / 2 + t12 * t18 / 2 + t12 * t21 / 2 + t12 * t5 / 2 - t9 * t18 / 2 - t9 * t21 / 2 - t7 * t5 / 2 - t9 * t5 / 2 + t13 / 2) / t15 / 2;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ_D_4_4( a={}, b={}, c={}, d={} ) return {}\n",
        xo__a, xo__b, xo__c, xo__d, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type result__ = areaQ(t6, t12, t18, t24);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1(t6, t12, t18, t24);
    real_type t30  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t1 / t6 * t25 - t19 / t24 * t30;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_1( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t28  = 2 * t1;
    real_type t30  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t31  = 1.0 / t24;
    real_type t34  = -2 * t19;
    real_type t41  = areaQ_D_1(t6, t12, t18, t24);
    real_type t45  = t28 * t28;
    real_type t51  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t59  = areaQ_D_4(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t28 * t26 * (t28 * t26 * t25 / 2 + t34 * t31 * t30 / 2) / 2 - t45 / t6 / t5 * t41 / 4 + t26 * t41 + t34 * t31 * (t28 * t26 * t30 / 2 + t34 * t31 * t51 / 2) / 2 - t63 / t24 / t23 * t59 / 4 + t31 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_1( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t28  = 2 * t3;
    real_type t30  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t31  = 1.0 / t24;
    real_type t34  = -2 * t21;
    real_type t39  = 2 * t1;
    real_type t42  = areaQ_D_1(t6, t12, t18, t24);
    real_type t51  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t58  = -2 * t19;
    real_type t61  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t39 * t26 * (t28 * t26 * t25 / 2 + t34 * t31 * t30 / 2) / 2 - t28 * t39 / t6 / t5 * t42 / 4 + t58 * t31 * (t28 * t26 * t30 / 2 + t34 * t31 * t51 / 2) / 2 - t34 * t58 / t24 / t23 * t61 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t1;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t7;
    real_type t39  = -t29;
    real_type t42  = areaQ_D_1(t6, t12, t18, t24);
    real_type t50  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t53  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = t39 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t39 / t6 / t5 * t42 / 4 - t26 * t42 - t19 / t24 * (t29 * t26 * t50 / 2 + t34 * t32 * t53 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t3;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t9;
    real_type t39  = 2 * t1;
    real_type t42  = areaQ_D_1(t6, t12, t18, t24);
    real_type t49  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t52  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = t39 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t39 / t6 / t5 * t42 / 4 - t19 / t24 * (t29 * t26 * t49 / 2 + t34 * t32 * t52 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t7;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t13;
    real_type t42  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t45  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type result__ = t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) - t19 / t24 * (t29 * t26 * t42 / 2 + t34 * t32 * t45 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t9;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t15;
    real_type t42  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t45  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type result__ = t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) - t19 / t24 * (t29 * t26 * t42 / 2 + t34 * t32 * t45 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t43  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t46  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t52  = -t34;
    real_type t55  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t52 * t32 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2) / 2 - t34 * t52 / t24 / t23 * t55 / 4 - t32 * t55;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_1_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t43  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t46  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t53  = -2 * t19;
    real_type t56  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t32 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2) / 2 - t34 * t53 / t24 / t23 * t56 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_1_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1(t6, t12, t18, t24);
    real_type t30  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t3 / t6 * t25 - t21 / t24 * t30;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_2( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t28  = 2 * t3;
    real_type t30  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t31  = 1.0 / t24;
    real_type t34  = -2 * t21;
    real_type t41  = areaQ_D_1(t6, t12, t18, t24);
    real_type t45  = t28 * t28;
    real_type t51  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t59  = areaQ_D_4(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t28 * t26 * (t28 * t26 * t25 / 2 + t34 * t31 * t30 / 2) / 2 - t45 / t6 / t5 * t41 / 4 + t26 * t41 + t34 * t31 * (t28 * t26 * t30 / 2 + t34 * t31 * t51 / 2) / 2 - t63 / t24 / t23 * t59 / 4 + t31 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_2( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t1;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t7;
    real_type t39  = 2 * t3;
    real_type t42  = areaQ_D_1(t6, t12, t18, t24);
    real_type t49  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t52  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = t39 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t39 / t6 / t5 * t42 / 4 - t21 / t24 * (t29 * t26 * t49 / 2 + t34 * t32 * t52 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t3;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t9;
    real_type t39  = -t29;
    real_type t42  = areaQ_D_1(t6, t12, t18, t24);
    real_type t50  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t53  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = t39 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t39 / t6 / t5 * t42 / 4 - t26 * t42 - t21 / t24 * (t29 * t26 * t50 / 2 + t34 * t32 * t53 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t7;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t13;
    real_type t42  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t45  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type result__ = t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) - t21 / t24 * (t29 * t26 * t42 / 2 + t34 * t32 * t45 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t9;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t15;
    real_type t42  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t45  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type result__ = t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) - t21 / t24 * (t29 * t26 * t42 / 2 + t34 * t32 * t45 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t43  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t46  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t53  = -2 * t21;
    real_type t56  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t32 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2) / 2 - t34 * t53 / t24 / t23 * t56 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_2_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t43  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t46  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t52  = -t34;
    real_type t55  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t52 * t32 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2) / 2 - t34 * t52 / t24 / t23 * t55 / 4 - t32 * t55;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_2_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1(t6, t12, t18, t24);
    real_type t31  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = -t1 / t6 * t25 + t7 / t12 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3_3( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t1;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t7;
    real_type t41  = areaQ_D_1(t6, t12, t18, t24);
    real_type t45  = t29 * t29;
    real_type t51  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t59  = areaQ_D_2(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t29 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t45 / t6 / t5 * t41 / 4 + t26 * t41 + t34 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t51 / 2) / 2 - t63 / t12 / t11 * t59 / 4 + t32 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3_3( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t3;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t9;
    real_type t40  = -2 * t1;
    real_type t43  = areaQ_D_1(t6, t12, t18, t24);
    real_type t52  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t58  = 2 * t7;
    real_type t61  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = t40 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t40 / t6 / t5 * t43 / 4 + t58 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t52 / 2) / 2 - t34 * t58 / t12 / t11 * t61 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t7;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t13;
    real_type t44  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t47  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t53  = -t29;
    real_type t56  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = -t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t12 / t11 * t56 / 4 - t26 * t56;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t9;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t15;
    real_type t44  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t47  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t53  = 2 * t7;
    real_type t56  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = -t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t12 / t11 * t56 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t43  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t46  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = -t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t7 / t12 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_3_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t1   = xo__p1x - xo__p2x;
    real_type t2   = t1 * t1;
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t43  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t46  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = -t1 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t7 / t12 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_3_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1(t6, t12, t18, t24);
    real_type t31  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = -t3 / t6 * t25 + t9 / t12 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_4_4( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t5   = t2 + t4;
    real_type t6   = sqrt(t5);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_1(t6, t12, t18, t24);
    real_type t26  = 1.0 / t6;
    real_type t29  = -2 * t3;
    real_type t31  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t32  = 1.0 / t12;
    real_type t34  = 2 * t9;
    real_type t41  = areaQ_D_1(t6, t12, t18, t24);
    real_type t45  = t29 * t29;
    real_type t51  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t59  = areaQ_D_2(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t29 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t45 / t6 / t5 * t41 / 4 + t26 * t41 + t34 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t51 / 2) / 2 - t63 / t12 / t11 * t59 / 4 + t32 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_4_4( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_4_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t7;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t13;
    real_type t44  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t47  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t53  = 2 * t9;
    real_type t56  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = -t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t12 / t11 * t56 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_4_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_4_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t9;
    real_type t31  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t15;
    real_type t44  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t47  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t53  = -t29;
    real_type t56  = areaQ_D_2(t6, t12, t18, t24);
    real_type result__ = -t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t12 / t11 * t56 / 4 - t26 * t56;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_4_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_4_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t43  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t46  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = -t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t9 / t12 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_4_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_4_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t3   = xo__p1y - xo__p2y;
    real_type t4   = t3 * t3;
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_1_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_1_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t43  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t46  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type result__ = -t3 / t6 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t9 / t12 * (t29 * t26 * t43 / 2 + t34 * t32 * t46 / 2);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_4_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2(t6, t12, t18, t24);
    real_type t31  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = -t7 / t12 * t25 + t13 / t18 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_5_5( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t7;
    real_type t31  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t13;
    real_type t41  = areaQ_D_2(t6, t12, t18, t24);
    real_type t45  = t29 * t29;
    real_type t51  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t59  = areaQ_D_3(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t29 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t45 / t12 / t11 * t41 / 4 + t26 * t41 + t34 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t51 / 2) / 2 - t63 / t18 / t17 * t59 / 4 + t32 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_5_5( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_5_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t9;
    real_type t31  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t15;
    real_type t40  = -2 * t7;
    real_type t43  = areaQ_D_2(t6, t12, t18, t24);
    real_type t52  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t58  = 2 * t13;
    real_type t61  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = t40 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t40 / t12 / t11 * t43 / 4 + t58 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t52 / 2) / 2 - t34 * t58 / t18 / t17 * t61 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_5_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_5_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t44  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t47  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t53  = -t29;
    real_type t56  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = -t7 / t12 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t18 / t17 * t56 / 4 - t26 * t56;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_5_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_5_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t7   = xo__p2x - xo__p3x;
    real_type t8   = t7 * t7;
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t44  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t47  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t53  = 2 * t13;
    real_type t56  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = -t7 / t12 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t18 / t17 * t56 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_5_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2(t6, t12, t18, t24);
    real_type t31  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = -t9 / t12 * t25 + t15 / t18 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_6_6( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t11  = t8 + t10;
    real_type t12  = sqrt(t11);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_2(t6, t12, t18, t24);
    real_type t26  = 1.0 / t12;
    real_type t29  = -2 * t9;
    real_type t31  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t32  = 1.0 / t18;
    real_type t34  = 2 * t15;
    real_type t41  = areaQ_D_2(t6, t12, t18, t24);
    real_type t45  = t29 * t29;
    real_type t51  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t59  = areaQ_D_3(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t29 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t45 / t12 / t11 * t41 / 4 + t26 * t41 + t34 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t51 / 2) / 2 - t63 / t18 / t17 * t59 / 4 + t32 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_6_6( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_6_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t44  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t47  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t53  = 2 * t15;
    real_type t56  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = -t9 / t12 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t18 / t17 * t56 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_6_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_6_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t9   = xo__p2y - xo__p3y;
    real_type t10  = t9 * t9;
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_2_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_2_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t44  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t47  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t53  = -t29;
    real_type t56  = areaQ_D_3(t6, t12, t18, t24);
    real_type result__ = -t9 / t12 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) + t53 * t26 * (t29 * t26 * t44 / 2 + t34 * t32 * t47 / 2) / 2 - t29 * t53 / t18 / t17 * t56 / 4 - t26 * t56;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_6_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t18  = sqrt(t14 + t16);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_3(t6, t12, t18, t24);
    real_type t31  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = -t13 / t18 * t25 + t19 / t24 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_7_7( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t16  = pow(xo__p3y - xo__p4y, 2);
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t22  = pow(xo__p4y - xo__p1y, 2);
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t13;
    real_type t31  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t19;
    real_type t41  = areaQ_D_3(t6, t12, t18, t24);
    real_type t45  = t29 * t29;
    real_type t51  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t59  = areaQ_D_4(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t29 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t45 / t18 / t17 * t41 / 4 + t26 * t41 + t34 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t51 / 2) / 2 - t63 / t24 / t23 * t59 / 4 + t32 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_7_7( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_7_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t13  = xo__p3x - xo__p4x;
    real_type t14  = t13 * t13;
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t19  = xo__p4x - xo__p1x;
    real_type t20  = t19 * t19;
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t40  = -2 * t13;
    real_type t43  = areaQ_D_3(t6, t12, t18, t24);
    real_type t52  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t58  = 2 * t19;
    real_type t61  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = t40 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t29 * t40 / t18 / t17 * t43 / 4 + t58 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t52 / 2) / 2 - t34 * t58 / t24 / t23 * t61 / 4;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_7_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t18  = sqrt(t14 + t16);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t24  = sqrt(t20 + t22);
    real_type t25  = areaQ_D_3(t6, t12, t18, t24);
    real_type t31  = areaQ_D_4(t6, t12, t18, t24);
    real_type result__ = -t15 / t18 * t25 + t21 / t24 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::areaQ2_D_8_8( real_type xo__p1x, real_type xo__p1y, real_type xo__p2x, real_type xo__p2y, real_type xo__p3x, real_type xo__p3y, real_type xo__p4x, real_type xo__p4y ) const {
    real_type t2   = pow(xo__p1x - xo__p2x, 2);
    real_type t4   = pow(xo__p1y - xo__p2y, 2);
    real_type t6   = sqrt(t2 + t4);
    real_type t8   = pow(xo__p2x - xo__p3x, 2);
    real_type t10  = pow(xo__p2y - xo__p3y, 2);
    real_type t12  = sqrt(t8 + t10);
    real_type t14  = pow(xo__p3x - xo__p4x, 2);
    real_type t15  = xo__p3y - xo__p4y;
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t18  = sqrt(t17);
    real_type t20  = pow(xo__p4x - xo__p1x, 2);
    real_type t21  = xo__p4y - xo__p1y;
    real_type t22  = t21 * t21;
    real_type t23  = t20 + t22;
    real_type t24  = sqrt(t23);
    real_type t25  = areaQ_D_3_3(t6, t12, t18, t24);
    real_type t26  = 1.0 / t18;
    real_type t29  = -2 * t15;
    real_type t31  = areaQ_D_3_4(t6, t12, t18, t24);
    real_type t32  = 1.0 / t24;
    real_type t34  = 2 * t21;
    real_type t41  = areaQ_D_3(t6, t12, t18, t24);
    real_type t45  = t29 * t29;
    real_type t51  = areaQ_D_4_4(t6, t12, t18, t24);
    real_type t59  = areaQ_D_4(t6, t12, t18, t24);
    real_type t63  = t34 * t34;
    real_type result__ = t29 * t26 * (t29 * t26 * t25 / 2 + t34 * t32 * t31 / 2) / 2 - t45 / t18 / t17 * t41 / 4 + t26 * t41 + t34 * t32 * (t29 * t26 * t31 / 2 + t34 * t32 * t51 / 2) / 2 - t63 / t24 / t23 * t59 / 4 + t32 * t59;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_areaQ2_D_8_8( p1x={}, p1y={}, p2x={}, p2y={}, p3x={}, p3y={}, p4x={}, p4y={} ) return {}\n",
        xo__p1x, xo__p1y, xo__p2x, xo__p2y, xo__p3x, xo__p3y, xo__p4x, xo__p4y, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Ax_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Ay_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Bx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = By_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Ax_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Ay_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Bx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = By_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = By_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Ax_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Ay_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Bx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = By_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = By_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Ax_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Ay_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Bx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = By_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Ax_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Ay_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Bx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = By_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = By_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AEB_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Ax_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Ay_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Bx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = By_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AEB_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Bx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = By_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Cx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Cy_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Bx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = By_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Cx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Cy_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Bx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = By_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Cx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Cy_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Bx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = By_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Cx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Cy_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Bx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = By_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Cx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Cy_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BEC_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Bx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = By_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Cx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Cy_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BEC_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Cx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Cy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Dx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Dy_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Cx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Cy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Dx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Dy_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Cx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Cy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Dx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Dy_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Cx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Cy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Dx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Dy_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Cx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Cy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Dx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Dy_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::CED_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Cx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Cy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Dx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Dy_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_CED_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Dx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Dy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Ax_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Ay_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Dx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Dy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Ax_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Ay_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Dx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Dy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Ax_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Ay_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t8 * t10 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t8 * t13 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t8 * t16 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t8 * t19 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t8 * t22 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Dx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Dy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Ax_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Ay_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Dx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Dy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ex_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Ey_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Ey_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Ax_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Ay_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DEA_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ex(xo__x, xo__y, xo__theta);
    real_type t4   = Ey(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ex_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Ey_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Dx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Dy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ex_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Ey_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Ax_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Ay_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DEA_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Ax_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Ay_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Bx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = By_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Ax_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Ay_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Bx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = By_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = By_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Ax_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Ay_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Bx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = By_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = By_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Ax_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Ay_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Bx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = By_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Ax_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Ay_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Bx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = By_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = By_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::AOB_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Bx(xo__x, xo__y, xo__theta);
    real_type t6   = By(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Ax_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Ay_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Bx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = By_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_AOB_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Bx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = By_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Cx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Cy_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Bx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = By_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Cx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Cy_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Bx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = By_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Cx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Cy_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Bx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = By_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Cx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Cy_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Bx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = By_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Cx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Cy_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::BOC_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Bx(xo__x, xo__y, xo__theta);
    real_type t2   = By(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Bx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = By_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Cx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Cy_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_BOC_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Cx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Cy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Dx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Dy_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Cx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Cy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Dx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Dy_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Cx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Cy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Dx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Dy_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Cx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Cy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Dx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Dy_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Cx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Cy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Dx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Dy_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::COD_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Cx(xo__x, xo__y, xo__theta);
    real_type t2   = Cy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Dx(xo__x, xo__y, xo__theta);
    real_type t6   = Dy(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Cx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Cy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Dx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Dy_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_COD_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type result__ = area2(t1, t2, t3, t4, t5, t6);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Dx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Dy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1_1(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Ax_D_1_1(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Ay_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t26  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Dx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Dy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_2(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Ax_D_1_2(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Ay_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Dx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Dy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_1(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_1_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_1(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Ax_D_1_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Ay_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Dx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Dy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2_2(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Ax_D_2_2(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Ay_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t10 * t8 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t13 * t8 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t16 * t8 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t19 * t8 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t22 * t8 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t26  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t28  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t29  = Dx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t32  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t34  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t36  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t38  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t40  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t45  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t46  = Dy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t50  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t56  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_2(xo__x, xo__y, xo__theta);
    real_type t61  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t62  = Ox_D_2_3(xo__x, xo__y, xo__theta);
    real_type t67  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t69  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t71  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t74  = Oy_D_2(xo__x, xo__y, xo__theta);
    real_type t76  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t77  = Oy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t88  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t90  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t91  = Ax_D_2_3(xo__x, xo__y, xo__theta);
    real_type t98  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t101 = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t103 = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t104 = Ay_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t26 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t29 * t28 + t43 * (t10 * t8 + t11 * t32 + t14 * t34 + t17 * t36 + t20 * t38 + t23 * t40) + t46 * t45 + t59 * (t11 * t34 + t13 * t8 + t14 * t50 + t17 * t52 + t20 * t54 + t23 * t56) + t62 * t61 + t74 * (t11 * t36 + t14 * t52 + t16 * t8 + t17 * t67 + t20 * t69 + t23 * t71) + t77 * t76 + t88 * (t11 * t38 + t14 * t54 + t17 * t69 + t19 * t8 + t20 * t83 + t23 * t85) + t91 * t90 + t101 * (t11 * t40 + t14 * t56 + t17 * t71 + t20 * t85 + t22 * t8 + t23 * t98) + t104 * t103;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::DOA_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Dx(xo__x, xo__y, xo__theta);
    real_type t2   = Dy(xo__x, xo__y, xo__theta);
    real_type t3   = Ox(xo__x, xo__y, xo__theta);
    real_type t4   = Oy(xo__x, xo__y, xo__theta);
    real_type t5   = Ax(xo__x, xo__y, xo__theta);
    real_type t6   = Ay(xo__x, xo__y, xo__theta);
    real_type t7   = area2_D_1_1(t1, t2, t3, t4, t5, t6);
    real_type t8   = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t10  = area2_D_1_2(t1, t2, t3, t4, t5, t6);
    real_type t11  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t13  = area2_D_1_3(t1, t2, t3, t4, t5, t6);
    real_type t14  = Ox_D_3(xo__x, xo__y, xo__theta);
    real_type t16  = area2_D_1_4(t1, t2, t3, t4, t5, t6);
    real_type t17  = Oy_D_3(xo__x, xo__y, xo__theta);
    real_type t19  = area2_D_1_5(t1, t2, t3, t4, t5, t6);
    real_type t20  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t22  = area2_D_1_6(t1, t2, t3, t4, t5, t6);
    real_type t23  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = area2_D_1(t1, t2, t3, t4, t5, t6);
    real_type t28  = Dx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t31  = area2_D_2_2(t1, t2, t3, t4, t5, t6);
    real_type t33  = area2_D_2_3(t1, t2, t3, t4, t5, t6);
    real_type t35  = area2_D_2_4(t1, t2, t3, t4, t5, t6);
    real_type t37  = area2_D_2_5(t1, t2, t3, t4, t5, t6);
    real_type t39  = area2_D_2_6(t1, t2, t3, t4, t5, t6);
    real_type t43  = area2_D_2(t1, t2, t3, t4, t5, t6);
    real_type t44  = Dy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t48  = area2_D_3_3(t1, t2, t3, t4, t5, t6);
    real_type t50  = area2_D_3_4(t1, t2, t3, t4, t5, t6);
    real_type t52  = area2_D_3_5(t1, t2, t3, t4, t5, t6);
    real_type t54  = area2_D_3_6(t1, t2, t3, t4, t5, t6);
    real_type t58  = area2_D_3(t1, t2, t3, t4, t5, t6);
    real_type t59  = Ox_D_3_3(xo__x, xo__y, xo__theta);
    real_type t64  = area2_D_4_4(t1, t2, t3, t4, t5, t6);
    real_type t66  = area2_D_4_5(t1, t2, t3, t4, t5, t6);
    real_type t68  = area2_D_4_6(t1, t2, t3, t4, t5, t6);
    real_type t72  = area2_D_4(t1, t2, t3, t4, t5, t6);
    real_type t73  = Oy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t79  = area2_D_5_5(t1, t2, t3, t4, t5, t6);
    real_type t81  = area2_D_5_6(t1, t2, t3, t4, t5, t6);
    real_type t85  = area2_D_5(t1, t2, t3, t4, t5, t6);
    real_type t86  = Ax_D_3_3(xo__x, xo__y, xo__theta);
    real_type t93  = area2_D_6_6(t1, t2, t3, t4, t5, t6);
    real_type t97  = area2_D_6(t1, t2, t3, t4, t5, t6);
    real_type t98  = Ay_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t8 * (t10 * t11 + t13 * t14 + t16 * t17 + t19 * t20 + t22 * t23 + t7 * t8) + t28 * t27 + t11 * (t8 * t10 + t11 * t31 + t14 * t33 + t17 * t35 + t20 * t37 + t23 * t39) + t44 * t43 + t14 * (t11 * t33 + t8 * t13 + t14 * t48 + t17 * t50 + t20 * t52 + t23 * t54) + t59 * t58 + t17 * (t11 * t35 + t14 * t50 + t8 * t16 + t17 * t64 + t20 * t66 + t23 * t68) + t73 * t72 + t20 * (t11 * t37 + t14 * t52 + t17 * t66 + t8 * t19 + t20 * t79 + t23 * t81) + t86 * t85 + t23 * (t11 * t39 + t14 * t54 + t17 * t68 + t20 * t81 + t8 * t22 + t23 * t93) + t98 * t97;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_DOA_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type result__ = areaQ2(t1, t2, t3, t4, t5, t6, t7, t8);
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_1_1( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_1_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_1_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_1_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_1_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_1_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_1_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_1_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t35  = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t36  = Ax_D_1_1(xo__x, xo__y, xo__theta);
    real_type t39  = areaQ2_D_2_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t41  = areaQ2_D_2_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = areaQ2_D_2_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = areaQ2_D_2_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t47  = areaQ2_D_2_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = areaQ2_D_2_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = areaQ2_D_2_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t56  = Ay_D_1_1(xo__x, xo__y, xo__theta);
    real_type t60  = areaQ2_D_3_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t62  = areaQ2_D_3_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t64  = areaQ2_D_3_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t66  = areaQ2_D_3_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t68  = areaQ2_D_3_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t70  = areaQ2_D_3_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t74  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = Bx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t80  = areaQ2_D_4_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t82  = areaQ2_D_4_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t84  = areaQ2_D_4_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t86  = areaQ2_D_4_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t88  = areaQ2_D_4_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t92  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = By_D_1_1(xo__x, xo__y, xo__theta);
    real_type t99  = areaQ2_D_5_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t101 = areaQ2_D_5_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t103 = areaQ2_D_5_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = areaQ2_D_5_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t110 = Cx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t117 = areaQ2_D_6_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t119 = areaQ2_D_6_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t121 = areaQ2_D_6_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t125 = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t126 = Cy_D_1_1(xo__x, xo__y, xo__theta);
    real_type t134 = areaQ2_D_7_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t136 = areaQ2_D_7_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t140 = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t141 = Dx_D_1_1(xo__x, xo__y, xo__theta);
    real_type t150 = areaQ2_D_8_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t154 = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t155 = Dy_D_1_1(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * (t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30) + t36 * t35 + t13 * (t10 * t12 + t13 * t39 + t16 * t41 + t19 * t43 + t22 * t45 + t25 * t47 + t28 * t49 + t31 * t51) + t56 * t55 + t16 * (t10 * t15 + t13 * t41 + t16 * t60 + t19 * t62 + t22 * t64 + t25 * t66 + t28 * t68 + t31 * t70) + t75 * t74 + t19 * (t10 * t18 + t13 * t43 + t16 * t62 + t19 * t80 + t22 * t82 + t25 * t84 + t28 * t86 + t31 * t88) + t93 * t92 + t22 * (t10 * t21 + t25 * t101 + t28 * t103 + t31 * t105 + t13 * t45 + t16 * t64 + t19 * t82 + t22 * t99) + t110 * t109 + t25 * (t10 * t24 + t22 * t101 + t25 * t117 + t28 * t119 + t31 * t121 + t13 * t47 + t16 * t66 + t19 * t84) + t126 * t125 + t28 * (t10 * t27 + t22 * t103 + t25 * t119 + t13 * t49 + t28 * t134 + t31 * t136 + t16 * t68 + t19 * t86) + t141 * t140 + t31 * (t10 * t30 + t22 * t105 + t25 * t121 + t13 * t51 + t28 * t136 + t31 * t150 + t16 * t70 + t19 * t88) + t155 * t154;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_1_1( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_1_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_1_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_1_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_1_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_1_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_1_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_1_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_1_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t34  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t36  = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = Ax_D_1_2(xo__x, xo__y, xo__theta);
    real_type t40  = areaQ2_D_2_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t42  = areaQ2_D_2_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t44  = areaQ2_D_2_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t46  = areaQ2_D_2_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t48  = areaQ2_D_2_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t50  = areaQ2_D_2_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t52  = areaQ2_D_2_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t57  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t58  = Ay_D_1_2(xo__x, xo__y, xo__theta);
    real_type t62  = areaQ2_D_3_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t64  = areaQ2_D_3_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t66  = areaQ2_D_3_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t68  = areaQ2_D_3_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t70  = areaQ2_D_3_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t72  = areaQ2_D_3_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t77  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t78  = Bx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t83  = areaQ2_D_4_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = areaQ2_D_4_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = areaQ2_D_4_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t89  = areaQ2_D_4_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = areaQ2_D_4_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t94  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t96  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = By_D_1_2(xo__x, xo__y, xo__theta);
    real_type t103 = areaQ2_D_5_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = areaQ2_D_5_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t107 = areaQ2_D_5_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = areaQ2_D_5_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t112 = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t114 = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t115 = Cx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t122 = areaQ2_D_6_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t124 = areaQ2_D_6_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t126 = areaQ2_D_6_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t131 = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t132 = Cy_D_1_2(xo__x, xo__y, xo__theta);
    real_type t140 = areaQ2_D_7_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t142 = areaQ2_D_7_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t145 = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t147 = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t148 = Dx_D_1_2(xo__x, xo__y, xo__theta);
    real_type t157 = areaQ2_D_8_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t160 = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t162 = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t163 = Dy_D_1_2(xo__x, xo__y, xo__theta);
    real_type result__ = t34 * (t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30) + t37 * t36 + t55 * (t10 * t12 + t13 * t40 + t16 * t42 + t19 * t44 + t22 * t46 + t25 * t48 + t28 * t50 + t31 * t52) + t58 * t57 + t75 * (t10 * t15 + t13 * t42 + t16 * t62 + t19 * t64 + t22 * t66 + t25 * t68 + t28 * t70 + t31 * t72) + t78 * t77 + t94 * (t10 * t18 + t13 * t44 + t16 * t64 + t19 * t83 + t22 * t85 + t25 * t87 + t28 * t89 + t31 * t91) + t97 * t96 + t112 * (t10 * t21 + t22 * t103 + t25 * t105 + t28 * t107 + t31 * t109 + t13 * t46 + t16 * t66 + t19 * t85) + t115 * t114 + t129 * (t10 * t24 + t22 * t105 + t25 * t122 + t28 * t124 + t31 * t126 + t13 * t48 + t16 * t68 + t19 * t87) + t132 * t131 + t145 * (t10 * t27 + t22 * t107 + t25 * t124 + t13 * t50 + t28 * t140 + t31 * t142 + t16 * t70 + t19 * t89) + t148 * t147 + t160 * (t10 * t30 + t22 * t109 + t25 * t126 + t13 * t52 + t28 * t142 + t31 * t157 + t16 * t72 + t19 * t91) + t163 * t162;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_1_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_1_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_1_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_1_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_1_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_1_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_1_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_1_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_1_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t34  = Ax_D_1(xo__x, xo__y, xo__theta);
    real_type t36  = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = Ax_D_1_3(xo__x, xo__y, xo__theta);
    real_type t40  = areaQ2_D_2_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t42  = areaQ2_D_2_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t44  = areaQ2_D_2_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t46  = areaQ2_D_2_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t48  = areaQ2_D_2_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t50  = areaQ2_D_2_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t52  = areaQ2_D_2_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = Ay_D_1(xo__x, xo__y, xo__theta);
    real_type t57  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t58  = Ay_D_1_3(xo__x, xo__y, xo__theta);
    real_type t62  = areaQ2_D_3_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t64  = areaQ2_D_3_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t66  = areaQ2_D_3_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t68  = areaQ2_D_3_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t70  = areaQ2_D_3_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t72  = areaQ2_D_3_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = Bx_D_1(xo__x, xo__y, xo__theta);
    real_type t77  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t78  = Bx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t83  = areaQ2_D_4_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = areaQ2_D_4_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = areaQ2_D_4_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t89  = areaQ2_D_4_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = areaQ2_D_4_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t94  = By_D_1(xo__x, xo__y, xo__theta);
    real_type t96  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = By_D_1_3(xo__x, xo__y, xo__theta);
    real_type t103 = areaQ2_D_5_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = areaQ2_D_5_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t107 = areaQ2_D_5_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = areaQ2_D_5_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t112 = Cx_D_1(xo__x, xo__y, xo__theta);
    real_type t114 = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t115 = Cx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t122 = areaQ2_D_6_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t124 = areaQ2_D_6_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t126 = areaQ2_D_6_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = Cy_D_1(xo__x, xo__y, xo__theta);
    real_type t131 = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t132 = Cy_D_1_3(xo__x, xo__y, xo__theta);
    real_type t140 = areaQ2_D_7_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t142 = areaQ2_D_7_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t145 = Dx_D_1(xo__x, xo__y, xo__theta);
    real_type t147 = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t148 = Dx_D_1_3(xo__x, xo__y, xo__theta);
    real_type t157 = areaQ2_D_8_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t160 = Dy_D_1(xo__x, xo__y, xo__theta);
    real_type t162 = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t163 = Dy_D_1_3(xo__x, xo__y, xo__theta);
    real_type result__ = t34 * (t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30) + t37 * t36 + t55 * (t10 * t12 + t13 * t40 + t16 * t42 + t19 * t44 + t22 * t46 + t25 * t48 + t28 * t50 + t31 * t52) + t58 * t57 + t75 * (t10 * t15 + t13 * t42 + t16 * t62 + t19 * t64 + t22 * t66 + t25 * t68 + t28 * t70 + t31 * t72) + t78 * t77 + t94 * (t10 * t18 + t13 * t44 + t16 * t64 + t19 * t83 + t22 * t85 + t25 * t87 + t28 * t89 + t31 * t91) + t97 * t96 + t112 * (t10 * t21 + t22 * t103 + t25 * t105 + t28 * t107 + t31 * t109 + t13 * t46 + t16 * t66 + t19 * t85) + t115 * t114 + t129 * (t10 * t24 + t22 * t105 + t25 * t122 + t28 * t124 + t31 * t126 + t13 * t48 + t16 * t68 + t19 * t87) + t132 * t131 + t145 * (t10 * t27 + t22 * t107 + t25 * t124 + t13 * t50 + t28 * t140 + t31 * t142 + t16 * t70 + t19 * t89) + t148 * t147 + t160 * (t10 * t30 + t22 * t109 + t25 * t126 + t13 * t52 + t28 * t142 + t31 * t157 + t16 * t72 + t19 * t91) + t163 * t162;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_1_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_2_2( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_1_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_1_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_1_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_1_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_1_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_1_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_1_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t35  = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t36  = Ax_D_2_2(xo__x, xo__y, xo__theta);
    real_type t39  = areaQ2_D_2_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t41  = areaQ2_D_2_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = areaQ2_D_2_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = areaQ2_D_2_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t47  = areaQ2_D_2_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = areaQ2_D_2_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = areaQ2_D_2_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t56  = Ay_D_2_2(xo__x, xo__y, xo__theta);
    real_type t60  = areaQ2_D_3_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t62  = areaQ2_D_3_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t64  = areaQ2_D_3_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t66  = areaQ2_D_3_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t68  = areaQ2_D_3_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t70  = areaQ2_D_3_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t74  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = Bx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t80  = areaQ2_D_4_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t82  = areaQ2_D_4_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t84  = areaQ2_D_4_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t86  = areaQ2_D_4_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t88  = areaQ2_D_4_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t92  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = By_D_2_2(xo__x, xo__y, xo__theta);
    real_type t99  = areaQ2_D_5_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t101 = areaQ2_D_5_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t103 = areaQ2_D_5_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = areaQ2_D_5_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t110 = Cx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t117 = areaQ2_D_6_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t119 = areaQ2_D_6_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t121 = areaQ2_D_6_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t125 = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t126 = Cy_D_2_2(xo__x, xo__y, xo__theta);
    real_type t134 = areaQ2_D_7_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t136 = areaQ2_D_7_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t140 = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t141 = Dx_D_2_2(xo__x, xo__y, xo__theta);
    real_type t150 = areaQ2_D_8_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t154 = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t155 = Dy_D_2_2(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * (t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30) + t36 * t35 + t13 * (t10 * t12 + t13 * t39 + t16 * t41 + t19 * t43 + t22 * t45 + t25 * t47 + t28 * t49 + t31 * t51) + t56 * t55 + t16 * (t10 * t15 + t13 * t41 + t16 * t60 + t19 * t62 + t22 * t64 + t25 * t66 + t28 * t68 + t31 * t70) + t75 * t74 + t19 * (t10 * t18 + t13 * t43 + t16 * t62 + t19 * t80 + t22 * t82 + t25 * t84 + t28 * t86 + t31 * t88) + t93 * t92 + t22 * (t10 * t21 + t25 * t101 + t28 * t103 + t31 * t105 + t13 * t45 + t16 * t64 + t19 * t82 + t22 * t99) + t110 * t109 + t25 * (t10 * t24 + t22 * t101 + t25 * t117 + t28 * t119 + t31 * t121 + t13 * t47 + t16 * t66 + t19 * t84) + t126 * t125 + t28 * (t10 * t27 + t22 * t103 + t25 * t119 + t13 * t49 + t28 * t134 + t31 * t136 + t16 * t68 + t19 * t86) + t141 * t140 + t31 * (t10 * t30 + t22 * t105 + t25 * t121 + t13 * t51 + t28 * t136 + t31 * t150 + t16 * t70 + t19 * t88) + t155 * t154;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_2_2( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_2_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_1_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_1_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_1_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_1_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_1_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_1_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_1_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t34  = Ax_D_2(xo__x, xo__y, xo__theta);
    real_type t36  = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t37  = Ax_D_2_3(xo__x, xo__y, xo__theta);
    real_type t40  = areaQ2_D_2_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t42  = areaQ2_D_2_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t44  = areaQ2_D_2_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t46  = areaQ2_D_2_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t48  = areaQ2_D_2_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t50  = areaQ2_D_2_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t52  = areaQ2_D_2_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = Ay_D_2(xo__x, xo__y, xo__theta);
    real_type t57  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t58  = Ay_D_2_3(xo__x, xo__y, xo__theta);
    real_type t62  = areaQ2_D_3_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t64  = areaQ2_D_3_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t66  = areaQ2_D_3_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t68  = areaQ2_D_3_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t70  = areaQ2_D_3_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t72  = areaQ2_D_3_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = Bx_D_2(xo__x, xo__y, xo__theta);
    real_type t77  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t78  = Bx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t83  = areaQ2_D_4_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t85  = areaQ2_D_4_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t87  = areaQ2_D_4_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t89  = areaQ2_D_4_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t91  = areaQ2_D_4_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t94  = By_D_2(xo__x, xo__y, xo__theta);
    real_type t96  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t97  = By_D_2_3(xo__x, xo__y, xo__theta);
    real_type t103 = areaQ2_D_5_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = areaQ2_D_5_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t107 = areaQ2_D_5_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = areaQ2_D_5_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t112 = Cx_D_2(xo__x, xo__y, xo__theta);
    real_type t114 = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t115 = Cx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t122 = areaQ2_D_6_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t124 = areaQ2_D_6_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t126 = areaQ2_D_6_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t129 = Cy_D_2(xo__x, xo__y, xo__theta);
    real_type t131 = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t132 = Cy_D_2_3(xo__x, xo__y, xo__theta);
    real_type t140 = areaQ2_D_7_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t142 = areaQ2_D_7_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t145 = Dx_D_2(xo__x, xo__y, xo__theta);
    real_type t147 = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t148 = Dx_D_2_3(xo__x, xo__y, xo__theta);
    real_type t157 = areaQ2_D_8_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t160 = Dy_D_2(xo__x, xo__y, xo__theta);
    real_type t162 = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t163 = Dy_D_2_3(xo__x, xo__y, xo__theta);
    real_type result__ = t34 * (t10 * t9 + t13 * t12 + t16 * t15 + t19 * t18 + t22 * t21 + t25 * t24 + t28 * t27 + t31 * t30) + t37 * t36 + t55 * (t10 * t12 + t13 * t40 + t16 * t42 + t19 * t44 + t22 * t46 + t25 * t48 + t28 * t50 + t31 * t52) + t58 * t57 + t75 * (t10 * t15 + t13 * t42 + t16 * t62 + t19 * t64 + t22 * t66 + t25 * t68 + t28 * t70 + t31 * t72) + t78 * t77 + t94 * (t10 * t18 + t13 * t44 + t16 * t64 + t19 * t83 + t22 * t85 + t25 * t87 + t28 * t89 + t31 * t91) + t97 * t96 + t112 * (t10 * t21 + t22 * t103 + t25 * t105 + t28 * t107 + t31 * t109 + t13 * t46 + t16 * t66 + t19 * t85) + t115 * t114 + t129 * (t10 * t24 + t22 * t105 + t25 * t122 + t28 * t124 + t31 * t126 + t13 * t48 + t16 * t68 + t19 * t87) + t132 * t131 + t145 * (t10 * t27 + t22 * t107 + t25 * t124 + t13 * t50 + t28 * t140 + t31 * t142 + t16 * t70 + t19 * t89) + t148 * t147 + t160 * (t10 * t30 + t22 * t109 + t25 * t126 + t13 * t52 + t28 * t142 + t31 * t157 + t16 * t72 + t19 * t91) + t163 * t162;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_2_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * t9 + t12 * t13 + t15 * t16 + t18 * t19 + t21 * t22 + t24 * t25 + t27 * t28 + t30 * t31;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

  real_type
  ICLOCS_ParallelParking::ABCD_D_3_3( real_type xo__x, real_type xo__y, real_type xo__theta ) const {
    real_type t1   = Ax(xo__x, xo__y, xo__theta);
    real_type t2   = Ay(xo__x, xo__y, xo__theta);
    real_type t3   = Bx(xo__x, xo__y, xo__theta);
    real_type t4   = By(xo__x, xo__y, xo__theta);
    real_type t5   = Cx(xo__x, xo__y, xo__theta);
    real_type t6   = Cy(xo__x, xo__y, xo__theta);
    real_type t7   = Dx(xo__x, xo__y, xo__theta);
    real_type t8   = Dy(xo__x, xo__y, xo__theta);
    real_type t9   = areaQ2_D_1_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t10  = Ax_D_3(xo__x, xo__y, xo__theta);
    real_type t12  = areaQ2_D_1_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t13  = Ay_D_3(xo__x, xo__y, xo__theta);
    real_type t15  = areaQ2_D_1_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t16  = Bx_D_3(xo__x, xo__y, xo__theta);
    real_type t18  = areaQ2_D_1_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t19  = By_D_3(xo__x, xo__y, xo__theta);
    real_type t21  = areaQ2_D_1_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t22  = Cx_D_3(xo__x, xo__y, xo__theta);
    real_type t24  = areaQ2_D_1_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t25  = Cy_D_3(xo__x, xo__y, xo__theta);
    real_type t27  = areaQ2_D_1_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t28  = Dx_D_3(xo__x, xo__y, xo__theta);
    real_type t30  = areaQ2_D_1_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t31  = Dy_D_3(xo__x, xo__y, xo__theta);
    real_type t35  = areaQ2_D_1(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t36  = Ax_D_3_3(xo__x, xo__y, xo__theta);
    real_type t39  = areaQ2_D_2_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t41  = areaQ2_D_2_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t43  = areaQ2_D_2_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t45  = areaQ2_D_2_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t47  = areaQ2_D_2_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t49  = areaQ2_D_2_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t51  = areaQ2_D_2_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t55  = areaQ2_D_2(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t56  = Ay_D_3_3(xo__x, xo__y, xo__theta);
    real_type t60  = areaQ2_D_3_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t62  = areaQ2_D_3_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t64  = areaQ2_D_3_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t66  = areaQ2_D_3_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t68  = areaQ2_D_3_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t70  = areaQ2_D_3_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t74  = areaQ2_D_3(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t75  = Bx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t80  = areaQ2_D_4_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t82  = areaQ2_D_4_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t84  = areaQ2_D_4_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t86  = areaQ2_D_4_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t88  = areaQ2_D_4_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t92  = areaQ2_D_4(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t93  = By_D_3_3(xo__x, xo__y, xo__theta);
    real_type t99  = areaQ2_D_5_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t101 = areaQ2_D_5_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t103 = areaQ2_D_5_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t105 = areaQ2_D_5_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t109 = areaQ2_D_5(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t110 = Cx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t117 = areaQ2_D_6_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t119 = areaQ2_D_6_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t121 = areaQ2_D_6_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t125 = areaQ2_D_6(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t126 = Cy_D_3_3(xo__x, xo__y, xo__theta);
    real_type t134 = areaQ2_D_7_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t136 = areaQ2_D_7_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t140 = areaQ2_D_7(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t141 = Dx_D_3_3(xo__x, xo__y, xo__theta);
    real_type t150 = areaQ2_D_8_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t154 = areaQ2_D_8(t1, t2, t3, t4, t5, t6, t7, t8);
    real_type t155 = Dy_D_3_3(xo__x, xo__y, xo__theta);
    real_type result__ = t10 * (t10 * t9 + t12 * t13 + t15 * t16 + t18 * t19 + t21 * t22 + t24 * t25 + t27 * t28 + t30 * t31) + t36 * t35 + t13 * (t10 * t12 + t13 * t39 + t16 * t41 + t19 * t43 + t22 * t45 + t25 * t47 + t28 * t49 + t31 * t51) + t56 * t55 + t16 * (t10 * t15 + t13 * t41 + t16 * t60 + t19 * t62 + t22 * t64 + t25 * t66 + t28 * t68 + t31 * t70) + t75 * t74 + t19 * (t10 * t18 + t13 * t43 + t16 * t62 + t19 * t80 + t22 * t82 + t25 * t84 + t28 * t86 + t31 * t88) + t93 * t92 + t22 * (t10 * t21 + t25 * t101 + t28 * t103 + t31 * t105 + t13 * t45 + t16 * t64 + t19 * t82 + t22 * t99) + t110 * t109 + t25 * (t10 * t24 + t22 * t101 + t25 * t117 + t28 * t119 + t31 * t121 + t13 * t47 + t16 * t66 + t19 * t84) + t126 * t125 + t28 * (t10 * t27 + t22 * t103 + t25 * t119 + t13 * t49 + t28 * t134 + t31 * t136 + t16 * t68 + t19 * t86) + t141 * t140 + t31 * (t10 * t30 + t22 * t105 + t25 * t121 + t13 * t51 + t28 * t136 + t31 * t150 + t16 * t70 + t19 * t88) + t155 * t154;
    if ( m_debug ) {
      UTILS_ASSERT(
        isRegular(result__),
        "UserFunctions_ABCD_D_3_3( x={}, y={}, theta={} ) return {}\n",
        xo__x, xo__y, xo__theta, result__
      );
    }
    return result__;
  }

}

// EOF: ICLOCS_ParallelParking_Methods_UserFunctions.cc
