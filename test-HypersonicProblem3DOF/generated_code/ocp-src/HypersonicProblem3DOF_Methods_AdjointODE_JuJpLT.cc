/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_AdjointODE.cc                    |
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
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::JP_numEqns() const { return 0; }

  void
  HypersonicProblem3DOF::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::LT_numEqns() const { return 2; }

  void
  HypersonicProblem3DOF::LT_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = X__[iX_G];
    real_type t4   = G_bound_min(-0.314159265358979323846264338328e1 - t2);
    result__[ 0   ] = t4 * t1;
    real_type t6   = G_bound_max(t2 - 0.314159265358979323846264338328e1);
    result__[ 1   ] = t6 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::JU_numEqns() const { return 1; }

  void
  HypersonicProblem3DOF::JU_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = u2Control(U__[iU_u2], -1, 1);
    result__[ 0   ] = t3 * P__[iP_Tf];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::LTargs_numEqns() const { return 2; }

  void
  HypersonicProblem3DOF::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_G];
    result__[ 0   ] = -0.314159265358979323846264338328e1 - t1;
    result__[ 1   ] = t1 - 0.314159265358979323846264338328e1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 2, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DJPDxpu_numRows() const { return 0; }
  integer HypersonicProblem3DOF::DJPDxpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::DJPDxpu_nnz()     const { return 0; }

  void
  HypersonicProblem3DOF::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HypersonicProblem3DOF::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DLTDxpu_numRows() const { return 2; }
  integer HypersonicProblem3DOF::DLTDxpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::DLTDxpu_nnz()     const { return 4; }

  void
  HypersonicProblem3DOF::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 7   ;
  }


  void
  HypersonicProblem3DOF::DLTDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = X__[iX_G];
    real_type t3   = -0.314159265358979323846264338328e1 - t2;
    real_type t4   = ALIAS_G_bound_min_D(t3);
    result__[ 0   ] = -t4 * t1;
    result__[ 1   ] = G_bound_min(t3);
    real_type t6   = t2 - 0.314159265358979323846264338328e1;
    real_type t7   = ALIAS_G_bound_max_D(t6);
    result__[ 2   ] = t7 * t1;
    result__[ 3   ] = G_bound_max(t6);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DJUDxpu_numRows() const { return 1; }
  integer HypersonicProblem3DOF::DJUDxpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::DJUDxpu_nnz()     const { return 2; }

  void
  HypersonicProblem3DOF::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 7   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 9   ;
  }


  void
  HypersonicProblem3DOF::DJUDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u2];
    result__[ 0   ] = u2Control(t1, -1, 1);
    real_type t3   = ALIAS_u2Control_D_1(t1, -1, 1);
    result__[ 1   ] = t3 * P__[iP_Tf];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DLTargsDxpu_numRows() const { return 2; }
  integer HypersonicProblem3DOF::DLTargsDxpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::DLTargsDxpu_nnz()     const { return 2; }

  void
  HypersonicProblem3DOF::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 4   ;
  }


  void
  HypersonicProblem3DOF::DLTargsDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 2, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2JPD2xpu_numRows() const { return 17; }
  integer HypersonicProblem3DOF::D2JPD2xpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::D2JPD2xpu_nnz()     const { return 0; }

  void
  HypersonicProblem3DOF::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HypersonicProblem3DOF::D2JPD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2LTD2xpu_numRows() const { return 17; }
  integer HypersonicProblem3DOF::D2LTD2xpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::D2LTD2xpu_nnz()     const { return 3; }

  void
  HypersonicProblem3DOF::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 4   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 4   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 7   ; jIndex[2 ] = 4   ;
  }


  void
  HypersonicProblem3DOF::D2LTD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = X__[iX_G];
    real_type t3   = -0.314159265358979323846264338328e1 - t2;
    real_type t4   = ALIAS_G_bound_min_DD(t3);
    real_type t6   = OMEGA__[0];
    real_type t8   = t2 - 0.314159265358979323846264338328e1;
    real_type t9   = ALIAS_G_bound_max_DD(t8);
    real_type t11  = OMEGA__[1];
    result__[ 0   ] = t1 * t11 * t9 + t1 * t4 * t6;
    real_type t13  = ALIAS_G_bound_min_D(t3);
    real_type t15  = ALIAS_G_bound_max_D(t8);
    result__[ 1   ] = t11 * t15 - t13 * t6;
    result__[ 2   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2JUD2xpu_numRows() const { return 17; }
  integer HypersonicProblem3DOF::D2JUD2xpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::D2JUD2xpu_nnz()     const { return 3; }

  void
  HypersonicProblem3DOF::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 7   ; jIndex[0 ] = 9   ;
    iIndex[1 ] = 9   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 9   ; jIndex[2 ] = 9   ;
  }


  void
  HypersonicProblem3DOF::D2JUD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u2];
    real_type t2   = ALIAS_u2Control_D_1(t1, -1, 1);
    real_type t3   = OMEGA__[0];
    result__[ 0   ] = t3 * t2;
    result__[ 1   ] = result__[0];
    real_type t5   = ALIAS_u2Control_D_1_1(t1, -1, 1);
    result__[ 2   ] = t3 * t5 * P__[iP_Tf];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::D2LTargsD2xpu_numRows() const { return 17; }
  integer HypersonicProblem3DOF::D2LTargsD2xpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  HypersonicProblem3DOF::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HypersonicProblem3DOF::D2LTargsD2xpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: HypersonicProblem3DOF_Methods_AdjointODE.cc
