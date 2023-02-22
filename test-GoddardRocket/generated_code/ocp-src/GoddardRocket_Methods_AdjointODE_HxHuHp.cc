/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_AdjointODE.cc                            |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::Hxp_numEqns() const { return 4; }

  void
  GoddardRocket::Hxp_eval(
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
    real_type t1   = MU__[1];
    real_type t2   = P__[iP_TimeSize];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    real_type t10  = gg_D(t4);
    result__[ 0   ] = (-t8 * t6 - t10) * t3;
    real_type t12  = ALIAS_vPositive_D(-t5);
    real_type t13  = MU__[0];
    real_type t15  = DD_D_2(t4, t5);
    result__[ 1   ] = -t8 * t15 * t3 + t2 * t13 - t12;
    real_type t18  = ALIAS_massPositive_D(-t7);
    real_type t19  = U__[iU_T];
    real_type t20  = DD(t4, t5);
    real_type t21  = t19 - t20;
    real_type t22  = t7 * t7;
    result__[ 2   ] = -t18 - 1.0 / t22 * t21 * t3;
    real_type t26  = ALIAS_TSPositive_D(-t2);
    real_type t29  = gg(t4);
    result__[ 3   ] = -t26 + t5 * t13 + (t8 * t21 - t29) * t1 - 1.0 / ModelPars[iM_c] * t19 * MU__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DHxpDxpuv_numRows() const { return 4; }
  integer GoddardRocket::DHxpDxpuv_numCols() const { return 8; }
  integer GoddardRocket::DHxpDxpuv_nnz()     const { return 18; }

  void
  GoddardRocket::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 2   ; jIndex[12] = 4   ;
    iIndex[13] = 3   ; jIndex[13] = 0   ;
    iIndex[14] = 3   ; jIndex[14] = 1   ;
    iIndex[15] = 3   ; jIndex[15] = 2   ;
    iIndex[16] = 3   ; jIndex[16] = 3   ;
    iIndex[17] = 3   ; jIndex[17] = 4   ;
  }


  void
  GoddardRocket::DHxpDxpuv_sparse(
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
    real_type t1   = MU__[1];
    real_type t2   = P__[iP_TimeSize];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_h];
    real_type t5   = X__[iX_v];
    real_type t6   = DD_D_1_1(t4, t5);
    real_type t7   = X__[iX_m];
    real_type t8   = 1.0 / t7;
    real_type t10  = gg_DD(t4);
    result__[ 0   ] = (-t8 * t6 - t10) * t3;
    real_type t12  = DD_D_1_2(t4, t5);
    result__[ 1   ] = -t8 * t12 * t3;
    real_type t15  = DD_D_1(t4, t5);
    real_type t16  = t7 * t7;
    real_type t17  = 1.0 / t16;
    result__[ 2   ] = t17 * t15 * t3;
    real_type t20  = gg_D(t4);
    result__[ 3   ] = (-t8 * t15 - t20) * t1;
    result__[ 4   ] = result__[1];
    real_type t22  = ALIAS_vPositive_DD(-t5);
    real_type t23  = DD_D_2_2(t4, t5);
    result__[ 5   ] = -t8 * t23 * t3 + t22;
    real_type t26  = DD_D_2(t4, t5);
    result__[ 6   ] = t17 * t26 * t3;
    result__[ 7   ] = -t8 * t26 * t1 + MU__[0];
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[6];
    real_type t31  = ALIAS_massPositive_DD(-t7);
    real_type t33  = DD(t4, t5);
    real_type t34  = U__[iU_T] - t33;
    result__[ 10  ] = t31 + 2 / t16 / t7 * t34 * t3;
    result__[ 11  ] = -t17 * t34 * t1;
    result__[ 12  ] = -t17 * t3;
    result__[ 13  ] = result__[3];
    result__[ 14  ] = result__[7];
    result__[ 15  ] = result__[11];
    result__[ 16  ] = ALIAS_TSPositive_DD(-t2);
    result__[ 17  ] = t8 * t1 - MU__[2] / ModelPars[iM_c];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 18, i_segment );
  }

}

// EOF: GoddardRocket_Methods_AdjointODE.cc
