/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_AdjointODE.cc                               |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::Hxp_numEqns() const { return 5; }

  void
  HangGlider::Hxp_eval(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t14  = U__[iU_cL];
    real_type t15  = t14 * t14;
    real_type t18  = t15 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t19  = Dfun(t7, t8, t9);
    real_type t20  = t19 * t18;
    real_type t22  = Lfun(t7, t8, t9);
    real_type t23  = t22 * t14;
    real_type t24  = w(t7, t9);
    real_type t26  = -t8 * t20 - t23 * t24;
    real_type t27  = t26 * t12;
    real_type t28  = v_D_1(t7, t8, t9);
    real_type t31  = 1.0 / t10;
    real_type t32  = t31 * t5;
    real_type t33  = Dfun_D_1(t7, t8, t9);
    real_type t34  = t33 * t18;
    real_type t36  = Lfun_D_1(t7, t8, t9);
    real_type t37  = t36 * t14;
    real_type t39  = w_D_1(t7, t9);
    real_type t44  = L__[iL_lambda4__xo];
    real_type t45  = t5 * t2;
    real_type t48  = -t24 * t20 + t8 * t23;
    real_type t49  = t48 * t12;
    result__[ 0   ] = -t28 * t27 * t6 + (-t39 * t23 - t24 * t37 - t8 * t34) * t32 * t3 + (-t28 * t49 * t45 + (-t39 * t20 - t24 * t34 + t8 * t37) * t31 * t45) * t44;
    result__[ 1   ] = 0;
    real_type t60  = L__[iL_lambda1__xo];
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t66  = t65 * t18;
    real_type t68  = Lfun_D_2(t7, t8, t9);
    real_type t69  = t68 * t14;
    result__[ 2   ] = t2 * t60 - t62 * t27 * t6 + (-t24 * t69 - t8 * t66 - t20) * t32 * t3 + (-t62 * t49 * t45 + (-t24 * t66 + t8 * t69 + t23) * t31 * t45) * t44;
    real_type t83  = L__[iL_lambda2__xo];
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t89  = t88 * t18;
    real_type t91  = Lfun_D_3(t7, t8, t9);
    real_type t92  = t91 * t14;
    real_type t94  = w_D_2(t7, t9);
    result__[ 3   ] = t2 * t83 - t85 * t27 * t6 + (-t94 * t23 - t24 * t92 - t8 * t89) * t32 * t3 + (-t85 * t49 * t45 + (-t94 * t20 - t24 * t89 + t8 * t92) * t31 * t45) * t44;
    result__[ 4   ] = t8 * t60 + t9 * t83 + t26 * t31 * t5 * t1 + (t48 * t32 - ModelPars[iM_g]) * t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DHxpDxpu_numRows() const { return 5; }
  integer HangGlider::DHxpDxpu_numCols() const { return 6; }
  integer HangGlider::DHxpDxpu_nnz()     const { return 19; }

  void
  HangGlider::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 3   ; jIndex[10] = 0   ;
    iIndex[11] = 3   ; jIndex[11] = 2   ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 3   ; jIndex[13] = 4   ;
    iIndex[14] = 3   ; jIndex[14] = 5   ;
    iIndex[15] = 4   ; jIndex[15] = 0   ;
    iIndex[16] = 4   ; jIndex[16] = 2   ;
    iIndex[17] = 4   ; jIndex[17] = 3   ;
    iIndex[18] = 4   ; jIndex[18] = 5   ;
  }


  void
  HangGlider::DHxpDxpu_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t13  = 1.0 / t11 / t10;
    real_type t14  = ModelPars[iM_c1];
    real_type t15  = U__[iU_cL];
    real_type t16  = t15 * t15;
    real_type t19  = t16 * t14 + ModelPars[iM_c0];
    real_type t20  = Dfun(t7, t8, t9);
    real_type t21  = t20 * t19;
    real_type t23  = Lfun(t7, t8, t9);
    real_type t24  = t23 * t15;
    real_type t25  = w(t7, t9);
    real_type t27  = -t8 * t21 - t25 * t24;
    real_type t28  = t27 * t13;
    real_type t29  = v_D_1(t7, t8, t9);
    real_type t30  = t29 * t29;
    real_type t34  = 1.0 / t11;
    real_type t35  = Dfun_D_1(t7, t8, t9);
    real_type t36  = t35 * t19;
    real_type t38  = Lfun_D_1(t7, t8, t9);
    real_type t39  = t38 * t15;
    real_type t41  = w_D_1(t7, t9);
    real_type t43  = -t41 * t24 - t25 * t39 - t8 * t36;
    real_type t44  = t43 * t34;
    real_type t48  = t27 * t34;
    real_type t49  = v_D_1_1(t7, t8, t9);
    real_type t52  = 1.0 / t10;
    real_type t53  = t52 * t5;
    real_type t54  = Dfun_D_1_1(t7, t8, t9);
    real_type t55  = t54 * t19;
    real_type t57  = Lfun_D_1_1(t7, t8, t9);
    real_type t58  = t57 * t15;
    real_type t62  = w_D_1_1(t7, t9);
    real_type t67  = L__[iL_lambda4__xo];
    real_type t68  = t5 * t2;
    real_type t71  = -t25 * t21 + t8 * t24;
    real_type t72  = t71 * t13;
    real_type t79  = -t41 * t21 - t25 * t36 + t8 * t39;
    real_type t80  = t79 * t34;
    real_type t84  = t71 * t34;
    result__[ 0   ] = 2 * t30 * t28 * t6 - 2 * t29 * t44 * t6 - t49 * t48 * t6 + (-t62 * t24 - t25 * t58 - 2 * t41 * t39 - t8 * t55) * t53 * t3 + (2 * t30 * t72 * t68 - 2 * t29 * t80 * t68 - t49 * t84 * t68 + (-t62 * t21 - t25 * t55 - 2 * t41 * t36 + t8 * t58) * t52 * t68) * t67;
    real_type t97  = v_D_2(t7, t8, t9);
    real_type t102 = Dfun_D_2(t7, t8, t9);
    real_type t103 = t102 * t19;
    real_type t105 = Lfun_D_2(t7, t8, t9);
    real_type t106 = t105 * t15;
    real_type t108 = -t8 * t103 - t25 * t106 - t21;
    real_type t109 = t108 * t34;
    real_type t112 = v_D_1_2(t7, t8, t9);
    real_type t117 = Dfun_D_1_2(t7, t8, t9);
    real_type t118 = t117 * t19;
    real_type t120 = Lfun_D_1_2(t7, t8, t9);
    real_type t121 = t120 * t15;
    real_type t127 = t13 * t68;
    real_type t128 = t29 * t71;
    real_type t134 = -t25 * t103 + t8 * t106 + t24;
    real_type t135 = t134 * t34;
    result__[ 1   ] = 2 * t97 * t29 * t28 * t6 - t29 * t109 * t6 - t112 * t48 * t6 - t97 * t44 * t6 + (-t41 * t106 - t8 * t118 - t25 * t121 - t36) * t53 * t3 + (2 * t97 * t128 * t127 - t29 * t135 * t68 - t112 * t84 * t68 - t97 * t80 * t68 + (-t41 * t103 - t25 * t118 + t8 * t121 + t39) * t52 * t68) * t67;
    real_type t150 = v_D_3(t7, t8, t9);
    real_type t155 = Dfun_D_3(t7, t8, t9);
    real_type t156 = t155 * t19;
    real_type t158 = Lfun_D_3(t7, t8, t9);
    real_type t159 = t158 * t15;
    real_type t161 = w_D_2(t7, t9);
    real_type t163 = -t8 * t156 - t25 * t159 - t161 * t24;
    real_type t164 = t163 * t34;
    real_type t167 = v_D_1_3(t7, t8, t9);
    real_type t172 = Dfun_D_1_3(t7, t8, t9);
    real_type t173 = t172 * t19;
    real_type t175 = Lfun_D_1_3(t7, t8, t9);
    real_type t176 = t175 * t15;
    real_type t180 = w_D_1_2(t7, t9);
    real_type t191 = -t25 * t156 + t8 * t159 - t161 * t21;
    real_type t192 = t191 * t34;
    result__[ 2   ] = 2 * t150 * t29 * t28 * t6 - t29 * t164 * t6 - t167 * t48 * t6 - t150 * t44 * t6 + (-t41 * t159 - t161 * t39 - t8 * t173 - t25 * t176 - t180 * t24) * t53 * t3 + (2 * t150 * t128 * t127 - t29 * t192 * t68 - t167 * t84 * t68 - t150 * t80 * t68 + (-t41 * t156 - t161 * t36 - t25 * t173 + t8 * t176 - t180 * t21) * t52 * t68) * t67;
    real_type t209 = t5 * t1;
    real_type t214 = t34 * t5;
    result__[ 3   ] = -t29 * t48 * t209 + t43 * t52 * t209 + (-t128 * t214 + t79 * t53) * t67;
    real_type t219 = t15 * t14;
    real_type t224 = -2 * t8 * t20 * t219 - t25 * t23;
    real_type t225 = t224 * t34;
    real_type t240 = -2 * t25 * t20 * t219 + t8 * t23;
    real_type t241 = t240 * t34;
    result__[ 4   ] = -t29 * t225 * t6 + (-2 * t8 * t35 * t219 - t41 * t23 - t25 * t38) * t53 * t3 + (-t29 * t241 * t68 + (-2 * t41 * t20 * t219 - 2 * t25 * t35 * t219 + t8 * t38) * t52 * t68) * t67;
    result__[ 5   ] = result__[1];
    real_type t256 = t97 * t97;
    real_type t263 = v_D_2_2(t7, t8, t9);
    real_type t266 = Dfun_D_2_2(t7, t8, t9);
    real_type t267 = t266 * t19;
    real_type t270 = Lfun_D_2_2(t7, t8, t9);
    real_type t271 = t270 * t15;
    result__[ 6   ] = 2 * t256 * t28 * t6 - 2 * t97 * t109 * t6 - t263 * t48 * t6 + (-t25 * t271 - t8 * t267 - 2 * t103) * t53 * t3 + (2 * t256 * t72 * t68 - 2 * t97 * t135 * t68 - t263 * t84 * t68 + (-t25 * t267 + t8 * t271 + 2 * t106) * t52 * t68) * t67;
    real_type t298 = v_D_2_3(t7, t8, t9);
    real_type t303 = Dfun_D_2_3(t7, t8, t9);
    real_type t304 = t303 * t19;
    real_type t306 = Lfun_D_2_3(t7, t8, t9);
    real_type t307 = t306 * t15;
    real_type t313 = t97 * t71;
    result__[ 7   ] = 2 * t150 * t97 * t28 * t6 - t97 * t164 * t6 - t298 * t48 * t6 - t150 * t109 * t6 + (-t161 * t106 - t25 * t307 - t8 * t304 - t156) * t53 * t3 + (2 * t150 * t313 * t127 - t97 * t192 * t68 - t298 * t84 * t68 - t150 * t135 * t68 + (-t161 * t103 - t25 * t304 + t8 * t307 + t159) * t52 * t68) * t67;
    result__[ 8   ] = L__[iL_lambda1__xo] - t97 * t48 * t209 + t108 * t52 * t209 + (t134 * t53 - t313 * t214) * t67;
    result__[ 9   ] = -t97 * t225 * t6 + (-2 * t8 * t102 * t219 - t25 * t105 - 2 * t20 * t219) * t53 * t3 + (-t97 * t241 * t68 + (-2 * t25 * t102 * t219 + t8 * t105 + t23) * t52 * t68) * t67;
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[7];
    real_type t362 = t150 * t150;
    real_type t369 = v_D_3_3(t7, t8, t9);
    real_type t372 = Dfun_D_3_3(t7, t8, t9);
    real_type t373 = t372 * t19;
    real_type t375 = Lfun_D_3_3(t7, t8, t9);
    real_type t376 = t375 * t15;
    real_type t380 = w_D_2_2(t7, t9);
    result__[ 12  ] = 2 * t362 * t28 * t6 - 2 * t150 * t164 * t6 - t369 * t48 * t6 + (-2 * t161 * t159 - t380 * t24 - t25 * t376 - t8 * t373) * t53 * t3 + (2 * t362 * t72 * t68 - 2 * t150 * t192 * t68 - t369 * t84 * t68 + (-2 * t161 * t156 - t380 * t21 - t25 * t373 + t8 * t376) * t52 * t68) * t67;
    result__[ 13  ] = L__[iL_lambda2__xo] - t150 * t48 * t209 + t163 * t52 * t209 + (-t150 * t71 * t214 + t191 * t53) * t67;
    result__[ 14  ] = -t150 * t225 * t6 + (-2 * t8 * t155 * t219 - t25 * t158 - t161 * t23) * t53 * t3 + (-t150 * t241 * t68 + (-2 * t25 * t155 * t219 - 2 * t161 * t20 * t219 + t8 * t158) * t52 * t68) * t67;
    result__[ 15  ] = result__[3];
    result__[ 16  ] = result__[8];
    result__[ 17  ] = result__[13];
    result__[ 18  ] = t240 * t52 * t5 * t67 + t224 * t52 * t209;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 19, i_segment );
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

  integer HangGlider::Hu_numEqns() const { return 1; }

  void
  HangGlider::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_cL];
    real_type t7   = P__[iP_T];
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_vy];
    real_type t14  = v(t11, t12, t13);
    real_type t16  = 1.0 / t14 / ModelPars[iM_m];
    real_type t18  = t2 * ModelPars[iM_c1];
    real_type t19  = Dfun(t11, t12, t13);
    real_type t23  = Lfun(t11, t12, t13);
    real_type t24  = w(t11, t13);
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] + (-2 * t12 * t18 * t19 - t23 * t24) * t16 * t7 * L__[iL_lambda3__xo] + (-2 * t18 * t19 * t24 + t12 * t23) * t16 * t7 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: HangGlider_Methods_AdjointODE.cc
