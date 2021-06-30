/*-----------------------------------------------------------------------*\
 |  file: EconomicGrowthModel2_Methods_controls.cc                       |
 |                                                                       |
 |  version: 1.0   date 5/7/2021                                         |
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
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t1   = XM__[4];
    real_type t3   = ALIAS_uControl_D_1(UM__[0], 0, 1);
    real_type t8   = Q(XM__[0], XM__[1]);
    real_type t6   = t8 * t1;
    result__[ 0   ] = t3 * t1 + LM__[1] * t6 - LM__[3] * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  EconomicGrowthModel2::DgDxlxlp_numRows() const
  { return 1; }

  integer
  EconomicGrowthModel2::DgDxlxlp_numCols() const
  { return 20; }

  integer
  EconomicGrowthModel2::DgDxlxlp_nnz() const
  { return 10; }

  void
  EconomicGrowthModel2::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 10  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 11  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 14  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 16  ;
    iIndex[9 ] = 0   ; jIndex[9 ] = 18  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t1   = LM__[1];
    real_type t2   = XM__[0];
    real_type t3   = XM__[1];
    real_type t4   = Q_D_1(t2, t3);
    real_type t6   = XM__[4];
    real_type t9   = LM__[3];
    real_type t5   = t4 * t6;
    result__[ 0   ] = 0.5e0 * t1 * t5 - 0.5e0 * t9 * t5;
    real_type t13  = Q_D_2(t2, t3);
    real_type t12  = t13 * t6;
    result__[ 1   ] = 0.5e0 * t1 * t12 - 0.5e0 * t9 * t12;
    real_type t21  = ALIAS_uControl_D_1(UM__[0], 0, 1);
    real_type t23  = Q(t2, t3);
    result__[ 2   ] = 0.5e0 * t21 + 0.5e0 * t23 * t1 - 0.5e0 * t9 * t23;
    result__[ 3   ] = 0.5e0 * t6 * t23;
    real_type t27  = result__[3];
    result__[ 4   ] = -t27;
    result__[ 5   ] = result__[0];
    result__[ 6   ] = result__[1];
    result__[ 7   ] = result__[2];
    result__[ 8   ] = t27;
    result__[ 9   ] = result__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 10, i_segment );
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
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  EconomicGrowthModel2::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t3   = ALIAS_uControl_D_1_1(UM__[0], 0, 1);
    result__[ 0   ] = t3 * XM__[4];
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
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
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
    real_type t3   = Q(XM__[0], XM__[1]);
    U__[ iU_u ] = uControl.solve(-(LM__[1] - LM__[3]) * t3, 0, 1);
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
    U_const_pointer_type       UM__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
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
    real_type t1   = XM__[0];
    real_type t2   = XM__[1];
    real_type t3   = Q(t1, t2);
    real_type t6   = LM__[1] - LM__[3];
    real_type t8   = uControl.solve_rhs(-t6 * t3, 0, 1);
    real_type t9   = Q_D_1(t1, t2);
    real_type tmp_0_0 = -0.5e0 * t6 * t9 * t8;
    real_type t13  = Q_D_2(t1, t2);
    real_type tmp_0_1 = -0.5e0 * t6 * t13 * t8;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type t18  = 0.5e0 * t8 * t3;
    real_type tmp_0_6 = -t18;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_0_8 = t18;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_0_10 = tmp_0_0;
    real_type tmp_0_11 = tmp_0_1;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_0_16 = tmp_0_6;
    real_type tmp_0_17 = 0.0e0;
    real_type tmp_0_18 = tmp_0_8;
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
  EconomicGrowthModel2::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_T];
    real_type t2   = Tpositive(t1);
    real_type t3   = U__[iU_u];
    real_type t4   = uControl(t3, 0, 1);
    real_type t10  = pow(-t1 * X__[iX_y1] + V__[0], 2);
    real_type t14  = Q(X__[iX_x1], X__[iX_x2]);
    real_type t18  = pow(-t1 * t14 * t3 + V__[2], 2);
    real_type t23  = pow(-t1 * X__[iX_y2] + V__[1], 2);
    real_type t29  = pow(V__[3] - t1 * t14 * (1 - t3), 2);
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
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_T];
    real_type t2   = U__[iU_u];
    real_type t3   = ALIAS_uControl_D_1(t2, 0, 1);
    real_type t8   = Q(X__[iX_x1], X__[iX_x2]);
    real_type t7   = t8 * t1;
    result__[ 0   ] = t3 * t1 - 2 * (-t2 * t7 + V__[2]) * t7 + 2 * (V__[3] - (1 - t2) * t7) * t7;
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
    integer iIndex[],
    integer jIndex[]
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
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
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
