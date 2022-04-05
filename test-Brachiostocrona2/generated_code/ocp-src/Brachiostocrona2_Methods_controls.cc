/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods_controls.cc                           |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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
#define ALIAS_TimePositive_DD(__t1) TimePositive.DD( __t1)
#define ALIAS_TimePositive_D(__t1) TimePositive.D( __t1)


namespace Brachiostocrona2Define {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Brachiostocrona2::g_fun_eval(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[0];
    real_type t5   = pow(t2 - ModelPars[iM_theta0], 2);
    real_type t8   = P__[iP_T];
    real_type t10  = XM__[2];
    real_type t11  = cos(t2);
    real_type t16  = sin(t2);
    real_type t24  = TimePositive(-t8);
    real_type result__ = t11 * t10 * t8 * LM__[0] + t16 * t10 * t8 * LM__[1] - t16 * ModelPars[iM_g] * t8 * LM__[2] + t5 * ModelPars[iM_epsi] + t24;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona2::g_numEqns() const { return 1; }

  void
  Brachiostocrona2::g_eval(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = UM__[0];
    real_type t8   = P__[iP_T];
    real_type t10  = XM__[2];
    real_type t11  = sin(t2);
    real_type t16  = cos(t2);
    result__[ 0   ] = 2 * (t2 - ModelPars[iM_theta0]) * ModelPars[iM_epsi] - t11 * t10 * t8 * LM__[0] + t16 * t10 * t8 * LM__[1] - t16 * ModelPars[iM_g] * t8 * LM__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DgDxlxlp_numRows() const { return 1; }
  integer Brachiostocrona2::DgDxlxlp_numCols() const { return 13; }
  integer Brachiostocrona2::DgDxlxlp_nnz()     const { return 9; }

  void
  Brachiostocrona2::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 9   ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 10  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 11  ;
    iIndex[8 ] = 0   ; jIndex[8 ] = 12  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DgDxlxlp_sparse(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = LM__[0];
    real_type t2   = P__[iP_T];
    real_type t4   = UM__[0];
    real_type t5   = sin(t4);
    real_type t8   = LM__[1];
    real_type t10  = cos(t4);
    result__[ 0   ] = -0.5e0 * t5 * t2 * t1 + 0.5e0 * t10 * t2 * t8;
    real_type t13  = XM__[2];
    real_type t14  = t13 * t2;
    result__[ 1   ] = -0.5e0 * t5 * t14;
    result__[ 2   ] = 0.5e0 * t10 * t14;
    real_type t18  = ModelPars[iM_g];
    result__[ 3   ] = -0.5e0 * t10 * t18 * t2;
    result__[ 4   ] = result__[0];
    result__[ 5   ] = result__[1];
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[3];
    result__[ 8   ] = -t5 * t13 * t1 + t10 * t13 * t8 - t10 * t18 * LM__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DgDu_numRows() const { return 1; }
  integer Brachiostocrona2::DgDu_numCols() const { return 1; }
  integer Brachiostocrona2::DgDu_nnz()     const { return 1; }

  void
  Brachiostocrona2::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DgDu_sparse(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = P__[iP_T];
    real_type t6   = XM__[2];
    real_type t7   = UM__[0];
    real_type t8   = cos(t7);
    real_type t13  = sin(t7);
    result__[ 0   ] = -t13 * t6 * t4 * LM__[1] + t13 * ModelPars[iM_g] * t4 * LM__[2] - t8 * t6 * t4 * LM__[0] + 2 * ModelPars[iM_epsi];
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
  Brachiostocrona2::u_eval_analytic(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    UTILS_ERROR(
      "Brachiostocrona2::u_eval_analytic\n"
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
  Brachiostocrona2::DuDxlxlp_full_analytic(
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
    real_type QM__[1], XM__[3], LM__[3];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
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
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 13 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Brachiostocrona2::m_eval(
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
    real_type t2   = TimePositive(-t1);
    real_type t5   = X__[iX_v] * t1;
    real_type t6   = U__[iU_theta];
    real_type t7   = cos(t6);
    real_type t10  = pow(-t7 * t5 + V__[0], 2);
    real_type t12  = sin(t6);
    real_type t15  = pow(-t12 * t5 + V__[1], 2);
    real_type t23  = pow(t12 * ModelPars[iM_g] * t1 + ModelPars[iM_mass] * V__[2], 2);
    real_type result__ = t2 + t10 + t15 + t23;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona2::DmDu_numEqns() const { return 1; }

  void
  Brachiostocrona2::DmDu_eval(
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
    real_type t2   = P__[iP_T];
    real_type t3   = X__[iX_v];
    real_type t4   = t3 * t2;
    real_type t5   = U__[iU_theta];
    real_type t6   = cos(t5);
    real_type t10  = sin(t5);
    real_type t22  = ModelPars[iM_g];
    result__[ 0   ] = 2 * t10 * t3 * t2 * (-t6 * t4 + V__[0]) - 2 * t6 * t3 * t2 * (-t10 * t4 + V__[1]) + 2 * t6 * t22 * t2 * (t10 * t22 * t2 + ModelPars[iM_mass] * V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DmDuu_numRows() const { return 1; }
  integer Brachiostocrona2::DmDuu_numCols() const { return 1; }
  integer Brachiostocrona2::DmDuu_nnz()     const { return 1; }

  void
  Brachiostocrona2::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  Brachiostocrona2::DmDuu_sparse(
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
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_v];
    real_type t4   = t3 * t3;
    real_type t5   = t4 * t2;
    real_type t6   = U__[iU_theta];
    real_type t7   = sin(t6);
    real_type t8   = t7 * t7;
    real_type t11  = t3 * t1;
    real_type t12  = cos(t6);
    real_type t18  = t12 * t12;
    real_type t26  = ModelPars[iM_g];
    real_type t27  = t26 * t26;
    result__[ 0   ] = 2 * t8 * t5 + 2 * t12 * t3 * t1 * (-t12 * t11 + V__[0]) + 2 * t18 * t5 + 2 * t7 * t3 * t1 * (-t7 * t11 + V__[1]) + 2 * t18 * t27 * t2 - 2 * t7 * t26 * t1 * (t7 * t26 * t1 + ModelPars[iM_mass] * V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: Brachiostocrona2_Methods_controls.cc
