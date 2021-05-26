/*-----------------------------------------------------------------------*\
 |  file: MinimumFuelOrbitRaising_Methods_controls.cc                    |
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


#include "MinimumFuelOrbitRaising.hh"
#include "MinimumFuelOrbitRaising_Pars.hh"

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


namespace MinimumFuelOrbitRaisingDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  MinimumFuelOrbitRaising::g_numEqns() const
  { return 1; }

  void
  MinimumFuelOrbitRaising::g_eval(
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
    real_type t4   = atan2(-L__[iL_lambda2__xo], -L__[iL_lambda3__xo]);
    result__[ 0   ] = U__[iU_u] - t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DgDxlp_numRows() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DgDxlp_numCols() const
  { return 6; }

  integer
  MinimumFuelOrbitRaising::DgDxlp_nnz() const
  { return 2; }

  void
  MinimumFuelOrbitRaising::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DgDxlp_sparse(
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
    real_type t1   = L__[iL_lambda3__xo];
    real_type t3   = L__[iL_lambda2__xo];
    real_type t4   = t3 * t3;
    real_type t5   = t1 * t1;
    real_type t6   = 1.0 / t5;
    real_type t9   = 1.0 / (t6 * t4 + 1);
    result__[ 0   ] = -t9 / t1;
    result__[ 1   ] = t9 * t6 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DgDu_numRows() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DgDu_numCols() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DgDu_nnz() const
  { return 1; }

  void
  MinimumFuelOrbitRaising::DgDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DgDu_sparse(
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
  MinimumFuelOrbitRaising::u_eval_analytic(
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
    real_type XM__[3];
    real_type LM__[3];
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_u ] = atan2(-LM__[1], -LM__[2]);
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
  MinimumFuelOrbitRaising::DuDxlxlp_full_analytic(
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
    real_type XM__[3];
    real_type LM__[3];
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
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type tmp_0_0 = 0.0e0;
    real_type tmp_0_1 = 0.0e0;
    real_type tmp_0_2 = 0.0e0;
    real_type tmp_0_3 = 0.0e0;
    real_type t1   = LM__[2];
    real_type t3   = LM__[1];
    real_type t4   = t3 * t3;
    real_type t5   = t1 * t1;
    real_type t6   = 1.0 / t5;
    real_type t9   = 1.0 / (t6 * t4 + 1);
    real_type tmp_0_4 = 0.5e0 * t9 / t1;
    real_type tmp_0_5 = -0.5e0 * t9 * t6 * t3;
    real_type tmp_0_6 = 0.0e0;
    real_type tmp_0_7 = 0.0e0;
    real_type tmp_0_8 = 0.0e0;
    real_type tmp_0_9 = 0.0e0;
    real_type tmp_0_10 = tmp_0_4;
    real_type tmp_0_11 = tmp_0_5;
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
    if ( m_debug )
      Mechatronix::check( DuDxlxlp.data(), "DuDxlxlp_full_analytic", 12 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  MinimumFuelOrbitRaising::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = X__[iX_x2];
    real_type t4   = pow(V__[0] - t2, 2);
    real_type t6   = X__[iX_x3];
    real_type t7   = t6 * t6;
    real_type t9   = X__[iX_x1];
    real_type t10  = 1.0 / t9;
    real_type t12  = t9 * t9;
    real_type t14  = ModelPars[iM_T];
    real_type t15  = U__[iU_u];
    real_type t16  = sin(t15);
    real_type t22  = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_md] + 1);
    real_type t25  = pow(V__[1] - t10 * t7 * t6 + 1.0 / t12 - t22 * t16 * t14, 2);
    real_type t29  = cos(t15);
    real_type t33  = pow(t10 * t6 * t2 - t22 * t29 * t14 + V__[2], 2);
    real_type result__ = t4 + t25 + t33;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DmDu_numEqns() const
  { return 1; }

  void
  MinimumFuelOrbitRaising::DmDu_eval(
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
    real_type t2   = X__[iX_x3];
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_x1];
    real_type t6   = 1.0 / t5;
    real_type t8   = t5 * t5;
    real_type t10  = ModelPars[iM_T];
    real_type t11  = U__[iU_u];
    real_type t12  = sin(t11);
    real_type t18  = 1.0 / (-Q__[iQ_zeta] * ModelPars[iM_md] + 1);
    real_type t22  = cos(t11);
    real_type t13  = t18 * t22;
    real_type t19  = t12 * t18;
    result__[ 0   ] = -2 * (V__[1] - t6 * t3 * t2 + 1.0 / t8 - t10 * t19) * t10 * t13 + 2 * (t6 * t2 * X__[iX_x2] - t10 * t13 + V__[2]) * t10 * t19;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  MinimumFuelOrbitRaising::DmDuu_numRows() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DmDuu_numCols() const
  { return 1; }

  integer
  MinimumFuelOrbitRaising::DmDuu_nnz() const
  { return 1; }

  void
  MinimumFuelOrbitRaising::DmDuu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DmDuu_sparse(
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
    real_type t1   = ModelPars[iM_T];
    real_type t2   = t1 * t1;
    real_type t3   = U__[iU_u];
    real_type t4   = cos(t3);
    real_type t5   = t4 * t4;
    real_type t10  = -Q__[iQ_zeta] * ModelPars[iM_md] + 1;
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t15  = X__[iX_x3];
    real_type t16  = t15 * t15;
    real_type t18  = X__[iX_x1];
    real_type t19  = 1.0 / t18;
    real_type t21  = t18 * t18;
    real_type t23  = sin(t3);
    real_type t25  = 1.0 / t10;
    real_type t31  = t23 * t23;
    real_type t14  = t25 * t23;
    real_type t33  = t25 * t4;
    result__[ 0   ] = 2 * t12 * t5 * t2 + 2 * (V__[1] - t19 * t16 * t15 + 1.0 / t21 - t1 * t14) * t1 * t14 + 2 * t12 * t31 * t2 + 2 * (t19 * t15 * X__[iX_x2] - t1 * t33 + V__[2]) * t1 * t33;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: MinimumFuelOrbitRaising_Methods_controls.cc
