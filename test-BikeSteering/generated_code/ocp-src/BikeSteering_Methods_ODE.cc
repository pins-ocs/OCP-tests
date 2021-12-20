/*-----------------------------------------------------------------------*\
 |  file: BikeSteering_Methods_ODE.cc                                    |
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


#include "BikeSteering.hh"
#include "BikeSteering_Pars.hh"

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
#define ALIAS_minimumTimeSize_DD(__t1) minimumTimeSize.DD( __t1)
#define ALIAS_minimumTimeSize_D(__t1) minimumTimeSize.D( __t1)
#define ALIAS_FyControl_D_3(__t1, __t2, __t3) FyControl.D_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2(__t1, __t2, __t3) FyControl.D_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1(__t1, __t2, __t3) FyControl.D_1( __t1, __t2, __t3)
#define ALIAS_FyControl_D_3_3(__t1, __t2, __t3) FyControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_3(__t1, __t2, __t3) FyControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_2_2(__t1, __t2, __t3) FyControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_3(__t1, __t2, __t3) FyControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_2(__t1, __t2, __t3) FyControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_FyControl_D_1_1(__t1, __t2, __t3) FyControl.D_1_1( __t1, __t2, __t3)


namespace BikeSteeringDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  BikeSteering::rhs_ode_numEqns() const
  { return 3; }

  void
  BikeSteering::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_TimeSize];
    result__[ 0   ] = X__[iX_omega] * t1;
    real_type t6   = ModelPars[iM_h];
    result__[ 1   ] = X__[iX_phi] * t6 * ModelPars[iM_g] * ModelPars[iM_m] * t1 - U__[iU_Fy] * t6 * t1;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BikeSteering::Drhs_odeDx_numRows() const
  { return 3; }

  integer
  BikeSteering::Drhs_odeDx_numCols() const
  { return 3; }

  integer
  BikeSteering::Drhs_odeDx_nnz() const
  { return 4; }

  void
  BikeSteering::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BikeSteering::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_TimeSize];
    result__[ 1   ] = X__[iX_omega];
    real_type t1   = ModelPars[iM_m];
    real_type t3   = ModelPars[iM_g];
    real_type t4   = ModelPars[iM_h];
    result__[ 2   ] = t4 * t3 * t1 * result__[0];
    result__[ 3   ] = X__[iX_phi] * t4 * t3 * t1 - U__[iU_Fy] * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BikeSteering::Drhs_odeDp_numRows() const
  { return 3; }

  integer
  BikeSteering::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  BikeSteering::Drhs_odeDp_nnz() const
  { return 0; }

  void
  BikeSteering::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BikeSteering::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BikeSteering::Drhs_odeDu_numRows() const
  { return 3; }

  integer
  BikeSteering::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  BikeSteering::Drhs_odeDu_nnz() const
  { return 1; }

  void
  BikeSteering::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BikeSteering::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_TimeSize] * ModelPars[iM_h];
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
  BikeSteering::A_numRows() const
  { return 3; }

  integer
  BikeSteering::A_numCols() const
  { return 3; }

  integer
  BikeSteering::A_nnz() const
  { return 3; }

  void
  BikeSteering::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BikeSteering::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = ModelPars[iM_Ix];
    result__[ 2   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: BikeSteering_Methods_ODE.cc
