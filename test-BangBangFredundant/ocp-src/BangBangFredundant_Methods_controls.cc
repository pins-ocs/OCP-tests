/*-----------------------------------------------------------------------*\
 |  file: BangBangFredundant_Methods_controls.cc                         |
 |                                                                       |
 |  version: 1.0   date 3/6/2021                                         |
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


#include "BangBangFredundant.hh"
#include "BangBangFredundant_Pars.hh"

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
#define ALIAS_Flim_DD(__t1) Flim.DD( __t1)
#define ALIAS_Flim_D(__t1) Flim.D( __t1)
#define ALIAS_aF2Control_D_3(__t1, __t2, __t3) aF2Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2(__t1, __t2, __t3) aF2Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1(__t1, __t2, __t3) aF2Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_3_3(__t1, __t2, __t3) aF2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_3(__t1, __t2, __t3) aF2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_2_2(__t1, __t2, __t3) aF2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_3(__t1, __t2, __t3) aF2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_2(__t1, __t2, __t3) aF2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF2Control_D_1_1(__t1, __t2, __t3) aF2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3(__t1, __t2, __t3) aF1Control.D_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2(__t1, __t2, __t3) aF1Control.D_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1(__t1, __t2, __t3) aF1Control.D_1( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_3_3(__t1, __t2, __t3) aF1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_3(__t1, __t2, __t3) aF1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_2_2(__t1, __t2, __t3) aF1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_3(__t1, __t2, __t3) aF1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_2(__t1, __t2, __t3) aF1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_aF1Control_D_1_1(__t1, __t2, __t3) aF1Control.D_1_1( __t1, __t2, __t3)


namespace BangBangFredundantDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  BangBangFredundant::g_numEqns() const
  { return 2; }

  void
  BangBangFredundant::g_eval(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_maxAF];
    real_type t3   = ALIAS_aF1Control_D_1(U__[iU_aF1], -t2, t2);
    result__[ 0   ] = t3 + L__[iL_lambda5__xo];
    real_type t6   = ALIAS_aF2Control_D_1(U__[iU_aF2], -t2, t2);
    result__[ 1   ] = t6 + L__[iL_lambda6__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFredundant::DgDxlp_numRows() const
  { return 2; }

  integer
  BangBangFredundant::DgDxlp_numCols() const
  { return 12; }

  integer
  BangBangFredundant::DgDxlp_nnz() const
  { return 2; }

  void
  BangBangFredundant::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 10  ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 11  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::DgDxlp_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFredundant::DgDu_numRows() const
  { return 2; }

  integer
  BangBangFredundant::DgDu_numCols() const
  { return 2; }

  integer
  BangBangFredundant::DgDu_nnz() const
  { return 2; }

  void
  BangBangFredundant::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::DgDu_sparse(
    NodeType2 const &    NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_maxAF];
    result__[ 0   ] = ALIAS_aF1Control_D_1_1(U__[iU_aF1], -t2, t2);
    result__[ 1   ] = ALIAS_aF2Control_D_1_1(U__[iU_aF2], -t2, t2);
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
  BangBangFredundant::u_eval_analytic(
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
    real_type QM__[1];
    real_type XM__[6];
    real_type LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_maxAF];
    U__[ iU_aF1 ] = aF1Control.solve(-LM__[4], -t2, t2);
    U__[ iU_aF2 ] = aF2Control.solve(-LM__[5], -t2, t2);
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
  BangBangFredundant::DuDxlxlp_full_analytic(
    NodeType2 const &          LEFT__,
    NodeType2 const &          RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlxlp
  ) const {
    real_type const * QL__ = LEFT__.q;
    real_type const * XL__ = LEFT__.x;
    real_type const * LL__ = LEFT__.lambda;
    real_type const * QR__ = RIGHT__.q;
    real_type const * XR__ = RIGHT__.x;
    real_type const * LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1];
    real_type XM__[6];
    real_type LM__[6];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    XM__[1] = (XL__[1]+XR__[1])/2;
    XM__[2] = (XL__[2]+XR__[2])/2;
    XM__[3] = (XL__[3]+XR__[3])/2;
    XM__[4] = (XL__[4]+XR__[4])/2;
    XM__[5] = (XL__[5]+XR__[5])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    LM__[1] = (LL__[1]+LR__[1])/2;
    LM__[2] = (LL__[2]+LR__[2])/2;
    LM__[3] = (LL__[3]+LR__[3])/2;
    LM__[4] = (LL__[4]+LR__[4])/2;
    LM__[5] = (LL__[5]+LR__[5])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_1_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_1_1 = 0.0e0;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_1_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type tmp_1_3 = 0.0e0;
    real_type tmp_0_4 = 0.0e0;
    real_type tmp_1_4 = 0.0e0;
    real_type tmp_0_5 = 0.0e0;
    real_type tmp_1_5 = 0.0e0;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_1_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_1_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_1_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_1_9 = 0.0e0;
    real_type t2   = ModelPars[iM_maxAF];
    real_type t3   = aF1Control.solve_rhs(-LM__[4], -t2, t2);
    real_type tmp_0_10 = -0.5e0 * t3;
    real_type tmp_1_10 = 0.0e0;
    real_type tmp_0_11 = 0.0e0;
    real_type t6   = aF2Control.solve_rhs(-LM__[5], -t2, t2);
    real_type tmp_1_11 = -0.5e0 * t6;
    real_type tmp_0_12 = 0.0e0;
    real_type tmp_1_12 = 0.0e0;
    real_type tmp_0_13 = 0.0e0;
    real_type tmp_1_13 = 0.0e0;
    real_type tmp_0_14 = 0.0e0;
    real_type tmp_1_14 = 0.0e0;
    real_type tmp_0_15 = 0.0e0;
    real_type tmp_1_15 = 0.0e0;
    real_type tmp_0_16 = 0.0e0;
    real_type tmp_1_16 = 0.0e0;
    real_type tmp_0_17 = 0.0e0;
    real_type tmp_1_17 = 0.0e0;
    real_type tmp_0_18 = 0.0e0;
    real_type tmp_1_18 = 0.0e0;
    real_type tmp_0_19 = 0.0e0;
    real_type tmp_1_19 = 0.0e0;
    real_type tmp_0_20 = 0.0e0;
    real_type tmp_1_20 = 0.0e0;
    real_type tmp_0_21 = 0.0e0;
    real_type tmp_1_21 = 0.0e0;
    real_type tmp_0_22 = tmp_0_10;
    real_type tmp_1_22 = 0.0e0;
    real_type tmp_0_23 = 0.0e0;
    real_type tmp_1_23 = tmp_1_11;
    DuDxlxlp(0, 0) = tmp_0_0;
    DuDxlxlp(1, 0) = tmp_1_0;
    DuDxlxlp(0, 1) = tmp_0_1;
    DuDxlxlp(1, 1) = tmp_1_1;
    DuDxlxlp(0, 2) = tmp_0_2;
    DuDxlxlp(1, 2) = tmp_1_2;
    DuDxlxlp(0, 3) = tmp_0_3;
    DuDxlxlp(1, 3) = tmp_1_3;
    DuDxlxlp(0, 4) = tmp_0_4;
    DuDxlxlp(1, 4) = tmp_1_4;
    DuDxlxlp(0, 5) = tmp_0_5;
    DuDxlxlp(1, 5) = tmp_1_5;
    DuDxlxlp(0, 6) = tmp_0_6;
    DuDxlxlp(1, 6) = tmp_1_6;
    DuDxlxlp(0, 7) = tmp_0_7;
    DuDxlxlp(1, 7) = tmp_1_7;
    DuDxlxlp(0, 8) = tmp_0_8;
    DuDxlxlp(1, 8) = tmp_1_8;
    DuDxlxlp(0, 9) = tmp_0_9;
    DuDxlxlp(1, 9) = tmp_1_9;
    DuDxlxlp(0, 10) = tmp_0_10;
    DuDxlxlp(1, 10) = tmp_1_10;
    DuDxlxlp(0, 11) = tmp_0_11;
    DuDxlxlp(1, 11) = tmp_1_11;
    DuDxlxlp(0, 12) = tmp_0_12;
    DuDxlxlp(1, 12) = tmp_1_12;
    DuDxlxlp(0, 13) = tmp_0_13;
    DuDxlxlp(1, 13) = tmp_1_13;
    DuDxlxlp(0, 14) = tmp_0_14;
    DuDxlxlp(1, 14) = tmp_1_14;
    DuDxlxlp(0, 15) = tmp_0_15;
    DuDxlxlp(1, 15) = tmp_1_15;
    DuDxlxlp(0, 16) = tmp_0_16;
    DuDxlxlp(1, 16) = tmp_1_16;
    DuDxlxlp(0, 17) = tmp_0_17;
    DuDxlxlp(1, 17) = tmp_1_17;
    DuDxlxlp(0, 18) = tmp_0_18;
    DuDxlxlp(1, 18) = tmp_1_18;
    DuDxlxlp(0, 19) = tmp_0_19;
    DuDxlxlp(1, 19) = tmp_1_19;
    DuDxlxlp(0, 20) = tmp_0_20;
    DuDxlxlp(1, 20) = tmp_1_20;
    DuDxlxlp(0, 21) = tmp_0_21;
    DuDxlxlp(1, 21) = tmp_1_21;
    DuDxlxlp(0, 22) = tmp_0_22;
    DuDxlxlp(1, 22) = tmp_1_22;
    DuDxlxlp(0, 23) = tmp_0_23;
    DuDxlxlp(1, 23) = tmp_1_23;
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 48 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  BangBangFredundant::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[iX_F1];
    real_type t3   = X__[iX_F2];
    real_type t5   = Flim(t2 + t3);
    real_type t7   = U__[iU_aF1];
    real_type t8   = ModelPars[iM_maxAF];
    real_type t9   = aF1Control(t7, -t8, t8);
    real_type t10  = U__[iU_aF2];
    real_type t11  = aF2Control(t10, -t8, t8);
    real_type t15  = pow(V__[0] - X__[iX_v], 2);
    real_type t18  = pow(V__[1] - t2 - t3, 2);
    real_type t22  = pow(V__[2] - X__[iX_vF1], 2);
    real_type t26  = pow(V__[3] - X__[iX_vF2], 2);
    real_type t29  = pow(V__[4] - t7, 2);
    real_type t32  = pow(V__[5] - t10, 2);
    real_type result__ = t5 * ModelPars[iM_w_F] + t11 + t15 + t18 + t22 + t26 + t29 + t32 + t9;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFredundant::DmDu_numEqns() const
  { return 2; }

  void
  BangBangFredundant::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = U__[iU_aF1];
    real_type t2   = ModelPars[iM_maxAF];
    real_type t3   = ALIAS_aF1Control_D_1(t1, -t2, t2);
    result__[ 0   ] = t3 - 2 * V__[4] + 2 * t1;
    real_type t7   = U__[iU_aF2];
    real_type t8   = ALIAS_aF2Control_D_1(t7, -t2, t2);
    result__[ 1   ] = t8 - 2 * V__[5] + 2 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFredundant::DmDuu_numRows() const
  { return 2; }

  integer
  BangBangFredundant::DmDuu_numCols() const
  { return 2; }

  integer
  BangBangFredundant::DmDuu_nnz() const
  { return 2; }

  void
  BangBangFredundant::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFredundant::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = ModelPars[iM_maxAF];
    real_type t3   = ALIAS_aF1Control_D_1_1(U__[iU_aF1], -t2, t2);
    result__[ 0   ] = t3 + 2;
    real_type t5   = ALIAS_aF2Control_D_1_1(U__[iU_aF2], -t2, t2);
    result__[ 1   ] = t5 + 2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 2, i_segment );
  }

}

// EOF: BangBangFredundant_Methods_controls.cc
