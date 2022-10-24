/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_AdjointODE.cc                       |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::Hxp_numEqns() const { return 3; }

  void
  ICLOCS_StirredTank::Hxp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = X__[iX_x1];
    real_type t4   = t2 - ModelPars[iM_x1_f];
    real_type t7   = L__[iL_lambda1__xo];
    real_type t8   = t1 * t7;
    real_type t10  = 1.0 / ModelPars[iM_theta];
    real_type t11  = ModelPars[iM_k];
    real_type t12  = ModelPars[iM_En];
    real_type t13  = X__[iX_x2];
    real_type t16  = exp(-1.0 / t13 * t12);
    real_type t17  = t16 * t11;
    real_type t20  = L__[iL_lambda2__xo];
    real_type t21  = t1 * t20;
    result__[ 0   ] = 2 * t4 * t1 + (-t10 - t17) * t8 + t17 * t21;
    real_type t24  = t13 - ModelPars[iM_x2_f];
    real_type t29  = t13 * t13;
    real_type t30  = 1.0 / t29;
    real_type t34  = t2 * t11;
    real_type t39  = U__[iU_u];
    real_type t40  = t39 * ModelPars[iM_a];
    result__[ 1   ] = 2 * t24 * t1 - t16 * t30 * t12 * t2 * t11 * t8 + (t16 * t30 * t12 * t34 - t10 - t40) * t21;
    real_type t44  = t4 * t4;
    real_type t45  = t24 * t24;
    real_type t48  = pow(t39 - ModelPars[iM_u_f], 2);
    real_type t51  = t16 * t34;
    result__[ 2   ] = ModelPars[iM_w_time] + t44 + t45 + t48 + (t10 * (1 - t2) - t51) * t7 + (t10 * (ModelPars[iM_Tf] - t13) + t51 - (t13 - ModelPars[iM_Tc]) * t40) * t20;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DHxpDxpu_numRows() const { return 3; }
  integer ICLOCS_StirredTank::DHxpDxpu_numCols() const { return 4; }
  integer ICLOCS_StirredTank::DHxpDxpu_nnz()     const { return 10; }

  void
  ICLOCS_StirredTank::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 1   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
  }


  void
  ICLOCS_StirredTank::DHxpDxpu_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    result__[ 0   ] = 2 * t1;
    real_type t2   = L__[iL_lambda1__xo];
    real_type t4   = ModelPars[iM_k];
    real_type t5   = t4 * t2 * t1;
    real_type t6   = ModelPars[iM_En];
    real_type t7   = X__[iX_x2];
    real_type t8   = t7 * t7;
    real_type t13  = exp(-1.0 / t7 * t6);
    real_type t14  = t13 / t8 * t6;
    real_type t16  = L__[iL_lambda2__xo];
    real_type t17  = t1 * t16;
    result__[ 1   ] = t14 * t4 * t17 - t14 * t5;
    real_type t20  = X__[iX_x1];
    real_type t25  = 1.0 / ModelPars[iM_theta];
    result__[ 2   ] = 2 * t20 - 2 * ModelPars[iM_x1_f] + (-t13 * t4 - t25) * t2 + t13 * t4 * t16;
    result__[ 3   ] = result__[1];
    real_type t33  = 1.0 / t8 / t7;
    real_type t38  = t6 * t6;
    real_type t40  = t8 * t8;
    real_type t41  = 1.0 / t40;
    real_type t45  = t20 * t4;
    result__[ 4   ] = result__[0] + 2 * t13 * t33 * t6 * t20 * t5 - t13 * t41 * t38 * t20 * t5 + (-2 * t13 * t33 * t6 * t45 + t13 * t41 * t38 * t45) * t17;
    real_type t62  = ModelPars[iM_a];
    real_type t63  = U__[iU_u];
    result__[ 5   ] = 2 * t7 - 2 * ModelPars[iM_x2_f] - t14 * t20 * t4 * t2 + (t14 * t45 - t63 * t62 - t25) * t16;
    result__[ 6   ] = -t62 * t17;
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[5];
    result__[ 9   ] = 2 * t63 - 2 * ModelPars[iM_u_f] - (t7 - ModelPars[iM_Tc]) * t62 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 10, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::Hu_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    result__[ 0   ] = (2 * U__[iU_u] - 2 * ModelPars[iM_u_f]) * t1 - ModelPars[iM_a] * (X__[iX_x2] - ModelPars[iM_Tc]) * t1 * L__[iL_lambda2__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

}

// EOF: ICLOCS_StirredTank_Methods_AdjointODE.cc
