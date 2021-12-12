/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc           |
 |                                                                       |
 |  version: 1.0   date 12/12/2021                                       |
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
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  ICLOCS_MinimumFuelOrbitRaising::Hx_numEqns() const
  { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Hx_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_vt];
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_r];
    real_type t5   = t4 * t4;
    real_type t6   = 1.0 / t5;
    real_type t13  = L__[iL_lambda3__xo];
    real_type t15  = X__[iX_vr] * t13;
    result__[ 0   ] = (-t6 * t3 + 2 / t5 / t4) * t1 + t6 * t2 * t15;
    real_type t20  = 1.0 / t4;
    result__[ 1   ] = -t20 * t2 * t13 + L__[iL_lambda1__xo] - 1;
    result__[ 2   ] = 2 * t20 * t2 * t1 - t20 * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHxDx_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHxDx_numCols() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHxDx_nnz() const
  { return 8; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 2   ;
  }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHxDx_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = X__[iX_vt];
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_r];
    real_type t5   = t4 * t4;
    real_type t7   = 1.0 / t5 / t4;
    real_type t10  = t5 * t5;
    real_type t15  = L__[iL_lambda3__xo];
    real_type t17  = X__[iX_vr] * t15;
    result__[ 0   ] = (2 * t7 * t3 - 6 / t10) * t1 - 2 * t7 * t2 * t17;
    real_type t22  = 1.0 / t5;
    result__[ 1   ] = t22 * t2 * t15;
    result__[ 2   ] = -2 * t22 * t2 * t1 + t22 * t17;
    result__[ 3   ] = result__[1];
    real_type t27  = 1.0 / t4;
    result__[ 4   ] = -t27 * t15;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 2 * t27 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHxDp_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHxDp_numCols() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHxDp_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DHxDp_sparse(
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
  ICLOCS_MinimumFuelOrbitRaising::Hu_numEqns() const
  { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_theta];
    real_type t6   = ModelPars[iM_T];
    real_type t8   = cos(t2);
    real_type t10  = mass(Q__[iQ_zeta]);
    real_type t11  = 1.0 / t10;
    real_type t16  = sin(t2);
    result__[ 0   ] = -t11 * t16 * t6 * L__[iL_lambda3__xo] + t11 * t8 * t6 * L__[iL_lambda2__xo] + 2 * t2 * ModelPars[iM_u_epsi];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHuDx_numRows() const
  { return 1; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHuDx_numCols() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHuDx_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHuDp_numRows() const
  { return 1; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHuDp_numCols() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHuDp_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DHuDp_sparse(
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
  ICLOCS_MinimumFuelOrbitRaising::Hp_numEqns() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHpDp_numRows() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHpDp_numCols() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DHpDp_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DHpDp_sparse(
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
  ICLOCS_MinimumFuelOrbitRaising::eta_numEqns() const
  { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DetaDx_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DetaDx_numCols() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DetaDx_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DetaDp_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DetaDp_numCols() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DetaDp_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDp_sparse(
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
  ICLOCS_MinimumFuelOrbitRaising::nu_numEqns() const
  { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DnuDx_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DnuDx_numCols() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DnuDx_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS_MinimumFuelOrbitRaising::DnuDp_numRows() const
  { return 3; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DnuDp_numCols() const
  { return 0; }

  integer
  ICLOCS_MinimumFuelOrbitRaising::DnuDp_nnz() const
  { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc
