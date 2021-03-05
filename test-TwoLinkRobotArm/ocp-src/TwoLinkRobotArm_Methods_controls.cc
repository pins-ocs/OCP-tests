/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods.cc                                     |
 |                                                                       |
 |  version: 1.0   date 5/3/2021                                         |
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


#include "TwoLinkRobotArm.hh"
#include "TwoLinkRobotArm_Pars.hh"

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


namespace TwoLinkRobotArmDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  TwoLinkRobotArm::g_numEqns() const
  { return 2; }

  void
  TwoLinkRobotArm::g_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * L__[iL_lambda1__xo];
    real_type t4   = X__[iX_x3];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t9   = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t6);
    real_type t13  = t2 * L__[iL_lambda2__xo];
    real_type t14  = cos(t4);
    real_type t19  = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    result__[ 0   ] = 4.0 / 3.0 * t9 * t3 - 3.0 / 2.0 * t9 * t14 * t13 + t19;
    real_type t20  = 3.0 / 2.0 * t14;
    real_type t28  = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    result__[ 1   ] = t9 * (-4.0 / 3.0 - t20) * t3 - t9 * (-7.0 / 3.0 - t20) * t13 + t28;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DgDxlp_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDxlp_numCols() const
  { return 9; }

  integer
  TwoLinkRobotArm::DgDxlp_nnz() const
  { return 8; }

  void
  TwoLinkRobotArm::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 4   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 5   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DgDxlp_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x3];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t8   = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t6;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = cos(t4);
    real_type t13  = t12 * t5 * t10;
    real_type t16  = L__[iL_lambda2__xo];
    real_type t17  = t2 * t16;
    real_type t18  = 1.0 / t8;
    real_type t19  = t18 * t5;
    real_type t21  = 3.0 / 2.0 * t19 * t17;
    real_type t22  = t12 * t12;
    result__[ 0   ] = -6 * t13 * t3 + t21 + 0.27e2 / 4.0 * t5 * t10 * t22 * t17;
    result__[ 1   ] = 4.0 / 3.0 * t18 * t2;
    result__[ 2   ] = -3.0 / 2.0 * t18 * t12 * t2;
    result__[ 3   ] = 4.0 / 3.0 * t18 * t1 - 3.0 / 2.0 * t18 * t12 * t16;
    real_type t38  = 3.0 / 2.0 * t12;
    real_type t39  = -4.0 / 3.0 - t38;
    real_type t43  = -7.0 / 3.0 - t38;
    result__[ 4   ] = 3.0 / 2.0 * t19 * t3 - 9.0 / 2.0 * t13 * t39 * t3 - t21 + 9.0 / 2.0 * t13 * t43 * t17;
    result__[ 5   ] = t18 * t39 * t2;
    result__[ 6   ] = -t18 * t43 * t2;
    result__[ 7   ] = t18 * t39 * t1 - t18 * t43 * t16;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 8, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DgDu_numRows() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDu_numCols() const
  { return 2; }

  integer
  TwoLinkRobotArm::DgDu_nnz() const
  { return 2; }

  void
  TwoLinkRobotArm::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DgDu_sparse(
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
    result__[ 0   ] = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
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
  TwoLinkRobotArm::u_numEqns() const
  { return 2; }

  void
  TwoLinkRobotArm::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = L__[iL_lambda2__xo];
    real_type t3   = X__[iX_x3];
    real_type t4   = cos(t3);
    real_type t7   = L__[iL_lambda1__xo];
    real_type t11  = sin(t3);
    real_type t12  = t11 * t11;
    real_type t15  = 1.0 / (81 * t12 + 31);
    U__[ iU_u1 ] = u1Control.solve(-6 * t15 * (-9 * t4 * t2 + 8 * t7) * t1, -1, 1);
    U__[ iU_u2 ] = u2Control.solve(54 * t15 * (t4 * (t7 - t2) + 8.0 / 9.0 * t7 - 0.14e2 / 9.0 * t2) * t1, -1, 1);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::u_eval_analytic(
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
  TwoLinkRobotArm::DuDxlp_full_analytic(
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
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(0, 2) = u1Control.solve_rhs(-6 * P__[iP_T] * (-9 * L__[iL_lambda2__xo] * cos(X__[iX_x3]) + 8 * L__[iL_lambda1__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * (-54 * P__[iP_T] * L__[iL_lambda2__xo] * sin(X__[iX_x3]) / (81 * pow(sin(X__[iX_x3]), 2) + 31) + 972 * P__[iP_T] * (-9 * L__[iL_lambda2__xo] * cos(X__[iX_x3]) + 8 * L__[iL_lambda1__xo]) * pow(81 * pow(sin(X__[iX_x3]), 2) + 31, -2) * sin(X__[iX_x3]) * cos(X__[iX_x3]));
    DuDxlp(1, 2) = u2Control.solve_rhs(54 * P__[iP_T] * ((L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * cos(X__[iX_x3]) + 8.0 / 9.0 * L__[iL_lambda1__xo] - 0.14e2 / 9.0 * L__[iL_lambda2__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * (-54 * P__[iP_T] * (L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * sin(X__[iX_x3]) / (81 * pow(sin(X__[iX_x3]), 2) + 31) - 8748 * P__[iP_T] * ((L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * cos(X__[iX_x3]) + 8.0 / 9.0 * L__[iL_lambda1__xo] - 0.14e2 / 9.0 * L__[iL_lambda2__xo]) * pow(81 * pow(sin(X__[iX_x3]), 2) + 31, -2) * sin(X__[iX_x3]) * cos(X__[iX_x3]));
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(0, 4) = -48 * u1Control.solve_rhs(-6 * P__[iP_T] * (-9 * L__[iL_lambda2__xo] * cos(X__[iX_x3]) + 8 * L__[iL_lambda1__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * P__[iP_T] / (81 * pow(sin(X__[iX_x3]), 2) + 31);
    DuDxlp(1, 4) = 54 * u2Control.solve_rhs(54 * P__[iP_T] * ((L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * cos(X__[iX_x3]) + 8.0 / 9.0 * L__[iL_lambda1__xo] - 0.14e2 / 9.0 * L__[iL_lambda2__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * P__[iP_T] * (cos(X__[iX_x3]) + 8.0 / 9.0) / (81 * pow(sin(X__[iX_x3]), 2) + 31);
    DuDxlp(0, 5) = 54 * u1Control.solve_rhs(-6 * P__[iP_T] * (-9 * L__[iL_lambda2__xo] * cos(X__[iX_x3]) + 8 * L__[iL_lambda1__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * P__[iP_T] * cos(X__[iX_x3]) / (81 * pow(sin(X__[iX_x3]), 2) + 31);
    DuDxlp(1, 5) = 54 * u2Control.solve_rhs(54 * P__[iP_T] * ((L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * cos(X__[iX_x3]) + 8.0 / 9.0 * L__[iL_lambda1__xo] - 0.14e2 / 9.0 * L__[iL_lambda2__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * P__[iP_T] * (-cos(X__[iX_x3]) - 0.14e2 / 9.0) / (81 * pow(sin(X__[iX_x3]), 2) + 31);
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
    DuDxlp(0, 8) = -6 * u1Control.solve_rhs(-6 * P__[iP_T] * (-9 * L__[iL_lambda2__xo] * cos(X__[iX_x3]) + 8 * L__[iL_lambda1__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * (-9 * L__[iL_lambda2__xo] * cos(X__[iX_x3]) + 8 * L__[iL_lambda1__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31);
    DuDxlp(1, 8) = 54 * u2Control.solve_rhs(54 * P__[iP_T] * ((L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * cos(X__[iX_x3]) + 8.0 / 9.0 * L__[iL_lambda1__xo] - 0.14e2 / 9.0 * L__[iL_lambda2__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31), -1, 1) * ((L__[iL_lambda1__xo] - L__[iL_lambda2__xo]) * cos(X__[iX_x3]) + 8.0 / 9.0 * L__[iL_lambda1__xo] - 0.14e2 / 9.0 * L__[iL_lambda2__xo]) / (81 * pow(sin(X__[iX_x3]), 2) + 31);
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoLinkRobotArm::DuDxlp_full_analytic(
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

}

// EOF: TwoLinkRobotArm_Methods.cc
