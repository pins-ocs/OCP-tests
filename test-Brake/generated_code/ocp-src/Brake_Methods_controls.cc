/*-----------------------------------------------------------------------*\
 |  file: Brake_Methods_controls.cc                                      |
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


#include "Brake.hh"
#include "Brake_Pars.hh"

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


namespace BrakeDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Brake::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t4   = U__[iU_a];
    real_type t7   = cos(t4 * 0.314159265358979323846264338328e1 / 2);
    real_type t8   = log(t7);
    real_type t12  = guess_u(Q__[iQ_zeta]);
    real_type t14  = pow(t4 - t12, 2);
    real_type result__ = t4 * t1 * MU__[1] - t8 * ModelPars[iM_epsilon] * t1 + X__[iX_v] * t1 * MU__[0] + t14 * ModelPars[iM_mu];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brake::g_numEqns() const { return 1; }

  void
  Brake::g_eval(
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
    real_type t1   = P__[iP_T];
    real_type t4   = U__[iU_a];
    real_type t6   = t4 * 0.314159265358979323846264338328e1 / 2;
    real_type t7   = sin(t6);
    real_type t9   = cos(t6);
    real_type t16  = guess_u(Q__[iQ_zeta]);
    result__[ 0   ] = 1.0 / t9 * t7 * 0.314159265358979323846264338328e1 * ModelPars[iM_epsilon] * t1 / 2 + 2 * (t4 - t16) * ModelPars[iM_mu] + t1 * MU__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brake::DgDxpm_numRows() const { return 1; }
  integer Brake::DgDxpm_numCols() const { return 5; }
  integer Brake::DgDxpm_nnz()     const { return 2; }

  void
  Brake::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::DgDxpm_sparse(
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
    real_type t5   = 0.314159265358979323846264338328e1 * U__[iU_a] / 2;
    real_type t6   = sin(t5);
    real_type t7   = cos(t5);
    result__[ 0   ] = 1.0 / t7 * t6 * ModelPars[iM_epsilon] * 0.314159265358979323846264338328e1 / 2 + MU__[1];
    result__[ 1   ] = P__[iP_T];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brake::DgDu_numRows() const { return 1; }
  integer Brake::DgDu_numCols() const { return 1; }
  integer Brake::DgDu_nnz()     const { return 1; }

  void
  Brake::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brake::DgDu_sparse(
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
    real_type t1   = 0.314159265358979323846264338328e1 * 0.314159265358979323846264338328e1;
    real_type t2   = P__[iP_T];
    real_type t4   = ModelPars[iM_epsilon];
    real_type t10  = 0.314159265358979323846264338328e1 * U__[iU_a] / 2;
    real_type t11  = sin(t10);
    real_type t12  = t11 * t11;
    real_type t14  = cos(t10);
    real_type t15  = t14 * t14;
    result__[ 0   ] = t4 * t2 * t1 / 4 + 1.0 / t15 * t12 * t1 * t4 * t2 / 4 + 2 * ModelPars[iM_mu];
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
  Brake::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "Brake::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: Brake_Methods_controls.cc
