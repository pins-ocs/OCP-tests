/*-----------------------------------------------------------------------*\
 |  file: CristianiMartinon_Methods_controls.cc                          |
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


#include "CristianiMartinon.hh"
#include "CristianiMartinon_Pars.hh"

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
#define ALIAS_pos_DD(__t1) pos.DD( __t1)
#define ALIAS_pos_D(__t1) pos.D( __t1)
#define ALIAS_Tpositive_DD(__t1) Tpositive.DD( __t1)
#define ALIAS_Tpositive_D(__t1) Tpositive.D( __t1)


namespace CristianiMartinonDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  CristianiMartinon::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_T];
    real_type t3   = X__[iX_y];
    real_type t5   = yguess(Q__[iQ_zeta]);
    real_type t7   = pow(t3 - t5, 2);
    real_type t9   = Tpositive(-t1);
    real_type t13  = cfun(X__[iX_x], t3);
    real_type t14  = U__[iU_u];
    real_type t15  = cos(t14);
    real_type t20  = sin(t14);
    real_type result__ = t15 * t13 * t1 * MU__[0] + t20 * t13 * t1 * MU__[1] + t7 * ModelPars[iM_WY] + t1 + t9;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer CristianiMartinon::g_numEqns() const { return 1; }

  void
  CristianiMartinon::g_eval(
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
    real_type t2   = P__[iP_T];
    real_type t6   = cfun(X__[iX_x], X__[iX_y]);
    real_type t7   = U__[iU_u];
    real_type t8   = sin(t7);
    real_type t13  = cos(t7);
    result__[ 0   ] = t13 * t6 * t2 * MU__[1] - t8 * t6 * t2 * MU__[0];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CristianiMartinon::DgDxpm_numRows() const { return 1; }
  integer CristianiMartinon::DgDxpm_numCols() const { return 5; }
  integer CristianiMartinon::DgDxpm_nnz()     const { return 5; }

  void
  CristianiMartinon::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CristianiMartinon::DgDxpm_sparse(
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
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_x];
    real_type t5   = X__[iX_y];
    real_type t6   = cfun_D_1(t4, t5);
    real_type t7   = U__[iU_u];
    real_type t8   = sin(t7);
    real_type t11  = MU__[1];
    real_type t12  = t2 * t11;
    real_type t13  = cos(t7);
    result__[ 0   ] = t13 * t6 * t12 - t8 * t6 * t3;
    real_type t16  = cfun_D_2(t4, t5);
    result__[ 1   ] = t13 * t16 * t12 - t8 * t16 * t3;
    real_type t21  = cfun(t4, t5);
    result__[ 2   ] = -t8 * t21 * t1 + t13 * t21 * t11;
    real_type t26  = t21 * t2;
    result__[ 3   ] = -t8 * t26;
    result__[ 4   ] = t13 * t26;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer CristianiMartinon::DgDu_numRows() const { return 1; }
  integer CristianiMartinon::DgDu_numCols() const { return 1; }
  integer CristianiMartinon::DgDu_nnz()     const { return 1; }

  void
  CristianiMartinon::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  CristianiMartinon::DgDu_sparse(
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
    real_type t2   = P__[iP_T];
    real_type t6   = cfun(X__[iX_x], X__[iX_y]);
    real_type t7   = U__[iU_u];
    real_type t8   = cos(t7);
    real_type t13  = sin(t7);
    result__[ 0   ] = -t13 * t6 * t2 * MU__[1] - t8 * t6 * t2 * MU__[0];
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
  CristianiMartinon::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    integer i_segment = NODE__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    U__[ iU_u ] = atan(MU__[1] / MU__[0]);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

}

// EOF: CristianiMartinon_Methods_controls.cc
