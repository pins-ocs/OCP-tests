/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_controls.cc                                 |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  HangGlider::g_numEqns() const
  { return 1; }

  void
  HangGlider::g_eval(
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
    real_type t2   = U__[iU_cL];
    real_type t7   = P__[iP_T];
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_vy];
    real_type t14  = v(t11, t12, t13);
    real_type t16  = 1.0 / t14 / ModelPars[iM_m];
    real_type t18  = t2 * ModelPars[iM_c1];
    real_type t19  = Dfun(t11, t12, t13);
    real_type t23  = Lfun(t11, t12, t13);
    real_type t24  = w(t11, t13);
    real_type t40  = ALIAS_cLControl_D_1(t2, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] + (-2 * t12 * t19 * t18 - t24 * t23) * t16 * t7 * L__[iL_lambda3__xo] + (-2 * t24 * t19 * t18 + t12 * t23) * t16 * t7 * L__[iL_lambda4__xo] + t40;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DgDxlp_numRows() const
  { return 1; }

  integer
  HangGlider::DgDxlp_numCols() const
  { return 9; }

  integer
  HangGlider::DgDxlp_nnz() const
  { return 6; }

  void
  HangGlider::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDxlp_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_c1] * U__[iU_cL];
    real_type t16  = Dfun(t7, t8, t9);
    real_type t20  = Lfun(t7, t8, t9);
    real_type t21  = w(t7, t9);
    real_type t23  = -2 * t8 * t16 * t15 - t21 * t20;
    real_type t24  = t23 * t12;
    real_type t25  = v_D_1(t7, t8, t9);
    real_type t28  = 1.0 / t10;
    real_type t29  = t28 * t5;
    real_type t30  = Dfun_D_1(t7, t8, t9);
    real_type t34  = Lfun_D_1(t7, t8, t9);
    real_type t36  = w_D_1(t7, t9);
    real_type t41  = L__[iL_lambda4__xo];
    real_type t42  = t2 * t41;
    real_type t43  = t5 * t42;
    real_type t48  = -2 * t21 * t16 * t15 + t8 * t20;
    real_type t49  = t48 * t12;
    result__[ 0   ] = -t25 * t24 * t6 + (-2 * t8 * t30 * t15 - t36 * t20 - t21 * t34) * t29 * t3 - t25 * t49 * t43 + (-2 * t36 * t16 * t15 - 2 * t21 * t30 * t15 + t8 * t34) * t29 * t42;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t71  = Lfun_D_2(t7, t8, t9);
    result__[ 1   ] = -t62 * t24 * t6 + (-2 * t8 * t65 * t15 - 2 * t16 * t15 - t21 * t71) * t29 * t3 - t62 * t49 * t43 + (-2 * t21 * t65 * t15 + t8 * t71 + t20) * t29 * t42;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t92  = Lfun_D_3(t7, t8, t9);
    real_type t94  = w_D_2(t7, t9);
    result__[ 2   ] = -t85 * t24 * t6 + (-2 * t8 * t88 * t15 - t94 * t20 - t21 * t92) * t29 * t3 - t85 * t49 * t43 + (-2 * t94 * t16 * t15 - 2 * t21 * t88 * t15 + t8 * t92) * t29 * t42;
    real_type t111 = t5 * t2;
    real_type t112 = t23 * t28;
    result__[ 3   ] = t112 * t111;
    real_type t113 = t48 * t28;
    result__[ 4   ] = t113 * t111;
    result__[ 5   ] = t112 * t5 * t1 + t113 * t5 * t41;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DgDu_numRows() const
  { return 1; }

  integer
  HangGlider::DgDu_numCols() const
  { return 1; }

  integer
  HangGlider::DgDu_nnz() const
  { return 1; }

  void
  HangGlider::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDu_sparse(
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
    real_type t4   = P__[iP_T];
    real_type t7   = 1.0 / ModelPars[iM_m];
    real_type t9   = X__[iX_x];
    real_type t10  = X__[iX_vx];
    real_type t11  = X__[iX_vy];
    real_type t12  = v(t9, t10, t11);
    real_type t15  = ModelPars[iM_c1] / t12;
    real_type t16  = Dfun(t9, t10, t11);
    real_type t24  = w(t9, t11);
    real_type t32  = ALIAS_cLControl_D_1_1(U__[iU_cL], ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    result__[ 0   ] = -2 * t10 * t16 * t15 * t7 * t4 * L__[iL_lambda3__xo] - 2 * t24 * t16 * t15 * t7 * t4 * L__[iL_lambda4__xo] + t32 + 2 * ModelPars[iM_W];
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
  HangGlider::u_numEqns() const
  { return 1; }

  void
  HangGlider::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_cL ] = 0;
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
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
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
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
  HangGlider::DuDxlp_full_analytic(
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
    DuDxlp(0, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(0, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(0, 8) = 0;
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
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
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  HangGlider::m_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = Tbound(t1);
    real_type t3   = U__[iU_cL];
    real_type t6   = cLControl(t3, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t7   = X__[iX_vx];
    real_type t11  = pow(-t7 * t1 + V__[0], 2);
    real_type t12  = X__[iX_vy];
    real_type t16  = pow(-t12 * t1 + V__[1], 2);
    real_type t20  = 1.0 / ModelPars[iM_m] * t1;
    real_type t21  = X__[iX_x];
    real_type t22  = v(t21, t7, t12);
    real_type t23  = 1.0 / t22;
    real_type t24  = t3 * t3;
    real_type t29  = Dfun(t21, t7, t12);
    real_type t30  = t29 * (ModelPars[iM_c1] * t24 + ModelPars[iM_c0]);
    real_type t32  = Lfun(t21, t7, t12);
    real_type t33  = t32 * t3;
    real_type t34  = w(t21, t12);
    real_type t40  = pow(V__[2] - (-t7 * t30 - t34 * t33) * t23 * t20, 2);
    real_type t50  = pow(V__[3] - (-t34 * t30 + t7 * t33) * t23 * t20 + ModelPars[iM_g] * t1, 2);
    real_type result__ = t2 + t6 + t11 + t16 + t40 + t50;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DmDu_numEqns() const
  { return 1; }

  void
  HangGlider::DmDu_eval(
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
    real_type t1   = U__[iU_cL];
    real_type t4   = ALIAS_cLControl_D_1(t1, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t6   = P__[iP_T];
    real_type t8   = 1.0 / ModelPars[iM_m];
    real_type t9   = t8 * t6;
    real_type t10  = X__[iX_x];
    real_type t11  = X__[iX_vx];
    real_type t12  = X__[iX_vy];
    real_type t13  = v(t10, t11, t12);
    real_type t14  = 1.0 / t13;
    real_type t15  = t1 * t1;
    real_type t16  = ModelPars[iM_c1];
    real_type t20  = Dfun(t10, t11, t12);
    real_type t21  = t20 * (t16 * t15 + ModelPars[iM_c0]);
    real_type t23  = Lfun(t10, t11, t12);
    real_type t24  = t23 * t1;
    real_type t25  = w(t10, t12);
    real_type t32  = t14 * t8;
    real_type t33  = t1 * t16;
    result__[ 0   ] = t4 - 2 * (-2 * t11 * t20 * t33 - t25 * t23) * t32 * t6 * (V__[2] - (-t11 * t21 - t25 * t24) * t14 * t9) - 2 * (-2 * t25 * t20 * t33 + t11 * t23) * t32 * t6 * (V__[3] - (t11 * t24 - t25 * t21) * t14 * t9 + ModelPars[iM_g] * t6);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DmDuu_numRows() const
  { return 1; }

  integer
  HangGlider::DmDuu_numCols() const
  { return 1; }

  integer
  HangGlider::DmDuu_nnz() const
  { return 1; }

  void
  HangGlider::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DmDuu_sparse(
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
    real_type t1   = U__[iU_cL];
    real_type t4   = ALIAS_cLControl_D_1_1(t1, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t5   = P__[iP_T];
    real_type t6   = t5 * t5;
    real_type t7   = ModelPars[iM_m];
    real_type t8   = t7 * t7;
    real_type t10  = 1.0 / t8 * t6;
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_vy];
    real_type t14  = v(t11, t12, t13);
    real_type t15  = t14 * t14;
    real_type t16  = 1.0 / t15;
    real_type t17  = ModelPars[iM_c1];
    real_type t18  = t1 * t17;
    real_type t19  = Dfun(t11, t12, t13);
    real_type t20  = t12 * t19;
    real_type t23  = Lfun(t11, t12, t13);
    real_type t24  = w(t11, t13);
    real_type t27  = pow(-2 * t20 * t18 - t24 * t23, 2);
    real_type t32  = 1.0 / t7;
    real_type t33  = t32 * t5;
    real_type t34  = 1.0 / t14;
    real_type t35  = t1 * t1;
    real_type t39  = t19 * (t35 * t17 + ModelPars[iM_c0]);
    real_type t41  = t23 * t1;
    real_type t49  = t17 * t34;
    real_type t53  = t24 * t19;
    real_type t58  = pow(t23 * t12 - 2 * t53 * t18, 2);
    result__[ 0   ] = t4 + 2 * t27 * t16 * t10 + 4 * t20 * t49 * t32 * t5 * (V__[2] - (-t12 * t39 - t24 * t41) * t34 * t33) + 2 * t58 * t16 * t10 + 4 * t53 * t49 * t32 * t5 * (V__[3] - (t12 * t41 - t24 * t39) * t34 * t33 + ModelPars[iM_g] * t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: HangGlider_Methods_controls.cc
