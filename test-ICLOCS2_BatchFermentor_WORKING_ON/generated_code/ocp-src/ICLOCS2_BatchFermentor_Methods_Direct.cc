/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_Guess.cc                        |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

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
#define ALIAS_penalization_DD(__t1) Pen1D.evaluate_DD( __t1)
#define ALIAS_penalization_D(__t1) Pen1D.evaluate_D( __t1)
#define ALIAS_penalization(__t1) Pen1D.evaluate( __t1)


using namespace std;

namespace ICLOCS2_BatchFermentorDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer ICLOCS2_BatchFermentor::fd_ode_numEqns() const { return 4; }

  void
  ICLOCS2_BatchFermentor::fd_ode_eval(
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
    real_type t2   = XM__[2];
    real_type t3   = XM__[0];
    real_type t4   = mu(t2, t3);
    real_type t5   = t3 * t4;
    real_type t7   = U(UM__[4]);
    real_type t10  = 1.0 / XM__[3];
    result__[ 0   ] = t10 * t7 * t3 - t5 + V__[0];
    real_type t13  = rho(t2);
    real_type t14  = t3 * t13;
    real_type t16  = XM__[1];
    result__[ 1   ] = t10 * t7 * t16 + t16 * ModelPars[iM_K_degr] - t14 + V__[1];
    result__[ 2   ] = V__[2] + 1.0 / ModelPars[iM_Yxs] * t5 + 1.0 / ModelPars[iM_Yes] * t14 + t3 / (ModelPars[iM_kappa_m] + t2) * t2 * ModelPars[iM_mu_s] - (ModelPars[iM_S_f] - t2) * t10 * t7;
    result__[ 3   ] = V__[3] - t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::Dfd_odeDxxpu_numRows() const { return 4; }
  integer ICLOCS2_BatchFermentor::Dfd_odeDxxpu_numCols() const { return 13; }
  integer ICLOCS2_BatchFermentor::Dfd_odeDxxpu_nnz()     const { return 26; }

  void
  ICLOCS2_BatchFermentor::Dfd_odeDxxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 2   ;
    iIndex[10] = 1   ; jIndex[10] = 3   ;
    iIndex[11] = 1   ; jIndex[11] = 4   ;
    iIndex[12] = 1   ; jIndex[12] = 5   ;
    iIndex[13] = 1   ; jIndex[13] = 6   ;
    iIndex[14] = 1   ; jIndex[14] = 7   ;
    iIndex[15] = 1   ; jIndex[15] = 12  ;
    iIndex[16] = 2   ; jIndex[16] = 0   ;
    iIndex[17] = 2   ; jIndex[17] = 2   ;
    iIndex[18] = 2   ; jIndex[18] = 3   ;
    iIndex[19] = 2   ; jIndex[19] = 4   ;
    iIndex[20] = 2   ; jIndex[20] = 6   ;
    iIndex[21] = 2   ; jIndex[21] = 7   ;
    iIndex[22] = 2   ; jIndex[22] = 12  ;
    iIndex[23] = 3   ; jIndex[23] = 3   ;
    iIndex[24] = 3   ; jIndex[24] = 7   ;
    iIndex[25] = 3   ; jIndex[25] = 12  ;
  }


  void
  ICLOCS2_BatchFermentor::Dfd_odeDxxpu_sparse(
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
    real_type t1   = XM__[2];
    real_type t2   = XM__[0];
    real_type t3   = mu_D_2(t1, t2);
    real_type t4   = t2 * t3;
    real_type t5   = 0.5e0 * t4;
    real_type t6   = mu(t1, t2);
    real_type t7   = 0.5e0 * t6;
    real_type t8   = UM__[4];
    real_type t9   = U(t8);
    real_type t10  = XM__[3];
    real_type t11  = 1.0 / t10;
    real_type t13  = 0.5e0 * t11 * t9;
    result__[ 0   ] = -t5 - t7 + t13 - __INV_DZETA;
    real_type t14  = mu_D_1(t1, t2);
    real_type t15  = t2 * t14;
    result__[ 1   ] = -0.5e0 * t15;
    real_type t18  = t10 * t10;
    real_type t19  = 1.0 / t18;
    result__[ 2   ] = -0.5e0 * t19 * t9 * t2;
    result__[ 3   ] = -t5 - t7 + t13 + __INV_DZETA;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t22  = U_D(t8);
    result__[ 6   ] = t11 * t22 * t2;
    real_type t24  = rho(t1);
    result__[ 7   ] = -0.5e0 * t24;
    real_type t27  = 0.5e0 * ModelPars[iM_K_degr];
    result__[ 8   ] = t27 + t13 - __INV_DZETA;
    real_type t28  = rho_D(t1);
    real_type t29  = t2 * t28;
    result__[ 9   ] = -0.5e0 * t29;
    real_type t31  = XM__[1];
    result__[ 10  ] = -0.5e0 * t19 * t9 * t31;
    result__[ 11  ] = result__[7];
    result__[ 12  ] = t27 + t13 + __INV_DZETA;
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[10];
    result__[ 15  ] = t11 * t22 * t31;
    real_type t37  = 1.0 / ModelPars[iM_Yxs];
    real_type t43  = 1.0 / ModelPars[iM_Yes];
    real_type t46  = ModelPars[iM_mu_s];
    real_type t47  = t1 * t46;
    real_type t49  = ModelPars[iM_kappa_m] + t1;
    real_type t50  = 1.0 / t49;
    result__[ 16  ] = 0.5e0 * t37 * t4 + 0.5e0 * t37 * t6 + 0.5e0 * t43 * t24 + 0.5e0 * t50 * t47;
    real_type t54  = 0.5e0 * t37 * t15;
    real_type t56  = 0.5e0 * t43 * t29;
    real_type t59  = 0.5e0 * t2 * t50 * t46;
    real_type t60  = t49 * t49;
    real_type t64  = 0.5e0 * t2 / t60 * t47;
    result__[ 17  ] = t54 + t56 + t59 - t64 + t13 - __INV_DZETA;
    real_type t67  = ModelPars[iM_S_f] - t1;
    result__[ 18  ] = 0.5e0 * t67 * t19 * t9;
    result__[ 19  ] = result__[16];
    result__[ 20  ] = t54 + t56 + t59 - t64 + t13 + __INV_DZETA;
    result__[ 21  ] = result__[18];
    result__[ 22  ] = -t67 * t11 * t22;
    result__[ 23  ] = -__INV_DZETA;
    result__[ 24  ] = __INV_DZETA;
    result__[ 25  ] = -t22;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxpu_eval", 26, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2fd_odeD2xxpu_numRows() const { return 13; }
  integer ICLOCS2_BatchFermentor::D2fd_odeD2xxpu_numCols() const { return 13; }
  integer ICLOCS2_BatchFermentor::D2fd_odeD2xxpu_nnz()     const { return 61; }

  void
  ICLOCS2_BatchFermentor::D2fd_odeD2xxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 7   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 12  ;
    iIndex[10] = 2   ; jIndex[10] = 0   ;
    iIndex[11] = 2   ; jIndex[11] = 2   ;
    iIndex[12] = 2   ; jIndex[12] = 3   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 2   ; jIndex[15] = 7   ;
    iIndex[16] = 2   ; jIndex[16] = 12  ;
    iIndex[17] = 3   ; jIndex[17] = 0   ;
    iIndex[18] = 3   ; jIndex[18] = 1   ;
    iIndex[19] = 3   ; jIndex[19] = 2   ;
    iIndex[20] = 3   ; jIndex[20] = 3   ;
    iIndex[21] = 3   ; jIndex[21] = 4   ;
    iIndex[22] = 3   ; jIndex[22] = 5   ;
    iIndex[23] = 3   ; jIndex[23] = 6   ;
    iIndex[24] = 3   ; jIndex[24] = 7   ;
    iIndex[25] = 3   ; jIndex[25] = 12  ;
    iIndex[26] = 4   ; jIndex[26] = 0   ;
    iIndex[27] = 4   ; jIndex[27] = 2   ;
    iIndex[28] = 4   ; jIndex[28] = 3   ;
    iIndex[29] = 4   ; jIndex[29] = 4   ;
    iIndex[30] = 4   ; jIndex[30] = 6   ;
    iIndex[31] = 4   ; jIndex[31] = 7   ;
    iIndex[32] = 4   ; jIndex[32] = 12  ;
    iIndex[33] = 5   ; jIndex[33] = 3   ;
    iIndex[34] = 5   ; jIndex[34] = 7   ;
    iIndex[35] = 5   ; jIndex[35] = 12  ;
    iIndex[36] = 6   ; jIndex[36] = 0   ;
    iIndex[37] = 6   ; jIndex[37] = 2   ;
    iIndex[38] = 6   ; jIndex[38] = 3   ;
    iIndex[39] = 6   ; jIndex[39] = 4   ;
    iIndex[40] = 6   ; jIndex[40] = 6   ;
    iIndex[41] = 6   ; jIndex[41] = 7   ;
    iIndex[42] = 6   ; jIndex[42] = 12  ;
    iIndex[43] = 7   ; jIndex[43] = 0   ;
    iIndex[44] = 7   ; jIndex[44] = 1   ;
    iIndex[45] = 7   ; jIndex[45] = 2   ;
    iIndex[46] = 7   ; jIndex[46] = 3   ;
    iIndex[47] = 7   ; jIndex[47] = 4   ;
    iIndex[48] = 7   ; jIndex[48] = 5   ;
    iIndex[49] = 7   ; jIndex[49] = 6   ;
    iIndex[50] = 7   ; jIndex[50] = 7   ;
    iIndex[51] = 7   ; jIndex[51] = 12  ;
    iIndex[52] = 12  ; jIndex[52] = 0   ;
    iIndex[53] = 12  ; jIndex[53] = 1   ;
    iIndex[54] = 12  ; jIndex[54] = 2   ;
    iIndex[55] = 12  ; jIndex[55] = 3   ;
    iIndex[56] = 12  ; jIndex[56] = 4   ;
    iIndex[57] = 12  ; jIndex[57] = 5   ;
    iIndex[58] = 12  ; jIndex[58] = 6   ;
    iIndex[59] = 12  ; jIndex[59] = 7   ;
    iIndex[60] = 12  ; jIndex[60] = 12  ;
  }


  void
  ICLOCS2_BatchFermentor::D2fd_odeD2xxpu_sparse(
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
    real_type t2   = XR__[iX_s];
    real_type t3   = XL__[iX_s];
    real_type t5   = t2 / 2 + t3 / 2;
    real_type t9   = XR__[iX_x] / 2 + XL__[iX_x] / 2;
    real_type t10  = mu_D_2_2(t5, t9);
    real_type t11  = t9 * t10;
    real_type t13  = mu_D_2(t5, t9);
    real_type t17  = LM__[2];
    real_type t19  = 1.0 / ModelPars[iM_Yxs];
    result__[ 0   ] = (-t11 / 4 - t13 / 2) * t1 + (t19 * t11 / 4 + t19 * t13 / 2) * t17;
    real_type t26  = mu_D_1_2(t5, t9);
    real_type t27  = t9 * t26;
    real_type t28  = mu_D_1(t5, t9);
    real_type t32  = LM__[1];
    real_type t33  = rho_D(t5);
    real_type t35  = t33 * t32 / 4;
    real_type t39  = 1.0 / ModelPars[iM_Yes];
    real_type t41  = ModelPars[iM_mu_s];
    real_type t43  = t2 / 2;
    real_type t44  = t3 / 2;
    real_type t45  = ModelPars[iM_kappa_m] + t43 + t44;
    real_type t48  = t5 * t41;
    real_type t49  = t45 * t45;
    real_type t50  = 1.0 / t49;
    real_type t54  = (t19 * t27 / 4 + t19 * t28 / 4 + t39 * t33 / 4 + 1.0 / t45 * t41 / 4 - t50 * t48 / 4) * t17;
    result__[ 1   ] = (-t27 / 4 - t28 / 4) * t1 - t35 + t54;
    real_type t55  = UM__[4];
    real_type t56  = U(t55);
    real_type t61  = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t62  = t61 * t61;
    real_type t63  = 1.0 / t62;
    result__[ 2   ] = -t63 * t56 * t1 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t66  = U_D(t55);
    real_type t68  = 1.0 / t61;
    result__[ 6   ] = t68 * t66 * t1 / 2;
    result__[ 7   ] = -t63 * t56 * t32 / 4;
    result__[ 8   ] = result__[7];
    result__[ 9   ] = t68 * t66 * t32 / 2;
    result__[ 10  ] = result__[4];
    real_type t75  = mu_D_1_1(t5, t9);
    real_type t79  = rho_DD(t5);
    result__[ 11  ] = -t9 * t75 * t1 / 4 - t9 * t79 * t32 / 4 + (t19 * t9 * t75 / 4 + t39 * t9 * t79 / 4 - t9 * t50 * t41 / 2 + t9 / t49 / t45 * t48 / 2) * t17;
    real_type t99  = t56 * t17;
    result__[ 12  ] = -t63 * t99 / 4;
    result__[ 13  ] = -t9 * t26 * t1 / 4 - t28 * t1 / 4 - t35 + t54;
    result__[ 14  ] = result__[11];
    result__[ 15  ] = result__[12];
    real_type t107 = t66 * t17;
    result__[ 16  ] = t68 * t107 / 2;
    result__[ 17  ] = result__[5];
    result__[ 18  ] = result__[8];
    result__[ 19  ] = result__[15];
    real_type t109 = t9 * t1;
    real_type t111 = 1.0 / t62 / t61;
    real_type t112 = t111 * t56;
    real_type t118 = (XR__[iX_p] / 2 + XL__[iX_p] / 2) * t32;
    real_type t121 = ModelPars[iM_S_f] - t43 - t44;
    result__[ 20  ] = -t121 * t111 * t99 / 2 + t112 * t109 / 2 + t112 * t118 / 2;
    result__[ 21  ] = result__[17];
    result__[ 22  ] = result__[18];
    result__[ 23  ] = result__[19];
    result__[ 24  ] = result__[20];
    real_type t125 = t63 * t66;
    result__[ 25  ] = t121 * t63 * t107 / 2 - t125 * t109 / 2 - t125 * t118 / 2;
    result__[ 26  ] = result__[3];
    result__[ 27  ] = result__[13];
    result__[ 28  ] = result__[21];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[10];
    result__[ 31  ] = result__[28];
    result__[ 32  ] = result__[6];
    result__[ 33  ] = result__[22];
    result__[ 34  ] = result__[33];
    result__[ 35  ] = result__[9];
    result__[ 36  ] = result__[30];
    result__[ 37  ] = result__[14];
    result__[ 38  ] = result__[23];
    result__[ 39  ] = result__[36];
    result__[ 40  ] = result__[37];
    result__[ 41  ] = result__[38];
    result__[ 42  ] = result__[16];
    result__[ 43  ] = result__[31];
    result__[ 44  ] = result__[34];
    result__[ 45  ] = result__[41];
    result__[ 46  ] = result__[24];
    result__[ 47  ] = result__[43];
    result__[ 48  ] = result__[44];
    result__[ 49  ] = result__[45];
    result__[ 50  ] = result__[46];
    result__[ 51  ] = result__[25];
    result__[ 52  ] = result__[32];
    result__[ 53  ] = result__[35];
    result__[ 54  ] = result__[42];
    result__[ 55  ] = result__[51];
    result__[ 56  ] = result__[52];
    result__[ 57  ] = result__[53];
    result__[ 58  ] = result__[54];
    result__[ 59  ] = result__[55];
    real_type t131 = U_DD(t55);
    real_type t132 = t68 * t131;
    result__[ 60  ] = -t121 * t68 * t131 * t17 + t132 * t109 + t132 * t118 - t131 * LM__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxpu_eval", 61, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: ICLOCS2_BatchFermentor_Methods_Guess.cc
