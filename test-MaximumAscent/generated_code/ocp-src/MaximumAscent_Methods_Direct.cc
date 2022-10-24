/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods_Guess.cc                                 |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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

namespace MaximumAscentDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer MaximumAscent::fd_ode_numEqns() const { return 4; }

  void
  MaximumAscent::fd_ode_eval(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t6   = XM__[1] * t4;
    result__[ 0   ] = V__[0] - t6;
    real_type t8   = XM__[2];
    real_type t9   = t8 * t8;
    real_type t10  = XM__[0];
    real_type t11  = 1.0 / t10;
    real_type t13  = t10 * t10;
    real_type t17  = Tbar(t3);
    real_type t25  = 1.0 / (-QM__[0] * ModelPars[iM_mdot] * t3 + ModelPars[iM_m0]) * t17;
    real_type t26  = UM__[0];
    real_type t27  = sin(t26);
    result__[ 1   ] = V__[1] - (t11 * t9 - 1.0 / t13) * t4 - t27 * t25;
    real_type t32  = cos(t26);
    result__[ 2   ] = t11 * t8 * t6 - t32 * t25 + V__[2];
    result__[ 3   ] = -t11 * t8 * t4 + V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::Dfd_odeDxxpu_numRows() const { return 4; }
  integer MaximumAscent::Dfd_odeDxxpu_numCols() const { return 9; }
  integer MaximumAscent::Dfd_odeDxxpu_nnz()     const { return 24; }

  void
  MaximumAscent::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 1   ; jIndex[10] = 8   ;
    iIndex[11] = 2   ; jIndex[11] = 0   ;
    iIndex[12] = 2   ; jIndex[12] = 1   ;
    iIndex[13] = 2   ; jIndex[13] = 2   ;
    iIndex[14] = 2   ; jIndex[14] = 4   ;
    iIndex[15] = 2   ; jIndex[15] = 5   ;
    iIndex[16] = 2   ; jIndex[16] = 6   ;
    iIndex[17] = 2   ; jIndex[17] = 8   ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 2   ;
    iIndex[20] = 3   ; jIndex[20] = 3   ;
    iIndex[21] = 3   ; jIndex[21] = 4   ;
    iIndex[22] = 3   ; jIndex[22] = 6   ;
    iIndex[23] = 3   ; jIndex[23] = 7   ;
  }


  void
  MaximumAscent::Dfd_odeDxxpu_sparse(
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
    real_type t2   = tf(ModelPars[iM_days]);
    real_type t3   = eta(t2);
    result__[ 1   ] = -0.5e0 * t3;
    result__[ 2   ] = __INV_DZETA;
    result__[ 3   ] = result__[1];
    real_type t5   = XM__[2];
    real_type t6   = t5 * t5;
    real_type t7   = XM__[0];
    real_type t8   = t7 * t7;
    real_type t9   = 1.0 / t8;
    result__[ 4   ] = -0.5e0 * (-t9 * t6 + 2 / t8 / t7) * t3;
    result__[ 5   ] = result__[0];
    real_type t17  = t5 * t3;
    real_type t18  = 1.0 / t7;
    real_type t19  = t18 * t17;
    result__[ 6   ] = -0.10e1 * t19;
    result__[ 7   ] = result__[4];
    result__[ 8   ] = __INV_DZETA;
    result__[ 9   ] = result__[6];
    real_type t21  = Tbar(t2);
    real_type t29  = 1.0 / (-QM__[0] * ModelPars[iM_mdot] * t2 + ModelPars[iM_m0]) * t21;
    real_type t30  = UM__[0];
    real_type t31  = cos(t30);
    result__[ 10  ] = -t31 * t29;
    real_type t34  = XM__[1] * t3;
    result__[ 11  ] = -0.5e0 * t9 * t5 * t34;
    result__[ 12  ] = 0.5e0 * t19;
    real_type t39  = 0.5e0 * t18 * t34;
    result__[ 13  ] = t39 + result__[5];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = result__[12];
    result__[ 16  ] = t39 + __INV_DZETA;
    real_type t40  = sin(t30);
    result__[ 17  ] = t40 * t29;
    result__[ 18  ] = 0.5e0 * t9 * t17;
    result__[ 19  ] = -0.5e0 * t18 * t3;
    result__[ 20  ] = result__[5];
    result__[ 21  ] = result__[18];
    result__[ 22  ] = result__[19];
    result__[ 23  ] = __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::D2fd_odeD2xxpu_numRows() const { return 9; }
  integer MaximumAscent::D2fd_odeD2xxpu_numCols() const { return 9; }
  integer MaximumAscent::D2fd_odeD2xxpu_nnz()     const { return 33; }

  void
  MaximumAscent::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 6   ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 1   ;
    iIndex[12] = 2   ; jIndex[12] = 2   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 5   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 4   ; jIndex[16] = 0   ;
    iIndex[17] = 4   ; jIndex[17] = 1   ;
    iIndex[18] = 4   ; jIndex[18] = 2   ;
    iIndex[19] = 4   ; jIndex[19] = 4   ;
    iIndex[20] = 4   ; jIndex[20] = 5   ;
    iIndex[21] = 4   ; jIndex[21] = 6   ;
    iIndex[22] = 5   ; jIndex[22] = 0   ;
    iIndex[23] = 5   ; jIndex[23] = 2   ;
    iIndex[24] = 5   ; jIndex[24] = 4   ;
    iIndex[25] = 5   ; jIndex[25] = 6   ;
    iIndex[26] = 6   ; jIndex[26] = 0   ;
    iIndex[27] = 6   ; jIndex[27] = 1   ;
    iIndex[28] = 6   ; jIndex[28] = 2   ;
    iIndex[29] = 6   ; jIndex[29] = 4   ;
    iIndex[30] = 6   ; jIndex[30] = 5   ;
    iIndex[31] = 6   ; jIndex[31] = 6   ;
    iIndex[32] = 8   ; jIndex[32] = 8   ;
  }


  void
  MaximumAscent::D2fd_odeD2xxpu_sparse(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t5   = t4 * t1;
    real_type t9   = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t10  = t9 * t9;
    real_type t14  = XR__[iX_r] / 2 + XL__[iX_r] / 2;
    real_type t15  = t14 * t14;
    real_type t17  = 1.0 / t15 / t14;
    real_type t20  = t15 * t15;
    real_type t25  = LM__[2];
    real_type t26  = t4 * t25;
    real_type t30  = XR__[iX_u] / 2 + XL__[iX_u] / 2;
    real_type t36  = t4 * LM__[3];
    result__[ 0   ] = -(t17 * t10 / 2 - 3.0 / 2.0 / t20) * t5 + t17 * t9 * t30 * t26 / 2 - t17 * t9 * t36 / 2;
    real_type t40  = 1.0 / t15;
    real_type t41  = t40 * t9;
    result__[ 1   ] = -t41 * t26 / 4;
    result__[ 2   ] = t41 * t5 / 2 - t40 * t30 * t26 / 4 + t40 * t36 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    real_type t51  = 1.0 / t14;
    result__[ 7   ] = t51 * t26 / 4;
    result__[ 8   ] = result__[6];
    result__[ 9   ] = result__[7];
    result__[ 10  ] = result__[5];
    result__[ 11  ] = result__[9];
    result__[ 12  ] = -t51 * t5 / 2;
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
    real_type t55  = Tbar(t3);
    real_type t63  = 1.0 / (-QM__[0] * ModelPars[iM_mdot] * t3 + ModelPars[iM_m0]);
    real_type t64  = UM__[0];
    real_type t65  = sin(t64);
    real_type t69  = cos(t64);
    result__[ 32  ] = t65 * t63 * t55 * t1 + t69 * t63 * t55 * t25;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 33, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: MaximumAscent_Methods_Guess.cc
