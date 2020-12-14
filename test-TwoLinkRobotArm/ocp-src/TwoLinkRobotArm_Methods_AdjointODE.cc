/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods.cc                                     |
 |                                                                       |
 |  version: 1.0   date 14/12/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "TwoLinkRobotArm.hh"
#include "TwoLinkRobotArm_Pars.hh"

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


namespace TwoLinkRobotArmDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  TwoLinkRobotArm::Hx_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::Hx_eval(
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    real_type t3   = t2 * L__[0];
    real_type t4   = X__[2];
    real_type t5   = sin(t4);
    real_type t7   = cos(t4);
    real_type t8   = X__[0];
    real_type t10  = t5 * t5;
    real_type t12  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t10;
    real_type t13  = 1.0 / t12;
    real_type t18  = t2 * L__[1];
    real_type t24  = t2 * L__[2];
    result__[ 0   ] = 9.0 / 2.0 * t13 * t8 * t7 * t5 * t3 - 7 * t13 * t8 * t5 * t18 - t24 + t2 * L__[3];
    real_type t27  = X__[1];
    result__[ 1   ] = 4 * t13 * t27 * t5 * t3 - 9.0 / 2.0 * t13 * t27 * t7 * t5 * t18 + t24;
    real_type t37  = t8 * t8;
    real_type t40  = t27 * t27;
    real_type t42  = 9.0 / 4.0 * t37 * t7 + 2 * t40;
    real_type t46  = U__[1];
    real_type t53  = U__[0];
    real_type t60  = t12 * t12;
    real_type t63  = t7 * t5 / t60;
    real_type t69  = 7.0 / 2.0 * t37 + 9.0 / 4.0 * t40 * t7;
    real_type t73  = t53 - t46;
    result__[ 2   ] = t13 * (t42 * t7 - 9.0 / 4.0 * t37 * t10 + 3.0 / 2.0 * t46 * t5) * t3 - 9.0 / 2.0 * t63 * (t42 * t5 + 4.0 / 3.0 * t53 - 4.0 / 3.0 * t46 - 3.0 / 2.0 * t46 * t7) * t3 - t13 * (t69 * t7 - 9.0 / 4.0 * t40 * t10 - 3.0 / 2.0 * t73 * t5) * t18 + 9.0 / 2.0 * t63 * (t69 * t5 - 7.0 / 3.0 * t46 + 3.0 / 2.0 * t73 * t7) * t18;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHxDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHxDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHxDx_nnz() const
  { return 7; }

  void
  TwoLinkRobotArm::DHxDx_pattern(
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
  TwoLinkRobotArm::DHxDx_sparse(
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    real_type t3   = t2 * L__[0];
    real_type t4   = X__[2];
    real_type t5   = sin(t4);
    real_type t6   = cos(t4);
    real_type t7   = t6 * t5;
    real_type t8   = t5 * t5;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t12  = t11 * t7;
    real_type t16  = t2 * L__[1];
    real_type t17  = t11 * t5;
    result__[ 0   ] = 9.0 / 2.0 * t12 * t3 - 7 * t17 * t16;
    real_type t20  = t6 * t6;
    real_type t21  = X__[0];
    real_type t22  = t21 * t20;
    real_type t26  = t21 * t8;
    real_type t30  = t8 * t3;
    real_type t31  = t10 * t10;
    real_type t32  = 1.0 / t31;
    real_type t35  = 0.81e2 / 4.0 * t32 * t22 * t30;
    real_type t39  = 7 * t11 * t21 * t6 * t16;
    real_type t40  = t8 * t16;
    real_type t44  = 0.63e2 / 2.0 * t6 * t32 * t21 * t40;
    result__[ 1   ] = 9.0 / 2.0 * t11 * t22 * t3 - 9.0 / 2.0 * t11 * t26 * t3 - t35 - t39 + t44;
    result__[ 2   ] = 4 * t17 * t3 - 9.0 / 2.0 * t12 * t16;
    real_type t49  = X__[1];
    real_type t53  = 4 * t11 * t49 * t6 * t3;
    real_type t57  = 18 * t6 * t32 * t49 * t30;
    real_type t58  = t49 * t20;
    real_type t62  = t49 * t8;
    real_type t68  = 0.81e2 / 4.0 * t32 * t58 * t40;
    result__[ 3   ] = t53 - t57 - 9.0 / 2.0 * t11 * t58 * t16 + 9.0 / 2.0 * t11 * t62 * t16 + t68;
    result__[ 4   ] = t11 * (9.0 / 2.0 * t22 - 9.0 / 2.0 * t26) * t3 - t35 - t39 + t44;
    result__[ 5   ] = t53 - t57 - t11 * (9.0 / 2.0 * t58 - 9.0 / 2.0 * t62) * t16 + t68;
    real_type t77  = t21 * t21;
    real_type t80  = t49 * t49;
    real_type t82  = 9.0 / 4.0 * t77 * t6 + 2 * t80;
    real_type t83  = t82 * t5;
    real_type t86  = U__[1];
    real_type t88  = 3.0 / 2.0 * t86 * t6;
    real_type t100 = t6 * t5 * t32;
    real_type t103 = U__[0];
    real_type t106 = t83 + 4.0 / 3.0 * t103 - 4.0 / 3.0 * t86 - t88;
    real_type t111 = t20 * t8 / t31 / t10;
    real_type t114 = t32 * t106;
    real_type t124 = 7.0 / 2.0 * t77 + 9.0 / 4.0 * t80 * t6;
    real_type t125 = t124 * t5;
    real_type t128 = t103 - t86;
    real_type t130 = 3.0 / 2.0 * t128 * t6;
    real_type t144 = t125 - 7.0 / 3.0 * t86 + t130;
    real_type t148 = t32 * t144;
    result__[ 6   ] = t11 * (-t83 - 0.27e2 / 4.0 * t77 * t7 + t88) * t3 - 9 * t100 * (t82 * t6 - 9.0 / 4.0 * t77 * t8 + 3.0 / 2.0 * t86 * t5) * t3 + 0.81e2 / 2.0 * t111 * t106 * t3 - 9.0 / 2.0 * t20 * t114 * t3 + 9.0 / 2.0 * t8 * t114 * t3 - t11 * (-t125 - 0.27e2 / 4.0 * t80 * t7 - t130) * t16 + 9 * t100 * (t124 * t6 - 9.0 / 4.0 * t80 * t8 - 3.0 / 2.0 * t128 * t5) * t16 - 0.81e2 / 2.0 * t111 * t144 * t16 + 9.0 / 2.0 * t20 * t148 * t16 - 9.0 / 2.0 * t8 * t148 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHxDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHxDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHxDp_nnz() const
  { return 3; }

  void
  TwoLinkRobotArm::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHxDp_sparse(
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = L__[0];
    real_type t2   = X__[2];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = cos(t2);
    real_type t6   = X__[0];
    real_type t8   = t3 * t3;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t15  = L__[1];
    real_type t16  = t3 * t15;
    real_type t20  = L__[2];
    result__[ 0   ] = 9.0 / 2.0 * t11 * t6 * t5 * t4 - 7 * t11 * t6 * t16 - t20 + L__[3];
    real_type t22  = X__[1];
    result__[ 1   ] = 4 * t11 * t22 * t4 - 9.0 / 2.0 * t11 * t22 * t5 * t16 + t20;
    real_type t30  = t6 * t6;
    real_type t33  = t22 * t22;
    real_type t35  = 9.0 / 4.0 * t30 * t5 + 2 * t33;
    real_type t39  = U__[1];
    real_type t46  = U__[0];
    real_type t53  = t10 * t10;
    real_type t56  = t5 * t3 / t53;
    real_type t62  = 7.0 / 2.0 * t30 + 9.0 / 4.0 * t33 * t5;
    real_type t66  = t46 - t39;
    result__[ 2   ] = t11 * (t35 * t5 - 9.0 / 4.0 * t30 * t8 + 3.0 / 2.0 * t39 * t3) * t1 - 9.0 / 2.0 * t56 * (t35 * t3 + 4.0 / 3.0 * t46 - 4.0 / 3.0 * t39 - 3.0 / 2.0 * t39 * t5) * t1 - t11 * (t62 * t5 - 9.0 / 4.0 * t33 * t8 - 3.0 / 2.0 * t66 * t3) * t15 + 9.0 / 2.0 * t56 * (t62 * t3 - 7.0 / 3.0 * t39 + 3.0 / 2.0 * t66 * t5) * t15;
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
  TwoLinkRobotArm::Hu_numEqns() const
  { return 2; }

  void
  TwoLinkRobotArm::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    real_type t3   = t2 * L__[0];
    real_type t4   = X__[2];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t9   = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t6);
    real_type t13  = t2 * L__[1];
    real_type t14  = cos(t4);
    result__[ 0   ] = 4.0 / 3.0 * t9 * t3 - 3.0 / 2.0 * t9 * t14 * t13;
    real_type t18  = 3.0 / 2.0 * t14;
    result__[ 1   ] = t9 * (-4.0 / 3.0 - t18) * t3 - t9 * (-7.0 / 3.0 - t18) * t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHuDx_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DHuDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DHuDx_nnz() const
  { return 2; }

  void
  TwoLinkRobotArm::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = P__[0];
    real_type t3   = t2 * L__[0];
    real_type t4   = X__[2];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t8   = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t6;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = cos(t4);
    real_type t13  = t12 * t5 * t10;
    real_type t17  = t2 * L__[1];
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
  TwoLinkRobotArm::DHuDp_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DHuDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHuDp_nnz() const
  { return 2; }

  void
  TwoLinkRobotArm::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = L__[0];
    real_type t2   = X__[2];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t3;
    real_type t7   = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t4);
    real_type t10  = L__[1];
    real_type t11  = cos(t2);
    result__[ 0   ] = 4.0 / 3.0 * t7 * t1 - 3.0 / 2.0 * t7 * t11 * t10;
    real_type t15  = 3.0 / 2.0 * t11;
    result__[ 1   ] = t7 * (-4.0 / 3.0 - t15) * t1 - t7 * (-7.0 / 3.0 - t15) * t10;
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
  TwoLinkRobotArm::Hp_numEqns() const
  { return 1; }

  void
  TwoLinkRobotArm::Hp_eval(
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[2];
    real_type t3   = sin(t2);
    real_type t4   = cos(t2);
    real_type t5   = X__[0];
    real_type t6   = t5 * t5;
    real_type t9   = X__[1];
    real_type t10  = t9 * t9;
    real_type t14  = U__[0];
    real_type t16  = U__[1];
    real_type t22  = t3 * t3;
    real_type t25  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t22);
    result__[ 0   ] = t25 * ((9.0 / 4.0 * t6 * t4 + 2 * t10) * t3 + 4.0 / 3.0 * t14 - 4.0 / 3.0 * t16 - 3.0 / 2.0 * t16 * t4) * L__[0] - t25 * ((7.0 / 2.0 * t6 + 9.0 / 4.0 * t10 * t4) * t3 - 7.0 / 3.0 * t16 + 3.0 / 2.0 * (t14 - t16) * t4) * L__[1] + (t9 - t5) * L__[2] + t5 * L__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DHpDp_numRows() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHpDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DHpDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DHpDp_sparse(
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
  TwoLinkRobotArm::eta_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = L__[2];
    result__[ 3   ] = L__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DetaDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DetaDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DetaDx_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DetaDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DetaDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DetaDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DetaDp_sparse(
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
  TwoLinkRobotArm::nu_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DnuDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DnuDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::DnuDx_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DnuDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::DnuDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::DnuDp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: TwoLinkRobotArm_Methods.cc
