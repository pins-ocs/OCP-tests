/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_ODE.cc                              |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_DD(__t1) x2bound.DD( __t1)
#define ALIAS_x2bound_D(__t1) x2bound.D( __t1)
#define ALIAS_x1bound_DD(__t1) x1bound.DD( __t1)
#define ALIAS_x1bound_D(__t1) x1bound.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_StirredTankDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  ICLOCS_StirredTank::rhs_ode_numEqns() const
  { return 2; }

  void
  ICLOCS_StirredTank::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = X__[iX_x1];
    real_type t5   = 1.0 / ModelPars[iM_theta];
    real_type t10  = X__[iX_x2];
    real_type t13  = exp(-1.0 / t10 * ModelPars[iM_En]);
    real_type t14  = t13 * t2 * ModelPars[iM_k];
    result__[ 0   ] = (t5 * (1 - t2) - t14) * t1;
    result__[ 1   ] = (t5 * (ModelPars[iM_Tf] - t10) + t14 - (t10 - ModelPars[iM_Tc]) * U__[iU_u] * ModelPars[iM_a]) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::Drhs_odeDx_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::Drhs_odeDx_numCols() const
  { return 2; }

  integer
  ICLOCS_StirredTank::Drhs_odeDx_nnz() const
  { return 4; }

  void
  ICLOCS_StirredTank::Drhs_odeDx_pattern(
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
  ICLOCS_StirredTank::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t3   = 1.0 / ModelPars[iM_theta];
    real_type t4   = ModelPars[iM_k];
    real_type t5   = ModelPars[iM_En];
    real_type t6   = X__[iX_x2];
    real_type t9   = exp(-1.0 / t6 * t5);
    result__[ 0   ] = (-t9 * t4 - t3) * t1;
    real_type t12  = t4 * t1;
    real_type t13  = X__[iX_x1];
    real_type t15  = t6 * t6;
    real_type t18  = t9 / t15 * t5;
    result__[ 1   ] = -t18 * t13 * t12;
    result__[ 2   ] = t9 * t12;
    result__[ 3   ] = (t18 * t13 * t4 - ModelPars[iM_a] * U__[iU_u] - t3) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::Drhs_odeDp_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::Drhs_odeDp_nnz() const
  { return 2; }

  void
  ICLOCS_StirredTank::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::Drhs_odeDp_sparse(
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
    real_type t4   = 1.0 / ModelPars[iM_theta];
    real_type t9   = X__[iX_x2];
    real_type t12  = exp(-1.0 / t9 * ModelPars[iM_En]);
    real_type t13  = t12 * t1 * ModelPars[iM_k];
    result__[ 0   ] = t4 * (1 - t1) - t13;
    result__[ 1   ] = t4 * (ModelPars[iM_Tf] - t9) + t13 - (t9 - ModelPars[iM_Tc]) * U__[iU_u] * ModelPars[iM_a];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_StirredTank::Drhs_odeDu_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  ICLOCS_StirredTank::Drhs_odeDu_nnz() const
  { return 1; }

  void
  ICLOCS_StirredTank::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -P__[iP_TimeSize] * ModelPars[iM_a] * (X__[iX_x2] - ModelPars[iM_Tc]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDu_sparse", 1, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  ICLOCS_StirredTank::A_numRows() const
  { return 2; }

  integer
  ICLOCS_StirredTank::A_numCols() const
  { return 2; }

  integer
  ICLOCS_StirredTank::A_nnz() const
  { return 2; }

  void
  ICLOCS_StirredTank::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::A_sparse(
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

// EOF: ICLOCS_StirredTank_Methods_ODE.cc
