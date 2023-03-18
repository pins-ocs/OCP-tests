/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_AdjointODE.cc                              |
 |                                                                       |
 |  version: 1.0   date 20/3/2023                                        |
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
#pragma warning( disable : 4189 )
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

  real_type
  TyreDynamic::JP_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type result__ = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JP_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  TyreDynamic::JU_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1.0 / X__[iX_v];
    real_type t4   = b__oControl(U__[iU_b__o], -1, 1);
    real_type t7   = p__oControl(U__[iU_p__o], -1, 1);
    real_type result__ = t4 * t2 + t7 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "JU_eval", 1, i_segment );
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  real_type
  TyreDynamic::LT_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t4   = ModelPars[iM_h__b];
    real_type t6   = OnlyBrakingRear(X__[iX_b] - t4);
    real_type t10  = OnlyTractionRear(-t4 - X__[iX_p]);
    real_type t15  = 1.0 / ModelPars[iM_lambda__max] * X__[iX_lambda];
    real_type t17  = LongSlipRear_min(-1 - t15);
    real_type t20  = LongSlipRear_max(t15 - 1);
    real_type t23  = v_min(1 - t1);
    real_type result__ = t10 * t2 + t17 * t2 + t20 * t2 + t23 * t2 + t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( &result__, "LT_eval", 1, i_segment );
    return result__;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JPxpu_numEqns() const { return 7; }

  void
  TyreDynamic::JPxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 0;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JPxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JUxpu_numEqns() const { return 7; }

  void
  TyreDynamic::JUxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = U__[iU_b__o];
    real_type t5   = b__oControl(t4, -1, 1);
    real_type t7   = U__[iU_p__o];
    real_type t8   = p__oControl(t7, -1, 1);
    result__[ 0   ] = -t5 * t3 - t8 * t3;
    result__[ 1   ] = 0;
    result__[ 2   ] = 0;
    result__[ 3   ] = 0;
    result__[ 4   ] = 0;
    real_type t10  = 1.0 / t1;
    real_type t11  = ALIAS_p__oControl_D_1(t7, -1, 1);
    result__[ 5   ] = t11 * t10;
    real_type t12  = ALIAS_b__oControl_D_1(t4, -1, 1);
    result__[ 6   ] = t12 * t10;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JUxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LTxpu_numEqns() const { return 7; }

  void
  TyreDynamic::LTxpu_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
    result__[ 5   ] = 0;
    result__[ 6   ] = 0;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LTxpu_eval", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LTargs_numEqns() const { return 5; }

  void
  TyreDynamic::LTargs_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
  integer TyreDynamic::D2JPD2xpu_numRows() const { return 7; }
  integer TyreDynamic::D2JPD2xpu_numCols() const { return 7; }
  integer TyreDynamic::D2JPD2xpu_nnz()     const { return 0; }

  void
  TyreDynamic::D2JPD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::D2JPD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2LTD2xpu_numRows() const { return 7; }
  integer TyreDynamic::D2LTD2xpu_numCols() const { return 7; }
  integer TyreDynamic::D2LTD2xpu_nnz()     const { return 10; }

  void
  TyreDynamic::D2LTD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
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
  TyreDynamic::D2LTD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
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
    result__[ 0   ] = 2 * t13 * t4 + 2 * t21 * t4 + 2 * t25 * t4 + 2 * t29 * t4 + 2 * t33 * t32 + t37 * t36 + 2 * t8 * t4;
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
      Mechatronix::check_in_segment( result__, "D2LTD2xpu_sparse", 10, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2JUD2xpu_numRows() const { return 7; }
  integer TyreDynamic::D2JUD2xpu_numCols() const { return 7; }
  integer TyreDynamic::D2JUD2xpu_nnz()     const { return 7; }

  void
  TyreDynamic::D2JUD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 5   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 6   ;
    iIndex[3 ] = 5   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 5   ; jIndex[4 ] = 5   ;
    iIndex[5 ] = 6   ; jIndex[5 ] = 0   ;
    iIndex[6 ] = 6   ; jIndex[6 ] = 6   ;
  }


  void
  TyreDynamic::D2JUD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t4   = 1.0 / t2 / t1;
    real_type t5   = U__[iU_b__o];
    real_type t6   = b__oControl(t5, -1, 1);
    real_type t8   = U__[iU_p__o];
    real_type t9   = p__oControl(t8, -1, 1);
    result__[ 0   ] = 2 * t6 * t4 + 2 * t9 * t4;
    real_type t12  = 1.0 / t2;
    real_type t13  = ALIAS_p__oControl_D_1(t8, -1, 1);
    result__[ 1   ] = -t13 * t12;
    real_type t15  = ALIAS_b__oControl_D_1(t5, -1, 1);
    result__[ 2   ] = -t15 * t12;
    result__[ 3   ] = result__[1];
    real_type t17  = 1.0 / t1;
    real_type t18  = ALIAS_p__oControl_D_1_1(t8, -1, 1);
    result__[ 4   ] = t18 * t17;
    result__[ 5   ] = result__[2];
    real_type t19  = ALIAS_b__oControl_D_1_1(t5, -1, 1);
    result__[ 6   ] = t19 * t17;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 7, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DLTargsDxpu_numRows() const { return 5; }
  integer TyreDynamic::DLTargsDxpu_numCols() const { return 7; }
  integer TyreDynamic::DLTargsDxpu_nnz()     const { return 5; }

  void
  TyreDynamic::DLTargsDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 4   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 3   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 2   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 0   ;
  }


  void
  TyreDynamic::DLTargsDxpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_ptr       result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    result__[ 0   ] = 1;
    result__[ 1   ] = -1;
    real_type t2   = 1.0 / ModelPars[iM_lambda__max];
    result__[ 2   ] = -t2;
    result__[ 3   ] = t2;
    result__[ 4   ] = -1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 5, i_segment );
  }



  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::D2LTargsD2xpu_numRows() const { return 7; }
  integer TyreDynamic::D2LTargsD2xpu_numCols() const { return 7; }
  integer TyreDynamic::D2LTargsD2xpu_nnz()     const { return 0; }

  void
  TyreDynamic::D2LTargsD2xpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::D2LTargsD2xpu_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    real_const_ptr OMEGA__,
    real_ptr       result__
  ) const {
    // EMPTY!
  }

}

// EOF: TyreDynamic_Methods_AdjointODE.cc
