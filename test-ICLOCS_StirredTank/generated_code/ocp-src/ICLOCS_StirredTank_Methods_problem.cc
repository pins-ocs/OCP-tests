/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_problem.cc                          |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_max_DD(__t1) x2bound_max.DD( __t1)
#define ALIAS_x2bound_max_D(__t1) x2bound_max.D( __t1)
#define ALIAS_x2bound_min_DD(__t1) x2bound_min.DD( __t1)
#define ALIAS_x2bound_min_D(__t1) x2bound_min.D( __t1)
#define ALIAS_x1bound_max_DD(__t1) x1bound_max.DD( __t1)
#define ALIAS_x1bound_max_D(__t1) x1bound_max.D( __t1)
#define ALIAS_x1bound_min_DD(__t1) x1bound_min.DD( __t1)
#define ALIAS_x1bound_min_D(__t1) x1bound_min.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_StirredTankDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_StirredTank::continuation_step_0( real_type s ) {
    real_type t1   = ModelPars[iM_epsi_ctrl0];
    uControl.update_epsilon(t1 + (ModelPars[iM_epsi_ctrl1] - t1) * s);
    real_type t6   = ModelPars[iM_tol_ctrl0];
    uControl.update_tolerance(t6 + (ModelPars[iM_tol_ctrl1] - t6) * s);
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_StirredTank::continuation_step_1( real_type s ) {
    real_type t1   = ModelPars[iM_w_time_max];
    ModelPars[iM_w_time] = t1 + (ModelPars[iM_w_time_min] - t1) * s;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ICLOCS_StirredTank::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_TimeSize];
    real_type t4   = tfbound(ModelPars[iM_T_min] - t2);
    real_type t5   = X__[iX_x1];
    real_type t6   = x1bound_min(-t5);
    real_type t7   = t5 - 1;
    real_type t8   = x1bound_max(t7);
    real_type t9   = X__[iX_x2];
    real_type t10  = x2bound_min(-t9);
    real_type t12  = x2bound_max(t9 - 1);
    real_type t14  = log(t2);
    real_type t18  = pow(t5 - ModelPars[iM_x1_f], 2);
    real_type t21  = pow(t9 - ModelPars[iM_x2_f], 2);
    real_type t22  = U__[iU_u];
    real_type t25  = pow(t22 - ModelPars[iM_u_f], 2);
    real_type t32  = 1.0 / ModelPars[iM_theta];
    real_type t39  = exp(-1.0 / t9 * ModelPars[iM_En]);
    real_type t40  = t39 * t5 * ModelPars[iM_k];
    real_type result__ = t4 + t6 + t8 + t10 + t12 + (t14 * ModelPars[iM_w_time] + t18 + t21 + t25) * t2 + (-t32 * t7 - t40) * t2 * L__[iL_lambda1__xo] + (t32 * (ModelPars[iM_Tf] - t9) + t40 - (t9 - ModelPars[iM_Tc]) * t22 * ModelPars[iM_a]) * t2 * L__[iL_lambda2__xo];
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
  ICLOCS_StirredTank::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JP_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_StirredTank::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = uControl(U__[iU_u], 0, 2);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_StirredTank::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = tfbound(ModelPars[iM_T_min] - P__[iP_TimeSize]);
    real_type t5   = X__[iX_x1];
    real_type t6   = x1bound_min(-t5);
    real_type t8   = x1bound_max(t5 - 1);
    real_type t9   = X__[iX_x2];
    real_type t10  = x2bound_min(-t9);
    real_type t12  = x2bound_max(t9 - 1);
    real_type result__ = t4 + t6 + t8 + t10 + t12;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "LT_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _
   |  | |   __ _ __ _ _ _ __ _ _ _  __ _ ___
   |  | |__/ _` / _` | '_/ _` | ' \/ _` / -_)
   |  |____\__,_\__, |_| \__,_|_||_\__, \___|
   |            |___/              |___/
  \*/

  real_type
  ICLOCS_StirredTank::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t3   = log(t1);
    real_type t8   = pow(X__[iX_x1] - ModelPars[iM_x1_f], 2);
    real_type t12  = pow(X__[iX_x2] - ModelPars[iM_x2_f], 2);
    real_type t16  = pow(U__[iU_u] - ModelPars[iM_u_f], 2);
    real_type result__ = (t3 * ModelPars[iM_w_time] + t12 + t16 + t8) * t1;
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
  ICLOCS_StirredTank::mayer_target(
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

  integer ICLOCS_StirredTank::DmayerDxxp_numEqns() const { return 5; }

  void
  ICLOCS_StirredTank::DmayerDxxp_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 5, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer ICLOCS_StirredTank::DlagrangeDxup_numEqns() const { return 4; }

  void
  ICLOCS_StirredTank::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t4   = X__[iX_x1] - ModelPars[iM_x1_f];
    result__[ 0   ] = 2 * t4 * t1;
    real_type t8   = X__[iX_x2] - ModelPars[iM_x2_f];
    result__[ 1   ] = 2 * t8 * t1;
    real_type t12  = U__[iU_u] - ModelPars[iM_u_f];
    result__[ 2   ] = 2 * t12 * t1;
    real_type t14  = ModelPars[iM_w_time];
    real_type t15  = log(t1);
    real_type t17  = t4 * t4;
    real_type t18  = t8 * t8;
    real_type t19  = t12 * t12;
    result__[ 3   ] = t15 * t14 + t14 + t17 + t18 + t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 4, i_segment );
  }

  /*\
   |   ___ ____   ___  ____ _____
   |  |_ _|  _ \ / _ \|  _ \_   _|
   |   | || |_) | | | | |_) || |
   |   | ||  __/| |_| |  __/ | |
   |  |___|_|    \___/|_|    |_|
  \*/
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::IPOPT_hess_numRows() const { return 4; }
  integer ICLOCS_StirredTank::IPOPT_hess_numCols() const { return 4; }
  integer ICLOCS_StirredTank::IPOPT_hess_nnz()     const { return 14; }

  void
  ICLOCS_StirredTank::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
    iIndex[10] = 3   ; jIndex[10] = 0   ;
    iIndex[11] = 3   ; jIndex[11] = 1   ;
    iIndex[12] = 3   ; jIndex[12] = 2   ;
    iIndex[13] = 3   ; jIndex[13] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::IPOPT_hess_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            sigma__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    result__[ 0   ] = 2 * t1 * sigma__;
    real_type t3   = L__[iL_lambda1__xo];
    real_type t5   = ModelPars[iM_k];
    real_type t6   = t5 * t1 * t3;
    real_type t7   = ModelPars[iM_En];
    real_type t8   = X__[iX_x2];
    real_type t9   = t8 * t8;
    real_type t14  = exp(-1.0 / t8 * t7);
    real_type t15  = t14 / t9 * t7;
    real_type t17  = L__[iL_lambda2__xo];
    real_type t18  = t1 * t17;
    result__[ 1   ] = t15 * t5 * t18 - t15 * t6;
    real_type t21  = X__[iX_x1];
    real_type t27  = 1.0 / ModelPars[iM_theta];
    result__[ 2   ] = (2 * t21 - 2 * ModelPars[iM_x1_f]) * sigma__ + (-t14 * t5 - t27) * t3 + t14 * t5 * t17;
    result__[ 3   ] = result__[1];
    real_type t35  = 1.0 / t9 / t8;
    real_type t40  = t7 * t7;
    real_type t42  = t9 * t9;
    real_type t43  = 1.0 / t42;
    real_type t47  = t21 * t5;
    result__[ 4   ] = result__[0] + 2 * t14 * t35 * t7 * t21 * t6 - t14 * t43 * t40 * t21 * t6 + (-2 * t14 * t35 * t7 * t47 + t14 * t43 * t40 * t47) * t18;
    real_type t57  = ModelPars[iM_a];
    result__[ 5   ] = -t57 * t18;
    real_type t67  = U__[iU_u];
    result__[ 6   ] = (2 * t8 - 2 * ModelPars[iM_x2_f]) * sigma__ - t15 * t21 * t5 * t3 + (t15 * t47 - t67 * t57 - t27) * t17;
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[0];
    result__[ 9   ] = (2 * t67 - 2 * ModelPars[iM_u_f]) * sigma__ - (t8 - ModelPars[iM_Tc]) * t57 * t17;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[6];
    result__[ 12  ] = result__[9];
    result__[ 13  ] = 1.0 / t1 * ModelPars[iM_w_time] * sigma__;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 14, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ICLOCS_StirredTank::q_numEqns() const
  { return 1; }

  void
  ICLOCS_StirredTank::q_eval(
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

  integer ICLOCS_StirredTank::segmentLink_numEqns() const { return 0; }

  void
  ICLOCS_StirredTank::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::DsegmentLinkDxp_numRows() const { return 0; }
  integer ICLOCS_StirredTank::DsegmentLinkDxp_numCols() const { return 0; }
  integer ICLOCS_StirredTank::DsegmentLinkDxp_nnz() const { return 0; }

  void
  ICLOCS_StirredTank::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DsegmentLinkDxp_sparse(
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

  integer ICLOCS_StirredTank::jump_numEqns() const { return 4; }

  void
  ICLOCS_StirredTank::jump_eval(
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
    result__[ 0   ] = XR__[iX_x1] - XL__[iX_x1];
    result__[ 1   ] = XR__[iX_x2] - XL__[iX_x2];
    result__[ 2   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 3   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 4, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DjumpDxlxlp_numRows() const { return 4; }
  integer ICLOCS_StirredTank::DjumpDxlxlp_numCols() const { return 9; }
  integer ICLOCS_StirredTank::DjumpDxlxlp_nnz()     const { return 8; }

  void
  ICLOCS_StirredTank::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DjumpDxlxlp_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 8, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer ICLOCS_StirredTank::post_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::post_eval(
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
    result__[ 0   ] = P__[iP_TimeSize] * Q__[iQ_zeta];
    Mechatronix::check_in_segment( result__, "post_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::integrated_post_numEqns() const { return 0; }

  void
  ICLOCS_StirredTank::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: ICLOCS_StirredTank_Methods_problem.cc
