/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_Guess.cc                            |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_max_DD(__t1) x2bound_max.DD( __t1)
#define ALIAS_x2bound_max_D(__t1) x2bound_max.D( __t1)
#define ALIAS_x2bound_min_DD(__t1) x2bound_min.DD( __t1)
#define ALIAS_x2bound_min_D(__t1) x2bound_min.D( __t1)
#define ALIAS_x1bound_max_DD(__t1) x1bound_max.DD( __t1)
#define ALIAS_x1bound_max_D(__t1) x1bound_max.D( __t1)
#define ALIAS_x1bound_min_DD(__t1) x1bound_min.DD( __t1)
#define ALIAS_x1bound_min_D(__t1) x1bound_min.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
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

namespace ICLOCS_StirredTankDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer ICLOCS_StirredTank::fd_ode_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::fd_ode_eval(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_TimeSize];
    real_type t3   = XM__[0];
    real_type t6   = 1.0 / ModelPars[iM_theta];
    real_type t11  = XM__[1];
    real_type t14  = exp(-1.0 / t11 * ModelPars[iM_En]);
    real_type t15  = t14 * t3 * ModelPars[iM_k];
    result__[ 0   ] = V__[0] - (t6 * (1 - t3) - t15) * t2;
    result__[ 1   ] = V__[1] - (t6 * (ModelPars[iM_Tf] - t11) + t15 - (t11 - ModelPars[iM_Tc]) * UM__[0] * ModelPars[iM_a]) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::Dfd_odeDxxpu_numRows() const { return 2; }
  integer ICLOCS_StirredTank::Dfd_odeDxxpu_numCols() const { return 6; }
  integer ICLOCS_StirredTank::Dfd_odeDxxpu_nnz()     const { return 11; }

  void
  ICLOCS_StirredTank::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
  }


  void
  ICLOCS_StirredTank::Dfd_odeDxxpu_sparse(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t3   = 1.0 / ModelPars[iM_theta];
    real_type t4   = ModelPars[iM_k];
    real_type t5   = ModelPars[iM_En];
    real_type t6   = XM__[1];
    real_type t9   = exp(-1.0 / t6 * t5);
    real_type t13  = 0.5e0 * (-t9 * t4 - t3) * t1;
    result__[ 0   ] = -t13 - __INV_DZETA;
    real_type t14  = t4 * t1;
    real_type t15  = XM__[0];
    real_type t17  = t6 * t6;
    real_type t20  = t9 / t17 * t5;
    result__[ 1   ] = 0.5e0 * t20 * t15 * t14;
    result__[ 2   ] = -t13 + __INV_DZETA;
    result__[ 3   ] = result__[1];
    real_type t24  = t15 * t4;
    real_type t25  = t9 * t24;
    result__[ 4   ] = -t3 * (1 - t15) + t25;
    result__[ 5   ] = -0.5e0 * t9 * t14;
    real_type t29  = ModelPars[iM_a];
    real_type t31  = UM__[0] * t29;
    real_type t34  = 0.5e0 * (t20 * t24 - t3 - t31) * t1;
    result__[ 6   ] = -t34 - __INV_DZETA;
    result__[ 7   ] = result__[5];
    result__[ 8   ] = -t34 + __INV_DZETA;
    real_type t37  = t6 - ModelPars[iM_Tc];
    result__[ 9   ] = t37 * t29 * t1;
    result__[ 10  ] = -t3 * (ModelPars[iM_Tf] - t6) - t25 + t37 * t31;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 11, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::D2fd_odeD2xxpu_numRows() const { return 6; }
  integer ICLOCS_StirredTank::D2fd_odeD2xxpu_numCols() const { return 6; }
  integer ICLOCS_StirredTank::D2fd_odeD2xxpu_nnz()     const { return 26; }

  void
  ICLOCS_StirredTank::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 2   ; jIndex[11] = 5   ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
    iIndex[16] = 3   ; jIndex[16] = 4   ;
    iIndex[17] = 3   ; jIndex[17] = 5   ;
    iIndex[18] = 4   ; jIndex[18] = 1   ;
    iIndex[19] = 4   ; jIndex[19] = 3   ;
    iIndex[20] = 4   ; jIndex[20] = 5   ;
    iIndex[21] = 5   ; jIndex[21] = 0   ;
    iIndex[22] = 5   ; jIndex[22] = 1   ;
    iIndex[23] = 5   ; jIndex[23] = 2   ;
    iIndex[24] = 5   ; jIndex[24] = 3   ;
    iIndex[25] = 5   ; jIndex[25] = 4   ;
  }


  void
  ICLOCS_StirredTank::D2fd_odeD2xxpu_sparse(
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
    real_type QM__[1], XM__[2], V__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    real_type __INV_DZETA = 1/(QR__[0] - QL__[0]);
    // Vvars
    V__[0] = __INV_DZETA*(XR__[0]-XL__[0]);
    V__[1] = __INV_DZETA*(XR__[1]-XL__[1]);
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_TimeSize];
    real_type t4   = ModelPars[iM_k];
    real_type t5   = t4 * t2 * t1;
    real_type t6   = ModelPars[iM_En];
    real_type t7   = XR__[iX_x2];
    real_type t8   = XL__[iX_x2];
    real_type t10  = t7 / 2 + t8 / 2;
    real_type t11  = t10 * t10;
    real_type t16  = exp(-1.0 / t10 * t6);
    real_type t17  = t16 / t11 * t6;
    real_type t19  = LM__[1];
    real_type t20  = t2 * t19;
    result__[ 0   ] = -t17 * t4 * t20 / 4 + t17 * t5 / 4;
    result__[ 1   ] = result__[0];
    real_type t25  = 1.0 / ModelPars[iM_theta];
    result__[ 2   ] = -(-t16 * t4 / 2 - t25 / 2) * t1 - t16 * t4 * t19 / 2;
    result__[ 3   ] = result__[1];
    real_type t36  = XR__[iX_x1] / 2 + XL__[iX_x1] / 2;
    real_type t39  = 1.0 / t11 / t10;
    real_type t44  = t6 * t6;
    real_type t46  = t11 * t11;
    real_type t47  = 1.0 / t46;
    real_type t52  = t36 * t4;
    result__[ 4   ] = -t16 * t39 * t6 * t36 * t5 / 2 + t16 * t47 * t44 * t36 * t5 / 4 - (-t16 * t39 * t6 * t52 / 2 + t16 * t47 * t44 * t52 / 4) * t20;
    result__[ 5   ] = result__[3];
    result__[ 6   ] = result__[4];
    real_type t63  = ModelPars[iM_a];
    result__[ 7   ] = t63 * t20 / 2;
    result__[ 8   ] = t17 * t36 * t4 * t1 / 2 - (t17 * t52 / 2 - UM__[0] * t63 / 2 - t25 / 2) * t19;
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[9];
    result__[ 11  ] = result__[2];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = result__[6];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[13];
    result__[ 16  ] = result__[7];
    result__[ 17  ] = result__[8];
    result__[ 18  ] = result__[16];
    result__[ 19  ] = result__[18];
    result__[ 20  ] = (t7 / 2 + t8 / 2 - ModelPars[iM_Tc]) * t63 * t19;
    result__[ 21  ] = result__[11];
    result__[ 22  ] = result__[17];
    result__[ 23  ] = result__[21];
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[20];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 26, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: ICLOCS_StirredTank_Methods_Guess.cc
