/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods.cc                                     |
 |                                                                       |
 |  version: 1.0   date 28/3/2020                                        |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  TwoLinkRobotArm::rhs_ode_numEqns() const
  { return 4; }

  void
  TwoLinkRobotArm::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[0];
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
    result__[ 0   ] = t25 * ((9.0 / 4.0 * t6 * t4 + 2 * t10) * t3 + 4.0 / 3.0 * t14 - 4.0 / 3.0 * t16 - 3.0 / 2.0 * t16 * t4) * t1;
    result__[ 1   ] = -t25 * ((7.0 / 2.0 * t6 + 9.0 / 4.0 * t10 * t4) * t3 - 7.0 / 3.0 * t16 + 3.0 / 2.0 * (t14 - t16) * t4) * t1;
    result__[ 2   ] = (t9 - t5) * t1;
    result__[ 3   ] = t5 * t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::Drhs_odeDx_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::Drhs_odeDx_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::Drhs_odeDx_nnz() const
  { return 9; }

  void
  TwoLinkRobotArm::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 1   ;
    iIndex[ 8  ] = 3   ; jIndex[ 8  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[0];
    real_type t2   = X__[2];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = cos(t2);
    real_type t6   = X__[0];
    real_type t8   = t3 * t3;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    result__[ 0   ] = 9.0 / 2.0 * t11 * t6 * t5 * t4;
    real_type t14  = X__[1];
    result__[ 1   ] = 4 * t11 * t14 * t4;
    real_type t17  = t6 * t6;
    real_type t20  = t14 * t14;
    real_type t22  = 9.0 / 4.0 * t17 * t5 + 2 * t20;
    real_type t26  = U__[1];
    real_type t33  = U__[0];
    real_type t40  = t10 * t10;
    real_type t43  = t5 * t3 / t40;
    result__[ 2   ] = t11 * (t22 * t5 - 9.0 / 4.0 * t17 * t8 + 3.0 / 2.0 * t26 * t3) * t1 - 9.0 / 2.0 * t43 * (t22 * t3 + 4.0 / 3.0 * t33 - 4.0 / 3.0 * t26 - 3.0 / 2.0 * t26 * t5) * t1;
    result__[ 3   ] = -7 * t11 * t6 * t4;
    result__[ 4   ] = -9.0 / 2.0 * t11 * t14 * t5 * t4;
    real_type t56  = 7.0 / 2.0 * t17 + 9.0 / 4.0 * t20 * t5;
    real_type t60  = t33 - t26;
    result__[ 5   ] = -t11 * (t56 * t5 - 9.0 / 4.0 * t20 * t8 - 3.0 / 2.0 * t60 * t3) * t1 + 9.0 / 2.0 * t43 * (t56 * t3 - 7.0 / 3.0 * t26 + 3.0 / 2.0 * t60 * t5) * t1;
    result__[ 6   ] = -t1;
    result__[ 7   ] = t1;
    result__[ 8   ] = result__[7];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",9);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::Drhs_odeDp_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  TwoLinkRobotArm::Drhs_odeDp_nnz() const
  { return 4; }

  void
  TwoLinkRobotArm::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 0   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[2];
    real_type t2   = sin(t1);
    real_type t3   = cos(t1);
    real_type t4   = X__[0];
    real_type t5   = t4 * t4;
    real_type t8   = X__[1];
    real_type t9   = t8 * t8;
    real_type t13  = U__[0];
    real_type t15  = U__[1];
    real_type t20  = t2 * t2;
    real_type t23  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t20);
    result__[ 0   ] = t23 * ((9.0 / 4.0 * t5 * t3 + 2 * t9) * t2 + 4.0 / 3.0 * t13 - 4.0 / 3.0 * t15 - 3.0 / 2.0 * t3 * t15);
    result__[ 1   ] = -t23 * ((7.0 / 2.0 * t5 + 9.0 / 4.0 * t9 * t3) * t2 - 7.0 / 3.0 * t15 + 3.0 / 2.0 * (t13 - t15) * t3);
    result__[ 2   ] = t8 - t4;
    result__[ 3   ] = t4;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDp_sparse",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::Drhs_odeDu_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::Drhs_odeDu_numCols() const
  { return 2; }

  integer
  TwoLinkRobotArm::Drhs_odeDu_nnz() const
  { return 4; }

  void
  TwoLinkRobotArm::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[0];
    real_type t2   = X__[2];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t3;
    real_type t7   = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t4);
    result__[ 0   ] = 4.0 / 3.0 * t7 * t1;
    real_type t9   = cos(t2);
    real_type t10  = 3.0 / 2.0 * t9;
    result__[ 1   ] = t7 * (-4.0 / 3.0 - t10) * t1;
    result__[ 2   ] = -3.0 / 2.0 * t7 * t9 * t1;
    result__[ 3   ] = -t7 * (-7.0 / 3.0 - t10) * t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",4);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  TwoLinkRobotArm::A_numRows() const
  { return 4; }

  integer
  TwoLinkRobotArm::A_numCols() const
  { return 4; }

  integer
  TwoLinkRobotArm::A_nnz() const
  { return 4; }

  void
  TwoLinkRobotArm::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",4);
    #endif
  }

}

// EOF: TwoLinkRobotArm_Methods.cc
