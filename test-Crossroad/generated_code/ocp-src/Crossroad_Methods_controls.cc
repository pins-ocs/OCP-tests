/*-----------------------------------------------------------------------*\
 |  file: Crossroad_Methods_controls.cc                                  |
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


#include "Crossroad.hh"
#include "Crossroad_Pars.hh"

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
#define ALIAS_VelBound_max_DD(__t1) VelBound_max.DD( __t1)
#define ALIAS_VelBound_max_D(__t1) VelBound_max.D( __t1)
#define ALIAS_VelBound_min_DD(__t1) VelBound_min.DD( __t1)
#define ALIAS_VelBound_min_D(__t1) VelBound_min.D( __t1)
#define ALIAS_AccBound_DD(__t1) AccBound.DD( __t1)
#define ALIAS_AccBound_D(__t1) AccBound.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)
#define ALIAS_jerkControl_D_3(__t1, __t2, __t3) jerkControl.D_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2(__t1, __t2, __t3) jerkControl.D_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1(__t1, __t2, __t3) jerkControl.D_1( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_3_3(__t1, __t2, __t3) jerkControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_3(__t1, __t2, __t3) jerkControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_2_2(__t1, __t2, __t3) jerkControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_3(__t1, __t2, __t3) jerkControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_2(__t1, __t2, __t3) jerkControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_jerkControl_D_1_1(__t1, __t2, __t3) jerkControl.D_1_1( __t1, __t2, __t3)


namespace CrossroadDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Crossroad::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_jerk];
    real_type t3   = t2 * t2;
    real_type t7   = X__[iX_Ts];
    real_type t11  = jerkControl(t2, ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    real_type t12  = Tpositive(-t7);
    real_type t13  = X__[iX_a];
    real_type t14  = t13 * t13;
    real_type t16  = ModelPars[iM_along_max] * ModelPars[iM_along_max];
    real_type t19  = X__[iX_v];
    real_type t20  = t19 * t19;
    real_type t21  = t20 * t20;
    real_type t23  = kappa(X__[iX_s]);
    real_type t24  = t23 * t23;
    real_type t27  = ModelPars[iM_alat_max] * ModelPars[iM_alat_max];
    real_type t31  = AccBound(1.0 / t16 * t14 + 1.0 / t27 * t24 * t21 - 1);
    real_type t32  = VelBound_min(-t19);
    real_type t35  = VelBound_max(t19 - ModelPars[iM_v_max]);
    real_type result__ = t7 * (t3 * ModelPars[iM_wJ] + ModelPars[iM_wT]) + t11 + t12 + t31 + t32 + t35 + t19 * t7 * MU__[0] + t13 * t7 * MU__[1] + t2 * t7 * MU__[2];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Crossroad::g_numEqns() const { return 1; }

  void
  Crossroad::g_eval(
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
    real_type t1   = U__[iU_jerk];
    real_type t4   = X__[iX_Ts];
    real_type t9   = ALIAS_jerkControl_D_1(t1, ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    result__[ 0   ] = 2 * t4 * ModelPars[iM_wJ] * t1 + t4 * MU__[2] + t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DgDxpm_numRows() const { return 1; }
  integer Crossroad::DgDxpm_numCols() const { return 8; }
  integer Crossroad::DgDxpm_nnz()     const { return 2; }

  void
  Crossroad::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DgDxpm_sparse(
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
    result__[ 0   ] = 2 * U__[iU_jerk] * ModelPars[iM_wJ] + MU__[2];
    result__[ 1   ] = X__[iX_Ts];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Crossroad::DgDu_numRows() const { return 1; }
  integer Crossroad::DgDu_numCols() const { return 1; }
  integer Crossroad::DgDu_nnz()     const { return 1; }

  void
  Crossroad::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Crossroad::DgDu_sparse(
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
    real_type t8   = ALIAS_jerkControl_D_1_1(U__[iU_jerk], ModelPars[iM_jerk_min], ModelPars[iM_jerk_max]);
    result__[ 0   ] = 2 * ModelPars[iM_wJ] * X__[iX_Ts] + t8;
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
  Crossroad::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "Crossroad::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: Crossroad_Methods_controls.cc
