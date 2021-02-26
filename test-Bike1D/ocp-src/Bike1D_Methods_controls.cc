/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods.cc                                              |
 |                                                                       |
 |  version: 1.0   date 26/2/2021                                        |
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


#include "Bike1D.hh"
#include "Bike1D_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3(__t1, __t2, __t3) mufControl.D_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2(__t1, __t2, __t3) mufControl.D_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1(__t1, __t2, __t3) mufControl.D_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3_3(__t1, __t2, __t3) mufControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_3(__t1, __t2, __t3) mufControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_2(__t1, __t2, __t3) mufControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_3(__t1, __t2, __t3) mufControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_2(__t1, __t2, __t3) mufControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_1(__t1, __t2, __t3) mufControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3(__t1, __t2, __t3) murControl.D_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2(__t1, __t2, __t3) murControl.D_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1(__t1, __t2, __t3) murControl.D_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3_3(__t1, __t2, __t3) murControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_3(__t1, __t2, __t3) murControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_2(__t1, __t2, __t3) murControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_3(__t1, __t2, __t3) murControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_2(__t1, __t2, __t3) murControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_1(__t1, __t2, __t3) murControl.D_1_1( __t1, __t2, __t3)


namespace Bike1DDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  Bike1D::g_numEqns() const
  { return 2; }

  void
  Bike1D::g_eval(
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
    real_type t3   = L__[0] * ModelPars[1];
    real_type t4   = X__[0];
    real_type t5   = 1.0 / t4;
    real_type t8   = Tmax_normalized(t4);
    real_type t10  = clip(t8, 0, ModelPars[4]);
    real_type t11  = ALIAS_murControl_D_1(U__[0], ModelPars[5], t10);
    result__[ 0   ] = t11 * t5 + t3;
    real_type t15  = ALIAS_mufControl_D_1(U__[1], ModelPars[3], 0);
    result__[ 1   ] = t15 * t5 + t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::DgDxlp_numRows() const
  { return 2; }

  integer
  Bike1D::DgDxlp_numCols() const
  { return 2; }

  integer
  Bike1D::DgDxlp_nnz() const
  { return 4; }

  void
  Bike1D::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDxlp_sparse(
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
    real_type t1   = X__[0];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = U__[0];
    real_type t5   = ModelPars[5];
    real_type t6   = Tmax_normalized(t1);
    real_type t7   = ModelPars[4];
    real_type t8   = clip(t6, 0, t7);
    real_type t9   = ALIAS_murControl_D_1(t4, t5, t8);
    real_type t12  = ALIAS_murControl_D_1_3(t4, t5, t8);
    real_type t14  = ALIAS_clip_D_1(t6, 0, t7);
    real_type t15  = Tmax_normalized_D(t1);
    result__[ 0   ] = -t9 * t3 + t15 * t14 * t12 / t1;
    result__[ 1   ] = ModelPars[1];
    real_type t20  = ALIAS_mufControl_D_1(U__[1], ModelPars[3], 0);
    result__[ 2   ] = -t20 * t3;
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::DgDu_numRows() const
  { return 2; }

  integer
  Bike1D::DgDu_numCols() const
  { return 2; }

  integer
  Bike1D::DgDu_nnz() const
  { return 2; }

  void
  Bike1D::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDu_sparse(
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
    real_type t1   = X__[0];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[4]);
    real_type t8   = ALIAS_murControl_D_1_1(U__[0], ModelPars[5], t7);
    result__[ 0   ] = t8 * t2;
    real_type t11  = ALIAS_mufControl_D_1_1(U__[1], ModelPars[3], 0);
    result__[ 1   ] = t11 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
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
  Bike1D::u_numEqns() const
  { return 2; }

  void
  Bike1D::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t4   = X__[0];
    real_type t5   = t4 * ModelPars[1] * L__[0];
    real_type t7   = Tmax_normalized(t4);
    real_type t9   = clip(t7, 0, ModelPars[4]);
    U__[ iU_mur ] = murControl.solve(-t5, ModelPars[5], t9);
    U__[ iU_muf ] = mufControl.solve(-t5, ModelPars[3], 0);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[1];
    real_type L__[1];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
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
  Bike1D::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = -murControl.solve_rhs(-L__[0] * ModelPars[1] * X__[0], ModelPars[5], clip(Tmax_normalized(X__[0]), 0, ModelPars[4])) * L__[0] * ModelPars[1] + murControl.solve_b(-L__[0] * ModelPars[1] * X__[0], ModelPars[5], clip(Tmax_normalized(X__[0]), 0, ModelPars[4])) * ALIAS_clip_D_1(Tmax_normalized(X__[0]), 0, ModelPars[4]) * Tmax_normalized_D(X__[0]);
    DuDxlp(1, 0) = -mufControl.solve_rhs(-L__[0] * ModelPars[1] * X__[0], ModelPars[3], 0) * L__[0] * ModelPars[1];
    DuDxlp(0, 1) = -murControl.solve_rhs(-L__[0] * ModelPars[1] * X__[0], ModelPars[5], clip(Tmax_normalized(X__[0]), 0, ModelPars[4])) * ModelPars[1] * X__[0];
    DuDxlp(1, 1) = -mufControl.solve_rhs(-L__[0] * ModelPars[1] * X__[0], ModelPars[3], 0) * ModelPars[1] * X__[0];
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[1];
    real_type L__[1];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

}

// EOF: Bike1D_Methods.cc
