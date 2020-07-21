/*-----------------------------------------------------------------------*\
 |  file: Train_Methods1.cc                                              |
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


#include "Train.hh"
#include "Train_Pars.hh"

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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  Train::continuationStep0( real_type s ) {
    int msg_level = 3;
    pConsole->message(
      fmt::format( "\nContinuation step N.0 s = {}\n", s ),
      msg_level
    );
    real_type t2   = 1 - s;
    real_type t6   = ModelPars[12] * s + t2 * ModelPars[11];
    uaControl.update_epsilon(t6);
    ubControl.update_epsilon(t6);
    real_type t11  = ModelPars[4] * s + t2 * ModelPars[3];
    uaControl.update_tolerance(t11);
    ubControl.update_tolerance(t11);
  }

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


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  Train::H_eval(
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
    real_type t1   = U__[0];
    real_type t2   = X__[1];
    real_type t8   = acc(X__[0], t2);
    return t2 * t1 + t2 * L__[0] + (t8 + t1 - U__[1]) * L__[1];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  Train::penalties_eval(
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

  real_type
  Train::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = uaControl(U__[0], 0, ModelPars[5]);
    real_type t6   = ubControl(U__[1], 0, ModelPars[6]);
    return t3 + t6;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  Train::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return U__[0] * X__[1];
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  Train::mayer_target(
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
  Train::q_numEqns() const
  { return 1; }

  void
  Train::q_eval(
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
  Train::u_guess_numEqns() const
  { return 2; }

  void
  Train::u_guess_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
      MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    std::fill_n( UGUESS__.pointer(), 2, 0 );
    UGUESS__[ iU_ua ] = ModelPars[5] / 2;
    UGUESS__[ iU_ub ] = ModelPars[6] / 2;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(UGUESS__.pointer(),"u_guess_eval",2);
    #endif
  }

  void
  Train::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q      = Q__;
    NODE__.x      = X__;
    NODE__.lambda = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  Train::u_check_if_admissible(
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
    ok = ok && uaControl.check_range(U__[0], 0, ModelPars[5]);
    ok = ok && ubControl.check_range(U__[1], 0, ModelPars[6]);
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
  Train::post_numEqns() const
  { return 3; }

  void
  Train::post_eval(
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
    result__[ 0   ] = uaControl(U__[0], 0, ModelPars[5]);
    result__[ 1   ] = ubControl(U__[1], 0, ModelPars[6]);
    result__[ 2   ] = h(X__[0]);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"post_eval",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Train::integrated_post_numEqns() const
  { return 0; }

  void
  Train::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: Train_Methods1.cc
