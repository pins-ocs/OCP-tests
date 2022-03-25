/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_AdjointODE.cc                               |
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


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
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


namespace UnderwaterDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::JPx_numEqns() const { return 6; }

  void
  Underwater::JPx_eval(
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
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::LTx_numEqns() const { return 6; }

  void
  Underwater::LTx_eval(
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
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::JUx_numEqns() const { return 6; }

  void
  Underwater::JUx_eval(
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
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::JPp_numEqns() const { return 1; }

  void
  Underwater::JPp_eval(
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

  integer Underwater::LTp_numEqns() const { return 1; }

  void
  Underwater::LTp_eval(
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

  integer Underwater::JUp_numEqns() const { return 1; }

  void
  Underwater::JUp_eval(
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
    real_type t6   = u3Control(U__[iU_u3], -1, 1);
    result__[ 0   ] = t2 + t4 + t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::JPu_numEqns() const { return 3; }

  void
  Underwater::JPu_eval(
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
      Mechatronix::check_in_segment( result__, "JPu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::LTu_numEqns() const { return 3; }

  void
  Underwater::LTu_eval(
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
      Mechatronix::check_in_segment( result__, "LTu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::JUu_numEqns() const { return 3; }

  void
  Underwater::JUu_eval(
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
    real_type t7   = ALIAS_u3Control_D_1(U__[iU_u3], -1, 1);
    result__[ 2   ] = t7 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::LTargs_numEqns() const { return 0; }

  void
  Underwater::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DJPxDxp_numRows() const { return 6; }
  integer Underwater::DJPxDxp_numCols() const { return 7; }
  integer Underwater::DJPxDxp_nnz()     const { return 0; }

  void
  Underwater::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DLTxDxp_numRows() const { return 6; }
  integer Underwater::DLTxDxp_numCols() const { return 7; }
  integer Underwater::DLTxDxp_nnz()     const { return 0; }

  void
  Underwater::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DJUxDxp_numRows() const { return 6; }
  integer Underwater::DJUxDxp_numCols() const { return 7; }
  integer Underwater::DJUxDxp_nnz()     const { return 0; }

  void
  Underwater::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DJPuDxp_numRows() const { return 3; }
  integer Underwater::DJPuDxp_numCols() const { return 7; }
  integer Underwater::DJPuDxp_nnz()     const { return 0; }

  void
  Underwater::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DLTuDxp_numRows() const { return 3; }
  integer Underwater::DLTuDxp_numCols() const { return 7; }
  integer Underwater::DLTuDxp_nnz()     const { return 0; }

  void
  Underwater::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DJUuDxp_numRows() const { return 3; }
  integer Underwater::DJUuDxp_numCols() const { return 7; }
  integer Underwater::DJUuDxp_nnz()     const { return 3; }

  void
  Underwater::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 6   ;
  }


  void
  Underwater::DJUuDxp_sparse(
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
    result__[ 2   ] = ALIAS_u3Control_D_1(U__[iU_u3], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DJPpDp_numRows() const { return 1; }
  integer Underwater::DJPpDp_numCols() const { return 1; }
  integer Underwater::DJPpDp_nnz()     const { return 0; }

  void
  Underwater::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DLTpDp_numRows() const { return 1; }
  integer Underwater::DLTpDp_numCols() const { return 1; }
  integer Underwater::DLTpDp_nnz()     const { return 0; }

  void
  Underwater::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DJUpDp_numRows() const { return 1; }
  integer Underwater::DJUpDp_numCols() const { return 1; }
  integer Underwater::DJUpDp_nnz()     const { return 0; }

  void
  Underwater::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DLTargsDxup_numRows() const { return 0; }
  integer Underwater::DLTargsDxup_numCols() const { return 10; }
  integer Underwater::DLTargsDxup_nnz()     const { return 0; }

  void
  Underwater::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::D2LTargsD2xup_numRows() const { return 10; }
  integer Underwater::D2LTargsD2xup_numCols() const { return 10; }
  integer Underwater::D2LTargsD2xup_nnz()     const { return 0; }

  void
  Underwater::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::D2LTargsD2xup_sparse(
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

  integer Underwater::Hx_numEqns() const { return 6; }

  void
  Underwater::Hx_eval(
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
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = cos(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = sin(t5);
    real_type t14  = t2 * L__[iL_lambda2__xo];
    result__[ 2   ] = (t4 * t6 - t9 * t8) * t3 + (-t9 * t4 - t6 * t8) * t14;
    real_type t22  = t2 * L__[iL_lambda5__xo];
    real_type t23  = X__[iX_Omega];
    real_type t24  = ModelPars[iM_m1];
    real_type t26  = ModelPars[iM_m3];
    real_type t27  = 1.0 / t26;
    real_type t31  = t2 * L__[iL_lambda6__xo];
    real_type t32  = t26 - t24;
    real_type t35  = 1.0 / ModelPars[iM_inertia];
    result__[ 3   ] = t27 * t24 * t23 * t22 + t35 * t32 * t4 * t31 - t9 * t14 + t6 * t3;
    real_type t41  = t2 * L__[iL_lambda4__xo];
    real_type t43  = 1.0 / t24;
    result__[ 4   ] = -t43 * t26 * t23 * t41 + t35 * t32 * t8 * t31 + t6 * t14 + t9 * t3;
    result__[ 5   ] = t27 * t24 * t8 * t22 - t43 * t26 * t4 * t41 + t2 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::Hp_numEqns() const { return 1; }

  void
  Underwater::Hp_eval(
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
    real_type t2   = X__[iX_vx];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vz];
    real_type t7   = sin(t3);
    real_type t17  = X__[iX_Omega];
    real_type t21  = ModelPars[iM_m1];
    real_type t22  = 1.0 / t21;
    real_type t25  = ModelPars[iM_m3];
    real_type t32  = 1.0 / t25;
    real_type t42  = 1.0 / ModelPars[iM_inertia];
    result__[ 0   ] = (t4 * t2 + t7 * t6) * L__[iL_lambda1__xo] + (-t7 * t2 + t4 * t6) * L__[iL_lambda2__xo] + t17 * L__[iL_lambda3__xo] + (-t22 * t25 * t17 * t6 + t22 * U__[iU_u1]) * L__[iL_lambda4__xo] + (t32 * t21 * t17 * t2 + t32 * U__[iU_u2]) * L__[iL_lambda5__xo] + (t42 * U__[iU_u3] + t42 * (t25 - t21) * t6 * t2) * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DHxDxp_numRows() const { return 6; }
  integer Underwater::DHxDxp_numCols() const { return 7; }
  integer Underwater::DHxDxp_nnz()     const { return 15; }

  void
  Underwater::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 6   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 3   ;
    iIndex[10] = 4   ; jIndex[10] = 5   ;
    iIndex[11] = 4   ; jIndex[11] = 6   ;
    iIndex[12] = 5   ; jIndex[12] = 3   ;
    iIndex[13] = 5   ; jIndex[13] = 4   ;
    iIndex[14] = 5   ; jIndex[14] = 6   ;
  }


  void
  Underwater::DHxDxp_sparse(
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
    real_type t4   = X__[iX_vz];
    real_type t5   = X__[iX_theta];
    real_type t6   = sin(t5);
    real_type t8   = X__[iX_vx];
    real_type t9   = cos(t5);
    real_type t11  = -t6 * t4 - t9 * t8;
    real_type t13  = L__[iL_lambda2__xo];
    real_type t14  = t2 * t13;
    real_type t17  = -t9 * t4 + t6 * t8;
    result__[ 0   ] = t11 * t3 + t17 * t14;
    result__[ 1   ] = -t9 * t14 - t6 * t3;
    result__[ 2   ] = -t6 * t14 + t9 * t3;
    result__[ 3   ] = -t17 * t1 + t11 * t13;
    result__[ 4   ] = result__[1];
    real_type t26  = L__[iL_lambda6__xo];
    real_type t28  = ModelPars[iM_m3];
    real_type t29  = ModelPars[iM_m1];
    real_type t33  = 1.0 / ModelPars[iM_inertia] * (t28 - t29);
    result__[ 5   ] = t33 * t2 * t26;
    real_type t34  = L__[iL_lambda5__xo];
    real_type t37  = 1.0 / t28 * t29;
    result__[ 6   ] = t37 * t2 * t34;
    real_type t40  = X__[iX_Omega];
    result__[ 7   ] = t33 * t4 * t26 + t37 * t40 * t34 + t9 * t1 - t6 * t13;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[5];
    real_type t45  = L__[iL_lambda4__xo];
    real_type t48  = 1.0 / t29 * t28;
    result__[ 10  ] = -t48 * t2 * t45;
    result__[ 11  ] = t33 * t8 * t26 - t48 * t40 * t45 + t6 * t1 + t9 * t13;
    result__[ 12  ] = result__[6];
    result__[ 13  ] = result__[10];
    result__[ 14  ] = t37 * t8 * t34 - t48 * t4 * t45 + L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 15, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DHpDp_numRows() const { return 1; }
  integer Underwater::DHpDp_numCols() const { return 1; }
  integer Underwater::DHpDp_nnz()     const { return 0; }

  void
  Underwater::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DHpDp_sparse(
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

  integer Underwater::Hu_numEqns() const { return 3; }

  void
  Underwater::Hu_eval(
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
    result__[ 0   ] = 1.0 / ModelPars[iM_m1] * t2 * L__[iL_lambda4__xo];
    result__[ 1   ] = 1.0 / ModelPars[iM_m3] * t2 * L__[iL_lambda5__xo];
    result__[ 2   ] = 1.0 / ModelPars[iM_inertia] * t2 * L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DHuDxp_numRows() const { return 3; }
  integer Underwater::DHuDxp_numCols() const { return 7; }
  integer Underwater::DHuDxp_nnz()     const { return 3; }

  void
  Underwater::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 6   ;
  }


  void
  Underwater::DHuDxp_sparse(
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
    result__[ 0   ] = L__[iL_lambda4__xo] / ModelPars[iM_m1];
    result__[ 1   ] = L__[iL_lambda5__xo] / ModelPars[iM_m3];
    result__[ 2   ] = L__[iL_lambda6__xo] / ModelPars[iM_inertia];
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

  integer Underwater::eta_numEqns() const { return 6; }

  void
  Underwater::eta_eval(
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
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DetaDxp_numRows() const { return 6; }
  integer Underwater::DetaDxp_numCols() const { return 7; }
  integer Underwater::DetaDxp_nnz()     const { return 0; }

  void
  Underwater::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DetaDxp_sparse(
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

  integer Underwater::nu_numEqns() const { return 6; }

  void
  Underwater::nu_eval(
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
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DnuDxp_numRows() const { return 6; }
  integer Underwater::DnuDxp_numCols() const { return 7; }
  integer Underwater::DnuDxp_nnz()     const { return 0; }

  void
  Underwater::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Underwater::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Underwater_Methods_AdjointODE.cc
