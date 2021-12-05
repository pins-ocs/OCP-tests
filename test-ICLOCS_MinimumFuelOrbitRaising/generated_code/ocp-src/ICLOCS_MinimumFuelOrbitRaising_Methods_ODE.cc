/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_ODE.cc                  |
 |                                                                       |
 |  version: 1.0   date 10/12/2021                                       |
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


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

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


namespace ICLOCS_MinimumFuelOrbitRaisingDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  ICLOCS_MinimumFuelOrbitRaising::rhs_ode_numEqns() const
  { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_x2];
    real_type t1   = X__[iX_x3];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_x1];
    real_type t4   = 1.0 / t3;
    real_type t6   = t3 * t3;
    real_type t8   = ModelPars[iM_T];
    real_type t9   = U__[iU_u];
    real_type t10  = sin(t9);
    real_type t16  = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_md] + 1);
    result__[ 1   ] = t4 * t2 - 1.0 / t6 + t16 * t10 * t8;
    real_type t20  = cos(t9);
    result__[ 2   ] = -t4 * t1 * result__[0] + t16 * t20 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDx_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDx_numCols() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDx_nnz() const
  { return 6; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    real_type t1   = X__[iX_x3];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_x1];
    real_type t4   = t3 * t3;
    real_type t5   = 1.0 / t4;
    result__[ 1   ] = -t5 * t2 + 2 / t4 / t3;
    real_type t10  = 1.0 / t3;
    real_type t11  = t10 * t1;
    result__[ 2   ] = 2 * t11;
    real_type t12  = X__[iX_x2];
    result__[ 3   ] = t5 * t1 * t12;
    result__[ 4   ] = -t11;
    result__[ 5   ] = -t10 * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDp_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDp_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDu_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDu_nnz() const
  { return 2; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_T];
    real_type t2   = U__[iU_u];
    real_type t3   = cos(t2);
    real_type t9   = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_md] + 1);
    result__[ 0   ] = t9 * t3 * t1;
    real_type t10  = sin(t2);
    result__[ 1   ] = -t9 * t10 * t1;
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
  ICLOCS_MinimumFuelOrbitRaising::A_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::A_numCols() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::A_nnz() const
  { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::A_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_ODE.cc
