/*-----------------------------------------------------------------------*\
 |  file: Train_Methods_Guess.cc                                         |
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


#include "Train.hh"
#include "Train_Pars.hh"

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
#define ALIAS_ubControl_D_3(__t1, __t2, __t3) ubControl.D_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2(__t1, __t2, __t3) ubControl.D_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1(__t1, __t2, __t3) ubControl.D_1( __t1, __t2, __t3)
#define ALIAS_ubControl_D_3_3(__t1, __t2, __t3) ubControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_3(__t1, __t2, __t3) ubControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_2(__t1, __t2, __t3) ubControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_3(__t1, __t2, __t3) ubControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_2(__t1, __t2, __t3) ubControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_1(__t1, __t2, __t3) ubControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3(__t1, __t2, __t3) uaControl.D_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2(__t1, __t2, __t3) uaControl.D_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1(__t1, __t2, __t3) uaControl.D_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3_3(__t1, __t2, __t3) uaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_3(__t1, __t2, __t3) uaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_2(__t1, __t2, __t3) uaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_3(__t1, __t2, __t3) uaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_2(__t1, __t2, __t3) uaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_1(__t1, __t2, __t3) uaControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace TrainDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Train::fd_ode_numEqns() const { return 2; }

  void
  Train::fd_ode_eval(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = XM__[1];
    result__[ 0   ] = V__[0] - t2;
    real_type t5   = acc(XM__[0], t2);
    result__[ 1   ] = V__[1] - t5 - UM__[0] + UM__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Train::Dfd_odeDxxpu_numRows() const { return 2; }
  integer Train::Dfd_odeDxxpu_numCols() const { return 6; }
  integer Train::Dfd_odeDxxpu_nnz()     const { return 10; }

  void
  Train::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
  }


  void
  Train::Dfd_odeDxxpu_sparse(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    result__[ 1   ] = -0.5e0;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = -0.5e0;
    real_type t1   = XM__[0];
    real_type t2   = XM__[1];
    real_type t3   = acc_D_1(t1, t2);
    result__[ 4   ] = -0.5e0 * t3;
    real_type t5   = acc_D_2(t1, t2);
    real_type t6   = 0.5e0 * t5;
    result__[ 5   ] = -t6 + result__[0];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = -t6 + __INV_DZETA;
    result__[ 8   ] = -1.0;
    result__[ 9   ] = 1.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Train::D2fd_odeD2xxpu_numRows() const { return 6; }
  integer Train::D2fd_odeD2xxpu_numCols() const { return 6; }
  integer Train::D2fd_odeD2xxpu_nnz()     const { return 16; }

  void
  Train::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
  }


  void
  Train::D2fd_odeD2xxpu_sparse(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[1];
    real_type t5   = XR__[iX_x] / 2 + XL__[iX_x] / 2;
    real_type t9   = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t10  = acc_D_1_1(t5, t9);
    result__[ 0   ] = -t10 * t1 / 4;
    real_type t13  = acc_D_1_2(t5, t9);
    result__[ 1   ] = -t13 * t1 / 4;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[3];
    real_type t16  = acc_D_2_2(t5, t9);
    result__[ 5   ] = -t16 * t1 / 4;
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[11];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Train_Methods_Guess.cc
