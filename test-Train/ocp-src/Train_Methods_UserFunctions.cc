/*-----------------------------------------------------------------------*\
 |  file: Train_Methods1.cc                                              |
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


#include "Train.hh"
#include "Train_Pars.hh"

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
#define ALIAS_ubControl_D_3(__t1, __t2, __t3) ubControl.D_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2(__t1, __t2, __t3) ubControl.D_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1(__t1, __t2, __t3) ubControl.D_1( __t1, __t2, __t3)
#define ALIAS_ubControl_D_3_3(__t1, __t2, __t3) ubControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_3(__t1, __t2, __t3) ubControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_2(__t1, __t2, __t3) ubControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_3(__t1, __t2, __t3) ubControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_2(__t1, __t2, __t3) ubControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_1(__t1, __t2, __t3) ubControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3(__t1, __t2, __t3) uaControl.D_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2(__t1, __t2, __t3) uaControl.D_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1(__t1, __t2, __t3) uaControl.D_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3_3(__t1, __t2, __t3) uaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_3(__t1, __t2, __t3) uaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_2(__t1, __t2, __t3) uaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_3(__t1, __t2, __t3) uaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_2(__t1, __t2, __t3) uaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_1(__t1, __t2, __t3) uaControl.D_1_1( __t1, __t2, __t3)


namespace TrainDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  Train::acc( real_type x__XO, real_type v__XO ) const {
    real_type t1   = h(x__XO);
    real_type t3   = v__XO * v__XO;
    return -t3 * ModelPars[2] - ModelPars[1] * v__XO + t1 - ModelPars[0];
  }

  real_type
  Train::acc_D_1( real_type x__XO, real_type v__XO ) const {
    return h_D(x__XO);
  }

  real_type
  Train::acc_D_1_1( real_type x__XO, real_type v__XO ) const {
    return h_DD(x__XO);
  }

  real_type
  Train::acc_D_1_2( real_type x__XO, real_type v__XO ) const {
    return 0;
  }

  real_type
  Train::acc_D_2( real_type x__XO, real_type v__XO ) const {
    return -2 * v__XO * ModelPars[2] - ModelPars[1];
  }

  real_type
  Train::acc_D_2_2( real_type x__XO, real_type v__XO ) const {
    return -2 * ModelPars[2];
  }

}

// EOF: Train_Methods1.cc
