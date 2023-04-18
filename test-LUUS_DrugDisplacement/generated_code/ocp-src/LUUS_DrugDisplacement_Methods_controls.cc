/*-----------------------------------------------------------------------*\
 |  file: LUUS_DrugDisplacement_Methods_controls.cc                      |
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


#include "LUUS_DrugDisplacement.hh"
#include "LUUS_DrugDisplacement_Pars.hh"

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
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace LUUS_DrugDisplacementDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  LUUS_DrugDisplacement::g_fun_eval(
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
    real_type t2   = U__[iU_u];
    real_type t3   = uControl(t2, 0, 8);
    real_type t7   = X__[iX_x1];
    real_type t8   = X__[iX_x2];
    real_type t9   = g1(t7, t8);
    real_type t10  = g4(t7, t8);
    real_type t14  = t2 - 2 * t8;
    real_type t22  = g3(t7, t8);
    real_type result__ = t3 * t1 + ((0.2e-1 - t7) * t10 + 0.464e2 * t14 * t7) * t9 * t1 * MU__[0] + (t14 * t22 + 0.928e0 - 0.464e2 * t7) * t9 * t1 * MU__[1];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer LUUS_DrugDisplacement::g_numEqns() const { return 1; }

  void
  LUUS_DrugDisplacement::g_eval(
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
    real_type t1   = P__[iP_T];
    real_type t3   = ALIAS_uControl_D_1(U__[iU_u], 0, 8);
    real_type t7   = X__[iX_x1];
    real_type t8   = X__[iX_x2];
    real_type t9   = g1(t7, t8);
    real_type t15  = g3(t7, t8);
    result__[ 0   ] = t3 * t1 + 0.464e2 * t7 * t9 * t1 * MU__[0] + t15 * t9 * t1 * MU__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DgDxpm_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DgDxpm_numCols() const { return 5; }
  integer LUUS_DrugDisplacement::DgDxpm_nnz()     const { return 5; }

  void
  LUUS_DrugDisplacement::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DgDxpm_sparse(
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
    real_type t4   = X__[iX_x1];
    real_type t5   = X__[iX_x2];
    real_type t6   = g1_D_1(t4, t5);
    real_type t10  = g1(t4, t5);
    real_type t13  = MU__[1];
    real_type t14  = t2 * t13;
    real_type t15  = g3(t4, t5);
    real_type t18  = g3_D_1(t4, t5);
    result__[ 0   ] = 0.464e2 * t4 * t6 * t3 + 0.464e2 * t10 * t3 + t15 * t6 * t14 + t18 * t10 * t14;
    real_type t21  = g1_D_2(t4, t5);
    real_type t27  = g3_D_2(t4, t5);
    result__[ 1   ] = 0.464e2 * t4 * t21 * t3 + t15 * t21 * t14 + t27 * t10 * t14;
    real_type t31  = ALIAS_uControl_D_1(U__[iU_u], 0, 8);
    result__[ 2   ] = t31 + 0.464e2 * t4 * t10 * t1 + t15 * t10 * t13;
    real_type t37  = t10 * t2;
    result__[ 3   ] = 0.464e2 * t4 * t37;
    result__[ 4   ] = t15 * t37;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer LUUS_DrugDisplacement::DgDu_numRows() const { return 1; }
  integer LUUS_DrugDisplacement::DgDu_numCols() const { return 1; }
  integer LUUS_DrugDisplacement::DgDu_nnz()     const { return 1; }

  void
  LUUS_DrugDisplacement::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  LUUS_DrugDisplacement::DgDu_sparse(
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
    real_type t3   = ALIAS_uControl_D_1_1(U__[iU_u], 0, 8);
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
  LUUS_DrugDisplacement::u_eval_analytic(
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
    real_type t1   = X__[iX_x1];
    real_type t2   = X__[iX_x2];
    real_type t3   = g1(t1, t2);
    real_type t8   = g3(t1, t2);
    U__[ iU_u ] = uControl.solve(-0.2000000000e0 * (0.232e3 * t1 * MU__[0] + 5.0 * t8 * MU__[1]) * t3, 0, 8);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 1 );
  }

}

// EOF: LUUS_DrugDisplacement_Methods_controls.cc
