/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_controls.cc                      |
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
#pragma warning( disable : 4189 )
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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * LM__[0];
    real_type t4   = XL__[iX_x1];
    real_type t5   = XL__[iX_x2];
    real_type t6   = g1(t4, t5);
    real_type t7   = g4(t4, t5);
    real_type t10  = UM__[0];
    real_type t12  = t10 - 2 * t5;
    real_type t19  = t2 * LM__[1];
    real_type t20  = g3(t4, t5);
    real_type t26  = uControl(t10, 0, 8);
    real_type t29  = XR__[iX_x1];
    real_type t30  = XR__[iX_x2];
    real_type t31  = g1(t29, t30);
    real_type t32  = g4(t29, t30);
    real_type t36  = t10 - 2 * t30;
    real_type t42  = g3(t29, t30);
    real_type result__ = ((0.2e-1 - t4) * t7 + 0.464e2 * t12 * t4) * t6 * t3 + (t12 * t20 + 0.928e0 - 0.464e2 * t4) * t6 * t19 + 2 * t26 * t2 + ((0.2e-1 - t29) * t32 + 0.464e2 * t36 * t29) * t31 * t3 + (t36 * t42 + 0.928e0 - 0.464e2 * t29) * t31 * t19;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::g_numEqns() const { return 1; }

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
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * LM__[0];
    real_type t4   = XL__[iX_x1];
    real_type t5   = XL__[iX_x2];
    real_type t6   = g1(t4, t5);
    real_type t11  = t2 * LM__[1];
    real_type t12  = g3(t4, t5);
    real_type t16  = ALIAS_uControl_D_1(UM__[0], 0, 8);
    real_type t19  = XR__[iX_x1];
    real_type t20  = XR__[iX_x2];
    real_type t21  = g1(t19, t20);
    real_type t25  = g3(t19, t20);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t3 + t12 * t6 * t11 + 2 * t16 * t2 + 0.464e2 * t19 * t21 * t3 + t25 * t21 * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DgDxlxlp_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DgDxlxlp_numCols() const { return 9; }
  integer LUUS_DrugDisplacement::DgDxlxlp_nnz()     const { return 9; }

  void
  LUUS_DrugDisplacement::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
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
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t4   = XL__[iX_x1];
    real_type t5   = XL__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t10  = g1(t4, t5);
    real_type t13  = LM__[1];
    real_type t14  = t2 * t13;
    real_type t15  = g3(t4, t5);
    real_type t18  = g3_D_1(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t3 + 0.464e2 * t10 * t3 + t15 * t6 * t14 + t18 * t10 * t14;
    real_type t21  = g1_D_2(t4, t5);
    real_type t27  = g3_D_2(t4, t5);
    result__[ 1   ] = 0.464e2 * t4 * t21 * t3 + t15 * t21 * t14 + t27 * t10 * t14;
    real_type t30  = t10 * t2;
    real_type t33  = XR__[iX_x1];
    real_type t34  = XR__[iX_x2];
    real_type t35  = g1(t33, t34);
    real_type t36  = t35 * t2;
    result__[ 2   ] = 0.2320e2 * t4 * t30 + 0.2320e2 * t33 * t36;
    real_type t41  = g3(t33, t34);
    result__[ 3   ] = 0.5e0 * t15 * t30 + 0.5e0 * t41 * t36;
    real_type t44  = g1_D_1(t33, t34);
    real_type t52  = g3_D_1(t33, t34);
    result__[ 4   ] = 0.464e2 * t33 * t44 * t3 + 0.464e2 * t35 * t3 + t41 * t44 * t14 + t52 * t35 * t14;
    real_type t55  = g1_D_2(t33, t34);
    real_type t61  = g3_D_2(t33, t34);
    result__[ 5   ] = 0.464e2 * t33 * t55 * t3 + t41 * t55 * t14 + t61 * t35 * t14;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    real_type t70  = ALIAS_uControl_D_1(UM__[0], 0, 8);
    result__[ 8   ] = 0.464e2 * t4 * t10 * t1 + t15 * t10 * t13 + 2 * t70 + 0.464e2 * t33 * t35 * t1 + t41 * t35 * t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DgDu_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DgDu_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DgDu_nnz()     const { return 1; }

  void
  LUUS_DrugDisplacement::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
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
    result__[ 0   ] = 2 * t3 * P__[iP_T];
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
    real_type t1   = LM__[0];
    real_type t2   = XL__[iX_x1];
    real_type t3   = XL__[iX_x2];
    real_type t4   = g1(t2, t3);
    real_type t8   = XR__[iX_x1];
    real_type t9   = XR__[iX_x2];
    real_type t10  = g1(t8, t9);
    real_type t14  = LM__[1];
    real_type t16  = g3(t2, t3);
    real_type t20  = g3(t8, t9);
    U__[ iU_u ] = uControl.solve(-0.2320000000e2 * t2 * t4 * t1 - 0.2320000000e2 * t8 * t10 * t1 - 0.5000000000e0 * t16 * t4 * t14 - 0.5000000000e0 * t20 * t10 * t14, 0, 8);
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
    real_type result__ = t3 * t1 + t20 + t28;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::DmDu_numEqns() const { return 1; }

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
    result__[ 0   ] = t3 * t1 - 0.928e2 * t6 * t8 * t1 * (V__[0] - ((0.2e-1 - t6) * t10 + 0.464e2 * t14 * t6) * t9) - 2 * t25 * t8 * t1 * (V__[1] - (t14 * t25 + 0.928e0 - 0.464e2 * t6) * t9);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DmDuu_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DmDuu_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DmDuu_nnz()     const { return 1; }

  void
  LUUS_DrugDisplacement::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


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
