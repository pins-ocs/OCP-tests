/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_controls.cc                            |
 |                                                                       |
 |  version: 1.0   date 14/6/2022                                        |
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


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

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
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


namespace BrachiostocronaDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Brachiostocrona::g_fun_eval(
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
    real_type t5   = UM__[1];
    real_type t9   = pow(XM__[0] * ModelPars[iM_slope_low] + t5 - XM__[1] + ModelPars[iM_y0_low], 2);
    real_type t11  = ModelPars[iM_mu];
    real_type t14  = exp(-1.0 / t11 * t5);
    real_type t15  = log(t5);
    real_type t18  = P__[iP_T];
    real_type t20  = XM__[2];
    real_type t21  = XM__[3];
    real_type t22  = cos(t21);
    real_type t27  = sin(t21);
    real_type t36  = UM__[0];
    real_type t38  = vthetaControl(t36, -10, 10);
    real_type result__ = t22 * t20 * t18 * LM__[0] + t27 * t20 * t18 * LM__[1] - t27 * ModelPars[iM_g] * t18 * LM__[2] - t11 * t15 + t38 * t18 + t36 * LM__[3] + t9 * ModelPars[iM_w_ARG] + t14;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::g_numEqns() const { return 2; }

  void
  Brachiostocrona::g_eval(
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
    real_type t4   = ALIAS_vthetaControl_D_1(UM__[0], -10, 10);
    result__[ 0   ] = t4 * P__[iP_T] + LM__[3];
    real_type t7   = UM__[1];
    real_type t9   = ModelPars[iM_mu];
    real_type t10  = ModelPars[iM_w_ARG];
    real_type t11  = t10 * t9;
    real_type t20  = t7 * t7;
    real_type t29  = 1.0 / t9;
    real_type t31  = exp(-t29 * t7);
    real_type t33  = t9 * t9;
    result__[ 1   ] = -1.0 / t7 * t29 * (-2 * ModelPars[iM_y0_low] * t10 * t9 * t7 - 2 * ModelPars[iM_slope_low] * t11 * t7 * XM__[0] - 2 * t10 * t9 * t20 + 2 * t11 * t7 * XM__[1] + t7 * t31 + t33);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DgDxlxlp_numRows() const { return 2; }
  integer Brachiostocrona::DgDxlxlp_numCols() const { return 17; }
  integer Brachiostocrona::DgDxlxlp_nnz()     const { return 7; }

  void
  Brachiostocrona::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 7   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 15  ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 16  ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 9   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona::DgDxlxlp_sparse(
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
    result__[ 0   ] = 0.5e0;
    result__[ 1   ] = 0.5e0;
    result__[ 2   ] = ALIAS_vthetaControl_D_1(UM__[0], -10, 10);
    real_type t2   = ModelPars[iM_w_ARG];
    result__[ 3   ] = 0.10e1 * ModelPars[iM_slope_low] * t2;
    result__[ 4   ] = -0.10e1 * t2;
    result__[ 5   ] = result__[3];
    result__[ 6   ] = result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DgDu_numRows() const { return 2; }
  integer Brachiostocrona::DgDu_numCols() const { return 2; }
  integer Brachiostocrona::DgDu_nnz()     const { return 2; }

  void
  Brachiostocrona::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona::DgDu_sparse(
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
    real_type t3   = ALIAS_vthetaControl_D_1_1(UM__[0], -10, 10);
    result__[ 0   ] = t3 * P__[iP_T];
    real_type t4   = XM__[0];
    real_type t5   = ModelPars[iM_mu];
    real_type t7   = ModelPars[iM_w_ARG];
    real_type t8   = ModelPars[iM_slope_low];
    real_type t12  = XM__[1];
    real_type t16  = UM__[1];
    real_type t17  = t5 * t16;
    real_type t20  = t7 * t5;
    real_type t21  = ModelPars[iM_y0_low];
    real_type t24  = 1.0 / t5;
    real_type t26  = exp(-t24 * t16);
    real_type t40  = t16 * t16;
    real_type t48  = t5 * t5;
    result__[ 1   ] = -1.0 / t16 * t24 * (-2 * t8 * t7 * t5 * t4 + 2 * t7 * t5 * t12 - t16 * t26 * t24 - 4 * t7 * t17 - 2 * t21 * t20 + t26) + 1.0 / t40 * t24 * (-2 * t8 * t20 * t16 * t4 + 2 * t20 * t16 * t12 - 2 * t21 * t7 * t17 - 2 * t7 * t5 * t40 + t16 * t26 + t48);
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
  Brachiostocrona::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "Brachiostocrona::u_eval_analytic\n"
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
  Brachiostocrona::m_eval(
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
    real_type t2   = U__[iU_vtheta];
    real_type t3   = vthetaControl(t2, -10, 10);
    real_type t7   = X__[iX_v] * t1;
    real_type t8   = X__[iX_theta];
    real_type t9   = cos(t8);
    real_type t12  = pow(-t9 * t7 + V__[0], 2);
    real_type t14  = sin(t8);
    real_type t17  = pow(-t14 * t7 + V__[1], 2);
    real_type t25  = pow(t14 * ModelPars[iM_g] * t1 + ModelPars[iM_mass] * V__[2], 2);
    real_type t28  = pow(V__[3] - t2, 2);
    real_type result__ = t3 * t1 + t12 + t17 + t25 + t28;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::DmDu_numEqns() const { return 2; }

  void
  Brachiostocrona::DmDu_eval(
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
    real_type t2   = U__[iU_vtheta];
    real_type t3   = ALIAS_vthetaControl_D_1(t2, -10, 10);
    result__[ 0   ] = t3 * P__[iP_T] + 2 * t2 - 2 * V__[3];
    result__[ 1   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DmDuu_numRows() const { return 2; }
  integer Brachiostocrona::DmDuu_numCols() const { return 2; }
  integer Brachiostocrona::DmDuu_nnz()     const { return 1; }

  void
  Brachiostocrona::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Brachiostocrona::DmDuu_sparse(
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
    real_type t3   = ALIAS_vthetaControl_D_1_1(U__[iU_vtheta], -10, 10);
    result__[ 0   ] = t3 * P__[iP_T] + 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: Brachiostocrona_Methods_controls.cc
