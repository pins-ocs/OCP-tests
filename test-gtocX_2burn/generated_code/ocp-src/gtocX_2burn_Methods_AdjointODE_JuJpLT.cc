/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_AdjointODE.cc                              |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burnDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  gtocX_2burn::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  gtocX_2burn::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  gtocX_2burn::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    real_type result__ = ray_positive(-t3 * X__[iX_f] - t6 * X__[iX_g] - 1);
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JPxpu_numEqns() const { return 6; }

  void
  gtocX_2burn::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JUxpu_numEqns() const { return 6; }

  void
  gtocX_2burn::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
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
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::LTxpu_numEqns() const { return 6; }

  void
  gtocX_2burn::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t9   = ALIAS_ray_positive_D(-t1 * t3 - t5 * t6 - 1);
    result__[ 1   ] = -t3 * t9;
    result__[ 2   ] = -t6 * t9;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = (t1 * t6 - t3 * t5) * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::LTargs_numEqns() const { return 1; }

  void
  gtocX_2burn::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    result__[ 0   ] = -t3 * X__[iX_f] - t6 * X__[iX_g] - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2JPD2xpu_numRows() const { return 6; }
  integer gtocX_2burn::D2JPD2xpu_numCols() const { return 6; }
  integer gtocX_2burn::D2JPD2xpu_nnz()     const { return 0; }

  void
  gtocX_2burn::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2LTD2xpu_numRows() const { return 6; }
  integer gtocX_2burn::D2LTD2xpu_numCols() const { return 6; }
  integer gtocX_2burn::D2LTD2xpu_nnz()     const { return 9; }

  void
  gtocX_2burn::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 5   ; jIndex[8 ] = 5   ;
  }


  void
  gtocX_2burn::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t4   = t3 * t1;
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t7   = t6 * t5;
    real_type t8   = -1 - t4 - t7;
    real_type t9   = ALIAS_ray_positive_DD(t8);
    real_type t10  = t3 * t3;
    result__[ 0   ] = t10 * t9;
    result__[ 1   ] = t3 * t6 * t9;
    real_type t14  = t6 * t1 - t3 * t5;
    real_type t15  = t14 * t9;
    real_type t17  = ALIAS_ray_positive_D(t8);
    result__[ 2   ] = -t3 * t15 + t6 * t17;
    result__[ 3   ] = result__[1];
    real_type t19  = t6 * t6;
    result__[ 4   ] = t19 * t9;
    result__[ 5   ] = -t6 * t15 - t3 * t17;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t22  = t14 * t14;
    result__[ 8   ] = t22 * t9 + (t4 + t7) * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2JUD2xpu_numRows() const { return 6; }
  integer gtocX_2burn::D2JUD2xpu_numCols() const { return 6; }
  integer gtocX_2burn::D2JUD2xpu_nnz()     const { return 0; }

  void
  gtocX_2burn::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DLTargsDxpu_numRows() const { return 1; }
  integer gtocX_2burn::DLTargsDxpu_numCols() const { return 6; }
  integer gtocX_2burn::DLTargsDxpu_nnz()     const { return 3; }

  void
  gtocX_2burn::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
  }


  void
  gtocX_2burn::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_L];
    real_type t2   = cos(t1);
    result__[ 0   ] = -t2;
    real_type t3   = sin(t1);
    result__[ 1   ] = -t3;
    result__[ 2   ] = -t2 * X__[iX_g] + t3 * X__[iX_f];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 3, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::D2LTargsD2xpu_numRows() const { return 6; }
  integer gtocX_2burn::D2LTargsD2xpu_numCols() const { return 6; }
  integer gtocX_2burn::D2LTargsD2xpu_nnz()     const { return 5; }

  void
  gtocX_2burn::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 5   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 5   ; jIndex[4 ] = 5   ;
  }


  void
  gtocX_2burn::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_L];
    real_type t2   = sin(t1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = t3 * t2;
    real_type t4   = cos(t1);
    result__[ 1   ] = -t3 * t4;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = t3 * (t2 * X__[iX_g] + t4 * X__[iX_f]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 5, i_segment );
  }

}

// EOF: gtocX_2burn_Methods_AdjointODE.cc
