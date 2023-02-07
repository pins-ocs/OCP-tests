/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods_Guess.cc                                         |
 |                                                                       |
 |  version: 1.0   date 8/2/2023                                         |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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


using namespace std;

namespace BrakeDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Brake::fd_ode_numEqns() const { return 2; }

  void
  Brake::fd_ode_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    U_const_p_type UM__,
    real_ptr       result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    result__[ 0   ] = -XM__[1] * t1 + V__[0];
    result__[ 1   ] = -UM__[0] * t1 + V__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brake::Dfd_odeDxxpu_numRows() const { return 2; }
  integer Brake::Dfd_odeDxxpu_numCols() const { return 6; }
  integer Brake::Dfd_odeDxxpu_nnz()     const { return 9; }

  void
  Brake::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
  }


  void
  Brake::Dfd_odeDxxpu_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    U_const_p_type UM__,
    real_ptr       result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = 1.0 / DZETA__xo;
    result__[ 0   ] = -t1;
    real_type t2   = P__[iP_T];
    result__[ 1   ] = -t2 / 2;
    result__[ 2   ] = t1;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = -XM__[1];
    result__[ 5   ] = result__[0];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = -UM__[0];
    result__[ 8   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brake::D2fd_odeD2xxpu_numRows() const { return 6; }
  integer Brake::D2fd_odeD2xxpu_numCols() const { return 6; }
  integer Brake::D2fd_odeD2xxpu_nnz()     const { return 6; }

  void
  Brake::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 4   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 4   ;
  }


  void
  Brake::D2fd_odeD2xxpu_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    U_const_p_type UM__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -OMEGA__[0] / 2;
    result__[ 1   ] = result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    result__[ 4   ] = -OMEGA__[1];
    result__[ 5   ] = result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Brake_Methods_Guess.cc
