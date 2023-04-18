/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_AdjointODE.cc                         |
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


#include "TwoPhaseSchwartz.hh"
#include "TwoPhaseSchwartz_Pars.hh"

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
#define ALIAS_bound2_DD(__t1) bound2.DD( __t1)
#define ALIAS_bound2_D(__t1) bound2.D( __t1)
#define ALIAS_bound1_DD(__t1) bound1.DD( __t1)
#define ALIAS_bound1_D(__t1) bound1.D( __t1)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoPhaseSchwartzDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::Hxp_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::Hxp_eval(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = t1 - 1;
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    real_type t10  = ALIAS_bound1_D(1 - 9 * t3 - t8);
    real_type t14  = MU__[1];
    result__[ 0   ] = -18 * t2 * t10 - 0.4e0 * t5 * t1 * t14;
    real_type t22  = ALIAS_bound2_D(-0.8e0 - t5);
    real_type t24  = t1 * t1;
    result__[ 1   ] = (-0.2222222222e2 * t5 + 0.8888888886e1) * t10 - t22 + MU__[0] + (-0.1e0 - 0.2e0 * t24) * t14;
    real_type t29  = ModelPars[iM_T2];
    real_type t30  = t29 * MU__[3];
    real_type t31  = X__[iX_x3];
    result__[ 2   ] = -0.4e0 * X__[iX_x4] * t31 * t30;
    real_type t38  = t31 * t31;
    result__[ 3   ] = t29 * MU__[2] + (-0.1e0 - 0.2e0 * t38) * t30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DHxpDxpuv_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DHxpDxpuv_numCols() const { return 10; }
  integer TwoPhaseSchwartz::DHxpDxpuv_nnz()     const { return 7; }

  void
  TwoPhaseSchwartz::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 2   ;
  }


  void
  TwoPhaseSchwartz::DHxpDxpuv_sparse(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = t1 - 1;
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x2];
    real_type t8   = pow(0.3333333333e1 * t5 - 0.1333333333e1, 2);
    real_type t9   = 1 - 9 * t3 - t8;
    real_type t10  = ALIAS_bound1_DD(t9);
    real_type t12  = -18 * t2;
    real_type t13  = t12 * t12;
    real_type t15  = ALIAS_bound1_D(t9);
    real_type t17  = MU__[1];
    result__[ 0   ] = t13 * t10 - 18 * t15 - 0.4e0 * t5 * t17;
    real_type t21  = -0.2222222222e2 * t5 + 0.8888888886e1;
    result__[ 1   ] = t12 * t21 * t10 - 0.4e0 * t1 * t17;
    result__[ 2   ] = result__[1];
    real_type t26  = t21 * t21;
    real_type t30  = ALIAS_bound2_DD(-0.8e0 - t5);
    result__[ 3   ] = t26 * t10 - 0.2222222222e2 * t15 + t30;
    real_type t33  = ModelPars[iM_T2] * MU__[3];
    result__[ 4   ] = -0.4e0 * X__[iX_x4] * t33;
    result__[ 5   ] = -0.4e0 * X__[iX_x3] * t33;
    result__[ 6   ] = result__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 7, i_segment );
  }

}

// EOF: TwoPhaseSchwartz_Methods_AdjointODE.cc
