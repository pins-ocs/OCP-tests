/*-----------------------------------------------------------------------*\
 |  file: gtocX_2burn_Methods_AdjointODE.cc                              |
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


#include "gtocX_2burn.hh"
#include "gtocX_2burn_Pars.hh"

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


namespace gtocX_2burnDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JPx_numEqns() const { return 6; }

  void
  gtocX_2burn::JPx_eval(
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
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::LTx_numEqns() const { return 6; }

  void
  gtocX_2burn::LTx_eval(
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
    real_type t1   = X__[iX_f];
    real_type t2   = X__[iX_L];
    real_type t3   = cos(t2);
    real_type t5   = X__[iX_g];
    real_type t6   = sin(t2);
    real_type t9   = ALIAS_ray_positive_D(-t3 * t1 - t6 * t5 - 1);
    result__[ 1   ] = -t3 * t9;
    result__[ 2   ] = -t6 * t9;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = (t6 * t1 - t3 * t5) * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JUx_numEqns() const { return 6; }

  void
  gtocX_2burn::JUx_eval(
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
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JPp_numEqns() const { return 0; }

  void
  gtocX_2burn::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::LTp_numEqns() const { return 0; }

  void
  gtocX_2burn::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JUp_numEqns() const { return 0; }

  void
  gtocX_2burn::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JPu_numEqns() const { return 0; }

  void
  gtocX_2burn::JPu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::LTu_numEqns() const { return 0; }

  void
  gtocX_2burn::LTu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::JUu_numEqns() const { return 0; }

  void
  gtocX_2burn::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::LTargs_numEqns() const { return 1; }

  void
  gtocX_2burn::LTargs_eval(
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
  integer gtocX_2burn::DJPxDxp_numRows() const { return 6; }
  integer gtocX_2burn::DJPxDxp_numCols() const { return 6; }
  integer gtocX_2burn::DJPxDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DLTxDxp_numRows() const { return 6; }
  integer gtocX_2burn::DLTxDxp_numCols() const { return 6; }
  integer gtocX_2burn::DLTxDxp_nnz()     const { return 9; }

  void
  gtocX_2burn::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 1   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 5   ;
    iIndex[3 ] = 2   ; jIndex[3 ] = 1   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 2   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 5   ;
    iIndex[6 ] = 5   ; jIndex[6 ] = 1   ;
    iIndex[7 ] = 5   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 5   ; jIndex[8 ] = 5   ;
  }


  void
  gtocX_2burn::DLTxDxp_sparse(
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
  integer gtocX_2burn::DJUxDxp_numRows() const { return 6; }
  integer gtocX_2burn::DJUxDxp_numCols() const { return 6; }
  integer gtocX_2burn::DJUxDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DJPuDxp_numRows() const { return 0; }
  integer gtocX_2burn::DJPuDxp_numCols() const { return 6; }
  integer gtocX_2burn::DJPuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DLTuDxp_numRows() const { return 0; }
  integer gtocX_2burn::DLTuDxp_numCols() const { return 6; }
  integer gtocX_2burn::DLTuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DJUuDxp_numRows() const { return 0; }
  integer gtocX_2burn::DJUuDxp_numCols() const { return 6; }
  integer gtocX_2burn::DJUuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DJPpDp_numRows() const { return 0; }
  integer gtocX_2burn::DJPpDp_numCols() const { return 0; }
  integer gtocX_2burn::DJPpDp_nnz()     const { return 0; }

  void
  gtocX_2burn::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DLTpDp_numRows() const { return 0; }
  integer gtocX_2burn::DLTpDp_numCols() const { return 0; }
  integer gtocX_2burn::DLTpDp_nnz()     const { return 0; }

  void
  gtocX_2burn::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DJUpDp_numRows() const { return 0; }
  integer gtocX_2burn::DJUpDp_numCols() const { return 0; }
  integer gtocX_2burn::DJUpDp_nnz()     const { return 0; }

  void
  gtocX_2burn::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DLTargsDxup_numRows() const { return 1; }
  integer gtocX_2burn::DLTargsDxup_numCols() const { return 6; }
  integer gtocX_2burn::DLTargsDxup_nnz()     const { return 3; }

  void
  gtocX_2burn::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 1   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 5   ;
  }


  void
  gtocX_2burn::DLTargsDxup_sparse(
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

  integer gtocX_2burn::Hx_numEqns() const { return 6; }

  void
  gtocX_2burn::Hx_eval(
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
    real_type t3   = X__[iX_p];
    real_type t4   = Q__[iQ_zeta];
    real_type t6   = ModelPars[iM_time_i];
    real_type t8   = ModelPars[iM_time_f];
    real_type t10  = t6 * (1 - t4) + t8 * t4;
    real_type t11  = p_guess(t10);
    real_type t12  = 1.0 / t11;
    real_type t18  = L__[iL_lambda2__xo];
    real_type t19  = t8 - t6;
    real_type t20  = sqrt(t3);
    real_type t23  = ModelPars[iM_muS];
    real_type t24  = sqrt(t23);
    real_type t25  = 1.0 / t24;
    real_type t26  = t25 / t20 * t19;
    real_type t27  = ModelPars[iM_w_nonlin];
    real_type t28  = X__[iX_f];
    real_type t29  = X__[iX_g];
    real_type t30  = X__[iX_L];
    real_type t31  = ray(t3, t28, t29, t30);
    real_type t32  = acceleration_r(t31, t23);
    real_type t33  = t32 * t27;
    real_type t34  = sin(t30);
    real_type t35  = t34 * t33;
    real_type t39  = t25 * t20 * t19;
    real_type t40  = acceleration_r_D_1(t31, t23);
    real_type t41  = t40 * t27;
    real_type t42  = ray_D_1(t3, t28, t29, t30);
    real_type t48  = L__[iL_lambda3__xo];
    real_type t49  = cos(t30);
    real_type t50  = t49 * t33;
    real_type t59  = t19 * L__[iL_lambda6__xo];
    real_type t62  = t49 * t28 + t34 * t29 + 1;
    real_type t63  = t62 * t62;
    real_type t64  = t3 * t3;
    result__[ 0   ] = 2 * t12 * (t12 * t3 - 1) * t2 + (t35 * t26 / 2 + t34 * t42 * t41 * t39) * t18 + (-t50 * t26 / 2 - t49 * t42 * t41 * t39) * t48 - 3.0 / 2.0 * t24 / t20 / t64 * t63 * t59;
    real_type t71  = f_guess(t10);
    real_type t76  = t25 * t20;
    real_type t77  = t76 * t19 * t18;
    real_type t78  = ray_D_2(t3, t28, t29, t30);
    real_type t83  = t76 * t19 * t48;
    real_type t87  = t62 * t59;
    real_type t90  = t24 / t20 / t3;
    result__[ 1   ] = (2 * t28 - 2 * t71) * t2 + t34 * t78 * t41 * t77 - t49 * t78 * t41 * t83 + 2 * t49 * t90 * t87;
    real_type t94  = g_guess(t10);
    real_type t98  = ray_D_3(t3, t28, t29, t30);
    result__[ 2   ] = (2 * t29 - 2 * t94) * t2 + t34 * t98 * t41 * t77 - t49 * t98 * t41 * t83 + 2 * t34 * t90 * t87;
    real_type t109 = h_guess(t10);
    result__[ 3   ] = (2 * X__[iX_h] - 2 * t109) * t2;
    real_type t113 = k_guess(t10);
    result__[ 4   ] = (2 * X__[iX_k] - 2 * t113) * t2;
    real_type t116 = L_guess(t10, t6);
    real_type t120 = ray_D_4(t3, t28, t29, t30);
    result__[ 5   ] = (2 * t30 - 2 * t116) * t2 + (t120 * t34 * t39 * t41 + t39 * t50) * t18 + (-t120 * t39 * t41 * t49 + t35 * t39) * t48 + 2 * (-t28 * t34 + t29 * t49) * t90 * t87;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::Hp_numEqns() const { return 0; }

  void
  gtocX_2burn::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DHxDxp_numRows() const { return 6; }
  integer gtocX_2burn::DHxDxp_numCols() const { return 6; }
  integer gtocX_2burn::DHxDxp_nnz()     const { return 18; }

  void
  gtocX_2burn::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 5   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 5   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 1   ;
    iIndex[10] = 2   ; jIndex[10] = 2   ;
    iIndex[11] = 2   ; jIndex[11] = 5   ;
    iIndex[12] = 3   ; jIndex[12] = 3   ;
    iIndex[13] = 4   ; jIndex[13] = 4   ;
    iIndex[14] = 5   ; jIndex[14] = 0   ;
    iIndex[15] = 5   ; jIndex[15] = 1   ;
    iIndex[16] = 5   ; jIndex[16] = 2   ;
    iIndex[17] = 5   ; jIndex[17] = 5   ;
  }


  void
  gtocX_2burn::DHxDxp_sparse(
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
    real_type t1   = ModelPars[iM_w_guess];
    real_type t2   = 1 - t1;
    real_type t3   = Q__[iQ_zeta];
    real_type t5   = ModelPars[iM_time_i];
    real_type t7   = ModelPars[iM_time_f];
    real_type t10  = p_guess(t5 * (1 - t3) + t7 * t3);
    real_type t11  = t10 * t10;
    real_type t15  = L__[iL_lambda2__xo];
    real_type t16  = t7 - t5;
    real_type t17  = X__[iX_p];
    real_type t18  = sqrt(t17);
    real_type t20  = 1.0 / t18 / t17;
    real_type t22  = ModelPars[iM_muS];
    real_type t23  = sqrt(t22);
    real_type t24  = 1.0 / t23;
    real_type t25  = t24 * t20 * t16;
    real_type t26  = ModelPars[iM_w_nonlin];
    real_type t27  = X__[iX_f];
    real_type t28  = X__[iX_g];
    real_type t29  = X__[iX_L];
    real_type t30  = ray(t17, t27, t28, t29);
    real_type t31  = acceleration_r(t30, t22);
    real_type t32  = t31 * t26;
    real_type t33  = sin(t29);
    real_type t34  = t33 * t32;
    real_type t37  = 1.0 / t18;
    real_type t39  = t24 * t37 * t16;
    real_type t40  = acceleration_r_D_1(t30, t22);
    real_type t41  = t40 * t26;
    real_type t42  = ray_D_1(t17, t27, t28, t29);
    real_type t43  = t33 * t42;
    real_type t44  = t43 * t41;
    real_type t46  = t18 * t16;
    real_type t47  = t24 * t46;
    real_type t48  = acceleration_r_D_1_1(t30, t22);
    real_type t49  = t48 * t26;
    real_type t50  = t42 * t42;
    real_type t54  = ray_D_1_1(t17, t27, t28, t29);
    real_type t60  = L__[iL_lambda3__xo];
    real_type t61  = cos(t29);
    real_type t62  = t61 * t32;
    real_type t65  = t61 * t42;
    real_type t66  = t65 * t41;
    real_type t77  = t16 * L__[iL_lambda6__xo];
    real_type t78  = t61 * t27;
    real_type t79  = t33 * t28;
    real_type t80  = 1 + t78 + t79;
    real_type t81  = t80 * t80;
    real_type t82  = t17 * t17;
    result__[ 0   ] = 2 / t11 * t2 + (-t34 * t25 / 4 + t44 * t39 + t33 * t50 * t49 * t47 + t33 * t54 * t41 * t47) * t15 + (t62 * t25 / 4 - t66 * t39 - t61 * t50 * t49 * t47 - t61 * t54 * t41 * t47) * t60 + 0.15e2 / 4.0 * t23 / t18 / t82 / t17 * t81 * t77;
    real_type t90  = ray_D_2(t17, t27, t28, t29);
    real_type t92  = t33 * t90 * t41;
    real_type t96  = t26 * t24 * t46;
    real_type t97  = t90 * t48;
    real_type t100 = ray_D_1_2(t17, t27, t28, t29);
    real_type t102 = t33 * t100 * t41;
    real_type t107 = t61 * t90 * t41;
    real_type t113 = t61 * t100 * t41;
    real_type t117 = t80 * t77;
    real_type t120 = t23 / t18 / t82;
    real_type t123 = 3 * t61 * t120 * t117;
    result__[ 1   ] = (t92 * t39 / 2 + t43 * t97 * t96 + t102 * t47) * t15 + (-t107 * t39 / 2 - t65 * t97 * t96 - t113 * t47) * t60 - t123;
    real_type t124 = ray_D_3(t17, t27, t28, t29);
    real_type t126 = t33 * t124 * t41;
    real_type t129 = t124 * t48;
    real_type t132 = ray_D_1_3(t17, t27, t28, t29);
    real_type t134 = t33 * t132 * t41;
    real_type t139 = t61 * t124 * t41;
    real_type t145 = t61 * t132 * t41;
    real_type t151 = 3 * t33 * t120 * t117;
    result__[ 2   ] = (t126 * t39 / 2 + t43 * t129 * t96 + t134 * t47) * t15 + (-t139 * t39 / 2 - t65 * t129 * t96 - t145 * t47) * t60 - t151;
    real_type t152 = ray_D_4(t17, t27, t28, t29);
    real_type t153 = t33 * t152;
    real_type t154 = t153 * t41;
    real_type t159 = t152 * t48;
    real_type t162 = ray_D_1_4(t17, t27, t28, t29);
    real_type t169 = t61 * t152;
    real_type t170 = t169 * t41;
    real_type t185 = -t27 * t33 + t28 * t61;
    result__[ 3   ] = (t154 * t39 / 2 + t62 * t39 / 2 + t43 * t159 * t96 + t33 * t162 * t41 * t47 + t66 * t47) * t15 + (-t170 * t39 / 2 + t34 * t39 / 2 - t65 * t159 * t96 - t61 * t162 * t41 * t47 + t44 * t47) * t60 - 3 * t185 * t120 * t117;
    real_type t189 = t16 * t15;
    real_type t190 = t24 * t37;
    real_type t191 = t190 * t189;
    real_type t194 = t24 * t18;
    real_type t195 = t194 * t189;
    real_type t196 = t90 * t42;
    real_type t201 = t16 * t60;
    real_type t202 = t190 * t201;
    real_type t205 = t194 * t201;
    result__[ 4   ] = t92 * t191 / 2 + t33 * t196 * t49 * t195 + t102 * t195 - t107 * t202 / 2 - t61 * t196 * t49 * t205 - t113 * t205 - t123;
    real_type t210 = 2 * t1;
    real_type t211 = t90 * t90;
    real_type t215 = ray_D_2_2(t17, t27, t28, t29);
    real_type t225 = t61 * t61;
    result__[ 5   ] = t195 * t211 * t33 * t49 + t195 * t215 * t33 * t41 + 2 * t20 * t225 * t23 * t77 - t205 * t211 * t49 * t61 - t205 * t215 * t41 * t61 - t210 + 2;
    real_type t230 = t90 * t124;
    real_type t234 = ray_D_2_3(t17, t27, t28, t29);
    real_type t245 = t23 * t20;
    real_type t246 = t61 * t245;
    result__[ 6   ] = t195 * t230 * t33 * t49 + t195 * t234 * t33 * t41 - t205 * t230 * t49 * t61 - t205 * t234 * t41 * t61 + 2 * t246 * t33 * t77;
    real_type t249 = t90 * t152;
    real_type t253 = ray_D_2_4(t17, t27, t28, t29);
    real_type t255 = t33 * t253 * t41;
    real_type t262 = t61 * t253 * t41;
    real_type t265 = t185 * t77;
    real_type t267 = 2 * t246 * t265;
    real_type t268 = t33 * t245;
    real_type t270 = 2 * t268 * t117;
    result__[ 7   ] = t195 * t249 * t33 * t49 - t205 * t249 * t49 * t61 + t107 * t195 + t195 * t255 - t205 * t262 + t205 * t92 + t267 - t270;
    real_type t273 = t124 * t42;
    result__[ 8   ] = t126 * t191 / 2 + t33 * t273 * t49 * t195 + t134 * t195 - t139 * t202 / 2 - t61 * t273 * t49 * t205 - t145 * t205 - t151;
    result__[ 9   ] = result__[6];
    real_type t284 = t124 * t124;
    real_type t288 = ray_D_3_3(t17, t27, t28, t29);
    real_type t298 = t33 * t33;
    result__[ 10  ] = t195 * t284 * t33 * t49 + t195 * t288 * t33 * t41 + 2 * t20 * t23 * t298 * t77 - t205 * t284 * t49 * t61 - t205 * t288 * t41 * t61 - t210 + 2;
    real_type t303 = t124 * t152;
    real_type t307 = ray_D_3_4(t17, t27, t28, t29);
    real_type t309 = t33 * t307 * t41;
    real_type t316 = t61 * t307 * t41;
    real_type t320 = 2 * t268 * t265;
    real_type t322 = 2 * t246 * t117;
    result__[ 11  ] = t195 * t303 * t33 * t49 - t205 * t303 * t49 * t61 + t126 * t205 + t139 * t195 + t195 * t309 - t205 * t316 + t320 + t322;
    result__[ 12  ] = 2 * t2;
    result__[ 13  ] = result__[12];
    result__[ 14  ] = result__[3];
    result__[ 15  ] = (t153 * t96 * t97 + t107 * t47 + t255 * t47) * t15 + (-t169 * t96 * t97 - t262 * t47 + t47 * t92) * t60 + t267 - t270;
    result__[ 16  ] = (t129 * t153 * t96 + t139 * t47 + t309 * t47) * t15 + (-t129 * t169 * t96 + t126 * t47 - t316 * t47) * t60 + t320 + t322;
    real_type t347 = t152 * t152;
    real_type t351 = ray_D_4_4(t17, t27, t28, t29);
    real_type t371 = t185 * t185;
    result__[ 17  ] = 2 - t210 + (t33 * t347 * t47 * t49 + t33 * t351 * t41 * t47 + 2 * t170 * t47 - t34 * t47) * t15 + (-t347 * t47 * t49 * t61 - t351 * t41 * t47 * t61 + 2 * t154 * t47 + t47 * t62) * t60 + 2 * t23 * t20 * t371 * t77 + 2 * (-t78 - t79) * t245 * t117;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 18, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DHpDp_numRows() const { return 0; }
  integer gtocX_2burn::DHpDp_numCols() const { return 0; }
  integer gtocX_2burn::DHpDp_nnz()     const { return 0; }

  void
  gtocX_2burn::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DHpDp_sparse(
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

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer gtocX_2burn::Hu_numEqns() const { return 0; }

  void
  gtocX_2burn::Hu_eval(
    NodeType2 const    & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DHuDxp_numRows() const { return 0; }
  integer gtocX_2burn::DHuDxp_numCols() const { return 6; }
  integer gtocX_2burn::DHuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DHuDxp_sparse(
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

  integer gtocX_2burn::eta_numEqns() const { return 6; }

  void
  gtocX_2burn::eta_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DetaDxp_numRows() const { return 6; }
  integer gtocX_2burn::DetaDxp_numCols() const { return 6; }
  integer gtocX_2burn::DetaDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DetaDxp_sparse(
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

  integer gtocX_2burn::nu_numEqns() const { return 6; }

  void
  gtocX_2burn::nu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 6, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer gtocX_2burn::DnuDxp_numRows() const { return 6; }
  integer gtocX_2burn::DnuDxp_numCols() const { return 6; }
  integer gtocX_2burn::DnuDxp_nnz()     const { return 0; }

  void
  gtocX_2burn::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  gtocX_2burn::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: gtocX_2burn_Methods_AdjointODE.cc
