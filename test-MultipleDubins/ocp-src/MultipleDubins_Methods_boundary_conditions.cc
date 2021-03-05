/*-----------------------------------------------------------------------*\
 |  file: MultipleDubins_Methods.cc                                      |
 |                                                                       |
 |  version: 1.0   date 5/3/2021                                         |
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


#include "MultipleDubins.hh"
#include "MultipleDubins_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_diff2pi_DD(__t1) diff2pi.DD( __t1)
#define ALIAS_diff2pi_D(__t1) diff2pi.D( __t1)


namespace MultipleDubinsDefine {

  /*\
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer
  MultipleDubins::boundaryConditions_numEqns() const
  { return 12; }

  void
  MultipleDubins::boundaryConditions_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = XL__[iX_x1] - ModelPars[iM_x_i];
    result__[ 1   ] = XL__[iX_y1] - ModelPars[iM_y_i];
    result__[ 2   ] = XL__[iX_theta1] - ModelPars[iM_theta_i];
    result__[ 3   ] = XR__[iX_x3] - ModelPars[iM_x_f];
    result__[ 4   ] = XR__[iX_y3] - ModelPars[iM_y_f];
    result__[ 5   ] = diff2pi(XR__[iX_theta3] - ModelPars[iM_theta_f]);
    result__[ 6   ] = XR__[iX_x1] - XL__[iX_x2];
    result__[ 7   ] = XR__[iX_y1] - XL__[iX_y2];
    result__[ 8   ] = XR__[iX_theta1] - XL__[iX_theta2];
    result__[ 9   ] = XR__[iX_x2] - XL__[iX_x3];
    result__[ 10  ] = XR__[iX_y2] - XL__[iX_y3];
    result__[ 11  ] = XR__[iX_theta2] - XL__[iX_theta3];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "boundaryConditions_eval", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DboundaryConditionsDx_numRows() const
  { return 12; }

  integer
  MultipleDubins::DboundaryConditionsDx_numCols() const
  { return 18; }

  integer
  MultipleDubins::DboundaryConditionsDx_nnz() const
  { return 18; }

  void
  MultipleDubins::DboundaryConditionsDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 15  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 16  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 17  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 6   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 7   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 7   ; jIndex[9 ] = 10  ;
    iIndex[10] = 8   ; jIndex[10] = 5   ;
    iIndex[11] = 8   ; jIndex[11] = 11  ;
    iIndex[12] = 9   ; jIndex[12] = 6   ;
    iIndex[13] = 9   ; jIndex[13] = 12  ;
    iIndex[14] = 10  ; jIndex[14] = 7   ;
    iIndex[15] = 10  ; jIndex[15] = 13  ;
    iIndex[16] = 11  ; jIndex[16] = 8   ;
    iIndex[17] = 11  ; jIndex[17] = 14  ;
  }

  void
  MultipleDubins::DboundaryConditionsDx_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = ALIAS_diff2pi_D(XR__[iX_theta3] - ModelPars[iM_theta_f]);
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DboundaryConditionsDxp_sparse", 18, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DboundaryConditionsDp_numRows() const
  { return 12; }

  integer
  MultipleDubins::DboundaryConditionsDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DboundaryConditionsDp_nnz() const
  { return 0; }

  void
  MultipleDubins::DboundaryConditionsDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  MultipleDubins::DboundaryConditionsDp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY

  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::adjointBC_numEqns() const
  { return 24; }

  void
  MultipleDubins::adjointBC_eval(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
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
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda3__xo];
    real_type t7   = OMEGA__[6];
    result__[ 3   ] = -t7 + LL__[iL_lambda4__xo];
    real_type t9   = OMEGA__[7];
    result__[ 4   ] = -t9 + LL__[iL_lambda5__xo];
    real_type t11  = OMEGA__[8];
    result__[ 5   ] = -t11 + LL__[iL_lambda6__xo];
    real_type t13  = OMEGA__[9];
    result__[ 6   ] = -t13 + LL__[iL_lambda7__xo];
    real_type t15  = OMEGA__[10];
    result__[ 7   ] = -t15 + LL__[iL_lambda8__xo];
    real_type t17  = OMEGA__[11];
    result__[ 8   ] = -t17 + LL__[iL_lambda9__xo];
    result__[ 9   ] = t7 - LR__[iL_lambda1__xo];
    result__[ 10  ] = t9 - LR__[iL_lambda2__xo];
    result__[ 11  ] = t11 - LR__[iL_lambda3__xo];
    result__[ 12  ] = t13 - LR__[iL_lambda4__xo];
    result__[ 13  ] = t15 - LR__[iL_lambda5__xo];
    result__[ 14  ] = t17 - LR__[iL_lambda6__xo];
    result__[ 15  ] = OMEGA__[3] - LR__[iL_lambda7__xo];
    result__[ 16  ] = OMEGA__[4] - LR__[iL_lambda8__xo];
    real_type t33  = ALIAS_diff2pi_D(XR__[iX_theta3] - ModelPars[iM_theta_f]);
    result__[ 17  ] = t33 * OMEGA__[5] - LR__[iL_lambda9__xo];
    result__[ 18  ] = 0;
    result__[ 19  ] = 0;
    result__[ 20  ] = 0;
    result__[ 21  ] = 0;
    result__[ 22  ] = 0;
    result__[ 23  ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "adjointBC_eval", 24, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DadjointBCDx_numRows() const
  { return 24; }

  integer
  MultipleDubins::DadjointBCDx_numCols() const
  { return 18; }

  integer
  MultipleDubins::DadjointBCDx_nnz() const
  { return 1; }

  void
  MultipleDubins::DadjointBCDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 17  ; jIndex[0 ] = 17  ;
  }

  void
  MultipleDubins::DadjointBCDx_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
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
    real_type t5   = ALIAS_diff2pi_DD(XR__[iX_theta3] - ModelPars[iM_theta_f]);
    result__[ 0   ] = t5 * OMEGA__[5];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DadjointBCDxp_sparse", 1, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::DadjointBCDp_numRows() const
  { return 24; }

  integer
  MultipleDubins::DadjointBCDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::DadjointBCDp_nnz() const
  { return 0; }

  void
  MultipleDubins::DadjointBCDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {

  }

  void
  MultipleDubins::DadjointBCDp_sparse(
    NodeType2 const             & LEFT__,
    NodeType2 const             & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: MultipleDubins_Methods.cc
