/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_AdjointODE.cc                              |
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
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::Hxp_numEqns() const { return 6; }

  void
  gtocX_2burn::Hxp_eval(
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
    real_type t3   = X__[iX_p];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = p_guess(t10);
    real_type t12  = 1.0 / t11;
    real_type t19  = t8 - t6;
    real_type t20  = t19 * L__[iL_lambda2__xo];
    real_type t21  = sqrt(t3);
    real_type t22  = 1.0 / t21;
    real_type t24  = ModelPars[iM_muS];
    real_type t25  = sqrt(t24);
    real_type t26  = 1.0 / t25;
    real_type t27  = ModelPars[iM_w_nonlin];
    real_type t28  = t27 * t26;
    real_type t29  = X__[iX_f];
    real_type t30  = X__[iX_g];
    real_type t31  = X__[iX_L];
    real_type t32  = ray(t3, t29, t30, t31);
    real_type t33  = acceleration_r(t32, t24);
    real_type t34  = sin(t31);
    real_type t36  = t34 * t33 * t28;
    real_type t39  = t26 * t21;
    real_type t40  = t39 * t20;
    real_type t41  = acceleration_r_D_1(t32, t24);
    real_type t42  = t41 * t27;
    real_type t43  = ray_D_1(t3, t29, t30, t31);
    real_type t48  = t19 * L__[iL_lambda3__xo];
    real_type t50  = cos(t31);
    real_type t52  = t50 * t33 * t28;
    real_type t55  = t39 * t48;
    real_type t60  = t19 * L__[iL_lambda6__xo];
    real_type t63  = t50 * t29 + t34 * t30 + 1;
    real_type t64  = t63 * t63;
    real_type t65  = t3 * t3;
    result__[ 0   ] = 2 * t12 * (t12 * t3 - 1) * t2 + t36 * t22 * t20 / 2 + t34 * t43 * t42 * t40 - t52 * t22 * t48 / 2 - t50 * t43 * t42 * t55 - 3.0 / 2.0 * t25 / t21 / t65 * t64 * t60;
    real_type t72  = f_guess(t10);
    real_type t76  = ray_D_2(t3, t29, t30, t31);
    real_type t83  = t63 * t60;
    real_type t86  = t25 / t21 / t3;
    result__[ 1   ] = (2 * t29 - 2 * t72) * t2 + t34 * t76 * t42 * t40 - t50 * t76 * t42 * t55 + 2 * t50 * t86 * t83;
    real_type t90  = g_guess(t10);
    real_type t94  = ray_D_3(t3, t29, t30, t31);
    result__[ 2   ] = (2 * t30 - 2 * t90) * t2 + t34 * t94 * t42 * t40 - t50 * t94 * t42 * t55 + 2 * t34 * t86 * t83;
    real_type t105 = h_guess(t10);
    result__[ 3   ] = (2 * X__[iX_h] - 2 * t105) * t2;
    real_type t109 = k_guess(t10);
    result__[ 4   ] = (2 * X__[iX_k] - 2 * t109) * t2;
    real_type t112 = L_guess(t10, t6);
    real_type t116 = ray_D_4(t3, t29, t30, t31);
    result__[ 5   ] = (2 * t31 - 2 * t112) * t2 + t34 * t116 * t42 * t40 + t52 * t21 * t20 - t50 * t116 * t42 * t55 + t36 * t21 * t48 + 2 * (-t34 * t29 + t50 * t30) * t86 * t83;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 6, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DHxpDxpu_numRows() const { return 6; }
  integer gtocX_2burn::DHxpDxpu_numCols() const { return 6; }
  integer gtocX_2burn::DHxpDxpu_nnz()     const { return 18; }

  void
  gtocX_2burn::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  gtocX_2burn::DHxpDxpu_sparse(
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
    real_type t2   = 1 - t1;
    real_type t3   = Q__[iQ_zeta];
    real_type t5   = ModelPars[iM_time_i];
    real_type t7   = ModelPars[iM_time_f];
    real_type t10  = p_guess(t5 * (1 - t3) + t7 * t3);
    real_type t11  = t10 * t10;
    real_type t16  = t7 - t5;
    real_type t17  = t16 * L__[iL_lambda2__xo];
    real_type t18  = X__[iX_p];
    real_type t19  = sqrt(t18);
    real_type t21  = 1.0 / t19 / t18;
    real_type t23  = ModelPars[iM_muS];
    real_type t24  = sqrt(t23);
    real_type t25  = 1.0 / t24;
    real_type t26  = ModelPars[iM_w_nonlin];
    real_type t27  = t26 * t25;
    real_type t28  = X__[iX_f];
    real_type t29  = X__[iX_g];
    real_type t30  = X__[iX_L];
    real_type t31  = ray(t18, t28, t29, t30);
    real_type t32  = acceleration_r(t31, t23);
    real_type t33  = sin(t30);
    real_type t35  = t33 * t32 * t27;
    real_type t38  = 1.0 / t19;
    real_type t39  = t25 * t38;
    real_type t40  = t39 * t17;
    real_type t41  = acceleration_r_D_1(t31, t23);
    real_type t42  = t41 * t26;
    real_type t43  = ray_D_1(t18, t28, t29, t30);
    real_type t45  = t33 * t43 * t42;
    real_type t47  = t25 * t19;
    real_type t48  = t47 * t17;
    real_type t49  = acceleration_r_D_1_1(t31, t23);
    real_type t50  = t49 * t26;
    real_type t51  = t43 * t43;
    real_type t55  = ray_D_1_1(t18, t28, t29, t30);
    real_type t60  = t16 * L__[iL_lambda3__xo];
    real_type t62  = cos(t30);
    real_type t64  = t62 * t32 * t27;
    real_type t67  = t39 * t60;
    real_type t69  = t62 * t43 * t42;
    real_type t71  = t47 * t60;
    real_type t79  = t16 * L__[iL_lambda6__xo];
    real_type t80  = t62 * t28;
    real_type t81  = t33 * t29;
    real_type t82  = 1 + t80 + t81;
    real_type t83  = t82 * t82;
    real_type t84  = t18 * t18;
    result__[ 0   ] = 2 / t11 * t2 - t35 * t21 * t17 / 4 + t45 * t40 + t33 * t51 * t50 * t48 + t33 * t55 * t42 * t48 + t64 * t21 * t60 / 4 - t69 * t67 - t62 * t51 * t50 * t71 - t62 * t55 * t42 * t71 + 0.15e2 / 4.0 * t24 / t19 / t84 / t18 * t83 * t79;
    real_type t92  = ray_D_2(t18, t28, t29, t30);
    real_type t94  = t33 * t92 * t42;
    real_type t97  = t43 * t92;
    real_type t101 = ray_D_1_2(t18, t28, t29, t30);
    real_type t106 = t62 * t92 * t42;
    real_type t115 = t82 * t79;
    real_type t118 = t24 / t19 / t84;
    result__[ 1   ] = t94 * t40 / 2 + t33 * t97 * t50 * t48 + t33 * t101 * t42 * t48 - t106 * t67 / 2 - t62 * t97 * t50 * t71 - t62 * t101 * t42 * t71 - 3 * t62 * t118 * t115;
    real_type t122 = ray_D_3(t18, t28, t29, t30);
    real_type t124 = t33 * t122 * t42;
    real_type t127 = t43 * t122;
    real_type t131 = ray_D_1_3(t18, t28, t29, t30);
    real_type t136 = t62 * t122 * t42;
    result__[ 2   ] = t124 * t40 / 2 + t33 * t127 * t50 * t48 + t33 * t131 * t42 * t48 - t136 * t67 / 2 - t62 * t127 * t50 * t71 - t62 * t131 * t42 * t71 - 3 * t33 * t118 * t115;
    real_type t148 = ray_D_4(t18, t28, t29, t30);
    real_type t150 = t33 * t148 * t42;
    real_type t156 = t43 * t148;
    real_type t160 = ray_D_1_4(t18, t28, t29, t30);
    real_type t166 = t62 * t148 * t42;
    real_type t181 = -t33 * t28 + t62 * t29;
    result__[ 3   ] = t150 * t40 / 2 + t64 * t38 * t17 / 2 + t33 * t156 * t50 * t48 + t33 * t160 * t42 * t48 + t69 * t48 - t166 * t67 / 2 + t35 * t38 * t60 / 2 - t62 * t156 * t50 * t71 - t62 * t160 * t42 * t71 + t45 * t71 - 3 * t181 * t118 * t115;
    result__[ 4   ] = result__[1];
    real_type t185 = 2 * t1;
    real_type t186 = t92 * t92;
    real_type t190 = ray_D_2_2(t18, t28, t29, t30);
    real_type t200 = t62 * t62;
    result__[ 5   ] = t33 * t186 * t50 * t48 - t62 * t186 * t50 * t71 + t33 * t190 * t42 * t48 - t62 * t190 * t42 * t71 + 2 * t24 * t21 * t200 * t79 - t185 + 2;
    real_type t205 = t92 * t122;
    real_type t209 = ray_D_2_3(t18, t28, t29, t30);
    real_type t220 = t24 * t21;
    real_type t221 = t62 * t220;
    result__[ 6   ] = t33 * t205 * t50 * t48 - t62 * t205 * t50 * t71 + t33 * t209 * t42 * t48 - t62 * t209 * t42 * t71 + 2 * t221 * t33 * t79;
    real_type t224 = t92 * t148;
    real_type t228 = ray_D_2_4(t18, t28, t29, t30);
    real_type t240 = t181 * t79;
    real_type t243 = t33 * t220;
    result__[ 7   ] = t33 * t224 * t50 * t48 - t62 * t224 * t50 * t71 + t33 * t228 * t42 * t48 - t62 * t228 * t42 * t71 + t106 * t48 - 2 * t243 * t115 + 2 * t221 * t240 + t94 * t71;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t246 = t122 * t122;
    real_type t250 = ray_D_3_3(t18, t28, t29, t30);
    real_type t260 = t33 * t33;
    result__[ 10  ] = 2 * t24 * t21 * t260 * t79 + t33 * t246 * t50 * t48 - t62 * t246 * t50 * t71 + t33 * t250 * t42 * t48 - t62 * t250 * t42 * t71 - t185 + 2;
    real_type t265 = t122 * t148;
    real_type t269 = ray_D_3_4(t18, t28, t29, t30);
    result__[ 11  ] = t33 * t265 * t50 * t48 - t62 * t265 * t50 * t71 + t33 * t269 * t42 * t48 - t62 * t269 * t42 * t71 + 2 * t221 * t115 + t124 * t71 + t136 * t48 + 2 * t243 * t240;
    result__[ 12  ] = 2 * t2;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[3];
    result__[ 15  ] = result__[7];
    result__[ 16  ] = result__[11];
    real_type t285 = t148 * t148;
    real_type t289 = ray_D_4_4(t18, t28, t29, t30);
    real_type t307 = t181 * t181;
    result__[ 17  ] = 2 - t185 + t33 * t285 * t50 * t48 + t33 * t289 * t42 * t48 + 2 * t166 * t48 - t35 * t19 * t17 - t62 * t285 * t50 * t71 - t62 * t289 * t42 * t71 + 2 * t150 * t71 + t64 * t19 * t60 + 2 * t24 * t21 * t307 * t79 + 2 * (-t80 - t81) * t220 * t115;
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

  integer gtocX_2burn::Hu_numEqns() const { return 0; }

  void
  gtocX_2burn::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods_AdjointODE.cc
