/*-----------------------------------------------------------------------*\
 |  file: MinimumFuelOrbitRaising_Methods.cc                             |
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


#include "MinimumFuelOrbitRaising.hh"
#include "MinimumFuelOrbitRaising_Pars.hh"

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


namespace MinimumFuelOrbitRaisingDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  MinimumFuelOrbitRaising::rhs_ode_numEqns() const
  { return 3; }

  void
  MinimumFuelOrbitRaising::rhs_ode_eval(
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
    real_type t1   = X__[2];
    real_type t2   = t1 * t1;
    real_type t4   = X__[0];
    real_type t5   = 1.0 / t4;
    real_type t7   = t4 * t4;
    real_type t9   = ModelPars[0];
    real_type t10  = U__[0];
    real_type t11  = sin(t10);
    real_type t17  = 1.0 / (-Q__[0] * ModelPars[1] + 1);
    result__[ 1   ] = t5 * t2 * t1 - 1.0 / t7 + t17 * t11 * t9;
    real_type t21  = cos(t10);
    result__[ 2   ] = -t5 * t1 * result__[0] + t17 * t21 * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::Drhs_odeDx_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::Drhs_odeDx_numCols() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::Drhs_odeDx_nnz() const
  { return 6; }

  void
  MinimumFuelOrbitRaising::Drhs_odeDx_pattern(
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
  MinimumFuelOrbitRaising::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    real_type t1   = X__[2];
    real_type t2   = t1 * t1;
    real_type t4   = X__[0];
    real_type t5   = t4 * t4;
    real_type t6   = 1.0 / t5;
    result__[ 1   ] = -t6 * t2 * t1 + 2 / t5 / t4;
    real_type t11  = 1.0 / t4;
    result__[ 2   ] = 3 * t11 * t2;
    real_type t13  = X__[1];
    result__[ 3   ] = t6 * t1 * t13;
    result__[ 4   ] = -t11 * t1;
    result__[ 5   ] = -t11 * t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::Drhs_odeDp_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::Drhs_odeDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::Drhs_odeDu_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::Drhs_odeDu_nnz() const
  { return 2; }

  void
  MinimumFuelOrbitRaising::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = ModelPars[0];
    real_type t2   = U__[0];
    real_type t3   = cos(t2);
    real_type t9   = 1.0 / (-Q__[0] * ModelPars[1] + 1);
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
  MinimumFuelOrbitRaising::A_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::A_numCols() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::A_nnz() const
  { return 3; }

  void
  MinimumFuelOrbitRaising::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::A_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 3, i_segment );
  }

}

// EOF: MinimumFuelOrbitRaising_Methods.cc
