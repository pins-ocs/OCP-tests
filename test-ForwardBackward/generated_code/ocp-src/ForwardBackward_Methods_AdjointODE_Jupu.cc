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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ForwardBackward::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ForwardBackward::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  ForwardBackward::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t4   = LimitV_min(ModelPars[iM_v_min] - t2);
    real_type t7   = LimitV_max(t2 - ModelPars[iM_v_max]);
    real_type t9   = U__[iU_a];
    real_type t11  = LimitA_min(ModelPars[iM_a_min] - t9);
    real_type t14  = LimitA_max(t9 - ModelPars[iM_a_max]);
    real_type t16  = t9 * t9;
    real_type t19  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t20  = t19 * t19;
    real_type t21  = t2 * t2;
    real_type t22  = t21 * t21;
    real_type t26  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t30  = LimitE(1.0 / t26 * (t16 * ModelPars[iM_WA] + t22 * t20) - 1);
    real_type result__ = t4 + t7 + t11 + t14 + t30;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::JPxpu_numEqns() const { return 2; }

  void
  ForwardBackward::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::JUxpu_numEqns() const { return 2; }

  void
  ForwardBackward::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::LTxpu_numEqns() const { return 2; }

  void
  ForwardBackward::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t4   = ALIAS_LimitV_min_D(ModelPars[iM_v_min] - t2);
    real_type t7   = ALIAS_LimitV_max_D(t2 - ModelPars[iM_v_max]);
    real_type t8   = ModelPars[iM_WA];
    real_type t9   = U__[iU_a];
    real_type t10  = t9 * t9;
    real_type t13  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t14  = t13 * t13;
    real_type t15  = t2 * t2;
    real_type t16  = t15 * t15;
    real_type t20  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t21  = 1.0 / t20;
    real_type t24  = ALIAS_LimitE_D(t21 * (t10 * t8 + t16 * t14) - 1);
    result__[ 0   ] = 4 * t21 * t15 * t2 * t14 * t24 - t4 + t7;
    real_type t32  = ALIAS_LimitA_min_D(ModelPars[iM_a_min] - t9);
    real_type t35  = ALIAS_LimitA_max_D(t9 - ModelPars[iM_a_max]);
    result__[ 1   ] = 2 * t21 * t9 * t8 * t24 - t32 + t35;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::LTargs_numEqns() const { return 5; }

  void
  ForwardBackward::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    result__[ 0   ] = ModelPars[iM_v_min] - t2;
    result__[ 1   ] = t2 - ModelPars[iM_v_max];
    real_type t5   = U__[iU_a];
    result__[ 2   ] = ModelPars[iM_a_min] - t5;
    result__[ 3   ] = t5 - ModelPars[iM_a_max];
    real_type t8   = t5 * t5;
    real_type t11  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t12  = t11 * t11;
    real_type t13  = t2 * t2;
    real_type t14  = t13 * t13;
    real_type t18  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    result__[ 4   ] = 1.0 / t18 * (t14 * t12 + t8 * ModelPars[iM_WA]) - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2JPD2xpu_numRows() const { return 2; }
  integer ForwardBackward::D2JPD2xpu_numCols() const { return 2; }
  integer ForwardBackward::D2JPD2xpu_nnz()     const { return 0; }

  void
  ForwardBackward::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2LTD2xpu_numRows() const { return 2; }
  integer ForwardBackward::D2LTD2xpu_numCols() const { return 2; }
  integer ForwardBackward::D2LTD2xpu_nnz()     const { return 4; }

  void
  ForwardBackward::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  ForwardBackward::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t4   = ALIAS_LimitV_min_DD(ModelPars[iM_v_min] - t2);
    real_type t7   = ALIAS_LimitV_max_DD(t2 - ModelPars[iM_v_max]);
    real_type t8   = ModelPars[iM_WA];
    real_type t9   = U__[iU_a];
    real_type t10  = t9 * t9;
    real_type t13  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t14  = t13 * t13;
    real_type t15  = t2 * t2;
    real_type t16  = t15 * t15;
    real_type t20  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t21  = 1.0 / t20;
    real_type t23  = t21 * (t10 * t8 + t16 * t14) - 1;
    real_type t24  = ALIAS_LimitE_DD(t23);
    real_type t25  = t14 * t14;
    real_type t28  = t20 * t20;
    real_type t29  = 1.0 / t28;
    real_type t33  = ALIAS_LimitE_D(t23);
    result__[ 0   ] = 16 * t29 * t16 * t15 * t25 * t24 + 12 * t21 * t15 * t14 * t33 + t4 + t7;
    result__[ 1   ] = 8 * t15 * t2 * t14 * t29 * t9 * t8 * t24;
    result__[ 2   ] = result__[1];
    real_type t46  = ALIAS_LimitA_min_DD(ModelPars[iM_a_min] - t9);
    real_type t49  = ALIAS_LimitA_max_DD(t9 - ModelPars[iM_a_max]);
    real_type t50  = t8 * t8;
    result__[ 3   ] = 4 * t29 * t10 * t50 * t24 + 2 * t21 * t8 * t33 + t46 + t49;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2JUD2xpu_numRows() const { return 2; }
  integer ForwardBackward::D2JUD2xpu_numCols() const { return 2; }
  integer ForwardBackward::D2JUD2xpu_nnz()     const { return 0; }

  void
  ForwardBackward::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DLTargsDxpu_numRows() const { return 5; }
  integer ForwardBackward::DLTargsDxpu_numCols() const { return 2; }
  integer ForwardBackward::DLTargsDxpu_nnz()     const { return 6; }

  void
  ForwardBackward::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 1   ;
  }


  void
  ForwardBackward::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    real_type t2   = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t3   = t2 * t2;
    real_type t4   = X__[iX_v];
    real_type t5   = t4 * t4;
    real_type t9   = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t10  = 1.0 / t9;
    result__[ 4   ] = 4 * t10 * t5 * t4 * t3;
    result__[ 5   ] = 2 * t10 * U__[iU_a] * ModelPars[iM_WA];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 6, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2LTargsD2xpu_numRows() const { return 2; }
  integer ForwardBackward::D2LTargsD2xpu_numCols() const { return 2; }
  integer ForwardBackward::D2LTargsD2xpu_nnz()     const { return 2; }

  void
  ForwardBackward::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  ForwardBackward::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_v] * X__[iX_v];
    real_type t8   = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t9   = 1.0 / t8;
    real_type t10  = OMEGA__[4];
    result__[ 0   ] = 12 * t10 * t9 * t5 * t3;
    result__[ 1   ] = 2 * t10 * t9 * ModelPars[iM_WA];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTargsD2xpu_sparse", 2, i_segment );
  }

}

// EOF: ForwardBackward_Methods_AdjointODE.cc
