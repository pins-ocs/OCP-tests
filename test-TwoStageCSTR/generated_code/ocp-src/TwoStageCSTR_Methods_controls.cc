/*-----------------------------------------------------------------------*\
 |  file: TwoStageCSTR_Methods_controls.cc                               |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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


#include "TwoStageCSTR.hh"
#include "TwoStageCSTR_Pars.hh"

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
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoStageCSTRDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  TwoStageCSTR::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x1];
    real_type t2   = t1 * t1;
    real_type t3   = X__[iX_x2];
    real_type t4   = t3 * t3;
    real_type t5   = X__[iX_x3];
    real_type t6   = t5 * t5;
    real_type t7   = X__[iX_x4];
    real_type t8   = t7 * t7;
    real_type t10  = U__[iU_u1];
    real_type t11  = t10 * t10;
    real_type t12  = U__[iU_u2];
    real_type t13  = t12 * t12;
    real_type t16  = u1Control(t10, -0.5e0, 0.5e0);
    real_type t17  = u2Control(t12, -0.5e0, 0.5e0);
    real_type t19  = R1(t1, t3);
    real_type t20  = 0.5e0 - t1 - t19;
    real_type t26  = t19 - (2 + t10) * (t3 + 0.25e0);
    real_type t29  = ModelPars[iM_tau];
    real_type t31  = R2(t5, t7);
    real_type result__ = t2 + t4 + t6 + t8 + (t11 + t13) * ModelPars[iM_W] + t16 + t17 + t20 * MU__[0] + t26 * MU__[1] + (t1 - t5 - t20 * t29 - t31 + 0.25e0) * MU__[2] + (t3 - 2 * t7 - (t7 + 0.25e0) * t12 - t26 * t29 + t31 - 0.25e0) * MU__[3];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoStageCSTR::g_numEqns() const { return 2; }

  void
  TwoStageCSTR::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_W];
    real_type t2   = U__[iU_u1];
    real_type t5   = ALIAS_u1Control_D_1(t2, -0.5e0, 0.5e0);
    real_type t8   = -X__[iX_x2] - 0.25e0;
    real_type t10  = MU__[3];
    result__[ 0   ] = -t8 * ModelPars[iM_tau] * t10 + 2 * t2 * t1 + t8 * MU__[1] + t5;
    real_type t14  = U__[iU_u2];
    real_type t17  = ALIAS_u2Control_D_1(t14, -0.5e0, 0.5e0);
    result__[ 1   ] = 2 * t14 * t1 + t17 + (-X__[iX_x4] - 0.25e0) * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::DgDxpm_numRows() const { return 2; }
  integer TwoStageCSTR::DgDxpm_numCols() const { return 8; }
  integer TwoStageCSTR::DgDxpm_nnz()     const { return 5; }

  void
  TwoStageCSTR::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = MU__[3];
    real_type t2   = ModelPars[iM_tau];
    result__[ 0   ] = t2 * t1 - MU__[1];
    result__[ 1   ] = -X__[iX_x2] - 0.25e0;
    result__[ 2   ] = -result__[1] * t2;
    result__[ 3   ] = -t1;
    result__[ 4   ] = -X__[iX_x4] - 0.25e0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoStageCSTR::DgDu_numRows() const { return 2; }
  integer TwoStageCSTR::DgDu_numCols() const { return 2; }
  integer TwoStageCSTR::DgDu_nnz()     const { return 2; }

  void
  TwoStageCSTR::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoStageCSTR::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = 2 * ModelPars[iM_W];
    real_type t4   = ALIAS_u1Control_D_1_1(U__[iU_u1], -0.5e0, 0.5e0);
    result__[ 0   ] = t2 + t4;
    real_type t6   = ALIAS_u2Control_D_1_1(U__[iU_u2], -0.5e0, 0.5e0);
    result__[ 1   ] = t2 + t6;
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
  TwoStageCSTR::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "TwoStageCSTR::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: TwoStageCSTR_Methods_controls.cc
