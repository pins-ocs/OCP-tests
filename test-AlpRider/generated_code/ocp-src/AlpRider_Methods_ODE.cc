/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_ODE.cc                                        |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer AlpRider::ode_numEqns() const { return 4; }

  void
  AlpRider::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t3   = U__[iU_u1];
    real_type t4   = U__[iU_u2];
    result__[ 0   ] = -10 * X__[iX_y1] + t3 + t4 - V__[0];
    result__[ 1   ] = -2 * X__[iX_y2] + t3 + 2 * t4 - V__[1];
    real_type t10  = X__[iX_y3];
    real_type t12  = X__[iX_y4];
    result__[ 2   ] = -3 * t10 + 5 * t12 + t3 - t4 - V__[2];
    result__[ 3   ] = 5 * t10 - 3 * t12 + t3 + 3 * t4 - V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::DodeDxpuv_numRows() const { return 4; }
  integer AlpRider::DodeDxpuv_numCols() const { return 10; }
  integer AlpRider::DodeDxpuv_nnz()     const { return 18; }

  void
  AlpRider::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
    iIndex[10] = 2   ; jIndex[10] = 4   ;
    iIndex[11] = 2   ; jIndex[11] = 5   ;
    iIndex[12] = 2   ; jIndex[12] = 8   ;
    iIndex[13] = 3   ; jIndex[13] = 2   ;
    iIndex[14] = 3   ; jIndex[14] = 3   ;
    iIndex[15] = 3   ; jIndex[15] = 4   ;
    iIndex[16] = 3   ; jIndex[16] = 5   ;
    iIndex[17] = 3   ; jIndex[17] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -10;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -1;
    result__[ 4   ] = -2;
    result__[ 5   ] = 1;
    result__[ 6   ] = 2;
    result__[ 7   ] = -1;
    result__[ 8   ] = -3;
    result__[ 9   ] = 5;
    result__[ 10  ] = 1;
    result__[ 11  ] = -1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 5;
    result__[ 14  ] = -3;
    result__[ 15  ] = 1;
    result__[ 16  ] = 3;
    result__[ 17  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 18, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::A_numRows() const { return 4; }
  integer AlpRider::A_numCols() const { return 4; }
  integer AlpRider::A_nnz()     const { return 4; }

  void
  AlpRider::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: AlpRider_Methods_ODE.cc
