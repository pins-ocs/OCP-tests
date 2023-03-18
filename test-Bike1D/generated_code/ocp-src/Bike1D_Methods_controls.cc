/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods_controls.cc                                     |
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
   |    __ _
   |   / _` |
   |  | (_| |
   |   \__, |
   |   |___/
  \*/

  real_type
  Bike1D::g_fun_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t3   = U__[iU_mur];
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = murControl(t3, ModelPars[iM_mur_min], t7);
    real_type t10  = U__[iU_muf];
    real_type t12  = mufControl(t10, ModelPars[iM_muf_min], 0);
    real_type t16  = vMinLimit(ModelPars[iM_v_min] - t1);
    real_type result__ = t2 + t8 * t2 + t12 * t2 + t16 * t2 + t2 * (t3 + t10) * MU__[0] * ModelPars[iM_g];
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::g_numEqns() const { return 2; }

  void
  Bike1D::g_eval(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1(U__[iU_mur], ModelPars[iM_mur_min], t7);
    real_type t13  = t2 * ModelPars[iM_g] * MU__[0];
    result__[ 0   ] = t8 * t2 + t13;
    real_type t16  = ALIAS_mufControl_D_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t16 * t2 + t13;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DgDxpm_numRows() const { return 2; }
  integer Bike1D::DgDxpm_numCols() const { return 2; }
  integer Bike1D::DgDxpm_nnz()     const { return 4; }

  void
  Bike1D::DgDxpm_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDxpm_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = U__[iU_mur];
    real_type t5   = ModelPars[iM_mur_min];
    real_type t6   = Tmax_normalized(t1);
    real_type t7   = ModelPars[iM_mur_max];
    real_type t8   = clip(t6, 0, t7);
    real_type t9   = ALIAS_murControl_D_1(t4, t5, t8);
    real_type t11  = 1.0 / t1;
    real_type t12  = ALIAS_murControl_D_1_3(t4, t5, t8);
    real_type t14  = ALIAS_clip_D_1(t6, 0, t7);
    real_type t15  = Tmax_normalized_D(t1);
    real_type t19  = ModelPars[iM_g];
    real_type t21  = t3 * t19 * MU__[0];
    result__[ 0   ] = t15 * t14 * t12 * t11 - t9 * t3 - t21;
    result__[ 1   ] = t11 * t19;
    real_type t24  = ALIAS_mufControl_D_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 2   ] = -t24 * t3 - t21;
    result__[ 3   ] = result__[1];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxpm_sparse", 4, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DgDu_numRows() const { return 2; }
  integer Bike1D::DgDu_numCols() const { return 2; }
  integer Bike1D::DgDu_nnz()     const { return 2; }

  void
  Bike1D::DgDu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 1   ; jIndex[1 ] = 1   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDu_sparse(
    NodeQX const &  NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_const_p_type  U__,
    real_ptr        result__
  ) const {
    integer i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1_1(U__[iU_mur], ModelPars[iM_mur_min], t7);
    result__[ 0   ] = t8 * t2;
    real_type t11  = ALIAS_mufControl_D_1_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t11 * t2;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDu_sparse", 2, i_segment );
  }

  /*\
   |   ____            _             _
   |  / ___|___  _ __ | |_ _ __ ___ | |___
   | | |   / _ \| '_ \| __| '__/ _ \| / __|
   | | |__| (_) | | | | |_| | | (_) | \__ \
   |  \____\___/|_| |_|\__|_|  \___/|_|___/
  \*/

  /*\
   |                      _
   |  _  _   _____ ____ _| |
   | | || | / -_) V / _` | |
   |  \_,_|_\___|\_/\__,_|_|
   |     |___|
  \*/

  void
  Bike1D::u_eval_analytic(
    NodeQXL const & NODE__,
    P_const_p_type  P__,
    MU_const_p_type MU__,
    U_p_type        U__
  ) const {
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    real_const_ptr L__ = NODE__.lambda;
    integer i_segment = NODE__.i_segment;
    MeshStd::SegmentClass const & segment = m_pMesh->get_segment_by_index(i_segment);
    real_type t3   = MU__[0] * ModelPars[iM_g];
    real_type t6   = Tmax_normalized(X__[iX_v]);
    real_type t8   = clip(t6, 0, ModelPars[iM_mur_max]);
    U__[ iU_mur ] = mufControl.solve(-t3, ModelPars[iM_mur_min], t8);
    U__[ iU_muf ] = mufControl.solve(-t3, ModelPars[iM_muf_min], 0);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

}

// EOF: Bike1D_Methods_controls.cc
