/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_ODE.cc                          |
 |                                                                       |
 |  version: 1.0   date 3/4/2022                                         |
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


#include "ICLOCS_TwoLinkRobotArm.hh"
#include "ICLOCS_TwoLinkRobotArm_Pars.hh"

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


namespace ICLOCS_TwoLinkRobotArmDefine {

  /*\
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer ICLOCS_TwoLinkRobotArm::rhs_ode_numEqns() const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_theta];
    real_type t3   = sin(t2);
    real_type t4   = cos(t2);
    real_type t5   = t4 * t3;
    real_type t6   = X__[iX_omega__alpha];
    real_type t7   = t6 * t6;
    real_type t10  = X__[iX_omega__beta];
    real_type t11  = t10 * t10;
    real_type t13  = U__[iU_u1];
    real_type t15  = U__[iU_u2];
    real_type t21  = t3 * t3;
    real_type t24  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t21);
    result__[ 0   ] = t24 * (9.0 / 4.0 * t7 * t5 + 2 * t11 + 4.0 / 3.0 * t13 - 4.0 / 3.0 * t15 - 3.0 / 2.0 * t15 * t4) * t1;
    result__[ 1   ] = -t24 * (9.0 / 4.0 * t11 * t5 + 7.0 / 2.0 * t7 - 7.0 / 3.0 * t15 + 3.0 / 2.0 * (t13 - t15) * t4) * t1;
    result__[ 2   ] = (t10 - t6) * t1;
    result__[ 3   ] = t6 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::Drhs_odeDxup_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::Drhs_odeDxup_numCols() const { return 7; }
  integer ICLOCS_TwoLinkRobotArm::Drhs_odeDxup_nnz()     const { return 17; }

  void
  ICLOCS_TwoLinkRobotArm::Drhs_odeDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 6   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 4   ;
    iIndex[10] = 1   ; jIndex[10] = 5   ;
    iIndex[11] = 1   ; jIndex[11] = 6   ;
    iIndex[12] = 2   ; jIndex[12] = 0   ;
    iIndex[13] = 2   ; jIndex[13] = 1   ;
    iIndex[14] = 2   ; jIndex[14] = 6   ;
    iIndex[15] = 3   ; jIndex[15] = 0   ;
    iIndex[16] = 3   ; jIndex[16] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::Drhs_odeDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_theta];
    real_type t3   = sin(t2);
    real_type t4   = t3 * t1;
    real_type t5   = cos(t2);
    real_type t6   = X__[iX_omega__alpha];
    real_type t8   = t3 * t3;
    real_type t10  = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t8;
    real_type t11  = 1.0 / t10;
    result__[ 0   ] = 9.0 / 2.0 * t11 * t6 * t5 * t4;
    real_type t14  = X__[iX_omega__beta];
    result__[ 1   ] = 4 * t11 * t14 * t1;
    real_type t17  = t5 * t5;
    real_type t18  = t6 * t6;
    real_type t23  = U__[iU_u2];
    real_type t29  = t5 * t3;
    real_type t32  = t14 * t14;
    real_type t34  = U__[iU_u1];
    real_type t39  = 9.0 / 4.0 * t18 * t29 + 2 * t32 + 4.0 / 3.0 * t34 - 4.0 / 3.0 * t23 - 3.0 / 2.0 * t23 * t5;
    real_type t41  = t10 * t10;
    real_type t44  = t5 * t3 / t41;
    result__[ 2   ] = t11 * (9.0 / 4.0 * t18 * t17 - 9.0 / 4.0 * t18 * t8 + 3.0 / 2.0 * t23 * t3) * t1 - 9.0 / 2.0 * t44 * t39 * t1;
    result__[ 3   ] = 4.0 / 3.0 * t11 * t1;
    real_type t48  = 3.0 / 2.0 * t5;
    result__[ 4   ] = t11 * (-4.0 / 3.0 - t48) * t1;
    result__[ 5   ] = t11 * t39;
    result__[ 6   ] = -7 * t11 * t6 * t1;
    result__[ 7   ] = -9.0 / 2.0 * t11 * t14 * t5 * t4;
    real_type t62  = t34 - t23;
    real_type t74  = 9.0 / 4.0 * t32 * t29 + 7.0 / 2.0 * t18 - 7.0 / 3.0 * t23 + 3.0 / 2.0 * t62 * t5;
    result__[ 8   ] = -t11 * (9.0 / 4.0 * t32 * t17 - 9.0 / 4.0 * t32 * t8 - 3.0 / 2.0 * t62 * t3) * t1 + 9.0 / 2.0 * t44 * t74 * t1;
    result__[ 9   ] = -3.0 / 2.0 * t11 * t5 * t1;
    result__[ 10  ] = -t11 * (-7.0 / 3.0 - t48) * t1;
    result__[ 11  ] = -t11 * t74;
    result__[ 12  ] = -t1;
    result__[ 13  ] = t1;
    result__[ 14  ] = t14 - t6;
    result__[ 15  ] = result__[13];
    result__[ 16  ] = t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxup_sparse", 17, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::A_numRows() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::A_numCols() const { return 4; }
  integer ICLOCS_TwoLinkRobotArm::A_nnz()     const { return 4; }

  void
  ICLOCS_TwoLinkRobotArm::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
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

// EOF: ICLOCS_TwoLinkRobotArm_Methods_ODE.cc
