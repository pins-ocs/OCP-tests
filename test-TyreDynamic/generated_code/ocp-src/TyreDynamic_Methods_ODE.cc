/*-----------------------------------------------------------------------*\
 |  file: TyreDynamic_Methods_ODE.cc                                     |
 |                                                                       |
 |  version: 1.0   date 9/5/2023                                         |
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
   |    ___  ___  ___
   |   / _ \|   \| __|
   |  | (_) | |) | _|
   |   \___/|___/|___|
  \*/

  integer TyreDynamic::ode_numEqns() const { return 5; }

  void
  TyreDynamic::ode_eval(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_lambda];
    real_type t2   = F__x(t1);
    real_type t3   = X__[iX_v];
    real_type t4   = Fa(t3);
    result__[ 0   ] = -V__[0] * ModelPars[iM_m] * t3 + t2 - t4;
    real_type t9   = X__[iX_p];
    real_type t10  = p__pos(t9);
    real_type t11  = X__[iX_omega];
    real_type t12  = TT(t10, t11);
    real_type t13  = X__[iX_b];
    real_type t14  = b__neg(t13);
    real_type t15  = TB(t14, t11);
    real_type t18  = Ma(t11);
    result__[ 1   ] = -V__[1] * t3 * ModelPars[iM_Iw] - ModelPars[iM_rw] * t2 + t12 + t15 + t18;
    real_type t23  = kappa__w(t3, t11);
    result__[ 2   ] = (t23 - t1) * t3 - V__[2] * ModelPars[iM_l__x] * t3;
    result__[ 3   ] = -V__[3] * ModelPars[iM_tau__p] * t3 - t9 + U__[iU_p__o];
    result__[ 4   ] = -V__[4] * ModelPars[iM_tau__b] * t3 - t13 + U__[iU_b__o];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "ode", 5, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::DodeDxpuv_numRows() const { return 5; }
  integer TyreDynamic::DodeDxpuv_numCols() const { return 12; }
  integer TyreDynamic::DodeDxpuv_nnz()     const { return 21; }

  void
  TyreDynamic::DodeDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 2   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 7   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 0   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 1   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 2   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 3   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 4   ;
    iIndex[8 ] = 1   ; jIndex[8 ] = 8   ;
    iIndex[9 ] = 2   ; jIndex[9 ] = 0   ;
    iIndex[10] = 2   ; jIndex[10] = 1   ;
    iIndex[11] = 2   ; jIndex[11] = 2   ;
    iIndex[12] = 2   ; jIndex[12] = 9   ;
    iIndex[13] = 3   ; jIndex[13] = 0   ;
    iIndex[14] = 3   ; jIndex[14] = 3   ;
    iIndex[15] = 3   ; jIndex[15] = 5   ;
    iIndex[16] = 3   ; jIndex[16] = 10  ;
    iIndex[17] = 4   ; jIndex[17] = 0   ;
    iIndex[18] = 4   ; jIndex[18] = 4   ;
    iIndex[19] = 4   ; jIndex[19] = 6   ;
    iIndex[20] = 4   ; jIndex[20] = 11  ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::DodeDxpuv_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    U_const_p_type U__,
    V_const_p_type V__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = Fa_D(t1);
    real_type t3   = ModelPars[iM_m];
    result__[ 0   ] = -V__[0] * t3 - t2;
    real_type t6   = X__[iX_lambda];
    result__[ 1   ] = F__x_D(t6);
    result__[ 2   ] = -t3 * t1;
    real_type t8   = ModelPars[iM_Iw];
    result__[ 3   ] = -V__[1] * t8;
    real_type t11  = X__[iX_p];
    real_type t12  = p__pos(t11);
    real_type t13  = X__[iX_omega];
    real_type t14  = TT_D_2(t12, t13);
    real_type t15  = X__[iX_b];
    real_type t16  = b__neg(t15);
    real_type t17  = TB_D_2(t16, t13);
    real_type t18  = Ma_D(t13);
    result__[ 4   ] = t14 + t17 + t18;
    result__[ 5   ] = -ModelPars[iM_rw] * result__[1];
    real_type t21  = TT_D_1(t12, t13);
    real_type t22  = p__pos_D(t11);
    result__[ 6   ] = t22 * t21;
    real_type t23  = TB_D_1(t16, t13);
    real_type t24  = b__neg_D(t15);
    result__[ 7   ] = t24 * t23;
    result__[ 8   ] = -t1 * t8;
    real_type t26  = kappa__w(t1, t13);
    real_type t27  = kappa__w_D_1(t1, t13);
    real_type t29  = ModelPars[iM_l__x];
    result__[ 9   ] = t27 * t1 - V__[2] * t29 + t26 - t6;
    real_type t32  = kappa__w_D_2(t1, t13);
    result__[ 10  ] = t32 * t1;
    result__[ 11  ] = -t1;
    result__[ 12  ] = -t29 * t1;
    real_type t34  = ModelPars[iM_tau__p];
    result__[ 13  ] = -V__[3] * t34;
    result__[ 14  ] = -1;
    result__[ 15  ] = 1;
    result__[ 16  ] = -t34 * t1;
    real_type t38  = ModelPars[iM_tau__b];
    result__[ 17  ] = -V__[4] * t38;
    result__[ 18  ] = -1;
    result__[ 19  ] = 1;
    result__[ 20  ] = -t38 * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DodeDxpuv_sparse", 21, i_segment );
  }

  /*\
   |   __  __              __  __      _       _
   |  |  \/  |__ _ ______ |  \/  |__ _| |_ _ _(_)_ __
   |  | |\/| / _` (_-<_-< | |\/| / _` |  _| '_| \ \ /
   |  |_|  |_\__,_/__/__/ |_|  |_\__,_|\__|_| |_/_\_\
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer TyreDynamic::A_numRows() const { return 5; }
  integer TyreDynamic::A_numCols() const { return 5; }
  integer TyreDynamic::A_nnz()     const { return 5; }

  void
  TyreDynamic::A_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 2   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 3   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 4   ; jIndex[4 ] = 4   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  TyreDynamic::A_sparse(
    NodeQX const & NODE__,
    P_const_p_type P__,
    real_ptr       result__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    result__[ 0   ] = ModelPars[iM_m] * t1;
    result__[ 1   ] = t1 * ModelPars[iM_Iw];
    result__[ 2   ] = ModelPars[iM_l__x] * t1;
    result__[ 3   ] = ModelPars[iM_tau__p] * t1;
    result__[ 4   ] = ModelPars[iM_tau__b] * t1;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "A_sparse", 5, i_segment );
  }

}

// EOF: TyreDynamic_Methods_ODE.cc
