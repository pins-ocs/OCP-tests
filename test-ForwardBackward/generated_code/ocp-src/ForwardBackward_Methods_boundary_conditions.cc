/*-----------------------------------------------------------------------*\
 |  file: ForwardBackward_Methods_boundary_conditions.cc                 |
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
   |   ___                   _
   |  | _ ) ___ _  _ _ _  __| |__ _ _ _ _  _
   |  | _ \/ _ \ || | ' \/ _` / _` | '_| || |
   |  |___/\___/\_,_|_||_\__,_\__,_|_|  \_, |
   |    ___             _ _ _   _       |__/
   |   / __|___ _ _  __| (_) |_(_)___ _ _  ___
   |  | (__/ _ \ ' \/ _` | |  _| / _ \ ' \(_-<
   |   \___\___/_||_\__,_|_|\__|_\___/_||_/__/
  \*/

  integer ForwardBackward::bc_numEqns() const { return 2; }

  void
  ForwardBackward::bc_eval(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    Path2D::SegmentClass const & segmentLeft  = pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_v] - ModelPars[iM_v0];
    result__[ 1   ] = XR__[iX_v] - ModelPars[iM_v1];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::DbcDxxp_numRows() const { return 2; }
  integer ForwardBackward::DbcDxxp_numCols() const { return 2; }
  integer ForwardBackward::DbcDxxp_nnz()     const { return 2; }

  void
  ForwardBackward::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  void
  ForwardBackward::DbcDxxp_sparse(
    NodeQX const & LEFT__,
    NodeQX const & RIGHT__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    Path2D::SegmentClass const & segmentLeft  = pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::D2bcD2xxp_numRows() const { return 2; }
  integer ForwardBackward::D2bcD2xxp_numCols() const { return 2; }
  integer ForwardBackward::D2bcD2xxp_nnz()     const { return 0; }

  void
  ForwardBackward::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ForwardBackward::D2bcD2xxp_sparse(
    NodeQX const &          LEFT__,
    NodeQX const &          RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ForwardBackward::fd_BC_numEqns() const { return 2; }

  void
  ForwardBackward::fd_BC_eval(
    NodeQXL const &         LEFT__,
    NodeQXL const &         RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    Path2D::SegmentClass const & segmentLeft  = pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] - LR__[iL_lambda1__xo];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "fd_BC_eval", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ForwardBackward::Dfd_BCDxlxlp_numRows() const { return 2; }
  integer ForwardBackward::Dfd_BCDxlxlp_numCols() const { return 4; }
  integer ForwardBackward::Dfd_BCDxlxlp_nnz()     const { return 2; }

  void
  ForwardBackward::Dfd_BCDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
  }


  void
  ForwardBackward::Dfd_BCDxlxlp_sparse(
    NodeQXL const &         LEFT__,
    NodeQXL const &         RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    integer  i_segment_left = LEFT__.i_segment;
    real_const_ptr     QL__ = LEFT__.q;
    real_const_ptr     XL__ = LEFT__.x;
    real_const_ptr     LL__ = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_const_ptr     QR__ = RIGHT__.q;
    real_const_ptr     XR__ = RIGHT__.x;
    real_const_ptr     LR__ = RIGHT__.lambda;
    Path2D::SegmentClass const & segmentLeft  = pTrajectory->get_segment_by_index(i_segment_left);
    Path2D::SegmentClass const & segmentRight = pTrajectory->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "Dfd_BCDxlxlp_sparse", 2, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: ForwardBackward_Methods_boundary_conditions.cc
