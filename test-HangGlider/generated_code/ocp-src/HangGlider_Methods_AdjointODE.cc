/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_AdjointODE.cc                               |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_vy];
    real_type t3   = w_D_1(t1, t2);
    real_type t4   = L__[iL_lambda4__xo];
    real_type t7   = U__[iU_cL];
    real_type t8   = t7 * t7;
    real_type t11  = t8 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t12  = X__[iX_vx];
    real_type t13  = Dfun(t1, t12, t2);
    real_type t14  = t13 * t11;
    real_type t16  = L__[iL_lambda3__xo];
    real_type t18  = w(t1, t2);
    real_type t21  = (t16 * t12 + t18 * t4) * t11;
    real_type t22  = Dfun_D_1(t1, t12, t2);
    real_type t25  = Lfun(t1, t12, t2);
    real_type t27  = Lfun_D_1(t1, t12, t2);
    real_type t30  = -t12 * t4 + t18 * t16;
    real_type t35  = v(t1, t12, t2);
    real_type t37  = v_D_1(t1, t12, t2);
    real_type t41  = t30 * t25 * t7 + t13 * t21;
    real_type t44  = P__[iP_T];
    real_type t46  = ModelPars[iM_m];
    real_type t48  = t35 * t35;
    real_type t50  = 1.0 / t48 / t46;
    result__[ 0   ] = -t50 * t44 * (t35 * (t14 * t4 * t3 + t22 * t21 + t7 * (t25 * t3 * t16 + t30 * t27)) - t41 * t37);
    result__[ 1   ] = 0;
    real_type t57  = Dfun_D_2(t1, t12, t2);
    real_type t60  = Lfun_D_2(t1, t12, t2);
    real_type t66  = v_D_2(t1, t12, t2);
    result__[ 2   ] = t50 * t44 * (t48 * t46 * L__[iL_lambda1__xo] + t35 * (-t13 * t11 * t16 - t57 * t21 - t7 * (-t25 * t4 + t30 * t60)) + t41 * t66);
    real_type t73  = w_D_2(t1, t2);
    real_type t76  = Dfun_D_3(t1, t12, t2);
    real_type t80  = Lfun_D_3(t1, t12, t2);
    real_type t86  = v_D_3(t1, t12, t2);
    result__[ 3   ] = t50 * t44 * (t48 * t46 * L__[iL_lambda2__xo] + t35 * (-t14 * t4 * t73 - t76 * t21 - t7 * (t25 * t16 * t73 + t30 * t80)) + t86 * t41);
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x];
    real_type t3   = X__[iX_vy];
    real_type t4   = w_D_1_1(t2, t3);
    real_type t5   = L__[iL_lambda4__xo];
    real_type t8   = U__[iU_cL];
    real_type t9   = t8 * t8;
    real_type t12  = t9 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t13  = X__[iX_vx];
    real_type t14  = Dfun(t2, t13, t3);
    real_type t15  = t14 * t12;
    real_type t17  = w_D_1(t2, t3);
    real_type t18  = t5 * t17;
    real_type t19  = Dfun_D_1(t2, t13, t3);
    real_type t20  = t19 * t12;
    real_type t23  = L__[iL_lambda3__xo];
    real_type t25  = Lfun(t2, t13, t3);
    real_type t26  = t25 * t8;
    real_type t29  = w(t2, t3);
    real_type t32  = (t13 * t23 + t29 * t5) * t12;
    real_type t33  = Dfun_D_1_1(t2, t13, t3);
    real_type t35  = t17 * t23;
    real_type t36  = Lfun_D_1(t2, t13, t3);
    real_type t39  = Lfun_D_1_1(t2, t13, t3);
    real_type t42  = -t13 * t5 + t29 * t23;
    real_type t47  = v(t2, t13, t3);
    real_type t48  = t47 * t47;
    real_type t50  = t15 * t18;
    real_type t51  = t19 * t32;
    real_type t56  = -t50 - t51 - t8 * (t25 * t35 + t42 * t36);
    real_type t58  = v_D_1(t2, t13, t3);
    real_type t62  = t14 * t32 + t42 * t26;
    real_type t63  = v_D_1_1(t2, t13, t3);
    real_type t67  = t58 * t58;
    real_type t76  = 1.0 / t48 / t47 / ModelPars[iM_m];
    result__[ 0   ] = -t76 * (t48 * (t15 * t5 * t4 + 2 * t20 * t18 + t26 * t4 * t23 + t33 * t32 + t8 * (2 * t36 * t35 + t42 * t39)) + t47 * (2 * t58 * t56 - t63 * t62) + 2 * t67 * t62) * t1;
    real_type t78  = t12 * t23;
    real_type t80  = Dfun_D_2(t2, t13, t3);
    real_type t81  = t80 * t12;
    real_type t83  = Dfun_D_1_2(t2, t13, t3);
    real_type t86  = Lfun_D_2(t2, t13, t3);
    real_type t88  = Lfun_D_1_2(t2, t13, t3);
    real_type t100 = -t14 * t78 - t80 * t32 - (-t25 * t5 + t42 * t86) * t8;
    real_type t102 = v_D_2(t2, t13, t3);
    real_type t104 = v_D_1_2(t2, t13, t3);
    result__[ 1   ] = -t76 * t1 * (t48 * (t19 * t78 + t81 * t18 + t83 * t32 + t8 * (t86 * t35 - t36 * t5 + t42 * t88)) + t47 * (t58 * t100 + t102 * t56 - t62 * t104) + 2 * t62 * t102 * t58);
    real_type t114 = w_D_1_2(t2, t3);
    real_type t119 = w_D_2(t2, t3);
    real_type t120 = t5 * t119;
    real_type t122 = Dfun_D_3(t2, t13, t3);
    real_type t123 = t122 * t12;
    real_type t125 = Dfun_D_1_3(t2, t13, t3);
    real_type t127 = t119 * t23;
    real_type t129 = Lfun_D_3(t2, t13, t3);
    real_type t131 = Lfun_D_1_3(t2, t13, t3);
    real_type t137 = t15 * t120;
    real_type t139 = t122 * t32;
    real_type t148 = v_D_3(t2, t13, t3);
    real_type t150 = v_D_1_3(t2, t13, t3);
    result__[ 2   ] = -t76 * t1 * (t48 * (t15 * t5 * t114 + t26 * t114 * t23 + t20 * t120 + t123 * t18 + t125 * t32 + t8 * (t36 * t127 + t129 * t35 + t42 * t131)) + t47 * (t58 * (-t42 * t8 * t129 - t26 * t127 - t137 - t139) + t148 * (-t42 * t8 * t36 - t26 * t35 - t50 - t51) - t150 * t62) + 2 * t58 * t62 * t148);
    result__[ 3   ] = result__[1];
    real_type t162 = Dfun_D_2_2(t2, t13, t3);
    real_type t166 = Lfun_D_2_2(t2, t13, t3);
    real_type t174 = v_D_2_2(t2, t13, t3);
    real_type t178 = t102 * t102;
    result__[ 4   ] = -t76 * t1 * (t48 * (2 * t80 * t78 + t162 * t32 + t8 * (t42 * t166 - 2 * t86 * t5)) + t47 * (2 * t102 * t100 - t62 * t174) + 2 * t178 * t62);
    real_type t186 = Dfun_D_2_3(t2, t13, t3);
    real_type t190 = Lfun_D_2_3(t2, t13, t3);
    real_type t200 = -t137 - t139 - t8 * (t25 * t127 + t42 * t129);
    real_type t203 = v_D_2_3(t2, t13, t3);
    result__[ 5   ] = -t76 * t1 * (t48 * (t81 * t120 + t122 * t78 + t186 * t32 + t8 * (t86 * t127 - t129 * t5 + t42 * t190)) + t47 * (t148 * t100 + t102 * t200 - t62 * t203) + 2 * t62 * t148 * t102);
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t213 = w_D_2_2(t2, t3);
    real_type t220 = Dfun_D_3_3(t2, t13, t3);
    real_type t224 = Lfun_D_3_3(t2, t13, t3);
    real_type t232 = v_D_3_3(t2, t13, t3);
    real_type t236 = t148 * t148;
    result__[ 8   ] = -t76 * (t48 * (t15 * t5 * t213 + 2 * t123 * t120 + t26 * t213 * t23 + t220 * t32 + t8 * (2 * t129 * t127 + t42 * t224)) + t47 * (2 * t148 * t200 - t232 * t62) + 2 * t236 * t62) * t1;
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_vy];
    real_type t3   = w_D_1(t1, t2);
    real_type t4   = L__[iL_lambda4__xo];
    real_type t7   = U__[iU_cL];
    real_type t8   = t7 * t7;
    real_type t11  = t8 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t12  = X__[iX_vx];
    real_type t13  = Dfun(t1, t12, t2);
    real_type t14  = t13 * t11;
    real_type t16  = L__[iL_lambda3__xo];
    real_type t18  = w(t1, t2);
    real_type t21  = (t12 * t16 + t18 * t4) * t11;
    real_type t22  = Dfun_D_1(t1, t12, t2);
    real_type t25  = Lfun(t1, t12, t2);
    real_type t27  = Lfun_D_1(t1, t12, t2);
    real_type t30  = -t12 * t4 + t18 * t16;
    real_type t35  = v(t1, t12, t2);
    real_type t40  = t30 * t7 * t25 + t13 * t21;
    real_type t41  = v_D_1(t1, t12, t2);
    real_type t44  = ModelPars[iM_m];
    real_type t45  = 1.0 / t44;
    real_type t47  = t35 * t35;
    real_type t48  = 1.0 / t47;
    result__[ 0   ] = t48 * t45 * (t35 * (-t14 * t4 * t3 - t22 * t21 - t7 * (t25 * t3 * t16 + t30 * t27)) + t41 * t40);
    real_type t54  = Dfun_D_2(t1, t12, t2);
    real_type t57  = Lfun_D_2(t1, t12, t2);
    real_type t63  = v_D_2(t1, t12, t2);
    result__[ 1   ] = t48 * t45 * (t47 * t44 * L__[iL_lambda1__xo] + t35 * (-t13 * t11 * t16 - t54 * t21 - (-t25 * t4 + t30 * t57) * t7) + t40 * t63);
    real_type t70  = w_D_2(t1, t2);
    real_type t73  = Dfun_D_3(t1, t12, t2);
    real_type t77  = Lfun_D_3(t1, t12, t2);
    real_type t83  = v_D_3(t1, t12, t2);
    result__[ 2   ] = t48 * t45 * (t47 * t44 * L__[iL_lambda2__xo] + t35 * (-t14 * t4 * t70 - t73 * t21 - t7 * (t25 * t70 * t16 + t30 * t77)) + t40 * t83);
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_cL];
    real_type t6   = P__[iP_T];
    real_type t10  = t2 * ModelPars[iM_c1];
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_vy];
    real_type t14  = Dfun(t11, t12, t13);
    real_type t17  = Lfun(t11, t12, t13);
    real_type t18  = w(t11, t13);
    real_type t23  = 1.0 / ModelPars[iM_m];
    real_type t25  = v(t11, t12, t13);
    real_type t26  = 1.0 / t25;
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] - 2 * t26 * t23 * (t12 * t14 * t10 + t18 * t17 / 2) * L__[iL_lambda3__xo] * t6 + (-2 * t18 * t14 * t10 + t12 * t17) * t26 * t23 * t6 * L__[iL_lambda4__xo];
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x];
    real_type t3   = X__[iX_vy];
    real_type t4   = w_D_1(t2, t3);
    real_type t5   = L__[iL_lambda4__xo];
    real_type t7   = U__[iU_cL];
    real_type t8   = ModelPars[iM_c1];
    real_type t9   = t8 * t7;
    real_type t10  = X__[iX_vx];
    real_type t11  = Dfun(t2, t10, t3);
    real_type t12  = t11 * t9;
    real_type t15  = L__[iL_lambda3__xo];
    real_type t17  = Lfun(t2, t10, t3);
    real_type t20  = w(t2, t3);
    real_type t22  = t10 * t15 + t20 * t5;
    real_type t23  = Dfun_D_1(t2, t10, t3);
    real_type t27  = Lfun_D_1(t2, t10, t3);
    real_type t30  = -t10 * t5 + t20 * t15;
    real_type t33  = v(t2, t10, t3);
    real_type t35  = v_D_1(t2, t10, t3);
    real_type t40  = 2 * t11 * t22 * t9 + t30 * t17;
    real_type t46  = t33 * t33;
    real_type t48  = 1.0 / t46 / ModelPars[iM_m];
    result__[ 0   ] = -t48 * (t33 * (2 * t12 * t5 * t4 + t17 * t4 * t15 + 2 * t23 * t22 * t9 + t30 * t27) - t40 * t35) * t1;
    real_type t55  = Dfun_D_2(t2, t10, t3);
    real_type t59  = Lfun_D_2(t2, t10, t3);
    real_type t63  = v_D_2(t2, t10, t3);
    result__[ 1   ] = -t48 * t1 * (t33 * (2 * t11 * t8 * t7 * t15 + 2 * t55 * t22 * t9 - t5 * t17 + t30 * t59) - t40 * t63);
    real_type t68  = w_D_2(t2, t3);
    real_type t74  = Dfun_D_3(t2, t10, t3);
    real_type t78  = Lfun_D_3(t2, t10, t3);
    real_type t82  = v_D_3(t2, t10, t3);
    result__[ 2   ] = -t48 * (t33 * (2 * t12 * t5 * t68 + t17 * t68 * t15 + 2 * t74 * t22 * t9 + t30 * t78) - t40 * t82) * t1;
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = L__[iL_lambda3__xo];
    real_type t5   = X__[iX_vx];
    real_type t7   = L__[iL_lambda4__xo];
    real_type t8   = X__[iX_x];
    real_type t9   = X__[iX_vy];
    real_type t10  = w(t8, t9);
    real_type t13  = Dfun(t8, t5, t9);
    real_type t17  = Lfun(t8, t5, t9);
    real_type t26  = v(t8, t5, t9);
    result__[ 0   ] = 1.0 / t26 / ModelPars[iM_m] * (-2 * t13 * (t10 * t7 + t5 * t4) * ModelPars[iM_c1] * U__[iU_cL] - (t10 * t4 - t5 * t7) * t17);
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_m];
    real_type t3   = X__[iX_vx];
    real_type t6   = L__[iL_lambda4__xo];
    real_type t9   = X__[iX_vy];
    real_type t12  = ALIAS_Tbound_D(P__[iP_T]);
    real_type t15  = X__[iX_x];
    real_type t16  = v(t15, t3, t9);
    real_type t19  = U__[iU_cL];
    real_type t20  = t19 * t19;
    real_type t24  = L__[iL_lambda3__xo];
    real_type t26  = w(t15, t9);
    real_type t30  = Dfun(t15, t3, t9);
    real_type t32  = Lfun(t15, t3, t9);
    result__[ 0   ] = 1.0 / t16 / t1 * (t16 * (t3 * L__[iL_lambda1__xo] - t6 * ModelPars[iM_g] + t9 * L__[iL_lambda2__xo] + t12) * t1 - t30 * (t3 * t24 + t26 * t6) * (t20 * ModelPars[iM_c1] + ModelPars[iM_c0]) - (t26 * t24 - t3 * t6) * t32 * t19);
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
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
    real_ptr             result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    // EMPTY!
  }

}

// EOF: HangGlider_Methods_AdjointODE.cc
