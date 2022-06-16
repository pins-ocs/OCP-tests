/*-----------------------------------------------------------------------*\
 |  file: GoddardRocket_Methods_controls.cc                              |
 |                                                                       |
 |  version: 1.0   date 19/6/2022                                        |
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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace GoddardRocketDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  GoddardRocket::g_fun_eval(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[0];
    real_type t3   = t2 * t2;
    real_type t6   = P__[iP_TimeSize];
    real_type t8   = XM__[1];
    real_type t12  = T(t2);
    real_type t14  = DD(XM__[0], t8);
    real_type t16  = XM__[2];
    real_type t28  = uControl(t2, 0, 1);
    real_type t29  = massPositive(-t16);
    real_type t30  = vPositive(-t8);
    real_type t31  = TSPositive(-t6);
    real_type result__ = t3 * ModelPars[iM_mu] + t8 * t6 * LM__[0] + (1.0 / t16 * (t12 - t14) - ModelPars[iM_g]) * t6 * LM__[1] - 1.0 / ModelPars[iM_Ve] * t12 * t6 * LM__[2] + t28 + t29 + t30 + t31;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::g_numEqns() const { return 1; }

  void
  GoddardRocket::g_eval(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[0];
    real_type t6   = P__[iP_TimeSize];
    real_type t8   = T_D(t2);
    real_type t19  = ALIAS_uControl_D_1(t2, 0, 1);
    result__[ 0   ] = 2 * t2 * ModelPars[iM_mu] + 1.0 / XM__[2] * t8 * t6 * LM__[1] - 1.0 / ModelPars[iM_Ve] * t8 * t6 * LM__[2] + t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DgDxlxlp_numRows() const { return 1; }
  integer GoddardRocket::DgDxlxlp_numCols() const { return 13; }
  integer GoddardRocket::DgDxlxlp_nnz()     const { return 7; }

  void
  GoddardRocket::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 10  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[1];
    real_type t2   = P__[iP_TimeSize];
    real_type t5   = T_D(UM__[0]);
    real_type t6   = XM__[2];
    real_type t7   = t6 * t6;
    result__[ 0   ] = -0.5e0 / t7 * t5 * t2 * t1;
    real_type t12  = t5 * t2;
    real_type t13  = 1.0 / t6;
    result__[ 1   ] = 0.5e0 * t13 * t12;
    real_type t16  = 1.0 / ModelPars[iM_Ve];
    result__[ 2   ] = -0.5e0 * t16 * t12;
    result__[ 3   ] = result__[0];
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    result__[ 6   ] = t13 * t5 * t1 - t16 * t5 * LM__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DgDu_numRows() const { return 1; }
  integer GoddardRocket::DgDu_numCols() const { return 1; }
  integer GoddardRocket::DgDu_nnz()     const { return 1; }

  void
  GoddardRocket::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  GoddardRocket::DgDu_sparse(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = P__[iP_TimeSize];
    real_type t6   = UM__[0];
    real_type t7   = T_DD(t6);
    real_type t18  = ALIAS_uControl_D_1_1(t6, 0, 1);
    result__[ 0   ] = 2 * ModelPars[iM_mu] + 1.0 / XM__[2] * t7 * t4 * LM__[1] - 1.0 / ModelPars[iM_Ve] * t7 * t4 * LM__[2] + t18;
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

  void
  GoddardRocket::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "GoddardRocket::u_eval_analytic\n"
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
  GoddardRocket::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_u];
    real_type t2   = uControl(t1, 0, 1);
    real_type t3   = X__[iX_m];
    real_type t4   = massPositive(-t3);
    real_type t5   = X__[iX_v];
    real_type t6   = vPositive(-t5);
    real_type t7   = P__[iP_TimeSize];
    real_type t8   = TSPositive(-t7);
    real_type t12  = pow(-t5 * t7 + V__[0], 2);
    real_type t14  = T(t1);
    real_type t16  = DD(X__[iX_h], t5);
    real_type t24  = pow(V__[1] - (1.0 / t3 * (t14 - t16) - ModelPars[iM_g]) * t7, 2);
    real_type t31  = pow(V__[2] + 1.0 / ModelPars[iM_Ve] * t14 * t7, 2);
    real_type result__ = t2 + t4 + t6 + t8 + t12 + t24 + t31;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer GoddardRocket::DmDu_numEqns() const { return 1; }

  void
  GoddardRocket::DmDu_eval(
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
    real_type t1   = U__[iU_u];
    real_type t2   = ALIAS_uControl_D_1(t1, 0, 1);
    real_type t4   = P__[iP_TimeSize];
    real_type t5   = T(t1);
    real_type t8   = DD(X__[iX_h], X__[iX_v]);
    real_type t11  = 1.0 / X__[iX_m];
    real_type t18  = T_D(t1);
    real_type t25  = 1.0 / ModelPars[iM_Ve];
    result__[ 0   ] = t2 - 2 * t11 * t18 * t4 * (V__[1] - (t11 * (t5 - t8) - ModelPars[iM_g]) * t4) + 2 * t25 * t18 * t4 * (t25 * t5 * t4 + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer GoddardRocket::DmDuu_numRows() const { return 1; }
  integer GoddardRocket::DmDuu_numCols() const { return 1; }
  integer GoddardRocket::DmDuu_nnz()     const { return 1; }

  void
  GoddardRocket::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  GoddardRocket::DmDuu_sparse(
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
    real_type t1   = U__[iU_u];
    real_type t2   = ALIAS_uControl_D_1_1(t1, 0, 1);
    real_type t3   = P__[iP_TimeSize];
    real_type t4   = t3 * t3;
    real_type t5   = T_D(t1);
    real_type t6   = t5 * t5;
    real_type t7   = t6 * t4;
    real_type t8   = X__[iX_m];
    real_type t9   = t8 * t8;
    real_type t14  = T(t1);
    real_type t17  = DD(X__[iX_h], X__[iX_v]);
    real_type t19  = 1.0 / t8;
    real_type t26  = T_DD(t1);
    real_type t30  = ModelPars[iM_Ve];
    real_type t31  = t30 * t30;
    real_type t37  = 1.0 / t30;
    result__[ 0   ] = t2 + 2 / t9 * t7 - 2 * t19 * t26 * t3 * (V__[1] - (t19 * (t14 - t17) - ModelPars[iM_g]) * t3) + 2 / t31 * t7 + 2 * t37 * t26 * t3 * (t37 * t14 * t3 + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: GoddardRocket_Methods_controls.cc
