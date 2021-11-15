/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods_problem.cc                                       |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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


#include "Brake.hh"
#include "Brake_Pars.hh"

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

#if 0
  real_type
  Brake::H_eval(
    integer              i_segment,
    CellType const &     CELL__,
    P_const_pointer_type P__
  ) const {
    integer     i_cell = CELL__.i_cell;
    real_const_ptr Q__ = CELL__.qM;
    real_const_ptr X__ = CELL__.xM;
    real_const_ptr L__ = CELL__.lambdaM;
    real_const_ptr U__ = CELL__.uM;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = Tpositive(t1);
    real_type t9   = U__[iU_a];
    real_type t11  = aControl(t9, -1, 1);
    real_type result__ = t9 * t1 * L__[iL_lambda2__xo] + X__[iX_v] * t1 * L__[iL_lambda1__xo] + t11 + t2;
    return result__;
  }
#else
  real_type
  Brake::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = Tpositive(t1);
    real_type t9   = U__[iU_a];
    real_type t11  = aControl(t9, -1, 1);
    real_type result__ = t9 * t1 * L__[iL_lambda2__xo] + X__[iX_v] * t1 * L__[iL_lambda1__xo] + t11 + t2;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }
#endif

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
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = Tpositive(P__[iP_T]);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Brake::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = aControl(U__[iU_a], -1, 1);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
    }
    return result__;
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
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
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
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type result__ = XR__[iX_x];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::DmayerDx_numEqns() const
  { return 4; }

  void
  Brake::DmayerDx_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 1;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDx_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::DmayerDp_numEqns() const
  { return 1; }

  void
  Brake::DmayerDp_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDp_eval", 1, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer
  Brake::DJDx_numEqns() const
  { return 2; }

  void
  Brake::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::DJDp_numEqns() const
  { return 1; }

  void
  Brake::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_Tpositive_D(P__[iP_T]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::DJDu_numEqns() const
  { return 1; }

  void
  Brake::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_aControl_D_1(U__[iU_a], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDu_eval", 1, i_segment );
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
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
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
  Brake::segmentLink_numEqns() const
  { return 0; }

  void
  Brake::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_ptr             segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  Brake::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  Brake::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  Brake::DsegmentLinkDxp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_ptr             DsegmentLinkDxp
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
  Brake::jump_numEqns() const
  { return 4; }

  void
  Brake::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    real_const_ptr    LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    real_const_ptr    LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XR__[iX_x] - XL__[iX_x];
    result__[ 1   ] = XR__[iX_v] - XL__[iX_v];
    result__[ 2   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 3   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::DjumpDxlxlp_numRows() const
  { return 4; }

  integer
  Brake::DjumpDxlxlp_numCols() const
  { return 9; }

  integer
  Brake::DjumpDxlxlp_nnz() const
  { return 8; }

  void
  Brake::DjumpDxlxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 7   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr    QL__  = LEFT__.q;
    real_const_ptr    XL__  = LEFT__.x;
    real_const_ptr    LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr    QR__  = RIGHT__.q;
    real_const_ptr    XR__  = RIGHT__.x;
    real_const_ptr    LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 8, i_segment_left, i_segment_right );
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
    real_ptr             result__
  ) const {
    // EMPTY!
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
    real_ptr             result__
  ) const {
   // EMPTY!
  }

}

// EOF: Brake_Methods_problem.cc
