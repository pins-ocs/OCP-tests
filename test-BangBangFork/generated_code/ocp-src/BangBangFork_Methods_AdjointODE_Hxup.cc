/*-----------------------------------------------------------------------*\
 |  file: BangBangFork_Methods_AdjointODE.cc                             |
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


#include "BangBangFork.hh"
#include "BangBangFork_Pars.hh"

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
#define ALIAS_Tbarrier_DD(__t1) Tbarrier.DD( __t1)
#define ALIAS_Tbarrier_D(__t1) Tbarrier.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace BangBangForkDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFork::Hxp_numEqns() const { return 4; }

  void
  BangBangFork::Hxp_eval(
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
    real_type t1   = MU__[2];
    real_type t2   = P__[iP_T];
    real_type t4   = X__[iX_x2];
    real_type t5   = t4 * t4;
    real_type t6   = t5 * t5;
    real_type t7   = ModelPars[iM_kappa];
    real_type t11  = MU__[0];
    result__[ 1   ] = -5 * t7 * t6 * t2 * t1 - t2 * t11;
    real_type t13  = MU__[1];
    result__[ 2   ] = t2 * t13;
    real_type t15  = U__[iU_u2];
    real_type t16  = t15 * t15;
    real_type t18  = U__[iU_u];
    real_type t19  = uControl(t18, -1, 1);
    real_type t20  = ALIAS_Tbarrier_D(-t2);
    result__[ 3   ] = t16 * ModelPars[iM_WC] + t19 - t20 - t4 * t11 + (t15 * ModelPars[iM_WU2] + X__[iX_x3]) * t13 + (-t6 * t4 * t7 + t18) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFork::DHxpDxpuv_numRows() const { return 4; }
  integer BangBangFork::DHxpDxpuv_numCols() const { return 9; }
  integer BangBangFork::DHxpDxpuv_nnz()     const { return 8; }

  void
  BangBangFork::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 3   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 3   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 5   ;
  }


  void
  BangBangFork::DHxpDxpuv_sparse(
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
    real_type t1   = MU__[2];
    real_type t2   = P__[iP_T];
    real_type t4   = ModelPars[iM_kappa];
    real_type t5   = X__[iX_x2];
    real_type t6   = t5 * t5;
    result__[ 0   ] = -20 * t6 * t5 * t4 * t2 * t1;
    real_type t12  = t6 * t6;
    result__[ 1   ] = -5 * t12 * t4 * t1 - MU__[0];
    result__[ 2   ] = MU__[1];
    result__[ 3   ] = result__[1];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = ALIAS_Tbarrier_DD(-t2);
    real_type t17  = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 6   ] = t17 + t1;
    result__[ 7   ] = 2 * ModelPars[iM_WC] * U__[iU_u2] + ModelPars[iM_WU2] * result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 8, i_segment );
  }

}

// EOF: BangBangFork_Methods_AdjointODE.cc
