/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 17/6/2022                                        |
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


#include "ICLOCS2_BatchFermentor.hh"
#include "ICLOCS2_BatchFermentor_Pars.hh"

using namespace std;
using namespace MechatronixLoad;

// user class in namespaces
using Mechatronix::PenaltyBarrier1DGreaterThan;
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
#endif

// map user defined functions and objects with macros
#define ALIAS_penalization_DD(__t1) Pen1D.evaluate_DD( __t1)
#define ALIAS_penalization_D(__t1) Pen1D.evaluate_D( __t1)
#define ALIAS_penalization(__t1) Pen1D.evaluate( __t1)


namespace ICLOCS2_BatchFermentorDefine {

  /*\
   |   _   _
   |  | | | |_  __ _ __
   |  | |_| \ \/ /| '_ \
   |  |  _  |>  < | |_) |
   |  |_| |_/_/\_\| .__/
   |              |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::Hxp_numEqns() const { return 4; }

  void
  ICLOCS2_BatchFermentor::Hxp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WP];
    real_type t2   = X__[iX_x];
    real_type t7   = L__[iL_lambda1__xo];
    real_type t8   = X__[iX_s];
    real_type t9   = mu_D_2(t8, t2);
    real_type t10  = t2 * t9;
    real_type t11  = mu(t8, t2);
    real_type t13  = U(U__[iU_w]);
    real_type t14  = X__[iX_v];
    real_type t16  = 1.0 / t14 * t13;
    real_type t19  = L__[iL_lambda2__xo];
    real_type t20  = rho(t8);
    real_type t22  = L__[iL_lambda3__xo];
    real_type t24  = 1.0 / ModelPars[iM_Yxs];
    real_type t28  = 1.0 / ModelPars[iM_Yes];
    real_type t30  = ModelPars[iM_mu_s];
    real_type t31  = t8 * t30;
    real_type t33  = ModelPars[iM_kappa_m] + t8;
    real_type t34  = 1.0 / t33;
    result__[ 0   ] = 2 * (t2 - U__[iU_c_x]) * t1 + (t10 + t11 - t16) * t7 + t20 * t19 + (-t24 * t10 - t24 * t11 - t28 * t20 - t34 * t31) * t22;
    real_type t38  = X__[iX_p];
    result__[ 1   ] = 2 * (t38 - U__[iU_c_p]) * t1 + (-ModelPars[iM_K_degr] - t16) * t19;
    real_type t50  = mu_D_1(t8, t2);
    real_type t53  = rho_D(t8);
    real_type t62  = t33 * t33;
    result__[ 2   ] = 2 * (t8 - U__[iU_c_s]) * t1 + t2 * t50 * t7 + t2 * t53 * t19 + (-t24 * t2 * t50 - t28 * t2 * t53 - t2 * t34 * t30 + t2 / t62 * t31 - t16) * t22;
    real_type t73  = 1.0 / ModelPars[iM_v_max];
    real_type t75  = ALIAS_penalization_D(t73 * t14);
    real_type t78  = t14 * t14;
    real_type t79  = 1.0 / t78;
    real_type t80  = t79 * t13;
    result__[ 3   ] = 2 * (t14 - U__[iU_c_v]) * t1 + t73 * t75 + t80 * t2 * t7 + t80 * t38 * t19 - (ModelPars[iM_S_f] - t8) * t79 * t13 * t22;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 4, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::DHxpDxpu_numRows() const { return 4; }
  integer ICLOCS2_BatchFermentor::DHxpDxpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::DHxpDxpu_nnz()     const { return 20; }

  void
  ICLOCS2_BatchFermentor::DHxpDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 0   ; jIndex[4 ] = 8   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 0   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 2   ; jIndex[12] = 6   ;
    iIndex[13] = 2   ; jIndex[13] = 8   ;
    iIndex[14] = 3   ; jIndex[14] = 0   ;
    iIndex[15] = 3   ; jIndex[15] = 1   ;
    iIndex[16] = 3   ; jIndex[16] = 2   ;
    iIndex[17] = 3   ; jIndex[17] = 3   ;
    iIndex[18] = 3   ; jIndex[18] = 7   ;
    iIndex[19] = 3   ; jIndex[19] = 8   ;
  }


  void
  ICLOCS2_BatchFermentor::DHxpDxpu_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 2 * ModelPars[iM_WP];
    real_type t3   = L__[iL_lambda1__xo];
    real_type t4   = X__[iX_s];
    real_type t5   = X__[iX_x];
    real_type t6   = mu_D_2_2(t4, t5);
    real_type t7   = t5 * t6;
    real_type t8   = mu_D_2(t4, t5);
    real_type t12  = L__[iL_lambda3__xo];
    real_type t14  = 1.0 / ModelPars[iM_Yxs];
    result__[ 0   ] = t2 + (t7 + 2 * t8) * t3 + (-t14 * t7 - 2 * t14 * t8) * t12;
    real_type t20  = mu_D_1_2(t4, t5);
    real_type t21  = t5 * t20;
    real_type t22  = mu_D_1(t4, t5);
    real_type t25  = L__[iL_lambda2__xo];
    real_type t26  = rho_D(t4);
    real_type t27  = t26 * t25;
    real_type t31  = 1.0 / ModelPars[iM_Yes];
    real_type t33  = ModelPars[iM_mu_s];
    real_type t35  = ModelPars[iM_kappa_m] + t4;
    real_type t38  = t4 * t33;
    real_type t39  = t35 * t35;
    real_type t40  = 1.0 / t39;
    real_type t43  = (-t14 * t21 - t14 * t22 - t31 * t26 - 1.0 / t35 * t33 + t40 * t38) * t12;
    result__[ 1   ] = (t21 + t22) * t3 + t27 + t43;
    real_type t44  = U__[iU_w];
    real_type t45  = U(t44);
    real_type t47  = X__[iX_v];
    real_type t48  = t47 * t47;
    real_type t49  = 1.0 / t48;
    result__[ 2   ] = t49 * t45 * t3;
    result__[ 3   ] = -t2;
    real_type t50  = U_D(t44);
    real_type t52  = 1.0 / t47;
    result__[ 4   ] = -t52 * t50 * t3;
    result__[ 5   ] = t2;
    result__[ 6   ] = t49 * t45 * t25;
    result__[ 7   ] = result__[3];
    result__[ 8   ] = -t52 * t50 * t25;
    result__[ 9   ] = t5 * t20 * t3 + t22 * t3 + t27 + t43;
    real_type t60  = mu_D_1_1(t4, t5);
    real_type t63  = rho_DD(t4);
    result__[ 10  ] = result__[5] + t5 * t60 * t3 + t5 * t63 * t25 + (-t14 * t5 * t60 - t31 * t5 * t63 + 2 * t5 * t40 * t33 - 2 * t5 / t39 / t35 * t38) * t12;
    real_type t80  = t45 * t12;
    result__[ 11  ] = t49 * t80;
    result__[ 12  ] = result__[7];
    real_type t81  = t50 * t12;
    result__[ 13  ] = -t52 * t81;
    result__[ 14  ] = result__[2];
    result__[ 15  ] = result__[6];
    result__[ 16  ] = result__[11];
    real_type t83  = ModelPars[iM_v_max];
    real_type t86  = ALIAS_penalization_DD(1.0 / t83 * t47);
    real_type t87  = t83 * t83;
    real_type t90  = t5 * t3;
    real_type t92  = 1.0 / t48 / t47;
    real_type t93  = t92 * t45;
    real_type t97  = X__[iX_p] * t25;
    real_type t101 = ModelPars[iM_S_f] - t4;
    result__[ 17  ] = result__[5] + 1.0 / t87 * t86 - 2 * t93 * t90 - 2 * t93 * t97 + 2 * t101 * t92 * t80;
    result__[ 18  ] = result__[12];
    real_type t105 = t49 * t50;
    result__[ 19  ] = -t101 * t49 * t81 + t105 * t90 + t105 * t97;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpu_sparse", 20, i_segment );
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::Hu_numEqns() const { return 5; }

  void
  ICLOCS2_BatchFermentor::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = ModelPars[iM_WP];
    real_type t2   = X__[iX_x];
    real_type t3   = U__[iU_c_x];
    real_type t8   = 1.0 / ModelPars[iM_x_max];
    real_type t9   = t8 * t3;
    real_type t10  = ALIAS_penalization_D(t9);
    real_type t13  = ALIAS_penalization_D(1 - t9);
    result__[ 0   ] = -2 * (t2 - t3) * t1 + t8 * t10 - t8 * t13;
    real_type t15  = X__[iX_p];
    real_type t16  = U__[iU_c_p];
    real_type t21  = 1.0 / ModelPars[iM_p_max];
    real_type t22  = t21 * t16;
    real_type t23  = ALIAS_penalization_D(t22);
    real_type t26  = ALIAS_penalization_D(1 - t22);
    result__[ 1   ] = -2 * (t15 - t16) * t1 + t21 * t23 - t21 * t26;
    real_type t28  = X__[iX_s];
    real_type t29  = U__[iU_c_s];
    real_type t34  = 1.0 / ModelPars[iM_s_max];
    real_type t35  = t34 * t29;
    real_type t36  = ALIAS_penalization_D(t35);
    real_type t39  = ALIAS_penalization_D(1 - t35);
    result__[ 2   ] = -2 * (t28 - t29) * t1 + t34 * t36 - t34 * t39;
    real_type t41  = X__[iX_v];
    real_type t42  = U__[iU_c_v];
    real_type t47  = 1.0 / ModelPars[iM_v_max];
    real_type t48  = t47 * t42;
    real_type t49  = ALIAS_penalization_D(t48);
    real_type t52  = ALIAS_penalization_D(1 - t48);
    result__[ 3   ] = -2 * (t41 - t42) * t1 + t47 * t49 - t47 * t52;
    real_type t55  = U__[iU_w];
    real_type t58  = ModelPars[iM_epsilon];
    real_type t61  = t55 * t55;
    real_type t62  = t58 * t58;
    real_type t70  = U_D(t55);
    real_type t71  = 1.0 / t41;
    real_type t72  = t71 * t70;
    result__[ 4   ] = 2 * t55 * ModelPars[iM_W] + 1.0 / (1 + 1.0 / t62 * t61) * t55 / t58 - t72 * t2 * L__[iL_lambda1__xo] - t72 * t15 * L__[iL_lambda2__xo] + (ModelPars[iM_S_f] - t28) * t71 * t70 * L__[iL_lambda3__xo] + t70 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 5, i_segment );
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_AdjointODE.cc
