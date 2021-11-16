/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_controls.cc                                 |
 |                                                                       |
 |  version: 1.0   date 16/11/2021                                       |
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

  integer
  HangGlider::g_numEqns() const
  { return 1; }

  void
  HangGlider::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_cL];
    real_type t7   = t2 * ModelPars[iM_c1];
    real_type t8   = X__[iX_x];
    real_type t9   = X__[iX_vx];
    real_type t10  = X__[iX_vy];
    real_type t11  = Dfun(t8, t9, t10);
    real_type t14  = Lfun(t8, t9, t10);
    real_type t15  = w(t8, t10);
    real_type t21  = P__[iP_T];
    real_type t23  = 1.0 / ModelPars[iM_m];
    real_type t25  = v(t8, t9, t10);
    real_type t26  = 1.0 / t25;
    real_type t42  = ALIAS_cLControl_D_1(t2, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] - 2 * t26 * t23 * t21 * L__[iL_lambda3__xo] * (t9 * t11 * t7 + t15 * t14 / 2) + (-2 * t15 * t11 * t7 + t9 * t14) * t26 * t23 * t21 * L__[iL_lambda4__xo] + t42;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  HangGlider::DgDxlp_numRows() const
  { return 1; }

  integer
  HangGlider::DgDxlp_numCols() const
  { return 9; }

  integer
  HangGlider::DgDxlp_nnz() const
  { return 6; }

  void
  HangGlider::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = X__[iX_x];
    real_type t3   = X__[iX_vy];
    real_type t4   = w_D_1(t2, t3);
    real_type t5   = L__[iL_lambda4__xo];
    real_type t7   = U__[iU_cL];
    real_type t8   = ModelPars[iM_c1];
    real_type t9   = t8 * t7;
    real_type t10  = X__[iX_vx];
    real_type t11  = Dfun(t2, t10, t3);
    real_type t12  = t11 * t9;
    real_type t15  = L__[iL_lambda3__xo];
    real_type t17  = Lfun(t2, t10, t3);
    real_type t20  = w(t2, t3);
    real_type t22  = t10 * t15 + t20 * t5;
    real_type t23  = Dfun_D_1(t2, t10, t3);
    real_type t27  = Lfun_D_1(t2, t10, t3);
    real_type t30  = -t10 * t5 + t20 * t15;
    real_type t33  = v(t2, t10, t3);
    real_type t35  = v_D_1(t2, t10, t3);
    real_type t40  = 2 * t11 * t22 * t9 + t30 * t17;
    real_type t45  = 1.0 / ModelPars[iM_m];
    real_type t46  = t33 * t33;
    real_type t48  = 1.0 / t46 * t45;
    result__[ 0   ] = -t48 * (t33 * (2 * t12 * t5 * t4 + t17 * t4 * t15 + 2 * t23 * t22 * t9 + t30 * t27) - t40 * t35) * t1;
    real_type t55  = Dfun_D_2(t2, t10, t3);
    real_type t59  = Lfun_D_2(t2, t10, t3);
    real_type t63  = v_D_2(t2, t10, t3);
    result__[ 1   ] = -t48 * t1 * (t33 * (2 * t11 * t8 * t7 * t15 + 2 * t55 * t22 * t9 - t17 * t5 + t30 * t59) - t40 * t63);
    real_type t68  = w_D_2(t2, t3);
    real_type t74  = Dfun_D_3(t2, t10, t3);
    real_type t78  = Lfun_D_3(t2, t10, t3);
    real_type t82  = v_D_3(t2, t10, t3);
    result__[ 2   ] = -t48 * (t33 * (2 * t12 * t5 * t68 + t17 * t68 * t15 + 2 * t74 * t22 * t9 + t30 * t78) - t40 * t82) * t1;
    real_type t88  = 1.0 / t33;
    result__[ 3   ] = (-2 * t10 * t11 * t9 - t20 * t17) * t88 * t45 * t1;
    result__[ 4   ] = -2 * t88 * t45 * (t20 * t11 * t9 - t10 * t17 / 2) * t1;
    result__[ 5   ] = -t88 * t45 * t40;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 6, i_segment );
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
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDu_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_m];
    real_type t5   = ALIAS_cLControl_D_1_1(U__[iU_cL], ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t10  = X__[iX_x];
    real_type t11  = X__[iX_vx];
    real_type t12  = X__[iX_vy];
    real_type t13  = v(t10, t11, t12);
    real_type t15  = Dfun(t10, t11, t12);
    real_type t22  = w(t10, t12);
    result__[ 0   ] = 1.0 / t13 / t1 * (t13 * (t5 + 2 * ModelPars[iM_W]) * t1 - 2 * (t11 * L__[iL_lambda3__xo] + t22 * L__[iL_lambda4__xo]) * ModelPars[iM_c1] * P__[iP_T] * t15);
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
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    U__[ iU_cL ] = 0;
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
  HangGlider::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type tmp_0_0 = 0;
    real_type tmp_0_1 = 0;
    real_type tmp_0_2 = 0;
    real_type tmp_0_3 = 0;
    real_type tmp_0_4 = 0;
    real_type tmp_0_5 = 0;
    real_type tmp_0_6 = 0;
    real_type tmp_0_7 = 0;
    real_type tmp_0_8 = 0;
    real_type tmp_0_9 = 0;
    real_type tmp_0_10 = 0;
    real_type tmp_0_11 = 0;
    real_type tmp_0_12 = 0;
    real_type tmp_0_13 = 0;
    real_type tmp_0_14 = 0;
    real_type tmp_0_15 = 0;
    real_type tmp_0_16 = 0;
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = U__[iU_cL];
    real_type t4   = ALIAS_cLControl_D_1(t1, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t5   = ModelPars[iM_m];
    real_type t6   = t5 * t5;
    real_type t8   = X__[iX_x];
    real_type t9   = X__[iX_vx];
    real_type t10  = X__[iX_vy];
    real_type t11  = v(t8, t9, t10);
    real_type t12  = t11 * t11;
    real_type t14  = ModelPars[iM_c1];
    real_type t16  = P__[iP_T];
    real_type t20  = ModelPars[iM_g] * t16 + V__[3];
    real_type t21  = w(t8, t10);
    real_type t23  = V__[2];
    real_type t26  = Dfun(t8, t9, t10);
    real_type t29  = Lfun(t8, t9, t10);
    real_type t40  = t1 * t1;
    real_type t45  = t26 * t26;
    real_type t47  = t29 * t29;
    real_type t51  = t16 * t16;
    real_type t52  = t21 * t21;
    real_type t53  = t9 * t9;
    result__[ 0   ] = 1.0 / t12 / t6 * (t12 * t6 * t4 + 4 * t11 * t5 * t16 * (t26 * (t21 * t20 + t9 * t23) * t14 * t1 - (t20 * t9 - t21 * t23) * t29 / 2) + 4 * (t52 + t53) * t51 * (t45 * (t40 * t14 + ModelPars[iM_c0]) * t14 + t47 / 2) * t1);
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
    integer_ptr iIndex,
    integer_ptr jIndex
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
    real_ptr             result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_c1];
    real_type t2   = U__[iU_cL];
    real_type t3   = t2 * t2;
    real_type t9   = P__[iP_T];
    real_type t10  = t9 * t9;
    real_type t11  = X__[iX_x];
    real_type t12  = X__[iX_vy];
    real_type t13  = w(t11, t12);
    real_type t14  = t13 * t13;
    real_type t15  = X__[iX_vx];
    real_type t16  = t15 * t15;
    real_type t17  = t14 + t16;
    real_type t19  = Dfun(t11, t15, t12);
    real_type t20  = t19 * t19;
    real_type t33  = v(t11, t15, t12);
    real_type t35  = ModelPars[iM_m];
    real_type t42  = ALIAS_cLControl_D_1_1(t2, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t43  = t35 * t35;
    real_type t45  = t33 * t33;
    real_type t47  = Lfun(t11, t15, t12);
    real_type t48  = t47 * t47;
    result__[ 0   ] = 1.0 / t45 / t43 * (12 * t20 * t17 * t10 * t1 * (t3 * t1 + ModelPars[iM_c0] / 3) + 4 * t19 * t35 * t9 * t33 * (t13 * (ModelPars[iM_g] * t9 + V__[3]) + t15 * V__[2]) * t1 + t45 * t43 * t42 + 2 * t17 * t48 * t10);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: HangGlider_Methods_controls.cc
