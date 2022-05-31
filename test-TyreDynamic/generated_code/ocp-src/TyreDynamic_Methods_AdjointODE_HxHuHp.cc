/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_AdjointODE.cc                              |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::Hxp_numEqns() const { return 5; }

  void
  TyreDynamic::Hxp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = U__[iU_p__o] * U__[iU_p__o];
    real_type t5   = U__[iU_b__o] * U__[iU_b__o];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t14  = L__[iL_lambda1__xo];
    real_type t15  = Fa_D(t10);
    real_type t17  = L__[iL_lambda3__xo];
    real_type t18  = X__[iX_omega];
    real_type t19  = kappa__w(t10, t18);
    real_type t20  = X__[iX_lambda];
    real_type t23  = t10 * t17;
    real_type t24  = kappa__w_D_1(t10, t18);
    real_type t30  = L__[iL_lambda2__xo];
    real_type t39  = L__[iL_lambda4__xo];
    real_type t44  = L__[iL_lambda5__xo];
    result__[ 0   ] = -1.0 / t11 * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5)) - t15 * t14 + (t19 - t20) * t17 + t24 * t23 - V__[0] * ModelPars[iM_m] * t14 - V__[1] * ModelPars[iM_Iw] * t30 - V__[2] * ModelPars[iM_l__x] * t17 - V__[3] * ModelPars[iM_tau__p] * t39 - V__[4] * ModelPars[iM_tau__b] * t44;
    real_type t49  = X__[iX_p];
    real_type t50  = p__pos(t49);
    real_type t51  = TT_D_2(t50, t18);
    real_type t52  = X__[iX_b];
    real_type t53  = b__neg(t52);
    real_type t54  = TB_D_2(t53, t18);
    real_type t55  = Ma_D(t18);
    real_type t58  = kappa__w_D_2(t10, t18);
    result__[ 1   ] = (t51 + t54 + t55) * t30 + t58 * t23;
    real_type t60  = F__x_D(t20);
    result__[ 2   ] = -ModelPars[iM_rw] * t60 * t30 + t60 * t14 - t23;
    real_type t65  = TT_D_1(t50, t18);
    real_type t67  = p__pos_D(t49);
    result__[ 3   ] = t67 * t65 * t30 - t39;
    real_type t69  = TB_D_1(t53, t18);
    real_type t71  = b__neg_D(t52);
    result__[ 4   ] = t71 * t69 * t30 - t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DHxpDxpu_numRows() const { return 5; }
  integer TyreDynamic::DHxpDxpu_numCols() const { return 7; }
  integer TyreDynamic::DHxpDxpu_nnz()     const { return 15; }

  void
  TyreDynamic::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 0   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 3   ; jIndex[11] = 1   ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 4   ;
  }


  void
  TyreDynamic::DHxpDxpu_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t7   = ModelPars[iM_w__U];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t16  = L__[iL_lambda1__xo];
    real_type t17  = Fa_DD(t10);
    real_type t19  = L__[iL_lambda3__xo];
    real_type t20  = X__[iX_omega];
    real_type t21  = kappa__w_D_1(t10, t20);
    real_type t24  = t10 * t19;
    real_type t25  = kappa__w_D_1_1(t10, t20);
    result__[ 0   ] = 2 / t11 / t10 * (ModelPars[iM_w__t] + t7 * (t3 + t5)) - t17 * t16 + 2 * t21 * t19 + t25 * t24;
    real_type t27  = kappa__w_D_2(t10, t20);
    real_type t29  = kappa__w_D_1_2(t10, t20);
    result__[ 1   ] = t27 * t19 + t29 * t24;
    result__[ 2   ] = -t19;
    real_type t32  = 1.0 / t11;
    result__[ 3   ] = -2 * t32 * t7 * t2;
    result__[ 4   ] = -2 * t32 * t7 * t4;
    result__[ 5   ] = result__[1];
    real_type t38  = L__[iL_lambda2__xo];
    real_type t39  = X__[iX_p];
    real_type t40  = p__pos(t39);
    real_type t41  = TT_D_2_2(t40, t20);
    real_type t42  = X__[iX_b];
    real_type t43  = b__neg(t42);
    real_type t44  = TB_D_2_2(t43, t20);
    real_type t45  = Ma_DD(t20);
    real_type t48  = kappa__w_D_2_2(t10, t20);
    result__[ 6   ] = (t41 + t44 + t45) * t38 + t48 * t24;
    real_type t50  = TT_D_1_2(t40, t20);
    real_type t52  = p__pos_D(t39);
    result__[ 7   ] = t52 * t50 * t38;
    real_type t53  = TB_D_1_2(t43, t20);
    real_type t55  = b__neg_D(t42);
    result__[ 8   ] = t55 * t53 * t38;
    result__[ 9   ] = result__[2];
    real_type t57  = F__x_DD(X__[iX_lambda]);
    result__[ 10  ] = -ModelPars[iM_rw] * t57 * t38 + t57 * t16;
    result__[ 11  ] = result__[7];
    real_type t62  = TT_D_1_1(t40, t20);
    real_type t64  = t52 * t52;
    real_type t66  = TT_D_1(t40, t20);
    real_type t68  = p__pos_DD(t39);
    result__[ 12  ] = t64 * t62 * t38 + t68 * t66 * t38;
    result__[ 13  ] = result__[8];
    real_type t70  = TB_D_1_1(t43, t20);
    real_type t72  = t55 * t55;
    real_type t74  = TB_D_1(t43, t20);
    real_type t76  = b__neg_DD(t42);
    result__[ 14  ] = t72 * t70 * t38 + t76 * t74 * t38;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 15, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::Hu_numEqns() const { return 2; }

  void
  TyreDynamic::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_w__U];
    real_type t5   = 1.0 / X__[iX_v];
    result__[ 0   ] = 2 * t5 * t2 * U__[iU_p__o] + L__[iL_lambda4__xo];
    result__[ 1   ] = 2 * t5 * t2 * U__[iU_b__o] + L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

}

// EOF: TyreDynamic_Methods_AdjointODE.cc
