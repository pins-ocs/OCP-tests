/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Methods_Guess.cc                           |
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


#include "EconomicGrowthModel.hh"
#include "EconomicGrowthModel_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace EconomicGrowthModelDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer EconomicGrowthModel::fd_ode_numEqns() const { return 3; }

  void
  EconomicGrowthModel::fd_ode_eval(
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
    real_type t2   = UM__[0];
    real_type t5   = Q(XM__[0], XM__[1]);
    real_type t7   = XM__[2];
    result__[ 0   ] = -t7 * t5 * t2 + V__[0];
    result__[ 1   ] = V__[1] - t7 * t5 * (1 - t2);
    result__[ 2   ] = V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::Dfd_odeDxxup_numRows() const { return 3; }
  integer EconomicGrowthModel::Dfd_odeDxxup_numCols() const { return 7; }
  integer EconomicGrowthModel::Dfd_odeDxxup_nnz()     const { return 16; }

  void
  EconomicGrowthModel::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 2   ; jIndex[14] = 2   ;
    iIndex[15] = 2   ; jIndex[15] = 5   ;
  }


  void
  EconomicGrowthModel::Dfd_odeDxxup_sparse(
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
    real_type t1   = UM__[0];
    real_type t2   = XM__[0];
    real_type t3   = XM__[1];
    real_type t4   = Q_D_1(t2, t3);
    real_type t6   = XM__[2];
    real_type t8   = 0.5e0 * t6 * t4 * t1;
    result__[ 0   ] = -t8 - __INV_DZETA;
    real_type t9   = Q_D_2(t2, t3);
    result__[ 1   ] = -0.5e0 * t6 * t9 * t1;
    real_type t13  = Q(t2, t3);
    result__[ 2   ] = -0.5e0 * t13 * t1;
    result__[ 3   ] = -t8 + __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t16  = t6 * t13;
    result__[ 6   ] = -t16;
    real_type t17  = 1 - t1;
    result__[ 7   ] = -0.5e0 * t6 * t4 * t17;
    real_type t23  = 0.5e0 * t6 * t9 * t17;
    result__[ 8   ] = -t23 - __INV_DZETA;
    result__[ 9   ] = -0.5e0 * t13 * t17;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = -t23 + __INV_DZETA;
    result__[ 12  ] = result__[9];
    result__[ 13  ] = t16;
    result__[ 14  ] = -__INV_DZETA;
    result__[ 15  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::D2fd_odeD2xxup_numRows() const { return 7; }
  integer EconomicGrowthModel::D2fd_odeD2xxup_numCols() const { return 7; }
  integer EconomicGrowthModel::D2fd_odeD2xxup_nnz()     const { return 44; }

  void
  EconomicGrowthModel::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 3   ;
    iIndex[17] = 2   ; jIndex[17] = 4   ;
    iIndex[18] = 2   ; jIndex[18] = 6   ;
    iIndex[19] = 3   ; jIndex[19] = 0   ;
    iIndex[20] = 3   ; jIndex[20] = 1   ;
    iIndex[21] = 3   ; jIndex[21] = 2   ;
    iIndex[22] = 3   ; jIndex[22] = 3   ;
    iIndex[23] = 3   ; jIndex[23] = 4   ;
    iIndex[24] = 3   ; jIndex[24] = 5   ;
    iIndex[25] = 3   ; jIndex[25] = 6   ;
    iIndex[26] = 4   ; jIndex[26] = 0   ;
    iIndex[27] = 4   ; jIndex[27] = 1   ;
    iIndex[28] = 4   ; jIndex[28] = 2   ;
    iIndex[29] = 4   ; jIndex[29] = 3   ;
    iIndex[30] = 4   ; jIndex[30] = 4   ;
    iIndex[31] = 4   ; jIndex[31] = 5   ;
    iIndex[32] = 4   ; jIndex[32] = 6   ;
    iIndex[33] = 5   ; jIndex[33] = 0   ;
    iIndex[34] = 5   ; jIndex[34] = 1   ;
    iIndex[35] = 5   ; jIndex[35] = 3   ;
    iIndex[36] = 5   ; jIndex[36] = 4   ;
    iIndex[37] = 5   ; jIndex[37] = 6   ;
    iIndex[38] = 6   ; jIndex[38] = 0   ;
    iIndex[39] = 6   ; jIndex[39] = 1   ;
    iIndex[40] = 6   ; jIndex[40] = 2   ;
    iIndex[41] = 6   ; jIndex[41] = 3   ;
    iIndex[42] = 6   ; jIndex[42] = 4   ;
    iIndex[43] = 6   ; jIndex[43] = 5   ;
  }


  void
  EconomicGrowthModel::D2fd_odeD2xxup_sparse(
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
    real_type t2   = UM__[0];
    real_type t3   = t2 * t1;
    real_type t7   = XR__[iX_x1] / 2 + XL__[iX_x1] / 2;
    real_type t11  = XR__[iX_x2] / 2 + XL__[iX_x2] / 2;
    real_type t12  = Q_D_1_1(t7, t11);
    real_type t16  = XR__[iX_T] / 2 + XL__[iX_T] / 2;
    real_type t17  = t16 * t12;
    real_type t19  = LM__[1];
    real_type t21  = (1 - t2) * t19;
    result__[ 0   ] = -t17 * t21 / 4 - t17 * t3 / 4;
    real_type t24  = Q_D_1_2(t7, t11);
    real_type t25  = t16 * t24;
    result__[ 1   ] = -t25 * t21 / 4 - t25 * t3 / 4;
    real_type t29  = Q_D_1(t7, t11);
    result__[ 2   ] = -t29 * t21 / 4 - t29 * t3 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = -t16 * t29 * t1 / 2 + t16 * t29 * t19 / 2;
    result__[ 7   ] = result__[4];
    real_type t38  = Q_D_2_2(t7, t11);
    real_type t39  = t16 * t38;
    result__[ 8   ] = -t39 * t21 / 4 - t39 * t3 / 4;
    real_type t43  = Q_D_2(t7, t11);
    result__[ 9   ] = -t43 * t21 / 4 - t43 * t3 / 4;
    result__[ 10  ] = result__[7];
    result__[ 11  ] = result__[8];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = -t16 * t43 * t1 / 2 + t16 * t43 * t19 / 2;
    result__[ 14  ] = result__[5];
    result__[ 15  ] = result__[12];
    result__[ 16  ] = result__[14];
    result__[ 17  ] = result__[15];
    real_type t52  = Q(t7, t11);
    result__[ 18  ] = -t52 * t1 / 2 + t52 * t19 / 2;
    result__[ 19  ] = result__[3];
    result__[ 20  ] = result__[10];
    result__[ 21  ] = result__[16];
    result__[ 22  ] = result__[19];
    result__[ 23  ] = result__[20];
    result__[ 24  ] = result__[21];
    result__[ 25  ] = result__[6];
    result__[ 26  ] = result__[23];
    result__[ 27  ] = result__[11];
    result__[ 28  ] = result__[17];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[27];
    result__[ 31  ] = result__[28];
    result__[ 32  ] = result__[13];
    result__[ 33  ] = result__[24];
    result__[ 34  ] = result__[31];
    result__[ 35  ] = result__[33];
    result__[ 36  ] = result__[34];
    result__[ 37  ] = result__[18];
    result__[ 38  ] = result__[25];
    result__[ 39  ] = result__[32];
    result__[ 40  ] = result__[37];
    result__[ 41  ] = result__[38];
    result__[ 42  ] = result__[39];
    result__[ 43  ] = result__[40];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 44, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: EconomicGrowthModel_Methods_Guess.cc
