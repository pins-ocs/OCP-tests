/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods.cc                                              |
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


#include "Bike1D.hh"
#include "Bike1D_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3(__t1, __t2, __t3) mufControl.D_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2(__t1, __t2, __t3) mufControl.D_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1(__t1, __t2, __t3) mufControl.D_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3_3(__t1, __t2, __t3) mufControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_3(__t1, __t2, __t3) mufControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_2(__t1, __t2, __t3) mufControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_3(__t1, __t2, __t3) mufControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_2(__t1, __t2, __t3) mufControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_1(__t1, __t2, __t3) mufControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3(__t1, __t2, __t3) murControl.D_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2(__t1, __t2, __t3) murControl.D_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1(__t1, __t2, __t3) murControl.D_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3_3(__t1, __t2, __t3) murControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_3(__t1, __t2, __t3) murControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_2(__t1, __t2, __t3) murControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_3(__t1, __t2, __t3) murControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_2(__t1, __t2, __t3) murControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_1(__t1, __t2, __t3) murControl.D_1_1( __t1, __t2, __t3)


namespace Bike1DDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  Bike1D::rhs_ode_numEqns() const
  { return 1; }

  void
  Bike1D::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = ModelPars[1] * (U__[0] + U__[1]);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::Drhs_odeDx_numRows() const
  { return 1; }

  integer
  Bike1D::Drhs_odeDx_numCols() const
  { return 1; }

  integer
  Bike1D::Drhs_odeDx_nnz() const
  { return 0; }

  void
  Bike1D::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::Drhs_odeDp_numRows() const
  { return 1; }

  integer
  Bike1D::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  Bike1D::Drhs_odeDp_nnz() const
  { return 0; }

  void
  Bike1D::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::Drhs_odeDu_numRows() const
  { return 1; }

  integer
  Bike1D::Drhs_odeDu_numCols() const
  { return 2; }

  integer
  Bike1D::Drhs_odeDu_nnz() const
  { return 2; }

  void
  Bike1D::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = ModelPars[1];
    result__[ 1   ] = result__[0];
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
  Bike1D::A_numRows() const
  { return 1; }

  integer
  Bike1D::A_numCols() const
  { return 1; }

  integer
  Bike1D::A_nnz() const
  { return 1; }

  void
  Bike1D::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = X__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",1);
    #endif
  }

}

// EOF: Bike1D_Methods.cc
