/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods1.cc                                           |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  AlpRider::p( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(t__XO - a__XO, 2);
    return exp(-t2 * b__XO);
  }

  real_type
  AlpRider::p_D_1( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -t__XO + a__XO;
    real_type t3   = t1 * t1;
    real_type t5   = exp(-t3 * b__XO);
    return 2 * t5 * t1 * b__XO;
  }

  real_type
  AlpRider::p_D_1_1( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(-t__XO + a__XO, 2);
    real_type t3   = t2 * b__XO;
    real_type t4   = exp(-t3);
    return 4 * (-1.0 / 2.0 + t3) * b__XO * t4;
  }

  real_type
  AlpRider::p_D_1_2( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(-t__XO + a__XO, 2);
    real_type t3   = t2 * b__XO;
    real_type t4   = exp(-t3);
    return -4 * (-1.0 / 2.0 + t3) * b__XO * t4;
  }

  real_type
  AlpRider::p_D_1_3( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -t__XO + a__XO;
    real_type t2   = t1 * t1;
    real_type t4   = exp(-t2 * b__XO);
    real_type t6   = a__XO * a__XO;
    real_type t11  = t__XO * t__XO;
    return -2 * (-2 * a__XO * b__XO * t__XO + t11 * b__XO + b__XO * t6 - 1) * t1 * t4;
  }

  real_type
  AlpRider::p_D_2( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -t__XO + a__XO;
    real_type t3   = t1 * t1;
    real_type t5   = exp(-t3 * b__XO);
    return -2 * t5 * t1 * b__XO;
  }

  real_type
  AlpRider::p_D_2_2( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(-t__XO + a__XO, 2);
    real_type t3   = t2 * b__XO;
    real_type t4   = exp(-t3);
    return 4 * (-1.0 / 2.0 + t3) * b__XO * t4;
  }

  real_type
  AlpRider::p_D_2_3( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -t__XO + a__XO;
    real_type t2   = t1 * t1;
    real_type t4   = exp(-t2 * b__XO);
    real_type t6   = a__XO * a__XO;
    real_type t11  = t__XO * t__XO;
    return 2 * (-2 * a__XO * b__XO * t__XO + t11 * b__XO + b__XO * t6 - 1) * t1 * t4;
  }

  real_type
  AlpRider::p_D_3( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(-t__XO + a__XO, 2);
    real_type t4   = exp(-t2 * b__XO);
    return -t4 * t2;
  }

  real_type
  AlpRider::p_D_3_3( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(-t__XO + a__XO, 2);
    real_type t3   = t2 * t2;
    real_type t5   = exp(-t2 * b__XO);
    return t5 * t3;
  }

  real_type
  AlpRider::q( real_type t__XO ) const {
    real_type t1   = p(t__XO, 3, 12);
    real_type t3   = p(t__XO, 6, 10);
    real_type t5   = p(t__XO, 10, 6);
    real_type t7   = p(t__XO, 15, 4);
    return 3 * t1 + 3 * t3 + 3 * t5 + 8 * t7 + 0.1e-1;
  }

  real_type
  AlpRider::q_D( real_type t__XO ) const {
    real_type t1   = p_D_1(t__XO, 3, 12);
    real_type t3   = p_D_1(t__XO, 6, 10);
    real_type t5   = p_D_1(t__XO, 10, 6);
    real_type t7   = p_D_1(t__XO, 15, 4);
    return 3 * t1 + 3 * t3 + 3 * t5 + 8 * t7;
  }

  real_type
  AlpRider::q_DD( real_type t__XO ) const {
    real_type t1   = p_D_1_1(t__XO, 3, 12);
    real_type t3   = p_D_1_1(t__XO, 6, 10);
    real_type t5   = p_D_1_1(t__XO, 10, 6);
    real_type t7   = p_D_1_1(t__XO, 15, 4);
    return 3 * t1 + 3 * t3 + 3 * t5 + 8 * t7;
  }

}

// EOF: AlpRider_Methods1.cc
