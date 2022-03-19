/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_problem.cc                            |
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


#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burn_parsDefine {
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn_pars::continuation_step_0( real_type s ) {
    ModelPars[iM_w_guess] = s;
  }
  /*\
   |   ___         _   _               _   _
   |  / __|___ _ _| |_(_)_ _ _  _ __ _| |_(_)___ _ _
   | | (__/ _ \ ' \  _| | ' \ || / _` |  _| / _ \ ' \
   |  \___\___/_||_\__|_|_||_\_,_\__,_|\__|_\___/_||_|
  \*/

  void
  gtocX_2burn_pars::continuation_step_1( real_type s ) {
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
  gtocX_2burn_pars::H_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
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
    real_type t8   = -t3 * t1 - t6 * t5 - 1;
    real_type t9   = ray_positive(t8);
    real_type t12  = P__[iP_p];
    real_type t13  = p_guess(0);
    real_type t17  = pow(1.0 / t13 * t12 - 1, 2);
    real_type t18  = Q__[iQ_zeta];
    real_type t20  = ModelPars[iM_time_i];
    real_type t22  = ModelPars[iM_time_f];
    real_type t24  = t20 * (1 - t18) + t22 * t18;
    real_type t25  = f_guess(t24);
    real_type t27  = pow(t1 - t25, 2);
    real_type t28  = g_guess(t24);
    real_type t30  = pow(t5 - t28, 2);
    real_type t32  = h_guess(0);
    real_type t34  = pow(P__[iP_h] - t32, 2);
    real_type t36  = k_guess(0);
    real_type t38  = pow(P__[iP_k] - t36, 2);
    real_type t39  = L_guess(t24, t20);
    real_type t41  = pow(t2 - t39, 2);
    real_type t45  = t22 - t20;
    real_type t47  = sqrt(t12);
    real_type t49  = ModelPars[iM_muS];
    real_type t50  = sqrt(t49);
    real_type t53  = ModelPars[iM_w_nonlin] / t50;
    real_type t54  = ray(t12, t1, t5, t2);
    real_type t55  = acceleration_r(t54, t49);
    real_type t68  = t8 * t8;
    real_type result__ = t9 + (t17 + t27 + t30 + t34 + t38 + t41) * (1 - ModelPars[iM_w_guess]) + t6 * t55 * t53 * t47 * t45 * L__[iL_lambda1__xo] - t3 * t55 * t53 * t47 * t45 * L__[iL_lambda2__xo] + t50 / t47 / t12 * t68 * t45 * L__[iL_lambda3__xo];
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
  gtocX_2burn_pars::JP_eval(
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
  gtocX_2burn_pars::JU_eval(
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
      UTILS_ASSERT( isRegular(result__), "JU_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  gtocX_2burn_pars::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    real_type result__ = ray_positive(-t3 * X__[iX_f] - t6 * X__[iX_g] - 1);
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
  gtocX_2burn_pars::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = p_guess(0);
    real_type t8   = pow(1.0 / t4 * P__[iP_p] - 1, 2);
    real_type t10  = Q__[iQ_zeta];
    real_type t12  = ModelPars[iM_time_i];
    real_type t16  = t12 * (1 - t10) + ModelPars[iM_time_f] * t10;
    real_type t17  = f_guess(t16);
    real_type t19  = pow(X__[iX_f] - t17, 2);
    real_type t21  = g_guess(t16);
    real_type t23  = pow(X__[iX_g] - t21, 2);
    real_type t25  = h_guess(0);
    real_type t27  = pow(P__[iP_h] - t25, 2);
    real_type t29  = k_guess(0);
    real_type t31  = pow(P__[iP_k] - t29, 2);
    real_type t33  = L_guess(t16, t12);
    real_type t35  = pow(X__[iX_L] - t33, 2);
    real_type result__ = (t8 + t19 + t23 + t27 + t31 + t35) * (1 - ModelPars[iM_w_guess]);
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
  gtocX_2burn_pars::mayer_target(
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

  integer gtocX_2burn_pars::DmayerDxxp_numEqns() const { return 9; }

  void
  gtocX_2burn_pars::DmayerDxxp_eval(
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

  integer gtocX_2burn_pars::DlagrangeDxup_numEqns() const { return 6; }

  void
  gtocX_2burn_pars::DlagrangeDxup_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t10  = t6 * (1 - t4) + ModelPars[iM_time_f] * t4;
    real_type t11  = f_guess(t10);
    result__[ 0   ] = (2 * X__[iX_f] - 2 * t11) * t2;
    real_type t15  = g_guess(t10);
    result__[ 1   ] = (2 * X__[iX_g] - 2 * t15) * t2;
    real_type t19  = L_guess(t10, t6);
    result__[ 2   ] = (2 * X__[iX_L] - 2 * t19) * t2;
    real_type t23  = p_guess(0);
    real_type t24  = 1.0 / t23;
    result__[ 3   ] = 2 * t24 * (t24 * P__[iP_p] - 1) * t2;
    real_type t30  = h_guess(0);
    result__[ 4   ] = (2 * P__[iP_h] - 2 * t30) * t2;
    real_type t34  = k_guess(0);
    result__[ 5   ] = (2 * P__[iP_k] - 2 * t34) * t2;
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
  integer gtocX_2burn_pars::IPOPT_hess_numRows() const { return 6; }
  integer gtocX_2burn_pars::IPOPT_hess_numCols() const { return 6; }
  integer gtocX_2burn_pars::IPOPT_hess_nnz()     const { return 18; }

  void
  gtocX_2burn_pars::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
    iIndex[16] = 4   ; jIndex[16] = 4   ;
    iIndex[17] = 5   ; jIndex[17] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::IPOPT_hess_sparse(
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
    real_type t3   = sigma__ * (1 - ModelPars[iM_w_guess]);
    real_type t4   = 2 * t3;
    real_type t5   = L__[iL_lambda1__xo];
    real_type t8   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t9   = t8 * t5;
    real_type t10  = P__[iP_p];
    real_type t11  = sqrt(t10);
    real_type t12  = ModelPars[iM_muS];
    real_type t13  = sqrt(t12);
    real_type t14  = 1.0 / t13;
    real_type t15  = t14 * t11;
    real_type t16  = t15 * t9;
    real_type t17  = ModelPars[iM_w_nonlin];
    real_type t18  = X__[iX_f];
    real_type t19  = X__[iX_g];
    real_type t20  = X__[iX_L];
    real_type t21  = ray(t10, t18, t19, t20);
    real_type t22  = acceleration_r_D_1_1(t21, t12);
    real_type t23  = t22 * t17;
    real_type t24  = ray_D_2(t10, t18, t19, t20);
    real_type t25  = t24 * t24;
    real_type t26  = sin(t20);
    real_type t30  = acceleration_r_D_1(t21, t12);
    real_type t31  = t30 * t17;
    real_type t32  = ray_D_2_2(t10, t18, t19, t20);
    real_type t36  = L__[iL_lambda2__xo];
    real_type t37  = t8 * t36;
    real_type t38  = t15 * t37;
    real_type t39  = cos(t20);
    real_type t47  = t8 * L__[iL_lambda3__xo];
    real_type t48  = t39 * t39;
    real_type t50  = 1.0 / t11 / t10;
    result__[ 0   ] = 2 * t13 * t50 * t48 * t47 + t26 * t25 * t23 * t16 + t26 * t32 * t31 * t16 - t39 * t25 * t23 * t38 - t39 * t32 * t31 * t38 + t4;
    real_type t55  = ray_D_3(t10, t18, t19, t20);
    real_type t56  = t24 * t55;
    real_type t60  = ray_D_2_3(t10, t18, t19, t20);
    real_type t71  = t13 * t50;
    real_type t72  = t39 * t71;
    result__[ 1   ] = t26 * t56 * t23 * t16 + t26 * t60 * t31 * t16 - t39 * t56 * t23 * t38 - t39 * t60 * t31 * t38 + 2 * t72 * t26 * t47;
    real_type t75  = ray_D_4(t10, t18, t19, t20);
    real_type t76  = t24 * t75;
    real_type t80  = ray_D_2_4(t10, t18, t19, t20);
    real_type t85  = t39 * t24 * t31;
    real_type t94  = t26 * t24 * t31;
    real_type t98  = -t26 * t18 + t39 * t19;
    real_type t99  = t98 * t47;
    real_type t102 = t39 * t18;
    real_type t103 = t26 * t19;
    real_type t104 = 1 + t102 + t103;
    real_type t105 = t104 * t47;
    real_type t106 = t26 * t71;
    result__[ 2   ] = t26 * t76 * t23 * t16 + t26 * t80 * t31 * t16 - t39 * t76 * t23 * t38 - t39 * t80 * t31 * t38 - 2 * t106 * t105 + t85 * t16 + t94 * t38 + 2 * t72 * t99;
    real_type t109 = 1.0 / t11;
    real_type t110 = t14 * t109;
    real_type t111 = t110 * t9;
    real_type t114 = ray_D_1(t10, t18, t19, t20);
    real_type t115 = t24 * t114;
    real_type t119 = ray_D_1_2(t10, t18, t19, t20);
    real_type t123 = t110 * t37;
    real_type t132 = t10 * t10;
    real_type t135 = t13 / t11 / t132;
    result__[ 3   ] = t94 * t111 / 2 + t26 * t115 * t23 * t16 + t26 * t119 * t31 * t16 - t85 * t123 / 2 - t39 * t115 * t23 * t38 - t39 * t119 * t31 * t38 - 3 * t39 * t135 * t105;
    result__[ 4   ] = result__[1];
    real_type t139 = t55 * t55;
    real_type t143 = ray_D_3_3(t10, t18, t19, t20);
    real_type t153 = t26 * t26;
    result__[ 5   ] = 2 * t13 * t50 * t153 * t47 + t26 * t139 * t23 * t16 - t39 * t139 * t23 * t38 + t26 * t143 * t31 * t16 - t39 * t143 * t31 * t38 + t4;
    real_type t158 = t55 * t75;
    real_type t162 = ray_D_3_4(t10, t18, t19, t20);
    real_type t167 = t39 * t55 * t31;
    real_type t176 = t26 * t55 * t31;
    result__[ 6   ] = t26 * t158 * t23 * t16 - t39 * t158 * t23 * t38 + t26 * t162 * t31 * t16 - t39 * t162 * t31 * t38 + 2 * t72 * t105 + 2 * t106 * t99 + t167 * t16 + t176 * t38;
    real_type t184 = t55 * t114;
    real_type t188 = ray_D_1_3(t10, t18, t19, t20);
    result__[ 7   ] = t176 * t111 / 2 + t26 * t184 * t23 * t16 + t26 * t188 * t31 * t16 - t167 * t123 / 2 - t39 * t184 * t23 * t38 - t39 * t188 * t31 * t38 - 3 * t26 * t135 * t105;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t203 = t11 * t8;
    real_type t204 = t14 * t203;
    real_type t205 = t75 * t75;
    real_type t209 = ray_D_4_4(t10, t18, t19, t20);
    real_type t213 = t39 * t75;
    real_type t214 = t213 * t31;
    real_type t217 = acceleration_r(t21, t12);
    real_type t218 = t217 * t17;
    real_type t219 = t26 * t218;
    real_type t229 = t26 * t75;
    real_type t230 = t229 * t31;
    real_type t233 = t39 * t218;
    real_type t237 = t98 * t98;
    result__[ 10  ] = t4 + (t26 * t205 * t23 * t204 + t26 * t209 * t31 * t204 + 2 * t214 * t204 - t219 * t204) * t5 + (-t39 * t205 * t23 * t204 - t39 * t209 * t31 * t204 + 2 * t230 * t204 + t233 * t204) * t36 + 2 * t13 * t50 * t237 * t47 + 2 * (-t102 - t103) * t71 * t105;
    real_type t247 = t14 * t109 * t8;
    real_type t251 = t17 * t14 * t203;
    real_type t252 = t114 * t22;
    real_type t255 = ray_D_1_4(t10, t18, t19, t20);
    real_type t262 = t39 * t114 * t31;
    real_type t276 = t26 * t114 * t31;
    result__[ 11  ] = (t230 * t247 / 2 + t229 * t252 * t251 + t26 * t255 * t31 * t204 + t233 * t247 / 2 + t262 * t204) * t5 + (-t214 * t247 / 2 - t213 * t252 * t251 - t39 * t255 * t31 * t204 + t219 * t247 / 2 + t276 * t204) * t36 - 3 * t98 * t135 * t105;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    real_type t283 = p_guess(0);
    real_type t284 = t283 * t283;
    real_type t289 = t14 * t50 * t8;
    real_type t293 = t114 * t114;
    real_type t297 = ray_D_1_1(t10, t18, t19, t20);
    real_type t314 = t104 * t104;
    result__[ 15  ] = 2 / t284 * t3 + (-t219 * t289 / 4 + t276 * t247 + t26 * t293 * t23 * t204 + t26 * t297 * t31 * t204) * t5 + (t233 * t289 / 4 - t262 * t247 - t39 * t293 * t23 * t204 - t39 * t297 * t31 * t204) * t36 + 0.15e2 / 4.0 * t13 / t11 / t132 / t10 * t314 * t47;
    result__[ 16  ] = t4;
    result__[ 17  ] = result__[16];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"IPOPT_hess_sparse", 18, i_segment );
  }

  /*\
   |    ___
   |   / _ \
   |  | (_) |
   |   \__\_\
  \*/

  integer
  gtocX_2burn_pars::q_numEqns() const
  { return 1; }

  void
  gtocX_2burn_pars::q_eval(
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

  integer gtocX_2burn_pars::segmentLink_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::DsegmentLinkDxp_numRows() const { return 0; }
  integer gtocX_2burn_pars::DsegmentLinkDxp_numCols() const { return 0; }
  integer gtocX_2burn_pars::DsegmentLinkDxp_nnz() const { return 0; }

  void
  gtocX_2burn_pars::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DsegmentLinkDxp_sparse(
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

  integer gtocX_2burn_pars::jump_numEqns() const { return 6; }

  void
  gtocX_2burn_pars::jump_eval(
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
    result__[ 0   ] = XR__[iX_f] - XL__[iX_f];
    result__[ 1   ] = XR__[iX_g] - XL__[iX_g];
    result__[ 2   ] = XR__[iX_L] - XL__[iX_L];
    result__[ 3   ] = LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo];
    result__[ 4   ] = LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo];
    result__[ 5   ] = LR__[iL_lambda3__xo] - LL__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 6, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DjumpDxlxlp_numRows() const { return 6; }
  integer gtocX_2burn_pars::DjumpDxlxlp_numCols() const { return 15; }
  integer gtocX_2burn_pars::DjumpDxlxlp_nnz()     const { return 12; }

  void
  gtocX_2burn_pars::DjumpDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 10  ;
    iIndex[10] = 5   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 11  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn_pars::DjumpDxlxlp_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlxlp_sparse", 12, i_segment_left, i_segment_right );
  }

  /*\
   |   ___        _     ___                       _
   |  | _ \___ __| |_  | _ \_ _ ___  __ ___ _____(_)_ _  __ _
   |  |  _/ _ (_-<  _| |  _/ '_/ _ \/ _/ -_|_-<_-< | ' \/ _` |
   |  |_| \___/__/\__| |_| |_| \___/\__\___/__/__/_|_||_\__, |
   |                                                    |___/
  \*/

  integer gtocX_2burn_pars::post_numEqns() const { return 20; }

  void
  gtocX_2burn_pars::post_eval(
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
    real_type t1   = Q__[iQ_zeta];
    result__[ 0   ] = ModelPars[iM_time_i] * (1 - t1) + ModelPars[iM_time_f] * t1;
    real_type t7   = P__[iP_p];
    real_type t8   = X__[iX_f];
    real_type t9   = X__[iX_g];
    real_type t10  = X__[iX_L];
    result__[ 1   ] = ray(t7, t8, t9, t10);
    real_type t11  = P__[iP_h];
    real_type t12  = P__[iP_k];
    real_type t13  = ModelPars[iM_retrograde];
    result__[ 2   ] = x_position(t7, t8, t9, t11, t12, t10, t13);
    result__[ 3   ] = y_position(t7, t8, t9, t11, t12, t10, t13);
    result__[ 4   ] = z_position(t7, t8, t9, t11, t12, t10, t13);
    result__[ 5   ] = x_velocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 6   ] = y_velocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 7   ] = z_velocity(t7, t8, t9, t11, t12, t10, t13);
    result__[ 8   ] = X_begin(result__[0]);
    result__[ 9   ] = Y_begin(result__[0]);
    result__[ 10  ] = Z_begin(result__[0]);
    result__[ 11  ] = VX_begin(result__[0]);
    result__[ 12  ] = VY_begin(result__[0]);
    result__[ 13  ] = VZ_begin(result__[0]);
    result__[ 14  ] = X_end(result__[0]);
    result__[ 15  ] = Y_end(result__[0]);
    result__[ 16  ] = Z_end(result__[0]);
    result__[ 17  ] = VX_end(result__[0]);
    result__[ 18  ] = VY_end(result__[0]);
    result__[ 19  ] = VZ_end(result__[0]);
    Mechatronix::check_in_segment( result__, "post_eval", 20, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::integrated_post_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: gtocX_2burn_pars_Methods_problem.cc
