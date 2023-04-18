/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_controls.cc                                |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  TyreDynamic::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t10  = X__[iX_v];
    real_type t11  = 1.0 / t10;
    real_type t13  = b__oControl(t4, -1, 1);
    real_type t15  = p__oControl(t2, -1, 1);
    real_type t17  = X__[iX_b];
    real_type t18  = ModelPars[iM_h__b];
    real_type t20  = OnlyBrakingRear(t17 - t18);
    real_type t22  = X__[iX_p];
    real_type t24  = OnlyTractionRear(-t18 - t22);
    real_type t28  = X__[iX_lambda];
    real_type t29  = t28 / ModelPars[iM_lambda__max];
    real_type t31  = LongSlipRear_min(-1 - t29);
    real_type t34  = LongSlipRear_max(t29 - 1);
    real_type t37  = v_min(1 - t10);
    real_type t40  = F__x(t28);
    real_type t41  = Fa(t10);
    real_type t45  = p__pos(t22);
    real_type t46  = X__[iX_omega];
    real_type t47  = TT(t45, t46);
    real_type t48  = b__neg(t17);
    real_type t49  = TB(t48, t46);
    real_type t52  = Ma(t46);
    real_type t57  = kappa__w(t10, t46);
    real_type result__ = t11 * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5)) + t13 * t11 + t15 * t11 + t20 * t11 + t24 * t11 + t31 * t11 + t34 * t11 + t37 * t11 + (t40 - t41) * MU__[0] + (-ModelPars[iM_rw] * t40 + t47 + t49 + t52) * MU__[1] + (t57 - t28) * t10 * MU__[2] + (-t22 + t2) * MU__[3] + (-t17 + t4) * MU__[4];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::g_numEqns() const { return 2; }

  void
  TyreDynamic::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_p__o];
    real_type t2   = ModelPars[iM_w__U];
    real_type t5   = 1.0 / X__[iX_v];
    real_type t8   = ALIAS_p__oControl_D_1(t1, -1, 1);
    result__[ 0   ] = 2 * t1 * t2 * t5 + t5 * t8 + MU__[3];
    real_type t11  = U__[iU_b__o];
    real_type t15  = ALIAS_b__oControl_D_1(t11, -1, 1);
    result__[ 1   ] = 2 * t11 * t2 * t5 + t15 * t5 + MU__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DgDxpm_numRows() const { return 2; }
  integer TyreDynamic::DgDxpm_numCols() const { return 10; }
  integer TyreDynamic::DgDxpm_nnz()     const { return 4; }

  void
  TyreDynamic::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_p__o];
    real_type t2   = ModelPars[iM_w__U];
    real_type t5   = X__[iX_v] * X__[iX_v];
    real_type t6   = 1.0 / t5;
    real_type t9   = ALIAS_p__oControl_D_1(t1, -1, 1);
    result__[ 0   ] = -2 * t6 * t2 * t1 - t9 * t6;
    result__[ 1   ] = 1;
    real_type t11  = U__[iU_b__o];
    real_type t15  = ALIAS_b__oControl_D_1(t11, -1, 1);
    result__[ 2   ] = -2 * t6 * t2 * t11 - t15 * t6;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 4, i_segment );
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
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = 1.0 / X__[iX_v];
    real_type t5   = 2 * t3 * ModelPars[iM_w__U];
    real_type t7   = ALIAS_p__oControl_D_1_1(U__[iU_p__o], -1, 1);
    result__[ 0   ] = t7 * t3 + t5;
    real_type t10  = ALIAS_b__oControl_D_1_1(U__[iU_b__o], -1, 1);
    result__[ 1   ] = t10 * t3 + t5;
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
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "TyreDynamic::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: TyreDynamic_Methods_controls.cc
