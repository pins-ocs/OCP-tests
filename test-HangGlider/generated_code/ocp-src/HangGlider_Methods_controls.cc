/*-----------------------------------------------------------------------*\
 |  file: HangGlider_Methods_controls.cc                                 |
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


#include "HangGlider.hh"
#include "HangGlider_Pars.hh"

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
#define ALIAS_Tbound_DD(__t1) Tbound.DD( __t1)
#define ALIAS_Tbound_D(__t1) Tbound.D( __t1)
#define ALIAS_cLControl_D_3(__t1, __t2, __t3) cLControl.D_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2(__t1, __t2, __t3) cLControl.D_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1(__t1, __t2, __t3) cLControl.D_1( __t1, __t2, __t3)
#define ALIAS_cLControl_D_3_3(__t1, __t2, __t3) cLControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_3(__t1, __t2, __t3) cLControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_2_2(__t1, __t2, __t3) cLControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_3(__t1, __t2, __t3) cLControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_2(__t1, __t2, __t3) cLControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_cLControl_D_1_1(__t1, __t2, __t3) cLControl.D_1_1( __t1, __t2, __t3)


namespace HangGliderDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  HangGlider::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = U__[iU_cL];
    real_type t4   = pow(t2 - 0.7e0, 2);
    real_type t8   = cLControl(t2, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t9   = P__[iP_T];
    real_type t10  = Tbound(-t9);
    real_type t13  = X__[iX_vx];
    real_type t17  = X__[iX_vy];
    real_type t22  = 1.0 / ModelPars[iM_m];
    real_type t23  = X__[iX_x];
    real_type t24  = v(t23, t13, t17);
    real_type t25  = 1.0 / t24;
    real_type t28  = t2 * t2;
    real_type t32  = Dfun(t23, t13, t17);
    real_type t33  = t32 * (t28 * ModelPars[iM_c1] + ModelPars[iM_c0]);
    real_type t35  = Lfun(t23, t13, t17);
    real_type t36  = t35 * t2;
    real_type t37  = w(t23, t17);
    real_type result__ = t4 * ModelPars[iM_W] + t8 + t10 + t13 * t9 * MU__[0] + t17 * t9 * MU__[1] + (-t13 * t33 - t37 * t36) * t25 * t22 * t9 * MU__[2] + ((t13 * t36 - t37 * t33) * t25 * t22 * t9 - ModelPars[iM_g] * t9) * MU__[3];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HangGlider::g_numEqns() const { return 1; }

  void
  HangGlider::g_eval(
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
    real_type t2   = U__[iU_cL];
    real_type t8   = ALIAS_cLControl_D_1(t2, ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t10  = P__[iP_T];
    real_type t14  = X__[iX_x];
    real_type t15  = X__[iX_vx];
    real_type t16  = X__[iX_vy];
    real_type t17  = v(t14, t15, t16);
    real_type t19  = 1.0 / t17 / ModelPars[iM_m];
    real_type t21  = t2 * ModelPars[iM_c1];
    real_type t22  = Dfun(t14, t15, t16);
    real_type t26  = Lfun(t14, t15, t16);
    real_type t27  = w(t14, t16);
    result__[ 0   ] = 2 * (t2 - 0.7e0) * ModelPars[iM_W] + t8 + (-2 * t15 * t21 * t22 - t26 * t27) * t19 * t10 * MU__[2] + (-2 * t27 * t22 * t21 + t15 * t26) * t19 * t10 * MU__[3];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DgDxpm_numRows() const { return 1; }
  integer HangGlider::DgDxpm_numCols() const { return 9; }
  integer HangGlider::DgDxpm_nnz()     const { return 6; }

  void
  HangGlider::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 8   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDxpm_sparse(
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
    real_type t1   = MU__[2];
    real_type t2   = P__[iP_T];
    real_type t3   = t2 * t1;
    real_type t5   = 1.0 / ModelPars[iM_m];
    real_type t6   = t5 * t3;
    real_type t7   = X__[iX_x];
    real_type t8   = X__[iX_vx];
    real_type t9   = X__[iX_vy];
    real_type t10  = v(t7, t8, t9);
    real_type t11  = t10 * t10;
    real_type t12  = 1.0 / t11;
    real_type t15  = ModelPars[iM_c1] * U__[iU_cL];
    real_type t16  = Dfun(t7, t8, t9);
    real_type t20  = Lfun(t7, t8, t9);
    real_type t21  = w(t7, t9);
    real_type t23  = -2 * t8 * t16 * t15 - t21 * t20;
    real_type t24  = t23 * t12;
    real_type t25  = v_D_1(t7, t8, t9);
    real_type t28  = 1.0 / t10;
    real_type t29  = t28 * t5;
    real_type t30  = Dfun_D_1(t7, t8, t9);
    real_type t34  = Lfun_D_1(t7, t8, t9);
    real_type t36  = w_D_1(t7, t9);
    real_type t41  = MU__[3];
    real_type t42  = t2 * t41;
    real_type t43  = t5 * t42;
    real_type t48  = -2 * t21 * t16 * t15 + t8 * t20;
    real_type t49  = t48 * t12;
    result__[ 0   ] = -t25 * t24 * t6 + (-2 * t8 * t30 * t15 - t36 * t20 - t21 * t34) * t29 * t3 - t25 * t49 * t43 + (-2 * t36 * t16 * t15 - 2 * t21 * t30 * t15 + t8 * t34) * t29 * t42;
    real_type t62  = v_D_2(t7, t8, t9);
    real_type t65  = Dfun_D_2(t7, t8, t9);
    real_type t71  = Lfun_D_2(t7, t8, t9);
    result__[ 1   ] = -t62 * t24 * t6 + (-2 * t8 * t65 * t15 - 2 * t16 * t15 - t21 * t71) * t29 * t3 - t62 * t49 * t43 + (-2 * t21 * t65 * t15 + t8 * t71 + t20) * t29 * t42;
    real_type t85  = v_D_3(t7, t8, t9);
    real_type t88  = Dfun_D_3(t7, t8, t9);
    real_type t92  = Lfun_D_3(t7, t8, t9);
    real_type t94  = w_D_2(t7, t9);
    result__[ 2   ] = -t85 * t24 * t6 + (-2 * t8 * t88 * t15 - t94 * t20 - t21 * t92) * t29 * t3 - t85 * t49 * t43 + (-2 * t94 * t16 * t15 - 2 * t21 * t88 * t15 + t8 * t92) * t29 * t42;
    real_type t112 = t23 * t28;
    real_type t115 = t48 * t28;
    result__[ 3   ] = t112 * t5 * t1 + t115 * t5 * t41;
    real_type t117 = t5 * t2;
    result__[ 4   ] = t112 * t117;
    result__[ 5   ] = t115 * t117;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HangGlider::DgDu_numRows() const { return 1; }
  integer HangGlider::DgDu_numCols() const { return 1; }
  integer HangGlider::DgDu_nnz()     const { return 1; }

  void
  HangGlider::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HangGlider::DgDu_sparse(
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
    real_type t6   = ALIAS_cLControl_D_1_1(U__[iU_cL], ModelPars[iM_cL_min], ModelPars[iM_cL_max]);
    real_type t8   = P__[iP_T];
    real_type t11  = 1.0 / ModelPars[iM_m];
    real_type t13  = X__[iX_x];
    real_type t14  = X__[iX_vx];
    real_type t15  = X__[iX_vy];
    real_type t16  = v(t13, t14, t15);
    real_type t19  = ModelPars[iM_c1] / t16;
    real_type t20  = Dfun(t13, t14, t15);
    real_type t28  = w(t13, t15);
    result__[ 0   ] = -2 * t14 * t20 * t19 * t11 * t8 * MU__[2] - 2 * t28 * t20 * t19 * t11 * t8 * MU__[3] + t6 + 2 * ModelPars[iM_W];
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
  HangGlider::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "HangGlider::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: HangGlider_Methods_controls.cc
