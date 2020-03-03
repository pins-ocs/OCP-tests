/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods.cc                                |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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

// map user defined functions and objects with macros
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  EconomicGrowthModel2::rhs_ode_numEqns() const
  { return 5; }

  void
  EconomicGrowthModel2::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[4];
    result__[ 0   ] = t2 * X__[2];
    real_type t3   = U__[0];
    real_type t6   = Q(X__[0], X__[1]);
    result__[ 1   ] = t2 * t6 * t3;
    result__[ 2   ] = t2 * X__[3];
    result__[ 3   ] = t2 * t6 * (1 - t3);
    result__[ 4   ] = 0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",5);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::Drhs_odeDx_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::Drhs_odeDx_numCols() const
  { return 5; }

  integer
  EconomicGrowthModel2::Drhs_odeDx_nnz() const
  { return 10; }

  void
  EconomicGrowthModel2::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 2   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 4   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 1   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 4   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 3   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 4   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 0   ;
    iIndex[ 8  ] = 3   ; jIndex[ 8  ] = 1   ;
    iIndex[ 9  ] = 3   ; jIndex[ 9  ] = 4   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = X__[4];
    result__[ 1   ] = X__[2];
    real_type t1   = U__[0];
    real_type t2   = X__[0];
    real_type t3   = X__[1];
    real_type t4   = Q_D_1(t2, t3);
    result__[ 2   ] = result__[0] * t4 * t1;
    real_type t6   = Q_D_2(t2, t3);
    result__[ 3   ] = result__[0] * t6 * t1;
    real_type t8   = Q(t2, t3);
    result__[ 4   ] = t8 * t1;
    result__[ 5   ] = result__[0];
    result__[ 6   ] = X__[3];
    real_type t9   = 1 - t1;
    result__[ 7   ] = result__[5] * t4 * t9;
    result__[ 8   ] = result__[5] * t6 * t9;
    result__[ 9   ] = t8 * t9;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",10);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::Drhs_odeDp_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  EconomicGrowthModel2::Drhs_odeDp_nnz() const
  { return 0; }

  void
  EconomicGrowthModel2::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::Drhs_odeDu_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  EconomicGrowthModel2::Drhs_odeDu_nnz() const
  { return 2; }

  void
  EconomicGrowthModel2::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 1   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 3   ; jIndex[ 1  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = Q(X__[0], X__[1]);
    result__[ 0   ] = X__[4] * t3;
    result__[ 1   ] = -result__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",2);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  EconomicGrowthModel2::A_numRows() const
  { return 5; }

  integer
  EconomicGrowthModel2::A_numCols() const
  { return 5; }

  integer
  EconomicGrowthModel2::A_nnz() const
  { return 5; }

  void
  EconomicGrowthModel2::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 2   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
    iIndex[ 4  ] = 4   ; jIndex[ 4  ] = 4   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::A_sparse(
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
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",5);
    #endif
  }

}

// EOF: EconomicGrowthModel2_Methods.cc
