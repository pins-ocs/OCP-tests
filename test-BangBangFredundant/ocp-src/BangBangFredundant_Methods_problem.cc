/*-----------------------------------------------------------------------*\
 |  file: BangBangFredundant_Methods1.cc                                 |
 |                                                                       |
 |  version: 1.0   date 19/1/2021                                        |
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


#include "BangBangFredundant.hh"
#include "BangBangFredundant_Pars.hh"

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
#define ALIAS_Flim_DD(__t1) Flim.DD( __t1)
#define ALIAS_Flim_D(__t1) Flim.D( __t1)
#define ALIAS_aF2Control_D_3(__t1, __t2, __t3) aF2Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2(__t1, __t2, __t3) aF2Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1(__t1, __t2, __t3) aF2Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_3_3(__t1, __t2, __t3) aF2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_3(__t1, __t2, __t3) aF2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_2(__t1, __t2, __t3) aF2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_3(__t1, __t2, __t3) aF2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_2(__t1, __t2, __t3) aF2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_1(__t1, __t2, __t3) aF2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3(__t1, __t2, __t3) aF1Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2(__t1, __t2, __t3) aF1Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1(__t1, __t2, __t3) aF1Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3_3(__t1, __t2, __t3) aF1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_3(__t1, __t2, __t3) aF1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_2(__t1, __t2, __t3) aF1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_3(__t1, __t2, __t3) aF1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_2(__t1, __t2, __t3) aF1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_1(__t1, __t2, __t3) aF1Control.D_1_1( __t1, __t2, __t3)


namespace BangBangFredundantDefine {


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  BangBangFredundant::H_eval(
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
    real_type t4   = X__[2] + X__[3];
    real_type t5   = Flim(t4);
    real_type t19  = U__[0];
    real_type t22  = U__[1];
    real_type t24  = ModelPars[0];
    real_type t25  = aF1Control(t19, -t24, t24);
    real_type t26  = aF2Control(t22, -t24, t24);
    return t19 * L__[4] + t22 * L__[5] + t4 * L__[1] + t5 * ModelPars[1] + L__[0] * X__[1] + L__[2] * X__[4] + L__[3] * X__[5] + t25 + t26;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  BangBangFredundant::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t5   = Flim(X__[2] + X__[3]);
    return t5 * ModelPars[1];
  }

  real_type
  BangBangFredundant::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[0];
    real_type t3   = aF1Control(U__[0], -t2, t2);
    real_type t5   = aF2Control(U__[1], -t2, t2);
    return t3 + t5;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  BangBangFredundant::lagrange_target(
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
  BangBangFredundant::mayer_target(
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
    real_type t5   = Flim(XL__[2] + XL__[3]);
    real_type t9   = Flim(XR__[2] + XR__[3]);
    return -XR__[0] + t5 + t9;
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  BangBangFredundant::q_numEqns() const
  { return 1; }

  void
  BangBangFredundant::q_eval(
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
  BangBangFredundant::u_guess_numEqns() const
  { return 2; }

  void
  BangBangFredundant::u_guess_eval(
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
    UGUESS__[ iU_aF1 ] = 0;
    UGUESS__[ iU_aF2 ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( UGUESS__.pointer(), "u_guess_eval", 2, i_segment );
  }

  void
  BangBangFredundant::u_guess_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       UGUESS__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
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
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
    this->u_guess_eval( NODE__, P__, UGUESS__ );
  }

  /*\
   |    ___ _           _
   |   / __| |_  ___ __| |__
   |  | (__| ' \/ -_) _| / /
   |   \___|_||_\___\__|_\_\
  \*/

  bool
  BangBangFredundant::u_check_if_admissible(
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
    real_type t2   = ModelPars[0];
    ok = ok && aF1Control.check_range(U__[0], -t2, t2);
    ok = ok && aF2Control.check_range(U__[1], -t2, t2);
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
  BangBangFredundant::post_numEqns() const
  { return 4; }

  void
  BangBangFredundant::post_eval(
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
    real_type t2   = ModelPars[0];
    result__[ 0   ] = aF1Control(U__[0], -t2, t2);
    result__[ 1   ] = aF2Control(U__[1], -t2, t2);
    real_type t6   = X__[2] + X__[3];
    result__[ 2   ] = Flim(t6);
    result__[ 3   ] = t6;
    Mechatronix::check_in_segment( result__, "post_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFredundant::integrated_post_numEqns() const
  { return 0; }

  void
  BangBangFredundant::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: BangBangFredundant_Methods1.cc
