/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_problem.cc                                 |
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
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  TyreDynamic::continuation_step_0( real_type s ) {
    real_type t1   = ModelPars[iM_w__t0];
    ModelPars[iM_w__t] = t1 + (ModelPars[iM_w__t1] - t1) * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  TyreDynamic::continuation_step_1( real_type s ) {
    real_type t1   = ModelPars[iM_eps_c0];
    real_type t5   = t1 + (ModelPars[iM_eps_c1] - t1) * s;
    p__oControl.update_epsilon(t5);
    real_type t6   = ModelPars[iM_tol_c0];
    real_type t10  = t6 + (ModelPars[iM_tol_c1] - t6) * s;
    p__oControl.update_tolerance(t10);
    b__oControl.update_epsilon(t5);
    b__oControl.update_tolerance(t10);
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  TyreDynamic::penalties_check_cell(
    NodeType const &     LEFT__,
    NodeType const &     RIGHT__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    // midpoint
    real_type Q__[1], X__[5];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    bool res = true;
    real_type t2   = ModelPars[iM_h__b];
    res = res && OnlyBrakingRear.check_range(X__[iX_b] - t2, m_max_penalty_value);
    res = res && OnlyTractionRear.check_range(-t2 - X__[iX_p], m_max_penalty_value);
    real_type t9   = 1.0 / ModelPars[iM_lambda__max] * X__[iX_lambda];
    res = res && LongSlipRear_min.check_range(-1 - t9, m_max_penalty_value);
    res = res && LongSlipRear_max.check_range(t9 - 1, m_max_penalty_value);
    res = res && v_min.check_range(1 - X__[iX_v], m_max_penalty_value);
    return res;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  TyreDynamic::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t10  = X__[iX_v];
    real_type t14  = X__[iX_lambda];
    real_type t15  = F__x(t14);
    real_type t16  = Fa(t10);
    real_type t20  = X__[iX_p];
    real_type t21  = p__pos(t20);
    real_type t22  = X__[iX_omega];
    real_type t23  = TT(t21, t22);
    real_type t24  = X__[iX_b];
    real_type t25  = b__neg(t24);
    real_type t26  = TB(t25, t22);
    real_type t29  = Ma(t22);
    real_type t34  = kappa__w(t10, t22);
    real_type result__ = 1.0 / t10 * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5)) + (t15 - t16) * L__[iL_lambda1__xo] + (-ModelPars[iM_rw] * t15 + t23 + t26 + t29) * L__[iL_lambda2__xo] + (t34 - t14) * t10 * L__[iL_lambda3__xo] + (-t20 + t2) * L__[iL_lambda4__xo] + (-t24 + t4) * L__[iL_lambda5__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  TyreDynamic::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = U__[iU_p__o] * U__[iU_p__o];
    real_type t5   = U__[iU_b__o] * U__[iU_b__o];
    real_type result__ = 1.0 / X__[iX_v] * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5));
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "lagrange_target(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   __  __
   |  |  \/  |__ _ _  _ ___ _ _
   |  | |\/| / _` | || / -_) '_|
   |  |_|  |_\__,_|\_, \___|_|
   |               |__/
  \*/

  real_type
  TyreDynamic::mayer_target(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::DmayerDxxp_numEqns() const { return 10; }

  void
  TyreDynamic::DmayerDxxp_eval(
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
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    result__[ 9   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2mayerD2xxp_numRows() const { return 10; }
  integer TyreDynamic::D2mayerD2xxp_numCols() const { return 10; }
  integer TyreDynamic::D2mayerD2xxp_nnz()     const { return 0; }

  void
  TyreDynamic::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::D2mayerD2xxp_sparse(
    NodeType const     & LEFT__,
    NodeType const     & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer TyreDynamic::DlagrangeDxpu_numEqns() const { return 7; }

  void
  TyreDynamic::DlagrangeDxpu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t7   = ModelPars[iM_w__U];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    result__[ 0   ] = -1.0 / t11 * (ModelPars[iM_w__t] + t7 * (t3 + t5));
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    real_type t15  = 1.0 / t10;
    result__[ 5   ] = 2 * t15 * t7 * t2;
    result__[ 6   ] = 2 * t15 * t7 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2lagrangeD2xpu_numRows() const { return 7; }
  integer TyreDynamic::D2lagrangeD2xpu_numCols() const { return 7; }
  integer TyreDynamic::D2lagrangeD2xpu_nnz()     const { return 7; }

  void
  TyreDynamic::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 5   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 6   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
  }


  void
  TyreDynamic::D2lagrangeD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_p__o];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = t4 * t4;
    real_type t7   = ModelPars[iM_w__U];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    result__[ 0   ] = 2 / t11 / t10 * (ModelPars[iM_w__t] + t7 * (t3 + t5));
    real_type t16  = 1.0 / t11;
    result__[ 1   ] = -2 * t16 * t7 * t2;
    result__[ 2   ] = -2 * t16 * t7 * t4;
    result__[ 3   ] = result__[1];
    result__[ 4   ] = 2 / t10 * t7;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xpu_eval", 7, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  TyreDynamic::q_numEqns() const
  { return 1; }

  void
  TyreDynamic::q_eval(
    integer        i_segment,
    real_type      s,
    Q_pointer_type result__
  ) const {
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = s;
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer TyreDynamic::segmentLink_numEqns() const { return 0; }

  void
  TyreDynamic::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::DsegmentLinkDxp_numRows() const { return 0; }
  integer TyreDynamic::DsegmentLinkDxp_numCols() const { return 0; }
  integer TyreDynamic::DsegmentLinkDxp_nnz() const { return 0; }

  void
  TyreDynamic::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer TyreDynamic::jump_numEqns() const { return 10; }

  void
  TyreDynamic::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    real_type t1   = XR__[iX_v];
    real_type t2   = XL__[iX_v];
    result__[ 0   ] = t1 - t2;
    result__[ 1   ] = XR__[iX_omega] - XL__[iX_omega];
    result__[ 2   ] = XR__[iX_lambda] - XL__[iX_lambda];
    result__[ 3   ] = XR__[iX_p] - XL__[iX_p];
    result__[ 4   ] = XR__[iX_b] - XL__[iX_b];
    real_type t13  = ModelPars[iM_m];
    result__[ 5   ] = t13 * t1 * LR__[iL_lambda1__xo] - t13 * t2 * LL__[iL_lambda1__xo];
    real_type t20  = ModelPars[iM_Iw];
    result__[ 6   ] = t20 * t1 * LR__[iL_lambda2__xo] - t20 * t2 * LL__[iL_lambda2__xo];
    real_type t27  = ModelPars[iM_l__x];
    result__[ 7   ] = t27 * t1 * LR__[iL_lambda3__xo] - t27 * t2 * LL__[iL_lambda3__xo];
    real_type t34  = ModelPars[iM_tau__p];
    result__[ 8   ] = t34 * t1 * LR__[iL_lambda4__xo] - t34 * t2 * LL__[iL_lambda4__xo];
    real_type t41  = ModelPars[iM_tau__b];
    result__[ 9   ] = t41 * t1 * LR__[iL_lambda5__xo] - t41 * t2 * LL__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DjumpDxlxlp_numRows() const { return 10; }
  integer TyreDynamic::DjumpDxlxlp_numCols() const { return 20; }
  integer TyreDynamic::DjumpDxlxlp_nnz()     const { return 30; }

  void
  TyreDynamic::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 10  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 11  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 12  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 13  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 14  ;
    iIndex[10] = 5   ; jIndex[10] = 0   ;
    iIndex[11] = 5   ; jIndex[11] = 5   ;
    iIndex[12] = 5   ; jIndex[12] = 10  ;
    iIndex[13] = 5   ; jIndex[13] = 15  ;
    iIndex[14] = 6   ; jIndex[14] = 0   ;
    iIndex[15] = 6   ; jIndex[15] = 6   ;
    iIndex[16] = 6   ; jIndex[16] = 10  ;
    iIndex[17] = 6   ; jIndex[17] = 16  ;
    iIndex[18] = 7   ; jIndex[18] = 0   ;
    iIndex[19] = 7   ; jIndex[19] = 7   ;
    iIndex[20] = 7   ; jIndex[20] = 10  ;
    iIndex[21] = 7   ; jIndex[21] = 17  ;
    iIndex[22] = 8   ; jIndex[22] = 0   ;
    iIndex[23] = 8   ; jIndex[23] = 8   ;
    iIndex[24] = 8   ; jIndex[24] = 10  ;
    iIndex[25] = 8   ; jIndex[25] = 18  ;
    iIndex[26] = 9   ; jIndex[26] = 0   ;
    iIndex[27] = 9   ; jIndex[27] = 9   ;
    iIndex[28] = 9   ; jIndex[28] = 10  ;
    iIndex[29] = 9   ; jIndex[29] = 19  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::DjumpDxlxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    real_type t1   = ModelPars[iM_m];
    result__[ 10  ] = -LL__[iL_lambda1__xo] * t1;
    real_type t4   = XL__[iX_v];
    result__[ 11  ] = -t1 * t4;
    result__[ 12  ] = LR__[iL_lambda1__xo] * t1;
    real_type t7   = XR__[iX_v];
    result__[ 13  ] = t1 * t7;
    real_type t8   = ModelPars[iM_Iw];
    result__[ 14  ] = -LL__[iL_lambda2__xo] * t8;
    result__[ 15  ] = -t4 * t8;
    result__[ 16  ] = LR__[iL_lambda2__xo] * t8;
    result__[ 17  ] = t7 * t8;
    real_type t13  = ModelPars[iM_l__x];
    result__[ 18  ] = -LL__[iL_lambda3__xo] * t13;
    result__[ 19  ] = -t13 * t4;
    result__[ 20  ] = LR__[iL_lambda3__xo] * t13;
    result__[ 21  ] = t13 * t7;
    real_type t18  = ModelPars[iM_tau__p];
    result__[ 22  ] = -LL__[iL_lambda4__xo] * t18;
    result__[ 23  ] = -t18 * t4;
    result__[ 24  ] = LR__[iL_lambda4__xo] * t18;
    result__[ 25  ] = t18 * t7;
    real_type t23  = ModelPars[iM_tau__b];
    result__[ 26  ] = -LL__[iL_lambda5__xo] * t23;
    result__[ 27  ] = -t23 * t4;
    result__[ 28  ] = LR__[iL_lambda5__xo] * t23;
    result__[ 29  ] = t23 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 30, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer TyreDynamic::post_numEqns() const { return 20; }

  void
  TyreDynamic::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = b__oControl(U__[iU_b__o], -1, 1);
    result__[ 1   ] = p__oControl(U__[iU_p__o], -1, 1);
    real_type t3   = X__[iX_b];
    real_type t4   = ModelPars[iM_h__b];
    result__[ 2   ] = OnlyBrakingRear(t3 - t4);
    real_type t6   = X__[iX_p];
    result__[ 3   ] = OnlyTractionRear(-t4 - t6);
    real_type t10  = X__[iX_lambda];
    real_type t11  = t10 / ModelPars[iM_lambda__max];
    result__[ 4   ] = LongSlipRear_min(-1 - t11);
    result__[ 5   ] = LongSlipRear_max(t11 - 1);
    real_type t14  = X__[iX_v];
    result__[ 6   ] = v_min(1 - t14);
    real_type t21  = F__x(t10);
    result__[ 7   ] = t21 / ModelPars[iM_m] / ModelPars[iM_g];
    real_type t22  = X__[iX_omega];
    result__[ 8   ] = kappa__w(t14, t22);
    result__[ 9   ] = t21;
    result__[ 10  ] = p__pos(t6);
    result__[ 11  ] = p__neg(t6);
    result__[ 12  ] = b__pos(t3);
    result__[ 13  ] = b__neg(t3);
    result__[ 14  ] = TT__env(t22);
    result__[ 15  ] = BT__env(t22);
    result__[ 16  ] = TT(result__[10], t22);
    result__[ 17  ] = TB(result__[13], t22);
    result__[ 18  ] = Fa(t14);
    result__[ 19  ] = Ma(t22);
    // do not check
    // Mechatronix::check_in_segment( result__, "post_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::integrated_post_numEqns() const { return 2; }

  void
  TyreDynamic::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1.0 / X__[iX_v];
    result__[ 1   ] = 1;
    // do not check
    // Mechatronix::check_in_segment( result__, "integrated_post_eval", 2, i_segment );
  }

}

// EOF: TyreDynamic_Methods_problem.cc
