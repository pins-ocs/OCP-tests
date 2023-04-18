/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods_AdjointODE.cc                                   |
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


#include "Bike1D.hh"
#include "Bike1D_Pars.hh"

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
#define ALIAS_clip_D_3(__t1, __t2, __t3) clip.D_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2(__t1, __t2, __t3) clip.D_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1(__t1, __t2, __t3) clip.D_1( __t1, __t2, __t3)
#define ALIAS_clip_D_3_3(__t1, __t2, __t3) clip.D_3_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_3(__t1, __t2, __t3) clip.D_2_3( __t1, __t2, __t3)
#define ALIAS_clip_D_2_2(__t1, __t2, __t3) clip.D_2_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_3(__t1, __t2, __t3) clip.D_1_3( __t1, __t2, __t3)
#define ALIAS_clip_D_1_2(__t1, __t2, __t3) clip.D_1_2( __t1, __t2, __t3)
#define ALIAS_clip_D_1_1(__t1, __t2, __t3) clip.D_1_1( __t1, __t2, __t3)
#define ALIAS_vMinLimit_DD(__t1) vMinLimit.DD( __t1)
#define ALIAS_vMinLimit_D(__t1) vMinLimit.D( __t1)
#define ALIAS_mufControl_D_3(__t1, __t2, __t3) mufControl.D_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2(__t1, __t2, __t3) mufControl.D_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1(__t1, __t2, __t3) mufControl.D_1( __t1, __t2, __t3)
#define ALIAS_mufControl_D_3_3(__t1, __t2, __t3) mufControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_3(__t1, __t2, __t3) mufControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_2_2(__t1, __t2, __t3) mufControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_3(__t1, __t2, __t3) mufControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_2(__t1, __t2, __t3) mufControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_mufControl_D_1_1(__t1, __t2, __t3) mufControl.D_1_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3(__t1, __t2, __t3) murControl.D_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2(__t1, __t2, __t3) murControl.D_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1(__t1, __t2, __t3) murControl.D_1( __t1, __t2, __t3)
#define ALIAS_murControl_D_3_3(__t1, __t2, __t3) murControl.D_3_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_3(__t1, __t2, __t3) murControl.D_2_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_2_2(__t1, __t2, __t3) murControl.D_2_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_3(__t1, __t2, __t3) murControl.D_1_3( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_2(__t1, __t2, __t3) murControl.D_1_2( __t1, __t2, __t3)
#define ALIAS_murControl_D_1_1(__t1, __t2, __t3) murControl.D_1_1( __t1, __t2, __t3)


namespace Bike1DDefine {

  /*\
   |   _   _
   |  | | | |_  ___ __  _   _
   |  | |_| \ \/ / '_ \| | | |
   |  |  _  |>  <| |_) | |_| |
   |  |_| |_/_/\_\ .__/ \__,_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::Hxp_numEqns() const { return 1; }

  void
  Bike1D::Hxp_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = U__[iU_mur];
    real_type t5   = ModelPars[iM_mur_min];
    real_type t6   = Tmax_normalized(t1);
    real_type t7   = ModelPars[iM_mur_max];
    real_type t8   = clip(t6, 0, t7);
    real_type t9   = murControl(t4, t5, t8);
    real_type t11  = 1.0 / t1;
    real_type t12  = ALIAS_murControl_D_3(t4, t5, t8);
    real_type t14  = ALIAS_clip_D_1(t6, 0, t7);
    real_type t15  = Tmax_normalized_D(t1);
    real_type t18  = U__[iU_muf];
    real_type t20  = mufControl(t18, ModelPars[iM_muf_min], 0);
    real_type t23  = ModelPars[iM_v_min] - t1;
    real_type t24  = vMinLimit(t23);
    real_type t26  = ALIAS_vMinLimit_D(t23);
    result__[ 0   ] = -t3 - t9 * t3 + t15 * t14 * t12 * t11 - t20 * t3 - t24 * t3 - t26 * t11 - t3 * (t4 + t18) * MU__[0] * ModelPars[iM_g];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "Hxp_eval", 1, i_segment );
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DHxpDxpuv_numRows() const { return 1; }
  integer Bike1D::DHxpDxpuv_numCols() const { return 4; }
  integer Bike1D::DHxpDxpuv_nnz()     const { return 3; }

  void
  Bike1D::DHxpDxpuv_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
  }


  void
  Bike1D::DHxpDxpuv_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    V_const_p_type  V__,
    real_ptr        result__
  ) const {
    integer i_segment  = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t4   = 1.0 / t2 / t1;
    real_type t6   = U__[iU_mur];
    real_type t7   = ModelPars[iM_mur_min];
    real_type t8   = Tmax_normalized(t1);
    real_type t9   = ModelPars[iM_mur_max];
    real_type t10  = clip(t8, 0, t9);
    real_type t11  = murControl(t6, t7, t10);
    real_type t14  = 1.0 / t2;
    real_type t15  = ALIAS_murControl_D_3(t6, t7, t10);
    real_type t17  = ALIAS_clip_D_1(t8, 0, t9);
    real_type t18  = Tmax_normalized_D(t1);
    real_type t19  = t18 * t17;
    real_type t22  = 1.0 / t1;
    real_type t23  = ALIAS_murControl_D_3_3(t6, t7, t10);
    real_type t25  = t17 * t17;
    real_type t26  = t18 * t18;
    real_type t29  = t15 * t22;
    real_type t30  = ALIAS_clip_D_1_1(t8, 0, t9);
    real_type t33  = Tmax_normalized_DD(t1);
    real_type t36  = U__[iU_muf];
    real_type t37  = ModelPars[iM_muf_min];
    real_type t38  = mufControl(t36, t37, 0);
    real_type t42  = ModelPars[iM_v_min] - t1;
    real_type t43  = vMinLimit(t42);
    real_type t46  = ALIAS_vMinLimit_D(t42);
    real_type t49  = ALIAS_vMinLimit_DD(t42);
    real_type t53  = MU__[0] * ModelPars[iM_g];
    result__[ 0   ] = 2 * t4 + 2 * t11 * t4 - 2 * t19 * t15 * t14 + t26 * t25 * t23 * t22 + t26 * t30 * t29 + t33 * t17 * t29 + 2 * t38 * t4 + 2 * t43 * t4 + 2 * t46 * t14 + t49 * t22 + 2 * t4 * (t6 + t36) * t53;
    real_type t58  = ALIAS_murControl_D_1(t6, t7, t10);
    real_type t60  = ALIAS_murControl_D_1_3(t6, t7, t10);
    real_type t63  = t14 * t53;
    result__[ 1   ] = t19 * t60 * t22 - t58 * t14 - t63;
    real_type t64  = ALIAS_mufControl_D_1(t36, t37, 0);
    result__[ 2   ] = -t64 * t14 - t63;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DHxpDxpuv_sparse", 3, i_segment );
  }

}

// EOF: Bike1D_Methods_AdjointODE.cc
