/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_AdjointODE.cc                          |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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

  integer ForwardBackward::JP_numEqns() const { return 0; }

  void
  ForwardBackward::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::LT_numEqns() const { return 5; }

  void
  ForwardBackward::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    result__[ 0   ] = LimitV_min(ModelPars[iM_v_min] - t2);
    result__[ 1   ] = LimitV_max(t2 - ModelPars[iM_v_max]);
    real_type t7   = U__[iU_a];
    result__[ 2   ] = LimitA_min(ModelPars[iM_a_min] - t7);
    result__[ 3   ] = LimitA_max(t7 - ModelPars[iM_a_max]);
    real_type t12  = t7 * t7;
    real_type t15  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t16  = t15 * t15;
    real_type t17  = t2 * t2;
    real_type t18  = t17 * t17;
    real_type t22  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    result__[ 4   ] = LimitE(1.0 / t22 * (t12 * ModelPars[iM_WA] + t18 * t16) - 1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::JU_numEqns() const { return 0; }

  void
  ForwardBackward::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::LTargs_numEqns() const { return 5; }

  void
  ForwardBackward::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  integer ForwardBackward::DJPDxpu_numRows() const { return 0; }
  integer ForwardBackward::DJPDxpu_numCols() const { return 2; }
  integer ForwardBackward::DJPDxpu_nnz()     const { return 0; }

  void
  ForwardBackward::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DLTDxpu_numRows() const { return 5; }
  integer ForwardBackward::DLTDxpu_numCols() const { return 2; }
  integer ForwardBackward::DLTDxpu_nnz()     const { return 6; }

  void
  ForwardBackward::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 4   ; jIndex[5 ] = 1   ;
  }


  void
  ForwardBackward::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t4   = ALIAS_LimitV_min_D(ModelPars[iM_v_min] - t2);
    result__[ 0   ] = -t4;
    result__[ 1   ] = ALIAS_LimitV_max_D(t2 - ModelPars[iM_v_max]);
    real_type t8   = U__[iU_a];
    real_type t10  = ALIAS_LimitA_min_D(ModelPars[iM_a_min] - t8);
    result__[ 2   ] = -t10;
    result__[ 3   ] = ALIAS_LimitA_max_D(t8 - ModelPars[iM_a_max]);
    real_type t13  = ModelPars[iM_WA];
    real_type t14  = t8 * t8;
    real_type t17  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t18  = t17 * t17;
    real_type t19  = t2 * t2;
    real_type t20  = t19 * t19;
    real_type t24  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t25  = 1.0 / t24;
    real_type t28  = ALIAS_LimitE_D(t25 * (t14 * t13 + t20 * t18) - 1);
    result__[ 4   ] = 4 * t25 * t19 * t2 * t18 * t28;
    result__[ 5   ] = 2 * t25 * t8 * t13 * t28;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DJUDxpu_numRows() const { return 0; }
  integer ForwardBackward::DJUDxpu_numCols() const { return 2; }
  integer ForwardBackward::DJUDxpu_nnz()     const { return 0; }

  void
  ForwardBackward::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
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
  integer ForwardBackward::D2JPD2xpu_numRows() const { return 2; }
  integer ForwardBackward::D2JPD2xpu_numCols() const { return 2; }
  integer ForwardBackward::D2JPD2xpu_nnz()     const { return 0; }

  void
  ForwardBackward::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    Path2D::SegmentClass const & segment = pTrajectory->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v];
    real_type t4   = ALIAS_LimitV_min_DD(ModelPars[iM_v_min] - t2);
    real_type t9   = ALIAS_LimitV_max_DD(t2 - ModelPars[iM_v_max]);
    real_type t12  = ModelPars[iM_WA];
    real_type t13  = U__[iU_a];
    real_type t14  = t13 * t13;
    real_type t17  = ALIAS_kappa(Q__[iQ_zeta]);
    real_type t18  = t17 * t17;
    real_type t19  = t2 * t2;
    real_type t20  = t19 * t19;
    real_type t24  = ModelPars[iM_E_max] * ModelPars[iM_E_max];
    real_type t25  = 1.0 / t24;
    real_type t27  = t25 * (t12 * t14 + t18 * t20) - 1;
    real_type t28  = ALIAS_LimitE_DD(t27);
    real_type t29  = t18 * t18;
    real_type t32  = t24 * t24;
    real_type t33  = 1.0 / t32;
    real_type t35  = OMEGA__[4];
    real_type t39  = ALIAS_LimitE_D(t27);
    result__[ 0   ] = 16 * t19 * t20 * t28 * t29 * t33 * t35 + 12 * t18 * t19 * t25 * t35 * t39 + t4 * OMEGA__[0] + t9 * OMEGA__[1];
    result__[ 1   ] = 8 * t35 * t19 * t2 * t18 * t33 * t13 * t12 * t28;
    result__[ 2   ] = result__[1];
    real_type t54  = ALIAS_LimitA_min_DD(ModelPars[iM_a_min] - t13);
    real_type t59  = ALIAS_LimitA_max_DD(t13 - ModelPars[iM_a_max]);
    real_type t62  = t12 * t12;
    result__[ 3   ] = 4 * t14 * t28 * t33 * t35 * t62 + 2 * t12 * t25 * t35 * t39 + t54 * OMEGA__[2] + t59 * OMEGA__[3];
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
