/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods.cc                                        |
 |                                                                       |
 |  version: 1.0   date 13/9/2020                                        |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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


namespace TwoStageCSTRDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  TwoStageCSTR::rhs_ode_numEqns() const
  { return 4; }

  void
  TwoStageCSTR::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[1];
    real_type t3   = R1(t1, t2);
    result__[ 0   ] = 0.5e0 - t1 - t3;
    result__[ 1   ] = t3 - (2 + U__[0]) * (t2 + 0.25e0);
    real_type t8   = X__[2];
    real_type t9   = ModelPars[1];
    real_type t11  = X__[3];
    real_type t12  = R2(t8, t11);
    result__[ 2   ] = t1 - t8 - result__[0] * t9 - t12 + 0.25e0;
    result__[ 3   ] = t2 - 2 * t11 - (t11 + 0.25e0) * U__[1] - result__[1] * t9 + t12 - 0.25e0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::Drhs_odeDx_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::Drhs_odeDx_numCols() const
  { return 4; }

  integer
  TwoStageCSTR::Drhs_odeDx_nnz() const
  { return 12; }

  void
  TwoStageCSTR::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 0   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 1   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 0   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 1   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 2   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 3   ;
    iIndex[ 8  ] = 3   ; jIndex[ 8  ] = 0   ;
    iIndex[ 9  ] = 3   ; jIndex[ 9  ] = 1   ;
    iIndex[ 10 ] = 3   ; jIndex[ 10 ] = 2   ;
    iIndex[ 11 ] = 3   ; jIndex[ 11 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[0];
    real_type t2   = X__[1];
    real_type t3   = R1_D_1(t1, t2);
    result__[ 0   ] = -1 - t3;
    real_type t4   = R1_D_2(t1, t2);
    result__[ 1   ] = -t4;
    result__[ 2   ] = t3;
    result__[ 3   ] = t4 - 2 - U__[0];
    real_type t6   = ModelPars[1];
    result__[ 4   ] = -result__[0] * t6 + 1;
    result__[ 5   ] = t4 * t6;
    real_type t8   = X__[2];
    real_type t9   = X__[3];
    real_type t10  = R2_D_1(t8, t9);
    result__[ 6   ] = -1 - t10;
    real_type t11  = R2_D_2(t8, t9);
    result__[ 7   ] = -t11;
    result__[ 8   ] = -result__[2] * t6;
    result__[ 9   ] = -result__[3] * t6 + 1;
    result__[ 10  ] = t10;
    result__[ 11  ] = -2 - U__[1] + t11;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",12);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::Drhs_odeDp_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  TwoStageCSTR::Drhs_odeDp_nnz() const
  { return 0; }

  void
  TwoStageCSTR::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoStageCSTR::Drhs_odeDu_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::Drhs_odeDu_numCols() const
  { return 2; }

  integer
  TwoStageCSTR::Drhs_odeDu_nnz() const
  { return 3; }

  void
  TwoStageCSTR::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 1   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 3   ; jIndex[ 1  ] = 0   ;
    iIndex[ 2  ] = 3   ; jIndex[ 2  ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = -X__[1] - 0.25e0;
    result__[ 1   ] = -result__[0] * ModelPars[1];
    result__[ 2   ] = -X__[3] - 0.25e0;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDu_sparse",3);
    #endif
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  TwoStageCSTR::A_numRows() const
  { return 4; }

  integer
  TwoStageCSTR::A_numCols() const
  { return 4; }

  integer
  TwoStageCSTR::A_nnz() const
  { return 4; }

  void
  TwoStageCSTR::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 3   ; jIndex[ 3  ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::A_sparse(
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
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"A_sparse",4);
    #endif
  }

}

// EOF: TwoStageCSTR_Methods.cc
