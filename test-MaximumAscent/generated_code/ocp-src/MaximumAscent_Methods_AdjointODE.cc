/*-----------------------------------------------------------------------*\
 |  file: MaximumAscent_Methods_AdjointODE.cc                            |
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


#include "MaximumAscent.hh"
#include "MaximumAscent_Pars.hh"

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


namespace MaximumAscentDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::JPx_numEqns() const { return 4; }

  void
  MaximumAscent::JPx_eval(
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

  integer MaximumAscent::LTx_numEqns() const { return 4; }

  void
  MaximumAscent::LTx_eval(
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

  integer MaximumAscent::JUx_numEqns() const { return 4; }

  void
  MaximumAscent::JUx_eval(
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

  integer MaximumAscent::JPp_numEqns() const { return 0; }

  void
  MaximumAscent::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::LTp_numEqns() const { return 0; }

  void
  MaximumAscent::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::JUp_numEqns() const { return 0; }

  void
  MaximumAscent::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::JPu_numEqns() const { return 1; }

  void
  MaximumAscent::JPu_eval(
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

  integer MaximumAscent::LTu_numEqns() const { return 1; }

  void
  MaximumAscent::LTu_eval(
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

  integer MaximumAscent::JUu_numEqns() const { return 1; }

  void
  MaximumAscent::JUu_eval(
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
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::LTargs_numEqns() const { return 0; }

  void
  MaximumAscent::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DJPxDxp_numRows() const { return 4; }
  integer MaximumAscent::DJPxDxp_numCols() const { return 4; }
  integer MaximumAscent::DJPxDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DLTxDxp_numRows() const { return 4; }
  integer MaximumAscent::DLTxDxp_numCols() const { return 4; }
  integer MaximumAscent::DLTxDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DJUxDxp_numRows() const { return 4; }
  integer MaximumAscent::DJUxDxp_numCols() const { return 4; }
  integer MaximumAscent::DJUxDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DJPuDxp_numRows() const { return 1; }
  integer MaximumAscent::DJPuDxp_numCols() const { return 4; }
  integer MaximumAscent::DJPuDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DLTuDxp_numRows() const { return 1; }
  integer MaximumAscent::DLTuDxp_numCols() const { return 4; }
  integer MaximumAscent::DLTuDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DJUuDxp_numRows() const { return 1; }
  integer MaximumAscent::DJUuDxp_numCols() const { return 4; }
  integer MaximumAscent::DJUuDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DJPpDp_numRows() const { return 0; }
  integer MaximumAscent::DJPpDp_numCols() const { return 0; }
  integer MaximumAscent::DJPpDp_nnz()     const { return 0; }

  void
  MaximumAscent::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DLTpDp_numRows() const { return 0; }
  integer MaximumAscent::DLTpDp_numCols() const { return 0; }
  integer MaximumAscent::DLTpDp_nnz()     const { return 0; }

  void
  MaximumAscent::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DJUpDp_numRows() const { return 0; }
  integer MaximumAscent::DJUpDp_numCols() const { return 0; }
  integer MaximumAscent::DJUpDp_nnz()     const { return 0; }

  void
  MaximumAscent::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DLTargsDxup_numRows() const { return 0; }
  integer MaximumAscent::DLTargsDxup_numCols() const { return 5; }
  integer MaximumAscent::DLTargsDxup_nnz()     const { return 0; }

  void
  MaximumAscent::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
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

  integer MaximumAscent::Hx_numEqns() const { return 4; }

  void
  MaximumAscent::Hx_eval(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t5   = t4 * L__[iL_lambda2__xo];
    real_type t6   = X__[iX_v];
    real_type t7   = t6 * t6;
    real_type t8   = X__[iX_r];
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t18  = t4 * L__[iL_lambda3__xo];
    real_type t19  = X__[iX_u];
    real_type t24  = t4 * L__[iL_lambda4__xo];
    result__[ 0   ] = (-t10 * t7 + 2 / t9 / t8) * t5 + t10 * t6 * t19 * t18 - t10 * t6 * t24;
    real_type t29  = 1.0 / t8;
    real_type t30  = t29 * t6;
    result__[ 1   ] = -t30 * t18 + t4 * L__[iL_lambda1__xo];
    result__[ 2   ] = -t29 * t19 * t18 + t29 * t24 + 2 * t30 * t5;
    result__[ 3   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer MaximumAscent::Hp_numEqns() const { return 0; }

  void
  MaximumAscent::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DHxDxp_numRows() const { return 4; }
  integer MaximumAscent::DHxDxp_numCols() const { return 4; }
  integer MaximumAscent::DHxDxp_nnz()     const { return 8; }

  void
  MaximumAscent::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 2   ;
  }


  void
  MaximumAscent::DHxDxp_sparse(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = eta(t3);
    real_type t5   = t4 * L__[iL_lambda2__xo];
    real_type t6   = X__[iX_v];
    real_type t7   = t6 * t6;
    real_type t8   = X__[iX_r];
    real_type t9   = t8 * t8;
    real_type t11  = 1.0 / t9 / t8;
    real_type t14  = t9 * t9;
    real_type t20  = t4 * L__[iL_lambda3__xo];
    real_type t21  = X__[iX_u];
    real_type t27  = t4 * L__[iL_lambda4__xo];
    result__[ 0   ] = (2 * t11 * t7 - 6 / t14) * t5 - 2 * t11 * t6 * t21 * t20 + 2 * t11 * t6 * t27;
    real_type t31  = 1.0 / t9;
    real_type t32  = t31 * t6;
    result__[ 1   ] = t32 * t20;
    result__[ 2   ] = t31 * t21 * t20 - t31 * t27 - 2 * t32 * t5;
    result__[ 3   ] = result__[1];
    real_type t38  = 1.0 / t8;
    result__[ 4   ] = -t38 * t20;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 2 * t38 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DHpDp_numRows() const { return 0; }
  integer MaximumAscent::DHpDp_numCols() const { return 0; }
  integer MaximumAscent::DHpDp_nnz()     const { return 0; }

  void
  MaximumAscent::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DHpDp_sparse(
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

  integer MaximumAscent::Hu_numEqns() const { return 1; }

  void
  MaximumAscent::Hu_eval(
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
    real_type t3   = tf(ModelPars[iM_days]);
    real_type t4   = Tbar(t3);
    real_type t12  = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_mdot] * t3 + ModelPars[iM_m0]);
    real_type t13  = U__[iU_alpha];
    real_type t14  = cos(t13);
    real_type t19  = sin(t13);
    result__[ 0   ] = t14 * t12 * t4 * L__[iL_lambda2__xo] - t19 * t12 * t4 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer MaximumAscent::DHuDxp_numRows() const { return 1; }
  integer MaximumAscent::DHuDxp_numCols() const { return 4; }
  integer MaximumAscent::DHuDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DHuDxp_sparse(
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

  integer MaximumAscent::eta_numEqns() const { return 4; }

  void
  MaximumAscent::eta_eval(
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
  integer MaximumAscent::DetaDxp_numRows() const { return 4; }
  integer MaximumAscent::DetaDxp_numCols() const { return 4; }
  integer MaximumAscent::DetaDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DetaDxp_sparse(
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

  integer MaximumAscent::nu_numEqns() const { return 4; }

  void
  MaximumAscent::nu_eval(
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
  integer MaximumAscent::DnuDxp_numRows() const { return 4; }
  integer MaximumAscent::DnuDxp_numCols() const { return 4; }
  integer MaximumAscent::DnuDxp_nnz()     const { return 0; }

  void
  MaximumAscent::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  MaximumAscent::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: MaximumAscent_Methods_AdjointODE.cc
