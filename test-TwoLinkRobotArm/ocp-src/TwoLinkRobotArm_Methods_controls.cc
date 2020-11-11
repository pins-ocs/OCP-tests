/*-----------------------------------------------------------------------*\
 |  file: TwoLinkRobotArm_Methods.cc                                     |
 |                                                                       |
 |  version: 1.0   date 12/11/2020                                       |
 |                                                                       |
 |  Copyright (C) 2020                                                   |
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
using Mechatronix::real_type;
using Mechatronix::integer;
using Mechatronix::ostream_type;

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
    real_type t2   = P__[0];
    real_type t3   = t2 * L__[0];
    real_type t4   = X__[2];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t9   = 1.0 / (0.31e2 / 0.36e2 + 9.0 / 4.0 * t6);
    real_type t13  = t2 * L__[1];
    real_type t14  = cos(t4);
    real_type t19  = ALIAS_u1Control_D_1(U__[0], -1, 1);
    result__[ 0   ] = 4.0 / 3.0 * t9 * t3 - 3.0 / 2.0 * t9 * t14 * t13 + t19;
    real_type t20  = 3.0 / 2.0 * t14;
    real_type t28  = ALIAS_u2Control_D_1(U__[1], -1, 1);
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
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 2   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 4   ;
    iIndex[ 2  ] = 0   ; jIndex[ 2  ] = 5   ;
    iIndex[ 3  ] = 0   ; jIndex[ 3  ] = 8   ;
    iIndex[ 4  ] = 1   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 1   ; jIndex[ 5  ] = 4   ;
    iIndex[ 6  ] = 1   ; jIndex[ 6  ] = 5   ;
    iIndex[ 7  ] = 1   ; jIndex[ 7  ] = 8   ;
  }

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
    real_type t1   = L__[0];
    real_type t2   = P__[0];
    real_type t3   = t2 * t1;
    real_type t4   = X__[2];
    real_type t5   = sin(t4);
    real_type t6   = t5 * t5;
    real_type t8   = 0.31e2 / 0.36e2 + 9.0 / 4.0 * t6;
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t12  = cos(t4);
    real_type t13  = t12 * t5 * t10;
    real_type t16  = L__[1];
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
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
  }

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
    result__[ 0   ] = ALIAS_u1Control_D_1_1(U__[0], -1, 1);
    result__[ 1   ] = ALIAS_u2Control_D_1_1(U__[1], -1, 1);
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
    real_type t1   = P__[0];
    real_type t2   = L__[1];
    real_type t3   = X__[2];
    real_type t4   = cos(t3);
    real_type t7   = L__[0];
    real_type t11  = sin(t3);
    real_type t12  = t11 * t11;
    real_type t15  = 1.0 / (81 * t12 + 31);
    U__[ iU_u1 ] = u1Control.solve(-6 * t15 * (-9 * t4 * t2 + 8 * t7) * t1, -1, 1);
    U__[ iU_u2 ] = u2Control.solve(54 * t15 * t1 * (t4 * (t7 - t2) + 8.0 / 9.0 * t7 - 0.14e2 / 9.0 * t2), -1, 1);
  }

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
    DuDxlp(0, 2) = u1Control.solve_rhs(-6 * P__[0] * (-9 * L__[1] * cos(X__[2]) + 8 * L__[0]) / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * (-54 * P__[0] * L__[1] * sin(X__[2]) / (81 * pow(sin(X__[2]), 2) + 31) + 972 * P__[0] * (-9 * L__[1] * cos(X__[2]) + 8 * L__[0]) * pow(81 * pow(sin(X__[2]), 2) + 31, -2) * sin(X__[2]) * cos(X__[2]));
    DuDxlp(1, 2) = u2Control.solve_rhs(54 * ((L__[0] - L__[1]) * cos(X__[2]) + 8.0 / 9.0 * L__[0] - 0.14e2 / 9.0 * L__[1]) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * (-54 * (L__[0] - L__[1]) * sin(X__[2]) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31) - 8748 * ((L__[0] - L__[1]) * cos(X__[2]) + 8.0 / 9.0 * L__[0] - 0.14e2 / 9.0 * L__[1]) * P__[0] * pow(81 * pow(sin(X__[2]), 2) + 31, -2) * sin(X__[2]) * cos(X__[2]));
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(0, 4) = -48 * u1Control.solve_rhs(-6 * P__[0] * (-9 * L__[1] * cos(X__[2]) + 8 * L__[0]) / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31);
    DuDxlp(1, 4) = 54 * u2Control.solve_rhs(54 * ((L__[0] - L__[1]) * cos(X__[2]) + 8.0 / 9.0 * L__[0] - 0.14e2 / 9.0 * L__[1]) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * (cos(X__[2]) + 8.0 / 9.0) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31);
    DuDxlp(0, 5) = 54 * u1Control.solve_rhs(-6 * P__[0] * (-9 * L__[1] * cos(X__[2]) + 8 * L__[0]) / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * P__[0] * cos(X__[2]) / (81 * pow(sin(X__[2]), 2) + 31);
    DuDxlp(1, 5) = 54 * u2Control.solve_rhs(54 * ((L__[0] - L__[1]) * cos(X__[2]) + 8.0 / 9.0 * L__[0] - 0.14e2 / 9.0 * L__[1]) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * (-cos(X__[2]) - 0.14e2 / 9.0) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31);
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
    DuDxlp(0, 8) = -6 * u1Control.solve_rhs(-6 * P__[0] * (-9 * L__[1] * cos(X__[2]) + 8 * L__[0]) / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * (-9 * L__[1] * cos(X__[2]) + 8 * L__[0]) / (81 * pow(sin(X__[2]), 2) + 31);
    DuDxlp(1, 8) = 54 * u2Control.solve_rhs(54 * ((L__[0] - L__[1]) * cos(X__[2]) + 8.0 / 9.0 * L__[0] - 0.14e2 / 9.0 * L__[1]) * P__[0] / (81 * pow(sin(X__[2]), 2) + 31), -1, 1) * ((L__[0] - L__[1]) * cos(X__[2]) + 8.0 / 9.0 * L__[0] - 0.14e2 / 9.0 * L__[1]) / (81 * pow(sin(X__[2]), 2) + 31);
  }

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

  /*\
   |   ___       ___      _                               _
   |  |   \ _  _|   \__ _| |_ __   _ _ _  _ _ __  ___ _ _(_)__
   |  | |) | || | |) \ \ / | '_ \ | ' \ || | '  \/ -_) '_| / _|
   |  |___/ \_,_|___//_\_\_| .__/ |_||_\_,_|_|_|_\___|_| |_\__|
   |                       |_|
  \*/

  bool
  TwoLinkRobotArm::DuDxlp_full_numeric(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    static integer DgDu_I[ 2 ], DgDu_J[ 2 ];
    static integer DgDxlp_I[ 8 ], DgDxlp_J[ 8 ];
    static bool    computed_pattern = false;
    if ( !computed_pattern ) {
      this->DgDu_pattern( DgDu_I, DgDu_J );
      this->DgDxlp_pattern( DgDxlp_I, DgDxlp_J );
      computed_pattern = true;
    }
    real_type DgDu_V[ 2 ], DgDxlp_V[ 8 ];
    this->DgDu_sparse( NODE__, U__, P__, DgDu_V );
    this->DgDxlp_sparse( NODE__, U__, P__, DgDxlp_V );

    integer   ipiv[ 2 ];
    real_type DgDu_storage[ 4 ];
    MatrixWrapper<real_type> DgDu( DgDu_storage, 2, 2, 2 );
    DgDu.zero_fill();
    DuDxlp.zero_fill();

    // fill DgDu
    DgDu( DgDu_I[ 0 ], DgDu_J[ 0 ] ) = DgDu_V[0];
    DgDu( DgDu_I[ 1 ], DgDu_J[ 1 ] ) = DgDu_V[1];
    // fill DgDxlp
    DuDxlp( DgDxlp_I[ 0 ], DgDxlp_J[ 0] ) = -DgDxlp_V[0];
    DuDxlp( DgDxlp_I[ 1 ], DgDxlp_J[ 1] ) = -DgDxlp_V[1];
    DuDxlp( DgDxlp_I[ 2 ], DgDxlp_J[ 2] ) = -DgDxlp_V[2];
    DuDxlp( DgDxlp_I[ 3 ], DgDxlp_J[ 3] ) = -DgDxlp_V[3];
    DuDxlp( DgDxlp_I[ 4 ], DgDxlp_J[ 4] ) = -DgDxlp_V[4];
    DuDxlp( DgDxlp_I[ 5 ], DgDxlp_J[ 5] ) = -DgDxlp_V[5];
    DuDxlp( DgDxlp_I[ 6 ], DgDxlp_J[ 6] ) = -DgDxlp_V[6];
    DuDxlp( DgDxlp_I[ 7 ], DgDxlp_J[ 7] ) = -DgDxlp_V[7];
    integer info = alglin::gesv( 2, 9, DgDu.data(), 2, ipiv, DuDxlp.data(), 2 );
    return info == 0;
  }

  bool
  TwoLinkRobotArm::DuDxlp_full_numeric(
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
    return this->DuDxlp_full_numeric( NODE__, P__, U__, DuDxlp );
  }

  /*\
   |   ____                                  _   _     _       _
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_| |   (_)_ __ | | __
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| |   | | '_ \| |/ /
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_| |___| | | | |   <
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|_|_| |_|_|\_\
   |              |___/
  \*/

  integer
  TwoLinkRobotArm::segmentLink_numEqns() const
  { return 0; }

  void
  TwoLinkRobotArm::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  TwoLinkRobotArm::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  TwoLinkRobotArm::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  TwoLinkRobotArm::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  void
  TwoLinkRobotArm::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
   UTILS_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  TwoLinkRobotArm::jump_numEqns() const
  { return 8; }

  void
  TwoLinkRobotArm::jump_eval(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = XR__[0] - XL__[0];
    result__[ 1   ] = XR__[1] - XL__[1];
    result__[ 2   ] = XR__[2] - XL__[2];
    result__[ 3   ] = XR__[3] - XL__[3];
    result__[ 4   ] = LR__[0] - LL__[0];
    result__[ 5   ] = LR__[1] - LL__[1];
    result__[ 6   ] = LR__[2] - LL__[2];
    result__[ 7   ] = LR__[3] - LL__[3];
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "jump_eval", 8, i_segment_left, i_segment_right );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  TwoLinkRobotArm::DjumpDxlp_numRows() const
  { return 8; }

  integer
  TwoLinkRobotArm::DjumpDxlp_numCols() const
  { return 17; }

  integer
  TwoLinkRobotArm::DjumpDxlp_nnz() const
  { return 16; }

  void
  TwoLinkRobotArm::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 8   ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 9   ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 10  ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 11  ;
    iIndex[ 8  ] = 4   ; jIndex[ 8  ] = 4   ;
    iIndex[ 9  ] = 4   ; jIndex[ 9  ] = 12  ;
    iIndex[ 10 ] = 5   ; jIndex[ 10 ] = 5   ;
    iIndex[ 11 ] = 5   ; jIndex[ 11 ] = 13  ;
    iIndex[ 12 ] = 6   ; jIndex[ 12 ] = 6   ;
    iIndex[ 13 ] = 6   ; jIndex[ 13 ] = 14  ;
    iIndex[ 14 ] = 7   ; jIndex[ 14 ] = 7   ;
    iIndex[ 15 ] = 7   ; jIndex[ 15 ] = 15  ;
  }

  void
  TwoLinkRobotArm::DjumpDxlp_sparse(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment_left  = LEFT__.i_segment;
    real_type const * QL__  = LEFT__.q;
    real_type const * XL__  = LEFT__.x;
    real_type const * LL__  = LEFT__.lambda;
    integer i_segment_right = RIGHT__.i_segment;
    real_type const * QR__  = RIGHT__.q;
    real_type const * XR__  = RIGHT__.x;
    real_type const * LR__  = RIGHT__.lambda;
    MeshStd::SegmentClass const & segmentLeft  = pMesh->getSegmentByIndex(i_segment_left);
    MeshStd::SegmentClass const & segmentRight = pMesh->getSegmentByIndex(i_segment_right);
    result__[ 0   ] = -1;
    result__[ 1   ] = 1;
    result__[ 2   ] = -1;
    result__[ 3   ] = 1;
    result__[ 4   ] = -1;
    result__[ 5   ] = 1;
    result__[ 6   ] = -1;
    result__[ 7   ] = 1;
    result__[ 8   ] = -1;
    result__[ 9   ] = 1;
    result__[ 10  ] = -1;
    result__[ 11  ] = 1;
    result__[ 12  ] = -1;
    result__[ 13  ] = 1;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment2( result__, "DjumpDxlp_sparse", 16, i_segment_left, i_segment_right );
  }

}

// EOF: TwoLinkRobotArm_Methods.cc
