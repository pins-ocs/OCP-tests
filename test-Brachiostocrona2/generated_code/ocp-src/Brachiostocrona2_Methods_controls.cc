/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona2_Methods_controls.cc                           |
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


#include "Brachiostocrona2.hh"
#include "Brachiostocrona2_Pars.hh"

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
#define ALIAS_TimePositive_DD(__t1) TimePositive.DD( __t1)
#define ALIAS_TimePositive_D(__t1) TimePositive.D( __t1)


namespace Brachiostocrona2Define {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Brachiostocrona2::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_theta];
    real_type t5   = pow(t2 - ModelPars[iM_theta0], 2);
    real_type t7   = P__[iP_T];
    real_type t8   = TimePositive(-t7);
    real_type t11  = X__[iX_v];
    real_type t12  = cos(t2);
    real_type t17  = sin(t2);
    real_type result__ = t12 * t11 * t7 * MU__[0] + t17 * t11 * t7 * MU__[1] - t17 * ModelPars[iM_g] * t7 * MU__[2] + t5 * ModelPars[iM_epsi] + t8;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona2::g_numEqns() const { return 1; }

  void
  Brachiostocrona2::g_eval(
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
    real_type t2   = U__[iU_theta];
    real_type t8   = P__[iP_T];
    real_type t10  = X__[iX_v];
    real_type t11  = sin(t2);
    real_type t16  = cos(t2);
    result__[ 0   ] = 2 * (t2 - ModelPars[iM_theta0]) * ModelPars[iM_epsi] - t10 * t11 * t8 * MU__[0] + t10 * t16 * t8 * MU__[1] - t16 * t8 * MU__[2] * ModelPars[iM_g];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DgDxpm_numRows() const { return 1; }
  integer Brachiostocrona2::DgDxpm_numCols() const { return 7; }
  integer Brachiostocrona2::DgDxpm_nnz()     const { return 5; }

  void
  Brachiostocrona2::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 2   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DgDxpm_sparse(
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
    real_type t1   = MU__[0];
    real_type t2   = P__[iP_T];
    real_type t4   = U__[iU_theta];
    real_type t5   = sin(t4);
    real_type t7   = MU__[1];
    real_type t9   = cos(t4);
    result__[ 0   ] = -t5 * t2 * t1 + t9 * t2 * t7;
    real_type t11  = X__[iX_v];
    real_type t17  = ModelPars[iM_g];
    result__[ 1   ] = -t5 * t11 * t1 + t9 * t11 * t7 - t9 * t17 * MU__[2];
    real_type t20  = t11 * t2;
    result__[ 2   ] = -t5 * t20;
    result__[ 3   ] = t9 * t20;
    result__[ 4   ] = -t9 * t17 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona2::DgDu_numRows() const { return 1; }
  integer Brachiostocrona2::DgDu_numCols() const { return 1; }
  integer Brachiostocrona2::DgDu_nnz()     const { return 1; }

  void
  Brachiostocrona2::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona2::DgDu_sparse(
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
    real_type t4   = P__[iP_T];
    real_type t6   = X__[iX_v];
    real_type t7   = U__[iU_theta];
    real_type t8   = cos(t7);
    real_type t13  = sin(t7);
    result__[ 0   ] = -t13 * t6 * t4 * MU__[1] + t13 * ModelPars[iM_g] * t4 * MU__[2] - t8 * t6 * t4 * MU__[0] + 2 * ModelPars[iM_epsi];
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
  Brachiostocrona2::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "Brachiostocrona2::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: Brachiostocrona2_Methods_controls.cc
