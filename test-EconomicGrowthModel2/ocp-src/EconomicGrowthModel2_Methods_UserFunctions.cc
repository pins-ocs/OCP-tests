/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods1.cc                               |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  EconomicGrowthModel2::Q( real_type x__XO, real_type y__XO ) const {
    return x__XO * y__XO;
  }

  real_type
  EconomicGrowthModel2::Q_D_1( real_type x__XO, real_type y__XO ) const {
    return y__XO;
  }

  real_type
  EconomicGrowthModel2::Q_D_1_1( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  EconomicGrowthModel2::Q_D_1_2( real_type x__XO, real_type y__XO ) const {
    return 1;
  }

  real_type
  EconomicGrowthModel2::Q_D_2( real_type x__XO, real_type y__XO ) const {
    return x__XO;
  }

  real_type
  EconomicGrowthModel2::Q_D_2_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  EconomicGrowthModel2::explog( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = log(a__XO);
    real_type t4   = log(b__XO);
    return exp((1 - s__XO) * t1 + s__XO * t4);
  }

  real_type
  EconomicGrowthModel2::explog_D_1( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, s__XO);
    return -t4 * t2 * (-1 + s__XO);
  }

  real_type
  EconomicGrowthModel2::explog_D_1_1( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t3   = pow(a__XO, -s__XO - 1);
    real_type t5   = pow(b__XO, s__XO);
    return t5 * s__XO * t3 * (-1 + s__XO);
  }

  real_type
  EconomicGrowthModel2::explog_D_1_2( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, t1);
    return -s__XO * t4 * t2 * t1;
  }

  real_type
  EconomicGrowthModel2::explog_D_1_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = pow(b__XO, s__XO);
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = -1 + s__XO;
    real_type t5   = log(a__XO);
    real_type t8   = log(b__XO);
    return (t5 * t4 - t8 * t4 - 1) * t2 * t1;
  }

  real_type
  EconomicGrowthModel2::explog_D_2( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(b__XO, t1);
    real_type t5   = pow(a__XO, -t1);
    return t5 * t2 * s__XO;
  }

  real_type
  EconomicGrowthModel2::explog_D_2_2( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t2   = pow(b__XO, -2 + s__XO);
    real_type t4   = -1 + s__XO;
    real_type t6   = pow(a__XO, -t4);
    return t6 * t4 * t2 * s__XO;
  }

  real_type
  EconomicGrowthModel2::explog_D_2_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = 1 - s__XO;
    real_type t2   = pow(a__XO, t1);
    real_type t4   = pow(b__XO, -t1);
    real_type t6   = log(a__XO);
    real_type t8   = log(b__XO);
    return -(s__XO * t6 - s__XO * t8 - 1) * t4 * t2;
  }

  real_type
  EconomicGrowthModel2::explog_D_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t5   = pow(a__XO, 1 - s__XO);
    real_type t7   = pow(b__XO, s__XO);
    return -t7 * t5 * (t1 - t2);
  }

  real_type
  EconomicGrowthModel2::explog_D_3_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t4   = pow(t1 - t2, 2);
    real_type t6   = pow(a__XO, 1 - s__XO);
    real_type t8   = pow(b__XO, s__XO);
    return t8 * t6 * t4;
  }

}

// EOF: EconomicGrowthModel2_Methods1.cc
