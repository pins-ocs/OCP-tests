/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_AdjointODE.cc                    |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace LUUS_DrugDisplacementDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::JPx_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::JPx_eval(
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

  integer LUUS_DrugDisplacement::LTx_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::LTx_eval(
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
      Mechatronix::check_in_segment( result__, "LTx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::JUx_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::JUx_eval(
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

  integer LUUS_DrugDisplacement::JPp_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::JPp_eval(
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

  integer LUUS_DrugDisplacement::LTp_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::LTp_eval(
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

  integer LUUS_DrugDisplacement::JUp_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = uControl(U__[iU_u], 0, 8);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::JPu_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::JPu_eval(
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

  integer LUUS_DrugDisplacement::LTu_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::LTu_eval(
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

  integer LUUS_DrugDisplacement::JUu_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ALIAS_uControl_D_1(U__[iU_u], 0, 8);
    result__[ 0   ] = t3 * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::LTargs_numEqns() const { return 0; }

  void
  LUUS_DrugDisplacement::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DJPxDxp_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::DJPxDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DJPxDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DLTxDxp_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::DLTxDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DLTxDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DJUxDxp_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::DJUxDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DJUxDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DJPuDxp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DJPuDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DJPuDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DLTuDxp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DLTuDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DLTuDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DJUuDxp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DJUuDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DJUuDxp_nnz()     const { return 1; }

  void
  LUUS_DrugDisplacement::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }


  void
  LUUS_DrugDisplacement::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], 0, 8);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DJPpDp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DJPpDp_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DJPpDp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DLTpDp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DLTpDp_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DLTpDp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DJUpDp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DJUpDp_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DJUpDp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DLTargsDxup_numRows() const { return 0; }
  integer LUUS_DrugDisplacement::DLTargsDxup_numCols() const { return 4; }
  integer LUUS_DrugDisplacement::DLTargsDxup_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::D2LTargsD2xup_numRows() const { return 4; }
  integer LUUS_DrugDisplacement::D2LTargsD2xup_numCols() const { return 4; }
  integer LUUS_DrugDisplacement::D2LTargsD2xup_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::D2LTargsD2xup_sparse(
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

  integer LUUS_DrugDisplacement::Hx_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::Hx_eval(
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
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t8   = 0.2e-1 - t4;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t5;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t4;
    real_type t18  = g1(t4, t5);
    real_type t19  = g4_D_1(t4, t5);
    real_type t27  = t2 * L__[iL_lambda2__xo];
    real_type t28  = g3(t4, t5);
    real_type t31  = t12 * t28 + 0.928e0 - 0.464e2 * t4;
    real_type t34  = g3_D_1(t4, t5);
    result__[ 0   ] = t15 * t6 * t3 + (t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t5) * t18 * t3 + t31 * t6 * t27 + (t12 * t34 - 0.464e2) * t18 * t27;
    real_type t39  = g1_D_2(t4, t5);
    real_type t42  = g4_D_2(t4, t5);
    real_type t50  = g3_D_2(t4, t5);
    result__[ 1   ] = t15 * t39 * t3 + (t8 * t42 - 0.928e2 * t4) * t18 * t3 + t31 * t39 * t27 + (t12 * t50 - 2 * t28) * t18 * t27;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::Hp_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::Hp_eval(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = g1(t2, t3);
    real_type t6   = g4(t2, t3);
    real_type t11  = U__[iU_u] - 2 * t3;
    real_type t18  = g3(t2, t3);
    result__[ 0   ] = ((0.2e-1 - t2) * t6 + 0.464e2 * t11 * t2) * t4 * L__[iL_lambda1__xo] + (t11 * t18 + 0.928e0 - 0.464e2 * t2) * t4 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DHxDxp_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::DHxDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DHxDxp_nnz()     const { return 6; }

  void
  LUUS_DrugDisplacement::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
  }


  void
  LUUS_DrugDisplacement::DHxDxp_sparse(
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
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1_1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t8   = 0.2e-1 - t4;
    real_type t10  = U__[iU_u];
    real_type t12  = t10 - 2 * t5;
    real_type t15  = t8 * t7 + 0.464e2 * t12 * t4;
    real_type t18  = g1_D_1(t4, t5);
    real_type t19  = g4_D_1(t4, t5);
    real_type t23  = t8 * t19 - t7 + 0.464e2 * t10 - 0.928e2 * t5;
    real_type t27  = g1(t4, t5);
    real_type t28  = g4_D_1_1(t4, t5);
    real_type t34  = L__[iL_lambda2__xo];
    real_type t35  = t2 * t34;
    real_type t36  = g3(t4, t5);
    real_type t39  = t12 * t36 + 0.928e0 - 0.464e2 * t4;
    real_type t42  = g3_D_1(t4, t5);
    real_type t44  = t12 * t42 - 0.464e2;
    real_type t48  = g3_D_1_1(t4, t5);
    result__[ 0   ] = t15 * t6 * t3 + 2 * t23 * t18 * t3 + (t8 * t28 - 2 * t19) * t27 * t3 + t39 * t6 * t35 + 2 * t44 * t18 * t35 + t12 * t48 * t27 * t35;
    real_type t52  = g1_D_1_2(t4, t5);
    real_type t55  = g4_D_2(t4, t5);
    real_type t58  = t8 * t55 - 0.928e2 * t4;
    real_type t61  = g1_D_2(t4, t5);
    real_type t64  = g4_D_1_2(t4, t5);
    real_type t71  = g3_D_2(t4, t5);
    real_type t74  = t12 * t71 - 2 * t36;
    real_type t79  = g3_D_1_2(t4, t5);
    result__[ 1   ] = t15 * t52 * t3 + t58 * t18 * t3 + t23 * t61 * t3 + (t8 * t64 - t55 - 0.928e2) * t27 * t3 + t39 * t52 * t35 + t74 * t18 * t35 + t44 * t61 * t35 + (t12 * t79 - 2 * t42) * t27 * t35;
    real_type t87  = t27 * t1;
    real_type t91  = t27 * t34;
    result__[ 2   ] = t15 * t18 * t1 + t39 * t18 * t34 + t23 * t87 + t44 * t91;
    result__[ 3   ] = result__[1];
    real_type t93  = g1_D_2_2(t4, t5);
    real_type t99  = g4_D_2_2(t4, t5);
    real_type t108 = g3_D_2_2(t4, t5);
    result__[ 4   ] = t15 * t93 * t3 + 2 * t58 * t61 * t3 + t8 * t99 * t27 * t3 + t39 * t93 * t35 + 2 * t74 * t61 * t35 + (t12 * t108 - 4 * t71) * t27 * t35;
    result__[ 5   ] = t15 * t61 * t1 + t39 * t61 * t34 + t58 * t87 + t74 * t91;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DHpDp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DHpDp_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DHpDp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DHpDp_sparse(
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

  integer LUUS_DrugDisplacement::Hu_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::Hu_eval(
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
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1(t4, t5);
    real_type t12  = g3(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t2 * L__[iL_lambda1__xo] + t12 * t6 * t2 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DHuDxp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DHuDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DHuDxp_nnz()     const { return 3; }

  void
  LUUS_DrugDisplacement::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }


  void
  LUUS_DrugDisplacement::DHuDxp_sparse(
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
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t10  = g1(t4, t5);
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t2 * t13;
    real_type t15  = g3(t4, t5);
    real_type t18  = g3_D_1(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t3 + 0.464e2 * t10 * t3 + t15 * t6 * t14 + t18 * t10 * t14;
    real_type t21  = g1_D_2(t4, t5);
    real_type t27  = g3_D_2(t4, t5);
    result__[ 1   ] = 0.464e2 * t4 * t21 * t3 + t15 * t21 * t14 + t27 * t10 * t14;
    result__[ 2   ] = 0.464e2 * t4 * t10 * t1 + t15 * t10 * t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 3, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::eta_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::eta_eval(
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
  integer LUUS_DrugDisplacement::DetaDxp_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::DetaDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DetaDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DetaDxp_sparse(
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

  integer LUUS_DrugDisplacement::nu_numEqns() const { return 2; }

  void
  LUUS_DrugDisplacement::nu_eval(
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
  integer LUUS_DrugDisplacement::DnuDxp_numRows() const { return 2; }
  integer LUUS_DrugDisplacement::DnuDxp_numCols() const { return 3; }
  integer LUUS_DrugDisplacement::DnuDxp_nnz()     const { return 0; }

  void
  LUUS_DrugDisplacement::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  LUUS_DrugDisplacement::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: LUUS_DrugDisplacement_Methods_AdjointODE.cc
