/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_AdjointODE.cc                                |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_max_DD(__t1) VelBound_max.DD( __t1)
#define ALIAS_VelBound_max_D(__t1) VelBound_max.D( __t1)
#define ALIAS_VelBound_min_DD(__t1) VelBound_min.DD( __t1)
#define ALIAS_VelBound_min_D(__t1) VelBound_min.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JPx_numEqns() const { return 4; }

  void
  Crossroad::JPx_eval(
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

  integer Crossroad::LTx_numEqns() const { return 4; }

  void
  Crossroad::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t19  = ALIAS_AccBound_D(t16 * t12 * t9 + t5 * t2 - 1);
    real_type t22  = kappa_D(t10);
    result__[ 0   ] = 2 * t22 * t16 * t11 * t9 * t19;
    real_type t30  = ALIAS_VelBound_min_D(-t7);
    real_type t33  = ALIAS_VelBound_max_D(t7 - ModelPars[iM_v_max]);
    result__[ 1   ] = 4 * t16 * t12 * t8 * t7 * t19 - t30 + t33;
    result__[ 2   ] = 2 * t5 * t1 * t19;
    real_type t37  = ALIAS_Tpositive_D(-X__[iX_Ts]);
    result__[ 3   ] = -t37;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JUx_numEqns() const { return 4; }

  void
  Crossroad::JUx_eval(
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

  integer Crossroad::JPp_numEqns() const { return 0; }

  void
  Crossroad::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::LTp_numEqns() const { return 0; }

  void
  Crossroad::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JUp_numEqns() const { return 0; }

  void
  Crossroad::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::JPu_numEqns() const { return 1; }

  void
  Crossroad::JPu_eval(
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

  integer Crossroad::LTu_numEqns() const { return 1; }

  void
  Crossroad::LTu_eval(
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

  integer Crossroad::JUu_numEqns() const { return 1; }

  void
  Crossroad::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_jerkControl_D_1(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::LTargs_numEqns() const { return 4; }

  void
  Crossroad::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -X__[iX_Ts];
    real_type t3   = X__[iX_a] * X__[iX_a];
    real_type t5   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t8   = X__[iX_v];
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t9;
    real_type t12  = kappa(X__[iX_s]);
    real_type t13  = t12 * t12;
    real_type t16  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    result__[ 1   ] = 1.0 / t5 * t3 + 1.0 / t16 * t13 * t10 - 1;
    result__[ 2   ] = -t8;
    result__[ 3   ] = t8 - ModelPars[iM_v_max];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJPxDxp_numRows() const { return 4; }
  integer Crossroad::DJPxDxp_numCols() const { return 4; }
  integer Crossroad::DJPxDxp_nnz()     const { return 0; }

  void
  Crossroad::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DLTxDxp_numRows() const { return 4; }
  integer Crossroad::DLTxDxp_numCols() const { return 4; }
  integer Crossroad::DLTxDxp_nnz()     const { return 10; }

  void
  Crossroad::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 3   ;
  }


  void
  Crossroad::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t18  = t16 * t12 * t9 + t5 * t2 - 1;
    real_type t19  = ALIAS_AccBound_DD(t18);
    real_type t20  = t9 * t9;
    real_type t22  = t15 * t15;
    real_type t23  = 1.0 / t22;
    real_type t25  = kappa_D(t10);
    real_type t26  = t25 * t25;
    real_type t30  = ALIAS_AccBound_D(t18);
    real_type t31  = t9 * t30;
    real_type t35  = t16 * t11;
    real_type t36  = kappa_DD(t10);
    result__[ 0   ] = 4 * t26 * t23 * t12 * t20 * t19 + 2 * t16 * t26 * t31 + 2 * t36 * t35 * t31;
    real_type t40  = t8 * t7;
    result__[ 1   ] = 8 * t25 * t23 * t12 * t11 * t9 * t40 * t19 + 8 * t25 * t35 * t40 * t30;
    real_type t52  = t5 * t1 * t19;
    result__[ 2   ] = 4 * t25 * t16 * t11 * t9 * t52;
    result__[ 3   ] = result__[1];
    real_type t59  = t12 * t12;
    real_type t67  = ALIAS_VelBound_min_DD(-t7);
    real_type t70  = ALIAS_VelBound_max_DD(t7 - ModelPars[iM_v_max]);
    result__[ 4   ] = 16 * t23 * t59 * t9 * t8 * t19 + 12 * t16 * t12 * t8 * t30 + t67 + t70;
    result__[ 5   ] = 8 * t16 * t12 * t40 * t52;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t75  = t4 * t4;
    result__[ 8   ] = 4 / t75 * t2 * t19 + 2 * t5 * t30;
    result__[ 9   ] = ALIAS_Tpositive_DD(-X__[iX_Ts]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJUxDxp_numRows() const { return 4; }
  integer Crossroad::DJUxDxp_numCols() const { return 4; }
  integer Crossroad::DJUxDxp_nnz()     const { return 0; }

  void
  Crossroad::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJPuDxp_numRows() const { return 1; }
  integer Crossroad::DJPuDxp_numCols() const { return 4; }
  integer Crossroad::DJPuDxp_nnz()     const { return 0; }

  void
  Crossroad::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DLTuDxp_numRows() const { return 1; }
  integer Crossroad::DLTuDxp_numCols() const { return 4; }
  integer Crossroad::DLTuDxp_nnz()     const { return 0; }

  void
  Crossroad::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJUuDxp_numRows() const { return 1; }
  integer Crossroad::DJUuDxp_numCols() const { return 4; }
  integer Crossroad::DJUuDxp_nnz()     const { return 0; }

  void
  Crossroad::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJPpDp_numRows() const { return 0; }
  integer Crossroad::DJPpDp_numCols() const { return 0; }
  integer Crossroad::DJPpDp_nnz()     const { return 0; }

  void
  Crossroad::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DLTpDp_numRows() const { return 0; }
  integer Crossroad::DLTpDp_numCols() const { return 0; }
  integer Crossroad::DLTpDp_nnz()     const { return 0; }

  void
  Crossroad::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DJUpDp_numRows() const { return 0; }
  integer Crossroad::DJUpDp_numCols() const { return 0; }
  integer Crossroad::DJUpDp_nnz()     const { return 0; }

  void
  Crossroad::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DLTargsDxup_numRows() const { return 4; }
  integer Crossroad::DLTargsDxup_numCols() const { return 5; }
  integer Crossroad::DLTargsDxup_nnz()     const { return 6; }

  void
  Crossroad::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 1   ;
  }


  void
  Crossroad::DLTargsDxup_sparse(
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
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_s];
    real_type t5   = kappa(t4);
    real_type t8   = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t9   = 1.0 / t8;
    real_type t10  = kappa_D(t4);
    result__[ 1   ] = 2 * t10 * t9 * t5 * t3;
    real_type t14  = t5 * t5;
    result__[ 2   ] = 4 * t9 * t14 * t2 * t1;
    real_type t19  = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    result__[ 3   ] = 2 / t19 * X__[iX_a];
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 6, i_segment );
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

  integer Crossroad::Hx_numEqns() const { return 4; }

  void
  Crossroad::Hx_eval(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = X__[iX_Ts];
    result__[ 1   ] = t2 * t1;
    real_type t3   = L__[iL_lambda2__xo];
    result__[ 2   ] = t2 * t3;
    real_type t5   = U__[iU_jerk];
    real_type t6   = t5 * t5;
    result__[ 3   ] = X__[iX_v] * t1 + X__[iX_a] * t3 + t5 * L__[iL_lambda3__xo] + t6 * ModelPars[iM_wJ] + ModelPars[iM_wT];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::Hp_numEqns() const { return 0; }

  void
  Crossroad::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DHxDxp_numRows() const { return 4; }
  integer Crossroad::DHxDxp_numCols() const { return 4; }
  integer Crossroad::DHxDxp_nnz()     const { return 4; }

  void
  Crossroad::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
  }


  void
  Crossroad::DHxDxp_sparse(
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
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DHpDp_numRows() const { return 0; }
  integer Crossroad::DHpDp_numCols() const { return 0; }
  integer Crossroad::DHpDp_nnz()     const { return 0; }

  void
  Crossroad::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DHpDp_sparse(
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

  integer Crossroad::Hu_numEqns() const { return 1; }

  void
  Crossroad::Hu_eval(
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
    real_type t4   = X__[iX_Ts];
    result__[ 0   ] = 2 * t4 * ModelPars[iM_wJ] * U__[iU_jerk] + t4 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DHuDxp_numRows() const { return 1; }
  integer Crossroad::DHuDxp_numCols() const { return 4; }
  integer Crossroad::DHuDxp_nnz()     const { return 1; }

  void
  Crossroad::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
  }


  void
  Crossroad::DHuDxp_sparse(
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
    result__[ 0   ] = 2 * U__[iU_jerk] * ModelPars[iM_wJ] + L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 1, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::eta_numEqns() const { return 4; }

  void
  Crossroad::eta_eval(
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
  integer Crossroad::DetaDxp_numRows() const { return 4; }
  integer Crossroad::DetaDxp_numCols() const { return 4; }
  integer Crossroad::DetaDxp_nnz()     const { return 0; }

  void
  Crossroad::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DetaDxp_sparse(
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

  integer Crossroad::nu_numEqns() const { return 4; }

  void
  Crossroad::nu_eval(
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
  integer Crossroad::DnuDxp_numRows() const { return 4; }
  integer Crossroad::DnuDxp_numCols() const { return 4; }
  integer Crossroad::DnuDxp_nnz()     const { return 0; }

  void
  Crossroad::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Crossroad::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Crossroad_Methods_AdjointODE.cc
