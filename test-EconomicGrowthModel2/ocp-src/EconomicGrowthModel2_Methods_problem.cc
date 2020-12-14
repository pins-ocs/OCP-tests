/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods1.cc                               |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  EconomicGrowthModel2::continuationStep0( real_type s ) {
    int msg_level = 3;
    m_console->message(
      fmt::format( "\nContinuation step N.0 s = {}\n", s ),
      msg_level
    );
    real_type t3   = explog(ModelPars[6], ModelPars[7], s);
    uControl.update_epsilon(t3);
  }

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  EconomicGrowthModel2::Q( real_type x__XO, real_type y__XO ) const {
    return x__XO * y__XO;
  }

  real_type
  EconomicGrowthModel2::Q_D_1( real_type x__XO, real_type y__XO ) const {
    return y__XO;
  }

  real_type
  EconomicGrowthModel2::Q_D_1_1( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  EconomicGrowthModel2::Q_D_1_2( real_type x__XO, real_type y__XO ) const {
    return 1;
  }

  real_type
  EconomicGrowthModel2::Q_D_2( real_type x__XO, real_type y__XO ) const {
    return x__XO;
  }

  real_type
  EconomicGrowthModel2::Q_D_2_2( real_type x__XO, real_type y__XO ) const {
    return 0;
  }

  real_type
  EconomicGrowthModel2::explog( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = log(a__XO);
    real_type t4   = log(b__XO);
    return exp((1 - s__XO) * t1 + s__XO * t4);
  }

  real_type
  EconomicGrowthModel2::explog_D_1( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, s__XO);
    return -t4 * t2 * (-1 + s__XO);
  }

  real_type
  EconomicGrowthModel2::explog_D_1_1( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t3   = pow(a__XO, -s__XO - 1);
    real_type t5   = pow(b__XO, s__XO);
    return t5 * s__XO * t3 * (-1 + s__XO);
  }

  real_type
  EconomicGrowthModel2::explog_D_1_2( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(a__XO, -s__XO);
    real_type t4   = pow(b__XO, t1);
    return -s__XO * t4 * t2 * t1;
  }

  real_type
  EconomicGrowthModel2::explog_D_1_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = pow(b__XO, s__XO);
    real_type t2   = -1 + s__XO;
    real_type t3   = log(a__XO);
    real_type t6   = log(b__XO);
    real_type t10  = pow(a__XO, -s__XO);
    return t10 * (t3 * t2 - t6 * t2 - 1) * t1;
  }

  real_type
  EconomicGrowthModel2::explog_D_2( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = -1 + s__XO;
    real_type t2   = pow(b__XO, t1);
    real_type t5   = pow(a__XO, -t1);
    return t5 * t2 * s__XO;
  }

  real_type
  EconomicGrowthModel2::explog_D_2_2( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t2   = pow(b__XO, -2 + s__XO);
    real_type t4   = -1 + s__XO;
    real_type t6   = pow(a__XO, -t4);
    return t6 * t4 * t2 * s__XO;
  }

  real_type
  EconomicGrowthModel2::explog_D_2_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = 1 - s__XO;
    real_type t2   = pow(a__XO, t1);
    real_type t4   = pow(b__XO, -t1);
    real_type t6   = log(a__XO);
    real_type t8   = log(b__XO);
    return -(s__XO * t6 - s__XO * t8 - 1) * t4 * t2;
  }

  real_type
  EconomicGrowthModel2::explog_D_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t5   = pow(a__XO, 1 - s__XO);
    real_type t7   = pow(b__XO, s__XO);
    return -t7 * t5 * (t1 - t2);
  }

  real_type
  EconomicGrowthModel2::explog_D_3_3( real_type a__XO, real_type b__XO, real_type s__XO ) const {
    real_type t1   = log(a__XO);
    real_type t2   = log(b__XO);
    real_type t4   = pow(t1 - t2, 2);
    real_type t6   = pow(a__XO, 1 - s__XO);
    real_type t8   = pow(b__XO, s__XO);
    return t8 * t6 * t4;
  }


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  EconomicGrowthModel2::H_eval(
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
    real_type t1   = X__[4];
    real_type t2   = Tpositive(t1);
    real_type t8   = U__[0];
    real_type t12  = Q(X__[0], X__[1]);
    real_type t13  = t1 * t12;
    return t2 + t1 * X__[2] * L__[0] + t13 * t8 * L__[1] + t1 * X__[3] * L__[2] + t13 * (1 - t8) * L__[3];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  EconomicGrowthModel2::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return Tpositive(X__[4]);
  }

  real_type
  EconomicGrowthModel2::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = uControl(U__[0], 0, 1);
    return t3 * X__[4];
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  EconomicGrowthModel2::lagrange_target(
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
  EconomicGrowthModel2::mayer_target(
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
    return XR__[4];
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  EconomicGrowthModel2::q_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel2::q_eval(
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
  EconomicGrowthModel2::u_guess_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel2::u_guess_eval(
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
    UGUESS__[ iU_u ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 1, i_segment );
  }

  void
  EconomicGrowthModel2::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[5];
    real_type L__[5];
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
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  EconomicGrowthModel2::u_check_if_admissible(
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
    ok = ok && uControl.check_range(U__[0], 0, 1);
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
  EconomicGrowthModel2::post_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel2::post_eval(
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
    result__[ 0   ] = L__[3] - L__[1];
    Mechatronix::check_in_segment( result__, "post_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::integrated_post_numEqns() const
  { return 0; }

  void
  EconomicGrowthModel2::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: EconomicGrowthModel2_Methods1.cc
