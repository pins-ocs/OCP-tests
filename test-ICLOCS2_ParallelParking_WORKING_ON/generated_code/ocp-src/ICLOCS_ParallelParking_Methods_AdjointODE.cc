/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 5/12/2021                                        |
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


#include "ICLOCS_ParallelParking.hh"
#include "ICLOCS_ParallelParking_Pars.hh"

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
#define ALIAS_phi_bound_DD(__t1) phi_bound.DD( __t1)
#define ALIAS_phi_bound_D(__t1) phi_bound.D( __t1)
#define ALIAS_acc_bound_DD(__t1) acc_bound.DD( __t1)
#define ALIAS_acc_bound_D(__t1) acc_bound.D( __t1)
#define ALIAS_vel_bound_DD(__t1) vel_bound.DD( __t1)
#define ALIAS_vel_bound_D(__t1) vel_bound.D( __t1)
#define ALIAS_EXTRA2_bound_DD(__t1) EXTRA2_bound.DD( __t1)
#define ALIAS_EXTRA2_bound_D(__t1) EXTRA2_bound.D( __t1)
#define ALIAS_EXTRA1_bound_DD(__t1) EXTRA1_bound.DD( __t1)
#define ALIAS_EXTRA1_bound_D(__t1) EXTRA1_bound.D( __t1)
#define ALIAS_D_bound_DD(__t1) D_bound.DD( __t1)
#define ALIAS_D_bound_D(__t1) D_bound.D( __t1)
#define ALIAS_C_bound_DD(__t1) C_bound.DD( __t1)
#define ALIAS_C_bound_D(__t1) C_bound.D( __t1)
#define ALIAS_B_bound_DD(__t1) B_bound.DD( __t1)
#define ALIAS_B_bound_D(__t1) B_bound.D( __t1)
#define ALIAS_A_bound_DD(__t1) A_bound.DD( __t1)
#define ALIAS_A_bound_D(__t1) A_bound.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_ParallelParkingDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  ICLOCS_ParallelParking::Hx_numEqns() const
  { return 6; }

  void
  ICLOCS_ParallelParking::Hx_eval(
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
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_y];
    real_type t3   = X__[iX_theta];
    real_type t4   = Ay(t1, t2, t3);
    real_type t5   = ALIAS_A_bound_D(t4);
    real_type t6   = Ay_D_1(t1, t2, t3);
    real_type t8   = By(t1, t2, t3);
    real_type t9   = ALIAS_B_bound_D(t8);
    real_type t10  = By_D_1(t1, t2, t3);
    real_type t12  = Cy(t1, t2, t3);
    real_type t13  = ALIAS_C_bound_D(t12);
    real_type t14  = Cy_D_1(t1, t2, t3);
    real_type t16  = Dy(t1, t2, t3);
    real_type t17  = ALIAS_D_bound_D(t16);
    real_type t18  = Dy_D_1(t1, t2, t3);
    real_type t20  = AEB(t1, t2, t3);
    real_type t21  = BEC(t1, t2, t3);
    real_type t22  = CED(t1, t2, t3);
    real_type t23  = DEA(t1, t2, t3);
    real_type t24  = ABCD(t1, t2, t3);
    real_type t26  = ALIAS_EXTRA1_bound_D(t20 + t21 + t22 + t23 - t24);
    real_type t27  = AEB_D_1(t1, t2, t3);
    real_type t28  = BEC_D_1(t1, t2, t3);
    real_type t29  = CED_D_1(t1, t2, t3);
    real_type t30  = DEA_D_1(t1, t2, t3);
    real_type t31  = ABCD_D_1(t1, t2, t3);
    real_type t34  = AOB(t1, t2, t3);
    real_type t35  = BOC(t1, t2, t3);
    real_type t36  = COD(t1, t2, t3);
    real_type t37  = DOA(t1, t2, t3);
    real_type t39  = ALIAS_EXTRA2_bound_D(t34 + t35 + t36 + t37 - t24);
    real_type t40  = AOB_D_1(t1, t2, t3);
    real_type t41  = BOC_D_1(t1, t2, t3);
    real_type t42  = COD_D_1(t1, t2, t3);
    real_type t43  = DOA_D_1(t1, t2, t3);
    result__[ 0   ] = t6 * t5 + t10 * t9 + t14 * t13 + t18 * t17 + (t27 + t28 + t29 + t30 - t31) * t26 + (t40 + t41 + t42 + t43 - t31) * t39;
    real_type t46  = Ay_D_2(t1, t2, t3);
    real_type t48  = By_D_2(t1, t2, t3);
    real_type t50  = Cy_D_2(t1, t2, t3);
    real_type t52  = Dy_D_2(t1, t2, t3);
    real_type t54  = AEB_D_2(t1, t2, t3);
    real_type t55  = BEC_D_2(t1, t2, t3);
    real_type t56  = CED_D_2(t1, t2, t3);
    real_type t57  = DEA_D_2(t1, t2, t3);
    real_type t58  = ABCD_D_2(t1, t2, t3);
    real_type t61  = AOB_D_2(t1, t2, t3);
    real_type t62  = BOC_D_2(t1, t2, t3);
    real_type t63  = COD_D_2(t1, t2, t3);
    real_type t64  = DOA_D_2(t1, t2, t3);
    result__[ 1   ] = t46 * t5 + t48 * t9 + t50 * t13 + t52 * t17 + (t54 + t55 + t56 + t57 - t58) * t26 + (t61 + t62 + t63 + t64 - t58) * t39;
    real_type t67  = X__[iX_v];
    real_type t68  = ALIAS_vel_bound_D(t67);
    real_type t70  = P__[iP_T];
    real_type t71  = t70 * L__[iL_lambda1__xo];
    real_type t72  = cos(t3);
    real_type t75  = t70 * L__[iL_lambda2__xo];
    real_type t76  = sin(t3);
    real_type t79  = t70 * L__[iL_lambda5__xo];
    real_type t80  = X__[iX_phi];
    real_type t81  = tan(t80);
    real_type t83  = 1.0 / ModelPars[iM_len_a];
    result__[ 2   ] = U__[iU_u2] * t70 * L__[iL_lambda6__xo] + t83 * t81 * t79 + t72 * t71 + t76 * t75 + t68;
    real_type t91  = ALIAS_acc_bound_D(X__[iX_a]);
    result__[ 3   ] = t70 * L__[iL_lambda3__xo] + t91;
    real_type t94  = Ay_D_3(t1, t2, t3);
    real_type t96  = By_D_3(t1, t2, t3);
    real_type t98  = Cy_D_3(t1, t2, t3);
    real_type t100 = Dy_D_3(t1, t2, t3);
    real_type t102 = AEB_D_3(t1, t2, t3);
    real_type t103 = BEC_D_3(t1, t2, t3);
    real_type t104 = CED_D_3(t1, t2, t3);
    real_type t105 = DEA_D_3(t1, t2, t3);
    real_type t106 = ABCD_D_3(t1, t2, t3);
    real_type t109 = AOB_D_3(t1, t2, t3);
    real_type t110 = BOC_D_3(t1, t2, t3);
    real_type t111 = COD_D_3(t1, t2, t3);
    real_type t112 = DOA_D_3(t1, t2, t3);
    result__[ 4   ] = t94 * t5 + t96 * t9 + t98 * t13 + t100 * t17 + (t102 + t103 + t104 + t105 - t106) * t26 + (t109 + t110 + t111 + t112 - t106) * t39 - t76 * t67 * t71 + t72 * t67 * t75;
    real_type t119 = ALIAS_phi_bound_D(t80);
    real_type t120 = t81 * t81;
    result__[ 5   ] = t119 + t83 * (1 + t120) * t67 * t79;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DHxDx_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DHxDx_numCols() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DHxDx_nnz() const
  { return 16; }

  void
  ICLOCS_ParallelParking::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 3   ;
    iIndex[10] = 4   ; jIndex[10] = 0   ;
    iIndex[11] = 4   ; jIndex[11] = 1   ;
    iIndex[12] = 4   ; jIndex[12] = 2   ;
    iIndex[13] = 4   ; jIndex[13] = 4   ;
    iIndex[14] = 5   ; jIndex[14] = 2   ;
    iIndex[15] = 5   ; jIndex[15] = 5   ;
  }

  void
  ICLOCS_ParallelParking::DHxDx_sparse(
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
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_y];
    real_type t3   = X__[iX_theta];
    real_type t4   = Ay(t1, t2, t3);
    real_type t5   = ALIAS_A_bound_DD(t4);
    real_type t6   = Ay_D_1(t1, t2, t3);
    real_type t7   = t6 * t6;
    real_type t9   = ALIAS_A_bound_D(t4);
    real_type t10  = Ay_D_1_1(t1, t2, t3);
    real_type t12  = By(t1, t2, t3);
    real_type t13  = ALIAS_B_bound_DD(t12);
    real_type t14  = By_D_1(t1, t2, t3);
    real_type t15  = t14 * t14;
    real_type t17  = ALIAS_B_bound_D(t12);
    real_type t18  = By_D_1_1(t1, t2, t3);
    real_type t20  = Cy(t1, t2, t3);
    real_type t21  = ALIAS_C_bound_DD(t20);
    real_type t22  = Cy_D_1(t1, t2, t3);
    real_type t23  = t22 * t22;
    real_type t25  = ALIAS_C_bound_D(t20);
    real_type t26  = Cy_D_1_1(t1, t2, t3);
    real_type t28  = Dy(t1, t2, t3);
    real_type t29  = ALIAS_D_bound_DD(t28);
    real_type t30  = Dy_D_1(t1, t2, t3);
    real_type t31  = t30 * t30;
    real_type t33  = ALIAS_D_bound_D(t28);
    real_type t34  = Dy_D_1_1(t1, t2, t3);
    real_type t36  = AEB(t1, t2, t3);
    real_type t37  = BEC(t1, t2, t3);
    real_type t38  = CED(t1, t2, t3);
    real_type t39  = DEA(t1, t2, t3);
    real_type t40  = ABCD(t1, t2, t3);
    real_type t41  = t36 + t37 + t38 + t39 - t40;
    real_type t42  = ALIAS_EXTRA1_bound_DD(t41);
    real_type t43  = AEB_D_1(t1, t2, t3);
    real_type t44  = BEC_D_1(t1, t2, t3);
    real_type t45  = CED_D_1(t1, t2, t3);
    real_type t46  = DEA_D_1(t1, t2, t3);
    real_type t47  = ABCD_D_1(t1, t2, t3);
    real_type t48  = t43 + t44 + t45 + t46 - t47;
    real_type t49  = t48 * t48;
    real_type t51  = ALIAS_EXTRA1_bound_D(t41);
    real_type t52  = AEB_D_1_1(t1, t2, t3);
    real_type t53  = BEC_D_1_1(t1, t2, t3);
    real_type t54  = CED_D_1_1(t1, t2, t3);
    real_type t55  = DEA_D_1_1(t1, t2, t3);
    real_type t56  = ABCD_D_1_1(t1, t2, t3);
    real_type t59  = AOB(t1, t2, t3);
    real_type t60  = BOC(t1, t2, t3);
    real_type t61  = COD(t1, t2, t3);
    real_type t62  = DOA(t1, t2, t3);
    real_type t63  = t59 + t60 + t61 + t62 - t40;
    real_type t64  = ALIAS_EXTRA2_bound_DD(t63);
    real_type t65  = AOB_D_1(t1, t2, t3);
    real_type t66  = BOC_D_1(t1, t2, t3);
    real_type t67  = COD_D_1(t1, t2, t3);
    real_type t68  = DOA_D_1(t1, t2, t3);
    real_type t69  = t65 + t66 + t67 + t68 - t47;
    real_type t70  = t69 * t69;
    real_type t72  = ALIAS_EXTRA2_bound_D(t63);
    real_type t73  = AOB_D_1_1(t1, t2, t3);
    real_type t74  = BOC_D_1_1(t1, t2, t3);
    real_type t75  = COD_D_1_1(t1, t2, t3);
    real_type t76  = DOA_D_1_1(t1, t2, t3);
    result__[ 0   ] = t7 * t5 + t10 * t9 + t15 * t13 + t18 * t17 + t23 * t21 + t26 * t25 + t31 * t29 + t34 * t33 + t49 * t42 + (t52 + t53 + t54 + t55 - t56) * t51 + t70 * t64 + (t73 + t74 + t75 + t76 - t56) * t72;
    real_type t79  = Ay_D_2(t1, t2, t3);
    real_type t82  = Ay_D_1_2(t1, t2, t3);
    real_type t84  = By_D_2(t1, t2, t3);
    real_type t87  = By_D_1_2(t1, t2, t3);
    real_type t89  = Cy_D_2(t1, t2, t3);
    real_type t92  = Cy_D_1_2(t1, t2, t3);
    real_type t94  = Dy_D_2(t1, t2, t3);
    real_type t97  = Dy_D_1_2(t1, t2, t3);
    real_type t99  = AEB_D_2(t1, t2, t3);
    real_type t100 = BEC_D_2(t1, t2, t3);
    real_type t101 = CED_D_2(t1, t2, t3);
    real_type t102 = DEA_D_2(t1, t2, t3);
    real_type t103 = ABCD_D_2(t1, t2, t3);
    real_type t104 = t99 + t100 + t101 + t102 - t103;
    real_type t107 = AEB_D_1_2(t1, t2, t3);
    real_type t108 = BEC_D_1_2(t1, t2, t3);
    real_type t109 = CED_D_1_2(t1, t2, t3);
    real_type t110 = DEA_D_1_2(t1, t2, t3);
    real_type t111 = ABCD_D_1_2(t1, t2, t3);
    real_type t114 = AOB_D_2(t1, t2, t3);
    real_type t115 = BOC_D_2(t1, t2, t3);
    real_type t116 = COD_D_2(t1, t2, t3);
    real_type t117 = DOA_D_2(t1, t2, t3);
    real_type t118 = t114 + t115 + t116 + t117 - t103;
    real_type t121 = AOB_D_1_2(t1, t2, t3);
    real_type t122 = BOC_D_1_2(t1, t2, t3);
    real_type t123 = COD_D_1_2(t1, t2, t3);
    real_type t124 = DOA_D_1_2(t1, t2, t3);
    result__[ 1   ] = t6 * t79 * t5 + t82 * t9 + t14 * t84 * t13 + t87 * t17 + t22 * t89 * t21 + t92 * t25 + t30 * t94 * t29 + t97 * t33 + t48 * t104 * t42 + (t107 + t108 + t109 + t110 - t111) * t51 + t69 * t118 * t64 + (t121 + t122 + t123 + t124 - t111) * t72;
    real_type t127 = Ay_D_3(t1, t2, t3);
    real_type t128 = t127 * t5;
    real_type t130 = Ay_D_1_3(t1, t2, t3);
    real_type t132 = By_D_3(t1, t2, t3);
    real_type t133 = t132 * t13;
    real_type t135 = By_D_1_3(t1, t2, t3);
    real_type t137 = Cy_D_3(t1, t2, t3);
    real_type t138 = t137 * t21;
    real_type t140 = Cy_D_1_3(t1, t2, t3);
    real_type t142 = Dy_D_3(t1, t2, t3);
    real_type t143 = t142 * t29;
    real_type t145 = Dy_D_1_3(t1, t2, t3);
    real_type t147 = AEB_D_3(t1, t2, t3);
    real_type t148 = BEC_D_3(t1, t2, t3);
    real_type t149 = CED_D_3(t1, t2, t3);
    real_type t150 = DEA_D_3(t1, t2, t3);
    real_type t151 = ABCD_D_3(t1, t2, t3);
    real_type t152 = t147 + t148 + t149 + t150 - t151;
    real_type t153 = t152 * t42;
    real_type t155 = AEB_D_1_3(t1, t2, t3);
    real_type t156 = BEC_D_1_3(t1, t2, t3);
    real_type t157 = CED_D_1_3(t1, t2, t3);
    real_type t158 = DEA_D_1_3(t1, t2, t3);
    real_type t159 = ABCD_D_1_3(t1, t2, t3);
    real_type t162 = AOB_D_3(t1, t2, t3);
    real_type t163 = BOC_D_3(t1, t2, t3);
    real_type t164 = COD_D_3(t1, t2, t3);
    real_type t165 = DOA_D_3(t1, t2, t3);
    real_type t166 = t162 + t163 + t164 + t165 - t151;
    real_type t167 = t166 * t64;
    real_type t169 = AOB_D_1_3(t1, t2, t3);
    real_type t170 = BOC_D_1_3(t1, t2, t3);
    real_type t171 = COD_D_1_3(t1, t2, t3);
    real_type t172 = DOA_D_1_3(t1, t2, t3);
    result__[ 2   ] = t6 * t128 + t130 * t9 + t14 * t133 + t135 * t17 + t22 * t138 + t140 * t25 + t30 * t143 + t145 * t33 + t48 * t153 + (t155 + t156 + t157 + t158 - t159) * t51 + t69 * t167 + (t169 + t170 + t171 + t172 - t159) * t72;
    result__[ 3   ] = result__[1];
    real_type t175 = t79 * t79;
    real_type t177 = Ay_D_2_2(t1, t2, t3);
    real_type t179 = t84 * t84;
    real_type t181 = By_D_2_2(t1, t2, t3);
    real_type t183 = t89 * t89;
    real_type t185 = Cy_D_2_2(t1, t2, t3);
    real_type t187 = t94 * t94;
    real_type t189 = Dy_D_2_2(t1, t2, t3);
    real_type t191 = t104 * t104;
    real_type t193 = AEB_D_2_2(t1, t2, t3);
    real_type t194 = BEC_D_2_2(t1, t2, t3);
    real_type t195 = CED_D_2_2(t1, t2, t3);
    real_type t196 = DEA_D_2_2(t1, t2, t3);
    real_type t197 = ABCD_D_2_2(t1, t2, t3);
    real_type t200 = t118 * t118;
    real_type t202 = AOB_D_2_2(t1, t2, t3);
    real_type t203 = BOC_D_2_2(t1, t2, t3);
    real_type t204 = COD_D_2_2(t1, t2, t3);
    real_type t205 = DOA_D_2_2(t1, t2, t3);
    result__[ 4   ] = t175 * t5 + t177 * t9 + t179 * t13 + t181 * t17 + t183 * t21 + t185 * t25 + t187 * t29 + t189 * t33 + t191 * t42 + (t193 + t194 + t195 + t196 - t197) * t51 + t200 * t64 + (t202 + t203 + t204 + t205 - t197) * t72;
    real_type t209 = Ay_D_2_3(t1, t2, t3);
    real_type t212 = By_D_2_3(t1, t2, t3);
    real_type t215 = Cy_D_2_3(t1, t2, t3);
    real_type t218 = Dy_D_2_3(t1, t2, t3);
    real_type t221 = AEB_D_2_3(t1, t2, t3);
    real_type t222 = BEC_D_2_3(t1, t2, t3);
    real_type t223 = CED_D_2_3(t1, t2, t3);
    real_type t224 = DEA_D_2_3(t1, t2, t3);
    real_type t225 = ABCD_D_2_3(t1, t2, t3);
    real_type t229 = AOB_D_2_3(t1, t2, t3);
    real_type t230 = BOC_D_2_3(t1, t2, t3);
    real_type t231 = COD_D_2_3(t1, t2, t3);
    real_type t232 = DOA_D_2_3(t1, t2, t3);
    result__[ 5   ] = t79 * t128 + t209 * t9 + t84 * t133 + t212 * t17 + t89 * t138 + t215 * t25 + t94 * t143 + t218 * t33 + t104 * t153 + (t221 + t222 + t223 + t224 - t225) * t51 + t118 * t167 + (t229 + t230 + t231 + t232 - t225) * t72;
    real_type t235 = X__[iX_v];
    result__[ 6   ] = ALIAS_vel_bound_DD(t235);
    real_type t237 = P__[iP_T];
    real_type t238 = t237 * L__[iL_lambda1__xo];
    real_type t239 = sin(t3);
    real_type t242 = t237 * L__[iL_lambda2__xo];
    real_type t243 = cos(t3);
    result__[ 7   ] = -t239 * t238 + t243 * t242;
    real_type t246 = t237 * L__[iL_lambda5__xo];
    real_type t247 = X__[iX_phi];
    real_type t248 = tan(t247);
    real_type t249 = t248 * t248;
    real_type t250 = 1 + t249;
    real_type t252 = 1.0 / ModelPars[iM_len_a];
    result__[ 8   ] = t252 * t250 * t246;
    result__[ 9   ] = ALIAS_acc_bound_DD(X__[iX_a]);
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[5];
    result__[ 12  ] = result__[7];
    real_type t255 = t127 * t127;
    real_type t257 = Ay_D_3_3(t1, t2, t3);
    real_type t259 = t132 * t132;
    real_type t261 = By_D_3_3(t1, t2, t3);
    real_type t263 = t137 * t137;
    real_type t265 = Cy_D_3_3(t1, t2, t3);
    real_type t267 = t142 * t142;
    real_type t269 = Dy_D_3_3(t1, t2, t3);
    real_type t271 = t152 * t152;
    real_type t273 = AEB_D_3_3(t1, t2, t3);
    real_type t274 = BEC_D_3_3(t1, t2, t3);
    real_type t275 = CED_D_3_3(t1, t2, t3);
    real_type t276 = DEA_D_3_3(t1, t2, t3);
    real_type t277 = ABCD_D_3_3(t1, t2, t3);
    real_type t280 = t166 * t166;
    real_type t282 = AOB_D_3_3(t1, t2, t3);
    real_type t283 = BOC_D_3_3(t1, t2, t3);
    real_type t284 = COD_D_3_3(t1, t2, t3);
    real_type t285 = DOA_D_3_3(t1, t2, t3);
    result__[ 13  ] = t255 * t5 + t257 * t9 + t259 * t13 + t261 * t17 + t263 * t21 + t265 * t25 + t267 * t29 + t269 * t33 + t271 * t42 + (t273 + t274 + t275 + t276 - t277) * t51 + t280 * t64 + (t282 + t283 + t284 + t285 - t277) * t72 - t243 * t235 * t238 - t239 * t235 * t242;
    result__[ 14  ] = result__[8];
    real_type t292 = ALIAS_phi_bound_DD(t247);
    result__[ 15  ] = 2 * t252 * t250 * t248 * t235 * t246 + t292;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DHxDp_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DHxDp_numCols() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::DHxDp_nnz() const
  { return 4; }

  void
  ICLOCS_ParallelParking::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 3   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 4   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DHxDp_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_theta];
    real_type t3   = cos(t2);
    real_type t5   = L__[iL_lambda2__xo];
    real_type t6   = sin(t2);
    real_type t8   = L__[iL_lambda5__xo];
    real_type t10  = tan(X__[iX_phi]);
    real_type t13  = 1.0 / ModelPars[iM_len_a];
    result__[ 0   ] = t10 * t13 * t8 + t1 * t3 + t5 * t6 + L__[iL_lambda6__xo] * U__[iU_u2];
    result__[ 1   ] = L__[iL_lambda3__xo];
    real_type t18  = X__[iX_v];
    result__[ 2   ] = -t1 * t18 * t6 + t18 * t3 * t5;
    real_type t24  = t10 * t10;
    result__[ 3   ] = t13 * (1 + t24) * t18 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDp_sparse", 4, i_segment );
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
  ICLOCS_ParallelParking::Hu_numEqns() const
  { return 2; }

  void
  ICLOCS_ParallelParking::Hu_eval(
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
    real_type t2   = P__[iP_T];
    result__[ 0   ] = t2 * L__[iL_lambda4__xo];
    result__[ 1   ] = X__[iX_v] * t2 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DHuDx_numRows() const
  { return 2; }

  integer
  ICLOCS_ParallelParking::DHuDx_numCols() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DHuDx_nnz() const
  { return 1; }

  void
  ICLOCS_ParallelParking::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DHuDx_sparse(
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
    result__[ 0   ] = L__[iL_lambda6__xo] * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DHuDp_numRows() const
  { return 2; }

  integer
  ICLOCS_ParallelParking::DHuDp_numCols() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::DHuDp_nnz() const
  { return 2; }

  void
  ICLOCS_ParallelParking::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DHuDp_sparse(
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
    result__[ 0   ] = L__[iL_lambda4__xo];
    result__[ 1   ] = L__[iL_lambda6__xo] * X__[iX_v];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHuDp_sparse", 2, i_segment );
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
  ICLOCS_ParallelParking::Hp_numEqns() const
  { return 1; }

  void
  ICLOCS_ParallelParking::Hp_eval(
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
    real_type t2   = X__[iX_v];
    real_type t4   = X__[iX_theta];
    real_type t5   = cos(t4);
    real_type t9   = sin(t4);
    real_type t20  = tan(X__[iX_phi]);
    result__[ 0   ] = t5 * t2 * L__[iL_lambda1__xo] + t9 * t2 * L__[iL_lambda2__xo] + L__[iL_lambda3__xo] * X__[iX_a] + L__[iL_lambda4__xo] * U__[iU_u1] + 1.0 / ModelPars[iM_len_a] * t20 * t2 * L__[iL_lambda5__xo] + U__[iU_u2] * t2 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DHpDp_numRows() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::DHpDp_numCols() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::DHpDp_nnz() const
  { return 0; }

  void
  ICLOCS_ParallelParking::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  ICLOCS_ParallelParking::eta_numEqns() const
  { return 6; }

  void
  ICLOCS_ParallelParking::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DetaDx_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DetaDx_numCols() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DetaDx_nnz() const
  { return 0; }

  void
  ICLOCS_ParallelParking::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DetaDp_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DetaDp_numCols() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::DetaDp_nnz() const
  { return 0; }

  void
  ICLOCS_ParallelParking::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DetaDp_sparse(
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
  ICLOCS_ParallelParking::nu_numEqns() const
  { return 6; }

  void
  ICLOCS_ParallelParking::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DnuDx_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DnuDx_numCols() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DnuDx_nnz() const
  { return 0; }

  void
  ICLOCS_ParallelParking::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::DnuDp_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::DnuDp_numCols() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::DnuDp_nnz() const
  { return 0; }

  void
  ICLOCS_ParallelParking::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_ParallelParking_Methods_AdjointODE.cc
