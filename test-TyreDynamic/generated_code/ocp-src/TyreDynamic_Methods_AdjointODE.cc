/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_AdjointODE.cc                              |
 |                                                                       |
 |  version: 1.0   date 5/4/2022                                         |
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


#include "TyreDynamic.hh"
#include "TyreDynamic_Pars.hh"

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
#define ALIAS_abs_reg_DD(__t1) abs_reg.DD( __t1)
#define ALIAS_abs_reg_D(__t1) abs_reg.D( __t1)
#define ALIAS_sign_reg_DD(__t1) sign_reg.DD( __t1)
#define ALIAS_sign_reg_D(__t1) sign_reg.D( __t1)
#define ALIAS_clipInt_D_3(__t1, __t2, __t3) clipInt.D_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2(__t1, __t2, __t3) clipInt.D_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1(__t1, __t2, __t3) clipInt.D_1( __t1, __t2, __t3)
#define ALIAS_clipInt_D_3_3(__t1, __t2, __t3) clipInt.D_3_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_3(__t1, __t2, __t3) clipInt.D_2_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_2_2(__t1, __t2, __t3) clipInt.D_2_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_3(__t1, __t2, __t3) clipInt.D_1_3( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_2(__t1, __t2, __t3) clipInt.D_1_2( __t1, __t2, __t3)
#define ALIAS_clipInt_D_1_1(__t1, __t2, __t3) clipInt.D_1_1( __t1, __t2, __t3)
#define ALIAS_clipSup_D_2(__t1, __t2) clipSup.D_2( __t1, __t2)
#define ALIAS_clipSup_D_1(__t1, __t2) clipSup.D_1( __t1, __t2)
#define ALIAS_clipSup_D_2_2(__t1, __t2) clipSup.D_2_2( __t1, __t2)
#define ALIAS_clipSup_D_1_2(__t1, __t2) clipSup.D_1_2( __t1, __t2)
#define ALIAS_clipSup_D_1_1(__t1, __t2) clipSup.D_1_1( __t1, __t2)
#define ALIAS_negPart_DD(__t1) negPart.DD( __t1)
#define ALIAS_negPart_D(__t1) negPart.D( __t1)
#define ALIAS_posPart_DD(__t1) posPart.DD( __t1)
#define ALIAS_posPart_D(__t1) posPart.D( __t1)
#define ALIAS_v_min_DD(__t1) v_min.DD( __t1)
#define ALIAS_v_min_D(__t1) v_min.D( __t1)
#define ALIAS_LongSlipRear_max_DD(__t1) LongSlipRear_max.DD( __t1)
#define ALIAS_LongSlipRear_max_D(__t1) LongSlipRear_max.D( __t1)
#define ALIAS_LongSlipRear_min_DD(__t1) LongSlipRear_min.DD( __t1)
#define ALIAS_LongSlipRear_min_D(__t1) LongSlipRear_min.D( __t1)
#define ALIAS_OnlyTractionRear_DD(__t1) OnlyTractionRear.DD( __t1)
#define ALIAS_OnlyTractionRear_D(__t1) OnlyTractionRear.D( __t1)
#define ALIAS_OnlyBrakingRear_DD(__t1) OnlyBrakingRear.DD( __t1)
#define ALIAS_OnlyBrakingRear_D(__t1) OnlyBrakingRear.D( __t1)
#define ALIAS_p__oControl_D_3(__t1, __t2, __t3) p__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2(__t1, __t2, __t3) p__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1(__t1, __t2, __t3) p__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_3_3(__t1, __t2, __t3) p__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_3(__t1, __t2, __t3) p__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_2_2(__t1, __t2, __t3) p__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_3(__t1, __t2, __t3) p__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_2(__t1, __t2, __t3) p__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_p__oControl_D_1_1(__t1, __t2, __t3) p__oControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3(__t1, __t2, __t3) b__oControl.D_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2(__t1, __t2, __t3) b__oControl.D_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1(__t1, __t2, __t3) b__oControl.D_1( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_3_3(__t1, __t2, __t3) b__oControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_3(__t1, __t2, __t3) b__oControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_2_2(__t1, __t2, __t3) b__oControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_3(__t1, __t2, __t3) b__oControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_2(__t1, __t2, __t3) b__oControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_b__oControl_D_1_1(__t1, __t2, __t3) b__oControl.D_1_1( __t1, __t2, __t3)


namespace TyreDynamicDefine {

  /*\
   |   ____                  _ _   _
   |  |  _ \ ___ _ __   __ _| | |_(_) ___  ___
   |  | |_) / _ \ '_ \ / _` | | __| |/ _ \/ __|
   |  |  __/  __/ | | | (_| | | |_| |  __/\__ \
   |  |_|   \___|_| |_|\__,_|_|\__|_|\___||___/
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JPx_numEqns() const { return 5; }

  void
  TyreDynamic::JPx_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LTx_numEqns() const { return 5; }

  void
  TyreDynamic::LTx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t5   = ModelPars[iM_h__b];
    real_type t6   = X__[iX_b] - t5;
    real_type t7   = OnlyBrakingRear(t6);
    real_type t10  = -t5 - X__[iX_p];
    real_type t11  = OnlyTractionRear(t10);
    real_type t14  = 1.0 / ModelPars[iM_lambda__max];
    real_type t16  = X__[iX_lambda] * t14;
    real_type t17  = -1 - t16;
    real_type t18  = LongSlipRear_min(t17);
    real_type t20  = t16 - 1;
    real_type t21  = LongSlipRear_max(t20);
    real_type t23  = 1 - t1;
    real_type t24  = v_min(t23);
    real_type t26  = 1.0 / t1;
    real_type t27  = ALIAS_v_min_D(t23);
    result__[ 0   ] = -t11 * t3 - t18 * t3 - t21 * t3 - t24 * t3 - t27 * t26 - t7 * t3;
    result__[ 1   ] = 0;
    real_type t29  = ALIAS_LongSlipRear_min_D(t17);
    real_type t32  = ALIAS_LongSlipRear_max_D(t20);
    result__[ 2   ] = -t14 * t29 * t26 + t14 * t32 * t26;
    real_type t35  = ALIAS_OnlyTractionRear_D(t10);
    result__[ 3   ] = -t35 * t26;
    real_type t37  = ALIAS_OnlyBrakingRear_D(t6);
    result__[ 4   ] = t37 * t26;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JUx_numEqns() const { return 5; }

  void
  TyreDynamic::JUx_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v] * X__[iX_v];
    real_type t3   = 1.0 / t2;
    real_type t5   = b__oControl(U__[iU_b__o], -1, 1);
    real_type t8   = p__oControl(U__[iU_p__o], -1, 1);
    result__[ 0   ] = -t5 * t3 - t8 * t3;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JPp_numEqns() const { return 0; }

  void
  TyreDynamic::JPp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LTp_numEqns() const { return 0; }

  void
  TyreDynamic::LTp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JUp_numEqns() const { return 0; }

  void
  TyreDynamic::JUp_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JPu_numEqns() const { return 2; }

  void
  TyreDynamic::JPu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LTu_numEqns() const { return 2; }

  void
  TyreDynamic::LTu_eval(
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
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JUu_numEqns() const { return 2; }

  void
  TyreDynamic::JUu_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1.0 / X__[iX_v];
    real_type t4   = ALIAS_p__oControl_D_1(U__[iU_p__o], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = ALIAS_b__oControl_D_1(U__[iU_b__o], -1, 1);
    result__[ 1   ] = t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LTargs_numEqns() const { return 5; }

  void
  TyreDynamic::LTargs_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = ModelPars[iM_h__b];
    result__[ 0   ] = X__[iX_b] - t2;
    result__[ 1   ] = -t2 - X__[iX_p];
    real_type t7   = 1.0 / ModelPars[iM_lambda__max] * X__[iX_lambda];
    result__[ 2   ] = -1 - t7;
    result__[ 3   ] = t7 - 1;
    result__[ 4   ] = 1 - X__[iX_v];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTargs_eval", 5, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJPxDxp_numRows() const { return 5; }
  integer TyreDynamic::DJPxDxp_numCols() const { return 5; }
  integer TyreDynamic::DJPxDxp_nnz()     const { return 0; }

  void
  TyreDynamic::DJPxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DJPxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DLTxDxp_numRows() const { return 5; }
  integer TyreDynamic::DLTxDxp_numCols() const { return 5; }
  integer TyreDynamic::DLTxDxp_nnz()     const { return 10; }

  void
  TyreDynamic::DLTxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 3   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 4   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 3   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
    iIndex[9 ] = 4   ; jIndex[9 ] = 4   ;
  }


  void
  TyreDynamic::DLTxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t4   = 1.0 / t2 / t1;
    real_type t6   = ModelPars[iM_h__b];
    real_type t7   = X__[iX_b] - t6;
    real_type t8   = OnlyBrakingRear(t7);
    real_type t12  = -t6 - X__[iX_p];
    real_type t13  = OnlyTractionRear(t12);
    real_type t16  = ModelPars[iM_lambda__max];
    real_type t17  = 1.0 / t16;
    real_type t19  = X__[iX_lambda] * t17;
    real_type t20  = -1 - t19;
    real_type t21  = LongSlipRear_min(t20);
    real_type t24  = t19 - 1;
    real_type t25  = LongSlipRear_max(t24);
    real_type t28  = 1 - t1;
    real_type t29  = v_min(t28);
    real_type t32  = 1.0 / t2;
    real_type t33  = ALIAS_v_min_D(t28);
    real_type t36  = 1.0 / t1;
    real_type t37  = ALIAS_v_min_DD(t28);
    result__[ 0   ] = 2 * t13 * t4 + 2 * t21 * t4 + 2 * t25 * t4 + 2 * t29 * t4 + 2 * t33 * t32 + t37 * t36 + 2 * t4 * t8;
    real_type t39  = ALIAS_LongSlipRear_min_D(t20);
    real_type t42  = ALIAS_LongSlipRear_max_D(t24);
    result__[ 1   ] = t17 * t39 * t32 - t17 * t42 * t32;
    real_type t45  = ALIAS_OnlyTractionRear_D(t12);
    result__[ 2   ] = t45 * t32;
    real_type t46  = ALIAS_OnlyBrakingRear_D(t7);
    result__[ 3   ] = -t46 * t32;
    result__[ 4   ] = result__[1];
    real_type t48  = ALIAS_LongSlipRear_min_DD(t20);
    real_type t50  = t16 * t16;
    real_type t51  = 1.0 / t50;
    real_type t53  = ALIAS_LongSlipRear_max_DD(t24);
    result__[ 5   ] = t51 * t48 * t36 + t51 * t53 * t36;
    result__[ 6   ] = result__[2];
    real_type t56  = ALIAS_OnlyTractionRear_DD(t12);
    result__[ 7   ] = t56 * t36;
    result__[ 8   ] = result__[3];
    real_type t57  = ALIAS_OnlyBrakingRear_DD(t7);
    result__[ 9   ] = t57 * t36;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTxDxp_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJUxDxp_numRows() const { return 5; }
  integer TyreDynamic::DJUxDxp_numCols() const { return 5; }
  integer TyreDynamic::DJUxDxp_nnz()     const { return 1; }

  void
  TyreDynamic::DJUxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
  }


  void
  TyreDynamic::DJUxDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t4   = 1.0 / t2 / t1;
    real_type t6   = b__oControl(U__[iU_b__o], -1, 1);
    real_type t9   = p__oControl(U__[iU_p__o], -1, 1);
    result__[ 0   ] = 2 * t6 * t4 + 2 * t9 * t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUxDxp_sparse", 1, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJPuDxp_numRows() const { return 2; }
  integer TyreDynamic::DJPuDxp_numCols() const { return 5; }
  integer TyreDynamic::DJPuDxp_nnz()     const { return 0; }

  void
  TyreDynamic::DJPuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DJPuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DLTuDxp_numRows() const { return 2; }
  integer TyreDynamic::DLTuDxp_numCols() const { return 5; }
  integer TyreDynamic::DLTuDxp_nnz()     const { return 0; }

  void
  TyreDynamic::DLTuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DLTuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJUuDxp_numRows() const { return 2; }
  integer TyreDynamic::DJUuDxp_numCols() const { return 5; }
  integer TyreDynamic::DJUuDxp_nnz()     const { return 2; }

  void
  TyreDynamic::DJUuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }


  void
  TyreDynamic::DJUuDxp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = X__[iX_v] * X__[iX_v];
    real_type t3   = 1.0 / t2;
    real_type t5   = ALIAS_p__oControl_D_1(U__[iU_p__o], -1, 1);
    result__[ 0   ] = -t5 * t3;
    real_type t8   = ALIAS_b__oControl_D_1(U__[iU_b__o], -1, 1);
    result__[ 1   ] = -t8 * t3;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUuDxp_sparse", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJPpDp_numRows() const { return 0; }
  integer TyreDynamic::DJPpDp_numCols() const { return 0; }
  integer TyreDynamic::DJPpDp_nnz()     const { return 0; }

  void
  TyreDynamic::DJPpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DJPpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DLTpDp_numRows() const { return 0; }
  integer TyreDynamic::DLTpDp_numCols() const { return 0; }
  integer TyreDynamic::DLTpDp_nnz()     const { return 0; }

  void
  TyreDynamic::DLTpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DLTpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJUpDp_numRows() const { return 0; }
  integer TyreDynamic::DJUpDp_numCols() const { return 0; }
  integer TyreDynamic::DJUpDp_nnz()     const { return 0; }

  void
  TyreDynamic::DJUpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DJUpDp_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DLTargsDxup_numRows() const { return 5; }
  integer TyreDynamic::DLTargsDxup_numCols() const { return 7; }
  integer TyreDynamic::DLTargsDxup_nnz()     const { return 5; }

  void
  TyreDynamic::DLTargsDxup_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
  }


  void
  TyreDynamic::DLTargsDxup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    real_type t2   = 1.0 / ModelPars[iM_lambda__max];
    result__[ 2   ] = -t2;
    result__[ 3   ] = t2;
    result__[ 4   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxup_sparse", 5, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2LTargsD2xup_numRows() const { return 7; }
  integer TyreDynamic::D2LTargsD2xup_numCols() const { return 7; }
  integer TyreDynamic::D2LTargsD2xup_nnz()     const { return 0; }

  void
  TyreDynamic::D2LTargsD2xup_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::D2LTargsD2xup_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
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

  integer TyreDynamic::Hx_numEqns() const { return 5; }

  void
  TyreDynamic::Hx_eval(
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
    real_type t3   = U__[iU_p__o] * U__[iU_p__o];
    real_type t5   = U__[iU_b__o] * U__[iU_b__o];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t14  = L__[iL_lambda1__xo];
    real_type t15  = Fa_D(t10);
    real_type t17  = L__[iL_lambda3__xo];
    real_type t18  = X__[iX_omega];
    real_type t19  = kappa__w(t10, t18);
    real_type t20  = X__[iX_lambda];
    real_type t23  = t10 * t17;
    real_type t24  = kappa__w_D_1(t10, t18);
    real_type t30  = L__[iL_lambda2__xo];
    real_type t39  = L__[iL_lambda4__xo];
    real_type t44  = L__[iL_lambda5__xo];
    result__[ 0   ] = -1.0 / t11 * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5)) - t15 * t14 + (t19 - t20) * t17 + t24 * t23 - V__[0] * ModelPars[iM_m] * t14 - V__[1] * ModelPars[iM_Iw] * t30 - V__[2] * ModelPars[iM_l__x] * t17 - V__[3] * ModelPars[iM_tau__p] * t39 - V__[4] * ModelPars[iM_tau__b] * t44;
    real_type t49  = X__[iX_p];
    real_type t50  = p__pos(t49);
    real_type t51  = TT_D_2(t50, t18);
    real_type t52  = X__[iX_b];
    real_type t53  = b__neg(t52);
    real_type t54  = TB_D_2(t53, t18);
    real_type t55  = Ma_D(t18);
    real_type t58  = kappa__w_D_2(t10, t18);
    result__[ 1   ] = (t51 + t54 + t55) * t30 + t58 * t23;
    real_type t60  = F__x_D(t20);
    result__[ 2   ] = -ModelPars[iM_rw] * t60 * t30 + t60 * t14 - t23;
    real_type t65  = TT_D_1(t50, t18);
    real_type t67  = p__pos_D(t49);
    result__[ 3   ] = t67 * t65 * t30 - t39;
    real_type t69  = TB_D_1(t53, t18);
    real_type t71  = b__neg_D(t52);
    result__[ 4   ] = t71 * t69 * t30 - t44;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hx_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::Hp_numEqns() const { return 0; }

  void
  TyreDynamic::Hp_eval(
    NodeType2 const    & NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DHxDxp_numRows() const { return 5; }
  integer TyreDynamic::DHxDxp_numCols() const { return 5; }
  integer TyreDynamic::DHxDxp_nnz()     const { return 13; }

  void
  TyreDynamic::DHxDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 3   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 4   ;
    iIndex[7 ] = 2   ; jIndex[7 ] = 0   ;
    iIndex[8 ] = 2   ; jIndex[8 ] = 2   ;
    iIndex[9 ] = 3   ; jIndex[9 ] = 1   ;
    iIndex[10] = 3   ; jIndex[10] = 3   ;
    iIndex[11] = 4   ; jIndex[11] = 1   ;
    iIndex[12] = 4   ; jIndex[12] = 4   ;
  }


  void
  TyreDynamic::DHxDxp_sparse(
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
    real_type t3   = U__[iU_p__o] * U__[iU_p__o];
    real_type t5   = U__[iU_b__o] * U__[iU_b__o];
    real_type t10  = X__[iX_v];
    real_type t11  = t10 * t10;
    real_type t16  = L__[iL_lambda1__xo];
    real_type t17  = Fa_DD(t10);
    real_type t19  = L__[iL_lambda3__xo];
    real_type t20  = X__[iX_omega];
    real_type t21  = kappa__w_D_1(t10, t20);
    real_type t24  = t10 * t19;
    real_type t25  = kappa__w_D_1_1(t10, t20);
    result__[ 0   ] = 2 / t11 / t10 * (ModelPars[iM_w__t] + ModelPars[iM_w__U] * (t3 + t5)) - t17 * t16 + 2 * t21 * t19 + t25 * t24;
    real_type t27  = kappa__w_D_2(t10, t20);
    real_type t29  = kappa__w_D_1_2(t10, t20);
    result__[ 1   ] = t27 * t19 + t29 * t24;
    result__[ 2   ] = -t19;
    result__[ 3   ] = result__[1];
    real_type t31  = L__[iL_lambda2__xo];
    real_type t32  = X__[iX_p];
    real_type t33  = p__pos(t32);
    real_type t34  = TT_D_2_2(t33, t20);
    real_type t35  = X__[iX_b];
    real_type t36  = b__neg(t35);
    real_type t37  = TB_D_2_2(t36, t20);
    real_type t38  = Ma_DD(t20);
    real_type t41  = kappa__w_D_2_2(t10, t20);
    result__[ 4   ] = (t34 + t37 + t38) * t31 + t41 * t24;
    real_type t43  = TT_D_1_2(t33, t20);
    real_type t45  = p__pos_D(t32);
    result__[ 5   ] = t45 * t43 * t31;
    real_type t46  = TB_D_1_2(t36, t20);
    real_type t48  = b__neg_D(t35);
    result__[ 6   ] = t48 * t46 * t31;
    result__[ 7   ] = result__[2];
    real_type t50  = F__x_DD(X__[iX_lambda]);
    result__[ 8   ] = -ModelPars[iM_rw] * t50 * t31 + t50 * t16;
    result__[ 9   ] = result__[5];
    real_type t55  = TT_D_1_1(t33, t20);
    real_type t57  = t45 * t45;
    real_type t59  = TT_D_1(t33, t20);
    real_type t61  = p__pos_DD(t32);
    result__[ 10  ] = t57 * t55 * t31 + t61 * t59 * t31;
    result__[ 11  ] = result__[6];
    real_type t63  = TB_D_1_1(t36, t20);
    real_type t65  = t48 * t48;
    real_type t67  = TB_D_1(t36, t20);
    real_type t69  = b__neg_DD(t35);
    result__[ 12  ] = t65 * t63 * t31 + t69 * t67 * t31;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxDxp_sparse", 13, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DHpDp_numRows() const { return 0; }
  integer TyreDynamic::DHpDp_numCols() const { return 0; }
  integer TyreDynamic::DHpDp_nnz()     const { return 0; }

  void
  TyreDynamic::DHpDp_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DHpDp_sparse(
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

  integer TyreDynamic::Hu_numEqns() const { return 2; }

  void
  TyreDynamic::Hu_eval(
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
    real_type t2   = ModelPars[iM_w__U];
    real_type t5   = 1.0 / X__[iX_v];
    result__[ 0   ] = 2 * t5 * t2 * U__[iU_p__o] + L__[iL_lambda4__xo];
    result__[ 1   ] = 2 * t5 * t2 * U__[iU_b__o] + L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DHuDxp_numRows() const { return 2; }
  integer TyreDynamic::DHuDxp_numCols() const { return 5; }
  integer TyreDynamic::DHuDxp_nnz()     const { return 2; }

  void
  TyreDynamic::DHuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
  }


  void
  TyreDynamic::DHuDxp_sparse(
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
    real_type t2   = ModelPars[iM_w__U];
    real_type t5   = X__[iX_v] * X__[iX_v];
    real_type t6   = 1.0 / t5;
    result__[ 0   ] = -2 * t6 * t2 * U__[iU_p__o];
    result__[ 1   ] = -2 * t6 * t2 * U__[iU_b__o];
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"DHuDxp_sparse", 2, i_segment );
  }

  /*\
   |        _
   |    ___| |_ __ _
   |   / _ \ __/ _` |
   |  |  __/ || (_| |
   |   \___|\__\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::eta_numEqns() const { return 5; }

  void
  TyreDynamic::eta_eval(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    result__[ 0   ] = L__[iL_lambda1__xo] * ModelPars[iM_m] * t1;
    result__[ 1   ] = L__[iL_lambda2__xo] * t1 * ModelPars[iM_Iw];
    result__[ 2   ] = L__[iL_lambda3__xo] * ModelPars[iM_l__x] * t1;
    result__[ 3   ] = L__[iL_lambda4__xo] * ModelPars[iM_tau__p] * t1;
    result__[ 4   ] = L__[iL_lambda5__xo] * ModelPars[iM_tau__b] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__,"eta_eval",5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DetaDxp_numRows() const { return 5; }
  integer TyreDynamic::DetaDxp_numCols() const { return 5; }
  integer TyreDynamic::DetaDxp_nnz()     const { return 5; }

  void
  TyreDynamic::DetaDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
  }


  void
  TyreDynamic::DetaDxp_sparse(
    NodeType2 const    & NODE__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_m] * L__[iL_lambda1__xo];
    result__[ 1   ] = ModelPars[iM_Iw] * L__[iL_lambda2__xo];
    result__[ 2   ] = ModelPars[iM_l__x] * L__[iL_lambda3__xo];
    result__[ 3   ] = ModelPars[iM_tau__p] * L__[iL_lambda4__xo];
    result__[ 4   ] = ModelPars[iM_tau__b] * L__[iL_lambda5__xo];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DetaDxp_sparse", 5, i_segment );
  }

  /*\
   |    _ __  _   _
   |   | '_ \| | | |
   |   | | | | |_| |
   |   |_| |_|\__,_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::nu_numEqns() const { return 5; }

  void
  TyreDynamic::nu_eval(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    result__[ 0   ] = V__[0] * ModelPars[iM_m] * t1;
    result__[ 1   ] = V__[1] * t1 * ModelPars[iM_Iw];
    result__[ 2   ] = V__[2] * ModelPars[iM_l__x] * t1;
    result__[ 3   ] = V__[3] * ModelPars[iM_tau__p] * t1;
    result__[ 4   ] = V__[4] * ModelPars[iM_tau__b] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "nu_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DnuDxp_numRows() const { return 5; }
  integer TyreDynamic::DnuDxp_numCols() const { return 5; }
  integer TyreDynamic::DnuDxp_nnz()     const { return 5; }

  void
  TyreDynamic::DnuDxp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 0   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
  }


  void
  TyreDynamic::DnuDxp_sparse(
    NodeType const     & NODE__,
    V_const_pointer_type V__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = ModelPars[iM_m] * V__[0];
    result__[ 1   ] = ModelPars[iM_Iw] * V__[1];
    result__[ 2   ] = ModelPars[iM_l__x] * V__[2];
    result__[ 3   ] = ModelPars[iM_tau__p] * V__[3];
    result__[ 4   ] = ModelPars[iM_tau__b] * V__[4];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DnuDxp_sparse", 5, i_segment );
  }

}

// EOF: TyreDynamic_Methods_AdjointODE.cc
