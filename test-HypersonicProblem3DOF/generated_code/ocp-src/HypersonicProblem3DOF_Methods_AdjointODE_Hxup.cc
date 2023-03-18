/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_AdjointODE.cc                    |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
#pragma warning( disable : 4189 )
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::Hxp_numEqns() const { return 8; }

  void
  HypersonicProblem3DOF::Hxp_eval(
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
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = P__[iP_Tf];
    real_type t3   = t2 * t1;
    real_type t4   = ModelPars[iM_ODE];
    real_type t5   = X__[iX_V];
    real_type t6   = t5 * t4;
    real_type t7   = t6 * t3;
    real_type t8   = X__[iX_G];
    real_type t9   = cos(t8);
    real_type t10  = X__[iX_psi];
    real_type t11  = cos(t10);
    real_type t12  = t11 * t9;
    real_type t14  = X__[iX_h];
    real_type t15  = ModelPars[iM_re] + t14;
    real_type t16  = t15 * t15;
    real_type t17  = 1.0 / t16;
    real_type t18  = X__[iX_phi];
    real_type t19  = cos(t18);
    real_type t20  = 1.0 / t19;
    real_type t24  = MU__[2];
    real_type t26  = t4 * t2 * t24;
    real_type t27  = t9 * t5;
    real_type t28  = sin(t10);
    real_type t32  = MU__[3];
    real_type t33  = t2 * t32;
    real_type t34  = sin(t8);
    real_type t35  = ModelPars[iM_mu];
    real_type t36  = t35 * t34;
    real_type t38  = 1.0 / t16 / t15;
    real_type t41  = ModelPars[iM_rho0];
    real_type t43  = 1.0 / ModelPars[iM_S];
    real_type t44  = t43 * t41;
    real_type t46  = exp(-t43 * t14);
    real_type t48  = t5 * t5;
    real_type t50  = U__[iU_alpha];
    real_type t51  = t50 * t50;
    real_type t56  = t50 * ModelPars[iM_CD1] + t51 * ModelPars[iM_CD2] + ModelPars[iM_CD0];
    real_type t58  = ModelPars[iM_Aref];
    real_type t60  = 1.0 / ModelPars[iM_m];
    real_type t61  = t60 * t58;
    real_type t68  = MU__[4];
    real_type t69  = t2 * t68;
    real_type t70  = t5 * t46;
    real_type t71  = t70 * t44;
    real_type t75  = t50 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t76  = t58 * t75;
    real_type t77  = X__[iX_sigma];
    real_type t78  = cos(t77);
    real_type t79  = t78 * t60;
    real_type t80  = t79 * t76;
    real_type t83  = t17 * t5;
    real_type t85  = 1.0 / t5;
    real_type t93  = MU__[5];
    real_type t94  = t2 * t93;
    real_type t95  = sin(t77);
    real_type t97  = 1.0 / t9;
    real_type t102 = tan(t18);
    real_type t103 = t102 * t12;
    result__[ 0   ] = -t20 * t17 * t12 * t7 - t17 * t28 * t27 * t26 + (2 * t38 * t36 + t61 * t56 * t48 * t46 * t44 / 2) * t4 * t33 + (-t80 * t71 / 2 + t9 * (2 * t85 * t38 * t35 - t83)) * t4 * t69 + (-t97 * t95 * t60 * t76 * t71 / 2 + t103 * t83) * t4 * t94;
    result__[ 1   ] = 0;
    real_type t108 = 1.0 / t15;
    real_type t109 = t19 * t19;
    real_type t112 = sin(t18);
    real_type t116 = t6 * t94;
    real_type t117 = t9 * t108;
    real_type t118 = t102 * t102;
    result__[ 2   ] = t112 / t109 * t108 * t12 * t7 - (1 + t118) * t11 * t117 * t116;
    real_type t123 = MU__[0];
    real_type t124 = t2 * t123;
    real_type t128 = t20 * t108;
    real_type t131 = t28 * t9;
    real_type t132 = t108 * t131;
    real_type t134 = t41 * t4;
    real_type t137 = t60 * t58 * t56;
    real_type t140 = t46 * t41;
    real_type t141 = t75 * t140;
    real_type t145 = t17 * t35;
    real_type t154 = t97 * t95 * t61;
    result__[ 3   ] = t34 * t4 * t124 + t128 * t12 * t4 * t3 + t132 * t26 - t137 * t70 * t134 * t33 + (t78 * t61 * t141 / 2 + t9 * (t108 + 1.0 / t48 * t145)) * t4 * t69 + (t154 * t141 / 2 - t102 * t11 * t117) * t4 * t94;
    real_type t162 = t8 / 2;
    real_type t163 = sin(t162);
    real_type t165 = cos(t162);
    real_type t169 = -0.314159265358979323846264338328e1 - t8;
    real_type t170 = ALIAS_G_bound_min_D(t169);
    real_type t172 = t8 - 0.314159265358979323846264338328e1;
    real_type t173 = ALIAS_G_bound_max_D(t172);
    real_type t175 = t9 * t6;
    real_type t177 = t11 * t34;
    real_type t188 = t108 * t5;
    real_type t190 = -t85 * t145 + t188;
    real_type t194 = t75 * t5;
    real_type t195 = t194 * t140;
    real_type t196 = t9 * t9;
    result__[ 4   ] = 1.0 / t165 * t163 * t2 / 2 - t170 * t2 + t173 * t2 + t175 * t124 - t128 * t177 * t7 - t108 * t28 * t34 * t5 * t26 - t17 * t35 * t9 * t4 * t33 - t34 * t190 * t4 * t69 + (t34 / t196 * t95 * t61 * t195 / 2 + t102 * t177 * t188) * t4 * t94;
    real_type t210 = t108 * t11;
    result__[ 5   ] = t102 * t28 * t117 * t116 - t128 * t131 * t7 + t210 * t27 * t26;
    real_type t216 = t46 * t134;
    result__[ 6   ] = t97 * t79 * t58 * t194 * t216 * t94 / 2 - t95 * t61 * t194 * t216 * t69 / 2;
    real_type t227 = log(t165);
    real_type t228 = U__[iU_c_h];
    real_type t229 = t228 * t228;
    real_type t230 = U__[iU_c_theta];
    real_type t231 = t230 * t230;
    real_type t232 = U__[iU_c_phi];
    real_type t233 = t232 * t232;
    real_type t234 = U__[iU_c_V];
    real_type t235 = t234 * t234;
    real_type t236 = U__[iU_c_G];
    real_type t237 = t236 * t236;
    real_type t238 = U__[iU_c_psi];
    real_type t239 = t238 * t238;
    real_type t240 = U__[iU_c_sigma];
    real_type t241 = t240 * t240;
    real_type t242 = U__[iU_u2];
    real_type t243 = u2Control(t242, -1, 1);
    real_type t244 = G_bound_min(t169);
    real_type t245 = G_bound_max(t172);
    real_type t247 = ModelPars[iM_CTRL];
    result__[ 7   ] = t51 - t227 + t229 + t231 + t233 + t235 + t237 + t239 + t241 + t243 + t244 + t245 + (t228 * t247 + t34 * t6) * t123 + (t20 * t210 * t175 + t230 * t247) * t1 + (t132 * t6 + t232 * t247) * t24 + ((-t17 * t36 - t137 * t48 * t140 / 2) * t4 + t234 * t247) * t32 + ((t80 * t5 * t140 / 2 + t9 * t190) * t4 + t236 * t247) * t68 + ((t154 * t195 / 2 - t103 * t188) * t4 + t238 * t247) * t93 + (t242 * ModelPars[iM_sigma_dot_max] * t4 + t240 * t247) * MU__[6];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 8, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DHxpDxpuv_numRows() const { return 8; }
  integer HypersonicProblem3DOF::DHxpDxpuv_numCols() const { return 24; }
  integer HypersonicProblem3DOF::DHxpDxpuv_nnz()     const { return 57; }

  void
  HypersonicProblem3DOF::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 7   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 2   ; jIndex[11] = 4   ;
    iIndex[12] = 2   ; jIndex[12] = 5   ;
    iIndex[13] = 2   ; jIndex[13] = 7   ;
    iIndex[14] = 3   ; jIndex[14] = 0   ;
    iIndex[15] = 3   ; jIndex[15] = 2   ;
    iIndex[16] = 3   ; jIndex[16] = 3   ;
    iIndex[17] = 3   ; jIndex[17] = 4   ;
    iIndex[18] = 3   ; jIndex[18] = 5   ;
    iIndex[19] = 3   ; jIndex[19] = 6   ;
    iIndex[20] = 3   ; jIndex[20] = 7   ;
    iIndex[21] = 3   ; jIndex[21] = 8   ;
    iIndex[22] = 4   ; jIndex[22] = 0   ;
    iIndex[23] = 4   ; jIndex[23] = 2   ;
    iIndex[24] = 4   ; jIndex[24] = 3   ;
    iIndex[25] = 4   ; jIndex[25] = 4   ;
    iIndex[26] = 4   ; jIndex[26] = 5   ;
    iIndex[27] = 4   ; jIndex[27] = 6   ;
    iIndex[28] = 4   ; jIndex[28] = 7   ;
    iIndex[29] = 4   ; jIndex[29] = 8   ;
    iIndex[30] = 5   ; jIndex[30] = 0   ;
    iIndex[31] = 5   ; jIndex[31] = 2   ;
    iIndex[32] = 5   ; jIndex[32] = 3   ;
    iIndex[33] = 5   ; jIndex[33] = 4   ;
    iIndex[34] = 5   ; jIndex[34] = 5   ;
    iIndex[35] = 5   ; jIndex[35] = 7   ;
    iIndex[36] = 6   ; jIndex[36] = 0   ;
    iIndex[37] = 6   ; jIndex[37] = 3   ;
    iIndex[38] = 6   ; jIndex[38] = 4   ;
    iIndex[39] = 6   ; jIndex[39] = 6   ;
    iIndex[40] = 6   ; jIndex[40] = 7   ;
    iIndex[41] = 6   ; jIndex[41] = 8   ;
    iIndex[42] = 7   ; jIndex[42] = 0   ;
    iIndex[43] = 7   ; jIndex[43] = 2   ;
    iIndex[44] = 7   ; jIndex[44] = 3   ;
    iIndex[45] = 7   ; jIndex[45] = 4   ;
    iIndex[46] = 7   ; jIndex[46] = 5   ;
    iIndex[47] = 7   ; jIndex[47] = 6   ;
    iIndex[48] = 7   ; jIndex[48] = 8   ;
    iIndex[49] = 7   ; jIndex[49] = 9   ;
    iIndex[50] = 7   ; jIndex[50] = 10  ;
    iIndex[51] = 7   ; jIndex[51] = 11  ;
    iIndex[52] = 7   ; jIndex[52] = 12  ;
    iIndex[53] = 7   ; jIndex[53] = 13  ;
    iIndex[54] = 7   ; jIndex[54] = 14  ;
    iIndex[55] = 7   ; jIndex[55] = 15  ;
    iIndex[56] = 7   ; jIndex[56] = 16  ;
  }


  void
  HypersonicProblem3DOF::DHxpDxpuv_sparse(
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
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = P__[iP_Tf];
    real_type t3   = t2 * t1;
    real_type t4   = ModelPars[iM_ODE];
    real_type t5   = X__[iX_V];
    real_type t6   = t5 * t4;
    real_type t7   = t6 * t3;
    real_type t8   = X__[iX_G];
    real_type t9   = cos(t8);
    real_type t10  = X__[iX_psi];
    real_type t11  = cos(t10);
    real_type t12  = t11 * t9;
    real_type t14  = X__[iX_h];
    real_type t15  = ModelPars[iM_re] + t14;
    real_type t16  = t15 * t15;
    real_type t18  = 1.0 / t16 / t15;
    real_type t19  = X__[iX_phi];
    real_type t20  = cos(t19);
    real_type t21  = 1.0 / t20;
    real_type t26  = MU__[2];
    real_type t28  = t4 * t2 * t26;
    real_type t29  = t9 * t5;
    real_type t30  = sin(t10);
    real_type t35  = MU__[3];
    real_type t36  = t2 * t35;
    real_type t37  = sin(t8);
    real_type t38  = ModelPars[iM_mu];
    real_type t39  = t38 * t37;
    real_type t40  = t16 * t16;
    real_type t41  = 1.0 / t40;
    real_type t44  = ModelPars[iM_rho0];
    real_type t45  = ModelPars[iM_S];
    real_type t46  = t45 * t45;
    real_type t48  = 1.0 / t46 * t44;
    real_type t49  = 1.0 / t45;
    real_type t51  = exp(-t49 * t14);
    real_type t53  = t5 * t5;
    real_type t54  = ModelPars[iM_CD2];
    real_type t55  = U__[iU_alpha];
    real_type t56  = t55 * t55;
    real_type t58  = ModelPars[iM_CD1];
    real_type t61  = t56 * t54 + t55 * t58 + ModelPars[iM_CD0];
    real_type t63  = ModelPars[iM_Aref];
    real_type t65  = 1.0 / ModelPars[iM_m];
    real_type t66  = t65 * t63;
    real_type t67  = t66 * t61 * t53;
    real_type t73  = MU__[4];
    real_type t74  = t2 * t73;
    real_type t75  = t5 * t51;
    real_type t76  = t75 * t48;
    real_type t77  = ModelPars[iM_CL1];
    real_type t80  = t55 * t77 + ModelPars[iM_CL0];
    real_type t81  = t63 * t80;
    real_type t82  = X__[iX_sigma];
    real_type t83  = cos(t82);
    real_type t84  = t83 * t65;
    real_type t85  = t84 * t81;
    real_type t88  = t18 * t5;
    real_type t91  = 1.0 / t5;
    real_type t99  = MU__[5];
    real_type t100 = t2 * t99;
    real_type t101 = sin(t82);
    real_type t102 = t101 * t65;
    real_type t103 = 1.0 / t9;
    real_type t104 = t103 * t102;
    real_type t105 = t104 * t81;
    real_type t108 = tan(t19);
    real_type t109 = t108 * t12;
    result__[ 0   ] = 2 * t21 * t18 * t12 * t7 + 2 * t18 * t30 * t29 * t28 + (-6 * t41 * t39 - t67 * t51 * t48 / 2) * t4 * t36 + (t85 * t76 / 2 + t9 * (-6 * t91 * t41 * t38 + 2 * t88)) * t4 * t74 + (t105 * t76 / 2 - 2 * t109 * t88) * t4 * t100;
    real_type t115 = 1.0 / t16;
    real_type t116 = t20 * t20;
    real_type t117 = 1.0 / t116;
    real_type t119 = sin(t19);
    real_type t123 = t6 * t100;
    real_type t124 = t9 * t115;
    real_type t125 = t108 * t108;
    real_type t126 = 1 + t125;
    real_type t127 = t126 * t11;
    result__[ 1   ] = -t119 * t117 * t115 * t12 * t7 + t127 * t124 * t123;
    real_type t130 = t4 * t3;
    real_type t131 = t21 * t115;
    real_type t132 = t131 * t12;
    real_type t134 = t30 * t9;
    real_type t135 = t115 * t134;
    real_type t137 = t44 * t4;
    real_type t138 = t49 * t137;
    real_type t139 = t138 * t36;
    real_type t144 = t49 * t44;
    real_type t145 = t51 * t144;
    real_type t148 = t18 * t38;
    real_type t149 = 1.0 / t53;
    real_type t157 = t80 * t51;
    real_type t160 = t103 * t101 * t66;
    real_type t163 = t108 * t11;
    result__[ 2   ] = -t132 * t130 - t135 * t28 + t65 * t63 * t61 * t75 * t139 + (-t85 * t145 / 2 + t9 * (-2 * t149 * t148 - t115)) * t4 * t74 + (-t160 * t157 * t144 / 2 + t163 * t124) * t4 * t100;
    real_type t168 = t11 * t37;
    real_type t171 = t37 * t5;
    real_type t175 = t4 * t36;
    real_type t176 = t38 * t9;
    real_type t180 = t115 * t5;
    real_type t183 = 2 * t91 * t148 - t180;
    real_type t187 = t80 * t75;
    real_type t189 = t9 * t9;
    real_type t190 = 1.0 / t189;
    real_type t192 = t37 * t190 * t101;
    real_type t193 = t192 * t66;
    real_type t196 = t108 * t168;
    result__[ 3   ] = t131 * t168 * t7 + t115 * t30 * t171 * t28 + 2 * t18 * t176 * t175 - t37 * t183 * t4 * t74 + (-t193 * t187 * t144 / 2 - t196 * t180) * t4 * t100;
    real_type t206 = t108 * t30;
    result__[ 4   ] = -t115 * t11 * t29 * t28 - t206 * t124 * t123 + t131 * t134 * t7;
    real_type t209 = t138 * t74;
    real_type t210 = t101 * t66;
    real_type t213 = t4 * t100;
    real_type t214 = t145 * t213;
    real_type t215 = t80 * t5;
    real_type t216 = t63 * t215;
    real_type t217 = t103 * t84;
    result__[ 5   ] = t210 * t187 * t209 / 2 - t217 * t216 * t214 / 2;
    real_type t221 = t4 * t1;
    real_type t222 = t5 * t221;
    real_type t224 = t4 * t26;
    real_type t225 = t5 * t224;
    real_type t227 = t4 * t35;
    real_type t234 = t4 * t73;
    real_type t235 = t75 * t144;
    real_type t241 = t4 * t99;
    result__[ 6   ] = -t132 * t222 - t135 * t225 + (2 * t18 * t39 + t67 * t145 / 2) * t227 + (-t85 * t235 / 2 + t9 * t183) * t234 + (-t105 * t235 / 2 + t109 * t180) * t241;
    real_type t250 = 2 * t55 * t54 + t58;
    real_type t252 = t65 * t63 * t250;
    real_type t256 = t83 * t66;
    real_type t259 = t77 * t5;
    real_type t260 = t63 * t259;
    result__[ 7   ] = t252 * t53 * t51 * t139 / 2 - t256 * t77 * t75 * t209 / 2 - t104 * t260 * t214 / 2;
    result__[ 8   ] = result__[1];
    real_type t264 = 1.0 / t15;
    real_type t268 = t119 * t119;
    real_type t273 = t21 * t264;
    real_type t275 = t273 * t12 * t7;
    real_type t276 = t9 * t264;
    result__[ 9   ] = 2 * t268 / t116 / t20 * t264 * t12 * t7 + t275 - 2 * t126 * t163 * t276 * t123;
    real_type t281 = t9 * t4;
    real_type t283 = t264 * t11;
    real_type t285 = t119 * t117 * t283;
    real_type t287 = t127 * t276;
    result__[ 10  ] = t285 * t281 * t3 - t287 * t213;
    real_type t290 = t119 * t117 * t264;
    real_type t293 = t37 * t264;
    result__[ 11  ] = t127 * t293 * t123 - t290 * t168 * t7;
    result__[ 12  ] = t126 * t30 * t276 * t123 - t290 * t134 * t7;
    real_type t303 = t5 * t241;
    result__[ 13  ] = t285 * t29 * t221 - t287 * t303;
    result__[ 14  ] = result__[2];
    result__[ 15  ] = result__[10];
    real_type t305 = t137 * t36;
    real_type t310 = t115 * t38;
    result__[ 16  ] = -t66 * t61 * t51 * t305 - 2 * t9 / t53 / t5 * t310 * t4 * t74;
    real_type t317 = MU__[0];
    real_type t318 = t2 * t317;
    real_type t320 = t273 * t168;
    real_type t322 = t30 * t37;
    real_type t323 = t264 * t322;
    real_type t326 = t149 * t310 + t264;
    real_type t330 = t51 * t44;
    result__[ 17  ] = t281 * t318 - t320 * t130 - t323 * t28 - t37 * t326 * t4 * t74 + (t37 * t190 * t102 * t81 * t330 / 2 + t163 * t293) * t4 * t100;
    real_type t340 = t273 * t134;
    real_type t342 = t264 * t12;
    real_type t344 = t206 * t276;
    result__[ 18  ] = -t340 * t130 + t344 * t213 + t342 * t28;
    real_type t346 = t137 * t74;
    real_type t349 = t51 * t137;
    real_type t350 = t349 * t100;
    real_type t351 = t217 * t81;
    result__[ 19  ] = -t210 * t157 * t346 / 2 + t351 * t350 / 2;
    real_type t354 = t4 * t317;
    real_type t361 = t330 * t227;
    real_type t365 = t80 * t330;
    real_type t373 = t163 * t276;
    result__[ 20  ] = t37 * t354 + t21 * t283 * t9 * t221 + t264 * t134 * t224 - t66 * t61 * t5 * t361 + (t256 * t365 / 2 + t9 * t326) * t234 + (t160 * t365 / 2 - t373) * t241;
    real_type t382 = t63 * t77;
    real_type t383 = t104 * t382;
    result__[ 21  ] = -t252 * t75 * t305 + t256 * t77 * t51 * t346 / 2 + t383 * t350 / 2;
    result__[ 22  ] = result__[3];
    result__[ 23  ] = result__[11];
    result__[ 24  ] = result__[17];
    real_type t387 = t8 / 2;
    real_type t388 = sin(t387);
    real_type t389 = t388 * t388;
    real_type t391 = cos(t387);
    real_type t392 = t391 * t391;
    real_type t396 = -0.314159265358979323846264338328e1 - t8;
    real_type t397 = ALIAS_G_bound_min_DD(t396);
    real_type t399 = t8 - 0.314159265358979323846264338328e1;
    real_type t400 = ALIAS_G_bound_max_DD(t399);
    real_type t406 = t264 * t30 * t29 * t28;
    real_type t409 = t264 * t5;
    real_type t411 = -t91 * t310 + t409;
    real_type t415 = t215 * t330;
    real_type t419 = t37 * t37;
    result__[ 25  ] = t2 / 4 + 1.0 / t392 * t389 * t2 / 4 + t397 * t2 + t400 * t2 - t37 * t6 * t318 - t275 - t406 + t115 * t39 * t175 - t9 * t411 * t4 * t74 + (t419 / t189 / t9 * t101 * t66 * t415 + t160 * t415 / 2 + t109 * t409) * t4 * t100;
    result__[ 26  ] = -t206 * t293 * t123 - t283 * t171 * t28 + t273 * t322 * t7;
    real_type t435 = t5 * t330;
    real_type t436 = t435 * t213;
    result__[ 27  ] = t37 * t190 * t83 * t65 * t81 * t436 / 2;
    real_type t445 = ALIAS_G_bound_min_D(t396);
    real_type t446 = ALIAS_G_bound_max_D(t399);
    result__[ 28  ] = 1.0 / t391 * t388 / 2 - t445 + t446 + t29 * t354 - t320 * t222 - t323 * t225 - t115 * t176 * t227 - t37 * t411 * t234 + (t193 * t415 / 2 + t196 * t409) * t241;
    result__[ 29  ] = t192 * t65 * t382 * t436 / 2;
    result__[ 30  ] = result__[4];
    result__[ 31  ] = result__[12];
    result__[ 32  ] = result__[18];
    result__[ 33  ] = result__[26];
    result__[ 34  ] = t373 * t123 - t275 - t406;
    result__[ 35  ] = -t340 * t222 + t342 * t225 + t344 * t303;
    result__[ 36  ] = result__[5];
    result__[ 37  ] = result__[19];
    result__[ 38  ] = result__[27];
    real_type t466 = t349 * t74;
    result__[ 39  ] = -t104 * t216 * t350 / 2 - t256 * t215 * t466 / 2;
    real_type t472 = t330 * t234;
    real_type t475 = t435 * t241;
    result__[ 40  ] = -t210 * t215 * t472 / 2 + t351 * t475 / 2;
    result__[ 41  ] = -t210 * t259 * t466 / 2 + t217 * t260 * t350 / 2;
    result__[ 42  ] = result__[6];
    result__[ 43  ] = result__[13];
    result__[ 44  ] = result__[20];
    result__[ 45  ] = result__[28];
    result__[ 46  ] = result__[35];
    result__[ 47  ] = result__[40];
    result__[ 48  ] = 2 * t55 - t66 * t250 * t53 * t361 / 2 + t256 * t259 * t472 / 2 + t383 * t475 / 2;
    real_type t494 = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    real_type t495 = MU__[6];
    result__[ 49  ] = ModelPars[iM_sigma_dot_max] * t4 * t495 + t494;
    real_type t499 = ModelPars[iM_CTRL];
    result__[ 50  ] = t499 * t317 + 2 * U__[iU_c_h];
    result__[ 51  ] = t499 * t1 + 2 * U__[iU_c_theta];
    result__[ 52  ] = t499 * t26 + 2 * U__[iU_c_phi];
    result__[ 53  ] = t499 * t35 + 2 * U__[iU_c_V];
    result__[ 54  ] = t499 * t73 + 2 * U__[iU_c_G];
    result__[ 55  ] = t499 * t99 + 2 * U__[iU_c_psi];
    result__[ 56  ] = t499 * t495 + 2 * U__[iU_c_sigma];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 57, i_segment );
  }

}

// EOF: HypersonicProblem3DOF_Methods_AdjointODE.cc
