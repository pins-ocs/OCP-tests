/*-----------------------------------------------------------------------*\
 |  file: Zermelo_Methods_controls.cc                                    |
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


#include "Zermelo.hh"
#include "Zermelo_Pars.hh"

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
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace ZermeloDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  Zermelo::g_numEqns() const
  { return 1; }

  void
  Zermelo::g_eval(
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
    real_type t4   = U__[iU_u];
    real_type t5   = cos(t4);
    real_type t8   = sin(t4);
    result__[ 0   ] = (L__[iL_lambda4__xo] * t5 - L__[iL_lambda3__xo] * t8) * ModelPars[iM_S] * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DgDxlp_numRows() const
  { return 1; }

  integer
  Zermelo::DgDxlp_numCols() const
  { return 10; }

  integer
  Zermelo::DgDxlp_nnz() const
  { return 3; }

  void
  Zermelo::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 7   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DgDxlp_sparse(
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
    real_type t2   = ModelPars[iM_S];
    real_type t4   = U__[iU_u];
    real_type t5   = sin(t4);
    real_type t9   = cos(t4);
    result__[ 0   ] = -t5 * t2 * L__[iL_lambda3__xo] + t9 * t2 * L__[iL_lambda4__xo];
    real_type t12  = t2 * X__[iX_T];
    result__[ 1   ] = -t5 * t12;
    result__[ 2   ] = t9 * t12;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DgDu_numRows() const
  { return 1; }

  integer
  Zermelo::DgDu_numCols() const
  { return 1; }

  integer
  Zermelo::DgDu_nnz() const
  { return 1; }

  void
  Zermelo::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DgDu_sparse(
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
    real_type t4   = U__[iU_u];
    real_type t5   = sin(t4);
    real_type t8   = cos(t4);
    result__[ 0   ] = -(L__[iL_lambda4__xo] * t5 + L__[iL_lambda3__xo] * t8) * ModelPars[iM_S] * X__[iX_T];
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
  Zermelo::u_eval_analytic(
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
    real_type X__[5];
    real_type L__[5];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    L__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_T];
    real_type t4   = XR__[iX_T];
    U__[ iU_u ] = atan(1.0 / (t1 * LL__[iL_lambda3__xo] + t4 * LR__[iL_lambda3__xo]) * (LL__[iL_lambda4__xo] * t1 + LR__[iL_lambda4__xo] * t4));
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
  Zermelo::DuDxlxlp_full_analytic(
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
    real_type X__[5];
    real_type L__[5];
    // Qvars
    Q__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    X__[0] = (XL__[0]+XR__[0])/2;
    X__[1] = (XL__[1]+XR__[1])/2;
    X__[2] = (XL__[2]+XR__[2])/2;
    X__[3] = (XL__[3]+XR__[3])/2;
    X__[4] = (XL__[4]+XR__[4])/2;
    // Lvars
    L__[0] = (LL__[0]+LR__[0])/2;
    L__[1] = (LL__[1]+LR__[1])/2;
    L__[2] = (LL__[2]+LR__[2])/2;
    L__[3] = (LL__[3]+LR__[3])/2;
    L__[4] = (LL__[4]+LR__[4])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type tmp_0_0 = 0;
    real_type tmp_0_1 = 0;
    real_type tmp_0_2 = 0;
    real_type tmp_0_3 = 0;
    real_type t1   = XR__[iX_T];
    real_type t2   = LL__[iL_lambda3__xo];
    real_type t3   = LR__[iL_lambda4__xo];
    real_type t5   = LL__[iL_lambda4__xo];
    real_type t6   = LR__[iL_lambda3__xo];
    real_type t8   = t3 * t2 - t6 * t5;
    real_type t10  = t6 * t6;
    real_type t11  = t3 * t3;
    real_type t13  = t1 * t1;
    real_type t15  = XL__[iX_T];
    real_type t22  = t15 * t15;
    real_type t23  = t2 * t2;
    real_type t24  = t5 * t5;
    real_type t28  = 1.0 / (t13 * (t10 + t11) + 2 * t1 * (t6 * t2 + t3 * t5) * t15 + (t23 + t24) * t22);
    real_type tmp_0_4 = -t28 * t8 * t1;
    real_type tmp_0_5 = 0;
    real_type tmp_0_6 = 0;
    real_type t32  = t3 * t1 + t5 * t15;
    real_type tmp_0_7 = -t28 * t15 * t32;
    real_type t37  = t1 * t6 + t15 * t2;
    real_type t38  = 1.0 / t37;
    real_type t40  = t32 * t32;
    real_type t41  = t37 * t37;
    real_type t45  = 1.0 / (1.0 / t41 * t40 + 1);
    real_type tmp_0_8 = t45 * t38 * t15;
    real_type tmp_0_9 = 0;
    real_type tmp_0_10 = 0;
    real_type tmp_0_11 = 0;
    real_type tmp_0_12 = 0;
    real_type tmp_0_13 = 0;
    real_type tmp_0_14 = t28 * t8 * t15;
    real_type tmp_0_15 = 0;
    real_type tmp_0_16 = 0;
    real_type tmp_0_17 = -t28 * t1 * t32;
    real_type tmp_0_18 = t45 * t38 * t1;
    real_type tmp_0_19 = 0;
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
  Zermelo::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_T];
    real_type t2   = Tpositive(t1);
    real_type t5   = X__[iX_x];
    real_type t6   = X__[iX_y];
    real_type t7   = velX(t5, t6);
    real_type t11  = pow(V__[0] - (X__[iX_vx] + t7) * t1, 2);
    real_type t14  = velY(t5, t6);
    real_type t18  = pow(V__[1] - (X__[iX_vy] + t14) * t1, 2);
    real_type t21  = ModelPars[iM_S] * t1;
    real_type t22  = U__[iU_u];
    real_type t23  = cos(t22);
    real_type t26  = pow(-t23 * t21 + V__[2], 2);
    real_type t28  = sin(t22);
    real_type t31  = pow(-t28 * t21 + V__[3], 2);
    real_type t33  = V__[4] * V__[4];
    real_type result__ = t2 + t11 + t18 + t26 + t31 + t33;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DmDu_numEqns() const
  { return 1; }

  void
  Zermelo::DmDu_eval(
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
    real_type t4   = U__[iU_u];
    real_type t5   = cos(t4);
    real_type t8   = sin(t4);
    result__[ 0   ] = -2 * (V__[3] * t5 - V__[2] * t8) * ModelPars[iM_S] * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  Zermelo::DmDuu_numRows() const
  { return 1; }

  integer
  Zermelo::DmDuu_numCols() const
  { return 1; }

  integer
  Zermelo::DmDuu_nnz() const
  { return 1; }

  void
  Zermelo::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Zermelo::DmDuu_sparse(
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
    real_type t4   = U__[iU_u];
    real_type t5   = sin(t4);
    real_type t8   = cos(t4);
    result__[ 0   ] = 2 * (V__[3] * t5 + V__[2] * t8) * ModelPars[iM_S] * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: Zermelo_Methods_controls.cc
