/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_controls.cc                                 |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#endif

// map user defined functions and objects with macros
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace UnderwaterDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  Underwater::g_numEqns() const
  { return 3; }

  void
  Underwater::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    real_type t4   = ModelPars[iM_m1];
    result__[ 0   ] = 1.0 / t4 * (t4 * t3 + L__[iL_lambda4__xo]) * t1;
    real_type t11  = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    real_type t12  = ModelPars[iM_m3];
    result__[ 1   ] = 1.0 / t12 * (t12 * t11 + L__[iL_lambda5__xo]) * t1;
    real_type t19  = ALIAS_u3Control_D_1(U__[iU_u3], -1, 1);
    real_type t20  = ModelPars[iM_inertia];
    result__[ 2   ] = 1.0 / t20 * (t20 * t19 + L__[iL_lambda6__xo]) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DgDxlp_numRows() const
  { return 3; }

  integer
  Underwater::DgDxlp_numCols() const
  { return 13; }

  integer
  Underwater::DgDxlp_nnz() const
  { return 6; }

  void
  Underwater::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 9   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 12  ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 10  ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 12  ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 11  ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 12  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = 1.0 / ModelPars[iM_m1];
    result__[ 0   ] = t3 * t1;
    real_type t7   = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    result__[ 1   ] = t3 * L__[iL_lambda4__xo] + t7;
    real_type t9   = 1.0 / ModelPars[iM_m3];
    result__[ 2   ] = t9 * t1;
    real_type t13  = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    result__[ 3   ] = t9 * L__[iL_lambda5__xo] + t13;
    real_type t15  = 1.0 / ModelPars[iM_inertia];
    result__[ 4   ] = t15 * t1;
    real_type t19  = ALIAS_u3Control_D_1(U__[iU_u3], -1, 1);
    result__[ 5   ] = t15 * L__[iL_lambda6__xo] + t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DgDu_numRows() const
  { return 3; }

  integer
  Underwater::DgDu_numCols() const
  { return 3; }

  integer
  Underwater::DgDu_nnz() const
  { return 3; }

  void
  Underwater::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DgDu_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    result__[ 1   ] = t5 * t1;
    real_type t7   = ALIAS_u3Control_D_1_1(U__[iU_u3], -1, 1);
    result__[ 2   ] = t7 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 3, i_segment );
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
  Underwater::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    X__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    L__[4] = (LL__[4]+LR__[4])/2;
    L__[5] = (LL__[5]+LR__[5])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    U__[ iU_u1 ] = u1Control.solve((-LL__[iL_lambda4__xo] - LR__[iL_lambda4__xo]) / ModelPars[iM_m1] / 2, -1, 1);
    U__[ iU_u2 ] = u2Control.solve((-LL__[iL_lambda5__xo] - LR__[iL_lambda5__xo]) / ModelPars[iM_m3] / 2, -1, 1);
    U__[ iU_u3 ] = u3Control.solve((-LL__[iL_lambda6__xo] - LR__[iL_lambda6__xo]) / ModelPars[iM_inertia] / 2, -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 3 );
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    X__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    L__[4] = (LL__[4]+LR__[4])/2;
    L__[5] = (LL__[5]+LR__[5])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type tmp_0_0 = 0;
    real_type tmp_1_0 = 0;
    real_type tmp_2_0 = 0;
    real_type tmp_0_1 = 0;
    real_type tmp_1_1 = 0;
    real_type tmp_2_1 = 0;
    real_type tmp_0_2 = 0;
    real_type tmp_1_2 = 0;
    real_type tmp_2_2 = 0;
    real_type tmp_0_3 = 0;
    real_type tmp_1_3 = 0;
    real_type tmp_2_3 = 0;
    real_type tmp_0_4 = 0;
    real_type tmp_1_4 = 0;
    real_type tmp_2_4 = 0;
    real_type tmp_0_5 = 0;
    real_type tmp_1_5 = 0;
    real_type tmp_2_5 = 0;
    real_type tmp_0_6 = 0;
    real_type tmp_1_6 = 0;
    real_type tmp_2_6 = 0;
    real_type tmp_0_7 = 0;
    real_type tmp_1_7 = 0;
    real_type tmp_2_7 = 0;
    real_type tmp_0_8 = 0;
    real_type tmp_1_8 = 0;
    real_type tmp_2_8 = 0;
    real_type t5   = 1.0 / ModelPars[iM_m1];
    real_type t8   = u1Control.solve_rhs(t5 * (-LL__[iL_lambda4__xo] - LR__[iL_lambda4__xo]) / 2, -1, 1);
    real_type tmp_0_9 = -t5 * t8 / 2;
    real_type tmp_1_9 = 0;
    real_type tmp_2_9 = 0;
    real_type tmp_0_10 = 0;
    real_type t15  = 1.0 / ModelPars[iM_m3];
    real_type t18  = u2Control.solve_rhs(t15 * (-LL__[iL_lambda5__xo] - LR__[iL_lambda5__xo]) / 2, -1, 1);
    real_type tmp_1_10 = -t15 * t18 / 2;
    real_type tmp_2_10 = 0;
    real_type tmp_0_11 = 0;
    real_type tmp_1_11 = 0;
    real_type t25  = 1.0 / ModelPars[iM_inertia];
    real_type t28  = u3Control.solve_rhs(t25 * (-LL__[iL_lambda6__xo] - LR__[iL_lambda6__xo]) / 2, -1, 1);
    real_type tmp_2_11 = -t25 * t28 / 2;
    real_type tmp_0_12 = 0;
    real_type tmp_1_12 = 0;
    real_type tmp_2_12 = 0;
    real_type tmp_0_13 = 0;
    real_type tmp_1_13 = 0;
    real_type tmp_2_13 = 0;
    real_type tmp_0_14 = 0;
    real_type tmp_1_14 = 0;
    real_type tmp_2_14 = 0;
    real_type tmp_0_15 = 0;
    real_type tmp_1_15 = 0;
    real_type tmp_2_15 = 0;
    real_type tmp_0_16 = 0;
    real_type tmp_1_16 = 0;
    real_type tmp_2_16 = 0;
    real_type tmp_0_17 = 0;
    real_type tmp_1_17 = 0;
    real_type tmp_2_17 = 0;
    real_type tmp_0_18 = 0;
    real_type tmp_1_18 = 0;
    real_type tmp_2_18 = 0;
    real_type tmp_0_19 = 0;
    real_type tmp_1_19 = 0;
    real_type tmp_2_19 = 0;
    real_type tmp_0_20 = 0;
    real_type tmp_1_20 = 0;
    real_type tmp_2_20 = 0;
    real_type tmp_0_21 = tmp_0_9;
    real_type tmp_1_21 = 0;
    real_type tmp_2_21 = 0;
    real_type tmp_0_22 = 0;
    real_type tmp_1_22 = tmp_1_10;
    real_type tmp_2_22 = 0;
    real_type tmp_0_23 = 0;
    real_type tmp_1_23 = 0;
    real_type tmp_2_23 = tmp_2_11;
    real_type tmp_0_24 = 0;
    real_type tmp_1_24 = 0;
    real_type tmp_2_24 = 0;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(2, 0) = tmp_2_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(2, 1) = tmp_2_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(2, 2) = tmp_2_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    DuDxlxlp(2, 3) = tmp_2_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(1, 4) = tmp_1_4;
    DuDxlxlp(2, 4) = tmp_2_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(1, 5) = tmp_1_5;
    DuDxlxlp(2, 5) = tmp_2_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(1, 6) = tmp_1_6;
    DuDxlxlp(2, 6) = tmp_2_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(1, 7) = tmp_1_7;
    DuDxlxlp(2, 7) = tmp_2_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(1, 8) = tmp_1_8;
    DuDxlxlp(2, 8) = tmp_2_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(1, 9) = tmp_1_9;
    DuDxlxlp(2, 9) = tmp_2_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(1, 10) = tmp_1_10;
    DuDxlxlp(2, 10) = tmp_2_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(1, 11) = tmp_1_11;
    DuDxlxlp(2, 11) = tmp_2_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(1, 12) = tmp_1_12;
    DuDxlxlp(2, 12) = tmp_2_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(1, 13) = tmp_1_13;
    DuDxlxlp(2, 13) = tmp_2_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(1, 14) = tmp_1_14;
    DuDxlxlp(2, 14) = tmp_2_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(1, 15) = tmp_1_15;
    DuDxlxlp(2, 15) = tmp_2_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(1, 16) = tmp_1_16;
    DuDxlxlp(2, 16) = tmp_2_16;
    DuDxlxlp(0, 17) = tmp_0_17;
    DuDxlxlp(1, 17) = tmp_1_17;
    DuDxlxlp(2, 17) = tmp_2_17;
    DuDxlxlp(0, 18) = tmp_0_18;
    DuDxlxlp(1, 18) = tmp_1_18;
    DuDxlxlp(2, 18) = tmp_2_18;
    DuDxlxlp(0, 19) = tmp_0_19;
    DuDxlxlp(1, 19) = tmp_1_19;
    DuDxlxlp(2, 19) = tmp_2_19;
    DuDxlxlp(0, 20) = tmp_0_20;
    DuDxlxlp(1, 20) = tmp_1_20;
    DuDxlxlp(2, 20) = tmp_2_20;
    DuDxlxlp(0, 21) = tmp_0_21;
    DuDxlxlp(1, 21) = tmp_1_21;
    DuDxlxlp(2, 21) = tmp_2_21;
    DuDxlxlp(0, 22) = tmp_0_22;
    DuDxlxlp(1, 22) = tmp_1_22;
    DuDxlxlp(2, 22) = tmp_2_22;
    DuDxlxlp(0, 23) = tmp_0_23;
    DuDxlxlp(1, 23) = tmp_1_23;
    DuDxlxlp(2, 23) = tmp_2_23;
    DuDxlxlp(0, 24) = tmp_0_24;
    DuDxlxlp(1, 24) = tmp_1_24;
    DuDxlxlp(2, 24) = tmp_2_24;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 75 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Underwater::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u1];
    real_type t3   = u1Control(t2, -1, 1);
    real_type t5   = U__[iU_u2];
    real_type t6   = u2Control(t5, -1, 1);
    real_type t8   = U__[iU_u3];
    real_type t9   = u3Control(t8, -1, 1);
    real_type t11  = X__[iX_vx];
    real_type t12  = t11 * t1;
    real_type t13  = X__[iX_theta];
    real_type t14  = cos(t13);
    real_type t16  = X__[iX_vz];
    real_type t17  = t16 * t1;
    real_type t18  = sin(t13);
    real_type t22  = pow(t14 * t12 + t18 * t17 - V__[0], 2);
    real_type t27  = pow(t18 * t12 - t14 * t17 + V__[1], 2);
    real_type t28  = X__[iX_Omega];
    real_type t32  = pow(-t28 * t1 + V__[2], 2);
    real_type t34  = ModelPars[iM_m1];
    real_type t35  = 1.0 / t34;
    real_type t38  = ModelPars[iM_m3];
    real_type t44  = pow(V__[3] - (-t35 * t38 * t28 * t16 + t35 * t2) * t1, 2);
    real_type t46  = 1.0 / t38;
    real_type t54  = pow(V__[4] - (t46 * t34 * t28 * t11 + t46 * t5) * t1, 2);
    real_type t57  = 1.0 / ModelPars[iM_inertia];
    real_type t66  = pow(V__[5] - (t57 * t8 + t57 * (t38 - t34) * t16 * t11) * t1, 2);
    real_type result__ = t3 * t1 + t6 * t1 + t9 * t1 + t22 + t27 + t32 + t44 + t54 + t66;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DmDu_numEqns() const
  { return 3; }

  void
  Underwater::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_vz];
    real_type t4   = X__[iX_Omega];
    real_type t5   = ModelPars[iM_m3];
    real_type t9   = U__[iU_u1];
    real_type t10  = ALIAS_u1Control_D_1(t9, -1, 1);
    real_type t11  = ModelPars[iM_m1];
    real_type t12  = t11 * t11;
    result__[ 0   ] = 1.0 / t12 * (-2 * t5 * t4 * t2 * t1 + 2 * t9 * t1 + t12 * t10 - 2 * t11 * V__[3]) * t1;
    real_type t22  = U__[iU_u2];
    real_type t23  = ALIAS_u2Control_D_1(t22, -1, 1);
    real_type t24  = t5 * t5;
    real_type t29  = X__[iX_vx];
    result__[ 1   ] = 2 / t24 * (t24 * t23 / 2 - t5 * V__[4] + (t11 * t4 * t29 + t22) * t1) * t1;
    real_type t38  = U__[iU_u3];
    real_type t39  = ALIAS_u3Control_D_1(t38, -1, 1);
    real_type t40  = ModelPars[iM_inertia];
    real_type t41  = t40 * t40;
    result__[ 2   ] = 2 / t41 * t1 * (t41 * t39 / 2 + t1 * (t38 - (-t5 + t11) * t2 * t29) - t40 * V__[5]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Underwater::DmDuu_numRows() const
  { return 3; }

  integer
  Underwater::DmDuu_numCols() const
  { return 3; }

  integer
  Underwater::DmDuu_nnz() const
  { return 3; }

  void
  Underwater::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    real_type t5   = t1 * t1;
    real_type t7   = ModelPars[iM_m1] * ModelPars[iM_m1];
    result__[ 0   ] = t3 * t1 + 2 / t7 * t5;
    real_type t12  = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    real_type t15  = ModelPars[iM_m3] * ModelPars[iM_m3];
    result__[ 1   ] = t12 * t1 + 2 / t15 * t5;
    real_type t20  = ALIAS_u3Control_D_1_1(U__[iU_u3], -1, 1);
    real_type t23  = ModelPars[iM_inertia] * ModelPars[iM_inertia];
    result__[ 2   ] = t20 * t1 + 2 / t23 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 3, i_segment );
  }

}

// EOF: Underwater_Methods_controls.cc
