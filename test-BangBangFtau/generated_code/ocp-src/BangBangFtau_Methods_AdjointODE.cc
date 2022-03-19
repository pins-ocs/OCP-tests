/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods_AdjointODE.cc                             |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vsTBInterval_max_DD(__t1) vsTBInterval_max.DD( __t1)
#define ALIAS_vsTBInterval_max_D(__t1) vsTBInterval_max.D( __t1)
#define ALIAS_vsTBInterval_min_DD(__t1) vsTBInterval_min.DD( __t1)
#define ALIAS_vsTBInterval_min_D(__t1) vsTBInterval_min.D( __t1)
#define ALIAS_vsTmax_DD(__t1) vsTmax.DD( __t1)
#define ALIAS_vsTmax_D(__t1) vsTmax.D( __t1)
#define ALIAS_vsBpositive_DD(__t1) vsBpositive.DD( __t1)
#define ALIAS_vsBpositive_D(__t1) vsBpositive.D( __t1)
#define ALIAS_vsTpositive_DD(__t1) vsTpositive.DD( __t1)
#define ALIAS_vsTpositive_D(__t1) vsTpositive.D( __t1)


namespace BangBangFtauDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JPx_numEqns() const { return 4; }

  void
  BangBangFtau::JPx_eval(
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

  integer BangBangFtau::LTx_numEqns() const { return 4; }

  void
  BangBangFtau::LTx_eval(
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

  integer BangBangFtau::JUx_numEqns() const { return 4; }

  void
  BangBangFtau::JUx_eval(
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

  integer BangBangFtau::JPp_numEqns() const { return 0; }

  void
  BangBangFtau::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::LTp_numEqns() const { return 0; }

  void
  BangBangFtau::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JUp_numEqns() const { return 0; }

  void
  BangBangFtau::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JPu_numEqns() const { return 2; }

  void
  BangBangFtau::JPu_eval(
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

  integer BangBangFtau::LTu_numEqns() const { return 2; }

  void
  BangBangFtau::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    real_type t2   = ALIAS_vsTpositive_D(-t1);
    real_type t5   = ALIAS_vsTmax_D(t1 - ModelPars[iM_maxT]);
    real_type t6   = U__[iU_vsB];
    real_type t8   = ALIAS_vsTBInterval_min_D(-1 - t1 + t6);
    real_type t10  = ALIAS_vsTBInterval_max_D(t1 - t6 - 1);
    result__[ 0   ] = -t2 + t5 - t8 + t10;
    real_type t11  = ALIAS_vsBpositive_D(-t6);
    result__[ 1   ] = -t11 + t8 - t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::JUu_numEqns() const { return 2; }

  void
  BangBangFtau::JUu_eval(
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

  integer BangBangFtau::LTargs_numEqns() const { return 5; }

  void
  BangBangFtau::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vsT];
    result__[ 0   ] = -t1;
    real_type t2   = U__[iU_vsB];
    result__[ 1   ] = -t2;
    result__[ 2   ] = t1 - ModelPars[iM_maxT];
    result__[ 3   ] = -1 + result__[0] + t2;
    result__[ 4   ] = t1 + result__[1] - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJPxDxp_numRows() const { return 4; }
  integer BangBangFtau::DJPxDxp_numCols() const { return 4; }
  integer BangBangFtau::DJPxDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DLTxDxp_numRows() const { return 4; }
  integer BangBangFtau::DLTxDxp_numCols() const { return 4; }
  integer BangBangFtau::DLTxDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJUxDxp_numRows() const { return 4; }
  integer BangBangFtau::DJUxDxp_numCols() const { return 4; }
  integer BangBangFtau::DJUxDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJPuDxp_numRows() const { return 2; }
  integer BangBangFtau::DJPuDxp_numCols() const { return 4; }
  integer BangBangFtau::DJPuDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DLTuDxp_numRows() const { return 2; }
  integer BangBangFtau::DLTuDxp_numCols() const { return 4; }
  integer BangBangFtau::DLTuDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJUuDxp_numRows() const { return 2; }
  integer BangBangFtau::DJUuDxp_numCols() const { return 4; }
  integer BangBangFtau::DJUuDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJPpDp_numRows() const { return 0; }
  integer BangBangFtau::DJPpDp_numCols() const { return 0; }
  integer BangBangFtau::DJPpDp_nnz()     const { return 0; }

  void
  BangBangFtau::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DLTpDp_numRows() const { return 0; }
  integer BangBangFtau::DLTpDp_numCols() const { return 0; }
  integer BangBangFtau::DLTpDp_nnz()     const { return 0; }

  void
  BangBangFtau::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DJUpDp_numRows() const { return 0; }
  integer BangBangFtau::DJUpDp_numCols() const { return 0; }
  integer BangBangFtau::DJUpDp_nnz()     const { return 0; }

  void
  BangBangFtau::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DLTargsDxup_numRows() const { return 5; }
  integer BangBangFtau::DLTargsDxup_numCols() const { return 6; }
  integer BangBangFtau::DLTargsDxup_nnz()     const { return 7; }

  void
  BangBangFtau::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 4   ; jIndex[6 ] = 5   ;
  }


  void
  BangBangFtau::DLTargsDxup_sparse(
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
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 7, i_segment );
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

  integer BangBangFtau::Hx_numEqns() const { return 4; }

  void
  BangBangFtau::Hx_eval(
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
    result__[ 1   ] = L__[iL_lambda1__xo];
    real_type t7   = ALIAS_clip_D_1(X__[iX_sT] - X__[iX_sB], ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    real_type t8   = t7 * L__[iL_lambda2__xo];
    result__[ 2   ] = t8 - L__[iL_lambda3__xo] / ModelPars[iM_tauT];
    result__[ 3   ] = -t8 - L__[iL_lambda4__xo] / ModelPars[iM_tauB];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::Hp_numEqns() const { return 0; }

  void
  BangBangFtau::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DHxDxp_numRows() const { return 4; }
  integer BangBangFtau::DHxDxp_numCols() const { return 4; }
  integer BangBangFtau::DHxDxp_nnz()     const { return 4; }

  void
  BangBangFtau::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  void
  BangBangFtau::DHxDxp_sparse(
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
    real_type t7   = ALIAS_clip_D_1_1(X__[iX_sT] - X__[iX_sB], ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    result__[ 0   ] = t7 * L__[iL_lambda2__xo];
    result__[ 1   ] = -result__[0];
    result__[ 2   ] = result__[1];
    result__[ 3   ] = result__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DHpDp_numRows() const { return 0; }
  integer BangBangFtau::DHpDp_numCols() const { return 0; }
  integer BangBangFtau::DHpDp_nnz()     const { return 0; }

  void
  BangBangFtau::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DHpDp_sparse(
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

  integer BangBangFtau::Hu_numEqns() const { return 2; }

  void
  BangBangFtau::Hu_eval(
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
    real_type t1   = ModelPars[iM_epsiTB];
    result__[ 0   ] = 2 * U__[iU_vsT] * t1 + L__[iL_lambda3__xo] / ModelPars[iM_tauT];
    result__[ 1   ] = 2 * U__[iU_vsB] * t1 + L__[iL_lambda4__xo] / ModelPars[iM_tauB];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DHuDxp_numRows() const { return 2; }
  integer BangBangFtau::DHuDxp_numCols() const { return 4; }
  integer BangBangFtau::DHuDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DHuDxp_sparse(
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

  integer BangBangFtau::eta_numEqns() const { return 4; }

  void
  BangBangFtau::eta_eval(
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
  integer BangBangFtau::DetaDxp_numRows() const { return 4; }
  integer BangBangFtau::DetaDxp_numCols() const { return 4; }
  integer BangBangFtau::DetaDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DetaDxp_sparse(
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

  integer BangBangFtau::nu_numEqns() const { return 4; }

  void
  BangBangFtau::nu_eval(
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
  integer BangBangFtau::DnuDxp_numRows() const { return 4; }
  integer BangBangFtau::DnuDxp_numCols() const { return 4; }
  integer BangBangFtau::DnuDxp_nnz()     const { return 0; }

  void
  BangBangFtau::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFtau::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFtau_Methods_AdjointODE.cc
