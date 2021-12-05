/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_controls.cc                     |
 |                                                                       |
 |  version: 1.0   date 6/12/2021                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

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
#define ALIAS_v_Limit_DD(__t1) v_Limit.DD( __t1)
#define ALIAS_v_Limit_D(__t1) v_Limit.D( __t1)
#define ALIAS_s_Limit_DD(__t1) s_Limit.DD( __t1)
#define ALIAS_s_Limit_D(__t1) s_Limit.D( __t1)
#define ALIAS_p_Limit_DD(__t1) p_Limit.DD( __t1)
#define ALIAS_p_Limit_D(__t1) p_Limit.D( __t1)
#define ALIAS_x_Limit_DD(__t1) x_Limit.DD( __t1)
#define ALIAS_x_Limit_D(__t1) x_Limit.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS2_BatchFermentorDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  ICLOCS2_BatchFermentor::g_numEqns() const
  { return 1; }

  void
  ICLOCS2_BatchFermentor::g_eval(
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
    real_type t2   = ALIAS_uControl_D_1(UM__[0], 0, 50);
    real_type t3   = ModelPars[iM_S_f];
    real_type t5   = XM__[3];
    result__[ 0   ] = 1.0 / t3 / t5 * (t5 * t3 * t2 + t5 * (ModelPars[iM_W] * t3 + LM__[3]) + (t3 - XM__[2]) * LM__[2] - LM__[1] * XM__[1] - LM__[0] * XM__[0]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DgDxlxlp_numRows() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DgDxlxlp_numCols() const
  { return 16; }

  integer
  ICLOCS2_BatchFermentor::DgDxlxlp_nnz() const
  { return 16; }

  void
  ICLOCS2_BatchFermentor::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 9   ;
    iIndex[10] = 0   ; jIndex[10] = 10  ;
    iIndex[11] = 0   ; jIndex[11] = 11  ;
    iIndex[12] = 0   ; jIndex[12] = 12  ;
    iIndex[13] = 0   ; jIndex[13] = 13  ;
    iIndex[14] = 0   ; jIndex[14] = 14  ;
    iIndex[15] = 0   ; jIndex[15] = 15  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DgDxlxlp_sparse(
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
    real_type t1   = LM__[0];
    real_type t2   = XM__[3];
    real_type t3   = 1.0 / t2;
    real_type t5   = ModelPars[iM_S_f];
    real_type t6   = 1.0 / t5;
    result__[ 0   ] = -0.5e0 * t6 * t3 * t1;
    real_type t9   = LM__[1];
    result__[ 1   ] = -0.5e0 * t6 * t3 * t9;
    real_type t13  = LM__[2];
    result__[ 2   ] = -0.5e0 * t6 * t3 * t13;
    real_type t18  = ALIAS_uControl_D_1(UM__[0], 0, 50);
    real_type t19  = t5 * t18;
    real_type t21  = t5 * ModelPars[iM_W];
    real_type t22  = LM__[3];
    real_type t31  = t5 - XM__[2];
    real_type t33  = XM__[1];
    real_type t35  = XM__[0];
    real_type t38  = t2 * t2;
    result__[ 3   ] = 0.5e0 * t6 * t3 * (t19 + t21 + t22) - 0.5e0 * t6 / t38 * (t2 * t19 + t2 * (t21 + t22) + t31 * t13 - t33 * t9 - t35 * t1);
    result__[ 4   ] = -0.5e0 * t6 * t3 * t35;
    result__[ 5   ] = -0.5e0 * t6 * t3 * t33;
    result__[ 6   ] = 0.5e0 * t6 * t3 * t31;
    result__[ 7   ] = 0.5e0 * t6;
    result__[ 8   ] = result__[0];
    result__[ 9   ] = result__[1];
    result__[ 10  ] = result__[2];
    result__[ 11  ] = result__[3];
    result__[ 12  ] = result__[4];
    result__[ 13  ] = result__[5];
    result__[ 14  ] = result__[6];
    result__[ 15  ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DgDu_numRows() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DgDu_numCols() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DgDu_nnz() const
  { return 1; }

  void
  ICLOCS2_BatchFermentor::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DgDu_sparse(
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
    result__[ 0   ] = ALIAS_uControl_D_1_1(UM__[0], 0, 50);
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
  ICLOCS2_BatchFermentor::u_eval_analytic(
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
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_S_f];
    real_type t6   = XM__[3];
    U__[ iU_u ] = uControl.solve(1.0 / t6 / t1 * (t6 * (-ModelPars[iM_W] * t1 - LM__[3]) + LM__[2] * (-t1 + XM__[2]) + LM__[1] * XM__[1] + LM__[0] * XM__[0]), 0, 50);
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
  ICLOCS2_BatchFermentor::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
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
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_S_f];
    real_type t5   = -ModelPars[iM_W] * t1 - LM__[3];
    real_type t6   = XM__[3];
    real_type t9   = -t1 + XM__[2];
    real_type t10  = LM__[2];
    real_type t12  = LM__[1];
    real_type t13  = XM__[1];
    real_type t15  = LM__[0];
    real_type t16  = XM__[0];
    real_type t19  = 1.0 / t1;
    real_type t20  = t19 * (t10 * t9 + t13 * t12 + t16 * t15 + t6 * t5);
    real_type t21  = 1.0 / t6;
    real_type t23  = uControl.solve_rhs(t21 * t20, 0, 50);
    real_type t25  = t19 * t21;
    real_type tmp_0_0 = 0.5e0 * t25 * t15 * t23;
    real_type tmp_0_1 = 0.5e0 * t25 * t12 * t23;
    real_type tmp_0_2 = 0.5e0 * t25 * t10 * t23;
    real_type t33  = t6 * t6;
    real_type tmp_0_3 = 0.5e0 * (t21 * t19 * t5 - 1.0 / t33 * t20) * t23;
    real_type tmp_0_4 = 0.5e0 * t25 * t16 * t23;
    real_type tmp_0_5 = 0.5e0 * t25 * t13 * t23;
    real_type tmp_0_6 = 0.5e0 * t25 * t9 * t23;
    real_type tmp_0_7 = -0.5e0 * t19 * t23;
    real_type tmp_0_8 = tmp_0_0;
    real_type tmp_0_9 = tmp_0_1;
    real_type tmp_0_10 = tmp_0_2;
    real_type tmp_0_11 = tmp_0_3;
    real_type tmp_0_12 = tmp_0_4;
    real_type tmp_0_13 = tmp_0_5;
    real_type tmp_0_14 = tmp_0_6;
    real_type tmp_0_15 = tmp_0_7;
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
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 16 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  ICLOCS2_BatchFermentor::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = ModelPars[iM_state_tol];
    real_type t4   = x_Limit(t1 + t2);
    real_type t5   = X__[iX_p];
    real_type t7   = p_Limit(t5 + t2);
    real_type t8   = X__[iX_s];
    real_type t10  = s_Limit(t8 + t2);
    real_type t11  = X__[iX_v];
    real_type t12  = v_Limit(t11);
    real_type t13  = U__[iU_u];
    real_type t14  = uControl(t13, 0, 50);
    real_type t16  = mu(t8, t1);
    real_type t17  = t1 * t16;
    real_type t20  = 1.0 / ModelPars[iM_S_f];
    real_type t21  = 1.0 / t11;
    real_type t22  = t21 * t20;
    real_type t25  = pow(t1 * t13 * t22 - t17 + V__[0], 2);
    real_type t27  = rho(t8);
    real_type t28  = t1 * t27;
    real_type t34  = pow(t13 * t22 * t5 + t5 * ModelPars[iM_K_degr] - t28 + V__[1], 2);
    real_type t54  = pow(V__[2] + 1.0 / ModelPars[iM_Yxs] * t17 + 1.0 / ModelPars[iM_Yes] * t28 + t1 / (ModelPars[iM_kappa_m] + t8) * t8 * ModelPars[iM_mu_s] - (-t20 * t8 + 1) * t21 * t13, 2);
    real_type t58  = pow(-t20 * t13 + V__[3], 2);
    real_type result__ = t4 + t7 + t10 + t12 + t14 + t25 + t34 + t54 + t58;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DmDu_numEqns() const
  { return 1; }

  void
  ICLOCS2_BatchFermentor::DmDu_eval(
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
    real_type t2   = ALIAS_uControl_D_1(t1, 0, 50);
    real_type t4   = X__[iX_s];
    real_type t5   = X__[iX_x];
    real_type t6   = mu(t4, t5);
    real_type t7   = t5 * t6;
    real_type t10  = 1.0 / ModelPars[iM_S_f];
    real_type t12  = 1.0 / X__[iX_v];
    real_type t13  = t12 * t10;
    real_type t20  = rho(t4);
    real_type t21  = t5 * t20;
    real_type t23  = X__[iX_p];
    real_type t47  = -t10 * t4 + 1;
    result__[ 0   ] = t2 + 2 * t13 * t5 * (t13 * t1 * t5 - t7 + V__[0]) + 2 * t13 * t23 * (t13 * t1 * t23 + t23 * ModelPars[iM_K_degr] - t21 + V__[1]) - 2 * t47 * t12 * (V__[2] + 1.0 / ModelPars[iM_Yxs] * t7 + 1.0 / ModelPars[iM_Yes] * t21 + t5 / (ModelPars[iM_kappa_m] + t4) * t4 * ModelPars[iM_mu_s] - t47 * t12 * t1) - 2 * t10 * (-t10 * t1 + V__[3]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DmDuu_numRows() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DmDuu_numCols() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DmDuu_nnz() const
  { return 1; }

  void
  ICLOCS2_BatchFermentor::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DmDuu_sparse(
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
    real_type t2   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 50);
    real_type t4   = X__[iX_x] * X__[iX_x];
    real_type t5   = ModelPars[iM_S_f];
    real_type t6   = t5 * t5;
    real_type t7   = 1.0 / t6;
    real_type t10  = X__[iX_v] * X__[iX_v];
    real_type t11  = 1.0 / t10;
    real_type t15  = X__[iX_p] * X__[iX_p];
    real_type t23  = pow(1 - 1.0 / t5 * X__[iX_s], 2);
    result__[ 0   ] = 2 * t11 * t7 * t15 + 2 * t11 * t7 * t4 + 2 * t23 * t11 + t2 + 2 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_controls.cc
