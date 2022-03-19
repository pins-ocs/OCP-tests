/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_problem.cc                      |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_TwoLinkRobotArmDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_TwoLinkRobotArm::continuation_step_0( real_type s ) {
    ModelPars[iM_W] = s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS_TwoLinkRobotArm::continuation_step_1( real_type s ) {
    real_type t2   = 1 - s;
    real_type t3   = pow(ModelPars[iM_u_epsilon0], t2);
    real_type t5   = pow(ModelPars[iM_u_epsilon1], s);
    real_type t6   = t5 * t3;
    u1Control.update_epsilon(t6);
    real_type t8   = pow(ModelPars[iM_u_tolerance0], t2);
    real_type t10  = pow(ModelPars[iM_u_tolerance1], s);
    real_type t11  = t10 * t8;
    u1Control.update_tolerance(t11);
    u2Control.update_epsilon(t6);
    u2Control.update_tolerance(t11);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ICLOCS_TwoLinkRobotArm::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t4   = U__[iU_u1];
    real_type t5   = t4 * t4;
    real_type t6   = U__[iU_u2];
    real_type t7   = t6 * t6;
    real_type t12  = X__[iX_theta];
    real_type t13  = sin(t12);
    real_type t14  = cos(t12);
    real_type t15  = t14 * t13;
    real_type t16  = X__[iX_omega__alpha];
    real_type t17  = t16 * t16;
    real_type t20  = X__[iX_omega__beta];
    real_type t21  = t20 * t20;
    real_type t28  = t13 * t13;
    real_type t31  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t28);
    real_type result__ = (t5 + t7) * t2 * ModelPars[iM_rho] + t31 * (9.0 / 4.0 * t17 * t15 + 2 * t21 + 4.0 / 3.0 * t4 - 4.0 / 3.0 * t6 - 3.0 / 2.0 * t6 * t14) * t2 * L__[iL_lambda1__xo] - t31 * (9.0 / 4.0 * t21 * t15 + 7.0 / 2.0 * t17 - 7.0 / 3.0 * t6 + 3.0 / 2.0 * (t4 - t6) * t14) * t2 * L__[iL_lambda2__xo] + (t20 - t16) * t2 * L__[iL_lambda3__xo] + t16 * t2 * L__[iL_lambda4__xo];
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
  ICLOCS_TwoLinkRobotArm::JP_eval(
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
  ICLOCS_TwoLinkRobotArm::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = u1Control(U__[iU_u1], -1, 1);
    real_type t6   = u2Control(U__[iU_u2], -1, 1);
    real_type result__ = t3 * t1 + t6 * t1;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_TwoLinkRobotArm::LT_eval(
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
  ICLOCS_TwoLinkRobotArm::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t5   = U__[iU_u1] * U__[iU_u1];
    real_type t7   = U__[iU_u2] * U__[iU_u2];
    real_type result__ = (t5 + t7) * P__[iP_T] * ModelPars[iM_rho];
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
  ICLOCS_TwoLinkRobotArm::mayer_target(
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
    real_type t2   = 1 - ModelPars[iM_W];
    real_type t3   = ModelPars[iM_T_guess];
    real_type t4   = t3 * t3;
    real_type t6   = P__[iP_T];
    real_type t11  = t6 * t6;
    real_type result__ = 1.0 / t6 * (-2 * t3 * t2 * t6 + t4 * t2 + t11);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::DmayerDxxp_numEqns() const { return 9; }

  void
  ICLOCS_TwoLinkRobotArm::DmayerDxxp_eval(
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
    real_type t2   = -1 + ModelPars[iM_W];
    real_type t3   = ModelPars[iM_T_guess];
    real_type t5   = P__[iP_T];
    real_type t11  = t3 * t3;
    real_type t16  = t5 * t5;
    result__[ 8   ] = 1.0 / t5 * (2 * t3 * t2 + 2 * t5) - 1.0 / t16 * (2 * t3 * t2 * t5 - t11 * t2 + t16);
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 9, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer ICLOCS_TwoLinkRobotArm::DlagrangeDxup_numEqns() const { return 7; }

  void
  ICLOCS_TwoLinkRobotArm::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    real_type t1   = ModelPars[iM_rho];
    real_type t3   = P__[iP_T] * t1;
    real_type t4   = U__[iU_u1];
    result__[ 4   ] = 2 * t4 * t3;
    real_type t6   = U__[iU_u2];
    result__[ 5   ] = 2 * t6 * t3;
    real_type t8   = t4 * t4;
    real_type t9   = t6 * t6;
    result__[ 6   ] = (t8 + t9) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 7, i_segment );
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
  integer ICLOCS_TwoLinkRobotArm::IPOPT_hess_numRows() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::IPOPT_hess_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::IPOPT_hess_nnz()     const { return 23; }

  void
  ICLOCS_TwoLinkRobotArm::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 5   ;
    iIndex[11] = 2   ; jIndex[11] = 6   ;
    iIndex[12] = 4   ; jIndex[12] = 2   ;
    iIndex[13] = 4   ; jIndex[13] = 4   ;
    iIndex[14] = 4   ; jIndex[14] = 6   ;
    iIndex[15] = 5   ; jIndex[15] = 2   ;
    iIndex[16] = 5   ; jIndex[16] = 5   ;
    iIndex[17] = 5   ; jIndex[17] = 6   ;
    iIndex[18] = 6   ; jIndex[18] = 0   ;
    iIndex[19] = 6   ; jIndex[19] = 1   ;
    iIndex[20] = 6   ; jIndex[20] = 2   ;
    iIndex[21] = 6   ; jIndex[21] = 4   ;
    iIndex[22] = 6   ; jIndex[22] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::IPOPT_hess_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = cos(t4);
    real_type t7   = t6 * t5;
    real_type t8   = t5 * t5;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t12  = t11 * t7;
    real_type t15  = L__[iL_lambda2__xo];
    real_type t16  = t2 * t15;
    result__[ 0   ] = 9.0 / 2.0 * t12 * t3 - 7 * t11 * t16;
    real_type t19  = t6 * t6;
    real_type t20  = X__[iX_omega__alpha];
    real_type t21  = t20 * t19;
    real_type t30  = t10 * t10;
    real_type t31  = 1.0 / t30;
    real_type t36  = t5 * t31;
    real_type t37  = t6 * t36;
    result__[ 1   ] = 9.0 / 2.0 * t11 * t21 * t3 - 9.0 / 2.0 * t11 * t20 * t8 * t3 - 0.81e2 / 4.0 * t31 * t21 * t8 * t3 + 0.63e2 / 2.0 * t37 * t20 * t16;
    real_type t48  = L__[iL_lambda3__xo];
    result__[ 2   ] = 9.0 / 2.0 * t11 * t20 * t6 * t5 * t1 - 7 * t11 * t20 * t15 - t48 + L__[iL_lambda4__xo];
    result__[ 3   ] = 4 * t11 * t3 - 9.0 / 2.0 * t12 * t16;
    real_type t54  = X__[iX_omega__beta];
    real_type t58  = t54 * t19;
    result__[ 4   ] = -18 * t37 * t54 * t3 - 9.0 / 2.0 * t11 * t58 * t16 + 9.0 / 2.0 * t11 * t54 * t8 * t16 + 0.81e2 / 4.0 * t31 * t58 * t8 * t16;
    result__[ 5   ] = 4 * t11 * t54 * t1 - 9.0 / 2.0 * t11 * t54 * t6 * t5 * t15 + t48;
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[4];
    real_type t78  = t20 * t20;
    real_type t79  = t78 * t7;
    real_type t81  = U__[iU_u2];
    real_type t83  = 3.0 / 2.0 * t81 * t6;
    real_type t93  = 9.0 / 4.0 * t78 * t19 - 9.0 / 4.0 * t78 * t8 + 3.0 / 2.0 * t81 * t5;
    real_type t98  = t54 * t54;
    real_type t100 = U__[iU_u1];
    real_type t103 = 9.0 / 4.0 * t79 + 2 * t98 + 4.0 / 3.0 * t100 - 4.0 / 3.0 * t81 - t83;
    real_type t104 = t103 * t2;
    real_type t108 = t19 * t8 / t30 / t10;
    real_type t111 = t19 * t31;
    real_type t114 = t8 * t31;
    real_type t119 = t98 * t7;
    real_type t121 = t100 - t81;
    real_type t123 = 3.0 / 2.0 * t121 * t6;
    real_type t133 = 9.0 / 4.0 * t98 * t19 - 9.0 / 4.0 * t98 * t8 - 3.0 / 2.0 * t121 * t5;
    real_type t140 = 9.0 / 4.0 * t119 + 7.0 / 2.0 * t78 - 7.0 / 3.0 * t81 + t123;
    real_type t141 = t140 * t2;
    result__[ 8   ] = (t11 * (-9 * t79 + t83) * t2 - 9 * t37 * t93 * t2 + 0.81e2 / 2.0 * t108 * t104 - 9.0 / 2.0 * t111 * t104 + 9.0 / 2.0 * t114 * t104) * t1 + (-t11 * (-9 * t119 - t123) * t2 + 9 * t37 * t133 * t2 - 0.81e2 / 2.0 * t108 * t141 + 9.0 / 2.0 * t111 * t141 - 9.0 / 2.0 * t114 * t141) * t15;
    real_type t154 = 3.0 / 2.0 * t11 * t5 * t2;
    result__[ 9   ] = -6 * t37 * t3 + (t154 + 0.27e2 / 4.0 * t36 * t19 * t2) * t15;
    real_type t160 = 3.0 / 2.0 * t6;
    real_type t161 = -4.0 / 3.0 - t160;
    real_type t167 = -7.0 / 3.0 - t160;
    result__[ 10  ] = (t154 - 9.0 / 2.0 * t37 * t161 * t2) * t1 + (-t154 + 9.0 / 2.0 * t37 * t167 * t2) * t15;
    result__[ 11  ] = (t11 * t93 - 9.0 / 2.0 * t7 * t31 * t103) * t1 + (-t11 * t133 + 9.0 / 2.0 * t7 * t31 * t140) * t15;
    result__[ 12  ] = result__[9];
    real_type t186 = ModelPars[iM_rho] * sigma__;
    result__[ 13  ] = 2 * t2 * t186;
    result__[ 14  ] = 2 * t100 * t186 + 4.0 / 3.0 * t11 * t1 - 3.0 / 2.0 * t11 * t6 * t15;
    result__[ 15  ] = result__[10];
    result__[ 16  ] = result__[13];
    result__[ 17  ] = t1 * t11 * t161 - t11 * t15 * t167 + 2 * t186 * t81;
    result__[ 18  ] = result__[2];
    result__[ 19  ] = result__[5];
    result__[ 20  ] = result__[11];
    result__[ 21  ] = result__[14];
    result__[ 22  ] = result__[17];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 23, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ICLOCS_TwoLinkRobotArm::q_numEqns() const
  { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::q_eval(
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

  integer ICLOCS_TwoLinkRobotArm::segmentLink_numEqns() const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::DsegmentLinkDxp_numRows() const { return 0; }
  integer ICLOCS_TwoLinkRobotArm::DsegmentLinkDxp_numCols() const { return 0; }
  integer ICLOCS_TwoLinkRobotArm::DsegmentLinkDxp_nnz() const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DsegmentLinkDxp_sparse(
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

  integer ICLOCS_TwoLinkRobotArm::jump_numEqns() const { return 8; }

  void
  ICLOCS_TwoLinkRobotArm::jump_eval(
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
    result__[ 0   ] = XR__[iX_omega__alpha] - XL__[iX_omega__alpha];
    result__[ 1   ] = XR__[iX_omega__beta] - XL__[iX_omega__beta];
    result__[ 2   ] = XR__[iX_theta] - XL__[iX_theta];
    result__[ 3   ] = XR__[iX_alpha] - XL__[iX_alpha];
    result__[ 4   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 5   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 6   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 7   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DjumpDxlxlp_numRows() const { return 8; }
  integer ICLOCS_TwoLinkRobotArm::DjumpDxlxlp_numCols() const { return 17; }
  integer ICLOCS_TwoLinkRobotArm::DjumpDxlxlp_nnz()     const { return 16; }

  void
  ICLOCS_TwoLinkRobotArm::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_TwoLinkRobotArm::DjumpDxlxlp_sparse(
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

  integer ICLOCS_TwoLinkRobotArm::post_numEqns() const { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::post_eval(
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
    result__[ 0   ] = Q__[iQ_zeta] * P__[iP_T];
    Mechatronix::check_in_segment( result__, "post_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::integrated_post_numEqns() const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_problem.cc
