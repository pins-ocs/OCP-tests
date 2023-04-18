/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_AdjointODE.cc                         |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burn_parsDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::Hxp_numEqns() const { return 6; }

  void
  gtocX_2burn_pars::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t3   = X__[iX_f];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = f_guess(t10);
    real_type t15  = X__[iX_L];
    real_type t16  = cos(t15);
    real_type t18  = X__[iX_g];
    real_type t19  = sin(t15);
    real_type t21  = -t16 * t3 - t19 * t18 - 1;
    real_type t22  = ALIAS_ray_positive_D(t21);
    real_type t24  = MU__[0];
    real_type t25  = t8 - t6;
    real_type t27  = P__[iP_p];
    real_type t28  = sqrt(t27);
    real_type t29  = ModelPars[iM_muS];
    real_type t30  = sqrt(t29);
    real_type t31  = 1.0 / t30;
    real_type t32  = t31 * t28;
    real_type t33  = t32 * t25 * t24;
    real_type t34  = ModelPars[iM_w_nonlin];
    real_type t35  = ray(t27, t3, t18, t15);
    real_type t36  = acceleration_r_D_1(t35, t29);
    real_type t37  = t36 * t34;
    real_type t38  = ray_D_2(t27, t3, t18, t15);
    real_type t42  = MU__[1];
    real_type t44  = t32 * t25 * t42;
    real_type t49  = t25 * MU__[2];
    real_type t50  = -t21;
    real_type t51  = t50 * t49;
    real_type t54  = t30 / t28 / t27;
    result__[ 0   ] = (2 * t3 - 2 * t11) * t2 - t16 * t22 + t19 * t38 * t37 * t33 - t16 * t38 * t37 * t44 + 2 * t16 * t54 * t51;
    real_type t58  = g_guess(t10);
    real_type t63  = ray_D_3(t27, t3, t18, t15);
    result__[ 1   ] = (2 * t18 - 2 * t58) * t2 - t19 * t22 + t19 * t63 * t37 * t33 - t16 * t63 * t37 * t44 + 2 * t19 * t54 * t51;
    real_type t73  = L_guess(t10, t6);
    real_type t79  = -t16 * t18 + t19 * t3;
    real_type t82  = t31 * t28 * t25;
    real_type t83  = ray_D_4(t27, t3, t18, t15);
    real_type t87  = acceleration_r(t35, t29);
    real_type t88  = t87 * t34;
    real_type t89  = t16 * t88;
    real_type t96  = t19 * t88;
    result__[ 2   ] = (2 * t15 - 2 * t73) * t2 + t79 * t22 + (t19 * t83 * t37 * t82 + t89 * t82) * t24 + (-t16 * t83 * t37 * t82 + t96 * t82) * t42 - 2 * t79 * t54 * t51;
    real_type t104 = p_guess(0);
    real_type t105 = 1.0 / t104;
    real_type t113 = t31 / t28 * t25;
    real_type t116 = ray_D_1(t27, t3, t18, t15);
    real_type t129 = t50 * t50;
    real_type t130 = t27 * t27;
    result__[ 3   ] = 2 * t105 * (t105 * t27 - 1) * t2 + (t96 * t113 / 2 + t19 * t116 * t37 * t82) * t24 + (-t89 * t113 / 2 - t16 * t116 * t37 * t82) * t42 - 3.0 / 2.0 * t30 / t28 / t130 * t129 * t49;
    real_type t138 = h_guess(0);
    result__[ 4   ] = (2 * P__[iP_h] - 2 * t138) * t2;
    real_type t142 = k_guess(0);
    result__[ 5   ] = (2 * P__[iP_k] - 2 * t142) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 6, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DHxpDxpuv_numRows() const { return 6; }
  integer gtocX_2burn_pars::DHxpDxpuv_numCols() const { return 9; }
  integer gtocX_2burn_pars::DHxpDxpuv_nnz()     const { return 18; }

  void
  gtocX_2burn_pars::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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


  void
  gtocX_2burn_pars::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_w_guess];
    real_type t2   = 2 * t1;
    real_type t3   = X__[iX_f];
    real_type t4   = X__[iX_L];
    real_type t5   = cos(t4);
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_g];
    real_type t8   = sin(t4);
    real_type t9   = t8 * t7;
    real_type t10  = -1 - t6 - t9;
    real_type t11  = ALIAS_ray_positive_DD(t10);
    real_type t12  = t5 * t5;
    real_type t14  = MU__[0];
    real_type t17  = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t18  = t17 * t14;
    real_type t19  = P__[iP_p];
    real_type t20  = sqrt(t19);
    real_type t21  = ModelPars[iM_muS];
    real_type t22  = sqrt(t21);
    real_type t23  = 1.0 / t22;
    real_type t24  = t23 * t20;
    real_type t25  = t24 * t18;
    real_type t26  = ModelPars[iM_w_nonlin];
    real_type t27  = ray(t19, t3, t7, t4);
    real_type t28  = acceleration_r_D_1_1(t27, t21);
    real_type t29  = t28 * t26;
    real_type t30  = ray_D_2(t19, t3, t7, t4);
    real_type t31  = t30 * t30;
    real_type t35  = acceleration_r_D_1(t27, t21);
    real_type t36  = t35 * t26;
    real_type t37  = ray_D_2_2(t19, t3, t7, t4);
    real_type t41  = MU__[1];
    real_type t42  = t17 * t41;
    real_type t43  = t24 * t42;
    real_type t51  = t17 * MU__[2];
    real_type t53  = 1.0 / t20 / t19;
    result__[ 0   ] = 2 * t22 * t53 * t12 * t51 + t8 * t31 * t29 * t25 + t8 * t37 * t36 * t25 - t5 * t31 * t29 * t43 - t5 * t37 * t36 * t43 + t12 * t11 - t2 + 2;
    real_type t60  = ray_D_3(t19, t3, t7, t4);
    real_type t61  = t30 * t60;
    real_type t65  = ray_D_2_3(t19, t3, t7, t4);
    real_type t76  = t22 * t53;
    real_type t77  = t5 * t76;
    result__[ 1   ] = t8 * t61 * t29 * t25 + t8 * t65 * t36 * t25 - t5 * t61 * t29 * t43 - t5 * t65 * t36 * t43 + t5 * t8 * t11 + 2 * t77 * t8 * t51;
    real_type t82  = t8 * t3 - t5 * t7;
    real_type t83  = t82 * t11;
    real_type t84  = t5 * t83;
    real_type t85  = ALIAS_ray_positive_D(t10);
    real_type t86  = t8 * t85;
    real_type t87  = ray_D_4(t19, t3, t7, t4);
    real_type t88  = t30 * t87;
    real_type t92  = ray_D_2_4(t19, t3, t7, t4);
    real_type t94  = t8 * t92 * t36;
    real_type t97  = t5 * t30 * t36;
    real_type t103 = t5 * t92 * t36;
    real_type t106 = t8 * t30 * t36;
    real_type t108 = -t82;
    real_type t109 = t108 * t51;
    real_type t111 = 2 * t77 * t109;
    real_type t112 = -t10;
    real_type t113 = t112 * t51;
    real_type t114 = t8 * t76;
    real_type t116 = 2 * t114 * t113;
    result__[ 2   ] = t8 * t88 * t29 * t25 - t5 * t88 * t29 * t43 - t103 * t43 + t106 * t43 + t94 * t25 + t97 * t25 + t111 - t116 - t84 + t86;
    real_type t117 = 1.0 / t20;
    real_type t118 = t23 * t117;
    real_type t119 = t118 * t18;
    real_type t122 = ray_D_1(t19, t3, t7, t4);
    real_type t123 = t30 * t122;
    real_type t127 = ray_D_1_2(t19, t3, t7, t4);
    real_type t129 = t8 * t127 * t36;
    real_type t131 = t118 * t42;
    real_type t138 = t5 * t127 * t36;
    real_type t140 = t19 * t19;
    real_type t143 = t22 / t20 / t140;
    real_type t146 = 3 * t5 * t143 * t113;
    result__[ 3   ] = t106 * t119 / 2 + t8 * t123 * t29 * t25 + t129 * t25 - t97 * t131 / 2 - t5 * t123 * t29 * t43 - t138 * t43 - t146;
    result__[ 4   ] = result__[1];
    real_type t147 = t8 * t8;
    real_type t149 = t60 * t60;
    real_type t153 = ray_D_3_3(t19, t3, t7, t4);
    result__[ 5   ] = 2 * t22 * t53 * t147 * t51 + t8 * t149 * t29 * t25 - t5 * t149 * t29 * t43 + t8 * t153 * t36 * t25 - t5 * t153 * t36 * t43 + t147 * t11 - t2 + 2;
    real_type t167 = t8 * t83;
    real_type t168 = t5 * t85;
    real_type t169 = t60 * t87;
    real_type t173 = ray_D_3_4(t19, t3, t7, t4);
    real_type t175 = t8 * t173 * t36;
    real_type t178 = t5 * t60 * t36;
    real_type t184 = t5 * t173 * t36;
    real_type t187 = t8 * t60 * t36;
    real_type t190 = 2 * t114 * t109;
    real_type t192 = 2 * t77 * t113;
    result__[ 6   ] = t8 * t169 * t29 * t25 - t5 * t169 * t29 * t43 + t175 * t25 + t178 * t25 - t184 * t43 + t187 * t43 - t167 - t168 + t190 + t192;
    real_type t195 = t60 * t122;
    real_type t199 = ray_D_1_3(t19, t3, t7, t4);
    real_type t201 = t8 * t199 * t36;
    real_type t209 = t5 * t199 * t36;
    real_type t213 = 3 * t8 * t143 * t113;
    result__[ 7   ] = t187 * t119 / 2 + t8 * t195 * t29 * t25 + t201 * t25 - t178 * t131 / 2 - t5 * t195 * t29 * t43 - t209 * t43 - t213;
    real_type t214 = t20 * t17;
    real_type t216 = t26 * t23 * t214;
    real_type t217 = t30 * t28;
    real_type t218 = t8 * t87;
    real_type t221 = t23 * t214;
    real_type t226 = t5 * t87;
    result__[ 8   ] = -t84 + t86 + (t218 * t217 * t216 + t94 * t221 + t97 * t221) * t14 + (-t226 * t217 * t216 - t103 * t221 + t106 * t221) * t41 + t111 - t116;
    real_type t233 = t60 * t28;
    result__[ 9   ] = -t167 - t168 + (t218 * t233 * t216 + t175 * t221 + t178 * t221) * t14 + (-t226 * t233 * t216 - t184 * t221 + t187 * t221) * t41 + t190 + t192;
    real_type t246 = t82 * t82;
    real_type t248 = t6 + t9;
    real_type t250 = t87 * t87;
    real_type t254 = ray_D_4_4(t19, t3, t7, t4);
    real_type t258 = t226 * t36;
    real_type t261 = acceleration_r(t27, t21);
    real_type t262 = t261 * t26;
    real_type t263 = t8 * t262;
    real_type t273 = t218 * t36;
    real_type t276 = t5 * t262;
    real_type t280 = t108 * t108;
    result__[ 10  ] = 2 - t2 + t246 * t11 + t248 * t85 + (t8 * t250 * t29 * t221 + t8 * t254 * t36 * t221 + 2 * t258 * t221 - t263 * t221) * t14 + (-t5 * t250 * t29 * t221 - t5 * t254 * t36 * t221 + 2 * t273 * t221 + t276 * t221) * t41 + 2 * t22 * t53 * t280 * t51 - 2 * t248 * t76 * t113;
    real_type t290 = t23 * t117 * t17;
    real_type t293 = t122 * t28;
    real_type t296 = ray_D_1_4(t19, t3, t7, t4);
    real_type t302 = t5 * t122;
    real_type t303 = t302 * t36;
    real_type t316 = t8 * t122;
    real_type t317 = t316 * t36;
    result__[ 11  ] = (t273 * t290 / 2 + t218 * t293 * t216 + t8 * t296 * t36 * t221 + t276 * t290 / 2 + t303 * t221) * t14 + (-t258 * t290 / 2 - t226 * t293 * t216 - t5 * t296 * t36 * t221 + t263 * t290 / 2 + t317 * t221) * t41 - 3 * t108 * t143 * t113;
    result__[ 12  ] = (t106 * t290 / 2 + t316 * t217 * t216 + t129 * t221) * t14 + (-t97 * t290 / 2 - t302 * t217 * t216 - t138 * t221) * t41 - t146;
    result__[ 13  ] = (t187 * t290 / 2 + t316 * t233 * t216 + t201 * t221) * t14 + (-t178 * t290 / 2 - t302 * t233 * t216 - t209 * t221) * t41 - t213;
    result__[ 14  ] = result__[11];
    real_type t352 = 1 - t1;
    real_type t353 = p_guess(0);
    real_type t354 = t353 * t353;
    real_type t359 = t23 * t53 * t17;
    real_type t363 = t122 * t122;
    real_type t367 = ray_D_1_1(t19, t3, t7, t4);
    real_type t384 = t112 * t112;
    result__[ 15  ] = 2 / t354 * t352 + (-t263 * t359 / 4 + t317 * t290 + t8 * t363 * t29 * t221 + t8 * t367 * t36 * t221) * t14 + (t276 * t359 / 4 - t303 * t290 - t5 * t363 * t29 * t221 - t5 * t367 * t36 * t221) * t41 + 0.15e2 / 4.0 * t22 / t20 / t140 / t19 * t384 * t51;
    result__[ 16  ] = 2 * t352;
    result__[ 17  ] = result__[16];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 18, i_segment );
  }

}

// EOF: gtocX_2burn_pars_Methods_AdjointODE.cc
