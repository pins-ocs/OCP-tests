/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_ODE.cc                                 |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer ForwardBackward::ode_numEqns() const { return 1; }

  void
  ForwardBackward::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    result__[ 0   ] = 1.0 / t2 * U__[iU_a] - ModelPars[iM_c0] - t2 * ModelPars[iM_c1] - V__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DodeDxpuv_numRows() const { return 1; }
  integer ForwardBackward::DodeDxpuv_numCols() const { return 3; }
  integer ForwardBackward::DodeDxpuv_nnz()     const { return 3; }

  void
  ForwardBackward::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t3   = t2 * t2;
    result__[ 0   ] = -1.0 / t3 * U__[iU_a] - ModelPars[iM_c1];
    result__[ 1   ] = 1.0 / t2;
    result__[ 2   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 3, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::A_numRows() const { return 1; }
  integer ForwardBackward::A_numCols() const { return 1; }
  integer ForwardBackward::A_nnz()     const { return 1; }

  void
  ForwardBackward::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ForwardBackward::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 1, i_segment );
  }

}

// EOF: ForwardBackward_Methods_ODE.cc
