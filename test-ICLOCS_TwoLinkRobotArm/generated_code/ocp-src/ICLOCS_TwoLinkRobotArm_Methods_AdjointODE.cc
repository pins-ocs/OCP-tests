/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc                   |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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


namespace ICLOCS_TwoLinkRobotArmDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JPx_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::JPx_eval(
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
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::LTx_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::LTx_eval(
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
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JUx_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::JUx_eval(
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
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JPp_numEqns() const { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::JPp_eval(
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

  integer ICLOCS_TwoLinkRobotArm::LTp_numEqns() const { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::LTp_eval(
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
      Mechatronix::check_in_segment( result__, "LTp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JUp_numEqns() const { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = u1Control(U__[iU_u1], -1, 1);
    real_type t4   = u2Control(U__[iU_u2], -1, 1);
    result__[ 0   ] = t2 + t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JPu_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::JPu_eval(
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
      Mechatronix::check_in_segment( result__, "JPu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::LTu_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::LTu_eval(
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
      Mechatronix::check_in_segment( result__, "LTu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JUu_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    result__[ 1   ] = t5 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::LTargs_numEqns() const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJPxDxp_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::DJPxDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DJPxDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DLTxDxp_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::DLTxDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DLTxDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJUxDxp_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::DJUxDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DJUxDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJPuDxp_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DJPuDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DJPuDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DLTuDxp_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DLTuDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DLTuDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJUuDxp_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DJUuDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DJUuDxp_nnz()     const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 4   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    result__[ 1   ] = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJPpDp_numRows() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DJPpDp_numCols() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DJPpDp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DLTpDp_numRows() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DLTpDp_numCols() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DLTpDp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJUpDp_numRows() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DJUpDp_numCols() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DJUpDp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DLTargsDxup_numRows() const { return 0; }
  integer ICLOCS_TwoLinkRobotArm::DLTargsDxup_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::DLTargsDxup_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2LTargsD2xup_numRows() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2LTargsD2xup_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2LTargsD2xup_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::D2LTargsD2xup_sparse(
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

  integer ICLOCS_TwoLinkRobotArm::Hx_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::Hx_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t7   = cos(t4);
    real_type t8   = X__[iX_omega__alpha];
    real_type t10  = t5 * t5;
    real_type t12  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t10;
    real_type t13  = 1.0 / t12;
    real_type t18  = t2 * L__[iL_lambda2__xo];
    real_type t23  = t2 * L__[iL_lambda3__xo];
    result__[ 0   ] = 9.0 / 2.0 * t13 * t8 * t7 * t5 * t3 - 7 * t13 * t8 * t18 - t23 + t2 * L__[iL_lambda4__xo];
    real_type t26  = X__[iX_omega__beta];
    result__[ 1   ] = 4 * t13 * t26 * t3 - 9.0 / 2.0 * t13 * t26 * t7 * t5 * t18 + t23;
    real_type t35  = t7 * t7;
    real_type t36  = t8 * t8;
    real_type t41  = U__[iU_u2];
    real_type t47  = t7 * t5;
    real_type t50  = t26 * t26;
    real_type t52  = U__[iU_u1];
    real_type t59  = t12 * t12;
    real_type t62  = t7 * t5 / t59;
    real_type t69  = t52 - t41;
    result__[ 2   ] = t13 * (9.0 / 4.0 * t36 * t35 - 9.0 / 4.0 * t36 * t10 + 3.0 / 2.0 * t41 * t5) * t3 - 9.0 / 2.0 * t62 * (9.0 / 4.0 * t36 * t47 + 2 * t50 + 4.0 / 3.0 * t52 - 4.0 / 3.0 * t41 - 3.0 / 2.0 * t41 * t7) * t3 - t13 * (9.0 / 4.0 * t50 * t35 - 9.0 / 4.0 * t50 * t10 - 3.0 / 2.0 * t69 * t5) * t18 + 9.0 / 2.0 * t62 * (9.0 / 4.0 * t50 * t47 + 7.0 / 2.0 * t36 - 7.0 / 3.0 * t41 + 3.0 / 2.0 * t69 * t7) * t18;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::Hp_numEqns() const { return 1; }

  void
  ICLOCS_TwoLinkRobotArm::Hp_eval(
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
    real_type t2   = U__[iU_u1];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_u2];
    real_type t5   = t4 * t4;
    real_type t9   = X__[iX_theta];
    real_type t10  = sin(t9);
    real_type t11  = cos(t9);
    real_type t12  = t11 * t10;
    real_type t13  = X__[iX_omega__alpha];
    real_type t14  = t13 * t13;
    real_type t17  = X__[iX_omega__beta];
    real_type t18  = t17 * t17;
    real_type t26  = t10 * t10;
    real_type t29  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t26);
    result__[ 0   ] = (t3 + t5) * ModelPars[iM_rho] + t29 * (9.0 / 4.0 * t14 * t12 + 2 * t18 + 4.0 / 3.0 * t2 - 4.0 / 3.0 * t4 - 3.0 / 2.0 * t4 * t11) * L__[iL_lambda1__xo] - t29 * (9.0 / 4.0 * t18 * t12 + 7.0 / 2.0 * t14 - 7.0 / 3.0 * t4 + 3.0 / 2.0 * (t2 - t4) * t11) * L__[iL_lambda2__xo] + (t17 - t13) * L__[iL_lambda3__xo] + t13 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DHxDxp_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::DHxDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DHxDxp_nnz()     const { return 10; }

  void
  ICLOCS_TwoLinkRobotArm::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 4   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::DHxDxp_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = cos(t4);
    real_type t7   = t6 * t5;
    real_type t8   = t5 * t5;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    real_type t12  = t11 * t7;
    real_type t15  = L__[iL_lambda2__xo];
    real_type t16  = t2 * t15;
    result__[ 0   ] = 9.0 / 2.0 * t12 * t3 - 7 * t11 * t16;
    real_type t19  = t6 * t6;
    real_type t20  = X__[iX_omega__alpha];
    real_type t21  = t20 * t19;
    real_type t25  = t20 * t8;
    real_type t30  = t10 * t10;
    real_type t31  = 1.0 / t30;
    real_type t34  = 0.81e2 / 4.0 * t31 * t21 * t8 * t3;
    real_type t37  = t6 * t5 * t31;
    real_type t39  = 0.63e2 / 2.0 * t37 * t20 * t16;
    result__[ 1   ] = 9.0 / 2.0 * t11 * t21 * t3 - 9.0 / 2.0 * t11 * t25 * t3 - t34 + t39;
    real_type t48  = L__[iL_lambda3__xo];
    result__[ 2   ] = 9.0 / 2.0 * t11 * t20 * t6 * t5 * t1 - 7 * t11 * t20 * t15 - t48 + L__[iL_lambda4__xo];
    result__[ 3   ] = 4 * t11 * t3 - 9.0 / 2.0 * t12 * t16;
    real_type t54  = X__[iX_omega__beta];
    real_type t57  = 18 * t37 * t54 * t3;
    real_type t58  = t54 * t19;
    real_type t62  = t54 * t8;
    real_type t69  = 0.81e2 / 4.0 * t31 * t58 * t8 * t16;
    result__[ 4   ] = -t57 - 9.0 / 2.0 * t11 * t58 * t16 + 9.0 / 2.0 * t11 * t62 * t16 + t69;
    result__[ 5   ] = 4 * t11 * t54 * t1 - 9.0 / 2.0 * t11 * t54 * t6 * t5 * t15 + t48;
    result__[ 6   ] = t11 * (9.0 / 2.0 * t21 - 9.0 / 2.0 * t25) * t3 - t34 + t39;
    result__[ 7   ] = -t57 - t11 * (9.0 / 2.0 * t58 - 9.0 / 2.0 * t62) * t16 + t69;
    real_type t86  = t20 * t20;
    real_type t87  = t86 * t7;
    real_type t89  = U__[iU_u2];
    real_type t91  = 3.0 / 2.0 * t89 * t6;
    real_type t101 = 9.0 / 4.0 * t86 * t19 - 9.0 / 4.0 * t86 * t8 + 3.0 / 2.0 * t89 * t5;
    real_type t106 = t54 * t54;
    real_type t108 = U__[iU_u1];
    real_type t111 = 9.0 / 4.0 * t87 + 2 * t106 + 4.0 / 3.0 * t108 - 4.0 / 3.0 * t89 - t91;
    real_type t116 = t19 * t8 / t30 / t10;
    real_type t119 = t31 * t111;
    real_type t126 = t106 * t7;
    real_type t128 = t108 - t89;
    real_type t130 = 3.0 / 2.0 * t128 * t6;
    real_type t140 = 9.0 / 4.0 * t106 * t19 - 9.0 / 4.0 * t106 * t8 - 3.0 / 2.0 * t128 * t5;
    real_type t147 = 9.0 / 4.0 * t126 + 7.0 / 2.0 * t86 - 7.0 / 3.0 * t89 + t130;
    real_type t151 = t31 * t147;
    result__[ 8   ] = t11 * (-9 * t87 + t91) * t3 - 9 * t37 * t101 * t3 + 0.81e2 / 2.0 * t116 * t111 * t3 - 9.0 / 2.0 * t19 * t119 * t3 + 9.0 / 2.0 * t8 * t119 * t3 - t11 * (-9 * t126 - t130) * t16 + 9 * t37 * t140 * t16 - 0.81e2 / 2.0 * t116 * t147 * t16 + 9.0 / 2.0 * t19 * t151 * t16 - 9.0 / 2.0 * t8 * t151 * t16;
    result__[ 9   ] = t11 * t101 * t1 - 9.0 / 2.0 * t37 * t111 * t1 - t11 * t140 * t15 + 9.0 / 2.0 * t37 * t147 * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DHpDp_numRows() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DHpDp_numCols() const { return 1; }
  integer ICLOCS_TwoLinkRobotArm::DHpDp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DHpDp_sparse(
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

  integer ICLOCS_TwoLinkRobotArm::Hu_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::Hu_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * ModelPars[iM_rho];
    real_type t8   = t2 * L__[iL_lambda1__xo];
    real_type t9   = X__[iX_theta];
    real_type t10  = sin(t9);
    real_type t11  = t10 * t10;
    real_type t14  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t11);
    real_type t18  = t2 * L__[iL_lambda2__xo];
    real_type t19  = cos(t9);
    result__[ 0   ] = 2 * U__[iU_u1] * t3 + 4.0 / 3.0 * t14 * t8 - 3.0 / 2.0 * t14 * t19 * t18;
    real_type t26  = 3.0 / 2.0 * t19;
    result__[ 1   ] = 2 * U__[iU_u2] * t3 + t14 * (-4.0 / 3.0 - t26) * t8 - t14 * (-7.0 / 3.0 - t26) * t18;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DHuDxp_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DHuDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DHuDxp_nnz()     const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 4   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::DHuDxp_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t8   = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t6;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = cos(t4);
    real_type t13  = t12 * t5 * t10;
    real_type t16  = L__[iL_lambda2__xo];
    real_type t17  = t2 * t16;
    real_type t18  = 1.0 / t8;
    real_type t19  = t18 * t5;
    real_type t21  = 3.0 / 2.0 * t19 * t17;
    real_type t22  = t12 * t12;
    result__[ 0   ] = -6 * t13 * t3 + t21 + 0.27e2 / 4.0 * t5 * t10 * t22 * t17;
    real_type t27  = ModelPars[iM_rho];
    result__[ 1   ] = 2 * U__[iU_u1] * t27 + 4.0 / 3.0 * t18 * t1 - 3.0 / 2.0 * t18 * t12 * t16;
    real_type t38  = 3.0 / 2.0 * t12;
    real_type t39  = -4.0 / 3.0 - t38;
    real_type t43  = -7.0 / 3.0 - t38;
    result__[ 2   ] = 3.0 / 2.0 * t19 * t3 - 9.0 / 2.0 * t13 * t39 * t3 - t21 + 9.0 / 2.0 * t13 * t43 * t17;
    result__[ 3   ] = t18 * t39 * t1 - t18 * t43 * t16 + 2 * U__[iU_u2] * t27;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 4, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::eta_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::eta_eval(
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
    result__[ 3   ] = L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DetaDxp_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::DetaDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DetaDxp_sparse(
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

  integer ICLOCS_TwoLinkRobotArm::nu_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::nu_eval(
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
    result__[ 3   ] = V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DnuDxp_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::DnuDxp_numCols() const { return 5; }
  integer ICLOCS_TwoLinkRobotArm::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc
