/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_problem.cc                               |
 |                                                                       |
 |  version: 1.0   date 13/3/2022                                        |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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
    real_type t3   = explog(s, ModelPars[iM_epsi_T], ModelPars[iM_epsi_Tmin]);
    TControl.update_epsilon(t3);
    real_type t6   = explog(s, ModelPars[iM_tol_T], ModelPars[iM_tol_Tmin]);
    TControl.update_tolerance(t6);
    real_type t9   = explog(s, ModelPars[iM_epsi_TS], ModelPars[iM_epsi_TSmin]);
    TSPositive.update_epsilon(t9);
    real_type t12  = explog(s, ModelPars[iM_tol_TS], ModelPars[iM_tol_TSmin]);
    TSPositive.update_tolerance(t12);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

#if 0
  real_type
  GoddardRocket::H_eval(
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
    real_type t1   = X__[iX_m];
    real_type t2   = massPositive(t1);
    real_type t3   = P__[iP_TimeSize];
    real_type t4   = TSPositive(t3);
    real_type t5   = X__[iX_v];
    real_type t6   = vPositive(t5);
    real_type t12  = X__[iX_h];
    real_type t13  = gg(t12);
    real_type t15  = U__[iU_T];
    real_type t16  = DD(t12, t5);
    real_type t28  = TControl(t15, 0, ModelPars[iM_Tmax]);
    real_type result__ = t2 + t4 + t6 + t5 * t3 * L__[iL_lambda1__xo] + 1.0 / t1 * (-t1 * t13 + t15 - t16) * t3 * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t15 * t3 * L__[iL_lambda3__xo] + t28;
    return result__;
  }
#else
  real_type
  GoddardRocket::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_m];
    real_type t2   = massPositive(t1);
    real_type t3   = P__[iP_TimeSize];
    real_type t4   = TSPositive(t3);
    real_type t5   = X__[iX_v];
    real_type t6   = vPositive(t5);
    real_type t12  = X__[iX_h];
    real_type t13  = gg(t12);
    real_type t15  = U__[iU_T];
    real_type t16  = DD(t12, t5);
    real_type t28  = TControl(t15, 0, ModelPars[iM_Tmax]);
    real_type result__ = t2 + t4 + t6 + t5 * t3 * L__[iL_lambda1__xo] + 1.0 / t1 * (-t1 * t13 + t15 - t16) * t3 * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t15 * t3 * L__[iL_lambda3__xo] + t28;
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
  GoddardRocket::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = massPositive(X__[iX_m]);
    real_type t4   = TSPositive(P__[iP_TimeSize]);
    real_type t6   = vPositive(X__[iX_v]);
    real_type result__ = t2 + t4 + t6;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  GoddardRocket::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = TControl(U__[iU_T], 0, ModelPars[iM_Tmax]);
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
  GoddardRocket::lagrange_target(
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
  GoddardRocket::mayer_target(
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
    real_type result__ = -XR__[iX_h];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DmayerDx_numEqns() const
  { return 6; }

  void
  GoddardRocket::DmayerDx_eval(
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
    result__[ 3   ] = -1;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDx_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DmayerDp_numEqns() const
  { return 1; }

  void
  GoddardRocket::DmayerDp_eval(
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
  GoddardRocket::DJDx_numEqns() const
  { return 3; }

  void
  GoddardRocket::DJDx_eval(
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
    result__[ 1   ] = ALIAS_vPositive_D(X__[iX_v]);
    result__[ 2   ] = ALIAS_massPositive_D(X__[iX_m]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DJDp_numEqns() const
  { return 1; }

  void
  GoddardRocket::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_TSPositive_D(P__[iP_TimeSize]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DJDu_numEqns() const
  { return 1; }

  void
  GoddardRocket::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_TControl_D_1(U__[iU_T], 0, ModelPars[iM_Tmax]);
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
  GoddardRocket::q_numEqns() const
  { return 1; }

  void
  GoddardRocket::q_eval(
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
  GoddardRocket::segmentLink_numEqns() const
  { return 0; }

  void
  GoddardRocket::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_ptr             segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  GoddardRocket::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  GoddardRocket::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  GoddardRocket::DsegmentLinkDxp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DsegmentLinkDxp_sparse(
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
  GoddardRocket::jump_numEqns() const
  { return 6; }

  void
  GoddardRocket::jump_eval(
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
    result__[ 0   ] = XR__[iX_h] - XL__[iX_h];
    result__[ 1   ] = XR__[iX_v] - XL__[iX_v];
    result__[ 2   ] = XR__[iX_m] - XL__[iX_m];
    result__[ 3   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 4   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 5   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DjumpDxlxlp_numRows() const
  { return 6; }

  integer
  GoddardRocket::DjumpDxlxlp_numCols() const
  { return 13; }

  integer
  GoddardRocket::DjumpDxlxlp_nnz() const
  { return 12; }

  void
  GoddardRocket::DjumpDxlxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 10  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 11  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DjumpDxlxlp_sparse(
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
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 12, i_segment_left, i_segment_right );
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_TimeSize];
    result__[ 0   ] = t2 * Q__[iQ_zeta];
    result__[ 1   ] = X__[iX_v] * t2;
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
    real_ptr             result__
  ) const {
   // EMPTY!
  }

}

// EOF: GoddardRocket_Methods_problem.cc
