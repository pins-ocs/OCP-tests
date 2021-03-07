/*-----------------------------------------------------------------------*\
 |  file: Farmer_Methods_controls.cc                                     |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = U__[iU_x1__o];
    real_type t11  = ALIAS_x1__oControl_D_1(t3, -0.1e-2, 100);
    result__[ 0   ] = 2 * (-X__[iX_x1] + t3) * ModelPars[iM_wJ1] + L__[iL_lambda1__xo] / ModelPars[iM_tau__1] + t11;
    real_type t14  = U__[iU_x2__o];
    real_type t22  = ALIAS_x2__oControl_D_1(t14, -0.1e-2, 100);
    result__[ 1   ] = 2 * (-X__[iX_x2] + t14) * ModelPars[iM_wJ2] + L__[iL_lambda2__xo] / ModelPars[iM_tau__2] + t22;
    real_type t25  = U__[iU_x3__o];
    real_type t33  = ALIAS_x3__oControl_D_1(t25, -0.1e-2, 100);
    result__[ 2   ] = 2 * (-X__[iX_x3] + t25) * ModelPars[iM_wJ3] + L__[iL_lambda3__xo] / ModelPars[iM_tau__3] + t33;
    real_type t36  = U__[iU_x4__o];
    real_type t44  = ALIAS_x4__oControl_D_1(t36, -0.1e-2, 100);
    result__[ 3   ] = 2 * (-X__[iX_x4] + t36) * ModelPars[iM_wJ4] + L__[iL_lambda5__xo] / ModelPars[iM_tau__5] + t44;
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
    NodeType2 const    & NODE__,
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
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t4   = ALIAS_x1__oControl_D_1_1(U__[iU_x1__o], -0.1e-2, 100);
    result__[ 0   ] = 2 * ModelPars[iM_wJ1] + t4;
    real_type t8   = ALIAS_x2__oControl_D_1_1(U__[iU_x2__o], -0.1e-2, 100);
    result__[ 1   ] = 2 * ModelPars[iM_wJ2] + t8;
    real_type t12  = ALIAS_x3__oControl_D_1_1(U__[iU_x3__o], -0.1e-2, 100);
    result__[ 2   ] = 2 * ModelPars[iM_wJ3] + t12;
    real_type t16  = ALIAS_x4__oControl_D_1_1(U__[iU_x4__o], -0.1e-2, 100);
    result__[ 3   ] = 2 * ModelPars[iM_wJ4] + t16;
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
  integer
  Farmer::u_numEqns() const
  { return 4; }

  void
  Farmer::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_x1__o ] = 0;
    U__[ iU_x2__o ] = 0;
    U__[ iU_x3__o ] = 0;
    U__[ iU_x4__o ] = 0;
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 4 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[5];
    real_type L__[5];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    this->u_eval_analytic( NODE__, P__, U__ );
  }

  /*\
   |   ___       ___      _                       _      _   _
   |  |   \ _  _|   \__ _| |_ __   __ _ _ _  __ _| |_  _| |_(_)__
   |  | |) | || | |) \ \ / | '_ \ / _` | ' \/ _` | | || |  _| / _|
   |  |___/ \_,_|___//_\_\_| .__/ \__,_|_||_\__,_|_|\_, |\__|_\__|
   |                       |_|                      |__/
  \*/
  void
  Farmer::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = 0;
    DuDxlp(1, 0) = 0;
    DuDxlp(2, 0) = 0;
    DuDxlp(3, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(2, 1) = 0;
    DuDxlp(3, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(1, 2) = 0;
    DuDxlp(2, 2) = 0;
    DuDxlp(3, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(2, 3) = 0;
    DuDxlp(3, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(2, 4) = 0;
    DuDxlp(3, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(2, 5) = 0;
    DuDxlp(3, 5) = 0;
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(2, 6) = 0;
    DuDxlp(3, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
    DuDxlp(2, 7) = 0;
    DuDxlp(3, 7) = 0;
    DuDxlp(0, 8) = 0;
    DuDxlp(1, 8) = 0;
    DuDxlp(2, 8) = 0;
    DuDxlp(3, 8) = 0;
    DuDxlp(0, 9) = 0;
    DuDxlp(1, 9) = 0;
    DuDxlp(2, 9) = 0;
    DuDxlp(3, 9) = 0;
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 4 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Farmer::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[5];
    real_type L__[5];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    X__[4] = (LEFT__.x[4]+RIGHT__.x[4])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Farmer::m_eval(
    NodeType const     & NODE__,
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
    NodeType const     & NODE__,
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
    NodeType const     & NODE__,
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
