/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_controls.cc                      |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace LUUS_DrugDisplacementDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  LUUS_DrugDisplacement::g_fun_eval(
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
    real_type QM__[1], XM__[2], LM__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = UM__[0];
    real_type t2   = XM__[1];
    real_type t5   = LM__[1];
    real_type t7   = XM__[0];
    real_type t8   = g3(t7, t2);
    real_type t12  = LM__[0];
    real_type t14  = g4(t7, t2);
    real_type t25  = g1(t7, t2);
    real_type t27  = uControl(t1, 0, 8);
    real_type result__ = P__[iP_T] * (t25 * (t8 * t5 * (t1 - 2.0 * t2) + t14 * t12 * (0.2e-1 - 1.0 * t7) + t12 * t7 * (0.464e2 * t1 - 0.928e2 * t2) + t5 * (0.928e0 - 0.464e2 * t7)) + t27);
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  integer
  LUUS_DrugDisplacement::g_numEqns() const
  { return 1; }

  void
  LUUS_DrugDisplacement::g_eval(
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
    real_type QM__[1], XM__[2], LM__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = XM__[0];
    real_type t4   = XM__[1];
    real_type t5   = g1(t3, t4);
    real_type t11  = g3(t3, t4);
    real_type t14  = ALIAS_uControl_D_1(UM__[0], 0, 8);
    result__[ 0   ] = (0.464e2 * t3 * t5 * LM__[0] + t11 * t5 * LM__[1] + t14) * P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DgDxlxlp_numRows() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DgDxlxlp_numCols() const
  { return 9; }

  integer
  LUUS_DrugDisplacement::DgDxlxlp_nnz() const
  { return 9; }

  void
  LUUS_DrugDisplacement::DgDxlxlp_pattern(
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
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[2], LM__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t2   = LM__[0];
    real_type t3   = XM__[0];
    real_type t4   = XM__[1];
    real_type t5   = g1_D_1(t3, t4);
    real_type t9   = g1(t3, t4);
    real_type t10  = t9 * t2;
    real_type t12  = LM__[1];
    real_type t14  = g3(t3, t4);
    real_type t16  = t9 * t12;
    real_type t17  = g3_D_1(t3, t4);
    result__[ 0   ] = 0.5e0 * (0.464e2 * t3 * t5 * t2 + 0.464e2 * t10 + t14 * t5 * t12 + t17 * t16) * t1;
    real_type t21  = g1_D_2(t3, t4);
    real_type t27  = g3_D_2(t3, t4);
    result__[ 1   ] = 0.5e0 * (0.464e2 * t3 * t21 * t2 + t14 * t21 * t12 + t27 * t16) * t1;
    real_type t31  = t9 * t1;
    result__[ 2   ] = 0.2320e2 * t3 * t31;
    result__[ 3   ] = 0.5e0 * t14 * t31;
    result__[ 4   ] = result__[0];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    real_type t38  = ALIAS_uControl_D_1(UM__[0], 0, 8);
    result__[ 8   ] = 0.464e2 * t3 * t10 + t14 * t16 + t38;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DgDu_numRows() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DgDu_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DgDu_nnz() const
  { return 1; }

  void
  LUUS_DrugDisplacement::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DgDu_sparse(
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
    real_type QM__[1], XM__[2], LM__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = ALIAS_uControl_D_1_1(UM__[0], 0, 8);
    result__[ 0   ] = t3 * P__[iP_T];
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
  LUUS_DrugDisplacement::u_eval_analytic(
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
    real_type QM__[1], XM__[2], LM__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XM__[0];
    real_type t2   = XM__[1];
    real_type t3   = g1(t1, t2);
    real_type t8   = g3(t1, t2);
    U__[ iU_u ] = uControl.solve(-0.2000000000e0 * (0.232e3 * t1 * LM__[0] + 5.0 * t8 * LM__[1]) * t3, 0, 8);
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
  LUUS_DrugDisplacement::DuDxlxlp_full_analytic(
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
    real_type QM__[1], XM__[2], LM__[2];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XM__[0];
    real_type t2   = XM__[1];
    real_type t3   = g1(t1, t2);
    real_type t4   = LM__[0];
    real_type t7   = LM__[1];
    real_type t8   = g3(t1, t2);
    real_type t11  = 0.232e3 * t1 * t4 + 5.0 * t8 * t7;
    real_type t14  = uControl.solve_rhs(-0.2000000000e0 * t11 * t3, 0, 8);
    real_type t15  = g1_D_1(t1, t2);
    real_type t19  = g3_D_1(t1, t2);
    real_type tmp_0_0 = 0.5e0 * (-0.2000000000e0 * t11 * t15 - 0.2000000000e0 * (0.232e3 * t4 + 5.0 * t19 * t7) * t3) * t14;
    real_type t27  = g1_D_2(t1, t2);
    real_type t31  = g3_D_2(t1, t2);
    real_type tmp_0_1 = 0.5e0 * (-0.2000000000e0 * t11 * t27 - 0.1000000000e1 * t31 * t3 * t7) * t14;
    real_type t36  = t3 * t14;
    real_type tmp_0_2 = -0.2320000000e2 * t1 * t36;
    real_type tmp_0_3 = -0.5000000000e0 * t8 * t36;
    real_type tmp_0_4 = tmp_0_0;
    real_type tmp_0_5 = tmp_0_1;
    real_type tmp_0_6 = tmp_0_2;
    real_type tmp_0_7 = tmp_0_3;
    real_type tmp_0_8 = 0.0e0;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 9 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  LUUS_DrugDisplacement::m_eval(
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
    real_type t2   = U__[iU_u];
    real_type t3   = uControl(t2, 0, 8);
    real_type t6   = X__[iX_x1];
    real_type t7   = X__[iX_x2];
    real_type t8   = g1(t6, t7);
    real_type t9   = t8 * t1;
    real_type t10  = g4(t6, t7);
    real_type t14  = t2 - 2 * t7;
    real_type t20  = pow(V__[0] - ((0.2e-1 - t6) * t10 + 0.464e2 * t14 * t6) * t9, 2);
    real_type t22  = g3(t6, t7);
    real_type t28  = pow(V__[1] - (t14 * t22 + 0.928e0 - 0.464e2 * t6) * t9, 2);
    real_type result__ = t1 * t3 + t20 + t28;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DmDu_numEqns() const
  { return 1; }

  void
  LUUS_DrugDisplacement::DmDu_eval(
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
    real_type t1   = P__[iP_T];
    real_type t2   = U__[iU_u];
    real_type t3   = ALIAS_uControl_D_1(t2, 0, 8);
    real_type t6   = X__[iX_x1];
    real_type t7   = X__[iX_x2];
    real_type t8   = g1(t6, t7);
    real_type t9   = t8 * t1;
    real_type t10  = g4(t6, t7);
    real_type t14  = t2 - 2 * t7;
    real_type t25  = g3(t6, t7);
    result__[ 0   ] = t1 * t3 - 0.928e2 * t6 * t8 * t1 * (V__[0] - ((0.2e-1 - t6) * t10 + 0.464e2 * t14 * t6) * t9) - 2 * t25 * t8 * t1 * (V__[1] - (t14 * t25 + 0.928e0 - 0.464e2 * t6) * t9);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  LUUS_DrugDisplacement::DmDuu_numRows() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DmDuu_numCols() const
  { return 1; }

  integer
  LUUS_DrugDisplacement::DmDuu_nnz() const
  { return 1; }

  void
  LUUS_DrugDisplacement::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DmDuu_sparse(
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
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 8);
    real_type t5   = t1 * t1;
    real_type t6   = X__[iX_x1];
    real_type t7   = X__[iX_x2];
    real_type t8   = g1(t6, t7);
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t5;
    real_type t11  = t6 * t6;
    real_type t14  = g3(t6, t7);
    real_type t15  = t14 * t14;
    result__[ 0   ] = t3 * t1 + 0.430592e4 * t11 * t10 + 2 * t15 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: LUUS_DrugDisplacement_Methods_controls.cc