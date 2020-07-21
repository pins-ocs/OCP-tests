/*-----------------------------------------------------------------------*\
 |  file: MinimumFuelOrbitRaising_Methods.cc                             |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
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


namespace MinimumFuelOrbitRaisingDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  MinimumFuelOrbitRaising::Hx_numEqns() const
  { return 3; }

  void
  MinimumFuelOrbitRaising::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = L__[1];
    real_type t2   = X__[2];
    real_type t3   = t2 * t2;
    real_type t5   = X__[0];
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t14  = L__[2];
    real_type t16  = X__[1] * t14;
    result__[ 0   ] = (-t7 * t3 * t2 + 2 / t6 / t5) * t1 + t7 * t2 * t16;
    real_type t21  = 1.0 / t5;
    result__[ 1   ] = -t21 * t2 * t14 + L__[0] - 1;
    result__[ 2   ] = 3 * t21 * t3 * t1 - t21 * t16;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hx_eval",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DHxDx_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DHxDx_numCols() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DHxDx_nnz() const
  { return 8; }

  void
  MinimumFuelOrbitRaising::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 2   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 0   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 0   ;
    iIndex[ 6  ] = 2   ; jIndex[ 6  ] = 1   ;
    iIndex[ 7  ] = 2   ; jIndex[ 7  ] = 2   ;
  }

  void
  MinimumFuelOrbitRaising::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = L__[1];
    real_type t2   = X__[2];
    real_type t3   = t2 * t2;
    real_type t5   = X__[0];
    real_type t6   = t5 * t5;
    real_type t8   = 1.0 / t6 / t5;
    real_type t11  = t6 * t6;
    real_type t16  = L__[2];
    real_type t18  = X__[1] * t16;
    result__[ 0   ] = (2 * t8 * t3 * t2 - 6 / t11) * t1 - 2 * t8 * t2 * t18;
    real_type t23  = 1.0 / t6;
    result__[ 1   ] = t23 * t2 * t16;
    result__[ 2   ] = -3 * t23 * t3 * t1 + t23 * t18;
    result__[ 3   ] = result__[1];
    real_type t28  = 1.0 / t5;
    result__[ 4   ] = -t28 * t16;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 6 * t28 * t2 * t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DHxDx_sparse",8);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DHxDp_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DHxDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DHxDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  integer
  MinimumFuelOrbitRaising::Hu_numEqns() const
  { return 1; }

  void
  MinimumFuelOrbitRaising::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[0];
    real_type t4   = U__[0];
    real_type t5   = cos(t4);
    real_type t10  = 1.0 / (-Q__[0] * ModelPars[1] + 1);
    real_type t15  = sin(t4);
    result__[ 0   ] = -t10 * t15 * t2 * L__[2] + t10 * t5 * t2 * L__[1];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hu_eval",1);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DHuDx_numRows() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DHuDx_numCols() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DHuDx_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DHuDp_numRows() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DHuDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DHuDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  MinimumFuelOrbitRaising::Hp_numEqns() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);

    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"Hp_eval",0);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DHpDp_numRows() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DHpDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DHpDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  integer
  MinimumFuelOrbitRaising::eta_numEqns() const
  { return 3; }

  void
  MinimumFuelOrbitRaising::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment     = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = L__[0];
    result__[ 1   ] = L__[1];
    result__[ 2   ] = L__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"eta_eval",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DetaDx_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DetaDx_numCols() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DetaDx_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DetaDp_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DetaDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DetaDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DetaDp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  integer
  MinimumFuelOrbitRaising::nu_numEqns() const
  { return 3; }

  void
  MinimumFuelOrbitRaising::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"nu_eval",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DnuDx_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DnuDx_numCols() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DnuDx_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DnuDp_numRows() const
  { return 3; }

  integer
  MinimumFuelOrbitRaising::DnuDp_numCols() const
  { return 0; }

  integer
  MinimumFuelOrbitRaising::DnuDp_nnz() const
  { return 0; }

  void
  MinimumFuelOrbitRaising::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: MinimumFuelOrbitRaising_Methods.cc
