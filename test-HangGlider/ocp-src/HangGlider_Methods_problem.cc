/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods1.cc                                         |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HangGlider::continuationStep0( real_type s ) {
    int msg_level = 3;
    pConsole->message(
      fmt::format( "\nContinuation step N.0 s = {}\n", s ),
      msg_level
    );
    ModelPars[2] = (1 - s) * ModelPars[3] + s * ModelPars[4];
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HangGlider::continuationStep1( real_type s ) {
    int msg_level = 3;
    pConsole->message(
      fmt::format( "\nContinuation step N.1 s = {}\n", s ),
      msg_level
    );
    real_type t2   = 1 - s;
    real_type t3   = pow(ModelPars[23], t2);
    real_type t5   = pow(ModelPars[24], s);
    cLControl.update_epsilon(t5 * t3);
    real_type t8   = pow(ModelPars[13], t2);
    real_type t10  = pow(ModelPars[14], s);
    cLControl.update_tolerance(t10 * t8);
  }

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
    real_type t2   = r(x__XO);
    real_type t3   = exp(-t2);
    real_type t6   = r_DD(x__XO);
    real_type t8   = r_D(x__XO);
    real_type t9   = t8 * t8;
    return -(t6 * (-t2 + 2) + (t2 - 3) * t9) * t3 * ModelPars[15];
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


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  HangGlider::H_eval(
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
    real_type t1   = P__[0];
    real_type t2   = Tbound(t1);
    real_type t4   = U__[0];
    real_type t6   = pow(t4 - 0.7e0, 2);
    real_type t10  = X__[2];
    real_type t14  = X__[3];
    real_type t19  = 1.0 / ModelPars[10];
    real_type t20  = X__[0];
    real_type t21  = v(t20, t10, t14);
    real_type t22  = 1.0 / t21;
    real_type t24  = t4 * t4;
    real_type t29  = Dfun(t20, t10, t14);
    real_type t30  = t29 * (ModelPars[6] * t24 + ModelPars[5]);
    real_type t32  = Lfun(t20, t10, t14);
    real_type t33  = t32 * t4;
    real_type t34  = w(t20, t14);
    return t2 + t6 * ModelPars[2] + t10 * t1 * L__[0] + t14 * t1 * L__[1] + (-t10 * t30 - t34 * t33) * t22 * t19 * t1 * L__[2] + ((t10 * t33 - t34 * t30) * t22 * t19 * t1 - ModelPars[9] * t1) * L__[3];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  HangGlider::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return Tbound(P__[0]);
  }

  real_type
  HangGlider::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return cLControl(U__[0], ModelPars[8], ModelPars[7]);
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  HangGlider::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t4   = pow(U__[0] - 0.7e0, 2);
    return t4 * ModelPars[2];
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  HangGlider::mayer_target(
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
    return -XR__[0];
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  HangGlider::q_numEqns() const
  { return 1; }

  void
  HangGlider::q_eval(
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
  HangGlider::u_guess_numEqns() const
  { return 1; }

  void
  HangGlider::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
      MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    std::fill_n( UGUESS__.pointer(), 1, 0 );
    UGUESS__[ iU_cL ] = 0.7e0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(UGUESS__.pointer(),"u_guess_eval",1);
    #endif
  }

  void
  HangGlider::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  HangGlider::u_check_if_admissible(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    bool ok = true;
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    ok = ok && cLControl.check_range(U__[0], ModelPars[8], ModelPars[7]);
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
  HangGlider::post_numEqns() const
  { return 0; }

  void
  HangGlider::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::integrated_post_numEqns() const
  { return 0; }

  void
  HangGlider::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: HangGlider_Methods1.cc
