/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods.cc                                       |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  MaximumAscent::rhs_ode_numEqns() const
  { return 4; }

  void
  MaximumAscent::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = tf(ModelPars[1]);
    real_type t3   = eta(t2);
    result__[ 0   ] = X__[1] * t3;
    real_type t5   = X__[2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[0];
    real_type t8   = 1.0 / t7;
    real_type t10  = t7 * t7;
    real_type t14  = Tbar(t2);
    real_type t22  = 1.0 / (-Q__[0] * ModelPars[5] * t2 + ModelPars[4]) * t14;
    real_type t23  = U__[0];
    real_type t24  = sin(t23);
    result__[ 1   ] = (t8 * t6 - 1.0 / t10) * t3 + t24 * t22;
    real_type t28  = cos(t23);
    result__[ 2   ] = -t8 * t5 * result__[0] + t28 * t22;
    result__[ 3   ] = t8 * t5 * t3;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"rhs_ode",4);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::Drhs_odeDx_numRows() const
  { return 4; }

  integer
  MaximumAscent::Drhs_odeDx_numCols() const
  { return 4; }

  integer
  MaximumAscent::Drhs_odeDx_nnz() const
  { return 8; }

  void
  MaximumAscent::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 1   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 0   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 2   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 1   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 2   ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 0   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = tf(ModelPars[1]);
    result__[ 0   ] = eta(t2);
    real_type t3   = X__[2];
    real_type t4   = t3 * t3;
    real_type t5   = X__[0];
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    result__[ 1   ] = (-t7 * t4 + 2 / t6 / t5) * result__[0];
    real_type t13  = t3 * result__[0];
    real_type t14  = 1.0 / t5;
    real_type t15  = t14 * t13;
    result__[ 2   ] = 2 * t15;
    real_type t17  = X__[1] * result__[0];
    result__[ 3   ] = t7 * t3 * t17;
    result__[ 4   ] = -t15;
    result__[ 5   ] = -t14 * t17;
    result__[ 6   ] = -t7 * t13;
    result__[ 7   ] = t14 * result__[0];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Drhs_odeDxp_sparse",8);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::Drhs_odeDp_numRows() const
  { return 4; }

  integer
  MaximumAscent::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  MaximumAscent::Drhs_odeDp_nnz() const
  { return 0; }

  void
  MaximumAscent::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MaximumAscent::Drhs_odeDu_numRows() const
  { return 4; }

  integer
  MaximumAscent::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  MaximumAscent::Drhs_odeDu_nnz() const
  { return 2; }

  void
  MaximumAscent::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 1   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 2   ; jIndex[ 1  ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MaximumAscent::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = tf(ModelPars[1]);
    real_type t3   = Tbar(t2);
    real_type t11  = 1.0 / (-Q__[0] * ModelPars[5] * t2 + ModelPars[4]) * t3;
    real_type t12  = U__[0];
    real_type t13  = cos(t12);
    result__[ 0   ] = t13 * t11;
    real_type t14  = sin(t12);
    result__[ 1   ] = -t14 * t11;
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
  MaximumAscent::A_numRows() const
  { return 4; }

  integer
  MaximumAscent::A_numCols() const
  { return 4; }

  integer
  MaximumAscent::A_nnz() const
  { return 4; }

  void
  MaximumAscent::A_pattern(
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
  MaximumAscent::A_sparse(
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

// EOF: MaximumAscent_Methods.cc
