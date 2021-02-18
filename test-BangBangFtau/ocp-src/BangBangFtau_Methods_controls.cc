/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods.cc                                        |
 |                                                                       |
 |  version: 1.0   date 23/2/2021                                        |
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


#include "BangBangFtau.hh"
#include "BangBangFtau_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vsTBInterval_DD(__t1) vsTBInterval.DD( __t1)
#define ALIAS_vsTBInterval_D(__t1) vsTBInterval.D( __t1)
#define ALIAS_vsTmax_DD(__t1) vsTmax.DD( __t1)
#define ALIAS_vsTmax_D(__t1) vsTmax.D( __t1)
#define ALIAS_vsBpositive_DD(__t1) vsBpositive.DD( __t1)
#define ALIAS_vsBpositive_D(__t1) vsBpositive.D( __t1)
#define ALIAS_vsTpositive_DD(__t1) vsTpositive.DD( __t1)
#define ALIAS_vsTpositive_D(__t1) vsTpositive.D( __t1)


namespace BangBangFtauDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  integer
  BangBangFtau::g_numEqns() const
  { return 2; }

  void
  BangBangFtau::g_eval(
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
    real_type t1   = ModelPars[iM_epsiTB];
    real_type t2   = U__[iU_vsT];
    real_type t5   = ALIAS_vsTpositive_D(t2);
    real_type t8   = ALIAS_vsTmax_D(ModelPars[iM_maxT] - t2);
    real_type t9   = U__[iU_vsB];
    real_type t11  = ALIAS_vsTBInterval_D(t2 - t9);
    result__[ 0   ] = 2 * t2 * t1 + t5 - t8 + t11 + L__[iL_lambda3__xo] / ModelPars[iM_tauT];
    real_type t18  = ALIAS_vsBpositive_D(t9);
    result__[ 1   ] = 2 * t9 * t1 + t18 - t11 + L__[iL_lambda4__xo] / ModelPars[iM_tauB];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DgDxlp_numRows() const
  { return 2; }

  integer
  BangBangFtau::DgDxlp_numCols() const
  { return 8; }

  integer
  BangBangFtau::DgDxlp_nnz() const
  { return 2; }

  void
  BangBangFtau::DgDxlp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 7   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DgDxlp_sparse(
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
    result__[ 0   ] = 1.0 / ModelPars[iM_tauT];
    result__[ 1   ] = 1.0 / ModelPars[iM_tauB];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DgDu_numRows() const
  { return 2; }

  integer
  BangBangFtau::DgDu_numCols() const
  { return 2; }

  integer
  BangBangFtau::DgDu_nnz() const
  { return 4; }

  void
  BangBangFtau::DgDu_pattern(
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
  BangBangFtau::DgDu_sparse(
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
    real_type t2   = 2 * ModelPars[iM_epsiTB];
    real_type t3   = U__[iU_vsT];
    real_type t4   = ALIAS_vsTpositive_DD(t3);
    real_type t7   = ALIAS_vsTmax_DD(ModelPars[iM_maxT] - t3);
    real_type t8   = U__[iU_vsB];
    real_type t10  = ALIAS_vsTBInterval_DD(t3 - t8);
    result__[ 0   ] = t2 + t4 + t7 + t10;
    result__[ 1   ] = -t10;
    result__[ 2   ] = result__[1];
    real_type t11  = ALIAS_vsBpositive_DD(t8);
    result__[ 3   ] = t2 + t11 + t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 4, i_segment );
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
  BangBangFtau::u_numEqns() const
  { return 2; }

  void
  BangBangFtau::u_eval_analytic(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    real_type const * L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    U__[ iU_vsT ] = 0;
    U__[ iU_vsB ] = 0;
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::u_eval_analytic(
    NodeType2 const    & LEFT__,
    NodeType2 const    & RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
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
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
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
  BangBangFtau::DuDxlp_full_analytic(
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
    DuDxlp(1, 0) = 0;
    DuDxlp(0, 1) = 0;
    DuDxlp(1, 1) = 0;
    DuDxlp(0, 2) = 0;
    DuDxlp(1, 2) = 0;
    DuDxlp(0, 3) = 0;
    DuDxlp(1, 3) = 0;
    DuDxlp(0, 4) = 0;
    DuDxlp(1, 4) = 0;
    DuDxlp(0, 5) = 0;
    DuDxlp(1, 5) = 0;
    DuDxlp(0, 6) = 0;
    DuDxlp(1, 6) = 0;
    DuDxlp(0, 7) = 0;
    DuDxlp(1, 7) = 0;
    if ( m_debug )
      Mechatronix::check( DuDxlp.data(), "DuDxlp_full_analytic", 2 );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DuDxlp_full_analytic(
    NodeType2 const          & LEFT__,
    NodeType2 const          & RIGHT__,
    P_const_pointer_type       P__,
    U_const_pointer_type       U__,
    MatrixWrapper<real_type> & DuDxlp
  ) const {
    NodeType2 NODE__;
    real_type Q__[1];
    real_type X__[4];
    real_type L__[4];
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
    X__[3] = (LEFT__.x[3]+RIGHT__.x[3])/2;
    // Lvars
    L__[0] = (LEFT__.lambda[0]+RIGHT__.lambda[0])/2;
    L__[1] = (LEFT__.lambda[1]+RIGHT__.lambda[1])/2;
    L__[2] = (LEFT__.lambda[2]+RIGHT__.lambda[2])/2;
    L__[3] = (LEFT__.lambda[3]+RIGHT__.lambda[3])/2;
    this->DuDxlp_full_analytic( NODE__, P__, U__, DuDxlp );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  BangBangFtau::m_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer     i_segment = NODE__.i_segment;
    real_type const * Q__ = NODE__.q;
    real_type const * X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->getSegmentByIndex(i_segment);
    real_type t2   = U__[iU_vsT];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_vsB];
    real_type t5   = t4 * t4;
    real_type t8   = vsTpositive(t2);
    real_type t9   = vsBpositive(t4);
    real_type t12  = vsTmax(ModelPars[iM_maxT] - t2);
    real_type t14  = vsTBInterval(t2 - t4);
    real_type t18  = power2(V__[0] - X__[iX_v]);
    real_type t20  = X__[iX_sT];
    real_type t21  = X__[iX_sB];
    real_type t25  = clip(t20 - t21, ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    real_type t27  = power2(V__[1] - t25);
    real_type t34  = power2(V__[2] + 1.0 / ModelPars[iM_tauT] * (t20 - t2));
    real_type t41  = power2(V__[3] + 1.0 / ModelPars[iM_tauB] * (t21 - t4));
    real_type result__ = (t3 + t5) * ModelPars[iM_epsiTB] + t8 + t9 + t12 + t14 + t18 + t27 + t34 + t41;
    if ( m_debug ) {
      UTILS_ASSERT( isRegular(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DmDu_numEqns() const
  { return 2; }

  void
  BangBangFtau::DmDu_eval(
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
    real_type t1   = ModelPars[iM_epsiTB];
    real_type t2   = U__[iU_vsT];
    real_type t5   = ALIAS_vsTpositive_D(t2);
    real_type t8   = ALIAS_vsTmax_D(ModelPars[iM_maxT] - t2);
    real_type t9   = U__[iU_vsB];
    real_type t11  = ALIAS_vsTBInterval_D(t2 - t9);
    real_type t16  = 1.0 / ModelPars[iM_tauT];
    result__[ 0   ] = 2 * t2 * t1 + t5 - t8 + t11 - 2 * t16 * (V__[2] + t16 * (X__[iX_sT] - t2));
    real_type t23  = ALIAS_vsBpositive_D(t9);
    real_type t28  = 1.0 / ModelPars[iM_tauB];
    result__[ 1   ] = 2 * t9 * t1 + t23 - t11 - 2 * t28 * (V__[3] + t28 * (X__[iX_sB] - t9));
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  BangBangFtau::DmDuu_numRows() const
  { return 2; }

  integer
  BangBangFtau::DmDuu_numCols() const
  { return 2; }

  integer
  BangBangFtau::DmDuu_nnz() const
  { return 4; }

  void
  BangBangFtau::DmDuu_pattern(
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
  BangBangFtau::DmDuu_sparse(
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
    real_type t2   = 2 * ModelPars[iM_epsiTB];
    real_type t3   = U__[iU_vsT];
    real_type t4   = ALIAS_vsTpositive_DD(t3);
    real_type t7   = ALIAS_vsTmax_DD(ModelPars[iM_maxT] - t3);
    real_type t8   = U__[iU_vsB];
    real_type t10  = ALIAS_vsTBInterval_DD(t3 - t8);
    real_type t12  = ModelPars[iM_tauT] * ModelPars[iM_tauT];
    result__[ 0   ] = t2 + t4 + t7 + t10 + 2 / t12;
    result__[ 1   ] = -t10;
    result__[ 2   ] = result__[1];
    real_type t15  = ALIAS_vsBpositive_DD(t8);
    real_type t17  = ModelPars[iM_tauB] * ModelPars[iM_tauB];
    result__[ 3   ] = t2 + t15 + t10 + 2 / t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: BangBangFtau_Methods.cc
