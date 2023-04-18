/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_AdjointODE.cc                              |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::Hxp_numEqns() const { return 6; }

  void
  gtocX_2burn::Hxp_eval(
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
    real_type t3   = X__[iX_p];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = p_guess(t10);
    real_type t12  = 1.0 / t11;
    real_type t18  = MU__[1];
    real_type t19  = t8 - t6;
    real_type t20  = sqrt(t3);
    real_type t23  = ModelPars[iM_muS];
    real_type t24  = sqrt(t23);
    real_type t25  = 1.0 / t24;
    real_type t26  = t25 / t20 * t19;
    real_type t27  = ModelPars[iM_w_nonlin];
    real_type t28  = X__[iX_f];
    real_type t29  = X__[iX_g];
    real_type t30  = X__[iX_L];
    real_type t31  = ray(t3, t28, t29, t30);
    real_type t32  = acceleration_r(t31, t23);
    real_type t33  = t32 * t27;
    real_type t34  = sin(t30);
    real_type t35  = t34 * t33;
    real_type t39  = t25 * t20 * t19;
    real_type t40  = acceleration_r_D_1(t31, t23);
    real_type t41  = t40 * t27;
    real_type t42  = ray_D_1(t3, t28, t29, t30);
    real_type t48  = MU__[2];
    real_type t49  = cos(t30);
    real_type t50  = t49 * t33;
    real_type t59  = t19 * MU__[5];
    real_type t62  = t49 * t28 + t34 * t29 + 1;
    real_type t63  = t62 * t62;
    real_type t64  = t3 * t3;
    result__[ 0   ] = 2 * t12 * (t12 * t3 - 1) * t2 + (t35 * t26 / 2 + t34 * t42 * t41 * t39) * t18 + (-t50 * t26 / 2 - t49 * t42 * t41 * t39) * t48 - 3.0 / 2.0 * t24 / t20 / t64 * t63 * t59;
    real_type t71  = f_guess(t10);
    real_type t76  = ALIAS_ray_positive_D(-t62);
    real_type t79  = t25 * t20;
    real_type t80  = t79 * t19 * t18;
    real_type t81  = ray_D_2(t3, t28, t29, t30);
    real_type t86  = t79 * t19 * t48;
    real_type t90  = t62 * t59;
    real_type t93  = t24 / t20 / t3;
    result__[ 1   ] = (2 * t28 - 2 * t71) * t2 - t49 * t76 + t34 * t81 * t41 * t80 - t49 * t81 * t41 * t86 + 2 * t49 * t93 * t90;
    real_type t97  = g_guess(t10);
    real_type t102 = ray_D_3(t3, t28, t29, t30);
    result__[ 2   ] = (2 * t29 - 2 * t97) * t2 - t34 * t76 + t34 * t102 * t41 * t80 - t49 * t102 * t41 * t86 + 2 * t34 * t93 * t90;
    real_type t113 = h_guess(t10);
    result__[ 3   ] = (2 * X__[iX_h] - 2 * t113) * t2;
    real_type t117 = k_guess(t10);
    result__[ 4   ] = (2 * X__[iX_k] - 2 * t117) * t2;
    real_type t120 = L_guess(t10, t6);
    real_type t126 = t34 * t28 - t49 * t29;
    real_type t128 = ray_D_4(t3, t28, t29, t30);
    result__[ 5   ] = (2 * t30 - 2 * t120) * t2 + t126 * t76 + (t34 * t128 * t41 * t39 + t50 * t39) * t18 + (-t49 * t128 * t41 * t39 + t35 * t39) * t48 - 2 * t126 * t93 * t90;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 6, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DHxpDxpuv_numRows() const { return 6; }
  integer gtocX_2burn::DHxpDxpuv_numCols() const { return 12; }
  integer gtocX_2burn::DHxpDxpuv_nnz()     const { return 18; }

  void
  gtocX_2burn::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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


  void
  gtocX_2burn::DHxpDxpuv_sparse(
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
    real_type t2   = 1 - t1;
    real_type t3   = Q__[iQ_zeta];
    real_type t5   = ModelPars[iM_time_i];
    real_type t7   = ModelPars[iM_time_f];
    real_type t10  = p_guess(t5 * (1 - t3) + t7 * t3);
    real_type t11  = t10 * t10;
    real_type t15  = MU__[1];
    real_type t16  = t7 - t5;
    real_type t17  = X__[iX_p];
    real_type t18  = sqrt(t17);
    real_type t20  = 1.0 / t18 / t17;
    real_type t22  = ModelPars[iM_muS];
    real_type t23  = sqrt(t22);
    real_type t24  = 1.0 / t23;
    real_type t25  = t24 * t20 * t16;
    real_type t26  = ModelPars[iM_w_nonlin];
    real_type t27  = X__[iX_f];
    real_type t28  = X__[iX_g];
    real_type t29  = X__[iX_L];
    real_type t30  = ray(t17, t27, t28, t29);
    real_type t31  = acceleration_r(t30, t22);
    real_type t32  = t31 * t26;
    real_type t33  = sin(t29);
    real_type t34  = t33 * t32;
    real_type t37  = 1.0 / t18;
    real_type t39  = t24 * t37 * t16;
    real_type t40  = acceleration_r_D_1(t30, t22);
    real_type t41  = t40 * t26;
    real_type t42  = ray_D_1(t17, t27, t28, t29);
    real_type t43  = t33 * t42;
    real_type t44  = t43 * t41;
    real_type t46  = t18 * t16;
    real_type t47  = t24 * t46;
    real_type t48  = acceleration_r_D_1_1(t30, t22);
    real_type t49  = t48 * t26;
    real_type t50  = t42 * t42;
    real_type t54  = ray_D_1_1(t17, t27, t28, t29);
    real_type t60  = MU__[2];
    real_type t61  = cos(t29);
    real_type t62  = t61 * t32;
    real_type t65  = t61 * t42;
    real_type t66  = t65 * t41;
    real_type t77  = t16 * MU__[5];
    real_type t78  = t61 * t27;
    real_type t79  = t33 * t28;
    real_type t80  = 1 + t78 + t79;
    real_type t81  = t80 * t80;
    real_type t82  = t17 * t17;
    result__[ 0   ] = 2 / t11 * t2 + (-t34 * t25 / 4 + t44 * t39 + t33 * t50 * t49 * t47 + t33 * t54 * t41 * t47) * t15 + (t62 * t25 / 4 - t66 * t39 - t61 * t50 * t49 * t47 - t61 * t54 * t41 * t47) * t60 + 0.15e2 / 4.0 * t23 / t18 / t82 / t17 * t81 * t77;
    real_type t90  = ray_D_2(t17, t27, t28, t29);
    real_type t92  = t33 * t90 * t41;
    real_type t96  = t26 * t24 * t46;
    real_type t97  = t90 * t48;
    real_type t100 = ray_D_1_2(t17, t27, t28, t29);
    real_type t102 = t33 * t100 * t41;
    real_type t107 = t61 * t90 * t41;
    real_type t113 = t61 * t100 * t41;
    real_type t117 = t80 * t77;
    real_type t120 = t23 / t18 / t82;
    real_type t123 = 3 * t61 * t120 * t117;
    result__[ 1   ] = (t92 * t39 / 2 + t43 * t97 * t96 + t102 * t47) * t15 + (-t107 * t39 / 2 - t65 * t97 * t96 - t113 * t47) * t60 - t123;
    real_type t124 = ray_D_3(t17, t27, t28, t29);
    real_type t126 = t33 * t124 * t41;
    real_type t129 = t124 * t48;
    real_type t132 = ray_D_1_3(t17, t27, t28, t29);
    real_type t134 = t33 * t132 * t41;
    real_type t139 = t61 * t124 * t41;
    real_type t145 = t61 * t132 * t41;
    real_type t151 = 3 * t33 * t120 * t117;
    result__[ 2   ] = (t126 * t39 / 2 + t43 * t129 * t96 + t134 * t47) * t15 + (-t139 * t39 / 2 - t65 * t129 * t96 - t145 * t47) * t60 - t151;
    real_type t152 = ray_D_4(t17, t27, t28, t29);
    real_type t153 = t33 * t152;
    real_type t154 = t153 * t41;
    real_type t159 = t152 * t48;
    real_type t162 = ray_D_1_4(t17, t27, t28, t29);
    real_type t169 = t61 * t152;
    real_type t170 = t169 * t41;
    real_type t185 = -t33 * t27 + t61 * t28;
    result__[ 3   ] = (t154 * t39 / 2 + t62 * t39 / 2 + t43 * t159 * t96 + t33 * t162 * t41 * t47 + t66 * t47) * t15 + (-t170 * t39 / 2 + t34 * t39 / 2 - t65 * t159 * t96 - t61 * t162 * t41 * t47 + t44 * t47) * t60 - 3 * t185 * t120 * t117;
    real_type t189 = t16 * t15;
    real_type t190 = t24 * t37;
    real_type t191 = t190 * t189;
    real_type t194 = t24 * t18;
    real_type t195 = t194 * t189;
    real_type t196 = t90 * t42;
    real_type t201 = t16 * t60;
    real_type t202 = t190 * t201;
    real_type t205 = t194 * t201;
    result__[ 4   ] = t92 * t191 / 2 + t33 * t196 * t49 * t195 + t102 * t195 - t107 * t202 / 2 - t61 * t196 * t49 * t205 - t113 * t205 - t123;
    real_type t210 = 2 * t1;
    real_type t211 = -t80;
    real_type t212 = ALIAS_ray_positive_DD(t211);
    real_type t213 = t61 * t61;
    real_type t215 = t90 * t90;
    real_type t219 = ray_D_2_2(t17, t27, t28, t29);
    result__[ 5   ] = t33 * t215 * t49 * t195 + t33 * t219 * t41 * t195 + 2 * t23 * t20 * t213 * t77 - t61 * t215 * t49 * t205 - t61 * t219 * t41 * t205 + t213 * t212 - t210 + 2;
    real_type t235 = t90 * t124;
    real_type t239 = ray_D_2_3(t17, t27, t28, t29);
    real_type t250 = t23 * t20;
    real_type t251 = t61 * t250;
    result__[ 6   ] = t33 * t235 * t49 * t195 + t33 * t239 * t41 * t195 - t61 * t235 * t49 * t205 - t61 * t239 * t41 * t205 + t61 * t33 * t212 + 2 * t251 * t33 * t77;
    real_type t254 = -t185;
    real_type t255 = t254 * t212;
    real_type t256 = t61 * t255;
    real_type t257 = ALIAS_ray_positive_D(t211);
    real_type t258 = t33 * t257;
    real_type t259 = t90 * t152;
    real_type t263 = ray_D_2_4(t17, t27, t28, t29);
    real_type t265 = t33 * t263 * t41;
    real_type t272 = t61 * t263 * t41;
    real_type t275 = t185 * t77;
    real_type t277 = 2 * t251 * t275;
    real_type t278 = t33 * t250;
    real_type t280 = 2 * t278 * t117;
    result__[ 7   ] = t33 * t259 * t49 * t195 - t61 * t259 * t49 * t205 + t107 * t195 + t265 * t195 - t272 * t205 + t92 * t205 - t256 + t258 + t277 - t280;
    real_type t283 = t124 * t42;
    result__[ 8   ] = t126 * t191 / 2 + t33 * t283 * t49 * t195 + t134 * t195 - t139 * t202 / 2 - t61 * t283 * t49 * t205 - t145 * t205 - t151;
    result__[ 9   ] = result__[6];
    real_type t294 = t33 * t33;
    real_type t296 = t124 * t124;
    real_type t300 = ray_D_3_3(t17, t27, t28, t29);
    result__[ 10  ] = t33 * t296 * t49 * t195 + t33 * t300 * t41 * t195 + 2 * t23 * t20 * t294 * t77 - t61 * t296 * t49 * t205 - t61 * t300 * t41 * t205 + t294 * t212 - t210 + 2;
    real_type t314 = t33 * t255;
    real_type t315 = t61 * t257;
    real_type t316 = t124 * t152;
    real_type t320 = ray_D_3_4(t17, t27, t28, t29);
    real_type t322 = t33 * t320 * t41;
    real_type t329 = t61 * t320 * t41;
    real_type t333 = 2 * t278 * t275;
    real_type t335 = 2 * t251 * t117;
    result__[ 11  ] = t33 * t316 * t49 * t195 - t61 * t316 * t49 * t205 + t126 * t205 + t139 * t195 + t322 * t195 - t329 * t205 - t314 - t315 + t333 + t335;
    result__[ 12  ] = 2 * t2;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[3];
    result__[ 15  ] = -t256 + t258 + (t153 * t97 * t96 + t107 * t47 + t265 * t47) * t15 + (-t169 * t97 * t96 - t272 * t47 + t92 * t47) * t60 + t277 - t280;
    result__[ 16  ] = -t314 - t315 + (t153 * t129 * t96 + t139 * t47 + t322 * t47) * t15 + (-t169 * t129 * t96 + t126 * t47 - t329 * t47) * t60 + t333 + t335;
    real_type t360 = t254 * t254;
    real_type t362 = t78 + t79;
    real_type t364 = t152 * t152;
    real_type t368 = ray_D_4_4(t17, t27, t28, t29);
    real_type t388 = t185 * t185;
    result__[ 17  ] = 2 - t210 + t360 * t212 + t362 * t257 + (t33 * t364 * t49 * t47 + t33 * t368 * t41 * t47 + 2 * t170 * t47 - t34 * t47) * t15 + (-t61 * t364 * t49 * t47 - t61 * t368 * t41 * t47 + 2 * t154 * t47 + t62 * t47) * t60 + 2 * t23 * t20 * t388 * t77 - 2 * t362 * t250 * t117;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 18, i_segment );
  }

}

// EOF: gtocX_2burn_Methods_AdjointODE.cc
