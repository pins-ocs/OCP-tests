/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_ODE.cc                                        |
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

  integer AlpRider::rhs_ode_numEqns() const { return 4; }

  void
  AlpRider::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = U__[iU_u1];
    real_type t4   = U__[iU_u2];
    result__[ 0   ] = -10 * X__[iX_y1] + t3 + t4;
    result__[ 1   ] = -2 * X__[iX_y2] + t3 + 2 * t4;
    real_type t8   = X__[iX_y3];
    real_type t10  = X__[iX_y4];
    result__[ 2   ] = -3 * t8 + 5 * t10 + t3 - t4;
    result__[ 3   ] = 5 * t8 - 3 * t10 + t3 + 3 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer AlpRider::Drhs_odeDxup_numRows() const { return 4; }
  integer AlpRider::Drhs_odeDxup_numCols() const { return 6; }
  integer AlpRider::Drhs_odeDxup_nnz()     const { return 14; }

  void
  AlpRider::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 5   ;
    iIndex[10] = 3   ; jIndex[10] = 2   ;
    iIndex[11] = 3   ; jIndex[11] = 3   ;
    iIndex[12] = 3   ; jIndex[12] = 4   ;
    iIndex[13] = 3   ; jIndex[13] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -10;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = -2;
    result__[ 4   ] = 1;
    result__[ 5   ] = 2;
    result__[ 6   ] = -3;
    result__[ 7   ] = 5;
    result__[ 8   ] = 1;
    result__[ 9   ] = -1;
    result__[ 10  ] = 5;
    result__[ 11  ] = -3;
    result__[ 12  ] = 1;
    result__[ 13  ] = 3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 14, i_segment );
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
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: AlpRider_Methods_ODE.cc
