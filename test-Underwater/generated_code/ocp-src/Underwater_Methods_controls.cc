/*-----------------------------------------------------------------------*\
 |  file: Underwater_Methods_controls.cc                                 |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
 |                                                                       |
 |      Enrico Bertolazzi, Francesco Biral and Paolo Bosetti             |
 |      Dipartimento di Ingegneria Industriale                           |
 |      Universita` degli Studi di Trento                                |
 |      Via Sommarive 9, I-38123, Trento, Italy                          |
 |      email: enrico.bertolazzi@unitn.it                                |
 |             francesco.biral@unitn.it                                  |
 |             paolo.bosetti@unitn.it                                    |
\*-----------------------------------------------------------------------*/


#include "Underwater.hh"
#include "Underwater_Pars.hh"

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
#pragma warning( disable : 4189 )
#endif

// map user defined functions and objects with macros
#define ALIAS_u3Control_D_3(__t1, __t2, __t3) u3Control.D_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2(__t1, __t2, __t3) u3Control.D_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1(__t1, __t2, __t3) u3Control.D_1( __t1, __t2, __t3)
#define ALIAS_u3Control_D_3_3(__t1, __t2, __t3) u3Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_3(__t1, __t2, __t3) u3Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_2_2(__t1, __t2, __t3) u3Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_3(__t1, __t2, __t3) u3Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_2(__t1, __t2, __t3) u3Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u3Control_D_1_1(__t1, __t2, __t3) u3Control.D_1_1( __t1, __t2, __t3)
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


namespace UnderwaterDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Underwater::g_fun_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * LM__[0];
    real_type t4   = XL__[iX_vx];
    real_type t5   = XL__[iX_theta];
    real_type t6   = cos(t5);
    real_type t8   = XL__[iX_vz];
    real_type t9   = sin(t5);
    real_type t14  = t2 * LM__[1];
    real_type t20  = t2 * LM__[2];
    real_type t21  = XL__[iX_Omega];
    real_type t24  = t2 * LM__[3];
    real_type t25  = UM__[0];
    real_type t26  = ModelPars[iM_m1];
    real_type t27  = 1.0 / t26;
    real_type t28  = t27 * t25;
    real_type t30  = ModelPars[iM_m3];
    real_type t31  = t27 * t30;
    real_type t36  = t2 * LM__[4];
    real_type t37  = UM__[1];
    real_type t38  = 1.0 / t30;
    real_type t39  = t38 * t37;
    real_type t41  = t38 * t26;
    real_type t46  = t2 * LM__[5];
    real_type t47  = UM__[2];
    real_type t49  = 1.0 / ModelPars[iM_inertia];
    real_type t50  = t49 * t47;
    real_type t53  = t49 * (t30 - t26);
    real_type t57  = u1Control(t25, -1, 1);
    real_type t60  = u2Control(t37, -1, 1);
    real_type t63  = u3Control(t47, -1, 1);
    real_type t66  = XR__[iX_vx];
    real_type t67  = XR__[iX_theta];
    real_type t68  = cos(t67);
    real_type t70  = XR__[iX_vz];
    real_type t71  = sin(t67);
    real_type t79  = XR__[iX_Omega];
    real_type result__ = (t6 * t4 + t9 * t8) * t3 + (-t9 * t4 + t6 * t8) * t14 + t21 * t20 + (-t31 * t21 * t8 + t28) * t24 + (t41 * t21 * t4 + t39) * t36 + (t53 * t8 * t4 + t50) * t46 + 2 * t57 * t2 + 2 * t60 * t2 + 2 * t63 * t2 + (t68 * t66 + t71 * t70) * t3 + (-t71 * t66 + t68 * t70) * t14 + t79 * t20 + (-t31 * t79 * t70 + t28) * t24 + (t41 * t79 * t66 + t39) * t36 + (t53 * t70 * t66 + t50) * t46;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::g_numEqns() const { return 3; }

  void
  Underwater::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = P__[iP_T];
    real_type t8   = ALIAS_u1Control_D_1(UM__[0], -1, 1);
    result__[ 0   ] = 2 / ModelPars[iM_m1] * t2 * LM__[3] + 2 * t8 * t2;
    real_type t17  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    result__[ 1   ] = 2 / ModelPars[iM_m3] * t2 * LM__[4] + 2 * t17 * t2;
    real_type t26  = ALIAS_u3Control_D_1(UM__[2], -1, 1);
    result__[ 2   ] = 2 / ModelPars[iM_inertia] * t2 * LM__[5] + 2 * t26 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DgDxlxlp_numRows() const { return 3; }
  integer Underwater::DgDxlxlp_numCols() const { return 25; }
  integer Underwater::DgDxlxlp_nnz()     const { return 9; }

  void
  Underwater::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 9   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 21  ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 24  ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 10  ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 22  ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 24  ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 11  ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 23  ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 24  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = 1.0 / ModelPars[iM_m1];
    result__[ 0   ] = 0.10e1 * t3 * t1;
    result__[ 1   ] = result__[0];
    real_type t8   = ALIAS_u1Control_D_1(UM__[0], -1, 1);
    result__[ 2   ] = 2 * LM__[3] * t3 + 2 * t8;
    real_type t11  = 1.0 / ModelPars[iM_m3];
    result__[ 3   ] = 0.10e1 * t11 * t1;
    result__[ 4   ] = result__[3];
    real_type t16  = ALIAS_u2Control_D_1(UM__[1], -1, 1);
    result__[ 5   ] = 2 * LM__[4] * t11 + 2 * t16;
    real_type t19  = 1.0 / ModelPars[iM_inertia];
    result__[ 6   ] = 0.10e1 * t19 * t1;
    result__[ 7   ] = result__[6];
    real_type t24  = ALIAS_u3Control_D_1(UM__[2], -1, 1);
    result__[ 8   ] = 2 * LM__[5] * t19 + 2 * t24;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DgDu_numRows() const { return 3; }
  integer Underwater::DgDu_numCols() const { return 3; }
  integer Underwater::DgDu_nnz()     const { return 3; }

  void
  Underwater::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Underwater::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1_1(UM__[0], -1, 1);
    result__[ 0   ] = 2 * t3 * t1;
    real_type t6   = ALIAS_u2Control_D_1_1(UM__[1], -1, 1);
    result__[ 1   ] = 2 * t6 * t1;
    real_type t9   = ALIAS_u3Control_D_1_1(UM__[2], -1, 1);
    result__[ 2   ] = 2 * t9 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 3, i_segment );
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
  Underwater::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[6], LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    U__[ iU_u1 ] = u3Control.solve(-1.0 / ModelPars[iM_m1] * LM__[3], -1, 1);
    U__[ iU_u2 ] = u3Control.solve(-1.0 / ModelPars[iM_m3] * LM__[4], -1, 1);
    U__[ iU_u3 ] = u3Control.solve(-1.0 / ModelPars[iM_inertia] * LM__[5], -1, 1);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 3 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Underwater::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u1];
    real_type t3   = u1Control(t2, -1, 1);
    real_type t5   = U__[iU_u2];
    real_type t6   = u2Control(t5, -1, 1);
    real_type t8   = U__[iU_u3];
    real_type t9   = u3Control(t8, -1, 1);
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_theta];
    real_type t14  = cos(t13);
    real_type t16  = X__[iX_vz];
    real_type t17  = sin(t13);
    real_type t22  = pow(V__[0] - (t14 * t12 + t17 * t16) * t1, 2);
    real_type t29  = pow(V__[1] - (-t17 * t12 + t14 * t16) * t1, 2);
    real_type t30  = X__[iX_Omega];
    real_type t34  = pow(-t30 * t1 + V__[2], 2);
    real_type t36  = ModelPars[iM_m1];
    real_type t37  = 1.0 / t36;
    real_type t40  = ModelPars[iM_m3];
    real_type t46  = pow(V__[3] - (-t37 * t40 * t30 * t16 + t37 * t2) * t1, 2);
    real_type t48  = 1.0 / t40;
    real_type t56  = pow(V__[4] - (t48 * t36 * t30 * t12 + t48 * t5) * t1, 2);
    real_type t59  = 1.0 / ModelPars[iM_inertia];
    real_type t68  = pow(V__[5] - (t59 * t8 + t59 * (t40 - t36) * t16 * t12) * t1, 2);
    real_type result__ = t3 * t1 + t6 * t1 + t9 * t1 + t22 + t29 + t34 + t46 + t56 + t68;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Underwater::DmDu_numEqns() const { return 3; }

  void
  Underwater::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u1];
    real_type t3   = ALIAS_u1Control_D_1(t2, -1, 1);
    real_type t6   = ModelPars[iM_m1];
    real_type t7   = 1.0 / t6;
    real_type t9   = X__[iX_vz];
    real_type t10  = X__[iX_Omega];
    real_type t12  = ModelPars[iM_m3];
    result__[ 0   ] = t3 * t1 - 2 * t7 * t1 * (V__[3] - (-t7 * t12 * t10 * t9 + t7 * t2) * t1);
    real_type t21  = U__[iU_u2];
    real_type t22  = ALIAS_u2Control_D_1(t21, -1, 1);
    real_type t25  = 1.0 / t12;
    real_type t27  = X__[iX_vx];
    result__[ 1   ] = t22 * t1 - 2 * t25 * t1 * (V__[4] - (t25 * t6 * t10 * t27 + t25 * t21) * t1);
    real_type t37  = U__[iU_u3];
    real_type t38  = ALIAS_u3Control_D_1(t37, -1, 1);
    real_type t42  = 1.0 / ModelPars[iM_inertia];
    result__[ 2   ] = t38 * t1 - 2 * t42 * t1 * (V__[5] - (t42 * t37 + t42 * (t12 - t6) * t9 * t27) * t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Underwater::DmDuu_numRows() const { return 3; }
  integer Underwater::DmDuu_numCols() const { return 3; }
  integer Underwater::DmDuu_nnz()     const { return 3; }

  void
  Underwater::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  void
  Underwater::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    real_type t5   = t1 * t1;
    real_type t7   = ModelPars[iM_m1] * ModelPars[iM_m1];
    result__[ 0   ] = t3 * t1 + 2 / t7 * t5;
    real_type t12  = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    real_type t15  = ModelPars[iM_m3] * ModelPars[iM_m3];
    result__[ 1   ] = t12 * t1 + 2 / t15 * t5;
    real_type t20  = ALIAS_u3Control_D_1_1(U__[iU_u3], -1, 1);
    real_type t23  = ModelPars[iM_inertia] * ModelPars[iM_inertia];
    result__[ 2   ] = t20 * t1 + 2 / t23 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 3, i_segment );
  }

}

// EOF: Underwater_Methods_controls.cc
