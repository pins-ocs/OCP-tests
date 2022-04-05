/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_Guess.cc                                 |
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


#include "OrbitTransfer.hh"
#include "OrbitTransfer_Pars.hh"

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


using namespace std;

namespace OrbitTransferDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer OrbitTransfer::fd_ode_numEqns() const { return 5; }

  void
  OrbitTransfer::fd_ode_eval(
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
    real_type QM__[1], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XM__[3];
    real_type t2   = ModelPars[iM_tf];
    result__[ 0   ] = -t2 * t1 + V__[2];
    real_type t6   = XM__[4];
    real_type t7   = t6 * t6;
    real_type t8   = XM__[2];
    real_type t9   = 1.0 / t8;
    real_type t12  = t8 * t8;
    real_type t15  = ModelPars[iM_T];
    real_type t16  = UM__[0];
    real_type t17  = sin(t16);
    real_type t20  = 1.0 / XM__[0];
    result__[ 1   ] = V__[3] - (t9 * t7 - 1.0 / t12 * ModelPars[iM_mu] + t20 * t17 * t15) * t2;
    real_type t27  = cos(t16);
    result__[ 2   ] = V__[4] - (-t9 * t1 * t6 + t20 * t27 * t15) * t2;
    result__[ 3   ] = ModelPars[iM_mdot] * t2 + V__[0];
    result__[ 4   ] = -t9 * t6 * t2 + V__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::Dfd_odeDxxup_numRows() const { return 5; }
  integer OrbitTransfer::Dfd_odeDxxup_numCols() const { return 11; }
  integer OrbitTransfer::Dfd_odeDxxup_nnz()     const { return 30; }

  void
  OrbitTransfer::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 7   ;
    iIndex[10] = 1   ; jIndex[10] = 8   ;
    iIndex[11] = 1   ; jIndex[11] = 9   ;
    iIndex[12] = 1   ; jIndex[12] = 10  ;
    iIndex[13] = 2   ; jIndex[13] = 0   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 3   ;
    iIndex[16] = 2   ; jIndex[16] = 4   ;
    iIndex[17] = 2   ; jIndex[17] = 5   ;
    iIndex[18] = 2   ; jIndex[18] = 7   ;
    iIndex[19] = 2   ; jIndex[19] = 8   ;
    iIndex[20] = 2   ; jIndex[20] = 9   ;
    iIndex[21] = 2   ; jIndex[21] = 10  ;
    iIndex[22] = 3   ; jIndex[22] = 0   ;
    iIndex[23] = 3   ; jIndex[23] = 5   ;
    iIndex[24] = 4   ; jIndex[24] = 1   ;
    iIndex[25] = 4   ; jIndex[25] = 2   ;
    iIndex[26] = 4   ; jIndex[26] = 4   ;
    iIndex[27] = 4   ; jIndex[27] = 6   ;
    iIndex[28] = 4   ; jIndex[28] = 7   ;
    iIndex[29] = 4   ; jIndex[29] = 9   ;
  }


  void
  OrbitTransfer::Dfd_odeDxxup_sparse(
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
    real_type QM__[1], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -__INV_DZETA;
    real_type t1   = ModelPars[iM_tf];
    result__[ 1   ] = -0.5e0 * t1;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = result__[1];
    real_type t4   = ModelPars[iM_T] * t1;
    real_type t5   = UM__[0];
    real_type t6   = sin(t5);
    real_type t7   = XM__[0];
    real_type t8   = t7 * t7;
    real_type t9   = 1.0 / t8;
    result__[ 4   ] = 0.5e0 * t9 * t6 * t4;
    real_type t12  = XM__[4];
    real_type t13  = t12 * t12;
    real_type t14  = XM__[2];
    real_type t15  = t14 * t14;
    real_type t16  = 1.0 / t15;
    result__[ 5   ] = -0.5e0 * (-t16 * t13 + 2 / t15 / t14 * ModelPars[iM_mu]) * t1;
    result__[ 6   ] = result__[0];
    real_type t26  = t12 * t1;
    real_type t27  = 1.0 / t14;
    real_type t28  = t27 * t26;
    result__[ 7   ] = -0.10e1 * t28;
    result__[ 8   ] = result__[4];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = __INV_DZETA;
    result__[ 11  ] = result__[7];
    real_type t30  = cos(t5);
    real_type t31  = 1.0 / t7;
    result__[ 12  ] = -t31 * t30 * t4;
    result__[ 13  ] = 0.5e0 * t9 * t30 * t4;
    real_type t36  = XM__[3];
    result__[ 14  ] = -0.5e0 * t16 * t36 * t26;
    result__[ 15  ] = 0.5e0 * t28;
    real_type t42  = 0.5e0 * t27 * t36 * t1;
    result__[ 16  ] = t42 + result__[6];
    result__[ 17  ] = result__[13];
    result__[ 18  ] = result__[14];
    result__[ 19  ] = result__[15];
    result__[ 20  ] = t42 + __INV_DZETA;
    result__[ 21  ] = t31 * t6 * t4;
    result__[ 22  ] = result__[6];
    result__[ 23  ] = __INV_DZETA;
    result__[ 24  ] = result__[22];
    result__[ 25  ] = 0.5e0 * t16 * t26;
    result__[ 26  ] = -0.5e0 * t27 * t1;
    result__[ 27  ] = __INV_DZETA;
    result__[ 28  ] = result__[25];
    result__[ 29  ] = result__[26];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 30, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::D2fd_odeD2xxup_numRows() const { return 11; }
  integer OrbitTransfer::D2fd_odeD2xxup_numCols() const { return 11; }
  integer OrbitTransfer::D2fd_odeD2xxup_nnz()     const { return 41; }

  void
  OrbitTransfer::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 9   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 2   ;
    iIndex[10] = 3   ; jIndex[10] = 4   ;
    iIndex[11] = 3   ; jIndex[11] = 7   ;
    iIndex[12] = 3   ; jIndex[12] = 9   ;
    iIndex[13] = 4   ; jIndex[13] = 2   ;
    iIndex[14] = 4   ; jIndex[14] = 3   ;
    iIndex[15] = 4   ; jIndex[15] = 4   ;
    iIndex[16] = 4   ; jIndex[16] = 7   ;
    iIndex[17] = 4   ; jIndex[17] = 8   ;
    iIndex[18] = 4   ; jIndex[18] = 9   ;
    iIndex[19] = 5   ; jIndex[19] = 0   ;
    iIndex[20] = 5   ; jIndex[20] = 5   ;
    iIndex[21] = 5   ; jIndex[21] = 10  ;
    iIndex[22] = 7   ; jIndex[22] = 2   ;
    iIndex[23] = 7   ; jIndex[23] = 3   ;
    iIndex[24] = 7   ; jIndex[24] = 4   ;
    iIndex[25] = 7   ; jIndex[25] = 7   ;
    iIndex[26] = 7   ; jIndex[26] = 8   ;
    iIndex[27] = 7   ; jIndex[27] = 9   ;
    iIndex[28] = 8   ; jIndex[28] = 2   ;
    iIndex[29] = 8   ; jIndex[29] = 4   ;
    iIndex[30] = 8   ; jIndex[30] = 7   ;
    iIndex[31] = 8   ; jIndex[31] = 9   ;
    iIndex[32] = 9   ; jIndex[32] = 2   ;
    iIndex[33] = 9   ; jIndex[33] = 3   ;
    iIndex[34] = 9   ; jIndex[34] = 4   ;
    iIndex[35] = 9   ; jIndex[35] = 7   ;
    iIndex[36] = 9   ; jIndex[36] = 8   ;
    iIndex[37] = 9   ; jIndex[37] = 9   ;
    iIndex[38] = 10  ; jIndex[38] = 0   ;
    iIndex[39] = 10  ; jIndex[39] = 5   ;
    iIndex[40] = 10  ; jIndex[40] = 10  ;
  }


  void
  OrbitTransfer::D2fd_odeD2xxup_sparse(
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
    real_type QM__[1], XM__[5], V__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    V__[2] = __INV_DZETA*(XR__[2]-XL__[2]);
    V__[3] = __INV_DZETA*(XR__[3]-XL__[3]);
    V__[4] = __INV_DZETA*(XR__[4]-XL__[4]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = t2 * LM__[1];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = UM__[0];
    real_type t6   = sin(t5);
    real_type t7   = t6 * t4;
    real_type t11  = XR__[iX_m] / 2 + XL__[iX_m] / 2;
    real_type t12  = t11 * t11;
    real_type t14  = 1.0 / t12 / t11;
    real_type t18  = t2 * LM__[2];
    real_type t19  = cos(t5);
    real_type t20  = t19 * t4;
    result__[ 0   ] = -t14 * t20 * t18 / 2 - t14 * t7 * t3 / 2;
    result__[ 1   ] = result__[0];
    real_type t24  = 1.0 / t12;
    result__[ 2   ] = -t24 * t7 * t18 / 2 + t24 * t20 * t3 / 2;
    real_type t33  = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t34  = t33 * t33;
    real_type t38  = XR__[iX_r] / 2 + XL__[iX_r] / 2;
    real_type t39  = t38 * t38;
    real_type t41  = 1.0 / t39 / t38;
    real_type t45  = t39 * t39;
    real_type t54  = XR__[iX_u] / 2 + XL__[iX_u] / 2;
    real_type t60  = t2 * LM__[4];
    result__[ 3   ] = -(t41 * t34 / 2 - 3.0 / 2.0 / t45 * ModelPars[iM_mu]) * t3 + t41 * t54 * t33 * t18 / 2 - t41 * t33 * t60 / 2;
    real_type t64  = 1.0 / t39;
    real_type t65  = t64 * t33;
    result__[ 4   ] = -t65 * t18 / 4;
    result__[ 5   ] = t65 * t3 / 2 - t64 * t54 * t18 / 4 + t64 * t60 / 4;
    result__[ 6   ] = result__[3];
    result__[ 7   ] = result__[4];
    result__[ 8   ] = result__[5];
    result__[ 9   ] = result__[7];
    real_type t75  = 1.0 / t38;
    result__[ 10  ] = t75 * t18 / 4;
    result__[ 11  ] = result__[9];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = result__[8];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = -t75 * t3 / 2;
    result__[ 16  ] = result__[13];
    result__[ 17  ] = result__[14];
    result__[ 18  ] = result__[15];
    result__[ 19  ] = result__[1];
    result__[ 20  ] = result__[19];
    result__[ 21  ] = result__[2];
    result__[ 22  ] = result__[6];
    result__[ 23  ] = result__[11];
    result__[ 24  ] = result__[16];
    result__[ 25  ] = result__[22];
    result__[ 26  ] = result__[23];
    result__[ 27  ] = result__[24];
    result__[ 28  ] = result__[26];
    result__[ 29  ] = result__[17];
    result__[ 30  ] = result__[28];
    result__[ 31  ] = result__[29];
    result__[ 32  ] = result__[27];
    result__[ 33  ] = result__[31];
    result__[ 34  ] = result__[18];
    result__[ 35  ] = result__[32];
    result__[ 36  ] = result__[33];
    result__[ 37  ] = result__[34];
    result__[ 38  ] = result__[21];
    result__[ 39  ] = result__[38];
    real_type t79  = 1.0 / t11;
    result__[ 40  ] = t79 * t20 * t18 + t79 * t7 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 41, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: OrbitTransfer_Methods_Guess.cc
