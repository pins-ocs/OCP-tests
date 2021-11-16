/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods_controls.cc                                     |
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


#include "Bike1D.hh"
#include "Bike1D_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vMinLimit_DD(__t1) vMinLimit.DD( __t1)
#define ALIAS_vMinLimit_D(__t1) vMinLimit.D( __t1)
#define ALIAS_mufControl_D_3(__t1, __t2, __t3) mufControl.D_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2(__t1, __t2, __t3) mufControl.D_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1(__t1, __t2, __t3) mufControl.D_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3_3(__t1, __t2, __t3) mufControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_3(__t1, __t2, __t3) mufControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_2(__t1, __t2, __t3) mufControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_3(__t1, __t2, __t3) mufControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_2(__t1, __t2, __t3) mufControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_1(__t1, __t2, __t3) mufControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3(__t1, __t2, __t3) murControl.D_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2(__t1, __t2, __t3) murControl.D_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1(__t1, __t2, __t3) murControl.D_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3_3(__t1, __t2, __t3) murControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_3(__t1, __t2, __t3) murControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_2(__t1, __t2, __t3) murControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_3(__t1, __t2, __t3) murControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_2(__t1, __t2, __t3) murControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_1(__t1, __t2, __t3) murControl.D_1_1( __t1, __t2, __t3)


namespace Bike1DDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  Bike1D::g_numEqns() const
  { return 2; }

  void
  Bike1D::g_eval(
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
    real_type t3   = L__[iL_lambda1__xo] * ModelPars[iM_g];
    real_type t4   = X__[iX_v];
    real_type t5   = 1.0 / t4;
    real_type t8   = Tmax_normalized(t4);
    real_type t10  = clip(t8, 0, ModelPars[iM_mur_max]);
    real_type t11  = ALIAS_murControl_D_1(U__[iU_mur], ModelPars[iM_mur_min], t10);
    result__[ 0   ] = t11 * t5 + t3;
    real_type t15  = ALIAS_mufControl_D_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t15 * t5 + t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::DgDxlp_numRows() const
  { return 2; }

  integer
  Bike1D::DgDxlp_numCols() const
  { return 2; }

  integer
  Bike1D::DgDxlp_nnz() const
  { return 4; }

  void
  Bike1D::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDxlp_sparse(
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
    real_type t1   = U__[iU_mur];
    real_type t2   = ModelPars[iM_mur_min];
    real_type t3   = X__[iX_v];
    real_type t4   = Tmax_normalized(t3);
    real_type t5   = ModelPars[iM_mur_max];
    real_type t6   = clip(t4, 0, t5);
    real_type t7   = ALIAS_murControl_D_1_3(t1, t2, t6);
    real_type t8   = ALIAS_clip_D_1(t4, 0, t5);
    real_type t10  = Tmax_normalized_D(t3);
    real_type t13  = ALIAS_murControl_D_1(t1, t2, t6);
    real_type t15  = t3 * t3;
    real_type t16  = 1.0 / t15;
    result__[ 0   ] = t16 * (t3 * t10 * t8 * t7 - t13);
    result__[ 1   ] = ModelPars[iM_g];
    real_type t19  = ALIAS_mufControl_D_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 2   ] = -t19 * t16;
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::DgDu_numRows() const
  { return 2; }

  integer
  Bike1D::DgDu_numCols() const
  { return 2; }

  integer
  Bike1D::DgDu_nnz() const
  { return 2; }

  void
  Bike1D::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDu_sparse(
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
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1_1(U__[iU_mur], ModelPars[iM_mur_min], t7);
    result__[ 0   ] = t8 * t2;
    real_type t11  = ALIAS_mufControl_D_1_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t11 * t2;
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
  Bike1D::u_eval_analytic(
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
    real_type X__[1];
    real_type L__[1];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_v];
    real_type t2   = XR__[iX_v];
    real_type t12  = 1.0 / (t1 + t2) * (LL__[iL_lambda1__xo] + LR__[iL_lambda1__xo]) * ModelPars[iM_g] * t2 * t1;
    real_type t15  = Tmax_normalized(X__[iX_v]);
    real_type t17  = clip(t15, 0, ModelPars[iM_mur_max]);
    U__[ iU_mur ] = murControl.solve(-t12, ModelPars[iM_mur_min], t17);
    U__[ iU_muf ] = mufControl.solve(-t12, ModelPars[iM_muf_min], 0);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
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
  Bike1D::DuDxlxlp_full_analytic(
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
    real_type X__[1];
    real_type L__[1];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_v];
    real_type t2   = XR__[iX_v];
    real_type t4   = ModelPars[iM_g];
    real_type t8   = (LL__[iL_lambda1__xo] + LR__[iL_lambda1__xo]) * t4;
    real_type t9   = t1 + t2;
    real_type t10  = 1.0 / t9;
    real_type t12  = t10 * t8 * t2 * t1;
    real_type t15  = Tmax_normalized(X__[iX_v]);
    real_type t17  = clip(t15, 0, ModelPars[iM_mur_max]);
    real_type t18  = murControl.solve_rhs(-t12, ModelPars[iM_mur_min], t17);
    real_type t19  = t2 * t2;
    real_type t21  = t9 * t9;
    real_type t23  = 1.0 / t21 * t8;
    real_type tmp_0_0 = -t23 * t19 * t18;
    real_type t26  = mufControl.solve_rhs(-t12, ModelPars[iM_muf_min], 0);
    real_type tmp_1_0 = -t23 * t19 * t26;
    real_type t31  = t10 * t4 * t2;
    real_type tmp_0_1 = -t31 * t1 * t18;
    real_type tmp_1_1 = -t31 * t1 * t26;
    real_type t35  = t1 * t1;
    real_type tmp_0_2 = -t23 * t35 * t18;
    real_type tmp_1_2 = -t23 * t35 * t26;
    real_type tmp_0_3 = tmp_0_1;
    real_type tmp_1_3 = tmp_1_1;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 8 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Bike1D::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = vMinLimit(t1 - ModelPars[iM_v_min]);
    real_type t7   = U__[iU_mur];
    real_type t9   = Tmax_normalized(t1);
    real_type t11  = clip(t9, 0, ModelPars[iM_mur_max]);
    real_type t12  = murControl(t7, ModelPars[iM_mur_min], t11);
    real_type t14  = U__[iU_muf];
    real_type t16  = mufControl(t14, ModelPars[iM_muf_min], 0);
    real_type t24  = pow((t7 + t14) * ModelPars[iM_g] - V__[0] * t1, 2);
    real_type result__ = t12 * t2 + t16 * t2 + t5 * t2 + t24;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::DmDu_numEqns() const
  { return 2; }

  void
  Bike1D::DmDu_eval(
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
    real_type t1   = U__[iU_mur];
    real_type t3   = X__[iX_v];
    real_type t4   = Tmax_normalized(t3);
    real_type t6   = clip(t4, 0, ModelPars[iM_mur_max]);
    real_type t7   = ALIAS_murControl_D_1(t1, ModelPars[iM_mur_min], t6);
    real_type t9   = t3 * t3;
    real_type t11  = ModelPars[iM_g];
    real_type t13  = 2 * t11 * t9 * V__[0];
    real_type t14  = U__[iU_muf];
    real_type t17  = t11 * t11;
    real_type t19  = t3 * t17 * (2 * t1 + 2 * t14);
    real_type t21  = 1.0 / t3;
    result__[ 0   ] = t21 * (t7 - t13 + t19);
    real_type t23  = ALIAS_mufControl_D_1(t14, ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t21 * (t23 - t13 + t19);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Bike1D::DmDuu_numRows() const
  { return 2; }

  integer
  Bike1D::DmDuu_numCols() const
  { return 2; }

  integer
  Bike1D::DmDuu_nnz() const
  { return 4; }

  void
  Bike1D::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DmDuu_sparse(
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
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1_1(U__[iU_mur], ModelPars[iM_mur_min], t7);
    real_type t11  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t12  = 2 * t11;
    result__[ 0   ] = t8 * t2 + t12;
    result__[ 1   ] = t12;
    result__[ 2   ] = result__[1];
    real_type t15  = ALIAS_mufControl_D_1_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 3   ] = t15 * t2 + result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: Bike1D_Methods_controls.cc
