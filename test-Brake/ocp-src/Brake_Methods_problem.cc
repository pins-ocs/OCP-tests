/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods1.cc                                              |
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


#include "Brake.hh"
#include "Brake_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_aControl_D_3(__t1, __t2, __t3) aControl.D_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_2(__t1, __t2, __t3) aControl.D_2( __t1, __t2, __t3)
#define ALIAS_aControl_D_1(__t1, __t2, __t3) aControl.D_1( __t1, __t2, __t3)
#define ALIAS_aControl_D_3_3(__t1, __t2, __t3) aControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_2_3(__t1, __t2, __t3) aControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_2_2(__t1, __t2, __t3) aControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_aControl_D_1_3(__t1, __t2, __t3) aControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_1_2(__t1, __t2, __t3) aControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_aControl_D_1_1(__t1, __t2, __t3) aControl.D_1_1( __t1, __t2, __t3)


namespace BrakeDefine {


  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  Brake::H_eval(
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
    real_type t2   = Tpositive(t1);
    return X__[1] * t1 * L__[0] + U__[0] * t1 * L__[1] + t2;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  Brake::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return Tpositive(P__[0]);
  }

  real_type
  Brake::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return aControl(U__[0], -1, 1);
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  Brake::lagrange_target(
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
  Brake::mayer_target(
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
    return XR__[0];
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  Brake::q_numEqns() const
  { return 1; }

  void
  Brake::q_eval(
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
  Brake::u_guess_numEqns() const
  { return 1; }

  void
  Brake::u_guess_eval(
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
    UGUESS__[ iU_a ] = 0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(UGUESS__.pointer(),"u_guess_eval",1);
    #endif
  }

  void
  Brake::u_guess_eval(
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
  Brake::u_check_if_admissible(
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
    ok = ok && aControl.check_range(U__[0], -1, 1);
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
  Brake::post_numEqns() const
  { return 0; }

  void
  Brake::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::integrated_post_numEqns() const
  { return 0; }

  void
  Brake::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: Brake_Methods1.cc
