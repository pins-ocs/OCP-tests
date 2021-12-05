/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_ParallelParking_Methods_ODE.cc                          |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  ICLOCS_ParallelParking::rhs_ode_numEqns() const
  { return 6; }

  void
  ICLOCS_ParallelParking::rhs_ode_eval(
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
    real_type t3   = X__[iX_v] * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = cos(t4);
    result__[ 0   ] = t5 * t3;
    real_type t6   = sin(t4);
    result__[ 1   ] = t6 * t3;
    result__[ 2   ] = X__[iX_a] * t1;
    result__[ 3   ] = U__[iU_u1] * t1;
    real_type t10  = tan(X__[iX_phi]);
    result__[ 4   ] = 1.0 / ModelPars[iM_len_a] * t10 * t3;
    result__[ 5   ] = U__[iU_u2] * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::Drhs_odeDx_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::Drhs_odeDx_numCols() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::Drhs_odeDx_nnz() const
  { return 8; }

  void
  ICLOCS_ParallelParking::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::Drhs_odeDx_sparse(
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
    real_type t2   = X__[iX_theta];
    real_type t3   = cos(t2);
    result__[ 0   ] = t1 * t3;
    real_type t4   = X__[iX_v];
    real_type t5   = t4 * t1;
    real_type t6   = sin(t2);
    result__[ 1   ] = -t5 * t6;
    result__[ 2   ] = t6 * t1;
    result__[ 3   ] = t3 * t5;
    result__[ 4   ] = t1;
    real_type t9   = tan(X__[iX_phi]);
    real_type t12  = 1.0 / ModelPars[iM_len_a];
    result__[ 5   ] = t12 * t9 * result__[4];
    real_type t14  = t9 * t9;
    result__[ 6   ] = t12 * (1 + t14) * t4 * result__[4];
    result__[ 7   ] = U__[iU_u2] * result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::Drhs_odeDp_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  ICLOCS_ParallelParking::Drhs_odeDp_nnz() const
  { return 6; }

  void
  ICLOCS_ParallelParking::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = X__[iX_theta];
    real_type t3   = cos(t2);
    result__[ 0   ] = t1 * t3;
    real_type t4   = sin(t2);
    result__[ 1   ] = t4 * t1;
    result__[ 2   ] = X__[iX_a];
    result__[ 3   ] = U__[iU_u1];
    real_type t6   = tan(X__[iX_phi]);
    result__[ 4   ] = 1.0 / ModelPars[iM_len_a] * t6 * t1;
    result__[ 5   ] = U__[iU_u2] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_ParallelParking::Drhs_odeDu_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::Drhs_odeDu_numCols() const
  { return 2; }

  integer
  ICLOCS_ParallelParking::Drhs_odeDu_nnz() const
  { return 2; }

  void
  ICLOCS_ParallelParking::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 5   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = P__[iP_T];
    result__[ 1   ] = X__[iX_v] * result__[0];
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
  ICLOCS_ParallelParking::A_numRows() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::A_numCols() const
  { return 6; }

  integer
  ICLOCS_ParallelParking::A_nnz() const
  { return 6; }

  void
  ICLOCS_ParallelParking::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_ParallelParking::A_sparse(
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
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 6, i_segment );
  }

}

// EOF: ICLOCS_ParallelParking_Methods_ODE.cc
