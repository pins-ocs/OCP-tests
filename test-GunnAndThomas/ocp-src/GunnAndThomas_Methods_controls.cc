/*-----------------------------------------------------------------------*\
 |  file: GunnAndThomas_Methods_controls.cc                              |
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


#include "GunnAndThomas.hh"
#include "GunnAndThomas_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace GunnAndThomasDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  GunnAndThomas::g_numEqns() const
  { return 1; }

  void
  GunnAndThomas::g_eval(
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
    real_type t2   = X__[iX_x2];
    real_type t4   = X__[iX_x1];
    real_type t12  = ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    result__[ 0   ] = (10 * t2 - t4) * L__[iL_lambda1__xo] + (t4 - 9 * t2) * L__[iL_lambda2__xo] + t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GunnAndThomas::DgDxlp_numRows() const
  { return 1; }

  integer
  GunnAndThomas::DgDxlp_numCols() const
  { return 4; }

  integer
  GunnAndThomas::DgDxlp_nnz() const
  { return 4; }

  void
  GunnAndThomas::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GunnAndThomas::DgDxlp_sparse(
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
    real_type t1   = L__[iL_lambda1__xo];
    real_type t2   = L__[iL_lambda2__xo];
    result__[ 0   ] = -t1 + t2;
    result__[ 1   ] = 10 * t1 - 9 * t2;
    real_type t5   = X__[iX_x2];
    real_type t7   = X__[iX_x1];
    result__[ 2   ] = 10 * t5 - t7;
    result__[ 3   ] = t7 - 9 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GunnAndThomas::DgDu_numRows() const
  { return 1; }

  integer
  GunnAndThomas::DgDu_numCols() const
  { return 1; }

  integer
  GunnAndThomas::DgDu_nnz() const
  { return 1; }

  void
  GunnAndThomas::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GunnAndThomas::DgDu_sparse(
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
    result__[ 0   ] = ALIAS_uControl_D_1_1(U__[iU_u], 0, 1);
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
  GunnAndThomas::u_numEqns() const
  { return 1; }

  void
  GunnAndThomas::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    U__[ iU_u ] = uControl.solve(L__[iL_lambda1__xo] * (t1 - 10 * t2) - (t1 - 9 * t2) * L__[iL_lambda2__xo], 0, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GunnAndThomas::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
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
  GunnAndThomas::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = uControl.solve_rhs((X__[iX_x1] - 10 * X__[iX_x2]) * L__[iL_lambda1__xo] - L__[iL_lambda2__xo] * (X__[iX_x1] - 9 * X__[iX_x2]), 0, 1) * (L__[iL_lambda1__xo] - L__[iL_lambda2__xo]);
    DuDxlp(0, 1) = uControl.solve_rhs((X__[iX_x1] - 10 * X__[iX_x2]) * L__[iL_lambda1__xo] - L__[iL_lambda2__xo] * (X__[iX_x1] - 9 * X__[iX_x2]), 0, 1) * (-10 * L__[iL_lambda1__xo] + 9 * L__[iL_lambda2__xo]);
    DuDxlp(0, 2) = uControl.solve_rhs((X__[iX_x1] - 10 * X__[iX_x2]) * L__[iL_lambda1__xo] - L__[iL_lambda2__xo] * (X__[iX_x1] - 9 * X__[iX_x2]), 0, 1) * (X__[iX_x1] - 10 * X__[iX_x2]);
    DuDxlp(0, 3) = uControl.solve_rhs((X__[iX_x1] - 10 * X__[iX_x2]) * L__[iL_lambda1__xo] - L__[iL_lambda2__xo] * (X__[iX_x1] - 9 * X__[iX_x2]), 0, 1) * (-X__[iX_x1] + 9 * X__[iX_x2]);
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GunnAndThomas::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[2];
    real_type L__[2];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  GunnAndThomas::m_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = U__[iU_u];
    real_type t2   = uControl(t1, 0, 1);
    real_type t4   = X__[iX_x2];
    real_type t7   = 10 * t4 - X__[iX_x1];
    real_type t10  = pow(-t7 * t1 + V__[0], 2);
    real_type t17  = pow(V__[1] + t7 * t1 + t4 * (1 - t1), 2);
    real_type result__ = t2 + t10 + t17;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GunnAndThomas::DmDu_numEqns() const
  { return 1; }

  void
  GunnAndThomas::DmDu_eval(
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
    real_type t1   = U__[iU_u];
    real_type t2   = ALIAS_uControl_D_1(t1, 0, 1);
    real_type t4   = X__[iX_x2];
    real_type t6   = X__[iX_x1];
    real_type t7   = 10 * t4 - t6;
    real_type t10  = -t7;
    result__[ 0   ] = t2 + 2 * t10 * (-t7 * t1 + V__[0]) + 2 * (-t6 + 9 * t4) * (V__[1] - t10 * t1 + t4 * (1 - t1));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  GunnAndThomas::DmDuu_numRows() const
  { return 1; }

  integer
  GunnAndThomas::DmDuu_numCols() const
  { return 1; }

  integer
  GunnAndThomas::DmDuu_nnz() const
  { return 1; }

  void
  GunnAndThomas::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GunnAndThomas::DmDuu_sparse(
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
    real_type t2   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 1);
    real_type t3   = X__[iX_x1];
    real_type t4   = X__[iX_x2];
    real_type t7   = pow(t3 - 10 * t4, 2);
    real_type t11  = pow(-t3 + 9 * t4, 2);
    result__[ 0   ] = t2 + 2 * t7 + 2 * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: GunnAndThomas_Methods_controls.cc
