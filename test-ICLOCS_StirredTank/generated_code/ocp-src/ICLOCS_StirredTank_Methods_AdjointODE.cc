/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_AdjointODE.cc                       |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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

// map user defined functions and objects with macros
#define ALIAS_x2bound_max_DD(__t1) x2bound_max.DD( __t1)
#define ALIAS_x2bound_max_D(__t1) x2bound_max.D( __t1)
#define ALIAS_x2bound_min_DD(__t1) x2bound_min.DD( __t1)
#define ALIAS_x2bound_min_D(__t1) x2bound_min.D( __t1)
#define ALIAS_x1bound_max_DD(__t1) x1bound_max.DD( __t1)
#define ALIAS_x1bound_max_D(__t1) x1bound_max.D( __t1)
#define ALIAS_x1bound_min_DD(__t1) x1bound_min.DD( __t1)
#define ALIAS_x1bound_min_D(__t1) x1bound_min.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_StirredTankDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JPx_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::JPx_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::LTx_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = ALIAS_x1bound_min_D(-t1);
    real_type t4   = ALIAS_x1bound_max_D(t1 - 1);
    result__[ 0   ] = -t2 + t4;
    real_type t5   = X__[iX_x2];
    real_type t6   = ALIAS_x2bound_min_D(-t5);
    real_type t8   = ALIAS_x2bound_max_D(t5 - 1);
    result__[ 1   ] = -t6 + t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JUx_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::JUx_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JPp_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::JPp_eval(
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
      Mechatronix::check_in_segment( result__, "JPp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::LTp_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_tfbound_D(ModelPars[iM_T_min] - P__[iP_TimeSize]);
    result__[ 0   ] = -t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JUp_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::JUp_eval(
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
      Mechatronix::check_in_segment( result__, "JUp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JPu_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::JPu_eval(
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

  integer ICLOCS_StirredTank::LTu_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::LTu_eval(
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

  integer ICLOCS_StirredTank::JUu_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], 0, 2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::LTargs_numEqns() const { return 5; }

  void
  ICLOCS_StirredTank::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_T_min] - P__[iP_TimeSize];
    real_type t3   = X__[iX_x1];
    result__[ 1   ] = -t3;
    result__[ 2   ] = t3 - 1;
    real_type t4   = X__[iX_x2];
    result__[ 3   ] = -t4;
    result__[ 4   ] = t4 - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DJPxDxp_numRows() const { return 2; }
  integer ICLOCS_StirredTank::DJPxDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DJPxDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DLTxDxp_numRows() const { return 2; }
  integer ICLOCS_StirredTank::DLTxDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DLTxDxp_nnz()     const { return 2; }

  void
  ICLOCS_StirredTank::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  ICLOCS_StirredTank::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = ALIAS_x1bound_min_DD(-t1);
    real_type t4   = ALIAS_x1bound_max_DD(t1 - 1);
    result__[ 0   ] = t2 + t4;
    real_type t5   = X__[iX_x2];
    real_type t6   = ALIAS_x2bound_min_DD(-t5);
    real_type t8   = ALIAS_x2bound_max_DD(t5 - 1);
    result__[ 1   ] = t6 + t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DJUxDxp_numRows() const { return 2; }
  integer ICLOCS_StirredTank::DJUxDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DJUxDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DJPuDxp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DJPuDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DJPuDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DLTuDxp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DLTuDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DLTuDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DJUuDxp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DJUuDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DJUuDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DJPpDp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DJPpDp_numCols() const { return 1; }
  integer ICLOCS_StirredTank::DJPpDp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DLTpDp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DLTpDp_numCols() const { return 1; }
  integer ICLOCS_StirredTank::DLTpDp_nnz()     const { return 1; }

  void
  ICLOCS_StirredTank::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  ICLOCS_StirredTank::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_tfbound_DD(ModelPars[iM_T_min] - P__[iP_TimeSize]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTpDp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DJUpDp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DJUpDp_numCols() const { return 1; }
  integer ICLOCS_StirredTank::DJUpDp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DLTargsDxup_numRows() const { return 5; }
  integer ICLOCS_StirredTank::DLTargsDxup_numCols() const { return 4; }
  integer ICLOCS_StirredTank::DLTargsDxup_nnz()     const { return 5; }

  void
  ICLOCS_StirredTank::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 1   ;
  }


  void
  ICLOCS_StirredTank::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 5, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::D2LTargsD2xup_numRows() const { return 4; }
  integer ICLOCS_StirredTank::D2LTargsD2xup_numCols() const { return 4; }
  integer ICLOCS_StirredTank::D2LTargsD2xup_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::D2LTargsD2xup_sparse(
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

  integer ICLOCS_StirredTank::Hx_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::Hx_eval(
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
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = X__[iX_x1];
    real_type t8   = t1 * L__[iL_lambda1__xo];
    real_type t10  = 1.0 / ModelPars[iM_theta];
    real_type t11  = ModelPars[iM_k];
    real_type t12  = ModelPars[iM_En];
    real_type t13  = X__[iX_x2];
    real_type t16  = exp(-1.0 / t13 * t12);
    real_type t17  = t16 * t11;
    real_type t21  = t1 * L__[iL_lambda2__xo];
    result__[ 0   ] = (2 * t2 - 2 * ModelPars[iM_x1_f]) * t1 + (-t10 - t17) * t8 + t17 * t21;
    real_type t29  = t13 * t13;
    real_type t30  = 1.0 / t29;
    result__[ 1   ] = (2 * t13 - 2 * ModelPars[iM_x2_f]) * t1 - t16 * t30 * t12 * t2 * t11 * t8 + (t16 * t30 * t12 * t2 * t11 - ModelPars[iM_a] * U__[iU_u] - t10) * t21;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::Hp_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::Hp_eval(
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
    real_type t1   = ModelPars[iM_w_time];
    real_type t3   = log(P__[iP_TimeSize]);
    real_type t5   = X__[iX_x1];
    real_type t8   = pow(t5 - ModelPars[iM_x1_f], 2);
    real_type t9   = X__[iX_x2];
    real_type t12  = pow(t9 - ModelPars[iM_x2_f], 2);
    real_type t13  = U__[iU_u];
    real_type t16  = pow(t13 - ModelPars[iM_u_f], 2);
    real_type t20  = 1.0 / ModelPars[iM_theta];
    real_type t27  = exp(-1.0 / t9 * ModelPars[iM_En]);
    real_type t28  = t27 * t5 * ModelPars[iM_k];
    result__[ 0   ] = t3 * t1 + t8 + t12 + t16 + t1 + (t20 * (1 - t5) - t28) * L__[iL_lambda1__xo] + (t20 * (ModelPars[iM_Tf] - t9) + t28 - (t9 - ModelPars[iM_Tc]) * t13 * ModelPars[iM_a]) * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DHxDxp_numRows() const { return 2; }
  integer ICLOCS_StirredTank::DHxDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DHxDxp_nnz()     const { return 6; }

  void
  ICLOCS_StirredTank::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
  }


  void
  ICLOCS_StirredTank::DHxDxp_sparse(
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
    real_type t1   = P__[iP_TimeSize];
    result__[ 0   ] = 2 * t1;
    real_type t2   = L__[iL_lambda1__xo];
    real_type t4   = ModelPars[iM_k];
    real_type t5   = t4 * t2 * t1;
    real_type t6   = ModelPars[iM_En];
    real_type t7   = X__[iX_x2];
    real_type t8   = t7 * t7;
    real_type t13  = exp(-1.0 / t7 * t6);
    real_type t14  = t13 / t8 * t6;
    real_type t16  = L__[iL_lambda2__xo];
    real_type t17  = t1 * t16;
    result__[ 1   ] = t14 * t4 * t17 - t14 * t5;
    real_type t20  = X__[iX_x1];
    real_type t25  = 1.0 / ModelPars[iM_theta];
    result__[ 2   ] = 2 * t20 - 2 * ModelPars[iM_x1_f] + (-t13 * t4 - t25) * t2 + t13 * t4 * t16;
    result__[ 3   ] = result__[1];
    real_type t33  = 1.0 / t8 / t7;
    real_type t38  = t6 * t6;
    real_type t40  = t8 * t8;
    real_type t41  = 1.0 / t40;
    real_type t45  = t20 * t4;
    result__[ 4   ] = result__[0] + 2 * t13 * t33 * t6 * t20 * t5 - t13 * t41 * t38 * t20 * t5 + (-2 * t13 * t33 * t45 * t6 + t13 * t38 * t41 * t45) * t17;
    result__[ 5   ] = 2 * t7 - 2 * ModelPars[iM_x2_f] - t14 * t20 * t4 * t2 + (t14 * t45 - ModelPars[iM_a] * U__[iU_u] - t25) * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DHpDp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DHpDp_numCols() const { return 1; }
  integer ICLOCS_StirredTank::DHpDp_nnz()     const { return 1; }

  void
  ICLOCS_StirredTank::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  ICLOCS_StirredTank::DHpDp_sparse(
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
    result__[ 0   ] = ModelPars[iM_w_time] / P__[iP_TimeSize];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse", 1, i_segment );
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

  integer ICLOCS_StirredTank::Hu_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::Hu_eval(
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
    real_type t1   = P__[iP_TimeSize];
    result__[ 0   ] = (2 * U__[iU_u] - 2 * ModelPars[iM_u_f]) * t1 - ModelPars[iM_a] * (X__[iX_x2] - ModelPars[iM_Tc]) * t1 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DHuDxp_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DHuDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DHuDxp_nnz()     const { return 2; }

  void
  ICLOCS_StirredTank::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
  }


  void
  ICLOCS_StirredTank::DHuDxp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda2__xo];
    real_type t4   = ModelPars[iM_a];
    result__[ 0   ] = -t4 * P__[iP_TimeSize] * t1;
    result__[ 1   ] = 2 * U__[iU_u] - 2 * ModelPars[iM_u_f] - (X__[iX_x2] - ModelPars[iM_Tc]) * t4 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 2, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::eta_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DetaDxp_numRows() const { return 2; }
  integer ICLOCS_StirredTank::DetaDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DetaDxp_sparse(
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

  integer ICLOCS_StirredTank::nu_numEqns() const { return 2; }

  void
  ICLOCS_StirredTank::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DnuDxp_numRows() const { return 2; }
  integer ICLOCS_StirredTank::DnuDxp_numCols() const { return 3; }
  integer ICLOCS_StirredTank::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_StirredTank_Methods_AdjointODE.cc
