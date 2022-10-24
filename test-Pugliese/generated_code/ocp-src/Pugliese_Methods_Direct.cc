/*-----------------------------------------------------------------------*\
 |  file: Pugliese_Methods_Guess.cc                                      |
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


#include "Pugliese.hh"
#include "Pugliese_Pars.hh"

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

namespace PuglieseDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer Pugliese::fd_ode_numEqns() const { return 5; }

  void
  Pugliese::fd_ode_eval(
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
    real_type t3   = XM__[0];
    real_type t9   = XM__[1];
    real_type t10  = T_lim(t3);
    real_type t13  = XM__[4];
    result__[ 0   ] = V__[0] - (1 - 1.0 / ModelPars[iM_K] * t3) * ModelPars[iM_r] + t10 * t9 + t3 * t9 * t13 * ModelPars[iM_kappa__AC];
    real_type t18  = XM__[3];
    real_type t19  = D_lim(t18);
    real_type t21  = IL(t3, t9);
    real_type t22  = IL_lim(t21);
    real_type t24  = XM__[2];
    result__[ 1   ] = V__[1] - t19 + (t24 * ModelPars[iM_kappa__R] + t22 + ModelPars[iM_mu__C]) * t9;
    result__[ 2   ] = -t18 * ModelPars[iM_a__R] - t21 * ModelPars[iM_a__IL] + t24 * ModelPars[iM_mu__R] + V__[2];
    result__[ 3   ] = ModelPars[iM_mu__D] * t18 + V__[3] - ModelPars[iM_rho__D];
    result__[ 4   ] = ModelPars[iM_lambda] * t13 + V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::Dfd_odeDxxpu_numRows() const { return 5; }
  integer Pugliese::Dfd_odeDxxpu_numCols() const { return 10; }
  integer Pugliese::Dfd_odeDxxpu_nnz()     const { return 26; }

  void
  Pugliese::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 3   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 1   ; jIndex[13] = 8   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 3   ;
    iIndex[18] = 2   ; jIndex[18] = 5   ;
    iIndex[19] = 2   ; jIndex[19] = 6   ;
    iIndex[20] = 2   ; jIndex[20] = 7   ;
    iIndex[21] = 2   ; jIndex[21] = 8   ;
    iIndex[22] = 3   ; jIndex[22] = 3   ;
    iIndex[23] = 3   ; jIndex[23] = 8   ;
    iIndex[24] = 4   ; jIndex[24] = 4   ;
    iIndex[25] = 4   ; jIndex[25] = 9   ;
  }


  void
  Pugliese::Dfd_odeDxxpu_sparse(
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
    real_type t5   = 0.5e0 * ModelPars[iM_r] / ModelPars[iM_K];
    real_type t6   = XM__[1];
    real_type t7   = XM__[0];
    real_type t8   = T_lim_D(t7);
    real_type t10  = 0.5e0 * t8 * t6;
    real_type t11  = ModelPars[iM_kappa__AC];
    real_type t13  = XM__[4] * t11;
    real_type t15  = 0.5e0 * t6 * t13;
    result__[ 0   ] = t5 + t10 + t15 - __INV_DZETA;
    real_type t16  = T_lim(t7);
    result__[ 1   ] = 0.5e0 * t16 + 0.5e0 * t7 * t13;
    result__[ 2   ] = 0.5e0 * t7 * t6 * t11;
    result__[ 3   ] = t5 + t10 + t15 + __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t22  = IL(t7, t6);
    real_type t23  = IL_lim_D(t22);
    real_type t24  = t23 * t6;
    real_type t25  = IL_D_1(t7, t6);
    result__[ 6   ] = 0.5e0 * t25 * t24;
    real_type t28  = 0.5e0 * ModelPars[iM_mu__C];
    real_type t29  = IL_lim(t22);
    real_type t30  = 0.5e0 * t29;
    real_type t31  = ModelPars[iM_kappa__R];
    real_type t34  = 0.5e0 * XM__[2] * t31;
    real_type t35  = IL_D_2(t7, t6);
    real_type t37  = 0.5e0 * t35 * t24;
    result__[ 7   ] = t28 + t30 + t34 + t37 - __INV_DZETA;
    result__[ 8   ] = 0.5e0 * t31 * t6;
    real_type t40  = D_lim_D(XM__[3]);
    result__[ 9   ] = -0.5e0 * t40;
    result__[ 10  ] = result__[6];
    result__[ 11  ] = t28 + t30 + t34 + t37 + __INV_DZETA;
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    real_type t42  = ModelPars[iM_a__IL];
    result__[ 14  ] = -0.5e0 * t25 * t42;
    result__[ 15  ] = -0.5e0 * t35 * t42;
    real_type t48  = 0.5e0 * ModelPars[iM_mu__R];
    result__[ 16  ] = t48 - __INV_DZETA;
    result__[ 17  ] = -0.5e0 * ModelPars[iM_a__R];
    result__[ 18  ] = result__[14];
    result__[ 19  ] = result__[15];
    result__[ 20  ] = t48 + __INV_DZETA;
    result__[ 21  ] = result__[17];
    real_type t52  = 0.5e0 * ModelPars[iM_mu__D];
    result__[ 22  ] = t52 - __INV_DZETA;
    result__[ 23  ] = t52 + __INV_DZETA;
    real_type t54  = 0.5e0 * ModelPars[iM_lambda];
    result__[ 24  ] = t54 - __INV_DZETA;
    result__[ 25  ] = t54 + __INV_DZETA;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 26, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Pugliese::D2fd_odeD2xxpu_numRows() const { return 10; }
  integer Pugliese::D2fd_odeD2xxpu_numCols() const { return 10; }
  integer Pugliese::D2fd_odeD2xxpu_nnz()     const { return 44; }

  void
  Pugliese::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 7   ;
    iIndex[13] = 1   ; jIndex[13] = 9   ;
    iIndex[14] = 2   ; jIndex[14] = 1   ;
    iIndex[15] = 2   ; jIndex[15] = 6   ;
    iIndex[16] = 3   ; jIndex[16] = 3   ;
    iIndex[17] = 3   ; jIndex[17] = 8   ;
    iIndex[18] = 4   ; jIndex[18] = 0   ;
    iIndex[19] = 4   ; jIndex[19] = 1   ;
    iIndex[20] = 4   ; jIndex[20] = 5   ;
    iIndex[21] = 4   ; jIndex[21] = 6   ;
    iIndex[22] = 5   ; jIndex[22] = 0   ;
    iIndex[23] = 5   ; jIndex[23] = 1   ;
    iIndex[24] = 5   ; jIndex[24] = 4   ;
    iIndex[25] = 5   ; jIndex[25] = 5   ;
    iIndex[26] = 5   ; jIndex[26] = 6   ;
    iIndex[27] = 5   ; jIndex[27] = 9   ;
    iIndex[28] = 6   ; jIndex[28] = 0   ;
    iIndex[29] = 6   ; jIndex[29] = 1   ;
    iIndex[30] = 6   ; jIndex[30] = 2   ;
    iIndex[31] = 6   ; jIndex[31] = 4   ;
    iIndex[32] = 6   ; jIndex[32] = 5   ;
    iIndex[33] = 6   ; jIndex[33] = 6   ;
    iIndex[34] = 6   ; jIndex[34] = 7   ;
    iIndex[35] = 6   ; jIndex[35] = 9   ;
    iIndex[36] = 7   ; jIndex[36] = 1   ;
    iIndex[37] = 7   ; jIndex[37] = 6   ;
    iIndex[38] = 8   ; jIndex[38] = 3   ;
    iIndex[39] = 8   ; jIndex[39] = 8   ;
    iIndex[40] = 9   ; jIndex[40] = 0   ;
    iIndex[41] = 9   ; jIndex[41] = 1   ;
    iIndex[42] = 9   ; jIndex[42] = 5   ;
    iIndex[43] = 9   ; jIndex[43] = 6   ;
  }


  void
  Pugliese::D2fd_odeD2xxpu_sparse(
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
    real_type t1   = LM__[0];
    real_type t5   = XR__[iX_C] / 2 + XL__[iX_C] / 2;
    real_type t10  = XR__[iX_T] / 2 + XL__[iX_T] / 2;
    real_type t11  = T_lim_DD(t10);
    real_type t13  = LM__[1];
    real_type t14  = t5 * t13;
    real_type t15  = IL(t10, t5);
    real_type t16  = IL_lim_DD(t15);
    real_type t17  = IL_D_1(t10, t5);
    real_type t18  = t17 * t17;
    real_type t21  = IL_lim_D(t15);
    real_type t22  = IL_D_1_1(t10, t5);
    real_type t27  = ModelPars[iM_a__IL] * LM__[2];
    result__[ 0   ] = t11 * t5 * t1 / 4 + t18 * t16 * t14 / 4 + t22 * t21 * t14 / 4 - t22 * t27 / 4;
    real_type t30  = T_lim_D(t10);
    real_type t31  = ModelPars[iM_kappa__AC];
    real_type t39  = (t30 / 4 + (XR__[iX_I__p] / 2 + XL__[iX_I__p] / 2) * t31 / 4) * t1;
    real_type t43  = IL_D_2(t10, t5);
    real_type t48  = IL_D_1_2(t10, t5);
    real_type t53  = t48 * t27 / 4;
    result__[ 1   ] = t39 + t17 * t21 * t13 / 4 + t17 * t43 * t16 * t14 / 4 + t48 * t21 * t14 / 4 - t53;
    real_type t54  = t31 * t1;
    result__[ 2   ] = t5 * t54 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    real_type t58  = t16 * t5;
    real_type t59  = t43 * t43;
    real_type t62  = t21 * t5;
    real_type t63  = IL_D_2_2(t10, t5);
    result__[ 7   ] = (t43 * t21 / 2 + t59 * t58 / 4 + t63 * t62 / 4) * t13 - t63 * t27 / 4;
    result__[ 8   ] = ModelPars[iM_kappa__R] * t13 / 4;
    result__[ 9   ] = t10 * t54 / 4;
    result__[ 10  ] = t39 + (t43 * t17 * t58 / 4 + t17 * t21 / 4 + t48 * t62 / 4) * t13 - t53;
    result__[ 11  ] = result__[7];
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = result__[14];
    real_type t84  = D_lim_DD(XR__[iX_DD] / 2 + XL__[iX_DD] / 2);
    result__[ 16  ] = -t84 * t13 / 4;
    result__[ 17  ] = result__[16];
    result__[ 18  ] = result__[5];
    result__[ 19  ] = result__[13];
    result__[ 20  ] = result__[18];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = result__[3];
    result__[ 23  ] = result__[10];
    result__[ 24  ] = result__[20];
    result__[ 25  ] = result__[22];
    result__[ 26  ] = result__[6];
    result__[ 27  ] = result__[24];
    result__[ 28  ] = result__[26];
    result__[ 29  ] = result__[11];
    result__[ 30  ] = result__[15];
    result__[ 31  ] = result__[21];
    result__[ 32  ] = result__[28];
    result__[ 33  ] = result__[29];
    result__[ 34  ] = result__[30];
    result__[ 35  ] = result__[31];
    result__[ 36  ] = result__[34];
    result__[ 37  ] = result__[36];
    result__[ 38  ] = result__[17];
    result__[ 39  ] = result__[38];
    result__[ 40  ] = result__[27];
    result__[ 41  ] = result__[35];
    result__[ 42  ] = result__[40];
    result__[ 43  ] = result__[41];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 44, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: Pugliese_Methods_Guess.cc
