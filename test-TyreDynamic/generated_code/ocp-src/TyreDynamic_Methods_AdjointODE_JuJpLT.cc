/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_AdjointODE.cc                              |
 |                                                                       |
 |  version: 1.0   date 1/6/2022                                         |
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

  integer TyreDynamic::JP_numEqns() const { return 0; }

  void
  TyreDynamic::JP_eval(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::LT_numEqns() const { return 5; }

  void
  TyreDynamic::LT_eval(
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
    real_type t2   = 1.0 / t1;
    real_type t4   = ModelPars[iM_h__b];
    real_type t6   = OnlyBrakingRear(X__[iX_b] - t4);
    result__[ 0   ] = t6 * t2;
    real_type t9   = OnlyTractionRear(-t4 - X__[iX_p]);
    result__[ 1   ] = t9 * t2;
    real_type t13  = 1.0 / ModelPars[iM_lambda__max] * X__[iX_lambda];
    real_type t15  = LongSlipRear_min(-1 - t13);
    result__[ 2   ] = t15 * t2;
    real_type t17  = LongSlipRear_max(t13 - 1);
    result__[ 3   ] = t17 * t2;
    real_type t19  = v_min(1 - t1);
    result__[ 4   ] = t19 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "LT_eval", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer TyreDynamic::JU_numEqns() const { return 2; }

  void
  TyreDynamic::JU_eval(
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
    real_type t4   = b__oControl(U__[iU_b__o], -1, 1);
    result__[ 0   ] = t4 * t2;
    real_type t6   = p__oControl(U__[iU_p__o], -1, 1);
    result__[ 1   ] = t6 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "JU_eval", 2, i_segment );
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
  integer TyreDynamic::DJPDxpu_numRows() const { return 0; }
  integer TyreDynamic::DJPDxpu_numCols() const { return 7; }
  integer TyreDynamic::DJPDxpu_nnz()     const { return 0; }

  void
  TyreDynamic::DJPDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    // EMPTY!
  }


  void
  TyreDynamic::DJPDxpu_sparse(
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DLTDxpu_numRows() const { return 5; }
  integer TyreDynamic::DLTDxpu_numCols() const { return 7; }
  integer TyreDynamic::DLTDxpu_nnz()     const { return 9; }

  void
  TyreDynamic::DLTDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 4   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 2   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 2   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 3   ; jIndex[6 ] = 0   ;
    iIndex[7 ] = 3   ; jIndex[7 ] = 2   ;
    iIndex[8 ] = 4   ; jIndex[8 ] = 0   ;
  }


  void
  TyreDynamic::DLTDxpu_sparse(
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
    result__[ 0   ] = -t7 * t3;
    real_type t9   = 1.0 / t1;
    real_type t10  = ALIAS_OnlyBrakingRear_D(t6);
    result__[ 1   ] = t10 * t9;
    real_type t12  = -t5 - X__[iX_p];
    real_type t13  = OnlyTractionRear(t12);
    result__[ 2   ] = -t13 * t3;
    real_type t15  = ALIAS_OnlyTractionRear_D(t12);
    result__[ 3   ] = -t15 * t9;
    real_type t18  = 1.0 / ModelPars[iM_lambda__max];
    real_type t20  = X__[iX_lambda] * t18;
    real_type t21  = -1 - t20;
    real_type t22  = LongSlipRear_min(t21);
    result__[ 4   ] = -t22 * t3;
    real_type t24  = ALIAS_LongSlipRear_min_D(t21);
    result__[ 5   ] = -t18 * t24 * t9;
    real_type t27  = t20 - 1;
    real_type t28  = LongSlipRear_max(t27);
    result__[ 6   ] = -t28 * t3;
    real_type t30  = ALIAS_LongSlipRear_max_D(t27);
    result__[ 7   ] = t18 * t30 * t9;
    real_type t32  = 1 - t1;
    real_type t33  = v_min(t32);
    real_type t35  = ALIAS_v_min_D(t32);
    result__[ 8   ] = -t3 * t33 - t35 * t9;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DLTDxpu_sparse", 9, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DJUDxpu_numRows() const { return 2; }
  integer TyreDynamic::DJUDxpu_numCols() const { return 7; }
  integer TyreDynamic::DJUDxpu_nnz()     const { return 4; }

  void
  TyreDynamic::DJUDxpu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 6   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 5   ;
  }


  void
  TyreDynamic::DJUDxpu_sparse(
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
    real_type t4   = U__[iU_b__o];
    real_type t5   = b__oControl(t4, -1, 1);
    result__[ 0   ] = -t5 * t3;
    real_type t7   = 1.0 / t1;
    real_type t8   = ALIAS_b__oControl_D_1(t4, -1, 1);
    result__[ 1   ] = t8 * t7;
    real_type t9   = U__[iU_p__o];
    real_type t10  = p__oControl(t9, -1, 1);
    result__[ 2   ] = -t10 * t3;
    real_type t12  = ALIAS_p__oControl_D_1(t9, -1, 1);
    result__[ 3   ] = t12 * t7;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DJUDxpu_sparse", 4, i_segment );
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
      Mechatronix::check_in_segment( result__, "DLTargsDxpu_sparse", 5, i_segment );
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
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
    real_type t10  = OMEGA__[0];
    real_type t14  = -t6 - X__[iX_p];
    real_type t15  = OnlyTractionRear(t14);
    real_type t17  = OMEGA__[1];
    real_type t20  = ModelPars[iM_lambda__max];
    real_type t21  = 1.0 / t20;
    real_type t23  = X__[iX_lambda] * t21;
    real_type t24  = -1 - t23;
    real_type t25  = LongSlipRear_min(t24);
    real_type t27  = OMEGA__[2];
    real_type t30  = t23 - 1;
    real_type t31  = LongSlipRear_max(t30);
    real_type t33  = OMEGA__[3];
    real_type t36  = 1 - t1;
    real_type t37  = v_min(t36);
    real_type t39  = OMEGA__[4];
    real_type t42  = 1.0 / t2;
    real_type t43  = ALIAS_v_min_D(t36);
    real_type t47  = 1.0 / t1;
    real_type t48  = ALIAS_v_min_DD(t36);
    result__[ 0   ] = 2 * t10 * t8 * t4 + 2 * t17 * t15 * t4 + 2 * t27 * t25 * t4 + 2 * t33 * t31 * t4 + 2 * t39 * t37 * t4 + 2 * t39 * t43 * t42 + t39 * t48 * t47;
    real_type t51  = ALIAS_LongSlipRear_min_D(t24);
    real_type t55  = ALIAS_LongSlipRear_max_D(t30);
    result__[ 1   ] = t27 * t21 * t51 * t42 - t33 * t21 * t55 * t42;
    real_type t59  = ALIAS_OnlyTractionRear_D(t14);
    result__[ 2   ] = t17 * t59 * t42;
    real_type t61  = ALIAS_OnlyBrakingRear_D(t7);
    result__[ 3   ] = -t10 * t61 * t42;
    result__[ 4   ] = result__[1];
    real_type t64  = ALIAS_LongSlipRear_min_DD(t24);
    real_type t66  = t20 * t20;
    real_type t67  = 1.0 / t66;
    real_type t70  = ALIAS_LongSlipRear_max_DD(t30);
    result__[ 5   ] = t27 * t67 * t64 * t47 + t33 * t67 * t70 * t47;
    result__[ 6   ] = result__[2];
    real_type t74  = ALIAS_OnlyTractionRear_DD(t14);
    result__[ 7   ] = t17 * t74 * t47;
    result__[ 8   ] = result__[3];
    real_type t76  = ALIAS_OnlyBrakingRear_DD(t7);
    result__[ 9   ] = t10 * t76 * t47;
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t4   = 1.0 / t2 / t1;
    real_type t5   = U__[iU_b__o];
    real_type t6   = b__oControl(t5, -1, 1);
    real_type t8   = OMEGA__[0];
    real_type t10  = U__[iU_p__o];
    real_type t11  = p__oControl(t10, -1, 1);
    real_type t13  = OMEGA__[1];
    result__[ 0   ] = 2 * t13 * t11 * t4 + 2 * t8 * t6 * t4;
    real_type t16  = 1.0 / t2;
    real_type t17  = ALIAS_p__oControl_D_1(t10, -1, 1);
    result__[ 1   ] = -t13 * t17 * t16;
    real_type t20  = ALIAS_b__oControl_D_1(t5, -1, 1);
    result__[ 2   ] = -t8 * t20 * t16;
    result__[ 3   ] = result__[1];
    real_type t23  = 1.0 / t1;
    real_type t24  = ALIAS_p__oControl_D_1_1(t10, -1, 1);
    result__[ 4   ] = t13 * t24 * t23;
    result__[ 5   ] = result__[2];
    real_type t26  = ALIAS_b__oControl_D_1_1(t5, -1, 1);
    result__[ 6   ] = t8 * t26 * t23;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "D2JUD2xpu_sparse", 7, i_segment );
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
    NodeType const     & NODE__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_const_ptr       OMEGA__,
    real_type            result__[]
  ) const {
    // EMPTY!
  }

}

// EOF: TyreDynamic_Methods_AdjointODE.cc
