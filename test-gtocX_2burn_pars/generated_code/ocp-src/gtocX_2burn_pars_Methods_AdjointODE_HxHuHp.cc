/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_AdjointODE.cc                         |
 |                                                                       |
 |  version: 1.0   date 4/6/2022                                         |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::Hxp_numEqns() const { return 6; }

  void
  gtocX_2burn_pars::Hxp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t3   = X__[iX_f];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = f_guess(t10);
    real_type t16  = t8 - t6;
    real_type t17  = t16 * L__[iL_lambda1__xo];
    real_type t18  = P__[iP_p];
    real_type t19  = sqrt(t18);
    real_type t20  = ModelPars[iM_muS];
    real_type t21  = sqrt(t20);
    real_type t22  = 1.0 / t21;
    real_type t23  = t22 * t19;
    real_type t24  = t23 * t17;
    real_type t25  = ModelPars[iM_w_nonlin];
    real_type t26  = X__[iX_g];
    real_type t27  = X__[iX_L];
    real_type t28  = ray(t18, t3, t26, t27);
    real_type t29  = acceleration_r_D_1(t28, t20);
    real_type t30  = t29 * t25;
    real_type t31  = ray_D_2(t18, t3, t26, t27);
    real_type t32  = sin(t27);
    real_type t37  = t16 * L__[iL_lambda2__xo];
    real_type t38  = t23 * t37;
    real_type t39  = cos(t27);
    real_type t44  = t16 * L__[iL_lambda3__xo];
    real_type t47  = t32 * t26 + t39 * t3 + 1;
    real_type t48  = t47 * t44;
    real_type t51  = t21 / t19 / t18;
    result__[ 0   ] = (2 * t3 - 2 * t11) * t2 + t32 * t31 * t30 * t24 - t39 * t31 * t30 * t38 + 2 * t39 * t51 * t48;
    real_type t55  = g_guess(t10);
    real_type t59  = ray_D_3(t18, t3, t26, t27);
    result__[ 1   ] = (2 * t26 - 2 * t55) * t2 + t32 * t59 * t30 * t24 - t39 * t59 * t30 * t38 + 2 * t32 * t51 * t48;
    real_type t69  = L_guess(t10, t6);
    real_type t73  = ray_D_4(t18, t3, t26, t27);
    real_type t78  = t25 * t22;
    real_type t79  = acceleration_r(t28, t20);
    real_type t81  = t39 * t79 * t78;
    real_type t88  = t32 * t79 * t78;
    result__[ 2   ] = (2 * t27 - 2 * t69) * t2 + t32 * t73 * t30 * t24 + t81 * t19 * t17 - t39 * t73 * t30 * t38 + t88 * t19 * t37 + 2 * (t39 * t26 - t32 * t3) * t51 * t48;
    real_type t96  = p_guess(0);
    real_type t97  = 1.0 / t96;
    real_type t103 = 1.0 / t19;
    real_type t107 = ray_D_1(t18, t3, t26, t27);
    real_type t117 = t47 * t47;
    real_type t118 = t18 * t18;
    result__[ 3   ] = 2 * t97 * (t97 * t18 - 1) * t2 + t88 * t103 * t17 / 2 + t32 * t107 * t30 * t24 - t81 * t103 * t37 / 2 - t39 * t107 * t30 * t38 - 3.0 / 2.0 * t21 / t19 / t118 * t117 * t44;
    real_type t126 = h_guess(0);
    result__[ 4   ] = (2 * P__[iP_h] - 2 * t126) * t2;
    real_type t130 = k_guess(0);
    result__[ 5   ] = (2 * P__[iP_k] - 2 * t130) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 6, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DHxpDxpu_numRows() const { return 6; }
  integer gtocX_2burn_pars::DHxpDxpu_numCols() const { return 6; }
  integer gtocX_2burn_pars::DHxpDxpu_nnz()     const { return 18; }

  void
  gtocX_2burn_pars::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  gtocX_2burn_pars::DHxpDxpu_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_w_guess];
    real_type t2   = 2 * t1;
    real_type t6   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t7   = t6 * L__[iL_lambda1__xo];
    real_type t8   = P__[iP_p];
    real_type t9   = sqrt(t8);
    real_type t10  = ModelPars[iM_muS];
    real_type t11  = sqrt(t10);
    real_type t12  = 1.0 / t11;
    real_type t13  = t12 * t9;
    real_type t14  = t13 * t7;
    real_type t15  = ModelPars[iM_w_nonlin];
    real_type t16  = X__[iX_f];
    real_type t17  = X__[iX_g];
    real_type t18  = X__[iX_L];
    real_type t19  = ray(t8, t16, t17, t18);
    real_type t20  = acceleration_r_D_1_1(t19, t10);
    real_type t21  = t20 * t15;
    real_type t22  = ray_D_2(t8, t16, t17, t18);
    real_type t23  = t22 * t22;
    real_type t24  = sin(t18);
    real_type t28  = acceleration_r_D_1(t19, t10);
    real_type t29  = t28 * t15;
    real_type t30  = ray_D_2_2(t8, t16, t17, t18);
    real_type t35  = t6 * L__[iL_lambda2__xo];
    real_type t36  = t13 * t35;
    real_type t37  = cos(t18);
    real_type t45  = t6 * L__[iL_lambda3__xo];
    real_type t46  = t37 * t37;
    real_type t48  = 1.0 / t9 / t8;
    result__[ 0   ] = 2 * t11 * t48 * t46 * t45 + t24 * t23 * t21 * t14 + t24 * t30 * t29 * t14 - t37 * t23 * t21 * t36 - t37 * t30 * t29 * t36 - t2 + 2;
    real_type t53  = ray_D_3(t8, t16, t17, t18);
    real_type t54  = t22 * t53;
    real_type t58  = ray_D_2_3(t8, t16, t17, t18);
    real_type t69  = t11 * t48;
    real_type t70  = t37 * t69;
    result__[ 1   ] = t24 * t54 * t21 * t14 + t24 * t58 * t29 * t14 - t37 * t54 * t21 * t36 - t37 * t58 * t29 * t36 + 2 * t70 * t24 * t45;
    real_type t73  = ray_D_4(t8, t16, t17, t18);
    real_type t74  = t22 * t73;
    real_type t78  = ray_D_2_4(t8, t16, t17, t18);
    real_type t83  = t37 * t22 * t29;
    real_type t92  = t24 * t22 * t29;
    real_type t96  = -t24 * t16 + t37 * t17;
    real_type t97  = t96 * t45;
    real_type t100 = t37 * t16;
    real_type t101 = t24 * t17;
    real_type t102 = 1 + t100 + t101;
    real_type t103 = t102 * t45;
    real_type t104 = t24 * t69;
    result__[ 2   ] = t24 * t74 * t21 * t14 + t24 * t78 * t29 * t14 - t37 * t74 * t21 * t36 - t37 * t78 * t29 * t36 - 2 * t104 * t103 + t83 * t14 + t92 * t36 + 2 * t70 * t97;
    real_type t107 = 1.0 / t9;
    real_type t108 = t12 * t107;
    real_type t109 = t108 * t7;
    real_type t112 = ray_D_1(t8, t16, t17, t18);
    real_type t113 = t22 * t112;
    real_type t117 = ray_D_1_2(t8, t16, t17, t18);
    real_type t121 = t108 * t35;
    real_type t130 = t8 * t8;
    real_type t133 = t11 / t9 / t130;
    result__[ 3   ] = t92 * t109 / 2 + t24 * t113 * t21 * t14 + t24 * t117 * t29 * t14 - t83 * t121 / 2 - t37 * t113 * t21 * t36 - t37 * t117 * t29 * t36 - 3 * t37 * t133 * t103;
    result__[ 4   ] = result__[1];
    real_type t137 = t53 * t53;
    real_type t141 = ray_D_3_3(t8, t16, t17, t18);
    real_type t151 = t24 * t24;
    result__[ 5   ] = 2 * t11 * t48 * t151 * t45 + t24 * t137 * t21 * t14 - t37 * t137 * t21 * t36 + t24 * t141 * t29 * t14 - t37 * t141 * t29 * t36 - t2 + 2;
    real_type t156 = t53 * t73;
    real_type t160 = ray_D_3_4(t8, t16, t17, t18);
    real_type t165 = t37 * t53 * t29;
    real_type t174 = t24 * t53 * t29;
    result__[ 6   ] = t24 * t156 * t21 * t14 + t24 * t160 * t29 * t14 - t37 * t156 * t21 * t36 - t37 * t160 * t29 * t36 + 2 * t70 * t103 + 2 * t104 * t97 + t165 * t14 + t174 * t36;
    real_type t182 = t53 * t112;
    real_type t186 = ray_D_1_3(t8, t16, t17, t18);
    result__[ 7   ] = t174 * t109 / 2 + t24 * t182 * t21 * t14 + t24 * t186 * t29 * t14 - t165 * t121 / 2 - t37 * t182 * t21 * t36 - t37 * t186 * t29 * t36 - 3 * t24 * t133 * t103;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t201 = t73 * t73;
    real_type t205 = ray_D_4_4(t8, t16, t17, t18);
    real_type t210 = t37 * t73 * t29;
    real_type t214 = t15 * t12;
    real_type t215 = acceleration_r(t19, t10);
    real_type t217 = t24 * t215 * t214;
    real_type t226 = t24 * t73 * t29;
    real_type t231 = t37 * t215 * t214;
    real_type t233 = t96 * t96;
    result__[ 10  ] = 2 - t2 + t24 * t201 * t21 * t14 + t24 * t205 * t29 * t14 + 2 * t210 * t14 - t217 * t9 * t7 - t37 * t201 * t21 * t36 - t37 * t205 * t29 * t36 + 2 * t226 * t36 + t231 * t9 * t35 + 2 * t11 * t48 * t233 * t45 + 2 * (-t100 - t101) * t69 * t103;
    real_type t244 = t73 * t112;
    real_type t248 = ray_D_1_4(t8, t16, t17, t18);
    real_type t256 = t37 * t112 * t29;
    real_type t270 = t24 * t112 * t29;
    result__[ 11  ] = t226 * t109 / 2 + t24 * t244 * t21 * t14 + t24 * t248 * t29 * t14 + t231 * t107 * t7 / 2 + t256 * t14 - t210 * t121 / 2 - t37 * t244 * t21 * t36 - t37 * t248 * t29 * t36 + t217 * t107 * t35 / 2 + t270 * t36 - 3 * t96 * t133 * t103;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    real_type t275 = 1 - t1;
    real_type t276 = p_guess(0);
    real_type t277 = t276 * t276;
    real_type t285 = t112 * t112;
    real_type t289 = ray_D_1_1(t8, t16, t17, t18);
    real_type t303 = t102 * t102;
    result__[ 15  ] = 2 / t277 * t275 - t217 * t48 * t7 / 4 + t270 * t109 + t24 * t285 * t21 * t14 + t24 * t289 * t29 * t14 + t231 * t48 * t35 / 4 - t256 * t121 - t37 * t285 * t21 * t36 - t37 * t289 * t29 * t36 + 0.15e2 / 4.0 * t11 / t9 / t130 / t8 * t303 * t45;
    result__[ 16  ] = 2 * t275;
    result__[ 17  ] = result__[16];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 18, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::Hu_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_pars_Methods_AdjointODE.cc
