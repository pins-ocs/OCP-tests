/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods_controls.cc                               |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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


namespace TwoStageCSTRDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  TwoStageCSTR::g_fun_eval(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_x1];
    real_type t2   = t1 * t1;
    real_type t3   = XL__[iX_x2];
    real_type t4   = t3 * t3;
    real_type t5   = XL__[iX_x3];
    real_type t6   = t5 * t5;
    real_type t7   = XL__[iX_x4];
    real_type t8   = t7 * t7;
    real_type t10  = UM__[0];
    real_type t11  = t10 * t10;
    real_type t12  = UM__[1];
    real_type t13  = t12 * t12;
    real_type t17  = LM__[0];
    real_type t18  = R1(t1, t3);
    real_type t19  = 0.5e0 - t1 - t18;
    real_type t21  = LM__[1];
    real_type t23  = 2 + t10;
    real_type t25  = t18 - t23 * (t3 + 0.25e0);
    real_type t27  = LM__[2];
    real_type t28  = ModelPars[iM_tau];
    real_type t30  = R2(t5, t7);
    real_type t33  = LM__[3];
    real_type t40  = u1Control(t10, -0.5e0, 0.5e0);
    real_type t42  = u2Control(t12, -0.5e0, 0.5e0);
    real_type t44  = XR__[iX_x1];
    real_type t45  = t44 * t44;
    real_type t46  = XR__[iX_x2];
    real_type t47  = t46 * t46;
    real_type t48  = XR__[iX_x3];
    real_type t49  = t48 * t48;
    real_type t50  = XR__[iX_x4];
    real_type t51  = t50 * t50;
    real_type t52  = R1(t44, t46);
    real_type t53  = 0.5e0 - t44 - t52;
    real_type t57  = t52 - t23 * (t46 + 0.25e0);
    real_type t60  = R2(t48, t50);
    real_type result__ = t2 + t4 + t6 + t8 + 2 * (t11 + t13) * ModelPars[iM_W] + t19 * t17 + t25 * t21 + (t1 - t5 - t19 * t28 - t30 + 0.25e0) * t27 + (t3 - 2 * t7 - (t7 + 0.25e0) * t12 - t25 * t28 + t30 - 0.25e0) * t33 + 2 * t40 + 2 * t42 + t45 + t47 + t49 + t51 + t53 * t17 + t57 * t21 + (t44 - t48 - t53 * t28 - t60 + 0.25e0) * t27 + (t46 - 2 * t50 - (t50 + 0.25e0) * t12 - t57 * t28 + t60 - 0.25e0) * t33;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoStageCSTR::g_numEqns() const { return 2; }

  void
  TwoStageCSTR::g_eval(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_W];
    real_type t2   = UM__[0];
    real_type t5   = LM__[1];
    real_type t7   = -XL__[iX_x2] - 0.25e0;
    real_type t9   = LM__[3];
    real_type t11  = ModelPars[iM_tau] * t9;
    real_type t13  = ALIAS_u1Control_D_1(t2, -0.5e0, 0.5e0);
    real_type t16  = -XR__[iX_x2] - 0.25e0;
    result__[ 0   ] = 4 * t2 * t1 - t16 * t11 - t7 * t11 + t16 * t5 + t7 * t5 + 2 * t13;
    real_type t19  = UM__[1];
    real_type t25  = ALIAS_u2Control_D_1(t19, -0.5e0, 0.5e0);
    result__[ 1   ] = 4 * t19 * t1 + (-XL__[iX_x4] - 0.25e0) * t9 + 2 * t25 + (-XR__[iX_x4] - 0.25e0) * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::DgDxlxlp_numRows() const { return 2; }
  integer TwoStageCSTR::DgDxlxlp_numCols() const { return 16; }
  integer TwoStageCSTR::DgDxlxlp_nnz()     const { return 10; }

  void
  TwoStageCSTR::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 9   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 13  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 15  ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 11  ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 15  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[3];
    real_type t2   = ModelPars[iM_tau];
    result__[ 0   ] = t2 * t1 - LM__[1];
    real_type t5   = XL__[iX_x2];
    real_type t7   = XR__[iX_x2];
    result__[ 1   ] = -0.5e0 * t5 - 0.250e0 - 0.5e0 * t7;
    result__[ 2   ] = -0.5e0 * (-t5 - 0.25e0) * t2 - 0.5e0 * (-t7 - 0.25e0) * t2;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = -t1;
    result__[ 7   ] = -0.5e0 * XL__[iX_x4] - 0.250e0 - 0.5e0 * XR__[iX_x4];
    result__[ 8   ] = result__[6];
    result__[ 9   ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::DgDu_numRows() const { return 2; }
  integer TwoStageCSTR::DgDu_numCols() const { return 2; }
  integer TwoStageCSTR::DgDu_nnz()     const { return 2; }

  void
  TwoStageCSTR::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DgDu_sparse(
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
    real_type QM__[1], XM__[4], LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 4 * ModelPars[iM_W];
    real_type t4   = ALIAS_u1Control_D_1_1(UM__[0], -0.5e0, 0.5e0);
    result__[ 0   ] = t2 + 2 * t4;
    real_type t7   = ALIAS_u2Control_D_1_1(UM__[1], -0.5e0, 0.5e0);
    result__[ 1   ] = t2 + 2 * t7;
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

  void
  TwoStageCSTR::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "TwoStageCSTR::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  TwoStageCSTR::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u1];
    real_type t2   = u1Control(t1, -0.5e0, 0.5e0);
    real_type t3   = U__[iU_u2];
    real_type t4   = u2Control(t3, -0.5e0, 0.5e0);
    real_type t6   = X__[iX_x1];
    real_type t7   = X__[iX_x2];
    real_type t8   = R1(t6, t7);
    real_type t10  = pow(V__[0] - 0.5e0 + t6 + t8, 2);
    real_type t14  = (2 + t1) * (t7 + 0.25e0);
    real_type t16  = pow(V__[1] - t8 + t14, 2);
    real_type t18  = X__[iX_x3];
    real_type t19  = ModelPars[iM_tau];
    real_type t22  = X__[iX_x4];
    real_type t23  = R2(t18, t22);
    real_type t25  = pow(V__[2] - t6 + t18 + (0.5e0 - t6 - t8) * t19 + t23 - 0.25e0, 2);
    real_type t33  = pow(V__[3] - t7 + 2 * t22 + (t22 + 0.25e0) * t3 + (t8 - t14) * t19 - t23 + 0.25e0, 2);
    real_type result__ = t2 + t4 + t10 + t16 + t25 + t33;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoStageCSTR::DmDu_numEqns() const { return 2; }

  void
  TwoStageCSTR::DmDu_eval(
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
    real_type t1   = U__[iU_u1];
    real_type t2   = ALIAS_u1Control_D_1(t1, -0.5e0, 0.5e0);
    real_type t5   = X__[iX_x2];
    real_type t6   = R1(X__[iX_x1], t5);
    real_type t7   = t5 + 0.25e0;
    real_type t9   = (2 + t1) * t7;
    real_type t14  = X__[iX_x4];
    real_type t16  = U__[iU_u2];
    real_type t17  = t14 + 0.25e0;
    real_type t19  = ModelPars[iM_tau];
    real_type t23  = R2(X__[iX_x3], t14);
    real_type t24  = V__[3] - t5 + 2 * t14 + t17 * t16 + (t6 - t9) * t19 - t23 + 0.25e0;
    result__[ 0   ] = t2 + 2 * t7 * (V__[1] - t6 + t9) - 2 * t7 * t19 * t24;
    real_type t29  = ALIAS_u2Control_D_1(t16, -0.5e0, 0.5e0);
    result__[ 1   ] = 2 * t17 * t24 + t29;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::DmDuu_numRows() const { return 2; }
  integer TwoStageCSTR::DmDuu_numCols() const { return 2; }
  integer TwoStageCSTR::DmDuu_nnz()     const { return 4; }

  void
  TwoStageCSTR::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  TwoStageCSTR::DmDuu_sparse(
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
    real_type t2   = ALIAS_u1Control_D_1_1(U__[iU_u1], -0.5e0, 0.5e0);
    real_type t4   = X__[iX_x2] + 0.25e0;
    real_type t5   = t4 * t4;
    real_type t7   = ModelPars[iM_tau];
    real_type t8   = t7 * t7;
    real_type t9   = -t4;
    real_type t10  = t9 * t9;
    result__[ 0   ] = 2 * t10 * t8 + t2 + 2 * t5;
    real_type t14  = X__[iX_x4] + 0.25e0;
    result__[ 1   ] = 2 * t9 * t7 * t14;
    result__[ 2   ] = result__[1];
    real_type t18  = ALIAS_u2Control_D_1_1(U__[iU_u2], -0.5e0, 0.5e0);
    real_type t19  = t14 * t14;
    result__[ 3   ] = t18 + 2 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: TwoStageCSTR_Methods_controls.cc
