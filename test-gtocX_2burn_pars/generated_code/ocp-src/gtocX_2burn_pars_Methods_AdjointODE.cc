/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_pars_Methods_AdjointODE.cc                         |
 |                                                                       |
 |  version: 1.0   date 19/3/2022                                        |
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


#include "gtocX_2burn_pars.hh"
#include "gtocX_2burn_pars_Pars.hh"

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
#define ALIAS_ray_positive_DD(__t1) ray_positive.DD( __t1)
#define ALIAS_ray_positive_D(__t1) ray_positive.D( __t1)


namespace gtocX_2burn_parsDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::JPx_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::JPx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::LTx_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t9   = ALIAS_ray_positive_D(-t3 * t1 - t6 * t5 - 1);
    result__[ 0   ] = -t3 * t9;
    result__[ 1   ] = -t6 * t9;
    result__[ 2   ] = (t6 * t1 - t3 * t5) * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::JUx_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::JPp_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPp_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::LTp_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTp_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::JUp_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUp_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::JPu_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::LTu_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::JUu_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::LTargs_numEqns() const { return 1; }

  void
  gtocX_2burn_pars::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t6   = sin(t2);
    result__[ 0   ] = -t3 * X__[iX_f] - t6 * X__[iX_g] - 1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DJPxDxp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DJPxDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DJPxDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DLTxDxp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DLTxDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DLTxDxp_nnz()     const { return 9; }

  void
  gtocX_2burn_pars::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 2   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 1   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
  }


  void
  gtocX_2burn_pars::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t4   = t3 * t1;
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t7   = t6 * t5;
    real_type t8   = -1 - t4 - t7;
    real_type t9   = ALIAS_ray_positive_DD(t8);
    real_type t10  = t3 * t3;
    result__[ 0   ] = t10 * t9;
    result__[ 1   ] = t3 * t6 * t9;
    real_type t14  = t6 * t1 - t3 * t5;
    real_type t15  = t14 * t9;
    real_type t17  = ALIAS_ray_positive_D(t8);
    result__[ 2   ] = -t3 * t15 + t6 * t17;
    result__[ 3   ] = result__[1];
    real_type t19  = t6 * t6;
    result__[ 4   ] = t19 * t9;
    result__[ 5   ] = -t6 * t15 - t3 * t17;
    result__[ 6   ] = result__[2];
    result__[ 7   ] = result__[5];
    real_type t22  = t14 * t14;
    result__[ 8   ] = t22 * t9 + (t4 + t7) * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DJUxDxp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DJUxDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DJUxDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DJPuDxp_numRows() const { return 0; }
  integer gtocX_2burn_pars::DJPuDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DJPuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DLTuDxp_numRows() const { return 0; }
  integer gtocX_2burn_pars::DLTuDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DLTuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DJUuDxp_numRows() const { return 0; }
  integer gtocX_2burn_pars::DJUuDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DJUuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DJPpDp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DJPpDp_numCols() const { return 3; }
  integer gtocX_2burn_pars::DJPpDp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DLTpDp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DLTpDp_numCols() const { return 3; }
  integer gtocX_2burn_pars::DLTpDp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DJUpDp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DJUpDp_numCols() const { return 3; }
  integer gtocX_2burn_pars::DJUpDp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DLTargsDxup_numRows() const { return 1; }
  integer gtocX_2burn_pars::DLTargsDxup_numCols() const { return 6; }
  integer gtocX_2burn_pars::DLTargsDxup_nnz()     const { return 3; }

  void
  gtocX_2burn_pars::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }


  void
  gtocX_2burn_pars::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_L];
    real_type t2   = cos(t1);
    result__[ 0   ] = -t2;
    real_type t3   = sin(t1);
    result__[ 1   ] = -t3;
    result__[ 2   ] = -t2 * X__[iX_g] + t3 * X__[iX_f];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 3, i_segment );
  }

  /*\
   |   _   _        _   _
   |  | | | |_  __ | | | |_ __
   |  | |_| \ \/ / | |_| | '_ \
   |  |  _  |>  <  |  _  | |_) |
   |  |_| |_/_/\_\ |_| |_| .__/
   |                     |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::Hx_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::Hx_eval(
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
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t3   = X__[iX_f];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = f_guess(t10);
    real_type t15  = L__[iL_lambda1__xo];
    real_type t16  = t8 - t6;
    real_type t18  = P__[iP_p];
    real_type t19  = sqrt(t18);
    real_type t20  = ModelPars[iM_muS];
    real_type t21  = sqrt(t20);
    real_type t22  = 1.0 / t21;
    real_type t23  = t22 * t19;
    real_type t24  = t23 * t16 * t15;
    real_type t25  = ModelPars[iM_w_nonlin];
    real_type t26  = X__[iX_g];
    real_type t27  = X__[iX_L];
    real_type t28  = ray(t18, t3, t26, t27);
    real_type t29  = acceleration_r_D_1(t28, t20);
    real_type t30  = t29 * t25;
    real_type t31  = ray_D_2(t18, t3, t26, t27);
    real_type t32  = sin(t27);
    real_type t36  = L__[iL_lambda2__xo];
    real_type t38  = t23 * t16 * t36;
    real_type t39  = cos(t27);
    real_type t48  = (t32 * t26 + t39 * t3 + 1) * t16 * L__[iL_lambda3__xo];
    real_type t51  = t21 / t19 / t18;
    result__[ 0   ] = (2 * t3 - 2 * t11) * t2 + t32 * t31 * t30 * t24 - t39 * t31 * t30 * t38 + 2 * t39 * t51 * t48;
    real_type t55  = g_guess(t10);
    real_type t59  = ray_D_3(t18, t3, t26, t27);
    result__[ 1   ] = (2 * t26 - 2 * t55) * t2 + t32 * t59 * t30 * t24 - t39 * t59 * t30 * t38 + 2 * t32 * t51 * t48;
    real_type t69  = L_guess(t10, t6);
    real_type t74  = t22 * t19 * t16;
    real_type t75  = ray_D_4(t18, t3, t26, t27);
    real_type t79  = acceleration_r(t28, t20);
    real_type t80  = t79 * t25;
    result__[ 2   ] = (2 * t27 - 2 * t69) * t2 + (t32 * t75 * t30 * t74 + t39 * t80 * t74) * t15 + (-t39 * t75 * t30 * t74 + t32 * t80 * t74) * t36 + 2 * (t39 * t26 - t32 * t3) * t51 * t48;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::Hp_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::Hp_eval(
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
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t3   = P__[iP_p];
    real_type t4   = p_guess(0);
    real_type t5   = 1.0 / t4;
    real_type t14  = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t15  = sqrt(t3);
    real_type t18  = ModelPars[iM_muS];
    real_type t19  = sqrt(t18);
    real_type t20  = 1.0 / t19;
    real_type t21  = t20 / t15 * t14;
    real_type t22  = ModelPars[iM_w_nonlin];
    real_type t23  = X__[iX_f];
    real_type t24  = X__[iX_g];
    real_type t25  = X__[iX_L];
    real_type t26  = ray(t3, t23, t24, t25);
    real_type t27  = acceleration_r(t26, t18);
    real_type t28  = t27 * t22;
    real_type t29  = sin(t25);
    real_type t34  = t20 * t15 * t14;
    real_type t35  = acceleration_r_D_1(t26, t18);
    real_type t36  = t35 * t22;
    real_type t37  = ray_D_1(t3, t23, t24, t25);
    real_type t44  = cos(t25);
    real_type t58  = pow(t44 * t23 + t29 * t24 + 1, 2);
    real_type t59  = t3 * t3;
    result__[ 0   ] = 2 * t5 * (t5 * t3 - 1) * t2 + (t29 * t28 * t21 / 2 + t29 * t37 * t36 * t34) * L__[iL_lambda1__xo] + (-t44 * t28 * t21 / 2 - t44 * t37 * t36 * t34) * L__[iL_lambda2__xo] - 3.0 / 2.0 * t19 / t15 / t59 * t58 * t14 * L__[iL_lambda3__xo];
    real_type t67  = h_guess(0);
    result__[ 1   ] = (2 * P__[iP_h] - 2 * t67) * t2;
    real_type t71  = k_guess(0);
    result__[ 2   ] = (2 * P__[iP_k] - 2 * t71) * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hp_eval", 3, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DHxDxp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DHxDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DHxDxp_nnz()     const { return 12; }

  void
  gtocX_2burn_pars::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 3   ;
  }


  void
  gtocX_2burn_pars::DHxDxp_sparse(
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
    real_type t2   = 2 * ModelPars[iM_w_guess];
    real_type t3   = L__[iL_lambda1__xo];
    real_type t6   = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t7   = t6 * t3;
    real_type t8   = P__[iP_p];
    real_type t9   = sqrt(t8);
    real_type t10  = ModelPars[iM_muS];
    real_type t11  = sqrt(t10);
    real_type t12  = 1.0 / t11;
    real_type t13  = t12 * t9;
    real_type t14  = t13 * t7;
    real_type t15  = ModelPars[iM_w_nonlin];
    real_type t16  = X__[iX_f];
    real_type t17  = X__[iX_g];
    real_type t18  = X__[iX_L];
    real_type t19  = ray(t8, t16, t17, t18);
    real_type t20  = acceleration_r_D_1_1(t19, t10);
    real_type t21  = t20 * t15;
    real_type t22  = ray_D_2(t8, t16, t17, t18);
    real_type t23  = t22 * t22;
    real_type t24  = sin(t18);
    real_type t28  = acceleration_r_D_1(t19, t10);
    real_type t29  = t28 * t15;
    real_type t30  = ray_D_2_2(t8, t16, t17, t18);
    real_type t34  = L__[iL_lambda2__xo];
    real_type t35  = t6 * t34;
    real_type t36  = t13 * t35;
    real_type t37  = cos(t18);
    real_type t45  = t6 * L__[iL_lambda3__xo];
    real_type t46  = t37 * t37;
    real_type t48  = 1.0 / t9 / t8;
    result__[ 0   ] = 2 * t11 * t48 * t46 * t45 + t24 * t23 * t21 * t14 + t24 * t30 * t29 * t14 - t37 * t23 * t21 * t36 - t37 * t30 * t29 * t36 - t2 + 2;
    real_type t53  = ray_D_3(t8, t16, t17, t18);
    real_type t54  = t22 * t53;
    real_type t58  = ray_D_2_3(t8, t16, t17, t18);
    real_type t69  = t11 * t48;
    real_type t70  = t37 * t69;
    result__[ 1   ] = t24 * t54 * t21 * t14 + t24 * t58 * t29 * t14 - t37 * t54 * t21 * t36 - t37 * t58 * t29 * t36 + 2 * t70 * t24 * t45;
    real_type t73  = ray_D_4(t8, t16, t17, t18);
    real_type t74  = t22 * t73;
    real_type t78  = ray_D_2_4(t8, t16, t17, t18);
    real_type t80  = t24 * t78 * t29;
    real_type t83  = t37 * t22 * t29;
    real_type t89  = t37 * t78 * t29;
    real_type t92  = t24 * t22 * t29;
    real_type t96  = -t24 * t16 + t37 * t17;
    real_type t97  = t96 * t45;
    real_type t99  = 2 * t70 * t97;
    real_type t100 = t37 * t16;
    real_type t101 = t24 * t17;
    real_type t103 = (1 + t100 + t101) * t45;
    real_type t104 = t24 * t69;
    real_type t106 = 2 * t104 * t103;
    result__[ 2   ] = t24 * t74 * t21 * t14 - t37 * t74 * t21 * t36 + t80 * t14 + t83 * t14 - t89 * t36 + t92 * t36 - t106 + t99;
    real_type t107 = 1.0 / t9;
    real_type t108 = t12 * t107;
    real_type t109 = t108 * t7;
    real_type t112 = ray_D_1(t8, t16, t17, t18);
    real_type t113 = t22 * t112;
    real_type t117 = ray_D_1_2(t8, t16, t17, t18);
    real_type t121 = t108 * t35;
    real_type t130 = t8 * t8;
    real_type t133 = t11 / t9 / t130;
    result__[ 3   ] = t92 * t109 / 2 + t24 * t113 * t21 * t14 + t24 * t117 * t29 * t14 - t83 * t121 / 2 - t37 * t113 * t21 * t36 - t37 * t117 * t29 * t36 - 3 * t37 * t133 * t103;
    result__[ 4   ] = result__[1];
    real_type t137 = t53 * t53;
    real_type t141 = ray_D_3_3(t8, t16, t17, t18);
    real_type t151 = t24 * t24;
    result__[ 5   ] = 2 * t11 * t48 * t151 * t45 + t24 * t137 * t21 * t14 - t37 * t137 * t21 * t36 + t24 * t141 * t29 * t14 - t37 * t141 * t29 * t36 - t2 + 2;
    real_type t156 = t53 * t73;
    real_type t160 = ray_D_3_4(t8, t16, t17, t18);
    real_type t162 = t24 * t160 * t29;
    real_type t165 = t37 * t53 * t29;
    real_type t171 = t37 * t160 * t29;
    real_type t174 = t24 * t53 * t29;
    real_type t177 = 2 * t104 * t97;
    real_type t179 = 2 * t70 * t103;
    result__[ 6   ] = t24 * t156 * t21 * t14 - t37 * t156 * t21 * t36 + t162 * t14 + t165 * t14 - t171 * t36 + t174 * t36 + t177 + t179;
    real_type t182 = t53 * t112;
    real_type t186 = ray_D_1_3(t8, t16, t17, t18);
    result__[ 7   ] = t174 * t109 / 2 + t24 * t182 * t21 * t14 + t24 * t186 * t29 * t14 - t165 * t121 / 2 - t37 * t182 * t21 * t36 - t37 * t186 * t29 * t36 - 3 * t24 * t133 * t103;
    real_type t201 = t9 * t6;
    real_type t203 = t15 * t12 * t201;
    real_type t204 = t22 * t20;
    real_type t205 = t24 * t73;
    real_type t208 = t12 * t201;
    real_type t213 = t37 * t73;
    result__[ 8   ] = (t205 * t204 * t203 + t80 * t208 + t83 * t208) * t3 + (-t213 * t204 * t203 - t89 * t208 + t92 * t208) * t34 + t99 - t106;
    real_type t220 = t53 * t20;
    result__[ 9   ] = (t205 * t220 * t203 + t162 * t208 + t165 * t208) * t3 + (-t213 * t220 * t203 - t171 * t208 + t174 * t208) * t34 + t177 + t179;
    real_type t233 = t73 * t73;
    real_type t237 = ray_D_4_4(t8, t16, t17, t18);
    real_type t241 = t213 * t29;
    real_type t244 = acceleration_r(t19, t10);
    real_type t245 = t244 * t15;
    real_type t246 = t24 * t245;
    real_type t256 = t205 * t29;
    real_type t259 = t37 * t245;
    real_type t263 = t96 * t96;
    result__[ 10  ] = 2 - t2 + (t24 * t233 * t21 * t208 + t24 * t237 * t29 * t208 + 2 * t241 * t208 - t246 * t208) * t3 + (-t37 * t233 * t21 * t208 - t37 * t237 * t29 * t208 + 2 * t256 * t208 + t259 * t208) * t34 + 2 * t11 * t48 * t263 * t45 + 2 * (-t100 - t101) * t69 * t103;
    real_type t273 = t12 * t107 * t6;
    real_type t276 = t112 * t20;
    real_type t279 = ray_D_1_4(t8, t16, t17, t18);
    result__[ 11  ] = (t256 * t273 / 2 + t205 * t276 * t203 + t24 * t279 * t29 * t208 + t259 * t273 / 2 + t37 * t112 * t29 * t208) * t3 + (-t241 * t273 / 2 - t213 * t276 * t203 - t37 * t279 * t29 * t208 + t246 * t273 / 2 + t24 * t112 * t29 * t208) * t34 - 3 * t96 * t133 * t103;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 12, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DHpDp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DHpDp_numCols() const { return 3; }
  integer gtocX_2burn_pars::DHpDp_nnz()     const { return 3; }

  void
  gtocX_2burn_pars::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
  }


  void
  gtocX_2burn_pars::DHpDp_sparse(
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
    real_type t2   = 1 - ModelPars[iM_w_guess];
    real_type t3   = p_guess(0);
    real_type t4   = t3 * t3;
    real_type t11  = ModelPars[iM_time_f] - ModelPars[iM_time_i];
    real_type t12  = P__[iP_p];
    real_type t13  = sqrt(t12);
    real_type t17  = ModelPars[iM_muS];
    real_type t18  = sqrt(t17);
    real_type t19  = 1.0 / t18;
    real_type t20  = t19 / t13 / t12 * t11;
    real_type t21  = ModelPars[iM_w_nonlin];
    real_type t22  = X__[iX_f];
    real_type t23  = X__[iX_g];
    real_type t24  = X__[iX_L];
    real_type t25  = ray(t12, t22, t23, t24);
    real_type t26  = acceleration_r(t25, t17);
    real_type t27  = t26 * t21;
    real_type t28  = sin(t24);
    real_type t34  = t19 / t13 * t11;
    real_type t35  = acceleration_r_D_1(t25, t17);
    real_type t36  = t35 * t21;
    real_type t37  = ray_D_1(t12, t22, t23, t24);
    real_type t42  = t19 * t13 * t11;
    real_type t43  = acceleration_r_D_1_1(t25, t17);
    real_type t44  = t43 * t21;
    real_type t45  = t37 * t37;
    real_type t49  = ray_D_1_1(t12, t22, t23, t24);
    real_type t56  = cos(t24);
    real_type t76  = pow(t56 * t22 + t28 * t23 + 1, 2);
    real_type t77  = t12 * t12;
    result__[ 0   ] = 2 / t4 * t2 + (-t28 * t27 * t20 / 4 + t28 * t37 * t36 * t34 + t28 * t45 * t44 * t42 + t28 * t49 * t36 * t42) * L__[iL_lambda1__xo] + (t56 * t27 * t20 / 4 - t56 * t37 * t36 * t34 - t56 * t45 * t44 * t42 - t56 * t49 * t36 * t42) * L__[iL_lambda2__xo] + 0.15e2 / 4.0 * t18 / t13 / t77 / t12 * t76 * t11 * L__[iL_lambda3__xo];
    result__[ 1   ] = 2 * t2;
    result__[ 2   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHpDp_sparse", 3, i_segment );
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

  integer gtocX_2burn_pars::Hu_numEqns() const { return 0; }

  void
  gtocX_2burn_pars::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DHuDxp_numRows() const { return 0; }
  integer gtocX_2burn_pars::DHuDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DHuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DHuDxp_sparse(
    NodeType2 const    & NODE__,
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn_pars::eta_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DetaDxp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DetaDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DetaDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DetaDxp_sparse(
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

  integer gtocX_2burn_pars::nu_numEqns() const { return 3; }

  void
  gtocX_2burn_pars::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 3, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn_pars::DnuDxp_numRows() const { return 3; }
  integer gtocX_2burn_pars::DnuDxp_numCols() const { return 6; }
  integer gtocX_2burn_pars::DnuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn_pars::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn_pars::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_pars_Methods_AdjointODE.cc
