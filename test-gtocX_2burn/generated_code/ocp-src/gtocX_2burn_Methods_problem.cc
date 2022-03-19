/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_problem.cc                                 |
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
    real_type t12  = X__[iX_p];
    real_type t13  = Q__[iQ_zeta];
    real_type t15  = ModelPars[iM_time_i];
    real_type t17  = ModelPars[iM_time_f];
    real_type t19  = t15 * (1 - t13) + t17 * t13;
    real_type t20  = p_guess(t19);
    real_type t24  = pow(1.0 / t20 * t12 - 1, 2);
    real_type t25  = f_guess(t19);
    real_type t27  = pow(t1 - t25, 2);
    real_type t28  = g_guess(t19);
    real_type t30  = pow(t5 - t28, 2);
    real_type t32  = h_guess(t19);
    real_type t34  = pow(X__[iX_h] - t32, 2);
    real_type t36  = k_guess(t19);
    real_type t38  = pow(X__[iX_k] - t36, 2);
    real_type t39  = L_guess(t19, t15);
    real_type t41  = pow(t2 - t39, 2);
    real_type t45  = t17 - t15;
    real_type t47  = sqrt(t12);
    real_type t49  = ModelPars[iM_muS];
    real_type t50  = sqrt(t49);
    real_type t53  = ModelPars[iM_w_nonlin] / t50;
    real_type t54  = ray(t12, t1, t5, t2);
    real_type t55  = acceleration_r(t54, t49);
    real_type t68  = t8 * t8;
    real_type result__ = t9 + (t24 + t27 + t30 + t34 + t38 + t41) * (1 - ModelPars[iM_w_guess]) + t6 * t55 * t53 * t47 * t45 * L__[iL_lambda2__xo] - t3 * t55 * t53 * t47 * t45 * L__[iL_lambda3__xo] + t50 / t47 / t12 * t68 * t45 * L__[iL_lambda6__xo];
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
  gtocX_2burn::JP_eval(
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
  gtocX_2burn::JU_eval(
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
  gtocX_2burn::LT_eval(
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
  gtocX_2burn::lagrange_target(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
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
  gtocX_2burn::mayer_target(
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

  integer gtocX_2burn::DmayerDxxp_numEqns() const { return 12; }

  void
  gtocX_2burn::DmayerDxxp_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DmayerDxxp_eval", 12, i_segment_left, i_segment_right );
  }

  /*\
   |   _
   |  | |    __ _  __ _ _ __ __ _ _ __   __ _  ___
   |  | |   / _` |/ _` | '__/ _` | '_ \ / _` |/ _ \
   |  | |__| (_| | (_| | | | (_| | | | | (_| |  __/
   |  |_____\__,_|\__, |_|  \__,_|_| |_|\__, |\___|
   |              |___/                 |___/
  \*/

  integer gtocX_2burn::DlagrangeDxup_numEqns() const { return 6; }

  void
  gtocX_2burn::DlagrangeDxup_eval(
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
  integer gtocX_2burn::IPOPT_hess_numRows() const { return 6; }
  integer gtocX_2burn::IPOPT_hess_numCols() const { return 6; }
  integer gtocX_2burn::IPOPT_hess_nnz()     const { return 18; }

  void
  gtocX_2burn::IPOPT_hess_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 5   ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 4   ; jIndex[13] = 4   ;
    iIndex[14] = 5   ; jIndex[14] = 0   ;
    iIndex[15] = 5   ; jIndex[15] = 1   ;
    iIndex[16] = 5   ; jIndex[16] = 2   ;
    iIndex[17] = 5   ; jIndex[17] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::IPOPT_hess_sparse(
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
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t11  = p_guess(t6 * (1 - t4) + t8 * t4);
    real_type t12  = t11 * t11;
    real_type t16  = L__[iL_lambda2__xo];
    real_type t17  = t8 - t6;
    real_type t18  = X__[iX_p];
    real_type t19  = sqrt(t18);
    real_type t21  = 1.0 / t19 / t18;
    real_type t23  = ModelPars[iM_muS];
    real_type t24  = sqrt(t23);
    real_type t25  = 1.0 / t24;
    real_type t26  = t25 * t21 * t17;
    real_type t27  = ModelPars[iM_w_nonlin];
    real_type t28  = X__[iX_f];
    real_type t29  = X__[iX_g];
    real_type t30  = X__[iX_L];
    real_type t31  = ray(t18, t28, t29, t30);
    real_type t32  = acceleration_r(t31, t23);
    real_type t33  = t32 * t27;
    real_type t34  = sin(t30);
    real_type t35  = t34 * t33;
    real_type t40  = t25 / t19 * t17;
    real_type t41  = acceleration_r_D_1(t31, t23);
    real_type t42  = t41 * t27;
    real_type t43  = ray_D_1(t18, t28, t29, t30);
    real_type t44  = t34 * t43;
    real_type t45  = t44 * t42;
    real_type t47  = t19 * t17;
    real_type t48  = t25 * t47;
    real_type t49  = acceleration_r_D_1_1(t31, t23);
    real_type t50  = t49 * t27;
    real_type t51  = t43 * t43;
    real_type t55  = ray_D_1_1(t18, t28, t29, t30);
    real_type t61  = L__[iL_lambda3__xo];
    real_type t62  = cos(t30);
    real_type t63  = t62 * t33;
    real_type t66  = t62 * t43;
    real_type t67  = t66 * t42;
    real_type t78  = t17 * L__[iL_lambda6__xo];
    real_type t79  = t62 * t28;
    real_type t80  = t34 * t29;
    real_type t81  = 1 + t79 + t80;
    real_type t82  = t81 * t81;
    real_type t83  = t18 * t18;
    result__[ 0   ] = 2 / t12 * t3 + (-t35 * t26 / 4 + t45 * t40 + t34 * t51 * t50 * t48 + t34 * t55 * t42 * t48) * t16 + (t63 * t26 / 4 - t67 * t40 - t62 * t51 * t50 * t48 - t62 * t55 * t42 * t48) * t61 + 0.15e2 / 4.0 * t24 / t19 / t83 / t18 * t82 * t78;
    real_type t91  = ray_D_2(t18, t28, t29, t30);
    real_type t93  = t34 * t91 * t42;
    real_type t97  = t27 * t25 * t47;
    real_type t98  = t91 * t49;
    real_type t101 = ray_D_1_2(t18, t28, t29, t30);
    real_type t108 = t62 * t91 * t42;
    real_type t118 = t81 * t78;
    real_type t121 = t24 / t19 / t83;
    result__[ 1   ] = (t93 * t40 / 2 + t44 * t98 * t97 + t34 * t101 * t42 * t48) * t16 + (-t108 * t40 / 2 - t66 * t98 * t97 - t62 * t101 * t42 * t48) * t61 - 3 * t62 * t121 * t118;
    real_type t125 = ray_D_3(t18, t28, t29, t30);
    real_type t127 = t34 * t125 * t42;
    real_type t130 = t125 * t49;
    real_type t133 = ray_D_1_3(t18, t28, t29, t30);
    real_type t140 = t62 * t125 * t42;
    result__[ 2   ] = (t127 * t40 / 2 + t44 * t130 * t97 + t34 * t133 * t42 * t48) * t16 + (-t140 * t40 / 2 - t66 * t130 * t97 - t62 * t133 * t42 * t48) * t61 - 3 * t34 * t121 * t118;
    real_type t153 = ray_D_4(t18, t28, t29, t30);
    real_type t155 = t34 * t153 * t42;
    real_type t160 = t153 * t49;
    real_type t163 = ray_D_1_4(t18, t28, t29, t30);
    real_type t171 = t62 * t153 * t42;
    real_type t186 = -t34 * t28 + t62 * t29;
    result__[ 3   ] = (t155 * t40 / 2 + t63 * t40 / 2 + t44 * t160 * t97 + t34 * t163 * t42 * t48 + t67 * t48) * t16 + (-t171 * t40 / 2 + t35 * t40 / 2 - t66 * t160 * t97 - t62 * t163 * t42 * t48 + t45 * t48) * t61 - 3 * t186 * t121 * t118;
    result__[ 4   ] = result__[1];
    real_type t190 = 2 * t3;
    real_type t192 = t25 * t19;
    real_type t193 = t192 * t17 * t16;
    real_type t194 = t91 * t91;
    real_type t198 = ray_D_2_2(t18, t28, t29, t30);
    real_type t203 = t192 * t17 * t61;
    real_type t210 = t62 * t62;
    result__[ 5   ] = t34 * t194 * t50 * t193 + t34 * t198 * t42 * t193 - t62 * t194 * t50 * t203 - t62 * t198 * t42 * t203 + 2 * t24 * t21 * t210 * t78 + t190;
    real_type t215 = t91 * t125;
    real_type t219 = ray_D_2_3(t18, t28, t29, t30);
    real_type t230 = t24 * t21;
    real_type t231 = t62 * t230;
    result__[ 6   ] = t34 * t215 * t50 * t193 + t34 * t219 * t42 * t193 - t62 * t215 * t50 * t203 - t62 * t219 * t42 * t203 + 2 * t231 * t34 * t78;
    real_type t234 = t91 * t153;
    real_type t238 = ray_D_2_4(t18, t28, t29, t30);
    real_type t250 = t186 * t78;
    real_type t253 = t34 * t230;
    result__[ 7   ] = t34 * t234 * t50 * t193 + t34 * t238 * t42 * t193 - t62 * t234 * t50 * t203 - t62 * t238 * t42 * t203 + t108 * t193 - 2 * t253 * t118 + t93 * t203 + 2 * t231 * t250;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t256 = t125 * t125;
    real_type t260 = ray_D_3_3(t18, t28, t29, t30);
    real_type t270 = t34 * t34;
    result__[ 10  ] = t34 * t256 * t50 * t193 + t34 * t260 * t42 * t193 - t62 * t256 * t50 * t203 - t62 * t260 * t42 * t203 + 2 * t24 * t21 * t270 * t78 + t190;
    real_type t275 = t125 * t153;
    real_type t279 = ray_D_3_4(t18, t28, t29, t30);
    result__[ 11  ] = t34 * t275 * t50 * t193 + t34 * t279 * t42 * t193 - t62 * t275 * t50 * t203 - t62 * t279 * t42 * t203 + 2 * t231 * t118 + t127 * t203 + t140 * t193 + 2 * t253 * t250;
    result__[ 12  ] = t190;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[3];
    result__[ 15  ] = result__[7];
    result__[ 16  ] = result__[11];
    real_type t295 = t153 * t153;
    real_type t299 = ray_D_4_4(t18, t28, t29, t30);
    real_type t319 = t186 * t186;
    result__[ 17  ] = result__[13] + (t34 * t295 * t50 * t48 + t34 * t299 * t42 * t48 + 2 * t171 * t48 - t35 * t48) * t16 + (-t62 * t295 * t50 * t48 - t62 * t299 * t42 * t48 + 2 * t155 * t48 + t63 * t48) * t61 + 2 * t24 * t21 * t319 * t78 + 2 * (-t79 - t80) * t230 * t118;
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
  gtocX_2burn::q_numEqns() const
  { return 1; }

  void
  gtocX_2burn::q_eval(
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

  integer gtocX_2burn::segmentLink_numEqns() const { return 0; }

  void
  gtocX_2burn::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::DsegmentLinkDxp_numRows() const { return 0; }
  integer gtocX_2burn::DsegmentLinkDxp_numCols() const { return 0; }
  integer gtocX_2burn::DsegmentLinkDxp_nnz() const { return 0; }

  void
  gtocX_2burn::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DsegmentLinkDxp_sparse(
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

  integer gtocX_2burn::jump_numEqns() const { return 12; }

  void
  gtocX_2burn::jump_eval(
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

  integer gtocX_2burn::post_numEqns() const { return 20; }

  void
  gtocX_2burn::post_eval(
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
    real_type t7   = X__[iX_p];
    real_type t8   = X__[iX_f];
    real_type t9   = X__[iX_g];
    real_type t10  = X__[iX_L];
    result__[ 1   ] = ray(t7, t8, t9, t10);
    real_type t11  = X__[iX_h];
    real_type t12  = X__[iX_k];
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

  integer gtocX_2burn::integrated_post_numEqns() const { return 0; }

  void
  gtocX_2burn::integrated_post_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
   // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods_problem.cc
