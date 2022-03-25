/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_AdjointODE.cc                            |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::JPx_numEqns() const { return 3; }

  void
  GoddardRocket::JPx_eval(
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

  integer GoddardRocket::LTx_numEqns() const { return 3; }

  void
  GoddardRocket::LTx_eval(
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
    real_type t2   = ALIAS_vPositive_D(-X__[iX_v]);
    result__[ 1   ] = -t2;
    real_type t4   = ALIAS_massPositive_D(-X__[iX_m]);
    result__[ 2   ] = -t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::JUx_numEqns() const { return 3; }

  void
  GoddardRocket::JUx_eval(
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

  integer GoddardRocket::JPp_numEqns() const { return 1; }

  void
  GoddardRocket::JPp_eval(
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

  integer GoddardRocket::LTp_numEqns() const { return 1; }

  void
  GoddardRocket::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_TSPositive_D(-P__[iP_TimeSize]);
    result__[ 0   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::JUp_numEqns() const { return 1; }

  void
  GoddardRocket::JUp_eval(
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

  integer GoddardRocket::JPu_numEqns() const { return 1; }

  void
  GoddardRocket::JPu_eval(
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

  integer GoddardRocket::LTu_numEqns() const { return 1; }

  void
  GoddardRocket::LTu_eval(
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

  integer GoddardRocket::JUu_numEqns() const { return 1; }

  void
  GoddardRocket::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_TControl_D_1(U__[iU_T], 0, ModelPars[iM_Tmax]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::LTargs_numEqns() const { return 3; }

  void
  GoddardRocket::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_m];
    result__[ 1   ] = -X__[iX_v];
    result__[ 2   ] = -P__[iP_TimeSize];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DJPxDxp_numRows() const { return 3; }
  integer GoddardRocket::DJPxDxp_numCols() const { return 4; }
  integer GoddardRocket::DJPxDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DLTxDxp_numRows() const { return 3; }
  integer GoddardRocket::DLTxDxp_numCols() const { return 4; }
  integer GoddardRocket::DLTxDxp_nnz()     const { return 2; }

  void
  GoddardRocket::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 2   ;
  }


  void
  GoddardRocket::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_vPositive_DD(-X__[iX_v]);
    result__[ 1   ] = ALIAS_massPositive_DD(-X__[iX_m]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DJUxDxp_numRows() const { return 3; }
  integer GoddardRocket::DJUxDxp_numCols() const { return 4; }
  integer GoddardRocket::DJUxDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DJPuDxp_numRows() const { return 1; }
  integer GoddardRocket::DJPuDxp_numCols() const { return 4; }
  integer GoddardRocket::DJPuDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DLTuDxp_numRows() const { return 1; }
  integer GoddardRocket::DLTuDxp_numCols() const { return 4; }
  integer GoddardRocket::DLTuDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DJUuDxp_numRows() const { return 1; }
  integer GoddardRocket::DJUuDxp_numCols() const { return 4; }
  integer GoddardRocket::DJUuDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DJPpDp_numRows() const { return 1; }
  integer GoddardRocket::DJPpDp_numCols() const { return 1; }
  integer GoddardRocket::DJPpDp_nnz()     const { return 0; }

  void
  GoddardRocket::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DLTpDp_numRows() const { return 1; }
  integer GoddardRocket::DLTpDp_numCols() const { return 1; }
  integer GoddardRocket::DLTpDp_nnz()     const { return 1; }

  void
  GoddardRocket::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  GoddardRocket::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_TSPositive_DD(-P__[iP_TimeSize]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTpDp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DJUpDp_numRows() const { return 1; }
  integer GoddardRocket::DJUpDp_numCols() const { return 1; }
  integer GoddardRocket::DJUpDp_nnz()     const { return 0; }

  void
  GoddardRocket::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DLTargsDxup_numRows() const { return 3; }
  integer GoddardRocket::DLTargsDxup_numCols() const { return 5; }
  integer GoddardRocket::DLTargsDxup_nnz()     const { return 3; }

  void
  GoddardRocket::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
  }


  void
  GoddardRocket::DLTargsDxup_sparse(
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
    result__[ 2   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 3, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::D2LTargsD2xup_numRows() const { return 5; }
  integer GoddardRocket::D2LTargsD2xup_numCols() const { return 5; }
  integer GoddardRocket::D2LTargsD2xup_nnz()     const { return 0; }

  void
  GoddardRocket::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::D2LTargsD2xup_sparse(
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

  integer GoddardRocket::Hx_numEqns() const { return 3; }

  void
  GoddardRocket::Hx_eval(
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
    real_type t2   = P__[iP_TimeSize];
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    real_type t10  = gg_D(t4);
    result__[ 0   ] = (-t8 * t6 - t10) * t3;
    real_type t14  = DD_D_2(t4, t5);
    result__[ 1   ] = -t8 * t14 * t3 + t2 * L__[iL_lambda1__xo];
    real_type t18  = DD(t4, t5);
    real_type t20  = t7 * t7;
    result__[ 2   ] = -1.0 / t20 * (U__[iU_T] - t18) * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::Hp_numEqns() const { return 1; }

  void
  GoddardRocket::Hp_eval(
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
    real_type t2   = X__[iX_v];
    real_type t5   = U__[iU_T];
    real_type t6   = X__[iX_h];
    real_type t7   = DD(t6, t2);
    real_type t12  = gg(t6);
    result__[ 0   ] = t2 * L__[iL_lambda1__xo] + (1.0 / X__[iX_m] * (t5 - t7) - t12) * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t5 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DHxDxp_numRows() const { return 3; }
  integer GoddardRocket::DHxDxp_numCols() const { return 4; }
  integer GoddardRocket::DHxDxp_nnz()     const { return 12; }

  void
  GoddardRocket::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
  }


  void
  GoddardRocket::DHxDxp_sparse(
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
    real_type t3   = P__[iP_TimeSize] * t1;
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    real_type t10  = gg_DD(t4);
    result__[ 0   ] = (-t8 * t6 - t10) * t3;
    real_type t12  = DD_D_1_2(t4, t5);
    result__[ 1   ] = -t8 * t12 * t3;
    real_type t15  = DD_D_1(t4, t5);
    real_type t16  = t7 * t7;
    real_type t17  = 1.0 / t16;
    result__[ 2   ] = t17 * t15 * t3;
    real_type t20  = gg_D(t4);
    result__[ 3   ] = (-t8 * t15 - t20) * t1;
    result__[ 4   ] = result__[1];
    real_type t22  = DD_D_2_2(t4, t5);
    result__[ 5   ] = -t8 * t22 * t3;
    real_type t25  = DD_D_2(t4, t5);
    result__[ 6   ] = t17 * t25 * t3;
    result__[ 7   ] = -t8 * t25 * t1 + L__[iL_lambda1__xo];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t31  = DD(t4, t5);
    real_type t32  = U__[iU_T] - t31;
    result__[ 10  ] = 2 / t16 / t7 * t32 * t3;
    result__[ 11  ] = -t17 * t32 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DHpDp_numRows() const { return 1; }
  integer GoddardRocket::DHpDp_numCols() const { return 1; }
  integer GoddardRocket::DHpDp_nnz()     const { return 0; }

  void
  GoddardRocket::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DHpDp_sparse(
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

  integer GoddardRocket::Hu_numEqns() const { return 1; }

  void
  GoddardRocket::Hu_eval(
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
    real_type t2   = P__[iP_TimeSize];
    result__[ 0   ] = 1.0 / X__[iX_m] * t2 * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DHuDxp_numRows() const { return 1; }
  integer GoddardRocket::DHuDxp_numCols() const { return 4; }
  integer GoddardRocket::DHuDxp_nnz()     const { return 2; }

  void
  GoddardRocket::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
  }


  void
  GoddardRocket::DHuDxp_sparse(
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
    real_type t4   = X__[iX_m];
    real_type t5   = t4 * t4;
    result__[ 0   ] = -1.0 / t5 * P__[iP_TimeSize] * t1;
    result__[ 1   ] = 1.0 / t4 * t1 - L__[iL_lambda3__xo] / ModelPars[iM_c];
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

  integer GoddardRocket::eta_numEqns() const { return 3; }

  void
  GoddardRocket::eta_eval(
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
  integer GoddardRocket::DetaDxp_numRows() const { return 3; }
  integer GoddardRocket::DetaDxp_numCols() const { return 4; }
  integer GoddardRocket::DetaDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DetaDxp_sparse(
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

  integer GoddardRocket::nu_numEqns() const { return 3; }

  void
  GoddardRocket::nu_eval(
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
  integer GoddardRocket::DnuDxp_numRows() const { return 3; }
  integer GoddardRocket::DnuDxp_numCols() const { return 4; }
  integer GoddardRocket::DnuDxp_nnz()     const { return 0; }

  void
  GoddardRocket::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  GoddardRocket::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: GoddardRocket_Methods_AdjointODE.cc
