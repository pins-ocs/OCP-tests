/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_ODE.cc                           |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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

  integer LUUS_DrugDisplacement::rhs_ode_numEqns() const { return 2; }

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
  integer LUUS_DrugDisplacement::Drhs_odeDxup_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::Drhs_odeDxup_numCols() const { return 4; }
  integer LUUS_DrugDisplacement::Drhs_odeDxup_nnz()     const { return 8; }

  void
  LUUS_DrugDisplacement::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::Drhs_odeDxup_sparse(
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
    result__[ 2   ] = 0.464e2 * t2 * t17;
    result__[ 3   ] = t14 * t16;
    real_type t33  = g3(t2, t3);
    real_type t36  = t11 * t33 + 0.928e0 - 0.464e2 * t2;
    real_type t38  = g3_D_1(t2, t3);
    result__[ 4   ] = t36 * t5 + (t11 * t38 - 0.464e2) * t17;
    real_type t43  = g3_D_2(t2, t3);
    result__[ 5   ] = t36 * t25 + (t11 * t43 - 2 * t33) * t17;
    result__[ 6   ] = t33 * t17;
    result__[ 7   ] = t36 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 8, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::A_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::A_numCols() const { return 2; }
  integer LUUS_DrugDisplacement::A_nnz()     const { return 2; }

  void
  LUUS_DrugDisplacement::A_pattern( integer iIndex[], integer jIndex[] ) const {
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
