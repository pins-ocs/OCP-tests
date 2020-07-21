/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods1.cc                                   |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn_pars::continuationStep0( real_type s ) {
    int msg_level = 3;
    pConsole->message(
      fmt::format( "\nContinuation step N.0 s = {}\n", s ),
      msg_level
    );
    ModelPars[3] = s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn_pars::continuationStep1( real_type s ) {
    int msg_level = 3;
    pConsole->message(
      fmt::format( "\nContinuation step N.1 s = {}\n", s ),
      msg_level
    );
    ModelPars[6] = s;
  }

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  gtocX_2burn_pars::cont( real_type s__XO, real_type eps0__XO, real_type eps1__XO ) const {
    real_type t2   = log(eps0__XO);
    real_type t4   = log(eps1__XO);
    return exp(t2 * (1 - s__XO) + t4 * s__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    return 1.0 / (t1 + t2 + 1) / (t4 * f__XO + t7 * g__XO + 1) * p__XO * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    return 1.0 / (t1 + t2 + 1) / (t4 * f__XO + t7 * g__XO + 1) * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t10  = cos(L__XO);
    real_type t15  = t10 * t10;
    real_type t16  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    return -1.0 / (2 * f__XO * g__XO * t6 * t10 + 2 * t10 * f__XO + 2 * t6 * g__XO + t16 * t15 - t18 * t15 + t18 + 1) * t10 * (2 * t6 * k__XO * retrograde__XO * h__XO + t1 * t10 - t2 * t10 + t10) / (t1 + t2 + 1);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t10  = cos(L__XO);
    real_type t15  = t10 * t10;
    real_type t16  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    return -1.0 / (2 * f__XO * g__XO * t6 * t10 + 2 * t10 * f__XO + 2 * t6 * g__XO + t16 * t15 - t18 * t15 + t18 + 1) * t6 * (2 * t6 * k__XO * retrograde__XO * h__XO + t1 * t10 - t2 * t10 + t10) / (t1 + t2 + 1);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t18  = pow(t1 + t2 + 1, 2);
    return -2 / t18 / (t7 * f__XO + t5 * g__XO + 1) * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7) * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t21  = pow(t2 + t3 + 1, 2);
    return 1.0 / t21 / (t9 * f__XO + t5 * g__XO + 1) * (2 * t5 * (t2 - t3 + 1) * h__XO * retrograde__XO - 4 * (t2 + 1) * t9 * k__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = k__XO * retrograde__XO;
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t8   = -t6 + t7 - 1;
    real_type t9   = sin(L__XO);
    real_type t16  = f__XO * f__XO;
    real_type t17  = g__XO * g__XO;
    real_type t19  = t1 * t1;
    return 1.0 / (t6 + t7 + 1) / (t19 * (t16 - t17) + t1 * (2 * t9 * g__XO * f__XO + 2 * f__XO) + t17 + 2 * t9 * g__XO + 1) * (2 * t3 * f__XO * h__XO + 2 * t3 * h__XO * t1 + g__XO * t8 + t9 * t8);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_1_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sin(L__XO);
    real_type t3   = cos(L__XO);
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    return 2 / (t9 + t10 + 1) / (t3 * f__XO + t2 * g__XO + 1) * t2 * h__XO * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t16  = t11 * t11;
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    return -1.0 / (2 * f__XO * g__XO * t7 * t11 + 2 * t11 * f__XO + 2 * t7 * g__XO + t17 * t16 - t19 * t16 + t19 + 1) * t11 * (2 * t7 * k__XO * retrograde__XO * h__XO + t1 * t11 - t2 * t11 + t11) / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t13  = t4 * t4;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t24  = t16 * g__XO;
    real_type t28  = 3 * t16;
    return 2 / (t1 + t2 + 1) / (t13 * t4 * (t14 * f__XO - 3 * t16 * f__XO) + t13 * (t7 * (3 * t14 * g__XO - t24) + 3 * t14 - t28) + 3 * t4 * (2 * t7 * g__XO + t16 + 1) * f__XO + t7 * (t24 + 3 * g__XO) + t28 + 1) * t13 * p__XO * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t11  = sin(L__XO);
    real_type t18  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t28  = t20 * g__XO;
    real_type t32  = 3 * t20;
    return 2 / (t7 + t8 + 1) / (t2 * t1 * (t18 * f__XO - 3 * t20 * f__XO) + t2 * (t11 * (3 * t18 * g__XO - t28) + 3 * t18 - t32) + 3 * t1 * (2 * t11 * g__XO + t20 + 1) * f__XO + t11 * (t28 + 3 * g__XO) + t32 + 1) * t1 * (-2 * k__XO * retrograde__XO * h__XO * t2 + t11 * t1 * (t7 - t8 + 1) + 2 * h__XO * k__XO * retrograde__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t15  = pow(t1 + t2 + 1, 2);
    real_type t18  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t21  = t7 * t7;
    return 2 / (t21 * (t18 - t19) + t7 * (2 * t5 * g__XO * f__XO + 2 * f__XO) + t19 + 2 * t5 * g__XO + 1) / t15 * t7 * k__XO * p__XO * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = k__XO * k__XO;
    real_type t10  = sin(L__XO);
    real_type t16  = pow(t1 + t8 + 1, 2);
    real_type t19  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t22  = t5 * t5;
    return -2 / (t22 * (t19 - t20) + t5 * (2 * t10 * g__XO * f__XO + 2 * f__XO) + t20 + 2 * t10 * g__XO + 1) / t16 * t5 * p__XO * (t5 * (-2 * k__XO * t1 - 2 * k__XO) + t10 * (t1 - t8 + 1) * h__XO * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t4   = k__XO * retrograde__XO;
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t9   = -t7 + t8 - 1;
    real_type t10  = sin(L__XO);
    real_type t18  = t10 * g__XO;
    real_type t24  = f__XO * f__XO;
    real_type t26  = g__XO * g__XO;
    real_type t34  = t26 * g__XO;
    real_type t38  = 3 * t26;
    return -2 / (t7 + t8 + 1) / (t2 * t1 * (t24 * f__XO - 3 * t26 * f__XO) + t2 * (t10 * (3 * t24 * g__XO - t34) + 3 * t24 - t38) + 3 * t1 * (t26 + 2 * t18 + 1) * f__XO + t10 * (t34 + 3 * g__XO) + t38 + 1) * (2 * t4 * h__XO * t2 + t1 * (t4 * f__XO * h__XO + g__XO * t9 + t10 * t9) - (t18 + 1) * retrograde__XO * h__XO * k__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t10  = t9 * t9;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    return -2 / (2 * f__XO * g__XO * t7 * t9 + 2 * t9 * f__XO + 2 * t7 * g__XO + t11 * t10 - t13 * t10 + t13 + 1) * t9 * t7 * k__XO * h__XO / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t16  = t11 * t11;
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    return -1.0 / (2 * f__XO * g__XO * t7 * t11 + 2 * t11 * f__XO + 2 * t7 * g__XO + t17 * t16 - t19 * t16 + t19 + 1) * t7 * (2 * t7 * k__XO * retrograde__XO * h__XO + t1 * t11 - t2 * t11 + t11) / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t12  = t7 * t7;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t20  = t4 * t4;
    real_type t25  = t16 * g__XO;
    real_type t29  = 3 * t16;
    return 2 / (t1 + t2 + 1) / (t20 * t4 * (t14 * f__XO - 3 * t16 * f__XO) + t20 * (t7 * (3 * t14 * g__XO - t25) + 3 * t14 - t29) + 3 * t4 * (2 * t7 * g__XO + t16 + 1) * f__XO + t7 * (t25 + 3 * g__XO) + t29 + 1) * p__XO * t12 * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t15  = pow(t2 + t3 + 1, 2);
    real_type t18  = f__XO * t7;
    real_type t23  = f__XO * f__XO;
    real_type t24  = g__XO * g__XO;
    real_type t26  = t7 * t7;
    return 2 / (t1 * (2 * t18 * g__XO + 2 * g__XO) + t26 * (t23 - t24) + 2 * t18 + t24 + 1) / t15 * k__XO * p__XO * (t1 * (t2 - t3 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7) * t1;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t6   = cos(L__XO);
    real_type t9   = k__XO * k__XO;
    real_type t16  = pow(t2 + t9 + 1, 2);
    real_type t19  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t22  = t6 * t6;
    return -2 / (t22 * (t19 - t20) + t6 * (2 * t1 * g__XO * f__XO + 2 * f__XO) + t20 + 2 * t1 * g__XO + 1) / t16 * p__XO * (t6 * (-2 * k__XO * t2 - 2 * k__XO) + t1 * (t2 - t9 + 1) * h__XO * retrograde__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 + 1;
    real_type t5   = cos(L__XO);
    real_type t6   = t5 * t5;
    real_type t9   = sin(L__XO);
    real_type t26  = f__XO * f__XO;
    real_type t28  = g__XO * g__XO;
    real_type t36  = t28 * g__XO;
    real_type t40  = 3 * t28;
    return -1.0 / (t1 + t2 + 1) / (t6 * t5 * (t26 * f__XO - 3 * t28 * f__XO) + t6 * (t9 * (3 * t26 * g__XO - t36) + 3 * t26 - t40) + 3 * t5 * (2 * t9 * g__XO + t28 + 1) * f__XO + t9 * (t36 + 3 * g__XO) + t40 + 1) * (2 * t6 * t3 + t5 * (4 * t9 * k__XO * retrograde__XO * h__XO + t3 * f__XO) + t9 * (4 * f__XO * h__XO * k__XO * retrograde__XO - g__XO * t3) - t1 + t2 - 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t8   = t7 * t7;
    real_type t10  = cos(L__XO);
    real_type t11  = t10 * t10;
    real_type t12  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    return -2 / (2 * f__XO * g__XO * t7 * t10 + 2 * t10 * f__XO + 2 * t7 * g__XO + t12 * t11 - t14 * t11 + t14 + 1) * t8 * k__XO * h__XO / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    return -2 / t19 / (t7 * f__XO + t5 * g__XO + 1) * k__XO * p__XO * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t22  = t2 + t5 + 1;
    real_type t23  = t22 * t22;
    return 4 / t23 / t22 / (t8 * f__XO + t11 * g__XO + 1) * (t8 * (-3 * k__XO * t2 + t5 * k__XO + k__XO) + (t2 - 3 * t5 - 3) * t11 * retrograde__XO * h__XO) * p__XO * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = t1 * t1;
    real_type t3   = k__XO * k__XO;
    real_type t6   = t3 * t3;
    real_type t9   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    return -2 / t24 / t23 / (t11 * f__XO + t9 * g__XO + 1) * (t9 * (-6 * t3 * t1 + t2 + t6 - 1) * retrograde__XO - 4 * (t1 - t3 + 1) * k__XO * h__XO * t11) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type t22  = f__XO * f__XO;
    real_type t23  = g__XO * g__XO;
    real_type t25  = t5 * t5;
    return -2 / (t25 * (t22 - t23) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t23 + 2 * t8 * g__XO + 1) / t19 * k__XO * p__XO * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t14  = pow(t1 + t2 + 1, 2);
    return -2 / t14 / (t7 * f__XO + t4 * g__XO + 1) * k__XO * p__XO * t4 * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t20  = pow(t2 + t3 + 1, 2);
    return 2 / t20 / (t8 * f__XO + t5 * g__XO + 1) * p__XO * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO - 2 * (t2 + 1) * t8 * k__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    return -4 / t24 / t23 / (t7 * f__XO + t9 * g__XO + 1) * (t7 * (t1 - 3 * t3 + 1) * (t1 + 1) + 3 * h__XO * retrograde__XO * (t1 - t3 / 3 + 1) * k__XO * t9) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t29  = pow(t2 + t3 + 1, 2);
    real_type t31  = f__XO * f__XO;
    real_type t32  = g__XO * g__XO;
    real_type t34  = t5 * t5;
    return 2 / (t34 * (t31 - t32) + t5 * (2 * t11 * g__XO * f__XO + 2 * f__XO) + t32 + 2 * t11 * g__XO + 1) / t29 * p__XO * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO + t11 * (2 * k__XO * t2 + 2 * k__XO) + retrograde__XO * t2 * h__XO * f__XO + 2 * k__XO * t2 * g__XO + h__XO * (-retrograde__XO * t3 * f__XO + f__XO * retrograde__XO) + 2 * g__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t14  = pow(t1 + t2 + 1, 2);
    return 2 / t14 / (t7 * f__XO + t5 * g__XO + 1) * p__XO * t5 * (t1 - t2 + 1) * h__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t3   = cos(L__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = (-t7 + t8 - 1) * p__XO;
    real_type t11  = sin(L__XO);
    real_type t23  = f__XO * f__XO;
    real_type t24  = g__XO * g__XO;
    real_type t26  = t3 * t3;
    return 1.0 / (t26 * (t23 - t24) + t3 * (2 * t11 * g__XO * f__XO + 2 * f__XO) + t24 + 2 * t11 * g__XO + 1) / (t7 + t8 + 1) * (2 * p__XO * f__XO * h__XO * k__XO * retrograde__XO + 2 * t3 * retrograde__XO * k__XO * p__XO * h__XO + g__XO * t10 + t11 * t10);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = k__XO * retrograde__XO;
    real_type t4   = t2 * g__XO * h__XO / 2;
    real_type t5   = h__XO * h__XO;
    real_type t6   = k__XO * k__XO;
    real_type t7   = t5 - t6 + 1;
    real_type t8   = t7 * f__XO;
    real_type t11  = cos(L__XO);
    real_type t12  = t11 * t11;
    real_type t20  = sin(L__XO);
    real_type t23  = g__XO * g__XO;
    real_type t25  = f__XO * g__XO;
    real_type t26  = h__XO * k__XO;
    real_type t35  = f__XO * f__XO;
    real_type t52  = t23 * g__XO;
    real_type t56  = 3 * t23;
    return 4 / (t5 + t6 + 1) / (t12 * t11 * (-3 * t23 * f__XO + t35 * f__XO) + t12 * (t20 * (3 * t35 * g__XO - t52) + 3 * t35 - t56) + 3 * t11 * (2 * t20 * g__XO + t23 + 1) * f__XO + t20 * (t52 + 3 * g__XO) + t56 + 1) * (t12 * (-t4 + t8 / 4) + t11 * (t20 * (g__XO * t7 / 4 + t2 * f__XO * h__XO / 2) + t23 * t7 / 2 - retrograde__XO * t26 * t25 - t5 / 4 + t6 / 4 - 1.0 / 4.0) + t20 * (-t7 * t25 / 2 + (t35 - 1.0 / 2.0) * retrograde__XO * t26) - t4 - t8 / 2) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = t7 * t7;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t15  = sin(L__XO);
    return 2 / (2 * f__XO * g__XO * t15 * t7 + 2 * t7 * f__XO + 2 * t15 * g__XO + t11 * t10 - t13 * t10 + t13 + 1) * (t7 + f__XO) * p__XO * k__XO * h__XO / (t1 + t2 + 1);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sin(L__XO);
    real_type t4   = cos(L__XO);
    real_type t10  = h__XO * h__XO;
    real_type t11  = k__XO * k__XO;
    return 2 / (t10 + t11 + 1) / (t4 * f__XO + t2 * g__XO + 1) * p__XO * t2 * k__XO * h__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_7_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yPosition( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    return -1.0 / (t1 + t2 + 1) / (t7 * f__XO + t5 * g__XO + 1) * p__XO * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    return 1.0 / (t1 + t2 + 1) / (t7 * f__XO + t5 * g__XO + 1) * (-t5 * (t1 - t2 - 1) * retrograde__XO + 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = t1 * t1;
    return 1.0 / (t2 + t3 + 1) / (t16 * (t13 - t14) + t1 * (2 * t6 * g__XO * f__XO + 2 * f__XO) + t14 + 2 * t6 * g__XO + 1) * (t6 * (t2 - t3 - 1) * retrograde__XO - 2 * k__XO * h__XO * t1) * t1;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t13  = t7 * f__XO;
    real_type t18  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t21  = t7 * t7;
    return 1.0 / (t1 + t2 + 1) / (t5 * (2 * g__XO * t13 + 2 * g__XO) + t21 * (t18 - t19) + 2 * t13 + t19 + 1) * t5 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t22  = pow(t1 + t3 + 1, 2);
    return 1.0 / t22 / (t7 * f__XO + t10 * g__XO + 1) * (t7 * (-2 * k__XO * t1 + 2 * t3 * k__XO + 2 * k__XO) - 4 * (t3 + 1) * t10 * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t18  = pow(t1 + t2 + 1, 2);
    return 2 * h__XO / t18 / (t4 * f__XO + t7 * g__XO + 1) * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t17  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    real_type t20  = t5 * t5;
    return 1.0 / (t1 + t2 + 1) / (t20 * (t17 - t18) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t18 + 2 * t8 * g__XO + 1) * (-retrograde__XO * t3 * f__XO - 2 * g__XO * h__XO * k__XO - 2 * t8 * k__XO * h__XO - t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = sin(L__XO);
    real_type t6   = cos(L__XO);
    return -1.0 / (t1 + t2 + 1) / (t6 * f__XO + t4 * g__XO + 1) * t4 * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t16  = f__XO * f__XO;
    real_type t17  = g__XO * g__XO;
    real_type t19  = t7 * t7;
    return 1.0 / (t19 * (t16 - t17) + t7 * (2 * t5 * g__XO * f__XO + 2 * f__XO) + t17 + 2 * t5 * g__XO + 1) / (t1 + t2 + 1) * t7 * p__XO * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t13  = t7 * t7;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t24  = t16 * g__XO;
    real_type t28  = 3 * t16;
    return -2 / (t1 + t2 + 1) / (t13 * t7 * (t14 * f__XO - 3 * t16 * f__XO) + t13 * (t5 * (3 * t14 * g__XO - t24) + 3 * t14 - t28) + 3 * t7 * (2 * t5 * g__XO + t16 + 1) * f__XO + t5 * (t24 + 3 * g__XO) + t28 + 1) * t13 * p__XO * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = (t1 - t2 - 1) * retrograde__XO;
    real_type t5   = cos(L__XO);
    real_type t6   = t5 * t5;
    real_type t8   = sin(L__XO);
    real_type t15  = f__XO * f__XO;
    real_type t17  = g__XO * g__XO;
    real_type t25  = t17 * g__XO;
    real_type t29  = 3 * t17;
    return 2 / (t1 + t2 + 1) / (t6 * t5 * (t15 * f__XO - 3 * t17 * f__XO) + t6 * (t8 * (3 * t15 * g__XO - t25) + 3 * t15 - t29) + 3 * t5 * (2 * t8 * g__XO + t17 + 1) * f__XO + t8 * (t25 + 3 * g__XO) + t29 + 1) * t5 * (2 * h__XO * k__XO * t8 * t5 + t6 * t4 - t4) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t16  = pow(t1 + t2 + 1, 2);
    real_type t19  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t22  = t5 * t5;
    return 2 / (t22 * (t19 - t20) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t20 + 2 * t8 * g__XO + 1) / t16 * t5 * p__XO * (t5 * (t1 - t2 - 1) * k__XO + 2 * (t2 + 1) * t8 * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t8   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t15  = pow(t8 + t10 + 1, 2);
    real_type t18  = t1 * t1;
    real_type t19  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    return -2 / (2 * f__XO * g__XO * t4 * t1 + 2 * t1 * f__XO + 2 * t4 * g__XO + t19 * t18 - t21 * t18 + t21 + 1) / t15 * h__XO * (2 * t4 * k__XO * retrograde__XO * h__XO - t10 * t1 + t8 * t1 + t1) * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t4   = t3 * retrograde__XO;
    real_type t5   = cos(L__XO);
    real_type t6   = t5 * t5;
    real_type t10  = sin(L__XO);
    real_type t20  = t10 * g__XO;
    real_type t25  = f__XO * f__XO;
    real_type t27  = g__XO * g__XO;
    real_type t35  = t27 * g__XO;
    real_type t39  = 3 * t27;
    return 1.0 / (t1 + t2 + 1) / (t6 * t5 * (t25 * f__XO - 3 * t27 * f__XO) + t6 * (t10 * (3 * t25 * g__XO - t35) + 3 * t25 - t39) + 3 * t5 * (t27 + 2 * t20 + 1) * f__XO + t10 * (t35 + 3 * g__XO) + t39 + 1) * (2 * t6 * t4 + t5 * (retrograde__XO * t3 * f__XO + 4 * g__XO * h__XO * k__XO + 4 * t10 * k__XO * h__XO) - (t20 + 1) * t4) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t10  = t9 * t8;
    real_type t11  = t8 * t8;
    real_type t12  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    return 1.0 / (2 * f__XO * g__XO * t10 + 2 * t8 * f__XO + 2 * t9 * g__XO + t12 * t11 - t14 * t11 + t14 + 1) * t10 / (t1 + t2 + 1) * p__XO * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t16  = f__XO * t7;
    real_type t21  = f__XO * f__XO;
    real_type t22  = g__XO * g__XO;
    real_type t24  = t7 * t7;
    return 1.0 / (t5 * (2 * g__XO * t16 + 2 * g__XO) + t24 * (t21 - t22) + 2 * t16 + t22 + 1) / (t1 + t2 + 1) * p__XO * t5 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t2   = t1 * t1;
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t20  = t8 * t8;
    real_type t25  = g__XO * t16;
    real_type t29  = 3 * t16;
    return -2 / (t3 + t4 + 1) / (t20 * t8 * (t14 * f__XO - 3 * t16 * f__XO) + t20 * (t1 * (3 * t14 * g__XO - t25) + 3 * t14 - t29) + 3 * t8 * (2 * t1 * g__XO + t16 + 1) * f__XO + t1 * (t25 + 3 * g__XO) + t29 + 1) * p__XO * (t1 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t8) * t2;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t16  = pow(t2 + t3 + 1, 2);
    real_type t19  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t22  = t6 * t6;
    return 2 / (t22 * (t19 - t20) + t6 * (2 * t1 * g__XO * f__XO + 2 * f__XO) + t20 + 2 * t1 * g__XO + 1) / t16 * p__XO * (t6 * (t2 - t3 - 1) * k__XO + 2 * (t3 + 1) * t1 * retrograde__XO * h__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t8   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t15  = pow(t8 + t10 + 1, 2);
    real_type t18  = t7 * t7;
    real_type t19  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    return -2 / (2 * f__XO * g__XO * t1 * t7 + 2 * f__XO * t7 + 2 * t1 * g__XO + t19 * t18 - t21 * t18 + t21 + 1) / t15 * h__XO * (2 * t1 * k__XO * retrograde__XO * h__XO - t10 * t7 + t8 * t7 + t7) * p__XO * t1;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t8   = t6 - t7 - 1;
    real_type t10  = sin(L__XO);
    real_type t25  = f__XO * f__XO;
    real_type t27  = g__XO * g__XO;
    real_type t35  = t27 * g__XO;
    real_type t39  = 3 * t27;
    return 2 / (t6 + t7 + 1) / (t2 * t1 * (t25 * f__XO - 3 * t27 * f__XO) + t2 * (t10 * (3 * t25 * g__XO - t35) + 3 * t25 - t39) + 3 * t1 * (2 * t10 * g__XO + t27 + 1) * f__XO + t10 * (t35 + 3 * g__XO) + t39 + 1) * (-2 * k__XO * h__XO * t2 + t1 * (-f__XO * h__XO * k__XO + t10 * t8 * retrograde__XO) + t10 * (retrograde__XO * t8 * f__XO + g__XO * h__XO * k__XO) + h__XO * k__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t8   = t7 * t7;
    real_type t10  = cos(L__XO);
    real_type t11  = t10 * t10;
    real_type t12  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    return 1.0 / (2 * f__XO * g__XO * t7 * t10 + 2 * t10 * f__XO + 2 * t7 * g__XO + t12 * t11 - t14 * t11 + t14 + 1) * t8 / (t1 + t2 + 1) * p__XO * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t20  = pow(t1 + t2 + 1, 2);
    return -2 / t20 / (t5 * f__XO + t8 * g__XO + 1) * p__XO * (t5 * (t1 - t2 - 1) * k__XO + 2 * (t2 + 1) * t8 * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = k__XO * k__XO;
    real_type t3   = h__XO * h__XO;
    real_type t7   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t23  = t3 + t1 + 1;
    real_type t24  = t23 * t23;
    return 4 / t24 / t23 / (t11 * f__XO + t7 * g__XO + 1) * (3 * t7 * retrograde__XO * (t3 - t1 / 3 - 1.0 / 3.0) * (t1 + 1) + (t3 - 3 * t1 - 3) * k__XO * h__XO * t11) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = t1 * t1;
    real_type t3   = k__XO * k__XO;
    real_type t6   = t3 * t3;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    return -2 / t24 / t23 / (t8 * f__XO + t11 * g__XO + 1) * (t8 * (-6 * t3 * t1 + t2 + t6 - 1) + 4 * (t1 - t3 - 1) * retrograde__XO * t11 * h__XO * k__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = cos(L__XO);
    real_type t3   = k__XO * k__XO;
    real_type t7   = h__XO * h__XO;
    real_type t10  = sin(L__XO);
    real_type t16  = f__XO * h__XO;
    real_type t27  = pow(t7 + t3 + 1, 2);
    real_type t29  = f__XO * f__XO;
    real_type t30  = g__XO * g__XO;
    real_type t32  = t2 * t2;
    return -4 / (t32 * (t29 - t30) + t2 * (2 * t10 * g__XO * f__XO + 2 * f__XO) + t30 + 2 * t10 * g__XO + 1) / t27 * ((t3 + 1) * t2 * retrograde__XO * h__XO - t10 * (t7 - t3 - 1) * k__XO / 2 + t3 * k__XO * g__XO / 2 + retrograde__XO * t3 * t16 + k__XO * (-t7 / 2 + 1.0 / 2.0) * g__XO + retrograde__XO * t16) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t12  = h__XO * h__XO;
    real_type t14  = pow(t12 + t3 + 1, 2);
    return -4 / t14 / (t6 * f__XO + t1 * g__XO + 1) * p__XO * (t3 + 1) * t1 * h__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    return 2 / t19 / (t4 * f__XO + t7 * g__XO + 1) * h__XO * p__XO * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t23  = t1 + t4 + 1;
    real_type t24  = t23 * t23;
    return 4 / t24 / t23 / (t8 * f__XO + t11 * g__XO + 1) * h__XO * (t8 * (-3 * k__XO * t1 + t4 * k__XO - 3 * k__XO) + (t1 - 3 * t4 + 1) * t11 * retrograde__XO * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t3   = k__XO * retrograde__XO;
    real_type t6   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = cos(L__XO);
    real_type t14  = sin(L__XO);
    real_type t19  = pow(t6 + t8 + 1, 2);
    real_type t22  = t10 * t10;
    real_type t23  = f__XO * f__XO;
    real_type t25  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t14 * t10 + 2 * t10 * f__XO + 2 * t14 * g__XO + t23 * t22 - t25 * t22 + t25 + 1) / t19 * (2 * t3 * f__XO * h__XO + 2 * t3 * h__XO * t10 - t6 * g__XO + t8 * g__XO - t6 * t14 + t8 * t14 - g__XO - t14) * p__XO * h__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t3   = sin(L__XO);
    real_type t5   = cos(L__XO);
    real_type t11  = k__XO * k__XO;
    real_type t13  = pow(t1 + t11 + 1, 2);
    return 4 / t13 / (t5 * f__XO + t3 * g__XO + 1) * p__XO * t3 * k__XO * t1;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t20  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    real_type t23  = t5 * t5;
    return -1.0 / (t23 * (t20 - t21) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t21 + 2 * t8 * g__XO + 1) / (t1 + t2 + 1) * p__XO * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t4   = t3 * retrograde__XO;
    real_type t6   = g__XO * t4 / 2;
    real_type t8   = f__XO * h__XO * k__XO;
    real_type t10  = cos(L__XO);
    real_type t11  = t10 * t10;
    real_type t15  = t3 * f__XO;
    real_type t19  = sin(L__XO);
    real_type t21  = g__XO * g__XO;
    real_type t27  = h__XO * k__XO;
    real_type t33  = f__XO * f__XO;
    real_type t49  = t21 * g__XO;
    real_type t53  = 3 * t21;
    return -2 / (t1 + t2 + 1) / (t11 * t10 * (-3 * t21 * f__XO + t33 * f__XO) + t11 * (t19 * (3 * t33 * g__XO - t49) + 3 * t33 - t53) + 3 * t10 * (2 * t19 * g__XO + t21 + 1) * f__XO + t19 * (t49 + 3 * g__XO) + t53 + 1) * (t11 * (-t6 - t8) + t10 * (t19 * (-g__XO * h__XO * k__XO + retrograde__XO * t15 / 2) - 2 * k__XO * h__XO * t21 - retrograde__XO * g__XO * t15 + t27) + t19 * (2 * t27 * f__XO * g__XO + (t33 - 1.0 / 2.0) * t4) - t6 + 2 * t8) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = t7 * t7;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t15  = sin(L__XO);
    return -1.0 / (2 * f__XO * g__XO * t15 * t7 + 2 * t7 * f__XO + 2 * t15 * g__XO + t11 * t10 - t13 * t10 + t13 + 1) * (t7 + f__XO) * (t1 - t2 - 1) / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = sin(L__XO);
    real_type t6   = cos(L__XO);
    return -1.0 / (t1 + t2 + 1) / (t6 * f__XO + g__XO * t4 + 1) * p__XO * t4 * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_7_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zPosition( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t12  = h__XO * h__XO;
    real_type t13  = k__XO * k__XO;
    return 2 / (t12 + t13 + 1) / (t1 * f__XO + g__XO * t4 + 1) * (-retrograde__XO * k__XO * t1 + t4 * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t13  = h__XO * h__XO;
    real_type t14  = k__XO * k__XO;
    return 1.0 / (t13 + t14 + 1) / (t1 * f__XO + g__XO * t4 + 1) * (-2 * retrograde__XO * k__XO * t1 + 2 * t4 * h__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t12  = t5 * t5;
    real_type t13  = f__XO * f__XO;
    real_type t15  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t8 * t5 + 2 * t5 * f__XO + 2 * t8 * g__XO + t13 * t12 - t15 * t12 + t15 + 1) * t5 * (retrograde__XO * k__XO * t5 - t8 * h__XO) / (t1 + t2 + 1);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t12  = t5 * t5;
    real_type t13  = f__XO * f__XO;
    real_type t15  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t8 * t5 + 2 * t5 * f__XO + 2 * t8 * g__XO + t13 * t12 - t15 * t12 + t15 + 1) * t8 * (retrograde__XO * k__XO * t5 - t8 * h__XO) / (t1 + t2 + 1);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    return 1.0 / t19 / (t7 * f__XO + t5 * g__XO + 1) * (t5 * (-2 * t1 + 2 * t2 + 2) + 4 * k__XO * retrograde__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    return 1.0 / t19 / (t5 * f__XO + t9 * g__XO + 1) * (-2 * t5 * (t1 - t2 + 1) * retrograde__XO - 4 * t9 * k__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t11  = h__XO * h__XO;
    real_type t12  = k__XO * k__XO;
    real_type t16  = t7 * t7;
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    return 1.0 / (2 * f__XO * g__XO * t5 * t7 + 2 * t7 * f__XO + 2 * t5 * g__XO + t17 * t16 - t19 * t16 + t19 + 1) / (t11 + t12 + 1) * (2 * g__XO * k__XO * retrograde__XO + 2 * t5 * k__XO * retrograde__XO + 2 * f__XO * h__XO + 2 * t7 * h__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_1_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    return -2 / (t8 + t9 + 1) / (t1 * f__XO + t4 * g__XO + 1) * t1 * k__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t13  = t6 * t6;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t9 * t6 + 2 * t6 * f__XO + 2 * t9 * g__XO + t14 * t13 - t16 * t13 + t16 + 1) * t6 * (retrograde__XO * k__XO * t6 - t9 * h__XO) / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t8   = t1 * t1;
    real_type t9   = f__XO * f__XO;
    real_type t11  = g__XO * g__XO;
    real_type t19  = t11 * g__XO;
    real_type t23  = 3 * t11;
    real_type t38  = h__XO * h__XO;
    real_type t39  = k__XO * k__XO;
    return 4 / (t38 + t39 + 1) / (t8 * t1 * (-3 * t11 * f__XO + t9 * f__XO) + t8 * (t4 * (3 * t9 * g__XO - t19) + 3 * t9 - t23) + 3 * t1 * (2 * t4 * g__XO + t11 + 1) * f__XO + t4 * (t19 + 3 * g__XO) + t23 + 1) * t8 * (-retrograde__XO * k__XO * t1 + t4 * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = sin(L__XO);
    real_type t6   = t1 * t1;
    real_type t10  = f__XO * f__XO;
    real_type t12  = g__XO * g__XO;
    real_type t20  = t12 * g__XO;
    real_type t24  = 3 * t12;
    real_type t39  = h__XO * h__XO;
    real_type t40  = k__XO * k__XO;
    return -4 / (t39 + t40 + 1) / (t6 * t1 * (t10 * f__XO - 3 * t12 * f__XO) + t6 * (t2 * (3 * t10 * g__XO - t20) + 3 * t10 - t24) + 3 * t1 * (2 * t2 * g__XO + t12 + 1) * f__XO + t2 * (t20 + 3 * g__XO) + t24 + 1) * t1 * (k__XO * retrograde__XO * t2 * t1 + h__XO * t6 - h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t8   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t14  = pow(t8 + t10 + 1, 2);
    real_type t17  = t1 * t1;
    real_type t18  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    return -2 / (2 * f__XO * g__XO * t7 * t1 + 2 * t1 * f__XO + 2 * t7 * g__XO + t18 * t17 - t20 * t17 + t20 + 1) / t14 * (2 * k__XO * retrograde__XO * h__XO * t1 + t10 * t7 - t8 * t7 + t7) * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t14  = pow(t1 + t2 + 1, 2);
    real_type t17  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    real_type t20  = t5 * t5;
    return 2 / (t20 * (t17 - t18) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t18 + 2 * t8 * g__XO + 1) / t14 * t5 * (t5 * (t1 - t2 + 1) * retrograde__XO + 2 * t8 * k__XO * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t9   = sin(L__XO);
    real_type t19  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    real_type t29  = t21 * g__XO;
    real_type t33  = 3 * t21;
    real_type t47  = h__XO * h__XO;
    real_type t48  = k__XO * k__XO;
    return -2 / (t47 + t48 + 1) / (t2 * t1 * (t19 * f__XO - 3 * t21 * f__XO) + t2 * (t9 * (3 * t19 * g__XO - t29) + 3 * t19 - t33) + 3 * t1 * (2 * t9 * g__XO + t21 + 1) * f__XO + t9 * (t29 + 3 * g__XO) + t33 + 1) * (2 * h__XO * t2 + t1 * (2 * g__XO * k__XO * retrograde__XO + 2 * t9 * k__XO * retrograde__XO + f__XO * h__XO) - t9 * h__XO * g__XO - h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t7   = t6 * t6;
    real_type t9   = f__XO * f__XO;
    real_type t11  = g__XO * g__XO;
    real_type t13  = sin(L__XO);
    return 2 / (2 * f__XO * g__XO * t13 * t6 + 2 * t6 * f__XO + 2 * t13 * g__XO - t11 * t7 + t9 * t7 + t11 + 1) * t7 * k__XO / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t13  = t6 * t6;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t9 * t6 + 2 * t6 * f__XO + 2 * t9 * g__XO + t14 * t13 - t16 * t13 + t16 + 1) * t9 * (retrograde__XO * k__XO * t6 - t9 * h__XO) / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t2   = t1 * t1;
    real_type t4   = cos(L__XO);
    real_type t9   = f__XO * f__XO;
    real_type t11  = g__XO * g__XO;
    real_type t15  = t4 * t4;
    real_type t20  = t11 * g__XO;
    real_type t24  = 3 * t11;
    real_type t39  = h__XO * h__XO;
    real_type t40  = k__XO * k__XO;
    return 4 / (t39 + t40 + 1) / (t15 * t4 * (-3 * t11 * f__XO + t9 * f__XO) + t15 * (t1 * (3 * t9 * g__XO - t20) + 3 * t9 - t24) + 3 * t4 * (2 * t1 * g__XO + t11 + 1) * f__XO + t1 * (t20 + 3 * g__XO) + t24 + 1) * (-retrograde__XO * k__XO * t4 + t1 * h__XO) * t2 * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = cos(L__XO);
    real_type t8   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t14  = pow(t8 + t10 + 1, 2);
    real_type t17  = t3 * t3;
    real_type t18  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    return -2 / (2 * f__XO * g__XO * t1 * t3 + 2 * t3 * f__XO + 2 * t1 * g__XO + t18 * t17 - t20 * t17 + t20 + 1) / t14 * (2 * k__XO * retrograde__XO * h__XO * t3 + t10 * t1 - t8 * t1 + t1) * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t14  = pow(t3 + t4 + 1, 2);
    real_type t17  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    real_type t20  = t7 * t7;
    return 2 / (t20 * (t17 - t18) + t7 * (2 * t1 * g__XO * f__XO + 2 * f__XO) + t18 + 2 * t1 * g__XO + 1) / t14 * (t7 * (t3 - t4 + 1) * retrograde__XO + 2 * t1 * k__XO * h__XO) * p__XO * t1;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t7   = k__XO * retrograde__XO;
    real_type t10  = sin(L__XO);
    real_type t21  = f__XO * f__XO;
    real_type t23  = g__XO * g__XO;
    real_type t31  = t23 * g__XO;
    real_type t35  = 3 * t23;
    real_type t49  = h__XO * h__XO;
    real_type t50  = k__XO * k__XO;
    return -2 / (t49 + t50 + 1) / (t2 * t1 * (t21 * f__XO - 3 * t23 * f__XO) + t2 * (t10 * (3 * t21 * g__XO - t31) + 3 * t21 - t35) + 3 * t1 * (2 * t10 * g__XO + t23 + 1) * f__XO + t10 * (t31 + 3 * g__XO) + t35 + 1) * p__XO * (retrograde__XO * t10 * g__XO * k__XO + 2 * t10 * h__XO * f__XO - t7 * f__XO * t1 + 2 * h__XO * t10 * t1 - 2 * retrograde__XO * k__XO * t2 + t7);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t9   = t8 * t7;
    real_type t10  = t7 * t7;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t9 + 2 * t7 * f__XO + 2 * t8 * g__XO + t11 * t10 - t13 * t10 + t13 + 1) * t9 * k__XO / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = sin(L__XO);
    real_type t18  = pow(t6 + t7 + 1, 2);
    return -2 / t18 / (t1 * f__XO + t9 * g__XO + 1) * (-2 * k__XO * retrograde__XO * h__XO * t1 + t9 * (t6 - t7 - 1)) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t21  = t1 + t2 + 1;
    real_type t22  = t21 * t21;
    return 4 / t22 / t21 / (t6 * f__XO + t10 * g__XO + 1) * (-3 * t6 * retrograde__XO * k__XO * (t1 - t2 / 3 - 1.0 / 3.0) + (t1 - 3 * t2 - 3) * t10 * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t21  = t2 + t3 + 1;
    real_type t22  = t21 * t21;
    return 4 / t22 / t21 / (t6 * f__XO + t9 * g__XO + 1) * (t6 * (t2 - 3 * t3 + 1) * h__XO * retrograde__XO + 3 * k__XO * (t2 - t3 / 3 - 1.0 / 3.0) * t9) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    real_type t21  = f__XO * f__XO;
    real_type t22  = g__XO * g__XO;
    real_type t24  = t4 * t4;
    return -2 / (t24 * (t21 - t22) + t4 * (2 * t7 * g__XO * f__XO + 2 * f__XO) + t22 + 2 * t7 * g__XO + 1) / t19 * (2 * g__XO * h__XO * k__XO * retrograde__XO + 2 * t7 * k__XO * retrograde__XO * h__XO + t3 * f__XO + t4 * t3) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t5   = sin(L__XO);
    real_type t10  = h__XO * h__XO;
    real_type t11  = k__XO * k__XO;
    real_type t13  = pow(t10 + t11 + 1, 2);
    return 4 / t13 / (t1 * f__XO + t5 * g__XO + 1) * k__XO * h__XO * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t18  = pow(t1 + t2 + 1, 2);
    return -2 / t18 / (t5 * f__XO + t8 * g__XO + 1) * (t5 * (t1 - t2 + 1) * retrograde__XO + 2 * t8 * k__XO * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t21  = t1 + t2 + 1;
    real_type t22  = t21 * t21;
    return -4 / t22 / t21 / (t6 * f__XO + t10 * g__XO + 1) * (-3 * t6 * retrograde__XO * (t1 - t2 / 3 + 1) * k__XO + (t1 - 3 * t2 + 1) * t10 * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = (t4 - t5 + 1) * retrograde__XO;
    real_type t8   = sin(L__XO);
    real_type t18  = pow(t4 + t5 + 1, 2);
    real_type t20  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    real_type t23  = t1 * t1;
    return -4 / (t23 * (t20 - t21) + t1 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t21 + 2 * t8 * g__XO + 1) / t18 * p__XO * (k__XO * h__XO * t1 - t8 * t7 / 2 - g__XO * t7 / 2 + f__XO * h__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t13  = pow(t1 + t2 + 1, 2);
    return -2 / t13 / (t5 * f__XO + g__XO * t7 + 1) * t5 * (t1 - t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sin(L__XO);
    real_type t6   = cos(L__XO);
    real_type t11  = h__XO * h__XO;
    real_type t12  = k__XO * k__XO;
    real_type t15  = t6 * t6;
    real_type t16  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t2 * t6 + 2 * t6 * f__XO + 2 * t2 * g__XO + t16 * t15 - t18 * t15 + t18 + 1) / (t11 + t12 + 1) * (g__XO * k__XO * retrograde__XO + t2 * k__XO * retrograde__XO + f__XO * h__XO + t6 * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = f__XO * k__XO * retrograde__XO;
    real_type t3   = g__XO * h__XO;
    real_type t6   = cos(L__XO);
    real_type t7   = t6 * t6;
    real_type t14  = sin(L__XO);
    real_type t16  = g__XO * g__XO;
    real_type t19  = f__XO * g__XO;
    real_type t21  = k__XO * retrograde__XO;
    real_type t26  = f__XO * f__XO;
    real_type t42  = t16 * g__XO;
    real_type t46  = 3 * t16;
    real_type t60  = h__XO * h__XO;
    real_type t61  = k__XO * k__XO;
    return 4 / (t60 + t61 + 1) / (t7 * t6 * (-3 * t16 * f__XO + t26 * f__XO) + t7 * (t14 * (3 * t26 * g__XO - t42) + 3 * t26 - t46) + 3 * t6 * (2 * t14 * g__XO + t16 + 1) * f__XO + t14 * (t42 + 3 * g__XO) + t46 + 1) * (t7 * (-t2 / 2 - t3 / 2) + t6 * (t14 * (-g__XO * k__XO * retrograde__XO / 2 + f__XO * h__XO / 2) - retrograde__XO * k__XO * t16 - h__XO * t19 + t21 / 2) + t14 * (t21 * t19 + h__XO * t26 - h__XO / 2) + t2 - t3 / 2) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t10  = t9 * t9;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    return 2 / (2 * f__XO * g__XO * t6 * t9 + 2 * t9 * f__XO + 2 * t6 * g__XO + t11 * t10 - t13 * t10 + t13 + 1) * (t6 + g__XO) * k__XO / (t1 + t2 + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    return -2 / (t9 + t10 + 1) / (t2 * f__XO + t4 * g__XO + 1) * t2 * p__XO * k__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_7_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = sin(L__XO);
    real_type t12  = k__XO * retrograde__XO;
    real_type t15  = cos(L__XO);
    return -1.0 / (t6 + t7 + 1) * (t9 * (t6 - t7 + 1) - 2 * t12 * f__XO * h__XO - 2 * t12 * h__XO * t15 + t6 * g__XO - t7 * g__XO + g__XO) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = sin(L__XO);
    real_type t7   = k__XO * retrograde__XO;
    real_type t10  = cos(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = sqrt(p__XO);
    return 1.0 / (2 * t1 + 2 * t2 + 2) / t20 / p__XO * t18 * (t4 * (t1 - t2 + 1) - 2 * t7 * f__XO * h__XO - 2 * t7 * h__XO * t10 + t1 * g__XO - t2 * g__XO + g__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t9   = k__XO * retrograde__XO;
    real_type t22  = sqrt(ModelPars[0]);
    real_type t24  = p__XO * p__XO;
    real_type t25  = sqrt(p__XO);
    return 1.0 / (4 * t1 + 4 * t2 + 4) / t25 / t24 * t22 * (t5 * (-3 * t1 + 3 * t2 - 3) + 6 * t9 * h__XO * t7 + 6 * t9 * f__XO * h__XO - 3 * t1 * g__XO + 3 * t2 * g__XO - 3 * g__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t4   = sqrt(ModelPars[0]);
    real_type t5   = sqrt(p__XO);
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    return -1.0 / (t9 + t10 + 1) / t5 / p__XO * t4 * h__XO * k__XO * retrograde__XO;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sqrt(ModelPars[0]);
    real_type t7   = sqrt(p__XO);
    return 1.0 / (2 * t1 + 2 * t2 + 2) / t7 / p__XO * t5 * (t1 - t2 + 1);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = sqrt(p__XO);
    real_type t25  = pow(t1 + t2 + 1, 2);
    return 1.0 / t25 / t20 / p__XO * k__XO * t18 * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t30  = sqrt(p__XO);
    real_type t34  = pow(t4 + t5 + 1, 2);
    return -1.0 / t34 / t30 / p__XO * (t7 * (t4 - t5 + 1) * h__XO * retrograde__XO + t13 * (2 * k__XO * t4 + 2 * k__XO) + retrograde__XO * t4 * h__XO * f__XO + 2 * k__XO * t4 * g__XO + h__XO * (-retrograde__XO * t5 * f__XO + f__XO * retrograde__XO) + 2 * g__XO * k__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t13  = sqrt(ModelPars[0]);
    real_type t15  = sqrt(p__XO);
    return 1.0 / (2 * t1 + 2 * t2 + 2) / t15 / p__XO * t13 * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t5   = cos(L__XO);
    real_type t7   = sqrt(p__XO);
    real_type t11  = h__XO * h__XO;
    real_type t12  = k__XO * k__XO;
    return -1.0 / (t11 + t12 + 1) / t7 / p__XO * (t5 + f__XO) * k__XO * h__XO * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    return 2 / (t8 + t9 + 1) * retrograde__XO * k__XO * h__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t5   = h__XO * h__XO;
    real_type t6   = k__XO * k__XO;
    real_type t8   = sqrt(p__XO);
    real_type t12  = pow(t5 + t6 + 1, 2);
    return -2 / t12 / t8 * (t5 - t6 - 1) * retrograde__XO * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t5   = h__XO * h__XO;
    real_type t6   = k__XO * k__XO;
    real_type t8   = sqrt(p__XO);
    real_type t12  = pow(t5 + t6 + 1, 2);
    return 2 / t12 / t8 * (t5 - t6 + 1) * retrograde__XO * h__XO * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return 2 / (t7 + t8 + 1) * k__XO * h__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    return -1.0 / (t6 + t7 + 1) * (t6 - t7 + 1) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = k__XO * k__XO;
    real_type t5   = sqrt(p__XO);
    real_type t8   = h__XO * h__XO;
    real_type t10  = pow(t8 + t4 + 1, 2);
    return -4 / t10 / t5 * t4 * t2 * h__XO;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = h__XO * h__XO;
    real_type t6   = sqrt(p__XO);
    real_type t9   = k__XO * k__XO;
    real_type t11  = pow(t4 + t9 + 1, 2);
    return 4 / t11 / t6 * (t4 + 1) * t2 * k__XO;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = sqrt(p__XO);
    real_type t24  = pow(t1 + t2 + 1, 2);
    return -2 / t24 / t20 * k__XO * t18 * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t5   = h__XO * h__XO;
    real_type t6   = k__XO * k__XO;
    real_type t9   = cos(L__XO);
    real_type t14  = t6 * k__XO;
    real_type t16  = sin(L__XO);
    real_type t19  = f__XO * h__XO;
    real_type t31  = sqrt(p__XO);
    real_type t34  = t5 + t6 + 1;
    real_type t35  = t34 * t34;
    return 4 / t35 / t34 / t31 * (t9 * (t5 - 3 * t6 - 3) * retrograde__XO * h__XO + t16 * (3 * k__XO * t5 - k__XO - t14) - t14 * g__XO - 3 * retrograde__XO * t6 * t19 + k__XO * (3 * t5 * g__XO - g__XO) + (t5 - 3) * retrograde__XO * t19) * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = t1 * t1;
    real_type t3   = k__XO * k__XO;
    real_type t6   = t3 * t3;
    real_type t9   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t38  = sqrt(ModelPars[0]);
    real_type t40  = sqrt(p__XO);
    real_type t42  = t1 + t3 + 1;
    real_type t43  = t42 * t42;
    return -2 / t43 / t42 / t40 * t38 * (t9 * (-6 * t3 * t1 + t2 + t6 - 1) * retrograde__XO + 4 * t13 * (t1 - t3 + 1) * k__XO * h__XO + retrograde__XO * t2 * f__XO + 4 * k__XO * t1 * h__XO * g__XO - 6 * retrograde__XO * t3 * t1 * f__XO + h__XO * (-4 * t3 * k__XO * g__XO + 4 * g__XO * k__XO) + retrograde__XO * t6 * f__XO - f__XO * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t15  = sqrt(p__XO);
    real_type t19  = pow(t3 + t4 + 1, 2);
    return 2 / t19 * k__XO / t15 * (t7 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t9) * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = pow(t7 + t8 + 1, 2);
    real_type t14  = cos(L__XO);
    return -2 * (t14 + f__XO) * (t7 - t8 - 1) / t10 / t4 * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t30  = sqrt(p__XO);
    real_type t33  = pow(t4 + t5 + 1, 2);
    return 2 / t33 / t30 * (t7 * (t4 - t5 + 1) * h__XO * retrograde__XO + t13 * (2 * k__XO * t4 + 2 * k__XO) + retrograde__XO * t4 * h__XO * f__XO + 2 * k__XO * t4 * g__XO + h__XO * (-retrograde__XO * t5 * f__XO + f__XO * retrograde__XO) + 2 * g__XO * k__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t9   = sin(L__XO);
    real_type t16  = cos(L__XO);
    real_type t19  = t3 * t3;
    real_type t39  = sqrt(p__XO);
    real_type t41  = t3 + t5 + 1;
    real_type t42  = t41 * t41;
    return -12 / t42 / t41 / t39 * (-t9 * (t3 - 3 * t5 + 1) * (t3 + 1) / 3 + t16 * (t3 - t5 / 3 + 1) * k__XO * retrograde__XO * h__XO - t19 * g__XO / 3 + k__XO * retrograde__XO * t3 * h__XO * f__XO + t3 * (t5 - 2.0 / 3.0) * g__XO - h__XO * (t5 - 3) * retrograde__XO * f__XO * k__XO / 3 + (t5 - 1.0 / 3.0) * g__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t15  = sqrt(ModelPars[0]);
    real_type t17  = sqrt(p__XO);
    real_type t20  = pow(t2 + t3 + 1, 2);
    return -2 / t20 / t17 * t15 * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO - 2 * (t2 + 1) * t8 * k__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t14  = cos(L__XO);
    return 2 * (t14 + f__XO) * (t6 - t7 + 1) * h__XO / t9 / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t13  = sqrt(ModelPars[0]);
    real_type t15  = sqrt(p__XO);
    return 1.0 / (t1 + t2 + 1) / t15 * t13 * (t4 * (-t1 + t2 - 1) - 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = sin(L__XO);
    real_type t6   = cos(L__XO);
    real_type t13  = sqrt(ModelPars[0]);
    real_type t15  = sqrt(p__XO);
    return 1.0 / (t1 + t2 + 1) / t15 * t13 * (t4 * (t1 - t2 + 1) - 2 * k__XO * retrograde__XO * h__XO * t6);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sin(L__XO);
    real_type t5   = sqrt(ModelPars[0]);
    real_type t6   = sqrt(p__XO);
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    return -2 / (t9 + t10 + 1) / t6 * t5 * t2 * k__XO * h__XO;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t12  = cos(L__XO);
    return 2 * (t12 + f__XO) * k__XO * h__XO / (t6 + t7 + 1) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_7_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t5   = t3 - t4 - 1;
    real_type t7   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t20  = sqrt(p__XO);
    return -2 / (t3 + t4 + 1) / t20 * (t7 * t5 * retrograde__XO / 2 + t11 * k__XO * h__XO + retrograde__XO * t5 * f__XO / 2 + g__XO * h__XO * k__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = sqrt(p__XO);
    return 1.0 / (2 * t1 + 2 * t2 + 2) / t20 / p__XO * t18 * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = p__XO * p__XO;
    real_type t21  = sqrt(p__XO);
    return -3 / (4 * t1 + 4 * t2 + 4) / t21 / t20 * t18 * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = sqrt(ModelPars[0]);
    real_type t7   = sqrt(p__XO);
    return 1.0 / (2 * t1 + 2 * t2 + 2) / t7 / p__XO * t6 * (t1 - t2 - 1) * retrograde__XO;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t3   = sqrt(ModelPars[0]);
    real_type t4   = sqrt(p__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    return 1.0 / (t8 + t9 + 1) / t4 / p__XO * t3 * k__XO * h__XO;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t18  = f__XO * h__XO;
    real_type t28  = sqrt(p__XO);
    real_type t32  = pow(t3 + t4 + 1, 2);
    return 2 / t32 / t28 / p__XO * (-t7 * (t3 - t4 - 1) * k__XO / 2 + (t4 + 1) * t11 * retrograde__XO * h__XO + t4 * k__XO * g__XO / 2 + retrograde__XO * t4 * t18 + k__XO * (-t3 * g__XO / 2 + g__XO / 2) + retrograde__XO * t18) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t23  = sqrt(ModelPars[0]);
    real_type t25  = sqrt(p__XO);
    real_type t29  = pow(t1 + t2 + 1, 2);
    return 1.0 / t29 / t25 / p__XO * t23 * (t5 * (t1 - t2 + 1) * h__XO - 2 * k__XO * retrograde__XO * t1 * t7 + t1 * h__XO * g__XO - 2 * t1 * retrograde__XO * f__XO * k__XO + h__XO * (-t2 * g__XO + g__XO));
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t15  = sqrt(p__XO);
    return -1.0 / (2 * t3 + 2 * t4 + 2) / t15 / p__XO * (t7 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t9) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t9   = sqrt(p__XO);
    return 1.0 / (2 * t3 + 2 * t4 + 2) / t9 / p__XO * (t7 + f__XO) * (t3 - t4 - 1) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = sqrt(p__XO);
    return -1.0 / (t4 + t5 + 1) / t7 * (t4 - t5 - 1) * retrograde__XO * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t5   = k__XO * k__XO;
    real_type t7   = sqrt(p__XO);
    real_type t10  = h__XO * h__XO;
    real_type t12  = pow(t10 + t5 + 1, 2);
    return -4 / t12 / t7 * (t5 + 1) * retrograde__XO * h__XO * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    real_type t11  = pow(t6 + t9 + 1, 2);
    return 4 / t11 * retrograde__XO * k__XO * t6 / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sqrt(p__XO);
    return -1.0 / (t3 + t4 + 1) / t7 * (t3 - t4 - 1) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return -2 / (t7 + t8 + 1) * k__XO * h__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = sqrt(ModelPars[0]);
    real_type t7   = sqrt(p__XO);
    real_type t11  = pow(t1 + t2 + 1, 2);
    return 2 / t11 / t7 * t6 * k__XO * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t10  = pow(t6 + t7 + 1, 2);
    return -2 * h__XO / t10 * (t6 - t7 + 1) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t18  = f__XO * h__XO;
    real_type t28  = sqrt(p__XO);
    real_type t31  = pow(t3 + t4 + 1, 2);
    return -4 / t31 / t28 * (-t7 * (t3 - t4 - 1) * k__XO / 2 + (t4 + 1) * t11 * retrograde__XO * h__XO + t4 * k__XO * g__XO / 2 + retrograde__XO * t4 * t18 + k__XO * (-t3 * g__XO / 2 + g__XO / 2) + retrograde__XO * t18) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t17  = t2 * t2;
    real_type t21  = g__XO * h__XO;
    real_type t24  = f__XO * retrograde__XO;
    real_type t36  = sqrt(ModelPars[0]);
    real_type t38  = sqrt(p__XO);
    real_type t40  = t1 + t2 + 1;
    real_type t41  = t40 * t40;
    return 12 / t41 / t40 / t38 * t36 * (t7 * retrograde__XO * (t2 + 1) * (t1 - t2 / 3 - 1.0 / 3.0) - t13 * (t1 - 3 * t2 - 3) * k__XO * h__XO / 3 - retrograde__XO * t17 * f__XO / 3 + t2 * k__XO * t21 + t2 * (t1 - 2.0 / 3.0) * t24 - k__XO * (t1 - 3) * t21 / 3 + (t1 - 1.0 / 3.0) * t24);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = t3 * t3;
    real_type t6   = k__XO * k__XO;
    real_type t9   = t6 * t6;
    real_type t12  = sin(L__XO);
    real_type t17  = cos(L__XO);
    real_type t39  = sqrt(p__XO);
    real_type t41  = t3 + t6 + 1;
    real_type t42  = t41 * t41;
    return -8 / t42 / t41 / t39 * (t12 * (-t4 / 4 + 3.0 / 2.0 * t6 * t3 - t9 / 4 + 1.0 / 4.0) + t17 * (t3 - t6 - 1) * k__XO * retrograde__XO * h__XO - t4 * g__XO / 4 + k__XO * retrograde__XO * t3 * h__XO * f__XO + 3.0 / 2.0 * t6 * t3 * g__XO - h__XO * (t6 + 1) * retrograde__XO * f__XO * k__XO - t9 * g__XO / 4 + g__XO / 4) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t17  = sqrt(p__XO);
    real_type t20  = pow(t3 + t4 + 1, 2);
    return 4 / t20 / t17 * (t7 * (t3 - t4 - 1) * k__XO / 2 + (t4 + 1) * t11 * retrograde__XO * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t14  = cos(L__XO);
    return -4 * (t14 + f__XO) * (t7 + 1) * h__XO / t9 / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = k__XO * retrograde__XO;
    real_type t5   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = sqrt(p__XO);
    real_type t24  = pow(t5 + t7 + 1, 2);
    return 2 / t24 / t20 * h__XO * t18 * (2 * t2 * f__XO * h__XO + 2 * t2 * h__XO * t9 - t5 * g__XO + t7 * g__XO - t5 * t13 + t7 * t13 - g__XO - t13);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * retrograde__XO;
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t16  = sin(L__XO);
    real_type t33  = sqrt(p__XO);
    real_type t36  = t4 + t5 + 1;
    real_type t37  = t36 * t36;
    return 4 / t37 / t36 / t33 * h__XO * (t8 * (t4 - 3 * t5 + 1) * t3 + t16 * (3 * k__XO * t4 - t5 * k__XO + 3 * k__XO) + retrograde__XO * t4 * h__XO * f__XO + 3 * k__XO * t4 * g__XO - 3 * t3 * f__XO * (t5 - 1.0 / 3.0) - (t5 - 3) * k__XO * g__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t15  = sqrt(ModelPars[0]);
    real_type t17  = sqrt(p__XO);
    real_type t20  = pow(t1 + t2 + 1, 2);
    return 1.0 / t20 / t17 * t15 * (-2 * t5 * (t1 - t2 + 1) * h__XO - 4 * t9 * k__XO * t1 * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t5   = sqrt(p__XO);
    real_type t8   = k__XO * k__XO;
    real_type t10  = pow(t3 + t8 + 1, 2);
    real_type t13  = cos(L__XO);
    return 4 * (t13 + f__XO) * k__XO / t10 / t5 * t3 * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t15  = sqrt(p__XO);
    return 1.0 / (t3 + t4 + 1) / t15 * (t7 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t9) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t15  = sqrt(p__XO);
    return 1.0 / (t3 + t4 + 1) / t15 * (t7 * (t3 - t4 - 1) * retrograde__XO + 2 * t10 * k__XO * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t8   = sqrt(p__XO);
    return 1.0 / (t3 + t4 + 1) / t8 * t7 * (t3 - t4 - 1) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t9   = sqrt(p__XO);
    return -1.0 / (t3 + t4 + 1) / t9 * (t7 + f__XO) * (t3 - t4 - 1) * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_7_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t13  = sqrt(p__XO);
    real_type t15  = h__XO * h__XO;
    real_type t16  = k__XO * k__XO;
    return 2 / (t15 + t16 + 1) / t13 * (g__XO * k__XO * retrograde__XO + t4 * k__XO * retrograde__XO + f__XO * h__XO + t8 * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t13  = sqrt(p__XO);
    real_type t16  = h__XO * h__XO;
    real_type t17  = k__XO * k__XO;
    return -1.0 / (t16 + t17 + 1) / t13 / p__XO * (g__XO * k__XO * retrograde__XO + t4 * k__XO * retrograde__XO + f__XO * h__XO + t8 * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t13  = p__XO * p__XO;
    real_type t14  = sqrt(p__XO);
    real_type t17  = h__XO * h__XO;
    real_type t18  = k__XO * k__XO;
    return 3 / (2 * t17 + 2 * t18 + 2) / t14 / t13 * (g__XO * k__XO * retrograde__XO + t4 * k__XO * retrograde__XO + f__XO * h__XO + t8 * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return -1.0 / (t7 + t8 + 1) / t4 / p__XO * h__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sqrt(p__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    return -1.0 / (t8 + t9 + 1) / t4 / p__XO * retrograde__XO * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t8   = sin(L__XO);
    real_type t12  = h__XO * h__XO;
    real_type t13  = k__XO * k__XO;
    real_type t15  = cos(L__XO);
    real_type t25  = pow(t12 + t13 + 1, 2);
    return 1.0 / t25 * (2 * t8 * k__XO * retrograde__XO * h__XO + t15 * (t12 - t13 - 1) + 2 * g__XO * h__XO * k__XO * retrograde__XO + t12 * f__XO - t13 * f__XO - f__XO) / t3 / p__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = (t4 - t5 + 1) * retrograde__XO;
    real_type t8   = sin(L__XO);
    real_type t17  = sqrt(ModelPars[0]);
    real_type t19  = sqrt(p__XO);
    real_type t23  = pow(t4 + t5 + 1, 2);
    return 2 / t23 / t19 / p__XO * t17 * (k__XO * h__XO * t1 - t8 * t7 / 2 - g__XO * t7 / 2 + f__XO * h__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = cos(L__XO);
    real_type t6   = sin(L__XO);
    real_type t10  = sqrt(p__XO);
    real_type t13  = h__XO * h__XO;
    real_type t14  = k__XO * k__XO;
    return -1.0 / (t13 + t14 + 1) / t10 / p__XO * (retrograde__XO * k__XO * t3 - t6 * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t12  = sin(L__XO);
    return -(t12 + g__XO) * k__XO / (t7 + t8 + 1) / t3 / p__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    return 2 / (t6 + t7 + 1) * h__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sqrt(ModelPars[0]);
    real_type t7   = sqrt(p__XO);
    real_type t10  = pow(t1 + t2 + 1, 2);
    return -2 / t10 / t7 * t5 * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    return -4 * k__XO / t9 * h__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return 2 / (t7 + t8 + 1) * retrograde__XO * k__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = pow(t7 + t8 + 1, 2);
    return -4 * h__XO / t10 * retrograde__XO * k__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = sqrt(p__XO);
    real_type t11  = pow(t4 + t5 + 1, 2);
    return 2 / t11 / t7 * (t4 - t5 + 1) * retrograde__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    return 2 / (t6 + t7 + 1) * k__XO / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t7   = sin(L__XO);
    real_type t11  = h__XO * h__XO;
    real_type t12  = k__XO * k__XO;
    real_type t14  = cos(L__XO);
    real_type t24  = pow(t11 + t12 + 1, 2);
    return -2 / t24 * (2 * t7 * k__XO * retrograde__XO * h__XO + t14 * (t11 - t12 - 1) + 2 * g__XO * h__XO * k__XO * retrograde__XO + t11 * f__XO - t12 * f__XO - f__XO) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t11  = cos(L__XO);
    real_type t16  = sin(L__XO);
    real_type t35  = t6 + t7 + 1;
    real_type t36  = t35 * t35;
    return 4 / t36 / t35 * (t11 * (t6 - 3 * t7 - 3) * h__XO + 3 * t16 * retrograde__XO * k__XO * (t6 - t7 / 3 - 1.0 / 3.0) + t6 * h__XO * f__XO + 3 * k__XO * retrograde__XO * t6 * g__XO + h__XO * (-3 * t7 * f__XO - 3 * f__XO) - (t7 + 1) * retrograde__XO * g__XO * k__XO) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t11  = cos(L__XO);
    real_type t14  = sin(L__XO);
    real_type t35  = t6 + t7 + 1;
    real_type t36  = t35 * t35;
    return 12 / t36 / t35 * (t11 * k__XO * (t6 - t7 / 3 - 1.0 / 3.0) - (t6 - 3 * t7 + 1) * t14 * retrograde__XO * h__XO / 3 - retrograde__XO * t6 * h__XO * g__XO / 3 + k__XO * t6 * f__XO + h__XO * (t7 - 1.0 / 3.0) * g__XO * retrograde__XO - (t7 + 1) * k__XO * f__XO / 3) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t14  = sqrt(ModelPars[0]);
    real_type t16  = sqrt(p__XO);
    real_type t19  = pow(t1 + t2 + 1, 2);
    return 1.0 / t19 / t16 * t14 * (t5 * (2 * t1 - 2 * t2 - 2) - 4 * k__XO * retrograde__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t13  = sin(L__XO);
    return -4 * (t13 + g__XO) * k__XO * h__XO / t9 / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = (t4 - t5 + 1) * retrograde__XO;
    real_type t8   = sin(L__XO);
    real_type t17  = sqrt(ModelPars[0]);
    real_type t19  = sqrt(p__XO);
    real_type t22  = pow(t4 + t5 + 1, 2);
    return -4 / t22 / t19 * t17 * (k__XO * h__XO * t1 - t8 * t7 / 2 - g__XO * t7 / 2 + f__XO * h__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t11  = cos(L__XO);
    real_type t16  = sin(L__XO);
    real_type t35  = t6 + t7 + 1;
    real_type t36  = t35 * t35;
    return -4 / t36 / t35 * (t11 * (t6 - 3 * t7 + 1) * h__XO + 3 * t16 * retrograde__XO * (t6 - t7 / 3 + 1) * k__XO + t6 * h__XO * f__XO + 3 * k__XO * retrograde__XO * t6 * g__XO + h__XO * (-3 * t7 * f__XO + f__XO) - (t7 - 3) * retrograde__XO * g__XO * k__XO) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t15  = sqrt(p__XO);
    real_type t18  = pow(t3 + t4 + 1, 2);
    return 2 / t18 / t15 * (t7 * (t3 - t4 + 1) * retrograde__XO + 2 * t10 * k__XO * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = sqrt(p__XO);
    real_type t13  = pow(t3 + t4 + 1, 2);
    return 2 / t13 / t9 * (t7 + g__XO) * (t3 - t4 + 1) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = cos(L__XO);
    real_type t6   = sin(L__XO);
    real_type t10  = sqrt(p__XO);
    real_type t12  = h__XO * h__XO;
    real_type t13  = k__XO * k__XO;
    return 2 / (t12 + t13 + 1) / t10 * (retrograde__XO * k__XO * t3 - t6 * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sin(L__XO);
    real_type t6   = cos(L__XO);
    real_type t10  = sqrt(p__XO);
    real_type t12  = h__XO * h__XO;
    real_type t13  = k__XO * k__XO;
    return -2 / (t12 + t13 + 1) / t10 * (t4 * k__XO * retrograde__XO + t6 * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = cos(L__XO);
    real_type t5   = sqrt(p__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    return 2 / (t8 + t9 + 1) / t5 * t4 * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t11  = sin(L__XO);
    return 2 * (t11 + g__XO) * k__XO / (t6 + t7 + 1) / t3 * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_7_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::norm_reg( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    return sqrt(t1 + t2 + t3 + t5);
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    real_type t7   = sqrt(t1 + t2 + t3 + t5);
    return x__XO / t7;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1_1( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = y__XO * y__XO;
    real_type t2   = z__XO * z__XO;
    real_type t4   = ModelPars[4] * ModelPars[4];
    real_type t6   = x__XO * x__XO;
    real_type t7   = t6 + t1 + t2 + t4;
    real_type t8   = sqrt(t7);
    return 1.0 / t8 / t7 * (t1 + t2 + t4);
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1_2( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    real_type t6   = t1 + t2 + t3 + t5;
    real_type t7   = sqrt(t6);
    return -y__XO * x__XO / t7 / t6;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_1_3( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    real_type t6   = t1 + t2 + t3 + t5;
    real_type t7   = sqrt(t6);
    return -z__XO * x__XO / t7 / t6;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_2( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    real_type t7   = sqrt(t1 + t2 + t3 + t5);
    return y__XO / t7;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_2_2( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = z__XO * z__XO;
    real_type t4   = ModelPars[4] * ModelPars[4];
    real_type t6   = y__XO * y__XO;
    real_type t7   = t6 + t1 + t2 + t4;
    real_type t8   = sqrt(t7);
    return 1.0 / t8 / t7 * (t1 + t2 + t4);
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_2_3( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    real_type t6   = t1 + t2 + t3 + t5;
    real_type t7   = sqrt(t6);
    return -z__XO * y__XO / t7 / t6;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_3( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t3   = z__XO * z__XO;
    real_type t5   = ModelPars[4] * ModelPars[4];
    real_type t7   = sqrt(t1 + t2 + t3 + t5);
    return z__XO / t7;
  }

  real_type
  gtocX_2burn_pars::norm_reg_D_3_3( real_type x__XO, real_type y__XO, real_type z__XO ) const {
    real_type t1   = x__XO * x__XO;
    real_type t2   = y__XO * y__XO;
    real_type t4   = ModelPars[4] * ModelPars[4];
    real_type t6   = z__XO * z__XO;
    real_type t7   = t1 + t2 + t6 + t4;
    real_type t8   = sqrt(t7);
    return 1.0 / t8 / t7 * (t1 + t2 + t4);
  }

  real_type
  gtocX_2burn_pars::ray( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = sin(L__XO);
    return 1.0 / (t1 * f__XO + t3 * g__XO + 1) * p__XO;
  }

  real_type
  gtocX_2burn_pars::ray_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = sin(L__XO);
    return 1.0 / (t1 * f__XO + t3 * g__XO + 1);
  }

  real_type
  gtocX_2burn_pars::ray_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t3   = f__XO * f__XO;
    real_type t5   = g__XO * g__XO;
    real_type t7   = sin(L__XO);
    return -1.0 / (2 * f__XO * g__XO * t7 * t1 + 2 * t1 * f__XO + 2 * t7 * g__XO + t3 * t2 - t5 * t2 + t5 + 1) * t1;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t2   = cos(L__XO);
    real_type t3   = t2 * t2;
    real_type t4   = f__XO * f__XO;
    real_type t6   = g__XO * g__XO;
    return -1.0 / (2 * f__XO * g__XO * t1 * t2 + 2 * t2 * f__XO + 2 * t1 * g__XO + t4 * t3 - t6 * t3 + t6 + 1) * t1;
  }

  real_type
  gtocX_2burn_pars::ray_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = cos(L__XO);
    real_type t6   = t3 * t3;
    real_type t7   = f__XO * f__XO;
    real_type t9   = g__XO * g__XO;
    return 1.0 / (2 * f__XO * g__XO * t1 * t3 + 2 * t3 * f__XO + 2 * t1 * g__XO + t7 * t6 - t9 * t6 + t9 + 1) * (t1 * f__XO - t3 * g__XO);
  }

  real_type
  gtocX_2burn_pars::ray_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = t1 * t1;
    real_type t4   = f__XO * f__XO;
    real_type t6   = g__XO * g__XO;
    real_type t8   = sin(L__XO);
    return -1.0 / (2 * f__XO * g__XO * t8 * t1 + 2 * t1 * f__XO + 2 * t8 * g__XO + t4 * t3 - t6 * t3 + t6 + 1) * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::ray_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t4   = f__XO * f__XO;
    real_type t6   = g__XO * g__XO;
    real_type t14  = t6 * g__XO;
    real_type t16  = sin(L__XO);
    real_type t19  = 3 * t6;
    return 2 / (t2 * t1 * (t4 * f__XO - 3 * t6 * f__XO) + t2 * (t16 * (3 * t4 * g__XO - t14) + 3 * t4 - t19) + 3 * t1 * (2 * t16 * g__XO + t6 + 1) * f__XO + t16 * (t14 + 3 * g__XO) + t19 + 1) * t2 * p__XO;
  }

  real_type
  gtocX_2burn_pars::ray_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = sin(L__XO);
    real_type t4   = f__XO * f__XO;
    real_type t6   = g__XO * g__XO;
    real_type t10  = t1 * t1;
    real_type t15  = t6 * g__XO;
    real_type t19  = 3 * t6;
    return 2 / (t10 * t1 * (t4 * f__XO - 3 * t6 * f__XO) + t10 * (t3 * (3 * t4 * g__XO - t15) + 3 * t4 - t19) + 3 * t1 * (2 * t3 * g__XO + t6 + 1) * f__XO + t3 * (t15 + 3 * g__XO) + t19 + 1) * t3 * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::ray_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t4   = sin(L__XO);
    real_type t9   = f__XO * f__XO;
    real_type t11  = g__XO * g__XO;
    real_type t19  = t11 * g__XO;
    real_type t23  = 3 * t11;
    return -1.0 / (t2 * t1 * (-3 * t11 * f__XO + t9 * f__XO) + t2 * (t4 * (3 * t9 * g__XO - t19) + 3 * t9 - t23) + 3 * t1 * (2 * t4 * g__XO + t11 + 1) * f__XO + t4 * (t19 + 3 * g__XO) + t23 + 1) * p__XO * (f__XO * t4 * t1 - g__XO * t2 - g__XO - t4);
  }

  real_type
  gtocX_2burn_pars::ray_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = cos(L__XO);
    real_type t4   = t3 * t3;
    real_type t5   = f__XO * f__XO;
    real_type t7   = g__XO * g__XO;
    return -1.0 / (2 * f__XO * g__XO * t1 * t3 + 2 * t3 * f__XO + 2 * t1 * g__XO + t5 * t4 - t7 * t4 + t7 + 1) * t1 * p__XO;
  }

  real_type
  gtocX_2burn_pars::ray_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t6   = f__XO * f__XO;
    real_type t8   = g__XO * g__XO;
    real_type t16  = t8 * g__XO;
    real_type t18  = sin(L__XO);
    real_type t21  = 3 * t8;
    return 1.0 / (t2 * t1 * (t6 * f__XO - 3 * t8 * f__XO) + t2 * (t18 * (3 * t6 * g__XO - t16) + 3 * t6 - t21) + 3 * t1 * (2 * t18 * g__XO + t8 + 1) * f__XO + t18 * (t16 + 3 * g__XO) + t21 + 1) * (-2 * t2 * p__XO + 2 * p__XO);
  }

  real_type
  gtocX_2burn_pars::ray_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t4   = sin(L__XO);
    real_type t5   = t4 * g__XO;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t21  = t13 * g__XO;
    real_type t25  = 3 * t13;
    return 1.0 / (t2 * t1 * (t11 * f__XO - 3 * t13 * f__XO) + t2 * (t4 * (3 * t11 * g__XO - t21) + 3 * t11 - t25) + 3 * t1 * (t13 + 2 * t5 + 1) * f__XO + t4 * (t21 + 3 * g__XO) + t25 + 1) * p__XO * (f__XO * t2 + t1 * (t5 - 1) - 2 * f__XO);
  }

  real_type
  gtocX_2burn_pars::ray_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = cos(L__XO);
    real_type t7   = f__XO * f__XO;
    real_type t8   = g__XO * g__XO;
    real_type t10  = t3 * t3;
    return 1.0 / (t10 * (t7 - t8) + t3 * (2 * t1 * g__XO * f__XO + 2 * f__XO) + t8 + 2 * t1 * g__XO + 1) * (t1 * f__XO - g__XO * t3) * p__XO;
  }

  real_type
  gtocX_2burn_pars::ray_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO ) const {
    real_type t1   = f__XO * f__XO;
    real_type t2   = g__XO * g__XO;
    real_type t4   = cos(L__XO);
    real_type t5   = t4 * t4;
    real_type t8   = sin(L__XO);
    real_type t14  = t8 * g__XO;
    real_type t25  = t2 * g__XO;
    real_type t29  = 3 * t2;
    return -1.0 / (t5 * t4 * (t1 * f__XO - 3 * f__XO * t2) + t5 * (t8 * (3 * t1 * g__XO - t25) + 3 * t1 - t29) + 3 * t4 * (t2 + 2 * t14 + 1) * f__XO + t8 * (t25 + 3 * g__XO) + t29 + 1) * p__XO * (t5 * (t1 - t2) + t4 * (2 * t8 * g__XO * f__XO - f__XO) - 2 * t1 - t2 - t14);
  }

  real_type
  gtocX_2burn_pars::vel( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t5   = sin(L__XO);
    return sqrt(1.0 / p__XO * ((2 * t1 + f__XO) * f__XO + (2 * t5 + g__XO) * g__XO + 1) * muS__XO);
  }

  real_type
  gtocX_2burn_pars::vel_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sqrt(p__XO);
    real_type t6   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t12  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t15  = sqrt(2 * t6 * f__XO + 2 * t9 * g__XO + t12 + t13 + 1);
    return -t15 / t2 / p__XO * t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = p__XO * p__XO;
    real_type t3   = sqrt(p__XO);
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = sqrt(2 * t7 * f__XO + 2 * t10 * g__XO + t13 + t14 + 1);
    return 3.0 / 4.0 * t16 / t3 / t2 * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sqrt(p__XO);
    real_type t6   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = sqrt(2 * t6 * f__XO + 2 * t10 * g__XO + t13 + t14 + 1);
    return -1.0 / t16 * (t6 + f__XO) / t2 / p__XO * t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sqrt(p__XO);
    real_type t6   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = sqrt(2 * t8 * f__XO + 2 * t6 * g__XO + t13 + t14 + 1);
    return -1.0 / t16 * (t6 + g__XO) / t2 / p__XO * t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sqrt(p__XO);
    real_type t6   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = sqrt(2 * t8 * f__XO + 2 * t6 * g__XO + t15 + t16 + 1);
    return -1.0 / t18 * (-t6 * f__XO + t8 * g__XO) / t2 / p__XO * t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t3   = sqrt(p__XO);
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = sqrt(2 * t7 * f__XO + 2 * t10 * g__XO + t13 + t14 + 1);
    return -t16 / t3 / p__XO / t1 / 4;
  }

  real_type
  gtocX_2burn_pars::vel_D_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = cos(L__XO);
    real_type t5   = sqrt(p__XO);
    real_type t9   = sin(L__XO);
    real_type t12  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t15  = sqrt(2 * f__XO * t2 + 2 * t9 * g__XO + t12 + t13 + 1);
    return 1.0 / t15 / t5 * (t2 + f__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = cos(L__XO);
    real_type t3   = t2 * t2;
    real_type t4   = sin(L__XO);
    real_type t6   = 2 * t4 * g__XO;
    real_type t7   = g__XO * g__XO;
    real_type t10  = sqrt(p__XO);
    real_type t14  = f__XO * f__XO;
    real_type t15  = 2 * f__XO * t2 + t14 + t6 + t7 + 1;
    real_type t16  = sqrt(t15);
    return 1.0 / t16 / t15 / t10 * (-t3 + t6 + t7 + 1) * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sqrt(p__XO);
    real_type t5   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t14  = f__XO * f__XO;
    real_type t15  = g__XO * g__XO;
    real_type t16  = 2 * t5 * f__XO + 2 * t7 * g__XO + t14 + t15 + 1;
    real_type t17  = sqrt(t16);
    return -1.0 / t17 / t16 * (t7 + g__XO) * (t5 + f__XO) / t2 * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t7   = f__XO * f__XO;
    real_type t8   = g__XO * g__XO;
    real_type t9   = 2 * t1 * f__XO + 2 * t4 * g__XO + t7 + t8 + 1;
    real_type t10  = sqrt(t9);
    real_type t13  = sqrt(p__XO);
    real_type t16  = sqrt(muS__XO);
    real_type t17  = t1 * t1;
    return -(-g__XO * t17 + t1 * (t4 + g__XO) * f__XO + t8 * t4 + 2 * g__XO + t4) * t16 / t13 / t10 / t9;
  }

  real_type
  gtocX_2burn_pars::vel_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t3   = cos(L__XO);
    real_type t6   = sqrt(p__XO);
    real_type t10  = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = sqrt(2 * t3 * f__XO + 2 * t10 * g__XO + t13 + t14 + 1);
    return 1.0 / t16 / t6 * (t3 + f__XO) / t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sin(L__XO);
    real_type t5   = sqrt(p__XO);
    real_type t7   = cos(L__XO);
    real_type t12  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t15  = sqrt(2 * t7 * f__XO + 2 * t2 * g__XO + t12 + t13 + 1);
    return 1.0 / t15 / t5 * (t2 + g__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = cos(L__XO);
    real_type t4   = pow(t2 + f__XO, 2);
    real_type t6   = sqrt(p__XO);
    real_type t10  = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t15  = 2 * t2 * f__XO + 2 * t10 * g__XO + t13 + t14 + 1;
    real_type t16  = sqrt(t15);
    return 1.0 / t16 / t15 / t6 * t4 * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = cos(L__XO);
    real_type t5   = t2 * f__XO;
    real_type t6   = sin(L__XO);
    real_type t7   = t6 * g__XO;
    real_type t9   = sqrt(p__XO);
    real_type t14  = f__XO * f__XO;
    real_type t15  = g__XO * g__XO;
    real_type t16  = 2 * t5 + 2 * t7 + t14 + t15 + 1;
    real_type t17  = sqrt(t16);
    return 1.0 / t17 / t16 / t9 * (1 + t5 + t7) * (t2 + f__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t3   = sin(L__XO);
    real_type t6   = sqrt(p__XO);
    real_type t8   = cos(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = sqrt(2 * t8 * f__XO + 2 * t3 * g__XO + t13 + t14 + 1);
    return 1.0 / t16 / t6 * (t3 + g__XO) / t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t2   = sin(L__XO);
    real_type t4   = cos(L__XO);
    real_type t8   = sqrt(p__XO);
    real_type t14  = f__XO * f__XO;
    real_type t15  = g__XO * g__XO;
    real_type t17  = sqrt(2 * t4 * f__XO + 2 * t2 * g__XO + t14 + t15 + 1);
    return 1.0 / t17 / t8 * (-t2 * f__XO + t4 * g__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = f__XO * f__XO;
    real_type t2   = g__XO * g__XO;
    real_type t4   = cos(L__XO);
    real_type t5   = t4 * t4;
    real_type t7   = sin(L__XO);
    real_type t9   = 2 * t7 * g__XO;
    real_type t20  = 2 * t4 * f__XO + t1 + t2 + t9 + 1;
    real_type t21  = sqrt(t20);
    real_type t25  = sqrt(p__XO);
    real_type t27  = sqrt(muS__XO);
    return -t27 / t25 / t21 / t20 * (t5 * (t1 - t2) + t4 * (t1 + t2 + t9 + 1) * f__XO + t7 * (t1 + t2 + 1) * g__XO + t1 + 2 * t2);
  }

  real_type
  gtocX_2burn_pars::vel_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = sqrt(muS__XO);
    real_type t3   = sin(L__XO);
    real_type t5   = cos(L__XO);
    real_type t9   = sqrt(p__XO);
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = sqrt(2 * t5 * f__XO + 2 * t3 * g__XO + t15 + t16 + 1);
    return 1.0 / t18 / t9 * (-t3 * f__XO + g__XO * t5) / t1 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t7   = f__XO * f__XO;
    real_type t8   = g__XO * g__XO;
    real_type t10  = sqrt(2 * t1 * f__XO + 2 * t4 * g__XO + t7 + t8 + 1);
    real_type t11  = sqrt(muS__XO);
    real_type t14  = sqrt(p__XO);
    return 1.0 / t14 / t11 * t10 / 2;
  }

  real_type
  gtocX_2burn_pars::vel_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t7   = f__XO * f__XO;
    real_type t8   = g__XO * g__XO;
    real_type t10  = sqrt(2 * t1 * f__XO + 2 * t4 * g__XO + t7 + t8 + 1);
    real_type t11  = sqrt(muS__XO);
    real_type t15  = sqrt(p__XO);
    return -1.0 / t15 / t11 / muS__XO * t10 / 4;
  }

  real_type
  gtocX_2burn_pars::acceleration_r( real_type r__XO, real_type muS__XO ) const {
    real_type t1   = 1.0 / r__XO;
    real_type t3   = vc(r__XO);
    real_type t4   = t3 * t3;
    return t1 * (t1 * muS__XO - t4);
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_1( real_type r__XO, real_type muS__XO ) const {
    real_type t1   = vc(r__XO);
    real_type t2   = vc_D(r__XO);
    real_type t4   = r__XO * r__XO;
    real_type t7   = t1 * t1;
    return 1.0 / t4 / r__XO * (-2 * t4 * t2 * t1 + r__XO * t7 - 2 * muS__XO);
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_1_1( real_type r__XO, real_type muS__XO ) const {
    real_type t1   = vc(r__XO);
    real_type t2   = vc_DD(r__XO);
    real_type t4   = r__XO * r__XO;
    real_type t5   = t4 * r__XO;
    real_type t8   = vc_D(r__XO);
    real_type t9   = t8 * t8;
    real_type t15  = t1 * t1;
    real_type t20  = t4 * t4;
    return 1.0 / t20 * (-2 * t5 * t2 * t1 + 4 * t4 * t8 * t1 - 2 * r__XO * t15 - 2 * t5 * t9 + 6 * muS__XO);
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_1_2( real_type r__XO, real_type muS__XO ) const {
    real_type t1   = r__XO * r__XO;
    return -2 / t1 / r__XO;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_2( real_type r__XO, real_type muS__XO ) const {
    real_type t1   = r__XO * r__XO;
    return 1.0 / t1;
  }

  real_type
  gtocX_2burn_pars::acceleration_r_D_2_2( real_type r__XO, real_type muS__XO ) const {
    return 0;
  }


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  gtocX_2burn_pars::H_eval(
    integer              i_segment,
    CellType const &     CELL__,
    P_const_pointer_type P__
  ) const {
    integer        i_cell = CELL__.i_cell;
    real_type const * Q__ = CELL__.qM;
    real_type const * X__ = CELL__.xM;
    real_type const * L__ = CELL__.lambdaM;
    real_type const * U__ = CELL__.uM;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[2];
    real_type t3   = cos(t2);
    real_type t5   = X__[1];
    real_type t6   = sin(t2);
    real_type t8   = t3 * t1 + t6 * t5 + 1;
    real_type t9   = ray_positive(t8);
    real_type t12  = P__[0];
    real_type t13  = p_guess(0);
    real_type t17  = pow(1.0 / t13 * t12 - 1, 2);
    real_type t18  = Q__[0];
    real_type t20  = ModelPars[2];
    real_type t22  = ModelPars[1];
    real_type t24  = t20 * (1 - t18) + t22 * t18;
    real_type t25  = f_guess(t24);
    real_type t27  = pow(t1 - t25, 2);
    real_type t28  = g_guess(t24);
    real_type t30  = pow(t5 - t28, 2);
    real_type t32  = h_guess(0);
    real_type t34  = pow(P__[1] - t32, 2);
    real_type t36  = k_guess(0);
    real_type t38  = pow(P__[2] - t36, 2);
    real_type t39  = L_guess(t24, t20);
    real_type t41  = pow(t2 - t39, 2);
    real_type t45  = t22 - t20;
    real_type t47  = sqrt(t12);
    real_type t49  = ModelPars[0];
    real_type t50  = sqrt(t49);
    real_type t53  = ModelPars[6] / t50;
    real_type t54  = ray(t12, t1, t5, t2);
    real_type t55  = acceleration_r(t54, t49);
    real_type t67  = t8 * t8;
    return t9 + (t17 + t27 + t30 + t34 + t38 + t41) * (1 - ModelPars[3]) + t6 * t55 * t53 * t47 * t45 * L__[0] - t3 * t55 * t53 * t47 * t45 * L__[1] + t50 / t47 / t12 * t67 * t45 * L__[2];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  gtocX_2burn_pars::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[2];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    return ray_positive(t3 * X__[0] + t6 * X__[1] + 1);
  }

  real_type
  gtocX_2burn_pars::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return 0;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  gtocX_2burn_pars::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t4   = p_guess(0);
    real_type t8   = pow(1.0 / t4 * P__[0] - 1, 2);
    real_type t10  = Q__[0];
    real_type t12  = ModelPars[2];
    real_type t16  = t12 * (1 - t10) + ModelPars[1] * t10;
    real_type t17  = f_guess(t16);
    real_type t19  = pow(X__[0] - t17, 2);
    real_type t21  = g_guess(t16);
    real_type t23  = pow(X__[1] - t21, 2);
    real_type t25  = h_guess(0);
    real_type t27  = pow(P__[1] - t25, 2);
    real_type t29  = k_guess(0);
    real_type t31  = pow(P__[2] - t29, 2);
    real_type t33  = L_guess(t16, t12);
    real_type t35  = pow(X__[2] - t33, 2);
    return (t8 + t19 + t23 + t27 + t31 + t35) * (1 - ModelPars[3]);
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  gtocX_2burn_pars::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    return 0;
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  gtocX_2burn_pars::q_numEqns() const
  { return 1; }

  void
  gtocX_2burn_pars::q_eval(
    integer        i_node,
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = s;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__.pointer(),"q_eval",1);
    #endif
  }

  /*\
   |    ___
   |   / __|_  _ ___ ______
   |  | (_ | || / -_|_-<_-<
   |   \___|\_,_\___/__/__/
  \*/

  integer
  gtocX_2burn_pars::u_guess_numEqns() const
  { return 0; }

  void
  gtocX_2burn_pars::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    // no controls to initialize
  }

  void
  gtocX_2burn_pars::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    // no controls to compute
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  gtocX_2burn_pars::u_check_if_admissible(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    // no controls to check
    return ok;
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  gtocX_2burn_pars::post_numEqns() const
  { return 20; }

  void
  gtocX_2burn_pars::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = Q__[0];
    result__[ 0   ] = ModelPars[2] * (1 - t1) + ModelPars[1] * t1;
    real_type t7   = P__[0];
    real_type t8   = X__[0];
    real_type t9   = X__[1];
    real_type t10  = X__[2];
    result__[ 1   ] = ray(t7, t8, t9, t10);
    real_type t11  = P__[1];
    real_type t12  = P__[2];
    real_type t13  = ModelPars[5];
    result__[ 2   ] = xPosition(t7, t8, t9, t11, t12, t10, t13);
    result__[ 3   ] = yPosition(t7, t8, t9, t11, t12, t10, t13);
    result__[ 4   ] = zPosition(t7, t8, t9, t11, t12, t10, t13);
    result__[ 5   ] = xVelocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 6   ] = yVelocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 7   ] = zVelocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 8   ] = X_begin(result__[0]);
    result__[ 9   ] = Y_begin(result__[0]);
    result__[ 10  ] = Z_begin(result__[0]);
    result__[ 11  ] = VX_begin(result__[0]);
    result__[ 12  ] = VY_begin(result__[0]);
    result__[ 13  ] = VZ_begin(result__[0]);
    result__[ 14  ] = X_end(result__[0]);
    result__[ 15  ] = Y_end(result__[0]);
    result__[ 16  ] = Z_end(result__[0]);
    result__[ 17  ] = VX_end(result__[0]);
    result__[ 18  ] = VY_end(result__[0]);
    result__[ 19  ] = VZ_end(result__[0]);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"post_eval",20);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  gtocX_2burn_pars::integrated_post_numEqns() const
  { return 0; }

  void
  gtocX_2burn_pars::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: gtocX_2burn_pars_Methods1.cc
