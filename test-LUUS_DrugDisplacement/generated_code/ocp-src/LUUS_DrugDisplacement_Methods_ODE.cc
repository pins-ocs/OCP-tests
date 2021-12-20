/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_ODE.cc                           |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace LUUS_DrugDisplacementDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  LUUS_DrugDisplacement::rhs_ode_numEqns() const
  { return 2; }

  void
  LUUS_DrugDisplacement::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1(t2, t3);
    real_type t5   = t4 * P__[iP_T];
    real_type t6   = g4(t2, t3);
    real_type t11  = U__[iU_u] - 2 * t3;
    result__[ 0   ] = ((0.2e-1 - t2) * t6 + 0.464e2 * t11 * t2) * t5;
    real_type t15  = g3(t2, t3);
    result__[ 1   ] = (t11 * t15 + 0.928e0 - 0.464e2 * t2) * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::Drhs_odeDx_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::Drhs_odeDx_numCols() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::Drhs_odeDx_nnz() const
  { return 4; }

  void
  LUUS_DrugDisplacement::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1_D_1(t2, t3);
    real_type t5   = t4 * t1;
    real_type t6   = g4(t2, t3);
    real_type t7   = 0.2e-1 - t2;
    real_type t9   = U__[iU_u];
    real_type t11  = t9 - 2 * t3;
    real_type t14  = t7 * t6 + 0.464e2 * t11 * t2;
    real_type t16  = g1(t2, t3);
    real_type t17  = t16 * t1;
    real_type t18  = g4_D_1(t2, t3);
    result__[ 0   ] = t14 * t5 + (t7 * t18 - t6 + 0.464e2 * t9 - 0.928e2 * t3) * t17;
    real_type t24  = g1_D_2(t2, t3);
    real_type t25  = t24 * t1;
    real_type t27  = g4_D_2(t2, t3);
    result__[ 1   ] = t14 * t25 + (t7 * t27 - 0.928e2 * t2) * t17;
    real_type t32  = g3(t2, t3);
    real_type t35  = t11 * t32 + 0.928e0 - 0.464e2 * t2;
    real_type t37  = g3_D_1(t2, t3);
    result__[ 2   ] = t35 * t5 + (t11 * t37 - 0.464e2) * t17;
    real_type t42  = g3_D_2(t2, t3);
    result__[ 3   ] = t35 * t25 + (t11 * t42 - 2 * t32) * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::Drhs_odeDp_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::Drhs_odeDp_nnz() const
  { return 2; }

  void
  LUUS_DrugDisplacement::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    real_type t3   = g1(t1, t2);
    real_type t4   = g4(t1, t2);
    real_type t9   = U__[iU_u] - 2 * t2;
    result__[ 0   ] = ((0.2e-1 - t1) * t4 + 0.464e2 * t9 * t1) * t3;
    real_type t13  = g3(t1, t2);
    result__[ 1   ] = (t9 * t13 + 0.928e0 - 0.464e2 * t1) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::Drhs_odeDu_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::Drhs_odeDu_nnz() const
  { return 2; }

  void
  LUUS_DrugDisplacement::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1(t2, t3);
    real_type t5   = t4 * P__[iP_T];
    result__[ 0   ] = 0.464e2 * t2 * t5;
    real_type t7   = g3(t2, t3);
    result__[ 1   ] = t7 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDu_sparse", 2, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  LUUS_DrugDisplacement::A_numRows() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::A_numCols() const
  { return 2; }

  integer
  LUUS_DrugDisplacement::A_nnz() const
  { return 2; }

  void
  LUUS_DrugDisplacement::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 2, i_segment );
  }

}

// EOF: LUUS_DrugDisplacement_Methods_ODE.cc
