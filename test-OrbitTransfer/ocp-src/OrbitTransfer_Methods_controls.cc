/*-----------------------------------------------------------------------*\
 |  file: OrbitTransfer_Methods_controls.cc                              |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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
#endif


namespace OrbitTransferDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  OrbitTransfer::g_numEqns() const
  { return 1; }

  void
  OrbitTransfer::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = cos(t5);
    real_type t9   = 1.0 / X__[iX_m];
    real_type t14  = sin(t5);
    real_type t7   = t2 * t4;
    result__[ 0   ] = -L__[iL_lambda3__xo] * t7 * t9 * t14 + L__[iL_lambda2__xo] * t7 * t9 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DgDxlp_numRows() const
  { return 1; }

  integer
  OrbitTransfer::DgDxlp_numCols() const
  { return 10; }

  integer
  OrbitTransfer::DgDxlp_nnz() const
  { return 3; }

  void
  OrbitTransfer::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = cos(t5);
    real_type t8   = X__[iX_m];
    real_type t9   = t8 * t8;
    real_type t10  = 1.0 / t9;
    real_type t15  = sin(t5);
    real_type t3   = t4 * t2;
    result__[ 0   ] = L__[iL_lambda3__xo] * t3 * t10 * t15 - L__[iL_lambda2__xo] * t3 * t10 * t6;
    real_type t19  = t4 * t2;
    real_type t20  = 1.0 / t8;
    result__[ 1   ] = t20 * t6 * t19;
    result__[ 2   ] = -t20 * t15 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DgDu_numRows() const
  { return 1; }

  integer
  OrbitTransfer::DgDu_numCols() const
  { return 1; }

  integer
  OrbitTransfer::DgDu_nnz() const
  { return 1; }

  void
  OrbitTransfer::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DgDu_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_tf];
    real_type t4   = ModelPars[iM_T];
    real_type t5   = U__[iU_theta];
    real_type t6   = sin(t5);
    real_type t9   = 1.0 / X__[iX_m];
    real_type t14  = cos(t5);
    result__[ 0   ] = -t14 * t2 * t4 * t9 * L__[iL_lambda3__xo] - t2 * t4 * t6 * t9 * L__[iL_lambda2__xo];
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
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1];
    real_type XM__[5];
    real_type LM__[5];
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_theta ] = atan(LM__[1] / LM__[2]);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  /*\
   |  ____        ____       _      _                           _       _   _
   | |  _ \ _   _|  _ \__  _| |_  _| |_ __     __ _ _ __   __ _| |_   _| |_(_) ___
   | | | | | | | | | | \ \/ / \ \/ / | '_ \   / _` | '_ \ / _` | | | | | __| |/ __|
   | | |_| | |_| | |_| |>  <| |>  <| | |_) | | (_| | | | | (_| | | |_| | |_| | (__
   | |____/ \__,_|____//_/\_\_/_/\_\_| .__/   \__,_|_| |_|\__,_|_|\__, |\__|_|\___|
   |                                 |_|                          |___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1];
    real_type XM__[5];
    real_type LM__[5];
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type t1   = LM__[2];
    real_type t3   = LM__[1];
    real_type t4   = t3 * t3;
    real_type t5   = t1 * t1;
    real_type t6   = 1.0 / t5;
    real_type t9   = 1.0 / (t6 * t4 + 1);
    real_type tmp_0_6 = 0.5e0 * t9 / t1;
    real_type tmp_0_7 = -0.5e0 * t9 * t6 * t3;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_0_10 = 0.0e0;
    real_type tmp_0_11 = 0.0e0;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_0_16 = tmp_0_6;
    real_type tmp_0_17 = tmp_0_7;
    real_type tmp_0_18 = 0.0e0;
    real_type tmp_0_19 = 0.0e0;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(0, 17) = tmp_0_17;
    DuDxlxlp(0, 18) = tmp_0_18;
    DuDxlxlp(0, 19) = tmp_0_19;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 20 );
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
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
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
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  OrbitTransfer::DmDu_numEqns() const
  { return 1; }

  void
  OrbitTransfer::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
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

  integer
  OrbitTransfer::DmDuu_numRows() const
  { return 1; }

  integer
  OrbitTransfer::DmDuu_numCols() const
  { return 1; }

  integer
  OrbitTransfer::DmDuu_nnz() const
  { return 1; }

  void
  OrbitTransfer::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  OrbitTransfer::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
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
    result__[ 0   ] = 2 * t11 * t8 * t5 + 2 * t27 * t1 * (V__[3] - (t18 * t16 - 1.0 / t21 * ModelPars[iM_mu] + t27) * t1) + 2 * t11 * t33 * t5 + 2 * t41 * t1 * (V__[4] - (-t18 * X__[iX_u] * t15 + t41) * t1);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: OrbitTransfer_Methods_controls.cc
