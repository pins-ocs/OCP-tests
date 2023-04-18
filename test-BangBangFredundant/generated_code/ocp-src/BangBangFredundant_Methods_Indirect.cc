/*-----------------------------------------------------------------------*\
 |  file: BangBangFredundant_Methods_Guess.cc                            |
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


#include "BangBangFredundant.hh"
#include "BangBangFredundant_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_Flim_max_DD(__t1) Flim_max.DD( __t1)
#define ALIAS_Flim_max_D(__t1) Flim_max.D( __t1)
#define ALIAS_Flim_min_DD(__t1) Flim_min.DD( __t1)
#define ALIAS_Flim_min_D(__t1) Flim_min.D( __t1)
#define ALIAS_aF2Control_D_3(__t1, __t2, __t3) aF2Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2(__t1, __t2, __t3) aF2Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1(__t1, __t2, __t3) aF2Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_3_3(__t1, __t2, __t3) aF2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_3(__t1, __t2, __t3) aF2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_2(__t1, __t2, __t3) aF2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_3(__t1, __t2, __t3) aF2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_2(__t1, __t2, __t3) aF2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_1(__t1, __t2, __t3) aF2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3(__t1, __t2, __t3) aF1Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2(__t1, __t2, __t3) aF1Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1(__t1, __t2, __t3) aF1Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3_3(__t1, __t2, __t3) aF1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_3(__t1, __t2, __t3) aF1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_2(__t1, __t2, __t3) aF1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_3(__t1, __t2, __t3) aF1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_2(__t1, __t2, __t3) aF1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_1(__t1, __t2, __t3) aF1Control.D_1_1( __t1, __t2, __t3)


using namespace std;

namespace BangBangFredundantDefine {

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


  integer BangBangFredundant::eta_numEqns() const { return 6; }

  void
  BangBangFredundant::eta_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    real_ptr        result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = MU__[0];
    result__[ 1   ] = MU__[1];
    result__[ 2   ] = MU__[2];
    result__[ 3   ] = MU__[3];
    result__[ 4   ] = MU__[4];
    result__[ 5   ] = MU__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "eta", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFredundant::DetaDxp_numRows() const { return 6; }
  integer BangBangFredundant::DetaDxp_numCols() const { return 6; }
  integer BangBangFredundant::DetaDxp_nnz()     const { return 0; }

  void
  BangBangFredundant::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::DetaDxp_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

  /*\
  :|:   ___           _ _               _
  :|:  |_ _|_ __   __| (_)_ __ ___  ___| |_
  :|:   | || '_ \ / _` | | '__/ _ \/ __| __|
  :|:   | || | | | (_| | | | |  __/ (__| |_
  :|:  |___|_| |_|\__,_|_|_|  \___|\___|\__|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::node_LR_to_cell(
    NodeQX const & LEFT,
    NodeQX const & RIGHT,
    NodeQX       & NODE
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::node_LR_to_cell(
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
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    L[0] = (LEFT.lambda[0]+RIGHT.lambda[0])/2;
    L[1] = (LEFT.lambda[1]+RIGHT.lambda[1])/2;
    L[2] = (LEFT.lambda[2]+RIGHT.lambda[2])/2;
    L[3] = (LEFT.lambda[3]+RIGHT.lambda[3])/2;
    L[4] = (LEFT.lambda[4]+RIGHT.lambda[4])/2;
    L[5] = (LEFT.lambda[5]+RIGHT.lambda[5])/2;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  BangBangFredundant::node_LR_to_cell(
    NodeQXL const & LEFT,
    NodeQXL const & RIGHT,
    NodeQXL       & NODE,
    V_p_type      & V,
    VL_p_type     & VL
  ) const {
    real_ptr Q = const_cast<real_ptr>(NODE.q);
    real_ptr X = const_cast<real_ptr>(NODE.x);
    real_ptr L = const_cast<real_ptr>(NODE.lambda);
    Q[0] = (LEFT.q[0]+RIGHT.q[0])/2;
    X[0] = (LEFT.x[0]+RIGHT.x[0])/2;
    X[1] = (LEFT.x[1]+RIGHT.x[1])/2;
    X[2] = (LEFT.x[2]+RIGHT.x[2])/2;
    X[3] = (LEFT.x[3]+RIGHT.x[3])/2;
    X[4] = (LEFT.x[4]+RIGHT.x[4])/2;
    X[5] = (LEFT.x[5]+RIGHT.x[5])/2;
    L[0] = (LEFT.lambda[0]+RIGHT.lambda[0])/2;
    L[1] = (LEFT.lambda[1]+RIGHT.lambda[1])/2;
    L[2] = (LEFT.lambda[2]+RIGHT.lambda[2])/2;
    L[3] = (LEFT.lambda[3]+RIGHT.lambda[3])/2;
    L[4] = (LEFT.lambda[4]+RIGHT.lambda[4])/2;
    L[5] = (LEFT.lambda[5]+RIGHT.lambda[5])/2;
    real_type DZETA__xo = RIGHT.q[0] - LEFT.q[0];
    V[0]  = (RIGHT.x[0]-LEFT.x[0])/DZETA__xo;
    V[1]  = (RIGHT.x[1]-LEFT.x[1])/DZETA__xo;
    V[2]  = (RIGHT.x[2]-LEFT.x[2])/DZETA__xo;
    V[3]  = (RIGHT.x[3]-LEFT.x[3])/DZETA__xo;
    V[4]  = (RIGHT.x[4]-LEFT.x[4])/DZETA__xo;
    V[5]  = (RIGHT.x[5]-LEFT.x[5])/DZETA__xo;
    VL[0] = (RIGHT.lambda[0]-LEFT.lambda[0])/DZETA__xo;
    VL[1] = (RIGHT.lambda[1]-LEFT.lambda[1])/DZETA__xo;
    VL[2] = (RIGHT.lambda[2]-LEFT.lambda[2])/DZETA__xo;
    VL[3] = (RIGHT.lambda[3]-LEFT.lambda[3])/DZETA__xo;
    VL[4] = (RIGHT.lambda[4]-LEFT.lambda[4])/DZETA__xo;
    VL[5] = (RIGHT.lambda[5]-LEFT.lambda[5])/DZETA__xo;
    return DZETA__xo;
  }

}

// EOF: BangBangFredundant_Methods_Guess.cc
