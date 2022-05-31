/*-----------------------------------------------------------------------*\
 |  file: Train_Methods_ODE.cc                                           |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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


#include "Train.hh"
#include "Train_Pars.hh"

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
#define ALIAS_ubControl_D_3(__t1, __t2, __t3) ubControl.D_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2(__t1, __t2, __t3) ubControl.D_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1(__t1, __t2, __t3) ubControl.D_1( __t1, __t2, __t3)
#define ALIAS_ubControl_D_3_3(__t1, __t2, __t3) ubControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_3(__t1, __t2, __t3) ubControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_2_2(__t1, __t2, __t3) ubControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_3(__t1, __t2, __t3) ubControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_2(__t1, __t2, __t3) ubControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_ubControl_D_1_1(__t1, __t2, __t3) ubControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3(__t1, __t2, __t3) uaControl.D_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2(__t1, __t2, __t3) uaControl.D_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1(__t1, __t2, __t3) uaControl.D_1( __t1, __t2, __t3)
#define ALIAS_uaControl_D_3_3(__t1, __t2, __t3) uaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_3(__t1, __t2, __t3) uaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_2_2(__t1, __t2, __t3) uaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_3(__t1, __t2, __t3) uaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_2(__t1, __t2, __t3) uaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uaControl_D_1_1(__t1, __t2, __t3) uaControl.D_1_1( __t1, __t2, __t3)


namespace TrainDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer Train::rhs_ode_numEqns() const { return 2; }

  void
  Train::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = X__[iX_v];
    real_type t2   = acc(X__[iX_x], result__[0]);
    result__[ 1   ] = t2 + U__[iU_ua] - U__[iU_ub];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Train::Drhs_odeDxpu_numRows() const { return 2; }
  integer Train::Drhs_odeDxpu_numCols() const { return 4; }
  integer Train::Drhs_odeDxpu_nnz()     const { return 5; }

  void
  Train::Drhs_odeDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Train::Drhs_odeDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    real_type t1   = X__[iX_x];
    real_type t2   = X__[iX_v];
    result__[ 1   ] = acc_D_1(t1, t2);
    result__[ 2   ] = acc_D_2(t1, t2);
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxpu_sparse", 5, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Train::A_numRows() const { return 2; }
  integer Train::A_numCols() const { return 2; }
  integer Train::A_nnz()     const { return 2; }

  void
  Train::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Train::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 2, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Train::eta_numEqns() const { return 2; }

  void
  Train::eta_eval(
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
  integer Train::DetaDxp_numRows() const { return 2; }
  integer Train::DetaDxp_numCols() const { return 2; }
  integer Train::DetaDxp_nnz()     const { return 0; }

  void
  Train::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Train::DetaDxp_sparse(
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

  integer Train::nu_numEqns() const { return 2; }

  void
  Train::nu_eval(
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
  integer Train::DnuDxp_numRows() const { return 2; }
  integer Train::DnuDxp_numCols() const { return 2; }
  integer Train::DnuDxp_nnz()     const { return 0; }

  void
  Train::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Train::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: Train_Methods_ODE.cc
