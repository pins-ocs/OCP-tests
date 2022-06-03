/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_boundary_conditions.cc                     |
 |                                                                       |
 |  version: 1.0   date 4/6/2022                                         |
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

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::MeshStd;


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


namespace TyreDynamicDefine {

  /*\
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer TyreDynamic::bc_numEqns() const { return 6; }

  void
  TyreDynamic::bc_eval(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = XL__[iX_v];
    real_type t2   = ModelPars[iM_v__ss];
    result__[ 0   ] = t1 - t2;
    real_type t3   = XL__[iX_b];
    result__[ 1   ] = t3 - ModelPars[iM_b__ss];
    result__[ 2   ] = XR__[iX_v] - t2;
    real_type t6   = XL__[iX_lambda];
    real_type t7   = F__x(t6);
    real_type t8   = Fa(t1);
    result__[ 3   ] = -t7 + t8;
    real_type t10  = p__pos(XL__[iX_p]);
    real_type t11  = XL__[iX_omega];
    real_type t12  = TT(t10, t11);
    real_type t13  = b__neg(t3);
    real_type t14  = TB(t13, t11);
    real_type t17  = Ma(t11);
    result__[ 4   ] = ModelPars[iM_rw] * t7 - t12 - t14 - t17;
    real_type t18  = kappa__w(t1, t11);
    result__[ 5   ] = -(t18 - t6) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DbcDxxp_numRows() const { return 6; }
  integer TyreDynamic::DbcDxxp_numCols() const { return 10; }
  integer TyreDynamic::DbcDxxp_nnz()     const { return 12; }

  void
  TyreDynamic::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 4   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 5   ; jIndex[9 ] = 0   ;
    iIndex[10] = 5   ; jIndex[10] = 1   ;
    iIndex[11] = 5   ; jIndex[11] = 2   ;
  }


  void
  TyreDynamic::DbcDxxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    real_type t1   = XL__[iX_v];
    result__[ 3   ] = Fa_D(t1);
    real_type t2   = XL__[iX_lambda];
    real_type t3   = F__x_D(t2);
    result__[ 4   ] = -t3;
    real_type t4   = XL__[iX_p];
    real_type t5   = p__pos(t4);
    real_type t6   = XL__[iX_omega];
    real_type t7   = TT_D_2(t5, t6);
    real_type t8   = XL__[iX_b];
    real_type t9   = b__neg(t8);
    real_type t10  = TB_D_2(t9, t6);
    real_type t11  = Ma_D(t6);
    result__[ 5   ] = -t7 - t10 - t11;
    result__[ 6   ] = ModelPars[iM_rw] * t3;
    real_type t13  = TT_D_1(t5, t6);
    real_type t14  = p__pos_D(t4);
    result__[ 7   ] = -t14 * t13;
    real_type t16  = TB_D_1(t9, t6);
    real_type t17  = b__neg_D(t8);
    result__[ 8   ] = -t17 * t16;
    real_type t19  = kappa__w(t1, t6);
    real_type t20  = kappa__w_D_1(t1, t6);
    result__[ 9   ] = -t20 * t1 - t19 + t2;
    real_type t22  = kappa__w_D_2(t1, t6);
    result__[ 10  ] = -t22 * t1;
    result__[ 11  ] = t1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2bcD2xxp_numRows() const { return 10; }
  integer TyreDynamic::D2bcD2xxp_numCols() const { return 10; }
  integer TyreDynamic::D2bcD2xxp_nnz()     const { return 13; }

  void
  TyreDynamic::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 1   ;
    iIndex[10] = 3   ; jIndex[10] = 3   ;
    iIndex[11] = 4   ; jIndex[11] = 1   ;
    iIndex[12] = 4   ; jIndex[12] = 4   ;
  }


  void
  TyreDynamic::D2bcD2xxp_sparse(
    NodeType const              & LEFT__,
    NodeType const              & RIGHT__,
    P_const_pointer_type          P__,
    OMEGA_full_const_pointer_type OMEGA__,
    real_type                     result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = OMEGA__[3];
    real_type t2   = XL__[iX_v];
    real_type t3   = Fa_DD(t2);
    real_type t5   = OMEGA__[5];
    real_type t6   = XL__[iX_omega];
    real_type t7   = kappa__w_D_1(t2, t6);
    real_type t10  = t2 * t5;
    real_type t11  = kappa__w_D_1_1(t2, t6);
    result__[ 0   ] = t3 * t1 - t11 * t10 - 2 * t7 * t5;
    real_type t13  = kappa__w_D_2(t2, t6);
    real_type t15  = kappa__w_D_1_2(t2, t6);
    result__[ 1   ] = -t15 * t10 - t13 * t5;
    result__[ 2   ] = t5;
    result__[ 3   ] = result__[1];
    real_type t17  = OMEGA__[4];
    real_type t18  = XL__[iX_p];
    real_type t19  = p__pos(t18);
    real_type t20  = TT_D_2_2(t19, t6);
    real_type t21  = XL__[iX_b];
    real_type t22  = b__neg(t21);
    real_type t23  = TB_D_2_2(t22, t6);
    real_type t24  = Ma_DD(t6);
    real_type t28  = kappa__w_D_2_2(t2, t6);
    result__[ 4   ] = (-t20 - t23 - t24) * t17 - t28 * t2 * result__[2];
    real_type t30  = TT_D_1_2(t19, t6);
    real_type t32  = p__pos_D(t18);
    result__[ 5   ] = -t32 * t30 * t17;
    real_type t34  = TB_D_1_2(t22, t6);
    real_type t36  = b__neg_D(t21);
    result__[ 6   ] = -t36 * t34 * t17;
    result__[ 7   ] = result__[2];
    real_type t39  = F__x_DD(XL__[iX_lambda]);
    result__[ 8   ] = ModelPars[iM_rw] * t39 * t17 - t39 * t1;
    result__[ 9   ] = result__[5];
    real_type t44  = TT_D_1_1(t19, t6);
    real_type t46  = t32 * t32;
    real_type t48  = TT_D_1(t19, t6);
    real_type t50  = p__pos_DD(t18);
    result__[ 10  ] = -t46 * t44 * t17 - t50 * t48 * t17;
    result__[ 11  ] = result__[6];
    real_type t52  = TB_D_1_1(t22, t6);
    real_type t54  = t36 * t36;
    real_type t56  = TB_D_1(t22, t6);
    real_type t58  = b__neg_DD(t21);
    result__[ 12  ] = -t54 * t52 * t17 - t58 * t56 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "D2bcD2xxp_sparse", 13, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: TyreDynamic_Methods_boundary_conditions.cc
