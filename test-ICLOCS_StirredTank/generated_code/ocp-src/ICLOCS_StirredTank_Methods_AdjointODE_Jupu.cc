/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_AdjointODE.cc                       |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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
#pragma warning( disable : 4189 )
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

  real_type
  ICLOCS_StirredTank::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_StirredTank::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = uControl(U__[iU_u], 0, 2);
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ICLOCS_StirredTank::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t4   = tfbound(ModelPars[iM_T_min] - P__[iP_TimeSize]);
    real_type t5   = X__[iX_x1];
    real_type t6   = x1bound_min(-t5);
    real_type t8   = x1bound_max(t5 - 1);
    real_type t9   = X__[iX_x2];
    real_type t10  = x2bound_min(-t9);
    real_type t12  = x2bound_max(t9 - 1);
    real_type result__ = t4 + t6 + t8 + t10 + t12;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JPxpu_numEqns() const { return 4; }

  void
  ICLOCS_StirredTank::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::JUxpu_numEqns() const { return 4; }

  void
  ICLOCS_StirredTank::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = ALIAS_uControl_D_1(U__[iU_u], 0, 2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::LTxpu_numEqns() const { return 4; }

  void
  ICLOCS_StirredTank::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = ALIAS_x1bound_min_D(-t1);
    real_type t4   = ALIAS_x1bound_max_D(t1 - 1);
    result__[ 0   ] = -t2 + t4;
    real_type t5   = X__[iX_x2];
    real_type t6   = ALIAS_x2bound_min_D(-t5);
    real_type t8   = ALIAS_x2bound_max_D(t5 - 1);
    result__[ 1   ] = -t6 + t8;
    real_type t12  = ALIAS_tfbound_D(ModelPars[iM_T_min] - P__[iP_TimeSize]);
    result__[ 2   ] = -t12;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::LTargs_numEqns() const { return 5; }

  void
  ICLOCS_StirredTank::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
  integer ICLOCS_StirredTank::D2JPD2xpu_numRows() const { return 4; }
  integer ICLOCS_StirredTank::D2JPD2xpu_numCols() const { return 4; }
  integer ICLOCS_StirredTank::D2JPD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::D2LTD2xpu_numRows() const { return 4; }
  integer ICLOCS_StirredTank::D2LTD2xpu_numCols() const { return 4; }
  integer ICLOCS_StirredTank::D2LTD2xpu_nnz()     const { return 3; }

  void
  ICLOCS_StirredTank::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  void
  ICLOCS_StirredTank::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = ALIAS_x1bound_min_DD(-t1);
    real_type t4   = ALIAS_x1bound_max_DD(t1 - 1);
    result__[ 0   ] = t2 + t4;
    real_type t5   = X__[iX_x2];
    real_type t6   = ALIAS_x2bound_min_DD(-t5);
    real_type t8   = ALIAS_x2bound_max_DD(t5 - 1);
    result__[ 1   ] = t6 + t8;
    result__[ 2   ] = ALIAS_tfbound_DD(ModelPars[iM_T_min] - P__[iP_TimeSize]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::D2JUD2xpu_numRows() const { return 4; }
  integer ICLOCS_StirredTank::D2JUD2xpu_numCols() const { return 4; }
  integer ICLOCS_StirredTank::D2JUD2xpu_nnz()     const { return 1; }

  void
  ICLOCS_StirredTank::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 3   ;
  }


  void
  ICLOCS_StirredTank::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1_1(U__[iU_u], 0, 2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DLTargsDxpu_numRows() const { return 5; }
  integer ICLOCS_StirredTank::DLTargsDxpu_numCols() const { return 4; }
  integer ICLOCS_StirredTank::DLTargsDxpu_nnz()     const { return 5; }

  void
  ICLOCS_StirredTank::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 1   ;
  }


  void
  ICLOCS_StirredTank::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    result__[ 1   ] = -1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 5, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::D2LTargsD2xpu_numRows() const { return 4; }
  integer ICLOCS_StirredTank::D2LTargsD2xpu_numCols() const { return 4; }
  integer ICLOCS_StirredTank::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  ICLOCS_StirredTank::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS_StirredTank::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS_StirredTank_Methods_AdjointODE.cc
