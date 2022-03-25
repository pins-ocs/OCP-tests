/*-----------------------------------------------------------------------*\
 |  file: SecondOrderSingularRegulator_Methods_AdjointODE.cc             |
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


#include "SecondOrderSingularRegulator.hh"
#include "SecondOrderSingularRegulator_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace SecondOrderSingularRegulatorDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::JPx_numEqns() const { return 2; }

  void
  SecondOrderSingularRegulator::JPx_eval(
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
      Mechatronix::check_in_segment( result__, "JPx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::LTx_numEqns() const { return 2; }

  void
  SecondOrderSingularRegulator::LTx_eval(
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
      Mechatronix::check_in_segment( result__, "LTx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::JUx_numEqns() const { return 2; }

  void
  SecondOrderSingularRegulator::JUx_eval(
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
      Mechatronix::check_in_segment( result__, "JUx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::JPp_numEqns() const { return 0; }

  void
  SecondOrderSingularRegulator::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::LTp_numEqns() const { return 0; }

  void
  SecondOrderSingularRegulator::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::JUp_numEqns() const { return 0; }

  void
  SecondOrderSingularRegulator::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::JPu_numEqns() const { return 1; }

  void
  SecondOrderSingularRegulator::JPu_eval(
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

  integer SecondOrderSingularRegulator::LTu_numEqns() const { return 1; }

  void
  SecondOrderSingularRegulator::LTu_eval(
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

  integer SecondOrderSingularRegulator::JUu_numEqns() const { return 1; }

  void
  SecondOrderSingularRegulator::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::LTargs_numEqns() const { return 0; }

  void
  SecondOrderSingularRegulator::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DJPxDxp_numRows() const { return 2; }
  integer SecondOrderSingularRegulator::DJPxDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DJPxDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DLTxDxp_numRows() const { return 2; }
  integer SecondOrderSingularRegulator::DLTxDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DLTxDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DJUxDxp_numRows() const { return 2; }
  integer SecondOrderSingularRegulator::DJUxDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DJUxDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DJPuDxp_numRows() const { return 1; }
  integer SecondOrderSingularRegulator::DJPuDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DJPuDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DLTuDxp_numRows() const { return 1; }
  integer SecondOrderSingularRegulator::DLTuDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DLTuDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DJUuDxp_numRows() const { return 1; }
  integer SecondOrderSingularRegulator::DJUuDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DJUuDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DJPpDp_numRows() const { return 0; }
  integer SecondOrderSingularRegulator::DJPpDp_numCols() const { return 0; }
  integer SecondOrderSingularRegulator::DJPpDp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DLTpDp_numRows() const { return 0; }
  integer SecondOrderSingularRegulator::DLTpDp_numCols() const { return 0; }
  integer SecondOrderSingularRegulator::DLTpDp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DJUpDp_numRows() const { return 0; }
  integer SecondOrderSingularRegulator::DJUpDp_numCols() const { return 0; }
  integer SecondOrderSingularRegulator::DJUpDp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DLTargsDxup_numRows() const { return 0; }
  integer SecondOrderSingularRegulator::DLTargsDxup_numCols() const { return 3; }
  integer SecondOrderSingularRegulator::DLTargsDxup_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::D2LTargsD2xup_numRows() const { return 3; }
  integer SecondOrderSingularRegulator::D2LTargsD2xup_numCols() const { return 3; }
  integer SecondOrderSingularRegulator::D2LTargsD2xup_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::D2LTargsD2xup_sparse(
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

  integer SecondOrderSingularRegulator::Hx_numEqns() const { return 2; }

  void
  SecondOrderSingularRegulator::Hx_eval(
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
    result__[ 0   ] = 2 * X__[iX_y1];
    result__[ 1   ] = 2 * X__[iX_y2] + L__[iL_lambda1__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer SecondOrderSingularRegulator::Hp_numEqns() const { return 0; }

  void
  SecondOrderSingularRegulator::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DHxDxp_numRows() const { return 2; }
  integer SecondOrderSingularRegulator::DHxDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DHxDxp_nnz()     const { return 2; }

  void
  SecondOrderSingularRegulator::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  SecondOrderSingularRegulator::DHxDxp_sparse(
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
    result__[ 0   ] = 2;
    result__[ 1   ] = 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DHpDp_numRows() const { return 0; }
  integer SecondOrderSingularRegulator::DHpDp_numCols() const { return 0; }
  integer SecondOrderSingularRegulator::DHpDp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DHpDp_sparse(
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

  integer SecondOrderSingularRegulator::Hu_numEqns() const { return 1; }

  void
  SecondOrderSingularRegulator::Hu_eval(
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
    result__[ 0   ] = L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DHuDxp_numRows() const { return 1; }
  integer SecondOrderSingularRegulator::DHuDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DHuDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DHuDxp_sparse(
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

  integer SecondOrderSingularRegulator::eta_numEqns() const { return 2; }

  void
  SecondOrderSingularRegulator::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DetaDxp_numRows() const { return 2; }
  integer SecondOrderSingularRegulator::DetaDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DetaDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DetaDxp_sparse(
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

  integer SecondOrderSingularRegulator::nu_numEqns() const { return 2; }

  void
  SecondOrderSingularRegulator::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer SecondOrderSingularRegulator::DnuDxp_numRows() const { return 2; }
  integer SecondOrderSingularRegulator::DnuDxp_numCols() const { return 2; }
  integer SecondOrderSingularRegulator::DnuDxp_nnz()     const { return 0; }

  void
  SecondOrderSingularRegulator::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  SecondOrderSingularRegulator::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: SecondOrderSingularRegulator_Methods_AdjointODE.cc
