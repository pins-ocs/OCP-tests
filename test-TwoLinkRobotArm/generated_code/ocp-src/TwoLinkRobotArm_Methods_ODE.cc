/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods_ODE.cc                                 |
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x3];
    real_type t3   = sin(t2);
    real_type t4   = cos(t2);
    real_type t6   = X__[iX_x1];
    real_type t7   = t6 * t6;
    real_type t10  = X__[iX_x2];
    real_type t11  = t10 * t10;
    real_type t12  = t11 * t3;
    real_type t14  = U__[iU_u2];
    real_type t17  = U__[iU_u1];
    real_type t22  = t3 * t3;
    real_type t25  = 1.0 / (81 * t22 + 31);
    result__[ 0   ] = 3 * t25 * (27 * t7 * t4 * t3 - 18 * t14 * t4 + 24 * t12 - 16 * t14 + 16 * t17) * t1;
    result__[ 1   ] = -54 * t25 * t1 * (t4 * (3.0 / 2.0 * t12 + t17 - t14) + 7.0 / 3.0 * t7 * t3 - 0.14e2 / 9.0 * t14);
    result__[ 2   ] = (t10 - t6) * t1;
    result__[ 3   ] = t6 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x3];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = cos(t2);
    real_type t6   = X__[iX_x1];
    real_type t8   = t3 * t3;
    real_type t10  = 81 * t8 + 31;
    real_type t11  = 1.0 / t10;
    result__[ 0   ] = 162 * t11 * t6 * t5 * t4;
    real_type t14  = X__[iX_x2];
    result__[ 1   ] = 144 * t11 * t14 * t4;
    real_type t17  = t5 * t5;
    real_type t18  = t6 * t6;
    real_type t23  = t14 * t14;
    real_type t26  = U__[iU_u2];
    real_type t40  = U__[iU_u1];
    real_type t44  = t10 * t10;
    real_type t45  = 1.0 / t44;
    result__[ 2   ] = 9 * t11 * (9 * t18 * t17 - 9 * t18 * t8 + 8 * t23 * t5 + 6 * t26 * t3) * t1 - 7776 * t45 * t1 * t5 * (t5 * (0.27e2 / 0.16e2 * t18 * t3 - 9.0 / 8.0 * t26) + 3.0 / 2.0 * t23 * t3 + t40 - t26) * t3;
    result__[ 3   ] = -252 * t11 * t6 * t4;
    result__[ 4   ] = -162 * t11 * t14 * t5 * t4;
    real_type t56  = t8 * t8;
    real_type t59  = t40 - t26;
    real_type t63  = t23 * t17;
    real_type t65  = t18 * t5;
    result__[ 5   ] = 8748 * t45 * t1 * (3.0 / 4.0 * t23 * t56 + t8 * t3 * t59 / 2 + t8 * (3.0 / 4.0 * t63 + 7.0 / 6.0 * t65 + 0.31e2 / 0.108e3 * t23) + t3 * (t17 * t59 - 0.14e2 / 9.0 * t26 * t5 + 0.31e2 / 0.162e3 * t40 - 0.31e2 / 0.162e3 * t26) - 0.31e2 / 0.108e3 * t63 - 0.217e3 / 0.486e3 * t65);
    result__[ 6   ] = -t1;
    result__[ 7   ] = t1;
    result__[ 8   ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 9, i_segment );
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x3];
    real_type t2   = cos(t1);
    real_type t3   = sin(t1);
    real_type t5   = X__[iX_x1];
    real_type t6   = t5 * t5;
    real_type t9   = X__[iX_x2];
    real_type t10  = t9 * t9;
    real_type t11  = t10 * t3;
    real_type t13  = U__[iU_u2];
    real_type t16  = U__[iU_u1];
    real_type t20  = t3 * t3;
    real_type t23  = 1.0 / (81 * t20 + 31);
    result__[ 0   ] = t23 * (81 * t6 * t3 * t2 - 54 * t13 * t2 + 72 * t11 - 48 * t13 + 48 * t16);
    result__[ 1   ] = t23 * (t2 * (-81 * t11 - 54 * t16 + 54 * t13) - 126 * t6 * t3 + 84 * t13);
    result__[ 2   ] = t9 - t5;
    result__[ 3   ] = t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 4, i_segment );
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x3];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t3;
    real_type t7   = 1.0 / (81 * t4 + 31);
    result__[ 0   ] = 48 * t1 * t7;
    real_type t9   = cos(t2);
    real_type t10  = 9 * t9;
    result__[ 1   ] = -6 * t7 * (8 + t10) * t1;
    result__[ 2   ] = -54 * t7 * t9 * t1;
    result__[ 3   ] = 6 * t7 * (14 + t10) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDu_sparse", 4, i_segment );
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: TwoLinkRobotArm_Methods_ODE.cc
