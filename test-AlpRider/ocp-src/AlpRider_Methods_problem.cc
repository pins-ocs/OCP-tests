/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods1.cc                                           |
 |                                                                       |
 |  version: 1.0   date 14/12/2020                                       |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  AlpRider::continuationStep0( real_type s ) {
    int msg_level = 3;
    m_console->message(
      fmt::format( "\nContinuation step N.0 s = {}\n", s ),
      msg_level
    );
    ModelPars[0] = ModelPars[1] * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  AlpRider::continuationStep1( real_type s ) {
    int msg_level = 3;
    m_console->message(
      fmt::format( "\nContinuation step N.1 s = {}\n", s ),
      msg_level
    );
    real_type t2   = 1 - s;
    Ybound.update_epsilon(ModelPars[3] * s + t2 * ModelPars[2]);
    Ybound.update_tolerance(ModelPars[5] * s + t2 * ModelPars[4]);
  }

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
    return 4 * (-1.0 / 2.0 + t3) * t4 * b__XO;
  }

  real_type
  AlpRider::p_D_1_2( real_type t__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(-t__XO + a__XO, 2);
    real_type t3   = t2 * b__XO;
    real_type t4   = exp(-t3);
    return -4 * (-1.0 / 2.0 + t3) * t4 * b__XO;
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
    return 4 * (-1.0 / 2.0 + t3) * t4 * b__XO;
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


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  AlpRider::H_eval(
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
    real_type t2   = t1 * t1;
    real_type t3   = X__[1];
    real_type t4   = t3 * t3;
    real_type t5   = X__[2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[3];
    real_type t8   = t7 * t7;
    real_type t10  = q(Q__[0]);
    real_type t12  = Ybound(t2 + t4 + t6 + t8 - t10);
    real_type t16  = U__[0];
    real_type t17  = t16 * t16;
    real_type t19  = U__[1];
    real_type t20  = t19 * t19;
    return t12 + (t2 + t4 + t6 + t8) * ModelPars[0] + 0.1e-1 * t17 + 0.1e-1 * t20 + (-10 * t1 + t16 + t19) * L__[0] + (-2 * t3 + t16 + 2 * t19) * L__[1] + (-3 * t5 + 5 * t7 + t16 - t19) * L__[2] + (5 * t5 - 3 * t7 + t16 + 3 * t19) * L__[3];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  AlpRider::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[0] * X__[0];
    real_type t4   = X__[1] * X__[1];
    real_type t6   = X__[2] * X__[2];
    real_type t8   = X__[3] * X__[3];
    real_type t10  = q(Q__[0]);
    return Ybound(t2 + t4 + t6 + t8 - t10);
  }

  real_type
  AlpRider::control_penalties_eval(
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
  AlpRider::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = X__[0] * X__[0];
    real_type t5   = X__[1] * X__[1];
    real_type t7   = X__[2] * X__[2];
    real_type t9   = X__[3] * X__[3];
    real_type t13  = U__[0] * U__[0];
    real_type t16  = U__[1] * U__[1];
    return (t3 + t5 + t7 + t9) * ModelPars[0] + 0.1e-1 * t13 + 0.1e-1 * t16;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  AlpRider::mayer_target(
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
  AlpRider::q_numEqns() const
  { return 1; }

  void
  AlpRider::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |    ___
   |   / __|_  _ ___ ______
   |  | (_ | || / -_|_-<_-<
   |   \___|\_,_\___/__/__/
  \*/

  integer
  AlpRider::u_guess_numEqns() const
  { return 2; }

  void
  AlpRider::u_guess_eval(
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
    UGUESS__[ iU_u1 ] = 0;
    UGUESS__[ iU_u2 ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 2, i_segment );
  }

  void
  AlpRider::u_guess_eval(
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
  AlpRider::u_check_if_admissible(
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
  AlpRider::post_numEqns() const
  { return 2; }

  void
  AlpRider::post_eval(
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
    real_type t2   = X__[0] * X__[0];
    real_type t4   = X__[1] * X__[1];
    real_type t6   = X__[2] * X__[2];
    real_type t8   = X__[3] * X__[3];
    result__[ 0   ] = t2 + t4 + t6 + t8;
    result__[ 1   ] = q(Q__[0]);
    Mechatronix::check_in_segment( result__, "post_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::integrated_post_numEqns() const
  { return 0; }

  void
  AlpRider::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: AlpRider_Methods1.cc
