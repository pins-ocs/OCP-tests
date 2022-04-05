/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_Guess.cc                                      |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


using namespace std;

namespace AlpRiderDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer AlpRider::fd_ode_numEqns() const { return 4; }

  void
  AlpRider::fd_ode_eval(
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
    real_type t4   = UM__[0];
    real_type t5   = UM__[1];
    result__[ 0   ] = V__[0] + 10 * XM__[0] - t4 - t5;
    result__[ 1   ] = V__[1] + 2 * XM__[1] - t4 - 2 * t5;
    real_type t11  = XM__[2];
    real_type t13  = XM__[3];
    result__[ 2   ] = V__[2] + 3 * t11 - 5 * t13 - t4 + t5;
    result__[ 3   ] = V__[3] - 5 * t11 + 3 * t13 - t4 - 3 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::Dfd_odeDxxup_numRows() const { return 4; }
  integer AlpRider::Dfd_odeDxxup_numCols() const { return 10; }
  integer AlpRider::Dfd_odeDxxup_nnz()     const { return 20; }

  void
  AlpRider::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 8   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 8   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
    iIndex[10] = 2   ; jIndex[10] = 6   ;
    iIndex[11] = 2   ; jIndex[11] = 7   ;
    iIndex[12] = 2   ; jIndex[12] = 8   ;
    iIndex[13] = 2   ; jIndex[13] = 9   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
    iIndex[16] = 3   ; jIndex[16] = 6   ;
    iIndex[17] = 3   ; jIndex[17] = 7   ;
    iIndex[18] = 3   ; jIndex[18] = 8   ;
    iIndex[19] = 3   ; jIndex[19] = 9   ;
  }


  void
  AlpRider::Dfd_odeDxxup_sparse(
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
    result__[ 0   ] = 5.0 - __INV_DZETA;
    result__[ 1   ] = 5.0 + __INV_DZETA;
    result__[ 2   ] = -1.0;
    result__[ 3   ] = -1.0;
    result__[ 4   ] = 1.0 - __INV_DZETA;
    result__[ 5   ] = 1.0 + __INV_DZETA;
    result__[ 6   ] = -1.0;
    result__[ 7   ] = -2.0;
    result__[ 8   ] = 0.150000000000000000e1 - __INV_DZETA;
    result__[ 9   ] = -0.250000000000000000e1;
    result__[ 10  ] = 0.150000000000000000e1 + __INV_DZETA;
    result__[ 11  ] = -0.250000000000000000e1;
    result__[ 12  ] = -1.0;
    result__[ 13  ] = 1.0;
    result__[ 14  ] = -0.250000000000000000e1;
    result__[ 15  ] = result__[8];
    result__[ 16  ] = -0.250000000000000000e1;
    result__[ 17  ] = result__[10];
    result__[ 18  ] = -1.0;
    result__[ 19  ] = -3.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::D2fd_odeD2xxup_numRows() const { return 10; }
  integer AlpRider::D2fd_odeD2xxup_numCols() const { return 10; }
  integer AlpRider::D2fd_odeD2xxup_nnz()     const { return 0; }

  void
  AlpRider::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::D2fd_odeD2xxup_sparse(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    P_const_pointer_type P__,
    U_const_pointer_type UM__,
    L_const_pointer_type LM__,
    real_ptr             result__
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: AlpRider_Methods_Guess.cc
