/*-----------------------------------------------------------------------*\
 |  file: BangBangFclip_Methods_Guess.cc                                 |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "BangBangFclip.hh"
#include "BangBangFclip_Pars.hh"

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
#define ALIAS_controlForce_D_3(__t1, __t2, __t3) controlForce.D_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_2(__t1, __t2, __t3) controlForce.D_2( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1(__t1, __t2, __t3) controlForce.D_1( __t1, __t2, __t3)
#define ALIAS_controlForce_D_3_3(__t1, __t2, __t3) controlForce.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_2_3(__t1, __t2, __t3) controlForce.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_2_2(__t1, __t2, __t3) controlForce.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1_3(__t1, __t2, __t3) controlForce.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1_2(__t1, __t2, __t3) controlForce.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlForce_D_1_1(__t1, __t2, __t3) controlForce.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace BangBangFclipDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer BangBangFclip::fd_ode_numEqns() const { return 3; }

  void
  BangBangFclip::fd_ode_eval(
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
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0] - XM__[1];
    real_type t7   = clip(XM__[2], ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    result__[ 1   ] = V__[1] - t7;
    result__[ 2   ] = V__[2] - UM__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::Dfd_odeDxxup_numRows() const { return 3; }
  integer BangBangFclip::Dfd_odeDxxup_numCols() const { return 7; }
  integer BangBangFclip::Dfd_odeDxxup_nnz()     const { return 11; }

  void
  BangBangFclip::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 2   ; jIndex[10] = 6   ;
  }


  void
  BangBangFclip::Dfd_odeDxxup_sparse(
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
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    result__[ 1   ] = -0.5e0;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = -0.5e0;
    result__[ 4   ] = result__[0];
    real_type t4   = ALIAS_clip_D_1(XM__[2], ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    result__[ 5   ] = -0.5e0 * t4;
    result__[ 6   ] = __INV_DZETA;
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[4];
    result__[ 9   ] = __INV_DZETA;
    result__[ 10  ] = -1.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 11, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFclip::D2fd_odeD2xxup_numRows() const { return 7; }
  integer BangBangFclip::D2fd_odeD2xxup_numCols() const { return 7; }
  integer BangBangFclip::D2fd_odeD2xxup_nnz()     const { return 4; }

  void
  BangBangFclip::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 5   ;
  }


  void
  BangBangFclip::D2fd_odeD2xxup_sparse(
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
    real_type QM__[1], XM__[3], V__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t8   = ALIAS_clip_D_1_1(XR__[iX_F] / 2 + XL__[iX_F] / 2, ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    result__[ 0   ] = -t8 * LM__[1] / 4;
    result__[ 1   ] = result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: BangBangFclip_Methods_Guess.cc
