/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_Guess.cc                                   |
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


#include "TyreDynamic.hh"
#include "TyreDynamic_Pars.hh"

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
#define ALIAS_abs_reg_DD(__t1) abs_reg.DD( __t1)
#define ALIAS_abs_reg_D(__t1) abs_reg.D( __t1)
#define ALIAS_sign_reg_DD(__t1) sign_reg.DD( __t1)
#define ALIAS_sign_reg_D(__t1) sign_reg.D( __t1)
#define ALIAS_clipInt_D_3(__t1, __t2, __t3) clipInt.D_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2(__t1, __t2, __t3) clipInt.D_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1(__t1, __t2, __t3) clipInt.D_1( __t1, __t2, __t3)
#define ALIAS_clipInt_D_3_3(__t1, __t2, __t3) clipInt.D_3_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_3(__t1, __t2, __t3) clipInt.D_2_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_2(__t1, __t2, __t3) clipInt.D_2_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_3(__t1, __t2, __t3) clipInt.D_1_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_2(__t1, __t2, __t3) clipInt.D_1_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_1(__t1, __t2, __t3) clipInt.D_1_1( __t1, __t2, __t3)
#define ALIAS_clipSup_D_2(__t1, __t2) clipSup.D_2( __t1, __t2)
#define ALIAS_clipSup_D_1(__t1, __t2) clipSup.D_1( __t1, __t2)
#define ALIAS_clipSup_D_2_2(__t1, __t2) clipSup.D_2_2( __t1, __t2)
#define ALIAS_clipSup_D_1_2(__t1, __t2) clipSup.D_1_2( __t1, __t2)
#define ALIAS_clipSup_D_1_1(__t1, __t2) clipSup.D_1_1( __t1, __t2)
#define ALIAS_negPart_DD(__t1) negPart.DD( __t1)
#define ALIAS_negPart_D(__t1) negPart.D( __t1)
#define ALIAS_posPart_DD(__t1) posPart.DD( __t1)
#define ALIAS_posPart_D(__t1) posPart.D( __t1)
#define ALIAS_v_min_DD(__t1) v_min.DD( __t1)
#define ALIAS_v_min_D(__t1) v_min.D( __t1)
#define ALIAS_LongSlipRear_max_DD(__t1) LongSlipRear_max.DD( __t1)
#define ALIAS_LongSlipRear_max_D(__t1) LongSlipRear_max.D( __t1)
#define ALIAS_LongSlipRear_min_DD(__t1) LongSlipRear_min.DD( __t1)
#define ALIAS_LongSlipRear_min_D(__t1) LongSlipRear_min.D( __t1)
#define ALIAS_OnlyTractionRear_DD(__t1) OnlyTractionRear.DD( __t1)
#define ALIAS_OnlyTractionRear_D(__t1) OnlyTractionRear.D( __t1)
#define ALIAS_OnlyBrakingRear_DD(__t1) OnlyBrakingRear.DD( __t1)
#define ALIAS_OnlyBrakingRear_D(__t1) OnlyBrakingRear.D( __t1)
#define ALIAS_p__oControl_D_3(__t1, __t2, __t3) p__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2(__t1, __t2, __t3) p__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1(__t1, __t2, __t3) p__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_3_3(__t1, __t2, __t3) p__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_3(__t1, __t2, __t3) p__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_2(__t1, __t2, __t3) p__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_3(__t1, __t2, __t3) p__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_2(__t1, __t2, __t3) p__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_1(__t1, __t2, __t3) p__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3(__t1, __t2, __t3) b__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2(__t1, __t2, __t3) b__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1(__t1, __t2, __t3) b__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3_3(__t1, __t2, __t3) b__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_3(__t1, __t2, __t3) b__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_2(__t1, __t2, __t3) b__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_3(__t1, __t2, __t3) b__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_2(__t1, __t2, __t3) b__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_1(__t1, __t2, __t3) b__oControl.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace TyreDynamicDefine {

  /*\
  :|:   ____  _               _
  :|:  |  _ \(_)_ __ ___  ___| |_
  :|:  | | | | | '__/ _ \/ __| __|
  :|:  | |_| | | | |  __/ (__| |_
  :|:  |____/|_|_|  \___|\___|\__|
  \*/


  integer TyreDynamic::fd_ode_numEqns() const { return 5; }

  void
  TyreDynamic::fd_ode_eval(
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
    real_type t1   = XM__[0];
    real_type t6   = XM__[2];
    real_type t7   = F__x(t6);
    real_type t8   = Fa(t1);
    result__[ 0   ] = V__[0] * ModelPars[iM_m] * t1 - t7 + t8;
    real_type t13  = XM__[3];
    real_type t14  = p__pos(t13);
    real_type t15  = XM__[1];
    real_type t16  = TT(t14, t15);
    real_type t17  = XM__[4];
    real_type t18  = b__neg(t17);
    real_type t19  = TB(t18, t15);
    real_type t22  = Ma(t15);
    result__[ 1   ] = V__[1] * t1 * ModelPars[iM_Iw] + ModelPars[iM_rw] * t7 - t16 - t19 - t22;
    real_type t27  = kappa__w(t1, t15);
    result__[ 2   ] = V__[2] * ModelPars[iM_l__x] * t1 - (t27 - t6) * t1;
    result__[ 3   ] = ModelPars[iM_tau__p] * t1 * V__[3] + t13 - UM__[0];
    result__[ 4   ] = ModelPars[iM_tau__b] * t1 * V__[4] + t17 - UM__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::Dfd_odeDxxup_numRows() const { return 5; }
  integer TyreDynamic::Dfd_odeDxxup_numCols() const { return 12; }
  integer TyreDynamic::Dfd_odeDxxup_nnz()     const { return 30; }

  void
  TyreDynamic::Dfd_odeDxxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 7   ;
    iIndex[12] = 1   ; jIndex[12] = 8   ;
    iIndex[13] = 1   ; jIndex[13] = 9   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 1   ;
    iIndex[16] = 2   ; jIndex[16] = 2   ;
    iIndex[17] = 2   ; jIndex[17] = 5   ;
    iIndex[18] = 2   ; jIndex[18] = 6   ;
    iIndex[19] = 2   ; jIndex[19] = 7   ;
    iIndex[20] = 3   ; jIndex[20] = 0   ;
    iIndex[21] = 3   ; jIndex[21] = 3   ;
    iIndex[22] = 3   ; jIndex[22] = 5   ;
    iIndex[23] = 3   ; jIndex[23] = 8   ;
    iIndex[24] = 3   ; jIndex[24] = 10  ;
    iIndex[25] = 4   ; jIndex[25] = 0   ;
    iIndex[26] = 4   ; jIndex[26] = 4   ;
    iIndex[27] = 4   ; jIndex[27] = 5   ;
    iIndex[28] = 4   ; jIndex[28] = 9   ;
    iIndex[29] = 4   ; jIndex[29] = 11  ;
  }


  void
  TyreDynamic::Dfd_odeDxxup_sparse(
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
    real_type t1   = ModelPars[iM_m];
    real_type t4   = 0.5e0 * V__[0] * t1;
    real_type t5   = XM__[0];
    real_type t6   = Fa_D(t5);
    real_type t7   = 0.5e0 * t6;
    real_type t8   = t5 * __INV_DZETA;
    real_type t9   = t1 * t8;
    result__[ 0   ] = t4 + t7 - t9;
    real_type t10  = XM__[2];
    real_type t11  = F__x_D(t10);
    result__[ 1   ] = -0.5e0 * t11;
    result__[ 2   ] = t4 + t7 + t9;
    result__[ 3   ] = result__[1];
    real_type t13  = ModelPars[iM_Iw];
    result__[ 4   ] = 0.5e0 * V__[1] * t13;
    real_type t16  = XM__[3];
    real_type t17  = p__pos(t16);
    real_type t18  = XM__[1];
    real_type t19  = TT_D_2(t17, t18);
    real_type t20  = 0.5e0 * t19;
    real_type t21  = XM__[4];
    real_type t22  = b__neg(t21);
    real_type t23  = TB_D_2(t22, t18);
    real_type t24  = 0.5e0 * t23;
    real_type t25  = Ma_D(t18);
    real_type t26  = 0.5e0 * t25;
    real_type t28  = t5 * t13 * __INV_DZETA;
    result__[ 5   ] = -t20 - t24 - t26 - t28;
    result__[ 6   ] = 0.5e0 * ModelPars[iM_rw] * t11;
    real_type t31  = TT_D_1(t17, t18);
    real_type t32  = p__pos_D(t16);
    result__[ 7   ] = -0.5e0 * t32 * t31;
    real_type t35  = TB_D_1(t22, t18);
    real_type t36  = b__neg_D(t21);
    result__[ 8   ] = -0.5e0 * t36 * t35;
    result__[ 9   ] = result__[4];
    result__[ 10  ] = -t20 - t24 - t26 + t28;
    result__[ 11  ] = result__[6];
    result__[ 12  ] = result__[7];
    result__[ 13  ] = result__[8];
    real_type t39  = ModelPars[iM_l__x];
    real_type t43  = kappa__w(t5, t18);
    real_type t46  = kappa__w_D_1(t5, t18);
    result__[ 14  ] = 0.5e0 * V__[2] * t39 - 0.5e0 * t43 + 0.5e0 * t10 - 0.5e0 * t46 * t5;
    real_type t49  = kappa__w_D_2(t5, t18);
    result__[ 15  ] = -0.5e0 * t49 * t5;
    real_type t52  = 0.5e0 * t5;
    real_type t53  = t39 * t8;
    result__[ 16  ] = t52 - t53;
    result__[ 17  ] = result__[14];
    result__[ 18  ] = result__[15];
    result__[ 19  ] = t52 + t53;
    real_type t54  = ModelPars[iM_tau__p];
    result__[ 20  ] = 0.5e0 * V__[3] * t54;
    real_type t57  = t54 * t8;
    result__[ 21  ] = 0.5e0 - t57;
    result__[ 22  ] = result__[20];
    result__[ 23  ] = 0.5e0 + t57;
    result__[ 24  ] = -1.0;
    real_type t58  = ModelPars[iM_tau__b];
    result__[ 25  ] = 0.5e0 * V__[4] * t58;
    real_type t61  = t58 * t8;
    result__[ 26  ] = 0.5e0 - t61;
    result__[ 27  ] = result__[25];
    result__[ 28  ] = 0.5e0 + t61;
    result__[ 29  ] = -1.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_odeDxxup_eval", 30, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2fd_odeD2xxup_numRows() const { return 12; }
  integer TyreDynamic::D2fd_odeD2xxup_numCols() const { return 12; }
  integer TyreDynamic::D2fd_odeD2xxup_nnz()     const { return 52; }

  void
  TyreDynamic::D2fd_odeD2xxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 3   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 1   ; jIndex[12] = 8   ;
    iIndex[13] = 1   ; jIndex[13] = 9   ;
    iIndex[14] = 2   ; jIndex[14] = 0   ;
    iIndex[15] = 2   ; jIndex[15] = 2   ;
    iIndex[16] = 2   ; jIndex[16] = 5   ;
    iIndex[17] = 2   ; jIndex[17] = 7   ;
    iIndex[18] = 3   ; jIndex[18] = 1   ;
    iIndex[19] = 3   ; jIndex[19] = 3   ;
    iIndex[20] = 3   ; jIndex[20] = 6   ;
    iIndex[21] = 3   ; jIndex[21] = 8   ;
    iIndex[22] = 4   ; jIndex[22] = 1   ;
    iIndex[23] = 4   ; jIndex[23] = 4   ;
    iIndex[24] = 4   ; jIndex[24] = 6   ;
    iIndex[25] = 4   ; jIndex[25] = 9   ;
    iIndex[26] = 5   ; jIndex[26] = 0   ;
    iIndex[27] = 5   ; jIndex[27] = 1   ;
    iIndex[28] = 5   ; jIndex[28] = 2   ;
    iIndex[29] = 5   ; jIndex[29] = 5   ;
    iIndex[30] = 5   ; jIndex[30] = 6   ;
    iIndex[31] = 5   ; jIndex[31] = 7   ;
    iIndex[32] = 6   ; jIndex[32] = 0   ;
    iIndex[33] = 6   ; jIndex[33] = 1   ;
    iIndex[34] = 6   ; jIndex[34] = 3   ;
    iIndex[35] = 6   ; jIndex[35] = 4   ;
    iIndex[36] = 6   ; jIndex[36] = 5   ;
    iIndex[37] = 6   ; jIndex[37] = 6   ;
    iIndex[38] = 6   ; jIndex[38] = 8   ;
    iIndex[39] = 6   ; jIndex[39] = 9   ;
    iIndex[40] = 7   ; jIndex[40] = 0   ;
    iIndex[41] = 7   ; jIndex[41] = 2   ;
    iIndex[42] = 7   ; jIndex[42] = 5   ;
    iIndex[43] = 7   ; jIndex[43] = 7   ;
    iIndex[44] = 8   ; jIndex[44] = 1   ;
    iIndex[45] = 8   ; jIndex[45] = 3   ;
    iIndex[46] = 8   ; jIndex[46] = 6   ;
    iIndex[47] = 8   ; jIndex[47] = 8   ;
    iIndex[48] = 9   ; jIndex[48] = 1   ;
    iIndex[49] = 9   ; jIndex[49] = 4   ;
    iIndex[50] = 9   ; jIndex[50] = 6   ;
    iIndex[51] = 9   ; jIndex[51] = 9   ;
  }


  void
  TyreDynamic::D2fd_odeD2xxup_sparse(
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
    real_type t5   = XR__[iX_v] / 2 + XL__[iX_v] / 2;
    real_type t6   = Fa_DD(t5);
    real_type t9   = LM__[2];
    real_type t13  = XR__[iX_omega] / 2 + XL__[iX_omega] / 2;
    real_type t14  = kappa__w_D_1(t5, t13);
    real_type t16  = kappa__w_D_1_1(t5, t13);
    result__[ 0   ] = t6 * t1 / 4 + (-t14 / 2 - t16 * t5 / 4) * t9;
    real_type t21  = kappa__w_D_2(t5, t13);
    real_type t22  = kappa__w_D_1_2(t5, t13);
    result__[ 1   ] = (-t22 * t5 / 4 - t21 / 4) * t9;
    result__[ 2   ] = t9 / 4;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    real_type t26  = LM__[1];
    real_type t30  = XR__[iX_p] / 2 + XL__[iX_p] / 2;
    real_type t31  = p__pos(t30);
    real_type t32  = TT_D_2_2(t31, t13);
    real_type t36  = XR__[iX_b] / 2 + XL__[iX_b] / 2;
    real_type t37  = b__neg(t36);
    real_type t38  = TB_D_2_2(t37, t13);
    real_type t39  = Ma_DD(t13);
    real_type t43  = t5 * t9;
    real_type t44  = kappa__w_D_2_2(t5, t13);
    result__[ 7   ] = (-t32 / 4 - t38 / 4 - t39 / 4) * t26 - t44 * t43 / 4;
    real_type t47  = TT_D_1_2(t31, t13);
    real_type t49  = p__pos_D(t30);
    result__[ 8   ] = -t49 * t47 * t26 / 4;
    real_type t52  = TB_D_1_2(t37, t13);
    real_type t54  = b__neg_D(t36);
    result__[ 9   ] = -t54 * t52 * t26 / 4;
    result__[ 10  ] = -t21 * t9 / 4 - t22 * t43 / 4;
    result__[ 11  ] = result__[7];
    result__[ 12  ] = result__[8];
    result__[ 13  ] = result__[9];
    result__[ 14  ] = result__[5];
    real_type t64  = F__x_DD(XR__[iX_lambda] / 2 + XL__[iX_lambda] / 2);
    result__[ 15  ] = ModelPars[iM_rw] * t64 * t26 / 4 - t64 * t1 / 4;
    result__[ 16  ] = result__[14];
    result__[ 17  ] = result__[15];
    result__[ 18  ] = result__[12];
    real_type t70  = TT_D_1_1(t31, t13);
    real_type t72  = t49 * t49;
    real_type t74  = TT_D_1(t31, t13);
    real_type t76  = p__pos_DD(t30);
    result__[ 19  ] = -t72 * t70 * t26 / 4 - t76 * t74 * t26 / 4;
    result__[ 20  ] = result__[18];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = result__[13];
    real_type t79  = TB_D_1_1(t37, t13);
    real_type t81  = t54 * t54;
    real_type t83  = TB_D_1(t37, t13);
    real_type t85  = b__neg_DD(t36);
    result__[ 23  ] = -t81 * t79 * t26 / 4 - t85 * t83 * t26 / 4;
    result__[ 24  ] = result__[22];
    result__[ 25  ] = result__[23];
    result__[ 26  ] = result__[3];
    result__[ 27  ] = result__[10];
    result__[ 28  ] = result__[16];
    result__[ 29  ] = result__[26];
    result__[ 30  ] = result__[6];
    result__[ 31  ] = result__[28];
    result__[ 32  ] = result__[30];
    result__[ 33  ] = result__[11];
    result__[ 34  ] = result__[20];
    result__[ 35  ] = result__[24];
    result__[ 36  ] = result__[32];
    result__[ 37  ] = result__[33];
    result__[ 38  ] = result__[34];
    result__[ 39  ] = result__[35];
    result__[ 40  ] = result__[31];
    result__[ 41  ] = result__[17];
    result__[ 42  ] = result__[40];
    result__[ 43  ] = result__[41];
    result__[ 44  ] = result__[38];
    result__[ 45  ] = result__[21];
    result__[ 46  ] = result__[44];
    result__[ 47  ] = result__[45];
    result__[ 48  ] = result__[39];
    result__[ 49  ] = result__[25];
    result__[ 50  ] = result__[48];
    result__[ 51  ] = result__[49];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2fd_odeD2xxup_eval", 52, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

}

// EOF: TyreDynamic_Methods_Guess.cc
