/*-----------------------------------------------------------------------*\
 |  file: RobotArm_Methods.cc                                            |
 |                                                                       |
 |  version: 1.0   date 21/7/2020                                        |
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


#include "RobotArm.hh"
#include "RobotArm_Pars.hh"

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
#define ALIAS_u_phiControl_D_3(__t1, __t2, __t3) u_phiControl.D_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_2(__t1, __t2, __t3) u_phiControl.D_2( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1(__t1, __t2, __t3) u_phiControl.D_1( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_3_3(__t1, __t2, __t3) u_phiControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_2_3(__t1, __t2, __t3) u_phiControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_2_2(__t1, __t2, __t3) u_phiControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1_3(__t1, __t2, __t3) u_phiControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1_2(__t1, __t2, __t3) u_phiControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_u_phiControl_D_1_1(__t1, __t2, __t3) u_phiControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_3(__t1, __t2, __t3) u_thetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_2(__t1, __t2, __t3) u_thetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1(__t1, __t2, __t3) u_thetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_3_3(__t1, __t2, __t3) u_thetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_2_3(__t1, __t2, __t3) u_thetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_2_2(__t1, __t2, __t3) u_thetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1_3(__t1, __t2, __t3) u_thetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1_2(__t1, __t2, __t3) u_thetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_u_thetaControl_D_1_1(__t1, __t2, __t3) u_thetaControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_3(__t1, __t2, __t3) u_rhoControl.D_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_2(__t1, __t2, __t3) u_rhoControl.D_2( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1(__t1, __t2, __t3) u_rhoControl.D_1( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_3_3(__t1, __t2, __t3) u_rhoControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_2_3(__t1, __t2, __t3) u_rhoControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_2_2(__t1, __t2, __t3) u_rhoControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1_3(__t1, __t2, __t3) u_rhoControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1_2(__t1, __t2, __t3) u_rhoControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_u_rhoControl_D_1_1(__t1, __t2, __t3) u_rhoControl.D_1_1( __t1, __t2, __t3)


namespace RobotArmDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  RobotArm::g_numEqns() const
  { return 3; }

  void
  RobotArm::g_eval(
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
    real_type t5   = ALIAS_u_rhoControl_D_1(U__[0], -1, 1);
    result__[ 0   ] = t5 * t2 + t2 * L__[0];
    real_type t10  = ALIAS_u_thetaControl_D_1(U__[1], -1, 1);
    result__[ 1   ] = t10 * t2 + t2 * L__[1];
    real_type t15  = ALIAS_u_phiControl_D_1(U__[2], -1, 1);
    result__[ 2   ] = t15 * t2 + t2 * L__[2];
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"g_eval",3);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DgDxlp_numRows() const
  { return 3; }

  integer
  RobotArm::DgDxlp_numCols() const
  { return 13; }

  integer
  RobotArm::DgDxlp_nnz() const
  { return 6; }

  void
  RobotArm::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 6   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 12  ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 7   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 12  ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 8   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 12  ;
  }

  void
  RobotArm::DgDxlp_sparse(
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
    result__[ 0   ] = P__[0];
    real_type t3   = ALIAS_u_rhoControl_D_1(U__[0], -1, 1);
    result__[ 1   ] = L__[0] + t3;
    result__[ 2   ] = result__[0];
    real_type t6   = ALIAS_u_thetaControl_D_1(U__[1], -1, 1);
    result__[ 3   ] = L__[1] + t6;
    result__[ 4   ] = result__[2];
    real_type t9   = ALIAS_u_phiControl_D_1(U__[2], -1, 1);
    result__[ 5   ] = L__[2] + t9;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDxlp_sparse",6);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DgDu_numRows() const
  { return 3; }

  integer
  RobotArm::DgDu_numCols() const
  { return 3; }

  integer
  RobotArm::DgDu_nnz() const
  { return 3; }

  void
  RobotArm::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 1   ; jIndex[ 1  ] = 1   ;
    iIndex[ 2  ] = 2   ; jIndex[ 2  ] = 2   ;
  }

  void
  RobotArm::DgDu_sparse(
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
    real_type t1   = P__[0];
    real_type t3   = ALIAS_u_rhoControl_D_1_1(U__[0], -1, 1);
    result__[ 0   ] = t3 * t1;
    real_type t5   = ALIAS_u_thetaControl_D_1_1(U__[1], -1, 1);
    result__[ 1   ] = t5 * t1;
    real_type t7   = ALIAS_u_phiControl_D_1_1(U__[2], -1, 1);
    result__[ 2   ] = t7 * t1;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DgDu_sparse",3);
    #endif
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
  RobotArm::u_numEqns() const
  { return 3; }

  void
  RobotArm::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_u_rho   ] = u_rhoControl.solve(-L__[0], -1, 1);
    U__[ iU_u_theta ] = u_thetaControl.solve(-L__[1], -1, 1);
    U__[ iU_u_phi   ] = u_phiControl.solve(-L__[2], -1, 1);
  }

  void
  RobotArm::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
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
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
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
  RobotArm::DuDxlp_full_analytic(
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
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(2, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(1, 2) = 0;
    DuDxlp(2, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(2, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(2, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(2, 5) = 0;
    DuDxlp(0, 6) = -u_rhoControl.solve_rhs(-L__[0], -1, 1);
    DuDxlp(1, 6) = 0;
    DuDxlp(2, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = -u_thetaControl.solve_rhs(-L__[1], -1, 1);
    DuDxlp(2, 7) = 0;
    DuDxlp(0, 8) = 0;
    DuDxlp(1, 8) = 0;
    DuDxlp(2, 8) = -u_phiControl.solve_rhs(-L__[2], -1, 1);
    DuDxlp(0, 9) = 0;
    DuDxlp(1, 9) = 0;
    DuDxlp(2, 9) = 0;
    DuDxlp(0, 10) = 0;
    DuDxlp(1, 10) = 0;
    DuDxlp(2, 10) = 0;
    DuDxlp(0, 11) = 0;
    DuDxlp(1, 11) = 0;
    DuDxlp(2, 11) = 0;
    DuDxlp(0, 12) = 0;
    DuDxlp(1, 12) = 0;
    DuDxlp(2, 12) = 0;
  }

  void
  RobotArm::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
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
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
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
  RobotArm::DuDxlp_full_numeric(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    static integer DgDu_I[ 3 ], DgDu_J[ 3 ];
    static integer DgDxlp_I[ 6 ], DgDxlp_J[ 6 ];
    static bool    computed_pattern = false;
    if ( !computed_pattern ) {
      this->DgDu_pattern( DgDu_I, DgDu_J );
      this->DgDxlp_pattern( DgDxlp_I, DgDxlp_J );
      computed_pattern = true;
    }
    real_type DgDu_V[ 3 ], DgDxlp_V[ 6 ];
    this->DgDu_sparse( NODE__, U__, P__, DgDu_V );
    this->DgDxlp_sparse( NODE__, U__, P__, DgDxlp_V );

    integer   ipiv[ 3 ];
    real_type DgDu_storage[ 9 ];
    MatrixWrapper<real_type> DgDu( DgDu_storage, 3, 3, 3 );
    DgDu.zero_fill();
    DuDxlp.zero_fill();

    // fill DgDu
    DgDu( DgDu_I[ 0 ], DgDu_J[ 0 ] ) = DgDu_V[0];
    DgDu( DgDu_I[ 1 ], DgDu_J[ 1 ] ) = DgDu_V[1];
    DgDu( DgDu_I[ 2 ], DgDu_J[ 2 ] ) = DgDu_V[2];
    // fill DgDxlp
    DuDxlp( DgDxlp_I[ 0 ], DgDxlp_J[ 0] ) = -DgDxlp_V[0];
    DuDxlp( DgDxlp_I[ 1 ], DgDxlp_J[ 1] ) = -DgDxlp_V[1];
    DuDxlp( DgDxlp_I[ 2 ], DgDxlp_J[ 2] ) = -DgDxlp_V[2];
    DuDxlp( DgDxlp_I[ 3 ], DgDxlp_J[ 3] ) = -DgDxlp_V[3];
    DuDxlp( DgDxlp_I[ 4 ], DgDxlp_J[ 4] ) = -DgDxlp_V[4];
    DuDxlp( DgDxlp_I[ 5 ], DgDxlp_J[ 5] ) = -DgDxlp_V[5];
    integer info = alglin::gesv( 3, 13, DgDu.get_data(), 3, ipiv, DuDxlp.get_data(), 3 );
    return info == 0;
  }

  bool
  RobotArm::DuDxlp_full_numeric(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[6];
    real_type L__[6];
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
    X__[5] = (LEFT__.x[5]+RIGHT__.x[5])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    L__[4] = (LEFT__.lambda[4]+RIGHT__.lambda[4])/2;
    L__[5] = (LEFT__.lambda[5]+RIGHT__.lambda[5])/2;
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
  RobotArm::segmentLink_numEqns() const
  { return 0; }

  void
  RobotArm::segmentLink_eval(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            segmentLink[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DsegmentLinkDxp_numRows() const
  { return 0; }

  integer
  RobotArm::DsegmentLinkDxp_numCols() const
  { return 0; }

  integer
  RobotArm::DsegmentLinkDxp_nnz() const
  { return 0; }

  void
  RobotArm::DsegmentLinkDxp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  void
  RobotArm::DsegmentLinkDxp_sparse(
    NodeType const     & L,
    NodeType const     & R,
    P_const_pointer_type p,
    real_type            DsegmentLinkDxp[]
  ) const {
    LW_ERROR0("NON IMPLEMENTATA\n");
  }

  /*\
   |     _
   |  _ | |_  _ _ __  _ __
   | | || | || | '  \| '_ \
   |  \__/ \_,_|_|_|_| .__/
   |                 |_|
  \*/

  integer
  RobotArm::jump_numEqns() const
  { return 12; }

  void
  RobotArm::jump_eval(
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
    real_type t1   = XR__[0];
    real_type t2   = XL__[0];
    result__[ 0   ] = t1 - t2;
    result__[ 1   ] = XR__[1] - XL__[1];
    real_type t5   = XR__[2];
    real_type t6   = XL__[2];
    result__[ 2   ] = t5 - t6;
    result__[ 3   ] = XR__[3] - XL__[3];
    result__[ 4   ] = XR__[4] - XL__[4];
    result__[ 5   ] = XR__[5] - XL__[5];
    result__[ 6   ] = LR__[3] - LL__[3];
    result__[ 7   ] = LR__[4] - LL__[4];
    result__[ 8   ] = LR__[5] - LL__[5];
    real_type t19  = ModelPars[0];
    result__[ 9   ] = -LL__[0] * t19 + LR__[0] * t19;
    real_type t24  = I_theta(t1, t5);
    real_type t27  = I_theta(t2, t6);
    result__[ 10  ] = LR__[1] * t24 - LL__[1] * t27;
    real_type t30  = I_phi(t1);
    real_type t33  = I_phi(t2);
    result__[ 11  ] = LR__[2] * t30 - LL__[2] * t33;
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"jump_eval",12);
    #endif
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  RobotArm::DjumpDxlp_numRows() const
  { return 12; }

  integer
  RobotArm::DjumpDxlp_numCols() const
  { return 25; }

  integer
  RobotArm::DjumpDxlp_nnz() const
  { return 30; }

  void
  RobotArm::DjumpDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[ 0  ] = 0   ; jIndex[ 0  ] = 0   ;
    iIndex[ 1  ] = 0   ; jIndex[ 1  ] = 12  ;
    iIndex[ 2  ] = 1   ; jIndex[ 2  ] = 1   ;
    iIndex[ 3  ] = 1   ; jIndex[ 3  ] = 13  ;
    iIndex[ 4  ] = 2   ; jIndex[ 4  ] = 2   ;
    iIndex[ 5  ] = 2   ; jIndex[ 5  ] = 14  ;
    iIndex[ 6  ] = 3   ; jIndex[ 6  ] = 3   ;
    iIndex[ 7  ] = 3   ; jIndex[ 7  ] = 15  ;
    iIndex[ 8  ] = 4   ; jIndex[ 8  ] = 4   ;
    iIndex[ 9  ] = 4   ; jIndex[ 9  ] = 16  ;
    iIndex[ 10 ] = 5   ; jIndex[ 10 ] = 5   ;
    iIndex[ 11 ] = 5   ; jIndex[ 11 ] = 17  ;
    iIndex[ 12 ] = 6   ; jIndex[ 12 ] = 9   ;
    iIndex[ 13 ] = 6   ; jIndex[ 13 ] = 21  ;
    iIndex[ 14 ] = 7   ; jIndex[ 14 ] = 10  ;
    iIndex[ 15 ] = 7   ; jIndex[ 15 ] = 22  ;
    iIndex[ 16 ] = 8   ; jIndex[ 16 ] = 11  ;
    iIndex[ 17 ] = 8   ; jIndex[ 17 ] = 23  ;
    iIndex[ 18 ] = 9   ; jIndex[ 18 ] = 6   ;
    iIndex[ 19 ] = 9   ; jIndex[ 19 ] = 18  ;
    iIndex[ 20 ] = 10  ; jIndex[ 20 ] = 0   ;
    iIndex[ 21 ] = 10  ; jIndex[ 21 ] = 2   ;
    iIndex[ 22 ] = 10  ; jIndex[ 22 ] = 7   ;
    iIndex[ 23 ] = 10  ; jIndex[ 23 ] = 12  ;
    iIndex[ 24 ] = 10  ; jIndex[ 24 ] = 14  ;
    iIndex[ 25 ] = 10  ; jIndex[ 25 ] = 19  ;
    iIndex[ 26 ] = 11  ; jIndex[ 26 ] = 0   ;
    iIndex[ 27 ] = 11  ; jIndex[ 27 ] = 8   ;
    iIndex[ 28 ] = 11  ; jIndex[ 28 ] = 12  ;
    iIndex[ 29 ] = 11  ; jIndex[ 29 ] = 20  ;
  }

  void
  RobotArm::DjumpDxlp_sparse(
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
    result__[ 16  ] = -1;
    result__[ 17  ] = 1;
    real_type t1   = ModelPars[0];
    result__[ 18  ] = -t1;
    result__[ 19  ] = t1;
    real_type t2   = XL__[0];
    real_type t3   = XL__[2];
    real_type t4   = I_theta_D_1(t2, t3);
    real_type t5   = LL__[1];
    result__[ 20  ] = -t5 * t4;
    real_type t7   = I_theta_D_2(t2, t3);
    result__[ 21  ] = -t5 * t7;
    real_type t9   = I_theta(t2, t3);
    result__[ 22  ] = -t9;
    real_type t10  = XR__[0];
    real_type t11  = XR__[2];
    real_type t12  = I_theta_D_1(t10, t11);
    real_type t13  = LR__[1];
    result__[ 23  ] = t13 * t12;
    real_type t14  = I_theta_D_2(t10, t11);
    result__[ 24  ] = t13 * t14;
    result__[ 25  ] = I_theta(t10, t11);
    real_type t15  = I_phi_D(t2);
    result__[ 26  ] = -LL__[2] * t15;
    real_type t18  = I_phi(t2);
    result__[ 27  ] = -t18;
    real_type t19  = I_phi_D(t10);
    result__[ 28  ] = LR__[2] * t19;
    result__[ 29  ] = I_phi(t10);
    #ifdef MECHATRONIX_DEBUG
    CHECK_NAN(result__,"DjumpDxlp_sparse",30);
    #endif
  }

}

// EOF: RobotArm_Methods.cc
