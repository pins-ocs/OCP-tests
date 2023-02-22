/*-----------------------------------------------------------------------*\
 |  file: ICLOCS_MinimumFuelOrbitRaising_Methods_controls.cc             |
 |                                                                       |
 |  version: 1.0   date 22/2/2023                                        |
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


#include "ICLOCS_MinimumFuelOrbitRaising.hh"
#include "ICLOCS_MinimumFuelOrbitRaising_Pars.hh"

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


namespace ICLOCS_MinimumFuelOrbitRaisingDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  ICLOCS_MinimumFuelOrbitRaising::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_vr];
    real_type t3   = U__[iU_theta];
    real_type t4   = t3 * t3;
    real_type t9   = X__[iX_vt];
    real_type t10  = t9 * t9;
    real_type t11  = X__[iX_r];
    real_type t12  = 1.0 / t11;
    real_type t14  = t11 * t11;
    real_type t16  = ModelPars[iM_T];
    real_type t17  = sin(t3);
    real_type t20  = mass(Q__[iQ_zeta]);
    real_type t21  = 1.0 / t20;
    real_type t28  = cos(t3);
    real_type result__ = -t1 + t4 * ModelPars[iM_epsilon] + t1 * MU__[0] + (t12 * t10 - 1.0 / t14 + t21 * t17 * t16) * MU__[1] + (-t12 * t9 * t1 + t21 * t28 * t16) * MU__[2];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS_MinimumFuelOrbitRaising::g_numEqns() const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::g_eval(
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
    real_type t6   = ModelPars[iM_T];
    real_type t8   = cos(t2);
    real_type t10  = mass(Q__[iQ_zeta]);
    real_type t11  = 1.0 / t10;
    real_type t16  = sin(t2);
    result__[ 0   ] = -t11 * t16 * t6 * MU__[2] + t11 * t8 * t6 * MU__[1] + 2 * t2 * ModelPars[iM_epsilon];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DgDxpm_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDxpm_numCols() const { return 6; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDxpm_nnz()     const { return 2; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDxpm_sparse(
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
    real_type t1   = ModelPars[iM_T];
    real_type t2   = U__[iU_theta];
    real_type t3   = cos(t2);
    real_type t6   = mass(Q__[iQ_zeta]);
    real_type t7   = 1.0 / t6;
    result__[ 0   ] = t7 * t3 * t1;
    real_type t8   = sin(t2);
    result__[ 1   ] = -t7 * t8 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS_MinimumFuelOrbitRaising::DgDu_numRows() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDu_numCols() const { return 1; }
  integer ICLOCS_MinimumFuelOrbitRaising::DgDu_nnz()     const { return 1; }

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS_MinimumFuelOrbitRaising::DgDu_sparse(
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
    real_type t4   = ModelPars[iM_T];
    real_type t6   = U__[iU_theta];
    real_type t7   = sin(t6);
    real_type t9   = mass(Q__[iQ_zeta]);
    real_type t10  = 1.0 / t9;
    real_type t15  = cos(t6);
    result__[ 0   ] = -t10 * t15 * t4 * MU__[2] - t10 * t7 * t4 * MU__[1] + 2 * ModelPars[iM_epsilon];
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
  ICLOCS_MinimumFuelOrbitRaising::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "ICLOCS_MinimumFuelOrbitRaising::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: ICLOCS_MinimumFuelOrbitRaising_Methods_controls.cc
