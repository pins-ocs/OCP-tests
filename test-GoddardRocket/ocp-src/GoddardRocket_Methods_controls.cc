/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_controls.cc                              |
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


#include "GoddardRocket.hh"
#include "GoddardRocket_Pars.hh"

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
#define ALIAS_TSPositive_DD(__t1) TSPositive.DD( __t1)
#define ALIAS_TSPositive_D(__t1) TSPositive.D( __t1)
#define ALIAS_vPositive_DD(__t1) vPositive.DD( __t1)
#define ALIAS_vPositive_D(__t1) vPositive.D( __t1)
#define ALIAS_massPositive_DD(__t1) massPositive.DD( __t1)
#define ALIAS_massPositive_D(__t1) massPositive.D( __t1)
#define ALIAS_TControl_D_3(__t1, __t2, __t3) TControl.D_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2(__t1, __t2, __t3) TControl.D_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1(__t1, __t2, __t3) TControl.D_1( __t1, __t2, __t3)
#define ALIAS_TControl_D_3_3(__t1, __t2, __t3) TControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_3(__t1, __t2, __t3) TControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_2_2(__t1, __t2, __t3) TControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_3(__t1, __t2, __t3) TControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_2(__t1, __t2, __t3) TControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_TControl_D_1_1(__t1, __t2, __t3) TControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  GoddardRocket::g_numEqns() const
  { return 1; }

  void
  GoddardRocket::g_eval(
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
    real_type t2   = P__[iP_TimeSize];
    real_type t14  = ALIAS_TControl_D_1(U__[iU_T], 0, ModelPars[iM_Tmax]);
    result__[ 0   ] = 1.0 / X__[iX_m] * t2 * L__[iL_lambda2__xo] - 1.0 / ModelPars[iM_c] * t2 * L__[iL_lambda3__xo] + t14;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DgDxlp_numRows() const
  { return 1; }

  integer
  GoddardRocket::DgDxlp_numCols() const
  { return 7; }

  integer
  GoddardRocket::DgDxlp_nnz() const
  { return 4; }

  void
  GoddardRocket::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DgDxlp_sparse(
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
    real_type t1   = L__[iL_lambda2__xo];
    real_type t2   = P__[iP_TimeSize];
    real_type t4   = X__[iX_m];
    real_type t5   = t4 * t4;
    result__[ 0   ] = -1.0 / t5 * t2 * t1;
    real_type t8   = 1.0 / t4;
    result__[ 1   ] = t8 * t2;
    real_type t10  = 1.0 / ModelPars[iM_c];
    result__[ 2   ] = -t10 * t2;
    result__[ 3   ] = t8 * t1 - t10 * L__[iL_lambda3__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DgDu_numRows() const
  { return 1; }

  integer
  GoddardRocket::DgDu_numCols() const
  { return 1; }

  integer
  GoddardRocket::DgDu_nnz() const
  { return 1; }

  void
  GoddardRocket::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DgDu_sparse(
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
    result__[ 0   ] = ALIAS_TControl_D_1_1(U__[iU_T], 0, ModelPars[iM_Tmax]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 1, i_segment );
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
  GoddardRocket::u_numEqns() const
  { return 1; }

  void
  GoddardRocket::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = ModelPars[iM_c];
    real_type t6   = X__[iX_m];
    U__[ iU_T ] = TControl.solve(-1.0 / t3 / t6 * (t3 * L__[iL_lambda2__xo] - t6 * L__[iL_lambda3__xo]) * P__[iP_TimeSize], 0, ModelPars[iM_Tmax]);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[3];
    real_type L__[3];
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
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
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
  GoddardRocket::DuDxlp_full_analytic(
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
    DuDxlp(0, 1) = 0;
    DuDxlp(0, 2) = TControl.solve_rhs(-P__[iP_TimeSize] * (L__[iL_lambda2__xo] * ModelPars[iM_c] - L__[iL_lambda3__xo] * X__[iX_m]) / X__[iX_m] / ModelPars[iM_c], 0, ModelPars[iM_Tmax]) * (P__[iP_TimeSize] * L__[iL_lambda3__xo] / X__[iX_m] / ModelPars[iM_c] + P__[iP_TimeSize] * (L__[iL_lambda2__xo] * ModelPars[iM_c] - L__[iL_lambda3__xo] * X__[iX_m]) * pow(X__[iX_m], -2) / ModelPars[iM_c]);
    DuDxlp(0, 3) = 0;
    DuDxlp(0, 4) = -TControl.solve_rhs(-P__[iP_TimeSize] * (L__[iL_lambda2__xo] * ModelPars[iM_c] - L__[iL_lambda3__xo] * X__[iX_m]) / X__[iX_m] / ModelPars[iM_c], 0, ModelPars[iM_Tmax]) * P__[iP_TimeSize] / X__[iX_m];
    DuDxlp(0, 5) = TControl.solve_rhs(-P__[iP_TimeSize] * (L__[iL_lambda2__xo] * ModelPars[iM_c] - L__[iL_lambda3__xo] * X__[iX_m]) / X__[iX_m] / ModelPars[iM_c], 0, ModelPars[iM_Tmax]) * P__[iP_TimeSize] / ModelPars[iM_c];
    DuDxlp(0, 6) = -TControl.solve_rhs(-P__[iP_TimeSize] * (L__[iL_lambda2__xo] * ModelPars[iM_c] - L__[iL_lambda3__xo] * X__[iX_m]) / X__[iX_m] / ModelPars[iM_c], 0, ModelPars[iM_Tmax]) * (L__[iL_lambda2__xo] * ModelPars[iM_c] - L__[iL_lambda3__xo] * X__[iX_m]) / X__[iX_m] / ModelPars[iM_c];
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[3];
    real_type L__[3];
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
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  GoddardRocket::m_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_m];
    real_type t2   = massPositive(t1);
    real_type t3   = P__[iP_TimeSize];
    real_type t4   = TSPositive(t3);
    real_type t5   = X__[iX_v];
    real_type t6   = vPositive(t5);
    real_type t7   = U__[iU_T];
    real_type t9   = TControl(t7, 0, ModelPars[iM_Tmax]);
    real_type t13  = pow(-t5 * t3 + V__[0], 2);
    real_type t15  = X__[iX_h];
    real_type t16  = DD(t15, t5);
    real_type t20  = gg(t15);
    real_type t24  = pow(V__[1] - (1.0 / t1 * (t7 - t16) - t20) * t3, 2);
    real_type t31  = pow(V__[2] + 1.0 / ModelPars[iM_c] * t7 * t3, 2);
    real_type result__ = t2 + t4 + t6 + t9 + t13 + t24 + t31;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DmDu_numEqns() const
  { return 1; }

  void
  GoddardRocket::DmDu_eval(
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
    real_type t1   = U__[iU_T];
    real_type t3   = ALIAS_TControl_D_1(t1, 0, ModelPars[iM_Tmax]);
    real_type t5   = P__[iP_TimeSize];
    real_type t6   = X__[iX_h];
    real_type t8   = DD(t6, X__[iX_v]);
    real_type t11  = 1.0 / X__[iX_m];
    real_type t13  = gg(t6);
    real_type t23  = 1.0 / ModelPars[iM_c];
    result__[ 0   ] = t3 - 2 * t11 * t5 * (V__[1] - (t11 * (t1 - t8) - t13) * t5) + 2 * t23 * t5 * (t23 * t1 * t5 + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GoddardRocket::DmDuu_numRows() const
  { return 1; }

  integer
  GoddardRocket::DmDuu_numCols() const
  { return 1; }

  integer
  GoddardRocket::DmDuu_nnz() const
  { return 1; }

  void
  GoddardRocket::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DmDuu_sparse(
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
    real_type t3   = ALIAS_TControl_D_1_1(U__[iU_T], 0, ModelPars[iM_Tmax]);
    real_type t5   = P__[iP_TimeSize] * P__[iP_TimeSize];
    real_type t7   = X__[iX_m] * X__[iX_m];
    real_type t12  = ModelPars[iM_c] * ModelPars[iM_c];
    result__[ 0   ] = t3 + 2 / t7 * t5 + 2 / t12 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: GoddardRocket_Methods_controls.cc
