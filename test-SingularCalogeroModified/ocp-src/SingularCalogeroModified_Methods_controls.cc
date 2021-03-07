/*-----------------------------------------------------------------------*\
 |  file: SingularCalogeroModified_Methods_controls.cc                   |
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


#include "SingularCalogeroModified.hh"
#include "SingularCalogeroModified_Pars.hh"

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


namespace SingularCalogeroModifiedDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  SingularCalogeroModified::g_numEqns() const
  { return 1; }

  void
  SingularCalogeroModified::g_eval(
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
    real_type t4   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t9   = pow(ModelPars[iM_C] * t4 + X__[iX_x] - 1, 2);
    real_type t12  = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 0   ] = L__[iL_lambda2__xo] + t12 * (ModelPars[iM_epsilon] + t9);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularCalogeroModified::DgDxlp_numRows() const
  { return 1; }

  integer
  SingularCalogeroModified::DgDxlp_numCols() const
  { return 4; }

  integer
  SingularCalogeroModified::DgDxlp_nnz() const
  { return 2; }

  void
  SingularCalogeroModified::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularCalogeroModified::DgDxlp_sparse(
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
    real_type t2   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t9   = ALIAS_uControl_D_1(U__[iU_u], -1, 1);
    result__[ 0   ] = t9 * (2 * ModelPars[iM_C] * t2 + 2 * X__[iX_x] - 2);
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularCalogeroModified::DgDu_numRows() const
  { return 1; }

  integer
  SingularCalogeroModified::DgDu_numCols() const
  { return 1; }

  integer
  SingularCalogeroModified::DgDu_nnz() const
  { return 1; }

  void
  SingularCalogeroModified::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularCalogeroModified::DgDu_sparse(
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
    real_type t3   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t8   = pow(ModelPars[iM_C] * t3 + X__[iX_x] - 1, 2);
    real_type t11  = ALIAS_uControl_D_1_1(U__[iU_u], -1, 1);
    result__[ 0   ] = t11 * (ModelPars[iM_epsilon] + t8);
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
  SingularCalogeroModified::u_numEqns() const
  { return 1; }

  void
  SingularCalogeroModified::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[iX_x];
    real_type t3   = t2 * t2;
    real_type t5   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_C];
    real_type t7   = t6 * t5;
    real_type t11  = t6 * t6;
    real_type t12  = t5 * t5;
    U__[ iU_u ] = uControl.solve(-1.0 / (t3 + t2 * (2 * t7 - 2) + t12 * t11 - 2 * t7 + ModelPars[iM_epsilon] + 1) * L__[iL_lambda2__xo], -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularCalogeroModified::u_eval_analytic(
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
  SingularCalogeroModified::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = uControl.solve_rhs(-L__[iL_lambda2__xo] / (X__[iX_x] * X__[iX_x] + (2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] - 2) * X__[iX_x] + ModelPars[iM_C] * ModelPars[iM_C] * pow(Q__[iQ_zeta], 4) - 2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] + ModelPars[iM_epsilon] + 1), -1, 1) * L__[iL_lambda2__xo] * pow(X__[iX_x] * X__[iX_x] + (2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] - 2) * X__[iX_x] + ModelPars[iM_C] * ModelPars[iM_C] * pow(Q__[iQ_zeta], 4) - 2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] + ModelPars[iM_epsilon] + 1, -2) * (2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] + 2 * X__[iX_x] - 2);
    DuDxlp(0, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(0, 3) = -uControl.solve_rhs(-L__[iL_lambda2__xo] / (X__[iX_x] * X__[iX_x] + (2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] - 2) * X__[iX_x] + ModelPars[iM_C] * ModelPars[iM_C] * pow(Q__[iQ_zeta], 4) - 2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] + ModelPars[iM_epsilon] + 1), -1, 1) / (X__[iX_x] * X__[iX_x] + (2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] - 2) * X__[iX_x] + ModelPars[iM_C] * ModelPars[iM_C] * pow(Q__[iQ_zeta], 4) - 2 * Q__[iQ_zeta] * Q__[iQ_zeta] * ModelPars[iM_C] + ModelPars[iM_epsilon] + 1);
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularCalogeroModified::DuDxlp_full_analytic(
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
  SingularCalogeroModified::m_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t8   = pow(ModelPars[iM_C] * t3 + X__[iX_x] - 1, 2);
    real_type t10  = U__[iU_u];
    real_type t11  = uControl(t10, -1, 1);
    real_type t16  = pow(V__[0] - X__[iX_y], 2);
    real_type t19  = pow(V__[1] - t10, 2);
    real_type result__ = t11 * (ModelPars[iM_epsilon] + t8) + t16 + t19;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularCalogeroModified::DmDu_numEqns() const
  { return 1; }

  void
  SingularCalogeroModified::DmDu_eval(
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
    real_type t3   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t8   = pow(ModelPars[iM_C] * t3 + X__[iX_x] - 1, 2);
    real_type t10  = U__[iU_u];
    real_type t11  = ALIAS_uControl_D_1(t10, -1, 1);
    result__[ 0   ] = t11 * (ModelPars[iM_epsilon] + t8) - 2 * V__[1] + 2 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  SingularCalogeroModified::DmDuu_numRows() const
  { return 1; }

  integer
  SingularCalogeroModified::DmDuu_numCols() const
  { return 1; }

  integer
  SingularCalogeroModified::DmDuu_nnz() const
  { return 1; }

  void
  SingularCalogeroModified::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  SingularCalogeroModified::DmDuu_sparse(
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
    real_type t3   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t8   = pow(ModelPars[iM_C] * t3 + X__[iX_x] - 1, 2);
    real_type t11  = ALIAS_uControl_D_1_1(U__[iU_u], -1, 1);
    result__[ 0   ] = t11 * (ModelPars[iM_epsilon] + t8) + 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: SingularCalogeroModified_Methods_controls.cc
