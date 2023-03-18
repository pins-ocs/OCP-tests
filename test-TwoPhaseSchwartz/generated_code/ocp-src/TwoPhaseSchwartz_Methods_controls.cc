/*-----------------------------------------------------------------------*\
 |  file: TwoPhaseSchwartz_Methods_controls.cc                           |
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


#include "TwoPhaseSchwartz.hh"
#include "TwoPhaseSchwartz_Pars.hh"

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
#define ALIAS_bound2_DD(__t1) bound2.DD( __t1)
#define ALIAS_bound2_D(__t1) bound2.D( __t1)
#define ALIAS_bound1_DD(__t1) bound1.DD( __t1)
#define ALIAS_bound1_D(__t1) bound1.D( __t1)
#define ALIAS_u1Control_D_3(__t1, __t2, __t3) u1Control.D_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2(__t1, __t2, __t3) u1Control.D_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1(__t1, __t2, __t3) u1Control.D_1( __t1, __t2, __t3)
#define ALIAS_u1Control_D_3_3(__t1, __t2, __t3) u1Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_3(__t1, __t2, __t3) u1Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_2_2(__t1, __t2, __t3) u1Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_3(__t1, __t2, __t3) u1Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_2(__t1, __t2, __t3) u1Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u1Control_D_1_1(__t1, __t2, __t3) u1Control.D_1_1( __t1, __t2, __t3)


namespace TwoPhaseSchwartzDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  TwoPhaseSchwartz::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_u2];
    real_type t3   = t2 * t2;
    real_type t5   = U__[iU_u1];
    real_type t6   = u1Control(t5, -1, 1);
    real_type t7   = X__[iX_x1];
    real_type t9   = pow(t7 - 1, 2);
    real_type t11  = X__[iX_x2];
    real_type t14  = pow(0.3333333333e1 * t11 - 0.1333333333e1, 2);
    real_type t16  = bound1(1 - 9 * t9 - t14);
    real_type t18  = bound2(-0.8e0 - t11);
    real_type t22  = t7 * t7;
    real_type t30  = ModelPars[iM_T2];
    real_type t32  = X__[iX_x4];
    real_type t37  = X__[iX_x3] * X__[iX_x3];
    real_type result__ = t3 * ModelPars[iM_epsilon] + t6 + t16 + t18 + t11 * MU__[0] + (t5 - 0.1e0 * t11 * (2 * t22 + 1)) * MU__[1] + t32 * t30 * MU__[2] + (t2 - 0.1e0 * t32 * (2 * t37 + 1)) * t30 * MU__[3];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TwoPhaseSchwartz::g_numEqns() const { return 2; }

  void
  TwoPhaseSchwartz::g_eval(
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
    real_type t2   = ALIAS_u1Control_D_1(U__[iU_u1], -1, 1);
    result__[ 0   ] = t2 + MU__[1];
    result__[ 1   ] = MU__[3] * ModelPars[iM_T2] + 2 * ModelPars[iM_epsilon] * U__[iU_u2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DgDxpm_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DgDxpm_numCols() const { return 8; }
  integer TwoPhaseSchwartz::DgDxpm_nnz()     const { return 2; }

  void
  TwoPhaseSchwartz::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 5   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 7   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DgDxpm_sparse(
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
    result__[ 0   ] = 1;
    result__[ 1   ] = ModelPars[iM_T2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TwoPhaseSchwartz::DgDu_numRows() const { return 2; }
  integer TwoPhaseSchwartz::DgDu_numCols() const { return 2; }
  integer TwoPhaseSchwartz::DgDu_nnz()     const { return 2; }

  void
  TwoPhaseSchwartz::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TwoPhaseSchwartz::DgDu_sparse(
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
    result__[ 0   ] = ALIAS_u1Control_D_1_1(U__[iU_u1], -1, 1);
    result__[ 1   ] = 2 * ModelPars[iM_epsilon];
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
  TwoPhaseSchwartz::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "TwoPhaseSchwartz::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: TwoPhaseSchwartz_Methods_controls.cc
