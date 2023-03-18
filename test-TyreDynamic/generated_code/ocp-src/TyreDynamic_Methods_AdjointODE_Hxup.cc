/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_AdjointODE.cc                              |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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
#pragma warning( disable : 4189 )
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::Hxp_numEqns() const { return 5; }

  void
  TyreDynamic::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t14  = b__oControl(t4, -1, 1);
    real_type t16  = p__oControl(t2, -1, 1);
    real_type t18  = X__[iX_b];
    real_type t19  = ModelPars[iM_h__b];
    real_type t20  = t18 - t19;
    real_type t21  = OnlyBrakingRear(t20);
    real_type t23  = X__[iX_p];
    real_type t24  = -t19 - t23;
    real_type t25  = OnlyTractionRear(t24);
    real_type t28  = 1.0 / ModelPars[iM_lambda__max];
    real_type t29  = X__[iX_lambda];
    real_type t30  = t29 * t28;
    real_type t31  = -1 - t30;
    real_type t32  = LongSlipRear_min(t31);
    real_type t34  = t30 - 1;
    real_type t35  = LongSlipRear_max(t34);
    real_type t37  = 1 - t10;
    real_type t38  = v_min(t37);
    real_type t40  = 1.0 / t10;
    real_type t41  = ALIAS_v_min_D(t37);
    real_type t43  = MU__[0];
    real_type t44  = Fa_D(t10);
    real_type t50  = MU__[1];
    real_type t55  = MU__[2];
    real_type t56  = X__[iX_omega];
    real_type t57  = kappa__w(t10, t56);
    real_type t58  = kappa__w_D_1(t10, t56);
    real_type t65  = MU__[3];
    real_type t70  = MU__[4];
    result__[ 0   ] = -t12 * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5)) - t14 * t12 - t16 * t12 - t21 * t12 - t25 * t12 - t32 * t12 - t35 * t12 - t38 * t12 - t41 * t40 + (-ModelPars[iM_m] * V__[0] - t44) * t43 - V__[1] * ModelPars[iM_Iw] * t50 + (t58 * t10 - ModelPars[iM_l__x] * V__[2] - t29 + t57) * t55 - V__[3] * ModelPars[iM_tau__p] * t65 - V__[4] * ModelPars[iM_tau__b] * t70;
    real_type t75  = p__pos(t23);
    real_type t76  = TT_D_2(t75, t56);
    real_type t77  = b__neg(t18);
    real_type t78  = TB_D_2(t77, t56);
    real_type t79  = Ma_D(t56);
    real_type t82  = t10 * t55;
    real_type t83  = kappa__w_D_2(t10, t56);
    result__[ 1   ] = (t76 + t78 + t79) * t50 + t83 * t82;
    real_type t85  = ALIAS_LongSlipRear_min_D(t31);
    real_type t88  = ALIAS_LongSlipRear_max_D(t34);
    real_type t91  = F__x_D(t29);
    result__[ 2   ] = -t28 * t85 * t40 + t28 * t88 * t40 - ModelPars[iM_rw] * t91 * t50 + t91 * t43 - t82;
    real_type t96  = ALIAS_OnlyTractionRear_D(t24);
    real_type t98  = TT_D_1(t75, t56);
    real_type t100 = p__pos_D(t23);
    result__[ 3   ] = t100 * t98 * t50 - t96 * t40 - t65;
    real_type t102 = ALIAS_OnlyBrakingRear_D(t20);
    real_type t104 = TB_D_1(t77, t56);
    real_type t106 = b__neg_D(t18);
    result__[ 4   ] = t106 * t104 * t50 + t102 * t40 - t70;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DHxpDxpuv_numRows() const { return 5; }
  integer TyreDynamic::DHxpDxpuv_numCols() const { return 12; }
  integer TyreDynamic::DHxpDxpuv_nnz()     const { return 24; }

  void
  TyreDynamic::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 9   ;
    iIndex[10] = 0   ; jIndex[10] = 10  ;
    iIndex[11] = 0   ; jIndex[11] = 11  ;
    iIndex[12] = 1   ; jIndex[12] = 0   ;
    iIndex[13] = 1   ; jIndex[13] = 1   ;
    iIndex[14] = 1   ; jIndex[14] = 3   ;
    iIndex[15] = 1   ; jIndex[15] = 4   ;
    iIndex[16] = 2   ; jIndex[16] = 0   ;
    iIndex[17] = 2   ; jIndex[17] = 2   ;
    iIndex[18] = 3   ; jIndex[18] = 0   ;
    iIndex[19] = 3   ; jIndex[19] = 1   ;
    iIndex[20] = 3   ; jIndex[20] = 3   ;
    iIndex[21] = 4   ; jIndex[21] = 0   ;
    iIndex[22] = 4   ; jIndex[22] = 1   ;
    iIndex[23] = 4   ; jIndex[23] = 4   ;
  }


  void
  TyreDynamic::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t7   = ModelPars[iM_w__U];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t13  = 1.0 / t11 / t10;
    real_type t16  = b__oControl(t4, -1, 1);
    real_type t19  = p__oControl(t2, -1, 1);
    real_type t22  = X__[iX_b];
    real_type t23  = ModelPars[iM_h__b];
    real_type t24  = t22 - t23;
    real_type t25  = OnlyBrakingRear(t24);
    real_type t28  = X__[iX_p];
    real_type t29  = -t23 - t28;
    real_type t30  = OnlyTractionRear(t29);
    real_type t33  = ModelPars[iM_lambda__max];
    real_type t34  = 1.0 / t33;
    real_type t35  = X__[iX_lambda];
    real_type t36  = t35 * t34;
    real_type t37  = -1 - t36;
    real_type t38  = LongSlipRear_min(t37);
    real_type t41  = t36 - 1;
    real_type t42  = LongSlipRear_max(t41);
    real_type t45  = 1 - t10;
    real_type t46  = v_min(t45);
    real_type t49  = 1.0 / t11;
    real_type t50  = ALIAS_v_min_D(t45);
    real_type t53  = 1.0 / t10;
    real_type t54  = ALIAS_v_min_DD(t45);
    real_type t56  = MU__[0];
    real_type t57  = Fa_DD(t10);
    real_type t59  = MU__[2];
    real_type t60  = X__[iX_omega];
    real_type t61  = kappa__w_D_1(t10, t60);
    real_type t63  = kappa__w_D_1_1(t10, t60);
    result__[ 0   ] = 2 * t13 * (ModelPars[iM_w__t] + t7 * (t3 + t5)) + 2 * t16 * t13 + 2 * t19 * t13 + 2 * t25 * t13 + 2 * t30 * t13 + 2 * t38 * t13 + 2 * t42 * t13 + 2 * t46 * t13 + 2 * t50 * t49 + t54 * t53 - t57 * t56 + (t63 * t10 + 2 * t61) * t59;
    real_type t67  = kappa__w_D_2(t10, t60);
    real_type t68  = kappa__w_D_1_2(t10, t60);
    result__[ 1   ] = (t68 * t10 + t67) * t59;
    real_type t71  = ALIAS_LongSlipRear_min_D(t37);
    real_type t74  = ALIAS_LongSlipRear_max_D(t41);
    result__[ 2   ] = t34 * t71 * t49 - t34 * t74 * t49 - t59;
    real_type t77  = ALIAS_OnlyTractionRear_D(t29);
    result__[ 3   ] = t77 * t49;
    real_type t78  = ALIAS_OnlyBrakingRear_D(t24);
    result__[ 4   ] = -t78 * t49;
    real_type t83  = ALIAS_p__oControl_D_1(t2, -1, 1);
    result__[ 5   ] = -2 * t49 * t7 * t2 - t83 * t49;
    real_type t88  = ALIAS_b__oControl_D_1(t4, -1, 1);
    result__[ 6   ] = -2 * t49 * t7 * t4 - t88 * t49;
    result__[ 7   ] = -ModelPars[iM_m] * t56;
    real_type t92  = MU__[1];
    result__[ 8   ] = -ModelPars[iM_Iw] * t92;
    result__[ 9   ] = -ModelPars[iM_l__x] * t59;
    result__[ 10  ] = -MU__[3] * ModelPars[iM_tau__p];
    result__[ 11  ] = -MU__[4] * ModelPars[iM_tau__b];
    real_type t104 = t10 * t59;
    result__[ 12  ] = t68 * t104 + t67 * t59;
    real_type t106 = p__pos(t28);
    real_type t107 = TT_D_2_2(t106, t60);
    real_type t108 = b__neg(t22);
    real_type t109 = TB_D_2_2(t108, t60);
    real_type t110 = Ma_DD(t60);
    real_type t113 = kappa__w_D_2_2(t10, t60);
    result__[ 13  ] = (t107 + t109 + t110) * t92 + t113 * t104;
    real_type t115 = TT_D_1_2(t106, t60);
    real_type t117 = p__pos_D(t28);
    result__[ 14  ] = t117 * t115 * t92;
    real_type t118 = TB_D_1_2(t108, t60);
    real_type t120 = b__neg_D(t22);
    result__[ 15  ] = t120 * t118 * t92;
    result__[ 16  ] = result__[2];
    real_type t121 = ALIAS_LongSlipRear_min_DD(t37);
    real_type t123 = t33 * t33;
    real_type t124 = 1.0 / t123;
    real_type t126 = ALIAS_LongSlipRear_max_DD(t41);
    real_type t129 = F__x_DD(t35);
    result__[ 17  ] = t124 * t121 * t53 + t124 * t126 * t53 - ModelPars[iM_rw] * t129 * t92 + t129 * t56;
    result__[ 18  ] = result__[3];
    result__[ 19  ] = result__[14];
    real_type t134 = ALIAS_OnlyTractionRear_DD(t29);
    real_type t136 = TT_D_1_1(t106, t60);
    real_type t138 = t117 * t117;
    real_type t140 = TT_D_1(t106, t60);
    real_type t142 = p__pos_DD(t28);
    result__[ 20  ] = t138 * t136 * t92 + t142 * t140 * t92 + t134 * t53;
    result__[ 21  ] = result__[4];
    result__[ 22  ] = result__[15];
    real_type t144 = ALIAS_OnlyBrakingRear_DD(t24);
    real_type t146 = TB_D_1_1(t108, t60);
    real_type t148 = t120 * t120;
    real_type t150 = TB_D_1(t108, t60);
    real_type t152 = b__neg_DD(t22);
    result__[ 23  ] = t148 * t146 * t92 + t152 * t150 * t92 + t144 * t53;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 24, i_segment );
  }

}

// EOF: TyreDynamic_Methods_AdjointODE.cc
