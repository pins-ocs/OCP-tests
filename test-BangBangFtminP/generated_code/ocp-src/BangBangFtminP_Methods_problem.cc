/*-----------------------------------------------------------------------*\
 |  file: BangBangFtminP_Methods_problem.cc                              |
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


#include "BangBangFtminP.hh"
#include "BangBangFtminP_Pars.hh"

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
#define ALIAS_Fcontrol_D_3(__t1, __t2, __t3) Fcontrol.D_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_2(__t1, __t2, __t3) Fcontrol.D_2( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1(__t1, __t2, __t3) Fcontrol.D_1( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_3_3(__t1, __t2, __t3) Fcontrol.D_3_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_2_3(__t1, __t2, __t3) Fcontrol.D_2_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_2_2(__t1, __t2, __t3) Fcontrol.D_2_2( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1_3(__t1, __t2, __t3) Fcontrol.D_1_3( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1_2(__t1, __t2, __t3) Fcontrol.D_1_2( __t1, __t2, __t3)
#define ALIAS_Fcontrol_D_1_1(__t1, __t2, __t3) Fcontrol.D_1_1( __t1, __t2, __t3)


namespace BangBangFtminPDefine {

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

#if 0
  real_type
  BangBangFtminP::H_eval(
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
    real_type t6   = U__[iU_F];
    real_type t8   = Fcontrol(t6, -1, 1);
    real_type result__ = (t6 * L__[iL_lambda2__xo] + L__[iL_lambda1__xo] * X__[iX_v] + t8) * P__[iP_T];
    return result__;
  }
#else
  real_type
  BangBangFtminP::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t6   = U__[iU_F];
    real_type t8   = Fcontrol(t6, -1, 1);
    real_type result__ = (t6 * L__[iL_lambda2__xo] + L__[iL_lambda1__xo] * X__[iX_v] + t8) * P__[iP_T];
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
  BangBangFtminP::penalties_eval(
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
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BangBangFtminP::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = Fcontrol(U__[iU_F], -1, 1);
    real_type result__ = t3 * P__[iP_T];
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
  BangBangFtminP::lagrange_target(
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
  BangBangFtminP::mayer_target(
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
    real_type result__ = P__[iP_T];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtminP::DmayerDx_numEqns() const
  { return 4; }

  void
  BangBangFtminP::DmayerDx_eval(
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
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDx_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtminP::DmayerDp_numEqns() const
  { return 1; }

  void
  BangBangFtminP::DmayerDp_eval(
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
    result__[ 0   ] = 1;
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
  BangBangFtminP::DJDx_numEqns() const
  { return 2; }

  void
  BangBangFtminP::DJDx_eval(
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
  BangBangFtminP::DJDp_numEqns() const
  { return 1; }

  void
  BangBangFtminP::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = Fcontrol(U__[iU_F], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtminP::DJDu_numEqns() const
  { return 1; }

  void
  BangBangFtminP::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ALIAS_Fcontrol_D_1(U__[iU_F], -1, 1);
    result__[ 0   ] = t3 * P__[iP_T];
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
  BangBangFtminP::q_numEqns() const
  { return 1; }

  void
  BangBangFtminP::q_eval(
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
  BangBangFtminP::segmentLink_numEqns() const
  { return 0; }

  void
  BangBangFtminP::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_ptr             segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtminP::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  BangBangFtminP::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  BangBangFtminP::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  BangBangFtminP::DsegmentLinkDxp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtminP::DsegmentLinkDxp_sparse(
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
  BangBangFtminP::jump_numEqns() const
  { return 4; }

  void
  BangBangFtminP::jump_eval(
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
  BangBangFtminP::DjumpDxlxlp_numRows() const
  { return 4; }

  integer
  BangBangFtminP::DjumpDxlxlp_numCols() const
  { return 9; }

  integer
  BangBangFtminP::DjumpDxlxlp_nnz() const
  { return 8; }

  void
  BangBangFtminP::DjumpDxlxlp_pattern(
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
  BangBangFtminP::DjumpDxlxlp_sparse(
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
  BangBangFtminP::post_numEqns() const
  { return 0; }

  void
  BangBangFtminP::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtminP::integrated_post_numEqns() const
  { return 0; }

  void
  BangBangFtminP::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
   // EMPTY!
  }

}

// EOF: BangBangFtminP_Methods_problem.cc
