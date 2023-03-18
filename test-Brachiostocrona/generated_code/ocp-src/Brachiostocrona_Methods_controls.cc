/*-----------------------------------------------------------------------*\
 |  file: Brachiostocrona_Methods_controls.cc                            |
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


#include "Brachiostocrona.hh"
#include "Brachiostocrona_Pars.hh"

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
#define ALIAS_LowBound_DD(__t1) LowBound.DD( __t1)
#define ALIAS_LowBound_D(__t1) LowBound.D( __t1)
#define ALIAS_vthetaControl_D_3(__t1, __t2, __t3) vthetaControl.D_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2(__t1, __t2, __t3) vthetaControl.D_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1(__t1, __t2, __t3) vthetaControl.D_1( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_3_3(__t1, __t2, __t3) vthetaControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_3(__t1, __t2, __t3) vthetaControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_2_2(__t1, __t2, __t3) vthetaControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_3(__t1, __t2, __t3) vthetaControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_2(__t1, __t2, __t3) vthetaControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_vthetaControl_D_1_1(__t1, __t2, __t3) vthetaControl.D_1_1( __t1, __t2, __t3)


namespace BrachiostocronaDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Brachiostocrona::g_fun_eval(
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
    real_type t2   = U__[iU_vtheta];
    real_type t3   = vthetaControl(t2, -10, 10);
    real_type t11  = LowBound(ModelPars[iM_slope_low] * X__[iX_x] - X__[iX_y] + ModelPars[iM_y0_low]);
    real_type t14  = X__[iX_v];
    real_type t15  = X__[iX_theta];
    real_type t16  = cos(t15);
    real_type t21  = sin(t15);
    real_type result__ = t16 * t14 * t1 * MU__[0] + t21 * t14 * t1 * MU__[1] - t21 * ModelPars[iM_g] * t1 * MU__[2] + t3 * t1 + t2 * MU__[3] + t11;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Brachiostocrona::g_numEqns() const { return 1; }

  void
  Brachiostocrona::g_eval(
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
    real_type t3   = ALIAS_vthetaControl_D_1(U__[iU_vtheta], -10, 10);
    result__[ 0   ] = t3 * P__[iP_T] + MU__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DgDxpm_numRows() const { return 1; }
  integer Brachiostocrona::DgDxpm_numCols() const { return 9; }
  integer Brachiostocrona::DgDxpm_nnz()     const { return 2; }

  void
  Brachiostocrona::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 8   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona::DgDxpm_sparse(
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
    result__[ 0   ] = ALIAS_vthetaControl_D_1(U__[iU_vtheta], -10, 10);
    result__[ 1   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Brachiostocrona::DgDu_numRows() const { return 1; }
  integer Brachiostocrona::DgDu_numCols() const { return 1; }
  integer Brachiostocrona::DgDu_nnz()     const { return 1; }

  void
  Brachiostocrona::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Brachiostocrona::DgDu_sparse(
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
    real_type t3   = ALIAS_vthetaControl_D_1_1(U__[iU_vtheta], -10, 10);
    result__[ 0   ] = t3 * P__[iP_T];
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
  Brachiostocrona::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    integer i_segment = NODE__.i_segment;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    U__[ iU_vtheta ] = vthetaControl.solve(-MU__[3] / P__[iP_T], -10, 10);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

}

// EOF: Brachiostocrona_Methods_controls.cc
