/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_ODE.cc                          |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer
  ICLOCS2_BatchFermentor::rhs_ode_numEqns() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::rhs_ode_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_s];
    real_type t2   = X__[iX_x];
    real_type t3   = mu(t1, t2);
    real_type t4   = t2 * t3;
    real_type t5   = U__[iU_u];
    real_type t8   = 1.0 / ModelPars[iM_S_f];
    real_type t10  = 1.0 / X__[iX_v];
    real_type t11  = t10 * t8;
    result__[ 0   ] = -t11 * t5 * t2 + t4;
    real_type t13  = rho(t1);
    real_type t14  = t2 * t13;
    real_type t16  = X__[iX_p];
    result__[ 1   ] = -t11 * t5 * t16 - t16 * ModelPars[iM_K_degr] + t14;
    result__[ 2   ] = -1.0 / ModelPars[iM_Yxs] * t4 - 1.0 / ModelPars[iM_Yes] * t14 - t2 / (ModelPars[iM_kappa_m] + t1) * t1 * ModelPars[iM_mu_s] + (-t8 * t1 + 1) * t10 * t5;
    result__[ 3   ] = t8 * t5;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDx_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDx_numCols() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDx_nnz() const
  { return 10; }

  void
  ICLOCS2_BatchFermentor::Drhs_odeDx_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::Drhs_odeDx_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_s];
    real_type t2   = X__[iX_x];
    real_type t3   = mu_D_2(t1, t2);
    real_type t4   = t2 * t3;
    real_type t5   = mu(t1, t2);
    real_type t6   = U__[iU_u];
    real_type t8   = 1.0 / ModelPars[iM_S_f];
    real_type t10  = X__[iX_v];
    real_type t12  = 1.0 / t10 * t8 * t6;
    result__[ 0   ] = t4 + t5 - t12;
    real_type t13  = mu_D_1(t1, t2);
    result__[ 1   ] = t2 * t13;
    real_type t15  = t10 * t10;
    real_type t16  = 1.0 / t15;
    real_type t17  = t16 * t8;
    result__[ 2   ] = t17 * t6 * t2;
    result__[ 3   ] = rho(t1);
    result__[ 4   ] = -ModelPars[iM_K_degr] - t12;
    real_type t19  = rho_D(t1);
    result__[ 5   ] = t2 * t19;
    result__[ 6   ] = t17 * t6 * X__[iX_p];
    real_type t23  = 1.0 / ModelPars[iM_Yxs];
    real_type t27  = 1.0 / ModelPars[iM_Yes];
    real_type t29  = ModelPars[iM_mu_s];
    real_type t30  = t1 * t29;
    real_type t32  = ModelPars[iM_kappa_m] + t1;
    real_type t33  = 1.0 / t32;
    result__[ 7   ] = -t23 * t4 - t23 * t5 - t27 * result__[3] - t33 * t30;
    real_type t41  = t32 * t32;
    result__[ 8   ] = -t23 * t2 * t13 - t27 * t2 * t19 - t2 * t33 * t29 + t2 / t41 * t30 - t12;
    result__[ 9   ] = -(-t8 * t1 + 1) * t16 * t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxp_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDp_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDp_numCols() const
  { return 0; }

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDp_nnz() const
  { return 0; }

  void
  ICLOCS2_BatchFermentor::Drhs_odeDp_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::Drhs_odeDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDu_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDu_numCols() const
  { return 1; }

  integer
  ICLOCS2_BatchFermentor::Drhs_odeDu_nnz() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::Drhs_odeDu_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::Drhs_odeDu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t3   = 1.0 / ModelPars[iM_S_f];
    real_type t6   = 1.0 / X__[iX_v];
    result__[ 0   ] = -t6 * t3 * X__[iX_x];
    result__[ 1   ] = -t6 * t3 * X__[iX_p];
    result__[ 2   ] = (-t3 * X__[iX_s] + 1) * t6;
    result__[ 3   ] = t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDu_sparse", 4, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  integer
  ICLOCS2_BatchFermentor::A_numRows() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::A_numCols() const
  { return 4; }

  integer
  ICLOCS2_BatchFermentor::A_nnz() const
  { return 4; }

  void
  ICLOCS2_BatchFermentor::A_pattern(
    integer iIndex[],
    integer jIndex[]
  ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::A_sparse(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 4, i_segment );
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_ODE.cc
