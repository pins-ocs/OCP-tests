/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_AdjointODE.cc                       |
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


#include "ICLOCS_StirredTank.hh"
#include "ICLOCS_StirredTank_Pars.hh"

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
#define ALIAS_x2bound_max_DD(__t1) x2bound_max.DD( __t1)
#define ALIAS_x2bound_max_D(__t1) x2bound_max.D( __t1)
#define ALIAS_x2bound_min_DD(__t1) x2bound_min.DD( __t1)
#define ALIAS_x2bound_min_D(__t1) x2bound_min.D( __t1)
#define ALIAS_x1bound_max_DD(__t1) x1bound_max.DD( __t1)
#define ALIAS_x1bound_max_D(__t1) x1bound_max.D( __t1)
#define ALIAS_x1bound_min_DD(__t1) x1bound_min.DD( __t1)
#define ALIAS_x1bound_min_D(__t1) x1bound_min.D( __t1)
#define ALIAS_tfbound_DD(__t1) tfbound.DD( __t1)
#define ALIAS_tfbound_D(__t1) tfbound.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS_StirredTankDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::Hxp_numEqns() const { return 3; }

  void
  ICLOCS_StirredTank::Hxp_eval(
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
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = X__[iX_x1];
    real_type t4   = t2 - ModelPars[iM_x1_f];
    real_type t7   = ALIAS_x1bound_min_D(-t2);
    real_type t8   = t2 - 1;
    real_type t9   = ALIAS_x1bound_max_D(t8);
    real_type t10  = MU__[0];
    real_type t11  = t1 * t10;
    real_type t13  = 1.0 / ModelPars[iM_theta];
    real_type t14  = ModelPars[iM_k];
    real_type t15  = ModelPars[iM_En];
    real_type t16  = X__[iX_x2];
    real_type t19  = exp(-1.0 / t16 * t15);
    real_type t20  = t19 * t14;
    real_type t23  = MU__[1];
    real_type t24  = t1 * t23;
    result__[ 0   ] = 2 * t4 * t1 - t7 + t9 + (-t13 - t20) * t11 + t20 * t24;
    real_type t27  = t16 - ModelPars[iM_x2_f];
    real_type t30  = ALIAS_x2bound_min_D(-t16);
    real_type t32  = ALIAS_x2bound_max_D(t16 - 1);
    real_type t35  = t16 * t16;
    real_type t36  = 1.0 / t35;
    real_type t40  = t2 * t14;
    real_type t45  = U__[iU_u];
    real_type t46  = t45 * ModelPars[iM_a];
    result__[ 1   ] = 2 * t27 * t1 - t30 + t32 - t19 * t36 * t15 * t2 * t14 * t11 + (t15 * t19 * t36 * t40 - t13 - t46) * t24;
    real_type t50  = t4 * t4;
    real_type t51  = t27 * t27;
    real_type t54  = pow(t45 - ModelPars[iM_u_f], 2);
    real_type t57  = ALIAS_tfbound_D(ModelPars[iM_T_min] - t1);
    real_type t60  = t19 * t40;
    result__[ 2   ] = ModelPars[iM_w_time] + t50 + t51 + t54 - t57 + (-t13 * t8 - t60) * t10 + (t13 * (ModelPars[iM_Tf] - t16) + t60 - (t16 - ModelPars[iM_Tc]) * t46) * t23;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DHxpDxpuv_numRows() const { return 3; }
  integer ICLOCS_StirredTank::DHxpDxpuv_numCols() const { return 6; }
  integer ICLOCS_StirredTank::DHxpDxpuv_nnz()     const { return 11; }

  void
  ICLOCS_StirredTank::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
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
  }


  void
  ICLOCS_StirredTank::DHxpDxpuv_sparse(
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
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = 2 * t1;
    real_type t3   = X__[iX_x1];
    real_type t4   = ALIAS_x1bound_min_DD(-t3);
    real_type t6   = ALIAS_x1bound_max_DD(t3 - 1);
    result__[ 0   ] = t2 + t4 + t6;
    real_type t7   = MU__[0];
    real_type t9   = ModelPars[iM_k];
    real_type t10  = t9 * t1 * t7;
    real_type t11  = ModelPars[iM_En];
    real_type t12  = X__[iX_x2];
    real_type t13  = t12 * t12;
    real_type t18  = exp(-1.0 / t12 * t11);
    real_type t19  = t18 / t13 * t11;
    real_type t21  = MU__[1];
    real_type t22  = t1 * t21;
    result__[ 1   ] = t19 * t9 * t22 - t19 * t10;
    real_type t29  = 1.0 / ModelPars[iM_theta];
    result__[ 2   ] = 2 * t3 - 2 * ModelPars[iM_x1_f] + (-t18 * t9 - t29) * t7 + t18 * t9 * t21;
    result__[ 3   ] = result__[1];
    real_type t35  = ALIAS_x2bound_min_DD(-t12);
    real_type t37  = ALIAS_x2bound_max_DD(t12 - 1);
    real_type t40  = 1.0 / t13 / t12;
    real_type t45  = t11 * t11;
    real_type t47  = t13 * t13;
    real_type t48  = 1.0 / t47;
    real_type t52  = t3 * t9;
    result__[ 4   ] = t2 + t35 + t37 + 2 * t18 * t40 * t11 * t3 * t10 - t18 * t48 * t45 * t3 * t10 + (-2 * t18 * t40 * t11 * t52 + t18 * t48 * t45 * t52) * t22;
    real_type t69  = ModelPars[iM_a];
    real_type t70  = U__[iU_u];
    result__[ 5   ] = 2 * t12 - 2 * ModelPars[iM_x2_f] - t19 * t3 * t9 * t7 + (t19 * t52 - t70 * t69 - t29) * t21;
    result__[ 6   ] = -t69 * t22;
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[5];
    result__[ 9   ] = ALIAS_tfbound_DD(ModelPars[iM_T_min] - t1);
    result__[ 10  ] = 2 * t70 - 2 * ModelPars[iM_u_f] - (t12 - ModelPars[iM_Tc]) * t69 * t21;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 11, i_segment );
  }

}

// EOF: ICLOCS_StirredTank_Methods_AdjointODE.cc
