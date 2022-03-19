/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_problem.cc                                  |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HangGlider::continuation_step_0( real_type s ) {
    ModelPars[iM_W] = (1 - s) * ModelPars[iM_W0] + s * ModelPars[iM_W1];
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HangGlider::continuation_step_1( real_type s ) {
    real_type t2   = 1 - s;
    real_type t3   = pow(ModelPars[iM_epsi_max], t2);
    real_type t5   = pow(ModelPars[iM_epsi_min], s);
    cLControl.update_epsilon(t5 * t3);
    real_type t8   = pow(ModelPars[iM_tol_max], t2);
    real_type t10  = pow(ModelPars[iM_tol_min], s);
    cLControl.update_tolerance(t10 * t8);
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  HangGlider::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = Tbound(-t1);
    real_type t4   = U__[iU_cL];
    real_type t6   = pow(t4 - 0.7e0, 2);
    real_type t10  = X__[iX_vx];
    real_type t14  = X__[iX_vy];
    real_type t19  = 1.0 / ModelPars[iM_m];
    real_type t20  = X__[iX_x];
    real_type t21  = v(t20, t10, t14);
    real_type t22  = 1.0 / t21;
    real_type t25  = t4 * t4;
    real_type t29  = Dfun(t20, t10, t14);
    real_type t30  = t29 * (t25 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t32  = Lfun(t20, t10, t14);
    real_type t33  = t32 * t4;
    real_type t34  = w(t20, t14);
    real_type result__ = t2 + t6 * ModelPars[iM_W] + t10 * t1 * L__[iL_lambda1__xo] + t14 * t1 * L__[iL_lambda2__xo] + (-t10 * t30 - t34 * t33) * t22 * t19 * t1 * L__[iL_lambda3__xo] + ((t10 * t33 - t34 * t30) * t22 * t19 * t1 - ModelPars[iM_g] * t1) * L__[iL_lambda4__xo];
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
  HangGlider::JP_eval(
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
  HangGlider::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = cLControl(U__[iU_cL], ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  HangGlider::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = Tbound(-P__[iP_T]);
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
  HangGlider::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = pow(U__[iU_cL] - 0.7e0, 2);
    real_type result__ = t4 * ModelPars[iM_W];
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
  HangGlider::mayer_target(
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
    real_type result__ = -XR__[iX_x];
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::DmayerDxxp_numEqns() const { return 9; }

  void
  HangGlider::DmayerDxxp_eval(
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
    result__[ 4   ] = -1;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    result__[ 7   ] = 0;
    result__[ 8   ] = 0;
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

  integer HangGlider::DlagrangeDxup_numEqns() const { return 6; }

  void
  HangGlider::DlagrangeDxup_eval(
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
    result__[ 4   ] = 2 * ModelPars[iM_W] * (U__[iU_cL] - 0.7e0);
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxup_eval", 6, i_segment );
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
  integer HangGlider::IPOPT_hess_numRows() const { return 6; }
  integer HangGlider::IPOPT_hess_numCols() const { return 6; }
  integer HangGlider::IPOPT_hess_nnz()     const { return 24; }

  void
  HangGlider::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 3   ; jIndex[10] = 0   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 3   ; jIndex[13] = 4   ;
    iIndex[14] = 3   ; jIndex[14] = 5   ;
    iIndex[15] = 4   ; jIndex[15] = 0   ;
    iIndex[16] = 4   ; jIndex[16] = 2   ;
    iIndex[17] = 4   ; jIndex[17] = 3   ;
    iIndex[18] = 4   ; jIndex[18] = 4   ;
    iIndex[19] = 4   ; jIndex[19] = 5   ;
    iIndex[20] = 5   ; jIndex[20] = 0   ;
    iIndex[21] = 5   ; jIndex[21] = 2   ;
    iIndex[22] = 5   ; jIndex[22] = 3   ;
    iIndex[23] = 5   ; jIndex[23] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::IPOPT_hess_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = P__[iP_T];
    real_type t4   = 1.0 / ModelPars[iM_m];
    real_type t5   = t4 * t2;
    real_type t6   = X__[iX_x];
    real_type t7   = X__[iX_vx];
    real_type t8   = X__[iX_vy];
    real_type t9   = v(t6, t7, t8);
    real_type t10  = t9 * t9;
    real_type t12  = 1.0 / t10 / t9;
    real_type t13  = ModelPars[iM_c1];
    real_type t14  = U__[iU_cL];
    real_type t15  = t14 * t14;
    real_type t18  = t15 * t13 + ModelPars[iM_c0];
    real_type t19  = Dfun(t6, t7, t8);
    real_type t20  = t19 * t18;
    real_type t22  = Lfun(t6, t7, t8);
    real_type t23  = t22 * t14;
    real_type t24  = w(t6, t8);
    real_type t26  = -t7 * t20 - t24 * t23;
    real_type t27  = t26 * t12;
    real_type t28  = v_D_1(t6, t7, t8);
    real_type t29  = t28 * t28;
    real_type t33  = 1.0 / t10;
    real_type t34  = Dfun_D_1(t6, t7, t8);
    real_type t35  = t34 * t18;
    real_type t37  = Lfun_D_1(t6, t7, t8);
    real_type t38  = t37 * t14;
    real_type t40  = w_D_1(t6, t8);
    real_type t42  = -t40 * t23 - t24 * t38 - t7 * t35;
    real_type t43  = t42 * t33;
    real_type t47  = t26 * t33;
    real_type t48  = v_D_1_1(t6, t7, t8);
    real_type t51  = 1.0 / t9;
    real_type t52  = Dfun_D_1_1(t6, t7, t8);
    real_type t53  = t52 * t18;
    real_type t55  = Lfun_D_1_1(t6, t7, t8);
    real_type t56  = t55 * t14;
    real_type t60  = w_D_1_1(t6, t8);
    real_type t67  = L__[iL_lambda4__xo];
    real_type t70  = -t24 * t20 + t7 * t23;
    real_type t71  = t70 * t12;
    real_type t78  = -t40 * t20 - t24 * t35 + t7 * t38;
    real_type t79  = t78 * t33;
    real_type t83  = t70 * t33;
    result__[ 0   ] = (2 * t29 * t27 * t5 - 2 * t28 * t43 * t5 - t48 * t47 * t5 + (-t60 * t23 - t24 * t56 - 2 * t40 * t38 - t7 * t53) * t51 * t5) * t1 + (2 * t29 * t71 * t5 - 2 * t28 * t79 * t5 - t48 * t83 * t5 + (-t60 * t20 - t24 * t53 - 2 * t40 * t35 + t7 * t56) * t51 * t5) * t67;
    real_type t96  = t12 * t5;
    real_type t97  = t28 * t26;
    real_type t98  = v_D_2(t6, t7, t8);
    real_type t102 = Dfun_D_2(t6, t7, t8);
    real_type t103 = t102 * t18;
    real_type t105 = Lfun_D_2(t6, t7, t8);
    real_type t106 = t105 * t14;
    real_type t108 = -t7 * t103 - t24 * t106 - t20;
    real_type t109 = t108 * t33;
    real_type t112 = v_D_1_2(t6, t7, t8);
    real_type t117 = Dfun_D_1_2(t6, t7, t8);
    real_type t118 = t117 * t18;
    real_type t120 = Lfun_D_1_2(t6, t7, t8);
    real_type t121 = t120 * t14;
    real_type t129 = t28 * t70;
    real_type t135 = -t24 * t103 + t7 * t106 + t23;
    real_type t136 = t135 * t33;
    result__[ 1   ] = (2 * t98 * t97 * t96 - t28 * t109 * t5 - t112 * t47 * t5 - t98 * t43 * t5 + (-t40 * t106 - t7 * t118 - t24 * t121 - t35) * t51 * t5) * t1 + (2 * t98 * t129 * t96 - t28 * t136 * t5 - t112 * t83 * t5 - t98 * t79 * t5 + (-t40 * t103 - t24 * t118 + t7 * t121 + t38) * t51 * t5) * t67;
    real_type t151 = v_D_3(t6, t7, t8);
    real_type t155 = Dfun_D_3(t6, t7, t8);
    real_type t156 = t155 * t18;
    real_type t158 = Lfun_D_3(t6, t7, t8);
    real_type t159 = t158 * t14;
    real_type t161 = w_D_2(t6, t8);
    real_type t163 = -t7 * t156 - t24 * t159 - t161 * t23;
    real_type t164 = t163 * t33;
    real_type t167 = v_D_1_3(t6, t7, t8);
    real_type t172 = Dfun_D_1_3(t6, t7, t8);
    real_type t173 = t172 * t18;
    real_type t175 = Lfun_D_1_3(t6, t7, t8);
    real_type t176 = t175 * t14;
    real_type t180 = w_D_1_2(t6, t8);
    real_type t193 = -t24 * t156 + t7 * t159 - t161 * t20;
    real_type t194 = t193 * t33;
    result__[ 2   ] = (2 * t151 * t97 * t96 - t28 * t164 * t5 - t167 * t47 * t5 - t151 * t43 * t5 + (-t40 * t159 - t161 * t38 - t7 * t173 - t24 * t176 - t180 * t23) * t51 * t5) * t1 + (2 * t151 * t129 * t96 - t28 * t194 * t5 - t167 * t83 * t5 - t151 * t79 * t5 + (-t40 * t156 - t161 * t35 - t24 * t173 + t7 * t176 - t180 * t20) * t51 * t5) * t67;
    real_type t211 = t14 * t13;
    real_type t212 = t7 * t19;
    real_type t216 = -2 * t212 * t211 - t24 * t22;
    real_type t217 = t216 * t33;
    real_type t230 = t24 * t19;
    real_type t234 = -2 * t230 * t211 + t7 * t22;
    real_type t235 = t234 * t33;
    result__[ 3   ] = (-t28 * t217 * t5 + (-2 * t7 * t34 * t211 - t40 * t22 - t24 * t37) * t51 * t5) * t1 + (-t28 * t235 * t5 + (-2 * t40 * t19 * t211 - 2 * t24 * t34 * t211 + t7 * t37) * t51 * t5) * t67;
    real_type t250 = t33 * t4;
    real_type t252 = t51 * t4;
    result__[ 4   ] = (-t97 * t250 + t42 * t252) * t1 + (-t129 * t250 + t78 * t252) * t67;
    result__[ 5   ] = result__[1];
    real_type t260 = t98 * t98;
    real_type t267 = v_D_2_2(t6, t7, t8);
    real_type t270 = Dfun_D_2_2(t6, t7, t8);
    real_type t271 = t270 * t18;
    real_type t274 = Lfun_D_2_2(t6, t7, t8);
    real_type t275 = t274 * t14;
    result__[ 6   ] = (2 * t260 * t27 * t5 - 2 * t98 * t109 * t5 - t267 * t47 * t5 + (-t24 * t275 - t7 * t271 - 2 * t103) * t51 * t5) * t1 + (2 * t260 * t71 * t5 - 2 * t98 * t136 * t5 - t267 * t83 * t5 + (-t24 * t271 + t7 * t275 + 2 * t106) * t51 * t5) * t67;
    real_type t298 = t98 * t26;
    real_type t304 = v_D_2_3(t6, t7, t8);
    real_type t309 = Dfun_D_2_3(t6, t7, t8);
    real_type t310 = t309 * t18;
    real_type t312 = Lfun_D_2_3(t6, t7, t8);
    real_type t313 = t312 * t14;
    real_type t321 = t98 * t70;
    result__[ 7   ] = (2 * t151 * t298 * t96 - t98 * t164 * t5 - t304 * t47 * t5 - t151 * t109 * t5 + (-t161 * t106 - t24 * t313 - t7 * t310 - t156) * t51 * t5) * t1 + (2 * t151 * t321 * t96 - t98 * t194 * t5 - t304 * t83 * t5 - t151 * t136 * t5 + (-t161 * t103 - t24 * t310 + t7 * t313 + t159) * t51 * t5) * t67;
    result__[ 8   ] = (-t98 * t217 * t5 + (-2 * t7 * t102 * t211 - t24 * t105 - 2 * t19 * t211) * t51 * t5) * t1 + (-t98 * t235 * t5 + (-2 * t24 * t102 * t211 + t7 * t105 + t22) * t51 * t5) * t67;
    result__[ 9   ] = L__[iL_lambda1__xo] + (t108 * t252 - t298 * t250) * t1 + (t135 * t252 - t321 * t250) * t67;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t372 = t151 * t151;
    real_type t379 = v_D_3_3(t6, t7, t8);
    real_type t382 = Dfun_D_3_3(t6, t7, t8);
    real_type t383 = t382 * t18;
    real_type t385 = Lfun_D_3_3(t6, t7, t8);
    real_type t386 = t385 * t14;
    real_type t390 = w_D_2_2(t6, t8);
    result__[ 12  ] = (2 * t372 * t27 * t5 - 2 * t151 * t164 * t5 - t379 * t47 * t5 + (-2 * t161 * t159 - t390 * t23 - t24 * t386 - t7 * t383) * t51 * t5) * t1 + (2 * t372 * t71 * t5 - 2 * t151 * t194 * t5 - t379 * t83 * t5 + (-2 * t161 * t156 - t390 * t20 - t24 * t383 + t7 * t386) * t51 * t5) * t67;
    result__[ 13  ] = (-t151 * t217 * t5 + (-2 * t7 * t155 * t211 - t24 * t158 - t161 * t22) * t51 * t5) * t1 + (-t151 * t235 * t5 + (-2 * t24 * t155 * t211 - 2 * t161 * t19 * t211 + t7 * t158) * t51 * t5) * t67;
    result__[ 14  ] = L__[iL_lambda2__xo] + (-t151 * t26 * t250 + t163 * t252) * t1 + (-t151 * t70 * t250 + t193 * t252) * t67;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    real_type t456 = t13 * t51;
    result__[ 18  ] = -2 * t212 * t456 * t4 * t2 * t1 - 2 * t230 * t456 * t4 * t2 * t67 + 2 * sigma__ * ModelPars[iM_W];
    result__[ 19  ] = t216 * t51 * t4 * t1 + t234 * t51 * t4 * t67;
    result__[ 20  ] = result__[4];
    result__[ 21  ] = result__[9];
    result__[ 22  ] = result__[14];
    result__[ 23  ] = result__[19];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 24, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  HangGlider::q_numEqns() const
  { return 1; }

  void
  HangGlider::q_eval(
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

  integer HangGlider::segmentLink_numEqns() const { return 0; }

  void
  HangGlider::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::DsegmentLinkDxp_numRows() const { return 0; }
  integer HangGlider::DsegmentLinkDxp_numCols() const { return 0; }
  integer HangGlider::DsegmentLinkDxp_nnz() const { return 0; }

  void
  HangGlider::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DsegmentLinkDxp_sparse(
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

  integer HangGlider::jump_numEqns() const { return 8; }

  void
  HangGlider::jump_eval(
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
    result__[ 2   ] = XR__[iX_vx] - XL__[iX_vx];
    result__[ 3   ] = XR__[iX_vy] - XL__[iX_vy];
    result__[ 4   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 5   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 6   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 7   ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DjumpDxlxlp_numRows() const { return 8; }
  integer HangGlider::DjumpDxlxlp_numCols() const { return 17; }
  integer HangGlider::DjumpDxlxlp_nnz()     const { return 16; }

  void
  HangGlider::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  HangGlider::DjumpDxlxlp_sparse(
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

  integer HangGlider::post_numEqns() const { return 0; }

  void
  HangGlider::post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::integrated_post_numEqns() const { return 0; }

  void
  HangGlider::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: HangGlider_Methods_problem.cc
