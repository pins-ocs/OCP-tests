/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_StirredTank_Methods_controls.cc                         |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ICLOCS_StirredTank::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t3   = X__[iX_x1];
    real_type t6   = pow(t3 - ModelPars[iM_x1_f], 2);
    real_type t7   = X__[iX_x2];
    real_type t10  = pow(t7 - ModelPars[iM_x2_f], 2);
    real_type t11  = U__[iU_u];
    real_type t14  = pow(t11 - ModelPars[iM_u_f], 2);
    real_type t17  = uControl(t11, 0, 2);
    real_type t20  = tfbound(ModelPars[iM_T_min] - t1);
    real_type t21  = x1bound_min(-t3);
    real_type t22  = t3 - 1;
    real_type t23  = x1bound_max(t22);
    real_type t24  = x2bound_min(-t7);
    real_type t26  = x2bound_max(t7 - 1);
    real_type t31  = 1.0 / ModelPars[iM_theta];
    real_type t38  = exp(-1.0 / t7 * ModelPars[iM_En]);
    real_type t39  = t38 * t3 * ModelPars[iM_k];
    real_type result__ = (ModelPars[iM_w_time] + t6 + t10 + t14) * t1 + t17 + t20 + t21 + t23 + t24 + t26 + (-t31 * t22 - t39) * t1 * MU__[0] + (t31 * (ModelPars[iM_Tf] - t7) + t39 - (t7 - ModelPars[iM_Tc]) * t11 * ModelPars[iM_a]) * t1 * MU__[1];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_StirredTank::g_numEqns() const { return 1; }

  void
  ICLOCS_StirredTank::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_TimeSize];
    real_type t2   = U__[iU_u];
    real_type t7   = ALIAS_uControl_D_1(t2, 0, 2);
    result__[ 0   ] = (2 * t2 - 2 * ModelPars[iM_u_f]) * t1 + t7 - ModelPars[iM_a] * (X__[iX_x2] - ModelPars[iM_Tc]) * t1 * MU__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DgDxpm_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DgDxpm_numCols() const { return 5; }
  integer ICLOCS_StirredTank::DgDxpm_nnz()     const { return 3; }

  void
  ICLOCS_StirredTank::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[1];
    real_type t2   = P__[iP_TimeSize];
    real_type t4   = ModelPars[iM_a];
    result__[ 0   ] = -t4 * t2 * t1;
    real_type t13  = X__[iX_x2] - ModelPars[iM_Tc];
    result__[ 1   ] = -t13 * t4 * t1 + 2 * U__[iU_u] - 2 * ModelPars[iM_u_f];
    result__[ 2   ] = -t13 * t4 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_StirredTank::DgDu_numRows() const { return 1; }
  integer ICLOCS_StirredTank::DgDu_numCols() const { return 1; }
  integer ICLOCS_StirredTank::DgDu_nnz()     const { return 1; }

  void
  ICLOCS_StirredTank::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_StirredTank::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t4   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 2);
    result__[ 0   ] = 2 * P__[iP_TimeSize] + t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 1, i_segment );
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
  ICLOCS_StirredTank::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "ICLOCS_StirredTank::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: ICLOCS_StirredTank_Methods_controls.cc
