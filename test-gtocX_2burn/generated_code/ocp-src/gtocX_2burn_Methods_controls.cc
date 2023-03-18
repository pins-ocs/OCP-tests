/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_controls.cc                                |
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


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burnDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  gtocX_2burn::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t3   = X__[iX_p];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = p_guess(t10);
    real_type t15  = pow(1.0 / t11 * t3 - 1, 2);
    real_type t16  = X__[iX_f];
    real_type t17  = f_guess(t10);
    real_type t19  = pow(t16 - t17, 2);
    real_type t20  = X__[iX_g];
    real_type t21  = g_guess(t10);
    real_type t23  = pow(t20 - t21, 2);
    real_type t25  = h_guess(t10);
    real_type t27  = pow(X__[iX_h] - t25, 2);
    real_type t29  = k_guess(t10);
    real_type t31  = pow(X__[iX_k] - t29, 2);
    real_type t32  = X__[iX_L];
    real_type t33  = L_guess(t10, t6);
    real_type t35  = pow(t32 - t33, 2);
    real_type t38  = cos(t32);
    real_type t40  = sin(t32);
    real_type t42  = -t38 * t16 - t40 * t20 - 1;
    real_type t43  = ray_positive(t42);
    real_type t45  = t8 - t6;
    real_type t47  = sqrt(t3);
    real_type t49  = ModelPars[iM_muS];
    real_type t50  = sqrt(t49);
    real_type t53  = ModelPars[iM_w_nonlin] / t50;
    real_type t54  = ray(t3, t16, t20, t32);
    real_type t55  = acceleration_r(t54, t49);
    real_type t68  = t42 * t42;
    real_type result__ = (t15 + t19 + t23 + t27 + t31 + t35) * (1 - ModelPars[iM_w_guess]) + t43 + t40 * t55 * t53 * t47 * t45 * MU__[1] - t38 * t55 * t53 * t47 * t45 * MU__[2] + t50 / t47 / t3 * t68 * t45 * MU__[5];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::g_numEqns() const { return 0; }

  void
  gtocX_2burn::g_eval(
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

    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 0, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DgDxpm_numRows() const { return 0; }
  integer gtocX_2burn::DgDxpm_numCols() const { return 12; }
  integer gtocX_2burn::DgDxpm_nnz()     const { return 0; }

  void
  gtocX_2burn::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DgDu_numRows() const { return 0; }
  integer gtocX_2burn::DgDu_numCols() const { return 0; }
  integer gtocX_2burn::DgDu_nnz()     const { return 0; }

  void
  gtocX_2burn::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  gtocX_2burn::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    // EMPTY!
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
  gtocX_2burn::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    // no controls to compute
  }

}

// EOF: gtocX_2burn_Methods_controls.cc
