/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_AdjointODE.cc                                |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_max_DD(__t1) VelBound_max.DD( __t1)
#define ALIAS_VelBound_max_D(__t1) VelBound_max.D( __t1)
#define ALIAS_VelBound_min_DD(__t1) VelBound_min.DD( __t1)
#define ALIAS_VelBound_min_D(__t1) VelBound_min.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::Hxp_numEqns() const { return 4; }

  void
  Crossroad::Hxp_eval(
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
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t19  = ALIAS_AccBound_D(t12 * t16 * t9 + t2 * t5 - 1);
    real_type t22  = kappa_D(t10);
    result__[ 0   ] = 2 * t22 * t16 * t11 * t9 * t19;
    real_type t30  = ALIAS_VelBound_min_D(-t7);
    real_type t33  = ALIAS_VelBound_max_D(t7 - ModelPars[iM_v_max]);
    real_type t34  = MU__[0];
    real_type t35  = X__[iX_Ts];
    result__[ 1   ] = 4 * t12 * t16 * t19 * t7 * t8 + t34 * t35 - t30 + t33;
    real_type t40  = MU__[1];
    result__[ 2   ] = 2 * t1 * t19 * t5 + t35 * t40;
    real_type t44  = U__[iU_jerk];
    real_type t45  = t44 * t44;
    real_type t47  = ALIAS_Tpositive_D(-t35);
    result__[ 3   ] = t1 * t40 + t34 * t7 + t44 * MU__[2] + t45 * ModelPars[iM_wJ] - t47 + ModelPars[iM_wT];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DHxpDxpuv_numRows() const { return 4; }
  integer Crossroad::DHxpDxpuv_numCols() const { return 9; }
  integer Crossroad::DHxpDxpuv_nnz()     const { return 15; }

  void
  Crossroad::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 2   ;
    iIndex[10] = 2   ; jIndex[10] = 3   ;
    iIndex[11] = 3   ; jIndex[11] = 1   ;
    iIndex[12] = 3   ; jIndex[12] = 2   ;
    iIndex[13] = 3   ; jIndex[13] = 3   ;
    iIndex[14] = 3   ; jIndex[14] = 4   ;
  }


  void
  Crossroad::DHxpDxpuv_sparse(
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
    real_type t1   = X__[iX_a];
    real_type t2   = t1 * t1;
    real_type t4   = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t5   = 1.0 / t4;
    real_type t7   = X__[iX_v];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_s];
    real_type t11  = kappa(t10);
    real_type t12  = t11 * t11;
    real_type t15  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t16  = 1.0 / t15;
    real_type t18  = t16 * t12 * t9 + t5 * t2 - 1;
    real_type t19  = ALIAS_AccBound_DD(t18);
    real_type t20  = t9 * t9;
    real_type t22  = t15 * t15;
    real_type t23  = 1.0 / t22;
    real_type t25  = kappa_D(t10);
    real_type t26  = t25 * t25;
    real_type t30  = ALIAS_AccBound_D(t18);
    real_type t31  = t9 * t30;
    real_type t35  = t16 * t11;
    real_type t36  = kappa_DD(t10);
    result__[ 0   ] = 4 * t26 * t23 * t12 * t20 * t19 + 2 * t16 * t26 * t31 + 2 * t36 * t35 * t31;
    real_type t40  = t8 * t7;
    result__[ 1   ] = 8 * t25 * t23 * t12 * t11 * t9 * t40 * t19 + 8 * t25 * t35 * t40 * t30;
    real_type t52  = t5 * t1 * t19;
    result__[ 2   ] = 4 * t25 * t16 * t11 * t9 * t52;
    result__[ 3   ] = result__[1];
    real_type t59  = t12 * t12;
    real_type t67  = ALIAS_VelBound_min_DD(-t7);
    real_type t70  = ALIAS_VelBound_max_DD(t7 - ModelPars[iM_v_max]);
    result__[ 4   ] = 16 * t23 * t59 * t9 * t8 * t19 + 12 * t16 * t12 * t8 * t30 + t67 + t70;
    result__[ 5   ] = 8 * t16 * t12 * t40 * t52;
    result__[ 6   ] = MU__[0];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[5];
    real_type t75  = t4 * t4;
    result__[ 9   ] = 4 / t75 * t2 * t19 + 2 * t5 * t30;
    result__[ 10  ] = MU__[1];
    result__[ 11  ] = result__[6];
    result__[ 12  ] = result__[10];
    result__[ 13  ] = ALIAS_Tpositive_DD(-X__[iX_Ts]);
    result__[ 14  ] = 2 * U__[iU_jerk] * ModelPars[iM_wJ] + MU__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 15, i_segment );
  }

}

// EOF: Crossroad_Methods_AdjointODE.cc
