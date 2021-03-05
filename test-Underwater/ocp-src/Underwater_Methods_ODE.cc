/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_ODE.cc                                      |
 |                                                                       |
 |  version: 1.0   date 6/3/2021                                         |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#endif

// map user defined functions and objects with macros
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace UnderwaterDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  Underwater::rhs_ode_numEqns() const
  { return 6; }

  void
  Underwater::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vx];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vz];
    real_type t7   = sin(t3);
    result__[ 0   ] = (t4 * t2 + t7 * t6) * t1;
    result__[ 1   ] = (-t7 * t2 + t4 * t6) * t1;
    real_type t13  = X__[iX_Omega];
    result__[ 2   ] = t13 * t1;
    real_type t15  = ModelPars[iM_m1];
    real_type t16  = 1.0 / t15;
    real_type t19  = ModelPars[iM_m3];
    result__[ 3   ] = (-t16 * t19 * t13 * t6 + t16 * U__[iU_u1]) * t1;
    real_type t24  = 1.0 / t19;
    result__[ 4   ] = (t24 * t15 * t13 * t2 + t24 * U__[iU_u2]) * t1;
    real_type t32  = 1.0 / ModelPars[iM_inertia];
    result__[ 5   ] = (t32 * U__[iU_u3] + t32 * (t19 - t15) * t6 * t2) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::Drhs_odeDx_numRows() const
  { return 6; }

  integer
  Underwater::Drhs_odeDx_numCols() const
  { return 6; }

  integer
  Underwater::Drhs_odeDx_nnz() const
  { return 13; }

  void
  Underwater::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 3   ;
    iIndex[10] = 4   ; jIndex[10] = 5   ;
    iIndex[11] = 5   ; jIndex[11] = 3   ;
    iIndex[12] = 5   ; jIndex[12] = 4   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vz];
    real_type t3   = X__[iX_theta];
    real_type t4   = cos(t3);
    real_type t6   = X__[iX_vx];
    real_type t7   = sin(t3);
    result__[ 0   ] = (t4 * t2 - t7 * t6) * t1;
    result__[ 1   ] = t4 * t1;
    result__[ 2   ] = t7 * t1;
    result__[ 3   ] = (-t7 * t2 - t6 * t4) * t1;
    result__[ 4   ] = -result__[2];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = t1;
    real_type t14  = X__[iX_Omega] * result__[6];
    real_type t15  = ModelPars[iM_m3];
    real_type t16  = ModelPars[iM_m1];
    real_type t18  = 1.0 / t16 * t15;
    result__[ 7   ] = -t18 * t14;
    real_type t20  = t2 * result__[6];
    result__[ 8   ] = -t18 * t20;
    real_type t23  = 1.0 / t15 * t16;
    result__[ 9   ] = t23 * t14;
    real_type t24  = t6 * result__[6];
    result__[ 10  ] = t23 * t24;
    real_type t28  = 1.0 / ModelPars[iM_inertia] * (t15 - t16);
    result__[ 11  ] = t28 * t20;
    result__[ 12  ] = t28 * t24;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 13, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::Drhs_odeDp_numRows() const
  { return 6; }

  integer
  Underwater::Drhs_odeDp_numCols() const
  { return 1; }

  integer
  Underwater::Drhs_odeDp_nnz() const
  { return 6; }

  void
  Underwater::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_vx];
    real_type t2   = X__[iX_theta];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_vz];
    real_type t6   = sin(t2);
    result__[ 0   ] = t3 * t1 + t6 * t5;
    result__[ 1   ] = -t6 * t1 + t3 * t5;
    result__[ 2   ] = X__[iX_Omega];
    real_type t11  = ModelPars[iM_m1];
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_m3];
    result__[ 3   ] = -t12 * t15 * result__[2] * t5 + t12 * U__[iU_u1];
    real_type t19  = 1.0 / t15;
    result__[ 4   ] = t19 * t11 * result__[2] * t1 + t19 * U__[iU_u2];
    real_type t26  = 1.0 / ModelPars[iM_inertia];
    result__[ 5   ] = t26 * U__[iU_u3] + t26 * (t15 - t11) * t5 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::Drhs_odeDu_numRows() const
  { return 6; }

  integer
  Underwater::Drhs_odeDu_numCols() const
  { return 3; }

  integer
  Underwater::Drhs_odeDu_nnz() const
  { return 3; }

  void
  Underwater::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 3   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 5   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    result__[ 0   ] = 1.0 / ModelPars[iM_m1] * t1;
    result__[ 1   ] = 1.0 / ModelPars[iM_m3] * t1;
    result__[ 2   ] = 1.0 / ModelPars[iM_inertia] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDu_sparse", 3, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  Underwater::A_numRows() const
  { return 6; }

  integer
  Underwater::A_numCols() const
  { return 6; }

  integer
  Underwater::A_nnz() const
  { return 6; }

  void
  Underwater::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 6, i_segment );
  }

}

// EOF: Underwater_Methods_ODE.cc
