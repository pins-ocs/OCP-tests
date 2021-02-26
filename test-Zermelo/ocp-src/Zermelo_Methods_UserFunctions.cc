/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods1.cc                                            |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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


namespace ZermeloDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  Zermelo::velX( real_type x__XO, real_type y__XO ) const {
    return -y__XO;
  }

  real_type
  Zermelo::velX_D_1( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velX_D_1_1( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velX_D_1_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velX_D_2( real_type x__XO, real_type y__XO ) const {
    return -1;
  }

  real_type
  Zermelo::velX_D_2_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velY( real_type x__XO, real_type y__XO ) const {
    return x__XO;
  }

  real_type
  Zermelo::velY_D_1( real_type x__XO, real_type y__XO ) const {
    return 1;
  }

  real_type
  Zermelo::velY_D_1_1( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velY_D_1_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velY_D_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  Zermelo::velY_D_2_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

}

// EOF: Zermelo_Methods1.cc
