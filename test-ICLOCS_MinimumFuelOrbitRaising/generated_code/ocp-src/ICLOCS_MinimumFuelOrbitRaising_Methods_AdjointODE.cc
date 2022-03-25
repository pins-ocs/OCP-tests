/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc           |
 |                                                                       |
 |  version: 1.0   date 25/3/2022                                        |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JPx_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::LTx_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JUx_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JPp_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::LTp_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JUp_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JPu_numEqns() const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::LTu_numEqns() const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::JUu_numEqns() const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::LTargs_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJPxDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPxDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPxDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DLTxDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTxDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTxDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJUxDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUxDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUxDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJPuDxp_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPuDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPuDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DLTuDxp_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTuDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTuDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJUuDxp_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUuDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUuDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJPpDp_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPpDp_numCols() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJPpDp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DLTpDp_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTpDp_numCols() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTpDp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DJUpDp_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUpDp_numCols() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DJUpDp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DLTargsDxup_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTargsDxup_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::DLTargsDxup_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xup_numRows() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xup_numCols() const { return 4; }
  integer ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xup_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::Hx_numEqns() const { return 3; }

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

  integer ICLOCS_MinimumFuelOrbitRaising::Hp_numEqns() const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DHxDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHxDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHxDxp_nnz()     const { return 8; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_MinimumFuelOrbitRaising::DHxDxp_sparse(
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
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DHpDp_numRows() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHpDp_numCols() const { return 0; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHpDp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


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
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::Hu_numEqns() const { return 1; }

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
    real_type t2   = ModelPars[iM_T];
    real_type t4   = U__[iU_theta];
    real_type t5   = cos(t4);
    real_type t7   = mass(Q__[iQ_zeta]);
    real_type t8   = 1.0 / t7;
    real_type t13  = sin(t4);
    result__[ 0   ] = -t8 * t13 * t2 * L__[iL_lambda3__xo] + t8 * t5 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DHuDxp_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHuDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHuDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DHuDxp_sparse(
    NodeType2 const    & NODE__,
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::eta_numEqns() const { return 3; }

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
  integer ICLOCS_MinimumFuelOrbitRaising::DetaDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DetaDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DetaDxp_sparse(
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::nu_numEqns() const { return 3; }

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
  integer ICLOCS_MinimumFuelOrbitRaising::DnuDxp_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DnuDxp_numCols() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_MinimumFuelOrbitRaising::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc
