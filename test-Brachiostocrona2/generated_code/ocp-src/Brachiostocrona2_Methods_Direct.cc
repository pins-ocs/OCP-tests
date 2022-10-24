/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods_Guess.cc                              |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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
#define ALIAS_TimePositive_DD(__t1) TimePositive.DD( __t1)
#define ALIAS_TimePositive_D(__t1) TimePositive.D( __t1)


using namespace std;

namespace Brachiostocrona2Define {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Brachiostocrona2::fd_ode_numEqns() const { return 3; }

  void
  Brachiostocrona2::fd_ode_eval(
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
    real_type t2   = P__[iP_T];
    real_type t4   = XM__[2] * t2;
    real_type t5   = UM__[0];
    real_type t6   = cos(t5);
    result__[ 0   ] = -t6 * t4 + V__[0];
    real_type t9   = sin(t5);
    result__[ 1   ] = -t9 * t4 + V__[1];
    result__[ 2   ] = t9 * ModelPars[iM_g] * t2 + ModelPars[iM_mass] * V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::Dfd_odeDxxpu_numRows() const { return 3; }
  integer Brachiostocrona2::Dfd_odeDxxpu_numCols() const { return 8; }
  integer Brachiostocrona2::Dfd_odeDxxpu_nnz()     const { return 16; }

  void
  Brachiostocrona2::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 7   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 5   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 2   ; jIndex[15] = 7   ;
  }


  void
  Brachiostocrona2::Dfd_odeDxxpu_sparse(
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
    real_type t2   = UM__[0];
    real_type t3   = cos(t2);
    result__[ 1   ] = -0.5e0 * t3 * t1;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = result__[1];
    real_type t6   = XM__[2];
    real_type t7   = t6 * t1;
    real_type t8   = sin(t2);
    result__[ 4   ] = t8 * t7;
    result__[ 5   ] = -t3 * t6;
    result__[ 6   ] = result__[0];
    result__[ 7   ] = -0.5e0 * t8 * t1;
    result__[ 8   ] = __INV_DZETA;
    result__[ 9   ] = result__[7];
    result__[ 10  ] = -t3 * t7;
    result__[ 11  ] = -t6 * t8;
    real_type t15  = __INV_DZETA * ModelPars[iM_mass];
    result__[ 12  ] = -t15;
    result__[ 13  ] = t15;
    real_type t16  = ModelPars[iM_g];
    result__[ 14  ] = t3 * t16 * t1;
    result__[ 15  ] = t8 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::D2fd_odeD2xxpu_numRows() const { return 8; }
  integer Brachiostocrona2::D2fd_odeD2xxpu_numCols() const { return 8; }
  integer Brachiostocrona2::D2fd_odeD2xxpu_nnz()     const { return 11; }

  void
  Brachiostocrona2::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 6   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 6   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 6   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 7   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 7   ; jIndex[9 ] = 5   ;
    iIndex[10] = 7   ; jIndex[10] = 6   ;
  }


  void
  Brachiostocrona2::D2fd_odeD2xxpu_sparse(
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
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = UM__[0];
    real_type t5   = sin(t4);
    real_type t7   = LM__[1];
    real_type t8   = t2 * t7;
    real_type t9   = cos(t4);
    result__[ 0   ] = t3 * t5 / 2 - t9 * t8 / 2;
    result__[ 1   ] = -t9 * t1 / 2 - t5 * t7 / 2;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = result__[4];
    real_type t18  = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t23  = LM__[2];
    real_type t25  = ModelPars[iM_g];
    result__[ 6   ] = -t5 * t25 * t2 * t23 + t9 * t18 * t3 + t5 * t18 * t8;
    result__[ 7   ] = t5 * t18 * t1 - t9 * t18 * t7 + t9 * t25 * t23;
    result__[ 8   ] = result__[3];
    result__[ 9   ] = result__[8];
    result__[ 10  ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 11, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Brachiostocrona2_Methods_Guess.cc
