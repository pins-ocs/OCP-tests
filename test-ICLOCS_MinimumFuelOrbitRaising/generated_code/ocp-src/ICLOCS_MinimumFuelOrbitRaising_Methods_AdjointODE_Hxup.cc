/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc           |
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


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

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


namespace ICLOCS_MinimumFuelOrbitRaisingDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::Hxp_numEqns() const { return 3; }

  void
  ICLOCS_MinimumFuelOrbitRaising::Hxp_eval(
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
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = X__[iX_vt];
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_r];
    real_type t5   = t4 * t4;
    real_type t6   = 1.0 / t5;
    real_type t13  = MU__[2];
    real_type t15  = X__[iX_vr] * t13;
    result__[ 0   ] = (-t6 * t3 + 2 / t5 / t4) * t1 + t6 * t2 * t15;
    real_type t20  = 1.0 / t4;
    result__[ 1   ] = -t20 * t2 * t13 + MU__[0] - 1;
    result__[ 2   ] = 2 * t20 * t2 * t1 - t20 * t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DHxpDxpuv_numRows() const { return 3; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHxpDxpuv_numCols() const { return 7; }
  integer ICLOCS_MinimumFuelOrbitRaising::DHxpDxpuv_nnz()     const { return 8; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
  ICLOCS_MinimumFuelOrbitRaising::DHxpDxpuv_sparse(
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
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = X__[iX_vt];
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_r];
    real_type t5   = t4 * t4;
    real_type t7   = 1.0 / t5 / t4;
    real_type t10  = t5 * t5;
    real_type t15  = MU__[2];
    real_type t17  = X__[iX_vr] * t15;
    result__[ 0   ] = (2 * t7 * t3 - 6 / t10) * t1 - 2 * t7 * t2 * t17;
    real_type t22  = 1.0 / t5;
    result__[ 1   ] = t22 * t2 * t15;
    result__[ 2   ] = -2 * t22 * t2 * t1 + t22 * t17;
    result__[ 3   ] = result__[1];
    real_type t27  = 1.0 / t4;
    result__[ 4   ] = -t27 * t15;
    result__[ 5   ] = result__[2];
    result__[ 6   ] = result__[4];
    result__[ 7   ] = 2 * t27 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 8, i_segment );
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_AdjointODE.cc
