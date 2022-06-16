/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_problem.cc                       |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"

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
#define ALIAS_G_bound_max_DD(__t1) G_bound_max.DD( __t1)
#define ALIAS_G_bound_max_D(__t1) G_bound_max.D( __t1)
#define ALIAS_G_bound_min_DD(__t1) G_bound_min.DD( __t1)
#define ALIAS_G_bound_min_D(__t1) G_bound_min.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)


namespace HypersonicProblem3DOFDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HypersonicProblem3DOF::continuation_step_0( real_type s ) {
    ModelPars[iM_ODE] = ModelPars[iM_ODE0] * (1 - s) + ModelPars[iM_ODE1] * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HypersonicProblem3DOF::continuation_step_1( real_type s ) {
    ModelPars[iM_WTF] = ModelPars[iM_WTF0] * (1 - s) + ModelPars[iM_WTF1] * s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  HypersonicProblem3DOF::continuation_step_2( real_type s ) {
    ModelPars[iM_CTRL] = ModelPars[iM_CTRL0] * (1 - s) + ModelPars[iM_CTRL1] * s;
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  HypersonicProblem3DOF::penalties_check_cell(
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
    real_type Q__[1], X__[7];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    X__[5] = (XL__[5]+XR__[5])/2;
    X__[6] = (XL__[6]+XR__[6])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    bool res = true;
    real_type t1   = X__[iX_G];
    res = res && G_bound_min.check_range(-0.314159265358979323846264338328e1 - t1, m_max_penalty_value);
    res = res && G_bound_max.check_range(t1 - 0.314159265358979323846264338328e1, m_max_penalty_value);
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
  HypersonicProblem3DOF::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = U__[iU_alpha];
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_G];
    real_type t7   = cos(t5 / 2);
    real_type t8   = log(t7);
    real_type t10  = U__[iU_c_h];
    real_type t11  = t10 * t10;
    real_type t12  = U__[iU_c_theta];
    real_type t13  = t12 * t12;
    real_type t14  = U__[iU_c_phi];
    real_type t15  = t14 * t14;
    real_type t16  = U__[iU_c_V];
    real_type t17  = t16 * t16;
    real_type t18  = U__[iU_c_G];
    real_type t19  = t18 * t18;
    real_type t20  = U__[iU_c_psi];
    real_type t21  = t20 * t20;
    real_type t22  = U__[iU_c_sigma];
    real_type t23  = t22 * t22;
    real_type t28  = ModelPars[iM_ODE];
    real_type t29  = X__[iX_V];
    real_type t30  = t29 * t28;
    real_type t31  = sin(t5);
    real_type t33  = ModelPars[iM_CTRL];
    real_type t39  = cos(t5);
    real_type t41  = X__[iX_psi];
    real_type t42  = cos(t41);
    real_type t44  = X__[iX_h];
    real_type t45  = ModelPars[iM_re] + t44;
    real_type t46  = 1.0 / t45;
    real_type t48  = X__[iX_phi];
    real_type t49  = cos(t48);
    real_type t58  = sin(t41);
    real_type t67  = ModelPars[iM_mu];
    real_type t69  = t45 * t45;
    real_type t70  = 1.0 / t69;
    real_type t76  = exp(-1.0 / ModelPars[iM_S] * t44);
    real_type t77  = t76 * ModelPars[iM_rho0];
    real_type t78  = t29 * t29;
    real_type t86  = ModelPars[iM_Aref];
    real_type t89  = 1.0 / ModelPars[iM_m];
    real_type t104 = t2 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t106 = X__[iX_sigma];
    real_type t107 = cos(t106);
    real_type t112 = t46 * t29;
    real_type t128 = sin(t106);
    real_type t135 = tan(t48);
    real_type result__ = t3 * t1 - t8 * t1 + (t11 + t13 + t15 + t17 + t19 + t21 + t23) * t1 + (t10 * t33 + t31 * t30) * t1 * L__[iL_lambda1__xo] + (1.0 / t49 * t46 * t42 * t39 * t30 + t12 * t33) * t1 * L__[iL_lambda2__xo] + (t46 * t58 * t39 * t30 + t14 * t33) * t1 * L__[iL_lambda3__xo] + ((-t70 * t67 * t31 - t89 * t86 * (t2 * ModelPars[iM_CD1] + t3 * ModelPars[iM_CD2] + ModelPars[iM_CD0]) * t78 * t77 / 2) * t28 + t16 * t33) * t1 * L__[iL_lambda4__xo] + ((t107 * t89 * t86 * t104 * t29 * t77 / 2 + t39 * (t112 - 1.0 / t29 * t70 * t67)) * t28 + t18 * t33) * t1 * L__[iL_lambda5__xo] + ((1.0 / t39 * t128 * t89 * t86 * t104 * t29 * t77 / 2 - t135 * t42 * t39 * t112) * t28 + t20 * t33) * t1 * L__[iL_lambda6__xo] + (U__[iU_u2] * ModelPars[iM_sigma_dot_max] * t28 + t22 * t33) * t1 * L__[iL_lambda7__xo];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "H_eval(...) return {}\n", result__ );
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
  HypersonicProblem3DOF::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t3   = U__[iU_alpha] * U__[iU_alpha];
    real_type t7   = cos(X__[iX_G] / 2);
    real_type t8   = log(t7);
    real_type t11  = U__[iU_c_h] * U__[iU_c_h];
    real_type t13  = U__[iU_c_theta] * U__[iU_c_theta];
    real_type t15  = U__[iU_c_phi] * U__[iU_c_phi];
    real_type t17  = U__[iU_c_V] * U__[iU_c_V];
    real_type t19  = U__[iU_c_G] * U__[iU_c_G];
    real_type t21  = U__[iU_c_psi] * U__[iU_c_psi];
    real_type t23  = U__[iU_c_sigma] * U__[iU_c_sigma];
    real_type result__ = t3 * t1 - t8 * t1 + (t11 + t13 + t15 + t17 + t19 + t21 + t23) * t1;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "lagrange_target(...) return {}\n", result__ );
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
  HypersonicProblem3DOF::mayer_target(
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
    real_type t3   = ModelPars[iM_Tf_guess];
    real_type t5   = pow(P__[iP_Tf] - t3, 2);
    real_type t7   = t3 * t3;
    real_type result__ = 1.0 / t7 * t5 * ModelPars[iM_WTF];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::DmayerDxxp_numEqns() const { return 15; }

  void
  HypersonicProblem3DOF::DmayerDxxp_eval(
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
    result__[ 12  ] = 0;
    result__[ 13  ] = 0;
    real_type t3   = ModelPars[iM_Tf_guess];
    real_type t6   = t3 * t3;
    result__[ 14  ] = 2 / t6 * (P__[iP_Tf] - t3) * ModelPars[iM_WTF];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 15, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2mayerD2xxp_numRows() const { return 15; }
  integer HypersonicProblem3DOF::D2mayerD2xxp_numCols() const { return 15; }
  integer HypersonicProblem3DOF::D2mayerD2xxp_nnz()     const { return 1; }

  void
  HypersonicProblem3DOF::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 14  ; jIndex[0 ] = 14  ;
  }


  void
  HypersonicProblem3DOF::D2mayerD2xxp_sparse(
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
    real_type t3   = ModelPars[iM_Tf_guess] * ModelPars[iM_Tf_guess];
    result__[ 0   ] = 2 / t3 * ModelPars[iM_WTF];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "D2mayerD2xxp_eval", 1, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer HypersonicProblem3DOF::DlagrangeDxpu_numEqns() const { return 17; }

  void
  HypersonicProblem3DOF::DlagrangeDxpu_eval(
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
    real_type t1   = P__[iP_Tf];
    real_type t3   = X__[iX_G] / 2;
    real_type t4   = sin(t3);
    real_type t6   = cos(t3);
    result__[ 4   ] = 1.0 / t6 * t4 * t1 / 2;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    real_type t9   = U__[iU_c_G];
    real_type t10  = t9 * t9;
    real_type t11  = U__[iU_c_psi];
    real_type t12  = t11 * t11;
    real_type t13  = U__[iU_c_sigma];
    real_type t14  = t13 * t13;
    real_type t15  = U__[iU_c_h];
    real_type t16  = t15 * t15;
    real_type t17  = U__[iU_c_theta];
    real_type t18  = t17 * t17;
    real_type t19  = U__[iU_c_phi];
    real_type t20  = t19 * t19;
    real_type t21  = U__[iU_alpha];
    real_type t22  = t21 * t21;
    real_type t23  = U__[iU_c_V];
    real_type t24  = t23 * t23;
    real_type t25  = log(t6);
    result__[ 7   ] = t10 + t12 + t14 + t16 + t18 + t20 + t22 + t24 - t25;
    result__[ 8   ] = 2 * t21 * t1;
    result__[ 9   ] = 0;
    result__[ 10  ] = 2 * t15 * t1;
    result__[ 11  ] = 2 * t17 * t1;
    result__[ 12  ] = 2 * t19 * t1;
    result__[ 13  ] = 2 * t23 * t1;
    result__[ 14  ] = 2 * t9 * t1;
    result__[ 15  ] = 2 * t11 * t1;
    result__[ 16  ] = 2 * t13 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 17, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2lagrangeD2xpu_numRows() const { return 17; }
  integer HypersonicProblem3DOF::D2lagrangeD2xpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::D2lagrangeD2xpu_nnz()     const { return 27; }

  void
  HypersonicProblem3DOF::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 16  ;
    iIndex[2 ] = 7   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 7   ; jIndex[3 ] = 16  ;
    iIndex[4 ] = 9   ; jIndex[4 ] = 9   ;
    iIndex[5 ] = 9   ; jIndex[5 ] = 16  ;
    iIndex[6 ] = 10  ; jIndex[6 ] = 10  ;
    iIndex[7 ] = 10  ; jIndex[7 ] = 16  ;
    iIndex[8 ] = 11  ; jIndex[8 ] = 11  ;
    iIndex[9 ] = 11  ; jIndex[9 ] = 16  ;
    iIndex[10] = 12  ; jIndex[10] = 12  ;
    iIndex[11] = 12  ; jIndex[11] = 16  ;
    iIndex[12] = 13  ; jIndex[12] = 13  ;
    iIndex[13] = 13  ; jIndex[13] = 16  ;
    iIndex[14] = 14  ; jIndex[14] = 14  ;
    iIndex[15] = 14  ; jIndex[15] = 16  ;
    iIndex[16] = 15  ; jIndex[16] = 15  ;
    iIndex[17] = 15  ; jIndex[17] = 16  ;
    iIndex[18] = 16  ; jIndex[18] = 4   ;
    iIndex[19] = 16  ; jIndex[19] = 7   ;
    iIndex[20] = 16  ; jIndex[20] = 9   ;
    iIndex[21] = 16  ; jIndex[21] = 10  ;
    iIndex[22] = 16  ; jIndex[22] = 11  ;
    iIndex[23] = 16  ; jIndex[23] = 12  ;
    iIndex[24] = 16  ; jIndex[24] = 13  ;
    iIndex[25] = 16  ; jIndex[25] = 14  ;
    iIndex[26] = 16  ; jIndex[26] = 15  ;
  }


  void
  HypersonicProblem3DOF::D2lagrangeD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t3   = X__[iX_G] / 2;
    real_type t4   = sin(t3);
    real_type t5   = t4 * t4;
    real_type t7   = cos(t3);
    real_type t8   = t7 * t7;
    result__[ 0   ] = t1 / 4 + 1.0 / t8 * t5 * t1 / 4;
    result__[ 1   ] = 1.0 / t7 * t4 / 2;
    result__[ 2   ] = 2 * t1;
    result__[ 3   ] = 2 * U__[iU_alpha];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = 2 * U__[iU_c_h];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 2 * U__[iU_c_theta];
    result__[ 8   ] = result__[6];
    result__[ 9   ] = 2 * U__[iU_c_phi];
    result__[ 10  ] = result__[8];
    result__[ 11  ] = 2 * U__[iU_c_V];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = 2 * U__[iU_c_G];
    result__[ 14  ] = result__[12];
    result__[ 15  ] = 2 * U__[iU_c_psi];
    result__[ 16  ] = result__[14];
    result__[ 17  ] = 2 * U__[iU_c_sigma];
    result__[ 18  ] = result__[1];
    result__[ 19  ] = result__[3];
    result__[ 20  ] = result__[5];
    result__[ 21  ] = result__[7];
    result__[ 22  ] = result__[9];
    result__[ 23  ] = result__[11];
    result__[ 24  ] = result__[13];
    result__[ 25  ] = result__[15];
    result__[ 26  ] = result__[17];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xpu_eval", 27, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  HypersonicProblem3DOF::q_numEqns() const
  { return 1; }

  void
  HypersonicProblem3DOF::q_eval(
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

  integer HypersonicProblem3DOF::segmentLink_numEqns() const { return 0; }

  void
  HypersonicProblem3DOF::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::DsegmentLinkDxp_numRows() const { return 0; }
  integer HypersonicProblem3DOF::DsegmentLinkDxp_numCols() const { return 0; }
  integer HypersonicProblem3DOF::DsegmentLinkDxp_nnz() const { return 0; }

  void
  HypersonicProblem3DOF::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::DsegmentLinkDxp_sparse(
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

  integer HypersonicProblem3DOF::jump_numEqns() const { return 14; }

  void
  HypersonicProblem3DOF::jump_eval(
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
    result__[ 0   ] = XR__[iX_h] - XL__[iX_h];
    result__[ 1   ] = XR__[iX_theta] - XL__[iX_theta];
    result__[ 2   ] = XR__[iX_phi] - XL__[iX_phi];
    result__[ 3   ] = XR__[iX_V] - XL__[iX_V];
    result__[ 4   ] = XR__[iX_G] - XL__[iX_G];
    result__[ 5   ] = XR__[iX_psi] - XL__[iX_psi];
    result__[ 6   ] = XR__[iX_sigma] - XL__[iX_sigma];
    result__[ 7   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 8   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 9   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    result__[ 10  ] = LR__[iL_lambda4__xo] - LL__[iL_lambda4__xo];
    result__[ 11  ] = LR__[iL_lambda5__xo] - LL__[iL_lambda5__xo];
    result__[ 12  ] = LR__[iL_lambda6__xo] - LL__[iL_lambda6__xo];
    result__[ 13  ] = LR__[iL_lambda7__xo] - LL__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 14, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DjumpDxlxlp_numRows() const { return 14; }
  integer HypersonicProblem3DOF::DjumpDxlxlp_numCols() const { return 29; }
  integer HypersonicProblem3DOF::DjumpDxlxlp_nnz()     const { return 28; }

  void
  HypersonicProblem3DOF::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 14  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 15  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 16  ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 17  ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 18  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 19  ;
    iIndex[12] = 6   ; jIndex[12] = 6   ;
    iIndex[13] = 6   ; jIndex[13] = 20  ;
    iIndex[14] = 7   ; jIndex[14] = 7   ;
    iIndex[15] = 7   ; jIndex[15] = 21  ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
    iIndex[17] = 8   ; jIndex[17] = 22  ;
    iIndex[18] = 9   ; jIndex[18] = 9   ;
    iIndex[19] = 9   ; jIndex[19] = 23  ;
    iIndex[20] = 10  ; jIndex[20] = 10  ;
    iIndex[21] = 10  ; jIndex[21] = 24  ;
    iIndex[22] = 11  ; jIndex[22] = 11  ;
    iIndex[23] = 11  ; jIndex[23] = 25  ;
    iIndex[24] = 12  ; jIndex[24] = 12  ;
    iIndex[25] = 12  ; jIndex[25] = 26  ;
    iIndex[26] = 13  ; jIndex[26] = 13  ;
    iIndex[27] = 13  ; jIndex[27] = 27  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::DjumpDxlxlp_sparse(
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
    result__[ 24  ] = -1;
    result__[ 25  ] = 1;
    result__[ 26  ] = -1;
    result__[ 27  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 28, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer HypersonicProblem3DOF::post_numEqns() const { return 14; }

  void
  HypersonicProblem3DOF::post_eval(
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
    result__[ 0   ] = u2Control(U__[iU_u2], -1, 1);
    real_type t2   = X__[iX_G];
    result__[ 1   ] = G_bound_min(-0.314159265358979323846264338328e1 - t2);
    result__[ 2   ] = G_bound_max(t2 - 0.314159265358979323846264338328e1);
    result__[ 3   ] = X__[iX_h];
    result__[ 4   ] = X__[iX_V];
    real_type t5   = U__[iU_alpha];
    real_type t6   = ModelPars[iM_to_deg];
    result__[ 5   ] = t6 * t5;
    result__[ 6   ] = t6 * X__[iX_theta];
    result__[ 7   ] = t6 * X__[iX_phi];
    result__[ 8   ] = t6 * t2;
    result__[ 9   ] = t6 * X__[iX_psi];
    result__[ 10  ] = t6 * X__[iX_sigma];
    result__[ 11  ] = t5 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t15  = t5 * t5;
    result__[ 12  ] = t15 * ModelPars[iM_CD2] + t5 * ModelPars[iM_CD1] + ModelPars[iM_CD0];
    result__[ 13  ] = 1.0 / 0.314159265358979323846264338328e1 * t2;
    // do not check
    // Mechatronix::check_in_segment( result__, "post_eval", 14, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::integrated_post_numEqns() const { return 0; }

  void
  HypersonicProblem3DOF::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: HypersonicProblem3DOF_Methods_problem.cc
