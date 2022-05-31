/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods_Guess.cc                                  |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

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
#define ALIAS_vsTBInterval_max_DD(__t1) vsTBInterval_max.DD( __t1)
#define ALIAS_vsTBInterval_max_D(__t1) vsTBInterval_max.D( __t1)
#define ALIAS_vsTBInterval_min_DD(__t1) vsTBInterval_min.DD( __t1)
#define ALIAS_vsTBInterval_min_D(__t1) vsTBInterval_min.D( __t1)
#define ALIAS_vsTmax_DD(__t1) vsTmax.DD( __t1)
#define ALIAS_vsTmax_D(__t1) vsTmax.D( __t1)
#define ALIAS_vsBpositive_DD(__t1) vsBpositive.DD( __t1)
#define ALIAS_vsBpositive_D(__t1) vsBpositive.D( __t1)
#define ALIAS_vsTpositive_DD(__t1) vsTpositive.DD( __t1)
#define ALIAS_vsTpositive_D(__t1) vsTpositive.D( __t1)


using namespace std;

namespace BangBangFtauDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer BangBangFtau::fd_ode_numEqns() const { return 4; }

  void
  BangBangFtau::fd_ode_eval(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[4], V__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0] - XM__[1];
    real_type t4   = XM__[2];
    real_type t5   = XM__[3];
    real_type t9   = clip(t4 - t5, ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    result__[ 1   ] = V__[1] - t9;
    result__[ 2   ] = V__[2] + 1.0 / ModelPars[iM_tauT] * (t4 - UM__[0]);
    result__[ 3   ] = V__[3] + 1.0 / ModelPars[iM_tauB] * (t5 - UM__[1]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::Dfd_odeDxxpu_numRows() const { return 4; }
  integer BangBangFtau::Dfd_odeDxxpu_numCols() const { return 10; }
  integer BangBangFtau::Dfd_odeDxxpu_nnz()     const { return 16; }

  void
  BangBangFtau::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 7   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 6   ;
    iIndex[12] = 2   ; jIndex[12] = 8   ;
    iIndex[13] = 3   ; jIndex[13] = 3   ;
    iIndex[14] = 3   ; jIndex[14] = 7   ;
    iIndex[15] = 3   ; jIndex[15] = 9   ;
  }


  void
  BangBangFtau::Dfd_odeDxxpu_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[4], V__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    result__[ 1   ] = -0.5e0;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = -0.5e0;
    result__[ 4   ] = result__[0];
    real_type t6   = ALIAS_clip_D_1(XM__[2] - XM__[3], ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    real_type t7   = 0.5e0 * t6;
    result__[ 5   ] = -t7;
    result__[ 6   ] = t7;
    result__[ 7   ] = __INV_DZETA;
    result__[ 8   ] = result__[5];
    result__[ 9   ] = result__[6];
    real_type t9   = 1.0 / ModelPars[iM_tauT];
    real_type t10  = 0.5e0 * t9;
    result__[ 10  ] = t10 + result__[4];
    result__[ 11  ] = t10 + __INV_DZETA;
    result__[ 12  ] = -t9;
    real_type t12  = 1.0 / ModelPars[iM_tauB];
    real_type t13  = 0.5e0 * t12;
    result__[ 13  ] = t13 + result__[4];
    result__[ 14  ] = t13 + __INV_DZETA;
    result__[ 15  ] = -t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::D2fd_odeD2xxpu_numRows() const { return 10; }
  integer BangBangFtau::D2fd_odeD2xxpu_numCols() const { return 10; }
  integer BangBangFtau::D2fd_odeD2xxpu_nnz()     const { return 16; }

  void
  BangBangFtau::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 6   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 6   ; jIndex[9 ] = 3   ;
    iIndex[10] = 6   ; jIndex[10] = 6   ;
    iIndex[11] = 6   ; jIndex[11] = 7   ;
    iIndex[12] = 7   ; jIndex[12] = 2   ;
    iIndex[13] = 7   ; jIndex[13] = 3   ;
    iIndex[14] = 7   ; jIndex[14] = 6   ;
    iIndex[15] = 7   ; jIndex[15] = 7   ;
  }


  void
  BangBangFtau::D2fd_odeD2xxpu_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_type QM__[1], XM__[4], V__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t10  = ALIAS_clip_D_1_1(XR__[iX_sT] / 2 + XL__[iX_sT] / 2 - XR__[iX_sB] / 2 - XL__[iX_sB] / 2, ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    real_type t12  = t10 * LM__[1] / 4;
    result__[ 0   ] = -t12;
    result__[ 1   ] = t12;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[7];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[11];
    result__[ 13  ] = result__[10];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: BangBangFtau_Methods_Guess.cc
