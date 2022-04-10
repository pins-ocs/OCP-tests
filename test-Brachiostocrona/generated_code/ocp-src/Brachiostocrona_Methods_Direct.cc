/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_Guess.cc                               |
 |                                                                       |
 |  version: 1.0   date 10/4/2022                                        |
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


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

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
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace BrachiostocronaDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Brachiostocrona::fd_ode_numEqns() const { return 4; }

  void
  Brachiostocrona::fd_ode_eval(
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
    real_type t2   = P__[iP_T];
    real_type t4   = XM__[2] * t2;
    real_type t5   = XM__[3];
    real_type t6   = cos(t5);
    result__[ 0   ] = -t6 * t4 + V__[0];
    real_type t9   = sin(t5);
    result__[ 1   ] = -t9 * t4 + V__[1];
    result__[ 2   ] = t9 * ModelPars[iM_g] * t2 + ModelPars[iM_mass] * V__[2];
    result__[ 3   ] = V__[3] - UM__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::Dfd_odeDxxup_numRows() const { return 4; }
  integer Brachiostocrona::Dfd_odeDxxup_numCols() const { return 10; }
  integer Brachiostocrona::Dfd_odeDxxup_nnz()     const { return 22; }

  void
  Brachiostocrona::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 9   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 1   ; jIndex[13] = 9   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 3   ;
    iIndex[16] = 2   ; jIndex[16] = 6   ;
    iIndex[17] = 2   ; jIndex[17] = 7   ;
    iIndex[18] = 2   ; jIndex[18] = 9   ;
    iIndex[19] = 3   ; jIndex[19] = 3   ;
    iIndex[20] = 3   ; jIndex[20] = 7   ;
    iIndex[21] = 3   ; jIndex[21] = 8   ;
  }


  void
  Brachiostocrona::Dfd_odeDxxup_sparse(
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
    real_type t1   = P__[iP_T];
    real_type t2   = XM__[3];
    real_type t3   = cos(t2);
    result__[ 1   ] = -0.5e0 * t3 * t1;
    real_type t6   = XM__[2];
    real_type t7   = t6 * t1;
    real_type t8   = sin(t2);
    result__[ 2   ] = 0.5e0 * t8 * t7;
    result__[ 3   ] = __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = -t3 * t6;
    result__[ 7   ] = result__[0];
    result__[ 8   ] = -0.5e0 * t8 * t1;
    result__[ 9   ] = -0.5e0 * t3 * t7;
    result__[ 10  ] = __INV_DZETA;
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = -t6 * t8;
    real_type t17  = __INV_DZETA * ModelPars[iM_mass];
    result__[ 14  ] = -t17;
    real_type t18  = ModelPars[iM_g];
    result__[ 15  ] = 0.5e0 * t3 * t18 * t1;
    result__[ 16  ] = t17;
    result__[ 17  ] = result__[15];
    result__[ 18  ] = t8 * t18;
    result__[ 19  ] = result__[7];
    result__[ 20  ] = __INV_DZETA;
    result__[ 21  ] = -1.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 22, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::D2fd_odeD2xxup_numRows() const { return 10; }
  integer Brachiostocrona::D2fd_odeD2xxup_numCols() const { return 10; }
  integer Brachiostocrona::D2fd_odeD2xxup_nnz()     const { return 20; }

  void
  Brachiostocrona::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 9   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 6   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 6   ; jIndex[9 ] = 7   ;
    iIndex[10] = 6   ; jIndex[10] = 9   ;
    iIndex[11] = 7   ; jIndex[11] = 2   ;
    iIndex[12] = 7   ; jIndex[12] = 3   ;
    iIndex[13] = 7   ; jIndex[13] = 6   ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 9   ;
    iIndex[16] = 9   ; jIndex[16] = 2   ;
    iIndex[17] = 9   ; jIndex[17] = 3   ;
    iIndex[18] = 9   ; jIndex[18] = 6   ;
    iIndex[19] = 9   ; jIndex[19] = 7   ;
  }


  void
  Brachiostocrona::D2fd_odeD2xxup_sparse(
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
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t7   = XR__[iX_theta] / 2 + XL__[iX_theta] / 2;
    real_type t8   = sin(t7);
    real_type t10  = LM__[1];
    real_type t11  = t2 * t10;
    real_type t12  = cos(t7);
    result__[ 0   ] = -t12 * t11 / 4 + t8 * t3 / 4;
    result__[ 1   ] = result__[0];
    result__[ 2   ] = -t12 * t1 / 2 - t8 * t10 / 2;
    result__[ 3   ] = result__[1];
    real_type t21  = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t26  = LM__[2];
    real_type t28  = ModelPars[iM_g];
    result__[ 4   ] = -t8 * t28 * t2 * t26 / 4 + t8 * t21 * t11 / 4 + t12 * t21 * t3 / 4;
    result__[ 5   ] = result__[3];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = t8 * t21 * t1 / 2 - t12 * t21 * t10 / 2 + t12 * t28 * t26 / 2;
    result__[ 8   ] = result__[5];
    result__[ 9   ] = result__[8];
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[6];
    result__[ 13  ] = result__[11];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[7];
    result__[ 16  ] = result__[10];
    result__[ 17  ] = result__[15];
    result__[ 18  ] = result__[16];
    result__[ 19  ] = result__[17];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Brachiostocrona_Methods_Guess.cc
