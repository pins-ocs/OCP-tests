/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_AdjointODE.cc                          |
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
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::Hxp_numEqns() const { return 1; }

  void
  ForwardBackward::Hxp_eval(
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
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t3   = t2 * t2;
    real_type t4   = 1.0 / t3;
    real_type t8   = ALIAS_LimitV_min_D(ModelPars[iM_v_min] - t2);
    real_type t11  = ALIAS_LimitV_max_D(t2 - ModelPars[iM_v_max]);
    real_type t13  = U__[iU_a];
    real_type t14  = t13 * t13;
    real_type t17  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t18  = t17 * t17;
    real_type t19  = t3 * t3;
    real_type t23  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t24  = 1.0 / t23;
    real_type t27  = ALIAS_LimitE_D(t24 * (t14 * ModelPars[iM_WA] + t19 * t18) - 1);
    result__[ 0   ] = -t4 * ModelPars[iM_wT] - t8 + t11 + 4 * t24 * t3 * t2 * t18 * t27 + (-t4 * t13 - ModelPars[iM_c1]) * MU__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DHxpDxpuv_numRows() const { return 1; }
  integer ForwardBackward::DHxpDxpuv_numCols() const { return 3; }
  integer ForwardBackward::DHxpDxpuv_nnz()     const { return 2; }

  void
  ForwardBackward::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }


  void
  ForwardBackward::DHxpDxpuv_sparse(
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
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t3   = t2 * t2;
    real_type t4   = t3 * t2;
    real_type t5   = 1.0 / t4;
    real_type t10  = ALIAS_LimitV_min_DD(ModelPars[iM_v_min] - t2);
    real_type t13  = ALIAS_LimitV_max_DD(t2 - ModelPars[iM_v_max]);
    real_type t14  = ModelPars[iM_WA];
    real_type t15  = U__[iU_a];
    real_type t16  = t15 * t15;
    real_type t19  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t20  = t19 * t19;
    real_type t21  = t3 * t3;
    real_type t25  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t26  = 1.0 / t25;
    real_type t28  = t26 * (t16 * t14 + t21 * t20) - 1;
    real_type t29  = ALIAS_LimitE_DD(t28);
    real_type t30  = t20 * t20;
    real_type t33  = t25 * t25;
    real_type t34  = 1.0 / t33;
    real_type t38  = ALIAS_LimitE_D(t28);
    real_type t43  = MU__[0];
    result__[ 0   ] = 16 * t34 * t21 * t3 * t30 * t29 + 12 * t26 * t3 * t20 * t38 + 2 * t5 * t15 * t43 + 2 * t5 * ModelPars[iM_wT] + t10 + t13;
    result__[ 1   ] = 8 * t4 * t20 * t34 * t15 * t14 * t29 - 1.0 / t3 * t43;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 2, i_segment );
  }

}

// EOF: ForwardBackward_Methods_AdjointODE.cc
