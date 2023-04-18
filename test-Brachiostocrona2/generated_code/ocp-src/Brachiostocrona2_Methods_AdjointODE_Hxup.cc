/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods_AdjointODE.cc                         |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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
#define ALIAS_TimePositive_DD(__t1) TimePositive.DD( __t1)
#define ALIAS_TimePositive_D(__t1) TimePositive.D( __t1)


namespace Brachiostocrona2Define {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona2::Hxp_numEqns() const { return 4; }

  void
  Brachiostocrona2::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    real_type t1   = MU__[0];
    real_type t2   = P__[iP_T];
    real_type t4   = U__[iU_theta];
    real_type t5   = cos(t4);
    real_type t7   = MU__[1];
    real_type t9   = sin(t4);
    result__[ 2   ] = t5 * t2 * t1 + t9 * t2 * t7;
    real_type t11  = ALIAS_TimePositive_D(-t2);
    real_type t12  = X__[iX_v];
    result__[ 3   ] = t5 * t12 * t1 + t9 * t12 * t7 - t9 * ModelPars[iM_g] * MU__[2] - t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DHxpDxpuv_numRows() const { return 4; }
  integer Brachiostocrona2::DHxpDxpuv_numCols() const { return 8; }
  integer Brachiostocrona2::DHxpDxpuv_nnz()     const { return 5; }

  void
  Brachiostocrona2::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 2   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 2   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 3   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 4   ;
  }


  void
  Brachiostocrona2::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t2   = U__[iU_theta];
    real_type t3   = cos(t2);
    real_type t5   = MU__[1];
    real_type t6   = sin(t2);
    result__[ 0   ] = t3 * t1 + t6 * t5;
    real_type t8   = P__[iP_T];
    result__[ 1   ] = -t6 * t8 * t1 + t3 * t8 * t5;
    result__[ 2   ] = result__[0];
    result__[ 3   ] = ALIAS_TimePositive_DD(-t8);
    real_type t13  = X__[iX_v];
    result__[ 4   ] = -t6 * t13 * t1 + t3 * t13 * t5 - t3 * ModelPars[iM_g] * MU__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 5, i_segment );
  }

}

// EOF: Brachiostocrona2_Methods_AdjointODE.cc
