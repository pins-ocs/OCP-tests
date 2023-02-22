/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_TwoLinkRobotArm_Methods_controls.cc                     |
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
#pragma warning( disable : 4189 )
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ICLOCS_TwoLinkRobotArm::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t4   = U__[iU_u1];
    real_type t5   = t4 * t4;
    real_type t6   = U__[iU_u2];
    real_type t7   = t6 * t6;
    real_type t10  = u1Control(t4, -1, 1);
    real_type t12  = u2Control(t6, -1, 1);
    real_type t16  = X__[iX_theta];
    real_type t17  = sin(t16);
    real_type t18  = cos(t16);
    real_type t19  = t18 * t17;
    real_type t20  = X__[iX_omega__alpha];
    real_type t21  = t20 * t20;
    real_type t24  = X__[iX_omega__beta];
    real_type t25  = t24 * t24;
    real_type t32  = t17 * t17;
    real_type t35  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t32);
    real_type result__ = (t5 + t7) * t2 * ModelPars[iM_rho] + t10 * t2 + t12 * t2 + t35 * (9.0 / 4.0 * t21 * t19 + 2 * t25 + 4.0 / 3.0 * t4 - 4.0 / 3.0 * t6 - 3.0 / 2.0 * t6 * t18) * t2 * MU__[0] - t35 * (9.0 / 4.0 * t25 * t19 + 7.0 / 2.0 * t21 - 7.0 / 3.0 * t6 + 3.0 / 2.0 * (t4 - t6) * t18) * t2 * MU__[1] + (t24 - t20) * t2 * MU__[2] + t20 * t2 * MU__[3];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_TwoLinkRobotArm::g_numEqns() const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * ModelPars[iM_rho];
    real_type t4   = U__[iU_u1];
    real_type t7   = ALIAS_u1Control_D_1(t4, -1, 1);
    real_type t10  = t2 * MU__[0];
    real_type t11  = X__[iX_theta];
    real_type t12  = sin(t11);
    real_type t13  = t12 * t12;
    real_type t16  = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t13);
    real_type t20  = t2 * MU__[1];
    real_type t21  = cos(t11);
    result__[ 0   ] = 2 * t4 * t3 + t7 * t2 + 4.0 / 3.0 * t16 * t10 - 3.0 / 2.0 * t16 * t21 * t20;
    real_type t25  = U__[iU_u2];
    real_type t28  = ALIAS_u2Control_D_1(t25, -1, 1);
    real_type t30  = 3.0 / 2.0 * t21;
    result__[ 1   ] = 2 * t25 * t3 + t28 * t2 + t16 * (-4.0 / 3.0 - t30) * t10 - t16 * (-7.0 / 3.0 - t30) * t20;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DgDxpm_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DgDxpm_numCols() const { return 9; }
  integer ICLOCS_TwoLinkRobotArm::DgDxpm_nnz()     const { return 8; }

  void
  ICLOCS_TwoLinkRobotArm::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_theta];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t8   = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t6;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = cos(t4);
    real_type t13  = t12 * t5 * t10;
    real_type t16  = MU__[1];
    real_type t17  = t2 * t16;
    real_type t18  = 1.0 / t8;
    real_type t19  = t18 * t5;
    real_type t21  = 3.0 / 2.0 * t19 * t17;
    real_type t22  = t12 * t12;
    result__[ 0   ] = -6 * t13 * t3 + t21 + 0.27e2 / 4.0 * t5 * t10 * t22 * t17;
    real_type t27  = ModelPars[iM_rho];
    real_type t28  = U__[iU_u1];
    real_type t31  = ALIAS_u1Control_D_1(t28, -1, 1);
    result__[ 1   ] = 2 * t28 * t27 + t31 + 4.0 / 3.0 * t18 * t1 - 3.0 / 2.0 * t18 * t12 * t16;
    result__[ 2   ] = 4.0 / 3.0 * t18 * t2;
    result__[ 3   ] = -3.0 / 2.0 * t18 * t12 * t2;
    real_type t43  = 3.0 / 2.0 * t12;
    real_type t44  = -4.0 / 3.0 - t43;
    real_type t48  = -7.0 / 3.0 - t43;
    result__[ 4   ] = 3.0 / 2.0 * t19 * t3 - 9.0 / 2.0 * t13 * t44 * t3 - t21 + 9.0 / 2.0 * t13 * t48 * t17;
    real_type t52  = U__[iU_u2];
    real_type t55  = ALIAS_u2Control_D_1(t52, -1, 1);
    result__[ 5   ] = t18 * t44 * t1 - t18 * t48 * t16 + 2 * t52 * t27 + t55;
    result__[ 6   ] = t18 * t44 * t2;
    result__[ 7   ] = -t18 * t48 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_TwoLinkRobotArm::DgDu_numRows() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DgDu_numCols() const { return 2; }
  integer ICLOCS_TwoLinkRobotArm::DgDu_nnz()     const { return 2; }

  void
  ICLOCS_TwoLinkRobotArm::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_TwoLinkRobotArm::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t4   = 2 * t2 * ModelPars[iM_rho];
    real_type t6   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    result__[ 0   ] = t6 * t2 + t4;
    real_type t9   = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    result__[ 1   ] = t9 * t2 + t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  ICLOCS_TwoLinkRobotArm::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "ICLOCS_TwoLinkRobotArm::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: ICLOCS_TwoLinkRobotArm_Methods_controls.cc
