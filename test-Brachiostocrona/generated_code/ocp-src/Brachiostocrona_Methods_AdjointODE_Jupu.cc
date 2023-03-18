/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_AdjointODE.cc                          |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_LowBound_DD(__t1) LowBound.DD( __t1)
#define ALIAS_LowBound_D(__t1) LowBound.D( __t1)
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


namespace BrachiostocronaDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Brachiostocrona::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Brachiostocrona::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t3   = vthetaControl(U__[iU_vtheta], -10, 10);
    real_type result__ = t3 * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  Brachiostocrona::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = LowBound(ModelPars[iM_slope_low] * X__[iX_x] - X__[iX_y] + ModelPars[iM_y0_low]);
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::JPxpu_numEqns() const { return 6; }

  void
  Brachiostocrona::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::JUxpu_numEqns() const { return 6; }

  void
  Brachiostocrona::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    real_type t1   = U__[iU_vtheta];
    result__[ 4   ] = vthetaControl(t1, -10, 10);
    real_type t3   = ALIAS_vthetaControl_D_1(t1, -10, 10);
    result__[ 5   ] = t3 * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::LTxpu_numEqns() const { return 6; }

  void
  Brachiostocrona::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_slope_low];
    real_type t7   = ALIAS_LowBound_D(X__[iX_x] * t1 - X__[iX_y] + ModelPars[iM_y0_low]);
    result__[ 0   ] = t1 * t7;
    result__[ 1   ] = -t7;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::LTargs_numEqns() const { return 1; }

  void
  Brachiostocrona::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_slope_low] * X__[iX_x] - X__[iX_y] + ModelPars[iM_y0_low];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::D2JPD2xpu_numRows() const { return 6; }
  integer Brachiostocrona::D2JPD2xpu_numCols() const { return 6; }
  integer Brachiostocrona::D2JPD2xpu_nnz()     const { return 0; }

  void
  Brachiostocrona::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Brachiostocrona::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::D2LTD2xpu_numRows() const { return 6; }
  integer Brachiostocrona::D2LTD2xpu_numCols() const { return 6; }
  integer Brachiostocrona::D2LTD2xpu_nnz()     const { return 4; }

  void
  Brachiostocrona::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  Brachiostocrona::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_slope_low];
    real_type t7   = ALIAS_LowBound_DD(X__[iX_x] * t1 - X__[iX_y] + ModelPars[iM_y0_low]);
    real_type t8   = t1 * t1;
    result__[ 0   ] = t8 * t7;
    result__[ 1   ] = -t1 * t7;
    result__[ 2   ] = result__[1];
    result__[ 3   ] = t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::D2JUD2xpu_numRows() const { return 6; }
  integer Brachiostocrona::D2JUD2xpu_numCols() const { return 6; }
  integer Brachiostocrona::D2JUD2xpu_nnz()     const { return 3; }

  void
  Brachiostocrona::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 5   ;
    iIndex[1 ] = 5   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 5   ;
  }


  void
  Brachiostocrona::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_vtheta];
    result__[ 0   ] = ALIAS_vthetaControl_D_1(t1, -10, 10);
    result__[ 1   ] = result__[0];
    real_type t3   = ALIAS_vthetaControl_D_1_1(t1, -10, 10);
    result__[ 2   ] = t3 * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DLTargsDxpu_numRows() const { return 1; }
  integer Brachiostocrona::DLTargsDxpu_numCols() const { return 6; }
  integer Brachiostocrona::DLTargsDxpu_nnz()     const { return 2; }

  void
  Brachiostocrona::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }


  void
  Brachiostocrona::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_slope_low];
    result__[ 1   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 2, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::D2LTargsD2xpu_numRows() const { return 6; }
  integer Brachiostocrona::D2LTargsD2xpu_numCols() const { return 6; }
  integer Brachiostocrona::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  Brachiostocrona::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  Brachiostocrona::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: Brachiostocrona_Methods_AdjointODE.cc
