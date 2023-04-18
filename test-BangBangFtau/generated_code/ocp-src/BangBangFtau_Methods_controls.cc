/*-----------------------------------------------------------------------*\
 |  file: BangBangFtau_Methods_controls.cc                               |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
 |                                                                       |
 |  Copyright (C) 2023                                                   |
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
#pragma warning( disable : 4189 )
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
#define ALIAS_vsTBInterval_max_DD(__t1) vsTBInterval_max.DD( __t1)
#define ALIAS_vsTBInterval_max_D(__t1) vsTBInterval_max.D( __t1)
#define ALIAS_vsTBInterval_min_DD(__t1) vsTBInterval_min.DD( __t1)
#define ALIAS_vsTBInterval_min_D(__t1) vsTBInterval_min.D( __t1)
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

  real_type
  BangBangFtau::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_vsT];
    real_type t3   = t2 * t2;
    real_type t4   = U__[iU_vsB];
    real_type t5   = t4 * t4;
    real_type t8   = vsTpositive(-t2);
    real_type t9   = vsBpositive(-t4);
    real_type t12  = vsTmax(t2 - ModelPars[iM_maxT]);
    real_type t14  = vsTBInterval_min(-1 - t2 + t4);
    real_type t16  = vsTBInterval_max(t2 - t4 - 1);
    real_type t21  = X__[iX_sT];
    real_type t22  = X__[iX_sB];
    real_type t26  = clip(t21 - t22, ModelPars[iM_minClip], ModelPars[iM_maxClip]);
    real_type result__ = (t3 + t5) * ModelPars[iM_epsiTB] + t8 + t9 + t12 + t14 + t16 + MU__[0] * X__[iX_v] + t26 * MU__[1] - 1.0 / ModelPars[iM_tauT] * (t21 - t2) * MU__[2] - 1.0 / ModelPars[iM_tauB] * (t22 - t4) * MU__[3];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer BangBangFtau::g_numEqns() const { return 2; }

  void
  BangBangFtau::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_epsiTB];
    real_type t2   = U__[iU_vsT];
    real_type t5   = ALIAS_vsTpositive_D(-t2);
    real_type t8   = ALIAS_vsTmax_D(t2 - ModelPars[iM_maxT]);
    real_type t9   = U__[iU_vsB];
    real_type t11  = ALIAS_vsTBInterval_min_D(-1 - t2 + t9);
    real_type t13  = ALIAS_vsTBInterval_max_D(t2 - t9 - 1);
    result__[ 0   ] = 2 * t2 * t1 - t5 + t8 - t11 + t13 + MU__[2] / ModelPars[iM_tauT];
    real_type t20  = ALIAS_vsBpositive_D(-t9);
    result__[ 1   ] = 2 * t9 * t1 - t20 + t11 - t13 + MU__[3] / ModelPars[iM_tauB];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DgDxpm_numRows() const { return 2; }
  integer BangBangFtau::DgDxpm_numCols() const { return 8; }
  integer BangBangFtau::DgDxpm_nnz()     const { return 2; }

  void
  BangBangFtau::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 6   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1.0 / ModelPars[iM_tauT];
    result__[ 1   ] = 1.0 / ModelPars[iM_tauB];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer BangBangFtau::DgDu_numRows() const { return 2; }
  integer BangBangFtau::DgDu_numCols() const { return 2; }
  integer BangBangFtau::DgDu_nnz()     const { return 4; }

  void
  BangBangFtau::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  BangBangFtau::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 2 * ModelPars[iM_epsiTB];
    real_type t3   = U__[iU_vsT];
    real_type t4   = ALIAS_vsTpositive_DD(-t3);
    real_type t7   = ALIAS_vsTmax_DD(t3 - ModelPars[iM_maxT]);
    real_type t8   = U__[iU_vsB];
    real_type t10  = ALIAS_vsTBInterval_min_DD(-1 - t3 + t8);
    real_type t12  = ALIAS_vsTBInterval_max_DD(t3 - t8 - 1);
    result__[ 0   ] = t2 + t4 + t7 + t10 + t12;
    result__[ 1   ] = -t10 - t12;
    result__[ 2   ] = result__[1];
    real_type t13  = ALIAS_vsBpositive_DD(-t8);
    result__[ 3   ] = t2 + t13 + t10 + t12;
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

  void
  BangBangFtau::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "BangBangFtau::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: BangBangFtau_Methods_controls.cc
