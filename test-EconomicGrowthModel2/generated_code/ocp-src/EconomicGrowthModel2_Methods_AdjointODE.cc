/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_AdjointODE.cc                     |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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


namespace EconomicGrowthModel2Define {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::JPx_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::JPx_eval(
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
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::LTx_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::LTx_eval(
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
    real_type t2   = ALIAS_Tpositive_D(-X__[iX_T]);
    result__[ 4   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::JUx_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::JUx_eval(
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
    result__[ 4   ] = uControl(U__[iU_u], 0, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::JPp_numEqns() const { return 0; }

  void
  EconomicGrowthModel2::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::LTp_numEqns() const { return 0; }

  void
  EconomicGrowthModel2::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::JUp_numEqns() const { return 0; }

  void
  EconomicGrowthModel2::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::JPu_numEqns() const { return 1; }

  void
  EconomicGrowthModel2::JPu_eval(
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

  integer EconomicGrowthModel2::LTu_numEqns() const { return 1; }

  void
  EconomicGrowthModel2::LTu_eval(
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

  integer EconomicGrowthModel2::JUu_numEqns() const { return 1; }

  void
  EconomicGrowthModel2::JUu_eval(
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

  integer EconomicGrowthModel2::LTargs_numEqns() const { return 1; }

  void
  EconomicGrowthModel2::LTargs_eval(
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
  integer EconomicGrowthModel2::DJPxDxp_numRows() const { return 5; }
  integer EconomicGrowthModel2::DJPxDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DJPxDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DLTxDxp_numRows() const { return 5; }
  integer EconomicGrowthModel2::DLTxDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DLTxDxp_nnz()     const { return 1; }

  void
  EconomicGrowthModel2::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
  }


  void
  EconomicGrowthModel2::DLTxDxp_sparse(
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
  integer EconomicGrowthModel2::DJUxDxp_numRows() const { return 5; }
  integer EconomicGrowthModel2::DJUxDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DJUxDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DJPuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel2::DJPuDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DJPuDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DLTuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel2::DLTuDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DLTuDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DJUuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel2::DJUuDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DJUuDxp_nnz()     const { return 1; }

  void
  EconomicGrowthModel2::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }


  void
  EconomicGrowthModel2::DJUuDxp_sparse(
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
  integer EconomicGrowthModel2::DJPpDp_numRows() const { return 0; }
  integer EconomicGrowthModel2::DJPpDp_numCols() const { return 0; }
  integer EconomicGrowthModel2::DJPpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DLTpDp_numRows() const { return 0; }
  integer EconomicGrowthModel2::DLTpDp_numCols() const { return 0; }
  integer EconomicGrowthModel2::DLTpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DJUpDp_numRows() const { return 0; }
  integer EconomicGrowthModel2::DJUpDp_numCols() const { return 0; }
  integer EconomicGrowthModel2::DJUpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DLTargsDxup_numRows() const { return 1; }
  integer EconomicGrowthModel2::DLTargsDxup_numCols() const { return 6; }
  integer EconomicGrowthModel2::DLTargsDxup_nnz()     const { return 1; }

  void
  EconomicGrowthModel2::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
  }


  void
  EconomicGrowthModel2::DLTargsDxup_sparse(
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
  integer EconomicGrowthModel2::D2LTargsD2xup_numRows() const { return 6; }
  integer EconomicGrowthModel2::D2LTargsD2xup_numCols() const { return 6; }
  integer EconomicGrowthModel2::D2LTargsD2xup_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::D2LTargsD2xup_sparse(
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

  integer EconomicGrowthModel2::Hx_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::Hx_eval(
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
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda4__xo];
    result__[ 0   ] = t8 * t12 + t8 * t3;
    real_type t14  = Q_D_2(t4, t5);
    real_type t15  = t7 * t14;
    result__[ 1   ] = t15 * t12 + t15 * t3;
    real_type t18  = L__[iL_lambda1__xo];
    result__[ 2   ] = t7 * t18;
    real_type t19  = L__[iL_lambda3__xo];
    result__[ 3   ] = t7 * t19;
    real_type t22  = Q(t4, t5);
    result__[ 4   ] = t22 * t12 + X__[iX_y1] * t18 + X__[iX_y2] * t19 + t22 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer EconomicGrowthModel2::Hp_numEqns() const { return 0; }

  void
  EconomicGrowthModel2::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DHxDxp_numRows() const { return 5; }
  integer EconomicGrowthModel2::DHxDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DHxDxp_nnz()     const { return 12; }

  void
  EconomicGrowthModel2::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 1   ;
    iIndex[10] = 4   ; jIndex[10] = 2   ;
    iIndex[11] = 4   ; jIndex[11] = 3   ;
  }


  void
  EconomicGrowthModel2::DHxDxp_sparse(
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
    real_type t3   = t2 * L__[iL_lambda2__xo];
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = Q_D_1_1(t4, t5);
    real_type t7   = X__[iX_T];
    real_type t8   = t7 * t6;
    real_type t12  = (1 - t2) * L__[iL_lambda4__xo];
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
    result__[ 6   ] = L__[iL_lambda1__xo];
    result__[ 7   ] = L__[iL_lambda3__xo];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    result__[ 10  ] = result__[6];
    result__[ 11  ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DHpDp_numRows() const { return 0; }
  integer EconomicGrowthModel2::DHpDp_numCols() const { return 0; }
  integer EconomicGrowthModel2::DHpDp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DHpDp_sparse(
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

  integer EconomicGrowthModel2::Hu_numEqns() const { return 1; }

  void
  EconomicGrowthModel2::Hu_eval(
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
    result__[ 0   ] = t6 * t4 * L__[iL_lambda2__xo] - t6 * t4 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DHuDxp_numRows() const { return 1; }
  integer EconomicGrowthModel2::DHuDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DHuDxp_nnz()     const { return 3; }

  void
  EconomicGrowthModel2::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
  }


  void
  EconomicGrowthModel2::DHuDxp_sparse(
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
    real_type t2   = X__[iX_x1];
    real_type t3   = X__[iX_x2];
    real_type t4   = Q_D_1(t2, t3);
    real_type t6   = X__[iX_T];
    real_type t8   = L__[iL_lambda4__xo];
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

  integer EconomicGrowthModel2::eta_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::eta_eval(
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
    result__[ 1   ] = L__[iL_lambda3__xo];
    result__[ 2   ] = L__[iL_lambda2__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DetaDxp_numRows() const { return 5; }
  integer EconomicGrowthModel2::DetaDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DetaDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DetaDxp_sparse(
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

  integer EconomicGrowthModel2::nu_numEqns() const { return 5; }

  void
  EconomicGrowthModel2::nu_eval(
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
    result__[ 1   ] = V__[2];
    result__[ 2   ] = V__[1];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer EconomicGrowthModel2::DnuDxp_numRows() const { return 5; }
  integer EconomicGrowthModel2::DnuDxp_numCols() const { return 5; }
  integer EconomicGrowthModel2::DnuDxp_nnz()     const { return 0; }

  void
  EconomicGrowthModel2::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  EconomicGrowthModel2::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: EconomicGrowthModel2_Methods_AdjointODE.cc
