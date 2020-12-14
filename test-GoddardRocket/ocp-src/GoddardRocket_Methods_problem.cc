/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods1.cc                                      |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  GoddardRocket::continuationStep0( real_type s ) {
    int msg_level = 3;
    m_console->message(
      fmt::format( "\nContinuation step N.0 s = {}\n", s ),
      msg_level
    );
    real_type t3   = explog(s, ModelPars[3], ModelPars[14]);
    TControl.update_epsilon(t3);
    real_type t6   = explog(s, ModelPars[10], ModelPars[16]);
    TControl.update_tolerance(t6);
    real_type t9   = explog(s, ModelPars[4], ModelPars[13]);
    TSPositive.update_epsilon(t9);
    real_type t12  = explog(s, ModelPars[11], ModelPars[15]);
    TSPositive.update_tolerance(t12);
  }

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  GoddardRocket::DD( real_type h__XO, real_type v__XO ) const {
    real_type t2   = v__XO * v__XO;
    real_type t10  = exp(ModelPars[7] * (1 - h__XO / ModelPars[6]));
    return t10 * t2 * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_1( real_type h__XO, real_type v__XO ) const {
    real_type t2   = v__XO * v__XO;
    real_type t4   = ModelPars[7];
    real_type t5   = ModelPars[6];
    real_type t8   = 1.0 / t5;
    real_type t10  = exp(t8 * (t5 - h__XO) * t4);
    return -t8 * t10 * t4 * t2 * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_1_1( real_type h__XO, real_type v__XO ) const {
    real_type t2   = v__XO * v__XO;
    real_type t4   = ModelPars[7];
    real_type t5   = t4 * t4;
    real_type t6   = ModelPars[6];
    real_type t7   = t6 * t6;
    real_type t14  = exp(1.0 / t6 * (t6 - h__XO) * t4);
    return t14 / t7 * t5 * t2 * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_1_2( real_type h__XO, real_type v__XO ) const {
    real_type t3   = ModelPars[7];
    real_type t4   = ModelPars[6];
    real_type t7   = 1.0 / t4;
    real_type t9   = exp(t7 * (t4 - h__XO) * t3);
    return -2 * t7 * t9 * t3 * ModelPars[0] * v__XO;
  }

  real_type
  GoddardRocket::DD_D_2( real_type h__XO, real_type v__XO ) const {
    real_type t4   = ModelPars[6];
    real_type t9   = exp(1.0 / t4 * (t4 - h__XO) * ModelPars[7]);
    return 2 * t9 * v__XO * ModelPars[0];
  }

  real_type
  GoddardRocket::DD_D_2_2( real_type h__XO, real_type v__XO ) const {
    real_type t3   = ModelPars[6];
    real_type t8   = exp(1.0 / t3 * (t3 - h__XO) * ModelPars[7]);
    return 2 * t8 * ModelPars[0];
  }

  real_type
  GoddardRocket::gg( real_type h__XO ) const {
    real_type t3   = ModelPars[6] * ModelPars[6];
    real_type t5   = h__XO * h__XO;
    return 1.0 / t5 * t3 * ModelPars[5];
  }

  real_type
  GoddardRocket::gg_D( real_type h__XO ) const {
    real_type t3   = ModelPars[6] * ModelPars[6];
    real_type t5   = h__XO * h__XO;
    return -2 / t5 / h__XO * t3 * ModelPars[5];
  }

  real_type
  GoddardRocket::gg_DD( real_type h__XO ) const {
    real_type t3   = ModelPars[6] * ModelPars[6];
    real_type t5   = h__XO * h__XO;
    real_type t6   = t5 * t5;
    return 6 / t6 * t3 * ModelPars[5];
  }

  real_type
  GoddardRocket::explog( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = log(a__XO);
    real_type t4   = log(b__XO);
    return exp(t2 * (1 - s__XO) + t4 * s__XO);
  }

  real_type
  GoddardRocket::explog_D_1( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t5   = pow(a__XO, 1 - s__XO);
    real_type t7   = pow(b__XO, s__XO);
    return -t7 * t5 * (t1 - t2);
  }

  real_type
  GoddardRocket::explog_D_1_1( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t4   = pow(t1 - t2, 2);
    real_type t6   = pow(a__XO, 1 - s__XO);
    real_type t8   = pow(b__XO, s__XO);
    return t8 * t6 * t4;
  }

  real_type
  GoddardRocket::explog_D_1_2( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = pow(b__XO, s__XO);
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = -1 + s__XO;
    real_type t5   = log(a__XO);
    real_type t8   = log(b__XO);
    return (t5 * t4 - t8 * t4 - 1) * t2 * t1;
  }

  real_type
  GoddardRocket::explog_D_1_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(b__XO, t1);
    real_type t4   = pow(a__XO, -t1);
    real_type t6   = log(a__XO);
    real_type t8   = log(b__XO);
    return -(s__XO * t6 - t8 * s__XO - 1) * t4 * t2;
  }

  real_type
  GoddardRocket::explog_D_2( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, s__XO);
    return -t4 * t2 * (-1 + s__XO);
  }

  real_type
  GoddardRocket::explog_D_2_2( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t3   = pow(a__XO, -s__XO - 1);
    real_type t5   = pow(b__XO, s__XO);
    return t5 * s__XO * t3 * (-1 + s__XO);
  }

  real_type
  GoddardRocket::explog_D_2_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, t1);
    return -s__XO * t4 * t2 * t1;
  }

  real_type
  GoddardRocket::explog_D_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(b__XO, t1);
    real_type t5   = pow(a__XO, -t1);
    return t5 * t2 * s__XO;
  }

  real_type
  GoddardRocket::explog_D_3_3( real_type s__XO, real_type a__XO, real_type b__XO ) const {
    real_type t2   = pow(b__XO, -2 + s__XO);
    real_type t4   = -1 + s__XO;
    real_type t6   = pow(a__XO, -t4);
    return t6 * t4 * t2 * s__XO;
  }


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  GoddardRocket::H_eval(
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
    real_type t1   = X__[2];
    real_type t2   = massPositive(t1);
    real_type t3   = P__[0];
    real_type t4   = TSPositive(t3);
    real_type t5   = X__[1];
    real_type t6   = vPositive(t5);
    real_type t12  = U__[0];
    real_type t13  = X__[0];
    real_type t14  = DD(t13, t5);
    real_type t18  = gg(t13);
    return t2 + t4 + t6 + t5 * t3 * L__[0] + (1.0 / t1 * (t12 - t14) - t18) * t3 * L__[1] - 1.0 / ModelPars[2] * t12 * t3 * L__[2];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  GoddardRocket::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = massPositive(X__[2]);
    real_type t4   = TSPositive(P__[0]);
    real_type t6   = vPositive(X__[1]);
    return t2 + t4 + t6;
  }

  real_type
  GoddardRocket::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return TControl(U__[0], 0, ModelPars[1]);
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  GoddardRocket::lagrange_target(
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
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  GoddardRocket::mayer_target(
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
  GoddardRocket::q_numEqns() const
  { return 1; }

  void
  GoddardRocket::q_eval(
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
  GoddardRocket::u_guess_numEqns() const
  { return 1; }

  void
  GoddardRocket::u_guess_eval(
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
    UGUESS__[ iU_T ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 1, i_segment );
  }

  void
  GoddardRocket::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[3];
    real_type L__[3];
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
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  GoddardRocket::u_check_if_admissible(
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
    ok = ok && TControl.check_range(U__[0], 0, ModelPars[1]);
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
  GoddardRocket::post_numEqns() const
  { return 2; }

  void
  GoddardRocket::post_eval(
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
    real_type t2   = P__[0];
    result__[ 0   ] = t2 * Q__[0];
    result__[ 1   ] = X__[1] * t2;
    Mechatronix::check_in_segment( result__, "post_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::integrated_post_numEqns() const
  { return 0; }

  void
  GoddardRocket::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: GoddardRocket_Methods1.cc
