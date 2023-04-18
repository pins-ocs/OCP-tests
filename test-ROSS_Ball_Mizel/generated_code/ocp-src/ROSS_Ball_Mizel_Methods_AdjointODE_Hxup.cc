/*-----------------------------------------------------------------------*\
 |  file: ROSS_Ball_Mizel_Methods_AdjointODE.cc                          |
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


#include "ROSS_Ball_Mizel.hh"
#include "ROSS_Ball_Mizel_Pars.hh"

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


namespace ROSS_Ball_MizelDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ROSS_Ball_Mizel::Hxp_numEqns() const { return 1; }

  void
  ROSS_Ball_Mizel::Hxp_eval(
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
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t5   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t8   = U__[iU_u] * U__[iU_u];
    real_type t9   = t8 * t8;
    real_type t11  = t9 * t9;
    result__[ 0   ] = -6 * t2 * t11 * t9 * t8 * (-t2 * t1 + t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ROSS_Ball_Mizel::DHxpDxpuv_numRows() const { return 1; }
  integer ROSS_Ball_Mizel::DHxpDxpuv_numCols() const { return 3; }
  integer ROSS_Ball_Mizel::DHxpDxpuv_nnz()     const { return 2; }

  void
  ROSS_Ball_Mizel::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }


  void
  ROSS_Ball_Mizel::DHxpDxpuv_sparse(
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
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_u];
    real_type t5   = t4 * t4;
    real_type t6   = t5 * t5;
    real_type t8   = t6 * t6;
    real_type t9   = t8 * t6 * t5;
    real_type t14  = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t15  = -t2 * t1 + t14;
    result__[ 0   ] = -12 * t1 * t9 * t15 + 18 * t9 * t3;
    result__[ 1   ] = -84 * t2 * t8 * t6 * t4 * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 2, i_segment );
  }

}

// EOF: ROSS_Ball_Mizel_Methods_AdjointODE.cc
