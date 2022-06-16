/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_problem.cc                      |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::PenaltyBarrier1DGreaterThan;
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
#define ALIAS_penalization_DD(__t1) Pen1D.evaluate_DD( __t1)
#define ALIAS_penalization_D(__t1) Pen1D.evaluate_D( __t1)
#define ALIAS_penalization(__t1) Pen1D.evaluate( __t1)


namespace ICLOCS2_BatchFermentorDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS2_BatchFermentor::continuation_step_0( real_type s ) {
    ModelPars[iM_WP] = s * ModelPars[iM_WP1] + (1 - s) * ModelPars[iM_WP0];
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  ICLOCS2_BatchFermentor::continuation_step_1( real_type s ) {
    ModelPars[iM_W] = s * ModelPars[iM_W1] + (1 - s) * ModelPars[iM_W0];
    ModelPars[iM_epsilon] = pow_average__xo(s, ModelPars[iM_epsilon0], ModelPars[iM_epsilon1]);
  }

  /*\
   |   ___               _ _   _
   |  | _ \___ _ _  __ _| | |_(_)___ ___
   |  |  _/ -_) ' \/ _` | |  _| / -_|_-<
   |  |_| \___|_||_\__,_|_|\__|_\___/__/
   |
  \*/

  bool
  ICLOCS2_BatchFermentor::penalties_check_cell(
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
    real_type Q__[1], X__[4];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    bool res = true;

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
    real_type t1   = ModelPars[iM_WP];
    real_type t2   = X__[iX_x];
    real_type t3   = U__[iU_c_x];
    real_type t5   = pow(t2 - t3, 2);
    real_type t7   = X__[iX_p];
    real_type t8   = U__[iU_c_p];
    real_type t10  = pow(t7 - t8, 2);
    real_type t12  = X__[iX_s];
    real_type t13  = U__[iU_c_s];
    real_type t15  = pow(t12 - t13, 2);
    real_type t17  = X__[iX_v];
    real_type t18  = U__[iU_c_v];
    real_type t20  = pow(t17 - t18, 2);
    real_type t24  = 1.0 / ModelPars[iM_x_max] * t3;
    real_type t25  = ALIAS_penalization(t24);
    real_type t27  = ALIAS_penalization(1 - t24);
    real_type t30  = 1.0 / ModelPars[iM_p_max] * t8;
    real_type t31  = ALIAS_penalization(t30);
    real_type t33  = ALIAS_penalization(1 - t30);
    real_type t36  = 1.0 / ModelPars[iM_s_max] * t13;
    real_type t37  = ALIAS_penalization(t36);
    real_type t39  = ALIAS_penalization(1 - t36);
    real_type t41  = 1.0 / ModelPars[iM_v_max];
    real_type t42  = t41 * t18;
    real_type t43  = ALIAS_penalization(t42);
    real_type t45  = ALIAS_penalization(1 - t42);
    real_type t47  = ALIAS_penalization(t41 * t17);
    real_type t49  = U__[iU_w];
    real_type t50  = t49 * t49;
    real_type t52  = ModelPars[iM_epsilon];
    real_type t53  = t52 * t52;
    real_type t57  = log(1 + 1.0 / t53 * t50);
    real_type t61  = mu(t12, t2);
    real_type t62  = t2 * t61;
    real_type t63  = U(t49);
    real_type t65  = 1.0 / t17;
    real_type t70  = rho(t12);
    real_type t71  = t2 * t70;
    real_type result__ = t5 * t1 + t10 * t1 + t15 * t1 + t20 * t1 + t25 + t27 + t31 + t33 + t37 + t39 + t43 + t45 + t47 + t50 * ModelPars[iM_W] + t57 * t52 / 2 + (-t65 * t63 * t2 + t62) * L__[iL_lambda1__xo] + (-t65 * t63 * t7 - t7 * ModelPars[iM_K_degr] + t71) * L__[iL_lambda2__xo] + (-1.0 / ModelPars[iM_Yxs] * t62 - 1.0 / ModelPars[iM_Yes] * t71 - t2 / (ModelPars[iM_kappa_m] + t12) * t12 * ModelPars[iM_mu_s] + (ModelPars[iM_S_f] - t12) * t65 * t63) * L__[iL_lambda3__xo] + t63 * L__[iL_lambda4__xo];
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
  ICLOCS2_BatchFermentor::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WP];
    real_type t3   = U__[iU_c_x];
    real_type t5   = pow(X__[iX_x] - t3, 2);
    real_type t8   = U__[iU_c_p];
    real_type t10  = pow(X__[iX_p] - t8, 2);
    real_type t13  = U__[iU_c_s];
    real_type t15  = pow(X__[iX_s] - t13, 2);
    real_type t17  = X__[iX_v];
    real_type t18  = U__[iU_c_v];
    real_type t20  = pow(t17 - t18, 2);
    real_type t24  = 1.0 / ModelPars[iM_x_max] * t3;
    real_type t25  = ALIAS_penalization(t24);
    real_type t27  = ALIAS_penalization(1 - t24);
    real_type t30  = 1.0 / ModelPars[iM_p_max] * t8;
    real_type t31  = ALIAS_penalization(t30);
    real_type t33  = ALIAS_penalization(1 - t30);
    real_type t36  = 1.0 / ModelPars[iM_s_max] * t13;
    real_type t37  = ALIAS_penalization(t36);
    real_type t39  = ALIAS_penalization(1 - t36);
    real_type t41  = 1.0 / ModelPars[iM_v_max];
    real_type t42  = t41 * t18;
    real_type t43  = ALIAS_penalization(t42);
    real_type t45  = ALIAS_penalization(1 - t42);
    real_type t47  = ALIAS_penalization(t41 * t17);
    real_type t50  = U__[iU_w] * U__[iU_w];
    real_type t52  = ModelPars[iM_epsilon];
    real_type t53  = t52 * t52;
    real_type t57  = log(1 + 1.0 / t53 * t50);
    real_type result__ = t5 * t1 + t10 * t1 + t15 * t1 + t20 * t1 + t25 + t27 + t31 + t33 + t37 + t39 + t43 + t45 + t47 + t50 * ModelPars[iM_W] + t57 * t52 / 2;
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

  integer ICLOCS2_BatchFermentor::DmayerDxxp_numEqns() const { return 8; }

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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2mayerD2xxp_numRows() const { return 8; }
  integer ICLOCS2_BatchFermentor::D2mayerD2xxp_numCols() const { return 8; }
  integer ICLOCS2_BatchFermentor::D2mayerD2xxp_nnz()     const { return 2; }

  void
  ICLOCS2_BatchFermentor::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 5   ; jIndex[0 ] = 7   ;
    iIndex[1 ] = 7   ; jIndex[1 ] = 5   ;
  }


  void
  ICLOCS2_BatchFermentor::D2mayerD2xxp_sparse(
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
    result__[ 0   ] = -1;
    result__[ 1   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "D2mayerD2xxp_eval", 2, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer ICLOCS2_BatchFermentor::DlagrangeDxpu_numEqns() const { return 9; }

  void
  ICLOCS2_BatchFermentor::DlagrangeDxpu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WP];
    real_type t3   = U__[iU_c_x];
    result__[ 0   ] = 2 * (X__[iX_x] - t3) * t1;
    real_type t7   = U__[iU_c_p];
    result__[ 1   ] = 2 * (X__[iX_p] - t7) * t1;
    real_type t11  = U__[iU_c_s];
    result__[ 2   ] = 2 * (X__[iX_s] - t11) * t1;
    real_type t14  = X__[iX_v];
    real_type t15  = U__[iU_c_v];
    real_type t18  = 2 * (t14 - t15) * t1;
    real_type t20  = 1.0 / ModelPars[iM_v_max];
    real_type t22  = ALIAS_penalization_D(t20 * t14);
    result__[ 3   ] = t20 * t22 + t18;
    real_type t25  = 1.0 / ModelPars[iM_x_max];
    real_type t26  = t25 * t3;
    real_type t27  = ALIAS_penalization_D(t26);
    real_type t30  = ALIAS_penalization_D(1 - t26);
    result__[ 4   ] = t25 * t27 - t25 * t30 - result__[0];
    real_type t33  = 1.0 / ModelPars[iM_p_max];
    real_type t34  = t33 * t7;
    real_type t35  = ALIAS_penalization_D(t34);
    real_type t38  = ALIAS_penalization_D(1 - t34);
    result__[ 5   ] = t33 * t35 - t33 * t38 - result__[1];
    real_type t41  = 1.0 / ModelPars[iM_s_max];
    real_type t42  = t41 * t11;
    real_type t43  = ALIAS_penalization_D(t42);
    real_type t46  = ALIAS_penalization_D(1 - t42);
    result__[ 6   ] = t41 * t43 - t41 * t46 - result__[2];
    real_type t48  = t20 * t15;
    real_type t49  = ALIAS_penalization_D(t48);
    real_type t52  = ALIAS_penalization_D(1 - t48);
    result__[ 7   ] = t20 * t49 - t20 * t52 - t18;
    real_type t55  = U__[iU_w];
    real_type t58  = ModelPars[iM_epsilon];
    real_type t61  = t55 * t55;
    real_type t62  = t58 * t58;
    result__[ 8   ] = 2 * t55 * ModelPars[iM_W] + 1.0 / (1 + 1.0 / t62 * t61) * t55 / t58;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::D2lagrangeD2xpu_numRows() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2lagrangeD2xpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::D2lagrangeD2xpu_nnz()     const { return 17; }

  void
  ICLOCS2_BatchFermentor::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 4   ;
    iIndex[10] = 5   ; jIndex[10] = 1   ;
    iIndex[11] = 5   ; jIndex[11] = 5   ;
    iIndex[12] = 6   ; jIndex[12] = 2   ;
    iIndex[13] = 6   ; jIndex[13] = 6   ;
    iIndex[14] = 7   ; jIndex[14] = 3   ;
    iIndex[15] = 7   ; jIndex[15] = 7   ;
    iIndex[16] = 8   ; jIndex[16] = 8   ;
  }


  void
  ICLOCS2_BatchFermentor::D2lagrangeD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 2 * ModelPars[iM_WP];
    result__[ 1   ] = -result__[0];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = result__[3];
    real_type t3   = ModelPars[iM_v_max];
    real_type t4   = 1.0 / t3;
    real_type t6   = ALIAS_penalization_DD(t4 * X__[iX_v]);
    real_type t7   = t3 * t3;
    real_type t8   = 1.0 / t7;
    result__[ 6   ] = t8 * t6 + result__[4];
    result__[ 7   ] = result__[5];
    result__[ 8   ] = result__[7];
    real_type t11  = ModelPars[iM_x_max];
    real_type t13  = 1.0 / t11 * U__[iU_c_x];
    real_type t14  = ALIAS_penalization_DD(t13);
    real_type t15  = t11 * t11;
    real_type t16  = 1.0 / t15;
    real_type t19  = ALIAS_penalization_DD(1 - t13);
    result__[ 9   ] = t16 * t14 + t16 * t19 + result__[4];
    result__[ 10  ] = result__[8];
    real_type t22  = ModelPars[iM_p_max];
    real_type t24  = 1.0 / t22 * U__[iU_c_p];
    real_type t25  = ALIAS_penalization_DD(t24);
    real_type t26  = t22 * t22;
    real_type t27  = 1.0 / t26;
    real_type t30  = ALIAS_penalization_DD(1 - t24);
    result__[ 11  ] = t27 * t25 + t27 * t30 + result__[4];
    result__[ 12  ] = result__[10];
    real_type t33  = ModelPars[iM_s_max];
    real_type t35  = 1.0 / t33 * U__[iU_c_s];
    real_type t36  = ALIAS_penalization_DD(t35);
    real_type t37  = t33 * t33;
    real_type t38  = 1.0 / t37;
    real_type t41  = ALIAS_penalization_DD(1 - t35);
    result__[ 13  ] = t38 * t36 + t38 * t41 + result__[4];
    result__[ 14  ] = result__[12];
    real_type t44  = t4 * U__[iU_c_v];
    real_type t45  = ALIAS_penalization_DD(t44);
    real_type t48  = ALIAS_penalization_DD(1 - t44);
    result__[ 15  ] = t8 * t45 + t8 * t48 + result__[4];
    real_type t52  = ModelPars[iM_epsilon];
    real_type t55  = U__[iU_w] * U__[iU_w];
    real_type t56  = t52 * t52;
    real_type t59  = 1 + 1.0 / t56 * t55;
    real_type t65  = t59 * t59;
    result__[ 16  ] = 2 * ModelPars[iM_W] + 1.0 / t59 / t52 - 2 / t65 * t55 / t56 / t52;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xpu_eval", 17, i_segment );
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

  integer ICLOCS2_BatchFermentor::segmentLink_numEqns() const { return 0; }

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

  integer ICLOCS2_BatchFermentor::DsegmentLinkDxp_numRows() const { return 0; }
  integer ICLOCS2_BatchFermentor::DsegmentLinkDxp_numCols() const { return 0; }
  integer ICLOCS2_BatchFermentor::DsegmentLinkDxp_nnz() const { return 0; }

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

  integer ICLOCS2_BatchFermentor::jump_numEqns() const { return 8; }

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
  integer ICLOCS2_BatchFermentor::DjumpDxlxlp_numRows() const { return 8; }
  integer ICLOCS2_BatchFermentor::DjumpDxlxlp_numCols() const { return 16; }
  integer ICLOCS2_BatchFermentor::DjumpDxlxlp_nnz()     const { return 16; }

  void
  ICLOCS2_BatchFermentor::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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

  integer ICLOCS2_BatchFermentor::post_numEqns() const { return 2; }

  void
  ICLOCS2_BatchFermentor::post_eval(
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
    real_type t2   = U(U__[iU_w]);
    result__[ 0   ] = ModelPars[iM_S_f] * t2;
    result__[ 1   ] = t2;
    // do not check
    // Mechatronix::check_in_segment( result__, "post_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::integrated_post_numEqns() const { return 0; }

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
