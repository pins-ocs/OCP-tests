/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
#pragma warning( disable : 4189 )
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

  integer ICLOCS_TwoLinkRobotArm::JP_numEqns() const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::LT_numEqns() const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::JU_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::JU_eval(
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
    real_type t3   = u1Control(U__[iU_u1], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = u2Control(U__[iU_u2], -1, 1);
    result__[ 1   ] = t5 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
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
  integer ICLOCS_TwoLinkRobotArm::DJPDxpu_numRows() const { return 0; }
  integer ICLOCS_TwoLinkRobotArm::DJPDxpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::DJPDxpu_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DLTDxpu_numRows() const { return 0; }
  integer ICLOCS_TwoLinkRobotArm::DLTDxpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::DLTDxpu_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DJUDxpu_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DJUDxpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::DJUDxpu_nnz()     const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 6   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    result__[ 0   ] = u1Control(t1, -1, 1);
    real_type t2   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1(t1, -1, 1);
    result__[ 1   ] = t3 * t2;
    real_type t4   = U__[iU_u2];
    result__[ 2   ] = u2Control(t4, -1, 1);
    real_type t5   = ALIAS_u2Control_D_1(t4, -1, 1);
    result__[ 3   ] = t5 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DLTargsDxpu_numRows() const { return 0; }
  integer ICLOCS_TwoLinkRobotArm::DLTargsDxpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::DLTargsDxpu_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2JPD2xpu_numRows() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2JPD2xpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2JPD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2LTD2xpu_numRows() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2LTD2xpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2LTD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2JUD2xpu_numRows() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2JUD2xpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2JUD2xpu_nnz()     const { return 6; }

  void
  ICLOCS_TwoLinkRobotArm::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 5   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 6   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 6   ; jIndex[5 ] = 6   ;
  }


  void
  ICLOCS_TwoLinkRobotArm::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = ALIAS_u1Control_D_1(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = t3 * t2;
    real_type t4   = U__[iU_u2];
    real_type t5   = ALIAS_u2Control_D_1(t4, -1, 1);
    real_type t6   = OMEGA__[1];
    result__[ 1   ] = t6 * t5;
    result__[ 2   ] = result__[0];
    real_type t7   = P__[iP_T];
    real_type t8   = ALIAS_u1Control_D_1_1(t1, -1, 1);
    result__[ 3   ] = t3 * t8 * t7;
    result__[ 4   ] = result__[1];
    real_type t10  = ALIAS_u2Control_D_1_1(t4, -1, 1);
    result__[ 5   ] = t6 * t10 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 6, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::D2LTargsD2xpu_numRows() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2LTargsD2xpu_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_TwoLinkRobotArm::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_TwoLinkRobotArm::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_AdjointODE.cc
