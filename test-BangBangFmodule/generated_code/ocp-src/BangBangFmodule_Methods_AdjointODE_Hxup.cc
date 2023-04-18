/*-----------------------------------------------------------------------*\
 |  file: BangBangFmodule_Methods_AdjointODE.cc                          |
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


#include "BangBangFmodule.hh"
#include "BangBangFmodule_Pars.hh"

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
#define ALIAS_controlM_D_3(__t1, __t2, __t3) controlM.D_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2(__t1, __t2, __t3) controlM.D_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1(__t1, __t2, __t3) controlM.D_1( __t1, __t2, __t3)
#define ALIAS_controlM_D_3_3(__t1, __t2, __t3) controlM.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2_3(__t1, __t2, __t3) controlM.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_2_2(__t1, __t2, __t3) controlM.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_3(__t1, __t2, __t3) controlM.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_2(__t1, __t2, __t3) controlM.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlM_D_1_1(__t1, __t2, __t3) controlM.D_1_1( __t1, __t2, __t3)
#define ALIAS_controlP_D_3(__t1, __t2, __t3) controlP.D_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2(__t1, __t2, __t3) controlP.D_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1(__t1, __t2, __t3) controlP.D_1( __t1, __t2, __t3)
#define ALIAS_controlP_D_3_3(__t1, __t2, __t3) controlP.D_3_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2_3(__t1, __t2, __t3) controlP.D_2_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_2_2(__t1, __t2, __t3) controlP.D_2_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_3(__t1, __t2, __t3) controlP.D_1_3( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_2(__t1, __t2, __t3) controlP.D_1_2( __t1, __t2, __t3)
#define ALIAS_controlP_D_1_1(__t1, __t2, __t3) controlP.D_1_1( __t1, __t2, __t3)


namespace BangBangFmoduleDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFmodule::Hxp_numEqns() const { return 2; }

  void
  BangBangFmodule::Hxp_eval(
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
    result__[ 1   ] = MU__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 2, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFmodule::DHxpDxpuv_numRows() const { return 2; }
  integer BangBangFmodule::DHxpDxpuv_numCols() const { return 6; }
  integer BangBangFmodule::DHxpDxpuv_nnz()     const { return 0; }

  void
  BangBangFmodule::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  BangBangFmodule::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

}

// EOF: BangBangFmodule_Methods_AdjointODE.cc
