/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_controls.cc                              |
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


#include "OrbitTransfer.hh"
#include "OrbitTransfer_Pars.hh"

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


namespace OrbitTransferDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  OrbitTransfer::g_fun_eval(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = t2 * LM__[0];
    real_type t4   = XL__[iX_u];
    real_type t7   = t2 * LM__[1];
    real_type t8   = XL__[iX_v];
    real_type t9   = t8 * t8;
    real_type t10  = XL__[iX_r];
    real_type t11  = 1.0 / t10;
    real_type t13  = ModelPars[iM_mu];
    real_type t14  = t10 * t10;
    real_type t17  = ModelPars[iM_T];
    real_type t18  = UM__[0];
    real_type t19  = sin(t18);
    real_type t20  = t19 * t17;
    real_type t22  = 1.0 / XL__[iX_m];
    real_type t27  = t2 * LM__[2];
    real_type t30  = cos(t18);
    real_type t31  = t30 * t17;
    real_type t41  = t2 * LM__[4];
    real_type t44  = XR__[iX_u];
    real_type t46  = XR__[iX_v];
    real_type t47  = t46 * t46;
    real_type t48  = XR__[iX_r];
    real_type t49  = 1.0 / t48;
    real_type t51  = t48 * t48;
    real_type t55  = 1.0 / XR__[iX_m];
    real_type result__ = t4 * t3 + (t11 * t9 - 1.0 / t14 * t13 + t22 * t20) * t7 + (-t11 * t4 * t8 + t22 * t31) * t27 - 2 * ModelPars[iM_mdot] * t2 * LM__[3] + t11 * t8 * t41 + t44 * t3 + (t49 * t47 - 1.0 / t51 * t13 + t55 * t20) * t7 + (-t49 * t44 * t46 + t55 * t31) * t27 + t49 * t46 * t41;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::g_numEqns() const { return 1; }

  void
  OrbitTransfer::g_eval(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ModelPars[iM_T] * ModelPars[iM_tf];
    real_type t5   = UM__[0];
    real_type t6   = cos(t5);
    real_type t9   = sin(t5);
    real_type t11  = t6 * LM__[1] - t9 * LM__[2];
    result__[ 0   ] = 1.0 / XL__[iX_m] * t11 * t3 + 1.0 / XR__[iX_m] * t11 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DgDxlxlp_numRows() const { return 1; }
  integer OrbitTransfer::DgDxlxlp_numCols() const { return 20; }
  integer OrbitTransfer::DgDxlxlp_nnz()     const { return 6; }

  void
  OrbitTransfer::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 10  ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 16  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 17  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ModelPars[iM_T] * ModelPars[iM_tf];
    real_type t5   = UM__[0];
    real_type t6   = cos(t5);
    real_type t9   = sin(t5);
    real_type t11  = t6 * LM__[1] - t9 * LM__[2];
    real_type t12  = XL__[iX_m];
    real_type t13  = t12 * t12;
    result__[ 0   ] = -1.0 / t13 * t11 * t3;
    real_type t17  = 1.0 / t12;
    real_type t21  = XR__[iX_m];
    real_type t22  = 1.0 / t21;
    result__[ 1   ] = 0.5e0 * t17 * t6 * t3 + 0.5e0 * t22 * t6 * t3;
    result__[ 2   ] = -0.5e0 * t17 * t9 * t3 - 0.5e0 * t22 * t9 * t3;
    real_type t32  = t21 * t21;
    result__[ 3   ] = -1.0 / t32 * t11 * t3;
    result__[ 4   ] = result__[1];
    result__[ 5   ] = result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DgDu_numRows() const { return 1; }
  integer OrbitTransfer::DgDu_numCols() const { return 1; }
  integer OrbitTransfer::DgDu_nnz()     const { return 1; }

  void
  OrbitTransfer::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DgDu_sparse(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ModelPars[iM_T] * ModelPars[iM_tf];
    real_type t5   = UM__[0];
    real_type t6   = sin(t5);
    real_type t9   = cos(t5);
    real_type t11  = -t6 * LM__[1] - t9 * LM__[2];
    result__[ 0   ] = 1.0 / XL__[iX_m] * t11 * t3 + 1.0 / XR__[iX_m] * t11 * t3;
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
  OrbitTransfer::u_eval_analytic(
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
    real_type QM__[1], XM__[5], LM__[5];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    U__[ iU_theta ] = atan(LM__[1] / LM__[2]);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  OrbitTransfer::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_tf];
    real_type t2   = X__[iX_u];
    real_type t6   = pow(-t2 * t1 + V__[2], 2);
    real_type t8   = X__[iX_v];
    real_type t9   = t8 * t8;
    real_type t10  = X__[iX_r];
    real_type t11  = 1.0 / t10;
    real_type t14  = t10 * t10;
    real_type t17  = ModelPars[iM_T];
    real_type t18  = U__[iU_theta];
    real_type t19  = sin(t18);
    real_type t22  = 1.0 / X__[iX_m];
    real_type t27  = pow(V__[3] - (t11 * t9 - 1.0 / t14 * ModelPars[iM_mu] + t22 * t19 * t17) * t1, 2);
    real_type t31  = cos(t18);
    real_type t37  = pow(V__[4] - (-t11 * t2 * t8 + t22 * t31 * t17) * t1, 2);
    real_type t42  = pow(ModelPars[iM_mdot] * t1 + V__[0], 2);
    real_type t47  = pow(-t11 * t8 * t1 + V__[1], 2);
    real_type result__ = t6 + t27 + t37 + t42 + t47;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer OrbitTransfer::DmDu_numEqns() const { return 1; }

  void
  OrbitTransfer::DmDu_eval(
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
    real_type t2   = ModelPars[iM_tf];
    real_type t3   = X__[iX_v];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_r];
    real_type t6   = 1.0 / t5;
    real_type t9   = t5 * t5;
    real_type t12  = ModelPars[iM_T];
    real_type t13  = U__[iU_theta];
    real_type t14  = sin(t13);
    real_type t17  = 1.0 / X__[iX_m];
    real_type t18  = t17 * t14 * t12;
    real_type t23  = cos(t13);
    real_type t25  = t17 * t23 * t12;
    result__[ 0   ] = -2 * t25 * t2 * (V__[3] - (t6 * t4 - 1.0 / t9 * ModelPars[iM_mu] + t18) * t2) + 2 * t18 * t2 * (V__[4] - (-t6 * X__[iX_u] * t3 + t25) * t2);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer OrbitTransfer::DmDuu_numRows() const { return 1; }
  integer OrbitTransfer::DmDuu_numCols() const { return 1; }
  integer OrbitTransfer::DmDuu_nnz()     const { return 1; }

  void
  OrbitTransfer::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  OrbitTransfer::DmDuu_sparse(
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
    real_type t1   = ModelPars[iM_tf];
    real_type t2   = t1 * t1;
    real_type t3   = ModelPars[iM_T];
    real_type t4   = t3 * t3;
    real_type t5   = t4 * t2;
    real_type t6   = U__[iU_theta];
    real_type t7   = cos(t6);
    real_type t8   = t7 * t7;
    real_type t9   = X__[iX_m];
    real_type t10  = t9 * t9;
    real_type t11  = 1.0 / t10;
    real_type t15  = X__[iX_v];
    real_type t16  = t15 * t15;
    real_type t17  = X__[iX_r];
    real_type t18  = 1.0 / t17;
    real_type t21  = t17 * t17;
    real_type t24  = sin(t6);
    real_type t26  = 1.0 / t9;
    real_type t27  = t26 * t24 * t3;
    real_type t33  = t24 * t24;
    real_type t41  = t26 * t7 * t3;
    result__[ 0   ] = 2 * t11 * t8 * t5 + 2 * t27 * t1 * (V__[3] - (t18 * t16 - 1.0 / t21 * ModelPars[iM_mu] + t27) * t1) + 2 * t11 * t33 * t5 + 2 * t41 * t1 * (V__[4] - (-t15 * t18 * X__[iX_u] + t41) * t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: OrbitTransfer_Methods_controls.cc
