/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods1.cc                                   |
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
    real_type t19  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t22  = t1 * t1;
    return 1.0 / (t22 * (t19 - t20) + t1 * (2 * t9 * g__XO * f__XO + 2 * f__XO) + t20 + 2 * t9 * g__XO + 1) / (t6 + t7 + 1) * (2 * t3 * f__XO * h__XO + 2 * t3 * h__XO * t1 + g__XO * t8 + t9 * t8);
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
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t8   = sin(L__XO);
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t27  = t19 * g__XO;
    real_type t31  = 3 * t19;
    return 2 / (t2 * t1 * (t17 * f__XO - 3 * t19 * f__XO) + t2 * (t8 * (3 * g__XO * t17 - t27) + 3 * t17 - t31) + 3 * t1 * (2 * g__XO * t8 + t19 + 1) * f__XO + t8 * (t27 + 3 * g__XO) + t31 + 1) / (t3 + t4 + 1) * p__XO * (t1 * (t3 - t4 + 1) + 2 * t8 * k__XO * retrograde__XO * h__XO) * t2;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t11  = sin(L__XO);
    real_type t21  = f__XO * f__XO;
    real_type t23  = g__XO * g__XO;
    real_type t31  = t23 * g__XO;
    real_type t35  = 3 * t23;
    return 2 / (t2 * t1 * (t21 * f__XO - 3 * t23 * f__XO) + t2 * (t11 * (3 * g__XO * t21 - t31) + 3 * t21 - t35) + 3 * t1 * (2 * t11 * g__XO + t23 + 1) * f__XO + t11 * (t31 + 3 * g__XO) + t35 + 1) / (t7 + t8 + 1) * p__XO * (-2 * k__XO * retrograde__XO * h__XO * t2 + t11 * t1 * (t7 - t8 + 1) + 2 * h__XO * k__XO * retrograde__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t14  = f__XO * f__XO;
    real_type t15  = g__XO * g__XO;
    real_type t17  = t1 * t1;
    real_type t30  = pow(t3 + t4 + 1, 2);
    return 2 / t30 / (t17 * (t14 - t15) + t1 * (2 * t7 * g__XO * f__XO + 2 * f__XO) + t15 + 2 * t7 * g__XO + 1) * p__XO * (t7 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t1) * t1 * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_2_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t3   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    real_type t11  = sin(L__XO);
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = t1 * t1;
    real_type t31  = pow(t3 + t9 + 1, 2);
    return -2 / t31 / (t18 * (t15 - t16) + t1 * (2 * t11 * g__XO * f__XO + 2 * f__XO) + t16 + 2 * t11 * g__XO + 1) * (t1 * (-2 * k__XO * t3 - 2 * k__XO) + t11 * (t3 - t9 + 1) * h__XO * retrograde__XO) * p__XO * t1;
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
    real_type t26  = f__XO * f__XO;
    real_type t28  = g__XO * g__XO;
    real_type t36  = t28 * g__XO;
    real_type t40  = 3 * t28;
    return -2 / (t2 * t1 * (t26 * f__XO - 3 * t28 * f__XO) + t2 * (t10 * (3 * g__XO * t26 - t36) + 3 * t26 - t40) + 3 * t1 * (t28 + 2 * t18 + 1) * f__XO + t10 * (t36 + 3 * g__XO) + t40 + 1) / (t7 + t8 + 1) * p__XO * (2 * t4 * h__XO * t2 + t1 * (t4 * f__XO * h__XO + g__XO * t9 + t10 * t9) - (t18 + 1) * retrograde__XO * h__XO * k__XO);
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
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t23  = t4 * t4;
    real_type t28  = t19 * g__XO;
    real_type t32  = 3 * t19;
    return 2 / (t23 * t4 * (t17 * f__XO - 3 * t19 * f__XO) + t23 * (t7 * (3 * g__XO * t17 - t28) + 3 * t17 - t32) + 3 * t4 * (2 * t7 * g__XO + t19 + 1) * f__XO + t7 * (t28 + 3 * g__XO) + t32 + 1) / (t1 + t2 + 1) * p__XO * t12 * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t14  = f__XO * t7;
    real_type t19  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t22  = t7 * t7;
    real_type t29  = pow(t1 + t2 + 1, 2);
    return 2 / t29 / (t5 * (2 * g__XO * t14 + 2 * g__XO) + t22 * (t19 - t20) + 2 * t14 + t20 + 1) * p__XO * t5 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7) * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sin(L__XO);
    real_type t3   = h__XO * h__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = k__XO * k__XO;
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = t7 * t7;
    real_type t31  = pow(t3 + t10 + 1, 2);
    return -2 / t31 / (t18 * (t15 - t16) + t7 * (2 * t1 * g__XO * f__XO + 2 * f__XO) + t16 + 2 * t1 * g__XO + 1) * (t7 * (-2 * k__XO * t3 - 2 * k__XO) + t1 * (t3 - t10 + 1) * h__XO * retrograde__XO) * p__XO * t1;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 + 1;
    real_type t5   = cos(L__XO);
    real_type t6   = t5 * t5;
    real_type t9   = sin(L__XO);
    real_type t28  = f__XO * f__XO;
    real_type t30  = g__XO * g__XO;
    real_type t38  = t30 * g__XO;
    real_type t42  = 3 * t30;
    return -1.0 / (t6 * t5 * (t28 * f__XO - 3 * t30 * f__XO) + t6 * (t9 * (3 * g__XO * t28 - t38) + 3 * t28 - t42) + 3 * t5 * (2 * t9 * g__XO + t30 + 1) * f__XO + t9 * (t38 + 3 * g__XO) + t42 + 1) / (t1 + t2 + 1) * p__XO * (2 * t6 * t3 + t5 * (4 * t9 * k__XO * retrograde__XO * h__XO + t3 * f__XO) + t9 * (4 * f__XO * h__XO * k__XO * retrograde__XO - g__XO * t3) - t1 + t2 - 1);
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
    return -2 / t19 / (t7 * f__XO + t5 * g__XO + 1) * p__XO * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7) * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t22  = t1 + t4 + 1;
    real_type t23  = t22 * t22;
    return 4 / t23 / t22 / (t7 * f__XO + t10 * g__XO + 1) * p__XO * (t7 * (-3 * k__XO * t1 + t4 * k__XO + k__XO) + (t1 - 3 * t4 - 3) * t10 * retrograde__XO * h__XO) * k__XO;
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
    return -2 / t24 / t23 / (t11 * f__XO + t9 * g__XO + 1) * p__XO * (t9 * (-6 * t3 * t1 + t2 + t6 - 1) * retrograde__XO - 4 * (t1 - t3 + 1) * k__XO * h__XO * t11);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t18  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t21  = t5 * t5;
    real_type t34  = pow(t1 + t2 + 1, 2);
    return -2 / t34 / (t21 * (t18 - t19) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t19 + 2 * t8 * g__XO + 1) * p__XO * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO) * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t14  = pow(t1 + t2 + 1, 2);
    return -2 / t14 / (t7 * f__XO + t5 * g__XO + 1) * p__XO * t5 * (t1 - t2 - 1) * k__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t20  = pow(t2 + t3 + 1, 2);
    return 2 / t20 / (t8 * f__XO + t5 * g__XO + 1) * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO - 2 * (t2 + 1) * t8 * k__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t23  = t1 + t3 + 1;
    real_type t24  = t23 * t23;
    return -4 / t24 / t23 / (t7 * f__XO + t13 * g__XO + 1) * p__XO * (t7 * (t1 - 3 * t3 + 1) * (t1 + 1) + 3 * t13 * h__XO * retrograde__XO * (t1 - t3 / 3 + 1) * k__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t28  = f__XO * f__XO;
    real_type t29  = g__XO * g__XO;
    real_type t31  = t5 * t5;
    real_type t43  = pow(t2 + t3 + 1, 2);
    return 2 / t43 / (t31 * (t28 - t29) + t5 * (2 * t11 * g__XO * f__XO + 2 * f__XO) + t29 + 2 * t11 * g__XO + 1) * p__XO * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO + t11 * (2 * k__XO * t2 + 2 * k__XO) + retrograde__XO * t2 * h__XO * f__XO + 2 * k__XO * t2 * g__XO + h__XO * (-retrograde__XO * t3 * f__XO + f__XO * retrograde__XO) + 2 * g__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::xPosition_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t14  = pow(t2 + t3 + 1, 2);
    return 2 / t14 / (t7 * f__XO + t6 * g__XO + 1) * t6 * (t2 - t3 + 1) * h__XO * p__XO;
  }

  real_type
  gtocX_2burn_pars::xPosition_D_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t3   = cos(L__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = (-t7 + t8 - 1) * p__XO;
    real_type t11  = sin(L__XO);
    real_type t20  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    real_type t23  = t3 * t3;
    return 1.0 / (t7 + t8 + 1) / (t23 * (t20 - t21) + t3 * (2 * t11 * g__XO * f__XO + 2 * f__XO) + t21 + 2 * t11 * g__XO + 1) * (2 * p__XO * f__XO * h__XO * k__XO * retrograde__XO + 2 * t3 * retrograde__XO * k__XO * p__XO * h__XO + g__XO * t10 + t11 * t10);
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
    real_type t54  = t23 * g__XO;
    real_type t58  = 3 * t23;
    return 4 / (t12 * t11 * (-3 * t23 * f__XO + t35 * f__XO) + t12 * (t20 * (3 * g__XO * t35 - t54) + 3 * t35 - t58) + 3 * t11 * (2 * t20 * g__XO + t23 + 1) * f__XO + t20 * (t54 + 3 * g__XO) + t58 + 1) / (t5 + t6 + 1) * p__XO * (t12 * (-t4 + t8 / 4) + t11 * (t20 * (g__XO * t7 / 4 + t2 * f__XO * h__XO / 2) + t23 * t7 / 2 - retrograde__XO * t26 * t25 - t5 / 4 + t6 / 4 - 1.0 / 4.0) + t20 * (-t7 * t25 / 2 + (t35 - 1.0 / 2.0) * retrograde__XO * t26) - t4 - t8 / 2);
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
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = t7 * t7;
    return 1.0 / (t18 * (t15 - t16) + t7 * (2 * t5 * g__XO * f__XO + 2 * f__XO) + t16 + 2 * t5 * g__XO + 1) / (t1 + t2 + 1) * t7 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_1_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t15  = t7 * f__XO;
    real_type t20  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    real_type t23  = t7 * t7;
    return 1.0 / (t5 * (2 * g__XO * t15 + 2 * g__XO) + t23 * (t20 - t21) + 2 * t15 + t21 + 1) / (t1 + t2 + 1) * t5 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
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
    real_type t20  = f__XO * f__XO;
    real_type t21  = g__XO * g__XO;
    real_type t23  = t5 * t5;
    return 1.0 / (t23 * (t20 - t21) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t21 + 2 * t8 * g__XO + 1) / (t1 + t2 + 1) * (-retrograde__XO * t3 * f__XO - 2 * g__XO * h__XO * k__XO - 2 * t8 * k__XO * h__XO - t5 * t3 * retrograde__XO);
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
    real_type t1   = cos(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = t1 * t1;
    return 1.0 / (t2 + t3 + 1) / (t16 * (t13 - t14) + t1 * (2 * t6 * g__XO * f__XO + 2 * f__XO) + t14 + 2 * t6 * g__XO + 1) * p__XO * (t6 * (t2 - t3 - 1) * retrograde__XO - 2 * k__XO * h__XO * t1) * t1;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t27  = t19 * g__XO;
    real_type t31  = 3 * t19;
    return -2 / (t2 * t1 * (t17 * f__XO - 3 * t19 * f__XO) + t2 * (t7 * (3 * g__XO * t17 - t27) + 3 * t17 - t31) + 3 * t1 * (2 * t7 * g__XO + t19 + 1) * f__XO + t7 * (t27 + 3 * g__XO) + t31 + 1) / (t3 + t4 + 1) * p__XO * (t7 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t1) * t2;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = (t2 - t3 - 1) * retrograde__XO;
    real_type t6   = t1 * t1;
    real_type t8   = sin(L__XO);
    real_type t18  = f__XO * f__XO;
    real_type t20  = g__XO * g__XO;
    real_type t28  = t20 * g__XO;
    real_type t32  = 3 * t20;
    return 2 / (t6 * t1 * (t18 * f__XO - 3 * t20 * f__XO) + t6 * (t8 * (3 * g__XO * t18 - t28) + 3 * t18 - t32) + 3 * t1 * (2 * t8 * g__XO + t20 + 1) * f__XO + t8 * (t28 + 3 * g__XO) + t32 + 1) / (t2 + t3 + 1) * p__XO * (2 * h__XO * k__XO * t8 * t1 + t6 * t5 - t5) * t1;
  }

  real_type
  gtocX_2burn_pars::yPosition_D_2_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t8   = sin(L__XO);
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = t1 * t1;
    real_type t31  = pow(t2 + t3 + 1, 2);
    return 2 / t31 / (t18 * (t15 - t16) + t1 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t16 + 2 * t8 * g__XO + 1) * p__XO * (t1 * (t2 - t3 - 1) * k__XO + 2 * (t3 + 1) * t8 * retrograde__XO * h__XO) * t1;
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
    return -2 / (2 * f__XO * g__XO * t4 * t1 + 2 * t1 * f__XO + 2 * t4 * g__XO + t19 * t18 - t21 * t18 + t21 + 1) / t15 * h__XO * (2 * t4 * k__XO * retrograde__XO * h__XO - t10 * t1 + t8 * t1 + t1) * p__XO * t1;
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
    real_type t27  = f__XO * f__XO;
    real_type t29  = g__XO * g__XO;
    real_type t37  = t29 * g__XO;
    real_type t41  = 3 * t29;
    return 1.0 / (t6 * t5 * (t27 * f__XO - 3 * t29 * f__XO) + t6 * (t10 * (3 * g__XO * t27 - t37) + 3 * t27 - t41) + 3 * t5 * (t29 + 2 * t20 + 1) * f__XO + t10 * (t37 + 3 * g__XO) + t41 + 1) / (t1 + t2 + 1) * p__XO * (2 * t6 * t4 + t5 * (retrograde__XO * t3 * f__XO + 4 * g__XO * h__XO * k__XO + 4 * t10 * k__XO * h__XO) - (t20 + 1) * t4);
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
    real_type t13  = f__XO * t7;
    real_type t18  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t21  = t7 * t7;
    return 1.0 / (t1 + t2 + 1) / (t5 * (2 * g__XO * t13 + 2 * g__XO) + t21 * (t18 - t19) + 2 * t13 + t19 + 1) * p__XO * t5 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t7   = cos(L__XO);
    real_type t12  = t5 * t5;
    real_type t17  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t23  = t7 * t7;
    real_type t28  = t19 * g__XO;
    real_type t32  = 3 * t19;
    return -2 / (t23 * t7 * (t17 * f__XO - 3 * t19 * f__XO) + t23 * (t5 * (3 * g__XO * t17 - t28) + 3 * t17 - t32) + 3 * t7 * (2 * t5 * g__XO + t19 + 1) * f__XO + t5 * (t28 + 3 * g__XO) + t32 + 1) / (t1 + t2 + 1) * p__XO * t12 * (t5 * (t1 - t2 - 1) * retrograde__XO - 2 * k__XO * h__XO * t7);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t15  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t18  = t5 * t5;
    real_type t31  = pow(t1 + t2 + 1, 2);
    return 2 / t31 / (t18 * (t15 - t16) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t16 + 2 * t8 * g__XO + 1) * p__XO * t8 * (t5 * (t1 - t2 - 1) * k__XO + 2 * (t2 + 1) * t8 * retrograde__XO * h__XO);
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
    real_type t27  = f__XO * f__XO;
    real_type t29  = g__XO * g__XO;
    real_type t37  = t29 * g__XO;
    real_type t41  = 3 * t29;
    return 2 / (t2 * t1 * (t27 * f__XO - 3 * t29 * f__XO) + t2 * (t10 * (3 * g__XO * t27 - t37) + 3 * t27 - t41) + 3 * t1 * (2 * t10 * g__XO + t29 + 1) * f__XO + t10 * (t37 + 3 * g__XO) + t41 + 1) / (t6 + t7 + 1) * p__XO * (-2 * k__XO * h__XO * t2 + t1 * (-f__XO * h__XO * k__XO + t10 * t8 * retrograde__XO) + t10 * (retrograde__XO * t8 * f__XO + g__XO * h__XO * k__XO) + h__XO * k__XO);
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
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t11  = cos(L__XO);
    real_type t23  = t1 + t2 + 1;
    real_type t24  = t23 * t23;
    return 4 / t24 / t23 / (t11 * f__XO + t7 * g__XO + 1) * p__XO * (3 * t7 * (t2 + 1) * (t1 - t2 / 3 - 1.0 / 3.0) * retrograde__XO + (t1 - 3 * t2 - 3) * k__XO * h__XO * t11);
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
    return -2 / t24 / t23 / (t8 * f__XO + t11 * g__XO + 1) * p__XO * (t8 * (-6 * t3 * t1 + t2 + t6 - 1) + 4 * (t1 - t3 - 1) * retrograde__XO * t11 * h__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = cos(L__XO);
    real_type t3   = k__XO * k__XO;
    real_type t7   = h__XO * h__XO;
    real_type t10  = sin(L__XO);
    real_type t16  = f__XO * h__XO;
    real_type t26  = f__XO * f__XO;
    real_type t27  = g__XO * g__XO;
    real_type t29  = t2 * t2;
    real_type t41  = pow(t7 + t3 + 1, 2);
    return -4 / t41 / (t29 * (t26 - t27) + t2 * (2 * t10 * g__XO * f__XO + 2 * f__XO) + t27 + 2 * t10 * g__XO + 1) * p__XO * ((t3 + 1) * t2 * retrograde__XO * h__XO - t10 * (t7 - t3 - 1) * k__XO / 2 + t3 * k__XO * g__XO / 2 + retrograde__XO * t3 * t16 + k__XO * (-t7 / 2 + 1.0 / 2.0) * g__XO + retrograde__XO * t16);
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
    return 2 / t19 / (t4 * f__XO + t7 * g__XO + 1) * p__XO * h__XO * (t4 * (t1 - t2 + 1) + 2 * t7 * k__XO * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yPosition_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t23  = t1 + t4 + 1;
    real_type t24  = t23 * t23;
    return 4 / t24 / t23 / (t8 * f__XO + t11 * g__XO + 1) * p__XO * h__XO * (t8 * (-3 * k__XO * t1 + t4 * k__XO - 3 * k__XO) + (t1 - 3 * t4 + 1) * t11 * retrograde__XO * h__XO);
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
    return 2 / (2 * f__XO * g__XO * t14 * t10 + 2 * t10 * f__XO + 2 * t14 * g__XO + t23 * t22 - t25 * t22 + t25 + 1) / t19 * (2 * t3 * f__XO * h__XO + 2 * t3 * h__XO * t10 - t6 * g__XO + t8 * g__XO - t6 * t14 + t8 * t14 - g__XO - t14) * h__XO * p__XO;
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
    real_type t18  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t21  = t5 * t5;
    return -1.0 / (t1 + t2 + 1) / (t21 * (t18 - t19) + t5 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t19 + 2 * t8 * g__XO + 1) * p__XO * (retrograde__XO * t3 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t8 * k__XO * h__XO + t5 * t3 * retrograde__XO);
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
    real_type t51  = t21 * g__XO;
    real_type t55  = 3 * t21;
    return -2 / (t11 * t10 * (-3 * t21 * f__XO + t33 * f__XO) + t11 * (t19 * (3 * g__XO * t33 - t51) + 3 * t33 - t55) + 3 * t10 * (2 * t19 * g__XO + t21 + 1) * f__XO + t19 * (t51 + 3 * g__XO) + t55 + 1) / (t1 + t2 + 1) * p__XO * (t11 * (-t6 - t8) + t10 * (t19 * (-g__XO * h__XO * k__XO + retrograde__XO * t15 / 2) - 2 * k__XO * h__XO * t21 - retrograde__XO * g__XO * t15 + t27) + t19 * (2 * t27 * f__XO * g__XO + (t33 - 1.0 / 2.0) * t4) - t6 + 2 * t8);
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
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t24  = t16 * g__XO;
    real_type t28  = 3 * t16;
    return 4 / (t8 * t1 * (t14 * f__XO - 3 * t16 * f__XO) + t8 * (t4 * (3 * g__XO * t14 - t24) + 3 * t14 - t28) + 3 * t1 * (2 * t4 * g__XO + t16 + 1) * f__XO + t4 * (t24 + 3 * g__XO) + t28 + 1) / (t9 + t10 + 1) * t8 * (-retrograde__XO * k__XO * t1 + t4 * h__XO) * p__XO;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = sin(L__XO);
    real_type t6   = t1 * t1;
    real_type t10  = h__XO * h__XO;
    real_type t11  = k__XO * k__XO;
    real_type t15  = f__XO * f__XO;
    real_type t17  = g__XO * g__XO;
    real_type t25  = t17 * g__XO;
    real_type t29  = 3 * t17;
    return -4 / (t6 * t1 * (t15 * f__XO - 3 * t17 * f__XO) + t6 * (t2 * (3 * g__XO * t15 - t25) + 3 * t15 - t29) + 3 * t1 * (2 * t2 * g__XO + t17 + 1) * f__XO + t2 * (t25 + 3 * g__XO) + t29 + 1) / (t10 + t11 + 1) * t1 * (k__XO * retrograde__XO * t2 * t1 + h__XO * t6 - h__XO) * p__XO;
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
    real_type t1   = cos(L__XO);
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t8   = sin(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = t1 * t1;
    real_type t29  = pow(t2 + t3 + 1, 2);
    return 2 / t29 / (t16 * (t13 - t14) + t1 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t14 + 2 * t8 * g__XO + 1) * p__XO * (t1 * (t2 - t3 + 1) * retrograde__XO + 2 * t8 * k__XO * h__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t9   = sin(L__XO);
    real_type t19  = h__XO * h__XO;
    real_type t20  = k__XO * k__XO;
    real_type t23  = f__XO * f__XO;
    real_type t25  = g__XO * g__XO;
    real_type t33  = t25 * g__XO;
    real_type t37  = 3 * t25;
    return -2 / (t2 * t1 * (t23 * f__XO - 3 * t25 * f__XO) + t2 * (t9 * (3 * g__XO * t23 - t33) + 3 * t23 - t37) + 3 * t1 * (2 * t9 * g__XO + t25 + 1) * f__XO + t9 * (t33 + 3 * g__XO) + t37 + 1) / (t19 + t20 + 1) * p__XO * (2 * h__XO * t2 + t1 * (2 * g__XO * k__XO * retrograde__XO + 2 * t9 * k__XO * retrograde__XO + f__XO * h__XO) - t9 * h__XO * g__XO - h__XO);
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
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t14  = f__XO * f__XO;
    real_type t16  = g__XO * g__XO;
    real_type t20  = t4 * t4;
    real_type t25  = t16 * g__XO;
    real_type t29  = 3 * t16;
    return 4 / (t20 * t4 * (t14 * f__XO - 3 * t16 * f__XO) + t20 * (t1 * (3 * g__XO * t14 - t25) + 3 * t14 - t29) + 3 * t4 * (2 * t1 * g__XO + t16 + 1) * f__XO + t1 * (t25 + 3 * g__XO) + t29 + 1) / (t9 + t10 + 1) * (-retrograde__XO * k__XO * t4 + t1 * h__XO) * t2 * p__XO;
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
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t13  = f__XO * f__XO;
    real_type t14  = g__XO * g__XO;
    real_type t16  = t6 * t6;
    real_type t29  = pow(t2 + t3 + 1, 2);
    return 2 / t29 / (t16 * (t13 - t14) + t6 * (2 * t1 * g__XO * f__XO + 2 * f__XO) + t14 + 2 * t1 * g__XO + 1) * p__XO * (t6 * (t2 - t3 + 1) * retrograde__XO + 2 * t1 * k__XO * h__XO) * t1;
  }

  real_type
  gtocX_2burn_pars::zPosition_D_3_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t2   = t1 * t1;
    real_type t7   = k__XO * retrograde__XO;
    real_type t10  = sin(L__XO);
    real_type t21  = h__XO * h__XO;
    real_type t22  = k__XO * k__XO;
    real_type t25  = f__XO * f__XO;
    real_type t27  = g__XO * g__XO;
    real_type t35  = t27 * g__XO;
    real_type t39  = 3 * t27;
    return -2 / (t2 * t1 * (t25 * f__XO - 3 * t27 * f__XO) + t2 * (t10 * (3 * g__XO * t25 - t35) + 3 * t25 - t39) + 3 * t1 * (2 * t10 * g__XO + t27 + 1) * f__XO + t10 * (t35 + 3 * g__XO) + t39 + 1) / (t21 + t22 + 1) * p__XO * (retrograde__XO * t10 * g__XO * k__XO + 2 * t10 * h__XO * f__XO - t7 * f__XO * t1 + 2 * h__XO * t10 * t1 - 2 * retrograde__XO * k__XO * t2 + t7);
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
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t21  = t2 + t3 + 1;
    real_type t22  = t21 * t21;
    return 4 / t22 / t21 / (t6 * f__XO + t10 * g__XO + 1) * p__XO * (-3 * t6 * (t2 - t3 / 3 - 1.0 / 3.0) * k__XO * retrograde__XO + (t2 - 3 * t3 - 3) * t10 * h__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t12  = sin(L__XO);
    real_type t21  = t2 + t3 + 1;
    real_type t22  = t21 * t21;
    return 4 / t22 / t21 / (t6 * f__XO + t12 * g__XO + 1) * p__XO * (t6 * (t2 - 3 * t3 + 1) * h__XO * retrograde__XO + 3 * t12 * (t2 - t3 / 3 - 1.0 / 3.0) * k__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t18  = f__XO * f__XO;
    real_type t19  = g__XO * g__XO;
    real_type t21  = t4 * t4;
    real_type t33  = pow(t1 + t2 + 1, 2);
    return -2 / t33 / (t21 * (t18 - t19) + t4 * (2 * t7 * g__XO * f__XO + 2 * f__XO) + t19 + 2 * t7 * g__XO + 1) * p__XO * (2 * g__XO * h__XO * k__XO * retrograde__XO + 2 * t7 * k__XO * retrograde__XO * h__XO + t3 * f__XO + t4 * t3);
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
    return -2 / t18 / (t5 * f__XO + t8 * g__XO + 1) * p__XO * (t5 * (t1 - t2 + 1) * retrograde__XO + 2 * t8 * k__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t21  = t1 + t2 + 1;
    real_type t22  = t21 * t21;
    return -4 / t22 / t21 / (t6 * f__XO + t10 * g__XO + 1) * p__XO * (-3 * t6 * retrograde__XO * (t1 - t2 / 3 + 1) * k__XO + (t1 - 3 * t2 + 1) * t10 * h__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t7   = (t4 - t5 + 1) * retrograde__XO;
    real_type t8   = sin(L__XO);
    real_type t17  = f__XO * f__XO;
    real_type t18  = g__XO * g__XO;
    real_type t20  = t1 * t1;
    real_type t32  = pow(t4 + t5 + 1, 2);
    return -4 / t32 / (t20 * (t17 - t18) + t1 * (2 * t8 * g__XO * f__XO + 2 * f__XO) + t18 + 2 * t8 * g__XO + 1) * p__XO * (k__XO * h__XO * t1 - t8 * t7 / 2 - g__XO * t7 / 2 + f__XO * h__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::zPosition_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t4   = cos(L__XO);
    real_type t7   = sin(L__XO);
    real_type t13  = pow(t1 + t2 + 1, 2);
    return -2 / t13 / (t4 * f__XO + g__XO * t7 + 1) * p__XO * t4 * (t1 - t2 + 1);
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
    real_type t34  = h__XO * h__XO;
    real_type t35  = k__XO * k__XO;
    real_type t46  = t16 * g__XO;
    real_type t50  = 3 * t16;
    return 4 / (t7 * t6 * (-3 * t16 * f__XO + t26 * f__XO) + t7 * (t14 * (3 * g__XO * t26 - t46) + 3 * t26 - t50) + 3 * t6 * (2 * t14 * g__XO + t16 + 1) * f__XO + t14 * (t46 + 3 * g__XO) + t50 + 1) / (t34 + t35 + 1) * p__XO * (t7 * (-t2 / 2 - t3 / 2) + t6 * (t14 * (-g__XO * k__XO * retrograde__XO / 2 + f__XO * h__XO / 2) - retrograde__XO * k__XO * t16 - h__XO * t19 + t21 / 2) + t14 * (t21 * t19 + h__XO * t26 - h__XO / 2) + t2 - t3 / 2);
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
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t6   = sin(L__XO);
    real_type t9   = k__XO * retrograde__XO;
    real_type t12  = cos(L__XO);
    real_type t20  = sqrt(p__XO);
    return -1.0 / (t3 + t4 + 1) / t20 * (t6 * (t3 - t4 + 1) - 2 * t9 * f__XO * h__XO - 2 * t9 * h__XO * t12 + t3 * g__XO - t4 * g__XO + g__XO) * t2;
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
    real_type t1   = sqrt(p__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t6   = t4 - t5 - 1;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t22  = sqrt(ModelPars[0]);
    real_type t25  = pow(t4 + t5 + 1, 2);
    return 1.0 / t25 * k__XO * t22 * (retrograde__XO * t6 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t11 * k__XO * h__XO + t8 * t6 * retrograde__XO) / t1 / p__XO;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t27  = sqrt(p__XO);
    real_type t32  = sqrt(ModelPars[0]);
    real_type t34  = pow(t2 + t3 + 1, 2);
    return -1.0 / t34 * t32 / t27 / p__XO * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO + t11 * (2 * k__XO * t2 + 2 * k__XO) + retrograde__XO * t2 * h__XO * f__XO + 2 * k__XO * t2 * g__XO + h__XO * (-retrograde__XO * t3 * f__XO + f__XO * retrograde__XO) + 2 * g__XO * k__XO);
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
    real_type t5   = sqrt(p__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    return 2 / (t8 + t9 + 1) / t5 * retrograde__XO * k__XO * h__XO * t2;
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
    real_type t4   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return 2 / (t7 + t8 + 1) / t4 * k__XO * h__XO * t2;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sqrt(p__XO);
    return -1.0 / (t3 + t4 + 1) / t7 * (t3 - t4 + 1) * t2;
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
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t5   = t3 - t4 - 1;
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t21  = sqrt(ModelPars[0]);
    real_type t24  = pow(t3 + t4 + 1, 2);
    return -2 / t24 * k__XO * t21 * (retrograde__XO * t5 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t10 * k__XO * h__XO + t7 * t5 * retrograde__XO) / t1;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t11  = t3 * k__XO;
    real_type t13  = sin(L__XO);
    real_type t16  = f__XO * h__XO;
    real_type t28  = sqrt(p__XO);
    real_type t32  = sqrt(ModelPars[0]);
    real_type t34  = t2 + t3 + 1;
    real_type t35  = t34 * t34;
    return 4 / t35 / t34 * k__XO * t32 / t28 * (t6 * (t2 - 3 * t3 - 3) * retrograde__XO * h__XO + t13 * (3 * k__XO * t2 - k__XO - t11) - t11 * g__XO - 3 * retrograde__XO * t3 * t16 + k__XO * (3 * t2 * g__XO - g__XO) + (t2 - 3) * retrograde__XO * t16);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = t1 * t1;
    real_type t3   = k__XO * k__XO;
    real_type t6   = t3 * t3;
    real_type t9   = cos(L__XO);
    real_type t13  = sin(L__XO);
    real_type t37  = sqrt(p__XO);
    real_type t41  = sqrt(ModelPars[0]);
    real_type t42  = t1 + t3 + 1;
    real_type t43  = t42 * t42;
    return -2 / t43 / t42 * t41 / t37 * (t9 * (-6 * t3 * t1 + t2 + t6 - 1) * retrograde__XO + 4 * t13 * (t1 - t3 + 1) * k__XO * h__XO + retrograde__XO * t2 * f__XO + 4 * k__XO * t1 * h__XO * g__XO - 6 * retrograde__XO * t3 * t1 * f__XO + h__XO * (-4 * t3 * k__XO * g__XO + 4 * g__XO * k__XO) + retrograde__XO * t6 * f__XO - f__XO * retrograde__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t8   = sin(L__XO);
    real_type t10  = cos(L__XO);
    real_type t16  = sqrt(ModelPars[0]);
    real_type t19  = pow(t4 + t5 + 1, 2);
    return 2 / t19 * t16 * (t8 * (t4 - t5 - 1) * retrograde__XO - 2 * t10 * k__XO * h__XO) * k__XO / t1;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = sqrt(ModelPars[0]);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = pow(t7 + t8 + 1, 2);
    real_type t14  = cos(L__XO);
    return -2 * (t14 + f__XO) * (t7 - t8 - 1) / t10 * k__XO * t4 / t1;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t27  = sqrt(p__XO);
    real_type t31  = sqrt(ModelPars[0]);
    real_type t33  = pow(t2 + t3 + 1, 2);
    return 2 / t33 * t31 / t27 * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO + t11 * (2 * k__XO * t2 + 2 * k__XO) + retrograde__XO * t2 * h__XO * f__XO + 2 * k__XO * t2 * g__XO + h__XO * (-retrograde__XO * t3 * f__XO + f__XO * retrograde__XO) + 2 * g__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t9   = sin(L__XO);
    real_type t16  = cos(L__XO);
    real_type t19  = t3 * t3;
    real_type t40  = sqrt(ModelPars[0]);
    real_type t41  = t3 + t5 + 1;
    real_type t42  = t41 * t41;
    return -12 / t42 / t41 * t40 * (-t9 * (t3 - 3 * t5 + 1) * (t3 + 1) / 3 + t16 * (t3 - t5 / 3 + 1) * k__XO * retrograde__XO * h__XO - t19 * g__XO / 3 + k__XO * retrograde__XO * t3 * h__XO * f__XO + t3 * (t5 - 2.0 / 3.0) * g__XO - h__XO * (t5 - 3) * retrograde__XO * f__XO * k__XO / 3 + (t5 - 1.0 / 3.0) * g__XO) / t1;
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t8   = cos(L__XO);
    real_type t14  = sqrt(p__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = pow(t2 + t3 + 1, 2);
    return -2 / t20 * t18 / t14 * (t5 * (t2 - t3 + 1) * h__XO * retrograde__XO - 2 * (t2 + 1) * t8 * k__XO);
  }

  real_type
  gtocX_2burn_pars::xVelocity_D_5_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = sqrt(ModelPars[0]);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t14  = cos(L__XO);
    return 2 * (t14 + f__XO) * (t6 - t7 + 1) * h__XO / t9 * t4 / t1;
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
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t3   = t1 - t2 - 1;
    real_type t5   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = sqrt(p__XO);
    return -2 / (t1 + t2 + 1) / t20 * t18 * (t5 * t3 * retrograde__XO / 2 + t9 * k__XO * h__XO + retrograde__XO * t3 * f__XO / 2 + g__XO * h__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t6   = t4 - t5 - 1;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t22  = sqrt(ModelPars[0]);
    return 1.0 / (2 * t4 + 2 * t5 + 2) * t22 * (retrograde__XO * t6 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t11 * k__XO * h__XO + t8 * t6 * retrograde__XO) / t1 / p__XO;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_1( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = p__XO * p__XO;
    real_type t2   = sqrt(p__XO);
    real_type t5   = h__XO * h__XO;
    real_type t6   = k__XO * k__XO;
    real_type t7   = t5 - t6 - 1;
    real_type t9   = cos(L__XO);
    real_type t12  = sin(L__XO);
    real_type t23  = sqrt(ModelPars[0]);
    return -3 / (4 * t5 + 4 * t6 + 4) * t23 * (retrograde__XO * t7 * f__XO + 2 * g__XO * h__XO * k__XO + 2 * t12 * k__XO * h__XO + t9 * t7 * retrograde__XO) / t2 / t1;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_1_2( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t5   = h__XO * h__XO;
    real_type t6   = k__XO * k__XO;
    real_type t9   = sqrt(ModelPars[0]);
    return 1.0 / (2 * t5 + 2 * t6 + 2) * t9 * (t5 - t6 - 1) * retrograde__XO / t1 / p__XO;
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
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t16  = f__XO * h__XO;
    real_type t25  = sqrt(p__XO);
    real_type t30  = sqrt(ModelPars[0]);
    real_type t32  = pow(t1 + t2 + 1, 2);
    return 2 / t32 * t30 / t25 / p__XO * (-t5 * (t1 - t2 - 1) * k__XO / 2 + (t2 + 1) * t9 * retrograde__XO * h__XO + t2 * k__XO * g__XO / 2 + retrograde__XO * t2 * t16 + k__XO * (-t1 * g__XO / 2 + g__XO / 2) + retrograde__XO * t16);
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
    real_type t1   = sqrt(p__XO);
    real_type t4   = h__XO * h__XO;
    real_type t5   = k__XO * k__XO;
    real_type t8   = sin(L__XO);
    real_type t10  = cos(L__XO);
    real_type t17  = sqrt(ModelPars[0]);
    return -1.0 / (2 * t4 + 2 * t5 + 2) * t17 * (t8 * (t4 - t5 - 1) * retrograde__XO - 2 * k__XO * h__XO * t10) / t1 / p__XO;
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
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = sqrt(ModelPars[0]);
    real_type t7   = sqrt(p__XO);
    return -1.0 / (t1 + t2 + 1) / t7 * t6 * (t1 - t2 - 1) * retrograde__XO;
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
    real_type t3   = h__XO * h__XO;
    real_type t6   = sqrt(p__XO);
    real_type t9   = k__XO * k__XO;
    real_type t11  = pow(t3 + t9 + 1, 2);
    return 4 / t11 / t6 * retrograde__XO * k__XO * t3 * t2;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_2_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sqrt(ModelPars[0]);
    real_type t7   = sqrt(p__XO);
    return -1.0 / (t1 + t2 + 1) / t7 * t5 * (t1 - t2 - 1);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t4   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return -2 / (t7 + t8 + 1) / t4 * k__XO * h__XO * t2;
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
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sqrt(p__XO);
    real_type t10  = pow(t3 + t4 + 1, 2);
    return -2 * h__XO / t10 / t7 * (t3 - t4 + 1) * t2;
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
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t16  = f__XO * h__XO;
    real_type t25  = sqrt(p__XO);
    real_type t29  = sqrt(ModelPars[0]);
    real_type t31  = pow(t1 + t2 + 1, 2);
    return -4 / t31 * t29 / t25 * (-t5 * (t1 - t2 - 1) * k__XO / 2 + (t2 + 1) * t9 * retrograde__XO * h__XO + t2 * k__XO * g__XO / 2 + retrograde__XO * t2 * t16 + k__XO * (-t1 * g__XO / 2 + g__XO / 2) + retrograde__XO * t16);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t9   = cos(L__XO);
    real_type t15  = sin(L__XO);
    real_type t19  = t4 * t4;
    real_type t23  = g__XO * h__XO;
    real_type t26  = f__XO * retrograde__XO;
    real_type t39  = sqrt(ModelPars[0]);
    real_type t40  = t3 + t4 + 1;
    real_type t41  = t40 * t40;
    return 12 / t41 / t40 * t39 * (t9 * (t4 + 1) * (t3 - t4 / 3 - 1.0 / 3.0) * retrograde__XO - t15 * (t3 - 3 * t4 - 3) * k__XO * h__XO / 3 - retrograde__XO * t19 * f__XO / 3 + t4 * k__XO * t23 + t4 * (t3 - 2.0 / 3.0) * t26 - k__XO * (t3 - 3) * t23 / 3 + (t3 - 1.0 / 3.0) * t26) / t1;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = t3 * t3;
    real_type t6   = k__XO * k__XO;
    real_type t9   = t6 * t6;
    real_type t12  = sin(L__XO);
    real_type t17  = cos(L__XO);
    real_type t40  = sqrt(ModelPars[0]);
    real_type t41  = t3 + t6 + 1;
    real_type t42  = t41 * t41;
    return -8 / t42 / t41 * t40 * (t12 * (-t4 / 4 + 3.0 / 2.0 * t6 * t3 - t9 / 4 + 1.0 / 4.0) + t17 * (t3 - t6 - 1) * k__XO * retrograde__XO * h__XO - t4 * g__XO / 4 + k__XO * retrograde__XO * t3 * h__XO * f__XO + 3.0 / 2.0 * t6 * t3 * g__XO - h__XO * (t6 + 1) * retrograde__XO * f__XO * k__XO - t9 * g__XO / 4 + g__XO / 4) / t1;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t9   = sin(L__XO);
    real_type t14  = sqrt(p__XO);
    real_type t18  = sqrt(ModelPars[0]);
    real_type t20  = pow(t1 + t2 + 1, 2);
    return 4 / t20 * t18 / t14 * (t5 * (t1 - t2 - 1) * k__XO / 2 + (t2 + 1) * t9 * retrograde__XO * h__XO);
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_4_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = sqrt(ModelPars[0]);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t14  = cos(L__XO);
    return -4 * (t14 + f__XO) * (t7 + 1) * h__XO / t9 * t4 / t1;
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
    real_type t2   = h__XO * h__XO;
    real_type t3   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t14  = sin(L__XO);
    real_type t32  = sqrt(p__XO);
    real_type t35  = sqrt(ModelPars[0]);
    real_type t37  = t2 + t3 + 1;
    real_type t38  = t37 * t37;
    return 4 / t38 / t37 * t35 / t32 * (t6 * (t2 - 3 * t3 + 1) * h__XO * retrograde__XO + t14 * (3 * k__XO * t2 - t3 * k__XO + 3 * k__XO) + retrograde__XO * t2 * h__XO * f__XO + 3 * k__XO * t2 * g__XO - 3 * h__XO * (t3 - 1.0 / 3.0) * f__XO * retrograde__XO - (t3 - 3) * k__XO * g__XO) * h__XO;
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
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = cos(L__XO);
    real_type t16  = sqrt(ModelPars[0]);
    return 1.0 / (t3 + t4 + 1) * t16 * (t7 * (t3 - t4 - 1) * retrograde__XO - 2 * k__XO * h__XO * t9) / t1;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_6_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = cos(L__XO);
    real_type t10  = sin(L__XO);
    real_type t16  = sqrt(ModelPars[0]);
    return 1.0 / (t3 + t4 + 1) * t16 * (t7 * (t3 - t4 - 1) * retrograde__XO + 2 * t10 * k__XO * h__XO) / t1;
  }

  real_type
  gtocX_2burn_pars::yVelocity_D_6_7( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t7   = sin(L__XO);
    real_type t9   = sqrt(ModelPars[0]);
    return 1.0 / (t3 + t4 + 1) * t9 * t7 * (t3 - t4 - 1) / t1;
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
    real_type t1   = sqrt(p__XO);
    real_type t5   = sin(L__XO);
    real_type t9   = h__XO * h__XO;
    real_type t10  = k__XO * k__XO;
    real_type t12  = cos(L__XO);
    real_type t23  = sqrt(ModelPars[0]);
    real_type t25  = pow(t9 + t10 + 1, 2);
    return 1.0 / t25 * t23 * (2 * t5 * k__XO * retrograde__XO * h__XO + t12 * (t9 - t10 - 1) + 2 * g__XO * h__XO * k__XO * retrograde__XO + t9 * f__XO - t10 * f__XO - f__XO) / t1 / p__XO;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_1_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = cos(L__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = (t7 - t8 + 1) * retrograde__XO;
    real_type t11  = sin(L__XO);
    real_type t21  = sqrt(ModelPars[0]);
    real_type t23  = pow(t7 + t8 + 1, 2);
    return 2 / t23 * t21 * (k__XO * h__XO * t4 - t11 * t10 / 2 - g__XO * t10 / 2 + f__XO * h__XO * k__XO) / t1 / p__XO;
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
    real_type t4   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    return 2 / (t6 + t7 + 1) / t4 * h__XO * t2;
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
    real_type t4   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    return -4 * k__XO / t9 / t4 * h__XO * t2;
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
    real_type t4   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    return 2 / (t7 + t8 + 1) / t4 * retrograde__XO * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_3( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    return 0;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_3_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t2   = sqrt(ModelPars[0]);
    real_type t5   = sqrt(p__XO);
    real_type t7   = h__XO * h__XO;
    real_type t8   = k__XO * k__XO;
    real_type t10  = pow(t7 + t8 + 1, 2);
    return -4 * h__XO / t10 / t5 * retrograde__XO * k__XO * t2;
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
    real_type t4   = sqrt(p__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    return 2 / (t6 + t7 + 1) / t4 * k__XO * t2;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t4   = sin(L__XO);
    real_type t8   = h__XO * h__XO;
    real_type t9   = k__XO * k__XO;
    real_type t11  = cos(L__XO);
    real_type t22  = sqrt(ModelPars[0]);
    real_type t24  = pow(t8 + t9 + 1, 2);
    return -2 / t24 * t22 * (2 * t4 * k__XO * retrograde__XO * h__XO + t11 * (t8 - t9 - 1) + 2 * g__XO * h__XO * k__XO * retrograde__XO + t8 * f__XO - t9 * f__XO - f__XO) / t1;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t30  = sqrt(p__XO);
    real_type t34  = sqrt(ModelPars[0]);
    real_type t35  = t1 + t2 + 1;
    real_type t36  = t35 * t35;
    return 4 / t36 / t35 * t34 / t30 * (t6 * (t1 - 3 * t2 - 3) * h__XO + 3 * t11 * k__XO * (t1 - t2 / 3 - 1.0 / 3.0) * retrograde__XO + t1 * h__XO * f__XO + 3 * k__XO * retrograde__XO * t1 * g__XO + h__XO * (-3 * t2 * f__XO - 3 * f__XO) - (t2 + 1) * retrograde__XO * g__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_4_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = h__XO * h__XO;
    real_type t4   = k__XO * k__XO;
    real_type t8   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t34  = sqrt(ModelPars[0]);
    real_type t35  = t3 + t4 + 1;
    real_type t36  = t35 * t35;
    return 12 / t36 / t35 * t34 * (t8 * k__XO * (t3 - t4 / 3 - 1.0 / 3.0) - (t3 - 3 * t4 + 1) * t11 * retrograde__XO * h__XO / 3 - retrograde__XO * t3 * h__XO * g__XO / 3 + k__XO * t3 * f__XO + h__XO * (t4 - 1.0 / 3.0) * g__XO * retrograde__XO - (t4 + 1) * k__XO * f__XO / 3) / t1;
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
    real_type t1   = sqrt(p__XO);
    real_type t4   = sqrt(ModelPars[0]);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = pow(t6 + t7 + 1, 2);
    real_type t13  = sin(L__XO);
    return -4 * (t13 + g__XO) * k__XO * h__XO / t9 * t4 / t1;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = sqrt(p__XO);
    real_type t3   = cos(L__XO);
    real_type t6   = h__XO * h__XO;
    real_type t7   = k__XO * k__XO;
    real_type t9   = (t6 - t7 + 1) * retrograde__XO;
    real_type t10  = sin(L__XO);
    real_type t20  = sqrt(ModelPars[0]);
    real_type t22  = pow(t6 + t7 + 1, 2);
    return -4 / t22 * t20 * (k__XO * h__XO * t3 - t10 * t9 / 2 - g__XO * t9 / 2 + f__XO * h__XO * k__XO) / t1;
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5_5( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t6   = cos(L__XO);
    real_type t11  = sin(L__XO);
    real_type t30  = sqrt(p__XO);
    real_type t34  = sqrt(ModelPars[0]);
    real_type t35  = t1 + t2 + 1;
    real_type t36  = t35 * t35;
    return -4 / t36 / t35 * t34 / t30 * (t6 * (t1 - 3 * t2 + 1) * h__XO + 3 * t11 * k__XO * (t1 - t2 / 3 + 1) * retrograde__XO + t1 * h__XO * f__XO + 3 * k__XO * retrograde__XO * t1 * g__XO + h__XO * (-3 * t2 * f__XO + f__XO) - (t2 - 3) * retrograde__XO * g__XO * k__XO);
  }

  real_type
  gtocX_2burn_pars::zVelocity_D_5_6( real_type p__XO, real_type f__XO, real_type g__XO, real_type h__XO, real_type k__XO, real_type L__XO, real_type retrograde__XO ) const {
    real_type t1   = h__XO * h__XO;
    real_type t2   = k__XO * k__XO;
    real_type t5   = cos(L__XO);
    real_type t8   = sin(L__XO);
    real_type t12  = sqrt(p__XO);
    real_type t16  = sqrt(ModelPars[0]);
    real_type t18  = pow(t1 + t2 + 1, 2);
    return 2 / t18 * t16 / t12 * (t5 * (t1 - t2 + 1) * retrograde__XO + 2 * t8 * k__XO * h__XO);
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
    real_type t7   = t6 + t1 + t2 + t4;
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
    return 1.0 / (2 * f__XO * g__XO * t1 * t3 + 2 * t3 * f__XO + 2 * t1 * g__XO + t7 * t6 - t9 * t6 + t9 + 1) * (t1 * f__XO - g__XO * t3);
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
    return 2 / (t2 * t1 * (t4 * f__XO - 3 * t6 * f__XO) + t2 * (t16 * (3 * g__XO * t4 - t14) + 3 * t4 - t19) + 3 * t1 * (2 * t16 * g__XO + t6 + 1) * f__XO + t16 * (t14 + 3 * g__XO) + t19 + 1) * t2 * p__XO;
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
    return 2 / (t10 * t1 * (t4 * f__XO - 3 * t6 * f__XO) + t10 * (t3 * (3 * g__XO * t4 - t15) + 3 * t4 - t19) + 3 * t1 * (2 * g__XO * t3 + t6 + 1) * f__XO + t3 * (t15 + 3 * g__XO) + t19 + 1) * t3 * t1 * p__XO;
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
    return -1.0 / (t2 * t1 * (-3 * t11 * f__XO + t9 * f__XO) + t2 * (t4 * (3 * g__XO * t9 - t19) + 3 * t9 - t23) + 3 * t1 * (2 * g__XO * t4 + t11 + 1) * f__XO + t4 * (t19 + 3 * g__XO) + t23 + 1) * p__XO * (f__XO * t4 * t1 - g__XO * t2 - g__XO - t4);
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
    real_type t5   = g__XO * t4;
    real_type t11  = f__XO * f__XO;
    real_type t13  = g__XO * g__XO;
    real_type t21  = t13 * g__XO;
    real_type t25  = 3 * t13;
    return 1.0 / (t2 * t1 * (t11 * f__XO - 3 * t13 * f__XO) + t2 * (t4 * (3 * t11 * g__XO - t21) + 3 * t11 - t25) + 3 * t1 * (t13 + 2 * t5 + 1) * f__XO + t4 * (t21 + 3 * g__XO) + t25 + 1) * (f__XO * t2 + t1 * (t5 - 1) - 2 * f__XO) * p__XO;
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
    real_type t25  = g__XO * t2;
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
    real_type t15  = sqrt(2 * t6 * f__XO + 2 * g__XO * t9 + t12 + t13 + 1);
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
    return -1.0 / t18 * (-t6 * f__XO + g__XO * t8) / t2 / p__XO * t1 / 2;
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
    real_type t15  = sqrt(2 * t2 * f__XO + 2 * t9 * g__XO + t12 + t13 + 1);
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
    real_type t15  = 2 * t2 * f__XO + t14 + t6 + t7 + 1;
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
    real_type t13  = sqrt(muS__XO);
    real_type t15  = t1 * t1;
    real_type t23  = sqrt(p__XO);
    return -1.0 / t23 * (-g__XO * t15 + t1 * (t4 + g__XO) * f__XO + t8 * t4 + 2 * g__XO + t4) * t13 / t10 / t9;
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
    return 1.0 / t17 / t8 * (-t2 * f__XO + g__XO * t4) * t1;
  }

  real_type
  gtocX_2burn_pars::vel_D_4_4( real_type p__XO, real_type f__XO, real_type g__XO, real_type L__XO, real_type muS__XO ) const {
    real_type t1   = cos(L__XO);
    real_type t4   = sin(L__XO);
    real_type t6   = 2 * g__XO * t4;
    real_type t7   = f__XO * f__XO;
    real_type t8   = g__XO * g__XO;
    real_type t9   = 2 * t1 * f__XO + t6 + t7 + t8 + 1;
    real_type t10  = sqrt(t9);
    real_type t13  = sqrt(muS__XO);
    real_type t16  = t1 * t1;
    real_type t26  = sqrt(p__XO);
    return -1.0 / t26 * (t16 * (t7 - t8) + t1 * (t7 + t8 + t6 + 1) * f__XO + t4 * (t7 + t8 + 1) * g__XO + t7 + 2 * t8) * t13 / t10 / t9;
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
    real_type t10  = sqrt(2 * t1 * f__XO + 2 * g__XO * t4 + t7 + t8 + 1);
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
    real_type t10  = sqrt(2 * t1 * f__XO + 2 * g__XO * t4 + t7 + t8 + 1);
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

}

// EOF: gtocX_2burn_pars_Methods1.cc
