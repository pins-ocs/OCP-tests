/*-----------------------------------------------------------------------*\
 |  file: ROSS_Ball_Mizel_Methods_controls.cc                            |
 |                                                                       |
 |  version: 1.0   date 12/3/2023                                        |
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


#include "ROSS_Ball_Mizel.hh"
#include "ROSS_Ball_Mizel_Pars.hh"

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


namespace ROSS_Ball_MizelDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ROSS_Ball_Mizel::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t5   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t7   = pow(-t2 * t1 + t5, 2);
    real_type t8   = U__[iU_u];
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t9;
    real_type t12  = t10 * t10;
    real_type result__ = t12 * t10 * t9 * t7 + t8 * MU__[0] + t9 * ModelPars[iM_epsilon];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ROSS_Ball_Mizel::g_numEqns() const { return 1; }

  void
  ROSS_Ball_Mizel::g_eval(
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
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t5   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t7   = pow(-t2 * t1 + t5, 2);
    real_type t8   = U__[iU_u];
    real_type t9   = t8 * t8;
    real_type t10  = t9 * t9;
    real_type t12  = t10 * t10;
    result__[ 0   ] = 14 * t12 * t10 * t8 * t7 + 2 * t8 * ModelPars[iM_epsilon] + MU__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ROSS_Ball_Mizel::DgDxpm_numRows() const { return 1; }
  integer ROSS_Ball_Mizel::DgDxpm_numCols() const { return 2; }
  integer ROSS_Ball_Mizel::DgDxpm_nnz()     const { return 2; }

  void
  ROSS_Ball_Mizel::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ROSS_Ball_Mizel::DgDxpm_sparse(
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
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t5   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t7   = U__[iU_u];
    real_type t8   = t7 * t7;
    real_type t9   = t8 * t8;
    real_type t11  = t9 * t9;
    result__[ 0   ] = -84 * t2 * t11 * t9 * t7 * (-t2 * t1 + t5);
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ROSS_Ball_Mizel::DgDu_numRows() const { return 1; }
  integer ROSS_Ball_Mizel::DgDu_numCols() const { return 1; }
  integer ROSS_Ball_Mizel::DgDu_nnz()     const { return 1; }

  void
  ROSS_Ball_Mizel::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ROSS_Ball_Mizel::DgDu_sparse(
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
    real_type t1   = X__[iX_x];
    real_type t2   = t1 * t1;
    real_type t5   = Q__[iQ_zeta] * Q__[iQ_zeta];
    real_type t7   = pow(-t2 * t1 + t5, 2);
    real_type t9   = U__[iU_u] * U__[iU_u];
    real_type t10  = t9 * t9;
    real_type t11  = t10 * t10;
    result__[ 0   ] = 182 * t11 * t10 * t7 + 2 * ModelPars[iM_epsilon];
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
  ROSS_Ball_Mizel::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "ROSS_Ball_Mizel::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: ROSS_Ball_Mizel_Methods_controls.cc
