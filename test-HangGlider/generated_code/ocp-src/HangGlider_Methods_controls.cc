/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_controls.cc                                 |
 |                                                                       |
 |  version: 1.0   date 13/12/2021                                       |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  HangGlider::g_fun_eval(
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
    real_type t1   = ModelPars[iM_W];
    real_type t2   = ModelPars[iM_m];
    real_type t3   = t2 * t1;
    real_type t4   = UM__[0];
    real_type t5   = t4 * t4;
    real_type t9   = LM__[3];
    real_type t10  = P__[iP_T];
    real_type t11  = t10 * t9;
    real_type t18  = XM__[2];
    real_type t23  = XM__[3];
    real_type t26  = Tbound(t10);
    real_type t31  = cLControl(t4, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t35  = XM__[0];
    real_type t36  = v(t35, t18, t23);
    real_type t39  = ModelPars[iM_c1];
    real_type t43  = ModelPars[iM_c0];
    real_type t47  = w(t35, t23);
    real_type t49  = LM__[2];
    real_type t60  = Dfun(t35, t18, t23);
    real_type t69  = Lfun(t35, t18, t23);
    real_type result__ = 1.0 / t36 / t2 * (t36 * (t5 * t3 - 0.14e1 * t4 * t3 - 1.0 * t2 * ModelPars[iM_g] * t11 + t2 * t18 * t10 * LM__[0] + t2 * t23 * t10 * LM__[1] + t2 * t26 + t2 * (0.49e0 * t1 + t31)) + t60 * (t47 * (-1.0 * t39 * t10 * t9 * t5 - 1.0 * t43 * t11) - 1.0 * t39 * t10 * t18 * t49 * t5 - 1.0 * t43 * t10 * t18 * t49) + t69 * (-1.0 * t10 * t47 * t49 * t4 + t11 * t18 * t4));
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  integer
  HangGlider::g_numEqns() const
  { return 1; }

  void
  HangGlider::g_eval(
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
    real_type t2   = UM__[0];
    real_type t7   = t2 * ModelPars[iM_c1];
    real_type t8   = XM__[0];
    real_type t9   = XM__[2];
    real_type t10  = XM__[3];
    real_type t11  = Dfun(t8, t9, t10);
    real_type t14  = Lfun(t8, t9, t10);
    real_type t15  = w(t8, t10);
    real_type t19  = P__[iP_T];
    real_type t23  = 1.0 / ModelPars[iM_m];
    real_type t25  = v(t8, t9, t10);
    real_type t26  = 1.0 / t25;
    real_type t42  = ALIAS_cLControl_D_1(t2, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] - 2 * t26 * t23 * LM__[2] * t19 * (t9 * t11 * t7 + t15 * t14 / 2) + (-2 * t15 * t11 * t7 + t9 * t14) * t26 * t23 * t19 * LM__[3] + t42;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DgDxlxlp_numRows() const
  { return 1; }

  integer
  HangGlider::DgDxlxlp_numCols() const
  { return 17; }

  integer
  HangGlider::DgDxlxlp_nnz() const
  { return 11; }

  void
  HangGlider::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 10  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 11  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 14  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 15  ;
    iIndex[10] = 0   ; jIndex[10] = 16  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDxlxlp_sparse(
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
    real_type t3   = ModelPars[iM_c1] * UM__[0];
    real_type t4   = XM__[0];
    real_type t5   = XM__[2];
    real_type t6   = XM__[3];
    real_type t7   = Dfun_D_1(t4, t5, t6);
    real_type t10  = Lfun_D_1(t4, t5, t6);
    real_type t11  = w(t4, t6);
    real_type t14  = Lfun(t4, t5, t6);
    real_type t15  = w_D_1(t4, t6);
    real_type t19  = P__[iP_T];
    real_type t21  = LM__[2];
    real_type t23  = 1.0 / ModelPars[iM_m];
    real_type t25  = v(t4, t5, t6);
    real_type t26  = 1.0 / t25;
    real_type t27  = t26 * t23 * t21;
    real_type t30  = Dfun(t4, t5, t6);
    real_type t35  = t5 * t30 * t3 + t11 * t14 / 2;
    real_type t36  = t19 * t35;
    real_type t37  = t21 * t36;
    real_type t38  = t25 * t25;
    real_type t39  = 1.0 / t38;
    real_type t40  = t39 * t23;
    real_type t41  = v_D_1(t4, t5, t6);
    real_type t45  = LM__[3];
    real_type t46  = t19 * t45;
    real_type t47  = t23 * t46;
    real_type t52  = -2 * t11 * t30 * t3 + t5 * t14;
    real_type t53  = t52 * t39;
    real_type t57  = t26 * t23;
    result__[ 0   ] = -0.10e1 * t27 * t19 * (t5 * t7 * t3 + t11 * t10 / 2 + t15 * t14 / 2) + 0.10e1 * t41 * t40 * t37 - 0.5e0 * t41 * t53 * t47 + 0.5e0 * (-2 * t11 * t7 * t3 - 2 * t15 * t30 * t3 + t5 * t10) * t57 * t46;
    real_type t69  = Dfun_D_2(t4, t5, t6);
    real_type t73  = Lfun_D_2(t4, t5, t6);
    real_type t80  = v_D_2(t4, t5, t6);
    result__[ 1   ] = -0.10e1 * t27 * t19 * (t5 * t69 * t3 + t30 * t3 + t11 * t73 / 2) + 0.10e1 * t80 * t40 * t37 - 0.5e0 * t80 * t53 * t47 + 0.5e0 * (-2 * t11 * t69 * t3 + t5 * t73 + t14) * t57 * t46;
    real_type t95  = Dfun_D_3(t4, t5, t6);
    real_type t98  = Lfun_D_3(t4, t5, t6);
    real_type t101 = w_D_2(t4, t6);
    real_type t108 = v_D_3(t4, t5, t6);
    result__[ 2   ] = -0.10e1 * t27 * t19 * (t5 * t95 * t3 + t11 * t98 / 2 + t101 * t14 / 2) + 0.10e1 * t108 * t40 * t37 - 0.5e0 * t108 * t53 * t47 + 0.5e0 * (-2 * t101 * t30 * t3 - 2 * t11 * t95 * t3 + t5 * t98) * t57 * t46;
    result__[ 3   ] = -0.10e1 * t57 * t36;
    real_type t129 = t52 * t26;
    result__[ 4   ] = 0.5e0 * t129 * t23 * t19;
    result__[ 5   ] = result__[0];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = result__[3];
    result__[ 9   ] = result__[4];
    result__[ 10  ] = t129 * t23 * t45 - 2 * t57 * t21 * t35;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 11, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DgDu_numRows() const
  { return 1; }

  integer
  HangGlider::DgDu_numCols() const
  { return 1; }

  integer
  HangGlider::DgDu_nnz() const
  { return 1; }

  void
  HangGlider::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDu_sparse(
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
    real_type t3   = ModelPars[iM_c1];
    real_type t4   = XM__[0];
    real_type t5   = XM__[2];
    real_type t6   = XM__[3];
    real_type t7   = Dfun(t4, t5, t6);
    real_type t10  = P__[iP_T];
    real_type t14  = 1.0 / ModelPars[iM_m];
    real_type t15  = v(t4, t5, t6);
    real_type t16  = 1.0 / t15;
    real_type t25  = w(t4, t6);
    real_type t33  = ALIAS_cLControl_D_1_1(UM__[0], ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    result__[ 0   ] = -2 * t25 * t7 * t3 * t16 * t14 * t10 * LM__[3] - 2 * t16 * t14 * LM__[2] * t10 * t5 * t7 * t3 + t33 + 2 * ModelPars[iM_W];
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
  HangGlider::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "HangGlider::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
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
  HangGlider::DuDxlxlp_full_analytic(
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
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_0_10 = 0.0e0;
    real_type tmp_0_11 = 0.0e0;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_0_16 = 0.0e0;
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
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 17 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  HangGlider::m_eval(
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
    real_type t2   = Tbound(t1);
    real_type t3   = U__[iU_cL];
    real_type t6   = cLControl(t3, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t7   = X__[iX_vx];
    real_type t11  = pow(-t7 * t1 + V__[0], 2);
    real_type t12  = X__[iX_vy];
    real_type t16  = pow(-t12 * t1 + V__[1], 2);
    real_type t20  = 1.0 / ModelPars[iM_m] * t1;
    real_type t21  = X__[iX_x];
    real_type t22  = v(t21, t7, t12);
    real_type t23  = 1.0 / t22;
    real_type t25  = t3 * t3;
    real_type t29  = Dfun(t21, t7, t12);
    real_type t30  = t29 * (t25 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t32  = Lfun(t21, t7, t12);
    real_type t33  = t32 * t3;
    real_type t34  = w(t21, t12);
    real_type t40  = pow(V__[2] - (-t7 * t30 - t34 * t33) * t23 * t20, 2);
    real_type t50  = pow(V__[3] - (-t34 * t30 + t7 * t33) * t23 * t20 + ModelPars[iM_g] * t1, 2);
    real_type result__ = t2 + t6 + t11 + t16 + t40 + t50;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DmDu_numEqns() const
  { return 1; }

  void
  HangGlider::DmDu_eval(
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
    real_type t1   = U__[iU_cL];
    real_type t4   = ALIAS_cLControl_D_1(t1, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t6   = P__[iP_T];
    real_type t8   = 1.0 / ModelPars[iM_m];
    real_type t9   = t8 * t6;
    real_type t10  = X__[iX_x];
    real_type t11  = X__[iX_vx];
    real_type t12  = X__[iX_vy];
    real_type t13  = v(t10, t11, t12);
    real_type t14  = 1.0 / t13;
    real_type t15  = ModelPars[iM_c1];
    real_type t16  = t1 * t1;
    real_type t20  = Dfun(t10, t11, t12);
    real_type t21  = t20 * (t16 * t15 + ModelPars[iM_c0]);
    real_type t23  = Lfun(t10, t11, t12);
    real_type t24  = t23 * t1;
    real_type t25  = w(t10, t12);
    real_type t32  = t14 * t8;
    real_type t33  = t1 * t15;
    result__[ 0   ] = t4 - 2 * (-2 * t11 * t20 * t33 - t25 * t23) * t32 * t6 * (V__[2] - (-t11 * t21 - t25 * t24) * t14 * t9) - 2 * (-2 * t25 * t20 * t33 + t11 * t23) * t32 * t6 * (V__[3] - (t11 * t24 - t25 * t21) * t14 * t9 + ModelPars[iM_g] * t6);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DmDuu_numRows() const
  { return 1; }

  integer
  HangGlider::DmDuu_numCols() const
  { return 1; }

  integer
  HangGlider::DmDuu_nnz() const
  { return 1; }

  void
  HangGlider::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DmDuu_sparse(
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
    real_type t1   = U__[iU_cL];
    real_type t4   = ALIAS_cLControl_D_1_1(t1, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t5   = P__[iP_T];
    real_type t6   = t5 * t5;
    real_type t7   = ModelPars[iM_m];
    real_type t8   = t7 * t7;
    real_type t10  = 1.0 / t8 * t6;
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vx];
    real_type t13  = X__[iX_vy];
    real_type t14  = v(t11, t12, t13);
    real_type t15  = t14 * t14;
    real_type t16  = 1.0 / t15;
    real_type t17  = ModelPars[iM_c1];
    real_type t18  = t1 * t17;
    real_type t19  = Dfun(t11, t12, t13);
    real_type t20  = t12 * t19;
    real_type t23  = Lfun(t11, t12, t13);
    real_type t24  = w(t11, t13);
    real_type t27  = pow(-2 * t20 * t18 - t24 * t23, 2);
    real_type t32  = 1.0 / t7;
    real_type t33  = t32 * t5;
    real_type t34  = 1.0 / t14;
    real_type t35  = t1 * t1;
    real_type t39  = t19 * (t35 * t17 + ModelPars[iM_c0]);
    real_type t41  = t23 * t1;
    real_type t49  = t17 * t34;
    real_type t53  = t24 * t19;
    real_type t58  = pow(t12 * t23 - 2 * t53 * t18, 2);
    result__[ 0   ] = t4 + 2 * t27 * t16 * t10 + 4 * t20 * t49 * t32 * t5 * (V__[2] - (-t12 * t39 - t24 * t41) * t34 * t33) + 2 * t58 * t16 * t10 + 4 * t53 * t49 * t32 * t5 * (V__[3] - (t12 * t41 - t24 * t39) * t34 * t33 + ModelPars[iM_g] * t5);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: HangGlider_Methods_controls.cc
