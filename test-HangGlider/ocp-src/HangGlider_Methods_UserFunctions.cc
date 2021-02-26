/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods1.cc                                         |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  HangGlider::r( real_type x__XO ) const {
    return pow(x__XO / ModelPars[11] - 0.25e1, 2);
  }

  real_type
  HangGlider::r_D( real_type x__XO ) const {
    real_type t2   = ModelPars[11];
    real_type t5   = t2 * t2;
    return 1.0 / t5 * (2.0 * x__XO - 5.0 * t2);
  }

  real_type
  HangGlider::r_DD( real_type x__XO ) const {
    real_type t2   = ModelPars[11] * ModelPars[11];
    return 2.0 / t2;
  }

  real_type
  HangGlider::u( real_type x__XO ) const {
    real_type t2   = r(x__XO);
    real_type t5   = exp(-t2);
    return t5 * (1 - t2) * ModelPars[15];
  }

  real_type
  HangGlider::u_D( real_type x__XO ) const {
    real_type t2   = r_D(x__XO);
    real_type t4   = r(x__XO);
    real_type t5   = exp(-t4);
    return (t4 - 2) * t5 * t2 * ModelPars[15];
  }

  real_type
  HangGlider::u_DD( real_type x__XO ) const {
    real_type t1   = r(x__XO);
    real_type t3   = r_DD(x__XO);
    real_type t5   = r_D(x__XO);
    real_type t6   = t5 * t5;
    real_type t12  = exp(-t1);
    return -t12 * ModelPars[15] * (t3 * (-t1 + 2) + (t1 - 3) * t6);
  }

  real_type
  HangGlider::w( real_type x__XO, real_type y1__XO ) const {
    real_type t1   = u(x__XO);
    return y1__XO - t1;
  }

  real_type
  HangGlider::w_D_1( real_type x__XO, real_type y1__XO ) const {
    real_type t1   = u_D(x__XO);
    return -t1;
  }

  real_type
  HangGlider::w_D_1_1( real_type x__XO, real_type y1__XO ) const {
    real_type t1   = u_DD(x__XO);
    return -t1;
  }

  real_type
  HangGlider::w_D_1_2( real_type x__XO, real_type y1__XO ) const {
    return 0;
  }

  real_type
  HangGlider::w_D_2( real_type x__XO, real_type y1__XO ) const {
    return 1;
  }

  real_type
  HangGlider::w_D_2_2( real_type x__XO, real_type y1__XO ) const {
    return 0;
  }

  real_type
  HangGlider::v2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = x1__XO * x1__XO;
    real_type t2   = w(x__XO, y1__XO);
    real_type t3   = t2 * t2;
    return t1 + t3;
  }

  real_type
  HangGlider::v2_D_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = w(x__XO, y1__XO);
    real_type t2   = w_D_1(x__XO, y1__XO);
    return 2 * t2 * t1;
  }

  real_type
  HangGlider::v2_D_1_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = w_D_1(x__XO, y1__XO);
    real_type t2   = t1 * t1;
    real_type t3   = w(x__XO, y1__XO);
    real_type t4   = w_D_1_1(x__XO, y1__XO);
    return 2 * t4 * t3 + 2 * t2;
  }

  real_type
  HangGlider::v2_D_1_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    return 0;
  }

  real_type
  HangGlider::v2_D_1_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = w_D_2(x__XO, y1__XO);
    real_type t2   = w_D_1(x__XO, y1__XO);
    real_type t4   = w(x__XO, y1__XO);
    real_type t5   = w_D_1_2(x__XO, y1__XO);
    return 2 * t2 * t1 + 2 * t5 * t4;
  }

  real_type
  HangGlider::v2_D_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    return 2 * x1__XO;
  }

  real_type
  HangGlider::v2_D_2_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    return 2;
  }

  real_type
  HangGlider::v2_D_2_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    return 0;
  }

  real_type
  HangGlider::v2_D_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = w(x__XO, y1__XO);
    real_type t2   = w_D_2(x__XO, y1__XO);
    return 2 * t2 * t1;
  }

  real_type
  HangGlider::v2_D_3_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = w_D_2(x__XO, y1__XO);
    real_type t2   = t1 * t1;
    real_type t3   = w(x__XO, y1__XO);
    real_type t4   = w_D_2_2(x__XO, y1__XO);
    return 2 * t4 * t3 + 2 * t2;
  }

  real_type
  HangGlider::v( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2(x__XO, x1__XO, y1__XO);
    return sqrt(t1);
  }

  real_type
  HangGlider::v_D_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2(x__XO, x1__XO, y1__XO);
    real_type t2   = sqrt(t1);
    real_type t4   = v2_D_1(x__XO, x1__XO, y1__XO);
    return t4 / t2 / 2;
  }

  real_type
  HangGlider::v_D_1_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2_D_1_1(x__XO, x1__XO, y1__XO);
    real_type t2   = v2(x__XO, x1__XO, y1__XO);
    real_type t5   = v2_D_1(x__XO, x1__XO, y1__XO);
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t2);
    return 1.0 / t8 / t2 * (2 * t2 * t1 - t6) / 4;
  }

  real_type
  HangGlider::v_D_1_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2_D_1_2(x__XO, x1__XO, y1__XO);
    real_type t2   = v2(x__XO, x1__XO, y1__XO);
    real_type t5   = v2_D_1(x__XO, x1__XO, y1__XO);
    real_type t6   = v2_D_2(x__XO, x1__XO, y1__XO);
    real_type t9   = sqrt(t2);
    return 1.0 / t9 / t2 * (2 * t2 * t1 - t6 * t5) / 4;
  }

  real_type
  HangGlider::v_D_1_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2_D_1_3(x__XO, x1__XO, y1__XO);
    real_type t2   = v2(x__XO, x1__XO, y1__XO);
    real_type t5   = v2_D_1(x__XO, x1__XO, y1__XO);
    real_type t6   = v2_D_3(x__XO, x1__XO, y1__XO);
    real_type t9   = sqrt(t2);
    return 1.0 / t9 / t2 * (2 * t2 * t1 - t6 * t5) / 4;
  }

  real_type
  HangGlider::v_D_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2(x__XO, x1__XO, y1__XO);
    real_type t2   = sqrt(t1);
    real_type t4   = v2_D_2(x__XO, x1__XO, y1__XO);
    return t4 / t2 / 2;
  }

  real_type
  HangGlider::v_D_2_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2_D_2_2(x__XO, x1__XO, y1__XO);
    real_type t2   = v2(x__XO, x1__XO, y1__XO);
    real_type t5   = v2_D_2(x__XO, x1__XO, y1__XO);
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t2);
    return 1.0 / t8 / t2 * (2 * t2 * t1 - t6) / 4;
  }

  real_type
  HangGlider::v_D_2_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2_D_2_3(x__XO, x1__XO, y1__XO);
    real_type t2   = v2(x__XO, x1__XO, y1__XO);
    real_type t5   = v2_D_2(x__XO, x1__XO, y1__XO);
    real_type t6   = v2_D_3(x__XO, x1__XO, y1__XO);
    real_type t9   = sqrt(t2);
    return 1.0 / t9 / t2 * (2 * t2 * t1 - t6 * t5) / 4;
  }

  real_type
  HangGlider::v_D_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2(x__XO, x1__XO, y1__XO);
    real_type t2   = sqrt(t1);
    real_type t4   = v2_D_3(x__XO, x1__XO, y1__XO);
    return t4 / t2 / 2;
  }

  real_type
  HangGlider::v_D_3_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t1   = v2_D_3_3(x__XO, x1__XO, y1__XO);
    real_type t2   = v2(x__XO, x1__XO, y1__XO);
    real_type t5   = v2_D_3(x__XO, x1__XO, y1__XO);
    real_type t6   = t5 * t5;
    real_type t8   = sqrt(t2);
    return 1.0 / t8 / t2 * (2 * t2 * t1 - t6) / 4;
  }

  real_type
  HangGlider::Dfun( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_1_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1_1(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_1_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1_2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_1_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_2_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_2_2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_2_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_2_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Dfun_D_3_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_3_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_1_1( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1_1(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_1_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1_2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_1_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_1_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_2_2( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_2_2(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_2_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_2_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

  real_type
  HangGlider::Lfun_D_3_3( real_type x__XO, real_type x1__XO, real_type y1__XO ) const {
    real_type t4   = v2_D_3_3(x__XO, x1__XO, y1__XO);
    return 0.5e0 * t4 * ModelPars[0] * ModelPars[12];
  }

}

// EOF: HangGlider_Methods1.cc
