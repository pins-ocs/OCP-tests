/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_AdjointODE.cc                               |
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



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::D2LTargsD2xup_numRows() const { return 6; }
  integer HangGlider::D2LTargsD2xup_numCols() const { return 6; }
  integer HangGlider::D2LTargsD2xup_nnz()     const { return 0; }

  void
  HangGlider::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HangGlider::D2LTargsD2xup_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda3__xo];
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t14  = U__[iU_cL];
    real_type t15  = t14 * t14;
    real_type t18  = t15 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t19  = Dfun(t7, t8, t9);
    real_type t20  = t19 * t18;
    real_type t22  = Lfun(t7, t8, t9);
    real_type t23  = t22 * t14;
    real_type t24  = w(t7, t9);
    real_type t27  = (-t8 * t20 - t24 * t23) * t12;
    real_type t28  = v_D_1(t7, t8, t9);
    real_type t31  = 1.0 / t10;
    real_type t32  = t31 * t5;
    real_type t33  = Dfun_D_1(t7, t8, t9);
    real_type t34  = t33 * t18;
    real_type t36  = Lfun_D_1(t7, t8, t9);
    real_type t37  = t36 * t14;
    real_type t39  = w_D_1(t7, t9);
    real_type t44  = L__[iL_lambda4__xo];
    real_type t45  = t5 * t2;
    real_type t49  = (-t24 * t20 + t8 * t23) * t12;
    result__[ 0   ] = -t28 * t27 * t6 + (-t39 * t23 - t24 * t37 - t8 * t34) * t32 * t3 + (-t28 * t49 * t45 + (-t39 * t20 - t24 * t34 + t8 * t37) * t31 * t45) * t44;
    result__[ 1   ] = 0;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t66  = t65 * t18;
    real_type t68  = Lfun_D_2(t7, t8, t9);
    real_type t69  = t68 * t14;
    result__[ 2   ] = t2 * L__[iL_lambda1__xo] - t62 * t27 * t6 + (-t24 * t69 - t8 * t66 - t20) * t32 * t3 + (-t62 * t49 * t45 + (-t24 * t66 + t8 * t69 + t23) * t31 * t45) * t44;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t89  = t88 * t18;
    real_type t91  = Lfun_D_3(t7, t8, t9);
    real_type t92  = t91 * t14;
    real_type t94  = w_D_2(t7, t9);
    result__[ 3   ] = t2 * L__[iL_lambda2__xo] - t85 * t27 * t6 + (-t94 * t23 - t24 * t92 - t8 * t89) * t32 * t3 + (-t85 * t49 * t45 + (-t94 * t20 - t24 * t89 + t8 * t92) * t31 * t45) * t44;
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t13  = 1.0 / t11 / t10;
    real_type t15  = U__[iU_cL];
    real_type t16  = t15 * t15;
    real_type t19  = t16 * ModelPars[iM_c1] + ModelPars[iM_c0];
    real_type t20  = Dfun(t7, t8, t9);
    real_type t21  = t20 * t19;
    real_type t23  = Lfun(t7, t8, t9);
    real_type t24  = t23 * t15;
    real_type t25  = w(t7, t9);
    real_type t27  = -t8 * t21 - t25 * t24;
    real_type t28  = t27 * t13;
    real_type t29  = v_D_1(t7, t8, t9);
    real_type t30  = t29 * t29;
    real_type t34  = 1.0 / t11;
    real_type t35  = Dfun_D_1(t7, t8, t9);
    real_type t36  = t35 * t19;
    real_type t38  = Lfun_D_1(t7, t8, t9);
    real_type t39  = t38 * t15;
    real_type t41  = w_D_1(t7, t9);
    real_type t43  = -t24 * t41 - t25 * t39 - t8 * t36;
    real_type t44  = t43 * t34;
    real_type t48  = t27 * t34;
    real_type t49  = v_D_1_1(t7, t8, t9);
    real_type t52  = 1.0 / t10;
    real_type t53  = t52 * t5;
    real_type t54  = Dfun_D_1_1(t7, t8, t9);
    real_type t55  = t54 * t19;
    real_type t57  = Lfun_D_1_1(t7, t8, t9);
    real_type t58  = t57 * t15;
    real_type t62  = w_D_1_1(t7, t9);
    real_type t67  = L__[iL_lambda4__xo];
    real_type t68  = t5 * t2;
    real_type t71  = -t25 * t21 + t8 * t24;
    real_type t72  = t71 * t13;
    real_type t79  = -t41 * t21 - t25 * t36 + t8 * t39;
    real_type t80  = t79 * t34;
    real_type t84  = t71 * t34;
    result__[ 0   ] = 2 * t30 * t28 * t6 - 2 * t29 * t44 * t6 - t49 * t48 * t6 + (-t62 * t24 - t25 * t58 - 2 * t41 * t39 - t8 * t55) * t53 * t3 + (2 * t30 * t72 * t68 - 2 * t29 * t80 * t68 - t49 * t84 * t68 + (-t62 * t21 - t25 * t55 - 2 * t41 * t36 + t8 * t58) * t52 * t68) * t67;
    real_type t97  = v_D_2(t7, t8, t9);
    real_type t102 = Dfun_D_2(t7, t8, t9);
    real_type t103 = t102 * t19;
    real_type t105 = Lfun_D_2(t7, t8, t9);
    real_type t106 = t105 * t15;
    real_type t108 = -t8 * t103 - t25 * t106 - t21;
    real_type t109 = t108 * t34;
    real_type t112 = v_D_1_2(t7, t8, t9);
    real_type t117 = Dfun_D_1_2(t7, t8, t9);
    real_type t118 = t117 * t19;
    real_type t120 = Lfun_D_1_2(t7, t8, t9);
    real_type t121 = t120 * t15;
    real_type t127 = t13 * t68;
    real_type t128 = t29 * t71;
    real_type t134 = -t25 * t103 + t8 * t106 + t24;
    real_type t135 = t134 * t34;
    result__[ 1   ] = 2 * t97 * t29 * t28 * t6 - t29 * t109 * t6 - t112 * t48 * t6 - t97 * t44 * t6 + (-t41 * t106 - t8 * t118 - t25 * t121 - t36) * t53 * t3 + (2 * t97 * t128 * t127 - t29 * t135 * t68 - t112 * t84 * t68 - t97 * t80 * t68 + (-t41 * t103 - t25 * t118 + t8 * t121 + t39) * t52 * t68) * t67;
    real_type t150 = v_D_3(t7, t8, t9);
    real_type t155 = Dfun_D_3(t7, t8, t9);
    real_type t156 = t155 * t19;
    real_type t158 = Lfun_D_3(t7, t8, t9);
    real_type t159 = t158 * t15;
    real_type t161 = w_D_2(t7, t9);
    real_type t163 = -t8 * t156 - t25 * t159 - t161 * t24;
    real_type t164 = t163 * t34;
    real_type t167 = v_D_1_3(t7, t8, t9);
    real_type t172 = Dfun_D_1_3(t7, t8, t9);
    real_type t173 = t172 * t19;
    real_type t175 = Lfun_D_1_3(t7, t8, t9);
    real_type t176 = t175 * t15;
    real_type t180 = w_D_1_2(t7, t9);
    real_type t191 = -t25 * t156 + t8 * t159 - t161 * t21;
    real_type t192 = t191 * t34;
    result__[ 2   ] = 2 * t150 * t29 * t28 * t6 - t29 * t164 * t6 - t167 * t48 * t6 - t150 * t44 * t6 + (-t41 * t159 - t161 * t39 - t8 * t173 - t25 * t176 - t180 * t24) * t53 * t3 + (2 * t150 * t128 * t127 - t29 * t192 * t68 - t167 * t84 * t68 - t150 * t80 * t68 + (-t41 * t156 - t161 * t36 - t25 * t173 + t8 * t176 - t180 * t21) * t52 * t68) * t67;
    real_type t209 = t5 * t1;
    real_type t214 = t34 * t5;
    result__[ 3   ] = -t29 * t48 * t209 + t43 * t52 * t209 + (-t128 * t214 + t79 * t53) * t67;
    result__[ 4   ] = result__[1];
    real_type t219 = t97 * t97;
    real_type t226 = v_D_2_2(t7, t8, t9);
    real_type t229 = Dfun_D_2_2(t7, t8, t9);
    real_type t230 = t229 * t19;
    real_type t233 = Lfun_D_2_2(t7, t8, t9);
    real_type t234 = t233 * t15;
    result__[ 5   ] = 2 * t219 * t28 * t6 - 2 * t97 * t109 * t6 - t226 * t48 * t6 + (-t8 * t230 - t25 * t234 - 2 * t103) * t53 * t3 + (2 * t219 * t72 * t68 - 2 * t97 * t135 * t68 - t226 * t84 * t68 + (-t25 * t230 + t8 * t234 + 2 * t106) * t52 * t68) * t67;
    real_type t261 = v_D_2_3(t7, t8, t9);
    real_type t266 = Dfun_D_2_3(t7, t8, t9);
    real_type t267 = t266 * t19;
    real_type t269 = Lfun_D_2_3(t7, t8, t9);
    real_type t270 = t269 * t15;
    real_type t276 = t97 * t71;
    result__[ 6   ] = 2 * t150 * t97 * t28 * t6 - t97 * t164 * t6 - t261 * t48 * t6 - t150 * t109 * t6 + (-t106 * t161 - t25 * t270 - t267 * t8 - t156) * t53 * t3 + (2 * t150 * t276 * t127 - t97 * t192 * t68 - t261 * t84 * t68 - t150 * t135 * t68 + (-t103 * t161 - t25 * t267 + t270 * t8 + t159) * t52 * t68) * t67;
    result__[ 7   ] = L__[iL_lambda1__xo] - t97 * t48 * t209 + t108 * t52 * t209 + (t134 * t53 - t214 * t276) * t67;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t303 = t150 * t150;
    real_type t310 = v_D_3_3(t7, t8, t9);
    real_type t313 = Dfun_D_3_3(t7, t8, t9);
    real_type t314 = t313 * t19;
    real_type t316 = Lfun_D_3_3(t7, t8, t9);
    real_type t317 = t316 * t15;
    real_type t321 = w_D_2_2(t7, t9);
    result__[ 10  ] = 2 * t303 * t28 * t6 - 2 * t150 * t164 * t6 - t310 * t48 * t6 + (-2 * t159 * t161 - t24 * t321 - t25 * t317 - t314 * t8) * t53 * t3 + (2 * t303 * t72 * t68 - 2 * t150 * t192 * t68 - t310 * t84 * t68 + (-2 * t156 * t161 - t21 * t321 - t25 * t314 + t317 * t8) * t52 * t68) * t67;
    result__[ 11  ] = L__[iL_lambda2__xo] - t150 * t48 * t209 + t163 * t52 * t209 + (-t150 * t214 * t71 + t191 * t53) * t67;
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
    real_type t23  = -2 * t8 * t16 * t15 - t21 * t20;
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
    real_type t48  = -2 * t21 * t16 * t15 + t8 * t20;
    real_type t49  = t48 * t12;
    result__[ 0   ] = -t25 * t24 * t6 + (-2 * t8 * t30 * t15 - t36 * t20 - t21 * t34) * t29 * t3 - t25 * t49 * t43 + (-2 * t36 * t16 * t15 - 2 * t21 * t30 * t15 + t8 * t34) * t29 * t42;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t71  = Lfun_D_2(t7, t8, t9);
    result__[ 1   ] = -t62 * t24 * t6 + (-2 * t8 * t65 * t15 - 2 * t16 * t15 - t21 * t71) * t29 * t3 - t62 * t49 * t43 + (-2 * t21 * t65 * t15 + t8 * t71 + t20) * t29 * t42;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t92  = Lfun_D_3(t7, t8, t9);
    real_type t94  = w_D_2(t7, t9);
    result__[ 2   ] = -t85 * t24 * t6 + (-2 * t8 * t88 * t15 - t94 * t20 - t21 * t92) * t29 * t3 - t85 * t49 * t43 + (-2 * t94 * t16 * t15 - 2 * t21 * t88 * t15 + t8 * t92) * t29 * t42;
    result__[ 3   ] = t23 * t28 * t5 * t1 + t48 * t28 * t5 * t41;
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
