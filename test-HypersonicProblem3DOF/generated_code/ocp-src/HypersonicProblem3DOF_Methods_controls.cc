/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_controls.cc                      |
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


#include "HypersonicProblem3DOF.hh"
#include "HypersonicProblem3DOF_Pars.hh"

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
#define ALIAS_G_bound_max_DD(__t1) G_bound_max.DD( __t1)
#define ALIAS_G_bound_max_D(__t1) G_bound_max.D( __t1)
#define ALIAS_G_bound_min_DD(__t1) G_bound_min.DD( __t1)
#define ALIAS_G_bound_min_D(__t1) G_bound_min.D( __t1)
#define ALIAS_u2Control_D_3(__t1, __t2, __t3) u2Control.D_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2(__t1, __t2, __t3) u2Control.D_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1(__t1, __t2, __t3) u2Control.D_1( __t1, __t2, __t3)
#define ALIAS_u2Control_D_3_3(__t1, __t2, __t3) u2Control.D_3_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_3(__t1, __t2, __t3) u2Control.D_2_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_2_2(__t1, __t2, __t3) u2Control.D_2_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_3(__t1, __t2, __t3) u2Control.D_1_3( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_2(__t1, __t2, __t3) u2Control.D_1_2( __t1, __t2, __t3)
#define ALIAS_u2Control_D_1_1(__t1, __t2, __t3) u2Control.D_1_1( __t1, __t2, __t3)


namespace HypersonicProblem3DOFDefine {

  /*\
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  HypersonicProblem3DOF::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = U__[iU_alpha];
    real_type t3   = t2 * t2;
    real_type t5   = X__[iX_G];
    real_type t7   = cos(t5 / 2);
    real_type t8   = log(t7);
    real_type t10  = U__[iU_c_h];
    real_type t11  = t10 * t10;
    real_type t12  = U__[iU_c_theta];
    real_type t13  = t12 * t12;
    real_type t14  = U__[iU_c_phi];
    real_type t15  = t14 * t14;
    real_type t16  = U__[iU_c_V];
    real_type t17  = t16 * t16;
    real_type t18  = U__[iU_c_G];
    real_type t19  = t18 * t18;
    real_type t20  = U__[iU_c_psi];
    real_type t21  = t20 * t20;
    real_type t22  = U__[iU_c_sigma];
    real_type t23  = t22 * t22;
    real_type t26  = U__[iU_u2];
    real_type t27  = u2Control(t26, -1, 1);
    real_type t30  = G_bound_min(-0.314159265358979323846264338328e1 - t5);
    real_type t33  = G_bound_max(t5 - 0.314159265358979323846264338328e1);
    real_type t37  = ModelPars[iM_ODE];
    real_type t38  = X__[iX_V];
    real_type t39  = t38 * t37;
    real_type t40  = sin(t5);
    real_type t42  = ModelPars[iM_CTRL];
    real_type t48  = cos(t5);
    real_type t50  = X__[iX_psi];
    real_type t51  = cos(t50);
    real_type t53  = X__[iX_h];
    real_type t54  = ModelPars[iM_re] + t53;
    real_type t55  = 1.0 / t54;
    real_type t57  = X__[iX_phi];
    real_type t58  = cos(t57);
    real_type t67  = sin(t50);
    real_type t76  = ModelPars[iM_mu];
    real_type t78  = t54 * t54;
    real_type t79  = 1.0 / t78;
    real_type t85  = exp(-1.0 / ModelPars[iM_S] * t53);
    real_type t86  = t85 * ModelPars[iM_rho0];
    real_type t87  = t38 * t38;
    real_type t95  = ModelPars[iM_Aref];
    real_type t98  = 1.0 / ModelPars[iM_m];
    real_type t113 = t2 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t115 = X__[iX_sigma];
    real_type t116 = cos(t115);
    real_type t121 = t55 * t38;
    real_type t137 = sin(t115);
    real_type t144 = tan(t57);
    real_type result__ = t3 * t1 - t8 * t1 + (t11 + t13 + t15 + t17 + t19 + t21 + t23) * t1 + t27 * t1 + t30 * t1 + t33 * t1 + (t10 * t42 + t40 * t39) * t1 * MU__[0] + (1.0 / t58 * t55 * t51 * t48 * t39 + t12 * t42) * t1 * MU__[1] + (t55 * t67 * t48 * t39 + t14 * t42) * t1 * MU__[2] + ((-t79 * t76 * t40 - t98 * t95 * (t2 * ModelPars[iM_CD1] + t3 * ModelPars[iM_CD2] + ModelPars[iM_CD0]) * t87 * t86 / 2) * t37 + t16 * t42) * t1 * MU__[3] + ((t116 * t98 * t95 * t113 * t38 * t86 / 2 + t48 * (t121 - 1.0 / t38 * t79 * t76)) * t37 + t18 * t42) * t1 * MU__[4] + ((1.0 / t48 * t137 * t98 * t95 * t113 * t38 * t86 / 2 - t144 * t51 * t48 * t121) * t37 + t20 * t42) * t1 * MU__[5] + (t26 * ModelPars[iM_sigma_dot_max] * t37 + t22 * t42) * t1 * MU__[6];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::g_numEqns() const { return 9; }

  void
  HypersonicProblem3DOF::g_eval(
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
    real_type t1   = P__[iP_Tf];
    real_type t2   = U__[iU_alpha];
    real_type t6   = t1 * MU__[3];
    real_type t7   = ModelPars[iM_ODE];
    real_type t9   = ModelPars[iM_rho0] * t7;
    real_type t15  = exp(-X__[iX_h] / ModelPars[iM_S]);
    real_type t16  = X__[iX_V];
    real_type t17  = t16 * t16;
    real_type t24  = ModelPars[iM_Aref];
    real_type t27  = 1.0 / ModelPars[iM_m];
    real_type t33  = t1 * MU__[4];
    real_type t34  = t15 * t9;
    real_type t37  = ModelPars[iM_CL1] * t16;
    real_type t39  = X__[iX_sigma];
    real_type t40  = cos(t39);
    real_type t46  = t1 * MU__[5];
    real_type t49  = sin(t39);
    real_type t52  = cos(X__[iX_G]);
    result__[ 0   ] = 2 * t2 * t1 - t27 * t24 * (2 * t2 * ModelPars[iM_CD2] + ModelPars[iM_CD1]) * t17 * t15 * t9 * t6 / 2 + t40 * t27 * t24 * t37 * t34 * t33 / 2 + 1.0 / t52 * t49 * t27 * t24 * t37 * t34 * t46 / 2;
    real_type t59  = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    real_type t62  = t1 * MU__[6];
    result__[ 1   ] = ModelPars[iM_sigma_dot_max] * t7 * t62 + t59 * t1;
    real_type t68  = ModelPars[iM_CTRL];
    result__[ 2   ] = t68 * t1 * MU__[0] + 2 * U__[iU_c_h] * t1;
    result__[ 3   ] = t68 * t1 * MU__[1] + 2 * U__[iU_c_theta] * t1;
    result__[ 4   ] = t68 * t1 * MU__[2] + 2 * U__[iU_c_phi] * t1;
    result__[ 5   ] = 2 * U__[iU_c_V] * t1 + t68 * t6;
    result__[ 6   ] = 2 * U__[iU_c_G] * t1 + t68 * t33;
    result__[ 7   ] = 2 * U__[iU_c_psi] * t1 + t68 * t46;
    result__[ 8   ] = 2 * U__[iU_c_sigma] * t1 + t68 * t62;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DgDxpm_numRows() const { return 9; }
  integer HypersonicProblem3DOF::DgDxpm_numCols() const { return 15; }
  integer HypersonicProblem3DOF::DgDxpm_nnz()     const { return 24; }

  void
  HypersonicProblem3DOF::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 4   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 6   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 7   ;
    iIndex[5 ] = 0   ; jIndex[5 ] = 11  ;
    iIndex[6 ] = 0   ; jIndex[6 ] = 12  ;
    iIndex[7 ] = 0   ; jIndex[7 ] = 13  ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 7   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 14  ;
    iIndex[10] = 2   ; jIndex[10] = 7   ;
    iIndex[11] = 2   ; jIndex[11] = 8   ;
    iIndex[12] = 3   ; jIndex[12] = 7   ;
    iIndex[13] = 3   ; jIndex[13] = 9   ;
    iIndex[14] = 4   ; jIndex[14] = 7   ;
    iIndex[15] = 4   ; jIndex[15] = 10  ;
    iIndex[16] = 5   ; jIndex[16] = 7   ;
    iIndex[17] = 5   ; jIndex[17] = 11  ;
    iIndex[18] = 6   ; jIndex[18] = 7   ;
    iIndex[19] = 6   ; jIndex[19] = 12  ;
    iIndex[20] = 7   ; jIndex[20] = 7   ;
    iIndex[21] = 7   ; jIndex[21] = 13  ;
    iIndex[22] = 8   ; jIndex[22] = 7   ;
    iIndex[23] = 8   ; jIndex[23] = 14  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::DgDxpm_sparse(
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
    real_type t1   = MU__[3];
    real_type t2   = P__[iP_Tf];
    real_type t3   = t2 * t1;
    real_type t4   = ModelPars[iM_ODE];
    real_type t5   = ModelPars[iM_rho0];
    real_type t6   = t5 * t4;
    real_type t8   = 1.0 / ModelPars[iM_S];
    real_type t9   = t8 * t6;
    real_type t13  = exp(-t8 * X__[iX_h]);
    real_type t14  = X__[iX_V];
    real_type t15  = t14 * t14;
    real_type t18  = U__[iU_alpha];
    real_type t22  = 2 * t18 * ModelPars[iM_CD2] + ModelPars[iM_CD1];
    real_type t23  = ModelPars[iM_Aref];
    real_type t26  = 1.0 / ModelPars[iM_m];
    real_type t27  = t26 * t23 * t22;
    real_type t30  = MU__[4];
    real_type t31  = t2 * t30;
    real_type t33  = t14 * t13;
    real_type t34  = ModelPars[iM_CL1];
    real_type t36  = t26 * t23;
    real_type t37  = X__[iX_sigma];
    real_type t38  = cos(t37);
    real_type t39  = t38 * t36;
    real_type t42  = MU__[5];
    real_type t43  = t2 * t42;
    real_type t44  = t4 * t43;
    real_type t48  = t34 * t14;
    real_type t49  = t23 * t48;
    real_type t50  = sin(t37);
    real_type t52  = X__[iX_G];
    real_type t53  = cos(t52);
    real_type t54  = 1.0 / t53;
    real_type t55  = t54 * t50 * t26;
    result__[ 0   ] = -t55 * t49 * t13 * t8 * t5 * t44 / 2 + t27 * t15 * t13 * t9 * t3 / 2 - t39 * t34 * t33 * t9 * t31 / 2;
    real_type t67  = t13 * t6;
    real_type t68  = t67 * t43;
    real_type t69  = t23 * t34;
    real_type t70  = t55 * t69;
    result__[ 1   ] = -t27 * t33 * t6 * t3 + t39 * t34 * t13 * t6 * t31 / 2 + t70 * t68 / 2;
    real_type t73  = t13 * t5;
    real_type t74  = t14 * t73;
    real_type t77  = t53 * t53;
    real_type t80  = sin(t52);
    result__[ 2   ] = t80 / t77 * t50 * t26 * t69 * t74 * t44 / 2;
    result__[ 3   ] = t54 * t38 * t26 * t49 * t68 / 2 - t50 * t36 * t48 * t67 * t31 / 2;
    real_type t97  = t36 * t22 * t15;
    real_type t102 = t39 * t48;
    result__[ 4   ] = 2 * t18 - t97 * t73 * t4 * t1 / 2 + t102 * t73 * t4 * t30 / 2 + t70 * t74 * t4 * t42 / 2;
    real_type t109 = t4 * t2;
    real_type t110 = t73 * t109;
    result__[ 5   ] = -t97 * t110 / 2;
    result__[ 6   ] = t102 * t110 / 2;
    result__[ 7   ] = t70 * t74 * t109 / 2;
    real_type t117 = ALIAS_u2Control_D_1(U__[iU_u2], -1, 1);
    real_type t118 = MU__[6];
    real_type t120 = ModelPars[iM_sigma_dot_max];
    result__[ 8   ] = t118 * t120 * t4 + t117;
    result__[ 9   ] = t120 * t109;
    real_type t123 = ModelPars[iM_CTRL];
    result__[ 10  ] = t123 * MU__[0] + 2 * U__[iU_c_h];
    result__[ 11  ] = t123 * t2;
    result__[ 12  ] = t123 * MU__[1] + 2 * U__[iU_c_theta];
    result__[ 13  ] = result__[11];
    result__[ 14  ] = t123 * MU__[2] + 2 * U__[iU_c_phi];
    result__[ 15  ] = result__[13];
    result__[ 16  ] = t1 * t123 + 2 * U__[iU_c_V];
    result__[ 17  ] = result__[15];
    result__[ 18  ] = t123 * t30 + 2 * U__[iU_c_G];
    result__[ 19  ] = result__[17];
    result__[ 20  ] = t123 * t42 + 2 * U__[iU_c_psi];
    result__[ 21  ] = result__[19];
    result__[ 22  ] = t118 * t123 + 2 * U__[iU_c_sigma];
    result__[ 23  ] = result__[21];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 24, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DgDu_numRows() const { return 9; }
  integer HypersonicProblem3DOF::DgDu_numCols() const { return 9; }
  integer HypersonicProblem3DOF::DgDu_nnz()     const { return 9; }

  void
  HypersonicProblem3DOF::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
    iIndex[7 ] = 7   ; jIndex[7 ] = 7   ;
    iIndex[8 ] = 8   ; jIndex[8 ] = 8   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::DgDu_sparse(
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
    real_type t1   = P__[iP_Tf];
    real_type t2   = 2 * t1;
    real_type t13  = exp(-X__[iX_h] / ModelPars[iM_S]);
    real_type t15  = X__[iX_V] * X__[iX_V];
    result__[ 0   ] = t2 - ModelPars[iM_CD2] * ModelPars[iM_Aref] / ModelPars[iM_m] * t15 * t13 * ModelPars[iM_ODE] * ModelPars[iM_rho0] * t1 * MU__[3];
    real_type t26  = ALIAS_u2Control_D_1_1(U__[iU_u2], -1, 1);
    result__[ 1   ] = t26 * t1;
    result__[ 2   ] = t2;
    result__[ 3   ] = result__[2];
    result__[ 4   ] = result__[3];
    result__[ 5   ] = result__[4];
    result__[ 6   ] = result__[5];
    result__[ 7   ] = result__[6];
    result__[ 8   ] = result__[7];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 9, i_segment );
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
  HypersonicProblem3DOF::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    UTILS_ERROR(
      "HypersonicProblem3DOF::u_eval_analytic\n"
      "no analytic control available, use iterative!\n"
    );
  }

}

// EOF: HypersonicProblem3DOF_Methods_controls.cc
