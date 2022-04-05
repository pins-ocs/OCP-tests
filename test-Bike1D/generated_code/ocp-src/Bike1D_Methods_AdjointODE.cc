/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods_AdjointODE.cc                                   |
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


#include "Bike1D.hh"
#include "Bike1D_Pars.hh"

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
#define ALIAS_vMinLimit_DD(__t1) vMinLimit.DD( __t1)
#define ALIAS_vMinLimit_D(__t1) vMinLimit.D( __t1)
#define ALIAS_mufControl_D_3(__t1, __t2, __t3) mufControl.D_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2(__t1, __t2, __t3) mufControl.D_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1(__t1, __t2, __t3) mufControl.D_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3_3(__t1, __t2, __t3) mufControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_3(__t1, __t2, __t3) mufControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_2(__t1, __t2, __t3) mufControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_3(__t1, __t2, __t3) mufControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_2(__t1, __t2, __t3) mufControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_1(__t1, __t2, __t3) mufControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3(__t1, __t2, __t3) murControl.D_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2(__t1, __t2, __t3) murControl.D_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1(__t1, __t2, __t3) murControl.D_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3_3(__t1, __t2, __t3) murControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_3(__t1, __t2, __t3) murControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_2(__t1, __t2, __t3) murControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_3(__t1, __t2, __t3) murControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_2(__t1, __t2, __t3) murControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_1(__t1, __t2, __t3) murControl.D_1_1( __t1, __t2, __t3)


namespace Bike1DDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::JPx_numEqns() const { return 1; }

  void
  Bike1D::JPx_eval(
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
      Mechatronix::check_in_segment( result__, "JPx_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::LTx_numEqns() const { return 1; }

  void
  Bike1D::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t5   = ModelPars[iM_v_min] - t1;
    real_type t6   = vMinLimit(t5);
    real_type t9   = ALIAS_vMinLimit_D(t5);
    result__[ 0   ] = -t6 / t2 - t9 / t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::JUx_numEqns() const { return 1; }

  void
  Bike1D::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = U__[iU_mur];
    real_type t5   = ModelPars[iM_mur_min];
    real_type t6   = Tmax_normalized(t1);
    real_type t7   = ModelPars[iM_mur_max];
    real_type t8   = clip(t6, 0, t7);
    real_type t9   = murControl(t4, t5, t8);
    real_type t12  = ALIAS_murControl_D_3(t4, t5, t8);
    real_type t14  = ALIAS_clip_D_1(t6, 0, t7);
    real_type t15  = Tmax_normalized_D(t1);
    real_type t20  = mufControl(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 0   ] = -t9 * t3 + t15 * t14 * t12 / t1 - t20 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::JPp_numEqns() const { return 0; }

  void
  Bike1D::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::LTp_numEqns() const { return 0; }

  void
  Bike1D::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::JUp_numEqns() const { return 0; }

  void
  Bike1D::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::JPu_numEqns() const { return 2; }

  void
  Bike1D::JPu_eval(
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

  integer Bike1D::LTu_numEqns() const { return 2; }

  void
  Bike1D::LTu_eval(
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

  integer Bike1D::JUu_numEqns() const { return 2; }

  void
  Bike1D::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1(U__[iU_mur], ModelPars[iM_mur_min], t7);
    result__[ 0   ] = t8 * t2;
    real_type t11  = ALIAS_mufControl_D_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t11 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::LTargs_numEqns() const { return 1; }

  void
  Bike1D::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_v_min] - X__[iX_v];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DJPxDxp_numRows() const { return 1; }
  integer Bike1D::DJPxDxp_numCols() const { return 1; }
  integer Bike1D::DJPxDxp_nnz()     const { return 0; }

  void
  Bike1D::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DLTxDxp_numRows() const { return 1; }
  integer Bike1D::DLTxDxp_numCols() const { return 1; }
  integer Bike1D::DLTxDxp_nnz()     const { return 1; }

  void
  Bike1D::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Bike1D::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t6   = ModelPars[iM_v_min] - t1;
    real_type t7   = vMinLimit(t6);
    real_type t11  = ALIAS_vMinLimit_D(t6);
    real_type t15  = ALIAS_vMinLimit_DD(t6);
    result__[ 0   ] = 2 * t7 / t2 / t1 + 2 * t11 / t2 + t15 / t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DJUxDxp_numRows() const { return 1; }
  integer Bike1D::DJUxDxp_numCols() const { return 1; }
  integer Bike1D::DJUxDxp_nnz()     const { return 1; }

  void
  Bike1D::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Bike1D::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t4   = 1.0 / t2 / t1;
    real_type t5   = U__[iU_mur];
    real_type t6   = ModelPars[iM_mur_min];
    real_type t7   = Tmax_normalized(t1);
    real_type t8   = ModelPars[iM_mur_max];
    real_type t9   = clip(t7, 0, t8);
    real_type t10  = murControl(t5, t6, t9);
    real_type t14  = ALIAS_murControl_D_3(t5, t6, t9);
    real_type t16  = ALIAS_clip_D_1(t7, 0, t8);
    real_type t17  = Tmax_normalized_D(t1);
    real_type t21  = 1.0 / t1;
    real_type t22  = ALIAS_murControl_D_3_3(t5, t6, t9);
    real_type t24  = t16 * t16;
    real_type t25  = t17 * t17;
    real_type t28  = t14 * t21;
    real_type t29  = ALIAS_clip_D_1_1(t7, 0, t8);
    real_type t32  = Tmax_normalized_DD(t1);
    real_type t37  = mufControl(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 0   ] = 2 * t10 * t4 - 2 * t17 * t16 * t14 / t2 + t25 * t24 * t22 * t21 + t25 * t29 * t28 + t32 * t16 * t28 + 2 * t37 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DJPuDxp_numRows() const { return 2; }
  integer Bike1D::DJPuDxp_numCols() const { return 1; }
  integer Bike1D::DJPuDxp_nnz()     const { return 0; }

  void
  Bike1D::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DLTuDxp_numRows() const { return 2; }
  integer Bike1D::DLTuDxp_numCols() const { return 1; }
  integer Bike1D::DLTuDxp_nnz()     const { return 0; }

  void
  Bike1D::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DJUuDxp_numRows() const { return 2; }
  integer Bike1D::DJUuDxp_numCols() const { return 1; }
  integer Bike1D::DJUuDxp_nnz()     const { return 2; }

  void
  Bike1D::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }


  void
  Bike1D::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = U__[iU_mur];
    real_type t5   = ModelPars[iM_mur_min];
    real_type t6   = Tmax_normalized(t1);
    real_type t7   = ModelPars[iM_mur_max];
    real_type t8   = clip(t6, 0, t7);
    real_type t9   = ALIAS_murControl_D_1(t4, t5, t8);
    real_type t12  = ALIAS_murControl_D_1_3(t4, t5, t8);
    real_type t14  = ALIAS_clip_D_1(t6, 0, t7);
    real_type t15  = Tmax_normalized_D(t1);
    result__[ 0   ] = -t9 * t3 + t15 * t14 * t12 / t1;
    real_type t20  = ALIAS_mufControl_D_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = -t20 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DJPpDp_numRows() const { return 0; }
  integer Bike1D::DJPpDp_numCols() const { return 0; }
  integer Bike1D::DJPpDp_nnz()     const { return 0; }

  void
  Bike1D::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DLTpDp_numRows() const { return 0; }
  integer Bike1D::DLTpDp_numCols() const { return 0; }
  integer Bike1D::DLTpDp_nnz()     const { return 0; }

  void
  Bike1D::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DJUpDp_numRows() const { return 0; }
  integer Bike1D::DJUpDp_numCols() const { return 0; }
  integer Bike1D::DJUpDp_nnz()     const { return 0; }

  void
  Bike1D::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DLTargsDxup_numRows() const { return 1; }
  integer Bike1D::DLTargsDxup_numCols() const { return 3; }
  integer Bike1D::DLTargsDxup_nnz()     const { return 1; }

  void
  Bike1D::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Bike1D::DLTargsDxup_sparse(
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
  integer Bike1D::D2LTargsD2xup_numRows() const { return 3; }
  integer Bike1D::D2LTargsD2xup_numCols() const { return 3; }
  integer Bike1D::D2LTargsD2xup_nnz()     const { return 0; }

  void
  Bike1D::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::D2LTargsD2xup_sparse(
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

  integer Bike1D::Hx_numEqns() const { return 1; }

  void
  Bike1D::Hx_eval(
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
    real_type t2   = X__[iX_v] * X__[iX_v];
    result__[ 0   ] = -1.0 / t2 - L__[iL_lambda1__xo] * V__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::Hp_numEqns() const { return 0; }

  void
  Bike1D::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DHxDxp_numRows() const { return 1; }
  integer Bike1D::DHxDxp_numCols() const { return 1; }
  integer Bike1D::DHxDxp_nnz()     const { return 1; }

  void
  Bike1D::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Bike1D::DHxDxp_sparse(
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
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    result__[ 0   ] = 2 / t2 / t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DHpDp_numRows() const { return 0; }
  integer Bike1D::DHpDp_numCols() const { return 0; }
  integer Bike1D::DHpDp_nnz()     const { return 0; }

  void
  Bike1D::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DHpDp_sparse(
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

  integer Bike1D::Hu_numEqns() const { return 2; }

  void
  Bike1D::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda1__xo] * ModelPars[iM_g];
    result__[ 1   ] = result__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DHuDxp_numRows() const { return 2; }
  integer Bike1D::DHuDxp_numCols() const { return 1; }
  integer Bike1D::DHuDxp_nnz()     const { return 0; }

  void
  Bike1D::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Bike1D::DHuDxp_sparse(
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

  integer Bike1D::eta_numEqns() const { return 1; }

  void
  Bike1D::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_v] * L__[iL_lambda1__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DetaDxp_numRows() const { return 1; }
  integer Bike1D::DetaDxp_numCols() const { return 1; }
  integer Bike1D::DetaDxp_nnz()     const { return 1; }

  void
  Bike1D::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Bike1D::DetaDxp_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DetaDxp_sparse", 1, i_segment );
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::nu_numEqns() const { return 1; }

  void
  Bike1D::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_v] * V__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DnuDxp_numRows() const { return 1; }
  integer Bike1D::DnuDxp_numCols() const { return 1; }
  integer Bike1D::DnuDxp_nnz()     const { return 1; }

  void
  Bike1D::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Bike1D::DnuDxp_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DnuDxp_sparse", 1, i_segment );
  }

}

// EOF: Bike1D_Methods_AdjointODE.cc
