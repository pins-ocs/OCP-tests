/*-----------------------------------------------------------------------*\
 |  file: MinimumFuelOrbitRaising_Methods_controls.cc                    |
 |                                                                       |
 |  version: 1.0   date 9/3/2021                                         |
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
    NodeType2 const    & NODE__,
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
    NodeType2 const    & NODE__,
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
    NodeType2 const    & NODE__,
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
  integer
  MinimumFuelOrbitRaising::u_numEqns() const
  { return 1; }

  void
  MinimumFuelOrbitRaising::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_u ] = atan2(-L__[iL_lambda2__xo], -L__[iL_lambda3__xo]);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[3];
    real_type L__[3];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    this->u_eval_analytic( NODE__, P__, U__ );
  }

  /*\
   |   ___       ___      _                       _      _   _
   |  |   \ _  _|   \__ _| |_ __   __ _ _ _  __ _| |_  _| |_(_)__
   |  | |) | || | |) \ \ / | '_ \ / _` | ' \/ _` | | || |  _| / _|
   |  |___/ \_,_|___//_\_\_| .__/ \__,_|_||_\__,_|_|\_, |\__|_\__|
   |                       |_|                      |__/
  \*/
  void
  MinimumFuelOrbitRaising::DuDxlp_full_analytic(
    NodeType2 const          & NODE__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    DuDxlp(0, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(0, 4) = 1.0 / L__[iL_lambda3__xo] / (1 + L__[iL_lambda2__xo] * L__[iL_lambda2__xo] * pow(L__[iL_lambda3__xo], -2));
    DuDxlp(0, 5) = -L__[iL_lambda2__xo] * pow(L__[iL_lambda3__xo], -2) / (1 + L__[iL_lambda2__xo] * L__[iL_lambda2__xo] * pow(L__[iL_lambda3__xo], -2));
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 1 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  MinimumFuelOrbitRaising::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[3];
    real_type L__[3];
    NODE__.i_segment = LEFT__.i_segment;
    NODE__.q         = Q__;
    NODE__.x         = X__;
    NODE__.lambda    = L__;
    // Qvars
    Q__[0] = (LEFT__.q[0]+RIGHT__.q[0])/2;
    // Xvars
    X__[0] = (LEFT__.x[0]+RIGHT__.x[0])/2;
    X__[1] = (LEFT__.x[1]+RIGHT__.x[1])/2;
    X__[2] = (LEFT__.x[2]+RIGHT__.x[2])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  MinimumFuelOrbitRaising::m_eval(
    NodeType const     & NODE__,
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
    NodeType const     & NODE__,
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
    result__[ 0   ] = -2 * t18 * t22 * t10 * (V__[1] - t6 * t3 * t2 + 1.0 / t8 - t18 * t12 * t10) + 2 * t18 * t12 * t10 * (-t18 * t22 * t10 + t6 * t2 * X__[iX_x2] + V__[2]);
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
    NodeType const     & NODE__,
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
    result__[ 0   ] = 2 * t12 * t5 * t2 + 2 * t25 * t23 * t1 * (V__[1] - t19 * t16 * t15 + 1.0 / t21 - t25 * t23 * t1) + 2 * t12 * t31 * t2 + 2 * t25 * t4 * t1 * (-t25 * t4 * t1 + t19 * t15 * X__[iX_x2] + V__[2]);
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 1, i_segment );
  }

}

// EOF: MinimumFuelOrbitRaising_Methods_controls.cc
