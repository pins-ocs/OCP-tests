/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_Guess.cc                              |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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


#include "TwoPhaseSchwartz.hh"
#include "TwoPhaseSchwartz_Pars.hh"

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
#define ALIAS_bound2_DD(__t1) bound2.DD( __t1)
#define ALIAS_bound2_D(__t1) bound2.D( __t1)
#define ALIAS_bound1_DD(__t1) bound1.DD( __t1)
#define ALIAS_bound1_D(__t1) bound1.D( __t1)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace TwoPhaseSchwartzDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer TwoPhaseSchwartz::fd_ode_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::fd_ode_eval(
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
    real_type t6   = XM__[0] * XM__[0];
    result__[ 1   ] = V__[1] - UM__[0] + 0.1e0 * t2 * (2 * t6 + 1);
    real_type t11  = XM__[3];
    real_type t12  = ModelPars[iM_T2];
    result__[ 2   ] = -t12 * t11 + V__[2];
    real_type t18  = XM__[2] * XM__[2];
    result__[ 3   ] = V__[3] - (UM__[1] - 0.1e0 * t11 * (2 * t18 + 1)) * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::Dfd_odeDxxup_numRows() const { return 4; }
  integer TwoPhaseSchwartz::Dfd_odeDxxup_numCols() const { return 10; }
  integer TwoPhaseSchwartz::Dfd_odeDxxup_nnz()     const { return 18; }

  void
  TwoPhaseSchwartz::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 2   ; jIndex[11] = 6   ;
    iIndex[12] = 2   ; jIndex[12] = 7   ;
    iIndex[13] = 3   ; jIndex[13] = 2   ;
    iIndex[14] = 3   ; jIndex[14] = 3   ;
    iIndex[15] = 3   ; jIndex[15] = 6   ;
    iIndex[16] = 3   ; jIndex[16] = 7   ;
    iIndex[17] = 3   ; jIndex[17] = 9   ;
  }


  void
  TwoPhaseSchwartz::Dfd_odeDxxup_sparse(
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
    real_type t1   = XM__[0];
    result__[ 4   ] = 0.20e0 * XM__[1] * t1;
    real_type t4   = t1 * t1;
    real_type t5   = 0.10e0 * t4;
    result__[ 5   ] = 0.5e-1 + t5 + result__[0];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 0.5e-1 + t5 + __INV_DZETA;
    result__[ 8   ] = -1.0;
    result__[ 9   ] = result__[0];
    real_type t6   = ModelPars[iM_T2];
    result__[ 10  ] = -0.5e0 * t6;
    result__[ 11  ] = __INV_DZETA;
    result__[ 12  ] = result__[10];
    real_type t8   = XM__[2];
    result__[ 13  ] = 0.20e0 * XM__[3] * t8 * t6;
    real_type t12  = t8 * t8;
    real_type t16  = 0.5e0 * (-0.1e0 - 0.2e0 * t12) * t6;
    result__[ 14  ] = -t16 + result__[9];
    result__[ 15  ] = result__[13];
    result__[ 16  ] = -t16 + __INV_DZETA;
    result__[ 17  ] = -t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 18, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::D2fd_odeD2xxup_numRows() const { return 10; }
  integer TwoPhaseSchwartz::D2fd_odeD2xxup_numCols() const { return 10; }
  integer TwoPhaseSchwartz::D2fd_odeD2xxup_nnz()     const { return 24; }

  void
  TwoPhaseSchwartz::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 6   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 7   ;
    iIndex[10] = 3   ; jIndex[10] = 2   ;
    iIndex[11] = 3   ; jIndex[11] = 6   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 4   ;
    iIndex[15] = 4   ; jIndex[15] = 5   ;
    iIndex[16] = 5   ; jIndex[16] = 0   ;
    iIndex[17] = 5   ; jIndex[17] = 4   ;
    iIndex[18] = 6   ; jIndex[18] = 2   ;
    iIndex[19] = 6   ; jIndex[19] = 3   ;
    iIndex[20] = 6   ; jIndex[20] = 6   ;
    iIndex[21] = 6   ; jIndex[21] = 7   ;
    iIndex[22] = 7   ; jIndex[22] = 2   ;
    iIndex[23] = 7   ; jIndex[23] = 6   ;
  }


  void
  TwoPhaseSchwartz::D2fd_odeD2xxup_sparse(
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
    real_type t1   = LM__[1];
    result__[ 0   ] = 0.1e0 * (XR__[iX_x2] / 2 + XL__[iX_x2] / 2) * t1;
    real_type t7   = XR__[iX_x1];
    real_type t8   = XL__[iX_x1];
    result__[ 1   ] = 0.5000000000e-1 * (t7 + t8) * t1;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = (0.5000000000e-1 * t7 + 0.5000000000e-1 * t8) * t1;
    real_type t16  = ModelPars[iM_T2] * LM__[3];
    result__[ 6   ] = 0.1e0 * (XR__[iX_x4] / 2 + XL__[iX_x4] / 2) * t16;
    real_type t22  = XR__[iX_x3];
    real_type t23  = XL__[iX_x3];
    result__[ 7   ] = 0.5000000000e-1 * (t22 + t23) * t16;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = result__[7];
    result__[ 10  ] = result__[9];
    result__[ 11  ] = -(-0.5000000000e-1 * t22 - 0.5000000000e-1 * t23) * t16;
    result__[ 12  ] = result__[2];
    result__[ 13  ] = result__[5];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[4];
    result__[ 16  ] = result__[15];
    result__[ 17  ] = result__[16];
    result__[ 18  ] = result__[8];
    result__[ 19  ] = result__[11];
    result__[ 20  ] = result__[18];
    result__[ 21  ] = result__[10];
    result__[ 22  ] = result__[21];
    result__[ 23  ] = result__[22];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: TwoPhaseSchwartz_Methods_Guess.cc
