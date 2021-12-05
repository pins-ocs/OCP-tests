/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_AdjointODE.cc                   |
 |                                                                       |
 |  version: 1.0   date 6/12/2021                                        |
 |                                                                       |
 |  Copyright (C) 2021                                                   |
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
#define ALIAS_v_Limit_DD(__t1) v_Limit.DD( __t1)
#define ALIAS_v_Limit_D(__t1) v_Limit.D( __t1)
#define ALIAS_s_Limit_DD(__t1) s_Limit.DD( __t1)
#define ALIAS_s_Limit_D(__t1) s_Limit.D( __t1)
#define ALIAS_p_Limit_DD(__t1) p_Limit.DD( __t1)
#define ALIAS_p_Limit_D(__t1) p_Limit.D( __t1)
#define ALIAS_x_Limit_DD(__t1) x_Limit.DD( __t1)
#define ALIAS_x_Limit_D(__t1) x_Limit.D( __t1)
#define ALIAS_uControl_D_3(__t1, __t2, __t3) uControl.D_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2(__t1, __t2, __t3) uControl.D_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1(__t1, __t2, __t3) uControl.D_1( __t1, __t2, __t3)
#define ALIAS_uControl_D_3_3(__t1, __t2, __t3) uControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_3(__t1, __t2, __t3) uControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_2_2(__t1, __t2, __t3) uControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_3(__t1, __t2, __t3) uControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_2(__t1, __t2, __t3) uControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_uControl_D_1_1(__t1, __t2, __t3) uControl.D_1_1( __t1, __t2, __t3)


namespace ICLOCS2_BatchFermentorDefine {

  /*\
   |  _   _
   | | | | |_  __
   | | |_| \ \/ /
   | |  _  |>  <
   | |_| |_/_/\_\
   |
  \*/

  integer
  ICLOCS2_BatchFermentor::Hx_numEqns() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::Hx_eval(
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
    real_type t1   = X__[iX_x];
    real_type t2   = ModelPars[iM_state_tol];
    real_type t4   = ALIAS_x_Limit_D(t1 + t2);
    real_type t5   = ModelPars[iM_WX];
    real_type t6   = ModelPars[iM_x_i];
    real_type t10  = 1.0 / ModelPars[iM_Tf] * Q__[iQ_zeta];
    real_type t17  = L__[iL_lambda1__xo];
    real_type t18  = X__[iX_s];
    real_type t19  = mu_D_2(t18, t1);
    real_type t20  = t1 * t19;
    real_type t21  = mu(t18, t1);
    real_type t22  = U__[iU_u];
    real_type t24  = 1.0 / ModelPars[iM_S_f];
    real_type t25  = t24 * t22;
    real_type t26  = X__[iX_v];
    real_type t28  = 1.0 / t26 * t25;
    real_type t31  = L__[iL_lambda2__xo];
    real_type t32  = rho(t18);
    real_type t34  = L__[iL_lambda3__xo];
    real_type t36  = 1.0 / ModelPars[iM_Yxs];
    real_type t40  = 1.0 / ModelPars[iM_Yes];
    real_type t42  = ModelPars[iM_mu_s];
    real_type t43  = t18 * t42;
    real_type t45  = ModelPars[iM_kappa_m] + t18;
    real_type t46  = 1.0 / t45;
    result__[ 0   ] = t4 + (2 * t1 - 2 * t6 - 2 * (ModelPars[iM_x_f] - t6) * t10) * t5 + (t20 + t21 - t28) * t17 + t32 * t31 + (-t36 * t20 - t36 * t21 - t40 * t32 - t46 * t43) * t34;
    real_type t50  = X__[iX_p];
    real_type t52  = ALIAS_p_Limit_D(t50 + t2);
    real_type t53  = ModelPars[iM_p_i];
    result__[ 1   ] = t52 + (2 * t50 - 2 * t53 - 2 * (ModelPars[iM_p_f] - t53) * t10) * t5 + (-ModelPars[iM_K_degr] - t28) * t31;
    real_type t64  = ALIAS_s_Limit_D(t18 + t2);
    real_type t65  = ModelPars[iM_s_i];
    real_type t72  = mu_D_1(t18, t1);
    real_type t75  = rho_D(t18);
    real_type t84  = t45 * t45;
    result__[ 2   ] = t64 + (2 * t18 - 2 * t65 - 2 * (ModelPars[iM_s_f] - t65) * t10) * t5 + t1 * t72 * t17 + t1 * t75 * t31 + (-t36 * t1 * t72 - t40 * t1 * t75 - t1 * t46 * t42 + t1 / t84 * t43 - t28) * t34;
    real_type t90  = ALIAS_v_Limit_D(t26);
    real_type t91  = ModelPars[iM_v_i];
    real_type t99  = t26 * t26;
    real_type t100 = 1.0 / t99;
    real_type t101 = t100 * t25;
    result__[ 3   ] = t90 + (2 * t26 - 2 * t91 - 2 * (ModelPars[iM_v_f] - t91) * t10) * t5 + t101 * t1 * t17 + t101 * t50 * t31 - (-t24 * t18 + 1) * t100 * t22 * t34;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DHxDx_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DHxDx_numCols() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DHxDx_nnz() const
  { return 12; }

  void
  ICLOCS2_BatchFermentor::DHxDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 3   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 3   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 1   ;
    iIndex[10] = 3   ; jIndex[10] = 2   ;
    iIndex[11] = 3   ; jIndex[11] = 3   ;
  }

  void
  ICLOCS2_BatchFermentor::DHxDx_sparse(
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
    real_type t1   = X__[iX_x];
    real_type t2   = ModelPars[iM_state_tol];
    real_type t4   = ALIAS_x_Limit_DD(t1 + t2);
    real_type t6   = 2 * ModelPars[iM_WX];
    real_type t7   = L__[iL_lambda1__xo];
    real_type t8   = X__[iX_s];
    real_type t9   = mu_D_2_2(t8, t1);
    real_type t10  = t1 * t9;
    real_type t11  = mu_D_2(t8, t1);
    real_type t15  = L__[iL_lambda3__xo];
    real_type t17  = 1.0 / ModelPars[iM_Yxs];
    result__[ 0   ] = t4 + t6 + (t10 + 2 * t11) * t7 + (-t17 * t10 - 2 * t17 * t11) * t15;
    real_type t23  = mu_D_1_2(t8, t1);
    real_type t24  = t1 * t23;
    real_type t25  = mu_D_1(t8, t1);
    real_type t28  = L__[iL_lambda2__xo];
    real_type t29  = rho_D(t8);
    real_type t30  = t29 * t28;
    real_type t34  = 1.0 / ModelPars[iM_Yes];
    real_type t36  = ModelPars[iM_mu_s];
    real_type t38  = ModelPars[iM_kappa_m] + t8;
    real_type t41  = t8 * t36;
    real_type t42  = t38 * t38;
    real_type t43  = 1.0 / t42;
    real_type t46  = (-t17 * t24 - t17 * t25 - t34 * t29 - 1.0 / t38 * t36 + t43 * t41) * t15;
    result__[ 1   ] = (t24 + t25) * t7 + t30 + t46;
    real_type t47  = U__[iU_u];
    real_type t50  = 1.0 / ModelPars[iM_S_f];
    real_type t51  = X__[iX_v];
    real_type t52  = t51 * t51;
    real_type t54  = 1.0 / t52 * t50;
    result__[ 2   ] = t54 * t47 * t7;
    real_type t55  = X__[iX_p];
    real_type t57  = ALIAS_p_Limit_DD(t55 + t2);
    result__[ 3   ] = t57 + t6;
    result__[ 4   ] = t54 * t47 * t28;
    result__[ 5   ] = t1 * t23 * t7 + t25 * t7 + t30 + t46;
    real_type t63  = ALIAS_s_Limit_DD(t8 + t2);
    real_type t64  = mu_D_1_1(t8, t1);
    real_type t67  = rho_DD(t8);
    result__[ 6   ] = t63 + t6 + t1 * t64 * t7 + t1 * t67 * t28 + (-t17 * t1 * t64 - t34 * t1 * t67 + 2 * t1 * t43 * t36 - 2 * t1 / t42 / t38 * t41) * t15;
    real_type t84  = t47 * t15;
    result__[ 7   ] = t54 * t84;
    result__[ 8   ] = result__[2];
    result__[ 9   ] = result__[4];
    result__[ 10  ] = result__[7];
    real_type t85  = ALIAS_v_Limit_DD(t51);
    real_type t89  = 1.0 / t52 / t51;
    real_type t90  = t89 * t50 * t47;
    result__[ 11  ] = t85 + t6 - 2 * t90 * t1 * t7 - 2 * t90 * t55 * t28 + 2 * (-t50 * t8 + 1) * t89 * t84;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDx_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DHxDp_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DHxDp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DHxDp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DHxDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DHxDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_   _
   | | |_| | | | |
   | |  _  | |_| |
   | |_| |_|\__,_|
   |
  \*/

  integer
  ICLOCS2_BatchFermentor::Hu_numEqns() const
  { return 1; }

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
    real_type t6   = 1.0 / ModelPars[iM_S_f];
    real_type t8   = 1.0 / X__[iX_v];
    real_type t9   = t8 * t6;
    result__[ 0   ] = ModelPars[iM_W] - t9 * L__[iL_lambda1__xo] * X__[iX_x] - t9 * L__[iL_lambda2__xo] * X__[iX_p] + (-t6 * X__[iX_s] + 1) * t8 * L__[iL_lambda3__xo] + t6 * L__[iL_lambda4__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DHuDx_numRows() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DHuDx_numCols() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DHuDx_nnz() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::DHuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DHuDx_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = L__[iL_lambda1__xo];
    real_type t3   = 1.0 / ModelPars[iM_S_f];
    real_type t5   = X__[iX_v];
    real_type t6   = 1.0 / t5;
    result__[ 0   ] = -t6 * t3 * t1;
    real_type t8   = L__[iL_lambda2__xo];
    result__[ 1   ] = -t6 * t3 * t8;
    real_type t11  = L__[iL_lambda3__xo];
    result__[ 2   ] = -t3 * t6 * t11;
    real_type t16  = t5 * t5;
    real_type t17  = 1.0 / t16;
    real_type t18  = t17 * t3;
    result__[ 3   ] = t18 * X__[iX_x] * t1 + t18 * X__[iX_p] * t8 - (-t3 * X__[iX_s] + 1) * t17 * t11;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDx_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DHuDp_numRows() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::DHuDp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DHuDp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DHuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DHuDp_sparse(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |  _   _
   | | | | |_ __
   | | |_| | '_ \
   | |  _  | |_) |
   | |_| |_| .__/
   |       |_|
  \*/

  integer
  ICLOCS2_BatchFermentor::Hp_numEqns() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DHpDp_numRows() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DHpDp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DHpDp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DHpDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DHpDp_sparse(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/
  integer
  ICLOCS2_BatchFermentor::eta_numEqns() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DetaDx_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DetaDx_numCols() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DetaDx_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DetaDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DetaDx_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DetaDp_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DetaDp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DetaDp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DetaDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DetaDp_sparse(
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

  integer
  ICLOCS2_BatchFermentor::nu_numEqns() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DnuDx_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DnuDx_numCols() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DnuDx_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DnuDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DnuDx_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::DnuDp_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::DnuDp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::DnuDp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::DnuDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::DnuDp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_AdjointODE.cc
