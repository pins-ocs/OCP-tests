/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 20/12/2021                                       |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  ICLOCS_TwoLinkRobotArm::Hx_numEqns() const
  { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::Hx_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t7   = cos(t4);
    real_type t8   = X__[iX_omega__alpha];
    real_type t10  = t5 * t5;
    real_type t12  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t10;
    real_type t13  = 1.0 / t12;
    real_type t18  = t2 * L__[iL_lambda2__xo];
    real_type t23  = t2 * L__[iL_lambda3__xo];
    result__[ 0   ] = 9.0 / 2.0 * t13 * t8 * t7 * t5 * t3 - 7 * t13 * t8 * t18 - t23 + t2 * L__[iL_lambda4__xo];
    real_type t26  = X__[iX_omega__beta];
    result__[ 1   ] = 4 * t13 * t26 * t3 - 9.0 / 2.0 * t13 * t26 * t7 * t5 * t18 + t23;
    real_type t35  = t7 * t7;
    real_type t36  = t8 * t8;
    real_type t41  = U__[iU_u2];
    real_type t47  = t7 * t5;
    real_type t50  = t26 * t26;
    real_type t52  = U__[iU_u1];
    real_type t59  = t12 * t12;
    real_type t62  = t7 * t5 / t59;
    real_type t69  = t52 - t41;
    result__[ 2   ] = t13 * (9.0 / 4.0 * t36 * t35 - 9.0 / 4.0 * t36 * t10 + 3.0 / 2.0 * t41 * t5) * t3 - 9.0 / 2.0 * t62 * (9.0 / 4.0 * t36 * t47 + 2 * t50 + 4.0 / 3.0 * t52 - 4.0 / 3.0 * t41 - 3.0 / 2.0 * t41 * t7) * t3 - t13 * (9.0 / 4.0 * t50 * t35 - 9.0 / 4.0 * t50 * t10 - 3.0 / 2.0 * t69 * t5) * t18 + 9.0 / 2.0 * t62 * (9.0 / 4.0 * t50 * t47 + 7.0 / 2.0 * t36 - 7.0 / 3.0 * t41 + 3.0 / 2.0 * t69 * t7) * t18;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DHxDx_numRows() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DHxDx_numCols() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DHxDx_nnz() const
  { return 7; }

  void
  ICLOCS_TwoLinkRobotArm::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
  }

  void
  ICLOCS_TwoLinkRobotArm::DHxDx_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = cos(t4);
    real_type t7   = t6 * t5;
    real_type t8   = t5 * t5;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t12  = t11 * t7;
    real_type t16  = t2 * L__[iL_lambda2__xo];
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
    result__[ 2   ] = 4 * t11 * t3 - 9.0 / 2.0 * t12 * t16;
    real_type t44  = X__[iX_omega__beta];
    real_type t47  = 18 * t37 * t44 * t3;
    real_type t48  = t44 * t19;
    real_type t52  = t44 * t8;
    real_type t59  = 0.81e2 / 4.0 * t31 * t48 * t8 * t16;
    result__[ 3   ] = -t47 - 9.0 / 2.0 * t11 * t48 * t16 + 9.0 / 2.0 * t11 * t52 * t16 + t59;
    result__[ 4   ] = t11 * (9.0 / 2.0 * t21 - 9.0 / 2.0 * t25) * t3 - t34 + t39;
    result__[ 5   ] = -t47 - t11 * (9.0 / 2.0 * t48 - 9.0 / 2.0 * t52) * t16 + t59;
    real_type t68  = t20 * t20;
    real_type t69  = t68 * t7;
    real_type t71  = U__[iU_u2];
    real_type t73  = 3.0 / 2.0 * t71 * t6;
    real_type t88  = t44 * t44;
    real_type t90  = U__[iU_u1];
    real_type t93  = 9.0 / 4.0 * t69 + 2 * t88 + 4.0 / 3.0 * t90 - 4.0 / 3.0 * t71 - t73;
    real_type t98  = t19 * t8 / t30 / t10;
    real_type t101 = t31 * t93;
    real_type t108 = t88 * t7;
    real_type t110 = t90 - t71;
    real_type t112 = 3.0 / 2.0 * t110 * t6;
    real_type t129 = 9.0 / 4.0 * t108 + 7.0 / 2.0 * t68 - 7.0 / 3.0 * t71 + t112;
    real_type t133 = t31 * t129;
    result__[ 6   ] = t11 * (-9 * t69 + t73) * t3 - 9 * t37 * (9.0 / 4.0 * t68 * t19 - 9.0 / 4.0 * t68 * t8 + 3.0 / 2.0 * t71 * t5) * t3 + 0.81e2 / 2.0 * t98 * t93 * t3 - 9.0 / 2.0 * t19 * t101 * t3 + 9.0 / 2.0 * t8 * t101 * t3 - t11 * (-9 * t108 - t112) * t16 + 9 * t37 * (9.0 / 4.0 * t88 * t19 - 9.0 / 4.0 * t88 * t8 - 3.0 / 2.0 * t110 * t5) * t16 - 0.81e2 / 2.0 * t98 * t129 * t16 + 9.0 / 2.0 * t19 * t133 * t16 - 9.0 / 2.0 * t8 * t133 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DHxDp_numRows() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DHxDp_numCols() const
  { return 1; }

  integer
  ICLOCS_TwoLinkRobotArm::DHxDp_nnz() const
  { return 3; }

  void
  ICLOCS_TwoLinkRobotArm::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DHxDp_sparse(
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
    real_type t3   = sin(t2);
    real_type t5   = cos(t2);
    real_type t6   = X__[iX_omega__alpha];
    real_type t8   = t3 * t3;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t15  = L__[iL_lambda2__xo];
    real_type t19  = L__[iL_lambda3__xo];
    result__[ 0   ] = 9.0 / 2.0 * t11 * t6 * t5 * t3 * t1 - 7 * t11 * t6 * t15 - t19 + L__[iL_lambda4__xo];
    real_type t21  = X__[iX_omega__beta];
    result__[ 1   ] = 4 * t11 * t21 * t1 - 9.0 / 2.0 * t11 * t21 * t5 * t3 * t15 + t19;
    real_type t30  = t5 * t5;
    real_type t31  = t6 * t6;
    real_type t36  = U__[iU_u2];
    real_type t42  = t5 * t3;
    real_type t45  = t21 * t21;
    real_type t47  = U__[iU_u1];
    real_type t54  = t10 * t10;
    real_type t57  = t5 * t3 / t54;
    real_type t64  = t47 - t36;
    result__[ 2   ] = t11 * (9.0 / 4.0 * t31 * t30 - 9.0 / 4.0 * t31 * t8 + 3.0 / 2.0 * t36 * t3) * t1 - 9.0 / 2.0 * t57 * (9.0 / 4.0 * t31 * t42 + 2 * t45 + 4.0 / 3.0 * t47 - 4.0 / 3.0 * t36 - 3.0 / 2.0 * t36 * t5) * t1 - t11 * (9.0 / 4.0 * t45 * t30 - 9.0 / 4.0 * t45 * t8 - 3.0 / 2.0 * t64 * t3) * t15 + 9.0 / 2.0 * t57 * (9.0 / 4.0 * t45 * t42 + 7.0 / 2.0 * t31 - 7.0 / 3.0 * t36 + 3.0 / 2.0 * t64 * t5) * t15;
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
  ICLOCS_TwoLinkRobotArm::Hu_numEqns() const
  { return 2; }

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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DHuDx_numRows() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DHuDx_numCols() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DHuDx_nnz() const
  { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DHuDx_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t8   = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t6;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = cos(t4);
    real_type t13  = t12 * t5 * t10;
    real_type t17  = t2 * L__[iL_lambda2__xo];
    real_type t19  = 1.0 / t8 * t5;
    real_type t21  = 3.0 / 2.0 * t19 * t17;
    real_type t22  = t12 * t12;
    result__[ 0   ] = -6 * t13 * t3 + t21 + 0.27e2 / 4.0 * t5 * t10 * t22 * t17;
    real_type t29  = 3.0 / 2.0 * t12;
    result__[ 1   ] = 3.0 / 2.0 * t19 * t3 - 9.0 / 2.0 * t13 * (-4.0 / 3.0 - t29) * t3 - t21 + 9.0 / 2.0 * t13 * (-7.0 / 3.0 - t29) * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DHuDp_numRows() const
  { return 2; }

  integer
  ICLOCS_TwoLinkRobotArm::DHuDp_numCols() const
  { return 1; }

  integer
  ICLOCS_TwoLinkRobotArm::DHuDp_nnz() const
  { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DHuDp_sparse(
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
    real_type t1   = ModelPars[iM_rho];
    real_type t5   = L__[iL_lambda1__xo];
    real_type t6   = X__[iX_theta];
    real_type t7   = sin(t6);
    real_type t8   = t7 * t7;
    real_type t11  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t8);
    real_type t14  = L__[iL_lambda2__xo];
    real_type t15  = cos(t6);
    result__[ 0   ] = 2 * U__[iU_u1] * t1 + 4.0 / 3.0 * t11 * t5 - 3.0 / 2.0 * t11 * t15 * t14;
    real_type t22  = 3.0 / 2.0 * t15;
    result__[ 1   ] = 2 * U__[iU_u2] * t1 + t11 * (-4.0 / 3.0 - t22) * t5 - t11 * (-7.0 / 3.0 - t22) * t14;
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
  ICLOCS_TwoLinkRobotArm::Hp_numEqns() const
  { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::Hp_eval(
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
    real_type t2   = U__[iU_u1];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_u2];
    real_type t5   = t4 * t4;
    real_type t9   = X__[iX_theta];
    real_type t10  = sin(t9);
    real_type t11  = cos(t9);
    real_type t12  = t11 * t10;
    real_type t13  = X__[iX_omega__alpha];
    real_type t14  = t13 * t13;
    real_type t17  = X__[iX_omega__beta];
    real_type t18  = t17 * t17;
    real_type t26  = t10 * t10;
    real_type t29  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t26);
    result__[ 0   ] = (t3 + t5) * ModelPars[iM_rho] + t29 * (9.0 / 4.0 * t14 * t12 + 2 * t18 + 4.0 / 3.0 * t2 - 4.0 / 3.0 * t4 - 3.0 / 2.0 * t4 * t11) * L__[iL_lambda1__xo] - t29 * (9.0 / 4.0 * t18 * t12 + 7.0 / 2.0 * t14 - 7.0 / 3.0 * t4 + 3.0 / 2.0 * (t2 - t4) * t11) * L__[iL_lambda2__xo] + (t17 - t13) * L__[iL_lambda3__xo] + t13 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DHpDp_numRows() const
  { return 1; }

  integer
  ICLOCS_TwoLinkRobotArm::DHpDp_numCols() const
  { return 1; }

  integer
  ICLOCS_TwoLinkRobotArm::DHpDp_nnz() const
  { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DHpDp_sparse(
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
  ICLOCS_TwoLinkRobotArm::eta_numEqns() const
  { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DetaDx_numRows() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DetaDx_numCols() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DetaDx_nnz() const
  { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DetaDp_numRows() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DetaDp_numCols() const
  { return 1; }

  integer
  ICLOCS_TwoLinkRobotArm::DetaDp_nnz() const
  { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DetaDp_sparse(
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
  ICLOCS_TwoLinkRobotArm::nu_numEqns() const
  { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DnuDx_numRows() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DnuDx_numCols() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DnuDx_nnz() const
  { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_TwoLinkRobotArm::DnuDp_numRows() const
  { return 4; }

  integer
  ICLOCS_TwoLinkRobotArm::DnuDp_numCols() const
  { return 1; }

  integer
  ICLOCS_TwoLinkRobotArm::DnuDp_nnz() const
  { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc
