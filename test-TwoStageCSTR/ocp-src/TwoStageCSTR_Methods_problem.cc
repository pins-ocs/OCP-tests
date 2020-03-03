/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods1.cc                                       |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoStageCSTRDefine {

  /*\
   |  _   _               ___             _   _
   | | | | |___ ___ _ _  | __|  _ _ _  __| |_(_)___ _ _  ___
   | | |_| (_-</ -_) '_| | _| || | ' \/ _|  _| / _ \ ' \(_-<
   |  \___//__/\___|_|   |_| \_,_|_||_\__|\__|_\___/_||_/__/
  \*/
  // user defined functions which has a body defined in MAPLE
  real_type
  TwoStageCSTR::R1( real_type x1__XO, real_type x2__XO ) const {
    real_type t6   = exp(25 * x2__XO / (x2__XO + 2));
    return t6 * (x1__XO + 0.5e0);
  }

  real_type
  TwoStageCSTR::R1_D_1( real_type x1__XO, real_type x2__XO ) const {
    return exp(25 * x2__XO / (x2__XO + 2));
  }

  real_type
  TwoStageCSTR::R1_D_1_1( real_type x1__XO, real_type x2__XO ) const {
    return 0;
  }

  real_type
  TwoStageCSTR::R1_D_1_2( real_type x1__XO, real_type x2__XO ) const {
    real_type t1   = x2__XO + 2;
    real_type t2   = t1 * t1;
    real_type t7   = exp(25 / t1 * x2__XO);
    return 50 * t7 / t2;
  }

  real_type
  TwoStageCSTR::R1_D_2( real_type x1__XO, real_type x2__XO ) const {
    real_type t2   = x2__XO + 2;
    real_type t3   = t2 * t2;
    real_type t9   = exp(25 / t2 * x2__XO);
    return 50 * t9 / t3 * (x1__XO + 0.5e0);
  }

  real_type
  TwoStageCSTR::R1_D_2_2( real_type x1__XO, real_type x2__XO ) const {
    real_type t2   = x2__XO + 2;
    real_type t6   = exp(25 / t2 * x2__XO);
    real_type t9   = t2 * t2;
    real_type t10  = t9 * t9;
    return -100 / t10 * (x2__XO - 23) * t6 * (x1__XO + 0.5e0);
  }

  real_type
  TwoStageCSTR::R2( real_type x3__XO, real_type x4__XO ) const {
    real_type t6   = exp(25 * x4__XO / (x4__XO + 2));
    return t6 * (x3__XO + 0.25e0);
  }

  real_type
  TwoStageCSTR::R2_D_1( real_type x3__XO, real_type x4__XO ) const {
    return exp(25 * x4__XO / (x4__XO + 2));
  }

  real_type
  TwoStageCSTR::R2_D_1_1( real_type x3__XO, real_type x4__XO ) const {
    return 0;
  }

  real_type
  TwoStageCSTR::R2_D_1_2( real_type x3__XO, real_type x4__XO ) const {
    real_type t1   = x4__XO + 2;
    real_type t2   = t1 * t1;
    real_type t7   = exp(25 / t1 * x4__XO);
    return 50 * t7 / t2;
  }

  real_type
  TwoStageCSTR::R2_D_2( real_type x3__XO, real_type x4__XO ) const {
    real_type t2   = x4__XO + 2;
    real_type t3   = t2 * t2;
    real_type t9   = exp(25 / t2 * x4__XO);
    return 50 * t9 / t3 * (x3__XO + 0.25e0);
  }

  real_type
  TwoStageCSTR::R2_D_2_2( real_type x3__XO, real_type x4__XO ) const {
    real_type t2   = x4__XO + 2;
    real_type t6   = exp(25 / t2 * x4__XO);
    real_type t9   = t2 * t2;
    real_type t10  = t9 * t9;
    return -100 / t10 * (x4__XO - 23) * t6 * (x3__XO + 0.25e0);
  }


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  TwoStageCSTR::H_eval(
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
    real_type t10  = U__[0];
    real_type t11  = t10 * t10;
    real_type t12  = U__[1];
    real_type t13  = t12 * t12;
    real_type t17  = R1(t1, t3);
    real_type t18  = 0.5e0 - t1 - t17;
    real_type t24  = t17 - (2 + t10) * (t3 + 0.25e0);
    real_type t27  = ModelPars[1];
    real_type t29  = R2(t5, t7);
    return t2 + t4 + t6 + t8 + (t11 + t13) * ModelPars[0] + t18 * L__[0] + t24 * L__[1] + (t1 - t5 - t18 * t27 - t29 + 0.25e0) * L__[2] + (t3 - 2 * t7 - (t7 + 0.25e0) * t12 - t24 * t27 + t29 - 0.25e0) * L__[3];
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  TwoStageCSTR::penalties_eval(
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
  TwoStageCSTR::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = u1Control(U__[0], -0.5e0, 0.5e0);
    real_type t4   = u2Control(U__[1], -0.5e0, 0.5e0);
    return t2 + t4;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  TwoStageCSTR::lagrange_target(
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
    real_type t11  = U__[0] * U__[0];
    real_type t13  = U__[1] * U__[1];
    return t2 + t4 + t6 + t8 + (t11 + t13) * ModelPars[0];
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  TwoStageCSTR::mayer_target(
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
  TwoStageCSTR::q_numEqns() const
  { return 1; }

  void
  TwoStageCSTR::q_eval(
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
  TwoStageCSTR::u_guess_numEqns() const
  { return 2; }

  void
  TwoStageCSTR::u_guess_eval(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(UGUESS__.pointer(),"u_guess_eval",2);
    #endif
  }

  void
  TwoStageCSTR::u_guess_eval(
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
  TwoStageCSTR::u_check_if_admissible(
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
    ok = ok && u1Control.check_range(U__[0], -0.5e0, 0.5e0);
    ok = ok && u2Control.check_range(U__[1], -0.5e0, 0.5e0);
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
  TwoStageCSTR::post_numEqns() const
  { return 0; }

  void
  TwoStageCSTR::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::integrated_post_numEqns() const
  { return 0; }

  void
  TwoStageCSTR::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: TwoStageCSTR_Methods1.cc
