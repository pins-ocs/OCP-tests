/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_controls.cc                            |
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


#include "ForwardBackward.hh"
#include "ForwardBackward_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::Path2D;


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
#define ALIAS_theta_DD(__t1) pTrajectory -> heading_DD( __t1)
#define ALIAS_theta_D(__t1) pTrajectory -> heading_D( __t1)
#define ALIAS_theta(__t1) pTrajectory -> heading( __t1)
#define ALIAS_yLane_DD(__t1) pTrajectory -> y_trajectory_DD( __t1)
#define ALIAS_yLane_D(__t1) pTrajectory -> y_trajectory_D( __t1)
#define ALIAS_yLane(__t1) pTrajectory -> y_trajectory( __t1)
#define ALIAS_xLane_DD(__t1) pTrajectory -> x_trajectory_DD( __t1)
#define ALIAS_xLane_D(__t1) pTrajectory -> x_trajectory_D( __t1)
#define ALIAS_xLane(__t1) pTrajectory -> x_trajectory( __t1)
#define ALIAS_kappa_DD(__t1) pTrajectory -> curvature_DD( __t1)
#define ALIAS_kappa_D(__t1) pTrajectory -> curvature_D( __t1)
#define ALIAS_kappa(__t1) pTrajectory -> curvature( __t1)
#define ALIAS_LimitE_DD(__t1) LimitE.DD( __t1)
#define ALIAS_LimitE_D(__t1) LimitE.D( __t1)
#define ALIAS_LimitA_max_DD(__t1) LimitA_max.DD( __t1)
#define ALIAS_LimitA_max_D(__t1) LimitA_max.D( __t1)
#define ALIAS_LimitA_min_DD(__t1) LimitA_min.DD( __t1)
#define ALIAS_LimitA_min_D(__t1) LimitA_min.D( __t1)
#define ALIAS_LimitV_max_DD(__t1) LimitV_max.DD( __t1)
#define ALIAS_LimitV_max_D(__t1) LimitV_max.D( __t1)
#define ALIAS_LimitV_min_DD(__t1) LimitV_min.DD( __t1)
#define ALIAS_LimitV_min_D(__t1) LimitV_min.D( __t1)


namespace ForwardBackwardDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ForwardBackward::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t3   = 1.0 / t2;
    real_type t6   = U__[iU_a];
    real_type t7   = t6 * t6;
    real_type t11  = LimitV_min(ModelPars[iM_v_min] - t2);
    real_type t14  = LimitV_max(t2 - ModelPars[iM_v_max]);
    real_type t17  = LimitA_min(ModelPars[iM_a_min] - t6);
    real_type t20  = LimitA_max(t6 - ModelPars[iM_a_max]);
    real_type t24  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t25  = t24 * t24;
    real_type t26  = t2 * t2;
    real_type t27  = t26 * t26;
    real_type t31  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t35  = LimitE(1.0 / t31 * (t27 * t25 + t7 * ModelPars[iM_WA]) - 1);
    real_type result__ = t3 * ModelPars[iM_wT] + t7 * ModelPars[iM_epsilon] + t11 + t14 + t17 + t20 + t35 + (-t2 * ModelPars[iM_c1] + t3 * t6 - ModelPars[iM_c0]) * MU__[0];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::g_numEqns() const { return 1; }

  void
  ForwardBackward::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_a];
    real_type t7   = ALIAS_LimitA_min_D(ModelPars[iM_a_min] - t2);
    real_type t10  = ALIAS_LimitA_max_D(t2 - ModelPars[iM_a_max]);
    real_type t11  = ModelPars[iM_WA];
    real_type t12  = t2 * t2;
    real_type t15  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t16  = t15 * t15;
    real_type t17  = X__[iX_v];
    real_type t18  = t17 * t17;
    real_type t19  = t18 * t18;
    real_type t23  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t24  = 1.0 / t23;
    real_type t27  = ALIAS_LimitE_D(t24 * (t11 * t12 + t16 * t19) - 1);
    result__[ 0   ] = 2 * t2 * ModelPars[iM_epsilon] - t7 + t10 + 2 * t24 * t2 * t11 * t27 + 1.0 / t17 * MU__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DgDxpm_numRows() const { return 1; }
  integer ForwardBackward::DgDxpm_numCols() const { return 2; }
  integer ForwardBackward::DgDxpm_nnz()     const { return 2; }

  void
  ForwardBackward::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WA];
    real_type t2   = U__[iU_a];
    real_type t3   = t2 * t2;
    real_type t6   = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t7   = t6 * t6;
    real_type t8   = X__[iX_v];
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t9;
    real_type t14  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t18  = ALIAS_LimitE_DD(1.0 / t14 * (t3 * t1 + t10 * t7) - 1);
    real_type t21  = t14 * t14;
    result__[ 0   ] = 8 * t9 * t8 * t7 / t21 * t2 * t1 * t18 - 1.0 / t9 * MU__[0];
    result__[ 1   ] = 1.0 / t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DgDu_numRows() const { return 1; }
  integer ForwardBackward::DgDu_numCols() const { return 1; }
  integer ForwardBackward::DgDu_nnz()     const { return 1; }

  void
  ForwardBackward::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t4   = U__[iU_a];
    real_type t6   = ALIAS_LimitA_min_DD(ModelPars[iM_a_min] - t4);
    real_type t9   = ALIAS_LimitA_max_DD(t4 - ModelPars[iM_a_max]);
    real_type t10  = ModelPars[iM_WA];
    real_type t11  = t4 * t4;
    real_type t14  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t15  = t14 * t14;
    real_type t17  = X__[iX_v] * X__[iX_v];
    real_type t18  = t17 * t17;
    real_type t22  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t23  = 1.0 / t22;
    real_type t25  = t23 * (t11 * t10 + t18 * t15) - 1;
    real_type t26  = ALIAS_LimitE_DD(t25);
    real_type t27  = t10 * t10;
    real_type t29  = t22 * t22;
    real_type t34  = ALIAS_LimitE_D(t25);
    result__[ 0   ] = 2 * ModelPars[iM_epsilon] + t6 + t9 + 4 / t29 * t11 * t27 * t26 + 2 * t23 * t10 * t34;
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
  ForwardBackward::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "ForwardBackward::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: ForwardBackward_Methods_controls.cc
