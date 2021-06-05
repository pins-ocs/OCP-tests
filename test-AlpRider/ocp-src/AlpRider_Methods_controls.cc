/*-----------------------------------------------------------------------*\
 |  file: AlpRider_Methods_controls.cc                                   |
 |                                                                       |
 |  version: 1.0   date 5/6/2021                                         |
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


#include "AlpRider.hh"
#include "AlpRider_Pars.hh"

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
#define ALIAS_Ybound_DD(__t1) Ybound.DD( __t1)
#define ALIAS_Ybound_D(__t1) Ybound.D( __t1)


namespace AlpRiderDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  AlpRider::g_numEqns() const
  { return 2; }

  void
  AlpRider::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type U__,
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
    real_type QM__[1];
    real_type XM__[4];
    real_type LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t3   = LL__[iL_lambda1__xo];
    real_type t4   = LL__[iL_lambda2__xo];
    real_type t5   = LL__[iL_lambda3__xo];
    real_type t6   = LL__[iL_lambda4__xo];
    real_type t7   = LR__[iL_lambda1__xo];
    real_type t8   = LR__[iL_lambda2__xo];
    real_type t9   = LR__[iL_lambda3__xo];
    real_type t10  = LR__[iL_lambda4__xo];
    result__[ 0   ] = U__[iU_u1] / 25 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
    result__[ 1   ] = U__[iU_u2] / 25 + t3 + 2 * t4 - t5 + 3 * t6 + t7 + 2 * t8 - t9 + 3 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DgDxlxlp_numRows() const
  { return 2; }

  integer
  AlpRider::DgDxlxlp_numCols() const
  { return 16; }

  integer
  AlpRider::DgDxlxlp_nnz() const
  { return 16; }

  void
  AlpRider::DgDxlxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 7   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 12  ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 13  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 14  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 15  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 4   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 5   ;
    iIndex[10] = 1   ; jIndex[10] = 6   ;
    iIndex[11] = 1   ; jIndex[11] = 7   ;
    iIndex[12] = 1   ; jIndex[12] = 12  ;
    iIndex[13] = 1   ; jIndex[13] = 13  ;
    iIndex[14] = 1   ; jIndex[14] = 14  ;
    iIndex[15] = 1   ; jIndex[15] = 15  ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type U__,
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
    real_type QM__[1];
    real_type XM__[4];
    real_type LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    result__[ 7   ] = 1;
    result__[ 8   ] = 1;
    result__[ 9   ] = 2;
    result__[ 10  ] = -1;
    result__[ 11  ] = 3;
    result__[ 12  ] = 1;
    result__[ 13  ] = 2;
    result__[ 14  ] = -1;
    result__[ 15  ] = 3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 16, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DgDu_numRows() const
  { return 2; }

  integer
  AlpRider::DgDu_numCols() const
  { return 2; }

  integer
  AlpRider::DgDu_nnz() const
  { return 2; }

  void
  AlpRider::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DgDu_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type U__,
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
    real_type QM__[1];
    real_type XM__[4];
    real_type LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    result__[ 0   ] = 1.0 / 0.25e2;
    result__[ 1   ] = 1.0 / 0.25e2;
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
  AlpRider::u_eval_analytic(
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
    real_type XM__[4];
    real_type LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = LL__[iL_lambda1__xo];
    real_type t2   = LL__[iL_lambda2__xo];
    real_type t3   = LL__[iL_lambda3__xo];
    real_type t4   = LL__[iL_lambda4__xo];
    real_type t5   = LR__[iL_lambda1__xo];
    real_type t6   = LR__[iL_lambda2__xo];
    real_type t7   = LR__[iL_lambda3__xo];
    real_type t8   = LR__[iL_lambda4__xo];
    U__[ iU_u1 ] = -25 * t1 - 25 * t2 - 25 * t3 - 25 * t4 - 25 * t5 - 25 * t6 - 25 * t7 - 25 * t8;
    U__[ iU_u2 ] = -25 * t1 - 50 * t2 + 25 * t3 - 75 * t4 - 25 * t5 - 50 * t6 + 25 * t7 - 75 * t8;
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
  AlpRider::DuDxlxlp_full_analytic(
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
    real_type XM__[4];
    real_type LM__[4];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type tmp_0_0 = 0;
    real_type tmp_1_0 = 0;
    real_type tmp_0_1 = 0;
    real_type tmp_1_1 = 0;
    real_type tmp_0_2 = 0;
    real_type tmp_1_2 = 0;
    real_type tmp_0_3 = 0;
    real_type tmp_1_3 = 0;
    real_type tmp_0_4 = -25;
    real_type tmp_1_4 = -25;
    real_type tmp_0_5 = -25;
    real_type tmp_1_5 = -50;
    real_type tmp_0_6 = -25;
    real_type tmp_1_6 = 25;
    real_type tmp_0_7 = -25;
    real_type tmp_1_7 = -75;
    real_type tmp_0_8 = 0;
    real_type tmp_1_8 = 0;
    real_type tmp_0_9 = 0;
    real_type tmp_1_9 = 0;
    real_type tmp_0_10 = 0;
    real_type tmp_1_10 = 0;
    real_type tmp_0_11 = 0;
    real_type tmp_1_11 = 0;
    real_type tmp_0_12 = -25;
    real_type tmp_1_12 = -25;
    real_type tmp_0_13 = -25;
    real_type tmp_1_13 = -50;
    real_type tmp_0_14 = -25;
    real_type tmp_1_14 = 25;
    real_type tmp_0_15 = -25;
    real_type tmp_1_15 = -75;
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
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 32 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  AlpRider::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t1   = X__[iX_y1];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_y2];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_y3];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_y4];
    real_type t8   = t7 * t7;
    real_type t11  = q(Q__[iQ_zeta]);
    real_type t13  = Ybound(t2 + t4 + t6 + t8 - t11);
    real_type t17  = U__[iU_u1];
    real_type t18  = U__[iU_u2];
    real_type t20  = pow(V__[0] + 10 * t1 - t17 - t18, 2);
    real_type t25  = pow(V__[1] + 2 * t3 - t17 - 2 * t18, 2);
    real_type t30  = pow(V__[2] + 3 * t5 - 5 * t7 - t17 + t18, 2);
    real_type t36  = pow(V__[3] - 5 * t5 + 3 * t7 - t17 - 3 * t18, 2);
    real_type result__ = t13 * (t2 + t4 + t6 + t8 + 1) + t20 + t25 + t30 + t36;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DmDu_numEqns() const
  { return 2; }

  void
  AlpRider::DmDu_eval(
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
    real_type t2   = 2 * V__[0];
    real_type t4   = 20 * X__[iX_y1];
    real_type t5   = U__[iU_u1];
    real_type t7   = U__[iU_u2];
    real_type t9   = V__[1];
    real_type t11  = X__[iX_y2];
    real_type t14  = 2 * V__[2];
    real_type t15  = X__[iX_y3];
    real_type t17  = X__[iX_y4];
    real_type t19  = V__[3];
    result__[ 0   ] = -t2 - t4 + 8 * t5 + 10 * t7 - 2 * t9 - 4 * t11 - t14 + 4 * t15 + 4 * t17 - 2 * t19;
    result__[ 1   ] = -t2 - t4 + 10 * t5 + 30 * t7 - 4 * t9 - 8 * t11 + t14 + 36 * t15 - 28 * t17 - 6 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  AlpRider::DmDuu_numRows() const
  { return 2; }

  integer
  AlpRider::DmDuu_numCols() const
  { return 2; }

  integer
  AlpRider::DmDuu_nnz() const
  { return 4; }

  void
  AlpRider::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  AlpRider::DmDuu_sparse(
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
    result__[ 0   ] = 8;
    result__[ 1   ] = 10;
    result__[ 2   ] = 10;
    result__[ 3   ] = 30;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: AlpRider_Methods_controls.cc
