/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_Guess.cc                |
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


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

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

namespace ICLOCS_MinimumFuelOrbitRaisingDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer ICLOCS_MinimumFuelOrbitRaising::fd_ode_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::fd_ode_eval(
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
    real_type t2   = XM__[1];
    result__[ 0   ] = V__[0] - t2;
    real_type t4   = XM__[2];
    real_type t5   = t4 * t4;
    real_type t6   = XM__[0];
    real_type t7   = 1.0 / t6;
    real_type t9   = t6 * t6;
    real_type t11  = ModelPars[iM_T];
    real_type t12  = UM__[0];
    real_type t13  = sin(t12);
    real_type t16  = mass(QM__[0]);
    real_type t17  = 1.0 / t16;
    result__[ 1   ] = V__[1] - t7 * t5 + 1.0 / t9 - t17 * t13 * t11;
    real_type t22  = cos(t12);
    result__[ 2   ] = -t17 * t22 * t11 + t7 * t4 * t2 + V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::Dfd_odeDxxup_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::Dfd_odeDxxup_numCols() const { return 7; }
  integer ICLOCS_MinimumFuelOrbitRaising::Dfd_odeDxxup_nnz()     const { return 18; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 2   ; jIndex[11] = 0   ;
    iIndex[12] = 2   ; jIndex[12] = 1   ;
    iIndex[13] = 2   ; jIndex[13] = 2   ;
    iIndex[14] = 2   ; jIndex[14] = 3   ;
    iIndex[15] = 2   ; jIndex[15] = 4   ;
    iIndex[16] = 2   ; jIndex[16] = 5   ;
    iIndex[17] = 2   ; jIndex[17] = 6   ;
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::Dfd_odeDxxup_sparse(
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
    result__[ 1   ] = -0.5e0;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = -0.5e0;
    real_type t1   = XM__[2];
    real_type t2   = t1 * t1;
    real_type t3   = XM__[0];
    real_type t4   = t3 * t3;
    real_type t5   = 1.0 / t4;
    result__[ 4   ] = 0.5e0 * t5 * t2 - 0.10e1 / t4 / t3;
    result__[ 5   ] = result__[0];
    real_type t11  = 1.0 / t3;
    real_type t12  = t11 * t1;
    result__[ 6   ] = -0.10e1 * t12;
    result__[ 7   ] = result__[4];
    result__[ 8   ] = __INV_DZETA;
    result__[ 9   ] = result__[6];
    real_type t14  = ModelPars[iM_T];
    real_type t15  = UM__[0];
    real_type t16  = cos(t15);
    real_type t19  = mass(QM__[0]);
    real_type t20  = 1.0 / t19;
    result__[ 10  ] = -t20 * t16 * t14;
    real_type t22  = XM__[1];
    result__[ 11  ] = -0.5e0 * t5 * t1 * t22;
    result__[ 12  ] = 0.5e0 * t12;
    real_type t27  = 0.5e0 * t11 * t22;
    result__[ 13  ] = t27 + result__[5];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = result__[12];
    result__[ 16  ] = t27 + __INV_DZETA;
    real_type t28  = sin(t15);
    result__[ 17  ] = t20 * t28 * t14;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 18, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::D2fd_odeD2xxup_numRows() const { return 7; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2fd_odeD2xxup_numCols() const { return 7; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2fd_odeD2xxup_nnz()     const { return 33; }

  void
  ICLOCS_MinimumFuelOrbitRaising::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 3   ;
    iIndex[14] = 2   ; jIndex[14] = 4   ;
    iIndex[15] = 2   ; jIndex[15] = 5   ;
    iIndex[16] = 3   ; jIndex[16] = 0   ;
    iIndex[17] = 3   ; jIndex[17] = 1   ;
    iIndex[18] = 3   ; jIndex[18] = 2   ;
    iIndex[19] = 3   ; jIndex[19] = 3   ;
    iIndex[20] = 3   ; jIndex[20] = 4   ;
    iIndex[21] = 3   ; jIndex[21] = 5   ;
    iIndex[22] = 4   ; jIndex[22] = 0   ;
    iIndex[23] = 4   ; jIndex[23] = 2   ;
    iIndex[24] = 4   ; jIndex[24] = 3   ;
    iIndex[25] = 4   ; jIndex[25] = 5   ;
    iIndex[26] = 5   ; jIndex[26] = 0   ;
    iIndex[27] = 5   ; jIndex[27] = 1   ;
    iIndex[28] = 5   ; jIndex[28] = 2   ;
    iIndex[29] = 5   ; jIndex[29] = 3   ;
    iIndex[30] = 5   ; jIndex[30] = 4   ;
    iIndex[31] = 5   ; jIndex[31] = 5   ;
    iIndex[32] = 6   ; jIndex[32] = 6   ;
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::D2fd_odeD2xxup_sparse(
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
    real_type t1   = LM__[1];
    real_type t5   = XR__[iX_vt] / 2 + XL__[iX_vt] / 2;
    real_type t6   = t5 * t5;
    real_type t10  = XR__[iX_r] / 2 + XL__[iX_r] / 2;
    real_type t11  = t10 * t10;
    real_type t13  = 1.0 / t11 / t10;
    real_type t16  = t11 * t11;
    real_type t21  = LM__[2];
    real_type t26  = (XR__[iX_vr] / 2 + XL__[iX_vr] / 2) * t21;
    result__[ 0   ] = (-t13 * t6 / 2 + 3.0 / 2.0 / t16) * t1 + t13 * t5 * t26 / 2;
    real_type t31  = 1.0 / t11;
    result__[ 1   ] = -t31 * t5 * t21 / 4;
    result__[ 2   ] = t31 * t5 * t1 / 2 - t31 * t26 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    real_type t39  = 1.0 / t10;
    result__[ 7   ] = t39 * t21 / 4;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = result__[7];
    result__[ 10  ] = result__[5];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = -t39 * t1 / 2;
    result__[ 13  ] = result__[10];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = result__[12];
    result__[ 16  ] = result__[3];
    result__[ 17  ] = result__[8];
    result__[ 18  ] = result__[13];
    result__[ 19  ] = result__[16];
    result__[ 20  ] = result__[17];
    result__[ 21  ] = result__[18];
    result__[ 22  ] = result__[20];
    result__[ 23  ] = result__[14];
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[23];
    result__[ 26  ] = result__[21];
    result__[ 27  ] = result__[25];
    result__[ 28  ] = result__[15];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[28];
    real_type t43  = ModelPars[iM_T];
    real_type t45  = UM__[0];
    real_type t46  = sin(t45);
    real_type t48  = mass(QM__[0]);
    real_type t49  = 1.0 / t48;
    real_type t53  = cos(t45);
    result__[ 32  ] = t49 * t46 * t43 * t1 + t49 * t53 * t43 * t21;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 33, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_Guess.cc
