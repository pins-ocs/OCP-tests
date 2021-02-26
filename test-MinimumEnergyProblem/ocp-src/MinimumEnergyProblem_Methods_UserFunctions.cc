/*-----------------------------------------------------------------------*\
 |  file: MinimumEnergyProblem_Methods1.cc                               |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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


#include "MinimumEnergyProblem.hh"
#include "MinimumEnergyProblem_Pars.hh"

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
#define ALIAS_x1Limitation_DD(__t1) x1Limitation.DD( __t1)
#define ALIAS_x1Limitation_D(__t1) x1Limitation.D( __t1)


namespace MinimumEnergyProblemDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  MinimumEnergyProblem::interpLog( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t2   = pow(v0__XO, 1 - s__XO);
    real_type t3   = pow(v1__XO, s__XO);
    return t3 * t2;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t2   = pow(v0__XO, 1 - s__XO);
    real_type t3   = pow(v1__XO, s__XO);
    real_type t5   = log(v1__XO);
    real_type t6   = log(v0__XO);
    return (t5 - t6) * t3 * t2;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1_1( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t2   = pow(v0__XO, 1 - s__XO);
    real_type t3   = pow(v1__XO, s__XO);
    real_type t5   = log(v1__XO);
    real_type t6   = log(v0__XO);
    real_type t8   = pow(t5 - t6, 2);
    return t8 * t3 * t2;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1_2( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t1   = pow(v1__XO, s__XO);
    real_type t2   = -1 + s__XO;
    real_type t3   = log(v0__XO);
    real_type t6   = log(v1__XO);
    real_type t10  = pow(v0__XO, -s__XO);
    return t10 * (t3 * t2 - t6 * t2 - 1) * t1;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_1_3( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t1   = 1 - s__XO;
    real_type t2   = pow(v0__XO, t1);
    real_type t4   = pow(v1__XO, -t1);
    real_type t6   = log(v1__XO);
    real_type t8   = log(v0__XO);
    return (t6 * s__XO - t8 * s__XO + 1) * t4 * t2;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_2( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t1   = pow(v0__XO, -s__XO);
    real_type t4   = pow(v1__XO, s__XO);
    return t4 * (1 - s__XO) * t1;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_2_2( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t2   = pow(v0__XO, -s__XO - 1);
    real_type t5   = pow(v1__XO, s__XO);
    return t5 * (-1 + s__XO) * s__XO * t2;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_2_3( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t1   = pow(v0__XO, -s__XO);
    real_type t2   = 1 - s__XO;
    real_type t5   = pow(v1__XO, -t2);
    return s__XO * t5 * t2 * t1;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_3( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t1   = 1 - s__XO;
    real_type t2   = pow(v0__XO, t1);
    real_type t4   = pow(v1__XO, -t1);
    return s__XO * t4 * t2;
  }

  real_type
  MinimumEnergyProblem::interpLog_D_3_3( real_type s__XO, real_type v0__XO, real_type v1__XO ) const {
    real_type t1   = 1 - s__XO;
    real_type t2   = pow(v0__XO, t1);
    real_type t4   = pow(v1__XO, -2 + s__XO);
    return -s__XO * t1 * t4 * t2;
  }

}

// EOF: MinimumEnergyProblem_Methods1.cc
