/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_problem.cc                                 |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burnDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn::continuation_step_0( real_type s ) {
    ModelPars[iM_w_guess] = s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn::continuation_step_1( real_type s ) {
    ModelPars[iM_w_nonlin] = s;
  }

  /*\
   |  _  _            _ _ _            _
   | | || |__ _ _ __ (_) | |_ ___ _ _ (_)__ _ _ _
   | | __ / _` | '  \| | |  _/ _ \ ' \| / _` | ' \
   | |_||_\__,_|_|_|_|_|_|\__\___/_||_|_\__,_|_||_|
   |
  \*/

  real_type
  gtocX_2burn::H_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_p];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = p_guess(t10);
    real_type t15  = pow(1.0 / t11 * t3 - 1, 2);
    real_type t16  = X__[iX_f];
    real_type t17  = f_guess(t10);
    real_type t19  = pow(t16 - t17, 2);
    real_type t20  = X__[iX_g];
    real_type t21  = g_guess(t10);
    real_type t23  = pow(t20 - t21, 2);
    real_type t25  = h_guess(t10);
    real_type t27  = pow(X__[iX_h] - t25, 2);
    real_type t29  = k_guess(t10);
    real_type t31  = pow(X__[iX_k] - t29, 2);
    real_type t32  = X__[iX_L];
    real_type t33  = L_guess(t10, t6);
    real_type t35  = pow(t32 - t33, 2);
    real_type t39  = t8 - t6;
    real_type t41  = sqrt(t3);
    real_type t43  = ModelPars[iM_muS];
    real_type t44  = sqrt(t43);
    real_type t47  = ModelPars[iM_w_nonlin] / t44;
    real_type t48  = ray(t3, t16, t20, t32);
    real_type t49  = acceleration_r(t48, t43);
    real_type t50  = sin(t32);
    real_type t57  = cos(t32);
    real_type t66  = pow(t57 * t16 + t50 * t20 + 1, 2);
    real_type result__ = (t15 + t19 + t23 + t27 + t31 + t35) * (1 - ModelPars[iM_w_guess]) + t50 * t49 * t47 * t41 * t39 * MU__[1] - t57 * t49 * t47 * t41 * t39 * MU__[2] + t44 / t41 / t3 * t66 * t39 * MU__[5];
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
  gtocX_2burn::lagrange_target(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t10  = t6 * (1 - t4) + ModelPars[iM_time_f] * t4;
    real_type t11  = p_guess(t10);
    real_type t15  = pow(1.0 / t11 * X__[iX_p] - 1, 2);
    real_type t17  = f_guess(t10);
    real_type t19  = pow(X__[iX_f] - t17, 2);
    real_type t21  = g_guess(t10);
    real_type t23  = pow(X__[iX_g] - t21, 2);
    real_type t25  = h_guess(t10);
    real_type t27  = pow(X__[iX_h] - t25, 2);
    real_type t29  = k_guess(t10);
    real_type t31  = pow(X__[iX_k] - t29, 2);
    real_type t33  = L_guess(t10, t6);
    real_type t35  = pow(X__[iX_L] - t33, 2);
    real_type result__ = (t15 + t19 + t23 + t27 + t31 + t35) * (1 - ModelPars[iM_w_guess]);
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
  gtocX_2burn::mayer_target(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__
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
      UTILS_ASSERT( Utils::is_finite(result__), "mayer_target(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::DmayerDxxp_numEqns() const { return 12; }

  void
  gtocX_2burn::DmayerDxxp_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 12, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2mayerD2xxp_numRows() const { return 12; }
  integer gtocX_2burn::D2mayerD2xxp_numCols() const { return 12; }
  integer gtocX_2burn::D2mayerD2xxp_nnz()     const { return 0; }

  void
  gtocX_2burn::D2mayerD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::D2mayerD2xxp_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
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

  integer gtocX_2burn::DlagrangeDxpu_numEqns() const { return 6; }

  void
  gtocX_2burn::DlagrangeDxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t10  = t6 * (1 - t4) + ModelPars[iM_time_f] * t4;
    real_type t11  = p_guess(t10);
    real_type t12  = 1.0 / t11;
    result__[ 0   ] = 2 * t12 * (t12 * X__[iX_p] - 1) * t2;
    real_type t18  = f_guess(t10);
    result__[ 1   ] = (2 * X__[iX_f] - 2 * t18) * t2;
    real_type t22  = g_guess(t10);
    result__[ 2   ] = (2 * X__[iX_g] - 2 * t22) * t2;
    real_type t26  = h_guess(t10);
    result__[ 3   ] = (2 * X__[iX_h] - 2 * t26) * t2;
    real_type t30  = k_guess(t10);
    result__[ 4   ] = (2 * X__[iX_k] - 2 * t30) * t2;
    real_type t34  = L_guess(t10, t6);
    result__[ 5   ] = (2 * X__[iX_L] - 2 * t34) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DlagrangeDxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2lagrangeD2xpu_numRows() const { return 6; }
  integer gtocX_2burn::D2lagrangeD2xpu_numCols() const { return 6; }
  integer gtocX_2burn::D2lagrangeD2xpu_nnz()     const { return 6; }

  void
  gtocX_2burn::D2lagrangeD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
  }


  void
  gtocX_2burn::D2lagrangeD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t3   = Q__[iQ_zeta];
    real_type t10  = p_guess(ModelPars[iM_time_i] * (1 - t3) + ModelPars[iM_time_f] * t3);
    real_type t11  = t10 * t10;
    result__[ 0   ] = 2 / t11 * t2;
    result__[ 1   ] = 2 * t2;
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2lagrangeD2xpu_eval", 6, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  gtocX_2burn::q_numEqns() const
  { return 1; }

  void
  gtocX_2burn::q_eval(
    integer   i_segment,
    real_type s,
    Q_p_type  result__
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

  integer gtocX_2burn::segmentLink_numEqns() const { return 0; }

  void
  gtocX_2burn::segmentLink_eval(
    NodeQX const & L,
    NodeQX const & R,
    P_const_p_type p,
    real_ptr        segmentLink
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::DsegmentLinkDxxp_numRows() const { return 0; }
  integer gtocX_2burn::DsegmentLinkDxxp_numCols() const { return 0; }
  integer gtocX_2burn::DsegmentLinkDxxp_nnz() const { return 0; }

  void
  gtocX_2burn::DsegmentLinkDxxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DsegmentLinkDxxp_sparse(
    NodeQX const & L,
    NodeQX const & R,
    P_const_p_type p,
    real_ptr       DsegmentLinkDxxp
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

  integer gtocX_2burn::jump_numEqns() const { return 12; }

  void
  gtocX_2burn::jump_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    real_ptr        result__
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
    result__[ 0   ] = XR__[iX_p] - XL__[iX_p];
    result__[ 1   ] = XR__[iX_f] - XL__[iX_f];
    result__[ 2   ] = XR__[iX_g] - XL__[iX_g];
    result__[ 3   ] = XR__[iX_h] - XL__[iX_h];
    result__[ 4   ] = XR__[iX_k] - XL__[iX_k];
    result__[ 5   ] = XR__[iX_L] - XL__[iX_L];
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
  integer gtocX_2burn::DjumpDxlxlp_numRows() const { return 12; }
  integer gtocX_2burn::DjumpDxlxlp_numCols() const { return 24; }
  integer gtocX_2burn::DjumpDxlxlp_nnz()     const { return 24; }

  void
  gtocX_2burn::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  gtocX_2burn::DjumpDxlxlp_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    real_ptr        result__
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

  integer gtocX_2burn::post_numEqns() const { return 21; }

  void
  gtocX_2burn::post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    result__[ 0   ] = ray_positive(-t3 * t1 - t6 * t5 - 1);
    real_type t9   = Q__[iQ_zeta];
    result__[ 1   ] = ModelPars[iM_time_i] * (1 - t9) + ModelPars[iM_time_f] * t9;
    real_type t15  = X__[iX_p];
    result__[ 2   ] = ray(t15, t1, t5, t2);
    real_type t16  = X__[iX_h];
    real_type t17  = X__[iX_k];
    real_type t18  = ModelPars[iM_retrograde];
    result__[ 3   ] = x_position(t15, t1, t5, t16, t17, t2, t18);
    result__[ 4   ] = y_position(t15, t1, t5, t16, t17, t2, t18);
    result__[ 5   ] = z_position(t15, t1, t5, t16, t17, t2, t18);
    result__[ 6   ] = x_velocity(t15, t1, t5, t16, t17, t2, t18);
    result__[ 7   ] = y_velocity(t15, t1, t5, t16, t17, t2, t18);
    result__[ 8   ] = z_velocity(t15, t1, t5, t16, t17, t2, t18);
    result__[ 9   ] = X_begin(result__[1]);
    result__[ 10  ] = Y_begin(result__[1]);
    result__[ 11  ] = Z_begin(result__[1]);
    result__[ 12  ] = VX_begin(result__[1]);
    result__[ 13  ] = VY_begin(result__[1]);
    result__[ 14  ] = VZ_begin(result__[1]);
    result__[ 15  ] = X_end(result__[1]);
    result__[ 16  ] = Y_end(result__[1]);
    result__[ 17  ] = Z_end(result__[1]);
    result__[ 18  ] = VX_end(result__[1]);
    result__[ 19  ] = VY_end(result__[1]);
    result__[ 20  ] = VZ_end(result__[1]);
    // do not check
    // Mechatronix::check_in_segment( result__, "post_eval", 21, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::integrated_post_numEqns() const { return 0; }

  void
  gtocX_2burn::integrated_post_eval(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods_problem.cc
