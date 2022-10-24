/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_controls.cc                                |
 |                                                                       |
 |  version: 1.0   date 11/11/2022                                       |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  TyreDynamic::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XR__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t3   = UM__[0];
    real_type t4   = p__oControl(t3, -1, 1);
    real_type t6   = LM__[3];
    real_type t7   = XL__[iX_p];
    real_type t10  = XR__[iX_p];
    real_type t13  = XL__[iX_v];
    real_type t14  = 1.0 / t13;
    real_type t15  = UM__[1];
    real_type t16  = b__oControl(t15, -1, 1);
    real_type t19  = LM__[4];
    real_type t20  = XL__[iX_b];
    real_type t23  = XR__[iX_b];
    real_type t26  = ModelPars[iM_h__b];
    real_type t28  = OnlyTractionRear(-t26 - t7);
    real_type t31  = OnlyBrakingRear(t20 - t26);
    real_type t34  = OnlyTractionRear(-t26 - t10);
    real_type t37  = OnlyBrakingRear(t23 - t26);
    real_type t39  = LM__[1];
    real_type t40  = p__pos(t7);
    real_type t41  = XL__[iX_omega];
    real_type t42  = TT(t40, t41);
    real_type t43  = b__neg(t20);
    real_type t44  = TB(t43, t41);
    real_type t45  = XL__[iX_lambda];
    real_type t46  = F__x(t45);
    real_type t47  = ModelPars[iM_rw];
    real_type t49  = Ma(t41);
    real_type t52  = p__pos(t10);
    real_type t53  = XR__[iX_omega];
    real_type t54  = TT(t52, t53);
    real_type t55  = b__neg(t23);
    real_type t56  = TB(t55, t53);
    real_type t57  = XR__[iX_lambda];
    real_type t58  = F__x(t57);
    real_type t60  = Ma(t53);
    real_type t63  = t4 * t2 + (-t7 + t3) * t6 + (-t10 + t3) * t6 + t16 * t14 + t16 * t2 + (-t20 + t15) * t19 + (-t23 + t15) * t19 + t28 * t14 + t31 * t14 + t34 * t2 + t37 * t2 + (-t47 * t46 + t42 + t44 + t49) * t39 + (-t47 * t58 + t54 + t56 + t60) * t39;
    real_type t65  = v_min(1 - t13);
    real_type t68  = v_min(1 - t1);
    real_type t70  = LM__[0];
    real_type t71  = Fa(t13);
    real_type t74  = Fa(t1);
    real_type t79  = t3 * t3;
    real_type t80  = t15 * t15;
    real_type t84  = ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t79 + t80);
    real_type t88  = 1.0 / ModelPars[iM_lambda__max];
    real_type t89  = t45 * t88;
    real_type t91  = LongSlipRear_min(-1 - t89);
    real_type t94  = LongSlipRear_max(t89 - 1);
    real_type t96  = t57 * t88;
    real_type t98  = LongSlipRear_min(-1 - t96);
    real_type t101 = LongSlipRear_max(t96 - 1);
    real_type t103 = LM__[2];
    real_type t105 = kappa__w(t1, t53);
    real_type t109 = kappa__w(t13, t41);
    real_type t112 = t65 * t14 + t68 * t2 + (t46 - t71) * t70 + (t58 - t74) * t70 + t4 * t14 + t14 * t84 + t2 * t84 + t91 * t14 + t94 * t14 + t98 * t2 + t101 * t2 + (t105 - t57) * t1 * t103 + (t109 - t45) * t13 * t103;
    real_type result__ = t63 + t112;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::g_numEqns() const { return 2; }

  void
  TyreDynamic::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = UM__[0];
    real_type t2   = ModelPars[iM_w__U];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / XL__[iX_v];
    real_type t10  = ALIAS_p__oControl_D_1(t1, -1, 1);
    real_type t13  = 1.0 / XR__[iX_v];
    result__[ 0   ] = t10 * t13 + t10 * t5 + 2 * t13 * t3 + 2 * t5 * t3 + 2 * LM__[3];
    real_type t17  = UM__[1];
    real_type t18  = t2 * t17;
    real_type t23  = ALIAS_b__oControl_D_1(t17, -1, 1);
    result__[ 1   ] = 2 * t13 * t18 + t23 * t13 + 2 * t5 * t18 + t23 * t5 + 2 * LM__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DgDxlxlp_numRows() const { return 2; }
  integer TyreDynamic::DgDxlxlp_numCols() const { return 20; }
  integer TyreDynamic::DgDxlxlp_nnz()     const { return 8; }

  void
  TyreDynamic::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 18  ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 10  ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 19  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = UM__[0];
    real_type t2   = ModelPars[iM_w__U];
    real_type t3   = t2 * t1;
    real_type t5   = XL__[iX_v] * XL__[iX_v];
    real_type t6   = 1.0 / t5;
    real_type t9   = ALIAS_p__oControl_D_1(t1, -1, 1);
    result__[ 0   ] = -2 * t6 * t3 - t9 * t6;
    result__[ 1   ] = 1.0;
    real_type t12  = XR__[iX_v] * XR__[iX_v];
    real_type t13  = 1.0 / t12;
    result__[ 2   ] = -2 * t13 * t3 - t9 * t13;
    result__[ 3   ] = 1.0;
    real_type t17  = UM__[1];
    real_type t18  = t2 * t17;
    real_type t21  = ALIAS_b__oControl_D_1(t17, -1, 1);
    result__[ 4   ] = -2 * t6 * t18 - t21 * t6;
    result__[ 5   ] = 1.0;
    result__[ 6   ] = -2 * t13 * t18 - t21 * t13;
    result__[ 7   ] = 1.0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DgDu_numRows() const { return 2; }
  integer TyreDynamic::DgDu_numCols() const { return 2; }
  integer TyreDynamic::DgDu_nnz()     const { return 2; }

  void
  TyreDynamic::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_w__U];
    real_type t3   = 1.0 / XL__[iX_v];
    real_type t5   = 2 * t3 * t1;
    real_type t7   = ALIAS_p__oControl_D_1_1(UM__[0], -1, 1);
    real_type t10  = 1.0 / XR__[iX_v];
    real_type t12  = 2 * t10 * t1;
    result__[ 0   ] = t7 * t10 + t7 * t3 + t12 + t5;
    real_type t15  = ALIAS_b__oControl_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = t15 * t10 + t15 * t3 + t12 + t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  TyreDynamic::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "TyreDynamic::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  TyreDynamic::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t3   = U__[iU_b__o];
    real_type t4   = b__oControl(t3, -1, 1);
    real_type t6   = U__[iU_p__o];
    real_type t7   = p__oControl(t6, -1, 1);
    real_type t9   = X__[iX_b];
    real_type t10  = ModelPars[iM_h__b];
    real_type t12  = OnlyBrakingRear(t9 - t10);
    real_type t14  = X__[iX_p];
    real_type t16  = OnlyTractionRear(-t10 - t14);
    real_type t20  = X__[iX_lambda];
    real_type t21  = t20 / ModelPars[iM_lambda__max];
    real_type t23  = LongSlipRear_min(-1 - t21);
    real_type t26  = LongSlipRear_max(t21 - 1);
    real_type t29  = v_min(1 - t1);
    real_type t35  = F__x(t20);
    real_type t36  = Fa(t1);
    real_type t38  = pow(V__[0] * ModelPars[iM_m] * t1 - t35 + t36, 2);
    real_type t43  = p__pos(t14);
    real_type t44  = X__[iX_omega];
    real_type t45  = TT(t43, t44);
    real_type t46  = b__neg(t9);
    real_type t47  = TB(t46, t44);
    real_type t50  = Ma(t44);
    real_type t52  = pow(V__[1] * t1 * ModelPars[iM_Iw] + ModelPars[iM_rw] * t35 - t45 - t47 - t50, 2);
    real_type t57  = kappa__w(t1, t44);
    real_type t61  = pow(V__[2] * ModelPars[iM_l__x] * t1 - (t57 - t20) * t1, 2);
    real_type t67  = pow(ModelPars[iM_tau__p] * t1 * V__[3] + t14 - t6, 2);
    real_type t73  = pow(ModelPars[iM_tau__b] * t1 * V__[4] - t3 + t9, 2);
    real_type result__ = t12 * t2 + t16 * t2 + t23 * t2 + t26 * t2 + t29 * t2 + t4 * t2 + t7 * t2 + t38 + t52 + t61 + t67 + t73;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::DmDu_numEqns() const { return 2; }

  void
  TyreDynamic::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t3   = U__[iU_p__o];
    real_type t4   = ALIAS_p__oControl_D_1(t3, -1, 1);
    result__[ 0   ] = -2 * ModelPars[iM_tau__p] * t1 * V__[3] + t4 * t2 + 2 * t3 - 2 * X__[iX_p];
    real_type t14  = U__[iU_b__o];
    real_type t15  = ALIAS_b__oControl_D_1(t14, -1, 1);
    result__[ 1   ] = -2 * ModelPars[iM_tau__b] * t1 * V__[4] + t15 * t2 + 2 * t14 - 2 * X__[iX_b];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DmDuu_numRows() const { return 2; }
  integer TyreDynamic::DmDuu_numCols() const { return 2; }
  integer TyreDynamic::DmDuu_nnz()     const { return 2; }

  void
  TyreDynamic::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  TyreDynamic::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1.0 / X__[iX_v];
    real_type t4   = ALIAS_p__oControl_D_1_1(U__[iU_p__o], -1, 1);
    result__[ 0   ] = t4 * t2 + 2;
    real_type t7   = ALIAS_b__oControl_D_1_1(U__[iU_b__o], -1, 1);
    result__[ 1   ] = t7 * t2 + 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: TyreDynamic_Methods_controls.cc
