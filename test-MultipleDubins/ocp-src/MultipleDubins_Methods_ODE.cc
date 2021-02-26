/*-----------------------------------------------------------------------*\
 |  file: MultipleDubins_Methods.cc                                      |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "MultipleDubins.hh"
#include "MultipleDubins_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_diff2pi_DD(__t1) diff2pi.DD( __t1)
#define ALIAS_diff2pi_D(__t1) diff2pi.D( __t1)


namespace MultipleDubinsDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  MultipleDubins::rhs_ode_numEqns() const
  { return 9; }

  void
  MultipleDubins::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[0];
    real_type t2   = X__[2];
    real_type t3   = cos(t2);
    result__[ 0   ] = t3 * t1;
    real_type t4   = sin(t2);
    result__[ 1   ] = t4 * t1;
    result__[ 2   ] = P__[3] * t1;
    real_type t6   = P__[1];
    real_type t7   = X__[5];
    real_type t8   = cos(t7);
    result__[ 3   ] = t8 * t6;
    real_type t9   = sin(t7);
    result__[ 4   ] = t9 * t6;
    result__[ 5   ] = P__[4] * t6;
    real_type t11  = P__[2];
    real_type t12  = X__[8];
    real_type t13  = cos(t12);
    result__[ 6   ] = t13 * t11;
    real_type t14  = sin(t12);
    result__[ 7   ] = t14 * t11;
    result__[ 8   ] = P__[5] * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::Drhs_odeDx_numRows() const
  { return 9; }

  integer
  MultipleDubins::Drhs_odeDx_numCols() const
  { return 9; }

  integer
  MultipleDubins::Drhs_odeDx_nnz() const
  { return 6; }

  void
  MultipleDubins::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 4   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 6   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 7   ; jIndex[5 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[0];
    real_type t2   = X__[2];
    real_type t3   = sin(t2);
    result__[ 0   ] = -t3 * t1;
    real_type t5   = cos(t2);
    result__[ 1   ] = t5 * t1;
    real_type t6   = P__[1];
    real_type t7   = X__[5];
    real_type t8   = sin(t7);
    result__[ 2   ] = -t8 * t6;
    real_type t10  = cos(t7);
    result__[ 3   ] = t10 * t6;
    real_type t11  = P__[2];
    real_type t12  = X__[8];
    real_type t13  = sin(t12);
    result__[ 4   ] = -t13 * t11;
    real_type t15  = cos(t12);
    result__[ 5   ] = t15 * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::Drhs_odeDp_numRows() const
  { return 9; }

  integer
  MultipleDubins::Drhs_odeDp_numCols() const
  { return 6; }

  integer
  MultipleDubins::Drhs_odeDp_nnz() const
  { return 12; }

  void
  MultipleDubins::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 6   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 7   ; jIndex[9 ] = 2   ;
    iIndex[10] = 8   ; jIndex[10] = 2   ;
    iIndex[11] = 8   ; jIndex[11] = 5   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[2];
    result__[ 0   ] = cos(t1);
    result__[ 1   ] = sin(t1);
    result__[ 2   ] = P__[3];
    result__[ 3   ] = P__[0];
    real_type t2   = X__[5];
    result__[ 4   ] = cos(t2);
    result__[ 5   ] = sin(t2);
    result__[ 6   ] = P__[4];
    result__[ 7   ] = P__[1];
    real_type t3   = X__[8];
    result__[ 8   ] = cos(t3);
    result__[ 9   ] = sin(t3);
    result__[ 10  ] = P__[5];
    result__[ 11  ] = P__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MultipleDubins::Drhs_odeDu_numRows() const
  { return 9; }

  integer
  MultipleDubins::Drhs_odeDu_numCols() const
  { return 0; }

  integer
  MultipleDubins::Drhs_odeDu_nnz() const
  { return 0; }

  void
  MultipleDubins::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  MultipleDubins::A_numRows() const
  { return 9; }

  integer
  MultipleDubins::A_numCols() const
  { return 9; }

  integer
  MultipleDubins::A_nnz() const
  { return 9; }

  void
  MultipleDubins::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MultipleDubins::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 9, i_segment );
  }

}

// EOF: MultipleDubins_Methods.cc
