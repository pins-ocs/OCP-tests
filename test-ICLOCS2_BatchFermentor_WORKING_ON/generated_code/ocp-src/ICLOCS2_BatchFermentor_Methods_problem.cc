/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_problem.cc                      |
 |                                                                       |
 |  version: 1.0   date 6/12/2021                                        |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
#define ALIAS_v_Limit_DD(__t1) v_Limit.DD( __t1)
#define ALIAS_v_Limit_D(__t1) v_Limit.D( __t1)
#define ALIAS_s_Limit_DD(__t1) s_Limit.DD( __t1)
#define ALIAS_s_Limit_D(__t1) s_Limit.D( __t1)
#define ALIAS_p_Limit_DD(__t1) p_Limit.DD( __t1)
#define ALIAS_p_Limit_D(__t1) p_Limit.D( __t1)
#define ALIAS_x_Limit_DD(__t1) x_Limit.DD( __t1)
#define ALIAS_x_Limit_D(__t1) x_Limit.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS2_BatchFermentorDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS2_BatchFermentor::continuation_step_0( real_type s ) {
    ModelPars[iM_W] = s * ModelPars[iM_W1] + (1 - s) * ModelPars[iM_W0];
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS2_BatchFermentor::continuation_step_1( real_type s ) {
    ModelPars[iM_WX] = s * ModelPars[iM_WX1] + (1 - s) * ModelPars[iM_WX0];
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS2_BatchFermentor::continuation_step_2( real_type s ) {
    real_type t2   = 1 - s;
    real_type t3   = pow(ModelPars[iM_state_epsi0], t2);
    real_type t5   = pow(ModelPars[iM_state_epsi1], s);
    real_type t6   = t5 * t3;
    x_Limit.update_epsilon(t6);
    real_type t8   = pow(ModelPars[iM_state_tol0], t2);
    real_type t10  = pow(ModelPars[iM_state_tol1], s);
    real_type t11  = t10 * t8;
    x_Limit.update_tolerance(t11);
    s_Limit.update_epsilon(t6);
    s_Limit.update_tolerance(t11);
    v_Limit.update_epsilon(t6);
    v_Limit.update_tolerance(t11);
    p_Limit.update_epsilon(t6);
    p_Limit.update_tolerance(t11);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ICLOCS2_BatchFermentor::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = ModelPars[iM_state_tol];
    real_type t4   = x_Limit(t1 + t2);
    real_type t5   = X__[iX_p];
    real_type t7   = p_Limit(t5 + t2);
    real_type t8   = X__[iX_s];
    real_type t10  = s_Limit(t8 + t2);
    real_type t11  = X__[iX_v];
    real_type t12  = v_Limit(t11);
    real_type t14  = U__[iU_u];
    real_type t17  = ModelPars[iM_p_i];
    real_type t21  = 1.0 / ModelPars[iM_Tf] * Q__[iQ_zeta];
    real_type t26  = pow(t5 - t17 - (ModelPars[iM_p_f] - t17) * t21, 2);
    real_type t27  = ModelPars[iM_s_i];
    real_type t32  = pow(t8 - t27 - (ModelPars[iM_s_f] - t27) * t21, 2);
    real_type t33  = ModelPars[iM_v_i];
    real_type t38  = pow(t11 - t33 - (ModelPars[iM_v_f] - t33) * t21, 2);
    real_type t39  = ModelPars[iM_x_i];
    real_type t44  = pow(t1 - t39 - (ModelPars[iM_x_f] - t39) * t21, 2);
    real_type t48  = mu(t8, t1);
    real_type t49  = t1 * t48;
    real_type t52  = 1.0 / ModelPars[iM_S_f];
    real_type t53  = 1.0 / t11;
    real_type t54  = t53 * t52;
    real_type t59  = rho(t8);
    real_type t60  = t1 * t59;
    real_type result__ = t4 + t7 + t10 + t12 + t14 * ModelPars[iM_W] + (t26 + t32 + t38 + t44) * ModelPars[iM_WX] + (-t54 * t14 * t1 + t49) * L__[iL_lambda1__xo] + (-t54 * t14 * t5 - t5 * ModelPars[iM_K_degr] + t60) * L__[iL_lambda2__xo] + (-1.0 / ModelPars[iM_Yxs] * t49 - 1.0 / ModelPars[iM_Yes] * t60 - t1 / (ModelPars[iM_kappa_m] + t8) * t8 * ModelPars[iM_mu_s] + (-t52 * t8 + 1) * t53 * t14) * L__[iL_lambda3__xo] + t52 * t14 * L__[iL_lambda4__xo];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "H_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
  \*/

  real_type
  ICLOCS2_BatchFermentor::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_state_tol];
    real_type t4   = x_Limit(X__[iX_x] + t2);
    real_type t7   = p_Limit(X__[iX_p] + t2);
    real_type t10  = s_Limit(X__[iX_s] + t2);
    real_type t12  = v_Limit(X__[iX_v]);
    real_type result__ = t4 + t7 + t10 + t12;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS2_BatchFermentor::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = uControl(U__[iU_u], 0, 50);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "control_penalties_eval(...) return {}\n", result__ );
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
  ICLOCS2_BatchFermentor::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t6   = ModelPars[iM_p_i];
    real_type t10  = 1.0 / ModelPars[iM_Tf] * Q__[iQ_zeta];
    real_type t15  = pow(X__[iX_p] - t6 - (ModelPars[iM_p_f] - t6) * t10, 2);
    real_type t17  = ModelPars[iM_s_i];
    real_type t22  = pow(X__[iX_s] - t17 - (ModelPars[iM_s_f] - t17) * t10, 2);
    real_type t24  = ModelPars[iM_v_i];
    real_type t29  = pow(X__[iX_v] - t24 - (ModelPars[iM_v_f] - t24) * t10, 2);
    real_type t31  = ModelPars[iM_x_i];
    real_type t36  = pow(X__[iX_x] - t31 - (ModelPars[iM_x_f] - t31) * t10, 2);
    real_type result__ = ModelPars[iM_W] * U__[iU_u] + (t15 + t22 + t29 + t36) * ModelPars[iM_WX];
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
  ICLOCS2_BatchFermentor::mayer_target(
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
    real_type result__ = -XR__[iX_p] * XR__[iX_v];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DmayerDxxp_numEqns() const
  { return 8; }

  void
  ICLOCS2_BatchFermentor::DmayerDxxp_eval(
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
    result__[ 5   ] = -XR__[iX_v];
    result__[ 6   ] = 0;
    result__[ 7   ] = -XR__[iX_p];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 8, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer
  ICLOCS2_BatchFermentor::DlagrangeDxup_numEqns() const
  { return 5; }

  void
  ICLOCS2_BatchFermentor::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WX];
    real_type t3   = ModelPars[iM_x_i];
    real_type t7   = 1.0 / ModelPars[iM_Tf] * Q__[iQ_zeta];
    result__[ 0   ] = (2 * X__[iX_x] - 2 * t3 - 2 * (ModelPars[iM_x_f] - t3) * t7) * t1;
    real_type t14  = ModelPars[iM_p_i];
    result__[ 1   ] = (2 * X__[iX_p] - 2 * t14 - 2 * (ModelPars[iM_p_f] - t14) * t7) * t1;
    real_type t21  = ModelPars[iM_s_i];
    result__[ 2   ] = (2 * X__[iX_s] - 2 * t21 - 2 * (ModelPars[iM_s_f] - t21) * t7) * t1;
    real_type t28  = ModelPars[iM_v_i];
    result__[ 3   ] = (2 * X__[iX_v] - 2 * t28 - 2 * (ModelPars[iM_v_f] - t28) * t7) * t1;
    result__[ 4   ] = ModelPars[iM_W];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 5, i_segment );
  }

  integer
  ICLOCS2_BatchFermentor::DJDx_numEqns() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_state_tol];
    result__[ 0   ] = ALIAS_x_Limit_D(X__[iX_x] + t2);
    result__[ 1   ] = ALIAS_p_Limit_D(X__[iX_p] + t2);
    result__[ 2   ] = ALIAS_s_Limit_D(X__[iX_s] + t2);
    result__[ 3   ] = ALIAS_v_Limit_D(X__[iX_v]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DJDp_numEqns() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DJDp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DJDu_numEqns() const
  { return 1; }

  void
  ICLOCS2_BatchFermentor::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], 0, 50);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDu_eval", 1, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ICLOCS2_BatchFermentor::q_numEqns() const
  { return 1; }

  void
  ICLOCS2_BatchFermentor::q_eval(
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

  integer
  ICLOCS2_BatchFermentor::segmentLink_numEqns() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DsegmentLinkDxp_sparse(
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

  integer
  ICLOCS2_BatchFermentor::jump_numEqns() const
  { return 8; }

  void
  ICLOCS2_BatchFermentor::jump_eval(
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
    result__[ 0   ] = XR__[iX_x] - XL__[iX_x];
    result__[ 1   ] = XR__[iX_p] - XL__[iX_p];
    result__[ 2   ] = XR__[iX_s] - XL__[iX_s];
    result__[ 3   ] = XR__[iX_v] - XL__[iX_v];
    result__[ 4   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 5   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 6   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 7   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DjumpDxlxlp_numRows() const
  { return 8; }

  integer
  ICLOCS2_BatchFermentor::DjumpDxlxlp_numCols() const
  { return 16; }

  integer
  ICLOCS2_BatchFermentor::DjumpDxlxlp_nnz() const
  { return 16; }

  void
  ICLOCS2_BatchFermentor::DjumpDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 10  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 11  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 12  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 13  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 14  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 15  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DjumpDxlxlp_sparse(
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
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 16, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  ICLOCS2_BatchFermentor::post_numEqns() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::integrated_post_numEqns() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_problem.cc
