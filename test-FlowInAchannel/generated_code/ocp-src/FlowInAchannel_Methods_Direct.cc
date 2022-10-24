/*-----------------------------------------------------------------------*\
 |  file: FlowInAchannel_Methods_Guess.cc                                |
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


#include "FlowInAchannel.hh"
#include "FlowInAchannel_Pars.hh"

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

namespace FlowInAchannelDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer FlowInAchannel::fd_ode_numEqns() const { return 4; }

  void
  FlowInAchannel::fd_ode_eval(
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
    real_type t2   = XM__[1];
    result__[ 0   ] = V__[0] - t2;
    real_type t4   = XM__[2];
    result__[ 1   ] = V__[1] - t4;
    real_type t6   = XM__[3];
    result__[ 2   ] = V__[2] - t6;
    result__[ 3   ] = V__[3] - (t4 * t2 - t6 * XM__[0]) * ModelPars[iM_R];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::Dfd_odeDxxpu_numRows() const { return 4; }
  integer FlowInAchannel::Dfd_odeDxxpu_numCols() const { return 8; }
  integer FlowInAchannel::Dfd_odeDxxpu_nnz()     const { return 20; }

  void
  FlowInAchannel::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
    iIndex[10] = 2   ; jIndex[10] = 6   ;
    iIndex[11] = 2   ; jIndex[11] = 7   ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
    iIndex[16] = 3   ; jIndex[16] = 4   ;
    iIndex[17] = 3   ; jIndex[17] = 5   ;
    iIndex[18] = 3   ; jIndex[18] = 6   ;
    iIndex[19] = 3   ; jIndex[19] = 7   ;
  }


  void
  FlowInAchannel::Dfd_odeDxxpu_sparse(
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
    result__[ 5   ] = -0.5e0;
    result__[ 6   ] = __INV_DZETA;
    result__[ 7   ] = -0.5e0;
    result__[ 8   ] = result__[4];
    result__[ 9   ] = -0.5e0;
    result__[ 10  ] = __INV_DZETA;
    result__[ 11  ] = -0.5e0;
    real_type t1   = ModelPars[iM_R];
    result__[ 12  ] = 0.5e0 * XM__[3] * t1;
    result__[ 13  ] = -0.5e0 * XM__[2] * t1;
    result__[ 14  ] = -0.5e0 * XM__[1] * t1;
    real_type t12  = 0.5e0 * XM__[0] * t1;
    result__[ 15  ] = t12 + result__[8];
    result__[ 16  ] = result__[12];
    result__[ 17  ] = result__[13];
    result__[ 18  ] = result__[14];
    result__[ 19  ] = t12 + __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer FlowInAchannel::D2fd_odeD2xxpu_numRows() const { return 8; }
  integer FlowInAchannel::D2fd_odeD2xxpu_numCols() const { return 8; }
  integer FlowInAchannel::D2fd_odeD2xxpu_nnz()     const { return 16; }

  void
  FlowInAchannel::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 7   ;
    iIndex[10] = 5   ; jIndex[10] = 2   ;
    iIndex[11] = 5   ; jIndex[11] = 6   ;
    iIndex[12] = 6   ; jIndex[12] = 1   ;
    iIndex[13] = 6   ; jIndex[13] = 5   ;
    iIndex[14] = 7   ; jIndex[14] = 0   ;
    iIndex[15] = 7   ; jIndex[15] = 4   ;
  }


  void
  FlowInAchannel::D2fd_odeD2xxpu_sparse(
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
    result__[ 0   ] = LM__[3] * ModelPars[iM_R] / 4;
    result__[ 1   ] = result__[0];
    result__[ 2   ] = -result__[1];
    result__[ 3   ] = result__[2];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = result__[4];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[6];
    result__[ 8   ] = result__[7];
    result__[ 9   ] = result__[8];
    result__[ 10  ] = result__[5];
    result__[ 11  ] = result__[10];
    result__[ 12  ] = result__[11];
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[9];
    result__[ 15  ] = result__[14];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: FlowInAchannel_Methods_Guess.cc
