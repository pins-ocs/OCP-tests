/*-----------------------------------------------------------------------*\
 |  file: BangBangFork_Methods_Guess.cc                                  |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "BangBangFork.hh"
#include "BangBangFork_Pars.hh"

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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_Tbarrier_DD(__t1) Tbarrier.DD( __t1)
#define ALIAS_Tbarrier_D(__t1) Tbarrier.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace BangBangForkDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer BangBangFork::fd_ode_numEqns() const { return 3; }

  void
  BangBangFork::fd_ode_eval(
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
    real_type t1   = P__[iP_T];
    real_type t2   = XM__[1];
    result__[ 0   ] = t2 * t1 + V__[0];
    result__[ 1   ] = V__[1] - (UM__[1] * ModelPars[iM_WU2] + XM__[2]) * t1;
    real_type t13  = t2 * t2;
    real_type t14  = t13 * t13;
    result__[ 2   ] = V__[2] - (-ModelPars[iM_kappa] * t14 * t2 + UM__[0]) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFork::Dfd_odeDxxpu_numRows() const { return 3; }
  integer BangBangFork::Dfd_odeDxxpu_numCols() const { return 9; }
  integer BangBangFork::Dfd_odeDxxpu_nnz()     const { return 17; }

  void
  BangBangFork::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 7   ;
    iIndex[10] = 1   ; jIndex[10] = 8   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 5   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 2   ; jIndex[16] = 8   ;
  }


  void
  BangBangFork::Dfd_odeDxxpu_sparse(
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
    real_type t1   = P__[iP_T];
    result__[ 1   ] = 0.5e0 * t1;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = XM__[1];
    result__[ 5   ] = result__[0];
    result__[ 6   ] = -result__[3];
    result__[ 7   ] = __INV_DZETA;
    result__[ 8   ] = result__[6];
    real_type t2   = ModelPars[iM_WU2];
    result__[ 9   ] = -t2 * t1;
    result__[ 10  ] = -t2 * UM__[1] - XM__[2];
    real_type t7   = ModelPars[iM_kappa];
    real_type t9   = result__[4] * result__[4];
    real_type t10  = t9 * t9;
    result__[ 11  ] = 0.25e1 * t10 * t7 * t1;
    result__[ 12  ] = result__[5];
    result__[ 13  ] = result__[11];
    result__[ 14  ] = __INV_DZETA;
    result__[ 15  ] = -t1;
    result__[ 16  ] = t7 * t10 * result__[4] - UM__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 17, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFork::D2fd_odeD2xxpu_numRows() const { return 9; }
  integer BangBangFork::D2fd_odeD2xxpu_numCols() const { return 9; }
  integer BangBangFork::D2fd_odeD2xxpu_nnz()     const { return 16; }

  void
  BangBangFork::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 6   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 7   ; jIndex[9 ] = 8   ;
    iIndex[10] = 8   ; jIndex[10] = 1   ;
    iIndex[11] = 8   ; jIndex[11] = 2   ;
    iIndex[12] = 8   ; jIndex[12] = 4   ;
    iIndex[13] = 8   ; jIndex[13] = 5   ;
    iIndex[14] = 8   ; jIndex[14] = 6   ;
    iIndex[15] = 8   ; jIndex[15] = 7   ;
  }


  void
  BangBangFork::D2fd_odeD2xxpu_sparse(
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
    real_type t1   = LM__[2];
    real_type t4   = ModelPars[iM_kappa];
    real_type t8   = XR__[iX_x2] / 2 + XL__[iX_x2] / 2;
    real_type t9   = t8 * t8;
    result__[ 0   ] = 5 * t9 * t8 * t4 * P__[iP_T] * t1;
    result__[ 1   ] = result__[0];
    real_type t16  = t9 * t9;
    result__[ 2   ] = LM__[0] / 2 + 5.0 / 2.0 * t16 * t4 * t1;
    real_type t19  = LM__[1];
    result__[ 3   ] = -t19 / 2;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[4];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    result__[ 8   ] = -t1;
    result__[ 9   ] = -ModelPars[iM_WU2] * t19;
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = result__[11];
    result__[ 14  ] = result__[8];
    result__[ 15  ] = result__[9];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: BangBangFork_Methods_Guess.cc