/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_boundary_conditions.cc           |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"

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
#define ALIAS_G_bound_max_DD(__t1) G_bound_max.DD( __t1)
#define ALIAS_G_bound_max_D(__t1) G_bound_max.D( __t1)
#define ALIAS_G_bound_min_DD(__t1) G_bound_min.DD( __t1)
#define ALIAS_G_bound_min_D(__t1) G_bound_min.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)


namespace HypersonicProblem3DOFDefine {

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

  integer HypersonicProblem3DOF::bc_numEqns() const { return 10; }

  void
  HypersonicProblem3DOF::bc_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = XL__[iX_h] - ModelPars[iM_h_i];
    result__[ 1   ] = XL__[iX_theta] - ModelPars[iM_theta_i];
    result__[ 2   ] = XL__[iX_phi] - ModelPars[iM_phi_i];
    result__[ 3   ] = XL__[iX_V] - ModelPars[iM_V_i];
    result__[ 4   ] = XL__[iX_G] - ModelPars[iM_G_i];
    result__[ 5   ] = XL__[iX_psi] - ModelPars[iM_psi_i];
    result__[ 6   ] = XL__[iX_sigma] - ModelPars[iM_sigma_i];
    result__[ 7   ] = XR__[iX_h] - ModelPars[iM_h_f];
    result__[ 8   ] = XR__[iX_theta] - ModelPars[iM_theta_f];
    result__[ 9   ] = XR__[iX_phi] - ModelPars[iM_phi_f];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "bc_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DbcDxxp_numRows() const { return 10; }
  integer HypersonicProblem3DOF::DbcDxxp_numCols() const { return 15; }
  integer HypersonicProblem3DOF::DbcDxxp_nnz()     const { return 10; }

  void
  HypersonicProblem3DOF::DbcDxxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 9   ;
  }


  void
  HypersonicProblem3DOF::DbcDxxp_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = 1;
    result__[ 9   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DbcDxxp_sparse", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2bcD2xxp_numRows() const { return 15; }
  integer HypersonicProblem3DOF::D2bcD2xxp_numCols() const { return 15; }
  integer HypersonicProblem3DOF::D2bcD2xxp_nnz()     const { return 0; }

  void
  HypersonicProblem3DOF::D2bcD2xxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HypersonicProblem3DOF::D2bcD2xxp_sparse(
    NodeQX const &          LEFT__,
    NodeQX const &          RIGHT__,
    P_const_p_type          P__,
    OMEGA_full_const_p_type OMEGA__,
    real_ptr                result__
  ) const {
    // EMPTY
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::fd_BC_numEqns() const { return 14; }

  void
  HypersonicProblem3DOF::fd_BC_eval(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = OMEGA__[0] + LL__[iL_lambda1__xo];
    result__[ 1   ] = OMEGA__[1] + LL__[iL_lambda2__xo];
    result__[ 2   ] = OMEGA__[2] + LL__[iL_lambda3__xo];
    result__[ 3   ] = OMEGA__[3] + LL__[iL_lambda4__xo];
    result__[ 4   ] = OMEGA__[4] + LL__[iL_lambda5__xo];
    result__[ 5   ] = OMEGA__[5] + LL__[iL_lambda6__xo];
    result__[ 6   ] = OMEGA__[6] + LL__[iL_lambda7__xo];
    result__[ 7   ] = OMEGA__[7] - LR__[iL_lambda1__xo];
    result__[ 8   ] = OMEGA__[8] - LR__[iL_lambda2__xo];
    result__[ 9   ] = OMEGA__[9] - LR__[iL_lambda3__xo];
    result__[ 10  ] = -LR__[iL_lambda4__xo];
    result__[ 11  ] = -LR__[iL_lambda5__xo];
    result__[ 12  ] = -LR__[iL_lambda6__xo];
    result__[ 13  ] = -LR__[iL_lambda7__xo];
    real_type t27  = ModelPars[iM_Tf_guess];
    real_type t30  = t27 * t27;
    result__[ 14  ] = 2 / t30 * (P__[iP_Tf] - t27) * ModelPars[iM_WTF];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "fd_BC_eval", 10, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::Dfd_BCDxlxlp_numRows() const { return 15; }
  integer HypersonicProblem3DOF::Dfd_BCDxlxlp_numCols() const { return 29; }
  integer HypersonicProblem3DOF::Dfd_BCDxlxlp_nnz()     const { return 15; }

  void
  HypersonicProblem3DOF::Dfd_BCDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 7   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 8   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 9   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 10  ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 11  ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 12  ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 13  ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 21  ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 22  ;
    iIndex[9 ] = 9   ; jIndex[9 ] = 23  ;
    iIndex[10] = 10  ; jIndex[10] = 24  ;
    iIndex[11] = 11  ; jIndex[11] = 25  ;
    iIndex[12] = 12  ; jIndex[12] = 26  ;
    iIndex[13] = 13  ; jIndex[13] = 27  ;
    iIndex[14] = 14  ; jIndex[14] = 28  ;
  }


  void
  HypersonicProblem3DOF::Dfd_BCDxlxlp_sparse(
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
    MeshStd::SegmentClass const & segmentLeft  = pMesh->get_segment_by_index(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->get_segment_by_index(i_segment_right);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = -1;
    result__[ 8   ] = -1;
    result__[ 9   ] = -1;
    result__[ 10  ] = -1;
    result__[ 11  ] = -1;
    result__[ 12  ] = -1;
    result__[ 13  ] = -1;
    real_type t3   = ModelPars[iM_Tf_guess] * ModelPars[iM_Tf_guess];
    result__[ 14  ] = 2 / t3 * ModelPars[iM_WTF];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "Dfd_BCDxlxlp_sparse", 15, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}

// EOF: HypersonicProblem3DOF_Methods_boundary_conditions.cc
