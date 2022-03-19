/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_AdjointODE.cc                               |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::JPx_numEqns() const { return 4; }

  void
  HangGlider::JPx_eval(
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

  integer HangGlider::LTx_numEqns() const { return 4; }

  void
  HangGlider::LTx_eval(
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

  integer HangGlider::JUx_numEqns() const { return 4; }

  void
  HangGlider::JUx_eval(
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

  integer HangGlider::JPp_numEqns() const { return 1; }

  void
  HangGlider::JPp_eval(
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

  integer HangGlider::LTp_numEqns() const { return 1; }

  void
  HangGlider::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_Tbound_D(-P__[iP_T]);
    result__[ 0   ] = -t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTp_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::JUp_numEqns() const { return 1; }

  void
  HangGlider::JUp_eval(
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

  integer HangGlider::JPu_numEqns() const { return 1; }

  void
  HangGlider::JPu_eval(
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

  integer HangGlider::LTu_numEqns() const { return 1; }

  void
  HangGlider::LTu_eval(
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

  integer HangGlider::JUu_numEqns() const { return 1; }

  void
  HangGlider::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_cLControl_D_1(U__[iU_cL], ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::LTargs_numEqns() const { return 1; }

  void
  HangGlider::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DJPxDxp_numRows() const { return 4; }
  integer HangGlider::DJPxDxp_numCols() const { return 5; }
  integer HangGlider::DJPxDxp_nnz()     const { return 0; }

  void
  HangGlider::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DLTxDxp_numRows() const { return 4; }
  integer HangGlider::DLTxDxp_numCols() const { return 5; }
  integer HangGlider::DLTxDxp_nnz()     const { return 0; }

  void
  HangGlider::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DJUxDxp_numRows() const { return 4; }
  integer HangGlider::DJUxDxp_numCols() const { return 5; }
  integer HangGlider::DJUxDxp_nnz()     const { return 0; }

  void
  HangGlider::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DJPuDxp_numRows() const { return 1; }
  integer HangGlider::DJPuDxp_numCols() const { return 5; }
  integer HangGlider::DJPuDxp_nnz()     const { return 0; }

  void
  HangGlider::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DLTuDxp_numRows() const { return 1; }
  integer HangGlider::DLTuDxp_numCols() const { return 5; }
  integer HangGlider::DLTuDxp_nnz()     const { return 0; }

  void
  HangGlider::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DJUuDxp_numRows() const { return 1; }
  integer HangGlider::DJUuDxp_numCols() const { return 5; }
  integer HangGlider::DJUuDxp_nnz()     const { return 0; }

  void
  HangGlider::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DJPpDp_numRows() const { return 1; }
  integer HangGlider::DJPpDp_numCols() const { return 1; }
  integer HangGlider::DJPpDp_nnz()     const { return 0; }

  void
  HangGlider::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DLTpDp_numRows() const { return 1; }
  integer HangGlider::DLTpDp_numCols() const { return 1; }
  integer HangGlider::DLTpDp_nnz()     const { return 1; }

  void
  HangGlider::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  HangGlider::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_Tbound_DD(-P__[iP_T]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTpDp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DJUpDp_numRows() const { return 1; }
  integer HangGlider::DJUpDp_numCols() const { return 1; }
  integer HangGlider::DJUpDp_nnz()     const { return 0; }

  void
  HangGlider::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DLTargsDxup_numRows() const { return 1; }
  integer HangGlider::DLTargsDxup_numCols() const { return 6; }
  integer HangGlider::DLTargsDxup_nnz()     const { return 1; }

  void
  HangGlider::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 5   ;
  }


  void
  HangGlider::DLTargsDxup_sparse(
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

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::Hx_numEqns() const { return 4; }

  void
  HangGlider::Hx_eval(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = P__[iP_T];
    real_type t5   = 1.0 / ModelPars[iM_m] * t2;
    real_type t6   = X__[iX_x];
    real_type t7   = X__[iX_vx];
    real_type t8   = X__[iX_vy];
    real_type t9   = v(t6, t7, t8);
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t13  = U__[iU_cL];
    real_type t14  = t13 * t13;
    real_type t17  = t14 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t18  = Dfun(t6, t7, t8);
    real_type t19  = t18 * t17;
    real_type t21  = Lfun(t6, t7, t8);
    real_type t22  = t21 * t13;
    real_type t23  = w(t6, t8);
    real_type t26  = (-t7 * t19 - t23 * t22) * t11;
    real_type t27  = v_D_1(t6, t7, t8);
    real_type t30  = 1.0 / t9;
    real_type t31  = Dfun_D_1(t6, t7, t8);
    real_type t32  = t31 * t17;
    real_type t34  = Lfun_D_1(t6, t7, t8);
    real_type t35  = t34 * t13;
    real_type t37  = w_D_1(t6, t8);
    real_type t44  = L__[iL_lambda4__xo];
    real_type t48  = (-t23 * t19 + t7 * t22) * t11;
    result__[ 0   ] = (-t27 * t26 * t5 + (-t37 * t22 - t23 * t35 - t7 * t32) * t30 * t5) * t1 + (-t27 * t48 * t5 + (-t37 * t19 - t23 * t32 + t7 * t35) * t30 * t5) * t44;
    result__[ 1   ] = 0;
    real_type t61  = v_D_2(t6, t7, t8);
    real_type t64  = Dfun_D_2(t6, t7, t8);
    real_type t65  = t64 * t17;
    real_type t67  = Lfun_D_2(t6, t7, t8);
    real_type t68  = t67 * t13;
    result__[ 2   ] = t2 * L__[iL_lambda1__xo] + (-t61 * t26 * t5 + (-t23 * t68 - t7 * t65 - t19) * t30 * t5) * t1 + (-t61 * t48 * t5 + (-t23 * t65 + t7 * t68 + t22) * t30 * t5) * t44;
    real_type t86  = v_D_3(t6, t7, t8);
    real_type t89  = Dfun_D_3(t6, t7, t8);
    real_type t90  = t89 * t17;
    real_type t92  = Lfun_D_3(t6, t7, t8);
    real_type t93  = t92 * t13;
    real_type t95  = w_D_2(t6, t8);
    result__[ 3   ] = t2 * L__[iL_lambda2__xo] + (-t86 * t26 * t5 + (-t95 * t22 - t23 * t93 - t7 * t90) * t30 * t5) * t1 + (-t86 * t48 * t5 + (-t95 * t19 - t23 * t90 + t7 * t93) * t30 * t5) * t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::Hp_numEqns() const { return 1; }

  void
  HangGlider::Hp_eval(
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
    real_type t5   = X__[iX_vy];
    real_type t9   = 1.0 / ModelPars[iM_m];
    real_type t11  = X__[iX_x];
    real_type t12  = v(t11, t2, t5);
    real_type t13  = 1.0 / t12;
    real_type t15  = U__[iU_cL];
    real_type t16  = t15 * t15;
    real_type t20  = Dfun(t11, t2, t5);
    real_type t21  = t20 * (t16 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t23  = Lfun(t11, t2, t5);
    real_type t24  = t23 * t15;
    real_type t25  = w(t11, t5);
    result__[ 0   ] = t2 * L__[iL_lambda1__xo] + t5 * L__[iL_lambda2__xo] + (-t2 * t21 - t25 * t24) * t13 * t9 * L__[iL_lambda3__xo] + ((t2 * t24 - t25 * t21) * t13 * t9 - ModelPars[iM_g]) * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DHxDxp_numRows() const { return 4; }
  integer HangGlider::DHxDxp_numCols() const { return 5; }
  integer HangGlider::DHxDxp_nnz()     const { return 12; }

  void
  HangGlider::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 2   ;
    iIndex[10] = 3   ; jIndex[10] = 3   ;
    iIndex[11] = 3   ; jIndex[11] = 4   ;
  }


  void
  HangGlider::DHxDxp_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t4   = 1.0 / ModelPars[iM_m];
    real_type t5   = t4 * P__[iP_T];
    real_type t6   = X__[iX_x];
    real_type t7   = X__[iX_vx];
    real_type t8   = X__[iX_vy];
    real_type t9   = v(t6, t7, t8);
    real_type t10  = t9 * t9;
    real_type t12  = 1.0 / t10 / t9;
    real_type t14  = U__[iU_cL];
    real_type t15  = t14 * t14;
    real_type t18  = t15 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t19  = Dfun(t6, t7, t8);
    real_type t20  = t19 * t18;
    real_type t22  = Lfun(t6, t7, t8);
    real_type t23  = t22 * t14;
    real_type t24  = w(t6, t8);
    real_type t26  = -t7 * t20 - t24 * t23;
    real_type t27  = t26 * t12;
    real_type t28  = v_D_1(t6, t7, t8);
    real_type t29  = t28 * t28;
    real_type t33  = 1.0 / t10;
    real_type t34  = Dfun_D_1(t6, t7, t8);
    real_type t35  = t34 * t18;
    real_type t37  = Lfun_D_1(t6, t7, t8);
    real_type t38  = t37 * t14;
    real_type t40  = w_D_1(t6, t8);
    real_type t42  = -t40 * t23 - t24 * t38 - t7 * t35;
    real_type t43  = t42 * t33;
    real_type t47  = t26 * t33;
    real_type t48  = v_D_1_1(t6, t7, t8);
    real_type t51  = 1.0 / t9;
    real_type t52  = Dfun_D_1_1(t6, t7, t8);
    real_type t53  = t52 * t18;
    real_type t55  = Lfun_D_1_1(t6, t7, t8);
    real_type t56  = t55 * t14;
    real_type t60  = w_D_1_1(t6, t8);
    real_type t67  = L__[iL_lambda4__xo];
    real_type t70  = -t24 * t20 + t7 * t23;
    real_type t71  = t70 * t12;
    real_type t78  = -t40 * t20 - t24 * t35 + t7 * t38;
    real_type t79  = t78 * t33;
    real_type t83  = t70 * t33;
    result__[ 0   ] = (2 * t29 * t27 * t5 - 2 * t28 * t43 * t5 - t48 * t47 * t5 + (-t60 * t23 - t24 * t56 - 2 * t40 * t38 - t7 * t53) * t51 * t5) * t1 + (2 * t29 * t71 * t5 - 2 * t28 * t79 * t5 - t48 * t83 * t5 + (-t60 * t20 - t24 * t53 - 2 * t40 * t35 + t7 * t56) * t51 * t5) * t67;
    real_type t96  = t12 * t5;
    real_type t97  = t28 * t26;
    real_type t98  = v_D_2(t6, t7, t8);
    real_type t102 = Dfun_D_2(t6, t7, t8);
    real_type t103 = t102 * t18;
    real_type t105 = Lfun_D_2(t6, t7, t8);
    real_type t106 = t105 * t14;
    real_type t108 = -t7 * t103 - t24 * t106 - t20;
    real_type t109 = t108 * t33;
    real_type t112 = v_D_1_2(t6, t7, t8);
    real_type t117 = Dfun_D_1_2(t6, t7, t8);
    real_type t118 = t117 * t18;
    real_type t120 = Lfun_D_1_2(t6, t7, t8);
    real_type t121 = t120 * t14;
    real_type t129 = t28 * t70;
    real_type t135 = -t24 * t103 + t7 * t106 + t23;
    real_type t136 = t135 * t33;
    result__[ 1   ] = (2 * t98 * t97 * t96 - t28 * t109 * t5 - t112 * t47 * t5 - t98 * t43 * t5 + (-t40 * t106 - t7 * t118 - t24 * t121 - t35) * t51 * t5) * t1 + (2 * t98 * t129 * t96 - t28 * t136 * t5 - t112 * t83 * t5 - t98 * t79 * t5 + (-t40 * t103 - t24 * t118 + t7 * t121 + t38) * t51 * t5) * t67;
    real_type t151 = v_D_3(t6, t7, t8);
    real_type t155 = Dfun_D_3(t6, t7, t8);
    real_type t156 = t155 * t18;
    real_type t158 = Lfun_D_3(t6, t7, t8);
    real_type t159 = t158 * t14;
    real_type t161 = w_D_2(t6, t8);
    real_type t163 = -t7 * t156 - t24 * t159 - t161 * t23;
    real_type t164 = t163 * t33;
    real_type t167 = v_D_1_3(t6, t7, t8);
    real_type t172 = Dfun_D_1_3(t6, t7, t8);
    real_type t173 = t172 * t18;
    real_type t175 = Lfun_D_1_3(t6, t7, t8);
    real_type t176 = t175 * t14;
    real_type t180 = w_D_1_2(t6, t8);
    real_type t193 = -t24 * t156 + t7 * t159 - t161 * t20;
    real_type t194 = t193 * t33;
    result__[ 2   ] = (2 * t151 * t97 * t96 - t28 * t164 * t5 - t167 * t47 * t5 - t151 * t43 * t5 + (-t40 * t159 - t161 * t38 - t7 * t173 - t24 * t176 - t180 * t23) * t51 * t5) * t1 + (2 * t151 * t129 * t96 - t28 * t194 * t5 - t167 * t83 * t5 - t151 * t79 * t5 + (-t40 * t156 - t161 * t35 - t24 * t173 + t7 * t176 - t180 * t20) * t51 * t5) * t67;
    real_type t211 = t33 * t4;
    real_type t213 = t51 * t4;
    result__[ 3   ] = (-t97 * t211 + t42 * t213) * t1 + (-t129 * t211 + t78 * t213) * t67;
    result__[ 4   ] = result__[1];
    real_type t221 = t98 * t98;
    real_type t228 = v_D_2_2(t6, t7, t8);
    real_type t231 = Dfun_D_2_2(t6, t7, t8);
    real_type t232 = t231 * t18;
    real_type t235 = Lfun_D_2_2(t6, t7, t8);
    real_type t236 = t235 * t14;
    result__[ 5   ] = (2 * t221 * t27 * t5 - 2 * t98 * t109 * t5 - t228 * t47 * t5 + (-t7 * t232 - t24 * t236 - 2 * t103) * t51 * t5) * t1 + (2 * t221 * t71 * t5 - 2 * t98 * t136 * t5 - t228 * t83 * t5 + (-t24 * t232 + t7 * t236 + 2 * t106) * t51 * t5) * t67;
    real_type t259 = t98 * t26;
    real_type t265 = v_D_2_3(t6, t7, t8);
    real_type t270 = Dfun_D_2_3(t6, t7, t8);
    real_type t271 = t270 * t18;
    real_type t273 = Lfun_D_2_3(t6, t7, t8);
    real_type t274 = t273 * t14;
    real_type t282 = t98 * t70;
    result__[ 6   ] = (2 * t151 * t259 * t96 - t98 * t164 * t5 - t265 * t47 * t5 - t151 * t109 * t5 + (-t161 * t106 - t24 * t274 - t7 * t271 - t156) * t51 * t5) * t1 + (2 * t151 * t282 * t96 - t98 * t194 * t5 - t265 * t83 * t5 - t151 * t136 * t5 + (-t161 * t103 - t24 * t271 + t7 * t274 + t159) * t51 * t5) * t67;
    result__[ 7   ] = L__[iL_lambda1__xo] + (t108 * t213 - t259 * t211) * t1 + (t135 * t213 - t282 * t211) * t67;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t309 = t151 * t151;
    real_type t316 = v_D_3_3(t6, t7, t8);
    real_type t319 = Dfun_D_3_3(t6, t7, t8);
    real_type t320 = t319 * t18;
    real_type t322 = Lfun_D_3_3(t6, t7, t8);
    real_type t323 = t322 * t14;
    real_type t327 = w_D_2_2(t6, t8);
    result__[ 10  ] = (2 * t309 * t27 * t5 - 2 * t151 * t164 * t5 - t316 * t47 * t5 + (-2 * t161 * t159 - t327 * t23 - t24 * t323 - t7 * t320) * t51 * t5) * t1 + (2 * t309 * t71 * t5 - 2 * t151 * t194 * t5 - t316 * t83 * t5 + (-2 * t161 * t156 - t327 * t20 - t24 * t320 + t7 * t323) * t51 * t5) * t67;
    result__[ 11  ] = L__[iL_lambda2__xo] + (-t151 * t26 * t211 + t163 * t213) * t1 + (-t151 * t70 * t211 + t193 * t213) * t67;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DHpDp_numRows() const { return 1; }
  integer HangGlider::DHpDp_numCols() const { return 1; }
  integer HangGlider::DHpDp_nnz()     const { return 0; }

  void
  HangGlider::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DHpDp_sparse(
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

  integer HangGlider::Hu_numEqns() const { return 1; }

  void
  HangGlider::Hu_eval(
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
    real_type t2   = U__[iU_cL];
    real_type t7   = P__[iP_T];
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_vy];
    real_type t14  = v(t11, t12, t13);
    real_type t16  = 1.0 / t14 / ModelPars[iM_m];
    real_type t18  = t2 * ModelPars[iM_c1];
    real_type t19  = Dfun(t11, t12, t13);
    real_type t23  = Lfun(t11, t12, t13);
    real_type t24  = w(t11, t13);
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] + (-2 * t12 * t19 * t18 - t24 * t23) * t16 * t7 * L__[iL_lambda3__xo] + (-2 * t24 * t19 * t18 + t12 * t23) * t16 * t7 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DHuDxp_numRows() const { return 1; }
  integer HangGlider::DHuDxp_numCols() const { return 5; }
  integer HangGlider::DHuDxp_nnz()     const { return 4; }

  void
  HangGlider::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
  }


  void
  HangGlider::DHuDxp_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_c1] * U__[iU_cL];
    real_type t16  = Dfun(t7, t8, t9);
    real_type t20  = Lfun(t7, t8, t9);
    real_type t21  = w(t7, t9);
    real_type t23  = -2 * t15 * t16 * t8 - t20 * t21;
    real_type t24  = t23 * t12;
    real_type t25  = v_D_1(t7, t8, t9);
    real_type t28  = 1.0 / t10;
    real_type t29  = t28 * t5;
    real_type t30  = Dfun_D_1(t7, t8, t9);
    real_type t34  = Lfun_D_1(t7, t8, t9);
    real_type t36  = w_D_1(t7, t9);
    real_type t41  = L__[iL_lambda4__xo];
    real_type t42  = t2 * t41;
    real_type t43  = t5 * t42;
    real_type t48  = -2 * t15 * t16 * t21 + t20 * t8;
    real_type t49  = t48 * t12;
    result__[ 0   ] = -t25 * t24 * t6 + (-2 * t15 * t30 * t8 - t20 * t36 - t21 * t34) * t29 * t3 - t25 * t49 * t43 + (-2 * t15 * t16 * t36 - 2 * t15 * t21 * t30 + t34 * t8) * t29 * t42;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t71  = Lfun_D_2(t7, t8, t9);
    result__[ 1   ] = -t62 * t24 * t6 + (-2 * t15 * t65 * t8 - 2 * t15 * t16 - t21 * t71) * t29 * t3 - t62 * t49 * t43 + (-2 * t15 * t21 * t65 + t71 * t8 + t20) * t29 * t42;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t92  = Lfun_D_3(t7, t8, t9);
    real_type t94  = w_D_2(t7, t9);
    result__[ 2   ] = -t85 * t24 * t6 + (-2 * t15 * t8 * t88 - t20 * t94 - t21 * t92) * t29 * t3 - t85 * t49 * t43 + (-2 * t94 * t16 * t15 - 2 * t21 * t88 * t15 + t8 * t92) * t29 * t42;
    result__[ 3   ] = t1 * t23 * t28 * t5 + t28 * t41 * t48 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 4, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::eta_numEqns() const { return 4; }

  void
  HangGlider::eta_eval(
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
  integer HangGlider::DetaDxp_numRows() const { return 4; }
  integer HangGlider::DetaDxp_numCols() const { return 5; }
  integer HangGlider::DetaDxp_nnz()     const { return 0; }

  void
  HangGlider::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DetaDxp_sparse(
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

  integer HangGlider::nu_numEqns() const { return 4; }

  void
  HangGlider::nu_eval(
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
  integer HangGlider::DnuDxp_numRows() const { return 4; }
  integer HangGlider::DnuDxp_numCols() const { return 5; }
  integer HangGlider::DnuDxp_nnz()     const { return 0; }

  void
  HangGlider::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: HangGlider_Methods_AdjointODE.cc
