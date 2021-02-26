/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods1.cc                                          |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_DD(__t1) VelBound.DD( __t1)
#define ALIAS_VelBound_D(__t1) VelBound.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  Crossroad::H_eval(
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
    real_type t1   = X__[3];
    real_type t2   = Tpositive(t1);
    real_type t3   = X__[2];
    real_type t4   = t3 * t3;
    real_type t6   = ModelPars[14] * ModelPars[14];
    real_type t9   = X__[1];
    real_type t10  = t9 * t9;
    real_type t11  = t10 * t10;
    real_type t13  = kappa(X__[0]);
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[13] * ModelPars[13];
    real_type t21  = AccBound(1 - 1.0 / t6 * t4 - 1.0 / t17 * t14 * t11);
    real_type t22  = VelBound(t9);
    real_type t24  = U__[0];
    real_type t25  = t24 * t24;
    real_type t41  = jerkControl(t24, ModelPars[16], ModelPars[15]);
    return t2 + t21 + t22 + t1 * (t25 * ModelPars[11] + ModelPars[12]) + t9 * t1 * L__[0] + t3 * t1 * L__[1] + t24 * t1 * L__[2] + t41;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  Crossroad::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = Tpositive(X__[3]);
    real_type t4   = X__[2] * X__[2];
    real_type t6   = ModelPars[14] * ModelPars[14];
    real_type t9   = X__[1];
    real_type t10  = t9 * t9;
    real_type t11  = t10 * t10;
    real_type t13  = kappa(X__[0]);
    real_type t14  = t13 * t13;
    real_type t17  = ModelPars[13] * ModelPars[13];
    real_type t21  = AccBound(1 - 1.0 / t6 * t4 - 1.0 / t17 * t14 * t11);
    real_type t22  = VelBound(t9);
    return t2 + t21 + t22;
  }

  real_type
  Crossroad::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    return jerkControl(U__[0], ModelPars[16], ModelPars[15]);
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  Crossroad::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = U__[0] * U__[0];
    return X__[3] * (t3 * ModelPars[11] + ModelPars[12]);
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  Crossroad::mayer_target(
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
  Crossroad::q_numEqns() const
  { return 1; }

  void
  Crossroad::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  Crossroad::segmentLink_numEqns() const
  { return 0; }

  void
  Crossroad::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  Crossroad::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  Crossroad::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  Crossroad::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  Crossroad::jump_numEqns() const
  { return 8; }

  void
  Crossroad::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    real_type t3   = ModelPars[0] / 2;
    result__[ 0   ] = XL__[0] - t3;
    result__[ 1   ] = XR__[1] - XL__[1];
    result__[ 2   ] = XR__[2] - XL__[2];
    result__[ 3   ] = LL__[3];
    result__[ 4   ] = XR__[0] - t3;
    result__[ 5   ] = LR__[1] - LL__[1];
    result__[ 6   ] = LR__[2] - LL__[2];
    result__[ 7   ] = LR__[3];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::DjumpDxlp_numRows() const
  { return 8; }

  integer
  Crossroad::DjumpDxlp_numCols() const
  { return 16; }

  integer
  Crossroad::DjumpDxlp_nnz() const
  { return 12; }

  void
  Crossroad::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 9   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 5   ; jIndex[8 ] = 13  ;
    iIndex[9 ] = 6   ; jIndex[9 ] = 6   ;
    iIndex[10] = 6   ; jIndex[10] = 14  ;
    iIndex[11] = 7   ; jIndex[11] = 15  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DjumpDxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = -1;
    result__[ 8   ] = 1;
    result__[ 9   ] = -1;
    result__[ 10  ] = 1;
    result__[ 11  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlp_sparse", 12, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  Crossroad::post_numEqns() const
  { return 3; }

  void
  Crossroad::post_eval(
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
    result__[ 0   ] = kappa(X__[0]);
    result__[ 1   ] = X__[2] / ModelPars[14];
    real_type t6   = X__[1] * X__[1];
    result__[ 2   ] = 1.0 / ModelPars[13] * result__[0] * t6;
    Mechatronix::check_in_segment( result__, "post_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Crossroad::integrated_post_numEqns() const
  { return 0; }

  void
  Crossroad::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
  }

}

// EOF: Crossroad_Methods1.cc
