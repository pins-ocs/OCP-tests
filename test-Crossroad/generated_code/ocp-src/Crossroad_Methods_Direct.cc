/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_Guess.cc                                     |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_max_DD(__t1) VelBound_max.DD( __t1)
#define ALIAS_VelBound_max_D(__t1) VelBound_max.D( __t1)
#define ALIAS_VelBound_min_DD(__t1) VelBound_min.DD( __t1)
#define ALIAS_VelBound_min_D(__t1) VelBound_min.D( __t1)
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


using namespace std;

namespace CrossroadDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Crossroad::fd_ode_numEqns() const { return 4; }

  void
  Crossroad::fd_ode_eval(
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
    real_type t1   = XM__[3];
    result__[ 0   ] = -XM__[1] * t1 + V__[0];
    result__[ 1   ] = -XM__[2] * t1 + V__[1];
    result__[ 2   ] = -UM__[0] * t1 + V__[2];
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::Dfd_odeDxxup_numRows() const { return 4; }
  integer Crossroad::Dfd_odeDxxup_numCols() const { return 9; }
  integer Crossroad::Dfd_odeDxxup_nnz()     const { return 19; }

  void
  Crossroad::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 7   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 2   ; jIndex[15] = 7   ;
    iIndex[16] = 2   ; jIndex[16] = 8   ;
    iIndex[17] = 3   ; jIndex[17] = 3   ;
    iIndex[18] = 3   ; jIndex[18] = 7   ;
  }


  void
  Crossroad::Dfd_odeDxxup_sparse(
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
    real_type t1   = XM__[3];
    result__[ 1   ] = -0.5e0 * t1;
    result__[ 2   ] = -0.5e0 * XM__[1];
    result__[ 3   ] = __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[0];
    result__[ 7   ] = result__[4];
    result__[ 8   ] = -0.5e0 * XM__[2];
    result__[ 9   ] = __INV_DZETA;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[6];
    result__[ 13  ] = -0.5e0 * UM__[0];
    result__[ 14  ] = __INV_DZETA;
    result__[ 15  ] = result__[13];
    result__[ 16  ] = -t1;
    result__[ 17  ] = result__[12];
    result__[ 18  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 19, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::D2fd_odeD2xxup_numRows() const { return 9; }
  integer Crossroad::D2fd_odeD2xxup_numCols() const { return 9; }
  integer Crossroad::D2fd_odeD2xxup_nnz()     const { return 20; }

  void
  Crossroad::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 3   ;
    iIndex[10] = 5   ; jIndex[10] = 7   ;
    iIndex[11] = 6   ; jIndex[11] = 3   ;
    iIndex[12] = 6   ; jIndex[12] = 7   ;
    iIndex[13] = 7   ; jIndex[13] = 1   ;
    iIndex[14] = 7   ; jIndex[14] = 2   ;
    iIndex[15] = 7   ; jIndex[15] = 5   ;
    iIndex[16] = 7   ; jIndex[16] = 6   ;
    iIndex[17] = 7   ; jIndex[17] = 8   ;
    iIndex[18] = 8   ; jIndex[18] = 3   ;
    iIndex[19] = 8   ; jIndex[19] = 7   ;
  }


  void
  Crossroad::D2fd_odeD2xxup_sparse(
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
    result__[ 0   ] = -LM__[0] / 4;
    result__[ 1   ] = result__[0];
    result__[ 2   ] = -LM__[1] / 4;
    result__[ 3   ] = result__[2];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[3];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = -LM__[2] / 2;
    result__[ 9   ] = result__[6];
    result__[ 10  ] = result__[9];
    result__[ 11  ] = result__[7];
    result__[ 12  ] = result__[11];
    result__[ 13  ] = result__[10];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    result__[ 16  ] = result__[14];
    result__[ 17  ] = result__[8];
    result__[ 18  ] = result__[17];
    result__[ 19  ] = result__[18];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Crossroad_Methods_Guess.cc
