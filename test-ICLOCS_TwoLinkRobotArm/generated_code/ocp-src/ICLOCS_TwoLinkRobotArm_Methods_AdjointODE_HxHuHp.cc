/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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


namespace ICLOCS_TwoLinkRobotArmDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::Hxp_numEqns() const { return 5; }

  void
  ICLOCS_TwoLinkRobotArm::Hxp_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t7   = cos(t4);
    real_type t8   = X__[iX_omega__alpha];
    real_type t10  = t5 * t5;
    real_type t12  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t10;
    real_type t13  = 1.0 / t12;
    real_type t17  = L__[iL_lambda2__xo];
    real_type t18  = t2 * t17;
    real_type t22  = L__[iL_lambda3__xo];
    real_type t23  = t2 * t22;
    real_type t24  = L__[iL_lambda4__xo];
    result__[ 0   ] = 9.0 / 2.0 * t13 * t8 * t7 * t5 * t3 - 7 * t13 * t8 * t18 - t23 + t2 * t24;
    real_type t26  = X__[iX_omega__beta];
    result__[ 1   ] = 4 * t13 * t26 * t3 - 9.0 / 2.0 * t13 * t26 * t7 * t5 * t18 + t23;
    real_type t35  = t7 * t7;
    real_type t36  = t8 * t8;
    real_type t41  = U__[iU_u2];
    real_type t47  = t7 * t5;
    real_type t50  = t26 * t26;
    real_type t52  = U__[iU_u1];
    real_type t57  = 9.0 / 4.0 * t36 * t47 + 2 * t50 + 4.0 / 3.0 * t52 - 4.0 / 3.0 * t41 - 3.0 / 2.0 * t41 * t7;
    real_type t59  = t12 * t12;
    real_type t62  = t7 * t5 / t59;
    real_type t69  = t52 - t41;
    real_type t81  = 9.0 / 4.0 * t50 * t47 + 7.0 / 2.0 * t36 - 7.0 / 3.0 * t41 + 3.0 / 2.0 * t69 * t7;
    result__[ 2   ] = t13 * (9.0 / 4.0 * t36 * t35 - 9.0 / 4.0 * t36 * t10 + 3.0 / 2.0 * t41 * t5) * t3 - 9.0 / 2.0 * t62 * t57 * t3 - t13 * (9.0 / 4.0 * t50 * t35 - 9.0 / 4.0 * t50 * t10 - 3.0 / 2.0 * t69 * t5) * t18 + 9.0 / 2.0 * t62 * t81 * t18;
    result__[ 3   ] = 0;
    real_type t86  = t52 * t52;
    real_type t87  = t41 * t41;
    result__[ 4   ] = (t86 + t87) * ModelPars[iM_rho] + t13 * t57 * t1 - t13 * t81 * t17 + (t26 - t8) * t22 + t8 * t24;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DHxpDxpu_numRows() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DHxpDxpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::DHxpDxpu_nnz()     const { return 17; }

  void
  ICLOCS_TwoLinkRobotArm::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 4   ;
    iIndex[10] = 2   ; jIndex[10] = 5   ;
    iIndex[11] = 2   ; jIndex[11] = 6   ;
    iIndex[12] = 4   ; jIndex[12] = 0   ;
    iIndex[13] = 4   ; jIndex[13] = 1   ;
    iIndex[14] = 4   ; jIndex[14] = 2   ;
    iIndex[15] = 4   ; jIndex[15] = 5   ;
    iIndex[16] = 4   ; jIndex[16] = 6   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::DHxpDxpu_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = cos(t4);
    real_type t7   = t6 * t5;
    real_type t8   = t5 * t5;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t12  = t11 * t7;
    real_type t15  = L__[iL_lambda2__xo];
    real_type t16  = t2 * t15;
    result__[ 0   ] = 9.0 / 2.0 * t12 * t3 - 7 * t11 * t16;
    real_type t19  = t6 * t6;
    real_type t20  = X__[iX_omega__alpha];
    real_type t21  = t20 * t19;
    real_type t25  = t20 * t8;
    real_type t30  = t10 * t10;
    real_type t31  = 1.0 / t30;
    real_type t34  = 0.81e2 / 4.0 * t31 * t21 * t8 * t3;
    real_type t37  = t6 * t5 * t31;
    real_type t39  = 0.63e2 / 2.0 * t37 * t20 * t16;
    result__[ 1   ] = 9.0 / 2.0 * t11 * t21 * t3 - 9.0 / 2.0 * t11 * t25 * t3 - t34 + t39;
    real_type t48  = L__[iL_lambda3__xo];
    result__[ 2   ] = 9.0 / 2.0 * t11 * t20 * t6 * t5 * t1 - 7 * t11 * t20 * t15 - t48 + L__[iL_lambda4__xo];
    result__[ 3   ] = 4 * t11 * t3 - 9.0 / 2.0 * t12 * t16;
    real_type t54  = X__[iX_omega__beta];
    real_type t57  = 18 * t37 * t54 * t3;
    real_type t58  = t54 * t19;
    real_type t62  = t54 * t8;
    real_type t69  = 0.81e2 / 4.0 * t31 * t58 * t8 * t16;
    result__[ 4   ] = -t57 - 9.0 / 2.0 * t11 * t58 * t16 + 9.0 / 2.0 * t11 * t62 * t16 + t69;
    result__[ 5   ] = 4 * t11 * t54 * t1 - 9.0 / 2.0 * t11 * t54 * t6 * t5 * t15 + t48;
    result__[ 6   ] = t11 * (9.0 / 2.0 * t21 - 9.0 / 2.0 * t25) * t3 - t34 + t39;
    result__[ 7   ] = -t57 - t11 * (9.0 / 2.0 * t58 - 9.0 / 2.0 * t62) * t16 + t69;
    real_type t86  = t20 * t20;
    real_type t87  = t86 * t7;
    real_type t89  = U__[iU_u2];
    real_type t91  = 3.0 / 2.0 * t89 * t6;
    real_type t101 = 9.0 / 4.0 * t86 * t19 - 9.0 / 4.0 * t86 * t8 + 3.0 / 2.0 * t89 * t5;
    real_type t106 = t54 * t54;
    real_type t108 = U__[iU_u1];
    real_type t111 = 9.0 / 4.0 * t87 + 2 * t106 + 4.0 / 3.0 * t108 - 4.0 / 3.0 * t89 - t91;
    real_type t116 = t19 * t8 / t30 / t10;
    real_type t119 = t31 * t111;
    real_type t126 = t106 * t7;
    real_type t128 = t108 - t89;
    real_type t130 = 3.0 / 2.0 * t128 * t6;
    real_type t140 = 9.0 / 4.0 * t106 * t19 - 9.0 / 4.0 * t106 * t8 - 3.0 / 2.0 * t128 * t5;
    real_type t147 = 9.0 / 4.0 * t126 + 7.0 / 2.0 * t86 - 7.0 / 3.0 * t89 + t130;
    real_type t151 = t31 * t147;
    result__[ 8   ] = t11 * (-9 * t87 + t91) * t3 - 9 * t37 * t101 * t3 + 0.81e2 / 2.0 * t116 * t111 * t3 - 9.0 / 2.0 * t19 * t119 * t3 + 9.0 / 2.0 * t8 * t119 * t3 - t11 * (-9 * t126 - t130) * t16 + 9 * t37 * t140 * t16 - 0.81e2 / 2.0 * t116 * t147 * t16 + 9.0 / 2.0 * t19 * t151 * t16 - 9.0 / 2.0 * t8 * t151 * t16;
    result__[ 9   ] = t11 * t101 * t1 - 9.0 / 2.0 * t37 * t111 * t1 - t11 * t140 * t15 + 9.0 / 2.0 * t37 * t147 * t15;
    real_type t170 = t11 * t5;
    real_type t172 = 3.0 / 2.0 * t170 * t16;
    result__[ 10  ] = -6 * t37 * t3 + t172 + 0.27e2 / 4.0 * t5 * t31 * t19 * t16;
    real_type t179 = 3.0 / 2.0 * t6;
    real_type t180 = -4.0 / 3.0 - t179;
    real_type t184 = -7.0 / 3.0 - t179;
    result__[ 11  ] = 3.0 / 2.0 * t170 * t3 - 9.0 / 2.0 * t37 * t180 * t3 - t172 + 9.0 / 2.0 * t37 * t184 * t16;
    result__[ 12  ] = result__[2];
    result__[ 13  ] = result__[5];
    result__[ 14  ] = result__[9];
    real_type t188 = ModelPars[iM_rho];
    result__[ 15  ] = 2 * t108 * t188 + 4.0 / 3.0 * t11 * t1 - 3.0 / 2.0 * t11 * t6 * t15;
    result__[ 16  ] = t11 * t180 * t1 - t11 * t184 * t15 + 2 * t89 * t188;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 17, i_segment );
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

  integer ICLOCS_TwoLinkRobotArm::Hu_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::Hu_eval(
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
    real_type t3   = t2 * ModelPars[iM_rho];
    real_type t8   = t2 * L__[iL_lambda1__xo];
    real_type t9   = X__[iX_theta];
    real_type t10  = sin(t9);
    real_type t11  = t10 * t10;
    real_type t14  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t11);
    real_type t18  = t2 * L__[iL_lambda2__xo];
    real_type t19  = cos(t9);
    result__[ 0   ] = 2 * U__[iU_u1] * t3 + 4.0 / 3.0 * t14 * t8 - 3.0 / 2.0 * t14 * t19 * t18;
    real_type t26  = 3.0 / 2.0 * t19;
    result__[ 1   ] = 2 * U__[iU_u2] * t3 + t14 * (-4.0 / 3.0 - t26) * t8 - t14 * (-7.0 / 3.0 - t26) * t18;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc
