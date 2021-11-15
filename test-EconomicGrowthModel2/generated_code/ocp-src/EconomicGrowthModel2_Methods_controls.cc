/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_controls.cc                       |
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


#include "EconomicGrowthModel2.hh"
#include "EconomicGrowthModel2_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace EconomicGrowthModel2Define {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  EconomicGrowthModel2::g_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel2::g_eval(
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
    real_type t3   = ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    real_type t6   = Q(X__[iX_x1], X__[iX_x2]);
    result__[ 0   ] = (t3 + (L__[iL_lambda2__xo] - L__[iL_lambda4__xo]) * t6) * X__[iX_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DgDxlp_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel2::DgDxlp_numCols() const
  { return 10; }

  integer
  EconomicGrowthModel2::DgDxlp_nnz() const
  { return 5; }

  void
  EconomicGrowthModel2::DgDxlp_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 8   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DgDxlp_sparse(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    real_type t3   = Q_D_1(t1, t2);
    real_type t4   = X__[iX_T];
    real_type t8   = L__[iL_lambda2__xo] - L__[iL_lambda4__xo];
    result__[ 0   ] = t8 * t4 * t3;
    real_type t9   = Q_D_2(t1, t2);
    result__[ 1   ] = t8 * t4 * t9;
    real_type t12  = ALIAS_uControl_D_1(U__[iU_u], 0, 1);
    real_type t13  = Q(t1, t2);
    result__[ 2   ] = t13 * t8 + t12;
    result__[ 3   ] = t4 * t13;
    result__[ 4   ] = -result__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DgDu_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel2::DgDu_numCols() const
  { return 1; }

  integer
  EconomicGrowthModel2::DgDu_nnz() const
  { return 1; }

  void
  EconomicGrowthModel2::DgDu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DgDu_sparse(
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
    real_type t3   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 1);
    result__[ 0   ] = t3 * X__[iX_T];
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
  EconomicGrowthModel2::u_eval_analytic(
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
    real_type t8   = Q(XL__[iX_x1], XL__[iX_x2]);
    real_type t12  = Q(XR__[iX_x1], XR__[iX_x2]);
    real_type t13  = XR__[iX_T];
    U__[ iU_u ] = uControl.solve(1.0 / (t1 + t13) * (-t8 * (LL__[iL_lambda2__xo] - LL__[iL_lambda4__xo]) * t1 - (LR__[iL_lambda2__xo] - LR__[iL_lambda4__xo]) * t13 * t12), 0, 1);
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
  EconomicGrowthModel2::DuDxlxlp_full_analytic(
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
    real_type t1   = XL__[iX_T];
    real_type t4   = LL__[iL_lambda2__xo] - LL__[iL_lambda4__xo];
    real_type t6   = XL__[iX_x1];
    real_type t7   = XL__[iX_x2];
    real_type t8   = Q(t6, t7);
    real_type t10  = XR__[iX_x1];
    real_type t11  = XR__[iX_x2];
    real_type t12  = Q(t10, t11);
    real_type t13  = XR__[iX_T];
    real_type t17  = LR__[iL_lambda2__xo] - LR__[iL_lambda4__xo];
    real_type t20  = t1 + t13;
    real_type t21  = 1.0 / t20;
    real_type t23  = uControl.solve_rhs(t21 * (-t8 * t4 * t1 - t17 * t13 * t12), 0, 1);
    real_type t24  = t1 * t23;
    real_type t25  = -t4;
    real_type t26  = Q_D_1(t6, t7);
    real_type tmp_0_0 = t21 * t26 * t25 * t24;
    real_type t29  = Q_D_2(t6, t7);
    real_type tmp_0_1 = t21 * t29 * t25 * t24;
    real_type tmp_0_2 = 0;
    real_type tmp_0_3 = 0;
    real_type t35  = (-t17 * t12 + t8 * t4) * t23;
    real_type t36  = t20 * t20;
    real_type t37  = 1.0 / t36;
    real_type tmp_0_4 = -t37 * t13 * t35;
    real_type tmp_0_5 = 0;
    real_type t41  = t21 * t8 * t24;
    real_type tmp_0_6 = -t41;
    real_type tmp_0_7 = 0;
    real_type tmp_0_8 = t41;
    real_type tmp_0_9 = 0;
    real_type t42  = Q_D_1(t10, t11);
    real_type t45  = t21 * t17 * t13;
    real_type tmp_0_10 = -t45 * t42 * t23;
    real_type t47  = Q_D_2(t10, t11);
    real_type tmp_0_11 = -t45 * t47 * t23;
    real_type tmp_0_12 = 0;
    real_type tmp_0_13 = 0;
    real_type tmp_0_14 = t37 * t1 * t35;
    real_type tmp_0_15 = 0;
    real_type t53  = t21 * t13 * t12 * t23;
    real_type tmp_0_16 = -t53;
    real_type tmp_0_17 = 0;
    real_type tmp_0_18 = t53;
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
  EconomicGrowthModel2::m_eval(
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
    real_type t3   = U__[iU_u];
    real_type t4   = uControl(t3, 0, 1);
    real_type t10  = pow(-t1 * X__[iX_y1] + V__[0], 2);
    real_type t14  = Q(X__[iX_x1], X__[iX_x2]);
    real_type t18  = pow(-t1 * t14 * t3 + V__[2], 2);
    real_type t23  = pow(-t1 * X__[iX_y2] + V__[1], 2);
    real_type t29  = pow(t14 * (t3 - 1) * t1 + V__[3], 2);
    real_type t31  = V__[4] * V__[4];
    real_type result__ = t4 * t1 + t10 + t18 + t2 + t23 + t29 + t31;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DmDu_numEqns() const
  { return 1; }

  void
  EconomicGrowthModel2::DmDu_eval(
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
    real_type t1   = X__[iX_T];
    real_type t4   = Q(X__[iX_x1], X__[iX_x2]);
    real_type t5   = t4 * t4;
    real_type t6   = U__[iU_u];
    real_type t18  = ALIAS_uControl_D_1(t6, 0, 1);
    result__[ 0   ] = (4 * t1 * t6 * t5 - 2 * t1 * t5 - 2 * V__[2] * t4 + 2 * V__[3] * t4 + t18) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DmDuu_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel2::DmDuu_numCols() const
  { return 1; }

  integer
  EconomicGrowthModel2::DmDuu_nnz() const
  { return 1; }

  void
  EconomicGrowthModel2::DmDuu_pattern(
    integer_ptr iIndex,
    integer_ptr jIndex
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DmDuu_sparse(
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
    real_type t1   = X__[iX_T];
    real_type t3   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 1);
    real_type t7   = Q(X__[iX_x1], X__[iX_x2]);
    real_type t8   = t7 * t7;
    real_type t9   = t1 * t1;
    result__[ 0   ] = t3 * t1 + 4 * t9 * t8;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: EconomicGrowthModel2_Methods_controls.cc
