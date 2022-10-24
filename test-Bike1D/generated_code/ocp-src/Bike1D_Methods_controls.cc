/*-----------------------------------------------------------------------*\
 |  file: Bike1D_Methods_controls.cc                                     |
 |                                                                       |
 |  version: 1.0   date 10/11/2022                                       |
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
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[1], LM__[1];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t6   = UM__[0];
    real_type t7   = UM__[1];
    real_type t13  = Tmax_normalized(XM__[0]);
    real_type t15  = clip(t13, 0, ModelPars[iM_mur_max]);
    real_type t16  = murControl(t6, ModelPars[iM_mur_min], t15);
    real_type t19  = mufControl(t7, ModelPars[iM_muf_min], 0);
    real_type t21  = ModelPars[iM_v_min];
    real_type t23  = vMinLimit(t21 - t1);
    real_type t25  = XR__[iX_v];
    real_type t26  = 1.0 / t25;
    real_type t30  = vMinLimit(t21 - t25);
    real_type result__ = t2 + 2 * (t6 + t7) * ModelPars[iM_g] * LM__[0] + t16 * t2 + t19 * t2 + t23 * t2 + t26 + t16 * t26 + t19 * t26 + t30 * t26;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "g_fun_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::g_numEqns() const { return 2; }

  void
  Bike1D::g_eval(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[1], LM__[1];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t4   = 2 * LM__[0] * ModelPars[iM_g];
    real_type t6   = 1.0 / XL__[iX_v];
    real_type t10  = Tmax_normalized(XM__[0]);
    real_type t12  = clip(t10, 0, ModelPars[iM_mur_max]);
    real_type t13  = ALIAS_murControl_D_1(UM__[0], ModelPars[iM_mur_min], t12);
    real_type t16  = 1.0 / XR__[iX_v];
    result__[ 0   ] = t13 * t16 + t13 * t6 + t4;
    real_type t20  = ALIAS_mufControl_D_1(UM__[1], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t20 * t16 + t20 * t6 + t4;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "g_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DgDxlxlp_numRows() const { return 2; }
  integer Bike1D::DgDxlxlp_numCols() const { return 4; }
  integer Bike1D::DgDxlxlp_nnz()     const { return 8; }

  void
  Bike1D::DgDxlxlp_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 0   ; jIndex[2 ] = 2   ;
    iIndex[3 ] = 0   ; jIndex[3 ] = 3   ;
    iIndex[4 ] = 1   ; jIndex[4 ] = 0   ;
    iIndex[5 ] = 1   ; jIndex[5 ] = 1   ;
    iIndex[6 ] = 1   ; jIndex[6 ] = 2   ;
    iIndex[7 ] = 1   ; jIndex[7 ] = 3   ;
  }


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  Bike1D::DgDxlxlp_sparse(
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[1], LM__[1];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_v];
    real_type t2   = t1 * t1;
    real_type t3   = 1.0 / t2;
    real_type t4   = UM__[0];
    real_type t5   = ModelPars[iM_mur_min];
    real_type t6   = XM__[0];
    real_type t7   = Tmax_normalized(t6);
    real_type t8   = ModelPars[iM_mur_max];
    real_type t9   = clip(t7, 0, t8);
    real_type t10  = ALIAS_murControl_D_1(t4, t5, t9);
    real_type t13  = ALIAS_murControl_D_1_3(t4, t5, t9);
    real_type t15  = ALIAS_clip_D_1(t7, 0, t8);
    real_type t16  = Tmax_normalized_D(t6);
    real_type t17  = t16 * t15;
    real_type t19  = 0.5e0 * t17 * t13 / t1;
    real_type t20  = XR__[iX_v];
    real_type t24  = 0.5e0 * t17 * t13 / t20;
    result__[ 0   ] = -t10 * t3 + t19 + t24;
    result__[ 1   ] = 0.10e1 * ModelPars[iM_g];
    real_type t26  = t20 * t20;
    real_type t27  = 1.0 / t26;
    result__[ 2   ] = -t10 * t27 + t19 + t24;
    result__[ 3   ] = result__[1];
    real_type t31  = ALIAS_mufControl_D_1(UM__[1], ModelPars[iM_muf_min], 0);
    result__[ 4   ] = -t31 * t3;
    result__[ 5   ] = result__[3];
    result__[ 6   ] = -t31 * t27;
    result__[ 7   ] = result__[5];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DgDxlxlp_sparse", 8, i_segment );
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
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    U_const_pointer_type UM__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer i_segment = LEFT__.i_segment;
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[1], LM__[1];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t2   = 1.0 / XL__[iX_v];
    real_type t6   = Tmax_normalized(XM__[0]);
    real_type t8   = clip(t6, 0, ModelPars[iM_mur_max]);
    real_type t9   = ALIAS_murControl_D_1_1(UM__[0], ModelPars[iM_mur_min], t8);
    real_type t12  = 1.0 / XR__[iX_v];
    result__[ 0   ] = t9 * t12 + t9 * t2;
    real_type t16  = ALIAS_mufControl_D_1_1(UM__[1], ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t16 * t12 + t16 * t2;
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
    NodeType2 const &    LEFT__,
    NodeType2 const &    RIGHT__,
    P_const_pointer_type P__,
    U_pointer_type       U__
  ) const {
    real_const_ptr QL__ = LEFT__.q;
    real_const_ptr XL__ = LEFT__.x;
    real_const_ptr LL__ = LEFT__.lambda;
    real_const_ptr QR__ = RIGHT__.q;
    real_const_ptr XR__ = RIGHT__.x;
    real_const_ptr LR__ = RIGHT__.lambda;
    // midpoint
    real_type QM__[1], XM__[1], LM__[1];
    // Qvars
    QM__[0] = (QL__[0]+QR__[0])/2;
    // Xvars
    XM__[0] = (XL__[0]+XR__[0])/2;
    // Lvars
    LM__[0] = (LL__[0]+LR__[0])/2;
    integer i_segment = LEFT__.i_segment;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = XL__[iX_v];
    real_type t2   = XR__[iX_v];
    real_type t11  = 2 * t2 * t1 * ModelPars[iM_g] * LM__[0] / (t1 + t2);
    real_type t14  = Tmax_normalized(XM__[0]);
    real_type t16  = clip(t14, 0, ModelPars[iM_mur_max]);
    U__[ iU_mur ] = mufControl.solve(-t11, ModelPars[iM_mur_min], t16);
    U__[ iU_muf ] = mufControl.solve(-t11, ModelPars[iM_muf_min], 0);
    if ( m_debug )
      Mechatronix::check( U__.pointer(), "u_eval_analytic", 2 );
  }

  /*\
  :|:   ___         _           _   ___    _   _            _
  :|:  / __|___ _ _| |_ _ _ ___| | | __|__| |_(_)_ __  __ _| |_ ___
  :|: | (__/ _ \ ' \  _| '_/ _ \ | | _|(_-<  _| | '  \/ _` |  _/ -_)
  :|:  \___\___/_||_\__|_| \___/_| |___/__/\__|_|_|_|_\__,_|\__\___|
  \*/

  real_type
  Bike1D::m_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t3   = U__[iU_mur];
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = murControl(t3, ModelPars[iM_mur_min], t7);
    real_type t10  = U__[iU_muf];
    real_type t12  = mufControl(t10, ModelPars[iM_muf_min], 0);
    real_type t16  = vMinLimit(ModelPars[iM_v_min] - t1);
    real_type t24  = pow(V__[0] * t1 - (t3 + t10) * ModelPars[iM_g], 2);
    real_type result__ = t12 * t2 + t16 * t2 + t8 * t2 + t24;
    if ( m_debug ) {
      UTILS_ASSERT( Utils::is_finite(result__), "m_eval(...) return {}\n", result__ );
    }
    return result__;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  integer Bike1D::DmDu_numEqns() const { return 2; }

  void
  Bike1D::DmDu_eval(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t3   = U__[iU_mur];
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1(t3, ModelPars[iM_mur_min], t7);
    real_type t12  = ModelPars[iM_g];
    real_type t13  = U__[iU_muf];
    real_type t18  = 2 * t12 * (V__[0] * t1 - (t3 + t13) * t12);
    result__[ 0   ] = t8 * t2 - t18;
    real_type t20  = ALIAS_mufControl_D_1(t13, ModelPars[iM_muf_min], 0);
    result__[ 1   ] = t20 * t2 - t18;
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDu_eval", 2, i_segment );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  integer Bike1D::DmDuu_numRows() const { return 2; }
  integer Bike1D::DmDuu_numCols() const { return 2; }
  integer Bike1D::DmDuu_nnz()     const { return 4; }

  void
  Bike1D::DmDuu_pattern( integer iIndex[], integer jIndex[] ) const {
    iIndex[0 ] = 0   ; jIndex[0 ] = 0   ;
    iIndex[1 ] = 0   ; jIndex[1 ] = 1   ;
    iIndex[2 ] = 1   ; jIndex[2 ] = 0   ;
    iIndex[3 ] = 1   ; jIndex[3 ] = 1   ;
  }


  void
  Bike1D::DmDuu_sparse(
    NodeType const &     NODE__,
    V_const_pointer_type V__,
    U_const_pointer_type U__,
    P_const_pointer_type P__,
    real_type            result__[]
  ) const {
    integer  i_segment = NODE__.i_segment;
    real_const_ptr Q__ = NODE__.q;
    real_const_ptr X__ = NODE__.x;
    MeshStd::SegmentClass const & segment = pMesh->get_segment_by_index(i_segment);
    real_type t1   = X__[iX_v];
    real_type t2   = 1.0 / t1;
    real_type t5   = Tmax_normalized(t1);
    real_type t7   = clip(t5, 0, ModelPars[iM_mur_max]);
    real_type t8   = ALIAS_murControl_D_1_1(U__[iU_mur], ModelPars[iM_mur_min], t7);
    real_type t11  = ModelPars[iM_g] * ModelPars[iM_g];
    real_type t12  = 2 * t11;
    result__[ 0   ] = t8 * t2 + t12;
    result__[ 1   ] = t12;
    result__[ 2   ] = result__[1];
    real_type t15  = ALIAS_mufControl_D_1_1(U__[iU_muf], ModelPars[iM_muf_min], 0);
    result__[ 3   ] = t15 * t2 + result__[2];
    if ( m_debug )
      Mechatronix::check_in_segment( result__, "DmDuu_sparse", 4, i_segment );
  }

}

// EOF: Bike1D_Methods_controls.cc
