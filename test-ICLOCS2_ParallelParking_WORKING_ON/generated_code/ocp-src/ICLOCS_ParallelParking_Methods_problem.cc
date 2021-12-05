/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking_Methods_problem.cc                      |
 |                                                                       |
 |  version: 1.0   date 5/12/2021                                        |
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


#include "ICLOCS_ParallelParking.hh"
#include "ICLOCS_ParallelParking_Pars.hh"

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
#define ALIAS_phi_bound_DD(__t1) phi_bound.DD( __t1)
#define ALIAS_phi_bound_D(__t1) phi_bound.D( __t1)
#define ALIAS_acc_bound_DD(__t1) acc_bound.DD( __t1)
#define ALIAS_acc_bound_D(__t1) acc_bound.D( __t1)
#define ALIAS_vel_bound_DD(__t1) vel_bound.DD( __t1)
#define ALIAS_vel_bound_D(__t1) vel_bound.D( __t1)
#define ALIAS_EXTRA2_bound_DD(__t1) EXTRA2_bound.DD( __t1)
#define ALIAS_EXTRA2_bound_D(__t1) EXTRA2_bound.D( __t1)
#define ALIAS_EXTRA1_bound_DD(__t1) EXTRA1_bound.DD( __t1)
#define ALIAS_EXTRA1_bound_D(__t1) EXTRA1_bound.D( __t1)
#define ALIAS_D_bound_DD(__t1) D_bound.DD( __t1)
#define ALIAS_D_bound_D(__t1) D_bound.D( __t1)
#define ALIAS_C_bound_DD(__t1) C_bound.DD( __t1)
#define ALIAS_C_bound_D(__t1) C_bound.D( __t1)
#define ALIAS_B_bound_DD(__t1) B_bound.DD( __t1)
#define ALIAS_B_bound_D(__t1) B_bound.D( __t1)
#define ALIAS_A_bound_DD(__t1) A_bound.DD( __t1)
#define ALIAS_A_bound_D(__t1) A_bound.D( __t1)
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


namespace ICLOCS_ParallelParkingDefine {

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  ICLOCS_ParallelParking::H_eval(
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
    real_type t2   = X__[iX_y];
    real_type t3   = X__[iX_theta];
    real_type t4   = Ay(t1, t2, t3);
    real_type t5   = A_bound(t4);
    real_type t6   = By(t1, t2, t3);
    real_type t7   = B_bound(t6);
    real_type t8   = Cy(t1, t2, t3);
    real_type t9   = C_bound(t8);
    real_type t10  = Dy(t1, t2, t3);
    real_type t11  = D_bound(t10);
    real_type t12  = AEB(t1, t2, t3);
    real_type t13  = BEC(t1, t2, t3);
    real_type t14  = CED(t1, t2, t3);
    real_type t15  = DEA(t1, t2, t3);
    real_type t16  = ABCD(t1, t2, t3);
    real_type t18  = EXTRA1_bound(t12 + t13 + t14 + t15 - t16);
    real_type t19  = AOB(t1, t2, t3);
    real_type t20  = BOC(t1, t2, t3);
    real_type t21  = COD(t1, t2, t3);
    real_type t22  = DOA(t1, t2, t3);
    real_type t24  = EXTRA2_bound(t19 + t20 + t21 + t22 - t16);
    real_type t25  = X__[iX_v];
    real_type t26  = vel_bound(t25);
    real_type t27  = X__[iX_a];
    real_type t28  = acc_bound(t27);
    real_type t29  = X__[iX_phi];
    real_type t30  = phi_bound(t29);
    real_type t32  = P__[iP_T];
    real_type t34  = cos(t3);
    real_type t39  = sin(t3);
    real_type t51  = tan(t29);
    real_type result__ = t5 + t7 + t9 + t11 + t18 + t24 + t26 + t28 + t30 + t34 * t25 * t32 * L__[iL_lambda1__xo] + t39 * t25 * t32 * L__[iL_lambda2__xo] + t27 * t32 * L__[iL_lambda3__xo] + U__[iU_u1] * t32 * L__[iL_lambda4__xo] + 1.0 / ModelPars[iM_len_a] * t51 * t25 * t32 * L__[iL_lambda5__xo] + U__[iU_u2] * t25 * t32 * L__[iL_lambda6__xo];
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
  ICLOCS_ParallelParking::penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_y];
    real_type t3   = X__[iX_theta];
    real_type t4   = Ay(t1, t2, t3);
    real_type t5   = A_bound(t4);
    real_type t6   = By(t1, t2, t3);
    real_type t7   = B_bound(t6);
    real_type t8   = Cy(t1, t2, t3);
    real_type t9   = C_bound(t8);
    real_type t10  = Dy(t1, t2, t3);
    real_type t11  = D_bound(t10);
    real_type t12  = AEB(t1, t2, t3);
    real_type t13  = BEC(t1, t2, t3);
    real_type t14  = CED(t1, t2, t3);
    real_type t15  = DEA(t1, t2, t3);
    real_type t16  = ABCD(t1, t2, t3);
    real_type t18  = EXTRA1_bound(t12 + t13 + t14 + t15 - t16);
    real_type t19  = AOB(t1, t2, t3);
    real_type t20  = BOC(t1, t2, t3);
    real_type t21  = COD(t1, t2, t3);
    real_type t22  = DOA(t1, t2, t3);
    real_type t24  = EXTRA2_bound(t19 + t20 + t21 + t22 - t16);
    real_type t26  = vel_bound(X__[iX_v]);
    real_type t28  = acc_bound(X__[iX_a]);
    real_type t30  = phi_bound(X__[iX_phi]);
    real_type result__ = t5 + t7 + t9 + t11 + t18 + t24 + t26 + t28 + t30;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "penalties_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_ParallelParking::control_penalties_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = cos(X__[iX_phi]);
    real_type t5   = t4 * t4;
    real_type t7   = 0.6e0 * t5 * ModelPars[iM_len_a];
    real_type t8   = u1Control(U__[iU_u1], -t7, t7);
    real_type t10  = u2Control(U__[iU_u2], -0.5e0, 0.5e0);
    real_type result__ = t8 + t10;
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
  ICLOCS_ParallelParking::lagrange_target(
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
  ICLOCS_ParallelParking::mayer_target(
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
    real_type result__ = P__[iP_T];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DmayerDxxp_numEqns() const
  { return 13; }

  void
  ICLOCS_ParallelParking::DmayerDxxp_eval(
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
    result__[ 10  ] = 0;
    result__[ 11  ] = 0;
    result__[ 12  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 13, i_segment_left, i_segment_right );
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
  ICLOCS_ParallelParking::DlagrangeDxup_numEqns() const
  { return 9; }

  void
  ICLOCS_ParallelParking::DlagrangeDxup_eval(
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
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 9, i_segment );
  }

  integer
  ICLOCS_ParallelParking::DJDx_numEqns() const
  { return 6; }

  void
  ICLOCS_ParallelParking::DJDx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_y];
    real_type t3   = X__[iX_theta];
    real_type t4   = Ay(t1, t2, t3);
    real_type t5   = ALIAS_A_bound_D(t4);
    real_type t6   = Ay_D_1(t1, t2, t3);
    real_type t8   = By(t1, t2, t3);
    real_type t9   = ALIAS_B_bound_D(t8);
    real_type t10  = By_D_1(t1, t2, t3);
    real_type t12  = Cy(t1, t2, t3);
    real_type t13  = ALIAS_C_bound_D(t12);
    real_type t14  = Cy_D_1(t1, t2, t3);
    real_type t16  = Dy(t1, t2, t3);
    real_type t17  = ALIAS_D_bound_D(t16);
    real_type t18  = Dy_D_1(t1, t2, t3);
    real_type t20  = AEB(t1, t2, t3);
    real_type t21  = BEC(t1, t2, t3);
    real_type t22  = CED(t1, t2, t3);
    real_type t23  = DEA(t1, t2, t3);
    real_type t24  = ABCD(t1, t2, t3);
    real_type t26  = ALIAS_EXTRA1_bound_D(t20 + t21 + t22 + t23 - t24);
    real_type t27  = AEB_D_1(t1, t2, t3);
    real_type t28  = BEC_D_1(t1, t2, t3);
    real_type t29  = CED_D_1(t1, t2, t3);
    real_type t30  = DEA_D_1(t1, t2, t3);
    real_type t31  = ABCD_D_1(t1, t2, t3);
    real_type t34  = AOB(t1, t2, t3);
    real_type t35  = BOC(t1, t2, t3);
    real_type t36  = COD(t1, t2, t3);
    real_type t37  = DOA(t1, t2, t3);
    real_type t39  = ALIAS_EXTRA2_bound_D(t34 + t35 + t36 + t37 - t24);
    real_type t40  = AOB_D_1(t1, t2, t3);
    real_type t41  = BOC_D_1(t1, t2, t3);
    real_type t42  = COD_D_1(t1, t2, t3);
    real_type t43  = DOA_D_1(t1, t2, t3);
    result__[ 0   ] = t6 * t5 + t10 * t9 + t14 * t13 + t18 * t17 + (t27 + t28 + t29 + t30 - t31) * t26 + (t40 + t41 + t42 + t43 - t31) * t39;
    real_type t46  = Ay_D_2(t1, t2, t3);
    real_type t48  = By_D_2(t1, t2, t3);
    real_type t50  = Cy_D_2(t1, t2, t3);
    real_type t52  = Dy_D_2(t1, t2, t3);
    real_type t54  = AEB_D_2(t1, t2, t3);
    real_type t55  = BEC_D_2(t1, t2, t3);
    real_type t56  = CED_D_2(t1, t2, t3);
    real_type t57  = DEA_D_2(t1, t2, t3);
    real_type t58  = ABCD_D_2(t1, t2, t3);
    real_type t61  = AOB_D_2(t1, t2, t3);
    real_type t62  = BOC_D_2(t1, t2, t3);
    real_type t63  = COD_D_2(t1, t2, t3);
    real_type t64  = DOA_D_2(t1, t2, t3);
    result__[ 1   ] = t46 * t5 + t48 * t9 + t50 * t13 + t52 * t17 + (t54 + t55 + t56 + t57 - t58) * t26 + (t61 + t62 + t63 + t64 - t58) * t39;
    result__[ 2   ] = ALIAS_vel_bound_D(X__[iX_v]);
    result__[ 3   ] = ALIAS_acc_bound_D(X__[iX_a]);
    real_type t69  = Ay_D_3(t1, t2, t3);
    real_type t71  = By_D_3(t1, t2, t3);
    real_type t73  = Cy_D_3(t1, t2, t3);
    real_type t75  = Dy_D_3(t1, t2, t3);
    real_type t77  = AEB_D_3(t1, t2, t3);
    real_type t78  = BEC_D_3(t1, t2, t3);
    real_type t79  = CED_D_3(t1, t2, t3);
    real_type t80  = DEA_D_3(t1, t2, t3);
    real_type t81  = ABCD_D_3(t1, t2, t3);
    real_type t84  = AOB_D_3(t1, t2, t3);
    real_type t85  = BOC_D_3(t1, t2, t3);
    real_type t86  = COD_D_3(t1, t2, t3);
    real_type t87  = DOA_D_3(t1, t2, t3);
    result__[ 4   ] = t69 * t5 + t71 * t9 + t73 * t13 + t75 * t17 + (t77 + t78 + t79 + t80 - t81) * t26 + (t84 + t85 + t86 + t87 - t81) * t39;
    real_type t90  = X__[iX_phi];
    real_type t91  = ALIAS_phi_bound_D(t90);
    real_type t92  = U__[iU_u1];
    real_type t93  = ModelPars[iM_len_a];
    real_type t94  = cos(t90);
    real_type t95  = t94 * t94;
    real_type t97  = 0.6e0 * t95 * t93;
    real_type t98  = ALIAS_u1Control_D_2(t92, -t97, t97);
    real_type t100 = sin(t90);
    real_type t101 = t100 * t94;
    real_type t104 = ALIAS_u1Control_D_3(t92, -t97, t97);
    result__[ 5   ] = t91 + 0.12e1 * t101 * t93 * t98 - 0.12e1 * t101 * t93 * t104;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DJDp_numEqns() const
  { return 1; }

  void
  ICLOCS_ParallelParking::DJDp_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DJDu_numEqns() const
  { return 2; }

  void
  ICLOCS_ParallelParking::DJDu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = cos(X__[iX_phi]);
    real_type t5   = t4 * t4;
    real_type t7   = 0.6e0 * t5 * ModelPars[iM_len_a];
    result__[ 0   ] = ALIAS_u1Control_D_1(U__[iU_u1], -t7, t7);
    result__[ 1   ] = ALIAS_u2Control_D_1(U__[iU_u2], -0.5e0, 0.5e0);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJDu_eval", 2, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  ICLOCS_ParallelParking::q_numEqns() const
  { return 1; }

  void
  ICLOCS_ParallelParking::q_eval(
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
  ICLOCS_ParallelParking::segmentLink_numEqns() const
  { return 0; }

  void
  ICLOCS_ParallelParking::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  ICLOCS_ParallelParking::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  ICLOCS_ParallelParking::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  ICLOCS_ParallelParking::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DsegmentLinkDxp_sparse(
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
  ICLOCS_ParallelParking::jump_numEqns() const
  { return 12; }

  void
  ICLOCS_ParallelParking::jump_eval(
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
    result__[ 1   ] = XR__[iX_y] - XL__[iX_y];
    result__[ 2   ] = XR__[iX_v] - XL__[iX_v];
    result__[ 3   ] = XR__[iX_a] - XL__[iX_a];
    result__[ 4   ] = XR__[iX_theta] - XL__[iX_theta];
    result__[ 5   ] = XR__[iX_phi] - XL__[iX_phi];
    result__[ 6   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 7   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 8   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 9   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 10  ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    result__[ 11  ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DjumpDxlxlp_numRows() const
  { return 12; }

  integer
  ICLOCS_ParallelParking::DjumpDxlxlp_numCols() const
  { return 25; }

  integer
  ICLOCS_ParallelParking::DjumpDxlxlp_nnz() const
  { return 24; }

  void
  ICLOCS_ParallelParking::DjumpDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 12  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 13  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 14  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 16  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 17  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 18  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 19  ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 20  ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 21  ;
    iIndex[20] = 10  ; jIndex[20] = 10  ;
    iIndex[21] = 10  ; jIndex[21] = 22  ;
    iIndex[22] = 11  ; jIndex[22] = 11  ;
    iIndex[23] = 11  ; jIndex[23] = 23  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DjumpDxlxlp_sparse(
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
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    result__[ 18  ] = -1;
    result__[ 19  ] = 1;
    result__[ 20  ] = -1;
    result__[ 21  ] = 1;
    result__[ 22  ] = -1;
    result__[ 23  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 24, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer
  ICLOCS_ParallelParking::post_numEqns() const
  { return 0; }

  void
  ICLOCS_ParallelParking::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::integrated_post_numEqns() const
  { return 0; }

  void
  ICLOCS_ParallelParking::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: ICLOCS_ParallelParking_Methods_problem.cc
