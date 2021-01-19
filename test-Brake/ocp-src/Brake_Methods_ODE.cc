/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods.cc                                               |
 |                                                                       |
 |  version: 1.0   date 20/1/2021                                        |
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


#include "Brake.hh"
#include "Brake_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_aControl_D_3(__t1, __t2, __t3) aControl.D_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_2(__t1, __t2, __t3) aControl.D_2( __t1, __t2, __t3)
#define ALIAS_aControl_D_1(__t1, __t2, __t3) aControl.D_1( __t1, __t2, __t3)
#define ALIAS_aControl_D_3_3(__t1, __t2, __t3) aControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_2_3(__t1, __t2, __t3) aControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_2_2(__t1, __t2, __t3) aControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_aControl_D_1_3(__t1, __t2, __t3) aControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_aControl_D_1_2(__t1, __t2, __t3) aControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_aControl_D_1_1(__t1, __t2, __t3) aControl.D_1_1( __t1, __t2, __t3)


namespace BrakeDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  Brake::rhs_ode_numEqns() const
  { return 2; }

  void
  Brake::rhs_ode_eval(
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
    result__[ 0   ] = X__[1] * t1;
    result__[ 1   ] = U__[0] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::Drhs_odeDx_numRows() const
  { return 2; }

  integer
  Brake::Drhs_odeDx_numCols() const
  { return 2; }

  integer
  Brake::Drhs_odeDx_nnz() const
  { return 1; }

  void
  Brake::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = P__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::Drhs_odeDp_numRows() const
  { return 2; }

  integer
  Brake::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  Brake::Drhs_odeDp_nnz() const
  { return 2; }

  void
  Brake::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = X__[1];
    result__[ 1   ] = U__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Brake::Drhs_odeDu_numRows() const
  { return 2; }

  integer
  Brake::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  Brake::Drhs_odeDu_nnz() const
  { return 1; }

  void
  Brake::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = P__[0];
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
  Brake::A_numRows() const
  { return 2; }

  integer
  Brake::A_numCols() const
  { return 2; }

  integer
  Brake::A_nnz() const
  { return 2; }

  void
  Brake::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::A_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 2, i_segment );
  }

}

// EOF: Brake_Methods.cc
