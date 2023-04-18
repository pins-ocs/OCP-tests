/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_ODE.cc                                |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer TwoPhaseSchwartz::ode_numEqns() const { return 4; }

  void
  TwoPhaseSchwartz::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x2];
    result__[ 0   ] = t1 - V__[0];
    real_type t5   = X__[iX_x1] * X__[iX_x1];
    result__[ 1   ] = U__[iU_u1] - 0.1e0 * t1 * (2 * t5 + 1) - V__[1];
    real_type t11  = ModelPars[iM_T2];
    real_type t12  = X__[iX_x4];
    result__[ 2   ] = t12 * t11 - V__[2];
    real_type t17  = X__[iX_x3] * X__[iX_x3];
    result__[ 3   ] = (U__[iU_u2] - 0.1e0 * t12 * (2 * t17 + 1)) * t11 - V__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DodeDxpuv_numRows() const { return 4; }
  integer TwoPhaseSchwartz::DodeDxpuv_numCols() const { return 10; }
  integer TwoPhaseSchwartz::DodeDxpuv_nnz()     const { return 12; }

  void
  TwoPhaseSchwartz::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 8   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 3   ;
    iIndex[10] = 3   ; jIndex[10] = 5   ;
    iIndex[11] = 3   ; jIndex[11] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    real_type t1   = X__[iX_x1];
    result__[ 2   ] = -0.4e0 * X__[iX_x2] * t1;
    real_type t5   = t1 * t1;
    result__[ 3   ] = -0.1e0 - 0.2e0 * t5;
    result__[ 4   ] = 1;
    result__[ 5   ] = -1;
    result__[ 6   ] = ModelPars[iM_T2];
    result__[ 7   ] = -1;
    real_type t7   = X__[iX_x3];
    result__[ 8   ] = -0.4e0 * X__[iX_x4] * t7 * result__[6];
    real_type t12  = t7 * t7;
    result__[ 9   ] = (-0.1e0 - 0.2e0 * t12) * result__[6];
    result__[ 10  ] = result__[6];
    result__[ 11  ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 12, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::A_numRows() const { return 4; }
  integer TwoPhaseSchwartz::A_numCols() const { return 4; }
  integer TwoPhaseSchwartz::A_nnz()     const { return 4; }

  void
  TwoPhaseSchwartz::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: TwoPhaseSchwartz_Methods_ODE.cc
