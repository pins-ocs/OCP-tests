/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_AdjointODE.cc                               |
 |                                                                       |
 |  version: 1.0   date 17/11/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  HangGlider::Hx_numEqns() const
  { return 4; }

  void
  HangGlider::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda3__xo];
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
    real_type t27  = (-t20 * t8 - t23 * t24) * t12;
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
    real_type t49  = (-t24 * t20 + t23 * t8) * t12;
    result__[ 0   ] = -t28 * t27 * t6 + (-t23 * t39 - t24 * t37 - t34 * t8) * t32 * t3 + (-t28 * t49 * t45 + (-t20 * t39 - t24 * t34 + t37 * t8) * t31 * t45) * t44;
    result__[ 1   ] = 0;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t66  = t65 * t18;
    real_type t68  = Lfun_D_2(t7, t8, t9);
    real_type t69  = t68 * t14;
    result__[ 2   ] = t2 * L__[iL_lambda1__xo] - t62 * t27 * t6 + (-t24 * t69 - t66 * t8 - t20) * t32 * t3 + (-t62 * t49 * t45 + (-t24 * t66 + t69 * t8 + t23) * t31 * t45) * t44;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t89  = t88 * t18;
    real_type t91  = Lfun_D_3(t7, t8, t9);
    real_type t92  = t91 * t14;
    real_type t94  = w_D_2(t7, t9);
    result__[ 3   ] = t2 * L__[iL_lambda2__xo] - t85 * t27 * t6 + (-t23 * t94 - t24 * t92 - t8 * t89) * t32 * t3 + (-t85 * t49 * t45 + (-t94 * t20 - t24 * t89 + t8 * t92) * t31 * t45) * t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DHxDx_numRows() const
  { return 4; }

  integer
  HangGlider::DHxDx_numCols() const
  { return 4; }

  integer
  HangGlider::DHxDx_nnz() const
  { return 9; }

  void
  HangGlider::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 3   ;
  }

  void
  HangGlider::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda3__xo];
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t13  = 1.0 / t11 / t10;
    real_type t15  = U__[iU_cL];
    real_type t16  = t15 * t15;
    real_type t19  = t16 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t20  = Dfun(t7, t8, t9);
    real_type t21  = t20 * t19;
    real_type t23  = Lfun(t7, t8, t9);
    real_type t24  = t23 * t15;
    real_type t25  = w(t7, t9);
    real_type t27  = -t21 * t8 - t24 * t25;
    real_type t28  = t27 * t13;
    real_type t29  = v_D_1(t7, t8, t9);
    real_type t30  = t29 * t29;
    real_type t34  = 1.0 / t11;
    real_type t35  = Dfun_D_1(t7, t8, t9);
    real_type t36  = t35 * t19;
    real_type t38  = Lfun_D_1(t7, t8, t9);
    real_type t39  = t38 * t15;
    real_type t41  = w_D_1(t7, t9);
    real_type t44  = (-t24 * t41 - t25 * t39 - t36 * t8) * t34;
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
    real_type t71  = -t21 * t25 + t24 * t8;
    real_type t72  = t71 * t13;
    real_type t80  = (-t21 * t41 - t25 * t36 + t39 * t8) * t34;
    real_type t84  = t71 * t34;
    result__[ 0   ] = 2 * t30 * t28 * t6 - 2 * t29 * t44 * t6 - t49 * t48 * t6 + (-t24 * t62 - t25 * t58 - 2 * t39 * t41 - t55 * t8) * t53 * t3 + (2 * t30 * t72 * t68 - 2 * t29 * t80 * t68 - t49 * t84 * t68 + (-t21 * t62 - t25 * t55 - 2 * t36 * t41 + t58 * t8) * t52 * t68) * t67;
    real_type t97  = v_D_2(t7, t8, t9);
    real_type t102 = Dfun_D_2(t7, t8, t9);
    real_type t103 = t102 * t19;
    real_type t105 = Lfun_D_2(t7, t8, t9);
    real_type t106 = t105 * t15;
    real_type t109 = (-t103 * t8 - t106 * t25 - t21) * t34;
    real_type t112 = v_D_1_2(t7, t8, t9);
    real_type t117 = Dfun_D_1_2(t7, t8, t9);
    real_type t118 = t117 * t19;
    real_type t120 = Lfun_D_1_2(t7, t8, t9);
    real_type t121 = t120 * t15;
    real_type t127 = t13 * t68;
    real_type t128 = t29 * t71;
    real_type t135 = (-t103 * t25 + t106 * t8 + t24) * t34;
    result__[ 1   ] = 2 * t97 * t29 * t28 * t6 - t29 * t109 * t6 - t112 * t48 * t6 - t97 * t44 * t6 + (-t106 * t41 - t118 * t8 - t121 * t25 - t36) * t53 * t3 + (2 * t97 * t128 * t127 - t29 * t135 * t68 - t112 * t84 * t68 - t97 * t80 * t68 + (-t103 * t41 - t118 * t25 + t121 * t8 + t39) * t52 * t68) * t67;
    real_type t150 = v_D_3(t7, t8, t9);
    real_type t155 = Dfun_D_3(t7, t8, t9);
    real_type t156 = t155 * t19;
    real_type t158 = Lfun_D_3(t7, t8, t9);
    real_type t159 = t158 * t15;
    real_type t161 = w_D_2(t7, t9);
    real_type t164 = (-t156 * t8 - t159 * t25 - t161 * t24) * t34;
    real_type t167 = v_D_1_3(t7, t8, t9);
    real_type t172 = Dfun_D_1_3(t7, t8, t9);
    real_type t173 = t172 * t19;
    real_type t175 = Lfun_D_1_3(t7, t8, t9);
    real_type t176 = t175 * t15;
    real_type t180 = w_D_1_2(t7, t9);
    real_type t192 = (-t156 * t25 + t159 * t8 - t161 * t21) * t34;
    result__[ 2   ] = 2 * t150 * t29 * t28 * t6 - t29 * t164 * t6 - t167 * t48 * t6 - t150 * t44 * t6 + (-t159 * t41 - t161 * t39 - t173 * t8 - t176 * t25 - t180 * t24) * t53 * t3 + (2 * t150 * t128 * t127 - t29 * t192 * t68 - t167 * t84 * t68 - t150 * t80 * t68 + (-t156 * t41 - t161 * t36 - t173 * t25 + t176 * t8 - t180 * t21) * t52 * t68) * t67;
    result__[ 3   ] = result__[1];
    real_type t209 = t97 * t97;
    real_type t216 = v_D_2_2(t7, t8, t9);
    real_type t219 = Dfun_D_2_2(t7, t8, t9);
    real_type t220 = t219 * t19;
    real_type t223 = Lfun_D_2_2(t7, t8, t9);
    real_type t224 = t223 * t15;
    result__[ 4   ] = 2 * t209 * t28 * t6 - 2 * t97 * t109 * t6 - t216 * t48 * t6 + (-t220 * t8 - t224 * t25 - 2 * t103) * t53 * t3 + (2 * t209 * t72 * t68 - 2 * t97 * t135 * t68 - t216 * t84 * t68 + (-t220 * t25 + t224 * t8 + 2 * t106) * t52 * t68) * t67;
    real_type t251 = v_D_2_3(t7, t8, t9);
    real_type t256 = Dfun_D_2_3(t7, t8, t9);
    real_type t257 = t256 * t19;
    real_type t259 = Lfun_D_2_3(t7, t8, t9);
    real_type t260 = t259 * t15;
    result__[ 5   ] = 2 * t150 * t97 * t28 * t6 - t97 * t164 * t6 - t251 * t48 * t6 - t150 * t109 * t6 + (-t106 * t161 - t25 * t260 - t257 * t8 - t156) * t53 * t3 + (2 * t150 * t97 * t71 * t127 - t97 * t192 * t68 - t251 * t84 * t68 - t150 * t135 * t68 + (-t103 * t161 - t25 * t257 + t260 * t8 + t159) * t52 * t68) * t67;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t284 = t150 * t150;
    real_type t291 = v_D_3_3(t7, t8, t9);
    real_type t294 = Dfun_D_3_3(t7, t8, t9);
    real_type t295 = t294 * t19;
    real_type t297 = Lfun_D_3_3(t7, t8, t9);
    real_type t298 = t297 * t15;
    real_type t302 = w_D_2_2(t7, t9);
    result__[ 8   ] = 2 * t284 * t28 * t6 - 2 * t150 * t164 * t6 - t291 * t48 * t6 + (-2 * t159 * t161 - t24 * t302 - t25 * t298 - t295 * t8) * t53 * t3 + (2 * t284 * t72 * t68 - 2 * t150 * t192 * t68 - t291 * t84 * t68 + (-2 * t156 * t161 - t21 * t302 - t25 * t295 + t298 * t8) * t52 * t68) * t67;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DHxDp_numRows() const
  { return 4; }

  integer
  HangGlider::DHxDp_numCols() const
  { return 1; }

  integer
  HangGlider::DHxDp_nnz() const
  { return 3; }

  void
  HangGlider::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = 1.0 / ModelPars[iM_m];
    real_type t4   = t3 * L__[iL_lambda3__xo];
    real_type t5   = X__[iX_x];
    real_type t6   = X__[iX_vx];
    real_type t7   = X__[iX_vy];
    real_type t8   = v(t5, t6, t7);
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = U__[iU_cL];
    real_type t13  = t12 * t12;
    real_type t16  = t13 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t17  = Dfun(t5, t6, t7);
    real_type t18  = t17 * t16;
    real_type t20  = Lfun(t5, t6, t7);
    real_type t21  = t20 * t12;
    real_type t22  = w(t5, t7);
    real_type t25  = (-t6 * t18 - t22 * t21) * t10;
    real_type t26  = v_D_1(t5, t6, t7);
    real_type t29  = 1.0 / t8;
    real_type t30  = Dfun_D_1(t5, t6, t7);
    real_type t31  = t30 * t16;
    real_type t33  = Lfun_D_1(t5, t6, t7);
    real_type t34  = t33 * t12;
    real_type t36  = w_D_1(t5, t7);
    real_type t41  = L__[iL_lambda4__xo];
    real_type t42  = t10 * t3;
    real_type t45  = -t22 * t18 + t6 * t21;
    real_type t48  = t29 * t3;
    result__[ 0   ] = -t26 * t25 * t4 + (-t36 * t21 - t22 * t34 - t6 * t31) * t29 * t4 + (-t26 * t45 * t42 + (-t36 * t18 - t22 * t31 + t6 * t34) * t48) * t41;
    real_type t57  = v_D_2(t5, t6, t7);
    real_type t60  = Dfun_D_2(t5, t6, t7);
    real_type t61  = t60 * t16;
    real_type t63  = Lfun_D_2(t5, t6, t7);
    real_type t64  = t63 * t12;
    result__[ 1   ] = L__[iL_lambda1__xo] - t57 * t25 * t4 + (-t22 * t64 - t6 * t61 - t18) * t29 * t4 + (-t57 * t45 * t42 + (-t22 * t61 + t6 * t64 + t21) * t48) * t41;
    real_type t78  = v_D_3(t5, t6, t7);
    real_type t81  = Dfun_D_3(t5, t6, t7);
    real_type t82  = t81 * t16;
    real_type t84  = Lfun_D_3(t5, t6, t7);
    real_type t85  = t84 * t12;
    real_type t87  = w_D_2(t5, t7);
    result__[ 2   ] = L__[iL_lambda2__xo] - t78 * t25 * t4 + (-t87 * t21 - t22 * t85 - t6 * t82) * t29 * t4 + (-t78 * t45 * t42 + (-t87 * t18 - t22 * t82 + t6 * t85) * t48) * t41;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 3, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  integer
  HangGlider::Hu_numEqns() const
  { return 1; }

  void
  HangGlider::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
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
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] + (-2 * t12 * t19 * t18 - t23 * t24) * t16 * t7 * L__[iL_lambda3__xo] + (-2 * t24 * t19 * t18 + t12 * t23) * t16 * t7 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DHuDx_numRows() const
  { return 1; }

  integer
  HangGlider::DHuDx_numCols() const
  { return 4; }

  integer
  HangGlider::DHuDx_nnz() const
  { return 3; }

  void
  HangGlider::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda3__xo];
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_c1] * U__[iU_cL];
    real_type t16  = Dfun(t7, t8, t9);
    real_type t20  = Lfun(t7, t8, t9);
    real_type t21  = w(t7, t9);
    real_type t24  = (-2 * t8 * t16 * t15 - t21 * t20) * t12;
    real_type t25  = v_D_1(t7, t8, t9);
    real_type t29  = 1.0 / t10 * t5;
    real_type t30  = Dfun_D_1(t7, t8, t9);
    real_type t34  = Lfun_D_1(t7, t8, t9);
    real_type t36  = w_D_1(t7, t9);
    real_type t42  = t2 * L__[iL_lambda4__xo];
    real_type t43  = t5 * t42;
    real_type t49  = (-2 * t21 * t16 * t15 + t8 * t20) * t12;
    result__[ 0   ] = -t25 * t24 * t6 + (-2 * t8 * t30 * t15 - t36 * t20 - t21 * t34) * t29 * t3 - t25 * t49 * t43 + (-2 * t36 * t16 * t15 - 2 * t21 * t30 * t15 + t8 * t34) * t29 * t42;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t71  = Lfun_D_2(t7, t8, t9);
    result__[ 1   ] = -t62 * t24 * t6 + (-2 * t8 * t65 * t15 - 2 * t16 * t15 - t21 * t71) * t29 * t3 - t62 * t49 * t43 + (-2 * t21 * t65 * t15 + t8 * t71 + t20) * t29 * t42;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t92  = Lfun_D_3(t7, t8, t9);
    real_type t94  = w_D_2(t7, t9);
    result__[ 2   ] = -t85 * t24 * t6 + (-2 * t8 * t88 * t15 - t94 * t20 - t21 * t92) * t29 * t3 - t85 * t49 * t43 + (-2 * t94 * t16 * t15 - 2 * t21 * t88 * t15 + t8 * t92) * t29 * t42;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DHuDp_numRows() const
  { return 1; }

  integer
  HangGlider::DHuDp_numCols() const
  { return 1; }

  integer
  HangGlider::DHuDp_nnz() const
  { return 1; }

  void
  HangGlider::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = 1.0 / ModelPars[iM_m];
    real_type t5   = X__[iX_x];
    real_type t6   = X__[iX_vx];
    real_type t7   = X__[iX_vy];
    real_type t8   = v(t5, t6, t7);
    real_type t9   = 1.0 / t8;
    real_type t12  = ModelPars[iM_c1] * U__[iU_cL];
    real_type t13  = Dfun(t5, t6, t7);
    real_type t17  = Lfun(t5, t6, t7);
    real_type t18  = w(t5, t7);
    result__[ 0   ] = (-2 * t6 * t13 * t12 - t18 * t17) * t9 * t3 * L__[iL_lambda3__xo] + (-2 * t18 * t13 * t12 + t6 * t17) * t9 * t3 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHuDp_sparse", 1, i_segment );
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  HangGlider::Hp_numEqns() const
  { return 1; }

  void
  HangGlider::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_Tbound_D(P__[iP_T]);
    real_type t4   = X__[iX_vx];
    real_type t7   = X__[iX_vy];
    real_type t11  = 1.0 / ModelPars[iM_m];
    real_type t13  = X__[iX_x];
    real_type t14  = v(t13, t4, t7);
    real_type t15  = 1.0 / t14;
    real_type t17  = U__[iU_cL];
    real_type t18  = t17 * t17;
    real_type t22  = Dfun(t13, t4, t7);
    real_type t23  = t22 * (t18 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t25  = Lfun(t13, t4, t7);
    real_type t26  = t25 * t17;
    real_type t27  = w(t13, t7);
    result__[ 0   ] = t2 + t4 * L__[iL_lambda1__xo] + t7 * L__[iL_lambda2__xo] + (-t4 * t23 - t27 * t26) * t15 * t11 * L__[iL_lambda3__xo] + ((-t27 * t23 + t4 * t26) * t15 * t11 - ModelPars[iM_g]) * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DHpDp_numRows() const
  { return 1; }

  integer
  HangGlider::DHpDp_numCols() const
  { return 1; }

  integer
  HangGlider::DHpDp_nnz() const
  { return 1; }

  void
  HangGlider::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_Tbound_DD(P__[iP_T]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse" ,1, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  HangGlider::eta_numEqns() const
  { return 4; }

  void
  HangGlider::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DetaDx_numRows() const
  { return 4; }

  integer
  HangGlider::DetaDx_numCols() const
  { return 4; }

  integer
  HangGlider::DetaDx_nnz() const
  { return 0; }

  void
  HangGlider::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DetaDp_numRows() const
  { return 4; }

  integer
  HangGlider::DetaDp_numCols() const
  { return 1; }

  integer
  HangGlider::DetaDp_nnz() const
  { return 0; }

  void
  HangGlider::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  HangGlider::nu_numEqns() const
  { return 4; }

  void
  HangGlider::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DnuDx_numRows() const
  { return 4; }

  integer
  HangGlider::DnuDx_numCols() const
  { return 4; }

  integer
  HangGlider::DnuDx_nnz() const
  { return 0; }

  void
  HangGlider::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DnuDp_numRows() const
  { return 4; }

  integer
  HangGlider::DnuDp_numCols() const
  { return 1; }

  integer
  HangGlider::DnuDp_nnz() const
  { return 0; }

  void
  HangGlider::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: HangGlider_Methods_AdjointODE.cc
