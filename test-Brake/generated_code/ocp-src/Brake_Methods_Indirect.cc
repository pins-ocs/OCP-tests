/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods_Guess.cc                                         |
 |                                                                       |
 |  version: 1.0   date 8/2/2023                                         |
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


#include "Brake.hh"
#include "Brake_Pars.hh"

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


using namespace std;

namespace BrakeDefine {

  /*\
  :|:   ___           _ _               _
  :|:  |_ _|_ __   __| (_)_ __ ___  ___| |_
  :|:   | || '_ \ / _` | | '__/ _ \/ __| __|
  :|:   | || | | | (_| | | | |  __/ (__| |_
  :|:  |___|_| |_|\__,_|_|_|  \___|\___|\__|
  \*/


  integer Brake::fd_ode2_numEqns() const { return 2; }

  void
  Brake::fd_ode2_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // LM -------------------------------
    real_type LM__[2];
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = 1.0 / DZETA__xo;
    result__[ 0   ] = (LR__[iL_lambda1__xo] - LL__[iL_lambda1__xo]) * t1;
    result__[ 1   ] = (LR__[iL_lambda2__xo] - LL__[iL_lambda2__xo]) * t1 + LM__[0] * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_ode2_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brake::Dfd_ode2Dxlxlpu_numRows() const { return 2; }
  integer Brake::Dfd_ode2Dxlxlpu_numCols() const { return 10; }
  integer Brake::Dfd_ode2Dxlxlpu_nnz()     const { return 7; }

  void
  Brake::Dfd_ode2Dxlxlpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 8   ;
  }


  void
  Brake::Dfd_ode2Dxlxlpu_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // LM -------------------------------
    real_type LM__[2];
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = 1.0 / DZETA__xo;
    result__[ 0   ] = -t1;
    result__[ 1   ] = t1;
    result__[ 2   ] = P__[iP_T] / 2;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[2];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = LM__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_ode2Dxlxlpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer Brake::fd_int_numEqns() const { return 1; }

  void
  Brake::fd_int_eval(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // LM -------------------------------
    real_type LM__[2];
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[0];
    real_type t5   = cos(t2 * 0.314159265358979323846264338328e1 / 2);
    real_type t6   = log(t5);
    result__[ 0   ] = (t2 * LM__[1] - t6 * ModelPars[iM_epsilon] + LM__[0] * XM__[1]) * DZETA__xo;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "fd_int_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brake::Dfd_intDxlxlpu_numRows() const { return 1; }
  integer Brake::Dfd_intDxlxlpu_numCols() const { return 10; }
  integer Brake::Dfd_intDxlxlpu_nnz()     const { return 7; }

  void
  Brake::Dfd_intDxlxlpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 9   ;
  }


  void
  Brake::Dfd_intDxlxlpu_sparse(
    NodeQXL const & LEFT__,
    NodeQXL const & RIGHT__,
    P_const_p_type  P__,
    U_const_p_type  UM__,
    real_ptr        result__
  ) const {
    integer i_segment = LEFT__.i_segment;
    // LEFT -----------------------------
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    // RIGHT ----------------------------
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // QM -------------------------------
    real_type QM__[1];
    QM__[0] = (QL__[0]+QR__[0])/2;
    // XM -------------------------------
    real_type XM__[2];
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // LM -------------------------------
    real_type LM__[2];
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    // V -------------------------------
    real_type DZETA__xo = QR__[0] - QL__[0];
    real_type V__[2];
    V__[0] = (XR__[0]-XL__[0])/DZETA__xo;
    V__[1] = (XR__[1]-XL__[1])/DZETA__xo;

    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = DZETA__xo * LM__[0] / 2;
    result__[ 1   ] = DZETA__xo * XM__[1] / 2;
    real_type t5   = UM__[0];
    result__[ 2   ] = t5 * DZETA__xo / 2;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    real_type t10  = t5 * 0.314159265358979323846264338328e1 / 2;
    real_type t11  = sin(t10);
    real_type t12  = cos(t10);
    result__[ 6   ] = (1.0 / t12 * t11 * ModelPars[iM_epsilon] * 0.314159265358979323846264338328e1 / 2 + LM__[1]) * DZETA__xo;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Dfd_intDxlxlpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::node_LR_to_cell(
    NodeQX const & LEFT,
    NodeQX const & RIGHT,
    NodeQX       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::node_LR_to_cell(
    NodeQXL const & LEFT,
    NodeQXL const & RIGHT,
    NodeQXL       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    real_ptr L = const_cast<real_ptr>(NODE.lambda);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    L[0] = (LEFT.lambda[0]+RIGHT.lambda[0])/2;
    L[1] = (LEFT.lambda[1]+RIGHT.lambda[1])/2;
  }
}

// EOF: Brake_Methods_Guess.cc
