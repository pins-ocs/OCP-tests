/*-----------------------------------------------------------------------*\
 |  file: Rayleight_Methods.cc                                           |
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


#include "Rayleight.hh"
#include "Rayleight_Pars.hh"

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


namespace RayleightDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  Rayleight::rhs_ode_numEqns() const
  { return 2; }

  void
  Rayleight::rhs_ode_eval(
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
    real_type t2   = result__[0] * result__[0];
    result__[ 1   ] = -X__[0] + result__[0] * (0.14e1 - 0.14e0 * t2) + 4 * U__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",2);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Rayleight::Drhs_odeDx_numRows() const
  { return 2; }

  integer
  Rayleight::Drhs_odeDx_numCols() const
  { return 2; }

  integer
  Rayleight::Drhs_odeDx_nnz() const
  { return 3; }

  void
  Rayleight::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 1   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 0   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Rayleight::Drhs_odeDx_sparse(
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
    result__[ 1   ] = -1;
    real_type t2   = X__[1] * X__[1];
    result__[ 2   ] = -0.42e0 * t2 + 0.14e1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Rayleight::Drhs_odeDp_numRows() const
  { return 2; }

  integer
  Rayleight::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  Rayleight::Drhs_odeDp_nnz() const
  { return 0; }

  void
  Rayleight::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Rayleight::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Rayleight::Drhs_odeDu_numRows() const
  { return 2; }

  integer
  Rayleight::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  Rayleight::Drhs_odeDu_nnz() const
  { return 1; }

  void
  Rayleight::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 1   ; jIndex[ 0  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Rayleight::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 4;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",1);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  Rayleight::A_numRows() const
  { return 2; }

  integer
  Rayleight::A_numCols() const
  { return 2; }

  integer
  Rayleight::A_nnz() const
  { return 2; }

  void
  Rayleight::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Rayleight::A_sparse(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",2);
    #endif
  }

}

// EOF: Rayleight_Methods.cc
