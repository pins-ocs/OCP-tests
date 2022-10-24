/*-----------------------------------------------------------------------*\
 |  file: HypersonicProblem3DOF_Methods_ODE.cc                           |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
 |                                                                       |
 |  Copyright (C) 2022                                                   |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer HypersonicProblem3DOF::rhs_ode_numEqns() const { return 7; }

  void
  HypersonicProblem3DOF::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = ModelPars[iM_ODE];
    real_type t3   = X__[iX_V];
    real_type t4   = t3 * t2;
    real_type t5   = X__[iX_G];
    real_type t6   = sin(t5);
    real_type t8   = ModelPars[iM_CTRL];
    result__[ 0   ] = (t6 * t4 + U__[iU_c_h] * t8) * t1;
    real_type t12  = cos(t5);
    real_type t14  = X__[iX_psi];
    real_type t15  = cos(t14);
    real_type t17  = X__[iX_h];
    real_type t18  = ModelPars[iM_re] + t17;
    real_type t19  = 1.0 / t18;
    real_type t21  = X__[iX_phi];
    real_type t22  = cos(t21);
    result__[ 1   ] = (1.0 / t22 * t19 * t15 * t12 * t4 + U__[iU_c_theta] * t8) * t1;
    real_type t29  = sin(t14);
    result__[ 2   ] = (t19 * t29 * t12 * t4 + U__[iU_c_phi] * t8) * t1;
    real_type t36  = ModelPars[iM_mu];
    real_type t38  = t18 * t18;
    real_type t39  = 1.0 / t38;
    real_type t45  = exp(-1.0 / ModelPars[iM_S] * t17);
    real_type t46  = t45 * ModelPars[iM_rho0];
    real_type t47  = t3 * t3;
    real_type t50  = U__[iU_alpha];
    real_type t51  = t50 * t50;
    real_type t57  = ModelPars[iM_Aref];
    real_type t60  = 1.0 / ModelPars[iM_m];
    result__[ 3   ] = ((-t39 * t36 * t6 - t60 * t57 * (t50 * ModelPars[iM_CD1] + t51 * ModelPars[iM_CD2] + ModelPars[iM_CD0]) * t47 * t46 / 2) * t2 + U__[iU_c_V] * t8) * t1;
    real_type t73  = t50 * ModelPars[iM_CL1] + ModelPars[iM_CL0];
    real_type t75  = X__[iX_sigma];
    real_type t76  = cos(t75);
    real_type t81  = t19 * t3;
    result__[ 4   ] = ((t76 * t60 * t57 * t73 * t3 * t46 / 2 + t12 * (t81 - 1.0 / t3 * t39 * t36)) * t2 + U__[iU_c_G] * t8) * t1;
    real_type t95  = sin(t75);
    real_type t102 = tan(t21);
    result__[ 5   ] = ((1.0 / t12 * t95 * t60 * t57 * t73 * t3 * t46 / 2 - t102 * t15 * t12 * t81) * t2 + U__[iU_c_psi] * t8) * t1;
    result__[ 6   ] = (U__[iU_u2] * ModelPars[iM_sigma_dot_max] * t2 + U__[iU_c_sigma] * t8) * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::Drhs_odeDxpu_numRows() const { return 7; }
  integer HypersonicProblem3DOF::Drhs_odeDxpu_numCols() const { return 17; }
  integer HypersonicProblem3DOF::Drhs_odeDxpu_nnz()     const { return 42; }

  void
  HypersonicProblem3DOF::Drhs_odeDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 3   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 10  ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 5   ;
    iIndex[9 ] = 1   ; jIndex[9 ] = 7   ;
    iIndex[10] = 1   ; jIndex[10] = 11  ;
    iIndex[11] = 2   ; jIndex[11] = 0   ;
    iIndex[12] = 2   ; jIndex[12] = 3   ;
    iIndex[13] = 2   ; jIndex[13] = 4   ;
    iIndex[14] = 2   ; jIndex[14] = 5   ;
    iIndex[15] = 2   ; jIndex[15] = 7   ;
    iIndex[16] = 2   ; jIndex[16] = 12  ;
    iIndex[17] = 3   ; jIndex[17] = 0   ;
    iIndex[18] = 3   ; jIndex[18] = 3   ;
    iIndex[19] = 3   ; jIndex[19] = 4   ;
    iIndex[20] = 3   ; jIndex[20] = 7   ;
    iIndex[21] = 3   ; jIndex[21] = 8   ;
    iIndex[22] = 3   ; jIndex[22] = 13  ;
    iIndex[23] = 4   ; jIndex[23] = 0   ;
    iIndex[24] = 4   ; jIndex[24] = 3   ;
    iIndex[25] = 4   ; jIndex[25] = 4   ;
    iIndex[26] = 4   ; jIndex[26] = 6   ;
    iIndex[27] = 4   ; jIndex[27] = 7   ;
    iIndex[28] = 4   ; jIndex[28] = 8   ;
    iIndex[29] = 4   ; jIndex[29] = 14  ;
    iIndex[30] = 5   ; jIndex[30] = 0   ;
    iIndex[31] = 5   ; jIndex[31] = 2   ;
    iIndex[32] = 5   ; jIndex[32] = 3   ;
    iIndex[33] = 5   ; jIndex[33] = 4   ;
    iIndex[34] = 5   ; jIndex[34] = 5   ;
    iIndex[35] = 5   ; jIndex[35] = 6   ;
    iIndex[36] = 5   ; jIndex[36] = 7   ;
    iIndex[37] = 5   ; jIndex[37] = 8   ;
    iIndex[38] = 5   ; jIndex[38] = 15  ;
    iIndex[39] = 6   ; jIndex[39] = 7   ;
    iIndex[40] = 6   ; jIndex[40] = 9   ;
    iIndex[41] = 6   ; jIndex[41] = 16  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::Drhs_odeDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = P__[iP_Tf];
    real_type t2   = ModelPars[iM_ODE];
    real_type t3   = t2 * t1;
    real_type t4   = X__[iX_G];
    real_type t5   = sin(t4);
    result__[ 0   ] = t5 * t3;
    real_type t6   = X__[iX_V];
    real_type t7   = cos(t4);
    result__[ 1   ] = t7 * t6 * t3;
    real_type t9   = t6 * t2;
    real_type t11  = ModelPars[iM_CTRL];
    result__[ 2   ] = U__[iU_c_h] * t11 + t5 * t9;
    result__[ 3   ] = t11 * t1;
    real_type t14  = t6 * t3;
    real_type t15  = X__[iX_psi];
    real_type t16  = cos(t15);
    real_type t17  = t16 * t7;
    real_type t19  = X__[iX_h];
    real_type t20  = ModelPars[iM_re] + t19;
    real_type t21  = t20 * t20;
    real_type t22  = 1.0 / t21;
    real_type t23  = X__[iX_phi];
    real_type t24  = cos(t23);
    real_type t25  = 1.0 / t24;
    result__[ 4   ] = -t25 * t22 * t17 * t14;
    real_type t29  = 1.0 / t20;
    real_type t30  = t29 * t16;
    real_type t31  = t24 * t24;
    real_type t33  = sin(t23);
    result__[ 5   ] = t33 / t31 * t30 * result__[1];
    real_type t37  = t25 * t30;
    result__[ 6   ] = t37 * t7 * t3;
    real_type t38  = t16 * t5;
    real_type t39  = t25 * t29;
    result__[ 7   ] = -t39 * t38 * t14;
    real_type t42  = sin(t15);
    real_type t43  = t42 * t7;
    result__[ 8   ] = -t39 * t43 * t14;
    result__[ 9   ] = t37 * t7 * t9 + U__[iU_c_theta] * t11;
    result__[ 10  ] = result__[3];
    result__[ 11  ] = -t22 * t43 * t14;
    real_type t52  = t29 * t43;
    result__[ 12  ] = t52 * t3;
    result__[ 13  ] = -t29 * t42 * t5 * t14;
    result__[ 14  ] = t29 * t17 * t14;
    result__[ 15  ] = U__[iU_c_phi] * t11 + t52 * t9;
    result__[ 16  ] = result__[10];
    real_type t60  = ModelPars[iM_mu];
    real_type t61  = t60 * t5;
    real_type t63  = 1.0 / t21 / t20;
    real_type t66  = ModelPars[iM_rho0];
    real_type t68  = 1.0 / ModelPars[iM_S];
    real_type t69  = t68 * t66;
    real_type t71  = exp(-t68 * t19);
    real_type t73  = t6 * t6;
    real_type t74  = ModelPars[iM_CD2];
    real_type t75  = U__[iU_alpha];
    real_type t76  = t75 * t75;
    real_type t78  = ModelPars[iM_CD1];
    real_type t81  = t76 * t74 + t75 * t78 + ModelPars[iM_CD0];
    real_type t83  = ModelPars[iM_Aref];
    real_type t85  = 1.0 / ModelPars[iM_m];
    real_type t86  = t85 * t83;
    result__[ 17  ] = (2 * t63 * t61 + t86 * t81 * t73 * t71 * t69 / 2) * t3;
    real_type t91  = t71 * t66;
    real_type t92  = t91 * t3;
    result__[ 18  ] = -t86 * t81 * t6 * t92;
    result__[ 19  ] = -t22 * t60 * t7 * t3;
    result__[ 20  ] = (-t22 * t61 - t85 * t83 * t81 * t73 * t91 / 2) * t2 + U__[iU_c_V] * t11;
    result__[ 21  ] = -t86 * (2 * t75 * t74 + t78) * t73 * t92 / 2;
    result__[ 22  ] = result__[16];
    real_type t117 = t6 * t71 * t69;
    real_type t118 = ModelPars[iM_CL1];
    real_type t121 = t75 * t118 + ModelPars[iM_CL0];
    real_type t122 = t83 * t121;
    real_type t123 = X__[iX_sigma];
    real_type t124 = cos(t123);
    real_type t125 = t124 * t85;
    real_type t126 = t125 * t122;
    real_type t129 = t22 * t6;
    real_type t131 = 1.0 / t6;
    result__[ 23  ] = (-t126 * t117 / 2 + t7 * (2 * t131 * t63 * t60 - t129)) * t3;
    real_type t137 = t121 * t91;
    real_type t138 = t124 * t86;
    real_type t141 = t22 * t60;
    result__[ 24  ] = (t138 * t137 / 2 + t7 * (t29 + 1.0 / t73 * t141)) * t3;
    real_type t147 = t29 * t6;
    real_type t149 = -t131 * t141 + t147;
    result__[ 25  ] = -t5 * t149 * t3;
    real_type t152 = t121 * t6;
    real_type t153 = sin(t123);
    result__[ 26  ] = -t153 * t86 * t152 * t92 / 2;
    real_type t158 = t6 * t91;
    result__[ 27  ] = (t126 * t158 / 2 + t7 * t149) * t2 + U__[iU_c_G] * t11;
    result__[ 28  ] = t138 * t118 * t6 * t92 / 2;
    result__[ 29  ] = result__[22];
    real_type t170 = 1.0 / t7;
    real_type t171 = t170 * t153 * t85;
    real_type t175 = tan(t23);
    real_type t176 = t175 * t17;
    result__[ 30  ] = (-t171 * t122 * t117 / 2 + t176 * t129) * t3;
    real_type t179 = t7 * t29;
    real_type t180 = t175 * t175;
    result__[ 31  ] = -(1 + t180) * t16 * t179 * t14;
    real_type t186 = t170 * t153 * t86;
    result__[ 32  ] = (t186 * t137 / 2 - t175 * t16 * t179) * t3;
    real_type t192 = t152 * t91;
    real_type t193 = t7 * t7;
    result__[ 33  ] = (t5 / t193 * t153 * t86 * t192 / 2 + t175 * t38 * t147) * t3;
    result__[ 34  ] = t175 * t42 * t179 * t14;
    real_type t205 = t158 * t3;
    result__[ 35  ] = t170 * t125 * t122 * t205 / 2;
    result__[ 36  ] = (t186 * t192 / 2 - t176 * t147) * t2 + U__[iU_c_psi] * t11;
    result__[ 37  ] = t171 * t83 * t118 * t205 / 2;
    result__[ 38  ] = result__[29];
    real_type t219 = ModelPars[iM_sigma_dot_max];
    result__[ 39  ] = U__[iU_u2] * t219 * t2 + U__[iU_c_sigma] * t11;
    result__[ 40  ] = t219 * t3;
    result__[ 41  ] = result__[38];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxpu_sparse", 42, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::A_numRows() const { return 7; }
  integer HypersonicProblem3DOF::A_numCols() const { return 7; }
  integer HypersonicProblem3DOF::A_nnz()     const { return 7; }

  void
  HypersonicProblem3DOF::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
    iIndex[5 ] = 5   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  HypersonicProblem3DOF::A_sparse(
    NodeType const     & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = 1;
    result__[ 2   ] = 1;
    result__[ 3   ] = 1;
    result__[ 4   ] = 1;
    result__[ 5   ] = 1;
    result__[ 6   ] = 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 7, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::eta_numEqns() const { return 7; }

  void
  HypersonicProblem3DOF::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = L__[iL_lambda1__xo];
    result__[ 1   ] = L__[iL_lambda2__xo];
    result__[ 2   ] = L__[iL_lambda3__xo];
    result__[ 3   ] = L__[iL_lambda4__xo];
    result__[ 4   ] = L__[iL_lambda5__xo];
    result__[ 5   ] = L__[iL_lambda6__xo];
    result__[ 6   ] = L__[iL_lambda7__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DetaDxp_numRows() const { return 7; }
  integer HypersonicProblem3DOF::DetaDxp_numCols() const { return 8; }
  integer HypersonicProblem3DOF::DetaDxp_nnz()     const { return 0; }

  void
  HypersonicProblem3DOF::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HypersonicProblem3DOF::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer HypersonicProblem3DOF::nu_numEqns() const { return 7; }

  void
  HypersonicProblem3DOF::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = V__[0];
    result__[ 1   ] = V__[1];
    result__[ 2   ] = V__[2];
    result__[ 3   ] = V__[3];
    result__[ 4   ] = V__[4];
    result__[ 5   ] = V__[5];
    result__[ 6   ] = V__[6];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer HypersonicProblem3DOF::DnuDxp_numRows() const { return 7; }
  integer HypersonicProblem3DOF::DnuDxp_numCols() const { return 8; }
  integer HypersonicProblem3DOF::DnuDxp_nnz()     const { return 0; }

  void
  HypersonicProblem3DOF::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  HypersonicProblem3DOF::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: HypersonicProblem3DOF_Methods_ODE.cc
