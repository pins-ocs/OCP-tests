/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods1.cc                                   |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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


namespace Brachiostocrona2Define {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  Brachiostocrona2::theta_sol( real_type v__XO, real_type l1__XO, real_type l2__XO, real_type l3__XO ) const {
    real_type t8   = arctan2(l2__XO * v__XO - l3__XO * ModelPars[2], v__XO * l1__XO);
    return ModelPars[3] * 0.3141592654e1 + t8;
  }

  real_type
  Brachiostocrona2::theta_sol_D_1( real_type v__XO, real_type l1__XO, real_type l2__XO, real_type l3__XO ) const {
    real_type t4   = l2__XO * v__XO - l3__XO * ModelPars[2];
    real_type t5   = v__XO * l1__XO;
    real_type t6   = arctan2_D_1(t4, t5);
    real_type t8   = arctan2_D_2(t4, t5);
    return l1__XO * t8 + l2__XO * t6;
  }

  real_type
  Brachiostocrona2::theta_sol_D_2( real_type v__XO, real_type l1__XO, real_type l2__XO, real_type l3__XO ) const {
    real_type t6   = arctan2_D_2(l2__XO * v__XO - l3__XO * ModelPars[2], v__XO * l1__XO);
    return v__XO * t6;
  }

  real_type
  Brachiostocrona2::theta_sol_D_3( real_type v__XO, real_type l1__XO, real_type l2__XO, real_type l3__XO ) const {
    real_type t6   = arctan2_D_1(l2__XO * v__XO - l3__XO * ModelPars[2], v__XO * l1__XO);
    return v__XO * t6;
  }

  real_type
  Brachiostocrona2::theta_sol_D_4( real_type v__XO, real_type l1__XO, real_type l2__XO, real_type l3__XO ) const {
    real_type t2   = ModelPars[2];
    real_type t6   = arctan2_D_1(l2__XO * v__XO - t2 * l3__XO, v__XO * l1__XO);
    return -t2 * t6;
  }

}

// EOF: Brachiostocrona2_Methods1.cc
