/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods1.cc                                      |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {
  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  MaximumAscent::eta( real_type tf__XO ) const {
    return ModelPars[11] * tf__XO / ModelPars[6];
  }

  real_type
  MaximumAscent::eta_D( real_type tf__XO ) const {
    return ModelPars[11] / ModelPars[6];
  }

  real_type
  MaximumAscent::eta_DD( real_type tf__XO ) const {
    return 0;
  }

  real_type
  MaximumAscent::Tbar( real_type tf__XO ) const {
    return ModelPars[0] * tf__XO / ModelPars[11];
  }

  real_type
  MaximumAscent::Tbar_D( real_type tf__XO ) const {
    return ModelPars[0] / ModelPars[11];
  }

  real_type
  MaximumAscent::Tbar_DD( real_type tf__XO ) const {
    return 0;
  }

  real_type
  MaximumAscent::tf( real_type days__XO ) const {
    return 86400 * days__XO;
  }

  real_type
  MaximumAscent::tf_D( real_type days__XO ) const {
    return 86400;
  }

  real_type
  MaximumAscent::tf_DD( real_type days__XO ) const {
    return 0;
  }

}

// EOF: MaximumAscent_Methods1.cc
