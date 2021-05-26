/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_controls.cc                                     |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#include "Farmer.hh"
#include "Farmer_Pars.hh"

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
#define ALIAS_LimitX2X4_DD(__t1) LimitX2X4.DD( __t1)
#define ALIAS_LimitX2X4_D(__t1) LimitX2X4.D( __t1)
#define ALIAS_x4__oControl_D_3(__t1, __t2, __t3) x4__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2(__t1, __t2, __t3) x4__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1(__t1, __t2, __t3) x4__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_3_3(__t1, __t2, __t3) x4__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2_3(__t1, __t2, __t3) x4__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_2_2(__t1, __t2, __t3) x4__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_3(__t1, __t2, __t3) x4__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_2(__t1, __t2, __t3) x4__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x4__oControl_D_1_1(__t1, __t2, __t3) x4__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_3(__t1, __t2, __t3) x3__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2(__t1, __t2, __t3) x3__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1(__t1, __t2, __t3) x3__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_3_3(__t1, __t2, __t3) x3__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2_3(__t1, __t2, __t3) x3__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_2_2(__t1, __t2, __t3) x3__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_3(__t1, __t2, __t3) x3__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_2(__t1, __t2, __t3) x3__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x3__oControl_D_1_1(__t1, __t2, __t3) x3__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_3(__t1, __t2, __t3) x2__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2(__t1, __t2, __t3) x2__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1(__t1, __t2, __t3) x2__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_3_3(__t1, __t2, __t3) x2__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2_3(__t1, __t2, __t3) x2__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_2_2(__t1, __t2, __t3) x2__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_3(__t1, __t2, __t3) x2__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_2(__t1, __t2, __t3) x2__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x2__oControl_D_1_1(__t1, __t2, __t3) x2__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_3(__t1, __t2, __t3) x1__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2(__t1, __t2, __t3) x1__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1(__t1, __t2, __t3) x1__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_3_3(__t1, __t2, __t3) x1__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2_3(__t1, __t2, __t3) x1__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_2_2(__t1, __t2, __t3) x1__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_3(__t1, __t2, __t3) x1__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_2(__t1, __t2, __t3) x1__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_x1__oControl_D_1_1(__t1, __t2, __t3) x1__oControl.D_1_1( __t1, __t2, __t3)


namespace FarmerDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  Farmer::g_numEqns() const
  { return 4; }

  void
  Farmer::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = U__[iU_x1__o];
    real_type t2   = ALIAS_x1__oControl_D_1(t1, -0.1e-2, 100);
    result__[ 0   ] = t2 + 2 * (-X__[iX_x1] + t1) * ModelPars[iM_wJ1] + L__[iL_lambda1__xo] / ModelPars[iM_tau__1];
    real_type t12  = U__[iU_x2__o];
    real_type t13  = ALIAS_x2__oControl_D_1(t12, -0.1e-2, 100);
    result__[ 1   ] = t13 + 2 * (-X__[iX_x2] + t12) * ModelPars[iM_wJ2] + L__[iL_lambda2__xo] / ModelPars[iM_tau__2];
    real_type t23  = U__[iU_x3__o];
    real_type t24  = ALIAS_x3__oControl_D_1(t23, -0.1e-2, 100);
    result__[ 2   ] = t24 + 2 * (-X__[iX_x3] + t23) * ModelPars[iM_wJ3] + L__[iL_lambda3__xo] / ModelPars[iM_tau__3];
    real_type t34  = U__[iU_x4__o];
    real_type t35  = ALIAS_x4__oControl_D_1(t34, -0.1e-2, 100);
    result__[ 3   ] = t35 + 2 * (-X__[iX_x4] + t34) * ModelPars[iM_wJ4] + L__[iL_lambda5__xo] / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DgDxlp_numRows() const
  { return 4; }

  integer
  Farmer::DgDxlp_numCols() const
  { return 10; }

  integer
  Farmer::DgDxlp_nnz() const
  { return 8; }

  void
  Farmer::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 1   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 7   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 9   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = -2 * ModelPars[iM_wJ1];
    result__[ 1   ] = 1.0 / ModelPars[iM_tau__1];
    result__[ 2   ] = -2 * ModelPars[iM_wJ2];
    result__[ 3   ] = 1.0 / ModelPars[iM_tau__2];
    result__[ 4   ] = -2 * ModelPars[iM_wJ3];
    result__[ 5   ] = 1.0 / ModelPars[iM_tau__3];
    result__[ 6   ] = -2 * ModelPars[iM_wJ4];
    result__[ 7   ] = 1.0 / ModelPars[iM_tau__5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DgDu_numRows() const
  { return 4; }

  integer
  Farmer::DgDu_numCols() const
  { return 4; }

  integer
  Farmer::DgDu_nnz() const
  { return 4; }

  void
  Farmer::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DgDu_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ALIAS_x1__oControl_D_1_1(U__[iU_x1__o], -0.1e-2, 100);
    result__[ 0   ] = t2 + 2 * ModelPars[iM_wJ1];
    real_type t6   = ALIAS_x2__oControl_D_1_1(U__[iU_x2__o], -0.1e-2, 100);
    result__[ 1   ] = t6 + 2 * ModelPars[iM_wJ2];
    real_type t10  = ALIAS_x3__oControl_D_1_1(U__[iU_x3__o], -0.1e-2, 100);
    result__[ 2   ] = t10 + 2 * ModelPars[iM_wJ3];
    real_type t14  = ALIAS_x4__oControl_D_1_1(U__[iU_x4__o], -0.1e-2, 100);
    result__[ 3   ] = t14 + 2 * ModelPars[iM_wJ4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 4, i_segment );
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
  Farmer::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1];
    real_type XM__[5];
    real_type LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_x1__o ] = 0;
    U__[ iU_x2__o ] = 0;
    U__[ iU_x3__o ] = 0;
    U__[ iU_x4__o ] = 0;
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 4 );
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
  Farmer::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1];
    real_type XM__[5];
    real_type LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_1_0 = 0.0e0;
    real_type tmp_2_0 = 0.0e0;
    real_type tmp_3_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_1_1 = 0.0e0;
    real_type tmp_2_1 = 0.0e0;
    real_type tmp_3_1 = 0.0e0;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_1_2 = 0.0e0;
    real_type tmp_2_2 = 0.0e0;
    real_type tmp_3_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_1_3 = 0.0e0;
    real_type tmp_2_3 = 0.0e0;
    real_type tmp_3_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_1_4 = 0.0e0;
    real_type tmp_2_4 = 0.0e0;
    real_type tmp_3_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type tmp_1_5 = 0.0e0;
    real_type tmp_2_5 = 0.0e0;
    real_type tmp_3_5 = 0.0e0;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_1_6 = 0.0e0;
    real_type tmp_2_6 = 0.0e0;
    real_type tmp_3_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_1_7 = 0.0e0;
    real_type tmp_2_7 = 0.0e0;
    real_type tmp_3_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_1_8 = 0.0e0;
    real_type tmp_2_8 = 0.0e0;
    real_type tmp_3_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_1_9 = 0.0e0;
    real_type tmp_2_9 = 0.0e0;
    real_type tmp_3_9 = 0.0e0;
    real_type tmp_0_10 = 0.0e0;
    real_type tmp_1_10 = 0.0e0;
    real_type tmp_2_10 = 0.0e0;
    real_type tmp_3_10 = 0.0e0;
    real_type tmp_0_11 = 0.0e0;
    real_type tmp_1_11 = 0.0e0;
    real_type tmp_2_11 = 0.0e0;
    real_type tmp_3_11 = 0.0e0;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_1_12 = 0.0e0;
    real_type tmp_2_12 = 0.0e0;
    real_type tmp_3_12 = 0.0e0;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_1_13 = 0.0e0;
    real_type tmp_2_13 = 0.0e0;
    real_type tmp_3_13 = 0.0e0;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_1_14 = 0.0e0;
    real_type tmp_2_14 = 0.0e0;
    real_type tmp_3_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_1_15 = 0.0e0;
    real_type tmp_2_15 = 0.0e0;
    real_type tmp_3_15 = 0.0e0;
    real_type tmp_0_16 = 0.0e0;
    real_type tmp_1_16 = 0.0e0;
    real_type tmp_2_16 = 0.0e0;
    real_type tmp_3_16 = 0.0e0;
    real_type tmp_0_17 = 0.0e0;
    real_type tmp_1_17 = 0.0e0;
    real_type tmp_2_17 = 0.0e0;
    real_type tmp_3_17 = 0.0e0;
    real_type tmp_0_18 = 0.0e0;
    real_type tmp_1_18 = 0.0e0;
    real_type tmp_2_18 = 0.0e0;
    real_type tmp_3_18 = 0.0e0;
    real_type tmp_0_19 = 0.0e0;
    real_type tmp_1_19 = 0.0e0;
    real_type tmp_2_19 = 0.0e0;
    real_type tmp_3_19 = 0.0e0;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(2, 0) = tmp_2_0;
    DuDxlxlp(3, 0) = tmp_3_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(2, 1) = tmp_2_1;
    DuDxlxlp(3, 1) = tmp_3_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(2, 2) = tmp_2_2;
    DuDxlxlp(3, 2) = tmp_3_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    DuDxlxlp(2, 3) = tmp_2_3;
    DuDxlxlp(3, 3) = tmp_3_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(1, 4) = tmp_1_4;
    DuDxlxlp(2, 4) = tmp_2_4;
    DuDxlxlp(3, 4) = tmp_3_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(1, 5) = tmp_1_5;
    DuDxlxlp(2, 5) = tmp_2_5;
    DuDxlxlp(3, 5) = tmp_3_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(1, 6) = tmp_1_6;
    DuDxlxlp(2, 6) = tmp_2_6;
    DuDxlxlp(3, 6) = tmp_3_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(1, 7) = tmp_1_7;
    DuDxlxlp(2, 7) = tmp_2_7;
    DuDxlxlp(3, 7) = tmp_3_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(1, 8) = tmp_1_8;
    DuDxlxlp(2, 8) = tmp_2_8;
    DuDxlxlp(3, 8) = tmp_3_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(1, 9) = tmp_1_9;
    DuDxlxlp(2, 9) = tmp_2_9;
    DuDxlxlp(3, 9) = tmp_3_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(1, 10) = tmp_1_10;
    DuDxlxlp(2, 10) = tmp_2_10;
    DuDxlxlp(3, 10) = tmp_3_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(1, 11) = tmp_1_11;
    DuDxlxlp(2, 11) = tmp_2_11;
    DuDxlxlp(3, 11) = tmp_3_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(1, 12) = tmp_1_12;
    DuDxlxlp(2, 12) = tmp_2_12;
    DuDxlxlp(3, 12) = tmp_3_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(1, 13) = tmp_1_13;
    DuDxlxlp(2, 13) = tmp_2_13;
    DuDxlxlp(3, 13) = tmp_3_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(1, 14) = tmp_1_14;
    DuDxlxlp(2, 14) = tmp_2_14;
    DuDxlxlp(3, 14) = tmp_3_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(1, 15) = tmp_1_15;
    DuDxlxlp(2, 15) = tmp_2_15;
    DuDxlxlp(3, 15) = tmp_3_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(1, 16) = tmp_1_16;
    DuDxlxlp(2, 16) = tmp_2_16;
    DuDxlxlp(3, 16) = tmp_3_16;
    DuDxlxlp(0, 17) = tmp_0_17;
    DuDxlxlp(1, 17) = tmp_1_17;
    DuDxlxlp(2, 17) = tmp_2_17;
    DuDxlxlp(3, 17) = tmp_3_17;
    DuDxlxlp(0, 18) = tmp_0_18;
    DuDxlxlp(1, 18) = tmp_1_18;
    DuDxlxlp(2, 18) = tmp_2_18;
    DuDxlxlp(3, 18) = tmp_3_18;
    DuDxlxlp(0, 19) = tmp_0_19;
    DuDxlxlp(1, 19) = tmp_1_19;
    DuDxlxlp(2, 19) = tmp_2_19;
    DuDxlxlp(3, 19) = tmp_3_19;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 80 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Farmer::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_x2];
    real_type t2   = X__[iX_x4];
    real_type t4   = LimitX2X4(0.12e0 - t1 - t2);
    real_type t5   = U__[iU_x1__o];
    real_type t6   = x1__oControl(t5, -0.1e-2, 100);
    real_type t7   = U__[iU_x2__o];
    real_type t8   = x2__oControl(t7, -0.1e-2, 100);
    real_type t9   = U__[iU_x3__o];
    real_type t10  = x3__oControl(t9, -0.1e-2, 100);
    real_type t11  = U__[iU_x4__o];
    real_type t12  = x4__oControl(t11, -0.1e-2, 100);
    real_type t20  = pow(V__[0] + 1.0 / ModelPars[iM_tau__1] * (X__[iX_x1] - t5), 2);
    real_type t27  = pow(V__[1] + 1.0 / ModelPars[iM_tau__2] * (t1 - t7), 2);
    real_type t29  = X__[iX_x3];
    real_type t35  = pow(V__[2] + 1.0 / ModelPars[iM_tau__3] * (t29 - t9), 2);
    real_type t42  = pow(V__[3] + 1.0 / ModelPars[iM_tau__4] * (-t29 + t2), 2);
    real_type t49  = pow(V__[4] + 1.0 / ModelPars[iM_tau__5] * (t2 - t11), 2);
    real_type result__ = t4 + t6 + t8 + t10 + t12 + t20 + t27 + t35 + t42 + t49;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DmDu_numEqns() const
  { return 4; }

  void
  Farmer::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = U__[iU_x1__o];
    real_type t2   = ALIAS_x1__oControl_D_1(t1, -0.1e-2, 100);
    real_type t7   = 1.0 / ModelPars[iM_tau__1];
    result__[ 0   ] = t2 - 2 * t7 * (V__[0] + t7 * (X__[iX_x1] - t1));
    real_type t12  = U__[iU_x2__o];
    real_type t13  = ALIAS_x2__oControl_D_1(t12, -0.1e-2, 100);
    real_type t18  = 1.0 / ModelPars[iM_tau__2];
    result__[ 1   ] = t13 - 2 * t18 * (V__[1] + t18 * (X__[iX_x2] - t12));
    real_type t23  = U__[iU_x3__o];
    real_type t24  = ALIAS_x3__oControl_D_1(t23, -0.1e-2, 100);
    real_type t29  = 1.0 / ModelPars[iM_tau__3];
    result__[ 2   ] = t24 - 2 * t29 * (V__[2] + t29 * (X__[iX_x3] - t23));
    real_type t34  = U__[iU_x4__o];
    real_type t35  = ALIAS_x4__oControl_D_1(t34, -0.1e-2, 100);
    real_type t40  = 1.0 / ModelPars[iM_tau__5];
    result__[ 3   ] = t35 - 2 * t40 * (V__[4] + t40 * (X__[iX_x4] - t34));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Farmer::DmDuu_numRows() const
  { return 4; }

  integer
  Farmer::DmDuu_numCols() const
  { return 4; }

  integer
  Farmer::DmDuu_nnz() const
  { return 4; }

  void
  Farmer::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ALIAS_x1__oControl_D_1_1(U__[iU_x1__o], -0.1e-2, 100);
    real_type t4   = ModelPars[iM_tau__1] * ModelPars[iM_tau__1];
    result__[ 0   ] = t2 + 2 / t4;
    real_type t8   = ALIAS_x2__oControl_D_1_1(U__[iU_x2__o], -0.1e-2, 100);
    real_type t10  = ModelPars[iM_tau__2] * ModelPars[iM_tau__2];
    result__[ 1   ] = t8 + 2 / t10;
    real_type t14  = ALIAS_x3__oControl_D_1_1(U__[iU_x3__o], -0.1e-2, 100);
    real_type t16  = ModelPars[iM_tau__3] * ModelPars[iM_tau__3];
    result__[ 2   ] = t14 + 2 / t16;
    real_type t20  = ALIAS_x4__oControl_D_1_1(U__[iU_x4__o], -0.1e-2, 100);
    real_type t22  = ModelPars[iM_tau__5] * ModelPars[iM_tau__5];
    result__[ 3   ] = t20 + 2 / t22;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: Farmer_Methods_controls.cc
