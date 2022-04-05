/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel_Methods_AdjointODE.cc                      |
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


#include "EconomicGrowthModel.hh"
#include "EconomicGrowthModel_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModelDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::JPx_numEqns() const { return 3; }

  void
  EconomicGrowthModel::JPx_eval(
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

  integer EconomicGrowthModel::LTx_numEqns() const { return 3; }

  void
  EconomicGrowthModel::LTx_eval(
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
    real_type t2   = ALIAS_Tpositive_D(-X__[iX_T]);
    result__[ 2   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::JUx_numEqns() const { return 3; }

  void
  EconomicGrowthModel::JUx_eval(
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
    result__[ 2   ] = uControl(U__[iU_u], 0, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::JPp_numEqns() const { return 0; }

  void
  EconomicGrowthModel::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::LTp_numEqns() const { return 0; }

  void
  EconomicGrowthModel::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::JUp_numEqns() const { return 0; }

  void
  EconomicGrowthModel::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::JPu_numEqns() const { return 1; }

  void
  EconomicGrowthModel::JPu_eval(
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

  integer EconomicGrowthModel::LTu_numEqns() const { return 1; }

  void
  EconomicGrowthModel::LTu_eval(
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

  integer EconomicGrowthModel::JUu_numEqns() const { return 1; }

  void
  EconomicGrowthModel::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    result__[ 0   ] = t3 * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::LTargs_numEqns() const { return 1; }

  void
  EconomicGrowthModel::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DJPxDxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DJPxDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DJPxDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DLTxDxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DLTxDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DLTxDxp_nnz()     const { return 1; }

  void
  EconomicGrowthModel::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
  }


  void
  EconomicGrowthModel::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_Tpositive_DD(-X__[iX_T]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DJUxDxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DJUxDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DJUxDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DJPuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel::DJPuDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DJPuDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DLTuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel::DLTuDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DLTuDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DJUuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel::DJUuDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DJUuDxp_nnz()     const { return 1; }

  void
  EconomicGrowthModel::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }


  void
  EconomicGrowthModel::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DJPpDp_numRows() const { return 0; }
  integer EconomicGrowthModel::DJPpDp_numCols() const { return 0; }
  integer EconomicGrowthModel::DJPpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DLTpDp_numRows() const { return 0; }
  integer EconomicGrowthModel::DLTpDp_numCols() const { return 0; }
  integer EconomicGrowthModel::DLTpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DJUpDp_numRows() const { return 0; }
  integer EconomicGrowthModel::DJUpDp_numCols() const { return 0; }
  integer EconomicGrowthModel::DJUpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DLTargsDxup_numRows() const { return 1; }
  integer EconomicGrowthModel::DLTargsDxup_numCols() const { return 4; }
  integer EconomicGrowthModel::DLTargsDxup_nnz()     const { return 1; }

  void
  EconomicGrowthModel::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
  }


  void
  EconomicGrowthModel::DLTargsDxup_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 1, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::D2LTargsD2xup_numRows() const { return 4; }
  integer EconomicGrowthModel::D2LTargsD2xup_numCols() const { return 4; }
  integer EconomicGrowthModel::D2LTargsD2xup_nnz()     const { return 0; }

  void
  EconomicGrowthModel::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::D2LTargsD2xup_sparse(
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

  integer EconomicGrowthModel::Hx_numEqns() const { return 3; }

  void
  EconomicGrowthModel::Hx_eval(
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
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda2__xo];
    result__[ 0   ] = t8 * t12 + t8 * t3;
    real_type t14  = Q_D_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t15 * t12 + t15 * t3;
    real_type t18  = Q(t4, t5);
    result__[ 2   ] = t18 * t12 + t18 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel::Hp_numEqns() const { return 0; }

  void
  EconomicGrowthModel::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DHxDxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DHxDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DHxDxp_nnz()     const { return 8; }

  void
  EconomicGrowthModel::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
  }


  void
  EconomicGrowthModel::DHxDxp_sparse(
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
    real_type t2   = U__[iU_u];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda2__xo];
    result__[ 0   ] = t8 * t12 + t8 * t3;
    real_type t14  = Q_D_1_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t15 * t12 + t15 * t3;
    real_type t18  = Q_D_1(t4, t5);
    result__[ 2   ] = t18 * t12 + t18 * t3;
    result__[ 3   ] = result__[1];
    real_type t21  = Q_D_2_2(t4, t5);
    real_type t22  = t7 * t21;
    result__[ 4   ] = t22 * t12 + t22 * t3;
    real_type t25  = Q_D_2(t4, t5);
    result__[ 5   ] = t25 * t12 + t25 * t3;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DHpDp_numRows() const { return 0; }
  integer EconomicGrowthModel::DHpDp_numCols() const { return 0; }
  integer EconomicGrowthModel::DHpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DHpDp_sparse(
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

  integer EconomicGrowthModel::Hu_numEqns() const { return 1; }

  void
  EconomicGrowthModel::Hu_eval(
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
    real_type t4   = Q(X__[iX_x1], X__[iX_x2]);
    real_type t6   = X__[iX_T];
    result__[ 0   ] = t6 * t4 * L__[iL_lambda1__xo] - t6 * t4 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel::DHuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel::DHuDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DHuDxp_nnz()     const { return 3; }

  void
  EconomicGrowthModel::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }


  void
  EconomicGrowthModel::DHuDxp_sparse(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = Q_D_1(t2, t3);
    real_type t6   = X__[iX_T];
    real_type t8   = L__[iL_lambda2__xo];
    result__[ 0   ] = t6 * t4 * t1 - t6 * t4 * t8;
    real_type t11  = Q_D_2(t2, t3);
    result__[ 1   ] = t6 * t11 * t1 - t6 * t11 * t8;
    real_type t16  = Q(t2, t3);
    result__[ 2   ] = t16 * t1 - t16 * t8;
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

  integer EconomicGrowthModel::eta_numEqns() const { return 3; }

  void
  EconomicGrowthModel::eta_eval(
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
  integer EconomicGrowthModel::DetaDxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DetaDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DetaDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DetaDxp_sparse(
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

  integer EconomicGrowthModel::nu_numEqns() const { return 3; }

  void
  EconomicGrowthModel::nu_eval(
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
  integer EconomicGrowthModel::DnuDxp_numRows() const { return 3; }
  integer EconomicGrowthModel::DnuDxp_numCols() const { return 3; }
  integer EconomicGrowthModel::DnuDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: EconomicGrowthModel_Methods_AdjointODE.cc
