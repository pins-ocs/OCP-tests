/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_AdjointODE.cc                                 |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::JPx_numEqns() const { return 4; }

  void
  AlpRider::JPx_eval(
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

  integer AlpRider::LTx_numEqns() const { return 4; }

  void
  AlpRider::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = q_lower(Q__[iQ_zeta]);
    real_type t3   = X__[iX_y1];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_y2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y3];
    real_type t8   = t7 * t7;
    real_type t9   = X__[iX_y4];
    real_type t10  = t9 * t9;
    real_type t12  = ALIAS_Ybound_D(t2 - t4 - t6 - t8 - t10);
    result__[ 0   ] = -2 * t3 * t12;
    result__[ 1   ] = -2 * t5 * t12;
    result__[ 2   ] = -2 * t7 * t12;
    result__[ 3   ] = -2 * t9 * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::JUx_numEqns() const { return 4; }

  void
  AlpRider::JUx_eval(
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

  integer AlpRider::JPp_numEqns() const { return 0; }

  void
  AlpRider::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::LTp_numEqns() const { return 0; }

  void
  AlpRider::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::JUp_numEqns() const { return 0; }

  void
  AlpRider::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::JPu_numEqns() const { return 2; }

  void
  AlpRider::JPu_eval(
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

  integer AlpRider::LTu_numEqns() const { return 2; }

  void
  AlpRider::LTu_eval(
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

  integer AlpRider::JUu_numEqns() const { return 2; }

  void
  AlpRider::JUu_eval(
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
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::LTargs_numEqns() const { return 1; }

  void
  AlpRider::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = q_lower(Q__[iQ_zeta]);
    real_type t4   = X__[iX_y1] * X__[iX_y1];
    real_type t6   = X__[iX_y2] * X__[iX_y2];
    real_type t8   = X__[iX_y3] * X__[iX_y3];
    real_type t10  = X__[iX_y4] * X__[iX_y4];
    result__[ 0   ] = t2 - t4 - t6 - t8 - t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DJPxDxp_numRows() const { return 4; }
  integer AlpRider::DJPxDxp_numCols() const { return 4; }
  integer AlpRider::DJPxDxp_nnz()     const { return 0; }

  void
  AlpRider::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DLTxDxp_numRows() const { return 4; }
  integer AlpRider::DLTxDxp_numCols() const { return 4; }
  integer AlpRider::DLTxDxp_nnz()     const { return 16; }

  void
  AlpRider::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
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
    iIndex[12] = 3   ; jIndex[12] = 0   ;
    iIndex[13] = 3   ; jIndex[13] = 1   ;
    iIndex[14] = 3   ; jIndex[14] = 2   ;
    iIndex[15] = 3   ; jIndex[15] = 3   ;
  }


  void
  AlpRider::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = q_lower(Q__[iQ_zeta]);
    real_type t3   = X__[iX_y1];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_y2];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y3];
    real_type t8   = t7 * t7;
    real_type t9   = X__[iX_y4];
    real_type t10  = t9 * t9;
    real_type t11  = t2 - t4 - t6 - t8 - t10;
    real_type t12  = ALIAS_Ybound_DD(t11);
    real_type t15  = ALIAS_Ybound_D(t11);
    real_type t16  = 2 * t15;
    result__[ 0   ] = 4 * t4 * t12 - t16;
    result__[ 1   ] = 4 * t3 * t5 * t12;
    real_type t19  = t7 * t12;
    result__[ 2   ] = 4 * t3 * t19;
    real_type t21  = t9 * t12;
    result__[ 3   ] = 4 * t3 * t21;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = 4 * t6 * t12 - t16;
    result__[ 6   ] = 4 * t5 * t19;
    result__[ 7   ] = 4 * t5 * t21;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    result__[ 10  ] = 4 * t8 * t12 - t16;
    result__[ 11  ] = 4 * t7 * t21;
    result__[ 12  ] = result__[3];
    result__[ 13  ] = result__[7];
    result__[ 14  ] = result__[11];
    result__[ 15  ] = 4 * t10 * t12 - t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DJUxDxp_numRows() const { return 4; }
  integer AlpRider::DJUxDxp_numCols() const { return 4; }
  integer AlpRider::DJUxDxp_nnz()     const { return 0; }

  void
  AlpRider::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DJPuDxp_numRows() const { return 2; }
  integer AlpRider::DJPuDxp_numCols() const { return 4; }
  integer AlpRider::DJPuDxp_nnz()     const { return 0; }

  void
  AlpRider::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DLTuDxp_numRows() const { return 2; }
  integer AlpRider::DLTuDxp_numCols() const { return 4; }
  integer AlpRider::DLTuDxp_nnz()     const { return 0; }

  void
  AlpRider::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DJUuDxp_numRows() const { return 2; }
  integer AlpRider::DJUuDxp_numCols() const { return 4; }
  integer AlpRider::DJUuDxp_nnz()     const { return 0; }

  void
  AlpRider::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DJPpDp_numRows() const { return 0; }
  integer AlpRider::DJPpDp_numCols() const { return 0; }
  integer AlpRider::DJPpDp_nnz()     const { return 0; }

  void
  AlpRider::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DLTpDp_numRows() const { return 0; }
  integer AlpRider::DLTpDp_numCols() const { return 0; }
  integer AlpRider::DLTpDp_nnz()     const { return 0; }

  void
  AlpRider::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DJUpDp_numRows() const { return 0; }
  integer AlpRider::DJUpDp_numCols() const { return 0; }
  integer AlpRider::DJUpDp_nnz()     const { return 0; }

  void
  AlpRider::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DLTargsDxup_numRows() const { return 1; }
  integer AlpRider::DLTargsDxup_numCols() const { return 6; }
  integer AlpRider::DLTargsDxup_nnz()     const { return 4; }

  void
  AlpRider::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
  }


  void
  AlpRider::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -2 * X__[iX_y1];
    result__[ 1   ] = -2 * X__[iX_y2];
    result__[ 2   ] = -2 * X__[iX_y3];
    result__[ 3   ] = -2 * X__[iX_y4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 4, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::D2LTargsD2xup_numRows() const { return 6; }
  integer AlpRider::D2LTargsD2xup_numCols() const { return 6; }
  integer AlpRider::D2LTargsD2xup_nnz()     const { return 4; }

  void
  AlpRider::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  void
  AlpRider::D2LTargsD2xup_sparse(
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
    result__[ 0   ] = -2 * OMEGA__[0];
    result__[ 1   ] = result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xup_sparse", 4, i_segment );
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

  integer AlpRider::Hx_numEqns() const { return 4; }

  void
  AlpRider::Hx_eval(
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
    real_type t1   = ModelPars[iM_W];
    result__[ 0   ] = 2 * X__[iX_y1] * t1 - 10 * L__[iL_lambda1__xo];
    result__[ 1   ] = 2 * X__[iX_y2] * t1 - 2 * L__[iL_lambda2__xo];
    real_type t14  = L__[iL_lambda3__xo];
    real_type t16  = L__[iL_lambda4__xo];
    result__[ 2   ] = 2 * X__[iX_y3] * t1 - 3 * t14 + 5 * t16;
    result__[ 3   ] = 2 * X__[iX_y4] * t1 + 5 * t14 - 3 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer AlpRider::Hp_numEqns() const { return 0; }

  void
  AlpRider::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DHxDxp_numRows() const { return 4; }
  integer AlpRider::DHxDxp_numCols() const { return 4; }
  integer AlpRider::DHxDxp_nnz()     const { return 4; }

  void
  AlpRider::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  void
  AlpRider::DHxDxp_sparse(
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
    result__[ 0   ] = 2 * ModelPars[iM_W];
    result__[ 1   ] = result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DHpDp_numRows() const { return 0; }
  integer AlpRider::DHpDp_numCols() const { return 0; }
  integer AlpRider::DHpDp_nnz()     const { return 0; }

  void
  AlpRider::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DHpDp_sparse(
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

  integer AlpRider::Hu_numEqns() const { return 2; }

  void
  AlpRider::Hu_eval(
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
    real_type t3   = L__[iL_lambda1__xo];
    real_type t4   = L__[iL_lambda2__xo];
    real_type t5   = L__[iL_lambda3__xo];
    real_type t6   = L__[iL_lambda4__xo];
    result__[ 0   ] = U__[iU_u1] / 50 + t3 + t4 + t5 + t6;
    result__[ 1   ] = U__[iU_u2] / 50 + t3 + 2 * t4 - t5 + 3 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DHuDxp_numRows() const { return 2; }
  integer AlpRider::DHuDxp_numCols() const { return 4; }
  integer AlpRider::DHuDxp_nnz()     const { return 0; }

  void
  AlpRider::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DHuDxp_sparse(
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

  integer AlpRider::eta_numEqns() const { return 4; }

  void
  AlpRider::eta_eval(
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
  integer AlpRider::DetaDxp_numRows() const { return 4; }
  integer AlpRider::DetaDxp_numCols() const { return 4; }
  integer AlpRider::DetaDxp_nnz()     const { return 0; }

  void
  AlpRider::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DetaDxp_sparse(
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

  integer AlpRider::nu_numEqns() const { return 4; }

  void
  AlpRider::nu_eval(
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
  integer AlpRider::DnuDxp_numRows() const { return 4; }
  integer AlpRider::DnuDxp_numCols() const { return 4; }
  integer AlpRider::DnuDxp_nnz()     const { return 0; }

  void
  AlpRider::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  AlpRider::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: AlpRider_Methods_AdjointODE.cc
