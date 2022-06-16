/*-----------------------------------------------------------------------*\
 |  file: ICLOCS2_BatchFermentor_Methods_ODE.cc                          |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer ICLOCS2_BatchFermentor::rhs_ode_numEqns() const { return 4; }

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
    real_type t6   = U(U__[iU_w]);
    real_type t9   = 1.0 / X__[iX_v];
    result__[ 0   ] = -t9 * t6 * t2 + t4;
    real_type t11  = rho(t1);
    real_type t12  = t2 * t11;
    real_type t14  = X__[iX_p];
    result__[ 1   ] = -t9 * t6 * t14 - t14 * ModelPars[iM_K_degr] + t12;
    result__[ 2   ] = -1.0 / ModelPars[iM_Yxs] * t4 - 1.0 / ModelPars[iM_Yes] * t12 - t2 / (ModelPars[iM_kappa_m] + t1) * t1 * ModelPars[iM_mu_s] + (ModelPars[iM_S_f] - t1) * t9 * t6;
    result__[ 3   ] = t6;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "rhs_ode", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::Drhs_odeDxpu_numRows() const { return 4; }
  integer ICLOCS2_BatchFermentor::Drhs_odeDxpu_numCols() const { return 9; }
  integer ICLOCS2_BatchFermentor::Drhs_odeDxpu_nnz()     const { return 14; }

  void
  ICLOCS2_BatchFermentor::Drhs_odeDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 8   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 0   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
    iIndex[12] = 2   ; jIndex[12] = 8   ;
    iIndex[13] = 3   ; jIndex[13] = 8   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  ICLOCS2_BatchFermentor::Drhs_odeDxpu_sparse(
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
    real_type t6   = U__[iU_w];
    real_type t7   = U(t6);
    real_type t8   = X__[iX_v];
    real_type t9   = 1.0 / t8;
    real_type t10  = t9 * t7;
    result__[ 0   ] = t4 + t5 - t10;
    real_type t11  = mu_D_1(t1, t2);
    result__[ 1   ] = t2 * t11;
    real_type t13  = t8 * t8;
    real_type t14  = 1.0 / t13;
    result__[ 2   ] = t14 * t7 * t2;
    real_type t15  = U_D(t6);
    result__[ 3   ] = -t9 * t15 * t2;
    result__[ 4   ] = rho(t1);
    result__[ 5   ] = -ModelPars[iM_K_degr] - t10;
    real_type t19  = rho_D(t1);
    result__[ 6   ] = t2 * t19;
    real_type t20  = X__[iX_p];
    result__[ 7   ] = t14 * t7 * t20;
    result__[ 8   ] = -t9 * t15 * t20;
    real_type t25  = 1.0 / ModelPars[iM_Yxs];
    real_type t29  = 1.0 / ModelPars[iM_Yes];
    real_type t31  = ModelPars[iM_mu_s];
    real_type t32  = t1 * t31;
    real_type t34  = ModelPars[iM_kappa_m] + t1;
    real_type t35  = 1.0 / t34;
    result__[ 9   ] = -t25 * t4 - t25 * t5 - t29 * result__[4] - t35 * t32;
    real_type t43  = t34 * t34;
    result__[ 10  ] = -t25 * t2 * t11 - t29 * t2 * t19 - t2 * t35 * t31 + t2 / t43 * t32 - t10;
    real_type t49  = ModelPars[iM_S_f] - t1;
    result__[ 11  ] = -t49 * t14 * t7;
    result__[ 12  ] = t49 * t9 * t15;
    result__[ 13  ] = t15;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Drhs_odeDxpu_sparse", 14, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer ICLOCS2_BatchFermentor::A_numRows() const { return 4; }
  integer ICLOCS2_BatchFermentor::A_numCols() const { return 4; }
  integer ICLOCS2_BatchFermentor::A_nnz()     const { return 4; }

  void
  ICLOCS2_BatchFermentor::A_pattern( integer iIndex[], integer jIndex[] ) const {
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

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer ICLOCS2_BatchFermentor::eta_numEqns() const { return 4; }

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
  integer ICLOCS2_BatchFermentor::DetaDxp_numRows() const { return 4; }
  integer ICLOCS2_BatchFermentor::DetaDxp_numCols() const { return 4; }
  integer ICLOCS2_BatchFermentor::DetaDxp_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::DetaDxp_sparse(
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

  integer ICLOCS2_BatchFermentor::nu_numEqns() const { return 4; }

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
  integer ICLOCS2_BatchFermentor::DnuDxp_numRows() const { return 4; }
  integer ICLOCS2_BatchFermentor::DnuDxp_numCols() const { return 4; }
  integer ICLOCS2_BatchFermentor::DnuDxp_nnz()     const { return 0; }

  void
  ICLOCS2_BatchFermentor::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  ICLOCS2_BatchFermentor::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: ICLOCS2_BatchFermentor_Methods_ODE.cc
